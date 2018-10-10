#include "DOtherSideJNI.h"

#include <DOtherSide/DOtherSide.h>

#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <vector>

namespace {

class JavaLongArrayRef {
public:
    inline JavaLongArrayRef(JNIEnv* env, jlongArray array)
        : env(env)
        , array(array)
        , c_array(env->GetLongArrayElements(array, nullptr))
        , size_(env->GetArrayLength(array))
    {}

    JavaLongArrayRef(const JavaLongArrayRef&) = delete;
    JavaLongArrayRef(JavaLongArrayRef&&) = delete;
    JavaLongArrayRef& operator=(const JavaLongArrayRef&) = delete;
    JavaLongArrayRef& operator=(JavaLongArrayRef&&) = delete;

    inline ~JavaLongArrayRef() { env->ReleaseLongArrayElements(array, c_array, 0); }

    inline size_t size() const { return size_; }

    inline operator jlong*() { return c_array; }

    inline jlong* begin() { return c_array; }
    inline jlong* end() { return c_array + size_; }

private:
    JNIEnv* env = nullptr;
    jlongArray array;
    jlong* c_array = nullptr;
    size_t size_ = 0;
};

class JavaStringRef {
public:
    inline JavaStringRef(JNIEnv* env, jstring str)
        : env(env)
        , str(str)
        , c_str(env->GetStringUTFChars(str, nullptr))
    {}

    JavaStringRef(const JavaStringRef&) = delete;
    JavaStringRef(JavaStringRef&&) = delete;
    JavaStringRef& operator=(const JavaStringRef&) = delete;
    JavaStringRef& operator=(JavaStringRef&&) = delete;

    inline ~JavaStringRef() { env->ReleaseStringUTFChars(str, c_str); }

    inline operator const char*() { return c_str; }

private:
    JNIEnv* env = nullptr;
    jstring str;
    const char* c_str = nullptr;
};

void* to_void_pointer(jlong value) {
    return reinterpret_cast<void*>(value);
}

jlong to_jlong(void* value) {
    return reinterpret_cast<jlong>(value);
}

JavaVM *callback_jvm;
jclass callback_class;
jmethodID callback_method;

void c_on_slot_called(void* self, void* slot_name, int parameters_count, void** parameters) {
    JNIEnv *env;
    jint rs = callback_jvm->AttachCurrentThread((void**) &env, nullptr);
    assert (rs == JNI_OK);

    std::vector<jlong> temp(parameters_count);
    std::transform(parameters, parameters + parameters_count, temp.begin(), ::to_jlong);

    jlongArray array = env->NewLongArray(parameters_count);
    env->SetLongArrayRegion(array, 0, parameters_count, temp.data());

    env->CallStaticVoidMethod(callback_class, callback_method, (jlong) self, (jlong) slot_name, array);
}

}

void JNICALL Java_DOtherSideJNI_initialize(JNIEnv *env , jclass t)
{
    jint rs = env->GetJavaVM(&callback_jvm);
    assert (rs == JNI_OK);
    callback_method = env->GetStaticMethodID(t, "onSlotCalled", "(JJ[J)V");
    callback_class = t;
}

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
  JavaStringRef c_str(env, str);
  dos_qqmlapplicationengine_add_import_path((void*)self, c_str);
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
  JavaStringRef c_name(env, name);
  dos_qqmlcontext_setcontextproperty((void*)self, c_name, (DosQVariant*)value);
}

jlong JNICALL Java_DOtherSideJNI_qurl_1create(JNIEnv *env, jclass t, jstring url, jint parsingMode)
{
  JavaStringRef c_url(env, url);
  return (jlong)dos_qurl_create(c_url, parsingMode);
}

jboolean JNICALL Java_DOtherSideJNI_qurl_1isValid(JNIEnv *env, jclass t, jlong self)
{
  return dos_qurl_isValid((DosQUrl*)self);
}

