public class QMetaObject {
    public QMetaObject(long self) {
        this.self = self;
    }

    public void delete() {
        DOtherSideJNI.qmetaobject_delete(self);
    }

    public long voidPointer() {
        return self;
    }

    private long self;
}
