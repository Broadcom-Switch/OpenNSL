/** \addtogroup pkt Packet Transmit and Receive
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
 * \file			rxX.h
 ******************************************************************************/

#ifndef __OPENNSL_RXX_H__
#define __OPENNSL_RXX_H__

#include <opennsl/types.h>
#include <opennsl/pkt.h>
#include <opennsl/tx.h>
#include <opennsl/mirror.h>

#if defined(VENDOR_BROADCOM)
#endif
#define OPENNSL_RX_COSQ_PACKET_TYPE_SWITCHED 0x1        
#define OPENNSL_RX_COSQ_PACKET_TYPE_NON_UNICAST 0x2        
#define OPENNSL_RX_COSQ_PACKET_TYPE_MIRROR  0x4        
/***************************************************************************//** 
 *\brief Map/Un-map packets to a CPU CoS queue.
 *
 *\description These APIs can be used to direct certain Host-bound packets to a
 *          specific Host CoS queue.
 *          CPU-bound packets may have zero or  more reasons associated with
 *          them which can be used to map packets to CoS queues.  (see
 *          =rx_reasons_code_table .)  Reasons used to classify a packet must
 *          be included  in both reasons and reasons_mask.
 *          A packet can also be classified by the internal packet priority by
 *          setting int_prio and int_prio_mask.
 *          Finally, a packet can be classified by the packet type (see below)
 *          using packet_type and packet_type_mask. If a specific packet type
 *          should not be used to classify a packet, the corresponding bit in
 *          packet_type_mask should be set to zero.
 *          A given packet may match multiple classification entries. This
 *          ambiguity is resolved by using the entry with the lowest index
 *          value to determine the CoS queue. The API 
 *          opennsl_rx_cosq_mapping_size_get can be used to determine the
 *          number of entries in  the CoS classification table for a given
 *          device.
 *          A few classication entries with the lowest priorities are reserved
 *          by the SDK to classify packets  to appropriate CPU CoS queues by
 *          default. These entries may be overwritten or deleted by the 
 *          application if the default behavior is undesirable.  When the
 *          number of queues per port on the  device is changed via
 *          =opennsl_cosq_config_set, the default entries are will be
 *          recreated as appropriate  for the new queues.
 *
 *\param    unit [IN]   Unit number.
 *\param    size [OUT]
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_PARAM Invalid parameter(s)
 *\retval    OPENNSL_E_UNAVAIL Not available on the specified unit
 ******************************************************************************/
extern int opennsl_rx_cosq_mapping_size_get(
    int unit, 
    int *size) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Map/Un-map packets to a CPU CoS queue.
 *
 *\description These APIs can be used to direct certain Host-bound packets to a
 *          specific Host CoS queue.
 *          CPU-bound packets may have zero or  more reasons associated with
 *          them which can be used to map packets to CoS queues.  (see
 *          =rx_reasons_code_table .)  Reasons used to classify a packet must
 *          be included  in both reasons and reasons_mask.
 *          A packet can also be classified by the internal packet priority by
 *          setting int_prio and int_prio_mask.
 *          Finally, a packet can be classified by the packet type (see below)
 *          using packet_type and packet_type_mask. If a specific packet type
 *          should not be used to classify a packet, the corresponding bit in
 *          packet_type_mask should be set to zero.
 *          A given packet may match multiple classification entries. This
 *          ambiguity is resolved by using the entry with the lowest index
 *          value to determine the CoS queue. The API 
 *          opennsl_rx_cosq_mapping_size_get can be used to determine the
 *          number of entries in  the CoS classification table for a given
 *          device.
 *          A few classication entries with the lowest priorities are reserved
 *          by the SDK to classify packets  to appropriate CPU CoS queues by
 *          default. These entries may be overwritten or deleted by the 
 *          application if the default behavior is undesirable.  When the
 *          number of queues per port on the  device is changed via
 *          =opennsl_cosq_config_set, the default entries are will be
 *          recreated as appropriate  for the new queues.
 *
 *\param    unit [IN]   Unit number.
 *\param    index [IN]   Index into CPU CoS mapping table
 *\param    reasons [IN]   Set of packet reasons
 *\param    reasons_mask [IN]   Mask for the set of packet reasons
 *\param    int_prio [IN]   Internal priority value of packet
 *\param    int_prio_mask [IN]   Mask for internal priority value
 *\param    packet_type [IN]   Packet type (see OPENNSL_RX_COSQ_PACKET_TYPE_*
 *          below)
 *\param    packet_type_mask [IN]   Mask for packet type
 *\param    cosq [IN]   CPU CoS queue
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_PARAM Invalid parameter(s)
 *\retval    OPENNSL_E_UNAVAIL Not available on the specified unit
 ******************************************************************************/
