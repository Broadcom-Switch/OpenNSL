/** \addtogroup types Types
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
 * \file			types.h
 ******************************************************************************/

#ifndef __OPENNSL_TYPES_H__
#define __OPENNSL_TYPES_H__

#include <sal/types.h>
#include <sal/commdefs.h>
#include <shared/bitop.h>
#include <shared/pbmp.h>
#include <shared/gport.h>
#include <shared/types.h>
#include <shared/util.h>

/** opennsl_multicast_t */
typedef int opennsl_multicast_t;

#if !defined(OPENNSL_LOCAL_UNITS_MAX)
#endif
#if !defined(OPENNSL_UNITS_MAX)
#endif
#define OPENNSL_PBMP_PORT_MAX   _SHR_PBMP_PORT_MAX 
#define OPENNSL_PBMP_CLEAR(pbm)  _SHR_PBMP_CLEAR(pbm) 
#define OPENNSL_PBMP_MEMBER(bmp, port)  _SHR_PBMP_MEMBER((bmp), (port)) 
#define OPENNSL_PBMP_ITER(bmp, port)  _SHR_PBMP_ITER((bmp), (port)) 
#define OPENNSL_PBMP_COUNT(pbm, count)  _SHR_PBMP_COUNT(pbm, count) 
#define OPENNSL_PBMP_IS_NULL(pbm)  _SHR_PBMP_IS_NULL(pbm) 
#define OPENNSL_PBMP_NOT_NULL(pbm)  _SHR_PBMP_NOT_NULL(pbm) 
#define OPENNSL_PBMP_EQ(pbm_a, pbm_b)  _SHR_PBMP_EQ(pbm_a, pbm_b) 
#define OPENNSL_PBMP_NEQ(pbm_a, pbm_b)  _SHR_PBMP_NEQ(pbm_a, pbm_b) 
#define OPENNSL_PBMP_ASSIGN(dst, src)  _SHR_PBMP_ASSIGN(dst, src) 
#define OPENNSL_PBMP_AND(pbm_a, pbm_b)  _SHR_PBMP_AND(pbm_a, pbm_b) 
#define OPENNSL_PBMP_OR(pbm_a, pbm_b)  _SHR_PBMP_OR(pbm_a, pbm_b) 
#define OPENNSL_PBMP_XOR(pbm_a, pbm_b)  _SHR_PBMP_XOR(pbm_a, pbm_b) 
#define OPENNSL_PBMP_REMOVE(pbm_a, pbm_b)  _SHR_PBMP_REMOVE(pbm_a, pbm_b) 
#define OPENNSL_PBMP_NEGATE(pbm_a, pbm_b)  _SHR_PBMP_NEGATE(pbm_a, pbm_b) 
#define OPENNSL_PBMP_PORT_SET(pbm, port)  _SHR_PBMP_PORT_SET(pbm, port) 
#define OPENNSL_PBMP_PORT_ADD(pbm, port)  _SHR_PBMP_PORT_ADD(pbm, port) 
#define OPENNSL_PBMP_PORT_REMOVE(pbm, port)  _SHR_PBMP_PORT_REMOVE(pbm, port) 
#define OPENNSL_PBMP_PORT_FLIP(pbm, port)  _SHR_PBMP_PORT_FLIP(pbm, port) 
/** Set the default tag protocol ID (TPID) for the specified port. */
typedef int opennsl_port_t;

/** opennsl_pbmp_t */
typedef _shr_pbmp_t opennsl_pbmp_t;

/** opennsl_mac_t */
typedef uint8 opennsl_mac_t[6];

/** opennsl_ip_t */
typedef uint32 opennsl_ip_t;

/** opennsl_ip6_t */
typedef uint8 opennsl_ip6_t[16];

/** opennsl_if_t */
typedef int opennsl_if_t;

/** opennsl_trill_name_t */
typedef int opennsl_trill_name_t;

/** opennsl_l4_port_t */
typedef int opennsl_l4_port_t;

/** opennsl_if_group_t */
typedef int opennsl_if_group_t;

/** opennsl_vrf_t */
typedef int opennsl_vrf_t;

/** opennsl_mpls_label_t */
typedef uint32 opennsl_mpls_label_t;

