#ifndef __SGEEE_H
#define __SGEEE_H
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

#include "sge_boundaries.h"
#include "cull.h"
#include "sge_schedd.h"
#include "scheduler.h"


#define SGE_USAGE_INTERVAL 60

int sgeee_scheduler( sge_Sdescr_t *lists,
                    lList *running_jobs,
                    lList *finished_jobs,
                    lList *pending_jobs,
                    lList **orderlist,
                    bool has_queues,
                    bool has_pending_jobs );
void sgeee_resort_pending_jobs(lList **job_list, lList *order_list); 
 
int calculate_host_tickets( lList **running, lList **hosts );
int  sort_host_list_by_share_load ( lList *host_list,       /* EH_Type */
                                    lList *complex_list );  /* CX_Type */

void sge_clear_job( lListElem *job, bool is_clear_all);

lList *sge_build_sgeee_orders( sge_Sdescr_t *lists,
                      lList *running_jobs,
                      lList *queued_jobs,
                      lList *finished_jobs,
                      lList *order_list,
                      bool update_usage_and_configuration,
                      int seqno,
                      bool update_execd);

#endif /*  __SGEEE_H */
