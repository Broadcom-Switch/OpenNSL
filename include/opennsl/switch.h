/** \addtogroup switch Switch Management
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
 * \file			switch.h
 ******************************************************************************/

#ifndef __OPENNSL_SWITCH_H__
#define __OPENNSL_SWITCH_H__

#include <opennsl/types.h>
#include <opennsl/port.h>
#include <opennsl/error.h>
#include <opennsl/stg.h>
#include <shared/switch.h>
#include <shared/bitop.h>

/** Switch controls. */
typedef enum opennsl_switch_control_e {
    opennslSwitchCpuSamplePrio = 16,    /**< Priority for sFlow sample to CPU. */
    opennslSwitchUnknownL3DestToCpu = 26, /**< DIP not found in L3/LPM tables. */
    opennslSwitchSampleIngressRandomSeed = 31, /**< SFlow ingress RNG seed. */
    opennslSwitchSampleEgressRandomSeed = 32, /**< SFlow egress RNG seed. */
    opennslSwitchV6L3DstMissToCpu = 40, /**< IPv6 unknown dest packets to CPU. */
    opennslSwitchV4L3DstMissToCpu = 43, /**< IPv6 unknown dest packets to CPU. */
    opennslSwitchL3SlowpathToCpu = 48,  /**< Slowpath packets to CPU. */
    opennslSwitchArpReplyToCpu = 84,    /**< ARP replies to CPU. */
    opennslSwitchArpRequestToCpu = 86,  /**< ARP requests to CPU. */
    opennslSwitchNdPktToCpu = 89,       /**< ND packets to CPU. */
    opennslSwitchIgmpPktToCpu = 92,     /**< IGMP packets to CPU. */
    opennslSwitchIgmpToCPU = opennslSwitchIgmpPktToCpu, /**< Legacy support for IGMP packets to
                                           CPU. */
    opennslSwitchDhcpPktToCpu = 94,     /**< DHCP packets to CPU. */
    opennslSwitchDhcpPktDrop = 95,      /**< DHCP packets dropped. */
    opennslSwitchV4ResvdMcPktToCpu = 98, /**< IPv4 reserved MC packets to CPU. */
    opennslSwitchDirectedMirroring = 125, /**< Enable directed mirroring mode. */
    opennslSwitchHashControl = 136,     /**< Hash Control of fields. */
    opennslSwitchMirrorUnmarked = 141,  /**< Send mirror packets as simple
                                           unicast. */
    opennslSwitchHashSeed0 = 147,       /**< network switch hash seeds. */
    opennslSwitchHashSeed1 = 148,       /**< For enhanced hashing algoithm. */
    opennslSwitchHashField0PreProcessEnable = 149, /**< Enable pre-processing for enhanced
                                           hash mode 0. */
    opennslSwitchHashField1PreProcessEnable = 150, /**< Enable pre-processing for enhanced
                                           hash mode 1. */
    opennslSwitchHashField0Config = 151, /**< network switch enhanced hash mode 0
                                           config. */
    opennslSwitchHashField0Config1 = 152, /**< network switch enhanced hash mode 0
                                           config 1. */
    opennslSwitchHashField1Config = 153, /**< network switch enhanced hash mode 1
                                           config. */
    opennslSwitchHashField1Config1 = 154, /**< network switch enhanced hash mode 1
                                           config 1. */
    opennslSwitchHashSelectControl = 156, /**< network switch field selection
                                           control. */
    opennslSwitchHashIP4Field0 = 157,   /**< network switch enhanced hash field. */
    opennslSwitchHashIP4Field1 = 158,   /**< Selections for IPv4 packets. */
    opennslSwitchHashIP4TcpUdpField0 = 159, /**< network switch enhanced hash field. */
    opennslSwitchHashIP4TcpUdpField1 = 160, /**< Selections for IPv4 TCP/UDP packets. */
    opennslSwitchHashIP4TcpUdpPortsEqualField0 = 161, /**< network switch enhanced hash field. */
    opennslSwitchHashIP4TcpUdpPortsEqualField1 = 162, /**< Selections for IPv4 TCP/UDP packets
                                           with source L4 port equals to
                                           destination L4 port. */
    opennslSwitchHashIP6Field0 = 163,   /**< network switch enhanced hash field. */
    opennslSwitchHashIP6Field1 = 164,   /**< Selections for IPv6 packets. */
    opennslSwitchHashIP6TcpUdpField0 = 165, /**< network switch enhanced hash field. */
    opennslSwitchHashIP6TcpUdpField1 = 166, /**< Selections for IPv6 TCP/UDP packets. */
    opennslSwitchHashIP6TcpUdpPortsEqualField0 = 167, /**< network switch enhanced hash field. */
    opennslSwitchHashIP6TcpUdpPortsEqualField1 = 168, /**< Selections for IPv6 TCP/UDP packets
                                           with source L4 port equals to
                                           destination L4 port. */
    opennslSwitchHashL2Field0 = 169,    /**< network switch enhanced hash field. */
    opennslSwitchHashL2Field1 = 170,    /**< Selections for L2 packets. */
    opennslSwitchECMPHashSet0Offset = 210, /**< network switch enhanced hash bits. */
    opennslSwitchECMPHashSet1Offset = 211, /**< Selections for ECMP. */
    opennslSwitchMirrorInvalidVlanDrop = 221, /**< Mirror-to-port packets are dropped
                                           upon invalid VLAN. */
    opennslSwitchMirrorPktChecksEnable = 222, /**< Enable/Disable all packet checks for
                                           mirror packets. */
    opennslSwitchL3EgressMode = 230,    /**< Enable advanced egress management. */
    opennslSwitchL3IngressMode = 232,   /**< Enable advanced Ingress-interface
                                           management. */
    opennslSwitchWarmBoot = 238,        /**< Set Warm boot state. */
    opennslSwitchStableSelect = 239,    /**< Select the storage (or stable)
                                           location for Level 2 Warm Boot. */
    opennslSwitchStableSize = 240,      /**< Select the storage (or stable) size
                                           (bytes) for Level 2 Warm Boot. */
    opennslSwitchStableUsed = 241,      /**< Query the storage (or stable) usage
                                           (bytes) for Level 2 Warm Boot. */
    opennslSwitchStableConsistent = 242, /**< Query the storage (or stable) for
                                           whether state is believed consistent
                                           with hardware (API completed prior to
                                           warmboot). */
    opennslSwitchControlSync = 243,     /**< Force a sync of the Level 2 warm boot
                                           state on demand. */
    opennslSwitchControlAutoSync = 244, /**< Perform a sync of the Level 2 warm
                                           boot state after every API. */
    opennslSwitchIpmcTtl1ToCpu = 249,   /**< Copy L3 Mcast with TTL 1 to CPU. */
    opennslSwitchL3UcastTtl1ToCpu = 250, /**< Copy L3 Ucast with TTL 1 to CPU. */
    opennslSwitchBstEnable = 717,       /**< Enable BST tracking. */
    opennslSwitchBstTrackingMode = 718, /**< BST resource usage tracking mode. */
    opennslSwitchVxlanUdpDestPortSet = 729, /**< Set UDP Destination port for VXLAN */
    opennslSwitchVxlanEntropyEnable = 730, /**< Set UDP Source port for VXLAN Tunnel
                                           Entropy(Value = TRUE/FALSE) */
    opennslSwitchVxlanVnIdMissToCpu = 731, /**< Set VXLAN VN_ID lookup failure Copy
                                           to Cpu */
    opennslSwitchVxlanTunnelMissToCpu = 732, /**< If set, send a copy of VXLAN packet
                                           to CPU if VXLAN Tunnel lookup fails. */
    opennslSwitchFlexibleMirrorDestinations = 781, /**< Enable configuration of the maximum
                                           number of mirror destinations. */
    opennslSwitchEcmpMacroFlowHashEnable = 782, /**< Enable ECMP macro-flow hashing. */
    opennslSwitchMcQueueSchedMode = 871, /**< Schedule mode select for multicast
                                           queues. */
    opennslSwitchBstSnapshotEnable = 878, /**< BST resource usage SnapShot mode. */
    opennslSwitchMirrorExclusive = 912, /**< Set Mirror exclusive behaviour
                                           between FP and Port */
} opennsl_switch_control_t;