#define OPENNSL_VLAN_NONE       ((opennsl_vlan_t)0x0000) 
#define OPENNSL_VLAN_DEFAULT    ((opennsl_vlan_t)0x0001) 
/** opennsl_vlan_t */
typedef uint16 opennsl_vlan_t;

/** opennsl_ethertype_t */
typedef uint16 opennsl_ethertype_t;

/** opennsl_vpn_t */
typedef opennsl_vlan_t opennsl_vpn_t;

/** opennsl_policer_t */
typedef int opennsl_policer_t;

/** opennsl_tunnel_id_t */
typedef uint32 opennsl_tunnel_id_t;

#define OPENNSL_VLAN_MIN        0          
#define OPENNSL_VLAN_MAX        4095       
#define OPENNSL_VLAN_COUNT      (OPENNSL_VLAN_MAX - OPENNSL_VLAN_MIN + 1) 
/** opennsl_vlan_vector_t */
typedef uint32 opennsl_vlan_vector_t[_SHR_BITDCLSIZE(OPENNSL_VLAN_COUNT)];

#define OPENNSL_VLAN_VEC_GET(vec, n)  SHR_BITGET(vec, n) 
#define OPENNSL_VLAN_VEC_SET(vec, n)  SHR_BITSET(vec, n) 
#define OPENNSL_VLAN_VEC_CLR(vec, n)  SHR_BITCLR(vec, n) 
#define OPENNSL_VLAN_VEC_ZERO(vec)  \
    memset(vec, 0, \
                    SHR_BITALLOCSIZE(OPENNSL_VLAN_COUNT)) 
/** opennsl_cos_t */
typedef int opennsl_cos_t;

/** opennsl_cos_queue_t */
typedef int opennsl_cos_queue_t;

#define OPENNSL_COS_MIN         0          
#define OPENNSL_COS_MAX         7          
#define OPENNSL_COS_COUNT       8          
#define OPENNSL_COS_DEFAULT     4          
#define OPENNSL_COS_INVALID     -1         
#define OPENNSL_PRIO_MIN        0          
#define OPENNSL_PRIO_MAX        7          
#define OPENNSL_PRIO_RED        0x100      
#define OPENNSL_PRIO_YELLOW     0x200      
#define OPENNSL_PRIO_DROP_FIRST OPENNSL_PRIO_RED 
#define OPENNSL_PRIO_MASK       0xff       
#define OPENNSL_PRIO_GREEN      0x400      
#define OPENNSL_PRIO_DROP_LAST  0x800      
#define OPENNSL_PRIO_PRESERVE   OPENNSL_PRIO_DROP_LAST 
#define OPENNSL_PRIO_STAG       0x100      
#define OPENNSL_PRIO_CTAG       0x200      
#define OPENNSL_DSCP_ECN        0x100      
#define OPENNSL_PRIO_BLACK      0x1000     
#define OPENNSL_PRIO_SECONDARY  0x2000     
/** opennsl_module_t */
typedef int opennsl_module_t;

#define OPENNSL_TRUNK_INVALID   ((opennsl_trunk_t) -1) 
/** opennsl_trunk_t */
typedef int opennsl_trunk_t;

/** Split Horizon Network Group */
typedef int opennsl_switch_network_group_t;

/** 
 * GPORT (generic port) definitions.
 * See shared/gport.h for more details.
 */
typedef int opennsl_gport_t;

