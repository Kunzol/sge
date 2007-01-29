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

#include <string.h>
#include <fnmatch.h>

#include "sge.h"

#include "sgeobj/sge_resource_quota.h"
#include "sgeobj/sge_strL.h"
#include "sgeobj/msg_sgeobjlib.h"
#include "sgeobj/sge_answer.h"
#include "sgeobj/sge_object.h"
#include "sgeobj/sge_centry.h"
#include "msg_common.h"
#include "uti/sge_log.h"
#include "uti/sge_parse_num_par.h"
#include "rmon/sgermon.h"
#include "sgeobj/sge_job.h"
#include "sgeobj/sge_ja_task.h"
#include "sgeobj/sge_pe.h"
#include "sched/sge_resource_utilizationL.h"
#include "sgeobj/sge_hgroup.h"
#include "sgeobj/sge_userset.h"
#include "sgeobj/sge_hrefL.h"
#include "sgeobj/sge_host.h"
#include "uti/sge_string.h"

static bool rqs_match_user_host_scope(lList *scope, int filter_type, const char *value, lList *master_userset_list, lList *master_hgroup_list, const char *group);
static bool rqs_filter_match(lListElem *filter, int filter_type, const char *value, lList *master_userset_list, lList *master_hgroup_list, const char *group);

/****** sge_resource_quota/rqs_parse_filter_from_string() *************************
*  NAME
*     rqs_parse_filter_from_string() -- parse a RQRF Object from string
*
*  SYNOPSIS
*     bool rqs_parse_filter_from_string(lListElem **filter, const char* buffer, 
*     lList **alp) 
*
*  FUNCTION
*     Converts a spooled RQRF Object to a CULL Element
*
*  INPUTS
*     lListElem **filter - resulting RQRF object
*     const char* buffer - string to be converted
*     lList **alp        - answer_list
*
*  RESULT
*     bool - true on success
*            false on error
*
*  NOTES
*     MT-NOTE: rqs_parse_filter_from_string() is MT safe 
*
*******************************************************************************/
bool rqs_parse_filter_from_string(lListElem **filter, const char* buffer, lList **alp) {
   lListElem *tmp_filter = NULL;
   lListElem *scope = NULL;
   lList *lp = NULL;
   lList *scope_list = NULL;
   lList *xscope_list = NULL;
   char delims[] = "\t \v\r,{}"; 

   DENTER(TOP_LAYER, "rqs_parse_filter_from_string");

   if (buffer == NULL) {
     DRETURN(false);
   }

   tmp_filter = lCreateElem(RQRF_Type);

   if ( buffer[0] == '{' ) {
      /* We have a expanded list */
      lSetBool(tmp_filter, RQRF_expand, true);
      if (buffer[strlen(buffer)-1] != '}') {
         ERROR((SGE_EVENT, MSG_RESOURCEQUOTA_NOVALIDEXPANDEDLIST));
         answer_list_add(alp, SGE_EVENT, STATUS_ESYNTAX, ANSWER_QUALITY_ERROR);
         DRETURN(false);
      }
   } else {
      lSetBool(tmp_filter, RQRF_expand, false);
   }

   lString2List(buffer, &lp, ST_Type, ST_name, delims); 

   for_each(scope, lp) {
      const char *name = lGetString(scope, ST_name);
      if ( name[0] == '!' ) {
         lAddElemStr(&xscope_list, ST_name, name+1, ST_Type);
      } else {
         lAddElemStr(&scope_list, ST_name, name, ST_Type);
      }
   }

   lFreeList(&lp);

   lSetList(tmp_filter, RQRF_scope, scope_list);
   lSetList(tmp_filter, RQRF_xscope, xscope_list);

   *filter = tmp_filter;
   
   DRETURN(true);
}

/****** sge_resource_quota/rqs_append_filter_to_dstring() *************************
*  NAME
*    rqs_append_filter_to_dstringRQRF_object_append_to_dstring() -- RQRF Element to string
*
*  SYNOPSIS
*     bool rqs_append_filter_to_dstring(lListElem *filter, dstring *buffer, 
*     lList **alp) 
*
*  FUNCTION
*     Converts a RQRF element to string for spooling 
*
*  INPUTS
*     lListElem *filter - Element to be converted
*     dstring *buffer   - buffer for the element string
*     lList **alp       - answer_list
*
*  RESULT
*     bool - true on success
*            false on error
*
*  NOTES
*     MT-NOTE: rqs_append_filter_to_dstring() is MT safe 
*
*******************************************************************************/
bool rqs_append_filter_to_dstring(const lListElem *filter, dstring *buffer, lList **alp){
   lList *tlp = NULL;
   lListElem *scope = NULL;
   bool first = true;
   bool expand = false;
   bool ret = false;

   if (filter == NULL) {
      return ret;
   }

   expand = lGetBool(filter, RQRF_expand) ? true : false;

   if (expand) {
      sge_dstring_append(buffer, "{");
   }

   tlp = lGetList(filter, RQRF_scope);
   for_each(scope, tlp) {
      ret = true;
      if (!first) {
         sge_dstring_append(buffer, ",");
      } else {
         first = false;
      }
      sge_dstring_append(buffer, lGetString(scope, ST_name));
   }

   tlp = lGetList(filter, RQRF_xscope);
   for_each(scope, tlp) {
      ret = true;
      if (!first) {
         sge_dstring_append(buffer, ",");
      } else {
         first = false;
      }
      sge_dstring_append(buffer, "!");
      sge_dstring_append(buffer, lGetString(scope, ST_name));
   }

   if (expand) {
      sge_dstring_append(buffer, "}");
   }

   return ret; 
}

