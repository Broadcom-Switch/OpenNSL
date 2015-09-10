/** \addtogroup pkt Packet Transmit and Receive
 *  @{
 */
/*****************************************************************************
 * 
 * (C) Copyright Broadcom Corporation 2013-2015
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
 * \file			rx.h
 ******************************************************************************/

#ifndef __OPENNSL_RX_H__
#define __OPENNSL_RX_H__

#include <opennsl/types.h>
#include <opennsl/pkt.h>
#include <opennsl/tx.h>

#define OPENNSL_RX_CHANNELS     4          /**< Max. number of RX channels. */
#define OPENNSL_RCO_F_COS_ACCEPT(cos)  (1 << (cos)) 
#define OPENNSL_RCO_F_ALL_COS       0x40000000 
/** Return values from PKT RX callout routines. */
typedef enum opennsl_rx_e {
    rxReservedEnum1 = 0, 
    OPENNSL_RX_NOT_HANDLED = 1,     /**< Packet not processed. */
    rxReservedEnum2 = 2, 
    OPENNSL_RX_HANDLED_OWNED = 3    /**< Packet handled and owned. */
} opennsl_rx_t;

typedef opennsl_rx_t (*opennsl_rx_cb_f)(
    int unit, 
    opennsl_pkt_t *pkt, 
    void *cookie);

typedef int (*opennsl_rx_alloc_f)(
    int reserved1, 
    int reserved2, 
    uint32 reserved3, 
    void **reserved4);

typedef int (*opennsl_rx_free_f)(
    int reserved1, 
    void *reserved2);

/** 
 * Channel-specific RX data.
 * 
 * The number of chains allowed for the channel controls the burst size
 * that the channel accepts.
 * 
 * The 'rate_pps' field is DEPRECATED. The rate may be set on a per-COS
 * basis using opennsl_rx_rate_set/get.
 * 
 * IMPORTANT: If OPENNSL_RX_F_MULTI_DCB is NOT used (single DCB per
 * packet) then the rx_free routine must be given the allocation pointer
 * (pkt->alloc_ptr) rather than the packet data pointer
 * (pkt->_pkt_data.data or pkt->pkt_data[0].data).
 */
typedef struct opennsl_rx_chan_cfg_s {
    int reserved1; 
    int reserved2; 
    int reserved3; 
    uint32 reserved4; 
} opennsl_rx_chan_cfg_t;

/** User-configurable, per-unit RX configuration. */
typedef struct opennsl_rx_cfg_s {
    int pkt_size;                       /**< Default packet size. */
    int pkts_per_chain;                 /**< Packets per DMA chain. */
    int global_pps;                     /**< Global rate limiting as packets per
                                           second. */
    int max_burst;                      /**< Max. packets to be received in a
                                           single burst. */
    opennsl_rx_chan_cfg_t chan_cfg[OPENNSL_RX_CHANNELS]; /**< RX channel configuration. */
    opennsl_rx_alloc_f rx_alloc;        /**< RX packet allocation function. */
    opennsl_rx_free_f rx_free;          /**< RX packet free function. */
    int32 flags;                        /**< See OPENNSL_RX_F_* definitions. */
    int num_of_cpu_addresses;           /**< Explicitly set the relevant num of
                                           CPU addresses - ignore if not
                                           relevant. */
    int *cpu_address;                   /**< Explicitly set the relevant CPU
                                           addresses - ignore if not relevant. */
} opennsl_rx_cfg_t;

/** 
 * PKT RX Packet Reasons; reason CPU received the packet.
 * 
 * It is possible no reasons are set (directed to CPU from ARL for
 * example), or multiple reasons may be set.
 */