extern int opennsl_rx_cosq_mapping_set(
    int unit, 
    int index, 
    opennsl_rx_reasons_t reasons, 
    opennsl_rx_reasons_t reasons_mask, 
    uint8 int_prio, 
    uint8 int_prio_mask, 
    uint32 packet_type, 
    uint32 packet_type_mask, 
    opennsl_cos_queue_t cosq) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Map/Un-map packets to a CPU CoS queue.
 *
 *\description These APIs can be used to direct certain Host-bound packets to a
 *          specific Host CoS queue.
 *          CPU-bound packets may have zero or  more reasons associated with
 *          them which can be used to map packets to CoS queues.  (see
 *          =rx_reasons_code_table .)  Reasons used to classify a packet must
 *          be included  in both reasons and reasons_mask.
 *          A packet can also be classified by the internal packet priority by
 *          setting int_prio and int_prio_mask.
 *          Finally, a packet can be classified by the packet type (see below)
 *          using packet_type and packet_type_mask. If a specific packet type
 *          should not be used to classify a packet, the corresponding bit in
 *          packet_type_mask should be set to zero.
 *          A given packet may match multiple classification entries. This
 *          ambiguity is resolved by using the entry with the lowest index
 *          value to determine the CoS queue. The API 
 *          opennsl_rx_cosq_mapping_size_get can be used to determine the
 *          number of entries in  the CoS classification table for a given
 *          device.
 *          A few classication entries with the lowest priorities are reserved
 *          by the SDK to classify packets  to appropriate CPU CoS queues by
 *          default. These entries may be overwritten or deleted by the 
 *          application if the default behavior is undesirable.  When the
 *          number of queues per port on the  device is changed via
 *          =opennsl_cosq_config_set, the default entries are will be
 *          recreated as appropriate  for the new queues.
 *
 *\param    unit [IN]   Unit number.
 *\param    index [IN]   Index into CPU CoS mapping table
 *\param    reasons [IN,OUT]   Set of packet reasons
 *\param    reasons_mask [IN,OUT]   Mask for the set of packet reasons
 *\param    int_prio [OUT]   Internal priority value of packet
 *\param    int_prio_mask [OUT]   Mask for internal priority value
 *\param    packet_type [OUT]   Packet type (see OPENNSL_RX_COSQ_PACKET_TYPE_*
 *          below)
 *\param    packet_type_mask [OUT]   Mask for packet type
 *\param    cosq [OUT]   CPU CoS queue
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_PARAM Invalid parameter(s)
 *\retval    OPENNSL_E_UNAVAIL Not available on the specified unit
 ******************************************************************************/
