/** \addtogroup l3 Layer 3 Management
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
 * \file			l3.h
 ******************************************************************************/

#ifndef __OPENNSL_L3_H__
#define __OPENNSL_L3_H__

#if defined(INCLUDE_L3)

#include <opennsl/types.h>
#include <opennsl/stat.h>
#include <opennsl/mpls.h>

#define OPENNSL_L3_L2ONLY               (1 << 0)   /**< L2 switch only on
                                                      interface. */
#define OPENNSL_L3_UNTAG                (1 << 1)   /**< Packet goes out untagged. */
#define OPENNSL_L3_S_HIT                (1 << 2)   /**< Source IP address match. */
#define OPENNSL_L3_D_HIT                (1 << 3)   /**< Destination IP address
                                                      match. */
#define OPENNSL_L3_HIT                  (OPENNSL_L3_S_HIT | OPENNSL_L3_D_HIT) 
#define OPENNSL_L3_HIT_CLEAR            (1 << 4)   /**< Clear HIT bit. */
#define OPENNSL_L3_ADD_TO_ARL           (1 << 5)   /**< Add interface address MAC
                                                      to ARL. */
#define OPENNSL_L3_WITH_ID              (1 << 6)   /**< ID is provided. */
#define OPENNSL_L3_REPLACE              (1 << 8)   /**< Replace existing entry. */
#define OPENNSL_L3_TGID                 (1 << 9)   /**< Port belongs to trunk. */
#define OPENNSL_L3_RPE                  (1 << 10)  /**< Pick up new priority
                                                      (COS). */
#define OPENNSL_L3_IPMC                 (1 << 11)  /**< Set IPMC for real IPMC
                                                      entry. */
#define OPENNSL_L3_L2TOCPU              (1 << 12)  /**< Packet to CPU unrouted,
                                                      XGS12: Set IPMC for UC
                                                      address. */
#define OPENNSL_L3_DEFIP_CPU            (1 << 13)  /**< switch family: DEFIP CPU
                                                      bit set. */
#define OPENNSL_L3_DEFIP_LOCAL          OPENNSL_L3_DEFIP_CPU /**< XGS: Local DEFIP route. */
#define OPENNSL_L3_MULTIPATH            (1 << 14)  /**< Specify ECMP treatment. */
#define OPENNSL_L3_HOST_LOCAL           (1 << 15)  /**< Packet to local IP stack. */
#define OPENNSL_L3_HOST_AS_ROUTE        (1 << 16)  /**< Use LPM if host table
                                                      full. */
#define OPENNSL_L3_IP6                  (1 << 17)  /**< IPv6. */
#define OPENNSL_L3_DST_DISCARD          (1 << 20)  /**< Destination match discard. */
#define OPENNSL_L3_COPY_TO_CPU          (1 << 23)  /**< Send a copy to CPU. */
#define OPENNSL_L3_DEREFERENCED_NEXTHOP (1 << 30)  /**< Indicates this is a wider
                                                      L3 entry. */
#define OPENNSL_L3_ECMP_RH_REPLACE      OPENNSL_L3_DEREFERENCED_NEXTHOP /**< Replace ECMP member
                                                      without RH flowset table
                                                      shuffle. */
#define OPENNSL_L3_VXLAN_ONLY           (1 << 31)  /**< Specific for VXLAN Nexthop */
#define OPENNSL_L3_INGRESS_REPLACE  (1 << 1)   /**< Replace existing L3 Ingress
                                                  entry. */
/** 
 * L3 Interface Structure.
 * 
 * Contains information required for manipulating L3 interfaces.
 */
typedef struct opennsl_l3_intf_s {
    uint32 l3a_flags;                   /**< See OPENNSL_L3_XXX flag definitions. */
    opennsl_vrf_t l3a_vrf;              /**< Virtual router instance. */
    opennsl_if_t l3a_intf_id;           /**< Interface ID. */
    opennsl_mac_t l3a_mac_addr;         /**< MAC address. */
    opennsl_vlan_t l3a_vid;             /**< VLAN ID. */
    int l3a_ttl;                        /**< TTL threshold. */
    int l3a_mtu;                        /**< MTU. */
    int l3a_ip4_options_profile_id;     /**< IP4 Options handling Profile ID */
} opennsl_l3_intf_t;

/** 
 * L3 Egress Structure.
 * 
 * Description of an L3 forwarding destination.
 */
typedef struct opennsl_l3_egress_s {
    uint32 flags;                       /**< Interface flags (OPENNSL_L3_TGID,
                                           OPENNSL_L3_L2TOCPU). */
    uint32 reserved1; 
    opennsl_if_t intf;                  /**< L3 interface (source MAC, tunnel). */
    opennsl_mac_t mac_addr;             /**< Next hop forwarding destination mac. */
    opennsl_vlan_t vlan;                /**< Next hop vlan id. */
    opennsl_module_t module;            
    opennsl_port_t port;                /**< Port packet switched to (if
                                           !OPENNSL_L3_TGID). */
    opennsl_trunk_t trunk;              /**< Trunk packet switched to (if
                                           OPENNSL_L3_TGID). */
    uint32 reserved2; 
    opennsl_mpls_label_t reserved3; 
    opennsl_reserved_enum_t reserved4; 
    int reserved5; 
    int reserved6; 
    uint8 reserved7; 
    uint8 reserved8; 
    uint8 reserved9; 
    int reserved10; 
    opennsl_if_t reserved11; 
    opennsl_failover_t reserved12; 
    opennsl_if_t reserved13; 
    opennsl_multicast_t reserved14; 
    int reserved15; 
    int reserved16; 
    int reserved17; 
    uint32 reserved18; 
    uint16 reserved19; 
    opennsl_vntag_t reserved20; 
    opennsl_reserved_enum_t reserved21; 
    opennsl_etag_t reserved22; 
    opennsl_reserved_enum_t reserved23; 
} opennsl_l3_egress_t;

