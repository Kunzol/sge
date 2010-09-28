#ifndef __CL_ERROR_H
#define __CL_ERROR_H
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

#define CL_RETVAL_START_ID 1000
#define CL_RETVAL_OK                       (CL_RETVAL_START_ID + 0)
#define CL_RETVAL_MALLOC                   (CL_RETVAL_START_ID + 1)
#define CL_RETVAL_PARAMS                   (CL_RETVAL_START_ID + 2)
#define CL_RETVAL_UNKNOWN                  (CL_RETVAL_START_ID + 3)
#define CL_RETVAL_MUTEX_ERROR              (CL_RETVAL_START_ID + 4)
#define CL_RETVAL_MUTEX_CLEANUP_ERROR      (CL_RETVAL_START_ID + 5)
#define CL_RETVAL_MUTEX_LOCK_ERROR         (CL_RETVAL_START_ID + 6)
#define CL_RETVAL_MUTEX_UNLOCK_ERROR       (CL_RETVAL_START_ID + 7)
#define CL_RETVAL_CONDITION_ERROR          (CL_RETVAL_START_ID + 8)
#define CL_RETVAL_CONDITION_CLEANUP_ERROR  (CL_RETVAL_START_ID + 9)
#define CL_RETVAL_CONDITION_WAIT_TIMEOUT   (CL_RETVAL_START_ID + 10)
#define CL_RETVAL_CONDITION_SIGNAL_ERROR   (CL_RETVAL_START_ID + 11)
#define CL_RETVAL_THREAD_CREATE_ERROR      (CL_RETVAL_START_ID + 12)
#define CL_RETVAL_THREAD_START_TIMEOUT     (CL_RETVAL_START_ID + 13)
#define CL_RETVAL_THREAD_NOT_FOUND         (CL_RETVAL_START_ID + 14)
#define CL_RETVAL_THREAD_JOIN_ERROR        (CL_RETVAL_START_ID + 15)
#define CL_RETVAL_THREAD_CANCELSTATE_ERROR (CL_RETVAL_START_ID + 16)
#define CL_RETVAL_LOG_NO_LOGLIST           (CL_RETVAL_START_ID + 17)
#define CL_RETVAL_CONNECTION_NOT_FOUND     (CL_RETVAL_START_ID + 18)
#define CL_RETVAL_HANDLE_NOT_FOUND         (CL_RETVAL_START_ID + 19)
#define CL_RETVAL_THREADS_ENABLED          (CL_RETVAL_START_ID + 20)
#define CL_RETVAL_NO_MESSAGE               (CL_RETVAL_START_ID + 21)
#define CL_RETVAL_CREATE_SOCKET            (CL_RETVAL_START_ID + 22)
#define CL_RETVAL_CONNECT_ERROR            (CL_RETVAL_START_ID + 23)
#define CL_RETVAL_CONNECT_TIMEOUT          (CL_RETVAL_START_ID + 24)
#define CL_RETVAL_NOT_OPEN                 (CL_RETVAL_START_ID + 25)
#define CL_RETVAL_SEND_ERROR               (CL_RETVAL_START_ID + 26)
#define CL_RETVAL_BIND_SOCKET              (CL_RETVAL_START_ID + 27)
#define CL_RETVAL_SELECT_ERROR             (CL_RETVAL_START_ID + 28)
#define CL_RETVAL_RECEIVE_ERROR            (CL_RETVAL_START_ID + 29)
#define CL_RETVAL_PIPE_ERROR               (CL_RETVAL_START_ID + 30)
#define CL_RETVAL_GETHOSTNAME_ERROR        (CL_RETVAL_START_ID + 31)
#define CL_RETVAL_SEND_TIMEOUT             (CL_RETVAL_START_ID + 32)
#define CL_RETVAL_READ_TIMEOUT             (CL_RETVAL_START_ID + 33)
#define CL_RETVAL_UNDEFINED_FRAMEWORK      (CL_RETVAL_START_ID + 34)
#define CL_RETVAL_NOT_SERVICE_HANDLER      (CL_RETVAL_START_ID + 35)
#define CL_RETVAL_NO_FRAMEWORK_INIT        (CL_RETVAL_START_ID + 36)
#define CL_RETVAL_SETSOCKOPT_ERROR         (CL_RETVAL_START_ID + 37)
#define CL_RETVAL_FCNTL_ERROR              (CL_RETVAL_START_ID + 38)
#define CL_RETVAL_LISTEN_ERROR             (CL_RETVAL_START_ID + 39)
#define CL_RETVAL_NEED_EMPTY_FRAMEWORK     (CL_RETVAL_START_ID + 40)
#define CL_RETVAL_LOCK_ERROR               (CL_RETVAL_START_ID + 41)
#define CL_RETVAL_UNLOCK_ERROR             (CL_RETVAL_START_ID + 42)
#define CL_RETVAL_WRONG_FRAMEWORK          (CL_RETVAL_START_ID + 43)
#define CL_RETVAL_READ_ERROR               (CL_RETVAL_START_ID + 44)
#define CL_RETVAL_MAX_READ_SIZE            (CL_RETVAL_START_ID + 45)
#define CL_RETVAL_CLIENT_WELCOME_ERROR     (CL_RETVAL_START_ID + 46)
#define CL_RETVAL_UNKOWN_HOST_ERROR        (CL_RETVAL_START_ID + 47)
#define CL_RETVAL_LOCAL_HOSTNAME_ERROR     (CL_RETVAL_START_ID + 48)
#define CL_RETVAL_UNKNOWN_ENDPOINT         (CL_RETVAL_START_ID + 49)
#define CL_RETVAL_UNCOMPLETE_WRITE         (CL_RETVAL_START_ID + 50)
#define CL_RETVAL_UNCOMPLETE_READ          (CL_RETVAL_START_ID + 51)
#define CL_RETVAL_LIST_DATA_NOT_EMPTY      (CL_RETVAL_START_ID + 52)
#define CL_RETVAL_LIST_NOT_EMPTY           (CL_RETVAL_START_ID + 53)
#define CL_RETVAL_LIST_DATA_IS_NULL        (CL_RETVAL_START_ID + 54)
#define CL_RETVAL_THREAD_SETSPECIFIC_ERROR (CL_RETVAL_START_ID + 55)
#define CL_RETVAL_NOT_THREAD_SPECIFIC_INIT (CL_RETVAL_START_ID + 56)
#define CL_RETVAL_ALLREADY_CONNECTED       (CL_RETVAL_START_ID + 57)
#define CL_RETVAL_STREAM_BUFFER_OVERFLOW   (CL_RETVAL_START_ID + 58)
#define CL_RETVAL_GMSH_ERROR               (CL_RETVAL_START_ID + 59)
#define CL_RETVAL_MESSAGE_ACK_ERROR        (CL_RETVAL_START_ID + 60)
#define CL_RETVAL_MESSAGE_WAIT_FOR_ACK     (CL_RETVAL_START_ID + 61)
#define CL_RETVAL_ENDPOINT_NOT_UNIQUE      (CL_RETVAL_START_ID + 62)
#define CL_RETVAL_SYNC_RECEIVE_TIMEOUT     (CL_RETVAL_START_ID + 63)
#define CL_RETVAL_MAX_MESSAGE_LENGTH_ERROR (CL_RETVAL_START_ID + 64)
#define CL_RETVAL_RESOLVING_SETUP_ERROR    (CL_RETVAL_START_ID + 65)
#define CL_RETVAL_IP_NOT_RESOLVED_ERROR    (CL_RETVAL_START_ID + 66)
#define CL_RETVAL_MESSAGE_IN_BUFFER        (CL_RETVAL_START_ID + 67)
#define CL_RETVAL_CONNECTION_GOING_DOWN    (CL_RETVAL_START_ID + 68)
#define CL_RETVAL_CONNECTION_STATE_ERROR   (CL_RETVAL_START_ID + 69)
#define CL_RETVAL_SELECT_TIMEOUT           (CL_RETVAL_START_ID + 70)
#define CL_RETVAL_SELECT_INTERRUPT         (CL_RETVAL_START_ID + 71)
#define CL_RETVAL_NO_SELECT_DESCRIPTORS    (CL_RETVAL_START_ID + 72)
#define CL_RETVAL_ALIAS_EXISTS             (CL_RETVAL_START_ID + 73)
#define CL_RETVAL_NO_ALIAS_FILE            (CL_RETVAL_START_ID + 74)
#define CL_RETVAL_ALIAS_FILE_NOT_FOUND     (CL_RETVAL_START_ID + 75)
#define CL_RETVAL_OPEN_ALIAS_FILE_FAILED   (CL_RETVAL_START_ID + 76)
#define CL_RETVAL_ALIAS_VERSION_ERROR      (CL_RETVAL_START_ID + 77)
#define CL_RETVAL_SECURITY_ANNOUNCE_FAILED (CL_RETVAL_START_ID + 78)
#define CL_RETVAL_SECURITY_SEND_FAILED     (CL_RETVAL_START_ID + 79)
#define CL_RETVAL_SECURITY_RECEIVE_FAILED  (CL_RETVAL_START_ID + 80)
#define CL_RETVAL_ACCESS_DENIED            (CL_RETVAL_START_ID + 81)
#define CL_RETVAL_MAX_CON_COUNT_REACHED    (CL_RETVAL_START_ID + 82)
#define CL_RETVAL_GETHOSTADDR_ERROR        (CL_RETVAL_START_ID + 83)
#define CL_RETVAL_NO_PORT_ERROR            (CL_RETVAL_START_ID + 84)
#define CL_RETVAL_PROTOCOL_ERROR           (CL_RETVAL_START_ID + 85)





#define CL_RETVAL_LAST_ID                  (CL_RETVAL_START_ID + 86)  /* this must be the last number + 1 */
#define CL_RETVAL_UNDEFINED_STR "UNDEFINED"

const char* cl_get_error_text(int error_id);   /* CR check */

#endif /* __CL_ERROR_H */