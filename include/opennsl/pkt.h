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
 * \file			pkt.h
 ******************************************************************************/

#ifndef __OPENNSL_PKT_H__
#define __OPENNSL_PKT_H__

#include <shared/rx.h>
#include <opennsl/types.h>
#include <opennsl/vlan.h>

/** 
 * The packet structure. The packet layout is as follows:
 * 
 *   DMAC + SMAC     12 bytes
 *   VLAN tag         4 bytes (may be filled in by SW on network switch)
 *   payload          N bytes
 *   CRC              4 bytes
 *   pad              M bytes
 *   SL tag           4 bytes (may be unused)
 *   HiGig Header    12 bytes (may be unused)
 * 
 * The rule is: alloc_len = 12 + 4 + N + 4 + M + 4 + 12 (all of above).
 * payload_len (below) is N.
 * 
 * Note that the payload may grow until M == 0; the CRC moves. The SL and
 * HiGig headers will not move.
 * 
 * The "IEEE packet" is everything from the DMAC through the CRC
 * (inclusive), not including SL tag or HiGig header.
 * 
 * Scatter/gather is used to put the data into the right positions on
 * transmit and receive. The SL/HiGig headers are parsed on RX into data
 * members in the packet structure. On TX, opennsl_tx will send the
 * packet according to the unit type. It will not check or affect any
 * fields except maybe the CRC. Other routines will be provided to ensure
 * the HiGig and SL tags are properly set up from the data in the packet
 * structure.
 */
typedef struct opennsl_pkt_s opennsl_pkt_t;

typedef void (*opennsl_pkt_cb_f)(
    int reserved1, 
    opennsl_pkt_t *reserved2, 
    void *reserved3);

/** OPENNSL packet gather block type. */
typedef struct opennsl_pkt_blk_s {
    uint8 *data;    
    int len;        
} opennsl_pkt_blk_t;

/** Set of 'reasons' (see opennslRxReason*) why a packet came to the CPU. */
typedef _shr_rx_reasons_t opennsl_rx_reasons_t;

/** Stacking header packet forwarding options. */
typedef enum opennsl_pkt_stk_forward_e {
    pktReservedEnum1, 
    pktReservedEnum2, 
    pktReservedEnum3, 
    pktReservedEnum4, 
    pktReservedEnum5, 
    pktReservedEnum6, 
    pktReservedEnum7, 
    pktReservedEnum8, 
    pktReservedEnum9, 
    pktReservedEnum10, 
    pktReservedEnum11, 
    pktReservedEnum12, 
    pktReservedEnum13, 
    pktReservedEnum14, 
    pktReservedEnum15 
} opennsl_pkt_stk_forward_t;

/** Decap Tunnel Types */
typedef enum opennsl_rx_decap_tunnel_e {
    opennslpktReservedEnum16, 
    opennslpktReservedEnum17, 
    opennslpktReservedEnum18, 
    opennslpktReservedEnum19, 
    opennslpktReservedEnum20, 
    opennslpktReservedEnum21, 
    opennslpktReservedEnum22, 
    opennslpktReservedEnum23, 
    opennslpktReservedEnum24, 
    opennslpktReservedEnum25, 
    opennslpktReservedEnum26, 
    opennslpktReservedEnum27, 
    opennslpktReservedEnum28, 
    opennslpktReservedEnum29, 
    opennslpktReservedEnum30, 
    opennslpktReservedEnum31, 
    opennslpktReservedEnum32, 
    opennslpktReservedEnum33, 
    opennslpktReservedEnum34 
} opennsl_rx_decap_tunnel_t;

/** OAM DM timestamp options. */
typedef enum opennsl_pkt_timestamp_mode_e {
    pktReservedEnum35, 
    pktReservedEnum36, 
    pktReservedEnum37, 
    pktReservedEnum38 
} opennsl_pkt_timestamp_mode_t;

/** OAM LM counter options. */
typedef enum opennsl_pkt_oam_lm_counter_mode_e {
    pktReservedEnum39, 
    pktReservedEnum40, 
    pktReservedEnum41, 
    pktReservedEnum42 
} opennsl_pkt_oam_lm_counter_mode_t;

