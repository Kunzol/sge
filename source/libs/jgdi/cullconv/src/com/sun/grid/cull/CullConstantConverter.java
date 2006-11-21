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
package com.sun.grid.cull;

import java.io.File;
import java.util.Iterator;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author richard.hierlmeier@sun.com
 */
public class CullConstantConverter extends AbstractCullToJavaConverter {
   
   public final static Logger logger = Logger.getLogger("cullconv");
   
   static {
      System.loadLibrary("drmaa");
   }
   
   /** Creates a new instance of CullConstantConverter */
   public CullConstantConverter() {
      
   }

   public void convert(CullDefinition cullDef) throws java.io.IOException {

      
      String packagename = getPackagename();
      
      String className = "CullConstants";
      
      File file = getFileForClass(className);
      
      boolean dirty = false;
      
      if(file.exists()) {

          Iterator iter = cullDef.getNameSpaceNameSet().iterator();

          while( iter.hasNext() ) {
             CullNameSpace ns = cullDef.getNameSpace((String)iter.next());

             File defFile = cullDef.getNameSource(ns.getNameSpace());
             if(defFile == null) {
                 logger.log(Level.WARNING, "no source file for namespace " + ns.getNameSpace() + " found");
             } else if(defFile.lastModified() > file.lastModified()) {
                 logger.log(Level.FINE, "namespace " + ns.getNameSpace() + " is dirty (defined in " + defFile + ")");
                 dirty = true;
                  break;
             } else {
                 logger.log(Level.FINE, "namespace " + ns.getNameSpace() + " is up to date");
             }
          }
      } else {
          dirty = true;
      }
      
      if(dirty) {
          Printer p = new Printer(file);

          p.println("/* Generated by " + getClass().getName() );
          p.println("*/");
          if( packagename != null ) {
             p.print( "package " );
             p.print( packagename );
             p.println( ";" );
          }

          p.print( "public interface ");
          p.println( className );
          p.println( " {");
          p.indent();


          Iterator iter = cullDef.getNameSpaceNameSet().iterator();

          while( iter.hasNext() ) {
             CullNameSpace ns = cullDef.getNameSpace((String)iter.next());
             writeNameSpace(ns,p);
             p.println();
          }

          p.deindent();
          p.println("}");
          p.flush();
      }
      
   }
   
   private void writeNameSpace( CullNameSpace ns, Printer p ) {
      
      
       Iterator iter = ns.getNames().iterator();
       
       while(iter.hasNext()) {
          String name = (String)iter.next();
          
          p.print("public static final int " );
//          p.print( ns.getNameSpace() );
//          p.print( '_' );
          p.print( name );
          p.print( " = ");
          p.print( strToNm(name ));
          p.println(";");
       }
   }
   
   private native int strToNm(String name);
   
}
