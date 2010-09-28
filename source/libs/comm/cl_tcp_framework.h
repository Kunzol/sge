#ifndef __CL_TCP_FRAMEWORK_H
#define __CL_TCP_FRAMEWORK_H

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

#include <netinet/in.h>
#include "cl_lists.h"
#include "cl_data_types.h"




/* connection specific struct (not used from outside) */
typedef struct cl_com_tcp_private_type {
   /* TCP/IP specific */
   int           server_port;         /* used port for server setup */
   int           connect_port;        /* port to connect to */
   int           sockfd;              /* socket file descriptor */
   struct sockaddr_in client_addr;    /* used in connect for storing client addr of connection partner */ 
} cl_com_tcp_private_t;




int cl_com_tcp_free_com_private(cl_com_connection_t* connection);   /* CR check */ 
void cl_dump_tcp_private(cl_com_connection_t* connection); 

int cl_com_tcp_get_fd(cl_com_connection_t* connection, int* fd);
int cl_com_tcp_get_service_port(cl_com_connection_t* connection, int* port);
int cl_com_tcp_get_connect_port(cl_com_connection_t* connection, int* port);

int cl_com_tcp_open_connection(cl_com_connection_t* connection, int timeout, unsigned long only_once);  /* CR check */
int cl_com_tcp_close_connection(cl_com_connection_t** connection);  /* CR check */
int cl_com_tcp_send_message(cl_com_connection_t* connection, int timeout_time, cl_byte_t* data, long size, unsigned long *only_one_write );  /* CR check */
int cl_com_tcp_receive_message(cl_com_connection_t* connection, int timeout_time, cl_byte_t* data_buffer, unsigned long data_buffer_size, unsigned long *only_one_read);  /* CR check */
int cl_com_tcp_open_connection_request_handler(cl_raw_list_t* connection_list, cl_com_connection_t* service_connection, int timeout_val_sec, int timeout_val_usec, cl_select_method_t select_mode ); /* CR check */


int cl_com_tcp_connection_request_handler_setup(cl_com_connection_t* connection,cl_com_endpoint_t* local_endpoint);  /* CR check */
int cl_com_tcp_connection_request_handler(cl_com_connection_t* connection,cl_com_connection_t** new_connection ,int timeout_val_sec, int timeout_val_usec );  /* CR check */
int cl_com_tcp_connection_request_handler_cleanup(cl_com_connection_t* connection); /* CR check */

/* connection establish help functions */
int cl_com_tcp_connection_complete_request(cl_com_connection_t* connection, unsigned long timeout,unsigned long only_once );  /* CR check */
int cl_com_tcp_read_GMSH(cl_com_connection_t* connection, unsigned long *only_one_read);





#endif /* __CL_TCP_FRAMEWORK_H */

