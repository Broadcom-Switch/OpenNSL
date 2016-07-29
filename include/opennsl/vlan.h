/** \addtogroup vlan Virtual LAN Management
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
 * \file			vlan.h
 ******************************************************************************/

#ifndef __OPENNSL_VLAN_H__
#define __OPENNSL_VLAN_H__

#include <opennsl/types.h>
#include <opennsl/port.h>

/** Initialize a VLAN data information structure. */
typedef struct opennsl_vlan_data_s {
    opennsl_vlan_t vlan_tag;        
    opennsl_pbmp_t port_bitmap;     
    opennsl_pbmp_t ut_port_bitmap;  
} opennsl_vlan_data_t;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Allocate and configure a VLAN on the OPENNSL device.
 *
 *\description Create a new VLAN with the given ID. This routine will satisfy
 *          requests until the number of VLANs supported in the underlying
 *          hardware is reached. The VLAN is placed in the default STG and can
 *          be reassigned later. To deallocate the VLAN, opennsl_vlan_destroy
 *          must be used, not opennsl_vlan_init, since opennsl_vlan_init does
 *          not remove the VLAN from its STG. See =switch for default
 *          multicast flood mode configuration.
 *
 *\param    unit [IN]   Unit number.
 *\param    vid [IN]   VLAN ID
 *
 *\retval    OPENNSL_E_NONE Success or when the default VLAN is created, even if it
 *          already exists.
 *\retval    OPENNSL_E_XXX
 *\retval    OPENNSL_E_EXISTS VLAN ID already in use.
 ******************************************************************************/
extern int opennsl_vlan_create(
    int unit, 
    opennsl_vlan_t vid) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Deallocate VLAN from the OPENNSL device.
 *
 *\description Remove references to previously created VLAN. Ports whose
 *          port-based VLAN is the destroyed VID are given the default VID.
 *
 *\param    unit [IN]   Unit number.
 *\param    vid [IN]   VLAN ID
 *
 *\retval    OPENNSL_E_BADID Cannot remove default VLAN
 *\retval    OPENNSL_E_NOT_FOUND VLAN ID not in use
 *\retval    OPENNSL_E_XXX
 *\retval    
 ******************************************************************************/
