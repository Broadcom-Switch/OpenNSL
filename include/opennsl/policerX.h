/** \addtogroup policer Policer
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
 * \file			policerX.h
 ******************************************************************************/

#ifndef __OPENNSL_POLICERX_H__
#define __OPENNSL_POLICERX_H__

#include <opennsl/types.h>

/** Policer Modes. */
typedef enum opennsl_policer_mode_e {
    opennslPolicerModeSrTcm = 0,        /**< RFC 2697 */
    opennslPolicerModeCommitted = 1,    
    opennslPolicerModePeak = 2,         
    opennslPolicerModeTrTcm = 3,        /**< RFC 2698 */
    opennslPolicerModeTrTcmDs = 4,      /**< RFC 4115, TrTcmModified */
} opennsl_policer_mode_t;

#define OPENNSL_POLICER_COLOR_BLIND     0x00000004 
#define OPENNSL_POLICER_MODE_BYTES      0x00000040 
#define OPENNSL_POLICER_MODE_PACKETS    0x00000080 
typedef struct opennsl_policer_config_s {
    uint32 flags;                       /**< OPENNSL_POLICER_* Flags. */
    opennsl_policer_mode_t mode;        /**< Policer mode. */
    uint32 ckbits_sec;                  /**< Committed rate (kbits per sec). */
    uint32 ckbits_burst;                /**< Committed burst size (kbits). */
    uint32 pkbits_sec;                  /**< Peak rate (kbits per sec). */
    uint32 max_pkbits_sec;              /**< Maximum Peak rate (kbits per sec),
                                           Applicable only for cascade mode. */
    uint32 pkbits_burst;                /**< Peak burst size (kbits). */
} opennsl_policer_config_t;

/***************************************************************************//** 
 *\brief Initialize a policer configuration structure.
 *
 *\description Initialize a policer configuration structure.
 *
 *\param    pol_cfg [IN,OUT]   Pointer to policer configuration structure to
 *          initialize.
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_policer_config_t_init(
    opennsl_policer_config_t *pol_cfg) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create a policer entry.
 *
 *\description Create a policer entry.
 *
 *\param    unit [IN]   Unit number.
 *\param    pol_cfg [IN]   Policer config
 *\param    policer_id [IN,OUT]   Policer ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_policer_create(
    int unit, 
    opennsl_policer_config_t *pol_cfg, 
    opennsl_policer_t *policer_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroy a policer entry.
 *
 *\description Destroy a policer entry. A policer entry has the following
 *          restrictions before it can be destroyed.
 *          1. The Policer should be detached from all the entries 2.
 *          Detaching the policer from the entry does not clear the policer
 *          and meter    entries from the hardware. So, the entry must be
 *          re-installed or removed    before policer destroy.
 *
 *\param    unit [IN]   Unit number.
 *\param    policer_id [IN]   Policer ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_policer_destroy(
    int unit, 
    opennsl_policer_t policer_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set the config settings for a policer entry.
 *
 *\description Set the config settings for a policer entry.
 *
 *\param    unit [IN]   Unit number.
 *\param    policer_id [IN]   Policer ID.
 *\param    pol_cfg [IN]   Policer configuration.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_policer_set(
    int unit, 
    opennsl_policer_t policer_id, 
    opennsl_policer_config_t *pol_cfg) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the config settings for a policer entry.
 *
 *\description Get the config settings for a policer entry.
 *
 *\param    unit [IN]   Unit number.
 *\param    policer_id [IN]   Policer ID.
 *\param    pol_cfg [OUT]   Policer configuration.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_policer_get(
    int unit, 
    opennsl_policer_t policer_id, 
    opennsl_policer_config_t *pol_cfg) LIB_DLL_EXPORTED ;

#endif /* __OPENNSL_POLICERX_H__ */
/*@}*/
