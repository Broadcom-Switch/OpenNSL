/** \addtogroup pkt Packet Transmit and Receive
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
 * \file			rx.h
 ******************************************************************************/

#ifndef __OPENNSL_RX_H__
#define __OPENNSL_RX_H__

#include <opennsl/types.h>
#include <opennsl/pkt.h>
#include <opennsl/tx.h>
#include <opennsl/mirror.h>

#define OPENNSL_RX_CHANNELS         4          /**< Max. number of RX channels. */
#define OPENNSL_CMICX_RX_CHANNELS   8          /**< Max. number of CMICx RX
                                                  channels. */
#define OPENNSL_RCO_F_COS_ACCEPT(cos)  (1 << (cos)) 
#define OPENNSL_RCO_F_ALL_COS       0x40000000 
/** Return values from PKT RX callout routines. */
typedef enum opennsl_rx_e {
    OPENNSL_RX_INVALID = 0,         /**< Invalid return value. */
    OPENNSL_RX_NOT_HANDLED = 1,     /**< Packet not processed. */
    OPENNSL_RX_HANDLED = 2,         /**< Packet handled, not owned. */
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
    int chains;     /**< Number of chains (DVs) set up. 0 means channel not used. */
    int rate_pps;   /**< Deprecated: Use opennsl_rx_cos_rate_set/get. */
    int flags;      /**< See OPENNSL_RX_F_* definitions. */
    uint32 cos_bmp; /**< COS bitmap, if supported. */
} opennsl_rx_chan_cfg_t;

/** User-configurable, per-unit RX configuration. */
typedef struct opennsl_rx_cfg_s {
    int pkt_size;                       /**< Default packet size. */
    int pkts_per_chain;                 /**< Packets per DMA chain. */
    int global_pps;                     /**< Global rate limiting as packets per
                                           second. */
    int max_burst;                      /**< Max. packets to be received in a
                                           single burst. */
    opennsl_rx_chan_cfg_t chan_cfg[OPENNSL_CMICX_RX_CHANNELS]; /**< RX channel configuration. */
    opennsl_rx_alloc_f rx_alloc;        /**< RX packet allocation function. */
    opennsl_rx_free_f rx_free;          /**< RX packet free function. */
    int32 flags;                        /**< See OPENNSL_RX_F_* definitions. */
    int num_of_cpu_addresses;           /**< Explicitly set the relevant num of
                                           CPU addresses - ignore if not
                                           relevant. */
    int *cpu_address;                   /**< Explicitly set the relevant CPU
                                           addresses - ignore if not relevant. */
} opennsl_rx_cfg_t;

#define OPENNSL_RX_REASON_NAMES_INITIALIZER _SHR_RX_REASON_NAMES_INITIALIZER 
/** 
 * PKT RX Packet Reasons; reason CPU received the packet.
 * 
 * It is possible no reasons are set (directed to CPU from ARL for
 * example), or multiple reasons may be set.
 */
