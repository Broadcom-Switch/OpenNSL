/** \addtogroup error Error Handling
 *  @{
 */
/*****************************************************************************
 * 
 * (C) Copyright Broadcom Corporation 2013-2015
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * 
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 ***************************************************************************//**
 * \file			error.h
 ******************************************************************************/

#ifndef __OPENNSL_ERROR_H__
#define __OPENNSL_ERROR_H__

#include <shared/error.h>

/** 
 * OPENNSL API error codes.
 * 
 * Note: An error code may be converted to a string by passing the code
 * to opennsl_errmsg().
 */
typedef enum opennsl_error_e {
    OPENNSL_E_NONE         = _SHR_E_NONE, 
    OPENNSL_E_INTERNAL     = _SHR_E_INTERNAL, 
    OPENNSL_E_MEMORY       = _SHR_E_MEMORY, 
    OPENNSL_E_UNIT         = _SHR_E_UNIT, 
    OPENNSL_E_PARAM        = _SHR_E_PARAM, 
    OPENNSL_E_EMPTY        = _SHR_E_EMPTY, 
    OPENNSL_E_FULL         = _SHR_E_FULL, 
    OPENNSL_E_NOT_FOUND    = _SHR_E_NOT_FOUND, 
    OPENNSL_E_EXISTS       = _SHR_E_EXISTS, 
    OPENNSL_E_TIMEOUT      = _SHR_E_TIMEOUT, 
    OPENNSL_E_BUSY         = _SHR_E_BUSY, 
    OPENNSL_E_FAIL         = _SHR_E_FAIL, 
    OPENNSL_E_DISABLED     = _SHR_E_DISABLED, 
    OPENNSL_E_BADID        = _SHR_E_BADID, 
    OPENNSL_E_RESOURCE     = _SHR_E_RESOURCE, 
    OPENNSL_E_CONFIG       = _SHR_E_CONFIG, 
    OPENNSL_E_UNAVAIL      = _SHR_E_UNAVAIL, 
    OPENNSL_E_INIT         = _SHR_E_INIT, 
    OPENNSL_E_PORT         = _SHR_E_PORT 
} opennsl_error_t;

/** Switch event types */
typedef enum opennsl_switch_event_e {
    OPENNSL_SWITCH_EVENT_PARITY_ERROR          =   _SHR_SWITCH_EVENT_PARITY_ERROR, 
    OPENNSL_SWITCH_EVENT_STABLE_FULL           =   _SHR_SWITCH_EVENT_STABLE_FULL, 
    OPENNSL_SWITCH_EVENT_STABLE_ERROR          =   _SHR_SWITCH_EVENT_STABLE_ERROR, 
    OPENNSL_SWITCH_EVENT_UNCONTROLLED_SHUTDOWN =   _SHR_SWITCH_EVENT_UNCONTROLLED_SHUTDOWN, 
    OPENNSL_SWITCH_EVENT_WARM_BOOT_DOWNGRADE   =   _SHR_SWITCH_EVENT_WARM_BOOT_DOWNGRADE, 
    OPENNSL_SWITCH_EVENT_MMU_BST_TRIGGER       =   _SHR_SWITCH_EVENT_MMU_BST_TRIGGER, 
} opennsl_switch_event_t;

#define OPENNSL_SUCCESS(rv)     \
    _SHR_E_SUCCESS(rv) 
#define OPENNSL_FAILURE(rv)     \
    _SHR_E_FAILURE(rv) 
#define OPENNSL_IF_ERROR_RETURN(op)  \
    _SHR_E_IF_ERROR_RETURN(op) 
#define OPENNSL_IF_ERROR_NOT_UNAVAIL_RETURN(op)  \
    _SHR_E_IF_ERROR_NOT_UNAVAIL_RETURN(op) 
#define opennsl_errmsg(rv)      \
    _SHR_ERRMSG(rv) 
#include <opennsl/errorX.h>
#endif /* __OPENNSL_ERROR_H__ */
/*@}*/
