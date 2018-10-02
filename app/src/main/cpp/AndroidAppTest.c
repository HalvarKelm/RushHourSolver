#include <stdio.h>
#include <jni.h>
#include <string.h>

/*JNIEXPORT void

JNICALL
Java_rhp_rushhourproject_MainActivity_StringtoCandStringfromC(
        JNIEnv *env,
        jobject obj ,
        jstring hello) {
    const char *nativeString = (*env)->GetStringUTFChars(env, hello, 0);
    //const char *nativeString = "Hi There";
    (*env)->ReleaseStringUTFChars(env, hello, nativeString);
}*/
/*JNIEXPORT jstring JNICALL Java_rhp_rushhourproject_MainActivity_StringtoCandStringfromC(
        JNIEnv *env,
        jobject obj,
        jstring javaString)
{
    const char *nativeString = (*env)->GetStringUTFChars(env, javaString, 0);

    // use your string
    strcat(nativeString, " test");

    jstring jstrBuf = (*env)->NewStringUTF(env, nativeString);
    return jstrBuf;
}*/