#define OPENNSL_GPORT_TYPE_NONE             _SHR_GPORT_NONE 
#define OPENNSL_GPORT_INVALID               _SHR_GPORT_INVALID 
#define OPENNSL_GPORT_TYPE_LOCAL            _SHR_GPORT_TYPE_LOCAL 
#define OPENNSL_GPORT_TYPE_MODPORT          _SHR_GPORT_TYPE_MODPORT 
#define OPENNSL_GPORT_TYPE_UCAST_QUEUE_GROUP _SHR_GPORT_TYPE_UCAST_QUEUE_GROUP 
#define OPENNSL_GPORT_TYPE_DESTMOD_QUEUE_GROUP _SHR_GPORT_TYPE_DESTMOD_QUEUE_GROUP 
#define OPENNSL_GPORT_TYPE_MCAST            _SHR_GPORT_TYPE_MCAST 
#define OPENNSL_GPORT_TYPE_MCAST_QUEUE_GROUP _SHR_GPORT_TYPE_MCAST_QUEUE_GROUP 
#define OPENNSL_GPORT_TYPE_SCHEDULER        _SHR_GPORT_TYPE_SCHEDULER 
#define OPENNSL_GPORT_TYPE_CHILD            _SHR_GPORT_TYPE_CHILD 
#define OPENNSL_GPORT_TYPE_EGRESS_GROUP     _SHR_GPORT_TYPE_EGRESS_GROUP 
#define OPENNSL_GPORT_TYPE_EGRESS_CHILD     _SHR_GPORT_TYPE_EGRESS_CHILD 
#define OPENNSL_GPORT_TYPE_EGRESS_MODPORT   _SHR_GPORT_TYPE_EGRESS_MODPORT 
#define OPENNSL_GPORT_TYPE_UCAST_SUBSCRIBER_QUEUE_GROUP _SHR_GPORT_TYPE_UCAST_SUBSCRIBER_QUEUE_GROUP 
#define OPENNSL_GPORT_TYPE_MCAST_SUBSCRIBER_QUEUE_GROUP _SHR_GPORT_TYPE_MCAST_SUBSCRIBER_QUEUE_GROUP 
#define OPENNSL_GPORT_TYPE_COSQ             _SHR_GPORT_TYPE_COSQ 
#define OPENNSL_GPORT_TYPE_PROFILE          _SHR_GPORT_TYPE_PROFILE 
#define OPENNSL_GPORT_IS_TRUNK(_gport)      _SHR_GPORT_IS_TRUNK(_gport) 
#define OPENNSL_GPORT_IS_UCAST_QUEUE_GROUP(_gport)  _SHR_GPORT_IS_UCAST_QUEUE_GROUP(_gport) 
#define OPENNSL_GPORT_IS_MCAST_QUEUE_GROUP(_gport)  _SHR_GPORT_IS_MCAST_QUEUE_GROUP(_gport) 
#define OPENNSL_GPORT_IS_SCHEDULER(_gport)  _SHR_GPORT_IS_SCHEDULER(_gport) 
#define OPENNSL_GPORT_IS_COSQ(_gport)       _SHR_GPORT_IS_COSQ(_gport) 
#define OPENNSL_GPORT_LOCAL_SET(_gport, _port)  \
    _SHR_GPORT_LOCAL_SET(_gport, _port) 
#define OPENNSL_GPORT_LOCAL_GET(_gport)  \
    (!_SHR_GPORT_IS_LOCAL(_gport) ? -1 : \
    _SHR_GPORT_LOCAL_GET(_gport)) 
#define OPENNSL_GPORT_MODPORT_SET(_gport, _module, _port)  \
    _SHR_GPORT_MODPORT_SET(_gport, _module, _port) 
#define OPENNSL_GPORT_MODPORT_MODID_GET(_gport)  \
    (!_SHR_GPORT_IS_MODPORT(_gport) ? -1 : \
    _SHR_GPORT_MODPORT_MODID_GET(_gport)) 
#define OPENNSL_GPORT_MODPORT_PORT_GET(_gport)  \
    (!_SHR_GPORT_IS_MODPORT(_gport) ? -1 : \
    _SHR_GPORT_MODPORT_PORT_GET(_gport)) 
#define OPENNSL_GPORT_TRUNK_SET(_gport, _trunk_id)  \
    _SHR_GPORT_TRUNK_SET(_gport, _trunk_id) 
#define OPENNSL_GPORT_TRAP_SET(_gport, _trap_id, _trap_strength, _snoop_strength)  \
   _SHR_GPORT_TRAP_SET(_gport, _trap_id, _trap_strength, _snoop_strength) 
#define OPENNSL_GPORT_TRAP_GET_ID(_gport)  \
     (!_SHR_GPORT_IS_TRAP(_gport) ? -1 : \
   _SHR_GPORT_TRAP_GET_ID(_gport)) 
#define OPENNSL_GPORT_TRAP_GET_STRENGTH(_gport)  \
   _SHR_GPORT_TRAP_GET_STRENGTH(_gport) 
