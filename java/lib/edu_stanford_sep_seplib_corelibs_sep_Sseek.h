/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class edu_stanford_sep_seplib_corelibs_sep_Sseek */

#ifndef _Included_edu_stanford_sep_seplib_corelibs_sep_Sseek
#define _Included_edu_stanford_sep_seplib_corelibs_sep_Sseek
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     edu_stanford_sep_seplib_corelibs_sep_Sseek
 * Method:    sseek
 * Signature: (Ljava/lang/String;II)I
 */
JNIEXPORT jint JNICALL Java_edu_stanford_sep_seplib_corelibs_sep_Sseek_sseek
  (JNIEnv *, jclass, jstring, jint, jint);

/*
 * Class:     edu_stanford_sep_seplib_corelibs_sep_Sseek
 * Method:    sseek_block
 * Signature: (Ljava/lang/String;III)I
 */
JNIEXPORT jint JNICALL Java_edu_stanford_sep_seplib_corelibs_sep_Sseek_sseek_1block
  (JNIEnv *, jclass, jstring, jint, jint, jint);

/*
 * Class:     edu_stanford_sep_seplib_corelibs_sep_Sseek
 * Method:    sseek_block_d
 * Signature: (Ljava/lang/String;III)D
 */
JNIEXPORT jdouble JNICALL Java_edu_stanford_sep_seplib_corelibs_sep_Sseek_sseek_1block_1d
  (JNIEnv *, jclass, jstring, jint, jint, jint);

/*
 * Class:     edu_stanford_sep_seplib_corelibs_sep_Sseek
 * Method:    file_position
 * Signature: (Ljava/lang/String;I[I[I)I
 */
JNIEXPORT jint JNICALL Java_edu_stanford_sep_seplib_corelibs_sep_Sseek_file_1position
  (JNIEnv *, jclass, jstring, jint, jintArray, jintArray);

/*
 * Class:     edu_stanford_sep_seplib_corelibs_sep_Sseek
 * Method:    sseekable
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_edu_stanford_sep_seplib_corelibs_sep_Sseek_sseekable
  (JNIEnv *, jclass, jstring);

#ifdef __cplusplus
}
#endif
#endif