#define OPENNSL_SWITCH_STABLE_APPLICATION   (_SHR_SWITCH_STABLE_APPLICATION) 
#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Configure port-specific and device-wide operating modes. Device wide
 *       operating modes are configured on all ports, except the stack ports.
 *
 *\description These APIs set parameters related to general device operation such
 *          as controlling whether certain types of packets should be sent to
 *          the local CPU, or setting the priority to be used when such
 *          packets are forwarded to the CPU.  The port specific operations
 *          affect only the indicated port (where possible) while the general
 *          APIs affect all ports.  Not all operations can be carried out on
 *          individual ports on all devices.
 *
 *\param    unit [IN]   Unit number.
 *\param    type [IN]   Switch control parameter (see =opennsl_switchs)
 *\param    arg [OUT]   (for _set) Argument whose meaning is dependent on type
 *
 *\retval    OPENNSL_E_UNAVAIL	Feature not available on this device
 *\retval    OPENNSL_E_XXX		Other error
 ******************************************************************************/
extern int opennsl_switch_control_get(
    int unit, 
    opennsl_switch_control_t type, 
    int *arg) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure port-specific and device-wide operating modes. Device wide
 *       operating modes are configured on all ports, except the stack ports.
 *
 *\description These APIs set parameters related to general device operation such
 *          as controlling whether certain types of packets should be sent to
 *          the local CPU, or setting the priority to be used when such
 *          packets are forwarded to the CPU.  The port specific operations
 *          affect only the indicated port (where possible) while the general
 *          APIs affect all ports.  Not all operations can be carried out on
 *          individual ports on all devices.
 *
 *\param    unit [IN]   Unit number.
 *\param    type [IN]   Switch control parameter (see =opennsl_switchs)
 *\param    arg [IN]   (for _set) Argument whose meaning is dependent on type
 *
 *\retval    OPENNSL_E_UNAVAIL	Feature not available on this device
 *\retval    OPENNSL_E_XXX		Other error
 ******************************************************************************/
