class DOtherSideJNI {
    static {
	System.loadLibrary("DOtherSideJNI");
    }

    public static native void qapplication_create();
    public static native void qapplication_exec();
    public static native void qapplication_quit();
    public static native void qapplication_delete();
}
