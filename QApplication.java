public class QApplication {
    public QApplication() {
        DOtherSideJNI.qapplication_create();
    }

    public void quit() {
        DOtherSideJNI.qapplication_quit();
    }

    public void exec() {
        DOtherSideJNI.qapplication_exec();
    }

    public void delete() {
        DOtherSideJNI.qapplication_delete();
    }

    @Override
    public void finalize() {
        delete();
    }
}