extern int opennsl_switch_control_set(
    int unit, 
    opennsl_switch_control_t type, 
    int arg) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure port-specific and device-wide operating modes. Device wide
 *       operating modes are configured on all ports, except the stack ports.
 *
 *\description These APIs set parameters related to general device operation such
 *          as controlling whether certain types of packets should be sent to
 *          the local CPU, or setting the priority to be used when such
 *          packets are forwarded to the CPU.  The port specific operations
 *          affect only the indicated port (where possible) while the general
 *          APIs affect all ports.  Not all operations can be carried out on
 *          individual ports on all devices.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    type [IN]   Switch control parameter (see =opennsl_switchs)
 *\param    arg [OUT]   (for _set) Argument whose meaning is dependent on type
 *
 *\retval    OPENNSL_E_UNAVAIL	Feature not available on this device
 *\retval    OPENNSL_E_XXX		Other error
 ******************************************************************************/
extern int opennsl_switch_control_port_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_switch_control_t type, 
    int *arg) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure port-specific and device-wide operating modes. Device wide
 *       operating modes are configured on all ports, except the stack ports.
 *
 *\description These APIs set parameters related to general device operation such
 *          as controlling whether certain types of packets should be sent to
 *          the local CPU, or setting the priority to be used when such
 *          packets are forwarded to the CPU.  The port specific operations
 *          affect only the indicated port (where possible) while the general
 *          APIs affect all ports.  Not all operations can be carried out on
 *          individual ports on all devices.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    type [IN]   Switch control parameter (see =opennsl_switchs)
 *\param    arg [IN]   (for _set) Argument whose meaning is dependent on type
 *
 *\retval    OPENNSL_E_UNAVAIL	Feature not available on this device
 *\retval    OPENNSL_E_XXX		Other error
 ******************************************************************************/
extern int opennsl_switch_control_port_set(
    int unit, 
    opennsl_port_t port, 
    opennsl_switch_control_t type, 
    int arg) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#define OPENNSL_SWITCH_PKT_INFO_SRC_GPORT   (1 << 0)   /**< Source gport (module,
                                                          port) field valid. */
#define OPENNSL_SWITCH_PKT_INFO_VLAN        (1 << 1)   /**< VLAN identifier field
                                                          valid. */
#define OPENNSL_SWITCH_PKT_INFO_ETHERTYPE   (1 << 2)   /**< Ethertype field valid. */
#define OPENNSL_SWITCH_PKT_INFO_SRC_MAC     (1 << 3)   /**< Source MAC address
                                                          field valid. */
