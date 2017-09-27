/** \addtogroup mpls MPLS Management
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
 * \file			mplsX.h
 ******************************************************************************/

#ifndef __OPENNSL_MPLSX_H__
#define __OPENNSL_MPLSX_H__

#include <opennsl/types.h>
#include <opennsl/vlan.h>
#include <opennsl/switch.h>

#if defined(INCLUDE_L3)
/** MPLS EXP Map Structure. */
typedef struct opennsl_mpls_exp_map_s {
    int priority;           /**< Internal priority. */
    opennsl_color_t color;  /**< Color. */
    uint8 dscp;             /**< Diff Serv Code Point. */
    uint8 exp;              /**< EXP value. */
    uint8 pkt_pri;          /**< Packet priority value. */
    uint8 pkt_cfi;          /**< Packet CFI value. */
} opennsl_mpls_exp_map_t;
#endif

#define OPENNSL_MPLS_EGRESS_LABEL_TTL_SET   0x00000001 
#define OPENNSL_MPLS_EGRESS_LABEL_TTL_COPY  0x00000002 
#define OPENNSL_MPLS_EGRESS_LABEL_TTL_DECREMENT 0x00000004 
#define OPENNSL_MPLS_EGRESS_LABEL_ACTION_VALID 0x00002000 /**< When set action is
                                                          taken from action
                                                          field */
#define OPENNSL_MPLS_EGRESS_LABEL_REPLACE   0x00004000 /**< Replace existing
                                                          entry. */
#define OPENNSL_MPLS_EGRESS_LABEL_WITH_ID   0x00008000 /**< Add using the
                                                          specified ID. */
/** MPLS label egress actions. */
typedef enum opennsl_mpls_egress_action_e {
    OPENNSL_MPLS_EGRESS_ACTION_SWAP = 0, 
    OPENNSL_MPLS_EGRESS_ACTION_PHP  = 1, 
    OPENNSL_MPLS_EGRESS_ACTION_PUSH = 2, 
    OPENNSL_MPLS_EGRESS_ACTION_NOP  = 3, 
    OPENNSL_MPLS_EGRESS_ACTION_SWAP_OR_PUSH = 4 
} opennsl_mpls_egress_action_t;

/** opennsl_mpls_egress_label_s */
typedef struct opennsl_mpls_egress_label_s {
    uint32 flags;                       /**< OPENNSL_MPLS_EGRESS_LABEL_xxx. */
    opennsl_mpls_label_t label;         
    int qos_map_id;                     /**< EXP map ID. */
    uint8 exp;                          
    uint8 ttl;                          
    uint8 pkt_pri;                      
    uint8 pkt_cfi;                      
    opennsl_if_t tunnel_id;             /**< Tunnel Interface. */
    opennsl_if_t l3_intf_id;            /**< l3 Interface ID. */
    opennsl_mpls_egress_action_t action; /**< MPLS label action, relevant when
                                           OPENNSL_MPLS_EGRESS_LABEL_ACTION_VALID
                                           is set. */
    int reserved1; 
    int reserved2; 
    opennsl_failover_t egress_failover_id; /**< Failover object index for Egress
                                           Protection. */
    opennsl_if_t egress_failover_if_id; /**< Failover MPLS Tunnel identifier for
                                           Egress Protection. */
    int outlif_counting_profile;        /**< Out LIF counting profile */
    opennsl_reserved_enum_t reserved3; 
    opennsl_reserved_enum_t reserved4; 
} opennsl_mpls_egress_label_t;

#if defined(INCLUDE_L3)
/** MPLS port match criteria. */
typedef enum opennsl_mpls_port_match_e {
    OPENNSL_MPLS_PORT_MATCH_INVALID = 0, /**< Illegal. */
    OPENNSL_MPLS_PORT_MATCH_NONE = 1,   /**< No source match criteria. */
    OPENNSL_MPLS_PORT_MATCH_PORT = 2,   /**< {Module, Port} or Trunk. */
    OPENNSL_MPLS_PORT_MATCH_PORT_VLAN = 3, /**< Mod/port/trunk + outer VLAN ID. */
    OPENNSL_MPLS_PORT_MATCH_PORT_INNER_VLAN = 4, /**< Mod/port/trunk + inner VLAN ID. */
    OPENNSL_MPLS_PORT_MATCH_PORT_VLAN_STACKED = 5, /**< Mod/port/trunk + outer/inner VLAN ID. */
    OPENNSL_MPLS_PORT_MATCH_VLAN_PRI = 6, /**< Mod/port/trunk + VLAN-PRI + VLAN-CFI. */
    OPENNSL_MPLS_PORT_MATCH_LABEL = 7,  /**< MPLS label. */
    OPENNSL_MPLS_PORT_MATCH_LABEL_PORT = 8, /**< MPLS label + Mod/port/trunk. */
    OPENNSL_MPLS_PORT_MATCH_LABEL_VLAN = 9, /**< MPLS label + VLAN. */
    OPENNSL_MPLS_PORT_MATCH_PORT_SUBPORT_PKT_VID = 10, /**< Mod/port/trunk + LLTAG VLAN ID. */
    OPENNSL_MPLS_PORT_MATCH_PORT_SUBPORT_PKT_VID_OUTER_VLAN = 11, /**< Mod/port/trunk + LLTAG VLAN ID +
                                           outer VLAN ID. */
    OPENNSL_MPLS_PORT_MATCH_PORT_SUBPORT_PKT_VID_INNER_VLAN = 12, /**< Mod/port/trunk + LLTAG VLAN ID +
                                           inner VLAN ID. */
    OPENNSL_MPLS_PORT_MATCH_SHARE = 13, /**< Multiple match criteria Share one
                                           MPLS logical port. */
    OPENNSL_MPLS_PORT_MATCH_PORT_VLAN_TAG = 14, /**< Mod/port/trunk + Outer VLAN-PRI +
                                           Outer VLAN-CFI + Outer VLAN ID. */
    OPENNSL_MPLS_PORT_MATCH_PORT_INNER_VLAN_TAG = 15, /**< Mod/port/trunk + Inner VLAN-PRI +
                                           Inner VLAN-CFI + Inner VLAN ID. */
    OPENNSL_MPLS_PORT_MATCH_COUNT = 16  /**< Must be last. */
} opennsl_mpls_port_match_t;
#endif

#if defined(INCLUDE_L3)
#endif
#if defined(INCLUDE_L3)
#endif
#if defined(INCLUDE_L3)
/** VCCV Control Channel Type */
typedef enum opennsl_mpls_port_control_channel_type_e {
    opennslMplsPortControlChannelNone         = 0, 
    opennslMplsPortControlChannelAch          = 1, 
    opennslMplsPortControlChannelRouterAlert  = 2, 
    opennslMplsPortControlChannelTtl          = 3, 
    opennslMplsPortControlChannelGalUnderPw   = 4 
} opennsl_mpls_port_control_channel_type_t;
#endif

