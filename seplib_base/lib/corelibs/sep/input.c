#include <stdio.h>
#include <string.h>
#include "streamlist.h"
#include <sep_main_external.h>
#include "sep_main_internal.h"

#if NeedFunctionPrototypes
_XFUNCPROTOBEGIN
FILE *input(void)
_XFUNCPROTOEND
#else
FILE *input()
#endif
{
	static FILE *rfile = NULL ;
	streaminf* info;

   /* logic:
       get the stream info structure for tag "in" and return the
	streamfile member.
   */
   if(rfile == NULL || isclosed(rfile)) {
	info = tag_info( "in", TAG_IN );

	if( ! info->valid) return 0;

        if( info->ioinf == 0 ) (*info->open_func)(info, &(info->ioinf) );

	if( ! info->valid) return 0;

        rfile = info->streamfile ;
   }
   return (rfile);
}
