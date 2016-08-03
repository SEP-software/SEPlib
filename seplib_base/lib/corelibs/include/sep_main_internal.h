#include <prototypes.h>
#include <sitedef.h>
#include <stdio.h>
#include <stdlib.h>


#if NeedFunctionPrototypes
_XFUNCPROTOBEGIN
extern char *envhead(char*);
extern int findnm( int, char*, int );
extern int fullnm( char*, int );
extern int isatape(int);
extern int isclosed(FILE*);
extern int fdordinary(int);
extern int isordinary(char*);
extern char *maketitle( char*);
extern double sseek_block_d(const char*,int,int,int);
void mkrandom_string(char *string_in, char *string_out);
void sep_headername(char *tag, char *headername);
extern char* sep_tail(char*);
extern char* get_format_name( int num);
int get_data_name(char *tag,char *string_out);






#ifdef USE_SOCKETS
extern int socklisten(  int , int );
extern int opensock2( char* , char* );
extern int opensock1( char*, int);
#endif /*END OF SOCKETS*/

_XFUNCPROTOEND
#else /*END OF NO PROTO */
extern char *envhead();
extern int findnm();
extern int fullnm();
extern int isatape();
extern int isclosed();
extern int fdordinary();
extern int isordinary();
extern char *maketitle();


#ifdef USE_SOCKETS
extern int socklisten();
extern int opensock2();
extern int opensock1();
#endif /*END OF SOCKETS*/
#endif /*END OF NO PROTO */

/*  $Id: sep_main_internal.h,v 1.3 2004/04/08 22:32:27 bob Exp $ */