#if defined(INCLUDE_L3)
/** MPLS port type. */
typedef struct opennsl_mpls_port_s {
    opennsl_gport_t mpls_port_id;       /**< GPORT identifier. */
    uint32 flags;                       /**< OPENNSL_MPLS_PORT_xxx. */
    uint32 flags2;                      /**< OPENNSL_MPLS_PORT2_xxx. */
    int if_class;                       /**< Interface class ID. */
    int exp_map;                        /**< Incoming EXP map ID. */
    int int_pri;                        /**< Internal priority. */
    uint8 pkt_pri;                      /**< Packet priority. */
    uint8 pkt_cfi;                      /**< Packet CFI. */
    uint16 service_tpid;                /**< Service VLAN TPID value. */
    opennsl_gport_t port;               /**< Match port and/or egress port. */
    opennsl_mpls_port_match_t criteria; /**< Match criteria. */
    opennsl_vlan_t match_vlan;          /**< Outer VLAN ID to match. */
    opennsl_vlan_t match_inner_vlan;    /**< Inner VLAN ID to match. */
    opennsl_mpls_label_t match_label;   /**< VC label to match. */
    opennsl_if_t egress_tunnel_if;      /**< MPLS tunnel egress object. */
    opennsl_mpls_egress_label_t egress_label; /**< Outgoing VC label. */
    int mtu;                            /**< MPLS port MTU. */
    opennsl_vlan_t egress_service_vlan; /**< Service VLAN to Add/Replace. */
    uint32 pw_seq_number;               /**< Initial-value of Pseudo-wire Sequence
                                           number */
    opennsl_if_t encap_id;              /**< Encap Identifier. */
    opennsl_failover_t ingress_failover_id; /**< Ingress Failover Object Identifier. */
    opennsl_gport_t ingress_failover_port_id; /**< Ingress Failover MPLS Port
                                           Identifier. */
    opennsl_failover_t failover_id;     /**< Failover Object Identifier. */
    opennsl_gport_t failover_port_id;   /**< Failover MPLS Port Identifier. */
    opennsl_policer_t policer_id;       /**< Policer ID to be associated with the
                                           MPLS gport */
    opennsl_multicast_t failover_mc_group; /**< MC group used for bi-cast. */
    opennsl_failover_t pw_failover_id;  /**< Failover Object Identifier for
                                           Redundant PW. */
    opennsl_gport_t pw_failover_port_id; /**< Redundant PW port Identifier. */
    opennsl_mpls_port_control_channel_type_t vccv_type; /**< Indicate VCCV Control Channel */
    opennsl_switch_network_group_t network_group_id; /**< Split Horizon network group
                                           identifier */
    opennsl_vlan_t match_subport_pkt_vid; /**< LLTAG VLAN ID to match. */
    opennsl_gport_t tunnel_id;          /**< Tunnel Id pointing to ingress LSP. */
    opennsl_gport_t per_flow_queue_base; /**< Base queue of the per flow queue set.
                                           Actual queue is decided based on
                                           internal priority and qos map. */
    int qos_map_id;                     /**< QOS map identifier. */
    opennsl_failover_t egress_failover_id; /**< Failover object index for Egress
                                           Protection */
    opennsl_gport_t egress_failover_port_id; /**< Failover MPLS Port identifier for
                                           Egress Protection */
    uint32 class_id;                    /**< Class ID */
    int inlif_counting_profile;         /**< In LIF counting profile */
} opennsl_mpls_port_t;
#endif

#if defined(INCLUDE_L3)
/** MPLS label actions. */
typedef enum opennsl_mpls_switch_action_e {
    OPENNSL_MPLS_SWITCH_ACTION_SWAP        = 0, 
    OPENNSL_MPLS_SWITCH_ACTION_PHP         = 1, 
    OPENNSL_MPLS_SWITCH_ACTION_POP         = 2, 
    OPENNSL_MPLS_SWITCH_ACTION_POP_DIRECT  = 3, 
    OPENNSL_MPLS_SWITCH_ACTION_NOP         = 4, 
    OPENNSL_MPLS_SWITCH_EGRESS_ACTION_PUSH = 5, 
    OPENNSL_MPLS_SWITCH_ACTION_INVALID     = 6 
} opennsl_mpls_switch_action_t;
#endif

#if defined(INCLUDE_L3)
#define OPENNSL_MPLS_SWITCH_INNER_TTL       0x00000100 /**< (POP/PHP) Get TTL from
                                                          header following
                                                          popped label. */
#define OPENNSL_MPLS_SWITCH_TTL_DECREMENT   0x00000200 /**< Decrement the TTL
                                                          value by 1. */
#endif
#if defined(INCLUDE_L3)
#endif
#if defined(INCLUDE_L3)
/** MPLS tunnel switch structure. */
typedef struct opennsl_mpls_tunnel_switch_s {
    uint32 flags;                       /**< OPENNSL_MPLS_SWITCH_xxx. */
    uint32 reserved1; 
    opennsl_mpls_label_t label;         /**< Incoming label value. */
    opennsl_mpls_label_t second_label;  /**< Incoming second label. */
    opennsl_gport_t port;               /**< Incoming port. */
    opennsl_mpls_switch_action_t action; /**< MPLS label action. */
    opennsl_mpls_switch_action_t action_if_bos; /**< MPLS label action if BOS. */
    opennsl_mpls_switch_action_t action_if_not_bos; /**< MPLS label action if not BOS. */
    opennsl_multicast_t mc_group;       /**< P2MP Multicast group. */
    int exp_map;                        /**< EXP-map ID. */
    int int_pri;                        /**< Internal priority. */
    opennsl_policer_t policer_id;       /**< Policer ID to be associated with the
                                           incoming label. */
    opennsl_vpn_t vpn;                  /**< L3 VPN used if action is POP. */
    opennsl_mpls_egress_label_t egress_label; /**< Outgoing label information. */
    opennsl_if_t egress_if;             /**< Outgoing egress object. */
    opennsl_if_t ingress_if;            /**< Ingress Interface object. */
    int mtu;                            /**< MTU. */
    int qos_map_id;                     /**< QOS map identifier. */
    opennsl_failover_t failover_id;     /**< Failover Object Identifier for
                                           protected tunnel. Used for 1+1
                                           protection also */
    opennsl_gport_t tunnel_id;          /**< Tunnel ID. */
    opennsl_gport_t failover_tunnel_id; /**< Failover Tunnel ID. */
    opennsl_if_t tunnel_if;             /**< hierarchical interface, relevant for
                                           when action is
                                           OPENNSL_MPLS_SWITCH_ACTION_POP. */
    opennsl_gport_t egress_port;        /**< Outgoing egress port. */
    uint16 oam_global_context_id;       /**< OAM global context id passed from
                                           ingress to egress XGS chip. */
    uint32 class_id;                    /**< Class ID */
    int inlif_counting_profile;         /**< In LIF counting profile */
    int reserved2; 
    int reserved3; 
} opennsl_mpls_tunnel_switch_t;
#endif

