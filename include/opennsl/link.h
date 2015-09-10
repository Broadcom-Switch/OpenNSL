/** \addtogroup link Link monitoring and notification
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
 * \file			link.h
 ******************************************************************************/

#ifndef __OPENNSL_LINK_H__
#define __OPENNSL_LINK_H__

#include <opennsl/types.h>
#include <opennsl/port.h>

typedef void (*opennsl_linkscan_handler_t)(
    int unit, 
    opennsl_port_t port, 
    opennsl_port_info_t *info);

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Terminate linkscan on the specified unit.
 *
 *\description Disables link scanning on the specified unit, terminates the
 *          linkscan thread, and frees all memory associated with linkscan on
 *          the device. All registered handlers are unregistered requiring
 *          them to re-register if =opennsl_linkscan_init is called to
 *          reinitialize linkscan.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_XXX Operation failed, linkscan state is undefined.
 ******************************************************************************/
extern int opennsl_linkscan_detach(
    int unit) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Enable and disable link scanning or set the polling interval.
 *
 *\description Calling opennsl_linkscan_enable_set with a non-zero scanning
 *          interval sets the scan interval starts the linkscan task if
 *          required. If the specified interval is zero, the linkscan task is
 *          stopped. For this reason, it is required to have link scan enabled
 *          and running with a non-zero interval even if all ports are
 *          operating in hardware linkscan mode.
 *          opennsl_linkscan_enable_get returns the current scan interval. A
 *          returned scan interval of 0 indicates linkscan is disabled.
 *
 *\param    unit [IN]   Unit number.
 *\param    us [IN]   (for _set) Minimum time between software link scan cycles in
 *          micro-seconds. 0 indicates linkscan is disabled.
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_MEMORY
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_linkscan_enable_set(
    int unit, 
    int us) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Enable and disable link scanning or set the polling interval.
 *
 *\description Calling opennsl_linkscan_enable_set with a non-zero scanning
 *          interval sets the scan interval starts the linkscan task if
 *          required. If the specified interval is zero, the linkscan task is
 *          stopped. For this reason, it is required to have link scan enabled
 *          and running with a non-zero interval even if all ports are
 *          operating in hardware linkscan mode.
 *          opennsl_linkscan_enable_get returns the current scan interval. A
 *          returned scan interval of 0 indicates linkscan is disabled.
 *
 *\param    unit [IN]   Unit number.
 *\param    us [OUT]   (for _set) Minimum time between software link scan cycles
 *          in micro-seconds. 0 indicates linkscan is disabled.
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_MEMORY
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_linkscan_enable_get(
    int unit, 
    int *us) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/** opennsl_linkscan_mode_e */
typedef enum opennsl_linkscan_mode_e {
    OPENNSL_LINKSCAN_MODE_NONE   = 0,   
    OPENNSL_LINKSCAN_MODE_SW     = 1,   
    OPENNSL_LINKSCAN_MODE_HW     = 2,   
    OPENNSL_LINKSCAN_MODE_COUNT = 3     
} opennsl_linkscan_mode_t;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Get or set the link scanning mode for a port.
 *
 *\description Get or set the current link scanning mode for a port. The possible
 *          modes for a port are described in table =OPENNSL_LINKSCAN_MODE_e .
 *          opennsl_linkscan_mode_set operates on one port while
 *          opennsl_linkscan_mode_set_pbm operates on all ports specified in
 *          the port bit map. When operating on a port bit map, a failure on
 *          any one port aborts the processing of the request and the link
 *          scan mode of all the ports specified is undefined. Ports not in
 *          the port bit map are unaffected.
 *          The use of opennsl_linkscan_mode_set_pbm is not recommended.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device port number to set or get the mode of
 *\param    mode [IN]   (for _set and _set_pbm) Link scan mode, see table
 *          =OPENNSL_LINKSCAN_MODE_e .
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_PORT Invalid port
 *\retval    OPENNSL_E_PARAM Invalid mode
 *\retval    OPENNSL_E_UNAVAIL Mode requested is not support
 *\retval    OPENNSL_E_XXX Operation failed
 ******************************************************************************/
