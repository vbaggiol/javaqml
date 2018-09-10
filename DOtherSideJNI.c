#include "DOtherSideJNI.h"

#include <DOtherSide/DOtherSide.h>

void JNICALL Java_DOtherSideJNI_qapplication_1create(JNIEnv *env, jclass t)
{
    dos_qapplication_create();
}

void JNICALL Java_DOtherSideJNI_qapplication_1exec(JNIEnv *env, jclass t)
{
    dos_qapplication_exec();
}

void JNICALL Java_DOtherSideJNI_qapplication_1quit(JNIEnv *env, jclass t)
{
    dos_qapplication_quit();
}

void JNICALL Java_DOtherSideJNI_qapplication_1delete(JNIEnv *env, jclass t)
{
    dos_qapplication_delete();
}

jlong JNICALL Java_DOtherSideJNI_qqmlapplicationengine_1create(JNIEnv *env, jclass t)
{
  return (jlong) dos_qqmlapplicationengine_create();
}

void JNICALL Java_DOtherSideJNI_qqmlapplicationengine_1load_1url(JNIEnv *env, jclass t, jlong self, jlong url)
{
  dos_qqmlapplicationengine_load_url((void*)self, (DosQUrl*)url);
}

void JNICALL Java_DOtherSideJNI_qqmlapplicationengine_1addImportPath(JNIEnv *env, jclass t, jlong self, jstring str)
{
  const char *c_str = (*env)->GetStringUTFChars(env, str, 0);
  dos_qqmlapplicationengine_add_import_path((void*)self, c_str);
  (*env)->ReleaseStringUTFChars(env, str, c_str);
}

jlong JNICALL Java_DOtherSideJNI_qqmlapplicationengine_1rootContext(JNIEnv *env, jclass t, jlong self)
{
  return (jlong)dos_qqmlapplicationengine_context((void*)self);
}

void JNICALL Java_DOtherSideJNI_qqmlapplicationengine_1delete(JNIEnv *env, jclass t, jlong self)
{
  dos_qqmlapplicationengine_delete((void*)self);
}

void JNICALL Java_DOtherSideJNI_qqmlcontext_1setContextProperty(JNIEnv *env, jclass t, jlong self, jstring name, jlong value)
{
  const char *c_name = (*env)->GetStringUTFChars(env, name, 0);
  dos_qqmlcontext_setcontextproperty((void*)self, c_name, (DosQVariant*)value);
  (*env)->ReleaseStringUTFChars(env, name, c_name);
}

jlong JNICALL Java_DOtherSideJNI_qurl_1create(JNIEnv *env, jclass t, jstring url, jint parsingMode)
{
  const char *c_url = (*env)->GetStringUTFChars(env, url, 0);
  jlong result = (jlong)dos_qurl_create(c_url, parsingMode);
  (*env)->ReleaseStringUTFChars(env, url, c_url);
  return result;
}

jboolean JNICALL Java_DOtherSideJNI_qurl_1isValid(JNIEnv *env, jclass t, jlong self)
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

void JNICALL Java_DOtherSideJNI_qurl_1delete(JNIEnv *env, jclass t, jlong self)
{
    dos_qurl_delete((DosQUrl*)self);
}

jlong JNICALL Java_DOtherSideJNI_qvariant_1create(JNIEnv *env, jclass t)
{
    return (jlong)dos_qvariant_create();
}

jlong JNICALL Java_DOtherSideJNI_qvariant_1create_1int(JNIEnv *env, jclass t, jint value)
{
    return (jlong)dos_qvariant_create_int(value);
}

jlong JNICALL Java_DOtherSideJNI_qvariant_1create_1bool(JNIEnv *env, jclass t, jboolean value)
{
    return (jlong)dos_qvariant_create_bool(value);
}

