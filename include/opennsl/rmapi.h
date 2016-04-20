/** \addtogroup rm Resource Management
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
 * \file			rmapi.h
 ******************************************************************************/

#ifndef __OPENNSL_RMAPI_H__
#define __OPENNSL_RMAPI_H__
#include <opennsl/types.h>
#include <sal/commdefs.h>

#define RM_MAX_UNITS         1
#define RM_MAX_CLIENTS       3

#define RM_MIN_CLIENT_ID     1
#define RM_MAX_CLIENT_ID     (RM_MAX_CLIENTS - 1)

/** opennsl_rm_retval_t */
typedef enum opennsl_rm_retval_e {
  OPENNSL_RM_E_NONE                   =  0,  /**< No Error */
  OPENNSL_RM_E_INVALID_INPUT          = -1,  /**< Invalid Input */
  OPENNSL_RM_E_INVALID_CLNT_ID        = -2,  /**< Invalid Client ID */
  OPENNSL_RM_E_INVALID_L2_ENTRY_LIMIT = -3,  /**< Invalid L2_ENTRY_CNT value */
  OPENNSL_RM_E_MEMALLOC_FAIL          = -4,  /**< Memory allocation failed */
  OPENNSL_RM_E_CLNT_LIMIT_EXCEEDED    = -5,  /**< Maximum clients reached */
  OPENNSL_RM_E_PHYPORT_CONFLICT       = -6,  /**< Requested ports already used*/
  OPENNSL_RM_E_VLAN_CONFLICT          = -7,  /**< Requested VLANs already used*/
  OPENNSL_RM_E_UNREGISTERED_CLNT_ID   = -8,  /**< Unregistered client ID */
  OPENNSL_RM_E_L2TABLE_LIMIT_EXCEEDED = -9,  /**< L2_Table limit exceeded */
  OPENNSL_RM_E_INTERNAL               = -10, /**< Internal error */
  OPENNSL_RM_E_LIMIT                  = -11, /**< Must be last */
} opennsl_rm_retval_t;

/** RM profile structure */
typedef struct opennsl_rm_profile_s
{
  opennsl_pbmp_t port_bitmap[RM_MAX_UNITS];  /**< Bitmap of physical ports */
  opennsl_vlan_vector_t vlan_bitmap;         /**< Bitmap of VLANs */
  uint32 l2_table_limit;                     /**< L2_Table limit value */
} opennsl_rm_profile_t;

/***************************************************************************//**
 *\brief Used to register with Resource Manager
 *
 *\description Each client which wants to use the resource manager(RM)
 *          functionality in OpenNSL, should register its requirements via a
 *          profile structure. This API validates the passed requirements
 *          along with the already registered clients and on successful
 *          registration returns a Client ID.
 *
 *\param    profile [IN] Pointer to the structure filled with resource
 *          requirements.
 *\param    client_id [OUT] Client ID assigned on successful registration
 *
 *\retval    OPENNSL_RM_E_XXX
 ******************************************************************************/
int opennsl_rm_register(opennsl_rm_profile_t *profile,
                        uint16 *client_id) LIB_DLL_EXPORTED;

/***************************************************************************//**
 *\brief Used to de-register with Resource Manager
 *
 *\description This API de-registers already registered client with the
 *             Resource Management(RM) module in OpenNSL.
 *
 *\param    client_id [IN] Client ID obtained on successful registration
 *
 *\retval    OPENNSL_RM_E_XXX
 ******************************************************************************/
int opennsl_rm_deregister(uint16 client_id) LIB_DLL_EXPORTED;


/***************************************************************************//**
 *\brief Used to update the registered ports with the Resource Manager for a
 *       given client.
 *
 *\description Each client which wants to use the resource manager(RM)
 *          functionality in OpenNSL, will register its requirements via a
 *          profile structure. If the client later wants to change its ports 
 *          requirement, it can use this API to update the ports value 
 *          of the profile.
 *
 *\param    client_id [IN] client ID returned by RM on successful registration
 *\param    unit [IN] unit ID for which the ports ownership is to be updated
 *\param    ports [OUT] New bitmap of the requested ports
 *
 *\retval    OPENNSL_RM_E_XXX
 ******************************************************************************/
int opennsl_rm_profile_ports_update(
                             uint16 client_id, 
                             int unit, 
                             opennsl_pbmp_t ports) LIB_DLL_EXPORTED;

/***************************************************************************//**
 *\brief Used to update the registered vlans with the Resource Manager for a
 *       given client.
 *
 *\description Each client which wants to use the resource manager(RM)
 *          functionality in OpenNSL, will register its requirements via a
 *          profile structure. If the client later wants to change its vlans 
 *          requirement, it can use this API to update the vlans value 
 *          of the profile.
 *
 *\param    client_id [IN] client ID returned by RM on successful registration
 *\param    vlans [OUT] New bitmap of the requested vlans
 *
 *\retval    OPENNSL_RM_E_XXX
 ******************************************************************************/
int opennsl_rm_profile_vlans_update(
                             uint16 client_id, 
                             opennsl_vlan_vector_t vlans) LIB_DLL_EXPORTED;

#ifdef RM_L2_LIMIT_CHECK
/***************************************************************************//**
 *\brief Used to update the registered l2 table limit value with the Resource 
 *       Manager for a given client.
 *
 *\description Each client which wants to use the resource manager(RM)
 *          functionality in OpenNSL, will register its requirements via a
 *          profile structure. If the client later wants to change its l2 table 
 *          limit requirement, it can use this API to update the l2 table limit 
 *          value of the profile.
 *
 *\param    client_id [IN] client ID returned by RM on successful registration
 *\param    vlans [OUT] New bitmap of the requested vlans
 *
 *\retval    OPENNSL_RM_E_XXX
 ******************************************************************************/
int opennsl_rm_profile_l2limit_update(
                             uint16 client_id, 
                             uint32 l2_table_limit) LIB_DLL_EXPORTED;
#endif /* RM_L2_LIMIT_CHECK */

/***************************************************************************//**
 *\brief Used to get the resource profile registered with Resource Manager
 *
 *\description Given a valid client ID, this API returns the profile structure
 *          registered with the Resource Manager(RM) in OpenNSL.
 *
 *\param    client_id [IN] Client ID obtained on successful registration
 *\param    profile [OUT] Pointer to the structure filled with resource
 *          requirements.
 *
 *\retval    OPENNSL_RM_E_XXX
 ******************************************************************************/
int opennsl_rm_profile_get(uint16 client_id,opennsl_rm_profile_t *profile) LIB_DLL_EXPORTED;

/***************************************************************************//**
 *\brief Return Resource Manager error string based on the error code
 *
 *\description Return Resource Manager error string based on the error code
 *
 *\param    rv [IN] error code
 *
 *\retval    Resource manager error string
 ******************************************************************************/
char* opennsl_rm_errmsg(int err) LIB_DLL_EXPORTED;

#endif /* __OPENNSL_RMAPI_H__ */
/*@}*/
