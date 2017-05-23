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

/***************************************************************************//** 
 *\brief Retrieves a list of the member ports of an existing VLAN.
 *
 *\description Retrieves a list of the member ports of an existing VLAN.
 *
 *\param    unit [IN]   Unit number.
 *\param    vid [IN]   VLAN ID
 *\param    pbmp [OUT]   Port bitmap for members of VLAN
 *\param    ubmp [OUT]   Port bitmap for untagged members of VLAN
 *
 *\retval    OPENNSL_E_NOT_FOUND VLAN ID not in use
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vlan_port_get(
    int unit, 
    opennsl_vlan_t vid, 
    opennsl_pbmp_t *pbmp, 
    opennsl_pbmp_t *ubmp) LIB_DLL_EXPORTED ;

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

/***************************************************************************//** 
 *\brief Initialize a VLAN tag action set structure.
 *
 *\description Initializes a VLAN tag action set structure to default values.
 *          This function should be used to initialize any VLAN tag action set
 *          structure prior to filling it out and passing it to an API
 *          function. This ensures that subsequent API releases may add new
 *          structure members to the opennsl_vlan_action_set_t structure, and
 *          opennsl_vlan_action_set_t_init will initialize the new members to
 *          correct default values.
 *          switch family?III devices that support the VLAN Action APIs can
 *          specify actions for a packet's inner and outer VLAN tag (add,
 *          delete, replace, copy, or do nothing). Depending on the number of
 *          VLAN tags in a packet along with the TPID value(s), a packet can
 *          be described as double-tagged, outer-tagged, inner-tagged, or
 *          untagged. In addition, VLAN tags with VLAN ID equal to 0 are
 *          referred to as 'priority-tagged'. Separate VLAN actions can be
 *          specified each of these types.
 *          The structure opennsl_vlan_action_set_t is used to specify each
 *          action:.
 *
 *\param    action [IN,OUT]   Pointer to VLAN tag action set structure to
 *          initialize.
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_vlan_action_set_t_init(
    opennsl_vlan_action_set_t *action) LIB_DLL_EXPORTED ;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Add an entry to the egress VLAN Translation table and assign VLAN
 *       actions.
 *
 *\description Add an entry to the egress VLAN Translation table and assign VLAN
 *          actions.
 *          The port class is a per-port property which is set using
 *          =opennsl_port_class_set along with
 *          opennslPortClassVlanTranslateEgress. This allows the same egress
 *          VLAN translation entry to match for all ports with the same port
 *          class.
 *          For devices that support the VLAN action APIs, within the system,
 *          a packet is either double-tagged or outer-tagged (that is, it
 *          always  has an outer tag). For double-tagged packets, the outer
 *          tag and inner tag VLAN IDs from the packet are used as the key.
 *          For outer-tagged packets, the outer tag VLAN ID is used from the
 *          packet and the inner VLAN ID is set to zero as the key. The only
 *          actions that can be set for this API are the double-tag and
 *          outer-tag actions. For systems  that support Destination Virtual
 *          Ports such could be specified in  a appropriate GPORT format as
 *          port_class parameter and will be recognized by the  API to perform
 *          matching based on Destination Virtual Port as a lookup key. For
 *          devices that support explicit second egress vlan translation
 *          lookup (key configured using =opennsl_vlan_control_port_set API
 *          with opennslVlanPortTranslateEgressKeySecond control), note that
 *          only the class-id in the resulting entry of second lookup will be
 *          used.
 *          Note: For GPORT based egress vlan translation entries,.
 *
 *\param    unit [IN]   Unit number.
 *\param    port_class [IN]   Port class
 *\param    outer_vlan [IN]   Outer VLAN ID
 *\param    inner_vlan [IN]   Inner VLAN ID
 *\param    action [IN]   VLAN tag action set, as specified in
 *          =OPENNSL_VLAN_ACTION_SET_t
 *
 *\retval    OPENNSL_E_UNAVAIL Not supported.
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vlan_translate_egress_action_add(
    int unit, 
    int port_class, 
    opennsl_vlan_t outer_vlan, 
    opennsl_vlan_t inner_vlan, 
    opennsl_vlan_action_set_t *action) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the assigned VLAN actions for egress VLAN translation on the given
 *       port class and VLAN tags.
 *
 *\description Get the assigned VLAN actions for egress VLAN translation on the
 *          given port class and VLAN tags.
 *
 *\param    unit [IN]   Unit number.
 *\param    port_class [IN]   Port class
 *\param    outer_vlan [IN]   Outer VLAN ID
 *\param    inner_vlan [IN]   Inner VLAN ID
 *\param    action [IN,OUT]   VLAN tag action set, as specified in
 *          =OPENNSL_VLAN_ACTION_SET_t
 *
 *\retval    OPENNSL_E_UNAVAIL Not supported.
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vlan_translate_egress_action_get(
    int unit, 
    int port_class, 
    opennsl_vlan_t outer_vlan, 
    opennsl_vlan_t inner_vlan, 
    opennsl_vlan_action_set_t *action) LIB_DLL_EXPORTED ;

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
 *          Notes: (1) When setting egress vlan translation lookup key for
 *          virtual ports, control type should be one of
 *          {opennslVlanPortTranslateEgressKey or
 *          opennslVlanPortTranslateEgressKeyFirst}. Also, the argument
 *          specifying key type in case of virtual ports should be one of
 *          {opennslVlanTranslateEgressKeyVpn,
 *          opennslVlanTranslateEgressKeyVpnGport,
 *          opennslVlanTranslateEgressKeyVpnGportGroup}. (2) When setting the
 *          key for explicit second vlan translation lookup using
 *          opennslVlanPortTranslateEgressKeySecond, the argument specifying
 *          key type should be one of
 *          {opennslVlanTranslateEgressKeyPortGroupDouble,
 *          opennslVlanTranslateEgressKeyPortDouble}.
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

#define OPENNSL_VLAN_PORT_REPLACE           0x00000001 /**< Replace existing
                                                          entry. */