typedef enum opennsl_rx_reason_e {
    opennslrxReservedEnum3 = _SHR_RX_INVALID, 
    opennslrxReservedEnum4 = _SHR_RX_ARP, 
    opennslRxReasonBpdu = _SHR_RX_BPDU, 
    opennslrxReservedEnum5 = _SHR_RX_BROADCAST, 
    opennslrxReservedEnum6 = _SHR_RX_CLASS_BASED_MOVE, 
    opennslrxReservedEnum7 = _SHR_RX_CLASS_TAG_PACKETS, 
    opennslrxReservedEnum8 = _SHR_RX_CONTROL, 
    opennslrxReservedEnum9 = _SHR_RX_CPU_LEARN, 
    opennslrxReservedEnum10 = _SHR_RX_DEST_LOOKUP_FAIL, 
    opennslrxReservedEnum11 = _SHR_RX_DHCP, 
    opennslrxReservedEnum12 = _SHR_RX_DOS_ATTACK, 
    opennslrxReservedEnum13 = _SHR_RX_E2E_HOL_IBP, 
    opennslrxReservedEnum14 = _SHR_RX_ENCAP_HIGIG_ERROR, 
    opennslrxReservedEnum15 = _SHR_RX_FILTER_MATCH, 
    opennslrxReservedEnum16 = _SHR_RX_GRE_CHECKSUM, 
    opennslrxReservedEnum17 = _SHR_RX_GRE_SOURCE_ROUTE, 
    opennslrxReservedEnum18 = _SHR_RX_HIGIG_CONTROL, 
    opennslrxReservedEnum19 = _SHR_RX_HIGIG_HDR_ERROR, 
    opennslrxReservedEnum20 = _SHR_RX_ICMP_REDIRECT, 
    opennslrxReservedEnum21 = _SHR_RX_IGMP, 
    opennslrxReservedEnum22 = _SHR_RX_INGRESS_FILTER, 
    opennslrxReservedEnum23 = _SHR_RX_IP, 
    opennslrxReservedEnum24 = _SHR_RX_IPFIX_RATE_VIOLATION, 
    opennslrxReservedEnum25 = _SHR_RX_IP_MCAST_MISS, 
    opennslrxReservedEnum26 = _SHR_RX_IPMC_RSVD, 
    opennslrxReservedEnum27 = _SHR_RX_IP_OPTION_VERSION, 
    opennslrxReservedEnum28 = _SHR_RX_IPMC, 
    opennslrxReservedEnum29 = _SHR_RX_L2_CPU, 
    opennslrxReservedEnum30 = _SHR_RX_L2_DEST_MISS, 
    opennslrxReservedEnum31 = _SHR_RX_L2_LEARN_LIMIT, 
    opennslrxReservedEnum32 = _SHR_RX_L2_MOVE, 
    opennslrxReservedEnum33 = _SHR_RX_L2_MTU_FAIL, 
    opennslrxReservedEnum34 = _SHR_RX_L2_NON_UNICAST_MISS, 
    opennslrxReservedEnum35 = _SHR_RX_L2_SOURCE_MISS, 
    opennslrxReservedEnum36 = _SHR_RX_L3_ADDR_BIND_FAIL, 
    opennslRxReasonL3DestMiss = _SHR_RX_L3_DEST_MISS, 
    opennslrxReservedEnum37 = _SHR_RX_L3_HEADER_ERROR, 
    opennslrxReservedEnum38 = _SHR_RX_L3_MTU_FAIL, 
    opennslRxReasonL3Slowpath = _SHR_RX_L3_SLOW_PATH, 
    opennslrxReservedEnum39 = _SHR_RX_L3_SOURCE_MISS, 
    opennslrxReservedEnum40 = _SHR_RX_L3_SOUCE_MOVE, 
    opennslrxReservedEnum41 = _SHR_RX_MARTIAN_ADDR, 
    opennslrxReservedEnum42 = _SHR_RX_MCAST_IDX_ERROR, 
    opennslrxReservedEnum43 = _SHR_RX_MCAST_MISS, 
    opennslrxReservedEnum44 = _SHR_RX_MIM_SERVICE_ERROR, 
    opennslrxReservedEnum45 = _SHR_RX_MPLS_CTRL_WORD_ERROR, 
    opennslrxReservedEnum46 = _SHR_RX_MPLS_ERROR, 
    opennslrxReservedEnum47 = _SHR_RX_MPLS_INVALID_ACTION, 
    opennslrxReservedEnum48 = _SHR_RX_MPLS_INVALID_PAYLOAD, 
    opennslrxReservedEnum49 = _SHR_RX_MPLS_LABEL_MISS, 
    opennslrxReservedEnum50 = _SHR_RX_MPLS_SEQUENCE_NUMBER, 
    opennslrxReservedEnum51 = _SHR_RX_MPLS_TTL, 
    opennslrxReservedEnum52 = _SHR_RX_MULTICAST, 
    opennslRxReasonNhop = _SHR_RX_NHOP, 
    opennslrxReservedEnum53 = _SHR_RX_OAM_ERROR, 
    opennslrxReservedEnum54 = _SHR_RX_OAM_SLOW_PATH, 
    opennslrxReservedEnum55 = _SHR_RX_OAM_LMDM, 
    opennslrxReservedEnum56 = _SHR_RX_PARITY_ERROR, 
    opennslRxReasonProtocol = _SHR_RX_PROTOCOL, 
    opennslrxReservedEnum57 = _SHR_RX_SAMPLE_DEST, 
    opennslrxReservedEnum58 = _SHR_RX_SAMPLE_SOURCE, 
    opennslrxReservedEnum59 = _SHR_RX_SHARED_VLAN_MISMATCH, 
    opennslrxReservedEnum60 = _SHR_RX_SOURCE_ROUTE, 
    opennslrxReservedEnum61 = _SHR_RX_TIME_STAMP, 
    opennslrxReservedEnum62 = _SHR_RX_TTL, 
    opennslrxReservedEnum63 = _SHR_RX_TTL1, 
    opennslrxReservedEnum64 = _SHR_RX_TUNNEL_ERROR, 
    opennslrxReservedEnum65 = _SHR_RX_UDP_CHECKSUM, 
    opennslrxReservedEnum66 = _SHR_RX_UNKNOWN_VLAN, 
    opennslrxReservedEnum67 = _SHR_RX_URPF_FAIL, 
    opennslrxReservedEnum68 = _SHR_RX_VC_LABEL_MISS, 
    opennslrxReservedEnum69 = _SHR_RX_VLAN_FILTER_MATCH, 
    opennslrxReservedEnum70 = _SHR_RX_WLAN_CLIENT_ERROR, 
    opennslrxReservedEnum71 = _SHR_RX_WLAN_SLOW_PATH, 
    opennslrxReservedEnum72 = _SHR_RX_WLAN_DOT1X_DROP, 
    opennslrxReservedEnum73 = _SHR_RX_EXCEPTION_FLOOD, 
    opennslrxReservedEnum74 = _SHR_RX_TIMESYNC, 
    opennslrxReservedEnum75 = _SHR_RX_EAV_DATA, 
    opennslrxReservedEnum76 = _SHR_RX_SAME_PORT_BRIDGE, 
    opennslrxReservedEnum77 = _SHR_RX_SPLIT_HORIZON, 
    opennslrxReservedEnum78 = _SHR_RX_L4_ERROR, 
    opennslrxReservedEnum79 = _SHR_RX_STP, 
    opennslrxReservedEnum80 = _SHR_RX_EGRESS_FILTER_REDIRECT, 
    opennslrxReservedEnum81 = _SHR_RX_FILTER_REDIRECT, 
    opennslrxReservedEnum82 = _SHR_RX_LOOPBACK, 
    opennslrxReservedEnum83 = _SHR_RX_VLAN_TRANSLATE, 
    opennslrxReservedEnum84 = _SHR_RX_MMRP, 
    opennslrxReservedEnum85 = _SHR_RX_SRP, 
    opennslrxReservedEnum86 = _SHR_RX_TUNNEL_CONTROL, 
    opennslrxReservedEnum87 = _SHR_RX_L2_MARKED, 
    opennslrxReservedEnum88 = _SHR_RX_WLAN_SLOWPATH_KEEPALIVE, 
    opennslrxReservedEnum89 = _SHR_RX_STATION, 
    opennslrxReservedEnum90 = _SHR_RX_NIV, 
    opennslrxReservedEnum91 = _SHR_RX_NIV_PRIO_DROP, 
    opennslrxReservedEnum92 = _SHR_RX_NIV_INTERFACE_MISS, 
    opennslrxReservedEnum93 = _SHR_RX_NIV_RPF_FAIL, 
    opennslrxReservedEnum94 = _SHR_RX_NIV_TAG_INVALID, 
    opennslrxReservedEnum95 = _SHR_RX_NIV_TAG_DROP, 
    opennslrxReservedEnum96 = _SHR_RX_NIV_UNTAG_DROP, 
    opennslrxReservedEnum97 = _SHR_RX_TRILL, 
    opennslrxReservedEnum98 = _SHR_RX_TRILL_INVALID, 
    opennslrxReservedEnum99 = _SHR_RX_TRILL_MISS, 
    opennslrxReservedEnum100 = _SHR_RX_TRILL_RPF_FAIL, 
    opennslrxReservedEnum101 = _SHR_RX_TRILL_SLOWPATH, 
    opennslrxReservedEnum102 = _SHR_RX_TRILL_CORE_IS_IS, 
    opennslrxReservedEnum103 = _SHR_RX_TRILL_TTL, 
    opennslrxReservedEnum104 = _SHR_RX_TRILL_NAME, 
    opennslrxReservedEnum105 = _SHR_RX_BFD_SLOWPATH, 
    opennslrxReservedEnum106 = _SHR_RX_BFD_ERROR, 
    opennslrxReservedEnum107 = _SHR_RX_MIRROR, 
    opennslrxReservedEnum108 = _SHR_RX_REGEX_ACTION, 
    opennslrxReservedEnum109 = _SHR_RX_REGEX_MATCH, 
    opennslrxReservedEnum110 = _SHR_RX_FAILOVER_DROP, 
    opennslrxReservedEnum111 = _SHR_RX_WLAN_TUNNEL_ERROR, 
    opennslrxReservedEnum112 = _SHR_RX_CONGESTION_CNM_PROXY, 
    opennslrxReservedEnum113 = _SHR_RX_CONGESTION_CNM_PROXY_ERROR, 
    opennslrxReservedEnum114 = _SHR_RX_CONGESTION_CNM, 
    opennslrxReservedEnum115 = _SHR_RX_MPLS_UNKNOWN_ACH, 
    opennslrxReservedEnum116 = _SHR_RX_MPLS_LOOKUPS_EXCEEDED, 
    opennslrxReservedEnum117 = _SHR_RX_MPLS_RESERVED_ENTROPY_LABEL, 
    opennslrxReservedEnum118 = _SHR_RX_MPLS_ILLEGAL_RESERVED_LABEL, 
    opennslrxReservedEnum119 = _SHR_RX_MPLS_ROUTER_ALERT_LABEL, 
    opennslrxReservedEnum120 = _SHR_RX_NIV_PRUNE, 
    opennslrxReservedEnum121 = _SHR_RX_VIRTUAL_PORT_PRUNE, 
    opennslrxReservedEnum122 = _SHR_RX_NON_UNICAST_DROP, 
    opennslrxReservedEnum123 = _SHR_RX_TRILL_PACKET_PORT_MISMATCH, 
    opennslrxReservedEnum124 = _SHR_RX_WLAN_CLIENT_MOVE, 
    opennslrxReservedEnum125 = _SHR_RX_WLAN_SOURCE_PORT_MISS, 
    opennslrxReservedEnum126 = _SHR_RX_WLAN_CLIENT_SOURCE_MISS, 
    opennslrxReservedEnum127 = _SHR_RX_WLAN_CLIENT_DEST_MISS, 
    opennslrxReservedEnum128 = _SHR_RX_WLAN_MTU, 
    opennslrxReservedEnum129 = _SHR_RX_L2GRE_SIP_MISS, 
    opennslrxReservedEnum130 = _SHR_RX_L2GRE_VPN_ID_MISS, 
    opennslrxReservedEnum131 = _SHR_RX_TIMESYNC_UNKNOWN_VERSION, 
    opennslrxReservedEnum132 = _SHR_RX_BFD_UNKNOWN_VERSION, 
    opennslrxReservedEnum133 = _SHR_RX_BFD_INVALID_VERSION, 
    opennslrxReservedEnum134 = _SHR_RX_BFD_LOOKUP_FAILURE, 
    opennslrxReservedEnum135 = _SHR_RX_BFD_INVALID_PACKET, 
    opennslrxReservedEnum136 = _SHR_RX_VXLAN_SIP_MISS, 
    opennslrxReservedEnum137 = _SHR_RX_VXLAN_VPN_ID_MISS, 
    opennslrxReservedEnum138 = _SHR_RX_FCOE_ZONE_CHECK_FAIL, 
    opennslrxReservedEnum139 = _SHR_RX_IPMC_INTERFACE_MISMATCH, 
    opennslrxReservedEnum140 = _SHR_RX_NAT, 
    opennslrxReservedEnum141 = _SHR_RX_TCP_UDP_NAT_MISS, 
    opennslrxReservedEnum142 = _SHR_RX_ICMP_NAT_MISS, 
    opennslrxReservedEnum143 = _SHR_RX_NAT_FRAGMENT, 
    opennslrxReservedEnum144 = _SHR_RX_NAT_MISS, 
    opennslrxReservedEnum145 = _SHR_RX_OAM_CCM_SLOWPATH, 
    opennslrxReservedEnum146 = _SHR_RX_BHH_OAM_PACKET, 
    opennslrxReservedEnum147 = _SHR_RX_UNKNOWN_SUBTENTING_PORT, 
    opennslrxReservedEnum148 = _SHR_RX_RESERVED_0, 
    opennslrxReservedEnum149 = _SHR_RX_OAM_MPLS_LMDM, 
    opennslrxReservedEnum150 = _SHR_RX_REASON_COUNT 
} opennsl_rx_reason_t;

