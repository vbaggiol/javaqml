public class QQmlContext {
    public QQmlContext(long self) {
	this.self = self;
    }

    void setContextProperty(String name, QVariant value) {
        DOtherSideJNI.qqmlcontext_setContextProperty(self, name, value.voidPointer());
    }

    private long self;
}