#define OPENNSL_SWITCH_PKT_INFO_DST_MAC     (1 << 4)   /**< Destination MAC
                                                          address field valid. */
#define OPENNSL_SWITCH_PKT_INFO_SRC_IP      (1 << 5)   /**< Source IPv4 address
                                                          field valid. */
#define OPENNSL_SWITCH_PKT_INFO_DST_IP      (1 << 6)   /**< Destination IPv4
                                                          address field valid. */
#define OPENNSL_SWITCH_PKT_INFO_SRC_IPV6    (1 << 7)   /**< Source IPv6 address
                                                          field valid. */
#define OPENNSL_SWITCH_PKT_INFO_DST_IPV6    (1 << 8)   /**< Destination IPv6
                                                          address field valid. */
#define OPENNSL_SWITCH_PKT_INFO_PROTOCOL    (1 << 9)   /**< IP protocol field
                                                          valid. */
#define OPENNSL_SWITCH_PKT_INFO_SRC_L4_PORT (1 << 10)  /**< Source L4 port field
                                                          valid. */
#define OPENNSL_SWITCH_PKT_INFO_DST_L4_PORT (1 << 11)  /**< Destination L4 port
                                                          field valid. */
#define OPENNSL_SWITCH_PKT_INFO_HASH_TRUNK  (1 << 12)  /**< Retrieve trunk hash
                                                          result. */
#define OPENNSL_SWITCH_PKT_INFO_HASH_MULTIPATH (1 << 13)  /**< Retrieve ECMP hash
                                                          result. */
#define OPENNSL_SWITCH_PKT_INFO_HASH_UDP_SOURCE_PORT (1 << 14)  /**< Retrieve Entropy Value
                                                          of VXLan packet. */
#define OPENNSL_SWITCH_PKT_INFO_HASH_LBID   (1 << 15)  /**< Retrieve LBID. */
#define OPENNSL_SWITCH_PKT_INFO_HASH_OVERLAY (1 << 16)  /**< Retrieve ECMP hash
                                                          result for overlay
                                                          layer. */
/** Packet forward reason for hash calculation. */
typedef enum opennsl_switch_pkt_hash_info_fwd_reason_e {
    opennslSwitchPktHashInfoFwdReasonUnicast = 0, /**< Known unicast packet */
    opennslSwitchPktHashInfoFwdReasonIpmc = 1, /**< L3 multicast packet */
    opennslSwitchPktHashInfoFwdReasonL2mc = 2, /**< L2 multicast packet */
    opennslSwitchPktHashInfoFwdReasonBcast = 3, /**< Broadcast packet */
    opennslSwitchPktHashInfoFwdReasonDlf = 4 /**< Destination lookup failed packet */
} opennsl_switch_pkt_hash_info_fwd_reason_t;

/** 
 * Switch packet info structure.
 * 
 * Contains packet fields for calculating aggregate link hash values.
 */
typedef struct opennsl_switch_pkt_info_s {
    uint32 flags;                       /**< OPENNSL_SWITCH_PKT_INFO_xxx flags for
                                           packet parameter hashing. */
    opennsl_gport_t src_gport;          /**< Source module and port,
                                           OPENNSL_GPORT_INVALID to wildcard. */
    opennsl_vlan_t vid;                 /**< VLAN ID. */
    opennsl_ethertype_t ethertype;      /**< Ethertype */
    opennsl_mac_t src_mac;              /**< Source MAC address. */
    opennsl_mac_t dst_mac;              /**< Destination MAC address. */
    opennsl_ip_t sip;                   /**< Source host IP address (IPv4). */
    opennsl_ip_t dip;                   /**< Destination host IP address (IPv4). */
    opennsl_ip6_t sip6;                 /**< Source host IP address (IPv6). */
    opennsl_ip6_t dip6;                 /**< Destination host IP address (IPv6). */
    uint8 protocol;                     /**< IP protocol */
    uint32 src_l4_port;                 /**< Source L4 port */
    uint32 dst_l4_port;                 /**< Destination L4 port. */
    opennsl_gport_t trunk_gport;        /**< Gport of trunk type on which packet
                                           will egress. */
    opennsl_if_t mpintf;                /**< Multipath egress forwarding object. */
    opennsl_switch_pkt_hash_info_fwd_reason_t fwd_reason; /**< Packet forward reason. */
} opennsl_switch_pkt_info_t;