#define OPENNSL_GPORT_TRAP_GET_SNOOP_STRENGTH(_gport)  \
   _SHR_GPORT_TRAP_GET_SNOOP_STRENGTH(_gport) 
#define OPENNSL_GPORT_IS_TRAP(_gport)  \
   _SHR_GPORT_IS_TRAP(_gport)         
#define OPENNSL_GPORT_TRUNK_GET(_gport)  \
    (!_SHR_GPORT_IS_TRUNK(_gport) ? OPENNSL_TRUNK_INVALID : \
    _SHR_GPORT_TRUNK_GET(_gport)) 
#define OPENNSL_GPORT_UCAST_QUEUE_GROUP_SET(_gport, _qid)  \
         _SHR_GPORT_UCAST_QUEUE_GROUP_SET(_gport, _qid) 
#define OPENNSL_GPORT_UCAST_QUEUE_GROUP_SYSQID_SET(_gport, _sysport_id, _qid)  \
         _SHR_GPORT_UCAST_QUEUE_GROUP_SYSQID_SET(_gport, _sysport_id, _qid) 
#define OPENNSL_GPORT_UCAST_QUEUE_GROUP_SYSPORTID_GET(_gport)  \
            (!_SHR_GPORT_IS_UCAST_QUEUE_GROUP(_gport) ? -1 :  \
        _SHR_GPORT_UCAST_QUEUE_GROUP_SYSPORTID_GET(_gport))
 
#define OPENNSL_GPORT_UCAST_QUEUE_GROUP_QID_GET(_gport)  \
            (!_SHR_GPORT_IS_UCAST_QUEUE_GROUP(_gport) ? -1 :  \
        _SHR_GPORT_UCAST_QUEUE_GROUP_QID_GET(_gport))
 
#define OPENNSL_GPORT_MCAST_QUEUE_GROUP_SET(_gport, _qid)  \
         _SHR_GPORT_MCAST_QUEUE_GROUP_SET(_gport, _qid)
 
#define OPENNSL_GPORT_MCAST_QUEUE_GROUP_GET(_gport)  \
            (!_SHR_GPORT_IS_MCAST_QUEUE_GROUP(_gport) ? -1 :  \
        _SHR_GPORT_MCAST_QUEUE_GROUP_GET(_gport))
 
#define OPENNSL_GPORT_MCAST_QUEUE_GROUP_SYSQID_SET(_gport, _sysport_id, _qid)  \
     _SHR_GPORT_MCAST_QUEUE_GROUP_SYSQID_SET(_gport, _sysport_id, _qid)
 
#define OPENNSL_GPORT_MCAST_QUEUE_GROUP_SYSPORTID_GET(_gport)  \
            (!_SHR_GPORT_IS_MCAST_QUEUE_GROUP(_gport) ? -1 :  \
        _SHR_GPORT_MCAST_QUEUE_GROUP_SYSPORTID_GET(_gport))
 
#define OPENNSL_GPORT_MCAST_QUEUE_GROUP_QID_GET(_gport)  \
            (!_SHR_GPORT_IS_MCAST_QUEUE_GROUP(_gport) ? -1 :  \
        _SHR_GPORT_MCAST_QUEUE_GROUP_QID_GET(_gport)) 
#define OPENNSL_GPORT_MCAST_QUEUE_GROUP_QUEUE_SET(_gport, _qid)  \
         _SHR_GPORT_MCAST_QUEUE_GROUP_QUEUE_SET(_gport, _qid) 
#define OPENNSL_GPORT_MCAST_QUEUE_GROUP_CORE_QUEUE_SET(_gport, _core, _qid)  \
         _SHR_GPORT_MCAST_QUEUE_GROUP_CORE_QUEUE_SET(_gport, _core, _qid) 
#define OPENNSL_GPORT_MCAST_QUEUE_GROUP_QUEUE_GET(_gport)  \
         (!_SHR_GPORT_IS_MCAST_QUEUE_GROUP(_gport) ? -1 : \
         _SHR_GPORT_MCAST_QUEUE_GROUP_QUEUE_GET(_gport)) 
#define OPENNSL_GPORT_MCAST_QUEUE_GROUP_CORE_GET(_gport)  \
         (!_SHR_GPORT_IS_MCAST_QUEUE_GROUP(_gport) ? -1 : \
         _SHR_GPORT_MCAST_QUEUE_GROUP_CORE_GET(_gport))
 
