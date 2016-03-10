/** \addtogroup multicast Multicast Traffic Management
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
 * \file			multicastX.h
 ******************************************************************************/

#ifndef __OPENNSL_MULTICASTX_H__
#define __OPENNSL_MULTICASTX_H__

#include <opennsl/types.h>

/***************************************************************************//** 
 *\brief Set/get miscellaneous per multicast group controls.
 *
 *\description Sets/gets miscellaneous per multicast group parameters.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Multicast group ID
 *\param    type [IN]   Multicast control parameter (see =multicast_controls)
 *\param    arg [IN]   (for _set) A parameter whose meaning is  dependent on
 *          'type'
 *
 *\retval    OPENNSL_E_UNAVAIL Feature not supported.
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_multicast_control_set(
    int unit, 
    opennsl_multicast_t group, 
    opennsl_multicast_control_t type, 
    int arg) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set/get miscellaneous per multicast group controls.
 *
 *\description Sets/gets miscellaneous per multicast group parameters.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Multicast group ID
 *\param    type [IN]   Multicast control parameter (see =multicast_controls)
 *\param    arg [OUT]   (for _set) A parameter whose meaning is  dependent on
 *          'type'
 *
 *\retval    OPENNSL_E_UNAVAIL Feature not supported.
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_multicast_control_get(
    int unit, 
    opennsl_multicast_t group, 
    opennsl_multicast_control_t type, 
    int *arg) LIB_DLL_EXPORTED ;

#endif /* __OPENNSL_MULTICASTX_H__ */
/*@}*/