/***************************************************************************//** 
 *\brief Initialize a opennsl_switch_pkt_info_t structure.
 *
 *\description Initializes a packet hashing parameters structure to default
 *          values. This function should be used to initialize any such
 *          structure prior to filling it out and passing it to an API
 *          function.  This ensures that subsequent API releases may add new
 *          structure members to the opennsl_switch_pkt_info_t structure, and
 *          opennsl_switch_pkt_info_t_init will initialize the new members to
 *          correct default values.
 *
 *\param    pkt_info [IN,OUT]   Packet hashing parameters
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern void opennsl_switch_pkt_info_t_init(
    opennsl_switch_pkt_info_t *pkt_info) LIB_DLL_EXPORTED ;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Gets the hash result for the specified link aggregation method using
 *       provided packet parameters and device configuration.
 *
 *\description This API will use provided packet information elements in
 *          conjunction with the current device configuration to determine
 *          either the destination system port for a LAG-directed packet or
 *          the egress object for a packet undergoing ECMP routing.  Note that
 *          only unicast L2 or L3 single-tagged packets without tunnel
 *          encapsulation are supported.
 *          Always initialize a switch packet information structure using the.
 *
 *\param    unit [IN]   Unit number.
 *\param    pkt_info [IN]   Packet parameter information for hash calculation.
 *\param    dst_gport [OUT]   Destination module and port.
 *\param    dst_intf [OUT]   Destination L3 interface ID egress object.
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_switch_pkt_info_hash_get(
    int unit, 
    opennsl_switch_pkt_info_t *pkt_info, 
    opennsl_gport_t *dst_gport, 
    opennsl_if_t *dst_intf) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

typedef void (*opennsl_switch_event_cb_t)(
    int unit, 
    opennsl_switch_event_t event, 
    uint32 arg1, 
    uint32 arg2, 
    uint32 arg3, 
    void *userdata);

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Registers/Unregisters a callback function for switch critical events.
 *
 *\description These APIs allow to the application to register a callback
 *          function which will be called when critical event occurs on the
 *          switch. Applications which register for switch events will be
 *          notified about critical errors described in table below. The
 *          application call back function should log all the information
 *          provided in arg1, arg2 and arg3 in such a way that the system
 *          operator is made aware of the issue. The system operator may need
 *          to take additional actions, up to and include rebooting the
 *          switch.
 *          Call back function is defined as following .
 *
 *\param    unit [IN]   Unit number.
 *\param    cb [IN]   A callback function to be called upon critical event
 *\param    userdata [IN]   Pointer to any provided user data to be called with a
 *          callback
 *
 *\retval    OPENNSL_E_NONE - Success
 *\retval    OPENNSL_E_UNIT - Invalid unit provided
 *\retval    OPENNSL_E_PARAM - Invalid callback function provided.
 *\retval    OPENNSL_E_MEMORY - Not enough memory to register callback
 ******************************************************************************/
extern int opennsl_switch_event_register(
    int unit, 
    opennsl_switch_event_cb_t cb, 
    void *userdata) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Registers/Unregisters a callback function for switch critical events.
 *
 *\description These APIs allow to the application to register a callback
 *          function which will be called when critical event occurs on the
 *          switch. Applications which register for switch events will be
 *          notified about critical errors described in table below. The
 *          application call back function should log all the information
 *          provided in arg1, arg2 and arg3 in such a way that the system
 *          operator is made aware of the issue. The system operator may need
 *          to take additional actions, up to and include rebooting the
 *          switch.
 *          Call back function is defined as following .
 *
 *\param    unit [IN]   Unit number.
 *\param    cb [IN]   A callback function to be called upon critical event
 *\param    userdata [IN]   Pointer to any provided user data to be called with a
 *          callback
 *
 *\retval    OPENNSL_E_NONE - Success
 *\retval    OPENNSL_E_UNIT - Invalid unit provided
 *\retval    OPENNSL_E_PARAM - Invalid callback function provided.
 *\retval    OPENNSL_E_MEMORY - Not enough memory to register callback
 ******************************************************************************/
