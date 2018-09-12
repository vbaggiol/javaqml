public class QMetaObject {
    public QMetaObject(String className,
                       DOtherSideJNI.SignalDefinition[] signals,
                       DOtherSideJNI.SlotDefinition[] slots,
                       DOtherSideJNI.PropertyDefinition[] properties) {
        this.self = DOtherSideJNI.qmetaobject_create(0, className, signals, slots, properties);
    }

    public void delete() {
        DOtherSideJNI.qmetaobject_delete(self);
    }

    public long voidPointer() {
        return self;
    }

    private long self;
}
