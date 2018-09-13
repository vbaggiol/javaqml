public class QObject {
    static {
        staticMetaObject = DOtherSideJNI.qobject_qmetaobject();
    }

    public QObject() {
        self = 0;
    }

    public static QMetaObject metaObject() {
        return staticMetaObject;
    }

    public QMetaObject metaObject() {
        return QObject.metaObject();
    }

    public void delete() {
        return DOtherSideJNI.qobject_delete(self);
    }

    protected void onSlotCalled(QVariant slotName, QVariant[] parameters) {

    }

    public static final QMetaObject staticMetaObject;

    private long self;
}
