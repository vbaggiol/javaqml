public class Main {
    public static void main(String[] args) {
        QApplication app = new QApplication();
	QQmlApplicationEngine engine = new QQmlApplicationEngine();
	QQmlContext context = engine.rootContext();
	String path = System.getProperty("user.dir") + "/Main.qml";
        engine.load(path);
        app.exec();
    }
}