/** OAM Pkt Type */
typedef enum opennsl_pkt_rx_oam_type_e {
    pktReservedEnum43, 
    pktReservedEnum44, 
    pktReservedEnum45, 
    pktReservedEnum46, 
    pktReservedEnum47, 
    pktReservedEnum48, 
    pktReservedEnum49, 
    pktReservedEnum50, 
    pktReservedEnum51, 
    pktReservedEnum52, 
    pktReservedEnum53, 
    pktReservedEnum54, 
    pktReservedEnum55, 
    pktReservedEnum56, 
    pktReservedEnum57, 
    pktReservedEnum58, 
    pktReservedEnum59, 
    pktReservedEnum60 
} opennsl_pkt_rx_oam_type_t;

/** OAM counter object ID */
typedef enum opennsl_pkt_oam_counter_object_e {
    pktReservedEnum61, 
    pktReservedEnum62, 
    pktReservedEnum63 
} opennsl_pkt_oam_counter_object_t;

/** OAM counter */
typedef struct opennsl_pkt_oam_counter_s {
    opennsl_pkt_oam_counter_object_t reserved1; 
    uint32 reserved2; 
    uint32 reserved3; 
    opennsl_pkt_oam_lm_counter_mode_t reserved4; 
    uint32 reserved5; 
    uint32 reserved6; 
    uint32 reserved7; 
} opennsl_pkt_oam_counter_t;

#define OPENNSL_PKT_OAM_COUNTER_MAX 3          
#define OPENNSL_PKT_NOF_DNX_HEADERS 9          
/** Pkt DNX types. */
typedef enum opennsl_pkt_dnx_type_e {
    opennslpktReservedEnum64 = 0, 
    opennslpktReservedEnum65 = 1, 
    opennslpktReservedEnum66 = 2, 
    opennslpktReservedEnum67 = 3, 
    opennslpktReservedEnum68 = 4, 
    opennslpktReservedEnum69 = 5, 
    opennslpktReservedEnum70 = 6, 
    opennslpktReservedEnum71 = 7 
} opennsl_pkt_dnx_type_t;

/** PTCH1 */
typedef struct opennsl_pkt_dnx_ptch1_s {
    opennsl_gport_t reserved1; 
    uint32 reserved2; 
    uint8 reserved3; 
} opennsl_pkt_dnx_ptch1_t;

/** PTCH2 */
typedef struct opennsl_pkt_dnx_ptch2_s {
    opennsl_gport_t reserved1; 
    uint32 reserved2; 
    uint8 reserved3; 
} opennsl_pkt_dnx_ptch2_t;

/** itmh dest type. */
typedef enum opennsl_pkt_dnx_itmh_dest_type_e {
    opennslpktReservedEnum72 = 0, 
    opennslpktReservedEnum73 = 1, 
    opennslpktReservedEnum74 = 2, 
    opennslpktReservedEnum75 = 3, 
    opennslpktReservedEnum76 = 4 
} opennsl_pkt_dnx_itmh_dest_type_t;

/** Itmh destination. */
typedef struct opennsl_pkt_dnx_itmh_dest_s {
    opennsl_pkt_dnx_itmh_dest_type_t reserved1; 
    opennsl_pkt_dnx_itmh_dest_type_t reserved2; 
    opennsl_gport_t reserved3; 
    opennsl_multicast_t reserved4; 
    opennsl_gport_t reserved5; 
} opennsl_pkt_dnx_itmh_dest_t;

/** Itmh */
typedef struct opennsl_pkt_dnx_itmh_s {
    uint8 reserved1; 
    uint32 reserved2; 
    uint32 reserved3; 
    opennsl_color_t reserved4; 
    opennsl_pkt_dnx_itmh_dest_t reserved5; 
} opennsl_pkt_dnx_itmh_t;

/** ftmh action type. */
typedef enum opennsl_pkt_dnx_ftmh_action_type_e {
    opennslpktReservedEnum77 = 0, 
    opennslpktReservedEnum78 = 1, 
    opennslpktReservedEnum79 = 2, 
    opennslpktReservedEnum80 = 3 
} opennsl_pkt_dnx_ftmh_action_type_t;

/** ftmh lb extension. */
typedef struct opennsl_pkt_dnx_ftmh_lb_extension_s {
    uint8 reserved1; 
    uint32 reserved2; 
} opennsl_pkt_dnx_ftmh_lb_extension_t;

