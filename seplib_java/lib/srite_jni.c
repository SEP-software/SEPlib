/* native method for Srite class static methods srite() */
#include "../include/sitedef.h"
#include "edu_stanford_sep_seplib_corelibs_sep_Srite.h"
#include <seplib.h>
#if HAVE_STRING_H
#include <string.h>
#endif
#include <errno.h>

#define BODYCODE(Typeval,typeval) \
   const char *tag; \
   jboolean isCopyTag; \
   jsize start, len, nInBuf; \
   jint rc; \
   jint nwritten; \
   j ## typeval iobuf[BUFSIZ]; /* write in chunks to preserve memory(?) */ \
   tag = (*env)->GetStringUTFChars(env, jtag, &isCopyTag); \
   if(tag == ((const char *) NULL)) { \
      return ((jint) (-1)); \
   } \
  /* protect against segfault */ \
   nInBuf = (*env)->GetArrayLength(env, jbuf); \
   if(((jint) nInBuf) < jnvals) jnvals = ((jint) nInBuf); \
   start = 0; \
   nwritten = 0; \
   while(jnvals > 0) { \
      len = BUFSIZ; if(len > jnvals) len = jnvals; \
      (*env)->Get ## Typeval ## ArrayRegion(env,jbuf,start,len,iobuf); \
      rc = srite(tag, iobuf, (int) (len*sizeof(iobuf[0]))); \
      if(rc <= 0) break; \
      nwritten += rc; \
      start += rc;   \
      jnvals -= rc;   \
   } \
   if(isCopyTag) (*env)->ReleaseStringUTFChars(env,jtag,tag); \
   if(rc < 0) nwritten = -1; /* I/O error */ \
   return (jint) (nwritten/sizeof(iobuf[0]))

/*ARGSUSED*/
JNIEXPORT jint JNICALL Java_edu_stanford_sep_seplib_corelibs_sep_Srite_srite__Ljava_lang_String_2_3BI
  (JNIEnv *env, jclass cls, jstring jtag, jbyteArray jbuf, jint jnvals) {
   BODYCODE(Byte,byte);
}
  
/*ARGSUSED*/
JNIEXPORT jint JNICALL Java_edu_stanford_sep_seplib_corelibs_sep_Srite_srite__Ljava_lang_String_2_3II
  (JNIEnv *env, jclass cls, jstring jtag, jintArray jbuf, jint jnvals) {
   BODYCODE(Int,int);
}

/*ARGSUSED*/
JNIEXPORT jint JNICALL Java_edu_stanford_sep_seplib_corelibs_sep_Srite_srite__Ljava_lang_String_2_3FI
  (JNIEnv *env, jclass cls, jstring jtag, jfloatArray jbuf, jint jnvals){
   BODYCODE(Float,float);
}

/*ARGSUSED*/
JNIEXPORT jint JNICALL Java_edu_stanford_sep_seplib_corelibs_sep_Srite_srite__Ljava_lang_String_2_3DI
  (JNIEnv *env, jclass cls, jstring jtag, jdoubleArray jbuf, jint jnvals){
   BODYCODE(Double,double);
}
