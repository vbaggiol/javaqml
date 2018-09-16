import java.beans.IntrospectionException;

public class Main {

    public static class User extends QObject {
        static {
//            DOtherSideJNI.SignalDefinition[] signals = new DOtherSideJNI.SignalDefinition[1];
//            signals[0] = new DOtherSideJNI.SignalDefinition();
//            signals[0].name = "nameChanged";
//            signals[0].parameters = new DOtherSideJNI.ParameterDefinition[0];
//
//            DOtherSideJNI.SlotDefinition[] slots = new DOtherSideJNI.SlotDefinition[2];
//            slots[0] = new DOtherSideJNI.SlotDefinition();
//            slots[0].name = "name";
//            slots[0].returnMetaType = DOtherSideJNI.MetaType.String.value();
//            slots[0].parameters = new DOtherSideJNI.ParameterDefinition[0];
//
//            slots[1] = new DOtherSideJNI.SlotDefinition();
//            slots[1].name = "setName";
//            slots[1].returnMetaType = DOtherSideJNI.MetaType.Void.value();
//            slots[1].parameters = new DOtherSideJNI.ParameterDefinition[1];
//            slots[1].parameters[0] = new DOtherSideJNI.ParameterDefinition();
//            slots[1].parameters[0].name = "value";
//            slots[1].parameters[0].metaType = DOtherSideJNI.MetaType.String.value();
//
//            DOtherSideJNI.PropertyDefinition[] properties = new DOtherSideJNI.PropertyDefinition[1];
//            properties[0] = new DOtherSideJNI.PropertyDefinition();
//            properties[0].name = "name";
//            properties[0].metaType = DOtherSideJNI.MetaType.String.value();
//            properties[0].readSlot = "name";
//            properties[0].writeSlot = "setName";
//            properties[0].notifySignal = "nameChanged";
//
//            staticMetaObject = new QMetaObject(QObject.staticMetaObject, "User", signals, slots, properties);
            try {
                staticMetaObject = new QmlMetaObjectBuilder(User.class).build();
            } catch (IntrospectionException e) {
                e.printStackTrace();
            }
        }

        public User(String name) {
            this.name = name;
        }

        public String getName() {
            return name;
        }

        public void setName(String name) {
            System.out.println("Setting " + name);
            this.name = name;
        }

        public QVariant onSlotCalled(QVariant name, QVariant[] arguments) {
            QVariant result = null;
            if (name.toString().equals("name"))
                result = new QVariant(getName());
            else if (name.toString().equals("setName"))
                setName(arguments[0].toString());
            else
                result = super.onSlotCalled(name, arguments);
            return result;
        }

        public QMetaObject metaObject() {
            return staticMetaObject;
        }

        private static QMetaObject staticMetaObject;
        
        @QProperty
        private String name;
    }

    public static void main(String[] args) {
        System.loadLibrary("DOtherSideJNI");
        QApplication app = new QApplication();
        QQmlApplicationEngine engine = new QQmlApplicationEngine();
        QQmlContext context = engine.rootContext();
        String path = System.getProperty("user.dir") + "/Main.qml";
        User user = new User("John Doo");
        engine.rootContext().setContextProperty("user", new QVariant(user));
        engine.load(path);
        app.exec();
    }
}