/****** sge_resource_quota/rqs_set_defaults() *******************************
*  NAME
*     rqs_set_defaults() -- set default values to given rqs
*
*  SYNOPSIS
*     lListElem* rqs_set_defaults(lListElem* rqs) 
*
*  FUNCTION
*     This function sets the default values to a resource quota set.
*     The default rule set is:
*     {
*       name = <must be already set>
*       enabled = true
*       limit to slots=0
*     }
*
*  INPUTS
*     lListElem* rqs - Already created object to be modified.
*
*  RESULT
*     lListElem* - modified Object
*
*  NOTES
*     MT-NOTE: rqs_set_defaults() is MT safe 
*******************************************************************************/
lListElem* rqs_set_defaults(lListElem* rqs)
{
   DENTER(TOP_LAYER, "rqs_set_defaults");

   if (rqs != NULL) {
      lList *limit_list = NULL;
      lList *rule_list = NULL;
      lListElem *rule = NULL;
      lListElem *limit = NULL;

      /* Free RQS_rule */
      rule_list = lGetList(rqs, RQS_rule);
      lFreeList(&rule_list);

      /* Create Rule List */
      rule_list = lCreateList("Rule_List", RQR_Type);
      rule = lCreateElem(RQR_Type);
      limit_list = lCreateList("Limit_List", RQRL_Type);
      limit = lCreateElem(RQRL_Type);
      lSetString(limit, RQRL_name, "slots");
      lSetString(limit, RQRL_value, "0");
      lAppendElem(limit_list, limit);
      lSetList(rule, RQR_limit, limit_list);
      lAppendElem(rule_list, rule);

      /* Set RQS_enabled */
      lSetBool(rqs, RQS_enabled, false);

      /* Set RQS_rule */
      lSetList(rqs, RQS_rule, rule_list);
   }
   DRETURN(rqs);
}

/****** sge_resource_quota/rqs_verify_attributes() **********************
*  NAME
*     rqs_verify_attributes() -- verify the attributes of a rqs Object 
*
*  SYNOPSIS
*     bool rqs_verify_attributes(lListElem *rqs, lList 
*     **answer_list, bool in_master) 
*
*  FUNCTION
*     This function verifies the attributes of a given rqs object. A valid rqs
*     object has a name and at least one rule set. After verification it sets the
*     double limit value.
*     Addition checks are done if in_master is true.
*
*  INPUTS
*     lListElem *rqs     - Object that should be verified
*     lList **answer_list - answer list in case of errors
*     bool in_master      - flag if called by qmaster or by qconf
*
*  RESULT
*     bool - true on success
*            false on error
*
*  NOTES
*     MT-NOTE: rqs_verify_attributes() is MT safe 
*******************************************************************************/
bool rqs_verify_attributes(lListElem *rqs, lList **answer_list, bool in_master)
{
   bool ret = true;
   lList *rules = NULL;

   DENTER(TOP_LAYER, "rqs_verify_attributes");

   /* every rule set needs a RQS_name */
   if (lGetString(rqs, RQS_name) == NULL) {
      answer_list_add_sprintf(answer_list, STATUS_ESYNTAX, ANSWER_QUALITY_ERROR, MSG_RESOURCEQUOTA_NONAME);
      ret = false;
   }

   /* every rule set needs at least one rule */
   rules = lGetList(rqs, RQS_rule);
   if (ret && (rules == NULL || lGetNumberOfElem(rules) < 1)) {
      answer_list_add_sprintf(answer_list, STATUS_ESYNTAX, ANSWER_QUALITY_ERROR, MSG_RESOURCEQUOTA_NORULES);
      ret = false;
   }
  
   if (ret && in_master) {
      lList *master_centry_list = (*centry_list_get_master_list());

      lListElem *rule = NULL;
      for_each(rule, rules) {
         bool host_expand = false;
         bool queue_expand = false;
         lListElem *limit = NULL;
         lListElem *filter = NULL;
         lList *limit_list = lGetList(rule, RQR_limit);

         /* set rule level. Needed by schedd */

         if ((filter = lGetObject(rule, RQR_filter_hosts))) {
            lListElem *host = NULL;
            host_expand = lGetBool(filter, RQRF_expand) ? true : false;

            for_each(host, lGetList(filter, RQRF_xscope)) {
               sge_resolve_host(host, ST_name);
            }
            for_each(host, lGetList(filter, RQRF_scope)) {
               sge_resolve_host(host, ST_name);
            }
            
         }
         if ((filter = lGetObject(rule, RQR_filter_queues))) {
            queue_expand = lGetBool(filter, RQRF_expand) ? true : false;
         }

         if (host_expand == false && queue_expand == false) {
            lSetUlong(rule, RQR_level, RQR_GLOBAL);
         } else if (host_expand == true && queue_expand == false) {
            /* per host */
            lSetUlong(rule, RQR_level, RQR_HOST);
         } else if (host_expand == false && queue_expand == true) {
            /* per queue */
            lSetUlong(rule, RQR_level, RQR_CQUEUE);
         } else {
            lSetUlong(rule, RQR_level, RQR_QUEUEI);
         }

         for_each(limit, limit_list) {
            const char *name = lGetString(limit, RQRL_name);
            const char *strval = lGetString(limit, RQRL_value);
            lListElem *centry = centry_list_locate(master_centry_list, name);

            if (centry == NULL) {
               sprintf(SGE_EVENT, MSG_NOTEXISTING_ATTRIBUTE_SS, SGE_RQS_NAME, name);
               answer_list_add(answer_list, SGE_EVENT, STATUS_ESYNTAX, ANSWER_QUALITY_ERROR);
               ret = false;
               break;
            }

            lSetString(limit, RQRL_name, lGetString(centry, CE_name));

            if (strchr(strval, '$') != NULL) {
               if (lGetUlong(rule, RQR_level) == RQR_HOST || lGetUlong(rule, RQR_level) == RQR_QUEUEI) {
                  /* the value is a dynamical limit */
                  if (!validate_load_formula(lGetString(limit, RQRL_value), answer_list, 
                                            master_centry_list, SGE_ATTR_DYNAMICAL_LIMIT)) {
                     ret = false;
                     break;
                  }

                  lSetUlong(limit, RQRL_type, lGetUlong(centry, CE_valtype));
                  lSetBool(limit, RQRL_dynamic, true);
               } else {
                  answer_list_add_sprintf(answer_list, STATUS_ESYNTAX, ANSWER_QUALITY_ERROR, MSG_RESOURCEQUOTA_DYNAMICLIMITNOTSUPPORTED);
                  ret = false;
                  break;
               }  
               /* The evaluation of the value needs to be done at scheduling time. Per default it's zero */
            } else {
               lListElem *tmp_ce = lCopyElem(centry);
               /* fix limit, fill up missing attributes */
               lSetBool(limit, RQRL_dynamic, false);
  
               lSetString(tmp_ce, CE_stringval, strval);
               if (centry_fill_and_check(tmp_ce, answer_list, false, false)) {
                  ret = false;
                  lFreeElem(&tmp_ce);
                  break;
               }
              
               lSetString(limit, RQRL_value, lGetString(tmp_ce, CE_stringval));
               lSetDouble(limit, RQRL_dvalue, lGetDouble(tmp_ce, CE_doubleval));
               lSetUlong(limit, RQRL_type, lGetUlong(tmp_ce, CE_valtype));
               lFreeElem(&tmp_ce);
            }
         }
         if (ret == false) {
            break;
         }
      }
   }

   DRETURN(ret);
}