#if defined(INCLUDE_L3)
/** MPLS Entropy identifier Config Structure. */
typedef struct opennsl_mpls_entropy_identifier_s {
    opennsl_mpls_label_t label; /**< Incoming entropy label value. */
    opennsl_mpls_label_t mask;  /**< Entropy label mask. */
    int pri;                    /**< Priority value of the entropy label. */
    uint32 flags;               /**< OPENNSL_MPLS_ENTROPY_xxx. */
} opennsl_mpls_entropy_identifier_t;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Initialize the MPLS port structure.
 *
 *\description Initialize the MPLS port structure.
 *
 *\param    mpls_port [IN,OUT]   Pointer to the struct to be initialized
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_mpls_port_t_init(
    opennsl_mpls_port_t *mpls_port) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Initialize the MPLS egress label structure.
 *
 *\description Initialize the MPLS egress label structure.
 *
 *\param    label [IN,OUT]   Pointer to the struct to be initialized
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_mpls_egress_label_t_init(
    opennsl_mpls_egress_label_t *label) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Initialize the MPLS tunnel switch structure.
 *
 *\description Initialize the MPLS tunnel switch structure.
 *
 *\param    info [IN,OUT]   Pointer to the struct to be initialized
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_mpls_tunnel_switch_t_init(
    opennsl_mpls_tunnel_switch_t *info) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Initialize MPLS Entropy label identifier structure.
 *
 *\description Initialize MPLS Entropy label identifier structure.
 *
 *\param    info [IN,OUT]   Pointer to the struct to be initialized
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_mpls_entropy_identifier_t_init(
    opennsl_mpls_entropy_identifier_t *info) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Initialize the MPLS EXP map structure.
 *
 *\description Initialize the MPLS EXP map structure.
 *
 *\param    exp_map [IN,OUT]   Pointer to the struct to be initialized
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_mpls_exp_map_t_init(
    opennsl_mpls_exp_map_t *exp_map) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Initialize the OPENNSL MPLS subsystem.
 *
 *\description Initialize the MPLS software module, clear all hardware MPLS
 *          state.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_init(
    int unit) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Detach the MPLS software module.
 *
 *\description Detach the MPLS software module, clear all hardware MPLS state.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_cleanup(
    int unit) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
#define OPENNSL_MPLS_VPN_L3         0x00000001 
#define OPENNSL_MPLS_VPN_VPWS       0x00000002 
#define OPENNSL_MPLS_VPN_VPLS       0x00000004 
#define OPENNSL_MPLS_VPN_REPLACE    0x00000008 
#define OPENNSL_MPLS_VPN_WITH_ID    0x00000010 
#endif
#if defined(INCLUDE_L3)
#endif
#if defined(INCLUDE_L3)
#endif
#if defined(INCLUDE_L3)
/** MPLS VPN Config Structure. */
typedef struct opennsl_mpls_vpn_config_s {
    uint32 flags;                       /**< OPENNSL_MPLS_VPN_xxx. */
    opennsl_vpn_t vpn;                  
    int lookup_id;                      
    opennsl_multicast_t broadcast_group; 
    opennsl_multicast_t unknown_unicast_group; 
    opennsl_multicast_t unknown_multicast_group; 
    opennsl_policer_t policer_id;       /**< Policer id to be used */
    opennsl_vlan_protocol_packet_ctrl_t protocol_pkt; /**< Protocol packet control */
} opennsl_mpls_vpn_config_t;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Initialize the MPLS VPN config structure.
 *
 *\description Initialize the MPLS VPN config structure.
 *
 *\param    info [IN,OUT]   Pointer to the struct to be initialized
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_mpls_vpn_config_t_init(
    opennsl_mpls_vpn_config_t *info) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Create an MPLS VPN.
 *
 *\description Create an MPLS VPN. The opennsl_mpls_vpn_config_t structure is
 *          described below:.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN,OUT]   VPN info
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_vpn_id_create(
    int unit, 
    opennsl_mpls_vpn_config_t *info) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Destroy an MPLS VPN.
 *
 *\description Destroy an MPLS VPN. .
 *
 *\param    unit [IN]   Unit number.
 *\param    vpn [IN]   VPN ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_vpn_id_destroy(
    int unit, 
    opennsl_vpn_t vpn) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Destroy an MPLS VPN.
 *
 *\description Destroy an MPLS VPN. .
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_vpn_id_destroy_all(
    int unit) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get an MPLS VPN.
 *
 *\description Get an MPLS VPN.
 *
 *\param    unit [IN]   Unit number.
 *\param    vpn [IN]   VPN ID
 *\param    info [OUT]   VPN info
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_vpn_id_get(
    int unit, 
    opennsl_vpn_t vpn, 
    opennsl_mpls_vpn_config_t *info) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
typedef int(*opennsl_mpls_vpn_traverse_cb)(
    int unit, 
    opennsl_mpls_vpn_config_t *info, 
    void *user_data);
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Traverse all valid MPLS VPN entries and call the supplied callback
 *       routine.
 *
 *\description Traverse all valid MPLS VPN entry and call the supplied callback
 *          routine. The callback function is defined as following:.
 *
 *\param    unit [IN]   Unit number.
 *\param    cb [IN]   User callback function, called once per MPLS VPN entry
 *\param    user_data [IN]   Cookie
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_vpn_traverse(
    int unit, 
    opennsl_mpls_vpn_traverse_cb cb, 
    void *user_data) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Add an MPLS port to an L2 VPN.
 *
 *\description Add an MPLS port to an L2 VPN. VPN ID may be a valid ID to add the
 *          MPLS port. When VPN ID is OPENNSL_MPLS_VPxS_VPN_INVALID, the MPLS
 *          port is added to an inactive VPN. The possible INVALID_VPN values
 *          are: OPENNSL_MPLS_VPWS_VPN_INVALID and
 *          OPENNSL_MPLS_VPLS_VPN_INVALID, the former is for VPWS VPN while
 *          the latter for VPLS VPN. OPENNSL_MPLS_PORT_WITH_ID may be used to
 *          attach/detach the mpls_port from VPN. When MPLS backup port is
 *          deleted and added back then user should pass failover id with
 *          backup port in order to associate it with primary port. Another
 *          alternate is to re-program primary port with
 *          OPENNSL_MPLS_PORT_REPLACE flag, but this might lead to
 *          intermediate traffic loss.
 *
 *\param    unit [IN]   Unit number.
 *\param    vpn [IN]   VPN ID
 *\param    mpls_port [IN,OUT]   MPLS port information
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_port_add(
    int unit, 
    opennsl_vpn_t vpn, 
    opennsl_mpls_port_t *mpls_port) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Delete an MPLS port from an L2 VPN.
 *
 *\description Delete an MPLS port from an L2 VPN.
 *
 *\param    unit [IN]   Unit number.
 *\param    vpn [IN]   VPN ID
 *\param    mpls_port_id [IN]   Mpls port ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_port_delete(
    int unit, 
    opennsl_vpn_t vpn, 
    opennsl_gport_t mpls_port_id) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Delete an MPLS port from an L2 VPN.
 *
 *\description Delete an MPLS port from an L2 VPN.
 *
 *\param    unit [IN]   Unit number.
 *\param    vpn [IN]   VPN ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_port_delete_all(
    int unit, 
    opennsl_vpn_t vpn) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get an MPLS port from an L2 VPN.
 *
 *\description Get an MPLS port from an L2 VPN.
 *
 *\param    unit [IN]   Unit number.
 *\param    vpn [IN]   VPN ID
 *\param    mpls_port [IN,OUT]   MPLS port information
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_port_get(
    int unit, 
    opennsl_vpn_t vpn, 
    opennsl_mpls_port_t *mpls_port) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get all MPLS ports from an L2 VPN.
 *
 *\description Get all MPLS ports from an L2 VPN.
 *
 *\param    unit [IN]   Unit number.
 *\param    vpn [IN]   VPN ID
 *\param    port_max [IN]   Maximum number of ports in array
 *\param    port_array [OUT]   Array of MPLS ports
 *\param    port_count [OUT]   Number of ports returned in array
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_port_get_all(
    int unit, 
    opennsl_vpn_t vpn, 
    int port_max, 
    opennsl_mpls_port_t *port_array, 
    int *port_count) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/** MPLS statistics counters. */
