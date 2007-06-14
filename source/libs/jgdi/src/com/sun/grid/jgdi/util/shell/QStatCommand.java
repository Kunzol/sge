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
package com.sun.grid.jgdi.util.shell;

import com.sun.grid.jgdi.JGDI;
import com.sun.grid.jgdi.monitoring.BasicQueueOptions;
import com.sun.grid.jgdi.monitoring.ClusterQueueSummaryOptions;
import com.sun.grid.jgdi.monitoring.QueueInstanceSummaryOptions;
import com.sun.grid.jgdi.monitoring.QueueInstanceSummaryPrinter;
import com.sun.grid.jgdi.monitoring.QueueInstanceSummaryResult;
import com.sun.grid.jgdi.monitoring.filter.JobStateFilter;
import com.sun.grid.jgdi.monitoring.filter.ParallelEnvironmentFilter;
import com.sun.grid.jgdi.monitoring.filter.QueueFilter;
import com.sun.grid.jgdi.monitoring.filter.QueueStateFilter;
import com.sun.grid.jgdi.monitoring.filter.ResourceAttributeFilter;
import com.sun.grid.jgdi.monitoring.filter.ResourceFilter;
import com.sun.grid.jgdi.monitoring.filter.UserFilter;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.util.LinkedList;
import java.util.List;

/**
 *
 */
public class QStatCommand extends AbstractCommand {
    
    /**
     * Creates a new instance of QStatCommand
     */
    public QStatCommand(Shell shell, String name) {
        super(shell, name);
    }
    
    public String getUsage() {
        StringWriter sw = new StringWriter();
        PrintWriter pw = new PrintWriter(sw);
        
        pw.println("usage: qstat [options]");
        pw.println("        [-ext]                            view additional attributes");
        pw.println("        [-explain a|c|A|E]                show reason for c(onfiguration amiguous), a(larm), suspend A(larm), E(rror) state");
        pw.println("        [-f]                              full output");
        pw.println("        [-F [resource_attributes]]        full output and show (selected) resources of queue(s)");
        pw.println("        [-g {c}]                          display cluster queue summary");
        pw.println("        [-g {d}]                          display all job-array tasks (do not group)");
        pw.println("        [-g {t}]                          display all parallel job tasks (do not group)");
        pw.println("        [-help]                           print this help");
        pw.println("        [-j job_identifier_list ]         show scheduler job information");
        pw.println("        [-l resource_list]                request the given resources");
        pw.println("        [-ne]                             hide empty queues");
        pw.println("        [-pe pe_list]                     select only queues with one of these parallel environments");
        pw.println("        [-q wc_queue_list]                print information on given queue");
        pw.println("        [-qs {a|c|d|o|s|u|A|C|D|E|S}]     selects queues, which are in the given state(s)");
        pw.println("        [-r]                              show requested resources of job(s)");
        pw.println("        [-s {p|r|s|z|hu|ho|hs|hj|ha|h|a}] show pending, running, suspended, zombie jobs,");
        pw.println("                                          jobs with a user/operator/system hold,");
        pw.println("                                          jobs with a start time in future or any combination only.");
        pw.println("                                          h is an abbreviation for huhohshjha");
        pw.println("                                          a is an abbreviation for prsh");
        pw.println("        [-t]                              show task information (implicitly -g t)");
        pw.println("        [-u user_list]                    view only jobs of this user");
        pw.println("        [-U user_list]                    select only queues where these users have access");
        pw.println("        [-urg]                            display job urgency information");
        pw.println("        [-pri]                            display job priority information");
        pw.println("        [-xml]                            display the information in XML-Format");
        pw.close();
        return sw.getBuffer().toString();
    }
    
    public void run(String[] args) throws Exception {
        BasicQueueOptions options = parse(args);
        
        JGDI jgdi = getShell().getConnection();
        
        if (jgdi == null) {
            throw new IllegalStateException("Not connected");
        }
        
        PrintWriter pw = new PrintWriter(System.out);
        if (options instanceof QueueInstanceSummaryOptions) {
            QueueInstanceSummaryResult res = jgdi.getQueueInstanceSummary((QueueInstanceSummaryOptions)options);
            QueueInstanceSummaryPrinter.print(pw, res, (QueueInstanceSummaryOptions)options);
        } else {
            List res = jgdi.getClusterQueueSummary((ClusterQueueSummaryOptions)options);
            pw.println("printing cluster queue summary not yet implemented");
        }
        pw.flush();
        
    }
    