jstring JNICALL Java_DOtherSideJNI_qurl_1toString(JNIEnv *env, jclass t, jlong self) 
{
  char* c_str = dos_qurl_to_string((DosQUrl*) self);
  jstring result = env->NewStringUTF(c_str);
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
    JavaStringRef c_value(env, value);
    return (jlong)dos_qvariant_create_string(c_value);
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

jlong JNICALL Java_DOtherSideJNI_qvariant_1create_1qobject(JNIEnv *env, jclass t, jlong value)
{
    return (jlong) dos_qvariant_create_qobject((DosQObject*) value);
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
    JavaStringRef c_value(env, value);
    dos_qvariant_setString((DosQVariant*)self, c_value);
}

void JNICALL Java_DOtherSideJNI_qvariant_1setQObject(JNIEnv *env, jclass t, jlong self, jlong value)
{
    dos_qvariant_setQObject((DosQVariant*)self, (DosQObject*)value);
}

jboolean JNICALL Java_DOtherSideJNI_qvariant_1isnullptr(JNIEnv *env, jclass t, jlong self)
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
    jstring result = env->NewStringUTF(c_str);
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

static const char* get_string_field(JNIEnv* env, jclass class_instance, jobject object, const char* fieldName) {
    jfieldID field = env->GetFieldID(class_instance, fieldName, "Ljava/lang/String;");
    jstring value = static_cast<jstring>(env->GetObjectField(object, field));
    return env->GetStringUTFChars(value, 0);
}

static jobjectArray get_array_field(JNIEnv* env, jclass class_instance, jobject object, const char* fieldName, const char* type) {
    jfieldID parametersField = env->GetFieldID(class_instance, fieldName, type);
    return static_cast<jobjectArray>(env->GetObjectField(object, parametersField));
}

static int get_int_field(JNIEnv* env, jclass class_instance, jobject object, const char* fieldName) {
    jfieldID field = env->GetFieldID(class_instance, fieldName, "I");
    return env->GetIntField(object, field);
}

static void free_string_field(JNIEnv* env, jclass class_instance, jobject object, const char* fieldName, const char* c_value) {
    jfieldID field = env->GetFieldID(class_instance, fieldName, "Ljava/lang/String;");
    jstring value = static_cast<jstring>(env->GetObjectField(object, field));
    env->ReleaseStringUTFChars(value, c_value);
}

static ParameterDefinition* to_parameter_definition(JNIEnv* env, jobjectArray array) {
    jsize count = env->GetArrayLength(array);
    ParameterDefinition* result = count == 0 ? nullptr : (ParameterDefinition*) malloc((size_t)count * sizeof(ParameterDefinition));
    for (jsize i = 0; i < count; ++i) {
        jobject object = env->GetObjectArrayElement(array, i);
        jclass class_instance = env->GetObjectClass(object);
        result[i].name = get_string_field(env, class_instance, object, "name");
        result[i].metaType = get_int_field(env, class_instance, object, "metaType");
    }
    return result;
}

static void free_parameter_definition(JNIEnv* env, jobjectArray array, ParameterDefinition* parameters) {
    jsize count = env->GetArrayLength(array);
    for (jsize i = 0; i < count; ++i) {
        jobject object = env->GetObjectArrayElement(array, i);
        jclass class_instance = env->GetObjectClass(object);
        free_string_field(env, class_instance, object, "name", parameters[i].name);
    }
    free(parameters);
}

static SignalDefinition* to_signal_definition(JNIEnv* env, jobjectArray array) {
    jsize count = env->GetArrayLength(array);
    SignalDefinition* result = count == 0 ? nullptr : (SignalDefinition*) malloc((size_t)count * sizeof(SignalDefinition));
    for (jsize i = 0; i < count; ++i) {
        jobject object = env->GetObjectArrayElement(array, i);
        jclass class_instance = env->GetObjectClass(object);

        result[i].name = get_string_field(env, class_instance, object, "name");

        jobjectArray parameters = get_array_field(env, class_instance, object, "parameters", "[LDOtherSideJNI$ParameterDefinition;");
        result[i].parametersCount = env->GetArrayLength(parameters);
        result[i].parameters = to_parameter_definition(env, parameters);
    }
    return result;
}

static void free_signal_definition(JNIEnv* env, jobjectArray array, SignalDefinition* signals) {
    jsize count = env->GetArrayLength(array);
    for (jsize i = 0; i < count; ++i) {
        jobject object = env->GetObjectArrayElement(array, i);
        jclass class_instance = env->GetObjectClass(object);

        free_string_field(env, class_instance, object, "name", signals[i].name);

        jobjectArray parameters = get_array_field(env, class_instance, object, "parameters", "[LDOtherSideJNI$ParameterDefinition;");
        free_parameter_definition(env, parameters, signals[i].parameters);
    }
    free(signals);
}

static SlotDefinition* to_slot_definition(JNIEnv *env, jobjectArray array) {
    jsize count = env->GetArrayLength(array);
    SlotDefinition* result = count == 0 ? nullptr : (SlotDefinition*) malloc((size_t)count * sizeof(SlotDefinition));
    for (jsize i = 0; i < count; ++i) {
        jobject object = env->GetObjectArrayElement(array, i);
        jclass class_instance = env->GetObjectClass(object);

        result[i].name = get_string_field(env, class_instance, object, "name");
        result[i].returnMetaType = get_int_field(env, class_instance, object, "returnMetaType");

        jobjectArray parameters = get_array_field(env, class_instance, object, "parameters", "[LDOtherSideJNI$ParameterDefinition;");
        result[i].parametersCount = env->GetArrayLength(parameters);
        result[i].parameters = to_parameter_definition(env, parameters);
    }
    return result;
}

static void free_slot_definition(JNIEnv* env, jobjectArray array, SlotDefinition* slots) {
    jsize count = env->GetArrayLength(array);
    for (jsize i = 0; i < count; ++i) {
        jobject object = env->GetObjectArrayElement(array, i);
        jclass class_instance = env->GetObjectClass(object);

        free_string_field(env, class_instance, object, "name", slots[i].name);

        jobjectArray parameters = get_array_field(env, class_instance, object, "parameters", "[LDOtherSideJNI$ParameterDefinition;");
        free_parameter_definition(env, parameters, slots[i].parameters);
    }
    free(slots);
}

static PropertyDefinition* to_property_definition(JNIEnv *env, jobjectArray array) {
    jsize count = env->GetArrayLength(array);
    PropertyDefinition* result = count == 0 ? nullptr : (PropertyDefinition*) malloc((size_t)count * sizeof(PropertyDefinition));
    for (jsize i = 0; i < count; ++i) {
        jobject object = env->GetObjectArrayElement(array, i);
        jclass class_instance = env->GetObjectClass(object);

        result[i].name = get_string_field(env, class_instance, object, "name");
        result[i].propertyMetaType = get_int_field(env, class_instance, object, "metaType");
        result[i].readSlot = get_string_field(env, class_instance, object, "readSlot");
        result[i].writeSlot = get_string_field(env, class_instance, object, "writeSlot");
        result[i].notifySignal = get_string_field(env, class_instance, object, "notifySignal");
    }
    return result;
}

static void free_property_definition(JNIEnv* env, jobjectArray array, PropertyDefinition* properties) {
    jsize count = env->GetArrayLength(array);
    for (jsize i = 0; i < count; ++i) {
        jobject object = env->GetObjectArrayElement(array, i);
        jclass class_instance = env->GetObjectClass(object);
        free_string_field(env, class_instance, object, "name", properties[i].name);
        free_string_field(env, class_instance, object, "readSlot", properties[i].readSlot);
        free_string_field(env, class_instance, object, "writeSlot", properties[i].writeSlot);
        free_string_field(env, class_instance, object, "notifySignal", properties[i].notifySignal);
    }
    free(properties);
}


jlong JNICALL Java_DOtherSideJNI_qmetaobject_1create(JNIEnv *env, jclass t, jlong superQMetaObject, jstring name, jobjectArray signals, jobjectArray slots, jobjectArray properties)
{
    SignalDefinitions c_signals;
    c_signals.count = env->GetArrayLength(signals);
    c_signals.definitions = to_signal_definition(env, signals);

    SlotDefinitions c_slots;
    c_slots.count = env->GetArrayLength(slots);
    c_slots.definitions = to_slot_definition(env, slots);

    PropertyDefinitions c_properties;
    c_properties.count = env->GetArrayLength(properties);
    c_properties.definitions = to_property_definition(env, properties);

    JavaStringRef c_name(env, name);
    jlong result = (jlong) dos_qmetaobject_create((DosQMetaObject*) superQMetaObject, c_name, &c_signals, &c_slots, &c_properties);

    free_signal_definition(env, signals, c_signals.definitions);
    free_slot_definition(env, slots, c_slots.definitions);
    free_property_definition(env, properties, c_properties.definitions);

    return result;
}

jlong JNICALL Java_DOtherSideJNI_qobject_1qmetaobject(JNIEnv *env, jclass t)
{
    return (jlong) dos_qobject_qmetaobject();
}

jlong JNICALL Java_DOtherSideJNI_qabstractlistmodel_1qmetaobject(JNIEnv *env, jclass t)
{
    return (jlong) dos_qabstractlistmodel_qmetaobject();
}

jlong JNICALL Java_DOtherSideJNI_qabstracttablemodel_1qmetaobject(JNIEnv *env, jclass t)
{
    return (jlong) dos_qabstracttablemodel_qmetaobject();
}

jlong JNICALL Java_DOtherSideJNI_qabstractitemmodel_1qmetaobject(JNIEnv *env, jclass t)
{
    return (jlong) dos_qabstractitemmodel_qmetaobject();
}

jlong JNICALL Java_DOtherSideJNI_qobject_1create(JNIEnv *env, jclass t, jlong javaObjectId, jlong metaObject)
{
    return (jlong) dos_qobject_create((void*)javaObjectId, (DosQMetaObject*) metaObject, c_on_slot_called);
}

void JNICALL Java_DOtherSideJNI_qobject_1delete(JNIEnv *, jclass, jlong self)
{
    dos_qobject_delete((DosQObject*) self);
}

void JNICALL Java_DOtherSideJNI_qobject_1deleteLater(JNIEnv *env, jclass t, jlong self)
{
    //dos_qobject_deleteLater((DosQObject*) self);
}

void JNICALL Java_DOtherSideJNI_qvariant_1assign(JNIEnv *env, jclass t, jlong lhs, jlong rhs)
{
    dos_qvariant_assign((DosQVariant*)lhs, (DosQVariant*)rhs);
}

void JNICALL Java_DOtherSideJNI_qobject_1signal_1emit(JNIEnv *env, jclass t, jlong self, jstring name, jlongArray arguments)
{
    JavaLongArrayRef elements (env, arguments);
    std::vector<void*> c_arguments(elements.size());
    std::transform(elements.begin(), elements.end(), c_arguments.begin(), ::to_void_pointer);

    JavaStringRef c_name(env, name);
    dos_qobject_signal_emit((DosQObject*) self, c_name, elements.size(), c_arguments.data());
}
