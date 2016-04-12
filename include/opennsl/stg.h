/** \addtogroup stg Spanning Tree
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
 * \file			stg.h
 ******************************************************************************/

#ifndef __OPENNSL_STG_H__
#define __OPENNSL_STG_H__

#include <shared/port.h>
#include <opennsl/types.h>

/** opennsl_stg_stp_e */
typedef enum opennsl_stg_stp_e {
    OPENNSL_STG_STP_DISABLE = _SHR_PORT_STP_DISABLE, /**< Disabled. */
    OPENNSL_STG_STP_BLOCK = _SHR_PORT_STP_BLOCK, /**< BPDUs/no learns. */
    OPENNSL_STG_STP_LISTEN = _SHR_PORT_STP_LISTEN, /**< BPDUs/no learns. */
    OPENNSL_STG_STP_LEARN = _SHR_PORT_STP_LEARN, /**< BPDUs/learns. */
    OPENNSL_STG_STP_FORWARD = _SHR_PORT_STP_FORWARD, /**< Normal operation. */
    OPENNSL_STG_STP_COUNT = _SHR_PORT_STP_COUNT 
} opennsl_stg_stp_t;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Initialize the Spanning Tree Group (STG) module to its initial
 *       configuration.
 *
 *\description Initializes the STG module. A default STG is then created, with
 *          all its ports in the OPENNSL_STG_STP_DISABLE state. Any previously
 *          existing STG information is lost. .
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_UNIT Invalid device ID
 *\retval    OPENNSL_E_XXX Other possible errors; for details, see
 ******************************************************************************/