/** ftmh dest extension. */
typedef struct opennsl_pkt_dnx_ftmh_dest_extension_s {
    uint8 reserved1; 
    opennsl_gport_t reserved2; 
} opennsl_pkt_dnx_ftmh_dest_extension_t;

/** ftmh stack extension. */
typedef struct opennsl_pkt_dnx_ftmh_stack_extension_s {
    uint8 reserved1; 
    uint32 reserved2; 
} opennsl_pkt_dnx_ftmh_stack_extension_t;

/** ftmh */
typedef struct opennsl_pkt_dnx_ftmh_s {
    uint32 reserved1; 
    uint32 reserved2; 
    opennsl_gport_t reserved3; 
    opennsl_gport_t reserved4; 
    opennsl_color_t reserved5; 
    opennsl_pkt_dnx_ftmh_action_type_t reserved6; 
    uint8 reserved7; 
    uint8 reserved8; 
    opennsl_multicast_t reserved9; 
    opennsl_gport_t reserved10; 
    uint32 reserved11; 
    opennsl_pkt_dnx_ftmh_lb_extension_t reserved12; 
    opennsl_pkt_dnx_ftmh_dest_extension_t reserved13; 
    opennsl_pkt_dnx_ftmh_stack_extension_t reserved14; 
} opennsl_pkt_dnx_ftmh_t;

/** pph eei extension */
typedef struct opennsl_pkt_dnx_pph_eei_extension_s {
    uint8 reserved1; 
    uint8 reserved2; 
    uint32 reserved3; 
    uint32 reserved4; 
    uint32 reserved5; 
} opennsl_pkt_dnx_pph_eei_extension_t;

/** pph learn extension */
typedef struct opennsl_pkt_dnx_pph_learn_extension_s {
    uint8 reserved1; 
    opennsl_port_t reserved2; 
    uint8 reserved3; 
    opennsl_pkt_dnx_pph_eei_extension_t reserved4; 
    uint8 reserved5; 
    int reserved6; 
    uint64 reserved7; 
} opennsl_pkt_dnx_pph_learn_extension_t;

/** pph fhei type */
typedef enum opennsl_pkt_dnx_pph_fhei_type_e {
    opennslpktReservedEnum81 = 0, 
    opennslpktReservedEnum82 = 1, 
    opennslpktReservedEnum83 = 2, 
    opennslpktReservedEnum84 = 3, 
    opennslpktReservedEnum85 = 4 
} opennsl_pkt_dnx_pph_fhei_type_t;

/** pph fhei bridge extension */
typedef struct opennsl_pkt_dnx_pph_fhei_bridge_extension_s {
    uint8 reserved1; 
    uint8 reserved2; 
    uint8 reserved3; 
    opennsl_vlan_t reserved4; 
    uint8 reserved5; 
    uint8 reserved6; 
    opennsl_vlan_t reserved7; 
} opennsl_pkt_dnx_pph_fhei_bridge_extension_t;

/** pph fhei trap extension */
typedef struct opennsl_pkt_dnx_pph_fhei_trap_extension_s {
    uint32 reserved1; 
    opennsl_gport_t reserved2; 
} opennsl_pkt_dnx_pph_fhei_trap_extension_t;

/** pph fhei ip extension */
typedef struct opennsl_pkt_dnx_pph_fhei_ip_extension_s {
    uint32 reserved1; 
    uint8 reserved2; 
    uint8 reserved3; 
} opennsl_pkt_dnx_pph_fhei_ip_extension_t;

/** pph fhei mpls extension */
typedef struct opennsl_pkt_dnx_pph_fhei_mpls_extension_s {
    uint32 reserved1; 
    uint32 reserved2; 
    opennsl_forwarding_type_t reserved3; 
    uint8 reserved4; 
    uint32 reserved5; 
    uint32 reserved6; 
    uint8 reserved7; 
    uint8 reserved8; 
} opennsl_pkt_dnx_pph_fhei_mpls_extension_t;

/** pph fhei trill extension */
typedef struct opennsl_pkt_dnx_pph_fhei_trill_extension_s {
    uint8 reserved1; 
} opennsl_pkt_dnx_pph_fhei_trill_extension_t;

