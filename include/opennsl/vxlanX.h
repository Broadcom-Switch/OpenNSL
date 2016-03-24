/** \addtogroup vxlan Virtual extensible LAN Management
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
 * \file			vxlanX.h
 ******************************************************************************/

#ifndef __OPENNSL_VXLANX_H__
#define __OPENNSL_VXLANX_H__

#if defined(INCLUDE_L3)

#include <opennsl/types.h>
#include <opennsl/l3.h>
#include <opennsl/tunnel.h>
#include <opennsl/vlan.h>

#if defined(INCLUDE_L3)
#define OPENNSL_VXLAN_VPN_ELINE             0x00000001 
#define OPENNSL_VXLAN_VPN_ELAN              0x00000002 
#define OPENNSL_VXLAN_VPN_WITH_ID           0x00000004 
#define OPENNSL_VXLAN_VPN_WITH_VPNID        0x00000008 
#define OPENNSL_VXLAN_VPN_SERVICE_TAGGED    0x00000010 
#define OPENNSL_VXLAN_VPN_SERVICE_VLAN_DELETE 0x00000080 
#endif
#if defined(INCLUDE_L3)
#endif
#if defined(INCLUDE_L3)
#endif
#if defined(INCLUDE_L3)
/** VXLAN VPN Config Structure. */
typedef struct opennsl_vxlan_vpn_config_s {
    uint32 flags;                       /**< OPENNSL_VXLAN_VPN_xxx. */
    opennsl_vpn_t vpn;                  /**< VXLAN VPN */
    uint32 vnid;                        /**< VNID */
    uint8 pkt_pri;                      /**< Packet Priority */
    uint8 pkt_cfi;                      /**< Packet CFI */
    uint16 egress_service_tpid;         /**< Service TPID */
    opennsl_vlan_t egress_service_vlan; /**< Service VLAN */
    opennsl_multicast_t broadcast_group; 
    opennsl_multicast_t unknown_unicast_group; 
    opennsl_multicast_t unknown_multicast_group; 
    opennsl_vlan_protocol_packet_ctrl_t protocol_pkt; 
    opennsl_vlan_t vlan;                /**< Outer VLAN */
    opennsl_gport_t match_port_class;   /**< local port vlan domain */
} opennsl_vxlan_vpn_config_t;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Initialize VXLAN VPN config structure.
 *
 *\description Initialize VXLAN VPN config structure.
 *
 *\param    info [IN,OUT]   Pointer to the struct to be initialized
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_vxlan_vpn_config_t_init(
    opennsl_vxlan_vpn_config_t *info) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Create or update VXLAN VPN. When create a VXLAN VPN: If use
 *       OPENNSL_VXLAN_VPN_WITH_VPNID, both VFI and VNID will be created. If not
 *       use flag OPENNSL_VXLAN_VPN_WITH_VPNID, only VFI will be created. When
 *       update an exist VXLAN VPN(OPENNSL_VXLAN_VPN_REPLACE should be used): If
 *       use both OPENNSL_VXLAN_VPN_REPLACE and OPENNSL_VXLAN_VPN_WITH_VPNID,
 *       both VFI and VNID will be created. If only use
 *       OPENNSL_VXLAN_VPN_REPLACE, the VNID will be removed. If the flex counter
 *       is attached to the VPN, the previous flex counter information can be
 *       kept.
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN,OUT]   VPN info
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vxlan_vpn_create(
    int unit, 
    opennsl_vxlan_vpn_config_t *info) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Destroy VXLAN VPN.
 *
 *\description Destroy VXLAN VPN. .
 *
 *\param    unit [IN]   Unit number.
 *\param    l2vpn [IN]
 *
 *\retval    OPENNSL_E_XXX If Flex Counters are attached to Vxlan port or Vxlan
 *          VPN,
 *\retval    customer API sequence should invoke opennsl_vxlan_stat_detach API
 *          prior to Vxlan
 *\retval    port or Vxlan VPN deletion. Otherwise Vxlan Port delete or Vxlan VPN
 *          delete will
 *\retval    return OPENNSL_E_RESOURCE.
 ******************************************************************************/