#define OPENNSL_L3_ECMP_DYNAMIC_SCALING_FACTOR_INVALID -1         /**< Invalid value for
                                                          dynamic_scaling_factor. */
#define OPENNSL_L3_ECMP_DYNAMIC_LOAD_WEIGHT_INVALID -1         /**< Invalid value for
                                                          dynamic_load_weight. */
/** L3 Ingress Interface URPF Mode setting. */
typedef enum opennsl_l3_ingress_urpf_mode_e {
    opennslL3IngressUrpfDisable = 0,    /**< Disable unicast RPF. */
    opennslL3IngressUrpfLoose = 1,      /**< Loose mode Unicast RPF. */
    opennslL3IngressUrpfStrict = 2      /**< Strict mode Unicast RPF. */
} opennsl_l3_ingress_urpf_mode_t;

/** 
 * L3 Ingress Structure.
 * 
 * Description of an L3 Ingress interface.
 */
typedef struct opennsl_l3_ingress_s {
    uint32 flags;                       /**< Interface flags. */
    opennsl_vrf_t vrf;                  /**< Virtual router id. */
    opennsl_l3_ingress_urpf_mode_t urpf_mode; /**< URPF mode setting for L3 Ingress
                                           Interface. */
    int intf_class;                     /**< Classification class ID. */
    opennsl_vlan_t ipmc_intf_id;        /**< IPMC L2 distribution Vlan. */
    int qos_map_id;                     /**< QoS DSCP priority map. */
    int ip4_options_profile_id;         /**< IP4 Options handling Profile ID */
    int nat_realm_id;                   /**< Realm id of the interface for NAT */
} opennsl_l3_ingress_t;

/** 
 * L3 Host Structure.
 * 
 * Contains information required for manipulating L3 host table entries.
 * 
 * The OPENNSL_L3_IP6 flag in l3a_flags must be set to specify whether
 * the IPv4 or IPv6 addresses are valid.
 */
typedef struct opennsl_l3_host_s {
    uint32 l3a_flags;               /**< See OPENNSL_L3_xxx flag definitions. */
    uint32 reserved1; 
    opennsl_vrf_t l3a_vrf;          /**< Virtual router instance. */
    opennsl_ip_t l3a_ip_addr;       /**< Destination host IP address (IPv4). */
    opennsl_ip6_t l3a_ip6_addr;     /**< Destination host IP address (IPv6). */
    opennsl_cos_t l3a_pri;          /**< New priority in packet. */
    opennsl_if_t l3a_intf;          /**< L3 intf associated with this address. */
    opennsl_mac_t l3a_nexthop_mac;  /**< Next hop MAC addr. */
    opennsl_module_t reserved2; 
    opennsl_port_t l3a_port_tgid;   /**< Port/TGID packet is switched to. */
    opennsl_port_t reserved3; 
    int reserved4; 
    int reserved5; 
    opennsl_if_t reserved6; 
    opennsl_if_t reserved7; 
} opennsl_l3_host_t;

/** 
 * L3 Route Structure
 * 
 * Contains information required for manipulating L3 route table entries.
 * 
 * The OPENNSL_L3_IP6 flag in l3a_flags must be set to specify whether
 * the IPv4 or IPv6 addresses are valid.
 */
typedef struct opennsl_l3_route_s {
    uint32 l3a_flags;               /**< See OPENNSL_L3_xxx flag definitions. */
    uint32 reserved1; 
    uint32 reserved2; 
    opennsl_vrf_t l3a_vrf;          /**< Virtual router instance. */
    opennsl_ip_t l3a_subnet;        /**< IP subnet address (IPv4). */
    opennsl_ip6_t l3a_ip6_net;      /**< IP subnet address (IPv6). */
    opennsl_ip_t l3a_ip_mask;       /**< IP subnet mask (IPv4). */
    opennsl_ip6_t l3a_ip6_mask;     /**< IP subnet mask (IPv6). */
    opennsl_if_t l3a_intf;          /**< L3 interface associated with route. */
    opennsl_ip_t reserved3; 
    opennsl_mac_t reserved4; 
    opennsl_module_t reserved5; 
    opennsl_port_t l3a_port_tgid;   /**< Port or trunk group ID. */
    opennsl_port_t reserved6; 
    opennsl_vlan_t reserved7; 
    opennsl_cos_t l3a_pri;          /**< Priority (COS). */
    uint32 reserved8; 
    opennsl_mpls_label_t reserved9; 
    int reserved10; 
    opennsl_if_t reserved11; 
    int reserved12; 
    opennsl_multicast_t reserved13; 
    opennsl_gport_t reserved14; 
} opennsl_l3_route_t;

/** 
 * L3 Information Structure.
 * 
 * Contains information about L3 hardware capacity and utilization.
 * 
 * 
 */
typedef struct opennsl_l3_info_s {
    int l3info_max_intf;    /**< Maximum L3 interfaces the chip supports. */
    int l3info_max_host;    /**< L3 host table size(unit is IPv4 unicast). */
    int l3info_max_route;   /**< L3 route table size (unit is IPv4 route). */
    int l3info_used_intf;   /**< L3 interfaces used. */
} opennsl_l3_info_t;