/** pph fhei extension */
typedef struct opennsl_pkt_dnx_pph_fhei_extension_s {
    opennsl_pkt_dnx_pph_fhei_type_t reserved1; 
    opennsl_pkt_dnx_pph_fhei_bridge_extension_t reserved2; 
    opennsl_pkt_dnx_pph_fhei_trap_extension_t reserved3; 
    opennsl_pkt_dnx_pph_fhei_ip_extension_t reserved4; 
    opennsl_pkt_dnx_pph_fhei_mpls_extension_t reserved5; 
    opennsl_pkt_dnx_pph_fhei_trill_extension_t reserved6; 
} opennsl_pkt_dnx_pph_fhei_extension_t;

/** pph fhei extension */
typedef struct opennsl_pkt_dnx_pph_s {
    uint32 reserved1; 
    opennsl_forwarding_type_t reserved2; 
    uint32 reserved3; 
    uint32 reserved4; 
    uint32 reserved5; 
    uint32 reserved6; 
    uint8 reserved7; 
    uint8 reserved8; 
    uint32 reserved9; 
    uint32 reserved10; 
    opennsl_gport_t reserved11; 
    opennsl_pkt_dnx_pph_fhei_extension_t reserved12; 
    opennsl_pkt_dnx_pph_eei_extension_t reserved13; 
    opennsl_pkt_dnx_pph_learn_extension_t reserved14; 
} opennsl_pkt_dnx_pph_t;

/** otsh type */
typedef enum opennsl_pkt_dnx_otsh_type_e {
    opennslpktReservedEnum86 = 0, 
    opennslpktReservedEnum87 = 1, 
    opennslpktReservedEnum88 = 2 
} opennsl_pkt_dnx_otsh_type_t;

/** otsh oam sutype */
typedef enum opennsl_pkt_dnx_otsh_oam_subtype_e {
    opennslpktReservedEnum89 = 0, 
    opennslpktReservedEnum90 = 1, 
    opennslpktReservedEnum91 = 2, 
    opennslpktReservedEnum92 = 3, 
    opennslpktReservedEnum93 = 4, 
    opennslpktReservedEnum94 = 5, 
    opennslpktReservedEnum95 = 7 
} opennsl_pkt_dnx_otsh_oam_subtype_t;

/** otsh */
typedef struct opennsl_pkt_dnx_otsh_s {
    opennsl_pkt_dnx_otsh_type_t reserved1; 
    opennsl_pkt_dnx_otsh_oam_subtype_t reserved2; 
    uint32 reserved3; 
    uint32 reserved4; 
    uint8 reserved5; 
    uint64 reserved6; 
    uint32 reserved7; 
    uint32 reserved8; 
} opennsl_pkt_dnx_otsh_t;

/** otmh src sysport extension */
typedef struct opennsl_pkt_dnx_otmh_src_sysport_extension_s {
    uint8 reserved1; 
    opennsl_gport_t reserved2; 
} opennsl_pkt_dnx_otmh_src_sysport_extension_t;

/** otmh vport extension */
typedef struct opennsl_pkt_dnx_otmh_vport_extension_s {
    uint8 reserved1; 
    opennsl_gport_t reserved2; 
} opennsl_pkt_dnx_otmh_vport_extension_t;

/** otmh */
typedef struct opennsl_pkt_dnx_otmh_s {
    opennsl_pkt_dnx_ftmh_action_type_t reserved1; 
    opennsl_color_t reserved2; 
    uint8 reserved3; 
    uint32 reserved4; 
    opennsl_gport_t reserved5; 
    opennsl_pkt_dnx_otmh_src_sysport_extension_t reserved6; 
    opennsl_pkt_dnx_otmh_vport_extension_t reserved7; 
} opennsl_pkt_dnx_otmh_t;

#define OPENNSL_PKT_DNX_RAW_SIZE_MAX    20         
/** raw */
typedef struct opennsl_pkt_dnx_raw_s {
    uint8 reserved1[OPENNSL_PKT_DNX_RAW_SIZE_MAX]; 
    int reserved2; 
} opennsl_pkt_dnx_raw_t;

/** dnx packet */
typedef struct opennsl_pkt_dnx_s {
    opennsl_pkt_dnx_type_t reserved1; 
    opennsl_pkt_dnx_ptch1_t reserved2; 
    opennsl_pkt_dnx_ptch2_t reserved3; 
    opennsl_pkt_dnx_itmh_t reserved4; 
    opennsl_pkt_dnx_ftmh_t reserved5; 
    opennsl_pkt_dnx_pph_t reserved6; 
    opennsl_pkt_dnx_otsh_t reserved7; 
    opennsl_pkt_dnx_otmh_t reserved8; 
    opennsl_pkt_dnx_raw_t reserved9; 
} opennsl_pkt_dnx_t;

