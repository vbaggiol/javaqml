public class QQmlApplicationEngine {
    public QQmlApplicationEngine() {
	self = DOtherSideJNI.qqmlapplicationengine_create();
    }

    public void addImportPath(String path) {
	DOtherSideJNI.qqmlapplicationengine_addImportPath(self, path);
    }

    public void load(String filename) {
        QUrl url = new QUrl(filename, 0);
        load(url);
        url.delete();
    }

    public void load(QUrl url) {
        DOtherSideJNI.qqmlapplicationengine_load_url(self, url.voidPointer());
    }

    public QQmlContext rootContext() {
	return new QQmlContext(DOtherSideJNI.qqmlapplicationengine_rootContext(self));
    }

    public void delete() {
	DOtherSideJNI.qqmlapplicationengine_delete(self);
    }

    private long self;
}