#define OPENNSL_RX_REASON_SET(_reasons, _reason)  \
   _SHR_RX_REASON_SET(_reasons, _reason) 
#define OPENNSL_RX_REASON_CLEAR_ALL(_reasons)  \
   _SHR_RX_REASON_CLEAR_ALL(_reasons) 
#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Start packet reception for the given device.
 *
 *\description If cfg is non-NULL, that configuration is copied to the device's
 *          local configuration.  The rx_alloc and rx_free members of cfg may
 *          be NULL in which case the default values for these functions are
 *          used.  These are normally the =opennsl_rx_pool_alloc functions.
 *          If the RX thread is not already running (only one thread runs for
 *          all devices) then that thread is started.
 *
 *\param    unit [IN]   Unit number.
 *\param    cfg [IN]   Configuration to use (may be NULL)
 *
 *\retval    OPENNSL_E_NONE Success; RX is now running on the device
 *\retval    OPENNSL_E_PARAM Invalid device or pkt_size/pkts_per_chain is 0
 *\retval    OPENNSL_E_MEMORY Unable to allocate necessary objects for
 *          initialization
 ******************************************************************************/
extern int opennsl_rx_start(
    int unit, 
    opennsl_rx_cfg_t *cfg) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Stop the RX software module.
 *
 *\description If RX is running on the given device, it will be given an
 *          indication that it should stop.  If this is the last device
 *          running, the RX thread will be signaled to terminate.  This
 *          function polls for acknowledgment of that operation will sleep
 *          between polls.  The current settings force will result in checking
 *          for acknowledgment 10 times at one-half second intervals.  A
 *          warning may be printed if the thread does not exit.
 *
 *\param    unit [IN]   Unit number.
 *\param    cfg [OUT]   Saved configuration state
 *
 *\retval    OPENNSL_E_NONE Success; RX is no longer running on this device
 ******************************************************************************/
