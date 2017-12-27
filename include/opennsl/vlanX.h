/** \addtogroup vlan Virtual LAN Management
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
 * \file			vlanX.h
 ******************************************************************************/

#ifndef __OPENNSL_VLANX_H__
#define __OPENNSL_VLANX_H__

#include <opennsl/types.h>
#include <opennsl/port.h>

/** 
 * Per VLAN Protocol Packet control. A protocol packet type is copied to
 * CPU if the packet control value is set to VLAN_PROTO_PKT_TOCPU_ENABLE.
 * Additionally the control can be set to one of
 * VLAN_PROTO_PKT_FORWARD_ENABLE, VLAN_PROTO_PKT_DROP_ENABLE, or
 * VLAN_PROTO_PKT_FLOOD_ENABLE to forward, drop or flood in VLAN
 * respectively.
 */
typedef struct opennsl_vlan_protocol_packet_ctrl_s {
    int mmrp_action;                /**< MMRP packet action */
    int srp_action;                 /**< SRP packet action */
    int arp_reply_action;           /**< ARP reply packet action */
    int arp_request_action;         /**< ARP request packet action */
    int nd_action;                  /**< ND packet action */
    int dhcp_action;                /**< DHCP packet action */
    int igmp_report_leave_action;   /**< IGMP Report(v1,v2,v3)/Leave(v2) packet
                                       action */
    int igmp_query_action;          /**< IGMP Query packet action */
    int igmp_unknown_msg_action;    /**< Unknown IGMP message packet action */
    int mld_report_done_action;     /**< MLD Report(v1,v2)/Done(v1) packet action */
    int mld_query_action;           /**< MLD Query packet action */
    int ip4_rsvd_mc_action;         /**< IPv4 reserved multicast packet
                                       (DIP=224.0.0.X) action */
    int ip6_rsvd_mc_action;         /**< IPv6 reserved multicast packet
                                       (DIP=ff0X:0:0:0:0:0:0:0) action */
    int reserved1; 
    int reserved2; 
    int reserved3; 
} opennsl_vlan_protocol_packet_ctrl_t;

/** This structure contains the configuration of a VLAN. */
typedef struct opennsl_vlan_control_vlan_s {
    uint32 flags;                       
} opennsl_vlan_control_vlan_t;

/***************************************************************************//** 
 *\brief Initialize the opennsl_vlan_control_vlan_t structure.
 *
 *\description Initialize the opennsl_vlan_control_vlan_t structure.
 *
 *\param    data [IN,OUT]   Pointer to the structure to be initialized
 *
 *\returns  Nothing
 ******************************************************************************/
extern void opennsl_vlan_control_vlan_t_init(
    opennsl_vlan_control_vlan_t *data) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set or retrieve current VLAN properties.
 *
 *\description Sets/gets miscellaneous VLAN-specific properties. The control
 *          properties are from =opennsl_vlan_control_vlan_t . The flags of
 *          the opennsl_vlan_control_vlan_t can be any combination of
 *          =OPENNSL_VLAN_CONTROL_VLAN_FLAG_table . On network switch devices
 *          that allow per-VLAN MPLS enable/disable, the only valid control
 *          parameter in this API is the OPENNSL_VLAN_MPLS_DISABLE control
 *          flag (all other control parameters are ignored).
 *          When only OPENNSL_VLAN_L2_CLASS_ID_ONLY is set, the if_class_id is
 *          set to VLAN_CLASS_ID(L3_IIF.CLASS_ID is not set). When only
 *          OPENNSL_VLAN_L3_CLASS_ID is set, the l3_if_class is set to
 *          L3_IIF.CLASS_ID(VLAN_CLASS_ID is not set). If none are set, the
 *          if_class_id is set to both VLAN_CLASS_ID and L3_IIF.CLASS_ID. If
 *          both are set, if_class_id is set to VLAN_CLASS_ID and l3_if_class
 *          is set to L3_IIF.CLASS_ID. Also, on a get, both the
 *          OPENNSL_VLAN_L2_CLASS_ID_ONLY and OPENNSL_VLAN_L3_CLASS_ID are set
 *          with the returned data, if_class is set to VLAN_CLASS_ID and
 *          l3_if_class is set to L3_IIF.CLASS_ID.
 *          For trident2 plus devices, this API can be used to derive VRF for
 *          a VPN. If VRF value is 0, the VRF is INVALID.
 *          If interface map mode (opennslSwitchL3IngressInterfaceMapSet
 *          =opennsl_switches) is not set, the vrf value set by this api can
 *          be overwritten by =opennsl_l3_intf_create().  If interface map
 *          mode is set, this api will not set vrf value.
 *          =opennsl_l3_ingress_create()  api should be used to set vrf with
 *          an ingress interface.
 *          For Trident3 devices, OPENNSL_VLAN_UNKNOWN_UCAST_TOCPU now becomes
 *          a global configuration instead of per VLAN configuration, the last
 *          API call which programs OPENNSL_VLAN_UNKNOWN_UCAST_TOCPU takes
 *          effect. .
 *
 *\param    unit [IN]   Unit number.
 *\param    vlan [IN]   VLAN
 *\param    control [OUT]   structure which contains VLAN property, see
 *          opennsl_vlan_control_vlan_t =opennsl_vlan_control_vlan_t
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNAVAIL Operation not supported
 *\retval    OPENNSL_E_XXX Operation failed.
 ******************************************************************************/