/** L3 ECMP structure */
typedef struct opennsl_l3_egress_ecmp_s {
    uint32 flags;           /**< See OPENNSL_L3_xxx flag definitions. */
    opennsl_if_t ecmp_intf; /**< L3 interface ID pointing to egress ecmp object. */
    int max_paths;          /**< Max number of paths in ECMP group. If max_paths
                               <= 0, the default max path which can be set by
                               the API opennsl_l3_route_max_ecmp_set will be
                               picked. */
    uint32 reserved1; 
    uint32 dynamic_mode;    /**< Dynamic load balancing mode. See
                               OPENNSL_L3_ECMP_DYNAMIC_MODE_xxx definitions. */
    uint32 dynamic_size;    /**< Number of flows for dynamic load balancing. Valid
                               values are 512, 1k, doubling up to 32k */
    uint32 reserved2; 
    uint32 reserved3; 
    uint32 reserved4; 
} opennsl_l3_egress_ecmp_t;

/** L3 ECMP member structure */
typedef struct opennsl_l3_ecmp_member_s {
    uint32 flags;                   /**< Member flag. */
    opennsl_if_t egress_if;         /**< L3 interface ID pointing to Egress
                                       Forwarding Object. */
    opennsl_failover_t reserved1; 
    opennsl_if_t reserved2; 
    int status;                     /**< Member status. */
} opennsl_l3_ecmp_member_t;

#define OPENNSL_L3_ECMP_DYNAMIC_MODE_RESILIENT 4          /**< ECMP resilient load
                                                          balancing mode:
                                                          minimize reassignment
                                                          of flows to members */
typedef int (*opennsl_l3_host_traverse_cb)(
    int unit, 
    int index, 
    opennsl_l3_host_t *info, 
    void *user_data);

typedef int (*opennsl_l3_route_traverse_cb)(
    int unit, 
    int index, 
    opennsl_l3_route_t *info, 
    void *user_data);

typedef int (*opennsl_l3_egress_traverse_cb)(
    int unit, 
    opennsl_if_t intf, 
    opennsl_l3_egress_t *info, 
    void *user_data);

typedef int (*opennsl_l3_egress_multipath_traverse_cb)(
    int unit, 
    opennsl_if_t mpintf, 
    int intf_count, 
    opennsl_if_t *intf_array, 
    void *user_data);

typedef int (*opennsl_l3_egress_ecmp_traverse_cb)(
    int unit, 
    opennsl_l3_egress_ecmp_t *ecmp, 
    int intf_count, 
    opennsl_if_t *intf_array, 
    void *user_data);

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Initialize the OPENNSL L3 subsystem.
 *
 *\description Initialize all L3 tables and internal data structures.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_init(
    int unit) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Get the status of hardware tables.
 *
 *\description Returns the L3 table capacities and usage, including information
 *          about the host and route tables.
 *
 *\param    unit [IN]   Unit number.
 *\param    l3info [OUT]   L3 capacity and usage information
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_info(
    int unit, 
    opennsl_l3_info_t *l3info) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/***************************************************************************//** 
 *\brief Initialize a opennsl_l3_intf_t structure.
 *
 *\description Initializes an interface structure to default values.  This
 *          function should be used to initialize any interface structure
 *          prior to filling it out and passing it to an API function.  This
 *          ensures that subsequent API releases may add new structure members
 *          to the opennsl_l3_intf_t structure, and opennsl_l3_intf_t_init
 *          will initialize the new members to correct default values.
 *
 *\param    intf [IN,OUT]   Interface information
 *
 *\retval    Nothing
 ******************************************************************************/
extern void opennsl_l3_intf_t_init(
    opennsl_l3_intf_t *intf) LIB_DLL_EXPORTED ;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Create a new L3 interface.
 *
 *\description Creates a new L3 interface.
 *          The MAC address for the new L3 interface is l3a_mac_addr, and the
 *          VLAN identifier is l3a_vid.
 *          The valid flags are as follows:.
 *
 *\param    unit [IN]   Unit number.
 *\param    intf [IN,OUT]   Interface information =L3_INTF_CREATE_FLAGS_table
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_intf_create(
    int unit, 
    opennsl_l3_intf_t *intf) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete an L3 interface.
 *
 *\description Deletes an entry from the L3 interface table.
 *          This function supersedes =opennsl_l3_interface_destroy .
 *
 *\param    unit [IN]   Unit number.
 *\param    intf [IN]   L3 interface information. Valid fields: l3a_intf_id - ID
 *          of interface to be deleted
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_intf_delete(
    int unit, 
    opennsl_l3_intf_t *intf) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Search for L3 interface by MAC address and VLAN.
 *
 *\description Finds an L3 interface ID based on MAC address and VLAN.
 *          This function supersedes =opennsl_l3_interface_lookup .
 *
 *\param    unit [IN]   Unit number.
 *\param    intf [IN,OUT]   L3 interface information =L3_INTF_FIND_FLAGS_table
 *
 *\retval    OPENNSL_E_NOT_FOUND - Interface not found
 *\retval    OPENNSL_E_XXX - Other error code
 ******************************************************************************/
extern int opennsl_l3_intf_find(
    int unit, 
    opennsl_l3_intf_t *intf) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Search for L3 interface by VLAN only.
 *
 *\description Find the L3 interface ID based on VLAN.  If more than one
 *          interface is found in the same VLAN, only the first is returned.
 *          This function supersedes =opennsl_l3_interface_find_by_vlan .
 *
 *\param    unit [IN]   Unit number.
 *\param    intf [IN,OUT]   L3 interface information. Valid Input: l3a_vid - 
 *          Interface VLAN, l3a_intf_id - L3 interface number, if found
 *
 *\retval    OPENNSL_E_NOT_FOUND - Interface not found
 *\retval    OPENNSL_E_XXX - Other error code
 ******************************************************************************/