extern int opennsl_linkscan_mode_set(
    int unit, 
    opennsl_port_t port, 
    int mode) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set the link scanning mode for a port.
 *
 *\description Get or set the current link scanning mode for a port. The possible
 *          modes for a port are described in table =OPENNSL_LINKSCAN_MODE_e .
 *          opennsl_linkscan_mode_set operates on one port while
 *          opennsl_linkscan_mode_set_pbm operates on all ports specified in
 *          the port bit map. When operating on a port bit map, a failure on
 *          any one port aborts the processing of the request and the link
 *          scan mode of all the ports specified is undefined. Ports not in
 *          the port bit map are unaffected.
 *          The use of opennsl_linkscan_mode_set_pbm is not recommended.
 *
 *\param    unit [IN]   Unit number.
 *\param    pbm [IN]   Port bit map of ports to set the mode on
 *\param    mode [IN]   (for _set and _set_pbm) Link scan mode, see table
 *          =OPENNSL_LINKSCAN_MODE_e .
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_PORT Invalid port
 *\retval    OPENNSL_E_PARAM Invalid mode
 *\retval    OPENNSL_E_UNAVAIL Mode requested is not support
 *\retval    OPENNSL_E_XXX Operation failed
 ******************************************************************************/
extern int opennsl_linkscan_mode_set_pbm(
    int unit, 
    opennsl_pbmp_t pbm, 
    int mode) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set the link scanning mode for a port.
 *
 *\description Get or set the current link scanning mode for a port. The possible
 *          modes for a port are described in table =OPENNSL_LINKSCAN_MODE_e .
 *          opennsl_linkscan_mode_set operates on one port while
 *          opennsl_linkscan_mode_set_pbm operates on all ports specified in
 *          the port bit map. When operating on a port bit map, a failure on
 *          any one port aborts the processing of the request and the link
 *          scan mode of all the ports specified is undefined. Ports not in
 *          the port bit map are unaffected.
 *          The use of opennsl_linkscan_mode_set_pbm is not recommended.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device port number to set or get the mode of
 *\param    mode [OUT]   (for _set and _set_pbm) Link scan mode, see table
 *          =OPENNSL_LINKSCAN_MODE_e .
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_PORT Invalid port
 *\retval    OPENNSL_E_PARAM Invalid mode
 *\retval    OPENNSL_E_UNAVAIL Mode requested is not support
 *\retval    OPENNSL_E_XXX Operation failed
 ******************************************************************************/
extern int opennsl_linkscan_mode_get(
    int unit, 
    opennsl_port_t port, 
    int *mode) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Register and unregister link notification callouts.
 *
 *\description Register a handler invoked on a link up or link down transition.
 *          If multiple handlers are registered, they are invoked on a link
 *          transition in the same order as they were registered. The behavior
 *          of registering the same callout more than once is undefined.
 *          If an application chooses to perform custom port configurations
 *          which bypass API functions, such custom operations may need to be
 *          repeated whenever a port's link comes up.  Consult a Field
 *          Application Engineer for guidance.
 *
 *\param    unit [IN]   Unit number.
 *\param    f [IN]   OPENNSL callback function pointer (see
 *          =opennsl_linkscan_handler_t)
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_MEMORY
 ******************************************************************************/
extern int opennsl_linkscan_register(
    int unit, 
    opennsl_linkscan_handler_t f) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Register and unregister link notification callouts.
 *
 *\description Register a handler invoked on a link up or link down transition.
 *          If multiple handlers are registered, they are invoked on a link
 *          transition in the same order as they were registered. The behavior
 *          of registering the same callout more than once is undefined.
 *          If an application chooses to perform custom port configurations
 *          which bypass API functions, such custom operations may need to be
 *          repeated whenever a port's link comes up.  Consult a Field
 *          Application Engineer for guidance.
 *
 *\param    unit [IN]   Unit number.
 *\param    f [IN]   OPENNSL callback function pointer (see
 *          =opennsl_linkscan_handler_t)
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_MEMORY
 ******************************************************************************/
extern int opennsl_linkscan_unregister(
    int unit, 
    opennsl_linkscan_handler_t f) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#endif /* __OPENNSL_LINK_H__ */
/*@}*/
