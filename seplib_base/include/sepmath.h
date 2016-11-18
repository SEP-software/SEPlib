#ifndef SEPMATH_H
#define SEPMATH_H yada

/* Include file <sepmath.h>  This file defines all the functions in
 * the sepmath library. It is include in <seplib.h>. It should also be
 * included in all the c-files in the sepmath library.
 *
 * Author 10/23/91 D.Nichols - split off from seplib.h
 */

#include <prototypes.h>
#include <math.h>



/* !__cplusplus */
/*#endif */

#ifndef MAX
#define MAX(a,b) ( ((a)>(b)) ? (a):(b) )
#endif
#ifndef MIN
#define MIN(a,b) ( ((a)<(b)) ? (a):(b) )
#endif

#endif
