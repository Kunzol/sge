#ifndef __MSG_SGEOBJLIB_H
#define __MSG_SGEOBJLIB_H
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

#define MSG_ANSWER_NOANSWERLIST     _MESSAGE(64000, _("no answer list - gdi request failed\n"))
#define MSG_CKPTREFINJOB_SU         _MESSAGE(64001, _("Checkpointing object "SFQ" is still referenced in job " U32CFormat".\n"))
#define MSG_GDI_INVALIDPRODUCTMODESTRING_S   _MESSAGE(64005, _("invalid security mode string "SFQ"\n"))
#define MSG_GDI_SWITCHFROMTO_SS              _MESSAGE(64007, _("switching from "SFQ" to "SFQ" feature set\n"))
#define MSG_HOSTREFINQUEUE_SS                _MESSAGE(64008, _("Host object "SFQ" is still referenced in cluster queue "SFQ".\n"))
#define MSG_HOSTREFINHGRP_SS                             _MESSAGE(64011, _("Host object "SFQ" is still referenced in host group "SFQ".\n"))
#define MSG_GDI_CONFIGNOARGUMENTGIVEN_S                  _MESSAGE(64012, _("no argument given in config option: "SFN"\n"))
#define MSG_GDI_CONFIGMISSINGARGUMENT_S                  _MESSAGE(64013, _("missing configuration attribute "SFQ""))
#define MSG_GDI_CONFIGADDLISTFAILED_S                    _MESSAGE(64014, _("can't add "SFQ" to list"))
#define MSG_GDI_CONFIGARGUMENTNOTDOUBLE_SS               _MESSAGE(64016, _("value for attribute "SFN" "SFQ" is not a double\n"))
#define MSG_GDI_CONFIGARGUMENTNOTTIME_SS                 _MESSAGE(64017, _("value for attribute "SFN" "SFQ" is not time\n"))
#define MSG_GDI_CONFIGARGUMENTNOMEMORY_SS                _MESSAGE(64018, _("value for attribute "SFN" "SFQ" is not memory\n"))
#define MSG_GDI_CONFIGINVALIDQUEUESPECIFIED              _MESSAGE(64019, _("reading conf file: invalid queue type specified\n"))
#define MSG_GDI_CONFIGREADFILEERRORNEAR_SS               _MESSAGE(64020, _("reading conf file: "SFN" error near "SFQ"\n"))
#define MSG_GDI_READCONFIGFILESPECGIVENTWICE_SS          _MESSAGE(64021, _("reading config file: specifier "SFQ" given twice for "SFQ"\n"))
#define MSG_GDI_READCONFIGFILEUNKNOWNSPEC_SS             _MESSAGE(64022, _("reading conf file: unknown specifier "SFQ" for "SFN"\n"))
#define MSG_GDI_READCONFIGFILEEMPTYENUMERATION_S         _MESSAGE(64023, _("reading conf file: empty enumeration for "SFQ"\n"))
#define MSG_JOB_XISINVALIDJOBTASKID_S                    _MESSAGE(64024, _("ERROR! "SFQ" is an invalid job-task identifier\n"))
#define MSG_JOB_LONELY_TOPTION_S                          _MESSAGE(64025, _("found lonely '-t "SFN"' option (The -t option needs a leading job name).\n"))