extern int opennsl_l3_intf_find_vlan(
    int unit, 
    opennsl_l3_intf_t *intf) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Given the L3 interface number, return the interface information.
 *
 *\description Given the L3 interface number, returns the MAC and VLAN of the
 *          interface.
 *
 *\param    unit [IN]   Unit number.
 *\param    intf [IN,OUT]   L3 interface information. =L3_INTF_GET_INPUT_table
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_intf_get(
    int unit, 
    opennsl_l3_intf_t *intf) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/***************************************************************************//** 
 *\brief Initialize a opennsl_l3_egress_t structure.
 *
 *\description Initializes an egress object structure to default values. This
 *          function should be used to initialize any host structure prior to
 *          filling it out and passing it to an API function.  This ensures
 *          that subsequent API releases may add new structure members to the
 *          opennsl_l3_egress_t structure, and opennsl_l3_egress_t_init will
 *          initialize the new members to correct default values.
 *
 *\param    egr [IN,OUT]   Egress object entry information
 *
 *\retval    Nothing
 ******************************************************************************/
extern void opennsl_l3_egress_t_init(
    opennsl_l3_egress_t *egr) LIB_DLL_EXPORTED ;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Create an Egress forwarding object.
 *
 *\description Create a unicast L3 Egress forwarding object on a physical port.
 *          On network switch, this API can be used to create additional types
 *          of L3 Egress objects:.
 *
 *\param    unit [IN]   Unit number.
 *\param    flags [IN]   OPENNSL_L3_REPLACE: replace existing. OPENNSL_L3_WITH_ID:
 *          intf argument is given.
 *\param    egr [IN,OUT]   Egress forwarding destination.
 *\param    if_id [IN,OUT]
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_egress_create(
    int unit, 
    uint32 flags, 
    opennsl_l3_egress_t *egr, 
    opennsl_if_t *if_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroy an Egress forwarding object.
 *
 *\description Destroy an Egress forwarding path.  Only unused egress objects can
 *          be deleted. That is, if forwarding path is used by
 *          routes/hosts/multipath objects operation will return
 *          OPENNSL_E_BUSY. .
 *
 *\param    unit [IN]   Unit number.
 *\param    intf [IN]   L3 interface ID pointing to Egress object.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_egress_destroy(
    int unit, 
    opennsl_if_t intf) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get an Egress forwarding object.
 *
 *\description Get an Egress forwarding path properties. .
 *
 *\param    unit [IN]   Unit number.
 *\param    intf [IN]   L3 interface ID pointing to Egress object.
 *\param    egr [OUT]   Egress forwarding path properties.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_egress_get(
    int unit, 
    opennsl_if_t intf, 
    opennsl_l3_egress_t *egr) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Find an interface pointing to an Egress forwarding object.
 *
 *\description Find an interface pointing to Egress forwarding path with
 *          specified properties.
 *
 *\param    unit [IN]   Unit number.
 *\param    egr [IN]   Egress forwarding path properties.
 *\param    intf [OUT]   L3 interface ID pointing to Egress object.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_egress_find(
    int unit, 
    opennsl_l3_egress_t *egr, 
    opennsl_if_t *intf) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Traverse through the egress object table and run callback at each valid
 *       entry.
 *
 *\description Goes through L3 egress table and runs the user callback function
 *          at each valid entry, passing back the information for that egress
 *          object entry.
 *
 *\param    unit [IN]   Unit number.
 *\param    trav_fn [IN]   Callback function
 *\param    user_data [IN]   User data to be passed to callback function
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_egress_traverse(
    int unit, 
    opennsl_l3_egress_traverse_cb trav_fn, 
    void *user_data) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create a Multipath Egress forwarding object.
 *
 *\description Create an Egress Multipath forwarding object.
 *
 *\param    unit [IN]   Unit number.
 *\param    flags [IN]   OPENNSL_L3_REPLACE: replace existing. OPENNSL_L3_WITH_ID:
 *          intf argument is given.
 *\param    intf_count [IN]   Number of elements in intf_array.
 *\param    intf_array [IN]   Array of Egress forwarding objects.
 *\param    mpintf [IN,OUT]   L3 interface ID pointing to Egress object. This is
 *          an IN argument if either OPENNSL_L3_REPLACE or OPENNSL_L3_WITH_ID are
 *          given in flags.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_egress_multipath_create(
    int unit, 
    uint32 flags, 
    int intf_count, 
    opennsl_if_t *intf_array, 
    opennsl_if_t *mpintf) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroy an Egress Multipath forwarding object.
 *
 *\description Destroy multipath egress forwarding object.  This is only unused
 *          egress objects can be deleted, if forwarding path is used by
 *          routes/hosts objects operation will return OPENNSL_E_BUSY. .
 *
 *\param    unit [IN]   Unit number.
 *\param    mpintf [IN]   L3 interface ID pointing to Egress multipath object.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_egress_multipath_destroy(
    int unit, 
    opennsl_if_t mpintf) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get an Egress Multipath forwarding object.
 *
 *\description Get an Egress Multipath forwarding object.
 *
 *\param    unit [IN]   Unit number.
 *\param    mpintf [IN]   L3 interface ID pointing to Egress multipath object.
 *\param    intf_size [IN]   Size of allocated entries in intf_array.
 *\param    intf_array [OUT]   Array of Egress forwarding objects.
 *\param    intf_count [OUT]   Number of entries of intf_count actually filled in.
 *          This will be a value less than or equal to the value passed in as
 *          intf_size unless intf_size is 0.  If intf_size is 0 then intf_array is
 *          ignored and intf_count is filled in with the number of entries that
 *          would have been filled into intf_array if intf_size was arbitrarily
 *          large.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_egress_multipath_get(
    int unit, 
    opennsl_if_t mpintf, 
    int intf_size, 
    opennsl_if_t *intf_array, 
    int *intf_count) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Add an Egress forwarding object to an Egress Multipath forwarding
 *       object.
 *
 *\description Add an Egress forwarding object to an Egress Multipath forwarding
 *          object.
 *
 *\param    unit [IN]   Unit number.
 *\param    mpintf [IN]   L3 interface ID pointing to Egress multipath object.
 *\param    intf [IN]   L3 interface ID pointing to Egress forwarding object.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_egress_multipath_add(
    int unit, 
    opennsl_if_t mpintf, 
    opennsl_if_t intf) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete an Egress forwarding object from an Egress Multipath forwarding
 *       object.
 *
 *\description Delete an Egress forwarding object from an Egress Multipath
 *          forwarding object.
 *
 *\param    unit [IN]   Unit number.
 *\param    mpintf [IN]   L3 interface ID pointing to Egress multipath object.
 *\param    intf [IN]   L3 interface ID pointing to Egress forwarding object.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_egress_multipath_delete(
    int unit, 
    opennsl_if_t mpintf, 
    opennsl_if_t intf) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Find an interface pointing to an Egress Multipath forwarding object.
 *
 *\description Find an interface pointing to Multipath Egress forwarding object
 *          with  specified unipath egress interfaces set. .
 *
 *\param    unit [IN]   Unit number.
 *\param    intf_count [IN]   Number of elements in intf_array.
 *\param    intf_array [IN]   Array of Egress forwarding objects.
 *\param    mpintf [OUT]   L3 interface ID pointing to Multipath Egress object.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_egress_multipath_find(
    int unit, 
    int intf_count, 
    opennsl_if_t *intf_array, 
    opennsl_if_t *mpintf) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Traverse through the multipath egress object table and run callback at
 *       each valid entry.
 *
 *\description Goes through multipath egress objects table and runs the user
 *          callback function  at each valid entry, passing back the
 *          information for that multipath egress object  entry (interface
 *          count and unipath egress objects array). .
 *
 *\param    unit [IN]   Unit number.
 *\param    trav_fn [IN]   Callback function
 *\param    user_data [IN]   User data to be passed to callback function
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_egress_multipath_traverse(
    int unit, 
    opennsl_l3_egress_multipath_traverse_cb trav_fn, 
    void *user_data) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/***************************************************************************//** 
 *\brief Initialize L3 Egress ECMP object structure.
 *
 *\description Initializes a L3 Egress ECMP object structure to default values.
 *          This function should be used to initialize the L3 Egress ECMP
 *          object  structure prior to invocation of opennsl_l3_egress_ecmp_*
 *          APIs. This ensures that the structure members are initialized to
 *          the correct default values.
 *
 *\param    ecmp [IN,OUT]   L3 Egress ECMP object structure
 *
 *\retval    Nothing
 ******************************************************************************/
extern void opennsl_l3_egress_ecmp_t_init(
    opennsl_l3_egress_ecmp_t *ecmp) LIB_DLL_EXPORTED ;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Get info about an Egress ECMP forwarding object.
 *
 *\description Get info about the Egress ECMP forwarding object pointed to by
 *          ecmp_info->ecmp_intf.
 *
 *\param    unit [IN]   Unit number.
 *\param    ecmp_info [IN,OUT]   ECMP group info.
 *\param    ecmp_member_size [IN]   Size of allocated entries in
 *          ecmp_member_array.
 *\param    ecmp_member_array [OUT]   Member array of Egress forwarding objects.
 *\param    ecmp_member_count [OUT]   Number of entries of ecmp_member_count
 *          actually filled in. This will be a value less than or equal to the
 *          value passed in as ecmp_member_size unless ecmp_member_size is 0.  If
 *          ecmp_member_size is 0 then ecmp_member_array is ignored and
 *          ecmp_member_count is filled in with the number of entries that would
 *          have been filled into ecmp_member_array if ecmp_member_size was
 *          arbitrarily large.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_ecmp_get(
    int unit, 
    opennsl_l3_egress_ecmp_t *ecmp_info, 
    int ecmp_member_size, 
    opennsl_l3_ecmp_member_t *ecmp_member_array, 
    int *ecmp_member_count) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create an Egress ECMP forwarding object.
 *
 *\description Create an Egress ECMP forwarding object. The L3 interface ID
 *          pointing to the created Egress ECMP object is returned in
 *          ecmp->ecmp_intf.
 *
 *\param    unit [IN]   Unit number.
 *\param    ecmp [IN,OUT]   ECMP group info.
 *\param    intf_count [IN]   Number of elements in intf_array.
 *\param    intf_array [IN]   Array of Egress forwarding objects.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_egress_ecmp_create(
    int unit, 
    opennsl_l3_egress_ecmp_t *ecmp, 
    int intf_count, 
    opennsl_if_t *intf_array) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroy an Egress ECMP forwarding object.
 *
 *\description Destroy the Egress ECMP forwarding object pointed to by
 *          ecmp->ecmp_intf.  Only unused egress objects can be deleted. If
 *          forwarding path is used by routes/hosts objects, operation will
 *          return OPENNSL_E_BUSY. .
 *
 *\param    unit [IN]   Unit number.
 *\param    ecmp [IN]   ECMP group info.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_egress_ecmp_destroy(
    int unit, 
    opennsl_l3_egress_ecmp_t *ecmp) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Add an Egress forwarding object to an Egress ECMP forwarding object.
 *
 *\description Add an Egress forwarding object to the Egress ECMP forwarding
 *          object pointed to by ecmp->ecmp_intf.
 *
 *\param    unit [IN]   Unit number.
 *\param    ecmp [IN]   ECMP group info.
 *\param    intf [IN]   L3 interface ID pointing to Egress forwarding object.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_egress_ecmp_add(
    int unit, 
    opennsl_l3_egress_ecmp_t *ecmp, 
    opennsl_if_t intf) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete an Egress forwarding object from an Egress ECMP forwarding
 *       object.
 *
 *\description Delete an Egress forwarding object from the Egress ECMP forwarding
 *          object pointed to by ecmp->ecmp_intf.
 *
 *\param    unit [IN]   Unit number.
 *\param    ecmp [IN]   ECMP group info.
 *\param    intf [IN]   L3 interface ID pointing to Egress forwarding object.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_egress_ecmp_delete(
    int unit, 
    opennsl_l3_egress_ecmp_t *ecmp, 
    opennsl_if_t intf) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Find an Egress ECMP forwarding object.
 *
 *\description Find an Egress ECMP forwarding object with the specified set of
 *          Egress forwarding objects.
 *
 *\param    unit [IN]   Unit number.
 *\param    intf_count [IN]   Number of elements in intf_array.
 *\param    intf_array [IN]   Array of Egress forwarding objects.
 *\param    ecmp [OUT]   ECMP group info.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_egress_ecmp_find(
    int unit, 
    int intf_count, 
    opennsl_if_t *intf_array, 
    opennsl_l3_egress_ecmp_t *ecmp) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Traverse through the valid Egress ECMP forwarding objects and run
 *       callback.
 *
 *\description Goes through all the valid Egress ECMP forwarding objects and runs
 *          the user callback function, passing back the information for that
 *          Egress ECMP forwarding object (including its set of Egress
 *          forwarding objects).
 *
 *\param    unit [IN]   Unit number.
 *\param    trav_fn [IN]   Callback function
 *\param    user_data [IN]   User data to be passed to callback function
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_egress_ecmp_traverse(
    int unit, 
    opennsl_l3_egress_ecmp_traverse_cb trav_fn, 
    void *user_data) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Create L3 Ingress Interface object.
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    ing_intf [IN]   Egress forwarding destination.
 *\param    intf_id [IN,OUT]   L3 Ingress Interface ID pointing to L3 IIF object.
 *          This is an IN argument if either OPENNSL_L3_INGRESS_REPLACE or
 *          OPENNSL_L3_INGRESS_WITH_ID are given in flags.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_ingress_create(
    int unit, 
    opennsl_l3_ingress_t *ing_intf, 
    opennsl_if_t *intf_id) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/***************************************************************************//** 
 *\brief Initialize a opennsl_l3_host_t structure.
 *
 *\description Initializes a host structure to default values.  This function
 *          should be used to initialize any host structure prior to filling
 *          it out and passing it to an API function.  This ensures that
 *          subsequent API releases may add new structure members to the
 *          opennsl_l3_host_t structure, and opennsl_l3_host_t_init will
 *          initialize the new members to correct default values.
 *
 *\param    ip [IN,OUT]
 *
 *\retval    Nothing
 ******************************************************************************/
extern void opennsl_l3_host_t_init(
    opennsl_l3_host_t *ip) LIB_DLL_EXPORTED ;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Look up an L3 host table entry based on IP address.
 *
 *\description Given an IP address, look for a corresponding entry in the L3 host
 *          table, and if found, return the entry's associated information.
 *          The valid flags are as follows:.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN,OUT]   Pointer to opennsl_l3_host_t
 *          =L3_HOST_FIND_FIELDS_table
 *
 *\retval    OPENNSL_E_NOT_FOUND - Matching host table entry not found
 *\retval    OPENNSL_E_XXX - Other error code
 *\retval    This function supersedes .
 ******************************************************************************/