/****** sge_resource_quota/rqs_list_verify_attributes() *********************
*  NAME
*     rqs_list_verify_attributes() -- verifies the attributes of a rqs list
*
*  SYNOPSIS
*     bool rqs_list_verify_attributes(lList *rqs_list, lList 
*     **answer_list, bool in_master) 
*
*  FUNCTION
*     This function iterates over a rqs list and checks for every rqs the attributes
*
*  INPUTS
*     lList *rqs_list    - List that should be verified
*     lList **answer_list - answer list 
*     bool in_master      - flag if called by qmaster or qconf
*
*  RESULT
*     bool - true on success
*            false on error
*  NOTES
*     MT-NOTE: rqs_list_verify_attributes() is MT safe 
*
*  SEE ALSO
*     sge_resource_quota/rqs_verify_attributes()
*******************************************************************************/
bool rqs_list_verify_attributes(lList *rqs_list, lList **answer_list, bool in_master)
{
   bool ret = true;
   
   DENTER(TOP_LAYER, "rqs_list_verify_attributes");
   if (rqs_list != NULL) {
      lListElem *rqs = NULL;

      for_each(rqs, rqs_list) {
         ret = rqs_verify_attributes(rqs, answer_list, in_master);
         if (!ret) {
            break;
         }
      }
   }
   DRETURN(ret);
}

/****** sge_resource_quota/rqs_list_locate() ****************************
*  NAME
*     rqs_list_locate() -- locate a specific resource quota set by name
*
*  SYNOPSIS
*     lListElem* rqs_list_locate(lList *lp, const char *name) 
*
*  FUNCTION
*     This function searches the rule set list for a specific resource quota
*     set. The search criteria is the name of the resource quota set.
*
*  INPUTS
*     lList *lp        - rule set list to be searched in
*     const char *name - rule set name of interest
*
*  RESULT
*     lListElem* - if found the reference to the resource quota set, else NULL
*
*  NOTES
*     MT-NOTE: rqs_list_locate() is MT safe 
*******************************************************************************/
lListElem *rqs_list_locate(lList *lp, const char *name)
{
   lListElem *ep = NULL;

   DENTER(TOP_LAYER, "rqs_list_locate");

   ep = lGetElemStr(lp, RQS_name, name);

   DRETURN(ep);
}

/****** sge_resource_quota/rqs_rule_locate() *************************************
*  NAME
*     rqs_rule_locate() -- locate a specific rule by name 
*
*  SYNOPSIS
*     lListElem* rqs_rule_locate(lList *lp, const char *name) 
*
*  FUNCTION
*     This function searches a rule list for a specific rule. The search criteria
*     is the name or the index of the rule.
*     The index is used if the name was successfully converted to an integer by
*     the atoi() function. If atoi() was not able to convert the name the rule is
*     searched by a sting compare.
*
*  INPUTS
*     lList *lp        - list to be searched in
*     const char *name - rule name of interest
*
*  RESULT
*     lListElem* - reference to found rule
*                  NULL if rule was not found
*
*  NOTES
*     MT-NOTE: rqs_rule_locate() is MT safe 
*******************************************************************************/
lListElem* rqs_rule_locate(lList *lp, const char *name)
{
   lListElem *ep = NULL;
   int get_pos = 0;
   int act_pos = 1;

   DENTER(TOP_LAYER, "rqs_rule_locate");

   if (name == NULL) {
      DRETURN(NULL);
   }

   get_pos = atoi(name);

   for_each(ep, lp) {
      const char *rule_name = lGetString(ep, RQR_name);
      if (get_pos != -1 && act_pos == get_pos) {
         break;
      } else if (rule_name != NULL && !strcasecmp(name, lGetString(ep, RQR_name))) {
         break;
      }
      act_pos++;
   }

   DRETURN(ep);
}

