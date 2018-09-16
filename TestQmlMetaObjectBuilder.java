/**
 * Copyright (c) 2018 European Organisation for Nuclear Research (CERN), All Rights Reserved.
 */

import static org.junit.Assert.assertEquals;

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
        DOtherSideJNI.SlotDefinition[] slots = builder.createQSlotDefinitions();
        assertEquals(2, slots.length);
        assertEquals("name", slots[0].name);
        assertEquals(DOtherSideJNI.MetaType.String.value(), slots[0].returnMetaType);
        assertEquals(0, slots[0].parameters.length);
        
        assertEquals("setName", slots[1].name);
        assertEquals(DOtherSideJNI.MetaType.Void.value(), slots[1].returnMetaType);
        assertEquals(1, slots[1].parameters.length);
        assertEquals("value", slots[1].parameters[0].name);
        assertEquals(DOtherSideJNI.MetaType.String.value(), slots[1].parameters[0].metaType);
    }
   
    @Test
    public void testCreatePropertyDefinitions() {
        DOtherSideJNI.PropertyDefinition[] properties = builder.createQPropertyDefinitions();
        assertEquals(1, properties.length);
        assertEquals("name", properties[0].name);
        assertEquals(DOtherSideJNI.MetaType.String.value(), properties[0].metaType);
        assertEquals("name", properties[0].readSlot);
        assertEquals("setName", properties[0].writeSlot);
        assertEquals("nameChanged", properties[0].notifySignal);
    }
}
