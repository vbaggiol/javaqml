import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.beans.IntrospectionException;

import org.junit.Before;
import org.junit.Test;

public class TestQmlMetaObjectBuilder {
    private QmlMetaObjectBuilder builder;
    @Before 
    public void setUp() throws IntrospectionException {
        builder = new QmlMetaObjectBuilder(Main.User.class);
    }
    
    @Test
    public void testCreateSignalDefinitions() {
        DOtherSideJNI.SignalDefinition[] signals = builder.createSignalDefinitions();
        assertEquals(1, signals.length);
        assertEquals("nameChanged", signals[0].name);
        assertEquals(0, signals[0].parameters.length);
    }

    @Test
    public void testCreateSlotDefinitions() {
        DOtherSideJNI.SlotDefinition[] slots = builder.createSlotDefinitions();
        assertEquals(2, slots.length);
        assertEquals("name", slots[0].name);
        assertEquals(DOtherSideJNI.MetaType.String.value(), slots[0].returnMetaType);
        assertEquals(0, slots[0].parameters.length);
        
        assertEquals("setName", slots[1].name);
        assertEquals(DOtherSideJNI.MetaType.Void.value(), slots[1].returnMetaType);
        assertEquals(1, slots[1].parameters.length);
        String parameterName = slots[1].parameters[0].name;
        // if the code was compiled with the option -parameters, then the name in the source code is returned
        // otherwise arg0 is generated
        assertTrue("name".equals(parameterName) || "arg0".equals(parameterName));
        assertEquals(DOtherSideJNI.MetaType.String.value(), slots[1].parameters[0].metaType);
    }
   
    @Test
    public void testCreatePropertyDefinitions() {
        DOtherSideJNI.PropertyDefinition[] properties = builder.createPropertyDefinitions();
        assertEquals(1, properties.length);
        assertEquals("name", properties[0].name);
        assertEquals(DOtherSideJNI.MetaType.String.value(), properties[0].metaType);
        assertEquals("name", properties[0].readSlot);
        assertEquals("setName", properties[0].writeSlot);
        assertEquals("nameChanged", properties[0].notifySignal);
    }
}