/****** sge_resource_quota/rqs_xattr_pre_gdi() *************************************
*  NAME
*     rqs_xattr_pre_gdi() -- qconf xattr list preformat
*
*  SYNOPSIS
*     bool rqs_xattr_pre_gdi(lList *this_list, lList **answer_list) 
*
*  FUNCTION
*     This function preformates the given list created by xattr. The xattr switch
*     allows to address single rules by using the special rule set name "rule_set_name/rule_name".
*     The rule name can be the name for named rules or the index of the rule.
*     This function splits such a name into the single rule set name and set the correct
*     rule name.
*
*  INPUTS
*     lList *this_list    - list to be modified
*     lList **answer_list - answer list
*
*  RESULT
*     bool - true on success
*            false on error
*
*  NOTES
*     MT-NOTE: rqs_xattr_pre_gdi() is MT safe 
*******************************************************************************/
bool rqs_xattr_pre_gdi(lList *this_list, lList **answer_list) 
{
   bool ret = true;
   char delim[] = "/";

   DENTER(TOP_LAYER, "rqs_xattr_pre_gdi");
   if (this_list != NULL) {
      lListElem *rqs = NULL;

      for_each(rqs, this_list) {
         lList *lp = NULL;
         const char *name = lGetString(rqs, RQS_name);
         
         lString2List(name, &lp, ST_Type, ST_name, delim);
         if (lGetNumberOfElem(lp) == 2) {
            lListElem *ep = NULL;
            lListElem *rule = NULL;
            lList *rules = lGetList(rqs, RQS_rule);

            ep = lFirst(lp);
            lSetString(rqs, RQS_name, lGetString(ep, ST_name));
            ep = lNext(ep);
            for_each(rule, rules) {
               lSetString(rule, RQR_name, lGetString(ep, ST_name));
            }
         }
         lFreeList(&lp);
      }
   }
   DRETURN(ret);
}

/****** sge_resource_quota/rqs_get_rue_string() *****************************
*  NAME
*     rqs_get_rue_string() -- creates a rue name
*
*  SYNOPSIS
*     bool rqs_get_rue_string(dstring *name, lListElem *rule, const char 
*     *user, const char *project, const char *host, const char *queue, const 
*     char* pe) 
*
*  FUNCTION
*     Creates the rue name used for debiting a specific job request. The name 
*     consists of the five touples devided by a /. The order is user, project,
*     pe, queue, host.
*     Filters that count for a sum
*     of hosts are saved as a empty string because they don't need to be matched.
*
*     For example the rule
*       limit users `*` queues `all.q,my.q` to slots=10
*     may result in the rue name
*       user1///all.q//
*
*  INPUTS
*     dstring *name       - out: rue_name
*     lListElem *rule     - resource quota rule (RQR_Type)
*     const char *user    - user name
*     const char *project - project name
*     const char *host    - host name
*     const char *queue   - queue name
*     const char* pe      - pe name
*
*  RESULT
*     bool - always true
*
*  NOTES
*     MT-NOTE: rqs_get_rue_string() is MT safe 
*
*******************************************************************************/
bool
rqs_get_rue_string(dstring *name, const lListElem *rule, const char *user, 
                              const char *project, const char *host, const char *queue,
                              const char* pe)
{
   lListElem *filter = NULL;

   DENTER(TOP_LAYER, "rqs_get_rue_string");

   if (rule == NULL) {
      DRETURN(false);
   }

   sge_dstring_clear(name);

   if ((filter = lGetObject(rule, RQR_filter_users)) != NULL) {
      if (filter != NULL && user != NULL && lGetBool(filter, RQRF_expand) == true) {
         sge_dstring_append(name, user); 
      }
   }
   sge_dstring_append(name, "/");

   if ((filter = lGetObject(rule, RQR_filter_projects)) != NULL) {
      if (filter != NULL && project != NULL && lGetBool(filter, RQRF_expand) == true) {
         sge_dstring_append(name, project); 
      }
   }
   sge_dstring_append(name, "/");

   if ((filter = lGetObject(rule, RQR_filter_pes)) != NULL) {
      if (filter != NULL && pe != NULL && lGetBool(filter, RQRF_expand) == true) {
         sge_dstring_append(name, pe); 
      }
   }
   sge_dstring_append(name, "/");

   if ((filter = lGetObject(rule, RQR_filter_queues)) != NULL) {
      if (filter != NULL && queue != NULL && lGetBool(filter, RQRF_expand) == true) {
         sge_dstring_append(name, queue); 
      }
   }
   sge_dstring_append(name, "/");

   if ((filter = lGetObject(rule, RQR_filter_hosts)) != NULL) {
      if (filter != NULL && host != NULL && lGetBool(filter, RQRF_expand) == true) {
         sge_dstring_append(name, host); 
      }
   }
   sge_dstring_append(name, "/");

   DPRINTF(("rue_name: %s\n", sge_dstring_get_string(name)));

   DRETURN(true);
}

