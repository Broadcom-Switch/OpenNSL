/** \addtogroup field Field Processor
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
 * \file			fieldX.h
 ******************************************************************************/

#ifndef __OPENNSL_FIELDX_H__
#define __OPENNSL_FIELDX_H__

#include <opennsl/types.h>
#include <opennsl/policer.h>
#include <opennsl/port.h>
#include <opennsl/rx.h>

#define OPENNSL_FIELD_COLOR_PRESERVE    0          
#define OPENNSL_FIELD_COLOR_GREEN       1          
#define OPENNSL_FIELD_COLOR_YELLOW      2          
#define OPENNSL_FIELD_COLOR_RED         3          
#define OPENNSL_FIELD_COLOR_BLACK       4          
#define OPENNSL_FIELD_TCPCONTROL_FIN    0x01       /**< No more data. */
#define OPENNSL_FIELD_TCPCONTROL_SYN    0x02       /**< Sync seq numbers. */
#define OPENNSL_FIELD_TCPCONTROL_RST    0x04       /**< Reset connection. */
#define OPENNSL_FIELD_TCPCONTROL_PSH    0x08       /**< Push. */
#define OPENNSL_FIELD_TCPCONTROL_ACK    0x10       /**< Ack field valid. */
#define OPENNSL_FIELD_TCPCONTROL_URG    0x20       /**< Urgent field valid. */
#define OPENNSL_FIELD_TCPCONTROL_R40    0x40       /**< Reserved. */
#define OPENNSL_FIELD_TCPCONTROL_R80    0x80       /**< Reserved. */
#define OPENNSL_FIELD_TCPCONTROL_MASK   0x3f       /**< All non-reserved bits. */
#define OPENNSL_FIELD_PKT_RES_UNKNOWN       0x0        /**< No resolution. */
#define OPENNSL_FIELD_PKT_RES_CONTROL       0x1        /**< Ethernet control
                                                          (8808). */
#define OPENNSL_FIELD_PKT_RES_L2BC          0x3        /**< L2 broadcast. */
#define OPENNSL_FIELD_PKT_RES_L2UC          0x4        /**< L2 unicast. */
#define OPENNSL_FIELD_PKT_RES_L3MCUNKNOWN   0x6        /**< Unknown L3 multicast. */
#define OPENNSL_FIELD_PKT_RES_L3MCKNOWN     0x7        /**< Known L3 multicast. */
#define OPENNSL_FIELD_PKT_RES_L3UCKNOWN     0xa        /**< Known L3 unicast. */
#define OPENNSL_FIELD_PKT_RES_L3UCUNKNOWN   0xb        /**< Unknown L3 unicast. */
#define OPENNSL_FIELD_USER_NUM_UDFS 93         
/** Opaque handle to a field entry. */
typedef int opennsl_field_entry_t;

/** Opaque handle to a field group. */
typedef int opennsl_field_group_t;

/** 
 * Field Qualifiers
 * 
 * Field qualifiers are collected into qualifier sets (qsets), which are
 * used to allocate field groups.
 * 
 * Note: These are in order of their bit width. Do not change the order
 * or the field select code algorithm for wide-mode will get slower.
 */
typedef enum opennsl_field_qualify_e {
    opennslFieldQualifySrcIp6 = 0,      /**<  Source IPv6 Address. */
    opennslFieldQualifyDstIp6 = 1,      /**<  Destination IPv6 Address. */
    opennslFieldQualifySrcMac = 6,      /**<  Source L2 MAC Address. */
    opennslFieldQualifyDstMac = 7,      /**<  Destination L2 MAC Address. */
    opennslFieldQualifySrcIp = 9,       /**<  Source IPv4 Address. */
    opennslFieldQualifyDstIp = 10,      /**<  Destination IPv4 Address. */
    opennslFieldQualifyInPort = 12,     /**<  Single Input Port. */
    opennslFieldQualifyInPorts = 13,    /**<  Input Port Bitmap. */
    opennslFieldQualifyOuterVlan = 17,  /**<  Outer VLAN. */
    opennslFieldQualifyOuterVlanId = 18, /**<  Outer VLAN Id. */
    opennslFieldQualifyInnerVlanId = 22, /**<  Inner VLAN Id. */
    opennslFieldQualifyRangeCheck = 26, /**<  TCP/UDP Port Range Check Results. */
    opennslFieldQualifyL4SrcPort = 27,  /**<  TCP/UDP Source Port. */
    opennslFieldQualifyL4DstPort = 28,  /**<  TCP/UDP Destination Port. */
    opennslFieldQualifyEtherType = 29,  /**<  Ethernet Type. */
    opennslFieldQualifyIpProtocol = 30, /**<  IP Protocol Field. */
    opennslFieldQualifyIp6NextHeader = opennslFieldQualifyIpProtocol, /**<  IPv6 Next Header/IP Protocol. */
    opennslFieldQualifyDSCP = 31,       /**<  Diffserv Code Point. */
    opennslFieldQualifyTtl = 32,        /**<  Time To Live/Hop Limit. */
    opennslFieldQualifyIp6HopLimit = opennslFieldQualifyTtl, /**<  IPv6 Hop Limit. */
    opennslFieldQualifySrcPort = 35,    /**<  Source Module ID and Port . */
    opennslFieldQualifyDstPort = 40,    /**<  Destination Module ID and Port . */
    opennslFieldQualifyDstTrunk = 41,   /**<  Destination Trunk Group ID . */
    opennslFieldQualifyTcpControl = 42, /**<  TCP Control Flags. */
    opennslFieldQualifyPacketRes = 43,  /**<  Pkt resolution
                                           (OPENNSL_FIELD_PKT_RES_xxx). */
    opennslFieldQualifySrcClassField = 47, /**<  Source Class based on
                                           opennslFieldStageLookup result. */
    opennslFieldQualifyDstClassField = 50, /**<  Destination Class based on
                                           opennslFieldStageLookup result. */
    opennslFieldQualifyIpProtocolCommon = 52, /**<  3: Common IP protocols. */
    opennslFieldQualifyIpType = 61,     /**<  IP Type (opennslFieldIpTypeXXX). */
    opennslFieldQualifyStage = 67,      /**<  Field Processor pipeline stage. */
    opennslFieldQualifyStageIngress = 68, /**<  Field Processor pipeline ingress
                                           stage. */
    opennslFieldQualifyStageLookup = 71, /**<  Field Processor pipeline lookup
                                           stage. */
    opennslFieldQualifyStageEgress = 72, /**<  Field Processor pipeline egress
                                           stage. */
    opennslFieldQualifyInterfaceClassPort = 81, /**<  Port Class Id. */
    opennslFieldQualifyL3Routable = 82, /**<  L3 routable bit for FB2. */
    opennslFieldQualifyIpFrag = 83,     /**<  IP Fragment info. */
    opennslFieldQualifyL3Ingress = 85,  /**<  L3 ingress interface. */
    opennslFieldQualifyOutPort = 86,    /**<  Single Output Port. */
    opennslFieldQualifyIp4 = 87,        /**<  Qualify IpType == IPv4Any. */
    opennslFieldQualifyIp6 = 88,        /**<  Qualify IpType == Ipv6Any. */
    opennslFieldQualifyIcmpTypeCode = 125, /**<  internal use only. */
    opennslFieldQualifyDstL3Egress = 131, /**<  Egress Object id. */
    opennslFieldQualifyColor = 141,     /**<  Packet color. */
    opennslFieldQualifyMyStationHit = 153, /**<  When RIOT is not enabled or not
                                           supported, qualifies on L2 tunnel
                                           termination lookup or Routing hit
                                           status (default). When RIOT is
                                           supported and enabled, qualifies on
                                           L2 underlay tunnel termination lookup
                                           hit status. */
    opennslFieldQualifyDstIpLocal = 171, /**<  Dest IP is local. */
    opennslFieldQualifyCpuQueue = 194,  /**<  CPU COS Queue value. */
    opennslFieldQualifyInterfaceClassProcessingPort = 213, /**< Packet-processing Port Class ID */
    opennslFieldQualifyIngressClassField = 269, /**< Class Id assigned for packet by
                                           Ingress Stage */
    opennslFieldQualifyCount = 620      /**< Always Last. Not a usable value. */
} opennsl_field_qualify_t;

/** 
 * Field Stage Type
 * 
 * Selects which pipeline stage an entry applies to.
 */
typedef enum opennsl_field_stage_e {
    opennslFieldStageFirst = 0,         /**< Earliest Field stage in device. */
    opennslFieldStageIngressEarly = 1,  /**< Early Ingress Field stage. */
    opennslFieldStageIngressLate = 2,   /**< Late Ingress Field stage. */
    opennslFieldStageDefault = 3,       /**< Default stage for device. */
    opennslFieldStageLast = 4,          /**< Latest Field stage in device. */
    opennslFieldStageIngress = 5,       /**< Ingress stage, when there is only one
                                           such. */
    opennslFieldStageEgress = 6,        /**< Egress field stage */
    opennslFieldStageExternal = 7,      /**< External field stage */
    opennslFieldStageHash = 8,          /**< Hashing stage */
    opennslFieldStageIngressExactMatch = 9, /**< Ingress exact match stage */
    opennslFieldStageCount = 10         /**< Always Last. Not a usable value. */
} opennsl_field_stage_t;

#define OPENNSL_FIELD_QUALIFY_MAX   (opennslFieldQualifyCount + OPENNSL_FIELD_USER_NUM_UDFS) /**< Must be >=
                                                  opennslFieldQualifyCount. */
