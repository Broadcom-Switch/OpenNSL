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
} opennsl_vlan_protocol_packet_ctrl_t;

#if defined(INCLUDE_L3)
#endif
#if defined(INCLUDE_L3)
#endif
#endif /* __OPENNSL_VLANX_H__ */
/*@}*/
