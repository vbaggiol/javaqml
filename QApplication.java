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

    @Override
    public void finalize() {
        DOtherSideJNI.qapplication_delete();
    }
}
