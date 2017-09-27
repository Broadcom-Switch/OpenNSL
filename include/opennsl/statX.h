/** \addtogroup stat Statistics
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
 * \file			statX.h
 ******************************************************************************/

#ifndef __OPENNSL_STATX_H__
#define __OPENNSL_STATX_H__

#include <opennsl/types.h>

/** Stat Group Mode Attribute Selectors */
typedef enum opennsl_stat_group_mode_attr_e {
    opennslStatGroupModeAttrColor = 1,  /**< Color Selector: Possible
                                           Value:opennslColorGreen|Yellow|REd or
                                           oxFFFFFFFF */
    opennslStatGroupModeAttrFieldIngressColor = 2, /**< Field Ingress Color Selector:
                                           Possible
                                           Values:opennslColorGreen|Yellow|REd
                                           or STAT_GROUP_MODE_ATTR_ALL_VALUES
                                           for all */
    opennslStatGroupModeAttrIntPri = 3, /**< Internal Priority Selector: Possible
                                           Values: 0 to 15 or
                                           STAT_GROUP_MODE_ATTR_ALL_VALUES for
                                           all */
    opennslStatGroupModeAttrVlan = 4,   /**< Vlan Type Selector: Possible Values:
                                           opennslStatGroupModeVlanAttr */
    opennslStatGroupModeAttrOuterPri = 5, /**< Outer Vlan Priority Selector:
                                           Possible Values: 0 to 7 or
                                           STAT_GROUP_MODE_ATTR_ALL_VALUES for
                                           all */
    opennslStatGroupModeAttrInnerPri = 6, /**< Inner Vlan Priority Selector:
                                           Possible Values: 0 to 7 or
                                           STAT_GROUP_MODE_ATTR_ALL_VALUES for
                                           all */
    opennslStatGroupModeAttrPort = 7,   /**< Logical Port Selector: Possible
                                           Values:<MaxLogicalPort> or
                                           STAT_GROUP_MODE_ATTR_ALL_VALUES for
                                           all */
    opennslStatGroupModeAttrTosDscp = 8, /**< Type Of Service Selector(DSCP :
                                           Differentiated services Code Point):
                                           Possible Values:<6b:TOS Val> or
                                           STAT_GROUP_MODE_ATTR_ALL_VALUES for
                                           all */
    opennslStatGroupModeAttrPktType = 10, /**< Packet Type Selector: Possible
                                           Values:<opennslStatGroupModeAttrPktType*> */
    opennslStatGroupModeAttrIngNetworkGroup = 11, /**< Ingress Network Group Selector:
                                           Possible Values:<Value> or
                                           STAT_GROUP_MODE_ATTR_ALL_VALUES for
                                           all */
    opennslStatGroupModeAttrDrop = 13,  /**< Drop Selector: Possible Values:<0 or
                                           1> */
    opennslStatGroupModeAttrPacketTypeIp = 14, /**< Ip Packet Selector: Possible
                                           Values:<0 or 1> */
} opennsl_stat_group_mode_attr_t;

/** Stat Flex Group Attribute Selector */
typedef struct opennsl_stat_group_mode_attr_selector_s {
    uint32 counter_offset;              /**< Counter Offset */
    opennsl_stat_group_mode_attr_t attr; /**< Attribute Selector */
    uint32 attr_value;                  /**< Attribute Values */
    uint32 udf_bitmap;                  /**< valid UDF bits, should be same in one
                                           mode id */
} opennsl_stat_group_mode_attr_selector_t;

/***************************************************************************//** 
 *\brief Initialize an attribute selector of Stat Flex Group Mode.
 *
 *\description This API create Customized Stat Group mode for given Counter
 *          Attributes and make system ready for attaching created mode id to
 *          different a/c objects.
 *
 *\param    attr_selector [IN,OUT]   Attribute Selector for Stat Flex Group Mode
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern void opennsl_stat_group_mode_attr_selector_t_init(
    opennsl_stat_group_mode_attr_selector_t *attr_selector) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create Customized Stat Group mode for given Counter Attributes In
 *       network switch, OAM LM is supported through Flex Counters, When
 *       OPENNSL_STAT_GROUP_MODE_CAPABILITY_OAM flag is passed along with
 *       OPENNSL_STAT_GROUP_MODE_INGRESS or OPENNSL_STAT_GROUP_MODE_EGRESS, it
 *       instructs the API to create a stat group suitable for OAM. In network
 *       switch, the packet cfi_pri offset map of Vlan Flow Counters is supported
 *       through this function to get the mode_id. And use this mode_id to create
 *       the customized group mode by opennsl_stat_custom_group_create. Counters
 *       with same counter_offset and with same attribute type but different
 *       attributes values are counted whenever either of the value(s) are true
 *       whereas with different attribute types the counter is incremented only
 *       when all of the attributes satisfy with their respective values. This
 *       API will be deprecated in the second half of 2016. stats mode id should
 *       be created using opennsl_stat_group_mode_id_config_create API.
 *
 *\description This API create Customized Stat Group mode for given Counter
 *          Attributes and make system ready for attaching created mode id to
 *          different a/c objects.
 *
 *\param    unit [IN]   Unit number.
 *\param    flags [IN]   STAT_GROUP_MODE_* flags (INGRESS/EGRESS)
 *\param    total_counters [IN]   Total Counters for Stat Flex Group Mode
 *\param    num_selectors [IN]   Number of Selectors for Stat Flex Group Mode
 *\param    attr_selectors [IN]   Attribute Selectors for Stat Flex Group Mode
 *\param    mode_id [OUT]   Created Mode Identifier for Stat Flex Group Mode
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_stat_group_mode_id_create(
    int unit, 
    uint32 flags, 
    uint32 total_counters, 
    uint32 num_selectors, 
    opennsl_stat_group_mode_attr_selector_t *attr_selectors, 
    uint32 *mode_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Associate an accounting object to customized group mode.
 *
 *\description This API Associate an accounting object to customized group mode
 *          and make system ready for further stat collection action.
 *
 *\param    unit [IN]   Unit number.
 *\param    mode_id [IN]   Created Mode Identifier for Stat Flex Group Mode
 *\param    object [IN]   Accounting Object
 *\param    stat_counter_id [OUT]
 *\param    num_entries [OUT]   Number of Counter entries created
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_stat_custom_group_create(
    int unit, 
    uint32 mode_id, 
    opennsl_stat_object_t object, 
    uint32 *stat_counter_id, 
    uint32 *num_entries) LIB_DLL_EXPORTED ;

#endif /* __OPENNSL_STATX_H__ */
/*@}*/
