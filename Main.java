public class Main {
    public static void main(String[] args) {
        DOtherSideJNI.SignalDefinition[] signals = new DOtherSideJNI.SignalDefinition[1];
        signals[0] = new DOtherSideJNI.SignalDefinition();
        signals[0].name = "nameChanged";
        signals[0].parameters = new DOtherSideJNI.ParameterDefinition[0];

        DOtherSideJNI.SlotDefinition[] slots = new DOtherSideJNI.SlotDefinition[2];
        slots[0] = new DOtherSideJNI.SlotDefinition();
        slots[0].name = "name";
        slots[0].returnMetaType = DOtherSideJNI.MetaType.Int.value();
        slots[0].parameters = new DOtherSideJNI.ParameterDefinition[0];

        slots[1] = new DOtherSideJNI.SlotDefinition();
        slots[1].name = "setName";
        slots[1].returnMetaType = DOtherSideJNI.MetaType.Void.value();
        slots[1].parameters = new DOtherSideJNI.ParameterDefinition[1];
        slots[1].parameters[0] = new DOtherSideJNI.ParameterDefinition();
        slots[1].parameters[0].name = "value";
        slots[1].parameters[0].metaType = DOtherSideJNI.MetaType.Int.value();

        DOtherSideJNI.PropertyDefinition[] properties = new DOtherSideJNI.PropertyDefinition[1];
        properties[0] = new DOtherSideJNI.PropertyDefinition();
        properties[0].name = "name";
        properties[0].metaType = DOtherSideJNI.MetaType.Int.value();
        properties[0].readSlot = "name";
        properties[0].writeSlot = "setName";
        properties[0].notifySignal = "nameChanged";

        QMetaObject metaObject = new QMetaObject(QObject.staticMetaObject, "Temp", signals, slots, properties);


//        QApplication app = new QApplication();
//	QQmlApplicationEngine engine = new QQmlApplicationEngine();
//	QQmlContext context = engine.rootContext();
//        QVariant value = new QVariant(10);
//	String path = System.getProperty("user.dir") + "/Main.qml";
//        engine.rootContext().setContextProperty("customValue", value);
//        engine.load(path);
//        app.exec();
    }
}