extern int opennsl_vxlan_vpn_destroy(
    int unit, 
    opennsl_vpn_t l2vpn) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Destroy VXLAN VPN.
 *
 *\description Destroy VXLAN VPN. .
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_XXX If Flex Counters are attached to Vxlan port or Vxlan
 *          VPN,
 *\retval    customer API sequence should invoke opennsl_vxlan_stat_detach API
 *          prior to Vxlan
 *\retval    port or Vxlan VPN deletion. Otherwise Vxlan Port delete or Vxlan VPN
 *          delete will
 *\retval    return OPENNSL_E_RESOURCE.
 ******************************************************************************/
extern int opennsl_vxlan_vpn_destroy_all(
    int unit) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get VXLAN VPN.
 *
 *\description Get VXLAN VPN.
 *
 *\param    unit [IN]   Unit number.
 *\param    l2vpn [IN]
 *\param    info [OUT]   VPN info
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vxlan_vpn_get(
    int unit, 
    opennsl_vpn_t l2vpn, 
    opennsl_vxlan_vpn_config_t *info) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
typedef int(*opennsl_vxlan_vpn_traverse_cb)(
    int unit, 
    opennsl_vxlan_vpn_config_t *info, 
    void *user_data);
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Traverse all valid VXLAN VPN entries and call the supplied callback
 *       routine.
 *
 *\description Traverse all valid VXLAN VPN entry and call the supplied callback
 *          routine. The callback function is defined as following:.
 *
 *\param    unit [IN]   Unit number.
 *\param    cb [IN]   User callback function, called once per VXLAN VPN entry
 *\param    user_data [IN]   Cookie
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vxlan_vpn_traverse(
    int unit, 
    opennsl_vxlan_vpn_traverse_cb cb, 
    void *user_data) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/** VXLAN port match criteria. */
typedef enum opennsl_vxlan_port_match_e {
    OPENNSL_VXLAN_PORT_MATCH_INVALID = 0, /**< Illegal. */
    OPENNSL_VXLAN_PORT_MATCH_NONE = 1,  /**< No source match criteria. */
    OPENNSL_VXLAN_PORT_MATCH_PORT = 2,  /**< {Module, Port} or Trunk. */
    OPENNSL_VXLAN_PORT_MATCH_PORT_VLAN = 3, /**< Mod/port/trunk + outer VLAN. */
    OPENNSL_VXLAN_PORT_MATCH_VN_ID = 7, /**< Match VXLAN VN_ID */
} opennsl_vxlan_port_match_t;
#endif

#if defined(INCLUDE_L3)
#define OPENNSL_VXLAN_PORT_WITH_ID          (1 << 0)   /**< create VXLAN port with
                                                          specified ID */
#define OPENNSL_VXLAN_PORT_NETWORK          (1 << 2)   /**< Network facing
                                                          interface */
#define OPENNSL_VXLAN_PORT_EGRESS_TUNNEL    (1 << 7)   /**< Specified Egress
                                                          tunnel is valid */
#define OPENNSL_VXLAN_PORT_SERVICE_TAGGED   (1 << 8)   /**< Service tag mode */
#define OPENNSL_VXLAN_PORT_MULTICAST        (1 << 19)  /**< Create Multicast-only
                                                          VXLAN Tunnel */
