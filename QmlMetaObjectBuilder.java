
import java.beans.BeanInfo;
import java.beans.IntrospectionException;
import java.beans.Introspector;
import java.beans.PropertyDescriptor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.lang.reflect.Parameter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * A class that uses introspection to create the {@link QMetaObject}
 */
public class QmlMetaObjectBuilder {

    private List<String> slotNames = new ArrayList<>();
    private final Class<? extends QObject> qClass;
    private final List<PropertyDescriptor> propertyDescriptors;
    
    QMetaObject buildx() {
        DOtherSideJNI.SlotDefinition[] slots = new DOtherSideJNI.SlotDefinition[slotNames.size()];
        slots[0] = new DOtherSideJNI.SlotDefinition();
        slots[0].name = "name";
        slots[0].returnMetaType = DOtherSideJNI.MetaType.String.value();
        slots[0].parameters = new DOtherSideJNI.ParameterDefinition[0];

        slots[1] = new DOtherSideJNI.SlotDefinition();
        slots[1].name = "setName";
        slots[1].returnMetaType = DOtherSideJNI.MetaType.Void.value();
        
        slots[1].parameters = new DOtherSideJNI.ParameterDefinition[1];
        slots[1].parameters[0] = new DOtherSideJNI.ParameterDefinition();
        slots[1].parameters[0].name = "value";
        slots[1].parameters[0].metaType = DOtherSideJNI.MetaType.String.value();

        DOtherSideJNI.PropertyDefinition[] properties = new DOtherSideJNI.PropertyDefinition[1];
        properties[0] = new DOtherSideJNI.PropertyDefinition();
        properties[0].name = "name";
        properties[0].metaType = DOtherSideJNI.MetaType.String.value();
        properties[0].readSlot = "name";
        properties[0].writeSlot = "setName";
        properties[0].notifySignal = "nameChanged";

        QMetaObject staticMetaObject = null; //new QMetaObject(QObject.staticMetaObject, "User", signals, slots, properties);
        
        return staticMetaObject;
    }

    
    /**
     * Creates a @link{DOtherSideJNI.SignalDefinition} according to the naming convention {@code propertyName + "Changed"}
     * @return
     */
    DOtherSideJNI.SignalDefinition createDefaultSignalDefinition(String propertyName) {
        DOtherSideJNI.SignalDefinition signalDef = new DOtherSideJNI.SignalDefinition();
        signalDef.name = propertyName + "Changed";
        signalDef.parameters = new DOtherSideJNI.ParameterDefinition[0];
        return signalDef;
    }
    
    /**
     * Creates a {@link DOtherSideJNI.ParameterDefinition}
     * <p>
     * this requires the java code to be compiled with the "-parameters" argument, 
     * otherwise arg0, arg1, ...  is returned as parameter name
     * @param javaParameter
     * @return
     */
    DOtherSideJNI.ParameterDefinition createParameter(Parameter javaParameter) {
        String javaParameterName = javaParameter.getName();
        Class<?> javaParameterType = javaParameter.getType();
        Util.assertValidString(javaParameterName);
        Util.assertKnownType(javaParameterType);
        DOtherSideJNI.ParameterDefinition parameter = new DOtherSideJNI.ParameterDefinition();
        parameter.name = javaParameterName;
        parameter.metaType = Util.toMetaType(javaParameterType).value();
        return parameter;
    }
    
    DOtherSideJNI.PropertyDefinition createPropertyDefinition(PropertyDescriptor beansDescriptor) {
        DOtherSideJNI.PropertyDefinition qPropDef = new DOtherSideJNI.PropertyDefinition();
        qPropDef.name = beansDescriptor.getName();
        Util.isKnownType(beansDescriptor.getPropertyType());
        qPropDef.metaType = Util.toMetaType(beansDescriptor.getPropertyType()).value();
        qPropDef.readSlot = fixGetterNameHack(beansDescriptor.getReadMethod().getName());
        qPropDef.writeSlot = beansDescriptor.getWriteMethod().getName();
        // TODO this should be more flexible
        qPropDef.notifySignal = qPropDef.name + "Changed";
        return qPropDef;
    }
    
