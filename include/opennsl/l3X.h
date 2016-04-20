/** \addtogroup l3 Layer 3 Management
 *  @{
 */
/*****************************************************************************
 * 
 * This software is governed by the Broadcom Advanced Switch APIs license.
 * This license is set out in the
 * https://github.com/Broadcom-Switch/OpenNSL/Legal/LICENSE-Adv file.
 * 
 * Copyright 2015-2016 Broadcom Corporation. All rights reserved.
 * 
 ***************************************************************************//**
 * \file			l3X.h
 ******************************************************************************/

#ifndef __OPENNSL_L3X_H__
#define __OPENNSL_L3X_H__

#if defined(INCLUDE_L3)

#include <opennsl/types.h>
#include <opennsl/stat.h>
#include <opennsl/mpls.h>

#define OPENNSL_L3_ECMP_DYNAMIC_MODE_NORMAL 1          /**< ECMP dynamic load
                                                          balancing normal mode:
                                                          if inactivity duration
                                                          lapsed, use optimal
                                                          member, else use
                                                          assigned member. */
/***************************************************************************//** 
 *\brief Attach counters entries to the given L3 Egress interface.
 *
 *\description This API will attach counters entries to the given L3 Egress
 *          interface.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    intf_id [IN]   Interface ID of a egress L3 object
 *\param    stat_counter_id [IN]   Stat Counter ID
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_l3_egress_stat_attach(
    int unit, 
    opennsl_if_t intf_id, 
    uint32 stat_counter_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Detach counters entries to the given L3 Egress interface.
 *
 *\description This API will detach counters entries to the given L3 Egress
 *          interface.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    intf_id [IN]   Interface ID of a egress L3 object.
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_l3_egress_stat_detach(
    int unit, 
    opennsl_if_t intf_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Attach counters entries to the given L3 ingress interface.
 *
 *\description This API will attach counters entries to the given L3 ingress
 *          Interface.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    intf_id [IN]   Interface ID of a L3 ingress object or a valid VLAN
 *\param    stat_counter_id [IN]   Stat Counter ID
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_l3_ingress_stat_attach(
    int unit, 
    opennsl_if_t intf_id, 
    uint32 stat_counter_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Detach counters entries to the given L3 ingress interface.
 *
 *\description This API will detach counters entries to the given L3 ingress
 *          Interface.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    intf_id [IN]   Interface ID of a L3 ingress object or a valid VLAN
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_l3_ingress_stat_detach(
    int unit, 
    opennsl_if_t intf_id) LIB_DLL_EXPORTED ;

#define OPENNSL_L3_IP4_OPTIONS_WITH_ID  0x00000001 /**< With ID option creation */
#define OPENNSL_L3_IP4_OPTIONS_REPLACE  0x00000002 /**< Replace existing entry */
/** L3 IP options handing actions. */
typedef enum opennsl_l3_ip4_options_action_e {
    opennslIntfIPOptionActionNone = 0,  /**< No action. */
    opennslIntfIPOptionActionCopyToCPU = 1, /**< Copy to CPU action. */
    opennslIntfIPOptionActionDrop = 2,  /**< Drop action. */
    opennslIntfIPOptionActionCopyCPUAndDrop = 3 /**< Copy to CPU and Drop action. */
} opennsl_l3_ip4_options_action_t;

/***************************************************************************//** 
 *\brief Create a new L3 IP options handling profile.
 *
 *\description Creates a new L3 IP option handling profile.
 *          The specified default action will be applied to all the IP options
 *          in the profile that is being created.
 *          The valid flags are as follows:.
 *
 *\param    unit [IN]   Unit number.
 *\param    flags [IN]   Flags
 *\param    default_action [IN]   default action to apply for all IP options in
 *          the profile.
 *\param    ip4_options_profile_id [IN,OUT]   Created Profile ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_ip4_options_profile_create(
    int unit, 
    uint32 flags, 
    opennsl_l3_ip4_options_action_t default_action, 
    int *ip4_options_profile_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete an L3 IP options Profile.
 *
 *\description Deletes an IP options profile.
 *
 *\param    unit [IN]   Unit number.
 *\param    ip4_options_profile_id [OUT]   ID of IP options profile. ID 0 is
 *          reserved and cannot be deleted.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_ip4_options_profile_destroy(
    int unit, 
    int ip4_options_profile_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set Individual IP options action for a given IP option profile.
 *
 *\description Update the action for the specified IP option for a given IP
 *          option profile.
 *
 *\param    unit [IN]   Unit number.
 *\param    ip4_options_profile_id [IN]   ID of IP options profile. ID 0 is
 *          reserved and cannot be Modified.
 *\param    ip4_option [IN]   ID of IP options profile. ID 0 is reserved and
 *          cannot be Modified.
 *\param    action [IN]   new action for the IP option specified in ip4_option
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_ip4_options_action_set(
    int unit, 
    int ip4_options_profile_id, 
    int ip4_option, 
    opennsl_l3_ip4_options_action_t action) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get Individual IP options action for a given IP option profile.
 *
 *\description Retrieve the action for the specified IP option for a given IP
 *          option profile.
 *
 *\param    unit [IN]   Unit number.
 *\param    ip4_options_profile_id [IN]   ID of IP options profile
 *\param    ip4_option [IN]   ID of IP options profile
 *\param    action [OUT]   Retrieved action for the IP option specified in
 *          ip4_option
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_ip4_options_action_get(
    int unit, 
    int ip4_options_profile_id, 
    int ip4_option, 
    opennsl_l3_ip4_options_action_t *action) LIB_DLL_EXPORTED ;

#endif /* defined(INCLUDE_L3) */

#endif /* __OPENNSL_L3X_H__ */
/*@}*/