typedef enum opennsl_rx_reason_e {
    opennslRxReasonInvalid = _SHR_RX_INVALID, 
    opennslRxReasonArp = _SHR_RX_ARP,   
    opennslRxReasonBpdu = _SHR_RX_BPDU, 
    opennslRxReasonBroadcast = _SHR_RX_BROADCAST, 
    opennslRxReasonClassBasedMove = _SHR_RX_CLASS_BASED_MOVE, 
    opennslRxReasonClassTagPackets = _SHR_RX_CLASS_TAG_PACKETS, 
    opennslRxReasonControl = _SHR_RX_CONTROL, 
    opennslRxReasonCpuLearn = _SHR_RX_CPU_LEARN, 
    opennslRxReasonDestLookupFail = _SHR_RX_DEST_LOOKUP_FAIL, 
    opennslRxReasonDhcp = _SHR_RX_DHCP, 
    opennslRxReasonDosAttack = _SHR_RX_DOS_ATTACK, 
    opennslRxReasonE2eHolIbp = _SHR_RX_E2E_HOL_IBP, 
    opennslRxReasonEncapHigigError = _SHR_RX_ENCAP_HIGIG_ERROR, 
    opennslRxReasonFilterMatch = _SHR_RX_FILTER_MATCH, 
    opennslRxReasonGreChecksum = _SHR_RX_GRE_CHECKSUM, 
    opennslRxReasonGreSourceRoute = _SHR_RX_GRE_SOURCE_ROUTE, 
    opennslRxReasonHigigControl = _SHR_RX_HIGIG_CONTROL, 
    opennslRxReasonHigigHdrError = _SHR_RX_HIGIG_HDR_ERROR, 
    opennslRxReasonIcmpRedirect = _SHR_RX_ICMP_REDIRECT, 
    opennslRxReasonIgmp = _SHR_RX_IGMP, 
    opennslRxReasonIngressFilter = _SHR_RX_INGRESS_FILTER, 
    opennslRxReasonIp = _SHR_RX_IP,     
    opennslRxReasonIpfixRateViolation = _SHR_RX_IPFIX_RATE_VIOLATION, 
    opennslRxReasonIpMcastMiss = _SHR_RX_IP_MCAST_MISS, 
    opennslRxReasonIpmcReserved = _SHR_RX_IPMC_RSVD, 
    opennslRxReasonIpOptionVersion = _SHR_RX_IP_OPTION_VERSION, 
    opennslRxReasonIpmc = _SHR_RX_IPMC, 
    opennslRxReasonL2Cpu = _SHR_RX_L2_CPU, 
    opennslRxReasonL2DestMiss = _SHR_RX_L2_DEST_MISS, 
    opennslRxReasonL2LearnLimit = _SHR_RX_L2_LEARN_LIMIT, 
    opennslRxReasonL2Move = _SHR_RX_L2_MOVE, 
    opennslRxReasonL2MtuFail = _SHR_RX_L2_MTU_FAIL, 
    opennslRxReasonL2NonUnicastMiss = _SHR_RX_L2_NON_UNICAST_MISS, 
    opennslRxReasonL2SourceMiss = _SHR_RX_L2_SOURCE_MISS, 
    opennslRxReasonL3AddrBindFail = _SHR_RX_L3_ADDR_BIND_FAIL, 
    opennslRxReasonL3DestMiss = _SHR_RX_L3_DEST_MISS, 
    opennslRxReasonL3HeaderError = _SHR_RX_L3_HEADER_ERROR, 
    opennslRxReasonL3MtuFail = _SHR_RX_L3_MTU_FAIL, 
    opennslRxReasonL3Slowpath = _SHR_RX_L3_SLOW_PATH, 
    opennslRxReasonL3SourceMiss = _SHR_RX_L3_SOURCE_MISS, 
    opennslRxReasonL3SourceMove = _SHR_RX_L3_SOUCE_MOVE, 
    opennslRxReasonMartianAddr = _SHR_RX_MARTIAN_ADDR, 
    opennslRxReasonMcastIdxError = _SHR_RX_MCAST_IDX_ERROR, 
    opennslRxReasonMcastMiss = _SHR_RX_MCAST_MISS, 
    opennslRxReasonMimServiceError = _SHR_RX_MIM_SERVICE_ERROR, 
    opennslRxReasonMplsCtrlWordError = _SHR_RX_MPLS_CTRL_WORD_ERROR, 
    opennslRxReasonMplsError = _SHR_RX_MPLS_ERROR, 
    opennslRxReasonMplsInvalidAction = _SHR_RX_MPLS_INVALID_ACTION, 
    opennslRxReasonMplsInvalidPayload = _SHR_RX_MPLS_INVALID_PAYLOAD, 
    opennslRxReasonMplsLabelMiss = _SHR_RX_MPLS_LABEL_MISS, 
    opennslRxReasonMplsSequenceNumber = _SHR_RX_MPLS_SEQUENCE_NUMBER, 
    opennslRxReasonMplsTtl = _SHR_RX_MPLS_TTL, 
    opennslRxReasonMulticast = _SHR_RX_MULTICAST, 
    opennslRxReasonNhop = _SHR_RX_NHOP, 
    opennslRxReasonOAMError = _SHR_RX_OAM_ERROR, 
    opennslRxReasonOAMSlowpath = _SHR_RX_OAM_SLOW_PATH, 
    opennslRxReasonOAMLMDM = _SHR_RX_OAM_LMDM, 
    opennslRxReasonParityError = _SHR_RX_PARITY_ERROR, 
    opennslRxReasonProtocol = _SHR_RX_PROTOCOL, 
    opennslRxReasonSampleDest = _SHR_RX_SAMPLE_DEST, 
    opennslRxReasonSampleSource = _SHR_RX_SAMPLE_SOURCE, 
    opennslRxReasonSharedVlanMismatch = _SHR_RX_SHARED_VLAN_MISMATCH, 
    opennslRxReasonSourceRoute = _SHR_RX_SOURCE_ROUTE, 
    opennslRxReasonTimeStamp = _SHR_RX_TIME_STAMP, 
    opennslRxReasonTtl = _SHR_RX_TTL,   
    opennslRxReasonTtl1 = _SHR_RX_TTL1, 
    opennslRxReasonTunnelError = _SHR_RX_TUNNEL_ERROR, 
    opennslRxReasonUdpChecksum = _SHR_RX_UDP_CHECKSUM, 
    opennslRxReasonUnknownVlan = _SHR_RX_UNKNOWN_VLAN, 
    opennslRxReasonUrpfFail = _SHR_RX_URPF_FAIL, 
    opennslRxReasonVcLabelMiss = _SHR_RX_VC_LABEL_MISS, 
    opennslRxReasonVlanFilterMatch = _SHR_RX_VLAN_FILTER_MATCH, 
    opennslRxReasonWlanClientError = _SHR_RX_WLAN_CLIENT_ERROR, 
    opennslRxReasonWlanSlowpath = _SHR_RX_WLAN_SLOW_PATH, 
    opennslRxReasonWlanDot1xDrop = _SHR_RX_WLAN_DOT1X_DROP, 
    opennslRxReasonExceptionFlood = _SHR_RX_EXCEPTION_FLOOD, 
    opennslRxReasonTimeSync = _SHR_RX_TIMESYNC, 
    opennslRxReasonEAVData = _SHR_RX_EAV_DATA, 
    opennslRxReasonSamePortBridge = _SHR_RX_SAME_PORT_BRIDGE, 
    opennslRxReasonSplitHorizon = _SHR_RX_SPLIT_HORIZON, 
    opennslRxReasonL4Error = _SHR_RX_L4_ERROR, 
    opennslRxReasonStp = _SHR_RX_STP,   
    opennslRxReasonEgressFilterRedirect = _SHR_RX_EGRESS_FILTER_REDIRECT, 
    opennslRxReasonFilterRedirect = _SHR_RX_FILTER_REDIRECT, 
    opennslRxReasonLoopback = _SHR_RX_LOOPBACK, 
    opennslRxReasonVlanTranslate = _SHR_RX_VLAN_TRANSLATE, 
    opennslRxReasonMmrp = _SHR_RX_MMRP, 
    opennslRxReasonSrp = _SHR_RX_SRP,   
    opennslRxReasonTunnelControl = _SHR_RX_TUNNEL_CONTROL, 
    opennslRxReasonL2Marked = _SHR_RX_L2_MARKED, 
    opennslRxReasonWlanSlowpathKeepalive = _SHR_RX_WLAN_SLOWPATH_KEEPALIVE, 
    opennslRxReasonStation = _SHR_RX_STATION, 
    opennslRxReasonNiv = _SHR_RX_NIV,   
    opennslRxReasonNivPrioDrop = _SHR_RX_NIV_PRIO_DROP, 
    opennslRxReasonNivInterfaceMiss = _SHR_RX_NIV_INTERFACE_MISS, 
    opennslRxReasonNivRpfFail = _SHR_RX_NIV_RPF_FAIL, 
    opennslRxReasonNivTagInvalid = _SHR_RX_NIV_TAG_INVALID, 
    opennslRxReasonNivTagDrop = _SHR_RX_NIV_TAG_DROP, 
    opennslRxReasonNivUntagDrop = _SHR_RX_NIV_UNTAG_DROP, 
    opennslRxReasonTrill = _SHR_RX_TRILL, 
    opennslRxReasonTrillInvalid = _SHR_RX_TRILL_INVALID, 
    opennslRxReasonTrillMiss = _SHR_RX_TRILL_MISS, 
    opennslRxReasonTrillRpfFail = _SHR_RX_TRILL_RPF_FAIL, 
    opennslRxReasonTrillSlowpath = _SHR_RX_TRILL_SLOWPATH, 
    opennslRxReasonTrillCoreIsIs = _SHR_RX_TRILL_CORE_IS_IS, 
    opennslRxReasonTrillTtl = _SHR_RX_TRILL_TTL, 
    opennslRxReasonTrillName = _SHR_RX_TRILL_NAME, 
    opennslRxReasonBfdSlowpath = _SHR_RX_BFD_SLOWPATH, 
    opennslRxReasonBfd = _SHR_RX_BFD_ERROR, 
    opennslRxReasonMirror = _SHR_RX_MIRROR, 
    opennslRxReasonRegexAction = _SHR_RX_REGEX_ACTION, 
    opennslRxReasonRegexMatch = _SHR_RX_REGEX_MATCH, 
    opennslRxReasonFailoverDrop = _SHR_RX_FAILOVER_DROP, 
    opennslRxReasonWlanTunnelError = _SHR_RX_WLAN_TUNNEL_ERROR, 
    opennslRxReasonCongestionCnmProxy = _SHR_RX_CONGESTION_CNM_PROXY, 
    opennslRxReasonCongestionCnmProxyError = _SHR_RX_CONGESTION_CNM_PROXY_ERROR, 
    opennslRxReasonCongestionCnm = _SHR_RX_CONGESTION_CNM, 
    opennslRxReasonMplsUnknownAch = _SHR_RX_MPLS_UNKNOWN_ACH, 
    opennslRxReasonMplsLookupsExceeded = _SHR_RX_MPLS_LOOKUPS_EXCEEDED, 
    opennslRxReasonMplsReservedEntropyLabel = _SHR_RX_MPLS_RESERVED_ENTROPY_LABEL, 
    opennslRxReasonMplsIllegalReservedLabel = _SHR_RX_MPLS_ILLEGAL_RESERVED_LABEL, 
    opennslRxReasonMplsRouterAlertLabel = _SHR_RX_MPLS_ROUTER_ALERT_LABEL, 
    opennslRxReasonNivPrune = _SHR_RX_NIV_PRUNE, 
    opennslRxReasonVirtualPortPrune = _SHR_RX_VIRTUAL_PORT_PRUNE, 
    opennslRxReasonNonUnicastDrop = _SHR_RX_NON_UNICAST_DROP, 
    opennslRxReasonTrillPacketPortMismatch = _SHR_RX_TRILL_PACKET_PORT_MISMATCH, 
    opennslRxReasonWlanClientMove = _SHR_RX_WLAN_CLIENT_MOVE, 
    opennslRxReasonWlanSourcePortMiss = _SHR_RX_WLAN_SOURCE_PORT_MISS, 
    opennslRxReasonWlanClientSourceMiss = _SHR_RX_WLAN_CLIENT_SOURCE_MISS, 
    opennslRxReasonWlanClientDestMiss = _SHR_RX_WLAN_CLIENT_DEST_MISS, 
    opennslRxReasonWlanMtu = _SHR_RX_WLAN_MTU, 
    opennslRxReasonL2GreSipMiss = _SHR_RX_L2GRE_SIP_MISS, 
    opennslRxReasonL2GreVpnIdMiss = _SHR_RX_L2GRE_VPN_ID_MISS, 
    opennslRxReasonTimesyncUnknownVersion = _SHR_RX_TIMESYNC_UNKNOWN_VERSION, 
    opennslRxReasonBfdUnknownVersion = _SHR_RX_BFD_UNKNOWN_VERSION, 
    opennslRxReasonBfdInvalidVersion = _SHR_RX_BFD_INVALID_VERSION, 
    opennslRxReasonBfdLookupFailure = _SHR_RX_BFD_LOOKUP_FAILURE, 
    opennslRxReasonBfdInvalidPacket = _SHR_RX_BFD_INVALID_PACKET, 
    opennslRxReasonVxlanSipMiss = _SHR_RX_VXLAN_SIP_MISS, 
    opennslRxReasonVxlanVpnIdMiss = _SHR_RX_VXLAN_VPN_ID_MISS, 
    opennslRxReasonFcoeZoneCheckFail = _SHR_RX_FCOE_ZONE_CHECK_FAIL, 
    opennslRxReasonIpmcInterfaceMismatch = _SHR_RX_IPMC_INTERFACE_MISMATCH, 
    opennslRxReasonNat = _SHR_RX_NAT,   
    opennslRxReasonTcpUdpNatMiss = _SHR_RX_TCP_UDP_NAT_MISS, 
    opennslRxReasonIcmpNatMiss = _SHR_RX_ICMP_NAT_MISS, 
    opennslRxReasonNatFragment = _SHR_RX_NAT_FRAGMENT, 
    opennslRxReasonNatMiss = _SHR_RX_NAT_MISS, 
    opennslRxReasonOAMCCMSlowpath = _SHR_RX_OAM_CCM_SLOWPATH, 
    opennslRxReasonBHHOAM = _SHR_RX_BHH_OAM_PACKET, 
    opennslRxReasonUnknownSubtendingPort = _SHR_RX_UNKNOWN_SUBTENTING_PORT, 
    opennslRxReasonReserved0 = _SHR_RX_RESERVED_0, 
    opennslRxReasonOAMMplsLmDm = _SHR_RX_OAM_MPLS_LMDM, 
    opennslRxReasonSat = _SHR_RX_SAT,   
    opennslRxReasonSampleSourceFlex = _SHR_RX_SAMPLE_SOURCE_FLEX, 
    opennslRxReasonFlexSflow = _SHR_RX_FLEX_SFLOW, 
    opennslRxReasonVxltMiss = _SHR_RX_VXLT_MISS, 
    opennslRxReasonTunnelDecapEcnError = _SHR_RX_TUNNEL_DECAP_ECN_ERROR, 
    opennslRxReasonTunnelObjectValidationFail = _SHR_RX_TUNNEL_OBJECT_VALIDATION_FAIL, 
    opennslRxReasonL3Cpu = _SHR_RX_L3_CPU, 
    opennslRxReasonTunnelAdaptLookupMiss = _SHR_RX_TUNNEL_ADAPT_LOOKUP_MISS, 
    opennslRxReasonPacketFlowSelectMiss = _SHR_RX_PACKET_FLOW_SELECT_MISS, 
    opennslRxReasonProtectionDataDrop = _SHR_RX_PROTECTION_DATA_DROP, 
    opennslRxReasonPacketFlowSelect = _SHR_RX_PACKET_FLOW_SELECT, 
    opennslRxReasonOtherLookupMiss = _SHR_RX_OTHER_LOOKUP_MISS, 
    opennslRxReasonInvalidTpid = _SHR_RX_INVALID_TPID, 
    opennslRxReasonMplsControlPacket = _SHR_RX_MPLS_CONTROL_PACKET, 
    opennslRxReasonTunnelTtlError = _SHR_RX_TUNNEL_TTL_ERROR, 
    opennslRxReasonL2HeaderError = _SHR_RX_L2_HEADER_ERROR, 
    opennslRxReasonOtherLookupHit = _SHR_RX_OTHER_LOOKUP_HIT, 
    opennslRxReasonL2SrcLookupMiss = _SHR_RX_L2_SRC_LOOKUP_MISS, 
    opennslRxReasonL2SrcLookupHit = _SHR_RX_L2_SRC_LOOKUP_HIT, 
    opennslRxReasonL2DstLookupMiss = _SHR_RX_L2_DST_LOOKUP_MISS, 
    opennslRxReasonL2DstLookupHit = _SHR_RX_L2_DST_LOOKUP_HIT, 
    opennslRxReasonL3SrcRouteLookupMiss = _SHR_RX_L3_SRC_ROUTE_LOOKUP_MISS, 
    opennslRxReasonL3SrcHostLookupMiss = _SHR_RX_L3_SRC_HOST_LOOKUP_MISS, 
    opennslRxReasonL3SrcRouteLookupHit = _SHR_RX_L3_SRC_ROUTE_LOOKUP_HIT, 
    opennslRxReasonL3SrcHostLookupHit = _SHR_RX_L3_SRC_HOST_LOOKUP_HIT, 
    opennslRxReasonL3DstRouteLookupMiss = _SHR_RX_L3_DST_ROUTE_LOOKUP_MISS, 
    opennslRxReasonL3DstHostLookupMiss = _SHR_RX_L3_DST_HOST_LOOKUP_MISS, 
    opennslRxReasonL3DstRouteLookupHit = _SHR_RX_L3_DST_ROUTE_LOOKUP_HIT, 
    opennslRxReasonL3DstHostLookupHit = _SHR_RX_L3_DST_HOST_LOOKUP_HIT, 
    opennslRxReasonVlanTranslate1Lookup1Miss = _SHR_RX_VLAN_TRANSLATE1_LOOKUP1_MISS, 
    opennslRxReasonVlanTranslate1Lookup2Miss = _SHR_RX_VLAN_TRANSLATE1_LOOKUP2_MISS, 
    opennslRxReasonMplsLookup1Miss = _SHR_RX_MPLS_LOOKUP1_MISS, 
    opennslRxReasonMplsLookup2Miss = _SHR_RX_MPLS_LOOKUP2_MISS, 
    opennslRxReasonL3TunnelLookupMiss = _SHR_RX_L3_TUNNEL_LOOKUP_MISS, 
    opennslRxReasonVlanTranslate2Lookup1Miss = _SHR_RX_VLAN_TRANSLATE2_LOOKUP1_MISS, 
    opennslRxReasonVlanTranslate2Lookup2Miss = _SHR_RX_VLAN_TRANSLATE2_LOOKUP2_MISS, 
    opennslRxReasonL2StuFail = _SHR_RX_L2_STU_FAIL, 
    opennslRxReasonSrCounterExceeded = _SHR_RX_SR_COUNTER_EXCEEDED, 
    opennslRxReasonSrCopyToCpuBit0 = _SHR_RX_SR_COPY_TO_CPU_BIT0, 
    opennslRxReasonSrCopyToCpuBit1 = _SHR_RX_SR_COPY_TO_CPU_BIT1, 
    opennslRxReasonSrCopyToCpuBit2 = _SHR_RX_SR_COPY_TO_CPU_BIT2, 
    opennslRxReasonSrCopyToCpuBit3 = _SHR_RX_SR_COPY_TO_CPU_BIT3, 
    opennslRxReasonSrCopyToCpuBit4 = _SHR_RX_SR_COPY_TO_CPU_BIT4, 
    opennslRxReasonSrCopyToCpuBit5 = _SHR_RX_SR_COPY_TO_CPU_BIT5, 
    opennslRxReasonCount = _SHR_RX_REASON_COUNT 
} opennsl_rx_reason_t;