typedef enum opennsl_mpls_stat_e {
    opennslMplsInBytes = 0,     
    opennslMplsOutBytes = 1,    
    opennslMplsInPkts = 2,      
    opennslMplsOutPkts = 3      
} opennsl_mpls_stat_t;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Attach statistics entity to the MPLS tunnel derived from the given L3
 *       Egress interface.
 *
 *\description This API will attach statistics entity to the given MPLS tunnel
 *          derived from the given L3 Egress interface
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    intf_id [IN]   Interface ID of a egress L3 object
 *\param    stat_counter_id [IN]   Stat Counter ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_tunnel_stat_attach(
    int unit, 
    opennsl_if_t intf_id, 
    uint32 stat_counter_id) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Detach statistics entity to the MPLS tunnel derived from the given L3
 *       Egress interface.
 *
 *\description This API will detach statistics entity to the MPLS tunnel derived
 *          from the given L3 Egress interface.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    intf_id [IN]   Interface ID of a egress L3 object.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_tunnel_stat_detach(
    int unit, 
    opennsl_if_t intf_id) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get counter value for the specified MPLS statistic type and Tunnel
 *       interface derived from the given L3 interface ID.
 *
 *\description This API will retrieve counter values for the specified MPLS
 *          statistic type and tunnel interface deroved from the L3 Interface
 *          ID.
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
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_tunnel_stat_counter_get(
    int unit, 
    opennsl_if_t intf_id, 
    opennsl_mpls_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    opennsl_stat_value_t *counter_values) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Force an immediate counter update and retrieve the specified counter
 *       statistic for a MPLS tunnel.
 *
 *\description Similar to opennsl_mpls_tunnel_stat_counter_get(), value returned
 *          is software accumulated counter synced with the hardware counter.
 *
 *\param    unit [IN]   Unit number.
 *\param    intf_id [IN]   Interface ID of a egress L3 object.
 *\param    stat [IN]   Type of the counter to retrieve that is, ingress/egress
 *          byte/packet
 *\param    num_entries [IN]   Number of counter Entries
 *\param    counter_indexes [IN]   Pointer to Counter indexes entries
 *\param    counter_values [OUT]   Pointer to counter values
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_tunnel_stat_counter_sync_get(
    int unit, 
    opennsl_if_t intf_id, 
    opennsl_mpls_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    opennsl_stat_value_t *counter_values) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get stat counter ID associated with the MPLS tunnel derived from the
 *       given L3 interface ID.
 *
 *\description This API will provide stat counter IDs associated with the MPLS
 *          tunnel derived from the given L3 Interface id.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    intf_id [IN]   Interface ID of a egress L3 object.
 *\param    stat [IN]   Type of the counter
 *\param    stat_counter_id [OUT]   stat counter ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_tunnel_stat_id_get(
    int unit, 
    opennsl_if_t intf_id, 
    opennsl_mpls_stat_t stat, 
    uint32 *stat_counter_id) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Set the counter value for the specified MPLS statistic type and Tunnel
 *       interface derived derived from the given L3 Interface ID.
 *
 *\description This API will set counter statistic values for the derived MPLS
 *          tunnel.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    intf_id [IN]   Interface ID of a egress L3 object.
 *\param    stat [IN]   Type of the counter to set that is, ingress/egress
 *          byte/packet
 *\param    num_entries [IN]   Number of counter Entries
 *\param    counter_indexes [IN]   Pointer to Counter indexes entries
 *\param    counter_values [IN]   Pointer to counter values
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_tunnel_stat_counter_set(
    int unit, 
    opennsl_if_t intf_id, 
    opennsl_mpls_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    opennsl_stat_value_t *counter_values) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Set the MPLS tunnel initiator parameters for an L3 interface.
 *
 *\description This API is called to set the tunnel initiator parameters for an
 *          L3 interface. The label_array contains information (label, EXP,
 *          TTL) for forming the MPLS label(s) to be pushed onto a packet
 *          entering the tunnel. The destination port information for the
 *          tunnel is specified by calling opennsl_l3_egress_create() API to
 *          create an egress object.
 *          For DNX devices, use the _create APIs. For other devices, use the
 *          _add APIs.
 *          The steps to completely setup an MPLS tunnel initiator are: .
 *
 *\param    unit [IN]   Unit number.
 *\param    intf [IN]   The egress L3 interface
 *\param    num_labels [IN]   Number of labels in the array
 *\param    label_array [IN]   Array of MPLS label and header information
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_tunnel_initiator_set(
    int unit, 
    opennsl_if_t intf, 
    int num_labels, 
    opennsl_mpls_egress_label_t *label_array) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    intf [IN]
 *\param    num_labels [IN]
 *\param    label_array [IN,OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_mpls_tunnel_initiator_create(
    int unit, 
    opennsl_if_t intf, 
    int num_labels, 
    opennsl_mpls_egress_label_t *label_array) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Clear the MPLS tunnel initiator parameters for an L3 interface.
 *
 *\description Clear the MPLS tunnel initiator parameters for an L3 interface.
 *
 *\param    unit [IN]   Unit number.
 *\param    intf [IN]   The egress L3 interface
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_tunnel_initiator_clear(
    int unit, 
    opennsl_if_t intf) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Clear all MPLS tunnel initiator information.
 *
 *\description Clear all MPLS tunnel initiator information.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_tunnel_initiator_clear_all(
    int unit) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get the MPLS tunnel initiator parameters from an L3 interface.
 *
 *\description Get the MPLS tunnel initiator parameters from an L3 interface.
 *
 *\param    unit [IN]   Unit number.
 *\param    intf [IN]   The egress L3 interface
 *\param    label_max [IN]   Number of entries in label_array
 *\param    label_array [OUT]   MPLS header information
 *\param    label_count [OUT]   Actual number of labels returned
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_tunnel_initiator_get(
    int unit, 
    opennsl_if_t intf, 
    int label_max, 
    opennsl_mpls_egress_label_t *label_array, 
    int *label_count) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Add an MPLS label entry.
 *
 *\description The opennsl_mpls_tunnel_switch_t structure is used to specify an
 *          entry in the MPLS label table. The ingress parameters specify the
 *          entry key, action (SWAP, POP, PHP), and QOS settings. The entry
 *          key is the MPLS label and optionally the incoming port. (On
 *          network switch devices, the key may include two MPLS labels). The
 *          action_if_bos and action_if_not_bos parameters can be used on
 *          certain devices to specify different label  actions for the cases
 *          of bottom-of-stack (BOS) labels and non-BOS labels. The  vpn
 *          parameter is used only if the specified action is POP. This is an
 *          L3  VPN used to get the VRF (virtual route table) to use for the
 *          IPv4 or IPv6 DIP  lookup.
 *          The opennsl_mpls_tunnel_switch_create API is replacing the _add
 *          API  for DNX devices. For other devices, use the _add API.
 *          There are 2 modes for SWAP/LSR configuration: Mode-1: The egress
 *          parameter egress_label is only used if the action is SWAP.  This
 *          parameter is used to specify the SWAP label information (label,
 *          EXP, TTL).  The egress_intf parameter is only used for SWAP and
 *          PHP operations. It points to an egress object which was created
 *          using opennsl_l3_egress_create().  The egress object can be an
 *          MPLS tunnel (see opennsl_mpls_tunnel_initiator_create() API for
 *          DNX devices, opennsl_mpls_tunnel_initiator_set for other devices),
 *          for example, if the desired operation is SWAP-and-PUSH. The MPLS
 *          information (Label, EXP, TTL) within the Egress Object must be
 *          initialized to 0.
 *          Mode-2: The egress_label must be initialized to 0, and  egress_if
 *          point to an Egress Object which must contain the SWAP label
 *          information (label, EXP, TTL).
 *          Although Mode-1 is maintained, Mode-2 is recommended for several
 *          reasons. The  next-hop allocation happens during the creation of
 *          Egress object. No new next hops  are allocated during tunnel
 *          switch creation. Multiple tunnel switch entries can point  to the
 *          same egress object.
 *          For Point-to-Multipoint (P2MP) label, set flags to
 *          OPENNSL_MPLS_SWITCH_P2MP and  mc_group to a valid L3 Multicast
 *          group.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN]   Label (switch) information
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_tunnel_switch_add(
    int unit, 
    opennsl_mpls_tunnel_switch_t *info) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Add an MPLS label entry.
 *
 *\description The opennsl_mpls_tunnel_switch_t structure is used to specify an
 *          entry in the MPLS label table. The ingress parameters specify the
 *          entry key, action (SWAP, POP, PHP), and QOS settings. The entry
 *          key is the MPLS label and optionally the incoming port. (On
 *          network switch devices, the key may include two MPLS labels). The
 *          action_if_bos and action_if_not_bos parameters can be used on
 *          certain devices to specify different label  actions for the cases
 *          of bottom-of-stack (BOS) labels and non-BOS labels. The  vpn
 *          parameter is used only if the specified action is POP. This is an
 *          L3  VPN used to get the VRF (virtual route table) to use for the
 *          IPv4 or IPv6 DIP  lookup.
 *          The opennsl_mpls_tunnel_switch_create API is replacing the _add
 *          API  for DNX devices. For other devices, use the _add API.
 *          There are 2 modes for SWAP/LSR configuration: Mode-1: The egress
 *          parameter egress_label is only used if the action is SWAP.  This
 *          parameter is used to specify the SWAP label information (label,
 *          EXP, TTL).  The egress_intf parameter is only used for SWAP and
 *          PHP operations. It points to an egress object which was created
 *          using opennsl_l3_egress_create().  The egress object can be an
 *          MPLS tunnel (see opennsl_mpls_tunnel_initiator_create() API for
 *          DNX devices, opennsl_mpls_tunnel_initiator_set for other devices),
 *          for example, if the desired operation is SWAP-and-PUSH. The MPLS
 *          information (Label, EXP, TTL) within the Egress Object must be
 *          initialized to 0.
 *          Mode-2: The egress_label must be initialized to 0, and  egress_if
 *          point to an Egress Object which must contain the SWAP label
 *          information (label, EXP, TTL).
 *          Although Mode-1 is maintained, Mode-2 is recommended for several
 *          reasons. The  next-hop allocation happens during the creation of
 *          Egress object. No new next hops  are allocated during tunnel
 *          switch creation. Multiple tunnel switch entries can point  to the
 *          same egress object.
 *          For Point-to-Multipoint (P2MP) label, set flags to
 *          OPENNSL_MPLS_SWITCH_P2MP and  mc_group to a valid L3 Multicast
 *          group.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN,OUT]   Label (switch) information
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_tunnel_switch_create(
    int unit, 
    opennsl_mpls_tunnel_switch_t *info) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Delete an MPLS label entry.
 *
 *\description Delete an MPLS label entry.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN]   Label (switch) information
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_tunnel_switch_delete(
    int unit, 
    opennsl_mpls_tunnel_switch_t *info) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Delete all MPLS label entries.
 *
 *\description Delete all MPLS label entries.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_tunnel_switch_delete_all(
    int unit) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get an MPLS label entry.
 *
 *\description Get an MPLS label entry.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN,OUT]   Label (switch) information
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_tunnel_switch_get(
    int unit, 
    opennsl_mpls_tunnel_switch_t *info) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