extern int opennsl_l3_host_find(
    int unit, 
    opennsl_l3_host_t *info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Add an entry into the L3 switching table.
 *
 *\description Add an entry to the L3 host table
 *          The valid flags are as follows:.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN]   Pointer to opennsl_l3_host_t containing fields related to
 *          L3 host table: =L3_HOST_ADD_FIELDS_table
 *
 *\retval    OPENNSL_E_XXX
 *\retval    This function supersedes .
 ******************************************************************************/
extern int opennsl_l3_host_add(
    int unit, 
    opennsl_l3_host_t *info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete an entry from the L3 host table.
 *
 *\description Deletes an L3 host table entry matching the IP address specified.
 *          The valid flag is:.
 *
 *\param    unit [IN]   Unit number.
 *\param    ip_addr [IN]   Pointer to opennsl_l3_host_t containing fields related
 *          to the IP address to be deleted from the L3 host table:
 *          =L3_HOST_DELETE_FIELDS_table
 *
 *\retval    OPENNSL_E_XXX
 *\retval    This function supersedes .
 ******************************************************************************/
extern int opennsl_l3_host_delete(
    int unit, 
    opennsl_l3_host_t *ip_addr) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Deletes L3 entries that match or do not match a specified L3 interface
 *       number.
 *
 *\description Deletes all the L3 entries that match/do not match the specified
 *          L3 interface.
 *          The valid flag is:.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN]   Structure specifying the L3 interface:
 *          =L3_HOST_DELETE_IF_FIELDS_table
 *
 *\retval    OPENNSL_E_XXX
 *\retval    This function supersedes .
 ******************************************************************************/
