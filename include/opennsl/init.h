/** \addtogroup init Initialization
 *  @{
 */
/*****************************************************************************
 * 
 * (C) Copyright Broadcom Corporation 2013-2016
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
 * \file			init.h
 ******************************************************************************/

#ifndef __OPENNSL_INIT_H__
#define __OPENNSL_INIT_H__

#include <opennsl/types.h>

/** OPENNSL Information structure. */
typedef struct opennsl_info_s {
    uint32 device;      /**< PCI values used usually. */
    uint32 revision;    /**< PCI values used usually. */
} opennsl_info_t;

/***************************************************************************//** 
 *\brief Attach a device as a OPENNSL unit.
 *
 *\description Create a OPENNSL unit instance.  If the unit parameter is
 *          	non-negative, use that value as the unit number for the        
 *          attached device.  Otherwise, search for an unused OPENNSL unit
 *          number. 	If the type parameter is NULL, then search for 	an
 *          appropriate dispatch driver.
 *
 *\param    unit [IN]   Unit number.
 *\param    type [IN]   Type of OPENNSL API dispatch driver
 *\param    subtype [IN]   Argument to dispatch driver
 *\param    remunit [IN]   Underlying remote unit
 *
 *\retval    unit			the attached non-negative unit number (if successful)
 *\retval    OPENNSL_E_MEMORY		memory allocation failure
 *\retval    OPENNSL_E_CONFIG		dispatch driver not found
 *\retval    OPENNSL_E_FULL		no available unit numbers
 *\retval    OPENNSL_E_EXISTS		requested unit number already attached
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_attach(
    int unit, 
    char *type, 
    char *subtype, 
    int remunit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Detach a device as a OPENNSL unit.
 *
 *\description Destroy a OPENNSL unit instance.  The unit is removed from the
 *          	list of OPENNSL dispatchable units.  Detaching a unit does not
 *          	affect the underlying device if it was attached as a loopback 	or
 *          remote unit. This API is not thread-safe. In a multi-threaded     
 *              environment where multiple threads may be calling various
 *          OPENNSL APIs,         it is recommended that such threads be
 *          stopped before invoking          opennsl_detach().
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_detach(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Determine if a OPENNSL unit is attached.
 *
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_UNIT	unit is not attached
 *\retval    OPENNSL_E_NONE	unit is attached
 ******************************************************************************/
extern int opennsl_attach_check(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Determine the highest OPENNSL unit currently attached.
 *
 *\description The parameter is filled with the highest currently attached 	unit
 *          number.  If no OPENNSL units are attached, then -1 will be 	stored
 *          through the parameter.
 *
 *\param    max_units [OUT]   highest unit number
 *
 *\retval    OPENNSL_E_NONE
 ******************************************************************************/
extern int opennsl_attach_max(
    int *max_units) LIB_DLL_EXPORTED ;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Get information about a OPENNSL unit.
 *
 *\description The OPENNSL device information structure given as an argument is
 *          filled in for the OPENNSL unit.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [OUT]   OPENNSL information structure, as defined in
 *          =opennsl_info_t
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_info_get(
    int unit, 
    opennsl_info_t *info) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/***************************************************************************//** 
 *\brief Initialize the OPENNSL Information structure.
 *
 *\description Initializes OPENNSL Information structure to default values. This
 *          function should be used to initialize any OPENNSL Information
 *          structure prior to filling it out and passing it to an API
 *          function. This ensures that subsequent API releases may add new
 *          structure members to the opennsl_info_t structure, and
 *          opennsl_info_t_init will initialize the new members to correct
 *          default values.
 *
 *\param    info [IN,OUT]   Pointer to OPENNSL Information structure.
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_info_t_init(
    opennsl_info_t *info) LIB_DLL_EXPORTED ;

#if !defined(OPENNSL_WARM_BOOT_SUPPORT)
#define _opennsl_shutdown(unit)  OPENNSL_E_NONE 
#endif
#include <opennsl/initX.h>
#endif /* __OPENNSL_INIT_H__ */
/*@}*/