extern int opennsl_switch_event_unregister(
    int unit, 
    opennsl_switch_event_cb_t cb, 
    void *userdata) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#define OPENNSL_HASH_CONTROL_MULTIPATH_L4PORTS 0x0001     /**< Use TCP/UDP ports. */
#define OPENNSL_HASH_CONTROL_MULTIPATH_DIP  0x0002     /**< Use destination IP
                                                          address. */
#define OPENNSL_HASH_CONTROL_TRUNK_UC_SRCPORT 0x0008     /**< Use source port. */
#define OPENNSL_HASH_CONTROL_TRUNK_NUC_DST  0x0010     /**< Use destination MAC or
                                                          IP address. */
#define OPENNSL_HASH_CONTROL_TRUNK_NUC_SRC  0x0020     /**< Use source MAC or IP
                                                          address. */
#define OPENNSL_HASH_CONTROL_ECMP_ENHANCE   0x0080     /**< Use enhanced ECMP
                                                          hashing. */
#define OPENNSL_HASH_CONTROL_TRUNK_NUC_ENHANCE 0x0100     /**< Use enhanced
                                                          non-unicast trunk
                                                          hashing. */
#define OPENNSL_HASH_FIELD_CONFIG_CRC16CCITT 0x00000007 /**< 16-bit CRC using CCITT
                                                          polynomial. */
#define OPENNSL_HASH_FIELD_CONFIG_CRC32LO   0x00000008 /**< Lower 16-bit of CRC32. */
#define OPENNSL_HASH_FIELD_CONFIG_CRC32HI   0x00000009 /**< Higher 16-bit of
                                                          CRC32. */
#define OPENNSL_HASH_FIELD_DSTL4        0x00000020 /**< Destination L4 port. */
#define OPENNSL_HASH_FIELD_SRCL4        0x00000040 /**< Source L4 port. */
#define OPENNSL_HASH_FIELD_VLAN         0x00000080 /**< VLAN ID. */
#define OPENNSL_HASH_FIELD_IP4DST_LO    0x00000100 /**< IPv4 destination address
                                                      lower 16 bits. */
#define OPENNSL_HASH_FIELD_IP4DST_HI    0x00000200 /**< IPv4 destination address
                                                      upper 16 bits. */
#define OPENNSL_HASH_FIELD_IP4SRC_LO    0x00000400 /**< IPv4 source address lower
                                                      16 bits. */
#define OPENNSL_HASH_FIELD_IP4SRC_HI    0x00000800 /**< IPv4 source address upper
                                                      16 bits. */
#define OPENNSL_HASH_FIELD_IP6DST_LO    0x00001000 /**< IPv6 collapsed destination
                                                      address lower 16 bits. */
#define OPENNSL_HASH_FIELD_IP6DST_HI    0x00002000 /**< IPv6 collapsed destination
                                                      address upper 16 bits. */
#define OPENNSL_HASH_FIELD_IP6SRC_LO    0x00004000 /**< IPv6 collapsed source
                                                      address lower 16 bits. */
#define OPENNSL_HASH_FIELD_IP6SRC_HI    0x00008000 /**< IPv6 collapsed source
                                                      address upper 16 bits. */
#define OPENNSL_HASH_FIELD_MACDA_LO     0x00040000 /**< MAC destination address
                                                      lower 16 bits. */
#define OPENNSL_HASH_FIELD_MACDA_MI     0x00080000 /**< MAC destination address
                                                      middle 16 bits. */
#define OPENNSL_HASH_FIELD_MACDA_HI     0x00100000 /**< MAC destination address
                                                      upper 16 bits. */
#define OPENNSL_HASH_FIELD_MACSA_LO     0x00200000 /**< MAC source address lower
                                                      16 bits. */
#define OPENNSL_HASH_FIELD_MACSA_MI     0x00400000 /**< MAC source address middle
                                                      16 bits. */
#define OPENNSL_HASH_FIELD_MACSA_HI     0x00800000 /**< MAC source address upper
                                                      16 bits. */
/** packet trace lookup result enums */
typedef enum opennsl_switch_pkt_trace_lookup_e {
    opennslSwitchPktTraceLookupCount = 20 
} opennsl_switch_pkt_trace_lookup_t;