extern int opennsl_rx_stop(
    int unit, 
    opennsl_rx_cfg_t *cfg) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the current configuration for the given device.
 *
 *\description If cfg is non-NULL, the current configuration for the indicated
 *          device is copied there.  If the device has not had
 *          =opennsl_rx_start called on it, the routine will return
 *          OPENNSL_E_INIT.  In this case, the state of cfg will be undefined.
 *
 *\param    unit [IN]   Unit number.
 *\param    cfg [OUT]   Where to copy the device's configuration
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_INIT Start has not yet been called on the device
 *\retval    OPENNSL_E_PARAM Invalid device
 *\retval    OPENNSL_E_MEMORY Unable to allocate necessary objects for
 *          initialization
 ******************************************************************************/
extern int opennsl_rx_cfg_get(
    int unit, 
    opennsl_rx_cfg_t *cfg) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Register or unregister to receive callbacks for received packets.
 *
 *\description See =opennsl_rx_reg_f for more information about the registration
 *          prototype.
 *          See =opennsl_rx_cb_f for more information about the callback
 *          function prototype for callback.  In particular, see =opennsl_rx_t
 *          for the legal return values of the callback.
 *          The callback is placed on an ordered list associated with the
 *          given device and will be called when packets are received on that
 *          device
 *          To set the interrupt and CoS settings for the callback, the flags
 *          parameter should be properly configured with the macros described
 *          above in =rx_callback_flags .
 *          As mentioned, callbacks may be registered to receive packets in
 *          interrupt context.  This is generally not recommended.
 *          A function may be registered multiple times with different
 *          priorities.  However, if the same function and priority are
 *          registered twice, the flags and cookie must match.  .
 *
 *\param    unit [IN]   Unit number.
 *\param    name [IN]   String to identify function; for reporting only
 *\param    callback [IN]   Function pointer to be called
 *\param    priority [IN]   Relative priority of the callback; 0 is lowest
 *\param    cookie [IN]   Application data passed on callback
 *\param    flags [IN]   CoS and interrupt level flags; see =rx_callback_flags
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_MEMORY Could not allocate an entry on the callback list
 *\retval    OPENNSL_E_PARAM Register was called with a NULL callback or
 *          re-registered with mismatched flags or cookie.
 ******************************************************************************/