/****** sge_resource_quota/rqs_debit_consumable() *********************************
*  NAME
*     rqs_debit_consumable() -- debit slots in all relevant rule sets
*
*  SYNOPSIS
*     int rqs_debit_consumable(lListElem *rqs, lListElem *job, lListElem 
*     *granted, lListElem *pe, lList *centry_list, int slots) 
*
*  FUNCTION
*     iterater over all rules in the given rule set and debit the amount of slots
*     in the relevant rule
*
*  INPUTS
*     lListElem *rqs     - resource quota set (RQS_Type)
*     lListElem *job     - job request (JB_Type)
*     lListElem *granted - granted destination identifier (JG_Type)
*     lListElem *pe      - granted pe (PE_Type)
*     lList *centry_list - consumable resouces list (CE_Type)
*     int slots          - slot amount
*
*  RESULT
*     int - amount of modified rule
*
*  NOTES
*     MT-NOTE: rqs_debit_consumable() is not MT safe 
*
*******************************************************************************/
int
rqs_debit_consumable(lListElem *rqs, lListElem *job, lListElem *granted, const char *pename, lList *centry_list, 
                      lList *acl_list, lList *hgrp_list, int slots)
{
   lListElem *rule = NULL;
   int mods = 0;
   const char* hostname = lGetHost(granted, JG_qhostname);
   const char* username = lGetString(job, JB_owner);
   const char* groupname = lGetString(job, JB_group);
   char *qname = NULL;
   const char *queue_instance = lGetString(granted, JG_qname);
   const char* project = lGetString(job, JB_project);
   char *at_sign = NULL; 

   DENTER(TOP_LAYER, "rqs_debit_consumable");

   if (!lGetBool(rqs, RQS_enabled)) {
      DRETURN(0);
   }

   /* remove the host name part of the queue instance name */
   at_sign = strchr(queue_instance, '@');
   if (at_sign != NULL) {
      int size = at_sign - queue_instance;
      qname = malloc(sizeof(char) * (size + 1));
      qname = strncpy(qname, queue_instance, size);
      qname[size] = '\0';
   } else {
      qname = strdup(queue_instance);
   }

   rule = rqs_get_matching_rule(rqs, username, groupname, project, pename, hostname, qname, acl_list, hgrp_list, NULL);

   if (rule != NULL) {
      /* debit usage */
      dstring rue_name = DSTRING_INIT;

      rqs_get_rue_string(&rue_name, rule, username, project,
                                hostname, qname, pename);

      mods = rqs_debit_rule_usage(job, rule, rue_name, slots, centry_list, lGetString(rqs, RQS_name));

      sge_dstring_free(&rue_name);
   }
   
   FREE(qname);

   DRETURN(mods); 
}

/****** sge_resource_quota/rqs_get_matching_rule() ********************************
*  NAME
*     rqs_get_matching_rule() -- found relevant rule for job request
*
*  SYNOPSIS
*     lListElem* rqs_get_matching_rule(lListElem *rqs, const char *user, 
*     const char *project, const char* pe, const char *host, const char *queue, 
*     lList *userset_list, lList* hgroup_list, dstring *rule_name) 
*
*  FUNCTION
*     This function searches in a resource quota set the relevant rule.
*
*  INPUTS
*     lListElem *rqs     - rule set (RQS_Type)
*     const char *user    - user name
*     const char *project - project name
*     const char* pe      - pe name
*     const char *host    - host name
*     const char *queue   - queue name
*     lList *userset_list - master user set list (US_Type)
*     lList* hgroup_list  - master host group list (HG_Type);
*     dstring *rule_name  - out: name or matching rule
*
*  RESULT
*     lListElem* - pointer to matching rule
*
*  NOTES
*     MT-NOTE: rqs_get_matching_rule() is MT safe 
*
*******************************************************************************/
lListElem *
rqs_get_matching_rule(const lListElem *rqs, const char *user, const char *group, const char *project,
                                  const char* pe, const char *host, const char *queue,
                                  lList *userset_list, lList* hgroup_list, dstring *rule_name)
{
   lListElem *rule = NULL;
   lList *rule_list = lGetList(rqs, RQS_rule);
   int i = 0;

   DENTER(TOP_LAYER, "rqs_get_matching_rule");

   for_each (rule, rule_list) {
      i++;

      if (!rqs_is_matching_rule(rule, user, group, project, pe, host, queue, userset_list, hgroup_list)) {
         continue;
      }
      if (lGetString(rule, RQR_name)) {
         DPRINTF(("Using resource quota %s\n", lGetString(rule, RQR_name)));
         sge_dstring_sprintf(rule_name, "%s/%s", lGetString(rqs, RQS_name), lGetString(rule, RQR_name));
      } else {
         DPRINTF(("Using resource quota %d\n", i));
         sge_dstring_sprintf(rule_name, "%s/%d", lGetString(rqs, RQS_name), i);
      }
      /* if all filter object matches this is our rule */
      break;
   }
   DRETURN(rule);
}

/****** sge_resource_quota/rqs_debit_rule_usage() *********************************
*  NAME
*     rqs_debit_rule_usage() -- debit usage in a resource quota rule 
*
*  SYNOPSIS
*     int rqs_debit_rule_usage(lListElem *job, lListElem *rule, dstring 
*     rue_name, int slots, lList *centry_list, const char *obj_name) 
*
*  FUNCTION
*     Debit an amount of slots in all limits of one resource quota rule
*
*  INPUTS
*     lListElem *job       - job request (JG_Type)
*     lListElem *rule      - resource quota rule (RQR_Type)
*     dstring rue_name     - rue name that counts
*     int slots            - amount of slots to debit
*     lList *centry_list   - consumable resource list (CE_Type)
*     const char *obj_name - name of the limit
*
*  RESULT
*     int - amount of debited limits
*
*  NOTES
*     MT-NOTE: rqs_debit_rule_usage() is MT safe 
*******************************************************************************/
int
rqs_debit_rule_usage(lListElem *job, lListElem *rule, dstring rue_name, int slots, lList *centry_list, const char *obj_name) 
{
   lList *limit_list;
   lListElem *limit;
   const char *centry_name;
   int mods = 0;

   DENTER(TOP_LAYER, "rqs_debit_rule_usage");

   limit_list = lGetList(rule, RQR_limit);

   for_each(limit, limit_list) {
      lListElem *raw_centry;
      lListElem *rue_elem;
      double dval;

      centry_name = lGetString(limit, RQRL_name);
      
      if (!(raw_centry = centry_list_locate(centry_list, centry_name))) {
         /* ignoring not defined centry */
         continue;
      }

      if (!lGetBool(raw_centry, CE_consumable)) {
         continue;
      }

      rue_elem = lGetSubStr(limit, RUE_name, sge_dstring_get_string(&rue_name), RQRL_usage);
      if(rue_elem == NULL) {
         rue_elem = lAddSubStr(limit, RUE_name, sge_dstring_get_string(&rue_name), RQRL_usage, RUE_Type);
         /* RUE_utilized_now is implicitly set to zero */
      }

      if (job) {
         bool tmp_ret = job_get_contribution(job, NULL, centry_name, &dval, raw_centry);
         if (tmp_ret && dval != 0.0) {
            DPRINTF(("debiting %f of %s on rqs %s for %s %d slots\n", dval, centry_name,
                     obj_name, sge_dstring_get_string(&rue_name), slots));
            lAddDouble(rue_elem, RUE_utilized_now, slots * dval);
            mods++;
         }
         if ((lGetDouble(rue_elem, RUE_utilized_now) == 0) && !lGetList(rue_elem, RUE_utilized)) {
            rue_elem = lDechainElem(lGetList(limit, RQRL_usage), rue_elem);
            lFreeElem(&rue_elem);
         }
      }
   }

   DRETURN(mods);
}