    /**
     * Creates a {@link DOtherSideJNI.SlotDefinition} for the given method
     * @param method
     * @return
     */
    DOtherSideJNI.SlotDefinition createSlot(Method method) {
        String methodName = method.getName();
        Util.assertValidString(methodName);
        Util.assertKnownType(method.getReturnType());
        DOtherSideJNI.SlotDefinition getter = new DOtherSideJNI.SlotDefinition();

        getter.name = fixGetterNameHack(methodName);
        getter.parameters = Arrays.stream(method.getParameters()).map(this::createParameter)
                .toArray(DOtherSideJNI.ParameterDefinition[]::new);
        getter.returnMetaType = Util.toMetaType(method.getReturnType()).value();
        return getter;
    }

    /**
     * FIXME
     * This is a hack because Qt expects the getter name not to have a "get", i.e. it wants to use name, instead of getName in QML 
     * @param methodName
     * @return
     * @deprecated this should be solved in a better way
     */
    @Deprecated
    private String fixGetterNameHack(String methodName) {
        if (methodName.startsWith("get")) {
            return Introspector.decapitalize(methodName.substring("get".length(), methodName.length()));
        } else {
            return methodName;
        }
    }
    
    /**
     * Constructor
     * @param qClass the class for which to create the {@link QMetaObject}
     * @throws IntrospectionException
     */
    public QmlMetaObjectBuilder(Class<? extends QObject> qClass) throws IntrospectionException {
        this.qClass = qClass;
        BeanInfo beanInfo = Introspector.getBeanInfo(qClass);
        PropertyDescriptor[] beanPropertyDescriptors = beanInfo.getPropertyDescriptors();
        Set<String> qPropertyNames = findQProperties(qClass);
        List<PropertyDescriptor> qpd = Arrays.stream(beanPropertyDescriptors)
                .filter(p -> qPropertyNames.contains(p.getName())).collect(Collectors.toList());
        propertyDescriptors = Collections.unmodifiableList(qpd);
    }
    
    /**
     * Creates the array of {@link DOtherSideJNI.PropertyDefinition}s for the class passed in the constructor 
     * @return
     */
    DOtherSideJNI.PropertyDefinition[] createQPropertyDefinitions() {
        DOtherSideJNI.PropertyDefinition[] jniProperties = 
                propertyDescriptors.stream().map(this::createPropertyDefinition)
                .toArray(DOtherSideJNI.PropertyDefinition[]::new);
        return jniProperties;
    }

    /** helper method to get all methods */
    private Stream<Method> getReadAndWriteMethods(PropertyDescriptor propertyDescriptor) { 
        // getXxxMethod can return null, which must be filtered out
        return Stream.of(propertyDescriptor.getReadMethod(), propertyDescriptor.getWriteMethod()).filter(f -> f != null);
    }
        
    /**
     * Creates the array of {@link DOtherSideJNI.SlotDefinition}s for the class passed in the constructor 
     * @return
     */
    DOtherSideJNI.SlotDefinition[] createQSlotDefinitions() {
        DOtherSideJNI.SlotDefinition[] jniSlots = propertyDescriptors.stream().flatMap(this::getReadAndWriteMethods)
                .map(meth -> createSlot(meth)).toArray(DOtherSideJNI.SlotDefinition[]::new);
        
        return jniSlots;
    }

    /**
     * Creates the array of {@link DOtherSideJNI.SignalDefinition}s for the class passed in the constructor 
     * @return
     */
    DOtherSideJNI.SignalDefinition[] createSignalDefinitions() {
        DOtherSideJNI.SignalDefinition[] jniSignals = propertyDescriptors.stream()
                .map(qpd -> createDefaultSignalDefinition(qpd.getName())).toArray(DOtherSideJNI.SignalDefinition[]::new);
        return jniSignals;
    }

    /**
     * Finds the names of the fields that are annotated with {@link QProperty}
     * @param qClass
     */
    private static Set<String> findQProperties(Class<? extends QObject> qClass) {
        return Arrays.stream(qClass.getDeclaredFields()).filter((field)-> field.isAnnotationPresent(QProperty.class))
                .map(Field::getName).collect(Collectors.toSet());
    }
    
    /**
     * Builds the {@link QMetaObject}
     * @return
     */
    public QMetaObject build() {
        QMetaObject qmo = new QMetaObject(QObject.staticMetaObject, this.qClass.getSimpleName(), createSignalDefinitions(), createQSlotDefinitions(), createQPropertyDefinitions());
        return qmo;
    }
    
//    public static void main(String[] args) throws IntrospectionException {
//        System.loadLibrary("DOtherSideJNI");
//
//        QmlMetaObjectBuilder builder = new QmlMetaObjectBuilder(PingPong.class);
//        builder.build();
//    }
}
