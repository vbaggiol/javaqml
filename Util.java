public class Util {
    public static void assertValidString(String str) {
        if (!isValidString(str)) {
            throw new IllegalArgumentException("Not a valid string '" + str + "'");
        }
    }
    
    public static boolean isValidString(String str) {
        return (str != null) && !"".equals(str.trim());
    }

    /**
     * @param propertyType
     */
    public static boolean isKnownType(Class<?> propertyType) {
        return toMetaType(propertyType).value() != DOtherSideJNI.MetaType.UnknownType.value(); 
        
    }

    public static void assertKnownType(Class<?> propertyType) {
        if (!isKnownType(propertyType)) {
            throw new IllegalArgumentException("Unknown type '" + propertyType + "'");
        }
    }

    static DOtherSideJNI.MetaType toMetaType(Class<?> javaType) {
        if (Boolean.class.equals(javaType) || Boolean.TYPE.equals(javaType)) {
            return DOtherSideJNI.MetaType.Bool;
        } else if (Integer.class.equals(javaType) || Integer.TYPE.equals(javaType)) {
            return DOtherSideJNI.MetaType.Int;
        } else if (Double.class.equals(javaType) || Double.TYPE.equals(javaType)) {
            return DOtherSideJNI.MetaType.Double;
        } else if (Float.class.equals(javaType) || Float.TYPE.equals(javaType)) {
            return DOtherSideJNI.MetaType.Float;
        } else if (String.class.equals(javaType)) {
            return DOtherSideJNI.MetaType.String;
        } else if (QObject.class.equals(javaType)) {
            return DOtherSideJNI.MetaType.QObject;
        } else if (QVariant.class.equals(javaType)) {
            return DOtherSideJNI.MetaType.QVariant;
        } else if (Void.class.equals(javaType) || Void.TYPE.equals(javaType)) {
            return DOtherSideJNI.MetaType.Void;
        }
        return DOtherSideJNI.MetaType.UnknownType;
        //TODO we are not handling VoidStr(31) void* check if we should
    }

}
