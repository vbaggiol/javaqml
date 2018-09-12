#include "DOtherSideJNI.h"

#include <DOtherSide/DOtherSide.h>

#include <stdlib.h>

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

void JNICALL Java_DOtherSideJNI_qmetaobject_1delete(JNIEnv *env, jclass t, jlong self)
{
    dos_qmetaobject_delete((DosQMetaObject*)self);
}

static ParameterDefinition* to_parameter_definition(JNIEnv* env, jobjectArray array) {
    jsize count = (*env)->GetArrayLength(env, array);
    ParameterDefinition* result = (ParameterDefinition*) malloc((uint)count * sizeof(ParameterDefinition));
    for (jsize i = 0; i < count; ++i) {
        jobject object = (*env)->GetObjectArrayElement(env, array, i);
        jclass class = (*env)->GetObjectClass(env, object);

        jfieldID nameFieldId = (*env)->GetFieldID(env, class, "name", "Ljava/lang/String;");
        jstring name = (*env)->GetObjectField(env, object, nameFieldId);
        result[i].name = (*env)->GetStringUTFChars(env, name, 0);

        jfieldID metaTypeFieldId = (*env)->GetFieldID(env, class, "metaType", "I");
        result[i].metaType = (*env)->GetIntField(env, object, metaTypeFieldId);
    }

    return result;
}

static void free_parameter_definition(JNIEnv* env, jobjectArray array, ParameterDefinition* parameters) {
    jsize count = (*env)->GetArrayLength(env, array);
    for (jsize i = 0; i < count; ++i) {
        jobject object = (*env)->GetObjectArrayElement(env, array, i);
        jclass class = (*env)->GetObjectClass(env, object);

        jfieldID nameFieldId = (*env)->GetFieldID(env, class, "name", "Ljava/lang/String;");
        jstring name = (*env)->GetObjectField(env, object, nameFieldId);
        (*env)->ReleaseStringUTFChars(env, name, parameters[i].name);
    }
    free(parameters);
}

static SignalDefinition* to_signal_definition(JNIEnv* env, jobjectArray array) {
    jsize count = (*env)->GetArrayLength(env, array);
    SignalDefinition* result = (SignalDefinition*) malloc((uint)count * sizeof(SignalDefinition));
    for (jsize i = 0; i < count; ++i) {
        jobject object = (*env)->GetObjectArrayElement(env, array, i);
        jclass class = (*env)->GetObjectClass(env, object);

        jfieldID nameField = (*env)->GetFieldID(env, class, "name", "Ljava/lang/String;");
        jstring name = (*env)->GetObjectField(env, object, nameField);
        result[i].name = (*env)->GetStringUTFChars(env, name, 0);

        jfieldID parametersField = (*env)->GetFieldID(env, class, "parameters", "[Ljava/lang/Object;");
        jobjectArray parameters = (*env)->GetObjectField(env, object, parametersField);

        result[i].parametersCount = (*env)->GetArrayLength(env, parameters);
        result[i].parameters = to_parameter_definition(env, parameters);
    }
    return result;
}

static void free_signal_definition(JNIEnv* env, jobjectArray array, SignalDefinition* signals) {
    jsize count = (*env)->GetArrayLength(env, array);
    for (jsize i = 0; i < count; ++i) {
        jobject object = (*env)->GetObjectArrayElement(env, array, i);
        jclass class = (*env)->GetObjectClass(env, object);

        jfieldID nameField = (*env)->GetFieldID(env, class, "name", "Ljava/lang/String;");
        jstring name = (*env)->GetObjectField(env, object, nameField);
        (*env)->ReleaseStringUTFChars(env, name, signals[i].name);

        jfieldID parametersField = (*env)->GetFieldID(env, class, "parameters", "[Ljava/lang/Object;");
        jobjectArray parameters = (*env)->GetObjectField(env, object, parametersField);

        free_parameter_definition(env, parameters, signals[i].parameters);
    }
    free(signals);
}

static SlotDefinition* to_slot_definition(JNIEnv *env, jobjectArray array) {
    jsize count = (*env)->GetArrayLength(env, array);
    SlotDefinition* result = (SlotDefinition*) malloc((uint)count * sizeof(SlotDefinition));
    for (jsize i = 0; i < count; ++i) {
        jobject object = (*env)->GetObjectArrayElement(env, array, i);
        jclass class = (*env)->GetObjectClass(env, object);

        jfieldID nameField = (*env)->GetFieldID(env, class, "name", "Ljava/lang/String;");
        jstring name = (*env)->GetObjectField(env, object, nameField);
        result[i].name = (*env)->GetStringUTFChars(env, name, 0);

        jfieldID returnMetaTypeField = (*env)->GetFieldID(env, class, "returnMetaType", "I");
        result[i].returnMetaType = (*env)->GetIntField(env, object, returnMetaTypeField);

        jfieldID parametersField = (*env)->GetFieldID(env, class, "parameters", "[Ljava/lang/Object;");
        jobjectArray parameters = (*env)->GetObjectField(env, object, parametersField);

        result[i].parametersCount = (*env)->GetArrayLength(env, parameters);
        result[i].parameters = to_parameter_definition(env, parameters);
    }
    return result;
}

