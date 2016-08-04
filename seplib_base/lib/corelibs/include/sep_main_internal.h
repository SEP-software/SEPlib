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


/*fortran junk to be rmoved some day*/
void srite2_f(const char *tag, void *v, const int sz);
void srite2_i(const char *tag, void *v, const int sz);
void srite2_c(const char *tag, void *v, const int sz);
void sreed2_f(const char *tag, void *v, const int sz);
void sreed2_i(const char *tag, void *v, const int sz);
void sreed2_c(const char *tag, void *v, const int sz);

void srite_f(const char *tag, void *v, const int sz);
void srite_i(const char *tag, void *v, const int sz);
void srite_c(const char *tag, void *v, const int sz);
void sreed_f(const char *tag, void *v, const int sz);
void sreed_i(const char *tag, void *v, const int sz);
void sreed_c(const char *tag, void *v, const int sz);

void srite_window_i(const char *tag,  int, int *ng, int *nw, int *fw, int *jw, int sz,
  void *val);
void srite_window_f(const char *tag,  int, int *ng, int *nw, int *fw, int *jw, int sz,
  void *val);
void srite_window_c(const char *tag,  int, int *ng, int *nw, int *fw, int *jw, int sz,
  void *val);
void sreed_window_i(const char *tag,  int, int *ng, int *nw, int *fw, int *jw, int sz,
  void *val);
void sreed_window_f(const char *tag,  int, int *ng, int *nw, int *fw, int *jw, int sz,
  void *val);
void sreed_window_c(const char *tag,  int, int *ng, int *nw, int *fw, int *jw, int sz,
  void *val);

void tetch_f_f(const char *arg, const char *typ, void *val);
void tetch_i_f(const char *arg, const char *typ, void *val);
void tetch_s_f(const char *arg, const char *typ, void *val);
void tetch_l_f(const char *arg, const char *typ, void *val);

void putch_f_f(const char *arg, const char *typ, void *val);
void putch_i_f(const char *arg, const char *typ, void *val);
void putch_s_f(const char *arg, const char *typ, void *val);
void putch_l_f(const char *arg, const char *typ, void *val);

void hetch_f_f_a(const char *arg, const char *typ, void *val);
void hetch_i_f_a(const char *arg, const char *typ, void *val);
void hetch_f_f(const char *arg, const char *typ, void *val);
void hetch_i_f(const char *arg, const char *typ, void *val);
void hetch_s_f(const char *arg, const char *typ, void *val);
void hetch_l_f(const char *arg, const char *typ, void *val);

void getch_f_f_a(const char *arg, const char *typ, void *val);
void getch_i_f_a(const char *arg, const char *typ, void *val);
void getch_f_f(const char *arg, const char *typ, void *val);
void getch_i_f(const char *arg, const char *typ, void *val);
void getch_s_f(const char *arg, const char *typ, void *val);
void getch_l_f(const char *arg, const char *typ, void *val);

void fetch_f_f_a(const char *arg, const char *typ, void *val);
void fetch_i_f_a(const char *arg, const char *typ, void *val);
void fetch_f_f(const char *arg, const char *typ, void *val);
void fetch_i_f(const char *arg, const char *typ, void *val);
void fetch_s_f(const char *arg, const char *typ, void *val);
void fetch_l_f(const char *arg, const char *typ, void *val);

void auxpar_f_f_a(const char *arg, const char *typ, void *val,const char *tag);
void auxpar_i_f_a(const char *arg, const char *typ, void *val,const char *tag);
void auxpar_f_f(const char *arg, const char *typ, void *val,const char *tag);
void auxpar_i_f(const char *arg, const char *typ, void *val,const char *tag);
void auxpar_s_f(const char *arg, const char *typ, void *val,const char *tag);
void auxpar_l_f(const char *arg, const char *typ, void *val,const char *tag);

void auxputch_f_f_a(const char *arg, const char *typ, void *val,const char *tag);
void auxputch_i_f_a(const char *arg, const char *typ, void *val,const char *tag);
void auxputch_f_f(const char *arg, const char *typ, void *val,const char *tag);
void auxputch_i_f(const char *arg, const char *typ, void *val,const char *tag);
void auxputch_s_f(const char *arg, const char *typ, void *val,const char *tag);
void auxputch_l_f(const char *arg, const char *typ, void *val,const char *tag);

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