extern int opennsl_rx_cosq_mapping_get(
    int unit, 
    int index, 
    opennsl_rx_reasons_t *reasons, 
    opennsl_rx_reasons_t *reasons_mask, 
    uint8 *int_prio, 
    uint8 *int_prio_mask, 
    uint32 *packet_type, 
    uint32 *packet_type_mask, 
    opennsl_cos_queue_t *cosq) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Map/Un-map packets to a CPU CoS queue.
 *
 *\description These APIs can be used to direct certain Host-bound packets to a
 *          specific Host CoS queue.
 *          CPU-bound packets may have zero or  more reasons associated with
 *          them which can be used to map packets to CoS queues.  (see
 *          =rx_reasons_code_table .)  Reasons used to classify a packet must
 *          be included  in both reasons and reasons_mask.
 *          A packet can also be classified by the internal packet priority by
 *          setting int_prio and int_prio_mask.
 *          Finally, a packet can be classified by the packet type (see below)
 *          using packet_type and packet_type_mask. If a specific packet type
 *          should not be used to classify a packet, the corresponding bit in
 *          packet_type_mask should be set to zero.
 *          A given packet may match multiple classification entries. This
 *          ambiguity is resolved by using the entry with the lowest index
 *          value to determine the CoS queue. The API 
 *          opennsl_rx_cosq_mapping_size_get can be used to determine the
 *          number of entries in  the CoS classification table for a given
 *          device.
 *          A few classication entries with the lowest priorities are reserved
 *          by the SDK to classify packets  to appropriate CPU CoS queues by
 *          default. These entries may be overwritten or deleted by the 
 *          application if the default behavior is undesirable.  When the
 *          number of queues per port on the  device is changed via
 *          =opennsl_cosq_config_set, the default entries are will be
 *          recreated as appropriate  for the new queues.
 *
 *\param    unit [IN]   Unit number.
 *\param    index [IN]   Index into CPU CoS mapping table
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_PARAM Invalid parameter(s)
 *\retval    OPENNSL_E_UNAVAIL Not available on the specified unit
 ******************************************************************************/
extern int opennsl_rx_cosq_mapping_delete(
    int unit, 
    int index) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get all the CPU CoS queue mapping reasons supported on the specified
 *       device.
 *
 *\description Get all the CPU CoS queue mapping reasons supported on the
 *          specified device.
 *
 *\param    unit [IN]   Unit number.
 *\param    reasons [OUT]   Set of packet reasons
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_PARAM Invalid parameter(s)
 *\retval    OPENNSL_E_UNAVAIL Not available on the specified unit
 ******************************************************************************/
extern int opennsl_rx_cosq_mapping_reasons_get(
    int unit, 
    opennsl_rx_reasons_t *reasons) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set/get the RX per-Cos rate limiting value.
 *
 *\description These functions configure rate limiting on a
 *          per-software-Cos-queue basis.  If packets for the given CoS are
 *          received at a rate higher than this setting,  they will be
 *          discarded in the interrupt handler.
 *          Both functions support a value of OPENNSL_RX_RATE_NOLIMIT for pps
 *          to indicate rate limiting is disabled.
 *          Setting the unit number to OPENNSL_RX_SYSTEM_UNIT (only in
 *          SDK-5.3.0 or SDK-5.2.4; see =opennsl_rx_rate_set ) will result in
 *          an error returned because system wide burst settings are not
 *          supported. .
 *
 *\param    unit [IN]   Unit number.
 *\param    cos [IN]   CoS to configure
 *\param    pps [IN]   Rate in packets/second
 *
 *\retval    OPENNSL_E_XXX Error during required initialization
 ******************************************************************************/
extern int opennsl_rx_cos_rate_set(
    int unit, 
    int cos, 
    int pps) LIB_DLL_EXPORTED ;

#if defined(OPENNSL_RPC_SUPPORT) || defined(OPENNSL_RCPU_SUPPORT)
#endif
/** Return values from PKT RX callout routines. */
typedef enum opennsl_rx_trap_e {
    opennslRxTrapUserDefine = 204,  /**< User define traps. */
} opennsl_rx_trap_t;