extern int opennsl_vlan_destroy(
    int unit, 
    opennsl_vlan_t vid) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroy all VLANs except the default VLAN.
 *
 *\description Destroy all VLANs except the default VLAN.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vlan_destroy_all(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Add ports to the specified VLAN.
 *
 *\description Adds the selected ports to the VLAN.  The port bitmap specifies
 *          ALL ports to be added to the VLAN. The untagged bitmap specifies
 *          the subset of these ports that are untagged. If the port is
 *          already a member of the VLAN then the tagged attribute gets
 *          updated. Packets sent from the untagged ports will not contain the
 *          802.1Q tag header.  .
 *
 *\param    unit [IN]   Unit number.
 *\param    vid [IN]   VLAN ID
 *\param    pbmp [IN]   Port bitmap for members of VLAN
 *\param    ubmp [IN]   Port bitmap for untagged members of VLAN
 *
 *\retval    OPENNSL_E_NOT_FOUND VLAN ID not in use
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vlan_port_add(
    int unit, 
    opennsl_vlan_t vid, 
    opennsl_pbmp_t pbmp, 
    opennsl_pbmp_t ubmp) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Remove ports from a specified VLAN.
 *
 *\description Removes the specified ports from the given VLAN. If some or all of
 *          the requested ports are not already members of the VLAN, the
 *          routine returns OPENNSL_E_NOT_FOUND.
 *
 *\param    unit [IN]   Unit number.
 *\param    vid [IN]   VLAN ID
 *\param    pbmp [IN]   Port bitmap for members of VLAN
 *
 *\retval    OPENNSL_E_NOT_FOUND VLAN ID not in use
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vlan_port_remove(
    int unit, 
    opennsl_vlan_t vid, 
    opennsl_pbmp_t pbmp) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Add a virtual or physical port to the specified VLAN.
 *
 *\description Adds the given port to the VLAN. For network switch and network
 *          switch, the port can be either a WLAN virtual port or a regular
 *          physical port. For network switch, the port can be a layer 2
 *          logical port or a regular physical port. WLAN virtual ports or
 *          layer 2 logical ports that are members of a VLAN will receive
 *          broadcast, multicast and unknown unicast packets that are flooded
 *          to the VLAN. For applications that require different recipients
 *          for broadcast, unknown multicast and unknown unicast, the
 *          different multicast groups can be set using the
 *          =opennsl_vlan_control_vlan_set API.
 *          Virtual Port(VP) can be added to the vlan through this API to
 *          obtain the vlan  membership. Due to the large amount of virtual
 *          port number, unlike physical port,  switch hardware can not uses a
 *          port bitmap in the vlan table entry to represent  the vlan
 *          membership. Instead the hardware uses two different methods: VP
 *          group  and hash table to provide VP vlan membership. The hash
 *          table method is only  available on opennsl56850 and later switch
 *          devices.
 *          The VP group referring as indirect vlan membership method is to
 *          associate a group of virtual port with a VP group and then the VP
 *          group establishes the membership  with the vlan. The hardware uses
 *          the VLAN_MEMBERSHIP_PROFILE field in the SOURCE_VP table to
 *          associate a virtual port with the VP group, and use the
 *          VP_GROUP_BITMAP  field in the vlan table to establish the vlan
 *          membership with the VP group.   This method works well when a
 *          group of VPs belong to the same number of vlans such as in the
 *          following case:.
 *
 *\param    unit [IN]   Unit number.
 *\param    vlan [IN]   VLAN ID
 *\param    port [IN]   Virtual or physical port to be added to the VLAN
 *\param    flags [IN]   Control flags. See =OPENNSL_VLAN_PORT_t
 *
 *\retval    OPENNSL_E_NOT_FOUND VLAN ID not in use
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vlan_gport_add(
    int unit, 
    opennsl_vlan_t vlan, 
    opennsl_gport_t port, 
    int flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Remove a virtual or physical port from the specified VLAN.
 *
 *\description Removes the given port to the VLAN. For network switch and network
 *          switch, the port can be either a WLAN virtual port or a regular
 *          physical port. For network switch, the port can be a layer 2
 *          logical port or a regular physical port.
 *
 *\param    unit [IN]   Unit number.
 *\param    vlan [IN]   VLAN ID
 *\param    port [IN]   Virtual or physical port to be removed from the VLAN
 *
 *\retval    OPENNSL_E_NOT_FOUND VLAN ID not in use
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vlan_gport_delete(
    int unit, 
    opennsl_vlan_t vlan, 
    opennsl_gport_t port) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Removes all virtual and physical port from the specified VLAN.
 *
 *\description Removes all virtual and physical ports from the specified VLAN.
 *
 *\param    unit [IN]   Unit number.
 *\param    vlan [IN]   VLAN ID
 *
 *\retval    OPENNSL_E_NOT_FOUND VLAN ID not in use
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vlan_gport_delete_all(
    int unit, 
    opennsl_vlan_t vlan) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get a virtual or physical port from the specified VLAN.
 *
 *\description Checks whether the given port is a member of the VLAN. For network
 *          switch and network switch,  the port can be either a WLAN virtual
 *          port or a regular physical port. For network switch, the port can
 *          be a layer 2 logical port or a regular physical port.
 *
 *\param    unit [IN]   Unit number.
 *\param    vlan [IN]   VLAN ID
 *\param    port [IN]   Virtual or physical port to get VLAN information
 *\param    flags [OUT]   Control flags. See =OPENNSL_VLAN_PORT_t
 *
 *\retval    OPENNSL_E_NOT_FOUND VLAN ID not in use or port is not a member
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vlan_gport_get(
    int unit, 
    opennsl_vlan_t vlan, 
    opennsl_gport_t port, 
    int *flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Returns an array of defined VLANs and their port bitmaps. If by pbmp,
 *       then only VLANs which contain at least one of the specified ports are
 *       listed.
 *
 *\description Returns an array of defined VLANs and their port bitmaps. If by
 *          pbmp, only VLANs which contain at least one of the specified ports
 *          are listed. The array is allocated by this routine and the pointer
 *          to the list is returned in *listp. This array should be destroyed
 *          by opennsl_vlan_list_destroy when it is no longer needed. See
 *          =vlan_data .
 *
 *\param    unit [IN]   Unit number.
 *\param    listp [OUT]   Place where pointer to return array will be stored,
 *          which will be NULL if there are zero VLANs defined.
 *\param    countp [OUT]   Place where number of entries in array will be stored,
 *          which will be 0 if there are zero VLANs defined.
 *
 *\retval    OPENNSL_E_MEMORY Out of system memory.
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vlan_list(
    int unit, 
    opennsl_vlan_data_t **listp, 
    int *countp) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroy a list returned by opennsl_vlan_list.
 *
 *\description Deallocate the array created by opennsl_vlan_list or
 *          opennsl_vlan_list_by_pbmp. Also works for the zero-VLAN case (NULL
 *          list).
 *
 *\param    unit [IN]   Unit number.
 *\param    list [IN]   List returned by opennsl_vlan_list
 *\param    count [IN]   Count returned by opennsl_vlan_list
 *
 *\retval    OPENNSL_E_NONE Success.
 ******************************************************************************/
extern int opennsl_vlan_list_destroy(
    int unit, 
    opennsl_vlan_data_t *list, 
    int count) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the default VLAN ID.
 *
 *\description Retrieve the current default VLAN ID.
 *
 *\param    unit [IN]   Unit number.
 *\param    vid_ptr [OUT]   Current default VLAN ID
 *
 *\retval    OPENNSL_E_NONE Success.
 ******************************************************************************/
extern int opennsl_vlan_default_get(
    int unit, 
    opennsl_vlan_t *vid_ptr) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set the default VLAN ID.
 *
 *\description Change the default VLAN to the specified VLAN ID. The new default
 *          VLAN must already exist. .
 *
 *\param    unit [IN]   Unit number.
 *\param    vid [IN]   New default VLAN ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vlan_default_set(
    int unit, 
    opennsl_vlan_t vid) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/** opennsl_vlan_control_t */
typedef enum opennsl_vlan_control_e {
    opennslVlanDropUnknown = 0,         /**< Drop unknown/FFF VLAN pkts or send to
                                           CPU. */
    opennslVlanShared = 3,              /**< Shared vs. Independent VLAN Learning. */
    opennslVlanSharedID = 4,            /**< Shared Learning VLAN ID. */
    opennslVlanTranslate = 5,           /**< Chip is in VLAN translate mode. */
    opennslVlanIgnorePktTag = 6,        /**< Ignore Packet VLAN tag. Treat packet
                                           as untagged. */
    opennslVlanMemberMismatchToCpu = 21 /**< Packets' incoming port is not the
                                           member of the VLAN are sent to CPU
                                           when set to 1. */
} opennsl_vlan_control_t;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Set/get miscellaneous VLAN-specific chip options.
 *
 *\description Sets/gets miscellaneous VLAN-specific chip options. The options
 *          are from the VLAN Control selection =vlan_ctrl.
 *
 *\param    unit [IN]   Unit number.
 *\param    type [IN]   A value from the opennsl_vlan_control_t enumerated list
 *\param    arg [IN]   (for _set) A parameter whose meaning is  dependent on
 *          'type'
 *
 *\retval    OPENNSL_E_UNAVAIL Feature not supported.
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vlan_control_set(
    int unit, 
    opennsl_vlan_control_t type, 
    int arg) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/** opennsl_vlan_control_port_t */
typedef enum opennsl_vlan_control_port_e {
    opennslVlanTranslateIngressEnable = 2, 
    opennslVlanTranslateIngressMissDrop = 4, 
    opennslVlanTranslateEgressEnable = 5, 
    opennslVlanTranslateEgressMissDrop = 6, 
} opennsl_vlan_control_port_t;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Set/get miscellaneous port-specific VLAN options.
 *
 *\description Sets/gets miscellaneous port-specific VLAN options. The options
 *          are from the VLAN Control Port selection =vlan_ctrl_port .
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    type [IN]   A value from the opennsl_vlan_control_port_t enumerated
 *          list
 *\param    arg [IN]   (for _set) A parameter whose meaning is  dependent on
 *          'type'
 *
 *\retval    OPENNSL_E_UNAVAIL Feature not supported.
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vlan_control_port_set(
    int unit, 
    int port, 
    opennsl_vlan_control_port_t type, 
    int arg) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#if defined(INCLUDE_L3)
#endif
#if defined(INCLUDE_L3)
#endif
#include <opennsl/vlanX.h>
#endif /* __OPENNSL_VLAN_H__ */
/*@}*/
