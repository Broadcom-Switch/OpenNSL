/** \addtogroup vswitch Virtual Switch
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
 * \file			vswitchX.h
 ******************************************************************************/

#ifndef __OPENNSL_VSWITCHX_H__
#define __OPENNSL_VSWITCHX_H__

#include <opennsl/types.h>
#include <opennsl/policer.h>
#include <opennsl/port.h>

/***************************************************************************//** 
 *\brief Initialize vswitch module.
 *
 *\description This API should be called first, before calling any other APIs in
 *          this module. It is usually automatically called as a part of
 *          =opennsl_init .
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vswitch_init(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Detach vswitch module.
 *
 *\description Cleans up any data structures used by the vswitch module. Usually
 *          called as a part of =opennsl_detach .
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vswitch_detach(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create a Virtual Switching Instance.
 *
 *\description Create a Virtual Switching Instance.
 *
 *\param    unit [IN]   Unit number.
 *\param    vsi [OUT]   Virtual Switching Instance
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vswitch_create(
    int unit, 
    opennsl_vlan_t *vsi) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create a Virtual Switching Instance, with a specified ID.
 *
 *\description Create a Virtual Switching Instance, with the specified ID.
 *
 *\param    unit [IN]   Unit number.
 *\param    vsi [IN]   Virtual Switching Instance
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vswitch_create_with_id(
    int unit, 
    opennsl_vlan_t vsi) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroy a Virtual Switching Instance.
 *
 *\description Destroy the specified Virtual Switching Instance.
 *
 *\param    unit [IN]   Unit number.
 *\param    vsi [IN]   Virtual Switching Instance
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vswitch_destroy(
    int unit, 
    opennsl_vlan_t vsi) LIB_DLL_EXPORTED ;

typedef int (*opennsl_vswitch_port_traverse_cb)(
    int unit, 
    opennsl_vlan_t vsi, 
    opennsl_gport_t port, 
    void *user_data);

/***************************************************************************//** 
 *\brief Traverse existing ports on vswitch.
 *
 *\description Traverse existing ports on vswitch .
 *
 *\param    unit [IN]   Unit number.
 *\param    vsi [IN]   Virtual Switching Instance
 *\param    cb [IN]   Vswitch port traverse prototype
 *\param    user_data [IN]   Cookie value supplied by caller during registration
 *          of the callout
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_vswitch_port_traverse(
    int unit, 
    opennsl_vlan_t vsi, 
    opennsl_vswitch_port_traverse_cb cb, 
    void *user_data) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Add a logical port to the specified virtual switching instance.
 *
 *\description Add a logical port to the specified virtual switching instance.
 *
 *\param    unit [IN]   Unit number.
 *\param    vsi [IN]   Virtual Switching Instance
 *\param    port [IN]   Port number
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vswitch_port_add(
    int unit, 
    opennsl_vlan_t vsi, 
    opennsl_gport_t port) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Remove a logical port from the specified virtual switching instance.
 *
 *\description Remove the specified logical port from the specified virtual
 *          switching instance.
 *
 *\param    unit [IN]   Unit number.
 *\param    vsi [IN]   Virtual Switching Instance
 *\param    port [IN]   Port number
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vswitch_port_delete(
    int unit, 
    opennsl_vlan_t vsi, 
    opennsl_gport_t port) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Remove all logical port members from the specified virtual switching
 *       instance.
 *
 *\description Remove all logical port members from the specified virtual
 *          switching instance.
 *
 *\param    unit [IN]   Unit number.
 *\param    vsi [IN]   Virtual Switching Instance
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vswitch_port_delete_all(
    int unit, 
    opennsl_vlan_t vsi) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the virtual switching instance of which the specified logical port
 *       is a member.
 *
 *\description Get the virtual switching instance of which the specified logical
 *          port is a member.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Port number
 *\param    vsi [OUT]   Virtual Switching Instance
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vswitch_port_get(
    int unit, 
    opennsl_gport_t port, 
    opennsl_vlan_t *vsi) LIB_DLL_EXPORTED ;

/** L3 tunneling initiator. */
typedef struct opennsl_vswitch_cross_connect_s {
    opennsl_gport_t port1;  /**< First gport in cross connect. */
    opennsl_gport_t port2;  /**< Second gport in cross connect. */
    int encap1;             /**< First gport encap id. */
    int encap2;             /**< Second gport encap id. */
    uint32 flags;           /**< OPENNSL_VSWITCH_CROSS_CONNECT_XXX flags. */
} opennsl_vswitch_cross_connect_t;

/***************************************************************************//** 
 *
 *
 *\param    cross_connect [IN,OUT]
 *
 *\returns  Nothing
 ******************************************************************************/
extern void opennsl_vswitch_cross_connect_t_init(
    opennsl_vswitch_cross_connect_t *cross_connect) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Attach two given logical ports in a point-to-point service.
 *
 *\description Attach two given logical ports in a point-to-point service. You
 *          can also use the following flags:.
 *
 *\param    unit [IN]   Unit number.
 *\param    gports [IN]   Logical ports
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vswitch_cross_connect_add(
    int unit, 
    opennsl_vswitch_cross_connect_t *gports) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Remove attachment between the given logical ports.
 *
 *\description Remove attachment between the given logical ports.
 *
 *\param    unit [IN]   Unit number.
 *\param    gports [IN]   Logical ports
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vswitch_cross_connect_delete(
    int unit, 
    opennsl_vswitch_cross_connect_t *gports) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete all point-to-point services.
 *
 *\description Delete all point-to-point services.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vswitch_cross_connect_delete_all(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Return peer, if protected return primary port, invalid gport is
 *       populated.
 *
 *\description Return peer, if protected return primary port, invalid gport is
 *          populated.
 *
 *\param    unit [IN]   Unit number.
 *\param    gports [IN,OUT]   Logical ports
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vswitch_cross_connect_get(
    int unit, 
    opennsl_vswitch_cross_connect_t *gports) LIB_DLL_EXPORTED ;

#endif /* __OPENNSL_VSWITCHX_H__ */
/*@}*/