extern int opennsl_l3_host_delete_by_interface(
    int unit, 
    opennsl_l3_host_t *info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Deletes all L3 host table entries.
 *
 *\description Deletes all L3 host table entries.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN]   Structure containing flags
 *
 *\retval    OPENNSL_E_XXX
 *\retval    This function supersedes .
 ******************************************************************************/
extern int opennsl_l3_host_delete_all(
    int unit, 
    opennsl_l3_host_t *info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Traverse through the L3 table and run callback at each valid L3 entry.
 *
 *\description Goes through L3 host table and runs the user callback function at
 *          each valid L3 host entry, passing back the information for that L3
 *          host entry.
 *          The valid flag is:.
 *
 *\param    unit [IN]   Unit number.
 *\param    flags [IN]   Operation control flags
 *\param    start [IN]   The starting valid entry number to be traversed
 *\param    end [IN]   The last valid entry number to be traversed
 *\param    cb [IN]   Callback function
 *\param    user_data [IN]   User data to be passed to callback function
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_host_traverse(
    int unit, 
    uint32 flags, 
    uint32 start, 
    uint32 end, 
    opennsl_l3_host_traverse_cb cb, 
    void *user_data) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/***************************************************************************//** 
 *\brief Initialize a opennsl_l3_route_t structure.
 *
 *\description Initializes a route structure to default values.  This function
 *          should be used to initialize any route structure prior to filling
 *          it out and passing it to an API function.  This ensures that
 *          subsequent API releases may add new structure members to the
 *          opennsl_l3_route_t structure, and opennsl_l3_route_t_init will
 *          initialize the new members to correct default values.
 *
 *\param    route [IN,OUT]   Route information
 *
 *\retval    Nothing
 ******************************************************************************/
extern void opennsl_l3_route_t_init(
    opennsl_l3_route_t *route) LIB_DLL_EXPORTED ;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Add an IP route to the L3 route table.
 *
 *\description Adds an L3 route to the route table.
 *          The valid flags are as follows:.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN]   Pointer to opennsl_l3_host_t containing fields related to
 *          routing table: =L3_ROUTE_ADD_FIELDS_table
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_route_add(
    int unit, 
    opennsl_l3_route_t *info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete an IP route from the DEFIP table.
 *
 *\description Deletes an L3 route from the route table.
 *          The valid flags are as follows:.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN]   Pointer to opennsl_l3_route_t containing the route to
 *          delete. Valid Fields: =L3_ROUTE_DELETE_FIELDS_table and if
 *          OPENNSL_L3_MULTIPATH flag is set, the following fields are also
 *          applicable: =L3_ROUTE_DELETE_MULTICAST_FIELDS_table
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_route_delete(
    int unit, 
    opennsl_l3_route_t *info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete routes based on matching or non-matching L3 interface number.
 *
 *\description Delete all the routes which match or do not match a specified
 *          outgoing L3 interface, including the default routes. .
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN]   Structure containing the L3 interface. Valid fields:
 *          =L3_ROUTE_DEL_BY_INTF_FIELDS_table
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_route_delete_by_interface(
    int unit, 
    opennsl_l3_route_t *info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete all routes.
 *
 *\description Delete all the routes installed, including default unicast IP
 *          routes and IPMC routes.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN]   Route information, of which only l3a_flags is used.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_route_delete_all(
    int unit, 
    opennsl_l3_route_t *info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Look up a route given the network and netmask.
 *
 *\description Gets information for an IP route from the route table.
 *          The valid flags are as follows:.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN,OUT]   Pointer to opennsl_l3_route_t specifying the network
 *          number. =L3_ROUTE_GET_FIELDS_table
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_route_get(
    int unit, 
    opennsl_l3_route_t *info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Given a network, return all the paths for this route.
 *
 *\description Get information for all ECMP paths for a route. For a non-ECMP
 *          route, only one path is returned.
 *          The valid flags are as follows:.
 *
 *\param    unit [IN]   Unit number.
 *\param    the_route [IN]   Pointer to opennsl_l3_route_t specifying the network
 *          number. Valid fields: =L3_ROUTE_MP_GET_ROUTE_FIELDS_table
 *\param    path_array [OUT]   Array of opennsl_l3_route_t to hold output path
 *          information for the network. Valid fields:
 *          =L3_ROUTE_MP_PATH_FIELDS_table
 *\param    max_path [IN]   Maximum number of ECMP paths that may be returned.
 *\param    path_count [OUT]
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_route_multipath_get(
    int unit, 
    opennsl_l3_route_t *the_route, 
    opennsl_l3_route_t *path_array, 
    int max_path, 
    int *path_count) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Traverse through the routing table and run callback at each route.
 *
 *\description Goes through the route table and runs the callback function at
 *          each valid route, passing it the route information.
 *          The valid flag is:.
 *
 *\param    unit [IN]   Unit number.
 *\param    flags [IN]   Operation control flags
 *\param    start [IN]   The starting route number to be traversed
 *\param    end [IN]   The last route number to be traversed
 *\param    trav_fn [IN]   Callback function
 *\param    user_data [IN]   User data to be passed to callback routine
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_route_traverse(
    int unit, 
    uint32 flags, 
    uint32 start, 
    uint32 end, 
    opennsl_l3_route_traverse_cb trav_fn, 
    void *user_data) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set the maximum ECMP paths allowed for a route (switch family only).
 *
 *\description For switch family only, set the maximum ECMP paths allowed for a
 *          route (the default is the maximum allowed by the hardware).
 *
 *\param    unit [IN]   Unit number.
 *\param    max [IN]   Maximum number of ECMP paths allowed
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_route_max_ecmp_set(
    int unit, 
    int max) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the maximum ECMP paths allowed for a route (switch family only).
 *
 *\description For switch family only, gets the maximum ECMP paths allowed for a
 *          route.
 *
 *\param    unit [IN]   Unit number.
 *\param    max [OUT]   Maximum number of ECMP paths
 *
 *\retval    OPENNSL_E_XXX
 *\retval    Additional Information
 ******************************************************************************/
extern int opennsl_l3_route_max_ecmp_get(
    int unit, 
    int *max) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/***************************************************************************//** 
 *\brief Initialize a opennsl_l3_info_t_init structure.
 *
 *\description Initializes a L3 information structure to default values. This
 *          function  should be used to initialize any L3 information
 *          structure prior to filling it out and passing it to an API
 *          function. This ensures that subsequent API releases may add new
 *          structure members to the opennsl_l3_info_t structure, and
 *          opennsl_l3_info_t_init will initialize the new members to correct
 *          default values.
 *
 *\param    info [IN,OUT]   Pointer to L3 information structure to initialize.
 *
 *\retval    Nothing
 ******************************************************************************/
extern void opennsl_l3_info_t_init(
    opennsl_l3_info_t *info) LIB_DLL_EXPORTED ;

/** Types of counters per L3 object. */
typedef enum opennsl_l3_stat_e {
    opennslL3StatOutPackets = 0,    
    opennslL3StatOutBytes = 1,      
    opennslL3StatDropPackets = 2,   
    opennslL3StatDropBytes = 3,     
    opennslL3StatInPackets = 4,     
    opennslL3StatInBytes = 5        
} opennsl_l3_stat_t;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Add VRID for the given VSI. Adding a VRID using this API means the
 *       physical node has become the master for the virtual router.
 *
 *\description Configure an active VRID (Virtual Router ID) for the given VSI  or
 *          VLAN. OPENNSL8802x devices support a maximum of 4 active VR IDs on
 *          a given VLAN.
 *
 *\param    unit [IN]   Unit number.
 *\param    vlan [IN]   VLAN/VSI/VPN Identifier
 *\param    vrid [IN]   VRID - Virtual router ID to be added
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_vrrp_add(
    int unit, 
    opennsl_vlan_t vlan, 
    uint32 vrid) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete VRID for a particular VLAN/VSI.
 *
 *\description Remove a VRID from the configured list of active VRIDs for a given
 *          VLAN.
 *
 *\param    unit [IN]   Unit number.
 *\param    vlan [IN]   VLAN/VSI
 *\param    vrid [IN]   VRID - Virtual router ID to be deleted
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_vrrp_delete(
    int unit, 
    opennsl_vlan_t vlan, 
    uint32 vrid) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete all the VRIDs for a particular VLAN/VSI.
 *
 *\description Delete all the VRIDs for a particular VLAN/VSI.
 *
 *\param    unit [IN]   Unit number.
 *\param    vlan [IN]   VLAN/VSI
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_vrrp_delete_all(
    int unit, 
    opennsl_vlan_t vlan) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get all the VRIDs for which the physical node is master for the virtual
 *       routers on the given VLAN/VSI.
 *
 *\description Get all the VRIDs for which the physical node is master for the
 *          virtual routers on the given VLAN/VSI.
 *
 *\param    unit [IN]   Unit number.
 *\param    vlan [IN]   VLAN/VSI
 *\param    alloc_size [IN]   Number of vrid_array elements
 *\param    vrid_array [OUT]   Pointer to the array to which the VRIDs will be
 *          copied
 *\param    count [OUT]   Number of VRIDs copied
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l3_vrrp_get(
    int unit, 
    opennsl_vlan_t vlan, 
    int alloc_size, 
    int *vrid_array, 
    int *count) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the specified counter statistic for a L3 egress interface.
 *
 *\description This API will retrieve set of counter statistic values for the
 *          specified L3  egress.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    intf_id [IN]   Interface ID of a egress L3 object.
 *\param    stat [IN]   Type of the counter to retrieve that is, ingress/egress
 *          byte/packet
 *\param    num_entries [IN]   Number of counter Entries
 *\param    counter_indexes [IN]   Pointer to Counter indexes entries
 *\param    counter_values [OUT]   Pointer to counter values
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_l3_egress_stat_counter_get(
    int unit, 
    opennsl_if_t intf_id, 
    opennsl_l3_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    opennsl_stat_value_t *counter_values) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get counter statistic values for a l3 interface object.
 *
 *\description This API will retrieve set of counter statistic values for a l3
 *          interface  object.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    intf_id [IN]   Interface ID of a L3 ingress object or a valid VLAN
 *\param    stat [IN]   Type of the counter to retrieve that is, ingress/egress
 *          byte/packet
 *\param    num_entries [IN]   Number of counter Entries
 *\param    counter_indexes [IN]   Pointer to Counter indexes entries
 *\param    counter_values [OUT]   Pointer to counter values
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_l3_ingress_stat_counter_get(
    int unit, 
    opennsl_if_t intf_id, 
    opennsl_l3_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    opennsl_stat_value_t *counter_values) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#ifndef OPENNSL_HIDE_DISPATCHABLE

#endif /* defined(INCLUDE_L3) */

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#include <opennsl/l3X.h>
#endif /* __OPENNSL_L3_H__ */
/*@}*/
