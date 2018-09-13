public class QVariant implements Cloneable {
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

    @Override
    protected QVariant clone() {
        return new QVariant(this);
    }

    @Override
    public void finalize() {
        delete();
    }

    private long self;
}