#define OPENNSL_FIELD_EXACT_MATCH_MASK  (~0)       /**< Mask parameter value. */
/** Field Qualifier IpType (for opennsl_field_qualify_IpType). */
typedef enum opennsl_field_IpType_e {
    opennslFieldIpTypeIpv4WithOpts = 4, /**< IPv4 with options. */
    opennslFieldIpTypeIpv4Any = 5,      /**< Any IPv4 packet. */
    opennslFieldIpTypeIpv6OneExtHdr = 8, /**< IPv6 packet with one extension
                                           header. */
    opennslFieldIpTypeIpv6TwoExtHdr = 9, /**< IPv6 packet with two or more
                                           extension headers. */
    opennslFieldIpTypeIpv6 = 10,        /**< IPv6 packet. */
} opennsl_field_IpType_t;

/** 
 * Field Qualifier IpProtocolCommon (for
 * opennsl_field_qualify_IpProtocolCommon).
 */
typedef enum opennsl_field_IpProtocolCommon_e {
    opennslFieldIpProtocolCommonTcp = 0, /**< TCP Packets (6) */
    opennslFieldIpProtocolCommonUdp = 1, /**< UDP Packets (17) */
    opennslFieldIpProtocolCommonIgmp = 2, /**< IGMP Packets (2) */
    opennslFieldIpProtocolCommonIcmp = 3, /**< ICMP Packets (1) */
} opennsl_field_IpProtocolCommon_t;

/** Field Qualifier IpFrag (for opennsl_field_qualify_IpFrag). */
typedef enum opennsl_field_IpFrag_e {
    opennslFieldIpFragNon = 0,          /**< Non-fragmented packet. */
    opennslFieldIpFragFirst = 1,        /**< First fragment of fragmented packet. */
    opennslFieldIpFragNonOrFirst = 2,   /**< Non-fragmented or first fragment. */
    opennslFieldIpFragNotFirst = 3,     /**< Not the first fragment. */
    opennslFieldIpFragAny = 4,          /**< Any fragment of fragmented packet. */
    opennslFieldIpFragCount = 5         /**< Always last. Not a usable value. */
} opennsl_field_IpFrag_t;

#define OPENNSL_FIELD_RANGE_SRCPORT         0x00000001 /**< Check source port
                                                          range */
#define OPENNSL_FIELD_RANGE_DSTPORT         0x00000002 /**< Check dest port range */
#define OPENNSL_FIELD_RANGE_TCP             0x00000004 /**< Check TCP port range */
#define OPENNSL_FIELD_RANGE_UDP             0x00000008 /**< Check UDP port range */
#define OPENNSL_FIELD_RANGE_INVERT          0x00000010 /**< Check for match
                                                          outside specified port
                                                          range */
#define OPENNSL_FIELD_RANGE_OUTER_VLAN      0x00000040 /**< Check outer VLAN ID
                                                          range */
#define OPENNSL_FIELD_RANGE_INNER_VLAN      0x00000080 /**< Check inner VLAN ID
                                                          range */
#define OPENNSL_FIELD_RANGE_PACKET_LENGTH   0x00000100 /**< Check packet length
                                                          range */
#define OPENNSL_FIELD_RANGE_REPLACE         0x00000800 /**< Modify configurations
                                                          of an existing range
                                                          checker. Using this
                                                          flag, the Range
                                                          checker's range limits
                                                          (min/max) and Type can
                                                          be modified
                                                          dynamically. */
/** Opaque handle to a field range. */
typedef uint32 opennsl_field_range_t;

/** Field qset defines the set of fields used for lookup. */
typedef struct opennsl_field_qset_s {
    SHR_BITDCL w[_SHR_BITDCLSIZE(OPENNSL_FIELD_QUALIFY_MAX)]; 
    SHR_BITDCL udf_map[_SHR_BITDCLSIZE(OPENNSL_FIELD_USER_NUM_UDFS)]; 
} opennsl_field_qset_t;

#define OPENNSL_FIELD_QSET_INIT(qset)  \
    memset(&(qset), 0, sizeof(opennsl_field_qset_t)) 
#define OPENNSL_FIELD_QSET_ADD(qset, q)  SHR_BITSET(((qset).w), (q)) 
#define OPENNSL_FIELD_QSET_REMOVE(qset, q)  SHR_BITCLR(((qset).w), (q)) 
#define OPENNSL_FIELD_QSET_TEST(qset, q)  SHR_BITGET(((qset).w), (q)) 
#define OPENNSL_FIELD_GROUP_PRIO_ANY    -0x7fffffff 
/** opennsl_field_action_e */
typedef enum opennsl_field_action_e {
    opennslFieldActionCosQNew = 0,      /**< Change CoS Queue; param0: New CoS
                                           Queue. */
    opennslFieldActionCosQCpuNew = 1,   /**< Change CoS Queue when CopyToCpu;
                                           param0: New CoS Queue. */
    opennslFieldActionPrioIntNew = 14,  /**< Internal priority from arg; param0:
                                           New priority. */
    opennslFieldActionDscpNew = 20,     /**< Change DSCP value; param0: New DSCP
                                           value. */
    opennslFieldActionDscpCancel = 21,  /**< Override another rule. */
    opennslFieldActionCopyToCpu = 23,   /**< Copy to CPU. */
    opennslFieldActionCopyToCpuCancel = 24, /**< Override another rule. */
    opennslFieldActionRedirectPort = 29, /**< Redirect Packet to single port;
                                           param0: Destination modid; param1:
                                           Destination port. */
    opennslFieldActionRedirectTrunk = 30, /**< Redirect Packet to a trunk; param0:
                                           Destination trunk ID. */
    opennslFieldActionDrop = 39,        /**< Drop. */
    opennslFieldActionDropCancel = 40,  /**< Override another rule. */
    opennslFieldActionMirrorOverride = 41, /**< Override any mirroring for packet. */
    opennslFieldActionMirrorIngress = 42, /**< Ingress mirror; param0: Dest modid;
                                           param1: Dest port/tgid. */
    opennslFieldActionMirrorEgress = 43, /**< Egress mirror; param0: Dest modid;
                                           param1: Dest port/tgid. */
    opennslFieldActionL3Switch = 48,    /**< L3-switch packet; param0: ECMP or
                                           next hop info. */
    opennslFieldActionRpDrop = 52,      /**< Red Priority Drop. */
    opennslFieldActionRpDropCancel = 53, /**< Override another rule. */
    opennslFieldActionRpCopyToCpu = 55, /**< Red Priority Copy to CPU. */
    opennslFieldActionRpCopyToCpuCancel = 56, /**< Override another rule. */
    opennslFieldActionRpDscpNew = 61,   /**< Red packet change DSCP value; param0:
                                           New DSCP value. */
    opennslFieldActionRpDscpCancel = 62, /**< Override any changes to DSCP field. */
    opennslFieldActionRpCosQNew = 72,   /**< Red packet change CoS Queue; param0:
                                           New CoS Queue. */
    opennslFieldActionYpDrop = 84,      /**< Yellow Priority Drop. */
    opennslFieldActionYpDropCancel = 85, /**< Override another rule. */
    opennslFieldActionYpCopyToCpu = 87, /**< Yellow Priority Copy to CPU. */
    opennslFieldActionYpCopyToCpuCancel = 88, /**< Override another rule. */
    opennslFieldActionYpDscpNew = 93,   /**< Yellow packet change DSCP value;
                                           param0: New DSCP value. */
    opennslFieldActionYpDscpCancel = 94, /**< Override any changes to DSCP field. */
    opennslFieldActionYpCosQNew = 104,  /**< Yellow packet change CoS Queue;
                                           param0: New CoS Queue. */
    opennslFieldActionClassDestSet = 119, /**< Set destination address lookup class
                                           ID. */
    opennslFieldActionClassSet = opennslFieldActionClassDestSet, /**< Same as
                                           opennslFieldActionClassDestSet. */
    opennslFieldActionClassSourceSet = 120, /**< Set source address lookup class ID. */
    opennslFieldActionGpDrop = 136,     /**< Green Priority Drop. */
    opennslFieldActionGpDropCancel = 137, /**< Override another rule. */
    opennslFieldActionGpCopyToCpu = 139, /**< Green Priority Copy to CPU. */
    opennslFieldActionGpCopyToCpuCancel = 140, /**< Override another rule. */
    opennslFieldActionGpDscpNew = 145,  /**< Green packet change DSCP value;
                                           param0: New DSCP value. */
    opennslFieldActionGpDscpCancel = 146, /**< Override any changes to DSCP field. */
    opennslFieldActionGpCosQNew = 158,  /**< Green packet change CoS Queue;
                                           param0: New CoS Queue. */
    opennslFieldActionNewClassId = 178, /**< Assign new classification ID. */
    opennslFieldActionRpRedirectPort = 184, /**< Redirect red packet to single port;
                                           param0: Destination modid; param1:
                                           Destination port. */
    opennslFieldActionRpMirrorIngress = 185, /**< Red packet ingress mirror; param0:
                                           Dest modid; param1: Dest port/tgid. */
    opennslFieldActionGpRedirectPort = 204, /**< Redirect green packet to single port;
                                           param0: Destination modid; param1:
                                           Destination port. */
    opennslFieldActionGpMirrorIngress = 205, /**< Green packet ingress mirror; param0:
                                           Dest modid; param1: Dest port/tgid. */
    opennslFieldActionEgressClassSelect = 235, /**< Select class to pass to EFP */
    opennslFieldActionStat0 = 243,      /**< Update statistics (statId in param0)
                                           on entry hit.  See
                                           opennsl_field_entry_stat_attach and
                                           related APIs. */
    opennslFieldActionStat = opennslFieldActionStat0, /**< Alias for opennslFieldActionStat0 */
    opennslFieldActionPolicerLevel0 = 244, /**< Apply policer (policerId in param0)
                                           to traffic hitting this entry.  See
                                           opennsl_field_entry_policer_attach
                                           and related APIs. */
    opennslFieldActionUsePolicerResult = 252, /**< Specify/override where policer result
                                           will be used for matched packets. 
                                           See
                                           OPENNSL_FIELD_USE_POLICER_RESULT_*
                                           for flags that go in param0. */
    opennslFieldActionSnoop = 255,      /**< Snoop matched packets (treat them
                                           according to the specified snoop
                                           profile) */
    opennslFieldActionYpMirrorIngress = 295, /**< Yellow packet ingress mirror; param0:
                                           Dest modid; param1: Dest port/tgid. */
    opennslFieldActionYpRedirectPort = 296, /**< Redirect yellow packet to single
                                           port; param0: Destination modid;
                                           param1: Destination port. */
    opennslFieldActionIngSampleEnable = 315, /**< Set the SFLOW Ingress Sampling. */
    opennslFieldActionEgrSampleEnable = 316, /**< Set the SFLOW Egress Sampling. */
    opennslFieldActionCount = 466       /**< Always Last. Not a usable value. */
} opennsl_field_action_t;