/** Forwarding header position overridden value */
typedef enum opennsl_rx_trap_forwarding_header_e {
    opennslRxTrapForwardingHeaderPacketStart = 0, /**< Start of packet. */
    opennslRxTrapForwardingHeaderL2Header = 1, /**< Ethernet header. */
    opennslRxTrapForwardingHeaderFirstHeader = 2, /**< First header after Ethernet. */
    opennslRxTrapForwardingHeaderSecondHeader = 3, /**< Second header after Ethernet. */
    opennslRxTrapForwardingHeaderThirdHeader = 4, /**< Third header after Ethernet. */
    opennslRxTrapForwardingHeaderFourthHeader = 5, /**< Fourth header after Ethernet. */
    opennslRxTrapForwardingHeaderOamBfdPdu = 6, /**< OAM or BFD PDU header. */
    opennslRxTrapForwardingHeaderCount = 7 /**< Always Last. Not a usable value. */
} opennsl_rx_trap_forwarding_header_t;

/** User-configurable, per-unit-core RX destination configuration. */
typedef struct opennsl_rx_trap_core_config_s {
    opennsl_gport_t dest_port;  /**< Destination port */
    opennsl_if_t encap_id;      /**< Encap-ID */
} opennsl_rx_trap_core_config_t;

/** User-configurable, per-unit RX configuration. */
typedef struct opennsl_rx_trap_config_s {
    uint32 flags;                       /**< OPENNSL_RX_TRAP_XXX FLAGS. */
    opennsl_gport_t dest_port;          /**< Destination port. */
    opennsl_multicast_t dest_group;     /**< Destination group. */
    int prio;                           /**< Internal priority of the packet. */
    opennsl_color_t color;              /**< Color of the packet. */
    opennsl_policer_t ether_policer_id; /**< Ethernet Policer. */
    opennsl_policer_t policer_id;       /**< general policer id. */
    int counter_num;                    /**< counter. */
    int trap_strength;                  /**< Strength of this trap, strongest trap
                                           in processing holds. */
    int snoop_cmnd;                     /**< snoop command. */
    int snoop_strength;                 /**< Strength of this trap, strongest
                                           snoop in processing holds. */
    opennsl_reserved_enum_t forwarding_type; /**< Forwarding type value */
    opennsl_rx_trap_forwarding_header_t forwarding_header; /**< Forwarding header position overridden
                                           value */
    opennsl_if_t encap_id;              /**< Encap-ID */
    opennsl_mirror_options_t *mirror_cmd; /**< Mirror options in ETPP traps */
    opennsl_rx_trap_core_config_t *core_config_arr; /**< Destinations information per core */
    int core_config_arr_len;            /**< core_config_arr length */
    int qos_map_id;                     /**< cos profile handle */
    int tunnel_termination_trap_strength; /**< Strength of tunnel termination trap,
                                           strongest trap in processing holds. */
    int tunnel_termination_snoop_strength; /**< Strength of tunnel termination trap,
                                           strongest snoop in processing holds. */
} opennsl_rx_trap_config_t;

/***************************************************************************//** 
 *\brief Initialize the rx_trap_config_t structure.
 *
 *\description Initialize the rx_trap_config_t structure. .
 *
 *\param    trap_config [IN,OUT]   Trap configuration structure
 *
 *\returns  Nothing
 ******************************************************************************/
extern void opennsl_rx_trap_config_t_init(
    opennsl_rx_trap_config_t *trap_config) LIB_DLL_EXPORTED ;

/** User-configurable, per-unit RX configuration. */
typedef struct opennsl_rx_snoop_config_s {
    uint32 flags;                   /**< OPENNSL_RX_SNOOP_XXX FLAGS. */
    opennsl_gport_t dest_port;      /**< Destination port. */
    opennsl_multicast_t dest_group; /**< Destination group. */
    int prio;                       /**< Internal priority of the packet. */
    opennsl_color_t color;          /**< Color of the packet. */
    opennsl_policer_t policer_id;   /**< policer_id. */
    int counter_num;                /**< counter. */
    int size;                       /**< what portion of the packet to snoop to
                                       CPU, use -1 to indicate full packet
                                       snooping. */
    int probability;                /**< snooping probability. Value represents
                                       percentage with percisionof a thousandth
                                       of a percent (100000 is 100.000%),  range
                                       0 - 100000. */
    opennsl_if_t encap_id;          /**< Encap-ID */
} opennsl_rx_snoop_config_t;