#define MSG_JOB_JLPPNULL                  _MESSAGE(64028, _("jlpp == NULL in job_add_job()\n"))                                                        
#define MSG_JOB_JEPNULL                   _MESSAGE(64029, _("jep == NULL in job_add_job()\n"))
#define MSG_JOB_JOBALREADYEXISTS_S        _MESSAGE(64030, _("can't add job "SFN" - job already exists\n") )
#define MSG_JOB_NULLNOTALLOWEDT           _MESSAGE(64031, _("job rejected: 0 is an invalid task id\n"))
#define MSG_JOB_NOIDNOTALLOWED            _MESSAGE(64032, _("job rejected: Job comprises no tasks in its id lists") )
#define MSG_JOB_JOB_ID_U                  _MESSAGE(64033, _(U32CFormat))
#define MSG_JOB_JOB_JATASK_ID_UU          _MESSAGE(64034, _(U32CFormat"."U32CFormat))
#define MSG_JOB_JOB_JATASK_PETASK_ID_UUS  _MESSAGE(64035, _(U32CFormat"."U32CFormat" task "SFN))
#define MSG_JOB_NODISPLAY_S               _MESSAGE(64036, _("no DISPLAY variable found with interactive job "SFN"\n"))
#define MSG_JOB_EMPTYDISPLAY_S            _MESSAGE(64037, _("empty DISPLAY variable delivered with interactive job "SFN"\n"))
#define MSG_JOB_LOCALDISPLAY_SS           _MESSAGE(64038, _("local DISPLAY variable "SFQ" delivered with interactive job "SFN"\n"))
#define MSG_ERRORPARSINGVALUEFORNM_S  _MESSAGE(64040, _("error parsing value "SFQ"\n"))
#define MSG_PARSE_STARTTIMETOOLONG    _MESSAGE(64041, _("Starttime specifier field length exceeds maximum"))
#define MSG_PARSE_INVALIDSECONDS      _MESSAGE(64042, _("Invalid format of seconds field."))
#define MSG_PARSE_INVALIDHOURMIN      _MESSAGE(64043, _("Invalid format of date/hour-minute field."))
#define MSG_PARSE_INVALIDMONTH        _MESSAGE(64044, _("Invalid month specifica tion."))
#define MSG_PARSE_INVALIDDAY          _MESSAGE(64045, _("Invalid day specificati on."))
#define MSG_PARSE_INVALIDHOUR         _MESSAGE(64046, _("Invalid hour specification."))
#define MSG_PARSE_INVALIDMINUTE       _MESSAGE(64047, _("Invalid minute specification."))
#define MSG_PARSE_INVALIDSECOND       _MESSAGE(64048, _("Invalid seconds specification."))
#define MSG_PARSE_NODATEFROMINPUT     _MESSAGE(64049, _("Couldn't generate date from input. Perhaps a date before 1970 was specified."))
#define MSG_PARSE_NODATE                                _MESSAGE(64050, _("no date specified"))
#define MSG_PEREFINJOB_SU                               _MESSAGE(64059, _("Pe "SFQ" is still referenced in job "U32CFormat".\n"))
#define MSG_GDI_INITIALPORTIONSTRINGNODECIMAL_S          _MESSAGE(64060, _("Numerical value invalid!\nThe initial portion of string "SFQ" contains no decimal number\n"))
#define MSG_GDI_RANGESPECIFIERWITHUNKNOWNTRAILER_SS      _MESSAGE(64061, _("Range specifier "SFQ" has unknown trailer "SFQ"\n"))
#define MSG_GDI_UNEXPECTEDRANGEFOLLOWINGUNDEFINED        _MESSAGE(64062, _("unexpected range following \"UNDEFINED\"\n"))
#define MSG_GDI_UNEXPECTEDUNDEFINEDFOLLOWINGRANGE        _MESSAGE(64063, _("unexpected \"UNDEFINED\" following range\n"))
#define MSG_GDI_NEGATIVSTEP                              _MESSAGE(64064, _("Negative or zero step in range is not allowed\n" ))
#define MSG_PARSE_NOALLOCATTRLIST     _MESSAGE(64065, _("unable to alloc space for attrib. list\n"))
#define MSG_PARSE_NOALLOCATTRELEM     _MESSAGE(64068, _("unable to alloc space for attrib. element\n"))
#define MSG_NONE_NOT_ALLOWED                    _MESSAGE(64079, _("The keyword \"none\" is not allowed in \"load_formula\"\n"))
#define MSG_NOTEXISTING_ATTRIBUTE_S             _MESSAGE(64080, _("\"load_formula\" references not existing complex attribute "SFQ"\n"))
#define MSG_WRONGTYPE_ATTRIBUTE_S               _MESSAGE(64081, _("String, CString or Host attributes are not allowed in \"load_formula\": " SFQ "\n"))
#define MSG_US_INVALIDUSERNAME                  _MESSAGE(64083, _("userset contains invalid (null) user name"))

/*
 * sge_event.c
 */
