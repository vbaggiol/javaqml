import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicLong;
import java.lang.ref.WeakReference;

public class QObject {
    static {
        objectsMap = new ConcurrentHashMap<Long, WeakReference<QObject>>();
        nextInstanceId = new AtomicLong(1);
        staticMetaObject = new QMetaObject(DOtherSideJNI.qobject_qmetaobject());
    }

    public QObject() {
        instanceId = nextInstanceId.getAndIncrement();
        objectsMap.put(new Long(instanceId), new WeakReference<QObject>(this));
        self = DOtherSideJNI.qobject_create(instanceId, metaObject().voidPointer());
    }

    public QMetaObject metaObject() {
        return staticMetaObject;
    }

    public void delete() {
        DOtherSideJNI.qobject_delete(self);
    }

    public long voidPointer() {
        return self;
    }

    public void deleteLater() {
        DOtherSideJNI.qobject_deleteLater(self);
    }

    @Override
    public void finalize() {
        deleteLater();
    }

    protected QVariant onSlotCalled(QVariant slotName, QVariant[] arguments) {
        return null;
    }

    public static void onSlotCalledCallback(long self, long cName, long[] cArguments) {
        QObject object = (QObject) objectsMap.get(self).get();
        if (object != null) {
            QVariant[] arguments = new QVariant[Math.max(0, cArguments.length - 1)];
            for (int i = 1; i < cArguments.length; ++i)
                arguments[i - 1] = QVariant.fromVoidPointer(cArguments[i], false);
            QVariant name = QVariant.fromVoidPointer(cName, false);
            QVariant result = object.onSlotCalled(name, arguments);
            if (result != null) {
                DOtherSideJNI.qvariant_assign(cArguments[0], result.voidPointer());
            }
        }
    }

    public static final QMetaObject staticMetaObject;

    private void emit(String name, QVariant[] arguments) {
        long[] c_arguments = new long[arguments.length];
        for (int i = 0; i < c_arguments.length; ++i) {
            c_arguments[i] = arguments[i].voidPointer();
        }
        DOtherSide.qobject_signal_emit(voidPointer(), name, c_arguments);
    }

    private static AtomicLong nextInstanceId;
    private static ConcurrentHashMap<Long, WeakReference<QObject>> objectsMap;
    private long self;
    private final long instanceId;
}