/** Initialize a OPENNSL packet structure. */
struct opennsl_pkt_s { 
    opennsl_pkt_blk_t *pkt_data;        /**< Pointer to array of data blocks. */
    uint8 blk_count;                    /**< Number of blocks in data array. */
    uint8 unit;                         /**< Unit number. */
    uint8 cos;                          /**< The local COS queue to use. */
    uint8 reserved1; 
    opennsl_vlan_t vlan;                /**< 802.1q VID or VSI or VPN. */
    uint8 reserved2; 
    uint8 reserved3; 
    opennsl_vlan_t reserved4; 
    uint8 reserved5; 
    uint8 reserved6; 
    opennsl_color_t reserved7; 
    int8 src_port;                      /**< Source port used in header/tag. */
    opennsl_trunk_t reserved8; 
    uint16 reserved9; 
    uint8 dest_port;                    /**< Destination port used in header/tag. */
    uint16 reserved10; 
    uint8 reserved11; 
    opennsl_gport_t reserved12; 
    opennsl_gport_t reserved13; 
    opennsl_multicast_t reserved14; 
    uint32 reserved15; 
    opennsl_pkt_stk_forward_t reserved16; 
    uint32 reserved17; 
    uint32 reserved18; 
    uint32 reserved19; 
    uint32 reserved20; 
    opennsl_if_t reserved21; 
    uint16 pkt_len;                     /**< Packet length according to flags. */
    uint16 tot_len;                     /**< Packet length as transmitted or
                                           received. */
    opennsl_pbmp_t tx_pbmp;             /**< Target ports. */
    opennsl_pbmp_t tx_upbmp;            /**< Untagged target ports. */
    opennsl_pbmp_t reserved22; 
    opennsl_port_t reserved23; 
    uint8 reserved24; 
    uint32 rx_reason;                   /**< Opcode from packet. */
    opennsl_rx_reasons_t reserved25; 
    uint32 reserved26; 
    uint8 reserved27; 
    uint8 rx_port;                      /**< Local rx port; not in HG hdr. */
    uint8 reserved28; 
    uint8 rx_untagged;                  /**< The packet was untagged on ingress. */
    uint32 reserved29; 
    uint32 reserved30; 
    opennsl_if_t reserved31; 
    opennsl_vlan_action_t reserved32; 
    opennsl_vlan_action_t reserved33; 
    uint32 reserved34; 
    uint32 reserved35; 
    uint32 reserved36; 
    void *reserved37; 
    void *reserved38; 
    opennsl_pkt_cb_f call_back;         /**< Callback function. */
    uint32 flags;                       /**< OPENNSL_PKT_F_xxx flags. */
    void *reserved39; 
    int8 reserved40; 
    opennsl_pkt_blk_t _pkt_data;        /**< For single block packets (internal). */
    opennsl_pkt_t *reserved41; 
    void *reserved42; 
    int8 reserved43; 
    opennsl_pkt_t *reserved44; 
    void *reserved45; 
    void *reserved46; 
    uint8 reserved47[16]; 
    uint8 reserved48[12]; 
    uint8 reserved49[4]; 
    uint8 _vtag[4];                     /**< VLAN tag if not in packet (network
                                           byte order). */
    uint8 reserved50[16]; 
    uint8 reserved51; 
    uint8 reserved52[10]; 
    int reserved53; 
    int reserved54; 
    uint32 reserved55; 
    opennsl_pbmp_t reserved56; 
    opennsl_pbmp_t reserved57; 
    uint32 reserved58; 
    uint8 reserved59; 
    uint8 reserved60; 
    uint16 reserved61; 
    uint32 reserved62; 
    void *reserved63; 
    uint16 reserved64; 
    uint16 reserved65; 
    opennsl_pkt_timestamp_mode_t reserved66; 
    opennsl_pkt_oam_lm_counter_mode_t reserved67; 
    opennsl_pkt_oam_lm_counter_mode_t reserved68; 
    uint8 reserved69; 
    opennsl_rx_decap_tunnel_t reserved70; 
    opennsl_gport_t reserved71; 
    opennsl_gport_t reserved72; 
    uint32 reserved73; 
    int reserved74; 
    opennsl_gport_t reserved75; 
    uint32 reserved76; 
    uint32 reserved77; 
    uint8 reserved78; 
    opennsl_pkt_rx_oam_type_t reserved79; 
    opennsl_pkt_oam_counter_t reserved80[OPENNSL_PKT_OAM_COUNTER_MAX]; 
    uint32 reserved81; 
    uint8 reserved82[20]; 
    opennsl_pkt_dnx_t reserved83[OPENNSL_PKT_NOF_DNX_HEADERS]; 
    uint8 reserved84; 
};

