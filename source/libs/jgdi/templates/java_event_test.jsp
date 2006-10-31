/*___INFO__MARK_BEGIN__*/
/*************************************************************************
 *
 *  The Contents of this file are made available subject to the terms of
 *  the Sun Industry Standards Source License Version 1.2
 *
 *  Sun Microsystems Inc., March, 2001
 *
 *
 *  Sun Industry Standards Source License Version 1.2
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.2 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://gridengine.sunsource.net/Gridengine_SISSL_license.html
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *   The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *   Copyright: 2001 by Sun Microsystems, Inc.
 *
 *   All Rights Reserved.
 *
 ************************************************************************/
/*___INFO__MARK_END__*/
/**
 *  Generated from java_event_test.jsp
 *  !!! DO NOT EDIT THIS FILE !!!
 */
<%
  final com.sun.grid.cull.JavaHelper jh = (com.sun.grid.cull.JavaHelper)params.get("javaHelper");
  final com.sun.grid.cull.CullDefinition cullDef = (com.sun.grid.cull.CullDefinition)params.get("cullDef");
  final com.sun.grid.cull.CullObject cullObj = (com.sun.grid.cull.CullObject)params.get("cullObj");  
  
  
  class TestGenerator {
     
     private com.sun.grid.cull.CullObject cullObj;
     
     public TestGenerator(com.sun.grid.cull.CullObject cullObj) {
        this.cullObj = cullObj;   
     }
     
     private void genAddDelTest() {
        String name = cullObj.getIdlName();
%>
   public void test<%=name%>Events() throws Exception {
<%
     if(cullObj.getType() == cullObj.TYPE_PRIMITIVE) {
           
        if(cullObj.getName().equals("SGE_HOST")) {
%>
      String testObj = TestValueFactory.getNextHostname();
<%        
        } else {
%>
      String testObj = "blubber";
<%
        }
     } else {
%>         
      Object [] testValues = TestValueFactory.getTestValues(<%=name%>.class); 

      assertTrue("No test values for <%=name%>", testValues.length > 0 );
      
      <%=name%> testObj = (<%=name%>)testValues[0];
<%
     }
%>

      WaitForEventThread waitThread = new WaitForEventThread(testObj);

      int flushInterval = 1; // in seconds
      long timeout = flushInterval * 1000 * 3;
      try {

         evc.addEventListener(waitThread);

         evc.subscribeAdd<%=name%>(true);
         evc.setAdd<%=name%>Flush(true, flushInterval);
         
         evc.subscribeDel<%=name%>(true);
         evc.setDel<%=name%>Flush(true, flushInterval);
<% 
   if (cullObj.hasModifyOperation()) {
%>         
         evc.subscribeMod<%=name%>(true);            
         evc.setMod<%=name%>Flush(true, flushInterval);
<%
   }
%>         

         evc.commit();
         // evc.start();

         waitThread.start();

         Thread.yield();

         jgdi.add<%=name%>(testObj);

         logger.fine(testObj.toString() + " added");
         assertTrue("<%=name%>: Did not get the add event", waitThread.waitForAddEvent(timeout) );

<% 
   if (cullObj.hasModifyOperation()) {
%>         
         // TODO modify the test object
<%
     if(name.equals("Calendar")) {
%>
         testObj.setYearCalendar("01.01.2007");
<%         
     } else if (name.equals("User")) {
%>
         testObj.setOticket(10);
<%         
     } else if (name.equals("ParallelEnvironment")) {
%>
         testObj.setSlots(10);
<%         
     }
%>
         jgdi.update<%=name%>(testObj);
         logger.fine(testObj.toString() + " modified");
         assertTrue("<%=name%>: Did not get the mod event", waitThread.waitForModEvent(timeout) );
<%
   } // end of cullObj.hasModifyOperation()
%>         

         jgdi.delete<%=name%>(testObj);
         logger.fine(testObj.toString() + " deleted");
         testObj = null;

         assertTrue("<%=name%>: Did not get the del event", waitThread.waitForDelEvent(timeout) );

      } finally {
         waitThread.interrupt();
         evc.subscribeAdd<%=name%>(false);
         evc.subscribeDel<%=name%>(false);
<% 
   if (cullObj.hasModifyOperation()) {
%>         
         evc.subscribeMod<%=name%>(false);            
<%
   }
%>         
         evc.commit();
         
         if (testObj != null) {
            try {
               jgdi.delete<%=name%>(testObj);
            } catch(Exception e) {
               // ignore
            }
         }
      }
   }
<%
     } // genAddDelTest
     
     private void genStaticTest() {
        String name = cullObj.getIdlName();
        
%>
   public void test<%=name%>() throws Exception {

      // static test for <%=name%> not implemented
      <%=name%> testObj = jgdi.get<%=name%>();
      
<%
         if(name.equals("SchedConf")) {         
%>
         int orgValue = testObj.getMaxujobs();
<%
         }
%>        
  
    
      WaitForEventThread waitThread = new WaitForEventThread(testObj);
    
      int flushInterval = 1; // in seconds
      long timeout = flushInterval * 1000 * 3;
      try {

         evc.addEventListener(waitThread);

         evc.subscribeMod<%=name%>(true);
         evc.setMod<%=name%>Flush(true, flushInterval);
         
         evc.commit();
         waitThread.start();
         Thread.yield();
<%
         if(name.equals("SchedConf")) {         
%>
         testObj.setMaxujobs(orgValue+1);
<%
         }
%>  

         jgdi.update<%=name%>(testObj);
         
         assertTrue("<%=name%>: Did not get the mod event", waitThread.waitForModEvent(timeout) );
         
      } finally {
         waitThread.interrupt();
         evc.subscribeMod<%=name%>(false);
         evc.commit();

         testObj = jgdi.get<%=name%>();
<%
         if(name.equals("SchedConf")) {         
%>
         testObj.setMaxujobs(orgValue);
<%
         }
%>  
         jgdi.update<%=name%>(testObj);
      }
         
   }
<%        
        
     } // end of genStaticTest
     
  } // end of class TestGenerator
