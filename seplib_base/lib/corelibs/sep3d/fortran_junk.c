#include <sep_fortran_internal.h>
#include <sep_main_external.h>

int sep_put_val_headers_ff(const char *tag, int *ind, int *n2, void *head){
return  sep_put_val_headers(tag,ind,n2,head);
}

int sep_put_val_headers_if(const char *tag, int *ind, int *n2, void *head){
return  sep_put_val_headers(tag,ind,n2,head);
}
int sep_get_val_headers_ff(const char *tag, int *ind, int *n2, void *head){
  return sep_get_val_headers(tag,ind,n2,head);
}

int sep_get_val_headers_if(const char *tag, int *ind, int *n2, void *head){
return  sep_get_val_headers(tag,ind,n2,head);
}