typedef int (*opennsl_mpls_tunnel_switch_traverse_cb)(
    int unit, 
    opennsl_mpls_tunnel_switch_t *info, 
    void *user_data);
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Traverse all valid MPLS label entries and call the supplied callback
 *       routine.
 *
 *\description Traverse all valid MPLS label entries and call the supplied
 *          callback routine. The callback function is defined as following:.
 *
 *\param    unit [IN]   Unit number.
 *\param    cb [IN]   User callback function, called once per MPLS entry
 *\param    user_data [IN]   Cookie
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_tunnel_switch_traverse(
    int unit, 
    opennsl_mpls_tunnel_switch_traverse_cb cb, 
    void *user_data) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
#endif
#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Add an MPLS Entropy Label Identifier.
 *
 *\description The opennsl_mpls_entropy_identifier_t structure is used to specify
 *          an MPLS entropy label identifier.
 *          Using this API, user can configure an entropy label identifier
 *          which will be used to detect the presence of an entropy label in
 *          the label stack. Currently, the only action supported is POP. User
 *          would have to ensure not to use any of the forwarding labels as
 *          entropy label because then it would qualify as MPLS forwarding
 *          label and not entropy label. Returns OPENNSL_E_PARAM if the label
 *          or mask passed by user is invalid.
 *
 *\param    unit [IN]   Unit number.
 *\param    options [IN]   MPLS_ENTROPY_LABEL_*
 *\param    info [IN]
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_entropy_identifier_add(
    int unit, 
    uint32 options, 
    opennsl_mpls_entropy_identifier_t *info) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get information about an MPLS Entropy Label Identifier.
 *
 *\description On passing entropy label+mask+pri to this API, returns information
 *          of the other fields.  Returns OPENNSL_E_EMPTY if no entropy label
 *          is configured. If no valid label+mask is passed by the user,
 *          information about the only configured label is returned.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN,OUT]
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_entropy_identifier_get(
    int unit, 
    opennsl_mpls_entropy_identifier_t *info) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Delete an MPLS Entropy Label Identifier.
 *
 *\description Deletes MLPS entropy configuration corresponding to the passed
 *          label+mask+pri key. Returns OPENNSL_E_EMPTY if no entropy label is
 *          configured. If label+mask passed by user is invalid, returns
 *          OPENNSL_E_PARAM.
 *
 *\param    unit [IN]   Unit number.
 *\param    info [IN]
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_entropy_identifier_delete(
    int unit, 
    opennsl_mpls_entropy_identifier_t *info) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Delete all MPLS Entropy Label Identifiers.
 *
 *\description Deletes all MPLS Entropy label identifier entries.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_entropy_identifier_delete_all(
    int unit) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
