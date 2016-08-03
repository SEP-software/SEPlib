#include <sitedef.h>
#if defined (HAVE_MOTIF) || defined(HAVE_ATHENA)
#include <stdio.h>
#include "main.h"
#include "axis.h"
#include "map.h"

Buffer edit_buffer = 0;
Vec edit_vec = 0;
int edit_size = 0;

/* extract frame of data, given frame */
EditFrame (data,map1,map2,map3,frame,dist)
Buffer data;
Map map1, map2, map3;
int frame;
float dist[256];
	{
	int inc2, i2, len1, len2;
	register int inc1;
	register Buffer data1, edata;

	inc1 = AxisStride (MapAxis (map1));
	inc2 = AxisStride (MapAxis (map2));
	len1 = MapWindow (map1) - 1;
	len2 = MapWindow (map2) - 1;
	data+=frame * AxisStride (MapAxis (map3)) + MapLow (map1) * inc1 + MapLow (map2) * inc2;
	for (i2=0; i2<len2; i2++, data+=inc2) {
		for (data1=data, edata=data1+inc1*len1; data1<edata; data1+=inc1) {
			dist[*data1] += 1.;
			}
		}
	return (len1*len2);
	}

/* extract six frames of a box, given three map axes */
EditBox (data,map1,map2,map3,dist)
Buffer data;
Map map1, map2, map3;
float dist[256];
	{
	int n = 0, i;

	for (i=0; i<256; i++) dist[i] = 0.;
	n+=EditFrame (data,map1,map2,map3,MapLow(map3),dist);
	n+=EditFrame (data,map1,map2,map3,MapHigh(map3),dist);
	n+=EditFrame (data,map2,map3,map1,MapLow(map1),dist);
	n+=EditFrame (data,map2,map3,map1,MapHigh(map1),dist);
	n+=EditFrame (data,map3,map1,map2,MapLow(map2),dist);
	n+=EditFrame (data,map3,map1,map2,MapHigh(map2),dist);
	return (n);
	}

/* return data distribution and stats given buffer */
EditStats (n,dist,low,median,high)
float *dist;
int n, *low, *median, *high;
	{
	int i;

	for (i=0, *low=-1, *median=-1, *high=0; i<256; i++) {
		if (i<255 && dist[i+1] > 0.) *high = i+1;
		if (i<255) dist[i+1]+=dist[i];
		dist[i] /= n;
		if (dist[i] > 0. && *low == -1) *low = i;
		if (dist[i] > .5 && *median == -1) *median = i;
		}
	}

/* extract sub volume given three map axes */
EditCube (data,map1,map2,map3,dist)
Buffer data;
Map map1, map2, map3;
float dist[256];
	{
	int i2, i3, inc2, inc3, len1, len2, len3, i;
        register int inc1;
	Buffer data2;
        register Buffer data1, edata;

        inc1 = AxisStride (MapAxis (map1));
        inc2 = AxisStride (MapAxis (map2));
        inc3 = AxisStride (MapAxis (map3));
	len1 = MapWindow (map1);
	len2 = MapWindow (map2);
	for (i=0; i<256; i++) dist[i] = 0.;
	len3 = MapWindow (map3);
        data+=MapLow(map3) * inc3 + MapLow (map2) * inc2 + MapLow (map1) * inc1;
        for (i3=0; i3<len3; i3++, data+=inc3) {
		for (i2=0, data2=data; i2<len2; i2++, data2+=inc2) {
			for (data1=data2, edata=data1+inc1*len1; data1<edata; data1+=inc1) {
				dist[*data1] += 1.;
				}
			}
		}
	return (len1*len2*len3);
	}

/* 3-D linear grade blemish repair; save backup */
EditGrade (data,map1,map2,map3)
Buffer data;
Map map1, map2, map3;
	{
	Buffer bufferp;
	Vec vecp;
	register Buffer datap;
	int off, d1, d2, d3;
	register int n1, n2, n3, e1, e2, e3, j1, j2, j3, i1, i2, i3;

	d1 = AxisStride(MapAxis(map1));
	d2 = AxisStride(MapAxis(map2));
	d3 = AxisStride(MapAxis(map3));
	n1 = MapWindow(map1);
	n2 = MapWindow(map2);
	n3 = MapWindow(map3);
	e1 = n1 * d1 - d1;
	e2 = n2 * d2 - d2;
	e3 = n3 * d3 - d3;
	off = MapLow(map1) * d1 + MapLow(map2) * d2 + MapLow(map3) * d3;
	datap = data + off;
	edit_size = (n1-2) * (n2-2) * (n3-2);
	if (edit_size < 1) return;
	FREE (edit_buffer);
	FREE (edit_vec);
	NEW (Buffer,edit_buffer,edit_size);
	NEW (Vec,edit_vec,edit_size);
	bufferp = edit_buffer;
	vecp = edit_vec;
	n1--;
	n2--;
	n3--;
	for (i1=1; i1<n1; i1++) {
	j1 = i1 * d1;
	for (i2=1; i2<n2; i2++) {
	j2 = i2 * d2;
	for (i3=1; i3<n3; i3++) {
	j3 = i3 * d3;
		*bufferp++ = datap[j1+j2+j3];
		*vecp++ = off + j1 + j2 + j3;
		datap[j1+j2+j3] = (
		((n1-i1) * (int)(datap[j2+j3]) + i1 * (int)(datap[e1+j2+j3])) / n1 +
		((n2-i2) * (int)(datap[j1+j3]) + i2 * (int)(datap[j1+e2+j3])) / n2 +
		((n3-i3) * (int)(datap[j1+j2]) + i3 * (int)(datap[j1+j2+e3])) / n3 )/3;
		}
		}
		}
	}

EditUndo (data)
Buffer data;
	{
	register Buffer bufferp, datap, endp;
	register Vec vecp;
	register int swap;

	for (bufferp=edit_buffer, vecp=edit_vec, datap=data, endp=edit_buffer+edit_size;
		bufferp<endp; bufferp++, vecp++) {
		swap = *bufferp;
		*bufferp = datap[*vecp];
		datap[*vecp] = swap;
		}
	}
#endif
