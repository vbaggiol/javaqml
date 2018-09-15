public class QVariant {
    public static QVariant fromVoidPointer(long ptr, boolean takeOwnership) {
        QVariant result = new QVariant();
        result.delete();
        result.self = takeOwnership ? ptr : DOtherSideJNI.qvariant_create_qvariant(ptr);
        return result;
    }

    public QVariant() {
        this.self = DOtherSideJNI.qvariant_create();
    }

    public QVariant(int value) {
        this.self = DOtherSideJNI.qvariant_create_int(value);
    }

    public QVariant(boolean value) {
        this.self = DOtherSideJNI.qvariant_create_bool(value);
    }

    public QVariant(String value) {
        this.self = DOtherSideJNI.qvariant_create_string(value);
    }

    public QVariant(QVariant value) {
        this.self = DOtherSideJNI.qvariant_create_qvariant(value.voidPointer());
    }

    public QVariant(float value) {
        this.self = DOtherSideJNI.qvariant_create_float(value);
    }

    public QVariant(double value) {
        this.self = DOtherSideJNI.qvariant_create_double(value);
    }

    public QVariant(QObject object) {
        this.self = DOtherSideJNI.qvariant_create_qobject(object.voidPointer());
    }

    public void SetValue(int value) {
        DOtherSideJNI.qvariant_setInt(self, value);
    }

    public void SetValue(boolean value) {
        DOtherSideJNI.qvariant_setBool(self, value);
    }

    public void SetValue(String value) {
        DOtherSideJNI.qvariant_setString(self, value);
    }

    public void SetValue(float value) {
        DOtherSideJNI.qvariant_setFloat(self, value);
    }

    public void SetValue(double value) {
        DOtherSideJNI.qvariant_setDouble(self, value);
    }

    public void setValue(QObject value) {
        DOtherSideJNI.qvariant_setQObject(self, value.voidPointer());
    }

    public int toInt() {
        return DOtherSideJNI.qvariant_toInt(self);
    }

    public boolean toBool() {
        return DOtherSideJNI.qvariant_toBool(self);
    }

    public float toFloat() {
        return DOtherSideJNI.qvariant_toFloat(self);
    }

    public double toDouble() {
        return DOtherSideJNI.qvariant_toDouble(self);
    }

    public String toString() {
        return DOtherSideJNI.qvariant_toString(self);
    }

    public void delete() {
        DOtherSideJNI.qvariant_delete(self);
    }

    public boolean isNull() {
        return DOtherSideJNI.qvariant_isNull(self);
    }

    public long voidPointer() {
        return self;
    }

    private long self;
}
