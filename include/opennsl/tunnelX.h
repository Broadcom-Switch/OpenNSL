/** \addtogroup tunnel Tunnelling
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
 * \file			tunnelX.h
 ******************************************************************************/

#ifndef __OPENNSL_TUNNELX_H__
#define __OPENNSL_TUNNELX_H__

#if defined(INCLUDE_L3)

#include <opennsl/types.h>
#include <opennsl/l3.h>

#define OPENNSL_TUNNEL_TERM_TUNNEL_WITH_ID  0x00000040 /**< Create tunnel with ID */
#define OPENNSL_TUNNEL_INIT_USE_INNER_DF    0x00000080 /**< Copy DF from inner
                                                          header. Note:flag
                                                          takes precedence over
                                                          ipv4_set_df flag. */
#define OPENNSL_TUNNEL_REPLACE              0x00010000 /**< Update existing
                                                          tunnel. */
#define OPENNSL_TUNNEL_WITH_ID              0x00080000 /**< Add using the
                                                          specified ID. */
/** Tunnel types. */
typedef enum opennsl_tunnel_type_e {
    opennslTunnelTypeVxlan = 30,        /**< VXLAN Tunnel */
} opennsl_tunnel_type_t;

/** L3 tunneling terminator. */
typedef struct opennsl_tunnel_terminator_s {
    uint32 flags;                   /**< Configuration flags. */
    uint32 multicast_flag;          /**< VXLAN Multicast trigger flags. */
    opennsl_vrf_t vrf;              /**< Virtual router instance. */
    opennsl_ip_t sip;               /**< SIP for tunnel header match. */
    opennsl_ip_t dip;               /**< DIP for tunnel header match. */
    opennsl_ip_t sip_mask;          /**< Source IP mask. */
    opennsl_ip_t dip_mask;          /**< Destination IP mask. */
    opennsl_ip6_t sip6;             /**< SIP for tunnel header match (IPv6). */
    opennsl_ip6_t dip6;             /**< DIP for tunnel header match (IPv6). */
    opennsl_ip6_t sip6_mask;        /**< Source IP mask (IPv6). */
    opennsl_ip6_t dip6_mask;        /**< Destination IP mask (IPv6). */
    uint32 udp_dst_port;            /**< UDP dst port for UDP packets. */
    uint32 udp_src_port;            /**< UDP src port for UDP packets */
    opennsl_tunnel_type_t type;     /**< Tunnel type */
    opennsl_pbmp_t pbmp;            /**< Port bitmap for this tunnel */
    opennsl_vlan_t vlan;            /**< The VLAN ID for IPMC lookup or WLAN
                                       tunnel */
    opennsl_gport_t remote_port;    /**< Remote termination */
    opennsl_gport_t tunnel_id;      /**< Tunnel id */
    int reserved1; 
    opennsl_multicast_t reserved2; 
    opennsl_failover_t reserved3; 
    opennsl_failover_t reserved4; 
    opennsl_gport_t reserved5; 
    opennsl_if_t tunnel_if;         /**< hierarchical interface. */
    int reserved6; 
    int qos_map_id;                 /**< QoS DSCP map this tunnel. */
    int inlif_counting_profile;     /**< In LIF counting profile */
    int reserved7; 
} opennsl_tunnel_terminator_t;

/** opennsl_tunnel_dscp_select_e */
typedef enum opennsl_tunnel_dscp_select_e {
    opennslTunnelDscpAssign = 0,    /**< Set outer IP header DSCP to tunnel
                                       initiator DSCP value. */
    opennslTunnelDscpPacket = 1,    /**< Copy packet DSCP to outer header. */
    opennslTunnelDscpMap = 2,       /**< Use DSCP value from DSCP map. */
    opennslTunnelDscpCount = 3      /**< Unused always last. */
} opennsl_tunnel_dscp_select_t;

