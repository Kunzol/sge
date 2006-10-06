#ifndef JUTI_H
#define JUTI_H
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

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef WINDOWS
typedef int gid_t;
#endif

typedef struct error_handler_str error_handler_t;

struct error_handler_str {
   void (*error)(const char* fmt, ...);
};

typedef enum {
   JUTI_AUTH_SUCCESS = 0,     /* authentication success */
   JUTI_AUTH_FAILED  = 1,    /* invalid username or password */
   JUTI_AUTH_ERROR   = 2     /* authentication is not proper configured */
} auth_result_t;

auth_result_t do_pam_authenticate(const char* service, const char *username, const char *password,
                        error_handler_t *error_handler);
int juti_getgrouplist(const char *uname, gid_t agroup, gid_t **groups_res, int *grpcnt);
auth_result_t get_crypted_password(const char* username, char* buffer, size_t size,
                                   error_handler_t *error_handler);

void setEcho(int flag);

#ifdef  __cplusplus
}
#endif


#endif
