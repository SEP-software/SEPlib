#include "glplot.h"
#ifdef USE_PROTO
#define A1(FTYP,SUF) \
int gl_transp ## SUF (float *x, float* y, struct datainfo ## SUF *data)
#else
#define A1(FTYP,SUF) \
int gl_transp ## SUF (x, y, data) \
    float          *x, *y; \
    struct datainfo ## SUF *data;
#endif
#define A2(FTYP,FMT,SUF) \
{ \
float          *xyexch; \
int             i, tempalloc, tempval; \
 \
    tempalloc = 0; \
    for (i = 0; i < data->n2; i++) \
    { \
	tempalloc = tempalloc + data->n1[i]; \
    } \
    xyexch = (float *) calloc ((data->esize / 2) * (tempalloc), sizeof (float)); \
	tempval = 0; \
    for (i = 0; i < data->n2; i++) \
    { \
	tempval = tempval + data->n1[i]; \
    } \
 \
    for (i = 0; i < tempval; i++) \
    { \
	xyexch[i] = x[i]; \
	x[i] = y[i]; \
	y[i] = xyexch[i]; \
    } \
 \
return 0; \
}

A1(float, )
A2(float,"f", )

A1(double,_g)
A2(double,"g",_g)