#define OPENNSL_PKT_F_NO_VTAG   0x4        /**< Packet does not contain VLAN tag. */
#define OPENNSL_TX_CRC_ALLOC    0x10       /**< Allocate buffer for CRC. */
#define OPENNSL_TX_CRC_REGEN    0x20       /**< Regenerate CRC. */
#define OPENNSL_TX_CRC_APPEND   (OPENNSL_TX_CRC_ALLOC + OPENNSL_TX_CRC_REGEN) 
#define OPENNSL_TX_ETHER        0x100000   /**< Fully mapped packet TX. */
#define OPENNSL_PKT_F_TRUNK     0x20000000 /**< Trunk port. */
#define OPENNSL_PKT_ONE_BUF_SETUP(pkt, buf, _len)  \
    do { \
        (pkt)->_pkt_data.data = (buf); \
        (pkt)->_pkt_data.len = (_len); \
        (pkt)->pkt_data = &(pkt)->_pkt_data; \
        (pkt)->blk_count = 1; \
    } while (0) 
/***************************************************************************//** 
 *\brief Initialize packet flags based on the type of device.
 *
 *\description Based on the device type of unit, initializes the flags for
 *          opennsl_pkt_t starting with init_flags.
 *
 *\param    unit [IN]   Unit number.
 *\param    pkt [IN]   Packet structure to modify
 *\param    init_flags [IN]   Initial flags to start with
 *
 *\retval    OPENNSL_E_NONE On success
 ******************************************************************************/
extern int opennsl_pkt_flags_init(
    int unit, 
    opennsl_pkt_t *pkt, 
    uint32 init_flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Allocate or deallocate a packet structure and packet data.
 *
 *\description opennsl_pkt_alloc will allocate a packet structure using
 *          sal_alloc, allocate a packet data buffer of size bytes using
 *          soc_cm_salloc and then link this buffer into the packet structure.
 *           It will call =opennsl_pkt_flags_init to set up the packet.
 *          opennsl_pkt_free deallocates a packet allocated by
 *          opennsl_pkt_alloc.
 *          opennsl_pkt_free supports freeing multiple packet data blocks.
 *          opennsl_pkt_alloc does not currently work when unit is a remote
 *          device.
 *
 *\param    unit [IN]   Unit number.
 *\param    size [IN]   Number of bytes to allocate for buffer space
 *\param    flags [IN]   Initial flags for the packet structure
 *\param    pkt_buf [OUT]   Structure to be allocated.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_MEMORY Not enough memory - pkt_buf will be NULL
 ******************************************************************************/
extern int opennsl_pkt_alloc(
    int unit, 
    int size, 
    uint32 flags, 
    opennsl_pkt_t **pkt_buf) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Allocate or deallocate a packet structure and packet data.
 *
 *\description opennsl_pkt_alloc will allocate a packet structure using
 *          sal_alloc, allocate a packet data buffer of size bytes using
 *          soc_cm_salloc and then link this buffer into the packet structure.
 *           It will call =opennsl_pkt_flags_init to set up the packet.
 *          opennsl_pkt_free deallocates a packet allocated by
 *          opennsl_pkt_alloc.
 *          opennsl_pkt_free supports freeing multiple packet data blocks.
 *          opennsl_pkt_alloc does not currently work when unit is a remote
 *          device.
 *
 *\param    unit [IN]   Unit number.
 *\param    pkt [IN]   Structure to be allocated.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_MEMORY Not enough memory - pkt_buf will be NULL
 ******************************************************************************/
extern int opennsl_pkt_free(
    int unit, 
    opennsl_pkt_t *pkt) LIB_DLL_EXPORTED ;

#endif /* __OPENNSL_PKT_H__ */
/*@}*/