/****** sge_resource_quota/rqs_match_user_host_scope() ****************************
*  NAME
*     rqs_match_user_host_scope() -- match user or host scope
*
*  SYNOPSIS
*     static bool rqs_match_user_host_scope(lList *scope, int filter_type, 
*     const char *value, lList *master_userset_list, lList *master_hgroup_list) 
*
*  FUNCTION
*     This function verifies a user or host scope. The function allows for every
*     scope entry and for the value a wildcard definition. Hostgroups and Usergroups
*     are resolved and matched against the value
*     
*
*  INPUTS
*     lList *scope               - Scope to match (ST_Type)
*     int filter_type            - filter type (FILTER_USERS or FILTER_HOSTS)
*     const char *value          - value to match
*     lList *master_userset_list - master userset list (US_Type)
*     lList *master_hgroup_list  - master hostgroup list (HG_Type)
*
*  RESULT
*     static bool - true, if value was found in scope 
*                   false, if value was not found in scope
*
*  NOTES
*     MT-NOTE: rqs_match_user_host_scope() is MT safe 
*
*  SEE ALSO
*     sge_resource_quota/rqs_match_user_host_scope()
*******************************************************************************/
static bool rqs_match_user_host_scope(lList *scope, int filter_type, const char *value, lList *master_userset_list, lList *master_hgroup_list, const char *group) {

   bool found = false;
   lListElem *ep;

   DENTER(TOP_LAYER, "rqs_match_user_host_scope");

   if (!sge_is_pattern(value)) {
      if (lGetElemStr(scope, ST_name, value) != NULL) {
         found = true;
      } else {
         for_each(ep, scope) {
            lListElem *group_ep;
            const char *cp = lGetString(ep, ST_name);
            const char *group_name = NULL;
            const char *query = NULL;

            if (fnmatch(cp, value, 0) == 0) {
               found = true;
               break;
            }

            if (!is_hgroup_name(value) && is_hgroup_name(cp)) {
               group_name = cp;
               query = value;
            } else if (is_hgroup_name(value) && !is_hgroup_name(cp)) {
               group_name = value;
               query = cp;
            }

            if (group_name != NULL && query != NULL) {
               DPRINTF(("group_name=%s, query=%s\n", group_name, query));
               if (filter_type == FILTER_USERS) {
                  /* the userset name does not contain the preattached \@ sign */
                  group_name++; 
                  if (!sge_is_pattern(group_name)) {
                     if ((group_ep = userset_list_locate(master_userset_list, group_name)) != NULL) {
                        if (sge_contained_in_access_list(query, group, group_ep, NULL) == 1) {
                           found = true;
                           break;
                        }
                     }
                  } else {
                     for_each(group_ep, master_userset_list) {
                        if (fnmatch(group_name, lGetString(group_ep, US_name), 0) == 0) {
                           if (sge_contained_in_access_list(query, group, group_ep, NULL) == 1) {
                              found = true;
                              break;
                           }
                        }
                     }
                     if (found == true) {
                        break;
                     }
                  }
               } else { /* FILTER_HOSTS */
                  lListElem *hgroup = NULL;
                  lList *host_list = NULL;
                  if (!sge_is_pattern(group_name)) {
                     if ((hgroup = hgroup_list_locate(master_hgroup_list, group_name))) { 
                        hgroup_find_all_references(hgroup, NULL, master_hgroup_list, &host_list, NULL);
                        if (host_list != NULL && lGetElemHost(host_list, HR_name, query) != NULL) {
                           lFreeList(&host_list);
                           found = true;
                           break;
                        } else if (sge_is_pattern(query)) {
                           lListElem *host_ep;
                           for_each(host_ep, host_list) {
                              if (fnmatch(query, lGetHost(host_ep, HR_name), 0) == 0) {
                                 lFreeList(&host_list);
                                 found = true;
                                 break;
                              }
                           }
                           if (found == true) {
                              break;
                           }
                        }
                        lFreeList(&host_list);
                     }
                  } else {
                     for_each(group_ep, master_hgroup_list) {
                        if (fnmatch(group_name, lGetHost(group_ep, HGRP_name), 0) == 0) {
                           hgroup_find_all_references(group_ep, NULL, master_hgroup_list, &host_list, NULL);
                           if (host_list != NULL && lGetElemHost(host_list, HR_name, query) != NULL) {
                              lFreeList(&host_list);
                              found = true;
                              break;
                           } else if (sge_is_pattern(query)) {
                              lListElem *host_ep;
                              for_each(host_ep, host_list) {
                                 if (fnmatch(query, lGetHost(host_ep, HR_name), 0) == 0) {
                                    lFreeList(&host_list);
                                    found = true;
                                    break;
                                 }
                              }
                              if (found == true) {
                                 break;
                              }
                           }
                           lFreeList(&host_list);
                        }
                     }
                  }
               }
            }
         }
      }
   } else {
      for_each(ep, scope) {
         const char *cp = lGetString(ep, ST_name);
         const char *group_name = NULL;
         const char *query = NULL;

         if (fnmatch(value, cp, 0) == 0) {
            found = true;
            break;
         }
         if (sge_is_pattern(cp) && (fnmatch(cp, value, 0) == 0)) {
            found = true;
            break;
         }
         if (!is_hgroup_name(value) && is_hgroup_name(cp)) {
            group_name = cp;
            query = value;
         } else if (is_hgroup_name(value) && !is_hgroup_name(cp)) {
            group_name = value;
            query = cp;
         }

         if (group_name != NULL && query != NULL) {
            lListElem *group_ep;
            DPRINTF(("group_name=%s, query=%s\n", group_name, query));
            if (filter_type == FILTER_USERS) {
               /* the userset name does not contain the preattached \@ sign */
               group_name++;
               for_each(group_ep, master_userset_list) {
                  if (fnmatch(group_name, lGetString(group_ep, US_name), 0) == 0) {
                     if (sge_contained_in_access_list(query, group, group_ep, NULL) == 1) {
                        found = true;
                        break;
                     }
                  }
               }
               if (found == true) {
                  break;
               }
            } else {
               lList *host_list = NULL;
               for_each(group_ep, master_hgroup_list) {
                  if (fnmatch(group_name, lGetHost(group_ep, HGRP_name), 0) == 0) {
                     lListElem *host_ep;
                     hgroup_find_all_references(group_ep, NULL, master_hgroup_list, &host_list, NULL);
                     for_each(host_ep, host_list) {
                        if (fnmatch(query, lGetHost(host_ep, HR_name), 0) == 0) {
                           found = true;
                           break;
                        }
                     }
                     lFreeList(&host_list);
                     if (found == true) {
                        break;
                     }
                  }
               }
               if (found == true) {
                  break;
               }
            }
         }
      }
   }
   DRETURN(found);
}

