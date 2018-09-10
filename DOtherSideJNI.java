class DOtherSideJNI {
    static {
	System.loadLibrary("DOtherSideJNI");
    }

    public static native void qapplication_create();
    public static native void qapplication_exec();
    public static native void qapplication_quit();
    public static native void qapplication_delete();

    public static native long qqmlapplicationengine_create();
    public static native void qqmlapplicationengine_load_url(long self, long url);
    public static native void qqmlapplicationengine_addImportPath(long self, String path);
    public static native long qqmlapplicationengine_rootContext(long self);
    public static native void qqmlapplicationengine_delete(long self);

    public static native void qqmlcontext_setContextProperty(long self, String name, long qvariantValue);

    public static native long qurl_create(String url, int parsingMode);
    public static native boolean qurl_isValid(long self);
    public static native String qurl_toString(long self);
    public static native void qurl_delete(long self);

    public static native long qvariant_create();
    public static native long qvariant_create_int(int value);
    public static native long qvariant_create_bool(boolean value);
    public static native long qvariant_create_string(String value);
    public static native long qvariant_create_qvariant(long value);
    public static native long qvariant_create_float(float value);
    public static native long qvariant_create_double(double value);
    public static native void qvariant_setInt(long self, int value);
    public static native void qvariant_setBool(long self, boolean value);
    public static native void qvariant_setFloat(long self, float value);
    public static native void qvariant_setDouble(long self, double value);
    public static native void qvariant_setString(long self, String value);
    public static native void qvariant_setQObject(long self, long value);
    public static native boolean qvariant_isNull(long self);
    public static native void qvariant_delete(long self);
    public static native int qvariant_toInt(long self);
    public static native boolean qvariant_toBool(long self);
    public static native String qvariant_toString(long self);
    public static native float qvariant_toFloat(long self);
    public static native double qvariant_toDouble(long self);
    public static native long qvariant_toQObject(long self);

    public class ParameterDefinition {
        public String name;
        public int metaType;
    };

    public class SignalDefinition {
        public String name;
        public ParameterDefinition[] parameters;
    };

    public class SlotDefinition {
        public String name;
        public int returnMetaType;
        public ParameterDefinition[] parameters;
    };

    public class PropertyDefinition {
        public String name;
        public int metaType;
        public String readSlot;
        public String writeSlot;
        public String notifySignal;
    };

    public static native long qmetaobject_create(long parentQMetaObject, String className, SignalDefinition[] signals, SlotDefinition[] slots, PropertyDefinition[] properties);

    public static native void qmetaobject_delete(long self);
}