typedef int (*opennsl_mpls_entropy_identifier_traverse_cb)(
    int unit, 
    opennsl_mpls_entropy_identifier_t *info, 
    void *user_data);
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Traverse all valid MPLS entropy label identifier entries and call the
 *       supplied callback routine.
 *
 *\description Returns OPENNSL_E_EMPTY if no entropy label is configured.
 *          Traverse all valid MPLS entropy label identifier entries and call
 *          the supplied callback routine. The callback function is defined as
 *          following:.
 *
 *\param    unit [IN]   Unit number.
 *\param    cb [IN]   User callback function, called once per MPLS entry
 *\param    user_data [IN]   Cookie
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_entropy_identifier_traverse(
    int unit, 
    opennsl_mpls_entropy_identifier_traverse_cb cb, 
    void *user_data) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
#endif
#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Create an MPLS EXP map instance.
 *
 *\description Create an EXP map instance. An EXP map can be an ingress or egress
 *          EXP map as specified by the flags parameter (see below). For
 *          incoming MPLS packets, and ingress EXP map is used to translate
 *          MPLS EXP value to  internal priority and color. For outgoing MPLS
 *          packets, an egress EXP map is used to translate the internal
 *          priority and color to an EXP  value. The egress_L2 EXP map is used
 *          to set the 802.1p priority and CFI  values for outgoing MPLS
 *          packets.
 *
 *\param    unit [IN]   Unit number.
 *\param    flags [IN]   OPENNSL_MPLS_EXP_MAP_*
 *\param    exp_map_id [IN,OUT]   Pointer to integer. If the call is successful,
 *          the EXP map ID allocated by the driver is filled into this integer
 *          location. If OPENNSL_MPLS_EXP_MAP_WITH_ID flag is set, a valid EXP map
 *          ID should be passed in.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_exp_map_create(
    int unit, 
    uint32 flags, 
    int *exp_map_id) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Destroy an MPLS EXP map instance.
 *
 *\description Destroy an existing EXP map instance.
 *
 *\param    unit [IN]   Unit number.
 *\param    exp_map_id [IN]   EXP map ID to be destroyed.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_exp_map_destroy(
    int unit, 
    int exp_map_id) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Set the EXP mapping parameters for the specified EXP map.
 *
 *\description Set the EXP mapping parameters for the specified EXP map. For
 *          ingress EXP maps, set the EXP-to-{internal priority, color}
 *          mapping. For egress EXP maps, set the {internal priority,
 *          color}-to-EXP mapping and the {internal priority,
 *          color}-to-{802.1p priority, CFI} mapping. For egress_L2 EXP maps,
 *          set the EXP-to-{802.1p priority, CFI} mapping.
 *
 *\param    unit [IN]   Unit number.
 *\param    exp_map_id [IN]   EXP map ID
 *\param    exp_map [IN]   EXP map ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_exp_map_set(
    int unit, 
    int exp_map_id, 
    opennsl_mpls_exp_map_t *exp_map) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get the EXP mapping parameters for the specified EXP map.
 *
 *\description Get the EXP mapping parameters for the specified EXP map. For
 *          ingress EXP maps, the specified EXP value is used to get  the
 *          EXP-to-{internal priority, color} mapping. For egress EXP maps, 
 *          the specified internal priority and color values are used to get
 *          the  {internal priority, color}-to-EXP mapping and the {internal
 *          priority,  color}-to-{802.1p priority, CFI} mapping. For egress_L2
 *          EXP maps, the  specified EXP value is used to get the
 *          EXP-to-{802.1p priority, CFI}  mapping.
 *
 *\param    unit [IN]   Unit number.
 *\param    exp_map_id [IN]   EXP map ID
 *\param    exp_map [IN,OUT]   EXP map ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_exp_map_get(
    int unit, 
    int exp_map_id, 
    opennsl_mpls_exp_map_t *exp_map) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Enable/disable statistics collection for MPLS label or MPLS gport.
 *
 *\description For switch family switches, this will initialize statistic
 *          collection for the given (label, port) (enable=TRUE) or release
 *          the HW resources used for the tracking the statistics
 *          (enable=FALSE). If the port  parameter is an MPLS gport, then this
 *          is equivalent to the.
 *
 *\param    unit [IN]   Unit number.
 *\param    label [IN]   MPLS label
 *\param    port [IN]   gport
 *\param    enable [IN]   Non-zero to enable counter collection, zero to disable.
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_mpls_label_stat_enable_set(
    int unit, 
    opennsl_mpls_label_t label, 
    opennsl_gport_t port, 
    int enable) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get MPLS Stats.
 *
 *\description This API is called to obtain the L2 MPLS PW Stats. The possible
 *          values for the  stat parameter are: opennslMplsInBytes,
 *          opennslMplsInPkts, opennslMplsOutBytes, opennslMplsOutPkts. When
 *          =opennsl_mpls_label_stat_enable_set is available, then ingress
 *          statistics (opennslMplsInBytes, opennslMplsInPkts ) may be
 *          retrieved for an enabled (label, port).
 *
 *\param    unit [IN]   Unit number.
 *\param    label [IN]   MPLS Label
 *\param    port [IN]   Gport
 *\param    stat [IN]   Specify the Stat Type
 *\param    val [OUT]   Pointer to stats value
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_label_stat_get(
    int unit, 
    opennsl_mpls_label_t label, 
    opennsl_gport_t port, 
    opennsl_mpls_stat_t stat, 
    uint64 *val) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Force an immediate counter update and retrieve MPLS Stats.
 *
 *\description Similar to opennsl_mpls_label_stat_get(), value returned is
 *          software  accumulated counter synced with the hardware counter.
 *
 *\param    unit [IN]   Unit number.
 *\param    label [IN]   MPLS Label
 *\param    port [IN]   Gport
 *\param    stat [IN]   Specify the Stat Type
 *\param    val [OUT]   Pointer to stats value
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_label_stat_sync_get(
    int unit, 
    opennsl_mpls_label_t label, 
    opennsl_gport_t port, 
    opennsl_mpls_stat_t stat, 
    uint64 *val) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get MPLS Stats.
 *
 *\description This API is called to obtain the L2 MPLS PW Stats. The possible
 *          values for the  stat parameter are: opennslMplsInBytes,
 *          opennslMplsInPkts, opennslMplsOutBytes, opennslMplsOutPkts. When
 *          =opennsl_mpls_label_stat_enable_set is available, then ingress
 *          statistics (opennslMplsInBytes, opennslMplsInPkts ) may be
 *          retrieved for an enabled (label, port).
 *
 *\param    unit [IN]   Unit number.
 *\param    label [IN]   MPLS Label
 *\param    port [IN]   Gport
 *\param    stat [IN]   Specify the Stat Type
 *\param    val [OUT]   Pointer to stats value
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_label_stat_get32(
    int unit, 
    opennsl_mpls_label_t label, 
    opennsl_gport_t port, 
    opennsl_mpls_stat_t stat, 
    uint32 *val) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Force an immediate counter update and retrieve MPLS Stats.
 *
 *\description Similar to opennsl_mpls_label_stat_get(), value returned is
 *          software  accumulated counter synced with the hardware counter.
 *
 *\param    unit [IN]   Unit number.
 *\param    label [IN]   MPLS Label
 *\param    port [IN]   Gport
 *\param    stat [IN]   Specify the Stat Type
 *\param    val [OUT]   Pointer to stats value
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_label_stat_sync_get32(
    int unit, 
    opennsl_mpls_label_t label, 
    opennsl_gport_t port, 
    opennsl_mpls_stat_t stat, 
    uint32 *val) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Clear MPLS Stats.
 *
 *\description This API is called to clear the L2 MPLS PW Stats. The possible
 *          values for the  stat parameter are: opennslMplsInBytes,
 *          opennslMplsInPkts, opennslMplsOutBytes, opennslMplsOutPkts. When
 *          =opennsl_mpls_label_stat_enable_set is available, then ingress
 *          statistics (opennslMplsInBytes, opennslMplsInPkts ) may be cleared
 *          for an enabled (label, port).
 *
 *\param    unit [IN]   Unit number.
 *\param    label [IN]   MPLS Label
 *\param    port [IN]   Gport
 *\param    stat [IN]   Specify the Stat Type
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_label_stat_clear(
    int unit, 
    opennsl_mpls_label_t label, 
    opennsl_gport_t port, 
    opennsl_mpls_stat_t stat) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Enable or disable collection of MPLS port statistics.
 *
 *\description Enable or disable collection of MPLS port statistics.
 *
 *\param    unit [IN]   Unit number.
 *\param    mpls_port [IN]   MEF port
 *\param    enable [IN]   Non-zero to enable counter collection, zero to disable.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_port_stat_enable_set(
    int unit, 
    opennsl_gport_t mpls_port, 
    int enable) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/** Types of statistics that are maintained per MPLS gport. */