    private BasicQueueOptions parse(String [] args) throws Exception {
        boolean ext = false;
        Character explain = null;
        boolean fullOutput = false;
        ResourceAttributeFilter resourceAttributeFilter = null;
        StringBuffer groupOptions = new StringBuffer();
        ResourceFilter resourceFilter = null;
        boolean showEmptyQueues = true;
        ParallelEnvironmentFilter peFilter = null;
        JobStateFilter jobStateFilter = null;
        QueueFilter queueFilter = null;
        QueueStateFilter queueStateFilter = null;
        boolean showRequestJobResources = false;
        boolean showTaskInfo = false;
        UserFilter jobUserFilter = null;
        UserFilter queueUserFilter = null;
        boolean showUrgency = false;
        boolean showJobPriority = false;
        
        LinkedList argList = new LinkedList();
        for (int i = 0; i < args.length; i++) {
            argList.add(args[i]);
        }
        
        while (!argList.isEmpty()) {
            String arg = (String)argList.removeFirst();
            
            if (arg.equals("-ext")) {
                ext = true;
            } else if (arg.equals("-explain")) {
                if (argList.isEmpty()) {
                    throw new IllegalArgumentException("-explain requires explain char");
                }
                arg = (String)argList.removeFirst();
                explain = new Character(arg.charAt(0));
                fullOutput = true;
            } else if (arg.equals("-f")) {
                fullOutput = true;
            } else if (arg.equals("-F")) {
                if (!argList.isEmpty()) {
                    arg = (String)argList.getFirst();
                    // we allow only a comma separated arg string 
                    // qhost CLI allows also whitespace separated arguments
                    if (!arg.startsWith("-")) {
                        arg = (String)argList.removeFirst();
                        resourceAttributeFilter = ResourceAttributeFilter.parse(arg);
                    } else {
                        resourceAttributeFilter = new ResourceAttributeFilter();
                    }
                } else {
                    resourceAttributeFilter = new ResourceAttributeFilter();
                }
                fullOutput = true;
            } else if (arg.equals("-g")) {
                if (argList.isEmpty()) {
                    throw new IllegalArgumentException("-g requires additional argument");
                }
                arg = (String)argList.removeFirst();
                groupOptions.append(arg);
            } else if (arg.equals("-j")) {
                throw new IllegalStateException("-j switch not implemented");
            } else if (arg.equals("-l")) {
                if (argList.isEmpty()) {
                    throw new IllegalArgumentException("missing resource_list");
                }
                resourceFilter = new ResourceFilter();
                arg = (String)argList.removeFirst();
                resourceFilter = ResourceFilter.parse(arg);
            } else if (arg.equals("-ne")) {
                showEmptyQueues = false;
            } else if (arg.equals("-pe")) {
                if (argList.isEmpty()) {
                    throw new IllegalArgumentException("missing pe_list");
                }
                arg = (String)argList.removeFirst();
                peFilter = ParallelEnvironmentFilter.parse(arg);
            } else if (arg.equals("-q")) {
                if (argList.isEmpty()) {
                    throw new IllegalArgumentException("missing wc_queue_list");
                }
                arg = (String)argList.removeFirst();
                queueFilter = QueueFilter.parse(arg);
            } else if (arg.equals("-qs")) {
                if (argList.isEmpty()) {
                    throw new IllegalArgumentException("missing queue state definition");
                }
                arg = (String)argList.removeFirst();
                queueStateFilter = QueueStateFilter.parse(arg);
            } else if (arg.equals("-r")) {
                showRequestJobResources = true;
            } else if (arg.equals("-s")) {
                if (argList.isEmpty()) {
                    throw new IllegalArgumentException("missing job state definition");
                }
                arg = (String)argList.removeFirst();
                jobStateFilter = JobStateFilter.parse(arg);
            } else if (arg.equals("-t")) {
                showTaskInfo = true;
                groupOptions.append("t");
            } else if (arg.equals("-u")) {
                if (argList.isEmpty()) {
                    throw new IllegalArgumentException("missing user_list");
                }
                arg = (String)argList.removeFirst();
                jobUserFilter = UserFilter.parse(arg);
            } else if (arg.equals("-U")) {
                if (argList.isEmpty()) {
                    throw new IllegalArgumentException("missing user_list");
                }
                arg = (String)argList.removeFirst();
                queueUserFilter = UserFilter.parse(arg);
            } else if (arg.equals("-urg")) {
                showUrgency = true;
            } else if (arg.equals("-pri")) {
                showJobPriority = true;
            } else {
                throw new IllegalStateException("Unknown argument" + arg);
            }
        }
        
        BasicQueueOptions options = null;
        
        if (groupOptions.indexOf("c") >= 0) {
            options = new ClusterQueueSummaryOptions();
        } else {
            options = new QueueInstanceSummaryOptions();
        }
        
        if (ext) {
            options.setShowAdditionalAttributes(true);
        }
        
        if (resourceFilter != null) {
            options.setResourceFilter(resourceFilter);
        }
        if (queueFilter != null) {
            options.setQueueFilter(queueFilter);
        }
        if (queueStateFilter != null) {
            options.setQueueStateFilter(queueStateFilter);
        }
        if (queueUserFilter != null) {
            options.setQueueUserFilter(queueUserFilter);
        }
        
        if ( options instanceof ClusterQueueSummaryOptions) {
            ClusterQueueSummaryOptions cqOptions = (ClusterQueueSummaryOptions)options;
        } else {
            QueueInstanceSummaryOptions ciOptions = (QueueInstanceSummaryOptions)options;
            
            if (explain != null) {
                ciOptions.setExplain(explain.charValue());
            }
            if (fullOutput) {
                ciOptions.setShowFullOutput(true);
            }
            if (resourceAttributeFilter != null) {
                ciOptions.setResourceAttributeFilter(resourceAttributeFilter);
            }
            ciOptions.setShowArrayJobs(groupOptions.indexOf("d") >= 0);
            ciOptions.setShowPEJobs(groupOptions.indexOf("t") >= 0);
            ciOptions.setShowEmptyQueues(showEmptyQueues);
            if (peFilter != null) {
                ciOptions.setPeFilter(peFilter);
            }
            if (jobStateFilter != null) {
                ciOptions.setJobStateFilter(jobStateFilter);
            }
            ciOptions.setShowRequestedResourcesForJobs(showRequestJobResources);
            ciOptions.setShowExtendedSubTaskInfo(showTaskInfo);
            if (jobUserFilter != null) {
                ciOptions.setJobUserFilter(jobUserFilter);
            }
            ciOptions.setShowJobUrgency(showUrgency);
            ciOptions.setShowJobPriorities(showJobPriority);
        }
        return options;
    }
}