jlong JNICALL Java_DOtherSideJNI_qvariant_1create_1string(JNIEnv *env, jclass t, jstring value)
{
    const char *c_value = (*env)->GetStringUTFChars(env, value, 0);
    jlong result = (jlong)dos_qvariant_create_string(c_value);
    (*env)->ReleaseStringUTFChars(env, value, c_value);
    return result;
}

jlong JNICALL Java_DOtherSideJNI_qvariant_1create_1qvariant(JNIEnv *env, jclass t, jlong value)
{
    return (jlong)dos_qvariant_create_qvariant((DosQVariant*)value);
}

jlong JNICALL Java_DOtherSideJNI_qvariant_1create_1float(JNIEnv *env, jclass t, jfloat value)
{
    return (jlong)dos_qvariant_create_float(value);
}

jlong JNICALL Java_DOtherSideJNI_qvariant_1create_1double(JNIEnv *env, jclass t, jdouble value)
{
    return (jlong)dos_qvariant_create_double(value);
}

void JNICALL Java_DOtherSideJNI_qvariant_1setInt(JNIEnv *env, jclass t, jlong self, jint value)
{
    dos_qvariant_setInt((DosQVariant*)self, value);
}

void JNICALL Java_DOtherSideJNI_qvariant_1setBool(JNIEnv *env, jclass t, jlong self, jboolean value)
{
    dos_qvariant_setBool((DosQVariant*)self, value);
}

void JNICALL Java_DOtherSideJNI_qvariant_1setFloat(JNIEnv *env, jclass t, jlong self, jfloat value)
{
    dos_qvariant_setFloat((DosQVariant*)self, value);
}

void JNICALL Java_DOtherSideJNI_qvariant_1setDouble(JNIEnv *env, jclass t, jlong self, jdouble value)
{
    dos_qvariant_setDouble((DosQVariant*)self, value);
}

void JNICALL Java_DOtherSideJNI_qvariant_1setString(JNIEnv *env, jclass t, jlong self, jstring value)
{
    const char *c_value = (*env)->GetStringUTFChars(env, value, 0);
    dos_qvariant_setString((DosQVariant*)self, c_value);
    (*env)->ReleaseStringUTFChars(env, value, c_value);
}

void JNICALL Java_DOtherSideJNI_qvariant_1setQObject(JNIEnv *env, jclass t, jlong self, jlong value)
{
    dos_qvariant_setQObject((DosQVariant*)self, (DosQObject*)value);
}

jboolean JNICALL Java_DOtherSideJNI_qvariant_1isNull(JNIEnv *env, jclass t, jlong self)
{
    return dos_qvariant_isnull((DosQVariant*)self);
}

void JNICALL Java_DOtherSideJNI_qvariant_1delete(JNIEnv *env, jclass t, jlong self)
{
    dos_qvariant_delete((DosQVariant*)self);
}

jint JNICALL Java_DOtherSideJNI_qvariant_1toInt(JNIEnv *env, jclass t, jlong self)
{
    return dos_qvariant_toInt((DosQVariant*)self);
}

jboolean JNICALL Java_DOtherSideJNI_qvariant_1toBool(JNIEnv *env, jclass t, jlong self)
{
    return dos_qvariant_toBool((DosQVariant*)self);
}

jstring JNICALL Java_DOtherSideJNI_qvariant_1toString(JNIEnv *env, jclass t, jlong self)
{
    char* c_str = dos_qvariant_toString((DosQVariant*)self);
    jstring result = (*env)->NewStringUTF(env, c_str);
    dos_chararray_delete(c_str);
    return result;
}

jfloat JNICALL Java_DOtherSideJNI_qvariant_1toFloat(JNIEnv *env, jclass t, jlong self)
{
    return dos_qvariant_toFloat((DosQVariant*)self);
}

jdouble JNICALL Java_DOtherSideJNI_qvariant_1toDouble(JNIEnv *env, jclass t, jlong self)
{
    return dos_qvariant_toDouble((DosQVariant*)self);
}