#endif
#if defined(INCLUDE_L3)
/** VXLAN Gport */
typedef struct opennsl_vxlan_port_s {
    opennsl_gport_t vxlan_port_id;      /**< GPORT identifier. */
    uint32 flags;                       /**< OPENNSL_VXLAN_PORT_xxx. */
    uint16 int_pri;                     /**< Internal Priority */
    uint8 pkt_pri;                      /**< Packet Priority */
    uint8 pkt_cfi;                      /**< Packet CFI */
    uint16 egress_service_tpid;         /**< Service Vlan TPID Value */
    opennsl_vlan_t egress_service_vlan; /**< SD-TAG Vlan ID. */
    uint16 mtu;                         /**< MTU */
    opennsl_gport_t match_port;         /**< Match port / trunk */
    opennsl_vxlan_port_match_t criteria; /**< Match criteria */
    opennsl_vlan_t match_vlan;          /**< Outer VLAN ID to match. */
    opennsl_vlan_t match_inner_vlan;    /**< Inner VLAN ID to match. */
    opennsl_gport_t egress_tunnel_id;   /**< Tunnel Initiator ID */
    opennsl_gport_t match_tunnel_id;    /**< Tunnel Terminator ID */
    opennsl_if_t egress_if;             /**< VXLAN egress object. */
} opennsl_vxlan_port_t;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Initialize VXLAN port structure.
 *
 *\description Initialize the VXLAN port structure.
 *
 *\param    vxlan_port [IN,OUT]   Pointer to the struct to be initialized
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_vxlan_port_t_init(
    opennsl_vxlan_port_t *vxlan_port) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Initialize the OPENNSL VXLAN subsystem.
 *
 *\description Initialize VXLAN software module, init all hardware VXLAN state.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vxlan_init(
    int unit) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Detach the OPENNSL VXLAN subsystem.
 *
 *\description Detach VXLAN software module, clear all hardware VXLAN state.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vxlan_cleanup(
    int unit) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief opennsl_vxlan_port_add adds a Access or Network VXLAN port.
 *
 *\description Add VXLAN/NIV/PE port to VXLAN Network.
 *          VXLAN Network-domain ports are shared by all VXLAN VPNs. Customers
 *          should make use of a Reserved VXLAN VPN to add all Network-domain
 *          VXLAN ports within their system.
 *          When parameter vxlan_port->vxlan_port_id is NIV/PE port id and
 *          flag OPENNSL_VXLAN_PORT_REPLACE is used, this API is used to add
 *          the NIV/PE port to VxLAN vpn forwarding domain. But please note
 *          that the NIV/PE port is not coverted to VxLAN port, it's still
 *          NIV/PE port. NIV/PE port id should be used for virtual port
 *          operations.
 *          When invalid vpn id OPENNSL_VXLAN_VPN_INVALID and vxlan port match
 *          criteria OPENNSL_VXLAN_PORT_MATCH_SHARE are used, this API is used
 *          to create access shared virtual port, which does not belong to any
 *          VPN and can be shared by multiple VXLAN VPNs. After the shared
 *          logical port is created, opennsl_port_match_add() can be used to
 *          associate multiple VPNs with that shared virtual port. Before
 *          deleting the shared logical port, we should use
 *          opennsl_port_match_delete() to remove all the associated port
 *          match criteria and VPNs first of all. The port match added by
 *          opennsl_port_match_add() should be deleted by
 *          opennsl_port_match_delete().
 *
 *\param    unit [IN]   Unit number.
 *\param    l2vpn [IN]
 *\param    vxlan_port [IN,OUT]   VXLAN port information
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vxlan_port_add(
    int unit, 
    opennsl_vpn_t l2vpn, 
    opennsl_vxlan_port_t *vxlan_port) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief opennsl_vxlan_port_delete VXLAN port from VXLAN network.
 *
 *\description Delete VXLAN port from VXLAN Network. If delete a shared logical
 *          port, the  parameter vpn must equal OPENNSL_VXLAN_VPN_INVALID. .
 *
 *\param    unit [IN]   Unit number.
 *\param    l2vpn [IN]
 *\param    vxlan_port_id [IN]   VXLAN port ID for deletion
 *
 *\retval    OPENNSL_E_XXX If Flex Counters are attached to Vxlan port or Vxlan
 *          VPN,
 *\retval    customer API sequence should invoke opennsl_vxlan_stat_detach API
 *          prior to Vxlan
 *\retval    port or Vxlan VPN deletion. Otherwise Vxlan Port delete or Vxlan VPN
 *          delete will
 *\retval    return OPENNSL_E_RESOURCE.
 *\retval    To delete all VXLAN Network-domain ports, specify Reserved VXLAN VPN.
 *\retval    To delete VXLAN Access-domain ports, specify VXLAN VPN.
 ******************************************************************************/