#define OPENNSL_GPORT_SCHEDULER_SET(_gport, _scheduler_id)  \
    _SHR_GPORT_SCHEDULER_SET(_gport, _scheduler_id) 
#define OPENNSL_GPORT_SCHEDULER_NODE_SET(_gport, _scheduler_level, _scheduler_id)  \
    _SHR_GPORT_SCHEDULER_NODE_SET(_gport, _scheduler_level,_scheduler_id) 
#define OPENNSL_GPORT_SCHEDULER_GET(_gport)  \
    _SHR_GPORT_SCHEDULER_GET(_gport) 
#define OPENNSL_GPORT_SCHEDULER_CORE_GET(_gport)  \
    _SHR_GPORT_SCHEDULER_CORE_GET(_gport) 
#define OPENNSL_GPORT_SCHEDULER_CORE_SET(_gport, _scheduler_id, _core_id)  \
    _SHR_GPORT_SCHEDULER_CORE_SET(_gport, _scheduler_id, _core_id) 
/** Multicast distribution set */
typedef int opennsl_fabric_distribution_t;

/** Failover Object */
typedef int opennsl_failover_t;

#define OPENNSL_GPORT_LOCAL_CPU _SHR_GPORT_LOCAL_CPU 
#define OPENNSL_GPORT_MIRROR_SET(_gport, _value)  \
    _SHR_GPORT_MIRROR_SET(_gport, _value) 
#define OPENNSL_GPORT_MIRROR_GET(_gport)  \
    (!_SHR_GPORT_IS_MIRROR(_gport) ? -1 : \
    _SHR_GPORT_MIRROR_GET(_gport)) 
#define OPENNSL_GPORT_TUNNEL_ID_SET(_gport, _tunnel_id)  \
        (_SHR_GPORT_TUNNEL_ID_SET(_gport, _tunnel_id))
 
#define OPENNSL_GPORT_TUNNEL_ID_GET(_gport)  \
            (!_SHR_GPORT_IS_TUNNEL(_gport) ? -1 :  \
        _SHR_GPORT_TUNNEL_ID_GET(_gport))
 
/** opennsl_stg_t */
typedef int opennsl_stg_t;

/** opennsl_color_t */
typedef enum opennsl_color_e {
    opennslColorGreen = _SHR_COLOR_GREEN, 
    opennslColorYellow = _SHR_COLOR_YELLOW, 
    opennslColorRed = _SHR_COLOR_RED,   
    opennslColorDropFirst = opennslColorRed, 
    opennslColorBlack = _SHR_COLOR_BLACK, 
    opennslColorPreserve = _SHR_COLOR_PRESERVE, 
    opennslColorCount = _SHR_COLOR_COUNT 
} opennsl_color_t;

typedef struct opennsl_priority_mapping_s {
    int internal_pri;               /**< Internal priority */
    opennsl_color_t color;          /**< (internal) color or drop precedence */
    int remark_internal_pri;        /**< (internal) remarking priority */
    opennsl_color_t remark_color;   /**< (internal) remarking color or drop
                                       precedence */
    int policer_offset;             /**< Offset based on pri/cos to fetch a
                                       policer */
} opennsl_priority_mapping_t;

#if defined(LE_HOST)
#else
#define opennsl_htonl(_l)       (_l)       
#define opennsl_htons(_s)       (_s)       
#define opennsl_ntohl(_l)       (_l)       
#define opennsl_ntohs(_s)       (_s)       
#endif
/***************************************************************************//** 
 *
 *
 *\param    ip6 [OUT]
 *\param    len [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_ip6_mask_create(
    opennsl_ip6_t ip6, 
    int len) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    len [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern opennsl_ip_t opennsl_ip_mask_create(
    int len) LIB_DLL_EXPORTED ;

/** VLAN TPID Action definitions. */
typedef enum opennsl_vlan_tpid_action_e {
    opennslVlanTpidActionNone = 0,      /**< Do not modify. */
    opennslVlanTpidActionModify = 1,    /**< Set to given value. */
    opennslVlanTpidActionInner = 2,     /**< Use packet's inner tpid. */
    opennslVlanTpidActionOuter = 3      /**< Use packet's outer tpid. */
} opennsl_vlan_tpid_action_t;

