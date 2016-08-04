#include <sep_fortran_internal.h>
#include <sep_main_external.h>

int sep3d_grab_header_vals_sf(const char *tag,char *tag2, void *vals){
  return sep_grab_header_vals_s(tag,tag2,vals);
}
int sep3d_grab_header_vals_si(const char *tag,char *tag2, void *vals){
  return sep_grab_header_vals_s(tag,tag2,vals);
}

int sep3d_grab_header_vals_if(const char *tag,int tag2, void *vals){
  return sep_grab_header_vals_i(tag,tag2,vals);
}
int sep3d_grab_header_vals_ii(const char *tag,int tag2, void *vals){
  return sep_grab_header_vals_i(tag,tag2,vals);
}

int sep3d_set_header_vals_sf(const char *tag,char *tag2, void *vals){
  return sep_set_header_vals_s(tag,tag2,vals);
}
int sep3d_set_header_vals_si(const char *tag,char *tag2, void *vals){
  return sep_set_header_vals_s(tag,tag2,vals);
}

int sep3d_set_header_vals_if(const char *tag,int tag2, void *vals){
  return sep_set_header_vals_i(tag,tag2,vals);
}
int sep3d_set_header_vals_ii(const char *tag,int tag2, void *vals){
  return sep_set_header_vals_i(tag,tag2,vals);
}



int sep_get_val_headers_si(const char *tag,char *tag2, void *vals){
return  sep_get_val_headers_s(tag,tag2,vals);
}
int sep_get_val_headers_sf(const char *tag,char *tag2, void *vals){
return  sep_get_val_headers_s(tag,tag2,vals);
}
int sep3d_ritecf(const char *tag, char *t2, int *n, int *f, int *j, void *v, int i1, int i2, int i3,int i4){
  return sep3d_rite(tag,t2,n,f,j,v,i1,i2,i3,i4);
}
int sep3d_riteff(const char *tag, char *t2, int *n, int *f,int *j, void *v, int i1, int i2, int i3,int i4){
  return sep3d_rite(tag,t2,n,f,j,v,i1,i2,i3,i4);
}
int sep3d_riteif(const char *tag, char *t2, int *n, int *f,int *j, void *v, int i1, int i2, int i3,int i4){
  return sep3d_rite(tag,t2,n,f,j,v,i1,i2,i3,i4);
}
int sep3d_reedcf(const char *tag, char *t2, int i1, int i2, int i3, void *v){
  return sep3d_reed(tag,t2,i1,i2,i3,v);
}
int sep3d_reedff(const char *tag, char *t2, int i1, int i2, int i3, void *v){
  return sep3d_reed(tag,t2,i1,i2,i3,v);
}
int sep3d_reedif(const char *tag, char *t2, int i1, int i2, int i3, void *v){
  return sep3d_reed(tag,t2,i1,i2,i3,v);
}