/****** sge_resource_quota/rqs_is_matching_rule() *********************************
*  NAME
*     rqs_is_matching_rule() -- matches a rule with the filter touples
*
*  SYNOPSIS
*     bool rqs_is_matching_rule(lListElem *rule, const char *user, const char 
*     *project, const char *pe, const char *host, const char *queue, lList 
*     *master_userset_list, lList *master_hgroup_list) 
*
*  FUNCTION
*     The function verifies for every filter touple if the request matches
*     the configured resource quota rule. If only one touple does not match
*     the whole rule will not match
*
*  INPUTS
*     lListElem *rule            - resource quota rule (RQR_Type)
*     const char *user           - user name
*     const char *project        - project name
*     const char *pe             - pe name
*     const char *host           - host name
*     const char *queue          - queue name
*     lList *master_userset_list - master user set list (US_Type)
*     lList *master_hgroup_list  - master hostgroup list (HG_Type)
*
*  RESULT
*     bool - true if the rule does match
*            false if the rule does not match
*
*  NOTES
*     MT-NOTE: rqs_is_matching_rule() is MT safe 
*
*******************************************************************************/
bool
rqs_is_matching_rule(lListElem *rule, const char *user, const char *group, const char *project, const char *pe, const char *host, const char *queue, lList *master_userset_list, lList *master_hgroup_list)
{
      DENTER(TOP_LAYER, "rqs_is_matching_rule");

      if (!rqs_filter_match(lGetObject(rule, RQR_filter_users), FILTER_USERS, user, master_userset_list, master_hgroup_list, group)) {
         DPRINTF(("user doesn't match\n"));
         DRETURN(false);
      }
      if (!rqs_filter_match(lGetObject(rule, RQR_filter_projects), FILTER_PROJECTS, project, master_userset_list, master_hgroup_list, NULL)) {
         DPRINTF(("project doesn't match\n"));
         DRETURN(false);
      }
      if (!rqs_filter_match(lGetObject(rule, RQR_filter_pes), FILTER_PES, pe, master_userset_list, master_hgroup_list, NULL)) {
         DPRINTF(("pe doesn't match\n"));
         DRETURN(false);
      }
      if (!rqs_filter_match(lGetObject(rule, RQR_filter_queues), FILTER_QUEUES, queue, master_userset_list, master_hgroup_list, NULL)) {
         DPRINTF(("queue doesn't match\n"));
         DRETURN(false);
      }
      if (!rqs_filter_match(lGetObject(rule, RQR_filter_hosts), FILTER_HOSTS, host, master_userset_list, master_hgroup_list, NULL)) {
         DPRINTF(("host doesn't match\n"));
         DRETURN(false);
      }

      DRETURN(true);
}