/** VLAN Pcp Action definitions. */
typedef enum opennsl_vlan_pcp_action_e {
    opennslVlanPcpActionNone = 0,       /**< Do not modify. */
    opennslVlanPcpActionMapped = 1,     /**< Use TC/DP mapped PCP. */
    opennslVlanPcpActionIngressInnerPcp = 2, /**< Use incoming packet's CTag PCP. */
    opennslVlanPcpActionIngressOuterPcp = 3, /**< Use incoming packet's Stag PCP. */
    opennslVlanPcpActionPortDefault = 4 /**< Use port default PCP. */
} opennsl_vlan_pcp_action_t;

/** VLAN Action definitions. */
typedef enum opennsl_vlan_action_e {
    opennslVlanActionNone = 0,          /**< Do not modify. */
    opennslVlanActionAdd = 1,           /**< Add VLAN tag. */
    opennslVlanActionReplace = 2,       /**< Replace VLAN tag. */
    opennslVlanActionDelete = 3,        /**< Delete VLAN tag. */
    opennslVlanActionCopy = 4,          /**< Copy VLAN tag. */
    opennslVlanActionCompressed = 5,    /**< Set VLAN compress tag. */
    opennslVlanActionMappedAdd = 6,     /**< Add a new VLAN tag according to
                                           Mapped VLAN. */
    opennslVlanActionMappedReplace = 7, /**< Replace existing VLAN tag according
                                           to Mapped VLAN. */
    opennslVlanActionOuterAdd = 8,      /**< Add a new VLAN tag with the Outer
                                           VLAN tag value. */
    opennslVlanActionInnerAdd = 9,      /**< Add a new VLAN tag with the Inner
                                           VLAN tag value. */
} opennsl_vlan_action_t;

typedef enum opennsl_reserved_enum_e {
    opennsl_enum_reserved = 0   /**< Reserved value */
} opennsl_reserved_enum_t;