extern int opennsl_stg_init(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroy all STGs and initialize the Spanning Tree Group (STG) module to
 *       its initial configuration.
 *
 *\description Destroys any current STGs and initializes the STG module to its
 *          initial configuration as described in =opennsl_stg_init . .
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_UNIT Invalid device ID
 *\retval    OPENNSL_E_INIT STG module is not currently initialized.
 *\retval    OPENNSL_E_XXX Other possible errors; for details, see
 ******************************************************************************/
extern int opennsl_stg_clear(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Designate the default STG ID for the chip.
 *
 *\description Sets the default STG ID of the chip. The indicated STG must be
 *          currently defined.
 *
 *\param    unit [IN]   Unit number.
 *\param    stg [IN]   Default STG ID for the chip.
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_INIT STG module is not currently initialized.
 *\retval    OPENNSL_E_BADID Invalid STG ID
 *\retval    OPENNSL_E_NOT_FOUND STG ID is not currently defined
 ******************************************************************************/
extern int opennsl_stg_default_set(
    int unit, 
    opennsl_stg_t stg) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Return the current default STG ID for the chip.
 *
 *\description Returns the default STG ID of the chip.
 *
 *\param    unit [IN]   Unit number.
 *\param    stg_ptr [OUT]   Pointer to returned default STG ID.
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_INIT STG module is not currently initialized.
 ******************************************************************************/
extern int opennsl_stg_default_get(
    int unit, 
    opennsl_stg_t *stg_ptr) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Add a VLAN to a specified STG.
 *
 *\description Adds the specified VLAN to the specified STG. Both VLAN and STG
 *          must be currently defined. The VLAN is implicitly removed from the
 *          STG it currently belongs to before it is added to the new STG.
 *          Note: STG Id 0 is reserved, created during initialization, and
 *          used for internal purposes.       VLANs should not be added to
 *          this group. .
 *
 *\param    unit [IN]   Unit number.
 *\param    stg [IN]   STG ID
 *\param    vid [IN]   VLAN ID
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_INIT STG module is not currently initialized.
 *\retval    OPENNSL_E_BADID Invalid STG ID or VLAN ID
 *\retval    OPENNSL_E_NOT_FOUND STG ID is not currently defined
 *\retval    OPENNSL_E_XXX Other possible errors; for details, see
 ******************************************************************************/
extern int opennsl_stg_vlan_add(
    int unit, 
    opennsl_stg_t stg, 
    opennsl_vlan_t vid) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Remove a VLAN from a Spanning Tree Group.
 *
 *\description Removes the specified VLAN from the specified STG and assigns it
 *          to the default STG. Both VLAN and STG must be currently defined.
 *
 *\param    unit [IN]   Unit number.
 *\param    stg [IN]   STG ID
 *\param    vid [IN]   VLAN ID
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_INIT STG module is not currently initialized.
 *\retval    OPENNSL_E_BADID Invalid STG ID or VLAN ID
 *\retval    OPENNSL_E_NOT_FOUND STG ID is not currently defined
 *\retval    OPENNSL_E_XXX Other possible errors; for details, see
 ******************************************************************************/
extern int opennsl_stg_vlan_remove(
    int unit, 
    opennsl_stg_t stg, 
    opennsl_vlan_t vid) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Remove all VLANs from a Spanning Tree Group.
 *
 *\description Removes all VLANs from the specified STG and assigns them to the
 *          default STG. The STG must be currently defined.
 *
 *\param    unit [IN]   Unit number.
 *\param    stg [IN]   STG ID
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_INIT STG module is not currently initialized.
 *\retval    OPENNSL_E_BADID Invalid STG ID or VLAN ID
 *\retval    OPENNSL_E_NOT_FOUND STG ID is not currently defined
 *\retval    OPENNSL_E_XXX Other possible errors; for details, see
 ******************************************************************************/
extern int opennsl_stg_vlan_remove_all(
    int unit, 
    opennsl_stg_t stg) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Generates a list of VLANs in a specified STG.
 *
 *\description Returns a pointer to a sorted list of VLANs belonging to the
 *          specified STG. If the STG currently contains no VLANs, *list is
 *          NULL and *count is 0. Otherwise, *list points to an array of the
 *          *count VLAN IDs in the indicated STG. The indicated STG must be
 *          currently defined. The caller is responsible for freeing the
 *          memory allocated for the returned list, that is, calling
 *          =opennsl_stg_vlan_list_destroy .
 *
 *\param    unit [IN]   Unit number.
 *\param    stg [IN]   STG ID
 *\param    list [OUT]   Pointer to returned pointer-to-array of VLAN IDs
 *\param    count [OUT]   Pointer to returned count of VLAN IDs
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_INIT STG module is not currently initialized.
 *\retval    OPENNSL_E_BADID Invalid STG ID or VLAN ID
 *\retval    OPENNSL_E_NOT_FOUND STG ID is not currently defined
 *\retval    OPENNSL_E_XXX Other possible errors; for details, see
 ******************************************************************************/
extern int opennsl_stg_vlan_list(
    int unit, 
    opennsl_stg_t stg, 
    opennsl_vlan_t **list, 
    int *count) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroy a list returned by =opennsl_stg_vlan_list .
 *
 *\description Destroys a list of VLAN IDs previously returned by
 *          =opennsl_stg_vlan_list , freeing the memory previously allocated
 *          by =opennsl_stg_vlan_list for the list of VLANs. The status of
 *          each VLAN in the list is not affected.
 *
 *\param    unit [IN]   Unit number.
 *\param    list [IN]   Pointer to array of VLAN IDs
 *\param    count [IN]   Count of VLAN IDs in the array
 *
 *\retval    OPENNSL_E_NONE Success
 ******************************************************************************/
extern int opennsl_stg_vlan_list_destroy(
    int unit, 
    opennsl_vlan_t *list, 
    int count) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create a new STG, using a new STG ID.
 *
 *\description Creates a new STG, and assigns the lowest available STG ID to it.
 *          All ports in the new STG are initialized to the
 *          OPENNSL_STG_STP_DISABLE state.
 *
 *\param    unit [IN]   Unit number.
 *\param    stg_ptr [OUT]   Pointer to returned STG ID
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_INIT STG module is not currently initialized.
 *\retval    OPENNSL_E_FULL if all available STG IDs are already being used
 *\retval    OPENNSL_E_XXX Other possible errors; for details, see
 ******************************************************************************/
extern int opennsl_stg_create(
    int unit, 
    opennsl_stg_t *stg_ptr) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroys the specified STG.
 *
 *\description Destroys the specified STG. Any VLAN(s) belonging to the specified
 *          STG will be put into the default STG. The default STG cannot be
 *          destroyed.
 *
 *\param    unit [IN]   Unit number.
 *\param    stg [IN]   STG ID
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_INIT STG module is not currently initialized.
 *\retval    OPENNSL_E_BADID Invalid STG ID
 *\retval    OPENNSL_E_NOT_FOUND STG ID is not currently defined
 *\retval    OPENNSL_E_XXX Other possible errors; for details, see
 ******************************************************************************/
extern int opennsl_stg_destroy(
    int unit, 
    opennsl_stg_t stg) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Generates a list of IDs for currently defined STGs.
 *
 *\description Returns a (pointer to a) sorted list of currently active STGs.  If
 *          there are no currently defined STGs, *list will be NULL and *count
 *          is 0. Otherwise, *list will point to an array of the *count
 *          currently defined STG IDs.  The caller is responsible for freeing
 *          the memory allocated for the returned list, that is, calling.
 *
 *\param    unit [IN]   Unit number.
 *\param    list [OUT]   Pointer to returned pointer-to-array of STG IDs
 *\param    count [OUT]   Pointer to returned count of STG IDs
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_INIT STG module is not currently initialized.
 *\retval    OPENNSL_E_XXX Other possible errors; for details, see
 ******************************************************************************/
extern int opennsl_stg_list(
    int unit, 
    opennsl_stg_t **list, 
    int *count) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroys a previously returned list of STG IDs; the STGs themselves are
 *       not affected.
 *
 *\description Destroys a list of STG IDs previously returned by
 *          =opennsl_stg_list, effectively freeing the memory previously
 *          allocated by opennsl_stg_list() for the list of STGs. The status
 *          of each STG in the list is not affected.
 *
 *\param    unit [IN]   Unit number.
 *\param    list [IN]   Pointer to array of STG IDs
 *\param    count [IN]   Count of STG IDs in the array
 *
 *\retval    OPENNSL_E_NONE Success
 ******************************************************************************/
extern int opennsl_stg_list_destroy(
    int unit, 
    opennsl_stg_t *list, 
    int count) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set the Spanning Tree Protocol state of a port/VP in the specified STG.
 *       VP GROUP STP state need to be setted per direction, Please use
 *       =opennsl_vlan_gport_add for this.
 *
 *\description Sets the specified local port to the indicated Spanning
 *          TreeProtocol (STP) state. The indicated STG must be currently
 *          defined. On some switches  the LISTENING state can be
 *          indistinguishable from the BLOCKING state.
 *
 *\param    unit [IN]   Unit number.
 *\param    stg [IN]   STG ID
 *\param    port [IN]   Local port number
 *\param    stp_state [IN]   Spanning Tree Protocol state
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_INIT STG module is not currently initialized.
 *\retval    OPENNSL_E_BADID Invalid STG ID
 *\retval    OPENNSL_E_PORT if invalid port specified
 *\retval    OPENNSL_E_NOT_FOUND STG ID is not currently defined
 *\retval    OPENNSL_E_XXX Other possible errors; for details, see
 ******************************************************************************/
extern int opennsl_stg_stp_set(
    int unit, 
    opennsl_stg_t stg, 
    opennsl_port_t port, 
    int stp_state) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Return the Spanning Tree Protocol state of a port in the specified STG.
 *
 *\description Returns the Spanning Tree Protocol state of the specified local
 *          port. The indicated STG must be currently defined. On some
 *          switches, the LISTENING state can be indistinguishable from the
 *          BLOCKING state.
 *
 *\param    unit [IN]   Unit number.
 *\param    stg [IN]   STG ID
 *\param    port [IN]   Local port number
 *\param    stp_state [OUT]   Pointer to the returned Spanning Tree Protocol state
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_INIT STG module is not currently initialized.
 *\retval    OPENNSL_E_BADID Invalid STG ID
 *\retval    OPENNSL_E_PORT if invalid port specified
 *\retval    OPENNSL_E_NOT_FOUND STG ID is not currently defined
 *\retval    OPENNSL_E_XXX Other possible errors; for details, see
 ******************************************************************************/
extern int opennsl_stg_stp_get(
    int unit, 
    opennsl_stg_t stg, 
    opennsl_port_t port, 
    int *stp_state) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Return the maximum number of STGs that the underlying hardware can
 *       support.
 *
 *\description Returns the maximum total number of STGs that the underlying
 *          hardware can support. The returned number is chip specific, and is
 *          not dependent upon the number of currently defined STGs.
 *
 *\param    unit [IN]   Unit number.
 *\param    max_stg [OUT]   Pointer to the returned max allowable STGs
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_INIT STG module is not currently initialized.
 ******************************************************************************/
extern int opennsl_stg_count_get(
    int unit, 
    int *max_stg) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#include <opennsl/stgX.h>
#endif /* __OPENNSL_STG_H__ */
/*@}*/
