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
 *\brief Get the multicast encapsulation ID for VXLAN replication.
 *
 *\description Get the multicast encapsulation ID for VXLAN replication. The
 *          encapsulation ID is an opaque object passed in to
 *          opennsl_multicast_egress_* APIs when adding/removing ports to a
 *          multicast group.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Multicast group ID
 *\param    port [IN]   Physical GPORT ID
 *\param    vxlan_port_id [IN]   VXLAN GPORT ID
 *\param    encap_id [OUT]   Encapsulation ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_multicast_vxlan_encap_get(
    int unit, 
    opennsl_multicast_t group, 
    opennsl_gport_t port, 
    opennsl_gport_t vxlan_port_id, 
    opennsl_if_t *encap_id) LIB_DLL_EXPORTED ;

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
