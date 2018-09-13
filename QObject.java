public class QObject {
    static {
        staticMetaObject = new QMetaObject(DOtherSideJNI.qobject_qmetaobject());
    }

    public QObject() {
        self = 0;
    }

    public QMetaObject metaObject() {
        return staticMetaObject;
    }

    public void delete() {
        DOtherSideJNI.qobject_delete(self);
    }

    protected void onSlotCalled(QVariant slotName, QVariant[] parameters) {

    }

    public static final QMetaObject staticMetaObject;

    private long self;
}