extern int opennsl_rx_register(
    int unit, 
    const char *name, 
    opennsl_rx_cb_f callback, 
    uint8 priority, 
    void *cookie, 
    uint32 flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Register or unregister to receive callbacks for received packets.
 *
 *\description See =opennsl_rx_reg_f for more information about the registration
 *          prototype.
 *          See =opennsl_rx_cb_f for more information about the callback
 *          function prototype for callback.  In particular, see =opennsl_rx_t
 *          for the legal return values of the callback.
 *          The callback is placed on an ordered list associated with the
 *          given device and will be called when packets are received on that
 *          device
 *          To set the interrupt and CoS settings for the callback, the flags
 *          parameter should be properly configured with the macros described
 *          above in =rx_callback_flags .
 *          As mentioned, callbacks may be registered to receive packets in
 *          interrupt context.  This is generally not recommended.
 *          A function may be registered multiple times with different
 *          priorities.  However, if the same function and priority are
 *          registered twice, the flags and cookie must match.  .
 *
 *\param    unit [IN]   Unit number.
 *\param    callback [IN]   Function pointer to be called
 *\param    priority [IN]   Relative priority of the callback; 0 is lowest
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_MEMORY Could not allocate an entry on the callback list
 *\retval    OPENNSL_E_PARAM Register was called with a NULL callback or
 *          re-registered with mismatched flags or cookie.
 ******************************************************************************/
extern int opennsl_rx_unregister(
    int unit, 
    opennsl_rx_cb_f callback, 
    uint8 priority) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Allocate or deallocate a packet buffer as configured.
 *
 *\description The RX module is configured with the =opennsl_rx_cfg_t structure
 *          which includes a pointer to packet buffer allocation and
 *          deallocation routines.  These functions are a gateway to those
 *          configured functions which, by default, are the
 *          =opennsl_rx_pool_alloc functions.
 *
 *\param    unit [IN]   Unit number.
 *\param    pkt_data [IN]   For opennsl_rx_free, pointer to the data to free
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_MEMORY Otherwise
 ******************************************************************************/
extern int opennsl_rx_free(
    int unit, 
    void *pkt_data) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#if defined(OPENNSL_RPC_SUPPORT) || defined(OPENNSL_RCPU_SUPPORT)
#endif
typedef enum opennsl_rx_control_e {
    opennslRxControlCRCStrip = 0,   /**< Strip CRC from packets. */
    opennslrxReservedEnum151 = 1, 
    opennslrxReservedEnum152 = 2, 
    opennslrxReservedEnum153 = 3, 
    opennslrxReservedEnum154 = 4, 
    opennslrxReservedEnum155 = 5, 
    opennslrxReservedEnum156 = 6, 
    opennslrxReservedEnum157 = 7 
} opennsl_rx_control_t;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Set/get RX operating modes.
 *
 *\description RX controls configure general behavior such as stripping of CRC or
 *          VLAN tags. RX controls may be changed by the application at any
 *          time.  Changes apply to newly received packets, but do not  affect
 *          previously received and buffered packets.  Applications must be
 *          prepared to continue to  handle packets according to the previous
 *          control settings for some time, or else stop packet reception and
 *          drain all queues before changing RX controls.
 *
 *\param    unit [IN]   Unit number.
 *\param    type [IN]   RX control parameter (see =opennsl_rx_control_switches)
 *\param    arg [OUT]   (for _set) Argument whose meaning is dependent on type
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_UNAVAIL Control unavailable
 ******************************************************************************/
extern int opennsl_rx_control_get(
    int unit, 
    opennsl_rx_control_t type, 
    int *arg) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set/get RX operating modes.
 *
 *\description RX controls configure general behavior such as stripping of CRC or
 *          VLAN tags. RX controls may be changed by the application at any
 *          time.  Changes apply to newly received packets, but do not  affect
 *          previously received and buffered packets.  Applications must be
 *          prepared to continue to  handle packets according to the previous
 *          control settings for some time, or else stop packet reception and
 *          drain all queues before changing RX controls.
 *
 *\param    unit [IN]   Unit number.
 *\param    type [IN]   RX control parameter (see =opennsl_rx_control_switches)
 *\param    arg [IN]   (for _set) Argument whose meaning is dependent on type
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_UNAVAIL Control unavailable
 ******************************************************************************/
extern int opennsl_rx_control_set(
    int unit, 
    opennsl_rx_control_t type, 
    int arg) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#endif /* __OPENNSL_RX_H__ */
/*@}*/