#define MSG_EVENT_JOBXFINISH_US                    _MESSAGE(64084, _(U32CFormat". EVENT JOB "SFN" FINISH"))
#define MSG_EVENT_ADDJATASK_US                     _MESSAGE(64085, _(U32CFormat". EVENT ADD JATASK "SFN""))
#define MSG_EVENT_DELJOB_US                        _MESSAGE(64086, _(U32CFormat". EVENT DEL JOB "SFN))
#define MSG_EVENT_ADDJOB_US                        _MESSAGE(64087, _(U32CFormat". EVENT ADD JOB "SFN))
#define MSG_EVENT_MODJOB_US                        _MESSAGE(64088, _(U32CFormat". EVENT MOD JOB "SFN))
#define MSG_EVENT_JOBLISTXELEMENTS_UI              _MESSAGE(64089, _(U32CFormat". EVENT JOB LIST %d Elements"))
#define MSG_EVENT_DELJOB_SCHEDD_INFO_III           _MESSAGE(64090, _("%d. EVENT DEL JOB_SCHEDD_INFO %d.%d"))
#define MSG_EVENT_ADDJOB_SCHEDD_INFO_III           _MESSAGE(64091, _("%d. EVENT ADD JOB_SCHEDD_INFO %d.%d"))
#define MSG_EVENT_MODJOB_SCHEDD_INFO_III           _MESSAGE(64092, _("%d. EVENT MOD JOB_SCHEDD_INFO %d.%d"))
#define MSG_EVENT_JOB_SCHEDD_INFOLISTXELEMENTS_II  _MESSAGE(64093, _("%d. EVENT JOB_SCHEDD_INFO LIST %d Elements"))
#define MSG_EVENT_MODSCHEDDPRIOOFJOBXTOY_USI       _MESSAGE(64094, _(U32CFormat". EVENT MODIFY SCHEDULING PRIORITY OF JOB "SFN" TO %d"))
#define MSG_EVENT_JOBXUSAGE_US                     _MESSAGE(64095, _(U32CFormat". EVENT JOB "SFN" USAGE"))
#define MSG_EVENT_JOBXFINALUSAGE_US                _MESSAGE(64096, _(U32CFormat". EVENT JOB "SFN" FINAL USAGE"))
#define MSG_EVENT_UNSUSPENDQUEUEXONSUBORDINATE_IS  _MESSAGE(64101, _("%d. EVENT UNSUSPEND QUEUE "SFN" ON SUBORDINATE"))
#define MSG_EVENT_SUSPENDQUEUEXONSUBORDINATE_IS    _MESSAGE(64102, _("%d. EVENT SUSPEND QUEUE "SFN" ON SUBORDINATE"))
#define MSG_EVENT_DELCONFIGX_IS                    _MESSAGE(64107, _("%d. EVENT DEL CONFIG "SFN""))
#define MSG_EVENT_ADDCONFIGX_IS                    _MESSAGE(64108, _("%d. EVENT ADD CONFIG "SFN""))
#define MSG_EVENT_MODCONFIGX_IS                    _MESSAGE(64109, _("%d. EVENT MOD CONFIG "SFN""))
#define MSG_EVENT_CONFIGLISTXELEMENTS_II           _MESSAGE(64110, _("%d. EVENT CONFIG LIST %d Elements"))
#define MSG_EVENT_DELCALENDARX_IS                  _MESSAGE(64111, _("%d. EVENT DEL CALENDAR "SFN""))
#define MSG_EVENT_ADDCALENDARX_IS                  _MESSAGE(64112, _("%d. EVENT ADD CALENDAR "SFN""))
#define MSG_EVENT_MODCALENDARX_IS                  _MESSAGE(64113, _("%d. EVENT MOD CALENDAR "SFN""))
#define MSG_EVENT_CALENDARLISTXELEMENTS_II         _MESSAGE(64114, _("%d. EVENT CALENDAR LIST %d Elements"))
#define MSG_EVENT_DELADMINHOSTX_IS                 _MESSAGE(64115, _("%d. EVENT DEL ADMINHOST "SFN""))
#define MSG_EVENT_ADDADMINHOSTX_IS                 _MESSAGE(64116, _("%d. EVENT ADD ADMINHOST "SFN""))
#define MSG_EVENT_MODADMINHOSTX_IS                 _MESSAGE(64117, _("%d. EVENT MOD ADMINHOST "SFN""))
#define MSG_EVENT_ADMINHOSTLISTXELEMENTS_II        _MESSAGE(64118, _("%d. EVENT ADMINHOST LIST %d Elements"))
#define MSG_EVENT_DELEXECHOSTX_IS                  _MESSAGE(64119, _("%d. EVENT DEL EXECHOST "SFN""))
#define MSG_EVENT_ADDEXECHOSTX_IS                  _MESSAGE(64120, _("%d. EVENT ADD EXECHOST "SFN""))
#define MSG_EVENT_MODEXECHOSTX_IS                  _MESSAGE(64121, _("%d. EVENT MOD EXECHOST "SFN""))
#define MSG_EVENT_EXECHOSTLISTXELEMENTS_II         _MESSAGE(64122, _("%d. EVENT EXECHOST LIST %d Elements"))
#define MSG_EVENT_DELMANAGERX_IS                   _MESSAGE(64123, _("%d. EVENT DEL MANAGER "SFN""))
#define MSG_EVENT_ADDMANAGERX_IS                   _MESSAGE(64124, _("%d. EVENT ADD MANAGER "SFN""))
#define MSG_EVENT_MODMANAGERX_IS                   _MESSAGE(64125, _("%d. EVENT MOD MANAGER "SFN""))
#define MSG_EVENT_MANAGERLISTXELEMENTS_II          _MESSAGE(64126, _("%d. EVENT MANAGER LIST %d Elements"))
#define MSG_EVENT_DELOPERATORX_IS                  _MESSAGE(64127, _("%d. EVENT DEL OPERATOR "SFN""))
#define MSG_EVENT_ADDOPERATORX_IS                  _MESSAGE(64128, _("%d. EVENT ADD OPERATOR "SFN""))
#define MSG_EVENT_MODOPERATORX_IS                  _MESSAGE(64129, _("%d. EVENT MOD OPERATOR "SFN""))
#define MSG_EVENT_OPERATORLISTXELEMENTS_II         _MESSAGE(64130, _("%d. EVENT OPERATOR LIST %d Elements"))
#define MSG_EVENT_DELSUBMITHOSTX_IS                _MESSAGE(64131, _("%d. EVENT DEL SUBMITHOST "SFN""))
#define MSG_EVENT_ADDSUBMITHOSTX_IS                _MESSAGE(64132, _("%d. EVENT ADD SUBMITHOST "SFN""))
#define MSG_EVENT_MODSUBMITHOSTX_IS                _MESSAGE(64133, _("%d. EVENT MOD SUBMITHOST "SFN""))
#define MSG_EVENT_SUBMITHOSTLISTXELEMENTS_II       _MESSAGE(64134, _("%d. EVENT SUBMITHOST LIST %d Elements"))
#define MSG_EVENT_DELUSERSETX_IS                   _MESSAGE(64135, _("%d. EVENT DEL USER SET "SFN""))
#define MSG_EVENT_ADDUSERSETX_IS                   _MESSAGE(64136, _("%d. EVENT ADD USER SET "SFN""))
#define MSG_EVENT_MODUSERSETX_IS                   _MESSAGE(64137, _("%d. EVENT MOD USER SET "SFN""))
#define MSG_EVENT_USERSETLISTXELEMENTS_II          _MESSAGE(64138, _("%d. EVENT USER SET LIST %d Elements"))
#define MSG_EVENT_DELUSERX_IS                      _MESSAGE(64139, _("%d. EVENT DEL USER "SFN""))
#define MSG_EVENT_ADDUSERX_IS                      _MESSAGE(64140, _("%d. EVENT ADD USER "SFN""))
#define MSG_EVENT_MODUSERX_IS                      _MESSAGE(64141, _("%d. EVENT MOD USER "SFN""))
#define MSG_EVENT_USERLISTXELEMENTS_II             _MESSAGE(64142, _("%d. EVENT USER LIST %d Elements"))
#define MSG_EVENT_DELPROJECTX_IS                   _MESSAGE(64143, _("%d. EVENT DEL PROJECT "SFN""))
#define MSG_EVENT_ADDPROJECTX_IS                   _MESSAGE(64144, _("%d. EVENT ADD PROJECT "SFN""))
#define MSG_EVENT_MODPROJECTX_IS                   _MESSAGE(64145, _("%d. EVENT MOD PROJECT "SFN""))
#define MSG_EVENT_PROJECTLISTXELEMENTS_II          _MESSAGE(64146, _("%d. EVENT PROJECT LIST %d Elements"))
#define MSG_EVENT_DELPEX_IS                        _MESSAGE(64147, _("%d. EVENT DEL PE "SFN""))
#define MSG_EVENT_ADDPEX_IS                        _MESSAGE(64148, _("%d. EVENT ADD PE "SFN""))
#define MSG_EVENT_MODPEX_IS                        _MESSAGE(64149, _("%d. EVENT MOD PE "SFN""))
#define MSG_EVENT_PELISTXELEMENTS_II               _MESSAGE(64150, _("%d. EVENT PE LIST %d Elements"))
#define MSG_EVENT_SHUTDOWN_I                       _MESSAGE(64151, _("%d. EVENT SHUTDOWN"))
#define MSG_EVENT_QMASTERGOESDOWN_I                _MESSAGE(64152, _("%d. EVENT QMASTER GOES DOWN"))
#define MSG_EVENT_TRIGGERSCHEDULERMONITORING_I     _MESSAGE(64153, _("%d. EVENT TRIGGER SCHEDULER MONITORING"))
#define MSG_EVENT_SHARETREEXNODESYLEAFS_III        _MESSAGE(64154, _("%d. EVENT SHARETREE %d nodes %d leafs"))
#define MSG_EVENT_SCHEDULERCONFIG_I                _MESSAGE(64155, _("%d. EVENT SCHEDULER CONFIG "))
#define MSG_EVENT_GLOBAL_CONFIG_I                  _MESSAGE(64156, _("%d. EVENT NEW GLOBAL CONFIG"))
#define MSG_EVENT_DELCKPT_IS                       _MESSAGE(64157, _("%d. EVENT DEL CKPT "SFN""))
#define MSG_EVENT_ADDCKPT_IS                       _MESSAGE(64158, _("%d. EVENT ADD CKPT "SFN""))
#define MSG_EVENT_MODCKPT_IS                       _MESSAGE(64159, _("%d. EVENT MOD CKPT "SFN""))
#define MSG_EVENT_CKPTLISTXELEMENTS_II             _MESSAGE(64160, _("%d. EVENT CKPT LIST %d Elements"))
#define MSG_EVENT_DELJATASK_US                     _MESSAGE(64161, _(U32CFormat". EVENT DEL JATASK "SFN""))
#define MSG_EVENT_MODJATASK_US                     _MESSAGE(64162, _(U32CFormat". EVENT MOD JATASK "SFN""))
#define MSG_EVENT_ADDPETASK_US                     _MESSAGE(64163, _(U32CFormat". EVENT ADD PETASK "SFN""))
#define MSG_EVENT_DELPETASK_US                     _MESSAGE(64164, _(U32CFormat". EVENT DEL PETASK "SFN""))
#define MSG_EVENT_NOTKNOWN_I                       _MESSAGE(64165, _("%d. EVENT ????????"))
#define MSG_OBJECT_INVALID_OBJECT_TYPE_SI          _MESSAGE(64167, _(SFN": invalid object type %d\n"))
#define MSG_HGRP_UNKNOWNHOST                       _MESSAGE(64168, _("unable to resolve host "SFQ"\n"))
#define MSG_CUSER_NOREMOTE_USER_S                  _MESSAGE(64169, _("attribute \'"SFQ"\' not available\n"))
#define MSG_EVENT_HGROUPLISTXELEMENTS_II           _MESSAGE(64170, _("%d. EVENT HOST GROUP LIST %d Elements"))
#define MSG_EVENT_DELHGROUPX_IS                    _MESSAGE(64171, _("%d. EVENT DEL HOST GROUP "SFN""))
#define MSG_EVENT_ADDHGROUPX_IS                    _MESSAGE(64172, _("%d. EVENT ADD HOST GROUP "SFN""))
#define MSG_EVENT_MODHGROUPX_IS                    _MESSAGE(64173, _("%d. EVENT MOD HOST GROUP "SFN""))
#define MSG_SGETEXT_NO_INTERFACE_S                 _MESSAGE(64174, _("no valid checkpoint interface "SFN"\n"))
#define MSG_OBJ_CKPTENV_SSS                        _MESSAGE(64175, _("parameter "SFN" of ckpt environment "SFQ": "SFN"\n"))
#define MSG_CKPT_XISNOTASIGNALSTRING_S             _MESSAGE(64176, _(SFQ" is not a signal string (like HUP, INT, " "WINCH, ..)\n"))
#define MSG_PE_STARTPROCARGS_SS                    _MESSAGE(64177, _("parameter start_proc_args of pe "SFQ": "SFN"\n"))
#define MSG_PE_STOPPROCARGS_SS                     _MESSAGE(64178, _("parameter stop_proc_args of pe "SFQ": "SFN"\n"))
#define MSG_ANSWERWITHOUTDIAG                      _MESSAGE(64179, _("error without diagnosis message"))
#define MSG_PEREFDOESNOTEXIST_S                    _MESSAGE(64180, _("Pe "SFQ" does not exist\n"))
#define MSG_CKPTREFDOESNOTEXIST_S                  _MESSAGE(64181, _("Ckpt "SFQ" does not exist\n"))
#define MSG_PEREFINQUEUE_SS                        _MESSAGE(64182, _("Pe "SFQ" is still referenced in queue "SFQ".\n"))
#define MSG_CKPTREFINQUEUE_SS                      _MESSAGE(64183, _("Ckpt "SFQ" is still referenced in queue "SFQ".\n"))
#define MSG_INVALID_CENTRY_TYPE_S                  _MESSAGE(64184, _("Invalid complex attribute type ("SFQ")\n"))
#define MSG_INVALID_CENTRY_RELOP_S                 _MESSAGE(64185, _("Invalid complex attribute for relation operator ("SFQ")\n"))
#define MSG_INVALID_CENTRY_REQUESTABLE_S           _MESSAGE(64186, _("Invalid complex attribute for requestable ("SFQ")\n"))
#define MSG_CENTRYREFINQUEUE_SS                    _MESSAGE(64187, _("Complex attribute "SFQ" is still referenced in queue "SFQ".\n"))
#define MSG_CENTRYREFINHOST_SS                     _MESSAGE(64188, _("Complex attribute "SFQ" is still referenced in host "SFQ".\n"))
#define MSG_CENTRYREFINSCONF_S                     _MESSAGE(64189, _("Complex attribute "SFQ" is still referenced in scheduler configuration.\n"))
#define MSG_PARSE_DUPLICATEHOSTINFILESPEC          _MESSAGE(64190,_("ERROR! two files are specified for the same host\n"))
#define MSG_EVENT_CENTRYLISTXELEMENTS_II           _MESSAGE(64191, _("%d. EVENT COMPLEX ENTRY LIST %d Elements"))
#define MSG_EVENT_DELCENTRYX_IS                    _MESSAGE(64192, _("%d. EVENT DEL COMPLEX ENTRY "SFN""))
#define MSG_EVENT_ADDCENTRYX_IS                    _MESSAGE(64193, _("%d. EVENT ADD COMPLEX ENTRY "SFN""))
#define MSG_EVENT_MODCENTRYX_IS                    _MESSAGE(64194, _("%d. EVENT MOD COMPLEX ENTRY "SFN""))
#define MSG_EVENT_CQUEUELISTXELEMENTS_II           _MESSAGE(64195, _("%d. EVENT CLUSTER QUEUE LIST %d Elements"))
#define MSG_EVENT_DELCQUEUEX_IS                    _MESSAGE(64196, _("%d. EVENT DEL CLUSTER QUEUE "SFN""))
#define MSG_EVENT_ADDCQUEUEX_IS                    _MESSAGE(64197, _("%d. EVENT ADD CLUSTER QUEUE "SFN""))
#define MSG_EVENT_MODCQUEUEX_IS                    _MESSAGE(64198, _("%d. EVENT MOD CLUSTER QUEUE "SFN""))
#define MSG_EVENT_DELQINSTANCE_ISS                 _MESSAGE(64199, _("%d. EVENT DEL QUEUE INSTANCE "SFN"@"SFN""))
#define MSG_EVENT_ADDQINSTANCE_ISS                 _MESSAGE(64200, _("%d. EVENT ADD QUEUE INSTANCE "SFN"@"SFN""))
#define MSG_EVENT_MODQINSTANCE_ISS                 _MESSAGE(64201, _("%d. EVENT MOD QUEUE INSTANCE "SFN"@"SFN""))
#define MSG_INVALID_CENTRY_DEFAULT_S               _MESSAGE(64202, _("Complex "SFQ" cannot have a default value\n"))
#define MSG_INVALID_CENTRY_CONSUMABLE_RELOP_S      _MESSAGE(64203, _("Consumable "SFQ" can have only <= as an relational operator\n"))
#define MSG_INVALID_CENTRY_CONSUMABLE_TYPE_SS      _MESSAGE(64204, _("Complex "SFQ" of type "SFQ" cannot be a consumable\n"))
#define MSG_INVALID_CENTRY_TYPE_RELOP_S            _MESSAGE(64205, _("Complex "SFQ" has an invalid relational operator\n")) 
#define MSG_INVALID_CENTRY_PARSE_DEFAULT_SS        _MESSAGE(64206, _("Complex "SFQ"'s default value should be of type "SFQ"\n"))
#define MSG_INVALID_CENTRY_CONSUMABLE_REQ1_S       _MESSAGE(64207, _("Consumable "SFQ" needs a default value because it is not requestable.\n"))
#define MSG_INVALID_CENTRY_CONSUMABLE_REQ2_S       _MESSAGE(64208, _("Consumable "SFQ" cannot have a default value because it is forced.\n")) 
#define MSG_INVALID_CENTRY_TYPE_CHANGE_S           _MESSAGE(64209, _("The type of the complex "SFQ" cannot be changed due to its built in status\n"))