/** Initialize a VLAN tag action set structure. */
typedef struct opennsl_vlan_action_set_s {
    opennsl_vlan_t new_outer_vlan;      /**< New outer VLAN for Add/Replace
                                           actions. */
    opennsl_vlan_t new_inner_vlan;      /**< New inner VLAN for Add/Replace
                                           actions. */
    uint8 new_inner_pkt_prio;           /**< New inner packet priority for
                                           Add/Replace actions. */
    uint8 new_outer_cfi;                /**< New outer packet CFI for Add/Replace
                                           actions. */
    uint8 new_inner_cfi;                /**< New inner packet CFI for Add/Replace
                                           actions. */
    opennsl_if_t ingress_if;            /**< L3 Ingress Interface. */
    int priority;                       /**< Internal or packet priority. */
    opennsl_vlan_action_t dt_outer;     /**< Outer-tag action for double-tagged
                                           packets. */
    opennsl_vlan_action_t dt_outer_prio; /**< Outer-priority-tag action for
                                           double-tagged packets. */
    opennsl_vlan_action_t dt_outer_pkt_prio; /**< Outer packet priority action for
                                           double-tagged packets. */
    opennsl_vlan_action_t dt_outer_cfi; /**< Outer packet CFI action for
                                           double-tagged packets. */
    opennsl_vlan_action_t dt_inner;     /**< Inner-tag action for double-tagged
                                           packets. */
    opennsl_vlan_action_t dt_inner_prio; /**< Inner-priority-tag action for
                                           double-tagged packets. */
    opennsl_vlan_action_t dt_inner_pkt_prio; /**< Inner packet priority action for
                                           double-tagged packets. */
    opennsl_vlan_action_t dt_inner_cfi; /**< Inner packet CFI action for
                                           double-tagged packets. */
    opennsl_vlan_action_t ot_outer;     /**< Outer-tag action for
                                           single-outer-tagged packets. */
    opennsl_vlan_action_t ot_outer_prio; /**< Outer-priority-tag action for
                                           single-outer-tagged packets. */
    opennsl_vlan_action_t ot_outer_pkt_prio; /**< Outer packet priority action for
                                           single-outer-tagged packets. */
    opennsl_vlan_action_t ot_outer_cfi; /**< Outer packet CFI action for
                                           single-outer-tagged packets. */
    opennsl_vlan_action_t ot_inner;     /**< Inner-tag action for
                                           single-outer-tagged packets. */
    opennsl_vlan_action_t ot_inner_pkt_prio; /**< Inner packet priority action for
                                           single-outer-tagged packets. */
    opennsl_vlan_action_t ot_inner_cfi; /**< Inner packet CFI action for
                                           single-outer-tagged packets. */
    opennsl_vlan_action_t it_outer;     /**< Outer-tag action for
                                           single-inner-tagged packets. */
    opennsl_vlan_action_t it_outer_pkt_prio; /**< Outer packet priority action for
                                           single-inner-tagged packets. */
    opennsl_vlan_action_t it_outer_cfi; /**< Outer packet CFI action for
                                           single-inner-tagged packets. */
    opennsl_vlan_action_t it_inner;     /**< Inner-tag action for
                                           single-inner-tagged packets. */
    opennsl_vlan_action_t it_inner_prio; /**< Inner-priority-tag action for
                                           single-inner-tagged packets. */
    opennsl_vlan_action_t it_inner_pkt_prio; /**< Inner packet priority action for
                                           single-inner-tagged packets. */
    opennsl_vlan_action_t it_inner_cfi; /**< Inner packet CFI action for
                                           single-inner-tagged packets. */
    opennsl_vlan_action_t ut_outer;     /**< Outer-tag action for untagged
                                           packets. */
    opennsl_vlan_action_t ut_outer_pkt_prio; /**< Outer packet priority action for
                                           untagged packets. */
    opennsl_vlan_action_t ut_outer_cfi; /**< Outer packet CFI action for untagged
                                           packets. */
    opennsl_vlan_action_t ut_inner;     /**< Inner-tag action for untagged
                                           packets. */
    opennsl_vlan_action_t ut_inner_pkt_prio; /**< Inner packet priority action for
                                           untagged packets. */
    opennsl_vlan_action_t ut_inner_cfi; /**< Inner packet CFI action for untagged
                                           packets. */
    opennsl_vlan_pcp_action_t outer_pcp; /**< Outer tag's pcp field action of
                                           outgoing packets. */
    opennsl_vlan_pcp_action_t inner_pcp; /**< Inner tag's pcp field action of
                                           outgoing packets. */
    opennsl_policer_t policer_id;       /**< Base policer to be used */
    uint16 outer_tpid;                  /**< New outer-tag's tpid field for modify
                                           action */
    uint16 inner_tpid;                  /**< New inner-tag's tpid field for modify
                                           action */
    opennsl_vlan_tpid_action_t outer_tpid_action; /**< Action of outer-tag's tpid field */
    opennsl_vlan_tpid_action_t inner_tpid_action; /**< Action of inner-tag's tpid field */
    int action_id;                      /**< Action Set index */
    uint32 class_id;                    /**< Class ID */
    uint32 flags;                       /**< OPENNSL_VLAN_ACTION_SET_xxx. */
} opennsl_vlan_action_set_t;

#define OPENNSL_FIELD_STAT_ID_SET(_stat_id, _proc, _ctr)  _SHR_FIELD_STAT_ID_SET(_stat_id, _proc, _ctr) 
#define OPENNSL_FIELD_STAT_ID_COUNTER_GET(_stat_id)  _SHR_FIELD_STAT_ID_COUNTER_GET(_stat_id) 
#define OPENNSL_FIELD_STAT_ID_PROCESSOR_GET(_stat_id)  _SHR_FIELD_STAT_ID_PROCESSOR_GET(_stat_id) 
/** VNTAG structure. */
typedef struct opennsl_vntag_s {
    uint8 reserved1; 
    uint8 reserved2; 
    uint16 reserved3; 
    uint8 reserved4; 
    uint16 reserved5; 
} opennsl_vntag_t;

/** ETAG structure. */
typedef struct opennsl_etag_s {
    uint8 reserved1; 
    uint8 reserved2; 
    uint16 reserved3; 
    uint16 reserved4; 
} opennsl_etag_t;

#include <opennsl/typesX.h>
#endif /* __OPENNSL_TYPES_H__ */
/*@}*/
