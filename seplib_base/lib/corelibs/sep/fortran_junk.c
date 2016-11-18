#include <sep_main_internal.h>
#include <sep_main_external.h>

/*this file is only necessary because gfortran has a bug in older versions*/
int sreed2_f(const char *tag,void *v, const int sz,const char *typ){
   return sreed2(tag,v,sz,typ);
}
int sreed2_c(const char *tag,void *v, const int sz,const char *typ){
  return sreed2(tag,v,sz,typ);
}
int sreed2_i(const char *tag,void *v, const int sz,const char *typ){
  return  sreed2(tag,v,sz,typ);
}
int srite2_f(const char *tag,void *v, const int sz,const char *typ){
  return srite2(tag,v,sz,typ);
}
int srite2_c(const char *tag,void *v, const int sz,const char *typ){
  return  srite2(tag,v,sz,typ);
}
int srite2_i(const char *tag,void *v, const int sz,const char *typ){
  return  srite2(tag,v,sz,typ);
}
long long sreedll_i(const char *tag,void *v, const long long sz){
  return sreed(tag,v,sz);
}
long long sreedll_c(const char *tag,void *v, const long long sz){
  return sreed(tag,v,sz);
}
long long sreedll_x(const char *tag,void *v, const long long sz){
  return sreed(tag,v,sz);
}
long long sreedll_f(const char *tag,void *v, const long long sz){
  return sreed(tag,v,sz);
}
long long sritell_x(const char *tag,void *v, const long long sz){
  return srite(tag,v,sz);
}
long long sritell_c(const char *tag,void *v, const long long sz){
  return srite(tag,v,sz);
}
long long sritell_i(const char *tag,void *v, const long long sz){
  return srite(tag,v,sz);
}
long long sritell_f(const char *tag,void *v, const long long sz){
  return srite(tag,v,sz);
}
int sreed_f(const char *tag,void *v, const int sz){
  return sreed(tag,v,sz);
}
int sreed_c(const char *tag,void *v, const int sz){
  return sreed(tag,v,sz);
}
int sreed_i(const char *tag,void *v, const int sz){
  return  sreed(tag,v,sz);
}
int srite_f(const char *tag,void *v, const int sz){
  return  srite(tag,v,sz);
}
int srite_c(const char *tag,void *v, const int sz){
  return srite(tag,v,sz);
}
int srite_i(const char *tag,void *v, const int sz){
  return  srite(tag,v,sz);
}
int srite_window_f(const char *tag, int *nd, int *ng, int *nw, int *fw,int *jw, int sz, void *val){
   return  srite_window(tag,nd,ng,nw,fw,jw,sz,val);
}
int srite_window_c(const char *tag, int *nd, int *ng, int *nw, int *fw,int *jw, int sz, void *val){
return   srite_window(tag,nd,ng,nw,fw,jw,sz,val);
}
int srite_window_i(const char *tag, int *nd, int *ng, int *nw, int *fw,int *jw, int sz, void *val){
  return srite_window(tag,nd,ng,nw,fw,jw,sz,val);
}

int sreed_window_i(const char *tag, int *nd, int *ng, int *nw, int *fw,int *jw, int sz, void *val){
  return  srite_window(tag,nd,ng,nw,fw,jw,sz,val);
}
int sreed_window_f(const char *tag, int *nd, int *ng, int *nw, int *fw,int *jw, int sz, void *val){
return   srite_window(tag,nd,ng,nw,fw,jw,sz,val);
}
int sreed_window_c(const char *tag, int *nd, int *ng, int *nw, int *fw,int *jw, int sz, void *val){
  return  srite_window(tag,nd,ng,nw,fw,jw,sz,val);
}
int tetch_f_f(const char *arg, const char *typ, void *val){return tetch(arg,typ,val);}
int tetch_i_f(const char *arg, const char *typ, void *val){return tetch(arg,typ,val);}
int tetch_s_f(const char *arg, const char *typ, void *val){return tetch(arg,typ,val);}
int tetch_l_f(const char *arg, const char *typ, void *val){return tetch(arg,typ,val);}