/** Holds which action to set width for, and the size of width to set */
typedef struct opennsl_field_action_width_s {
    uint32 action;  
    uint32 width;   
    uint8 valid;    
} opennsl_field_action_width_t;

/** 
 * Used to specify the actions that can be taken by the entries in a
 * group
 */
typedef struct opennsl_field_aset_s {
    SHR_BITDCL w[_SHR_BITDCLSIZE(opennslFieldActionCount)]; 
    opennsl_field_action_width_t actions_width[16]; /**< Actions width struct, used by
                                           opennsl_petra_field_action_width_set
                                           to set width for certain action, 16
                                           is max_actions_per_db */
} opennsl_field_aset_t;

#define OPENNSL_FIELD_ASET_INIT(aset)  \
    memset(&(aset), 0, sizeof(opennsl_field_aset_t)) 
#define OPENNSL_FIELD_ASET_ADD(aset, q)  SHR_BITSET(((aset).w), (q)) 
#define OPENNSL_FIELD_ASET_REMOVE(aset, q)  SHR_BITCLR(((aset).w), (q)) 
#define OPENNSL_FIELD_ASET_TEST(aset, q)  SHR_BITGET(((aset).w), (q)) 
#define OPENNSL_FIELD_PRESEL_INIT(presel_set)  \
    memset(&(presel_set), 0, sizeof(opennsl_field_presel_set_t)) 
#define OPENNSL_FIELD_PRESEL_ADD(presel_set, presel_id)  SHR_BITSET(((presel_set).w), (presel_id)) 
#define OPENNSL_FIELD_PRESEL_REMOVE(presel_set, presel_id)  SHR_BITCLR(((presel_set).w), (presel_id)) 
#define OPENNSL_FIELD_PRESEL_TEST(presel_set, presel_id)  SHR_BITGET(((presel_set).w), (presel_id)) 
/** Field Group Status structure. */
typedef struct opennsl_field_group_status_s {
    int prio_min;       /**< Minimum priority within group. */
    int prio_max;       /**< Maximum priority within group. */
    int entries_total;  /**< Total possible entries in group. */
    int entries_free;   /**< Unused entries in slice. */
    int counters_total; /**< Total possible counters in slice. */
    int counters_free;  /**< Unused counters in slice. */
    int meters_total;   /**< Total meters in slice. */
    int meters_free;    /**< Unused meters in slice. */
    int entry_count;    /**< Number of entries in the group. */
    int counter_count;  /**< Number of counters attached to group entries. */
    int meter_count;    /**< Number of meters attached to group entries. */
} opennsl_field_group_status_t;

/** Group Modes (single, double or triple wide). */
typedef enum opennsl_field_group_mode_e {
    opennslFieldGroupModeSingle = 0,    /**< Single-wide group. */
    opennslFieldGroupModeDouble = 1,    /**< Double-wide group. */
    opennslFieldGroupModeAuto = 4,      /**< Auto-expand group based on Qset
                                           (default). */
} opennsl_field_group_mode_t;

#define OPENNSL_FIELD_PRESEL_SEL_MAX    1024       /**< Maximum Preselection
                                                      entries supported. */
/** Bitmap of all possible preselection specification IDs. */
typedef struct opennsl_field_presel_set_s {
    SHR_BITDCL w[_SHR_BITDCLSIZE(OPENNSL_FIELD_PRESEL_SEL_MAX)]; 
} opennsl_field_presel_set_t;

/***************************************************************************//** 
 *\brief Initialize field software subsystem.
 *
 *\description Initializes the field software and hardware subsystem. Enables
 *          field support and clears the hardware tables. Initializes the
 *          metering function.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNAVAIL Feature unavailable on this device
 *\retval    OPENNSL_E_MEMORY Memory allocation failure
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_field_init(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief De-initialize field software subsystem.
 *
 *\description Uninitializes the field software and hardware subsystem.  Disables
 *          field support in the hardware and releases memory resources held
 *          by the software module.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_field_detach(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create a field group.
 *
 *\description Creates a field group with a specified priority and qualifier set.
 *          The _id variant requests that a particular group identifier be
 *          assigned, and may be useful when handles are desired to be the
 *          same across multiple chips. opennsl_field_group_wlan_xxx groups
 *          apply to WLAN tunnel terminated frames.  Incoming port can not be
 *          used as match criteria for WLAN traffic.
 *
 *\param    unit [IN]   Unit number.
 *\param    qset [IN]   Field qualifier set
 *\param    pri [IN]   Priority within allowable range or
 *          OPENNSL_FIELD_GROUP_PRIO_ANY to automatically assign a priority.
 *          Higher numerical value for priority has better priority for conflict
 *          resolution when there is a search hit on multiple slices. See
 *          =fp_groups for priority value restrictions.
 *\param    group [OUT]   (for _create_id and _create_mode_id) Field group ID
 *
 *\retval    OPENNSL_E_NONE Successful creation of group
 *\retval    OPENNSL_E_INIT Field module not initialized on unit
 *\retval    OPENNSL_E_RESOURCE Hardware slice/port unavailable or no select codes
 *          can satisfy Qset.
 *\retval    OPENNSL_E_CONFIG If device does not support virtual group priority
 *          feature, then this error code is returned when specified priority
 *          value is already assigned to another group.
 *\retval    OPENNSL_E_PARAM Priority out of range
 *\retval    OPENNSL_E_EXISTS Requested group ID already exists
 *\retval    OPENNSL_E_MEMORY Allocation failure
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_field_group_create(
    int unit, 
    opennsl_field_qset_t qset, 
    int pri, 
    opennsl_field_group_t *group) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create a field group.
 *
 *\description Creates a field group with a specified priority and qualifier set.
 *          The _id variant requests that a particular group identifier be
 *          assigned, and may be useful when handles are desired to be the
 *          same across multiple chips. opennsl_field_group_wlan_xxx groups
 *          apply to WLAN tunnel terminated frames.  Incoming port can not be
 *          used as match criteria for WLAN traffic.
 *
 *\param    unit [IN]   Unit number.
 *\param    qset [IN]   Field qualifier set
 *\param    pri [IN]   Priority within allowable range or
 *          OPENNSL_FIELD_GROUP_PRIO_ANY to automatically assign a priority.
 *          Higher numerical value for priority has better priority for conflict
 *          resolution when there is a search hit on multiple slices. See
 *          =fp_groups for priority value restrictions.
 *\param    group [IN]   (for _create_id and _create_mode_id) Field group ID
 *
 *\retval    OPENNSL_E_NONE Successful creation of group
 *\retval    OPENNSL_E_INIT Field module not initialized on unit
 *\retval    OPENNSL_E_RESOURCE Hardware slice/port unavailable or no select codes
 *          can satisfy Qset.
 *\retval    OPENNSL_E_CONFIG If device does not support virtual group priority
 *          feature, then this error code is returned when specified priority
 *          value is already assigned to another group.
 *\retval    OPENNSL_E_PARAM Priority out of range
 *\retval    OPENNSL_E_EXISTS Requested group ID already exists
 *\retval    OPENNSL_E_MEMORY Allocation failure
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_field_group_create_id(
    int unit, 
    opennsl_field_qset_t qset, 
    int pri, 
    opennsl_field_group_t group) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create a field group.
 *
 *\description Creates a field group with a specified priority and qualifier set.
 *          The _id variant requests that a particular group identifier be
 *          assigned, and may be useful when handles are desired to be the
 *          same across multiple chips. opennsl_field_group_wlan_xxx groups
 *          apply to WLAN tunnel terminated frames.  Incoming port can not be
 *          used as match criteria for WLAN traffic.
 *
 *\param    unit [IN]   Unit number.
 *\param    qset [IN]   Field qualifier set
 *\param    pri [IN]   Priority within allowable range or
 *          OPENNSL_FIELD_GROUP_PRIO_ANY to automatically assign a priority.
 *          Higher numerical value for priority has better priority for conflict
 *          resolution when there is a search hit on multiple slices. See
 *          =fp_groups for priority value restrictions.
 *\param    mode [IN]   See =fp_group_mode for a list of modes.
 *\param    group [OUT]   (for _create_id and _create_mode_id) Field group ID
 *
 *\retval    OPENNSL_E_NONE Successful creation of group
 *\retval    OPENNSL_E_INIT Field module not initialized on unit
 *\retval    OPENNSL_E_RESOURCE Hardware slice/port unavailable or no select codes
 *          can satisfy Qset.
 *\retval    OPENNSL_E_CONFIG If device does not support virtual group priority
 *          feature, then this error code is returned when specified priority
 *          value is already assigned to another group.
 *\retval    OPENNSL_E_PARAM Priority out of range
 *\retval    OPENNSL_E_EXISTS Requested group ID already exists
 *\retval    OPENNSL_E_MEMORY Allocation failure
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_field_group_create_mode(
    int unit, 
    opennsl_field_qset_t qset, 
    int pri, 
    opennsl_field_group_mode_t mode, 
    opennsl_field_group_t *group) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create a field group.
 *
 *\description Creates a field group with a specified priority and qualifier set.
 *          The _id variant requests that a particular group identifier be
 *          assigned, and may be useful when handles are desired to be the
 *          same across multiple chips. opennsl_field_group_wlan_xxx groups
 *          apply to WLAN tunnel terminated frames.  Incoming port can not be
 *          used as match criteria for WLAN traffic.
 *
 *\param    unit [IN]   Unit number.
 *\param    qset [IN]   Field qualifier set
 *\param    pri [IN]   Priority within allowable range or
 *          OPENNSL_FIELD_GROUP_PRIO_ANY to automatically assign a priority.
 *          Higher numerical value for priority has better priority for conflict
 *          resolution when there is a search hit on multiple slices. See
 *          =fp_groups for priority value restrictions.
 *\param    mode [IN]   See =fp_group_mode for a list of modes.
 *\param    group [IN]   (for _create_id and _create_mode_id) Field group ID
 *
 *\retval    OPENNSL_E_NONE Successful creation of group
 *\retval    OPENNSL_E_INIT Field module not initialized on unit
 *\retval    OPENNSL_E_RESOURCE Hardware slice/port unavailable or no select codes
 *          can satisfy Qset.
 *\retval    OPENNSL_E_CONFIG If device does not support virtual group priority
 *          feature, then this error code is returned when specified priority
 *          value is already assigned to another group.
 *\retval    OPENNSL_E_PARAM Priority out of range
 *\retval    OPENNSL_E_EXISTS Requested group ID already exists
 *\retval    OPENNSL_E_MEMORY Allocation failure
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_field_group_create_mode_id(
    int unit, 
    opennsl_field_qset_t qset, 
    int pri, 
    opennsl_field_group_mode_t mode, 
    opennsl_field_group_t group) LIB_DLL_EXPORTED ;

typedef int (*opennsl_field_group_traverse_cb)(
    int unit, 
    opennsl_field_group_t group, 
    void *user_data);

/***************************************************************************//** 
 *\brief Traverse all the fp groups on the device, calling a specified callback
 *       for each valid group.
 *
 *\description Traverse all the fp groups on the device, calling a specified
 *          callback  for each valid group.
 *
 *\param    unit [IN]   Unit number.
 *\param    callback [IN]   User provided callback.
 *\param    user_data [IN]   User callback cookie.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_field_group_traverse(
    int unit, 
    opennsl_field_group_traverse_cb callback, 
    void *user_data) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Change or retrieve the qualifiers for a field group.
 *
 *\description The set call changes the qualifier set for the specified group. 
 *          If no entries exist in this group, then updates are always
 *          permitted.  If entries exist, then updates are permitted only if
 *          it can be satisfied with the current selection of field selector
 *          encodings dependent on chip architecture. It is assumed that
 *          existing entries are depending on the Qset present when the
 *          entries were created. This means that setting a new Qset will only
 *          add qualifiers. If the old Qset contains qualifiers that does not
 *          exist in the new Qset, a union of the two Qsets will be performed
 *          in the setting operation.
 *          The get call retrieves the qualifier set for a specified group.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Field group ID
 *\param    qset [IN]   (for _set) Field qualifier set
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_PARAM qset points to NULL
 ******************************************************************************/