extern int opennsl_vxlan_port_delete(
    int unit, 
    opennsl_vpn_t l2vpn, 
    opennsl_gport_t vxlan_port_id) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief opennsl_vxlan_port_delete VXLAN port from VXLAN network.
 *
 *\description Delete VXLAN port from VXLAN Network. If delete a shared logical
 *          port, the  parameter vpn must equal OPENNSL_VXLAN_VPN_INVALID. .
 *
 *\param    unit [IN]   Unit number.
 *\param    l2vpn [IN]
 *
 *\retval    OPENNSL_E_XXX If Flex Counters are attached to Vxlan port or Vxlan
 *          VPN,
 *\retval    customer API sequence should invoke opennsl_vxlan_stat_detach API
 *          prior to Vxlan
 *\retval    port or Vxlan VPN deletion. Otherwise Vxlan Port delete or Vxlan VPN
 *          delete will
 *\retval    return OPENNSL_E_RESOURCE.
 *\retval    To delete all VXLAN Network-domain ports, specify Reserved VXLAN VPN.
 *\retval    To delete VXLAN Access-domain ports, specify VXLAN VPN.
 ******************************************************************************/
extern int opennsl_vxlan_port_delete_all(
    int unit, 
    opennsl_vpn_t l2vpn) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get VXLAN port information.
 *
 *\description Get VXLAN port information for given VXLAN port ID.
 *
 *\param    unit [IN]   Unit number.
 *\param    l2vpn [IN]
 *\param    vxlan_port [IN,OUT]   VXLAN port information
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vxlan_port_get(
    int unit, 
    opennsl_vpn_t l2vpn, 
    opennsl_vxlan_port_t *vxlan_port) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get all VXLAN port information.
 *
 *\description Get all VXLAN port information. To obtain all VXLAN Network-domain
 *          ports, specify Reserved VXLAN VPN. To obtain VXLAN Access-domain
 *          ports, specify VXLAN VPN.
 *
 *\param    unit [IN]   Unit number.
 *\param    l2vpn [IN]
 *\param    port_max [IN]   Maximum number of VXLAN ports in array
 *\param    port_array [OUT]   Array of VXLAN ports
 *\param    port_count [OUT]   Number of VXLAN ports returned in array
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vxlan_port_get_all(
    int unit, 
    opennsl_vpn_t l2vpn, 
    int port_max, 
    opennsl_vxlan_port_t *port_array, 
    int *port_count) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Create VXLAN Tunnel Initiator.
 *
 *\description Create VXLAN Tunnel Initiator. When OPENNSL_TUNNEL_REPLACE is used
 *          to modify a existed VXLAN Tunnel Initiator, dip of Tunnel
 *          Initiator should be dip of this existed VXLAN Tunnel Initiator you
 *          want to modify. Dip of Tunnel Initiator can not updated with this
 *          flag. In fact, dip can not be updated now. And multicast_flag can
 *          not take effect in this API either.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN,OUT]   Tunnel Initiator Info
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vxlan_tunnel_initiator_create(
    int unit, 
    opennsl_tunnel_initiator_t *info) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Delete VXLAN Tunnel Initiator.
 *
 *\description Delete VXLAN Tunnel Initiator.
 *
 *\param    unit [IN]   Unit number.
 *\param    vxlan_tunnel_id [IN]   Tunnel Initiator Id
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vxlan_tunnel_initiator_destroy(
    int unit, 
    opennsl_gport_t vxlan_tunnel_id) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get VXLAN Tunnel Initiator.
 *
 *\description Get VXLAN Tunnel Initiator.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN,OUT]   Tunnel Initiator Info
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vxlan_tunnel_initiator_get(
    int unit, 
    opennsl_tunnel_initiator_t *info) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Traverse VXLAN Tunnel initiator.
 *
 *\description Traverse VXLAN Tunnel initiator. The callback function is defined
 *          as following:.
 *
 *\param    unit [IN]   Unit number.
 *\param    cb [IN]   User callback function
 *\param    user_data [IN]   User supplied cookie used in parameter in callback
 *          function
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vxlan_tunnel_initiator_traverse(
    int unit, 
    opennsl_tunnel_initiator_traverse_cb cb, 
    void *user_data) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Create VXLAN Tunnel terminator.
 *
 *\description Create VXLAN Tunnel terminator.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN,OUT]   Tunnel Terminator Info
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vxlan_tunnel_terminator_create(
    int unit, 
    opennsl_tunnel_terminator_t *info) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Update multicast/active state per VXLAN Tunnel terminator.
 *
 *\description Update multicast/active state of VXLAN Tunnel terminator. And this
 *          API can only be used to Update multicast/active state of VXLAN
 *          Tunnel terminator.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN,OUT]   Tunnel Terminator Info
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vxlan_tunnel_terminator_update(
    int unit, 
    opennsl_tunnel_terminator_t *info) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Delete VXLAN Tunnel terminator.
 *
 *\description Delete VXLAN Tunnel terminator.
 *
 *\param    unit [IN]   Unit number.
 *\param    vxlan_tunnel_id [IN]
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vxlan_tunnel_terminator_destroy(
    int unit, 
    opennsl_gport_t vxlan_tunnel_id) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get VXLAN Tunnel terminator.
 *
 *\description Get VXLAN Tunnel terminator.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN,OUT]   Tunnel Terminator Info
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vxlan_tunnel_terminator_get(
    int unit, 
    opennsl_tunnel_terminator_t *info) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Traverse VXLAN Tunnel terminator.
 *
 *\description Traverse VXLAN Tunnel terminator. The callback function is defined
 *          as following:.
 *
 *\param    unit [IN]   Unit number.
 *\param    cb [IN]   User callback function
 *\param    user_data [IN]   User supplied cookie used in parameter in callback
 *          function
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vxlan_tunnel_terminator_traverse(
    int unit, 
    opennsl_tunnel_terminator_traverse_cb cb, 
    void *user_data) LIB_DLL_EXPORTED ;