/** lookup result set bit map */
typedef struct opennsl_switch_pkt_trace_lookup_result_s {
    SHR_BITDCL pkt_trace_status_bitmap[_SHR_BITDCLSIZE(opennslSwitchPktTraceLookupCount)]; /**< bit map for packet trace lookup
                                           result set */
} opennsl_switch_pkt_trace_lookup_result_t;

#define OPENNSL_SWITCH_PKT_TRACE_ECMP_1     0x0001     /**< level 1 ecmp hashing
                                                          resolution done */
#define OPENNSL_SWITCH_PKT_TRACE_ECMP_2     0x0002     /**< level 2 ecmp hashing
                                                          resolution done */
#define OPENNSL_SWITCH_PKT_TRACE_TRUNK      0x0004     /**< trunk hashing
                                                          resolution done */
#define OPENNSL_SWITCH_PKT_TRACE_FABRIC_TRUNK 0x0008     /**< hg trunk hashing
                                                          resolution done */
/** packet hashing resolution information */
typedef struct opennsl_switch_pkt_trace_hashing_info_s {
    uint32 flags;                       /**< flag containing
                                           OPENNSL_SWITCH_PKT_TRACE_ECMP/TRUNK/FABRIC_TRUNK,
                                           0 == no hashing resolution done */
    opennsl_if_t ecmp_1_group;          /**< multipath egress forwarding object. */
    opennsl_if_t ecmp_1_egress;         /**< ecmp destination interface */
    opennsl_if_t ecmp_2_group;          /**< multipath egress forwarding object. */
    opennsl_if_t ecmp_2_egress;         /**< ecmp destination interface */
    opennsl_gport_t trunk;              /**< destination trunk group */
    opennsl_gport_t trunk_member;       /**< destination member port which packet
                                           egress. */
    opennsl_gport_t fabric_trunk;       /**< destination hg trunk group */
    opennsl_gport_t fabric_trunk_member; /**< destination member hg port which
                                           packet will egress. */
} opennsl_switch_pkt_trace_hashing_info_t;

#define OPENNSL_SWITCH_PKT_TRACE_RAW_DATA_MAX 112        /**< max bytes of
                                                          pkt_trace_info.raw_data */
/** packet trace ingress process data */
typedef struct opennsl_switch_pkt_trace_info_s {
    opennsl_switch_pkt_trace_lookup_result_t pkt_trace_lookup_status; /**< packet trace lookup status set */
    opennsl_switch_pkt_trace_hashing_info_t pkt_trace_hash_info; /**< packet trace hashing information */
    opennsl_stg_stp_t pkt_trace_stp_state; /**< packet trace ingress stp state */
    uint32 dest_pipe_num;               /**< ingress pipeline number of the pkt
                                           trace packet */
    uint32 raw_data_length;             /**< number of bytes returned as raw_data */
    uint8 raw_data[OPENNSL_SWITCH_PKT_TRACE_RAW_DATA_MAX]; /**< packet trace process result data in
                                           raw format */
} opennsl_switch_pkt_trace_info_t;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Generate a visibility trace packet and then read the result of the
 *       packets ingress processing information.
 *
 *\description Generate a visibility packet. Read visibility packet process data
 *          from PTR_RESULTS_BUFFER_IVP, ISW1, and ISW2 then store the raw
 *          data into opennsl_pkt_trace_info_t*  Last, convert the raw data
 *          into abstracted format and store into opennsl_pkt_trace_info_t*
 *          These profile options are used to set loopback headers
 *          cpu_pkt_profile field.
 *
 *\param    unit [IN]   Unit number.
 *\param    options [IN]   FLAGS to select pre-configured cpu_pkt_profile register
 *          values
 *\param    port [IN]
 *\param    len [IN]   Number of bytes to copy from data
 *\param    data [IN]   Source packet buffer to copy from
 *\param    pkt_trace_info [IN,OUT]   visibility packet process information in
 *          opennsl_pkt_trace_info_s format
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_switch_pkt_trace_info_get(
    int unit, 
    uint32 options, 
    uint8 port, 
    int len, 
    uint8 *data, 
    opennsl_switch_pkt_trace_info_t *pkt_trace_info) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#include <opennsl/switchX.h>
#endif /* __OPENNSL_SWITCH_H__ */
/*@}*/