extern int opennsl_field_group_set(
    int unit, 
    opennsl_field_group_t group, 
    opennsl_field_qset_t qset) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Change or retrieve the qualifiers for a field group.
 *
 *\description The set call changes the qualifier set for the specified group. 
 *          If no entries exist in this group, then updates are always
 *          permitted.  If entries exist, then updates are permitted only if
 *          it can be satisfied with the current selection of field selector
 *          encodings dependent on chip architecture. It is assumed that
 *          existing entries are depending on the Qset present when the
 *          entries were created. This means that setting a new Qset will only
 *          add qualifiers. If the old Qset contains qualifiers that does not
 *          exist in the new Qset, a union of the two Qsets will be performed
 *          in the setting operation.
 *          The get call retrieves the qualifier set for a specified group.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Field group ID
 *\param    qset [OUT]   (for _set) Field qualifier set
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_PARAM qset points to NULL
 ******************************************************************************/
extern int opennsl_field_group_get(
    int unit, 
    opennsl_field_group_t group, 
    opennsl_field_qset_t *qset) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Change or retrieve the actions for a field group.
 *
 *\description The set call changes the action set for the specified group.  If
 *          no entries exist in this group, then updates are always permitted.
 *           If entries exist, then updates are permitted only if it can be
 *          satisfied with the current selection of field action encodings
 *          dependent on chip architecture. It is assumed that existing
 *          entries are depending on the Aset present when the entries were
 *          created. This means that setting a new Aset will only add actions.
 *          If the old Aset contains actions that do not exist in the new
 *          Aset, a union of the two Asets will be performed in the setting
 *          operation.
 *          The get call retrieves the action set for a specified group.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Field group ID
 *\param    aset [IN]   (for _set) Field action set
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_PARAM qset points to NULL
 ******************************************************************************/
extern int opennsl_field_group_action_set(
    int unit, 
    opennsl_field_group_t group, 
    opennsl_field_aset_t aset) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Change or retrieve the actions for a field group.
 *
 *\description The set call changes the action set for the specified group.  If
 *          no entries exist in this group, then updates are always permitted.
 *           If entries exist, then updates are permitted only if it can be
 *          satisfied with the current selection of field action encodings
 *          dependent on chip architecture. It is assumed that existing
 *          entries are depending on the Aset present when the entries were
 *          created. This means that setting a new Aset will only add actions.
 *          If the old Aset contains actions that do not exist in the new
 *          Aset, a union of the two Asets will be performed in the setting
 *          operation.
 *          The get call retrieves the action set for a specified group.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Field group ID
 *\param    aset [OUT]   (for _set) Field action set
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_PARAM qset points to NULL
 ******************************************************************************/
extern int opennsl_field_group_action_get(
    int unit, 
    opennsl_field_group_t group, 
    opennsl_field_aset_t *aset) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Deallocates a field group.
 *
 *\description Deallocates a field group.
 *          All entries that uses this group must have been destroyed before
 *          calling this routine, or the call will fail.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Field group ID
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_NOT_FOUND Group ID not found in unit
 *\retval    OPENNSL_E_BUSY Entries still exist in the group
 ******************************************************************************/
extern int opennsl_field_group_destroy(
    int unit, 
    opennsl_field_group_t group) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Retrieve status of a specified field group.
 *
 *\description Retrieves the status of a specified group.  See =fp_group_status
 *          for a description of the status information returned.  For
 *          auto-expanding groups, resources from unused slices are included
 *          in the counts.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Field group ID
 *\param    status [OUT]   Status for field group
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_NOT_FOUND Group ID not found in unit
 *\retval    OPENNSL_E_PARAM status points to NULL
 ******************************************************************************/
extern int opennsl_field_group_status_get(
    int unit, 
    opennsl_field_group_t group, 
    opennsl_field_group_status_t *status) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set the group enable state.
 *
 *\description Packet lookup can be enabled or disabled on a group. This allows
 *          offline changes to be made to a group, which avoids possibly
 *          unwanted intermediate states.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Field group ID
 *\param    enable [IN]   (for _set) Packet lookup Enable(1) or Disable (0) state
 *          of group
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT Field not initialized on unit
 *\retval    OPENNSL_E_NOT_FOUND Group ID not found for this unit
 *\retval    OPENNSL_E_UNAVAIL OPENNSL device does not have enable/disable feature
 ******************************************************************************/
extern int opennsl_field_group_enable_set(
    int unit, 
    opennsl_field_group_t group, 
    int enable) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set the group enable state.
 *
 *\description Packet lookup can be enabled or disabled on a group. This allows
 *          offline changes to be made to a group, which avoids possibly
 *          unwanted intermediate states.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Field group ID
 *\param    enable [OUT]   (for _set) Packet lookup Enable(1) or Disable (0) state
 *          of group
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT Field not initialized on unit
 *\retval    OPENNSL_E_NOT_FOUND Group ID not found for this unit
 *\retval    OPENNSL_E_UNAVAIL OPENNSL device does not have enable/disable feature
 ******************************************************************************/
extern int opennsl_field_group_enable_get(
    int unit, 
    opennsl_field_group_t group, 
    int *enable) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Allocate a range checker with specified configuration.
 *
 *\description Creates a virtual Layer 4 TCP/UDP port range checker.  The
 *          required hardware resources are allocated and programmed.  The
 *          resulting range identifier can be passed to
 *          opennsl_field_qualify_RangeCheck.  The range can be inverted using
 *          the 'invert' argument to opennsl_field_qualify_RangeCheck. In
 *          network switch, only an external entry can qualify on an external
 *          range checker. In TBx, the control flag OPENNSL_FIELD_RANGE_LOOKUP
 *          can be configured for range check in IVM.
 *          The opennsl_field_range_create_id call uses an arbitrary
 *          user-specified value to identify the range checker.  The
 *          opennsl_field_range_create call picks an arbitrary non-zero unused
 *          identifier.
 *
 *\param    unit [IN]   Unit number.
 *\param    range [OUT]   (for _create_id) Range check ID
 *\param    flags [IN]   Range control flags =RANGE_CONTROL_FLAGS_table
 *\param    min [IN]   Lowest port number to match (inclusive)
 *\param    max [IN]   Highest port number to match (inclusive)
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL field module not initialized
 *\retval    OPENNSL_E_EXISTS Range check ID already in use
 *\retval    OPENNSL_E_XXX Error code
 ******************************************************************************/