/** L3 tunneling initiator. */
typedef struct opennsl_tunnel_initiator_s {
    uint32 flags;                       /**< Configuration flags. */
    opennsl_tunnel_type_t type;         /**< Tunnel type. */
    int ttl;                            /**< Tunnel header TTL. */
    opennsl_mac_t dmac;                 /**< Destination MAC address. */
    opennsl_ip_t dip;                   /**< Tunnel header DIP (IPv4). */
    opennsl_ip_t sip;                   /**< Tunnel header SIP (IPv4). */
    opennsl_ip6_t sip6;                 /**< Tunnel header SIP (IPv6). */
    opennsl_ip6_t dip6;                 /**< Tunnel header DIP (IPv6). */
    uint32 flow_label;                  /**< Tunnel header flow label (IPv6). */
    opennsl_tunnel_dscp_select_t dscp_sel; /**< Tunnel header DSCP select. */
    int dscp;                           /**< Tunnel header DSCP value. */
    int dscp_map;                       /**< DSCP-map ID. */
    opennsl_gport_t tunnel_id;          /**< Tunnel ID */
    uint16 udp_dst_port;                /**< Destination UDP port */
    uint16 udp_src_port;                /**< Source UDP port */
    opennsl_mac_t smac;                 /**< WLAN outer MAC */
    int mtu;                            /**< WLAN MTU */
    opennsl_vlan_t vlan;                /**< Tunnel VLAN */
    uint16 tpid;                        /**< Tunnel TPID */
    uint8 pkt_pri;                      /**< Tunnel priority */
    uint8 pkt_cfi;                      /**< Tunnel CFI */
    uint16 ip4_id;                      /**< IPv4 ID. */
    opennsl_if_t l3_intf_id;            /**< l3 Interface ID. */
    uint16 span_id;                     /**< Erspan Span ID. */
    uint32 aux_data;                    /**< Tunnel associated data. */
    int outlif_counting_profile;        /**< Out LIF counting profile */
    opennsl_reserved_enum_t encap_access; /**< Encapsulation Access stage */
} opennsl_tunnel_initiator_t;

typedef int (*opennsl_tunnel_initiator_traverse_cb)(
    int unit, 
    opennsl_tunnel_initiator_t *info, 
    void *user_data);

typedef int (*opennsl_tunnel_terminator_traverse_cb)(
    int unit, 
    opennsl_tunnel_terminator_t *info, 
    void *user_data);