extern int opennsl_vlan_control_vlan_get(
    int unit, 
    opennsl_vlan_t vlan, 
    opennsl_vlan_control_vlan_t *control) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set or retrieve current VLAN properties.
 *
 *\description Sets/gets miscellaneous VLAN-specific properties. The control
 *          properties are from =opennsl_vlan_control_vlan_t . The flags of
 *          the opennsl_vlan_control_vlan_t can be any combination of
 *          =OPENNSL_VLAN_CONTROL_VLAN_FLAG_table . On network switch devices
 *          that allow per-VLAN MPLS enable/disable, the only valid control
 *          parameter in this API is the OPENNSL_VLAN_MPLS_DISABLE control
 *          flag (all other control parameters are ignored).
 *          When only OPENNSL_VLAN_L2_CLASS_ID_ONLY is set, the if_class_id is
 *          set to VLAN_CLASS_ID(L3_IIF.CLASS_ID is not set). When only
 *          OPENNSL_VLAN_L3_CLASS_ID is set, the l3_if_class is set to
 *          L3_IIF.CLASS_ID(VLAN_CLASS_ID is not set). If none are set, the
 *          if_class_id is set to both VLAN_CLASS_ID and L3_IIF.CLASS_ID. If
 *          both are set, if_class_id is set to VLAN_CLASS_ID and l3_if_class
 *          is set to L3_IIF.CLASS_ID. Also, on a get, both the
 *          OPENNSL_VLAN_L2_CLASS_ID_ONLY and OPENNSL_VLAN_L3_CLASS_ID are set
 *          with the returned data, if_class is set to VLAN_CLASS_ID and
 *          l3_if_class is set to L3_IIF.CLASS_ID.
 *          For trident2 plus devices, this API can be used to derive VRF for
 *          a VPN. If VRF value is 0, the VRF is INVALID.
 *          If interface map mode (opennslSwitchL3IngressInterfaceMapSet
 *          =opennsl_switches) is not set, the vrf value set by this api can
 *          be overwritten by =opennsl_l3_intf_create().  If interface map
 *          mode is set, this api will not set vrf value.
 *          =opennsl_l3_ingress_create()  api should be used to set vrf with
 *          an ingress interface.
 *          For Trident3 devices, OPENNSL_VLAN_UNKNOWN_UCAST_TOCPU now becomes
 *          a global configuration instead of per VLAN configuration, the last
 *          API call which programs OPENNSL_VLAN_UNKNOWN_UCAST_TOCPU takes
 *          effect. .
 *
 *\param    unit [IN]   Unit number.
 *\param    vlan [IN]   VLAN
 *\param    control [IN]   structure which contains VLAN property, see
 *          opennsl_vlan_control_vlan_t =opennsl_vlan_control_vlan_t
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNAVAIL Operation not supported
 *\retval    OPENNSL_E_XXX Operation failed.
 ******************************************************************************/
extern int opennsl_vlan_control_vlan_set(
    int unit, 
    opennsl_vlan_t vlan, 
    opennsl_vlan_control_vlan_t control) LIB_DLL_EXPORTED ;

#if defined(INCLUDE_L3)
#endif
#if defined(INCLUDE_L3)
#endif
#endif /* __OPENNSL_VLANX_H__ */
/*@}*/
