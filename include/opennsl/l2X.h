/** \addtogroup l2 Layer 2 Address Management
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
 * \file			l2X.h
 ******************************************************************************/

#ifndef __OPENNSL_L2X_H__
#define __OPENNSL_L2X_H__

#include <opennsl/types.h>

#define OPENNSL_L2_LEARN_LIMIT_SYSTEM   0x00000001 /**< Limit is system wide. */
/** L2 learn limit structure. */
typedef struct opennsl_l2_learn_limit_s {
    uint32 flags;                   /**< OPENNSL_L2_LEARN_LIMIT_xxx actions and
                                       qualifiers. */
    int limit;                      /**< Maximum number of learned entries, -1 for
                                       unlimited. */
} opennsl_l2_learn_limit_t;

/***************************************************************************//** 
 *\brief Initialize an L2 learn limit structure.
 *
 *\description Initialize an L2 learn limit structure opennsl_l2_learn_limit_t
 *          zeroing all fields.
 *
 *\param    limit [IN,OUT]   Pointer to L2 learn limit structure to initialize
 *
 *\retval    Nothing
 ******************************************************************************/
extern void opennsl_l2_learn_limit_t_init(
    opennsl_l2_learn_limit_t *limit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set/Get L2 addresses learn limit.
 *
 *\description Set/Get L2 learned address limit.
 *          Use OPENNSL_L2_LEARN_LIMIT_SYSTEM or combination of
 *          OPENNSL_L2_LEARN_LIMIT_VLAN, OPENNSL_L2_LEARN_LIMIT_PORT, and
 *          OPENNSL_L2_LEARN_LIMIT_TRUNK in flags of opennsl_l2_learn_limit_t
 *          structure to indicate whether the limit is applied to system wide,
 *          per-VLAN, per-port, or per-trunk.
 *          For devices which do not support per-VLAN learn limits, only the
 *          system wide, per-port, and per-trunk can be configured.
 *          Use flags to specify the action to be taken if learned L2 address
 *          exceeds the specified limit. OPENNSL_L2_LEARN_LIMIT_ACTION_PREFER
 *          flag indicates that system wide limit actions should be used when
 *          both system wide and a non-system wide limit is exceeded. This
 *          flag is not longer supported starting form network switch device
 *          To remove a configured learn limit, specify the appropriate flags
 *          along with a negative value for the limit field of the
 *          opennsl_l2_learn_limit_t structure.
 *          For the feature to function properly, following requirements must
 *          be fulfilled:
 *          When port moves to trunk, all MAC addresses previously learned on
 *          that port should be deleted. When port moves out of a trunk and it
 *          is last port or trunk  is destroyed, all MAC addresses previously
 *          learned on that trunk should be deleted.
 *          It is recommended that all MAC addresses deletion will be done
 *          using the following sequence: a. Setting the limit on the resource
 *          to 0, to disable further learning b. Delete all associated MAC
 *          addresses by calling opennsl_l2_addr_delete_by_port or
 *          opennsl_l2_addr_delete_by_trunk.
 *
 *\param    unit [IN]   Unit number.
 *\param    limit [IN]   (for _set) Pointer to L2 address learn limit info
 *          structure
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l2_learn_limit_set(
    int unit, 
    opennsl_l2_learn_limit_t *limit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set/Get L2 addresses learn limit.
 *
 *\description Set/Get L2 learned address limit.
 *          Use OPENNSL_L2_LEARN_LIMIT_SYSTEM or combination of
 *          OPENNSL_L2_LEARN_LIMIT_VLAN, OPENNSL_L2_LEARN_LIMIT_PORT, and
 *          OPENNSL_L2_LEARN_LIMIT_TRUNK in flags of opennsl_l2_learn_limit_t
 *          structure to indicate whether the limit is applied to system wide,
 *          per-VLAN, per-port, or per-trunk.
 *          For devices which do not support per-VLAN learn limits, only the
 *          system wide, per-port, and per-trunk can be configured.
 *          Use flags to specify the action to be taken if learned L2 address
 *          exceeds the specified limit. OPENNSL_L2_LEARN_LIMIT_ACTION_PREFER
 *          flag indicates that system wide limit actions should be used when
 *          both system wide and a non-system wide limit is exceeded. This
 *          flag is not longer supported starting form network switch device
 *          To remove a configured learn limit, specify the appropriate flags
 *          along with a negative value for the limit field of the
 *          opennsl_l2_learn_limit_t structure.
 *          For the feature to function properly, following requirements must
 *          be fulfilled:
 *          When port moves to trunk, all MAC addresses previously learned on
 *          that port should be deleted. When port moves out of a trunk and it
 *          is last port or trunk  is destroyed, all MAC addresses previously
 *          learned on that trunk should be deleted.
 *          It is recommended that all MAC addresses deletion will be done
 *          using the following sequence: a. Setting the limit on the resource
 *          to 0, to disable further learning b. Delete all associated MAC
 *          addresses by calling opennsl_l2_addr_delete_by_port or
 *          opennsl_l2_addr_delete_by_trunk.
 *
 *\param    unit [IN]   Unit number.
 *\param    limit [IN,OUT]   (for _set) Pointer to L2 address learn limit info
 *          structure
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l2_learn_limit_get(
    int unit, 
    opennsl_l2_learn_limit_t *limit) LIB_DLL_EXPORTED ;

#endif /* __OPENNSL_L2X_H__ */
/*@}*/