extern int opennsl_field_range_create(
    int unit, 
    opennsl_field_range_t *range, 
    uint32 flags, 
    opennsl_l4_port_t min, 
    opennsl_l4_port_t max) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Install all entries of a field group into the hardware tables.
 *
 *\description Installs a group of entries into the hardware tables. Will
 *          silently reinstall entries already in the hardware tables. The
 *          opennsl_field_group_t object is not consumed or destroyed. It can
 *          be used to remove or update the entry.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Field group ID
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_NOT_FOUND Group ID is not in use
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_field_group_install(
    int unit, 
    opennsl_field_group_t group) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Retrieve parameters associated with an existing range checker.
 *
 *\description Retrieves information that was used when a virtual range checker
 *          was created.
 *
 *\param    unit [IN]   Unit number.
 *\param    range [IN]   Range check ID
 *\param    flags [OUT]   Range control flags =RANGE_CONTROL_FLAGS_RANGE_table
 *\param    min [OUT]   Lowest port number to match (inclusive)
 *\param    max [OUT]   Highest port number to match (inclusive)
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL field module not initialized
 *\retval    OPENNSL_E_NOT_FOUND Range check ID not found
 *\retval    OPENNSL_E_XXX Error code
 ******************************************************************************/
extern int opennsl_field_range_get(
    int unit, 
    opennsl_field_range_t range, 
    uint32 *flags, 
    opennsl_l4_port_t *min, 
    opennsl_l4_port_t *max) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroy a virtual range checker.
 *
 *\description Deallocates a virtual range checker.  Associated hardware
 *          resources are freed if there are no other virtual range checkers
 *          using the same resources.
 *
 *\param    unit [IN]   Unit number.
 *\param    range [IN]   Range check ID
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL field module not initialized
 *\retval    OPENNSL_E_NOT_FOUND Range check ID not found
 *\retval    OPENNSL_E_XXX Error code
 ******************************************************************************/
extern int opennsl_field_range_destroy(
    int unit, 
    opennsl_field_range_t range) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create a blank field entry.
 *
 *\description Creates an empty field entry based on a field group. The _id
 *          variant requests that a particular entry identifier be assigned.
 *          Entry IDs 0xFFFFFFFF to 0xFFFFF000 are reserved for internal use.
 *          To destroy the field entry, use =opennsl_field_entry_destroy api.
 *          .
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Field group ID
 *\param    entry [OUT]   (for _create_id) Field entry ID
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_NOT_FOUND Group ID not found in unit
 *\retval    OPENNSL_E_EXISTS Requested entry ID already exists
 *\retval    OPENNSL_E_BADID Requested entry ID out-of-range
 *\retval    OPENNSL_E_PARAM *entry points to NULL
 *\retval    OPENNSL_E_MEMORY Memory allocation failure
 *\retval    OPENNSL_E_RESOURCE No unused entries available
 ******************************************************************************/
extern int opennsl_field_entry_create(
    int unit, 
    opennsl_field_group_t group, 
    opennsl_field_entry_t *entry) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create a blank field entry.
 *
 *\description Creates an empty field entry based on a field group. The _id
 *          variant requests that a particular entry identifier be assigned.
 *          Entry IDs 0xFFFFFFFF to 0xFFFFF000 are reserved for internal use.
 *          To destroy the field entry, use =opennsl_field_entry_destroy api.
 *          .
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Field group ID
 *\param    entry [IN]   (for _create_id) Field entry ID
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_NOT_FOUND Group ID not found in unit
 *\retval    OPENNSL_E_EXISTS Requested entry ID already exists
 *\retval    OPENNSL_E_BADID Requested entry ID out-of-range
 *\retval    OPENNSL_E_PARAM *entry points to NULL
 *\retval    OPENNSL_E_MEMORY Memory allocation failure
 *\retval    OPENNSL_E_RESOURCE No unused entries available
 ******************************************************************************/
extern int opennsl_field_entry_create_id(
    int unit, 
    opennsl_field_group_t group, 
    opennsl_field_entry_t entry) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get an array of entry IDs in use in a group.
 *
 *\description Fills an array with the entry IDs for the specified group.  This
 *          should first be called with an entry_size of 0 to get the number
 *          of entries to be returned, so that an appropriately-sized array
 *          can be allocated.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Field group ID
 *\param    entry_size [IN]   The maximum number of entry IDs to return.  If 0,
 *          the number of entries is returned
 *\param    entry_array [OUT]   A pointer to a memory buffer to hold the array of
 *          IDs
 *\param    entry_count [OUT]   A pointer to store the number of entries returned
 *          or, if entry_size is 0, the number of entries available
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_NOT_FOUND Group ID not found in unit
 *\retval    OPENNSL_E_MEMORY Memory allocation failure
 ******************************************************************************/
extern int opennsl_field_entry_multi_get(
    int unit, 
    opennsl_field_group_t group, 
    int entry_size, 
    opennsl_field_entry_t *entry_array, 
    int *entry_count) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroy a field entry.
 *
 *\description This API deallocates the memory, which contains a software field
 *          entry. If the entry has been installed in hardware, the function
 *          would invoke a opennsl_field_entry_remove API to clean up the
 *          entry in hardware and  free hardware resources. .
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]   Field entry ID
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_NOT_FOUND Entry ID not found in unit
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_field_entry_destroy(
    int unit, 
    opennsl_field_entry_t entry) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroy all field entries.
 *
 *\description Destroys all field entries.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_XXX Other Error code
 ******************************************************************************/
extern int opennsl_field_entry_destroy_all(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create a copy of an existing field entry.
 *
 *\description Creates a copy of an existing field entry.
 *          The _id variant requests that a particular entry identifier be
 *          assigned.  The entry identifier is the same as the priority of the
 *          entry.  Higher numbers represent higher priority.  The value must
 *          be in the range prio_min through prio_max (as returned by.
 *
 *\param    unit [IN]   Unit number.
 *\param    src_entry [IN]   Field entry ID to copy from
 *\param    dst_entry [OUT]   (for _copy_id) New entry copied from src_entry
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_NOT_FOUND Source entry ID not found
 *\retval    OPENNSL_E_EXISTS Requested entry ID already exists
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_field_entry_copy(
    int unit, 
    opennsl_field_entry_t src_entry, 
    opennsl_field_entry_t *dst_entry) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Install a field entry into the hardware tables.
 *
 *\description Installs an entry into the hardware tables. The entry should be
 *          configured before installing by adding qualifications using.
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]   Field entry ID
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_NOT_FOUND Entry ID not found
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_field_entry_install(
    int unit, 
    opennsl_field_entry_t entry) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Re-install a field entry into the hardware tables.
 *
 *\description Re-installs an entry into the hardware tables.  This call may only
 *          be used to change the actions associated with an entry that is
 *          already installed in the hardware table.  It avoids the need to
 *          completely delete and re-add the entry.
 *          Hitless entry install: Hitless entry install provides the
 *          capability to apply existing rules of the already installed entry
 *          to the incoming traffic while updating new modifications on the
 *          entry in the hardware tables. For achieving entry hitless update,
 *          it is recommended that the entries created in a group should have
 *          unique priority. Eventhough entry installation might not result in
 *          hitless update in the following cases 1. Entry hitless update
 *          can't be achieved if all the slices are full with entries. 2.
 *          Entry installation might not result in hitless update if
 *          non-global counters/flex stats or non-global meters    are
 *          attached to the entry.
 *          In the above two cases entry installation might result in error,
 *          if config property field_atomic_update is set.
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]   Field entry ID
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_NOT_FOUND Entry ID not found
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_field_entry_reinstall(
    int unit, 
    opennsl_field_entry_t entry) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Remove a field entry from the hardware tables.
 *
 *\description Removes an entry from the hardware tables.  This does not destroy
 *          the entry; it only uninstalls it from the hardware tables. 
 *          Destroy an entry using =opennsl_field_entry_destroy .
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]   Field entry ID
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_NOT_FOUND Entry ID not found
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_field_entry_remove(
    int unit, 
    opennsl_field_entry_t entry) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Attach a policer to a field entry.
 *
 *\description Attach a policer to a field entry. Global policers associated with
 *          Lookup  stage entries are given highest priority over policers
 *          associated with other resources (Port, Vlan translate etc) when
 *          following flag is specified in level parameter.     
 *          OPENNSL_FIELD_POLICER_GLOBAL_METER_USE_STAGE_LOOKUP_ACTION 0x1
 *          See opennsl_policer_xxx APIs for policer creation and properties
 *          definition.
 *
 *\param    unit [IN]   Unit number.
 *\param    entry_id [IN]   Field entry ID.
 *\param    level [IN]   Policer level.
 *\param    policer_id [IN]   Policer ID.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_field_entry_policer_attach(
    int unit, 
    opennsl_field_entry_t entry_id, 
    int level, 
    opennsl_policer_t policer_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Detach a policer from a field entry. When the API is called, the policer
 *       is marked as detached but it is not completely detached from the entry.
 *       This is because, the policer and meter entries are updated in the
 *       hardware during entry re-install. So, this API should always be followed
 *       by entry remove or entry re-install to completely detach the policer
 *       from the entry.
 *
 *\description Detach a policer from a field entry.
 *
 *\param    unit [IN]   Unit number.
 *\param    entry_id [IN]   Field entry ID.
 *\param    level [IN]   Policer level.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_field_entry_policer_detach(
    int unit, 
    opennsl_field_entry_t entry_id, 
    int level) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the policer(s) attached to a field entry.
 *
 *\description Get the policer(s) attached to a field entry.
 *
 *\param    unit [IN]   Unit number.
 *\param    entry_id [IN]   Field entry ID.
 *\param    level [IN]   Policer level.
 *\param    policer_id [OUT]   Policer ID.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_field_entry_policer_get(
    int unit, 
    opennsl_field_entry_t entry_id, 
    int level, 
    opennsl_policer_t *policer_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get/Set the priority for an entry within a group.
 *
 *\description Sets or gets the priority class of an entry within a group.
 *          Entries with higher priority values take precedence over entries
 *          with lower values. Since TCAM lookups start at low indexes,
 *          precedence within a physical slice is the reverse of this. The
 *          effect of this is that entries with the greatest priority will
 *          have the lowest TCAM index. Change in Field entry priority may
 *          require movement of the entry in the same or across the slices.
 *          Stat, Policer attached to an entry must be moved in hardware
 *          during entry move operation if CAP stage does not support global
 *          counters and global meters.
 *          Entries should have only positive priority values. Negative ones
 *          are reserved for pre-defined cases. Currently there are four
 *          predefined cases:.
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]   Field entry ID
 *\param    prio [OUT]   (for _set) Entry priority
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit/Field stage not initialized
 *\retval    OPENNSL_E_NOT_FOUND
 *\retval    
 *\retval     Group ID/Field Entry ID/Field stage not found
 *\retval     in unit
 *\retval    
 *\retval     Policer ID attached to entry not found.
 *\retval    
 *\retval     Stat ID attached to entry not found.
 *\retval    
 *\retval    OPENNSL_E_PARAM
 *\retval    
 *\retval     *entry points to NULL (opennsl_field_entry_prio_get)
 *\retval    
 *\retval     Preliminary resource check before actual entry
 *\retval     move operation detects that no free entry is
 *\retval     available in target slice.
 *\retval    
 *\retval     In device CAP stage that do not support global meter
 *\retval     pools and global counter pools, entry move requires
 *\retval     a Stat, Policer move in hardware and preliminary
 *\retval     resource check before actual entry move operation
 *\retval     detects that no free counters, meters are available
 *\retval     in target slice.
 *\retval    
 *\retval    OPENNSL_E_INTERNAL
 *\retval    
 *\retval     Invalid hardware resource allocation by other
 *\retval     Field API's (could be wrong slice id, policer slice
 *\retval     index), although this should not happen.
 *\retval    
 *\retval     Invalid Field entry id.
 *\retval    
 *\retval     Invalid Policer slice index.
 *\retval    
 *\retval     Invalid hardware meter/counter index.
 *\retval    
 *\retval    OPENNSL_E_CONFIG
 *\retval    
 *\retval     If change in priority of field entry requires
 *\retval     movement of the entry and there are no free
 *\retval     entries in any of the slices belonging to
 *\retval     this group,
 *\retval    
 *\retval     Invalid Flex Stat mode in Lookup Stage
 *\retval    
 *\retval    OPENNSL_E_RESOURCE This error code is returned when Stat, Policer
 *\retval     attached to an entry must be moved in hardware
 *\retval     during entry move operation as device CAP stage
 *\retval     does not support global counters and global
 *\retval     meters and no meters, counters are available
 *\retval     in the target slice while actual entry move
 *\retval     happens.
 *\retval    OPENNSL_E_UNAVAIL Unknown Field external stage
 *          (opennsl_field_entry_prio_set).
 ******************************************************************************/