#define MSG_CQUEUE_NONDEFNOTALLOWED                _MESSAGE(64210, _("Queue domain/instance values are only allowed for cluster queues.\n"))
#define MSG_CQUEUE_PRIORITYNOTINRANGE  _MESSAGE(64211, _("Priority not in range -20 to +20\n"))
#define MSG_CQUEUE_UNKNOWNUSERSET_S    _MESSAGE(64213, _("Userset "SFQ" does not exist\n") )
#define MSG_CQUEUE_UNKNOWNPROJECT_S    _MESSAGE(64214, _("Project "SFQ" does not exist\n"))
#define MSG_CQUEUE_UNKNOWNCALENDAR_S   _MESSAGE(64215, _("Calendar "SFQ" does not exist\n"))
#define MSG_CQUEUE_UNKNOWNINITSTATE_S  _MESSAGE(64216, _("Invalid value "SFQ" as initial state\n"))
#define MSG_CQUEUE_UNKNOWNSTARTMODE_S  _MESSAGE(64217, _("Invalid value "SFQ" as shell start mode\n"))

#define MSG_ATTR_VALUEMULDEFINED_S     _MESSAGE(64218, _("Value for "SFQ" is multiply defined\n"))
#define MSG_ATTR_NONEWATTRSETTING_S    _MESSAGE(64219, _("Cannot create new attribute setting for host "SFQ"\n"))
#define MSG_ATTR_RESULTUNAMBIGUOUS_S   _MESSAGE(64220, _("Modification would result in ambiguous configuration\n"))
#define MSG_ATTR_NOCONFVALUE           _MESSAGE(64221, _("No default/hostgroup/host value found\n"))
#define MSG_ATTR_MISSINGCOMMA_S        _MESSAGE(64222, _("All list elements must be separated by commas: "SFQ"\n"))
#define MSG_ATTR_MISSINGBRACKET_S      _MESSAGE(64223, _("The last character of each list item must be enclosed in brackets: "SFQ"\n"))
#define MSG_ATTR_EQUALSIGNEXPRECTED    _MESSAGE(64224, _("\'=\' has to sepatate host or group from value\n"))
#define MSG_ATTR_TRAILINGCOMMA_S       _MESSAGE(64225, _("There is an extra comma at the end of the list: "SFQ"\n"))
#define MSG_ATTR_PARSINGERROR_S        _MESSAGE(64226, _("Error during parsing of attribute value "SFQ"\n"))
#define MSG_ATTR_NOVALUEGIVEN          _MESSAGE(64227, _("No value specified\n"))