static void free_slot_definition(JNIEnv* env, jobjectArray array, SlotDefinition* slots) {
    jsize count = (*env)->GetArrayLength(env, array);
    for (jsize i = 0; i < count; ++i) {
        jobject object = (*env)->GetObjectArrayElement(env, array, i);
        jclass class = (*env)->GetObjectClass(env, object);

        jfieldID nameField = (*env)->GetFieldID(env, class, "name", "Ljava/lang/String;");
        jstring name = (*env)->GetObjectField(env, object, nameField);
        (*env)->ReleaseStringUTFChars(env, name, slots[i].name);

        jfieldID parametersField = (*env)->GetFieldID(env, class, "parameters", "[Ljava/lang/Object;");
        jobjectArray parameters = (*env)->GetObjectField(env, object, parametersField);

        free_parameter_definition(env, parameters, slots[i].parameters);
    }
    free(slots);
}

static PropertyDefinition* to_property_definition(JNIEnv *env, jobjectArray array) {
    jsize count = (*env)->GetArrayLength(env, array);
    PropertyDefinition* result = (PropertyDefinition*) malloc((uint)count * sizeof(PropertyDefinition));
    for (jsize i = 0; i < count; ++i) {
        jobject object = (*env)->GetObjectArrayElement(env, array, i);
        jclass class = (*env)->GetObjectClass(env, object);

        {
            jfieldID nameField = (*env)->GetFieldID(env, class, "name", "Ljava/lang/String;");
            jstring name = (*env)->GetObjectField(env, object, nameField);
            result[i].name = (*env)->GetStringUTFChars(env, name, 0);
        }

        {
            jfieldID metaTypeField = (*env)->GetFieldID(env, class, "metaType", "I");
            result[i].propertyMetaType = (*env)->GetIntField(env, object, metaTypeField);
        }

        {
            jfieldID readSlotField = (*env)->GetFieldID(env, class, "readSlot", "Ljava/lang/String;");
            jstring readSlot = (*env)->GetObjectField(env, object, readSlotField);
            result[i].readSlot = (*env)->GetStringUTFChars(env, readSlot, 0);
        }

        {
            jfieldID writeSlotField = (*env)->GetFieldID(env, class, "writeSlot", "Ljava/lang/String;");
            jstring writeSlot = (*env)->GetObjectField(env, object, writeSlotField);
            result[i].writeSlot = (*env)->GetStringUTFChars(env, writeSlot, 0);
        }

        {
            jfieldID notifySignalField = (*env)->GetFieldID(env, class, "notifySignal", "Ljava/lang/String;");
            jstring notifySignal = (*env)->GetObjectField(env, object, notifySignalField);
            result[i].notifySignal = (*env)->GetStringUTFChars(env, notifySignal, 0);
        }
    }
    return result;
}

static void free_property_definition(JNIEnv* env, jobjectArray array, PropertyDefinition* properties) {
    jsize count = (*env)->GetArrayLength(env, array);
    for (jsize i = 0; i < count; ++i) {
        jobject object = (*env)->GetObjectArrayElement(env, array, i);
        jclass class = (*env)->GetObjectClass(env, object);

        {
            jfieldID nameField = (*env)->GetFieldID(env, class, "name", "Ljava/lang/String;");
            jstring name = (*env)->GetObjectField(env, object, nameField);
            (*env)->ReleaseStringUTFChars(env, name, properties[i].name);
        }

        {
            jfieldID readSlotField = (*env)->GetFieldID(env, class, "readSlot", "Ljava/lang/String;");
            jstring readSlot = (*env)->GetObjectField(env, object, readSlotField);
            (*env)->ReleaseStringUTFChars(env, readSlot, properties[i].readSlot);
        }

        {
            jfieldID writeSlotField = (*env)->GetFieldID(env, class, "writeSlot", "Ljava/lang/String;");
            jstring writeSlot = (*env)->GetObjectField(env, object, writeSlotField);
            (*env)->ReleaseStringUTFChars(env, writeSlot, properties[i].writeSlot);
        }

        {
            jfieldID notifySignalField = (*env)->GetFieldID(env, class, "notifySignal", "Ljava/lang/String;");
            jstring notifySignal = (*env)->GetObjectField(env, object, notifySignalField);
            (*env)->ReleaseStringUTFChars(env, notifySignal, properties[i].notifySignal);
        }
    }
    free(properties);
}


jlong JNICALL Java_DOtherSideJNI_qmetaobject_1create(JNIEnv *env, jclass t, jlong superQMetaObject, jstring name, jobjectArray signals, jobjectArray slots, jobjectArray properties)
{
    const char *c_name = (*env)->GetStringUTFChars(env, name, 0);
    SignalDefinitions c_signals;
    c_signals.count = (*env)->GetArrayLength(env, signals);
    c_signals.definitions = to_signal_definition(env, signals);

    SlotDefinitions c_slots;
    c_slots.count = (*env)->GetArrayLength(env, slots);
    c_slots.definitions = to_slot_definition(env, slots);

    PropertyDefinitions c_properties;
    c_properties.count = (*env)->GetArrayLength(env, properties);
    c_properties.definitions = to_property_definition(env, properties);

    jlong result = (jlong) dos_qmetaobject_create((DosQMetaObject*)superQMetaObject, c_name, &c_signals, &c_slots, &c_properties);
    (*env)->ReleaseStringUTFChars(env, name, c_name);

    free_signal_definition(env, signals, c_signals.definitions);
    free_slot_definition(env, slots, c_slots.definitions);
    free_property_definition(env, properties, c_properties.definitions);

    return result;
}
