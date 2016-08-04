#include <prototypes.h>
#include <stdio.h>


#if NeedFunctionPrototypes
_XFUNCPROTOBEGIN
extern void finitpar(void);
extern int noieeeinterupt(void);
extern int fortalloc( char*,int);
extern int fortfree( char*);
extern char* fsbrk(unsigned int);
int sep3d_grab_header_vals_si(const char *tag, char *ind, int *n2, void *head);
int sep3d_grab_header_vals_sf(const char *tag, char *ind, int *n2, void *head);
int sep3d_grab_header_vals_if(const char *tag, int *ind, int *n2, void *head);
int sep3d_grab_header_vals_ii(const char *tag, int *ind, int *n2, void *head);
int sep3d_set_header_vals_if(const char *tag,int tag2, void *vals);
int sep3d_set_header_vals_ii(const char *tag,int tag2, void *vals);
int sep3d_set_header_vals_sf(const char *tag,char *tag2, void *vals);
int sep3d_set_header_vals_si(const char *tag,char *tag2, void *vals);


int sep3d_writeif(const char *tag, char *t2, int *n, int *f,int *j, void *v, int i1, int i2, int i3,int i4); 
int sep3d_writeff(const char *tag, char *t2, int *n, int *f,int *j, void *v, int i1, int i2, int i3,int i4); 
int sep3d_writecf(const char *tag, char *t2, int *n, int *f,int *j, void *v, int i1, int i2, int i3,int i4); 
int sep3d_readcf(const char *tag, char *t2, int i1, int i2, int i3, void *v);
int sep3d_readif(const char *tag, char *t2, int i1, int i2, int i3, void *v);
int sep3d_readff(const char *tag, char *t2, int i1, int i2, int i3, void *v);
#endif