%>
package com.sun.grid.jgdi.event;


import com.sun.grid.jgdi.JGDIException;
import com.sun.grid.jgdi.JGDI;
import com.sun.grid.jgdi.configuration.*;
import com.sun.grid.jgdi.configuration.reflect.*;
import junit.framework.*;
import com.sun.grid.jgdi.BaseTestCase;
import java.util.Hashtable;
import com.sun.grid.jgdi.EventClient;
import com.sun.grid.jgdi.JGDIFactory;
import java.util.Collection;
import java.util.LinkedList;
import java.util.Map;
import java.util.Iterator;
import com.sun.grid.jgdi.TestValueFactory;

public class <%=cullObj.getIdlName()%>EventTestCase extends BaseTestCase {

   private JGDI jgdi;
   private JGDI jgdi_evc;
   private EventClient evc;
   
   public <%=cullObj.getIdlName()%>EventTestCase(String name) {
      super(name);
   }
   
   public static Test suite() {
      TestSuite suite = new TestSuite(<%=cullObj.getIdlName()%>EventTestCase.class);
      return suite;
   }
   
   protected void setUp() throws Exception {
      logger.fine("Loading jgdi");
      // System.loadLibrary( "jgdi" );
      
      jgdi = createJGDI();
      jgdi_evc = createJGDI();
      evc = JGDIFactory.createEventClient(jgdi_evc, 0);
      evc.start();
      super.setUp();
      logger.fine("SetUp done");
   }
   
   protected void tearDown() throws Exception {
      try {
        evc.close();
      } finally {
         jgdi.close();
         jgdi_evc.close();
      }
   }
   

<%
   TestGenerator gen = new  TestGenerator(cullObj);

   if( cullObj.hasAddOperation() &&
       cullObj.hasAddEvent() &&
       cullObj.hasDeleteOperation() &&
       cullObj.hasDeleteEvent() ) {
      gen.genAddDelTest();
   } else if(cullObj.hasModifyEvent() && cullObj.hasModifyOperation()) {
      if (!cullObj.getIdlName().equals("JobSchedulingInfo")) {
         gen.genStaticTest();
      }
   }
%>

}