/** \addtogroup multicast Multicast Traffic Management
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
 * \file			multicast.h
 ******************************************************************************/

#ifndef __OPENNSL_MULTICAST_H__
#define __OPENNSL_MULTICAST_H__

#include <opennsl/types.h>

#define OPENNSL_MULTICAST_WITH_ID           0x00000001 
#define OPENNSL_MULTICAST_TYPE_L2           0x00010000 
#define OPENNSL_MULTICAST_TYPE_L3           0x00020000 
#define OPENNSL_MULTICAST_TYPE_VLAN         0x00400000 
#define OPENNSL_MULTICAST_TYPE_VXLAN        0x08000000 
#define OPENNSL_MULTICAST_TYPE_PORTS_GROUP  0x40000000 
#define OPENNSL_MULTICAST_TYPE_MASK         0xffff0000 
#define OPENNSL_MULTICAST_INGRESS_GROUP     0x00000004 
#define OPENNSL_MULTICAST_EGRESS_GROUP      0x00000008 
#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Initialize the multicast module.
 *
 *\description Initialize device tables and driver structures for multicast
 *          management functions.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_multicast_init(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create a multicast group for packet replication.
 *
 *\description Create a multicast group for packet replication. The types of 
 *          multicast groups supported are L2, L3, VPLS, SUBPORT, MiM, WLAN,
 *          and VLAN. Packet replication types supported are INGRESS and
 *          EGRESS.  to create multicast group for a specific packet
 *          replication type use the suitable flag.  By default, the API would
 *          create Ingress and Egress multicast groups. The group identifier
 *          is returned in this API (except when OPENNSL_MULTICAST_WITH_ID is
 *          used). Note that when using OPENNSL_MULTICAST_WITH_ID, the
 *          provided group ID should match the ID returned by
 *          opennsl_multicast_create from another unit in the stack.  For
 *          example,.
 *
 *\param    unit [IN]   Unit number.
 *\param    flags [IN]   OPENNSL_MULTICAST_*
 *\param    group [IN,OUT]   Multicast group ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_multicast_create(
    int unit, 
    uint32 flags, 
    opennsl_multicast_t *group) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroy a multicast group.
 *
 *\description Destroy a multicast group.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Multicast group ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_multicast_destroy(
    int unit, 
    opennsl_multicast_t group) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the multicast encapsulation ID for L3 replication.
 *
 *\description Get the multicast encapsulation ID for L3 replication. The
 *          encapsulation ID is an opaque object passed in to
 *          opennsl_multicast_egress_* APIs to when adding/removing ports to a
 *          multicast group.
 *          To select a port for L2 replication as part of an L3 replication
 *          group, use OPENNSL_IF_INVALID for the intf parameter.
 *          On network switch, this API can also be used to get the multicast
 *          encapsulation ID for a L3 interface residing on a virtual port. In
 *          this case, the parameter port contains the GPORT ID representing
 *          the virtual port. This method will be deprecated in the future, in
 *          favor of =opennsl_l3_egress_create . This method and the method
 *          employing =opennsl_l3_egress_create should not be used at the same
 *          time.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Multicast group ID
 *\param    port [IN]   Physical GPORT ID
 *\param    intf [IN]   L3 interface
 *\param    encap_id [OUT]   Encapsulation ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_multicast_l3_encap_get(
    int unit, 
    opennsl_multicast_t group, 
    opennsl_gport_t port, 
    opennsl_if_t intf, 
    opennsl_if_t *encap_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the multicast encapsulation ID for L2 replication.
 *
 *\description Get the multicast encapsulation ID for L2 replication. The
 *          encapsulation ID is an opaque object passed in to
 *          opennsl_multicast_egress_* APIs when adding/removing ports to a
 *          multicast group.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Multicast group ID
 *\param    port [IN]   Physical GPORT ID
 *\param    vlan [IN]   VLAN ID
 *\param    encap_id [OUT]   Encapsulation ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_multicast_l2_encap_get(
    int unit, 
    opennsl_multicast_t group, 
    opennsl_gport_t port, 
    opennsl_vlan_t vlan, 
    opennsl_if_t *encap_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the multicast encapsulation ID for layer 2 logical port replication.
 *
 *\description Get the multicast encapsulation ID for layer 2 logical port
 *          replication. The encapsulation ID is an opaque object passed in to
 *          opennsl_multicast_egress_* APIs when adding/removing ports to a
 *          multicast group.
 *          For ROBO Arch. in SDK, the vlan_port_id parameter for this API is
 *          used to carry  VLAN information for VLAN replication. Bit0 to
 *          bit11 are used to represent VLAN  index and the bit12 is used to
 *          indicate this VLAN is untagged.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Multicast group ID
 *\param    port [IN]   Physical GPORT ID
 *\param    vlan_port_id [IN]   Layer 2 logical port ID
 *\param    encap_id [OUT]   Encapsulation ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_multicast_vlan_encap_get(
    int unit, 
    opennsl_multicast_t group, 
    opennsl_gport_t port, 
    opennsl_gport_t vlan_port_id, 
    opennsl_if_t *encap_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the multicast encapsulation ID for egress_object type replication.
 *
 *\description Get the multicast encapsulation ID for Egress Object type
 *          replication. The encapsulation ID is an opaque object passed in to
 *          opennsl_multicast_egress_* APIs when adding/removing ports to a
 *          multicast group.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Multicast group ID
 *\param    intf [IN]   Egress Object ID
 *\param    encap_id [OUT]   Encapsulation ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_multicast_egress_object_encap_get(
    int unit, 
    opennsl_multicast_t group, 
    opennsl_if_t intf, 
    opennsl_if_t *encap_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Add an encapsulated interface to a multicast group's replication list on
 *       a specific port.
 *
 *\description Add a port to a multicast group's replication list. The port is
 *          the physical port where replicated packets will be sent. The
 *          encap_id is an opaque encapsulation ID returned from the
 *          opennsl_multicast_*_encap_get APIs. The subscriber_queue is an
 *          opaque subscriber queue ID.  The subscriber form is only available
 *          on certain devices in specific modes; if the non-subscriber form
 *          is used in these modes, it will assume zero as queue group.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Multicast group ID
 *\param    port [IN]   GPORT ID
 *\param    encap_id [IN]   Encapsulation ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_multicast_egress_add(
    int unit, 
    opennsl_multicast_t group, 
    opennsl_gport_t port, 
    opennsl_if_t encap_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete a port from a multicast group's replication list.
 *
 *\description Delete a port from a multicast group's replication list. The port
 *          is the physical port where replicated packets will be sent. The
 *          encap_id is an opaque encapsulation ID returned from the
 *          opennsl_multicast_*_encap_get APIs. The subscriber_queue is an
 *          opaque subscriber queue ID.  The subscriber form is only available
 *          on certain devices in specific modes; if the non-subscriber form
 *          is used in these modes, it will assume zero as queue group.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Multicast group ID
 *\param    port [IN]   GPORT ID
 *\param    encap_id [IN]   Encapsulation ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_multicast_egress_delete(
    int unit, 
    opennsl_multicast_t group, 
    opennsl_gport_t port, 
    opennsl_if_t encap_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete all replications for the specified multicast index.
 *
 *\description Delete all replications for the specified multicast index.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Multicast group ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_multicast_egress_delete_all(
    int unit, 
    opennsl_multicast_t group) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Assign a set of encapsulated interfaces on specific ports as a multicast
 *       group's replication list.
 *
 *\description Assign a set of encapsulated interfaces on specific ports as a
 *          multicast group's replication list. The multicast group's existing
 *          replication list, if any, will be deleted. If port_count is 0,
 *          then all replication lists in the multicast group will be cleared.
 *          The port_array contains physical ports where replicated packets
 *          will be sent. The encap_id_array contains the opaque encapsulation
 *          IDs returned from the opennsl_multicast_*_encap_get APIs. The
 *          subscriber_queue is an array of opaque subscriber queue IDs. The
 *          subscriber form is only available on certain devices in specific
 *          modes; if the non-subscriber form is used in these modes, it will
 *          assume zeros as all queue groups. For incremental modification of
 *          a multicast group's replication list, opennsl_multicast_egress_add
 *          or opennsl_multicast_egress_delete should be used.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Multicast group ID
 *\param    port_count [IN]   Number of ports in the array
 *\param    port_array [IN]   Array of physical ports
 *\param    encap_id_array [IN]   Array of encapsulation IDs
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_multicast_egress_set(
    int unit, 
    opennsl_multicast_t group, 
    int port_count, 
    opennsl_gport_t *port_array, 
    opennsl_if_t *encap_id_array) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the set of encapsulated interfaces on specific ports which comprises
 *       a multicast group's replication list.
 *
 *\description Get the set of encapsulated interfaces on specific ports which
 *          comprises a multicast group's replication list. The port_array
 *          contains physical ports where replicated packets will be sent. The
 *          encap_id_array contains the opaque encapsulation IDs returned from
 *          the opennsl_multicast_*_encap_get APIs. The subscriber_queue is an
 *          array of opaque subscriber queue IDs. The subscriber form is only
 *          available on certain devices in specific modes; if the
 *          non-subscriber form is used in these modes, it will not return the
 *          subscriber queue group IDs. If port_max = 0, port_array and
 *          encap_id_array must be NULL, and the function will return in
 *          port_count the number of ports in the given multicast group.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Multicast group ID
 *\param    port_max [IN]   Number of items allocated in the array
 *\param    port_array [OUT]   Array of physical ports
 *\param    encap_id_array [OUT]   Array of encapsulation IDs
 *\param    port_count [OUT]   Actual number of ports returned in the array
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_multicast_egress_get(
    int unit, 
    opennsl_multicast_t group, 
    int port_max, 
    opennsl_gport_t *port_array, 
    opennsl_if_t *encap_id_array, 
    int *port_count) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Add a port to a Ingress Multicast group's replication list.
 *
 *\description Add a port to a multicast group's replication list in device
 *          Ingress. The port is the physical port where replicated packets
 *          will be sent. The encap_id is an opaque encapsulation ID returned
 *          from the opennsl_multicast_*_encap_get APIs.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Multicast group ID
 *\param    port [IN]   Physical GPORT ID
 *\param    encap_id [IN]   Encapsulation ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_multicast_ingress_add(
    int unit, 
    opennsl_multicast_t group, 
    opennsl_gport_t port, 
    opennsl_if_t encap_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete a port from Ingress Multicast group's replication list.
 *
 *\description Delete a port from multicast group's replication list in device
 *          Ingress. The port is the physical port where replicated packets
 *          will be sent. The encap_id is an opaque encapsulation ID returned
 *          from the opennsl_multicast_*_encap_get APIs.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Multicast group ID
 *\param    port [IN]   Physical GPORT ID
 *\param    encap_id [IN]   Encapsulation ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_multicast_ingress_delete(
    int unit, 
    opennsl_multicast_t group, 
    opennsl_gport_t port, 
    opennsl_if_t encap_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief opennsl_multicast_egress_delete_all.
 *
 *\description Remove all ports from Multicast replication list from device
 *          Ingress.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Multicast group ID
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_multicast_ingress_delete_all(
    int unit, 
    opennsl_multicast_t group) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Add a set of ports to a Ingress multicast group's replication list.
 *
 *\description Add a set of ports to a multicast group's replication list in
 *          device Ingress. The port_array contains physical ports where
 *          replicated packets will be sent. The encap_id_array contains the
 *          opaque encapsulation IDs returned from the
 *          opennsl_multicast_*_encap_get APIs.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Multicast group ID
 *\param    port_count [IN]   Number of ports in the array
 *\param    port_array [IN]   Array of physical ports
 *\param    encap_id_array [IN]   Array of encapsulation IDs
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_multicast_ingress_set(
    int unit, 
    opennsl_multicast_t group, 
    int port_count, 
    opennsl_gport_t *port_array, 
    opennsl_if_t *encap_id_array) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief opennsl_multicast_ingress_get.
 *
 *\description Get the ports in a multicast group's replication list from device
 *          Ingress. The port_array contains physical ports where replicated
 *          packets will be sent. The encap_id_array contains the opaque
 *          encapsulation IDs returned from the opennsl_multicast_*_encap_get
 *          APIs. If port_max = 0, port_array and encap_id_array must be NULL,
 *          and the function will return in port_count the number of ports in
 *          the given multicast group.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Multicast group ID
 *\param    port_max [IN]   Number of items allocated in the array
 *\param    port_array [OUT]   Array of physical ports
 *\param    encap_id_array [OUT]   Array of encapsulation IDs
 *\param    port_count [OUT]   Actual number of ports returned in the array
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_multicast_ingress_get(
    int unit, 
    opennsl_multicast_t group, 
    int port_max, 
    opennsl_gport_t *port_array, 
    opennsl_if_t *encap_id_array, 
    int *port_count) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Retrieve the flags associated with a multicast group.
 *
 *\description Given a multicast group previously reserved by
 *          =opennsl_multicast_create , this function will return the flags
 *          necessary to create the same group on a different unit.  That is,
 *          the returned flags values will be the value of
 *          OPENNSL_MULTICAST_TYPE_* with which the group was created combined
 *          with the OPENNSL_MULTICAST_WITH_ID flag.  The returned flags will
 *          include OPENNSL_MULTICAST_WITH_ID even if the group was not
 *          originally created via this flag. This API can also be used to
 *          check if the given multicast group was created. The flags
 *          OPENNSL_MULTICAST_EGRESS_GROUP, OPENNSL_MULTICAST_INGRESS_GROUP
 *          are returned respectively if the group was created for egress,
 *          ingress multicast.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Multicast group ID
 *\param    flags [OUT]   OPENNSL_MULTICAST_*
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_multicast_group_get(
    int unit, 
    opennsl_multicast_t group, 
    uint32 *flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Request if the given multicast group is available on the device.
 *
 *\description Determine if a specified opennsl_multicast_t value for a multicast
 *          group is currently unused on the device.  This allows an
 *          application to specify a multicast group id via the
 *          OPENNSL_*_WITH_ID flag while omitting the initial call without the
 *          flag. May be used in multi-device systems with different multicast
 *          group capabilities to manage the multicast group ids.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Multicast group ID.
 *
 *\retval    OPENNSL_E_NONE Multicast group is valid and available on the device
 *\retval    OPENNSL_E_EXISTS Multicast group is valid but already in use on this
 *          device
 *\retval    OPENNSL_E_PARAM Multicast group is not valid on this device
 *\retval    OPENNSL_E_UNAVAIL Feature unavailable
 ******************************************************************************/
extern int opennsl_multicast_group_is_free(
    int unit, 
    opennsl_multicast_t group) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Retrieve the minimum and maximum unallocated multicast groups for a
 *       given multicast type.
 *
 *\description The minimum and maximum unused multicast groups of the requested
 *          type are returned.  The full range may have allocated groups
 *          within it. Before using any given group id,
 *          =opennsl_multicast_group_is_free must be used to verify that the
 *          particular value is available.
 *
 *\param    unit [IN]   Unit number.
 *\param    type_flag [IN]   One of OPENNSL_MULTICAST_TYPE_*.
 *\param    group_min [OUT]   Minimum available multicast group of specified type.
 *\param    group_max [OUT]   Maximum available multicast group of specified type.
 *
 *\retval    OPENNSL_E_NONE Multicast group range of requested type returned
 *\retval    OPENNSL_E_NOT_FOUND No available multicast groups of this type
 *\retval    OPENNSL_E_PARAM Multicast group type is not valid on this device
 *\retval    OPENNSL_E_UNAVAIL Feature unavailable
 ******************************************************************************/
extern int opennsl_multicast_group_free_range_get(
    int unit, 
    uint32 type_flag, 
    opennsl_multicast_t *group_min, 
    opennsl_multicast_t *group_max) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

typedef int (*opennsl_multicast_group_traverse_cb_t)(
    int unit, 
    opennsl_multicast_t group, 
    uint32 flags, 
    void *user_data);

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Iterate over the defined multicast groups of the type specified in
 *       'flags'. If all types are desired, use MULTICAST_TYPE_MASK.
 *
 *\description Iterates over created multicast groups and executes user callback
 *          function for each valid entry. The flags parameter specifies the
 *          multicast types which should be included.  For all types, use
 *          OPENNSL_MULTICAST_TYPE_MASK.    The callback function is defined
 *          as following:.
 *
 *\param    unit [IN]   Unit number.
 *\param    trav_fn [IN]   Callback function.
 *\param    flags [IN]   OPENNSL_MULTICAST_*
 *\param    user_data [IN]   User data to be passed to callback function.
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_multicast_group_traverse(
    int unit, 
    opennsl_multicast_group_traverse_cb_t trav_fn, 
    uint32 flags, 
    void *user_data) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/** Multicast group controls. */
typedef enum opennsl_multicast_control_e {
    opennslMulticastControlMtu = 0,     /**< Maximum transmission unit. */
    opennslMulticastVpTrunkResolve = 1, /**< Enable virtual port trunk group
                                           resolution. */
    opennslMulticastRemapGroup = 2,     /**< Remap multicast groups. */
    opennslMulticastControlCount = 3    /**< Must be last */
} opennsl_multicast_control_t;

#ifndef OPENNSL_HIDE_DISPATCHABLE

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#include <opennsl/multicastX.h>
#endif /* __OPENNSL_MULTICAST_H__ */
/*@}*/
