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
#endif /* __OPENNSL_RXX_H__ */
/*@}*/