/****** sge_resource_quota/rqs_filter_match() *******************************
*  NAME
*     rqs_filter_match() -- compares value with configured filter
*
*  SYNOPSIS
*     bool rqs_filter_match(lListElem *filter, int filter_type, const 
*     char *value, lList *master_userset_list, lList *master_hgroup_list) 
*
*  FUNCTION
*     This function compares for the given filter if the value does match
*     the configured one. Wildcards are allowed for the filter as well as for
*     the value.
*
*  INPUTS
*     lListElem *filter          - filter element (RQRF_Type)
*     int filter_type            - filter type
*     const char *value          - value to match
*     lList *master_userset_list - master userset list (US_Type)
*     lList *master_hgroup_list  - master hostgroup list (HG_Type)
*
*  RESULT
*     bool - true if the value does match
*            false if the value does not match
*
*  NOTES
*     MT-NOTE: rqs_filter_match() is MT safe 
*
*******************************************************************************/
static bool 
rqs_filter_match(lListElem *filter, int filter_type, const char *value, lList *master_userset_list, lList *master_hgroup_list, const char *group) {
   bool ret = true;
   lListElem* ep; 

   DENTER(TOP_LAYER, "rqs_filter_match");

   if (filter != NULL) {
      lList* scope = lGetList(filter, RQRF_scope);
      lList* xscope = lGetList(filter, RQRF_xscope);

      switch (filter_type) {
         case FILTER_USERS:
         case FILTER_HOSTS:
         {  
            DPRINTF(("matching users or hosts with %s\n", value));
            /* inverse logic because of xscope */
            ret = rqs_match_user_host_scope(xscope, filter_type, value, master_userset_list, master_hgroup_list, group) ? false: true;
            if (ret == true) { 
               bool found = false;
               found = rqs_match_user_host_scope(scope, filter_type, value, master_userset_list, master_hgroup_list, group);
               if (scope != NULL && found == false) {
                  ret = false;
               }
            }
            break;
         }
         case FILTER_PROJECTS:
         case FILTER_PES:
         case FILTER_QUEUES:
            DPRINTF(("matching projects, pes or queues with %s\n", value? value: "NULL"));
            if (lGetElemStr(xscope, ST_name, value) != NULL) {
               ret = false;
            } else {
               for_each(ep, xscope) {
                  const char *cp = lGetString(ep, ST_name);
                  if (value == NULL || (strcmp(value, "*") == 0)) {
                     break;
                  }
                  DPRINTF(("xscope: strcmp(%s,%s)\n", cp, value));
                  if ((strcmp(cp, "*") == 0) || (fnmatch(cp, value, 0) == 0) || (fnmatch(value,cp, 0) == 0)) {
                     DPRINTF(("match\n"));
                     ret = false;
                     break;
                  }
                  DPRINTF(("no match\n"));
               }
            }
            if (ret != false) { 
               bool found = false;
               if (lGetElemStr(scope, ST_name, value) != NULL) {
                  found = true;
               } else {
                  for_each(ep, scope) {
                     const char *cp = lGetString(ep, ST_name);

                     if (value == NULL) {
                        break;
                     }
                     DPRINTF(("scope: strcmp(%s,%s)\n", cp, value));
                     if ((strcmp(cp, "*") == 0) || (fnmatch(cp, value, 0) == 0) || (fnmatch(value,cp, 0) == 0)) {
                        found = true;
                        break;
                     }
                  }
               }
               if (scope != NULL && found == false) {
                  ret = false;
               }
            }
            break;
      }
   }

   DRETURN(ret);
}

/****** sge_resource_quota/sge_user_is_referenced_in_rqs() ************************
*  NAME
*     sge_user_is_referenced_in_rqs() -- search for user reference in rqs 
*
*  SYNOPSIS
*     bool sge_user_is_referenced_in_rqs(const lList *rqs, const char *user, 
*     lList *acl_list) 
*
*  FUNCTION
*     Search for a user reference in the resource quota sets
*
*  INPUTS
*     const lList *rqs - resource quota set list
*     const char *user  - user to search
*     const char *group - user's group
*     lList *acl_list   - acl list for user resolving
*
*  RESULT
*     bool - true if user was found
*            false if user was not found
*
*  NOTES
*     MT-NOTE: sge_user_is_referenced_in_rqs() is MT safe 
*
*******************************************************************************/
bool sge_user_is_referenced_in_rqs(const lList *rqs, const char *user, const char *group, lList *acl_list)
{
   bool ret = false;
   lListElem *ep;

   for_each(ep, rqs) {
      lList *rule_list = lGetList(ep, RQS_rule);
      lListElem *rule;
      for_each(rule, rule_list) {
         if (rqs_filter_match(lGetObject(rule, RQR_filter_users), FILTER_USERS, user, acl_list, NULL, group)) {
            ret = true;
            break;
         }
      }
      if (ret == true) {
         break;
      }
   }
   return ret;
}

/****** sge_resource_quota/sge_centry_referenced_in_rqs() *************************
*  NAME
*     sge_centry_referenced_in_rqs() -- search for a centry reference in
*                                        a resource quota set
*
*  SYNOPSIS
*     bool sge_centry_referenced_in_rqs(const lListElem *rqs, const lListElem 
*     *centry) 
*
*  FUNCTION
*     This function search a centry reference in a resource quota set
*
*  INPUTS
*     const lListElem *rqs   - resource quota set
*     const lListElem *centry - complex entry
*
*  RESULT
*     bool - true if found
*            false if not found
*
*  NOTES
*     MT-NOTE: sge_centry_referenced_in_rqs() is MT safe 
*
*******************************************************************************/
bool sge_centry_referenced_in_rqs(const lListElem *rqs, const lListElem *centry)
{
   bool ret = false;
   const char *centry_name = lGetString(centry, CE_name);
   lListElem *rule;

   DENTER(TOP_LAYER, "sge_centry_referenced_in_rqs");

   for_each(rule, lGetList(rqs, RQS_rule)) {
      lListElem *limit;
      for_each(limit, lGetList(rule, RQR_limit)) {
         const char *limit_name = lGetString(limit, RQRL_value);
         DPRINTF(("limit name %s\n", limit_name));
         if (strchr(limit_name, '$') != NULL) {
            /* dynamical limit */
            if (load_formula_is_centry_referenced(limit_name, centry)) {
               ret = true;
               break;
            }
         } else {
            /* static limit */
            if (strcmp(limit_name, centry_name) == 0) {
               ret = true;
               break;
            }
         }
      }
      if (ret) {
         break;
      }
   }

   DRETURN(ret);
}
