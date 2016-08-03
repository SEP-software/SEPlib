/* native method for Tetch class static methods tetch() */
#include "../include/sitedef.h"
#include "edu_stanford_sep_seplib_corelibs_sep_Tetch.h"
#include <seplib.h>
#if HAVE_STRING_H
#include <string.h>
#endif

#define BODYCODE(Typeval, typeval, mytypeval) \
  j ## typeval *valBuf; \
  jsize valBufLen; \
  jboolean isCopyName, isCopyFormat, isCopyVals; \
  const char *name, *format; \
  jint rc; \
  jint i; \
  jclass exceptCls; \
  mytypeval myVals[BUFSIZ]; /* try to protect against memory overflow */ \
  memset(myVals,'\0',BUFSIZ*sizeof(mytypeval)); \
  name = (*env)->GetStringUTFChars(env,jname,&isCopyName); \
  if(name == ((char *) NULL)) return(0); /* an exception was thrown */ \
  format = (*env)->GetStringUTFChars(env,jformat,&isCopyFormat); \
  if(format == ((char *) NULL)) return(0); /* an exception was thrown */ \
  rc = tetch((char *)name, (char *)format, myVals); \
  if(rc < 1) return(rc); \
  if( ((char *) format)[0] == 's' ) rc = strlen((char *) myVals); \
  if(rc > sizeof(myVals)/sizeof(myVals[0])) { /* throw an overflow exception */\
     exceptCls = (*env)->FindClass(env,"java/lang/ArrayIndexOutOfBoundsException"); \
     if(exceptCls != ((jclass) NULL)) { \
         (*env)->ThrowNew(env,exceptCls,"tetch array overrun\n"); \
     } \
     return(rc); \
  } \
  /* Copy tetch result to output argument */ \
  valBufLen = (*env)->GetArrayLength(env, jvals); \
  if(rc > valBufLen) rc = valBufLen; /* shorten to prevent overflow */ \
  valBuf = (*env)->Get ## Typeval ## ArrayElements(env, jvals, &isCopyVals); \
  if(valBuf == ((j ## typeval *) NULL)) return(0); /* an exception was thrown */ \
  for(i=0; i<rc; ++i) valBuf[i] = myVals[i]; \
  if(isCopyVals == JNI_TRUE) (*env)->Release ## Typeval ## ArrayElements(env, jvals, valBuf, 0); \
  if(isCopyFormat == JNI_TRUE) (*env)->ReleaseStringUTFChars(env,jformat,format); \
  if(isCopyName == JNI_TRUE) (*env)->ReleaseStringUTFChars(env,jname,name); \
  return(rc)

/*ARGSUSED*/
JNIEXPORT jint JNICALL Java_edu_stanford_sep_seplib_corelibs_sep_Tetch_tetch__Ljava_lang_String_2Ljava_lang_String_2_3I
  (JNIEnv *env, jclass cls, jstring jname, jstring jformat, jintArray jvals) {

   BODYCODE(Int,int,int);
}

/*ARGSUSED*/
JNIEXPORT jint JNICALL Java_edu_stanford_sep_seplib_corelibs_sep_Tetch_tetch__Ljava_lang_String_2Ljava_lang_String_2_3F
  (JNIEnv *env, jclass cls, jstring jname, jstring jformat, jfloatArray jvals){

   BODYCODE(Float,float,float);
}

/*ARGSUSED*/
JNIEXPORT jint JNICALL Java_edu_stanford_sep_seplib_corelibs_sep_Tetch_tetch__Ljava_lang_String_2Ljava_lang_String_2_3D
  (JNIEnv *env, jclass cls, jstring jname, jstring jformat, jdoubleArray jvals){

   BODYCODE(Double,double,double);
}

/*ARGSUSED*/
JNIEXPORT jint JNICALL Java_edu_stanford_sep_seplib_corelibs_sep_Tetch_tetch__Ljava_lang_String_2Ljava_lang_String_2_3B
  (JNIEnv *env, jclass cls, jstring jname, jstring jformat, jbyteArray jvals){

  BODYCODE(Byte,byte,char);
}
