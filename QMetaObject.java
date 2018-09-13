public class QMetaObject {
    public QMetaObject(long self) {
        this.self = self;
    }

    public QMetaObject(QMetaObject superClassMetaObject,
                       String className,
                       DOtherSideJNI.SignalDefinition[] signals,
                       DOtherSideJNI.SlotDefinition[] slots,
                       DOtherSideJNI.PropertyDefinition[] properties) {
        this.self = DOtherSideJNI.qmetaobject_create(superClassMetaObject.voidPointer(), className, signals, slots, properties);
        this.signals = signals;
        this.slots = slots;
        this.properties = properties;
    }

    public DOtherSideJNI.SignalDefinition[] signals() {
        return this.signals;
    }

    public DOtherSideJNI.SlotDefinition[] slots() {
        return this.slots;
    }

    public DOtherSideJNI.PropertyDefinition[] properties() {
        return this.properties;
    }

    public void delete() {
        DOtherSideJNI.qmetaobject_delete(self);
    }

    public long voidPointer() {
        return self;
    }

    @Override
    public void finalize() {
        delete();
    }

    private long self;
    private DOtherSideJNI.SignalDefinition[] signals;
    private DOtherSideJNI.SlotDefinition[] slots;
    private DOtherSideJNI.PropertyDefinition[] properties;
}
