#include <prototypes.h>
#include <stdio.h>


#if NeedFunctionPrototypes
_XFUNCPROTOBEGIN
extern int auxpar(const char*,const char*,void*,const char*);
extern int auxputch(const char*,const char*,const void*,const char*);
extern int fetch(char*,char*,void*);
extern int getch(const char*,const char*,void*);
extern int getch_add_string(const char*);
extern int hetch(char*,char*,void*);
extern void initpar(int,char**);
extern int putch(char*,char*,void*);
extern int auxputhead(char*,char*, ... );
extern int puthead(char*, ... );
extern int tetch(char*,char*, ... );
extern int putlin(char*);
_XFUNCPROTOEND

#endif
/*  $Id: sep_pars_external.h,v 1.1.1.1 2004/03/25 06:37:22 cvs Exp $ */
