/* segykml < segyfile coords=[latlong,utm] [utmzone=] [> utmconv.segy] */
/* Creates files shots.kml receivers.kml and midpoints.kml */
/* in current directory */

#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include "GeodeticCoordinates.h"
#include "UTMCoordinates.h"
#include "UTM.h"
#include <tdb.h>

typedef
struct {
  double longitude;
  double latitude;
} coords;

static void addPoint(coords *pt, FILE *fp)
{
    fputs("\t<Placemark>\n",fp);
    fprintf(fp,"\t<Point>\n\t\t<coordinates>%12.6f,%12.6f</coordinates>\n\t</Point>\n",
            pt->longitude, pt->latitude);
    fputs("\t</Placemark>\n",fp);
}

int main(int argc, char **argv)
{
   int rc;

  int i,j;
  size_t ntrace = 0;
  size_t ntrace_limit = -1;
  int trlen;
  ssize_t nread, nwrite;
  int16_t coord_scale;
  int16_t coord_units;
  int32_t sx, sy, gx, gy;
  double sxd, syd, gxd, gyd, mxd, myd;
  double dtmp, etmp, scaleit;
  int8_t *inhdr, *inhdr1;
  int16_t *s2hd;
  uint16_t *u2hd;
  int32_t *s4hd;
  uint32_t *u4hd;
  float *f4hd;
  double *f8hd;
  union {
     int32_t i;
     int16_t s[2];
  } endiantest;
#define IMLITTLEENDIAN endiantest.s[0] != 0
  struct tdb_context *shotDB, *receiverDB, *midpointDB;
  TDB_DATA xyKey, xyVal;
  double datumpair[2]; /* long, lat */
  coords latLong;
  double degrees, minutes, seconds;
  const double deg_to_rad = 0.017453292519943295;
  FILE *fp;
  char ctmp[BUFSIZ];
  int utmzone = 0;
  enum CRS {
     CRSUNDEFINED = 0,
     CRSLATLONG = 1,
     CRSUTM = 2
  } crsConvert;
  double RadToDeg = 57.295779513082320876;

  xyKey.dptr = (unsigned char *) (&(datumpair[0]));
  xyKey.dsize = (size_t) sizeof(datumpair);
  xyVal.dptr = (unsigned char *) (&(datumpair[0]));
  xyVal.dsize = (size_t) 0;

  MSP::CCS::GeodeticCoordinates* geod = new MSP::CCS::GeodeticCoordinates();
  MSP::CCS::UTMCoordinates* utmxy = new MSP::CCS::UTMCoordinates();
  MSP::CCS::UTM* myutm =  new MSP::CCS::UTM();

  endiantest.i = 1;

  if(isatty(fileno(stdin))) {
    fprintf(stderr,"syntax: %s < segyfile coords=[latlong,utm] [utmzone=] [utmhemisphere='N'] [> utmconv.segy])\n", argv[0]);
    fprintf(stderr,"        %s Creates files shots.kml receivers.kml and midpoints.kml in current directory\n", argv[0]);
    fprintf(stderr,"        %s Optionally writes output segy with UTM coords\n", argv[0]);
    return (EXIT_FAILURE);
  }

/* Decode arguments */
  utmxy->setHemisphere('N');
  for(i=1; i<argc; ++i) {
     if(0 == strncmp(argv[i],"coords=",7)) {
        if(0 == strcmp(argv[i]+7,"latlong")) crsConvert = CRSLATLONG;
        if(0 == strcmp(argv[i]+7,"utm")) crsConvert = CRSUTM;
     }
     if(0 == strncmp(argv[i],"utmzone=",8)) {
        utmzone = atoi(argv[i]+8);
        utmxy->setZone(utmzone);     
     }
     if(0 == strncmp(argv[i],"utmhemisphere=",14)) {
        utmxy->setHemisphere(*(argv[i]+14));
     }
  }

/* allocate buffer and alias to various datatypes */
  inhdr1 = (int8_t *) malloc(2*400);
  if(inhdr1 == ((int8_t *) NULL)) {
    perror(argv[0]);
    fprintf(stderr,"Unable to allocate trace header array\n");
    return (EXIT_FAILURE);
  }
  if(IMLITTLEENDIAN) inhdr = inhdr1+400;
  else inhdr = inhdr1;
  s2hd = (int16_t *) inhdr;
  u2hd = (uint16_t *) inhdr;
  s4hd = (int32_t *) inhdr;
  u4hd = (uint32_t *) inhdr;
  f4hd = (float *) inhdr;
  f8hd = (double *) inhdr;

  shotDB = tdb_open("./.segykml_shot.tdb",0,TDB_CLEAR_IF_FIRST|TDB_NOLOCK|TDB_NOMMAP|TDB_NOSYNC, O_RDWR|O_CREAT|O_TRUNC|O_LARGEFILE, 0664);
  if(shotDB == NULL) {
     fprintf(stderr,"%s: %s\n",argv[0],tdb_errorstr(shotDB));
     return(EXIT_FAILURE);
  }
  receiverDB = tdb_open("./.segykml_receiver.tdb",0,TDB_CLEAR_IF_FIRST|TDB_NOLOCK|TDB_NOMMAP|TDB_NOSYNC, O_RDWR|O_CREAT|O_TRUNC|O_LARGEFILE, 0664);
  if(receiverDB == NULL) {
     fprintf(stderr,"%s: %s\n",argv[0],tdb_errorstr(shotDB));
     return(EXIT_FAILURE);
  }
  midpointDB = tdb_open("./.segykml_midpoint.tdb",0,TDB_CLEAR_IF_FIRST|TDB_NOLOCK|TDB_NOMMAP|TDB_NOSYNC, O_RDWR|O_CREAT|O_TRUNC|O_LARGEFILE, 0664);
  if(midpointDB == NULL) {
     fprintf(stderr,"%s: %s\n",argv[0],tdb_errorstr(shotDB));
     return(EXIT_FAILURE);
  }

  /* done initializing */

  /* read and handl card image */ 
  if(isatty(fileno(stdout))) {
      for(i=0; i<3200; ++i) (void) getc(stdin);
  } else {
      for(i=0; i<3200; ++i) putc(getc(stdin), stdout);
  }

  /* extract trace length from binary reel header */ 
  nread = fread(inhdr1,1,400,stdin);
  if(!isatty(fileno(stdout)))
      nwrite = fwrite(inhdr1,1,400,stdout);
  if(IMLITTLEENDIAN) {
      swab(inhdr1,u2hd,26);
  }
      
  trlen = u2hd[10];
  switch (u2hd[12]) {
  case 1:
  case 2:
  case 4:
  case 5:
      trlen *= 4;
      break;
  case 3:
      trlen *= 2;
      break;
  }

  /* now process headers, toss trace data */
  do {
     nread = fread(inhdr1,1,240,stdin);
     if(nread < 240) break;
     ++ntrace;
     if(IMLITTLEENDIAN) swab(inhdr1, inhdr, 240);
   
     coord_scale = s2hd[35];
     if(coord_scale == 0) coord_scale = 1;

     coord_units = s2hd[44];
     if(coord_units == 0) coord_units = 1; /* assume UTM x, y */
     if(coord_units == 1) crsConvert = CRSUTM;
     else crsConvert = CRSLATLONG;

     if(IMLITTLEENDIAN) {
        for(i=0; i<120; i += 2){
           j = s2hd[i]; 
           s2hd[i] = s2hd[i+1];
           s2hd[i+1] = j;
        }
     }

     sx = s4hd[18]; sy=s4hd[19]; gx=s4hd[20]; gy=s4hd[21];

     sxd = (double) sx; syd = (double) sy;
     gxd = (double) gx; gyd = (double) gy;

     if(coord_scale > 0) dtmp = (double) coord_scale;
     else                dtmp = -1.0/((double) coord_scale);

     sxd *= dtmp; syd *= dtmp; gxd *= dtmp; gyd *= dtmp;
     mxd = 0.5*(sxd+gxd); myd = 0.5*(syd+gyd);

     switch (coord_units) {
     case 2:
        dtmp = 1.0/3600.0;
        sxd *= dtmp; syd *= dtmp; gxd *= dtmp; gyd *= dtmp;
        mxd *= dtmp; myd *= dtmp;
        break;
     case 4:
        dtmp = 1.0/3600.0;
        etmp = 1.0/60.0;
#define DMStoDEGREES(value) \
        degrees = fmod(value,dtmp); \
        value -= degrees*3600.0; \
        minutes = fmod(value,etmp);\
        value -= minutes*60.0;\
        value *= dtmp; /* seconds to degrees */\
        value += degrees + minutes * etmp
        DMStoDEGREES(sxd);
        DMStoDEGREES(syd);
        DMStoDEGREES(gxd);
        DMStoDEGREES(gyd);
        DMStoDEGREES(mxd);
        DMStoDEGREES(myd);
        break;
     default:
        break;
     }

     datumpair[0] = sxd;
     datumpair[1] = syd;
     (void) tdb_store(shotDB,xyKey,xyVal,TDB_INSERT);

     datumpair[0] = gxd;
     datumpair[1] = gyd;
     (void) tdb_store(receiverDB,xyKey,xyVal,TDB_INSERT);

     datumpair[0] = mxd;
     datumpair[1] = myd;
     (void) tdb_store(midpointDB,xyKey,xyVal,TDB_INSERT);

     if(!isatty(fileno(stdout))) {

     /* calculate UTM header coordinates */

         geod->setLongitude(deg_to_rad*sxd); geod->setLatitude(deg_to_rad*syd);
         utmxy = myutm->convertFromGeodetic(geod);
         sxd = utmxy->easting();
         syd = utmxy->northing();
         geod->setLongitude(deg_to_rad*gxd); geod->setLatitude(deg_to_rad*gyd);
         utmxy = myutm->convertFromGeodetic(geod);
         gxd = utmxy->easting();
         gyd = utmxy->northing();
         geod->setLongitude(deg_to_rad*mxd); geod->setLatitude(deg_to_rad*myd);
         utmxy = myutm->convertFromGeodetic(geod);
         mxd = utmxy->easting();
         myd = utmxy->northing();

        dtmp = 0.0;
        if(sxd > dtmp) dtmp = sxd;
        if(syd > dtmp) dtmp = syd;
        if(gxd > dtmp) dtmp = gxd;
        if(gyd > dtmp) dtmp = gyd;
        if(mxd > dtmp) dtmp = mxd;
        if(myd > dtmp) dtmp = myd;

        if(dtmp >=      2147483647500.0)
          coord_scale = 10000;
        else if(dtmp >= 214748364750.00)
          coord_scale = 1000;
        else if(dtmp >= 21474836475.000)
          coord_scale = 100;
        else if(dtmp >= 2147483647.5000)
          coord_scale = 10;
        else if(dtmp >= 214748364.75000)
          coord_scale = 1;
        else if(dtmp >= 21474836.475000)
          coord_scale = -10;
        else if(dtmp >= 2147483.6475000)
          coord_scale = -100;
        else if(dtmp >= 214748.36475000)
          coord_scale = -1000;
        else
          coord_scale = -10000;
        scaleit = 1.0;
        if(coord_scale > 0) scaleit = 1.0/coord_scale;
        if(coord_scale < 0) scaleit = -1.0*coord_scale;

     /* write out updated trace header */
        s4hd[18] = rint(sxd*scaleit);
        s4hd[19] = rint(syd*scaleit);
        s4hd[20] = rint(gxd*scaleit);
        s4hd[21] = rint(gyd*scaleit);
        s4hd[45] = rint(mxd*scaleit);
        s4hd[44] = rint(myd*scaleit);

        if(IMLITTLEENDIAN) {
            for(i=0; i<120; i+= 2) {
                j = s2hd[i];
                s2hd[i] = s2hd[i+1];
                s2hd[i+1] = j;
            }
        }

        s2hd[35] = coord_scale; /* meters or feet */
        s2hd[44] = 1; /* meters or feet */
        if(IMLITTLEENDIAN) swab(inhdr, inhdr1, 240);
        nwrite = fwrite(inhdr1, 1, 240, stdout);

     /* write out updated trace data */
        for(i=0; i<trlen; ++i) putc(getc(stdin),stdout);

/* check for errors on stdin and stdout */
        if(ferror(stdout) || feof(stdout)) nread = 0;
     }

   } while(nread > 0 && ntrace != ntrace_limit);

   /* create shots.kml */
   fp = popen("zip -m -q -9 shots.kmz -","w");
   rc = fputs("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n",fp);
   rc = fputs("<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n",fp);
   rc = fputs("<Folder>\n",fp);

   xyKey = tdb_firstkey(shotDB);
   while(xyKey.dptr != NULL) {
      if(crsConvert == CRSLATLONG) {
         latLong.longitude = ((double *)xyKey.dptr)[0];
         latLong.latitude  = ((double *)xyKey.dptr)[1];
      }
      if(crsConvert == CRSUTM) {
         utmxy->setEasting(((double *) xyKey.dptr)[0]);
         utmxy->setNorthing(((double *) xyKey.dptr)[1]);
         geod = myutm->convertToGeodetic(utmxy);
         latLong.longitude = RadToDeg*geod->longitude();
         latLong.latitude  = RadToDeg*geod->latitude();
         delete geod;
      }
      addPoint(&latLong, fp);
      xyVal = tdb_nextkey(shotDB,xyKey);
      free(xyKey.dptr);
      xyKey = xyVal;
   }
   rc = fputs("</Folder>\n",fp);
   rc = fputs("</kml>\n",fp);
   fclose(fp);
   tdb_close(shotDB);

   /* create receivers.kml */
   fp = popen("zip -m -q -9 receivers.kmz -","w");
   rc = fputs("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n",fp);
   rc = fputs("<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n",fp);
   rc = fputs("<Folder>\n",fp);

   xyKey = tdb_firstkey(receiverDB);
   while(xyKey.dptr != NULL) {
      if(crsConvert == CRSLATLONG) {
         latLong.longitude = ((double *)xyKey.dptr)[0];
         latLong.latitude  = ((double *)xyKey.dptr)[1];
      }
      if(crsConvert == CRSUTM) {
         utmxy->setEasting(((double *) xyKey.dptr)[0]);
         utmxy->setNorthing(((double *) xyKey.dptr)[1]);
         geod = myutm->convertToGeodetic(utmxy);
         latLong.longitude = RadToDeg*geod->longitude();
         latLong.latitude  = RadToDeg*geod->latitude();
      }
      addPoint(&latLong, fp);
      xyVal = tdb_nextkey(receiverDB,xyKey);
      free(xyKey.dptr);
      xyKey = xyVal;
   }
   rc = fputs("</Folder>\n",fp);
   rc = fputs("</kml>\n",fp);
   fclose(fp);
   tdb_close(receiverDB);

   /* create receivers.kml */
   fp = popen("zip -m -q -9 midpoints.kmz -","w");
   rc = fputs("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n",fp);
   rc = fputs("<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n",fp);
   rc = fputs("<Folder>\n",fp);

   xyKey = tdb_firstkey(midpointDB);
   while(xyKey.dptr != NULL) {
      if(crsConvert == CRSLATLONG) {
         latLong.longitude = ((double *)xyKey.dptr)[0];
         latLong.latitude  = ((double *)xyKey.dptr)[1];
      }
      if(crsConvert == CRSUTM) {
         utmxy->setEasting(((double *) xyKey.dptr)[0]);
         utmxy->setNorthing(((double *) xyKey.dptr)[1]);
         geod = myutm->convertToGeodetic(utmxy);
         latLong.longitude = RadToDeg*geod->longitude();
         latLong.latitude  = RadToDeg*geod->latitude();
      }
      addPoint(&latLong, fp);
      xyVal = tdb_nextkey(midpointDB,xyKey);
      free(xyKey.dptr);
      xyKey = xyVal;
   }
   rc = fputs("</Folder>\n",fp);
   rc = fputs("</kml>\n",fp);
   fclose(fp);
   tdb_close(midpointDB);

   return (rc >=0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