#endif

/** Ingress and Egress statistics maintained per Vxlan. */
typedef enum opennsl_vxlan_stat_e {
    opennslVxlanInPackets = 0,  /**< Packets that ingress on the vxlan */
    opennslVxlanOutPackets = 1, /**< Packets that egress on the vxlan */
    opennslVxlanInBytes = 2,    /**< Bytes that ingress on the vxlan */
    opennslVxlanOutBytes = 3    /**< Bytes that egress on the vxlan */
} opennsl_vxlan_stat_t;

/***************************************************************************//** 
 *\brief Attach counters entries to the given vxlan vp/vpn index.
 *
 *\description This API will attach counters entries to the given vxlan vp or vpn
 *          index. It's recommended to associate the vxlan port with a set of
 *          counters which are created with opennslStatObjectIngVxlan or
 *          opennslStatObjectEgrVxlan. It's recommended to associate the vxlan
 *          vpn with a set of counters which are created with
 *          opennslStatObjectIngVfi or opennslStatObjectEgrVfi. The below
 *          table mentions the flex stat actions for the input vxlan
 *          parameters.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   vxlan vp index
 *\param    vpn [IN]   vxlan vpn index
 *\param    stat_counter_id [IN]   Stat Counter ID
 *
 *\retval    OPENNSL_E_xxx
 *\retval    OPENNSL_E_PARAM for Invalid Vpn and Invalid Port
 ******************************************************************************/