int fetch_f_f_a(const char *arg, const char *typ, void *val){return fetch(arg,typ,val);}
int fetch_i_f_a(const char *arg, const char *typ, void *val){return fetch(arg,typ,val);}
int fetch_f_f(const char *arg, const char *typ, void *val){return fetch(arg,typ,val);}
int fetch_l_f(const char *arg, const char *typ, void *val){return fetch(arg,typ,val);}
int fetch_s_f(const char *arg, const char *typ, void *val){return fetch(arg,typ,val);}
int fetch_i_f(const char *arg, const char *typ, void *val){return fetch(arg,typ,val);}

int getch_f_f_a(const char *arg, const char *typ, void *val){return getch(arg,typ,val);}
int getch_i_f_a(const char *arg, const char *typ, void *val){return getch(arg,typ,val);}
int getch_f_f(const char *arg, const char *typ, void *val){return getch(arg,typ,val);}
int getch_i_f(const char *arg, const char *typ, void *val){return getch(arg,typ,val);}
int getch_s_f(const char *arg, const char *typ, void *val){return getch(arg,typ,val);}
int getch_l_f(const char *arg, const char *typ, void *val){return getch(arg,typ,val);}

int hetch_f_f_a(const char *arg, const char *typ, void *val){return hetch(arg,typ,val);}
int hetch_i_f_a(const char *arg, const char *typ, void *val){return hetch(arg,typ,val);}
int hetch_f_f(const char *arg, const char *typ, void *val){return hetch(arg,typ,val);}
int hetch_i_f(const char *arg, const char *typ, void *val){return hetch(arg,typ,val);}
int hetch_s_f(const char *arg, const char *typ, void *val){return hetch(arg,typ,val);}
int hetch_l_f(const char *arg, const char *typ, void *val){return hetch(arg,typ,val);}

int putch_f_f_a(const char *arg, const char *typ, void *val){return putch(arg,typ,val);}
int putch_i_f_a(const char *arg, const char *typ, void *val){return putch(arg,typ,val);}
int putch_f_f(const char *arg, const char *typ, void *val){return putch(arg,typ,val);}
int putch_i_f(const char *arg, const char *typ, void *val){return putch(arg,typ,val);}
int putch_s_f(const char *arg, const char *typ, void *val){return putch(arg,typ,val);}
int putch_l_f(const char *arg, const char *typ, void *val){return putch(arg,typ,val);}
 
int auxpar_f_f_a(const char *arg, const char *typ, void *val,const char *fle){return auxpar(arg,typ,val,fle);}
int auxpar_i_f_a(const char *arg, const char *typ, void *val,const char *fle){return auxpar(arg,typ,val,fle);}
int auxpar_f_f(const char *arg, const char *typ, void *val,const char *fle){return auxpar(arg,typ,val,fle);}
int auxpar_i_f(const char *arg, const char *typ, void *val,const char *fle){return auxpar(arg,typ,val,fle);}
int auxpar_l_f(const char *arg, const char *typ, void *val,const char *fle){return auxpar(arg,typ,val,fle);}
int auxpar_s_f(const char *arg, const char *typ, void *val,const char *fle){return auxpar(arg,typ,val,fle);}

int auxputch_f_f_a(const char *arg, const char *typ, void *val,const char *fle){return auxputch(arg,typ,val,fle);}
int auxputch_i_f_a(const char *arg, const char *typ, void *val,const char *fle){return auxputch(arg,typ,val,fle);}
int auxputch_f_f(const char *arg, const char *typ, void *val,const char *fle){return auxputch(arg,typ,val,fle);}
int auxputch_i_f(const char *arg, const char *typ, void *val,const char *fle){return auxputch(arg,typ,val,fle);}
int auxputch_s_f(const char *arg, const char *typ, void *val,const char *fle){return auxputch(arg,typ,val,fle);}
int auxputch_l_f(const char *arg, const char *typ, void *val,const char *fle){return auxputch(arg,typ,val,fle);}

