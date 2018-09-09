#include "DOtherSideJNI.h"

#include <DOtherSide/DOtherSide.h>

void Java_DOtherSideJNI_qapplication_1create(JNIEnv *env, jclass t)
{
    dos_qapplication_create();
}

void Java_DOtherSideJNI_qapplication_1exec(JNIEnv *env, jclass t)
{
    dos_qapplication_exec();
}

void Java_DOtherSideJNI_qapplication_1quit(JNIEnv *env, jclass t)
{
    dos_qapplication_quit();
}

void Java_DOtherSideJNI_qapplication_1delete(JNIEnv *env, jclass t)
{
    dos_qapplication_delete();
}

jlong JNICALL Java_DOtherSideJNI_qqmlapplicationengine_1create(JNIEnv *env, jclass t)
{
  return (jlong) dos_qqmlapplicationengine_create();
}

void Java_DOtherSideJNI_qqmlapplicationengine_1load_1url(JNIEnv *env, jclass t, jlong self, jlong url)
{
  dos_qqmlapplicationengine_load_url((void*)self, (DosQUrl*)url);
}

void Java_DOtherSideJNI_qqmlapplicationengine_1addImportPath(JNIEnv *env, jclass t, jlong self, jstring str)
{
  const char *c_str = (*env)->GetStringUTFChars(env, str, 0);
  dos_qqmlapplicationengine_add_import_path((void*)self, c_str);
  (*env)->ReleaseStringUTFChars(env, str, c_str);
}

jlong JNICALL Java_DOtherSideJNI_qqmlapplicationengine_1rootContext(JNIEnv *env, jclass t, jlong self)
{
  return (jlong)dos_qqmlapplicationengine_context((void*)self);
}

void Java_DOtherSideJNI_qqmlapplicationengine_1delete(JNIEnv *env, jclass t, jlong self)
{
  dos_qqmlapplicationengine_delete((void*)self);
}

void Java_DOtherSideJNI_qmlcontext_1setContextProperty(JNIEnv *env, jclass t, jlong self, jstring name, jlong value)
{
  const char *c_name = (*env)->GetStringUTFChars(env, name, 0);
  dos_qqmlcontext_setcontextproperty((void*)self, c_name, (DosQVariant*)value);
  (*env)->ReleaseStringUTFChars(env, name, c_name);
}

jlong Java_DOtherSideJNI_qurl_1create(JNIEnv *env, jclass t, jstring url, jint parsingMode) 
{
  const char *c_url = (*env)->GetStringUTFChars(env, url, 0);
  jlong result = (jlong)dos_qurl_create(c_url, parsingMode);
  (*env)->ReleaseStringUTFChars(env, url, c_url);
  return result;
}

jboolean Java_DOtherSideJNI_qurl_1isValid(JNIEnv *env, jclass t, jlong self)
{
  return dos_qurl_isValid((DosQUrl*)self);
}

jstring JNICALL Java_DOtherSideJNI_qurl_1toString(JNIEnv *env, jclass t, jlong self) 
{
  char* c_str = dos_qurl_to_string((DosQUrl*) self);
  jstring result = (*env)->NewStringUTF(env, c_str);
  dos_chararray_delete(c_str);
  return result;
}

void Java_DOtherSideJNI_qurl_1delete(JNIEnv *env, jclass t, jlong self)
{
    dos_qurl_delete((DosQUrl*)self);
}
