/* convert ARCGIS ascii grid to SEPlib 
 *
 * ARCGIS2SEP arcgisfile
 *
 * Creates SEPlib .H and .H@ files based on the supplied ARCGIS filename.
 * The .H always appears in the current directory.
 *
 * If DATAPATH is present in the environment, the output .H@ file will
 * be placed in that directory otherwise it will also be placed in the 
 * current one.
 *
 * The expected input format consists of 6 header lines followed by the
 * data printed as floating point numbers.  The header lines are
 *
 *   ncols  nnn
 *   nrows  nnn
 *   xllcorner ffffff.ff
 *   yllcorner ffffff.ff
 *   cellsize  ffffff.ff
 *   NODATA_value fffff.f
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <rpc/rpc.h>

int main(int argc, char **argv, char **envp)
{
    unsigned int ncols, nrows;
    double xllcorner, yllcorner;
    double cellsize;
    double NODATA_value;

    FILE *arcgis;
    FILE *SEP_H;
    FILE *SEP_H_at;
    XDR SEP_H_at_xdr;

    double ingridval;
    float  outgridval;

    unsigned int icol, irow;
    int rc;

    size_t ntocopy;

    char fnbuf[2*PATH_MAX+5];
    char *basename;
    char *suffix;

    char *datapath;
    char defaultpath[] = { '.', '\0' };

    /* self doc if input filename not supplied */
    if(argc != 2) {
	fprintf(stderr,"Syntax: %s ARCGIS_file\n",argv[0]);
	return(EXIT_FAILURE);
    }

    arcgis = fopen(argv[1],"r");
    if(arcgis == ((FILE *) NULL)) {
	perror(argv[1]);
	fprintf(stderr,"Problem opening ARCGIS input. Exiting.\n");
	return(EXIT_FAILURE);
    }

    datapath = getenv("DATAPATH");
    if(datapath == ((char *) NULL)) datapath = defaultpath;

    /* construct output file names from that of the input */
    memset(fnbuf,'\0',sizeof(fnbuf));
    strncpy(fnbuf,datapath,PATH_MAX);
    if(datapath[strlen(datapath)-1] != '/')
	strcat(fnbuf,"/");

    /* get basename of the input */
    basename = strrchr(argv[1],'/');
    if(basename == (char *) NULL) basename = argv[1];
    else basename++;

    /* then locate suffix */
    suffix = strrchr(basename,'.');
    if(suffix == (char *) NULL) suffix = basename+strlen(basename);
    else suffix++;

    /* append basename w/o suffix to fnbuf */
    ntocopy = (size_t) (suffix-basename-1);
    strncat(fnbuf,basename,ntocopy);
    strcat(fnbuf,".H");
    
    SEP_H = fopen(fnbuf+strlen(fnbuf)-2-ntocopy,"wb");
    if(SEP_H == ((FILE *) NULL)) {
	perror(fnbuf+strlen(fnbuf)-ntocopy);
	fprintf(stderr,"Problem creating output seplib header. Exiting.\n");
	return(EXIT_FAILURE);
    }
    
    strcat(fnbuf,"@");
    SEP_H_at = fopen(fnbuf,"wb");
    if(SEP_H_at == ((FILE *) NULL)) {
	perror(fnbuf);
	fprintf(stderr,"Problem creating output seplib data. Exiting.\n");
	return(EXIT_FAILURE);
    }

    xdrstdio_create(&SEP_H_at_xdr,SEP_H_at,XDR_ENCODE);

    /* read header lines  */
    rc = fscanf(arcgis, " ncols %u",&ncols);
    if(rc != 1) {
	fprintf(stderr,"Problem reading ncols from ARCGIS header. Exiting.\n");
	return(EXIT_FAILURE);
    }
    rc = fscanf(arcgis, " nrows %u",&nrows);
    if(rc != 1) {
	fprintf(stderr,"Problem reading nrows from ARCGIS header. Exiting.\n");
	return(EXIT_FAILURE);
    }
    rc = fscanf(arcgis, " xllcorner %lg",&xllcorner);
    if(rc != 1) {
	fprintf(stderr,"Problem reading xllcorner from ARCGIS header. Exiting.\n");
	return(EXIT_FAILURE);
    }
    rc = fscanf(arcgis, " yllcorner %lg",&yllcorner);
    if(rc != 1) {
	fprintf(stderr,"Problem reading yllcorner from ARCGIS header. Exiting.\n");
	return(EXIT_FAILURE);
    }
    rc = fscanf(arcgis, " cellsize %lg",&cellsize);
    if(rc != 1) {
	fprintf(stderr,"Problem reading cellsize from ARCGIS header. Exiting.\n");
	return(EXIT_FAILURE);
    }
    rc = fscanf(arcgis, " NODATA_value %lg",&NODATA_value);
    if(rc != 1) {
	fprintf(stderr,"Problem reading NODATA_value from ARCGIS header. Exiting.\n");
	return(EXIT_FAILURE);
    }

    /* populate seplib header file */
    fprintf(SEP_H,"in=\"%s\"\n",fnbuf);
    fprintf(SEP_H,"esize=4 data_format=xdr_float\n"
	          "n1=%u n2=%u n3=1\n",ncols,nrows);
    fprintf(SEP_H,"o1=%lg o2=%lg o3=0.0\n",xllcorner,yllcorner);
    fprintf(SEP_H,"d1=%lg d2=%lg d3=1.0\n",cellsize,cellsize);
    fprintf(SEP_H,"hff=\"-1\" gff=\"-1\"\n");
    fprintf(SEP_H,"nodata_value=\"%lg\"\n",NODATA_value);

    if(0 != fclose(SEP_H)) {
	perror("SEPlib header file");
	fprintf(stderr,"Problem closing output header file. Exiting.\n");
	return(EXIT_FAILURE);
    }

    for(irow = 0; irow < nrows; ++irow) {
	for (icol = 0; icol < ncols; ++icol) {
	    if(1 != fscanf(arcgis," %lg",&ingridval)) {
		perror(argv[1]);
		fprintf(stderr,"Problem reading input grid. Exiting.\n");
		return(EXIT_FAILURE);
	    }
	    outgridval = (float) ingridval;
	    rc = xdr_float(&SEP_H_at_xdr,&outgridval);
	    if(rc == 0 || ferror(SEP_H_at) || feof(SEP_H_at)) {
		perror(fnbuf);
		fprintf(stderr,"Problem writing output grid. Exiting.\n");
		return(EXIT_FAILURE);
            }
	}
    }

    xdr_destroy(&SEP_H_at_xdr);

    if(0 != fclose(SEP_H_at)) {
	perror("SEPlib data file");
	fprintf(stderr,"Problem closing output data file. Exiting.\n");
	return(EXIT_FAILURE);
    }

    return(EXIT_SUCCESS);
}
