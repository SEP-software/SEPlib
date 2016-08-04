#include <sep_main_internal.h>
#include <sep_main_external.h>

/*this file is only necessary because gfortran has a bug in older versions*/
void sreed2_f(const char *tag,void *v, const int sz){
   sreed2(tag,v,sz);
}
void sreed2_c(const char *tag,void *v, const int sz){
   sreed2(tag,v,sz);
}
void sreed2_i(const char *tag,void *v, const int sz){
   sreed2(tag,v,sz);
}
void srite2_f(const char *tag,void *v, const int sz){
   srite2(tag,v,sz);
}
void srite2_c(const char *tag,void *v, const int sz){
   srite2(tag,v,sz);
}
void srite2_i(const char *tag,void *v, const int sz){
   srite2(tag,v,sz);
}
void sreed_f(const char *tag,void *v, const int sz){
   sreed(tag,v,sz);
}
void sreed_c(const char *tag,void *v, const int sz){
   sreed(tag,v,sz);
}
void sreed_i(const char *tag,void *v, const int sz){
   sreed(tag,v,sz);
}
void srite_f(const char *tag,void *v, const int sz){
   srite(tag,v,sz);
}
void srite_c(const char *tag,void *v, const int sz){
   srite(tag,v,sz);
}
void srite_i(const char *tag,void *v, const int sz){
   srite(tag,v,sz);
}
void srite_window_f(const char *tag, int nd, int *ng, int *nw, int *fw,int *jw, int sz, void *val){
   srite_window(tag,nd,ng,nw,fw,jw,sz,val);
}
void srite_window_f(const char *tag, int nd, int *ng, int *nw, int *fw,int *jw, int sz, void *val){
   srite_window(tag,nd,ng,nw,fw,jw,sz,val);
}
void srite_window_i(const char *tag, int nd, int *ng, int *nw, int *fw,int *jw, int sz, void *val){
   srite_window(tag,nd,ng,nw,fw,jw,sz,val);
}

void sreed_window_i(const char *tag, int nd, int *ng, int *nw, int *fw,int *jw, int sz, void *val){
   srite_window(tag,nd,ng,nw,fw,jw,sz,val);
}
void sreed_window_f(const char *tag, int nd, int *ng, int *nw, int *fw,int *jw, int sz, void *val){
   srite_window(tag,nd,ng,nw,fw,jw,sz,val);
}
void sreed_window_c(const char *tag, int nd, int *ng, int *nw, int *fw,int *jw, int sz, void *val){
   srite_window(tag,nd,ng,nw,fw,jw,sz,val);
}
void tetch_f_f(const char *arg, const char *typ, void *val){tetch(arg,typ,val);}
void tetch_i_f(const char *arg, const char *typ, void *val){tetch(arg,typ,val);}
void tetch_s_f(const char *arg, const char *typ, void *val){tetch(arg,typ,val);}
void tetch_l_f(const char *arg, const char *typ, void *val){tetch(arg,typ,val);}

void fetch_f_f_a(const char *arg, const char *typ, void *val){fetch(arg,typ,val);}
void fetch_i_f_a(const char *arg, const char *typ, void *val){fetch(arg,typ,val);}
void fetch_f_f(const char *arg, const char *typ, void *val){fetch(arg,typ,val);}
void fetch_l_f(const char *arg, const char *typ, void *val){fetch(arg,typ,val);}
void fetch_s_f(const char *arg, const char *typ, void *val){fetch(arg,typ,val);}
void fetch_i_f(const char *arg, const char *typ, void *val){fetch(arg,typ,val);}

void getch_f_f_a(const char *arg, const char *typ, void *val){getch(arg,typ,val);}
void getch_i_f_a(const char *arg, const char *typ, void *val){getch(arg,typ,val);}
void getch_f_f(const char *arg, const char *typ, void *val){getch(arg,typ,val);}
void getch_i_f(const char *arg, const char *typ, void *val){getch(arg,typ,val);}
void getch_s_f(const char *arg, const char *typ, void *val){getch(arg,typ,val);}
void getch_l_f(const char *arg, const char *typ, void *val){getch(arg,typ,val);}

void hetch_f_f_a(const char *arg, const char *typ, void *val){hetch(arg,typ,val);}
void hetch_i_f_a(const char *arg, const char *typ, void *val){hetch(arg,typ,val);}
void hetch_f_f(const char *arg, const char *typ, void *val){hetch(arg,typ,val);}
void hetch_i_f(const char *arg, const char *typ, void *val){hetch(arg,typ,val);}
void hetch_s_f(const char *arg, const char *typ, void *val){hetch(arg,typ,val);}
void hetch_l_f(const char *arg, const char *typ, void *val){hetch(arg,typ,val);}

void putch_f_f_a(const char *arg, const char *typ, void *val){putch(arg,typ,val);}
void putch_i_f_a(const char *arg, const char *typ, void *val){putch(arg,typ,val);}
void putch_f_f(const char *arg, const char *typ, void *val){putch(arg,typ,val);}
void putch_i_f(const char *arg, const char *typ, void *val){putch(arg,typ,val);}
void putch_s_f(const char *arg, const char *typ, void *val){putch(arg,typ,val);}
void putch_l_f(const char *arg, const char *typ, void *val){putch(arg,typ,val);}
 
void auxpar_f_f_a(const char *arg, const char *typ, void *val){auxpar(arg,typ,val);}
void auxpar_i_f_a(const char *arg, const char *typ, void *val){auxpar(arg,typ,val);}
void auxpar_f_f(const char *arg, const char *typ, void *val){auxpar(arg,typ,val);}
void auxpar_i_f(const char *arg, const char *typ, void *val){auxpar(arg,typ,val);}
void auxpar_l_f(const char *arg, const char *typ, void *val){auxpar(arg,typ,val);}
void auxpar_s_f(const char *arg, const char *typ, void *val){auxpar(arg,typ,val);}

void auxputch_f_f_a(const char *arg, const char *typ, void *val){auxputch(arg,typ,val);}
void auxputch_f_i_a(const char *arg, const char *typ, void *val){auxputch(arg,typ,val);}
void auxputch_f_f(const char *arg, const char *typ, void *val){auxputch(arg,typ,val);}
void auxputch_f_i(const char *arg, const char *typ, void *val){auxputch(arg,typ,val);}
void auxputch_f_s(const char *arg, const char *typ, void *val){auxputch(arg,typ,val);}
void auxputch_f_l(const char *arg, const char *typ, void *val){auxputch(arg,typ,val);}