extern int opennsl_field_entry_prio_get(
    int unit, 
    opennsl_field_entry_t entry, 
    int *prio) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get/Set the priority for an entry within a group.
 *
 *\description Sets or gets the priority class of an entry within a group.
 *          Entries with higher priority values take precedence over entries
 *          with lower values. Since TCAM lookups start at low indexes,
 *          precedence within a physical slice is the reverse of this. The
 *          effect of this is that entries with the greatest priority will
 *          have the lowest TCAM index. Change in Field entry priority may
 *          require movement of the entry in the same or across the slices.
 *          Stat, Policer attached to an entry must be moved in hardware
 *          during entry move operation if CAP stage does not support global
 *          counters and global meters.
 *          Entries should have only positive priority values. Negative ones
 *          are reserved for pre-defined cases. Currently there are four
 *          predefined cases:.
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]   Field entry ID
 *\param    prio [IN]   (for _set) Entry priority
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit/Field stage not initialized
 *\retval    OPENNSL_E_NOT_FOUND
 *\retval    
 *\retval     Group ID/Field Entry ID/Field stage not found
 *\retval     in unit
 *\retval    
 *\retval     Policer ID attached to entry not found.
 *\retval    
 *\retval     Stat ID attached to entry not found.
 *\retval    
 *\retval    OPENNSL_E_PARAM
 *\retval    
 *\retval     *entry points to NULL (opennsl_field_entry_prio_get)
 *\retval    
 *\retval     Preliminary resource check before actual entry
 *\retval     move operation detects that no free entry is
 *\retval     available in target slice.
 *\retval    
 *\retval     In device CAP stage that do not support global meter
 *\retval     pools and global counter pools, entry move requires
 *\retval     a Stat, Policer move in hardware and preliminary
 *\retval     resource check before actual entry move operation
 *\retval     detects that no free counters, meters are available
 *\retval     in target slice.
 *\retval    
 *\retval    OPENNSL_E_INTERNAL
 *\retval    
 *\retval     Invalid hardware resource allocation by other
 *\retval     Field API's (could be wrong slice id, policer slice
 *\retval     index), although this should not happen.
 *\retval    
 *\retval     Invalid Field entry id.
 *\retval    
 *\retval     Invalid Policer slice index.
 *\retval    
 *\retval     Invalid hardware meter/counter index.
 *\retval    
 *\retval    OPENNSL_E_CONFIG
 *\retval    
 *\retval     If change in priority of field entry requires
 *\retval     movement of the entry and there are no free
 *\retval     entries in any of the slices belonging to
 *\retval     this group,
 *\retval    
 *\retval     Invalid Flex Stat mode in Lookup Stage
 *\retval    
 *\retval    OPENNSL_E_RESOURCE This error code is returned when Stat, Policer
 *\retval     attached to an entry must be moved in hardware
 *\retval     during entry move operation as device CAP stage
 *\retval     does not support global counters and global
 *\retval     meters and no meters, counters are available
 *\retval     in the target slice while actual entry move
 *\retval     happens.
 *\retval    OPENNSL_E_UNAVAIL Unknown Field external stage
 *          (opennsl_field_entry_prio_set).
 ******************************************************************************/
extern int opennsl_field_entry_prio_set(
    int unit, 
    opennsl_field_entry_t entry, 
    int prio) LIB_DLL_EXPORTED ;

#define OPENNSL_FIELD_QUALIFY_PRESEL    0x40000000 /**< OR with ID when calling
                                                      opennsl_field_qualify_*
                                                      functions to indicate ID
                                                      is a preselector instead
                                                      of an entry */
