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

#include "sge_unistd.h"
#include "sge_all_listsL.h"
#include "usage.h"
#include "parse_qconf.h"
#include "sge_gdi.h"
#include "setup.h"
#include "sig_handlers.h"
#include "commlib.h"
#include "sge_prog.h"
#include "sgermon.h"
#include "sge_log.h"
#include "msg_clients_common.h"
#include "msg_common.h"
#include "sge_answer.h"
#include "sge_mt_init.h"

#ifdef TEST_GDI2
#include "sge_gdi_ctx.h"
#include "sge_feature.h"
#endif


extern char **environ;

int main(int argc, char *argv[]);

/************************************************************************/
int main(int argc, char **argv)
{
   lList *alp = NULL;
#ifdef TEST_GDI2
   sge_gdi_ctx_class_t *ctx = NULL;
#endif   

   DENTER_MAIN(TOP_LAYER, "qconf");

   log_state_set_log_gui(1);
   sge_setup_sig_handlers(QCONF);
   
#ifdef TEST_GDI2
   if (sge_gdi2_setup(&ctx, QCONF, &alp) != AE_OK) {
      answer_list_output(&alp);
      SGE_EXIT((void**)&ctx, 1);
   }

   if (sge_parse_qconf((void*)ctx, ++argv)) {
      SGE_EXIT((void**)&ctx, 1);
   } else {
      SGE_EXIT((void**)&ctx, 0);
   }
   DEXIT;
   return 0;
#else
   sge_mt_init();

   lInit(nmv);

   sge_gdi_param(SET_MEWHO, QCONF, NULL);
   if (sge_gdi_setup(prognames[QCONF], &alp)!=AE_OK) {
      answer_list_output(&alp);
      SGE_EXIT(NULL, 1);
   }

   if (sge_parse_qconf(NULL, ++argv)) {
      SGE_EXIT(NULL, 1);
   } else {
      SGE_EXIT(NULL, 0);
   }
   DEXIT;
   return 0;
#endif

}