#if defined(VENDOR_BROADCOM)
#endif
#define OPENNSL_RX_REASON_GET(_reasons, _reason)  \
   _SHR_RX_REASON_GET(_reasons, _reason) 
#define OPENNSL_RX_REASON_SET(_reasons, _reason)  \
   _SHR_RX_REASON_SET(_reasons, _reason) 
#define OPENNSL_RX_REASON_CLEAR_ALL(_reasons)  \
   _SHR_RX_REASON_CLEAR_ALL(_reasons) 
#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Re-initialize the user level configuration for the RX module.
 *
 *\description The default configuration is copied to the RX module's
 *          configuration for the given device.
 *          The device must not be active (started without being stopped).
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_BUSY Device has been started
 *\retval    OPENNSL_E_PARAM Invalid device
 *\retval    OPENNSL_E_MEMORY Unable to allocate necessary objects for
 *          initialization
 ******************************************************************************/
extern int opennsl_rx_cfg_init(
    int unit) LIB_DLL_EXPORTED ;

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
 *\brief Boolean indication of whether RX is running on this device.
 *
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    TRUE The RX module is initialized and running on this device
 *\retval    FALSE The RX module is not running on this device
 ******************************************************************************/
extern int opennsl_rx_active(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get highest priority queue number supported by device.
 *
 *\description Get highest priority queue number supported by device.
 *
 *\param    unit [IN]   Unit number.
 *\param    cosq [OUT]   Maximum priority queue supported by device.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_rx_queue_max_get(
    int unit, 
    opennsl_cos_queue_t *cosq) LIB_DLL_EXPORTED ;

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
 *\brief Get all the CPU RX reasons supported on the specified device.
 *
 *\description Get all the CPU RX reasons supported on the specified device. This
 *          may be different than the set of CPU CoS queue mapping reasons
 *          (see opennsl_rx_cosq_mapping_reasons_get). For example, some 
 *          devices have a many-to-one mapping of CPU COS queue mapping
 *          reasons to RX reason in the RX packet structure.
 *
 *\param    unit [IN]   Unit number.
 *\param    reasons [OUT]   Set of packet reasons
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_PARAM Invalid parameter(s)
 *\retval    OPENNSL_E_UNAVAIL Not available on the specified unit
 ******************************************************************************/
extern int opennsl_rx_reasons_get(
    int unit, 
    opennsl_rx_reasons_t *reasons) LIB_DLL_EXPORTED ;

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

/***************************************************************************//** 
 *\brief Initialize a OPENNSL RX configuration structure.
 *
 *\description Initializes a OPENNSL RX configuration structure to default
 *          values. This function should be used to initialize any OPENNSL RX
 *          configuration structure prior to filling it out and passing it to
 *          an API function. This ensures that subsequent API releases may add
 *          new structure members to the opennsl_rx_cfg_t structure, and
 *          opennsl_rx_cfg_t_init will initialize the new members to correct
 *          default values.
 *
 *\param    rx_cfg [IN,OUT]   Pointer to OPENNSL RX configuration structure to
 *          initialize.
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_rx_cfg_t_init(
    opennsl_rx_cfg_t *rx_cfg) LIB_DLL_EXPORTED ;

#if defined(OPENNSL_RPC_SUPPORT) || defined(OPENNSL_RCPU_SUPPORT)
#endif
typedef enum opennsl_rx_control_e {
    opennslRxControlCRCStrip = 0,   /**< Strip CRC from packets. */
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

#ifndef OPENNSL_HIDE_DISPATCHABLE

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#include <opennsl/rxX.h>
#endif /* __OPENNSL_RX_H__ */
/*@}*/