extern int opennsl_vxlan_stat_attach(
    int unit, 
    opennsl_gport_t port, 
    opennsl_vpn_t vpn, 
    uint32 stat_counter_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Detach counters entries to the given vxlan vp/vpn index.
 *
 *\description This API will detach counters entries to the given vxlan vp/vpn
 *          index. The below table mentions the flex stat actions for the
 *          input vxlan parameters.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   vxlan vp index
 *\param    vpn [IN]   vxlan vpn index
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_vxlan_stat_detach(
    int unit, 
    opennsl_gport_t port, 
    opennsl_vpn_t vpn) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get counter statistic values for a vxlan vp/vpn index.
 *
 *\description This API will retrieve set of counter statistic values for a vxlan
 *          vp/vpn index. The below table mentions the flex stat actions for
 *          the input vxlan parameters.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   vxlan vp index
 *\param    vpn [IN]   vxlan vpn index
 *\param    stat [IN]   Vxlan counter stat types.
 *\param    num_entries [IN]   Number of counter Entries
 *\param    counter_indexes [IN]   Pointer to Counter indexes entries
 *\param    counter_values [OUT]   Pointer to counter values
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_vxlan_stat_counter_get(
    int unit, 
    opennsl_gport_t port, 
    opennsl_vpn_t vpn, 
    opennsl_vxlan_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    opennsl_stat_value_t *counter_values) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Force an immediate counter update and retrieve counter statistic values
 *       for a vxlan vp/vpn index.
 *
 *\description Similar to opennsl_vxlan_stat_counter_get(), value returned is
 *          software  accumulated counter synced with the hardware counter.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   vxlan vp index
 *\param    vpn [IN]   vxlan vpn index
 *\param    stat [IN]   Vxlan counter stat types.
 *\param    num_entries [IN]   Number of counter Entries
 *\param    counter_indexes [IN]   Pointer to Counter indexes entries
 *\param    counter_values [OUT]   Pointer to counter values
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_vxlan_stat_counter_sync_get(
    int unit, 
    opennsl_gport_t port, 
    opennsl_vpn_t vpn, 
    opennsl_vxlan_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    opennsl_stat_value_t *counter_values) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set counter statistic values for a vxlan vp/vpn index.
 *
 *\description This API will set counter statistic values for a vxlan vp/vpn
 *          index. The below table mentions the flex stat actions for the
 *          input vxlan parameters.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   vxlan vp index
 *\param    vpn [IN]   vxlan vpn index
 *\param    stat [IN]   Vxlan counter stat types.
 *\param    num_entries [IN]   Number of counter Entries
 *\param    counter_indexes [IN]   Pointer to Counter indexes entries
 *\param    counter_values [IN]   Pointer to counter values
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_vxlan_stat_counter_set(
    int unit, 
    opennsl_gport_t port, 
    opennsl_vpn_t vpn, 
    opennsl_vxlan_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    opennsl_stat_value_t *counter_values) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get stat counter ID associated with given vxlan vp/vpn index.
 *
 *\description This API will provide stat counter IDs associated with given vxlan
 *          vp/vpn index The below table mentions the flex stat actions for
 *          the input vxlan parameters.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   vxlan vp index
 *\param    vpn [IN]   vxlan vpn index
 *\param    stat [IN]   Vxlan counter stat types.
 *\param    stat_counter_id [OUT]   stat counter ID
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_vxlan_stat_id_get(
    int unit, 
    opennsl_gport_t port, 
    opennsl_vpn_t vpn, 
    opennsl_vxlan_stat_t stat, 
    uint32 *stat_counter_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Enable/Disable collection of statistics on the indicated port or vpn.
 *
 *\description This API will initialize statistic collection for the given vp/vpn
 *          (enable=TRUE)  or release the HW resources used for the tracking
 *          the statistics (enable=FALSE). The below table mentions the flex
 *          stat actions for the input vxlan parameters.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   vxlan vp index
 *\param    vpn [IN]   vxlan vpn index
 *\param    enable [IN]   Non-zero to enable counter collection, zero to disable.
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_vxlan_stat_enable_set(
    int unit, 
    opennsl_gport_t port, 
    opennsl_vpn_t vpn, 
    int enable) LIB_DLL_EXPORTED ;

#if defined(INCLUDE_L3)
typedef int(*opennsl_vxlan_port_traverse_cb)(
    int unit, 
    opennsl_vxlan_port_t *info, 
    void *user_data);
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Traverse all valid VXLAN port and call the supplied callback routine.
 *
 *\description Traverse all valid VXLAN port and call the supplied callback
 *          routine to get the VXLAN port information. The callback function
 *          is defined as following: .
 *
 *\param    unit [IN]   Unit number.
 *\param    cb [IN]   User callback function, called once per VXLAN port
 *\param    user_data [IN]   Cookie
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_vxlan_port_traverse(
    int unit, 
    opennsl_vxlan_port_traverse_cb cb, 
    void *user_data) LIB_DLL_EXPORTED ;
#endif

#endif /* defined(INCLUDE_L3) */

#endif /* __OPENNSL_VXLANX_H__ */
/*@}*/