/***************************************************************************//** 
 *\brief Set the tunneling initiator parameters on an L3 interface.
 *
 *\description Sets the tunnel configuration information for a particular L3
 *          interface. For DNX devices, use opennsl_tunnel_initiator_create. 
 *          For other devices, use opennsl_tunnel_initiator_set. .
 *
 *\param    unit [IN]   Unit number.
 *\param    intf [IN]   Interface information, of which only the interface ID is
 *          used
 *\param    tunnel [IN]   Individual tunnel configuration state
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_tunnel_initiator_set(
    int unit, 
    opennsl_l3_intf_t *intf, 
    opennsl_tunnel_initiator_t *tunnel) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set the tunneling initiator parameters on an L3 interface.
 *
 *\description Sets the tunnel configuration information for a particular L3
 *          interface. For DNX devices, use opennsl_tunnel_initiator_create. 
 *          For other devices, use opennsl_tunnel_initiator_set. .
 *
 *\param    unit [IN]   Unit number.
 *\param    intf [IN,OUT]   Interface information, of which only the interface ID
 *          is used
 *\param    tunnel [IN,OUT]   Individual tunnel configuration state
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_tunnel_initiator_create(
    int unit, 
    opennsl_l3_intf_t *intf, 
    opennsl_tunnel_initiator_t *tunnel) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete the tunnel association for the given L3 interface.
 *
 *\description Delete the tunnel association for the given L3 interface.
 *
 *\param    unit [IN]   Unit number.
 *\param    intf [IN]   Interface information, of which only the interface ID is
 *          used
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_tunnel_initiator_clear(
    int unit, 
    opennsl_l3_intf_t *intf) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the tunnel property for the given L3 interface.
 *
 *\description Gets the tunnel configuration information for a particular L3
 *          interface.
 *
 *\param    unit [IN]   Unit number.
 *\param    intf [IN]   Interface information, of which only the interface ID is
 *          used
 *\param    tunnel [OUT]   Individual tunnel configuration state
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_tunnel_initiator_get(
    int unit, 
    opennsl_l3_intf_t *intf, 
    opennsl_tunnel_initiator_t *tunnel) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Traverse tunnel initiator.
 *
 *\description Traverse tunnel initiator. The callback function is defined as
 *          following:.
 *
 *\param    unit [IN]   Unit number.
 *\param    cb [IN]   User callback function
 *\param    user_data [IN]   Pointer to user supplied cookie used in parameter in
 *          callback function
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_tunnel_initiator_traverse(
    int unit, 
    opennsl_tunnel_initiator_traverse_cb cb, 
    void *user_data) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Add a tunnel terminator for DIP-SIP key.
 *
 *\description Add a tunnel terminator for DIP-SIP key. On some devices, UDP
 *          source/dest port values are also used in the key. UDP source/dest
 *          port values are set to 0 for no UDP packet.
 *          opennsl_tunnel_terminator_create API is used for DNX devices,
 *          while  opennsl_tunnel_terminator_add API should be used for other
 *          devices.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN]   Pointer to opennsl_tunnel_terminator_t containing fields
 *          related to IP tunnel terminator point. Valid fields:
 *          =TUNNEL_TERM_ADD_FIELDS_table
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_tunnel_terminator_add(
    int unit, 
    opennsl_tunnel_terminator_t *info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Add a tunnel terminator for DIP-SIP key.
 *
 *\description Add a tunnel terminator for DIP-SIP key. On some devices, UDP
 *          source/dest port values are also used in the key. UDP source/dest
 *          port values are set to 0 for no UDP packet.
 *          opennsl_tunnel_terminator_create API is used for DNX devices,
 *          while  opennsl_tunnel_terminator_add API should be used for other
 *          devices.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN,OUT]   Pointer to opennsl_tunnel_terminator_t containing
 *          fields related to IP tunnel terminator point. Valid fields:
 *          =TUNNEL_TERM_ADD_FIELDS_table
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_tunnel_terminator_create(
    int unit, 
    opennsl_tunnel_terminator_t *info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete a tunnel terminator for DIP-SIP key.
 *
 *\description Delete a tunnel terminator for DIP-SIP key.  On some devices, UDP
 *          source/dest port values are also used in the key.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN]   Pointer to opennsl_tunnel_terminator_t containing the keys
 *          for IP tunnel terminator point. Valid fields:
 *          =TUNNEL_TERM_DEL_FIELDS_table
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_tunnel_terminator_delete(
    int unit, 
    opennsl_tunnel_terminator_t *info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Update a tunnel terminator for DIP-SIP key.
 *
 *\description Update a tunnel terminator for DIP-SIP key.  On some devices, UDP
 *          source/dest port values are also used in the key.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN]   Pointer to opennsl_tunnel_terminator_t containing fields
 *          related to IP tunnel terminator point. Valid Fields:
 *          =TUNNEL_TERM_UPDATE_FIELDS_table
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_tunnel_terminator_update(
    int unit, 
    opennsl_tunnel_terminator_t *info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get a tunnel terminator for DIP-SIP key.
 *
 *\description Get a tunnel terminator for DIP-SIP key.  On some devices, UDP
 *          source/dest port values are also used in the key.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN,OUT]   Pointer to opennsl_tunnel_terminator_t containing
 *          fields related to IP tunnel terminator point. Valid fields:
 *          =TUNNEL_TERM_GET_FIELDS_table
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_tunnel_terminator_get(
    int unit, 
    opennsl_tunnel_terminator_t *info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Traverse tunnel terminator.
 *
 *\description Traverse tunnel terminator. The callback function is defined as
 *          following:.
 *
 *\param    unit [IN]   Unit number.
 *\param    cb [IN]   User callback function
 *\param    user_data [IN]   Pointer to user supplied cookie used in parameter in
 *          callback function
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_tunnel_terminator_traverse(
    int unit, 
    opennsl_tunnel_terminator_traverse_cb cb, 
    void *user_data) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Initialize a opennsl_tunnel_initiator_t structure.
 *
 *\description Initializes a tunnel initiator structure to default values. This
 *          function should be used to initialize any tunnel initiator
 *          structure prior to filling it out and passing it to an API
 *          function. This ensures that subsequent API releases may add new
 *          structure members to the opennsl_tunnel_initiator_t structure, and
 *          opennsl_tunnel_initiator_t_init will initialize the new members to
 *           correct default values.
 *
 *\param    tunnel_init [IN,OUT]
 *
 *\retval    Nothing
 ******************************************************************************/
extern void opennsl_tunnel_initiator_t_init(
    opennsl_tunnel_initiator_t *tunnel_init) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Initialize a opennsl_tunnel_terminator_t structure.
 *
 *\description Initializes a tunnel terminator structure to default values. This
 *          function should be used to initialize any tunnel terminator
 *          structure prior to filling it out and passing it to an API
 *          function. This ensures that subsequent API releases may add new
 *          structure members to the opennsl_tunnel_terminator_t structure,
 *          and  opennsl_tunnel_terminator_t_init will initialize the new
 *          members to correct  default values.
 *
 *\param    tunnel_term [IN,OUT]
 *
 *\retval    Nothing
 ******************************************************************************/
extern void opennsl_tunnel_terminator_t_init(
    opennsl_tunnel_terminator_t *tunnel_term) LIB_DLL_EXPORTED ;

#endif /* defined(INCLUDE_L3) */

#endif /* __OPENNSL_TUNNELX_H__ */
/*@}*/