/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_InPort(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_port_t data, 
    opennsl_port_t mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_OutPort(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_port_t data, 
    opennsl_port_t mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_InPorts(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_pbmp_t data, 
    opennsl_pbmp_t mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data_modid [IN]
 *\param    mask_modid [IN]
 *\param    data_port [IN]
 *\param    mask_port [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_SrcPort(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_module_t data_modid, 
    opennsl_module_t mask_modid, 
    opennsl_port_t data_port, 
    opennsl_port_t mask_port) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data_modid [IN]
 *\param    mask_modid [IN]
 *\param    data_port [IN]
 *\param    mask_port [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_DstPort(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_module_t data_modid, 
    opennsl_module_t mask_modid, 
    opennsl_port_t data_port, 
    opennsl_port_t mask_port) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_DstTrunk(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_trunk_t data, 
    opennsl_trunk_t mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_L4SrcPort(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_l4_port_t data, 
    opennsl_l4_port_t mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_L4DstPort(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_l4_port_t data, 
    opennsl_l4_port_t mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_OuterVlan(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_vlan_t data, 
    opennsl_vlan_t mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_OuterVlanId(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_vlan_t data, 
    opennsl_vlan_t mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_InnerVlanId(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_vlan_t data, 
    opennsl_vlan_t mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_EtherType(
    int unit, 
    opennsl_field_entry_t entry, 
    uint16 data, 
    uint16 mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    if_id [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_DstL3Egress(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_if_t if_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    color [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_Color(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 color) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_IpProtocol(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 data, 
    uint8 mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_PacketRes(
    int unit, 
    opennsl_field_entry_t entry, 
    uint32 data, 
    uint32 mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_SrcIp(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_ip_t data, 
    opennsl_ip_t mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_DstIp(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_ip_t data, 
    opennsl_ip_t mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_DSCP(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 data, 
    uint8 mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_TcpControl(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 data, 
    uint8 mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_Ttl(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 data, 
    uint8 mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    range [IN]
 *\param    invert [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_RangeCheck(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_field_range_t range, 
    int invert) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_SrcIp6(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_ip6_t data, 
    opennsl_ip6_t mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_DstIp6(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_ip6_t data, 
    opennsl_ip6_t mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_Ip6NextHeader(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 data, 
    uint8 mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_Ip6HopLimit(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 data, 
    uint8 mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_SrcMac(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_mac_t data, 
    opennsl_mac_t mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_DstMac(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_mac_t data, 
    opennsl_mac_t mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    type [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_IpType(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_field_IpType_t type) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_InterfaceClassPort(
    int unit, 
    opennsl_field_entry_t entry, 
    uint32 data, 
    uint32 mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_SrcClassField(
    int unit, 
    opennsl_field_entry_t entry, 
    uint32 data, 
    uint32 mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_DstClassField(
    int unit, 
    opennsl_field_entry_t entry, 
    uint32 data, 
    uint32 mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    protocol [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_IpProtocolCommon(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_field_IpProtocolCommon_t protocol) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_L3Routable(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 data, 
    uint8 mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    frag_info [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_IpFrag(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_field_IpFrag_t frag_info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_Vrf(
    int unit, 
    opennsl_field_entry_t entry, 
    uint32 data, 
    uint32 mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    intf_id [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_L3Ingress(
    int unit, 
    opennsl_field_entry_t entry, 
    uint32 intf_id, 
    uint32 mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_MyStationHit(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 data, 
    uint8 mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_IcmpTypeCode(
    int unit, 
    opennsl_field_entry_t entry, 
    uint16 data, 
    uint16 mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    color [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_Color_get(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 *color) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    if_id [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_DstL3Egress_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_if_t *if_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_InPort_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_port_t *data, 
    opennsl_port_t *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_OutPort_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_port_t *data, 
    opennsl_port_t *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_InPorts_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_pbmp_t *data, 
    opennsl_pbmp_t *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data_modid [OUT]
 *\param    mask_modid [OUT]
 *\param    data_port [OUT]
 *\param    mask_port [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_SrcPort_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_module_t *data_modid, 
    opennsl_module_t *mask_modid, 
    opennsl_port_t *data_port, 
    opennsl_port_t *mask_port) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data_modid [OUT]
 *\param    mask_modid [OUT]
 *\param    data_port [OUT]
 *\param    mask_port [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_DstPort_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_module_t *data_modid, 
    opennsl_module_t *mask_modid, 
    opennsl_port_t *data_port, 
    opennsl_port_t *mask_port) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_DstTrunk_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_trunk_t *data, 
    opennsl_trunk_t *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_L4SrcPort_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_l4_port_t *data, 
    opennsl_l4_port_t *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_L4DstPort_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_l4_port_t *data, 
    opennsl_l4_port_t *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_OuterVlan_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_vlan_t *data, 
    opennsl_vlan_t *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_OuterVlanId_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_vlan_t *data, 
    opennsl_vlan_t *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_EtherType_get(
    int unit, 
    opennsl_field_entry_t entry, 
    uint16 *data, 
    uint16 *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_IpProtocol_get(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 *data, 
    uint8 *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_PacketRes_get(
    int unit, 
    opennsl_field_entry_t entry, 
    uint32 *data, 
    uint32 *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_SrcIp_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_ip_t *data, 
    opennsl_ip_t *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_DstIp_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_ip_t *data, 
    opennsl_ip_t *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_DSCP_get(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 *data, 
    uint8 *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_TcpControl_get(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 *data, 
    uint8 *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_Ttl_get(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 *data, 
    uint8 *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    max_count [IN]
 *\param    range [OUT]
 *\param    invert [OUT]
 *\param    count [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_RangeCheck_get(
    int unit, 
    opennsl_field_entry_t entry, 
    int max_count, 
    opennsl_field_range_t *range, 
    int *invert, 
    int *count) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_SrcIp6_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_ip6_t *data, 
    opennsl_ip6_t *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_DstIp6_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_ip6_t *data, 
    opennsl_ip6_t *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_Ip6NextHeader_get(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 *data, 
    uint8 *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_Ip6HopLimit_get(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 *data, 
    uint8 *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_SrcMac_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_mac_t *data, 
    opennsl_mac_t *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_DstMac_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_mac_t *data, 
    opennsl_mac_t *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    type [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_IpType_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_field_IpType_t *type) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_InterfaceClassPort_get(
    int unit, 
    opennsl_field_entry_t entry, 
    uint32 *data, 
    uint32 *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_SrcClassField_get(
    int unit, 
    opennsl_field_entry_t entry, 
    uint32 *data, 
    uint32 *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_DstClassField_get(
    int unit, 
    opennsl_field_entry_t entry, 
    uint32 *data, 
    uint32 *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    protocol [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_IpProtocolCommon_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_field_IpProtocolCommon_t *protocol) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_L3Routable_get(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 *data, 
    uint8 *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    frag_info [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_IpFrag_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_field_IpFrag_t *frag_info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_L3Ingress_get(
    int unit, 
    opennsl_field_entry_t entry, 
    uint32 *data, 
    uint32 *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_MyStationHit_get(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 *data, 
    uint8 *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_IcmpTypeCode_get(
    int unit, 
    opennsl_field_entry_t entry, 
    uint16 *data, 
    uint16 *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_DstIpLocal(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 data, 
    uint8 mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_DstIpLocal_get(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 *data, 
    uint8 *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_CpuQueue(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 data, 
    uint8 mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_CpuQueue_get(
    int unit, 
    opennsl_field_entry_t entry, 
    uint8 *data, 
    uint8 *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_InterfaceClassProcessingPort(
    int unit, 
    opennsl_field_entry_t entry, 
    uint64 data, 
    uint64 mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_InterfaceClassProcessingPort_get(
    int unit, 
    opennsl_field_entry_t entry, 
    uint64 *data, 
    uint64 *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Add an action to a field entry.
 *
 *\description Adds an action to be performed when a packet matches an entry
 *          rule. Multiple actions may be added for an entry by calling this
 *          function repeatedly.
 *          FP action is applied to ports from given list that are local to 
 *          the devices where packets are ingressing.
 *          See =fp_actions for the list of actions and their respective
 *          parameters .
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]   Field entry ID
 *\param    action [IN]   Field action value
 *\param    param0 [IN]   Action-dependent value; 0 if not used
 *\param    param1 [IN]   Action-dependent value; 0 if not used
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_MEMORY Memory allocation failure
 *\retval    OPENNSL_E_RESOURCE Counter not previously created for entry
 *\retval    OPENNSL_E_NOT_FOUND Entry ID not found
 *\retval    OPENNSL_E_EXISTS Action already added
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_field_action_add(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_field_action_t action, 
    uint32 param0, 
    uint32 param1) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete an action from a field entry.
 *
 *\description Deletes an action from a field entry.
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]   Field entry ID
 *\param    action [IN]   Field action value
 *\param    param0 [IN]   Action parameter 0.
 *\param    param1 [IN]   Action parameter 1.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_NOT_FOUND Entry ID or Action not found
 *\retval    OPENNSL_E_PARAM Invalid Action value
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_field_action_delete(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_field_action_t action, 
    uint32 param0, 
    uint32 param1) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Add an action to a field entry.
 *
 *\description Adds an action to be performed when a packet matches an entry
 *          rule. Multiple actions may be added for an entry by calling this
 *          function repeatedly.
 *          FP action is applied to ports from given list that are local to 
 *          the devices where packets are ingressing.
 *          See =fp_actions for the list of actions and their respective
 *          parameters .
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]   Field entry ID
 *\param    action [IN]   Field action value
 *\param    mac [IN]   MAC address for actions involving src/dst mac.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_MEMORY Memory allocation failure
 *\retval    OPENNSL_E_RESOURCE Counter not previously created for entry
 *\retval    OPENNSL_E_NOT_FOUND Entry ID not found
 *\retval    OPENNSL_E_EXISTS Action already added
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_field_action_mac_add(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_field_action_t action, 
    opennsl_mac_t mac) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Add an action to a field entry.
 *
 *\description Adds an action to be performed when a packet matches an entry
 *          rule. Multiple actions may be added for an entry by calling this
 *          function repeatedly.
 *          FP action is applied to ports from given list that are local to 
 *          the devices where packets are ingressing.
 *          See =fp_actions for the list of actions and their respective
 *          parameters .
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]   Field entry ID
 *\param    action [IN]   Field action value
 *\param    pbmp [IN]   pbmp for actions involving port bitmap
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_MEMORY Memory allocation failure
 *\retval    OPENNSL_E_RESOURCE Counter not previously created for entry
 *\retval    OPENNSL_E_NOT_FOUND Entry ID not found
 *\retval    OPENNSL_E_EXISTS Action already added
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_field_action_ports_add(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_field_action_t action, 
    opennsl_pbmp_t pbmp) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Retrieve the parameters for an action previously added to a field entry.
 *
 *\description Retrieves the parameters used for a particular action that was
 *          previously added to a field entry.
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]   Field entry ID
 *\param    action [IN]   Field action value
 *\param    param0 [OUT]   Action-dependent value
 *\param    param1 [OUT]   Action-dependent value
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_NOT_FOUND Entry ID or Action not found
 *\retval    OPENNSL_E_PARAM *paramX points to NULL
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_field_action_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_field_action_t action, 
    uint32 *param0, 
    uint32 *param1) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Retrieve the parameters for an action previously added to a field entry.
 *
 *\description Retrieves the parameters used for a particular action that was
 *          previously added to a field entry.
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]   Field entry ID
 *\param    action [IN]   Field action value
 *\param    mac [OUT]   MAC address for actions involving src/dst mac.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_NOT_FOUND Entry ID or Action not found
 *\retval    OPENNSL_E_PARAM *paramX points to NULL
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_field_action_mac_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_field_action_t action, 
    opennsl_mac_t *mac) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Retrieve the parameters for an action previously added to a field entry.
 *
 *\description Retrieves the parameters used for a particular action that was
 *          previously added to a field entry.
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]   Field entry ID
 *\param    action [IN]   Field action value
 *\param    pbmp [OUT]   pbmp for actions involving port bitmap
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_NOT_FOUND Entry ID or Action not found
 *\retval    OPENNSL_E_PARAM *paramX points to NULL
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_field_action_ports_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_field_action_t action, 
    opennsl_pbmp_t *pbmp) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Remove an action from a field entry.
 *
 *\description Removes an action from a field entry. Same as
 *          opennsl_field_action_delete for actions without parameters. Can be
 *          used on some architectures to remove actions that have parameters,
 *          without requiring that the parameters be specified. Also used to
 *          remove a direct extraction action from an entry.
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]   Field entry ID
 *\param    action [IN]   Field action value
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_NOT_FOUND Entry ID or Action not found
 *\retval    OPENNSL_E_PARAM Invalid Action value
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_field_action_remove(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_field_action_t action) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Remove all actions from a field entry.
 *
 *\description Removes all actions from a field entry.
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]   Field entry ID
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_NOT_FOUND Entry ID not found
 ******************************************************************************/
extern int opennsl_field_action_remove_all(
    int unit, 
    opennsl_field_entry_t entry) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create stat collection entity.
 *
 *\description Creates an aggregated entity describing set of counters. The
 *          entity might be attached to field processor entries and used for
 *          various counters collection.
 *          To get the counter engine ID from stat_id use macro
 *          OPENNSL_FIELD_STAT_ID_PROCESSOR_GET(stat_id) To get the counter ID
 *          from stat_id use macro OPENNSL_FIELD_STAT_ID_COUNTER_GET(stat_id).
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Field group statistics entity will be associated with in
 *          the future.
 *\param    nstat [IN]   Number of elements in stat_arr - counter types array.
 *\param    stat_arr [IN]   Array of counters to be collected in statistics
 *          entity.
 *\param    stat_id [OUT]   Statistics entity ID.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_field_stat_create(
    int unit, 
    opennsl_field_group_t group, 
    int nstat, 
    opennsl_field_stat_t *stat_arr, 
    int *stat_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create stat collection entity with specified Statistics entity ID value.
 *
 *\description Creates an aggregated entity describing set of counters. The
 *          entity might be attached to field processor entries and used for
 *          various counters collection.
 *          To get the counter engine ID from stat_id use macro
 *          OPENNSL_FIELD_STAT_ID_PROCESSOR_GET(stat_id) To get the counter ID
 *          from stat_id use macro OPENNSL_FIELD_STAT_ID_COUNTER_GET(stat_id).
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Field group statistics entity will be associated with in
 *          the future.
 *\param    nstat [IN]   Number of elements in stat_arr - counter types array.
 *\param    stat_arr [IN]   Array of counters to be collected in statistics
 *          entity.
 *\param    stat_id [IN]   Statistics entity ID.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_field_stat_create_id(
    int unit, 
    opennsl_field_group_t group, 
    int nstat, 
    opennsl_field_stat_t *stat_arr, 
    int stat_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get flex stat counter ID associated with given field group and its
 *       associated stats ID.
 *
 *\description This API will provide stat counter IDs associated with given field
 *          group.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Field Group
 *\param    stat_id [IN]   Statistics entity ID
 *\param    stat_counter_id [OUT]   Flex Stat Counter ID
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_stat_id_get(
    int unit, 
    opennsl_field_group_t group, 
    uint32 stat_id, 
    uint32 *stat_counter_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroy stat collection entity.
 *
 *\description This API comes to destroy an aggregated entity of counters, used
 *          for stat collection in field APIs.
 *
 *\param    unit [IN]   Unit number.
 *\param    stat_id [IN]   Statistics entity ID.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_field_stat_destroy(
    int unit, 
    int stat_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get number of counters associated with statistics entity.
 *
 *\description The purpose of this API is to retrieve number of counters
 *          associated with statistics entity.
 *
 *\param    unit [IN]   Unit number.
 *\param    stat_id [IN]   Statistics entity ID.
 *\param    stat_size [OUT]   Number of collected counters.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_field_stat_size(
    int unit, 
    int stat_id, 
    int *stat_size) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set 64-bit counter value for specific statistic type.
 *
 *\description Set 64-bit counter value for specific statistic type.
 *
 *\param    unit [IN]   Unit number.
 *\param    stat_id [IN]   Statistics entity ID.
 *\param    stat [IN]   Statistics entity ID.
 *\param    value [IN]   New value for statistics type.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_field_stat_set(
    int unit, 
    int stat_id, 
    opennsl_field_stat_t stat, 
    uint64 value) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set 64-bit counter value to all counters.
 *
 *\description Set 64-bit counter value to all counters participating in
 *          statistics entity.
 *
 *\param    unit [IN]   Unit number.
 *\param    stat_id [IN]   Statistics entity ID.
 *\param    value [IN]   New value for statistics type.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_field_stat_all_set(
    int unit, 
    int stat_id, 
    uint64 value) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get 64-bit counter value for specific statistic type.
 *
 *\description Get 64-bit counter value for specific statistic type. To create a
 *          stat_id use macro FIELD_STAT_ID_SET(stat_id, engine_id,
 *          counter_id).
 *
 *\param    unit [IN]   Unit number.
 *\param    stat_id [IN]   Statistics entity ID.
 *\param    stat [IN]   Statistics entity ID.
 *\param    value [OUT]   Counter value for statistics type.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_field_stat_get(
    int unit, 
    int stat_id, 
    opennsl_field_stat_t stat, 
    uint64 *value) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Attach statistics entity to Field Processor entry.
 *
 *\description The purpose of this API is to attach statistics collection entity 
 *          to a field entry.
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]   Field entry ID.
 *\param    stat_id [IN]   Statistics entity ID.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_field_entry_stat_attach(
    int unit, 
    opennsl_field_entry_t entry, 
    int stat_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Detach statistics entity from Field Processor entry.
 *
 *\description The purpose of this API is to detach statistics collection entity 
 *          from a field entry.
 *          To create a stat_id use macro FIELD_STAT_ID_SET(stat_id,
 *          engine_id, counter_id).
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]   Field entry ID.
 *\param    stat_id [IN]   Statistics entity ID.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_field_entry_stat_detach(
    int unit, 
    opennsl_field_entry_t entry, 
    int stat_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get statistics entity attached to Field Processor entry.
 *
 *\description The purpose of this API is to check if any statistics collection
 *          entity  is attached to  field entry.
 *          To get the counter engine ID from stat_id use macro
 *          OPENNSL_FIELD_STAT_ID_PROCESSOR_GET(stat_id) To get the counter ID
 *          from stat_id use macro OPENNSL_FIELD_STAT_ID_COUNTER_GET(stat_id).
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]   Field entry ID.
 *\param    stat_id [OUT]   Statistics entity ID.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_field_entry_stat_get(
    int unit, 
    opennsl_field_entry_t entry, 
    int *stat_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Detach counters entries to a field group.
 *
 *\description This API will detach counters entries to a field group.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    stat_id [IN]   Statistics entity ID
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_stat_detach(
    int unit, 
    uint32 stat_id) LIB_DLL_EXPORTED ;

/** Opaque handle to a field presel. */
typedef int opennsl_field_presel_t;

/***************************************************************************//** 
 *\brief Create a preselection specification.
 *
 *\description Create a preselection specification for a preselector set. The
 *          preselector indicates which packets are selected for this set.
 *          To destroy the preselector, use =opennsl_field_presel_destroy API.
 *          .
 *
 *\param    unit [IN]   Unit number.
 *\param    presel_id [OUT]   presel ID
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_PARAM *entry points to NULL
 *\retval    OPENNSL_E_MEMORY Memory allocation failure
 *\retval    OPENNSL_E_RESOURCE No unused entries available
 ******************************************************************************/
extern int opennsl_field_presel_create(
    int unit, 
    opennsl_field_presel_t *presel_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create a preselection specification using a specific ID.
 *
 *\description Create a preselection specification for a preselector set using a
 *          specific ID. The preselector indicates which packets are selected
 *          for this set.
 *          To destroy the preselector, use =opennsl_field_presel_destroy API.
 *          .
 *
 *\param    unit [IN]   Unit number.
 *\param    presel_id [IN]   presel ID
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_EXISTS Requested presel ID already exists
 *\retval    OPENNSL_E_PARAM *entry points to NULL
 *\retval    OPENNSL_E_MEMORY Memory allocation failure
 *\retval    OPENNSL_E_RESOURCE No unused entries available
 ******************************************************************************/
extern int opennsl_field_presel_create_id(
    int unit, 
    opennsl_field_presel_t presel_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroy a preselection specification.
 *
 *\description Destroy a preselection specification. .
 *
 *\param    unit [IN]   Unit number.
 *\param    presel_id [IN]
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_NOT_FOUND Presel ID not found in unit
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_field_presel_destroy(
    int unit, 
    opennsl_field_presel_t presel_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Associate a set of preselectors with a Field group.
 *
 *\description Associate a set of preselectors with a Field group, operation is
 *          OR -- if any preselector is matched by the frame, the frame goes
 *          to the group. .
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Field group ID
 *\param    presel [IN]   A pointer to a presel_set structure
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_NOT_FOUND Group ID not found in unit
 *\retval    OPENNSL_E_PARAM *presel_set points to NULL
 *          (opennsl_field_presel_set_t)
 ******************************************************************************/
extern int opennsl_field_group_presel_set(
    int unit, 
    opennsl_field_group_t group, 
    opennsl_field_presel_set_t *presel) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the set of preselectors associated with a Field group.
 *
 *\description Get the set of preselectors associated with a Field group.
 *
 *\param    unit [IN]   Unit number.
 *\param    group [IN]   Field group ID
 *\param    presel [OUT]   A pointer to a presel_set structure
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT OPENNSL unit not initialized
 *\retval    OPENNSL_E_NOT_FOUND Group ID not found in unit
 *\retval    OPENNSL_E_MEMORY Memory allocation failure
 ******************************************************************************/
extern int opennsl_field_group_presel_get(
    int unit, 
    opennsl_field_group_t group, 
    opennsl_field_presel_set_t *presel) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [IN]
 *\param    mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_IngressClassField(
    int unit, 
    opennsl_field_entry_t entry, 
    uint32 data, 
    uint32 mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *\param    mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_IngressClassField_get(
    int unit, 
    opennsl_field_entry_t entry, 
    uint32 *data, 
    uint32 *mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set qualification on a particular stage. This feature is normally used
 *       for preselectors.
 *
 *\description Set qualification on a particular stage. The API is only used for
 *          preselector entries. For XGS devices, it is mandatory to call this
 *          API specifying the stage
 *          (opennslFieldStageIngress/opennslFieldStageIngressExactMatch)
 *          before setting any other qualifier to the preselector entry. On
 *          Tomahawk, only Stage Ingress and Stage Exact Match supports
 *          Preselection,  so this API is used to associate the stage to the
 *          preselector. Preselector Entry ID can be retrieved using a macro
 *          OPENNSL_FIELD_PRESEL_ENTRY_SET.
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]   OPENNSL field entry id.
 *\param    data [IN]   Stage on which to qualify
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_Stage(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_field_stage_t data) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    entry [IN]
 *\param    data [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_field_qualify_Stage_get(
    int unit, 
    opennsl_field_entry_t entry, 
    opennsl_field_stage_t *data) LIB_DLL_EXPORTED ;

#endif /* __OPENNSL_FIELDX_H__ */
/*@}*/