#define OPENNSL_VLAN_PORT_WITH_ID           0x00000002 /**< Add using the
                                                          specified ID. */
#define OPENNSL_VLAN_PORT_INNER_VLAN_PRESERVE 0x00000004 /**< Preserve the inner
                                                          VLAN tag (by default
                                                          it is stripped). */
#define OPENNSL_VLAN_PORT_OUTER_VLAN_PRESERVE 0x00000100 /**< Preserve the outer
                                                          VLAN tag (by default
                                                          it is stripped). */
/** Logical layer 2 port match criteria */
typedef enum opennsl_vlan_port_match_e {
    OPENNSL_VLAN_PORT_MATCH_INVALID = 0, /**< Illegal. */
    OPENNSL_VLAN_PORT_MATCH_NONE = 1,   /**< No source match criteria. */
    OPENNSL_VLAN_PORT_MATCH_PORT = 2,   /**< {Module, Port} or Trunk. */
    OPENNSL_VLAN_PORT_MATCH_PORT_VLAN = 3, /**< Mod/port/trunk + outer VLAN. */
} opennsl_vlan_port_match_t;

/** Layer 2 Logical port type */
typedef struct opennsl_vlan_port_s {
    opennsl_vlan_port_match_t criteria; /**< Match criteria. */
    uint32 flags;                       /**< OPENNSL_VLAN_PORT_xxx. */
    opennsl_vlan_t vsi;                 /**< Populated for opennsl_vlan_port_find
                                           only */
    opennsl_vlan_t match_vlan;          /**< Outer VLAN ID to match. */
    opennsl_vlan_t match_inner_vlan;    /**< Inner VLAN ID to match. */
    opennsl_gport_t port;               /**< Gport: local or remote Physical or
                                           logical gport. */
    opennsl_vlan_t egress_vlan;         /**< Egress Outer VLAN or SD-TAG VLAN ID. */
    opennsl_gport_t vlan_port_id;       /**< GPORT identifier */
} opennsl_vlan_port_t;

/***************************************************************************//** 
 *\brief Initialize the VLAN port structure.
 *
 *\description This API initializes the opennsl_vlan_port_t structure.
 *
 *\param    vlan_port [IN,OUT]   Layer 2 Logical port.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern void opennsl_vlan_port_t_init(
    opennsl_vlan_port_t *vlan_port) LIB_DLL_EXPORTED ;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Create a layer 2 logical port.
 *
 *\description Create a Layer 2 Logical Port based on the parameters passed via
 *          vlan_port structure.   Uses the ID in the vlan_port_id field of
 *          the opennsl_vlan_port_t if the OPENNSL_VLAN_PORT_WITH_ID flag is
 *          specified, otherwise it places the new ID into the vlan_port_id
 *          field of the opennsl_vlan_port_t.  This should be called on the
 *          home unit (where the logical port will physically exist) first,
 *          then the opennsl_vlan_port_t used as modified by this call to
 *          reproduce the data to any other units that may need to send to the
 *          logical port.
 *
 *\param    unit [IN]   Unit number.
 *\param    vlan_port [IN,OUT]   Layer 2 Logical port.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vlan_port_create(
    int unit, 
    opennsl_vlan_port_t *vlan_port) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroy a layer 2 logical port.
 *
 *\description Destroy the given Layer 2 Logical Port.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   Gport
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vlan_port_destroy(
    int unit, 
    opennsl_gport_t gport) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get/find a layer 2 logical port given the GPORT ID or match criteria.
 *
 *\description Given a GPORT ID or the match criteria of a logical layer 2 port,
 *          find/get  the Layer 2 logical port information.
 *          When the VSI (or the VPN) is passed in opennsl_vlan_port_t
 *          parameter,  the API will search only through VLAN gports that are
 *          connected to the VSI (or the VPN).
 *
 *\param    unit [IN]   Unit number.
 *\param    vlan_port [IN,OUT]   Layer 2 logical port
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vlan_port_find(
    int unit, 
    opennsl_vlan_port_t *vlan_port) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#if defined(INCLUDE_L3)
#endif
#if defined(INCLUDE_L3)
#endif
#include <opennsl/vlanX.h>
#endif /* __OPENNSL_VLAN_H__ */
/*@}*/