typedef enum opennsl_mpls_port_stat_e {
    opennslMplsPortStatUnicastPackets = 0, 
    opennslMplsPortStatUnicastBytes = 1, 
    opennslMplsPortStatNonUnicastPackets = 2, 
    opennslMplsPortStatNonUnicastBytes = 3, 
    opennslMplsPortStatDropPackets = 4, 
    opennslMplsPortStatDropBytes = 5,   
    opennslMplsPortStatFloodPackets = 6, 
    opennslMplsPortStatFloodBytes = 7,  
    opennslMplsPortStatFloodDropPackets = 8, 
    opennslMplsPortStatFloodDropBytes = 9, 
    opennslMplsPortStatGreenPackets = 10, 
    opennslMplsPortStatGreenBytes = 11, 
    opennslMplsPortStatYellowPackets = 12, 
    opennslMplsPortStatYellowBytes = 13, 
    opennslMplsPortStatRedPackets = 14, 
    opennslMplsPortStatRedBytes = 15    
} opennsl_mpls_port_stat_t;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Set the specified statistic to the indicated value.
 *
 *\description Set the specified statistic to the indicated value.
 *
 *\param    unit [IN]   Unit number.
 *\param    mpls_port [IN]   MEF port.
 *\param    cos [IN]   COS.
 *\param    stat [IN]   Type of statistics to set.
 *\param    val [IN]   The new value to set.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_port_stat_set(
    int unit, 
    opennsl_gport_t mpls_port, 
    opennsl_cos_t cos, 
    opennsl_mpls_port_stat_t stat, 
    uint64 val) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    mpls_port [IN]
 *\param    cos [IN]
 *\param    stat [IN]
 *\param    val [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_mpls_port_stat_set32(
    int unit, 
    opennsl_gport_t mpls_port, 
    opennsl_cos_t cos, 
    opennsl_mpls_port_stat_t stat, 
    uint32 val) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get the specified statistics per MPLS/MEF port.
 *
 *\description Returns the value of the specified counter for the given MEF port.
 *
 *\param    unit [IN]   Unit number.
 *\param    mpls_port [IN]   MEF port.
 *\param    cos [IN]   Class of service.
 *\param    stat [IN]   Type of statistics.
 *\param    val [OUT]   Pointer to the retrieved value.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_port_stat_get(
    int unit, 
    opennsl_gport_t mpls_port, 
    opennsl_cos_t cos, 
    opennsl_mpls_port_stat_t stat, 
    uint64 *val) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get the specified statistics per MPLS/MEF port.
 *
 *\description Returns the value of the specified counter for the given MEF port.
 *
 *\param    unit [IN]   Unit number.
 *\param    mpls_port [IN]   MEF port.
 *\param    cos [IN]   Class of service.
 *\param    stat [IN]   Type of statistics.
 *\param    val [OUT]   Pointer to the retrieved value.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mpls_port_stat_get32(
    int unit, 
    opennsl_gport_t mpls_port, 
    opennsl_cos_t cos, 
    opennsl_mpls_port_stat_t stat, 
    uint32 *val) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get stat counter ID associated with given MPLS gport and VPN.
 *
 *\description This API will provide stat counter IDs associated with given MPLS
 *          gport  and VPN.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    vpn [IN]   VPN ID
 *\param    port [IN]   MPLS Gport
 *\param    stat [IN]   Type of the counter
 *\param    stat_counter_id [OUT]   Stat Counter ID
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_mpls_port_stat_id_get(
    int unit, 
    opennsl_vpn_t vpn, 
    opennsl_gport_t port, 
    opennsl_mpls_stat_t stat, 
    uint32 *stat_counter_id) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get stat counter ID associated with given MPLS label and gport.
 *
 *\description This API will provide stat counter IDs associated with MPLS label
 *          and gport.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    label [IN]   MPLS Label
 *\param    port [IN]   MPLS Gport
 *\param    stat [IN]   Type of the counter
 *\param    stat_counter_id [OUT]   Stat Counter ID
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_mpls_label_stat_id_get(
    int unit, 
    opennsl_mpls_label_t label, 
    opennsl_gport_t port, 
    opennsl_mpls_stat_t stat, 
    uint32 *stat_counter_id) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Attach counters entries to the given MPLS gport and vpn.
 *
 *\description This API will attach counters entries to the given MPLS gport and
 *          VPN.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    vpn [IN]   VPN ID
 *\param    port [IN]   MPLS Gport
 *\param    stat_counter_id [IN]   Stat Counter ID
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_mpls_port_stat_attach(
    int unit, 
    opennsl_vpn_t vpn, 
    opennsl_gport_t port, 
    uint32 stat_counter_id) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Detach counters entries to the given MPLS port and vpn.
 *
 *\description This API will detach counters entries to the given MPLS port and
 *          VPN.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    vpn [IN]   VPN ID
 *\param    port [IN]   MPLS Gport
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_mpls_port_stat_detach(
    int unit, 
    opennsl_vpn_t vpn, 
    opennsl_gport_t port) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get counter statistic values for specific vpn and gport.
 *
 *\description This API will retrieve set of counter statistic values for
 *          specific vpn and  gport.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    vpn [IN]   VPN ID
 *\param    port [IN]   MPLS Gport
 *\param    stat [IN]   Type of the counter to retrieve that is, ingress/egress
 *          byte/packet
 *\param    num_entries [IN]   Number of counter Entries
 *\param    counter_indexes [IN]   Pointer to Counter indexes entries
 *\param    counter_values [OUT]   Pointer to counter values
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_mpls_port_stat_counter_get(
    int unit, 
    opennsl_vpn_t vpn, 
    opennsl_gport_t port, 
    opennsl_mpls_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    opennsl_stat_value_t *counter_values) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Force an immediate counter update and retrieve get counter statistic
 *       values for specific vpn and gport.
 *
 *\description Similar to opennsl_mpls_port_stat_counter_sync_get(), value
 *          returned is software  accumulated counter synced with the hardware
 *          counter.
 *
 *\param    unit [IN]   Unit number.
 *\param    vpn [IN]   VPN ID
 *\param    port [IN]   MPLS Gport
 *\param    stat [IN]   Type of the counter to retrieve that is, ingress/egress
 *          byte/packet
 *\param    num_entries [IN]   Number of counter Entries
 *\param    counter_indexes [IN]   Pointer to Counter indexes entries
 *\param    counter_values [OUT]   Pointer to counter values
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_mpls_port_stat_counter_sync_get(
    int unit, 
    opennsl_vpn_t vpn, 
    opennsl_gport_t port, 
    opennsl_mpls_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    opennsl_stat_value_t *counter_values) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Set counter statistic values for specific vpn and gport.
 *
 *\description This API will counter statistic values for specific vpn and gport.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    vpn [IN]   VPN ID
 *\param    port [IN]   MPLS Gport
 *\param    stat [IN]   Type of the counter to set that is, ingress/egress
 *          byte/packet
 *\param    num_entries [IN]   Number of counter Entries
 *\param    counter_indexes [IN]   Pointer to Counter indexes entries
 *\param    counter_values [IN]   Pointer to counter values
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_mpls_port_stat_counter_set(
    int unit, 
    opennsl_vpn_t vpn, 
    opennsl_gport_t port, 
    opennsl_mpls_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    opennsl_stat_value_t *counter_values) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Attach counters entries to the given MPLS label and gport.
 *
 *\description This API will attach counters entries to the given MPLS label and
 *          gport.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    label [IN]   MPLS Label
 *\param    port [IN]   MPLS Gport
 *\param    stat_counter_id [IN]   Stat Counter ID
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_mpls_label_stat_attach(
    int unit, 
    opennsl_mpls_label_t label, 
    opennsl_gport_t port, 
    uint32 stat_counter_id) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Detach counters entries to the given MPLS label and gport.
 *
 *\description This API will detach counters entries to the given MPLS label and
 *          gport.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    label [IN]   MPLS Label
 *\param    port [IN]   MPLS Gport
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_mpls_label_stat_detach(
    int unit, 
    opennsl_mpls_label_t label, 
    opennsl_gport_t port) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Force an immediate counter update and retrieve counter statistic values
 *       for specific MPLS label and gport.
 *
 *\description Similar to opennsl_mpls_label_stat_counter_get(), value returned
 *          is software accumulated counter synced with the hardware counter.
 *
 *\param    unit [IN]   Unit number.
 *\param    label [IN]   MPLS Label
 *\param    port [IN]   MPLS Gport
 *\param    stat [IN]   Type of the counter to retrieve that is, ingress/egress
 *          byte/packet
 *\param    num_entries [IN]   Number of counter Entries
 *\param    counter_indexes [IN]   Pointer to Counter indexes entries
 *\param    counter_values [OUT]   Pointer to counter values
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_mpls_label_stat_counter_sync_get(
    int unit, 
    opennsl_mpls_label_t label, 
    opennsl_gport_t port, 
    opennsl_mpls_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    opennsl_stat_value_t *counter_values) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get counter statistic values for specific MPLS label and gport.
 *
 *\description This API will retrieve set of counter statistic values for
 *          specific MPLS  label and gport.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    label [IN]   MPLS Label
 *\param    port [IN]   MPLS Gport
 *\param    stat [IN]   Type of the counter to retrieve that is, ingress/egress
 *          byte/packet
 *\param    num_entries [IN]   Number of counter Entries
 *\param    counter_indexes [IN]   Pointer to Counter indexes entries
 *\param    counter_values [OUT]   Pointer to counter values
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_mpls_label_stat_counter_get(
    int unit, 
    opennsl_mpls_label_t label, 
    opennsl_gport_t port, 
    opennsl_mpls_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    opennsl_stat_value_t *counter_values) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Set counter statistic values for specific MPLS label and gport.
 *
 *\description This API will set counter statistic values for specific MPLS label
 *          and gport.
 *          (Ref: =FLEXIBLE_COUNTER_s).
 *
 *\param    unit [IN]   Unit number.
 *\param    label [IN]   MPLS Label
 *\param    port [IN]   MPLS Gport
 *\param    stat [IN]   Type of the counter to set that is, ingress/egress
 *          byte/packet
 *\param    num_entries [IN]   Number of counter Entries
 *\param    counter_indexes [IN]   Pointer to Counter indexes entries
 *\param    counter_values [IN]   Pointer to counter values
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_mpls_label_stat_counter_set(
    int unit, 
    opennsl_mpls_label_t label, 
    opennsl_gport_t port, 
    opennsl_mpls_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    opennsl_stat_value_t *counter_values) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
#endif
#if defined(INCLUDE_L3)
/** MPLS range action */
typedef struct opennsl_mpls_range_action_s {
    uint32 flags;                       /**< OPENNSL_MPLS_RANGE_ACTION_xxx */
    opennsl_mpls_label_t compressed_label; /**< lowest label in the range */
} opennsl_mpls_range_action_t;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Set range of labels per in lif.
 *
 *\description This API allows allocation of one in-lif per given label range.
 *
 *\param    unit [IN]   Unit number.
 *\param    label_low [IN]   lower label
 *\param    label_high [IN]   higher label
 *\param    action [IN]   range action
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_mpls_range_action_add(
    int unit, 
    opennsl_mpls_label_t label_low, 
    opennsl_mpls_label_t label_high, 
    opennsl_mpls_range_action_t *action) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Remove range of labels per in lif.
 *
 *\description This API allows removal of a given label range.
 *
 *\param    unit [IN]   Unit number.
 *\param    label_low [IN]   lower label
 *\param    label_high [IN]   higher label
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_mpls_range_action_remove(
    int unit, 
    opennsl_mpls_label_t label_low, 
    opennsl_mpls_label_t label_high) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Get range of labels per in lif.
 *
 *\description This API gets the action associated to a given label range.
 *
 *\param    unit [IN]   Unit number.
 *\param    label_low [IN]   lower label
 *\param    label_high [IN]   higher label
 *\param    action [IN,OUT]   range action
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_mpls_range_action_get(
    int unit, 
    opennsl_mpls_label_t label_low, 
    opennsl_mpls_label_t label_high, 
    opennsl_mpls_range_action_t *action) LIB_DLL_EXPORTED ;
#endif

#if defined(INCLUDE_L3)
/***************************************************************************//** 
 *\brief Initialize the MPLS range action structure.
 *
 *\description Initialize the MPLS range action structure.
 *
 *\param    label [IN,OUT]
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_mpls_range_action_t_init(
    opennsl_mpls_range_action_t *label) LIB_DLL_EXPORTED ;
#endif

#endif /* __OPENNSL_MPLSX_H__ */
/*@}*/