#define MSG_CQUEUE_NODEFVALUE_S        _MESSAGE(64228, _(SFQ" has no default value\n"))
#define MSG_CQUEUE_MULVALNOTALLOWED_S  _MESSAGE(64229, _("Multiple values for one queue domain/host ("SFN") are not allowed\n"))
#define MSG_CQUEUE_WRONGCHARINPRIO     _MESSAGE(64231, _("Invalid character\n"))
#define MSG_QINSTANCE_ALARM            _MESSAGE(64233, _("load alarm"))
#define MSG_QINSTANCE_SUSPALARM        _MESSAGE(64234, _("suspend alarm"))
#define MSG_QINSTANCE_DISABLED         _MESSAGE(64235, _("disabled"))
#define MSG_QINSTANCE_SUSPENDED        _MESSAGE(64236, _("suspended"))
#define MSG_QINSTANCE_UNKNOWN          _MESSAGE(64237, _("unknown"))
#define MSG_QINSTANCE_ERROR            _MESSAGE(64238, _("error"))
#define MSG_QINSTANCE_SUSPOSUB         _MESSAGE(64239, _("suspended on subordinate"))
#define MSG_QINSTANCE_CALDIS           _MESSAGE(64240, _("calendar disabled"))
#define MSG_QINSTANCE_CALSUSP          _MESSAGE(64241, _("calendar suspended"))
#define MSG_QINSTANCE_CONFAMB          _MESSAGE(64242, _("configuration ambiguous"))
#define MSG_QINSTANCE_ORPHANED         _MESSAGE(64243, _("orphaned"))

