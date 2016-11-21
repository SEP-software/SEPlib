#ifndef _SEP_CUBE_H
#define _SEP_CUBE_H

/* Include file <sepcube.h>  This file contains function definitions for all
 * the routines in libcube. It should be includded in all the c-files in
 * that library.
 *
 * Author 10/23/91 D.Nichols - split up seplib.h
 *
 *  copyright (c) 1991 Stanford University
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <prototypes.h>

/* Moved this to the general include file because almost everything uses
   malloc - questionable  -Bob*/

#include <stdlib.h>
/* library name redefinitions, to prevent name conflicts  */

#define FILE_DESCR int



#include<sep_fortran.h>        
#include<sep_old_external.h>
#include<sep_main_external.h>
#include<sep_pars_external.h>
#endif