/***************************************************************************//** 
 *\brief Initialize the rx_snoop_config_t structure.
 *
 *\description Initialize the rx_snoop_config_t structure. .
 *
 *\param    snoop_config [IN,OUT]   snoop configuration structure
 *
 *\returns  Nothing
 ******************************************************************************/
extern void opennsl_rx_snoop_config_t_init(
    opennsl_rx_snoop_config_t *snoop_config) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create trap handle for a given type.
 *
 *\description Create trap handle for a given type  .
 *
 *\param    unit [IN]   Unit number.
 *\param    flags [IN]   See OPENNSL_RX_TRAP_xxx
 *\param    type [IN]   Type of trap see opennsl_rx_trap_t
 *\param    trap_id [IN,OUT]   Trap id
 *
 *\retval    OPENNSL_E_RESOURCE No more trap-id of given type
 *\retval    OPENNSL_E_EXISTS Trap-id already exists
 ******************************************************************************/
extern int opennsl_rx_trap_type_create(
    int unit, 
    int flags, 
    opennsl_rx_trap_t type, 
    int *trap_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get trap id according to type.
 *
 *\description Get trap id according to type.  .
 *
 *\param    unit [IN]   Unit number.
 *\param    flags [IN]   See OPENNSL_RX_TRAP_xxx
 *\param    type [IN]   Type of trap see opennsl_rx_trap_t
 *\param    trap_id [OUT]   Trap id
 *
 *\retval    OPENNSL_E_PARAM Bad parameter
 ******************************************************************************/
extern int opennsl_rx_trap_type_get(
    int unit, 
    int flags, 
    opennsl_rx_trap_t type, 
    int *trap_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get trap type according to trap id.
 *
 *\description Get  trap type according to trap id.  .
 *
 *\param    unit [IN]   Unit number.
 *\param    flags [IN]   reserved for future use
 *\param    trap_id [IN]   Trap id
 *\param    trap_type [OUT]   Trap type
 *
 *\retval    OPENNSL_E_NOT_FOUND if trap type not found
 ******************************************************************************/
extern int opennsl_rx_trap_type_from_id_get(
    int unit, 
    int flags, 
    int trap_id, 
    opennsl_rx_trap_t *trap_type) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroy trap handle for a given trap id.
 *
 *\description Destroy trap handle for a given trap id. .
 *
 *\param    unit [IN]   Unit number.
 *\param    trap_id [IN]   Trap id
 *
 *\retval    OPENNSL_E_NOT_FOUND Trap not found
 ******************************************************************************/
extern int opennsl_rx_trap_type_destroy(
    int unit, 
    int trap_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set how to handle packet according to trap type.
 *
 *\description Set how to handle packet according to trap type. .
 *
 *\param    unit [IN]   Unit number.
 *\param    trap_id [IN]   Trap id
 *\param    config [IN]   Trap configuration
 *
 *\retval    OPENNSL_E_UNIT Illegal unit number
 *\retval    OPENNSL_E_INIT Unit not initialized yet
 *\retval    OPENNSL_E_PARAM Bad parameter
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_rx_trap_set(
    int unit, 
    int trap_id, 
    opennsl_rx_trap_config_t *config) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get trap configuration according to trap id.
 *
 *\description Get  trap configuration according to trap id.  .
 *
 *\param    unit [IN]   Unit number.
 *\param    trap_id [IN]   Trap id
 *\param    config [OUT]   Trap configuration
 *
 *\retval    OPENNSL_E_NOT_FOUND Trap not found
 ******************************************************************************/
extern int opennsl_rx_trap_get(
    int unit, 
    int trap_id, 
    opennsl_rx_trap_config_t *config) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief The snoop can be set for given trap-code (e.g. IGMP), or by other
 *       action, like FP, or forwarding lookup.
 *
 *\description The snoop can be set for given trap-code (e.g. IGMP), or by other
 *          action, like FP, or forwarding lookup. .
 *
 *\param    unit [IN]   Unit number.
 *\param    snoop_cmnd [IN]   Snoop command
 *\param    config [IN]   Pointer for opennsl_rx_snoop_config_t struct
 *
 *\retval    OPENNSL_E_UNIT Illegal unit number
 *\retval    OPENNSL_E_INIT Unit not initialized yet
 *\retval    OPENNSL_E_PARAM Bad parameter
 *\retval    OPENNSL_E_XXX Other error code
 ******************************************************************************/
extern int opennsl_rx_snoop_set(
    int unit, 
    int snoop_cmnd, 
    opennsl_rx_snoop_config_t *config) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set snoop configuration of the snoop command.
 *
 *\description Set snoop configuration of the snoop command  .
 *
 *\param    unit [IN]   Unit number.
 *\param    snoop_cmnd [IN]   Snoop command
 *\param    config [OUT]   Pointer for opennsl_rx_snoop_config_t struct
 *
 *\retval    OPENNSL_E_NOT_FOUND Trap not found
 ******************************************************************************/
extern int opennsl_rx_snoop_get(
    int unit, 
    int snoop_cmnd, 
    opennsl_rx_snoop_config_t *config) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create snoop command.
 *
 *\description Create snoop command.  .
 *
 *\param    unit [IN]   Unit number.
 *\param    flags [IN]   OPENNSL_RX_SNOOP_XXX FLAGS
 *\param    snoop_cmnd [IN,OUT]   Snoop command
 *
 *\retval    OPENNSL_E_RESOURCE No more trap-id of given type
 *\retval    OPENNSL_E_EXISTS Trap-id already exists
 ******************************************************************************/
extern int opennsl_rx_snoop_create(
    int unit, 
    int flags, 
    int *snoop_cmnd) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroy create snoop command.
 *
 *\description Destroy create snoop command. .
 *
 *\param    unit [IN]   Unit number.
 *\param    flags [IN]   See OPENNSL_RX_TRAP_xxx
 *\param    snoop_cmnd [IN]   Snoop command
 *
 *\retval    OPENNSL_E_NOT_FOUND Trap not found
 ******************************************************************************/
extern int opennsl_rx_snoop_destroy(
    int unit, 
    int flags, 
    int snoop_cmnd) LIB_DLL_EXPORTED ;

#define OPENNSL_RX_TRAP_REPLACE 0x00000800 /**< Replace config of existing
                                              trap/snoop. */
#define OPENNSL_RX_SNOOP_UPDATE_DEST        0x00000001 /**< update destination. */
#define OPENNSL_RX_SNOOP_UPDATE_PRIO        0x00000002 /**< update priority. */
#define OPENNSL_RX_SNOOP_UPDATE_COLOR       0x00000004 /**< update color. */
#define OPENNSL_RX_SNOOP_UPDATE_POLICER     0x00000008 /**< update policer id. */
#define OPENNSL_RX_SNOOP_UPDATE_ETHERNET_POLICER 0x00000010 /**< update Ethernet
                                                          policer. */
#define OPENNSL_RX_SNOOP_UPDATE_COUNTER     0x00000020 /**< update counter. */
#define OPENNSL_RX_SNOOP_DEST_MULTICAST     0x00000040 /**< destination is
                                                          multicast. */
#define OPENNSL_RX_SNOOP_WITH_ID            0x00000080 /**< Use the specified
                                                          trap/snoop id. */
#define OPENNSL_RX_SNOOP_REPLACE            0x00000100 /**< Replace config of
                                                          existing trap/snoop. */
#endif /* __OPENNSL_RXX_H__ */
/*@}*/
