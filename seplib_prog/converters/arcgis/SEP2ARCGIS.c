/* convert regular 2D SEPlib file to ARCGIS ascii grid
 *
 * SEP2ARCGIS < SEPfile > ARCGISfile
 *
 * The output header format consists of 6 header lines followed by the
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
#include <seplib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <rpc/rpc.h>
extern int sepxargc;
extern char **sepxargv;
/*ARGSUSED*/
int main(int argc, char **argv, char **envp)
{
    unsigned int ncols, nrows;
    double xllcorner, yllcorner;
    double cellsize;
    double NODATA_value;

    double outgridval;
    float  ingridval;

    unsigned int icol, irow;
    int rc;

    size_t ntocopy;

    initpar(argc, argv);
    getch_add_string("head=/dev/null");
    if(!redin()) {
	fprintf(stderr,"Syntax: %s <SEPlib_file > ARCGIS_file\n",argv[0]);
	return(EXIT_FAILURE);
    }

    if(!fetch("n1","i",&ncols)) seperr("missing n1!\n");
    if(!fetch("n2","i",&nrows)) seperr("missing n2!\n");
    if(!fetch("o1","g",&xllcorner)) seperr("missing o1!\n");
    if(!fetch("o2","g",&yllcorner)) seperr("missing o2!\n");
    if(!fetch("d2","g",&cellsize)) seperr("missing d2!\n");
    if(!fetch("NODATA_value","g",&NODATA_value)) NODATA_value = INFINITY;

    puthead("ncols %u\n",ncols);
    puthead("nrows %u\n",nrows);
    puthead("xllcorner %lg\n",xllcorner);
    puthead("yllcorner %lg\n",yllcorner+nrows*cellsize-cellsize);
    puthead("cellsize %lg\n",cellsize);
    puthead("NODATA_value %lg\n",NODATA_value);

    for(irow = 0; irow < nrows; ++irow) {
	for (icol = 0; icol < ncols; ++icol) {
            (void) sreed("in",&ingridval,sizeof(float));
	    outgridval = (double) ingridval;
	    puthead("%lg ",outgridval);
	}
    }

    hclose();

    return(EXIT_SUCCESS);
}