#define MSG_QINSTANCE_NALARM           _MESSAGE(64244, _("no load alarm"))
#define MSG_QINSTANCE_NSUSPALARM       _MESSAGE(64245, _("no suspend alarm"))
#define MSG_QINSTANCE_NDISABLED        _MESSAGE(64246, _("enabled"))
#define MSG_QINSTANCE_NSUSPENDED       _MESSAGE(64247, _("unsuspended"))
#define MSG_QINSTANCE_NUNKNOWN         _MESSAGE(64248, _("not unknown"))
#define MSG_QINSTANCE_NERROR           _MESSAGE(64249, _("no error"))
#define MSG_QINSTANCE_NSUSPOSUB        _MESSAGE(64250, _("no suspended on subordinate"))
#define MSG_QINSTANCE_NCALDIS          _MESSAGE(64251, _("calendar enabled"))
#define MSG_QINSTANCE_NCALSUSP         _MESSAGE(64252, _("calendar unsuspended"))
#define MSG_QINSTANCE_NCONFAMB         _MESSAGE(64253, _("not configuration ambiguous"))
#define MSG_QINSTANCE_NORPHANED        _MESSAGE(64254, _("not orphaned"))
#define MSG_QINSTANCE_MISSLOTS_S       _MESSAGE(64255, _("missing \"slots\" entry in consumable actual list of queue "SFQ"\n"))
#define MSG_CALENDAR_REFINQUEUE_SS     _MESSAGE(64256, _("Calendar "SFQ" is still referenced in queue "SFQ".\n"))
#define MSG_STR_INVALIDSTR             _MESSAGE(64257, _("Encountered invalid id\n"))
#define MSG_QINSTANCE_INVALIDACTION    _MESSAGE(64258, _("Invalid action\n" ))
#define MSG_QINSTANCE_INVALIDOPTION    _MESSAGE(64259, _("Invalid option flag\n"))
#define MSG_ID_UNABLETOCREATE          _MESSAGE(64260, _("Unable to create id element\n"))
#define MSG_CQUEUE_SUBITSELF_S         _MESSAGE(64261, _("Cluster queue "SFQ" can't get subordinated by itself\n"))
#define MSG_CQUEUE_UNKNOWNSUB_SS       _MESSAGE(64262, _("Subordinated cluster queue "SFQ" referenced in "SFQ" does not exist\n"))
#define MSG_QREF_QUNKNOWN_S            _MESSAGE(64263, _("Job was rejected because job requests unknown queue "SFQ"\n"))
#define MSG_QREF_QNOTREQUESTABLE       _MESSAGE(64264, _("Job was rejected because job requests a queue while queues are not configured as requestable\n"))
#define MSG_ATTRIB_PARSATTRFAILED_SS         _MESSAGE(64265, _("failed parsing attribute "SFQ": "SFN"\n"))
#define MSG_OBJECT_NO_LIST_TO_MOD_TYPE_SI    _MESSAGE(64266, _("%s: has no master list to modify %d\n"))
#define MSG_INVALID_CENTRY_PARSE_URGENCY_SS  _MESSAGE(64267, _("The following error occoured for complex "SFQ", while parsing the urgency value: "SFQ"\n"))
#define MSG_ULONG_INCORRECTSTRING      _MESSAGE(64268, _("error parsing unsigned long value from string "SFQ"\n"))
#define MSG_INT_INCORRECTSTRING        _MESSAGE(64269, _("error parsing signed int value from string "SFQ"\n"))
#define MSG_CHAR_INCORRECTSTRING       _MESSAGE(64270, _("error parsing character value from string "SFQ"\n"))
#define MSG_LONG_INCORRECTSTRING       _MESSAGE(64271, _("error parsing signed long from string "SFQ"\n"))
#define MSG_DOUBLE_INCORRECTSTRING     _MESSAGE(64272, _("error parsing double value from string "SFQ"\n"))
#define MSG_FLOAT_INCORRECTSTRING      _MESSAGE(64273, _("error parsing float value from string "SFQ"\n"))
#define MSG_QTYPE_INCORRECTSTRING      _MESSAGE(64274, _("error parsing queue type from string "SFQ"\n"))
#define MSG_QSTATE_UNKNOWNCHAR_CS      _MESSAGE(64275, _("unknwon queue state: %c found in string: %s\n"))
#define MSG_QSTAT_WRONGGCHAR_C         _MESSAGE(64276, _("wrong character \'%c\' for -g option\n"))
#define MSG_CQUEUE_UNKNOWNCENTRY_S     _MESSAGE(64277, _("Complex attribute "SFQ" does not exist\n"))
#define MSG_OBJECT_ALREADYEXIN_SSS     _MESSAGE(64278, _("No modification because "SFQ" already exists in "SFQ" of "SFQ"\n"))
#define MSG_CONF_USING_SS              _MESSAGE(64300, _("using "SFQ" for "SFN"\n"))
#define MSG_CONF_NOCONFIGFROMMASTER    _MESSAGE(64301, _("could not get configuration from qmaster - using defaults\n"))
#define MSG_CONF_NR_DYNAMIC_EVENT_CLIENT_EXCEEDS_MAX_FILEDESCR_U _MESSAGE(64302, _("nr of dynamic event clients exceeds max file descriptor limit, setting MAX_DYN_EC="U32CFormat"\n"))
#define MSG_CENTRY_QINOTALLOWED        _MESSAGE(64303, _("Queue instance names are not allowed in -l resource requests\n"))
#define MSG_OBJECT_VALUENOTULONG_S     _MESSAGE(64304, _(SFQ" is not an u_long32 value\n"))
#define MSG_CQUEUE_INVALIDDOMSETTING_SS _MESSAGE(64305, _("Did not modify "SFQ" for host group "SFQ" which does not exist.\n"))
#define MSG_HGRP_INVALIDHOSTGROUPNAME_S   _MESSAGE(64306, _("host group name "SFQ" is not valid\n"))
#define MSG_WEIGHTFACTNONUMB_S         _MESSAGE(64307, _("\"load_formula\" uses "SFQ" as weighting factor (only numbers are allowed)\n"))
#define MSG_MULTIPLEWEIGHTFACT         _MESSAGE(64308, _("\"load_formula\" may not use multiple weighting factors\n"))

#define MSG_QINSTANCE_HOSTFORQUEUEDOESNOTEXIST_SS   _MESSAGE(64309, _("can't creae queue "SFQ": host "SFQ" is not known\n"))

#endif /* __MSG_SGEOBJLIB_H */
