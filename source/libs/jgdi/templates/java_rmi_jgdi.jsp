/**
 * Copyright 2003-2004 Sun Microsystems, Inc. All rights reserved.
 * Use is subject to license terms.
 * -----------------------------------------------------------------------------
 *  Generated from java_rmi_jgdi.template
 *  !!! DO NOT EDIT THIS FILE !!!
 */
<%
  final com.sun.grid.cull.JavaHelper jh = (com.sun.grid.cull.JavaHelper)params.get("javaHelper");
  final com.sun.grid.cull.CullDefinition cullDef = (com.sun.grid.cull.CullDefinition)params.get("cullDef");
  
  class JGDIRMIGenerator extends com.sun.grid.cull.AbstractGDIGenerator {
     
     public JGDIRMIGenerator(com.sun.grid.cull.CullObject cullObject) {
        super(cullObject.getIdlName(),  jh.getClassName(cullObject), cullObject);
        addPrimaryKeys(cullObject, jh);
     }
     
     public void genImport() {
      if(!(cullObject.getType() == cullObject.TYPE_PRIMITIVE || 
             cullObject.getType() == cullObject.TYPE_MAPPED)) {
%>import com.sun.grid.jgdi.configuration.<%=classname%>;        
<%        
      }
     } // end of genImport
     
     public void genUpdateMethods() {
%>
   /**
    *  Update <%=getPrimaryKeyCount() == 0 ? "the" : "a"%> <%=name%> object
    *
    *  @param obj  the <%=name%> object with the new values
    *  @throws RemoteException on any error
    */
   public void update<%=name%>(<%=classname%> obj) throws RemoteException;        
<%   } // end of genUpdateMethod
        
     public void genGetMethod() {
%>   
   /**
    *   Get the <code><%=name%></code> object.
    *   @return the <code><%=name%></code> object
    *   @throws RemoteException on any error
    */
   public <%=classname%> get<%=name%>() throws RemoteException;     
<% } // end of genGetMethod
     
     protected void genGetListMethod() {
%>
   /**
    *   Get all <code><%=name%></code> objects.
    *
    *   @return a list of <code><%=name%></code> objects
    *   @throws RemoteException on any error
    */
   public java.util.List get<%=name%>List() throws RemoteException;
<% } // end of genGetListMethod
     
   protected void genAddMethod() {
%>   
   /**
    *   Add a new <code><%=name%></code> object.
    *
    *   @param obj the new <code><%=name%></code> object
    *   @throws RemoteException on any error
    */
   public void add<%=name%>(<%=classname%> obj) throws RemoteException;
   
<%
   } // end of genAddMethod

   protected void genUpdateMethod() {
%>   
   /**
    *   Update a <code><%=name%></code> object.
    *
    *   @param obj the <code><%=name%></code> object
    *   @throws RemoteException on any error
    */
   public void update<%=name%>(<%=classname%> obj) throws RemoteException;
   
<%
   } // end of genUpdateMethod
   
   protected void genDeleteMethod() {
%>
   /**
    *   Add a delete <code><%=name%></code> object.
    *
    *   @param obj the <code><%=name%></code> object with the primary key information
    *   @throws RemoteException on any error
    */
   public void delete<%=name%>(<%=classname%> obj) throws RemoteException;
   
<%
   } // end of genDeleteMethod
     
   protected void genGetByPrimaryKeyMethod() {
%>
   /**
    *   Get a a <code><%=name%></code> object by its primary key
    *
<%   java.util.Iterator iter = primaryKeys.keySet().iterator();
   boolean first = true;
   while(iter.hasNext()) {
      String pkName = (String)iter.next();
%>    *   @param <%=pkName%>  the <%=pkName%> of the <code><%=name%></code> object <%      
   }
%>      
    *   @return the <code><%=name%></code> object or <code>null</code>
    *   @throws RemoteException on any error
    */
   public <%=classname%> get<%=name%>(<%
   
   iter = primaryKeys.keySet().iterator();
   first = true;
   while(iter.hasNext()) {
      String pkName = (String)iter.next();
      String pkType = (String)primaryKeys.get(pkName);
      if(first) {
         first = false;
      } else {
         %>, <%
      }
      %> <%=pkType%> <%=pkName%><%
   }
   %>) throws RemoteException;
<%        
     } // end of genGetByPrimaryKeyMethod
  } // end of class JGDIRMIGenerator
  
  // ---------------------------------------------------------------------------
  // Build Generator instances
  // ---------------------------------------------------------------------------

  java.util.Iterator iter = cullDef.getObjectNames().iterator();
  java.util.List generators = new java.util.ArrayList();
  while(iter.hasNext()) {
    String name = (String)iter.next();
    com.sun.grid.cull.CullObject cullObj = cullDef.getCullObject(name);
    generators.add(new JGDIRMIGenerator(cullObj));
  }
%>
package com.sun.grid.jgdi.rmi;


import java.rmi.RemoteException; 
import java.rmi.Remote;

<% // Import all cull object names;
    iter = generators.iterator();

    while( iter.hasNext() ) {
       JGDIRMIGenerator gen = (JGDIRMIGenerator)iter.next();
       gen.genImport();
    } // end of while %>
    
    
/**
 *   Remote interface of {@link com.sun.grid.jgdi.JGDI} for a RMI service.
 *   Defines all method as {@link com.sun.grid.jgdi.JGDI}, but throws a
 *   {@link java.rmi.RemoteException} which includes the
 *   {@link com.sun.grid.jgdi.JGDIException} as cause.
 */
public interface JGDIRemote extends JGDIRemoteBase, Remote {
<% iter = generators.iterator();
   while( iter.hasNext() ) {
       JGDIRMIGenerator gen = (JGDIRMIGenerator)iter.next();
       gen.genMethods();
   } // end of while 
%>
}
