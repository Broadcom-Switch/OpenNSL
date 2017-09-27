/** \addtogroup qos Quality of Service
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
 * \file			qosX.h
 ******************************************************************************/

#ifndef __OPENNSL_QOSX_H__
#define __OPENNSL_QOSX_H__

#include <opennsl/types.h>
#include <opennsl/multicast.h>
#include <opennsl/l3.h>

#define OPENNSL_QOS_MAP_WITH_ID         0x0001     
#define OPENNSL_QOS_MAP_REPLACE         0x0002     
#define OPENNSL_QOS_MAP_L2              0x0004     
#define OPENNSL_QOS_MAP_L2_OUTER_TAG    OPENNSL_QOS_MAP_L2 
#define OPENNSL_QOS_MAP_L2_INNER_TAG    0x0008     
#define OPENNSL_QOS_MAP_L2_UNTAGGED     0x0010     
#define OPENNSL_QOS_MAP_L2_VLAN_PCP     0x0020     
#define OPENNSL_QOS_MAP_L3              0x0040     
#define OPENNSL_QOS_MAP_IPV4            OPENNSL_QOS_MAP_L3 
#define OPENNSL_QOS_MAP_IPV6            0x0080     
#define OPENNSL_QOS_MAP_ENCAP           0x0200     
#define OPENNSL_QOS_MAP_INGRESS         0x0400     
#define OPENNSL_QOS_MAP_EGRESS          0x0800     
#define OPENNSL_QOS_MAP_QUEUE           0x4000     
#define OPENNSL_QOS_MAP_POLICER         0x8000     
#define OPENNSL_QOS_MAP_PACKET_INVALID  0x10000    
#define OPENNSL_QOS_MAP_IGNORE_OFFSET   0x20000    
#define OPENNSL_QOS_MAP_OPCODE          0x40000    
#define OPENNSL_QOS_MAP_L2_ETAG         0x80000    
#define OPENNSL_QOS_MAP_L2_VLAN_ETAG    0x100000   
#define OPENNSL_QOS_MAP_SUBPORT         0x400000   
#define OPENNSL_QOS_MAP_L3_L2           0x800000   
/** QoS Map structure */
typedef struct opennsl_qos_map_s {
    uint8 pkt_pri;                  /**< Packet priority */
    uint8 pkt_cfi;                  /**< Packet CFI */
    int dscp;                       /**< Packet DSCP */
    int exp;                        /**< Packet EXP */
    int int_pri;                    /**< Internal priority */
    opennsl_color_t color;          /**< Color */
    int remark_int_pri;             /**< (internal) remarking priority */
    opennsl_color_t remark_color;   /**< (internal) remark color */
    int policer_offset;             /**< Offset based on pri/cos to fetch a
                                       policer */
    int queue_offset;               /**< Offset based on int_pri to fetch cosq for
                                       subscriber ports */
    int port_offset;                /**< Offset based on port connection for
                                       indexing into the action table */
    uint8 etag_pcp;                 /**< ETAG PCP field */
    uint8 etag_de;                  /**< ETAG DE field */
    int counter_offset;             /**< Offset based on priority for indexing
                                       into the loss measurement counter table */
    int inherited_dscp_exp;         /**< Inherited DSCP EXP value */
} opennsl_qos_map_t;

/***************************************************************************//** 
 *\brief Initialize the QoS Map structure.
 *
 *\description Initializes a QoS map structure to zero.
 *
 *\param    qos_map [IN,OUT]   Pointer to a QoS map structure.
 *
 *\retval    Void
 ******************************************************************************/
extern void opennsl_qos_map_t_init(
    opennsl_qos_map_t *qos_map) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Allocates hardware resources for QoS mapping.
 *
 *\description Allocates hardware resources for QoS mapping. Depending on the
 *          type of mapping  specified by the configuration flags (L2, L3,
 *          L2_VLAN_PCP, MPLS, ingress, egress),  the corresponding set of
 *          entries is reserved in the  appropriate priority  mapping table.
 *          The map_id is an identifier associated with the reserved chunk.  A
 *          QoS map can be shared by multiple objects, which are GPORTS.
 *          The flags which are passed in indicate which type of map is to be
 *          created. These flags are or-ed together.
 *          General flags: OPENNSL_QOS_MAP_WITH_ID - Use the indicated map
 *          table and type indicated in the                       map passed
 *          in. OPENNSL_QOS_MAP_REPLACE - Replace the indicated map type.
 *          OPENNSL_QOS_MAP_INGRESS - Create an ingress map used in
 *          conjunction with map type. OPENNSL_QOS_MAP_EGRESS  - Create an
 *          egress map used in conjunction with map type.
 *          L2 flags: OPENNSL_QOS_MAP_L2 - create L2 type of map - defaults to
 *          outer tag map. For Trident2plus,                  this flag will
 *          only create an MPLS type of map while outer tag map will          
 *                 be created via flag OPENNSL_QOS_MAP_L3.
 *          OPENNSL_QOS_MAP_L2_OUTER_TAG - create L2 outer tag map.
 *          OPENNSL_QOS_MAP_L2_INNER_TAG - create L2 inner tag map.
 *          OPENNSL_QOS_MAP_L2_UNTAGGED - create L2 untagged map.
 *          OPENNSL_QOS_MAP_L2_VLAN_PCP - indicates that mapping is done via
 *          VLAN_PCP rather than LIF.                            If not set
 *          and other L2 flags set, indicates LIF COS map type.
 *          MiM flags: OPENNSL_QOS_MAP_MIM_ITAG - create a MiM map - used in
 *          conjunction wiht L2 flags.
 *          L3 flags: OPENNSL_QOS_MAP_L3 - create L3 type of map - defaults to
 *          IPV4 map. For Trident2plus,                  this flag will create
 *          both IPV4 map and outer tag map. OPENNSL_QOS_MAP_IPV4 - create
 *          IPV4 L3 map. OPENNSL_QOS_MAP_IPV6 - create IPV6 L3 map. For the
 *          network switch, network switch and network switch families, these
 *          flags are not supported. To configure the ingress DSCP mapping,
 *          user can use port API opennsl_port_dscp_map_set/get() to control
 *          related DSCP mapping.
 *          FCOE flags: OPENNSL_QOS_MAP_VFT - create a FCOE VFT map.
 *          OPENNSL_QOS_MAP_VSAN - create a FCOE VSAN map.
 *          MPLS OPENNSL_QOS_MAP_MPLS - create an MPLS type of map.
 *          OPENNSL_QOS_MAP_MPLS_ELSP - create an MPLS map for ELSP.
 *          OPENNSL_QOS_MAP_MPLS_PHP - create an MPLS map for PHP.
 *          MiML flags: OPENNSL_QOS_MAP_MIML - create a MiML map - used in
 *          conjunction wiht L2 flags.
 *          Other: OPENNSL_QOS_MAP_ENCAP - indicates an encapsulated header.
 *          OPENNSL_QOS_MAP_PACKET_INVALID  Drops packets on a specific
 *          port*VLAN when the UP/PCP                              values do
 *          not match configured values for that port
 *          OPENNSL_QOS_MAP_IGNORE_OFFSET  This option prevents AC offset from
 *          being added to the                            default logical
 *          interface, although the offset still                            
 *          applies to Qos-related processing
 *          OPENNSL_QOS_MAP_OPCODE  Sets the AC according to the CoS
 *          attributes arriving in the                     packet. This map ID
 *          sets the opcode according to either                      the IPV4
 *          or IPV6 TOS field or the Layer2 header according                  
 *            to the VLAN tag or resolving the packet using a combination     
 *                          of Traffic Class and Drop Precedence fields.
 *          OPENNSL_OAM_MAP_OAM_PCP - Configures the mapping of the TOS to
 *          OAM-PCP.                       Must be used together with one (and
 *          only one) of the flags                       OPENNSL_QOS_INGRESS
 *          or OPENNSL_QOS_EGRESS
 *          OPENNSL_QOS_MAP_OAM_INTPRI - Configures the mapping of the
 *          Internal priority                          to LM counter offset.
 *          OPENNSL_QOS_MAP_OAM_OUTER_VLAN_PCP - Configures the mapping of the
 *          outer vlan priority                                  to LM counter
 *          offset. OPENNSL_QOS_MAP_OAM_INNER_VLAN_PCP - Configures the
 *          mapping of the inner vlan priority                                
 *           to LM counter offset. OPENNSL_QOS_MAP_OAM_MPLS_EXP - Configures
 *          the mapping of the exp field in mpls label to                     
 *                LM counter offset. OPENNSL_QOS_MAP_REPLICATION - Configures
 *          replication QOS map profile. .
 *
 *\param    unit [IN]   Unit number.
 *\param    flags [IN]   Configuration flags
 *\param    map_id [IN,OUT]   QoS map ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_qos_map_create(
    int unit, 
    uint32 flags, 
    int *map_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Frees hardware resources for QoS mapping.
 *
 *\description Given a map_id, this API de-allocates the hardware resources that
 *          were reserved using.
 *
 *\param    unit [IN]   Unit number.
 *\param    map_id [IN]   QoS map ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_qos_map_destroy(
    int unit, 
    int map_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Add a specific mapping entry to a QoS map.
 *
 *\description A QoS map identified by map_id is a set of mapping entries between
 *          a packet's QoS  markings and the internal priority and color. The
 *          opennsl_qos_map_add API adds a specific  mapping entry to the QoS
 *          map. This API actually programs the mapping in the hardware. 
 *          Configuration flags which may be specified include L2 (untagged,
 *          outer, inner, vlan_pcp),  L3 (ipv4, ipv6) or MPLS.
 *          The OPENNSL_QOS_MAP_SUBPORT flag is used for mapping egress SubTag
 *          CoE packet's PHB (internal priority and color) to subport tag's
 *          Priority Code Point(PCP) and Drop Eligible(DE). If the paremeter
 *          flags = OPENNSL_QOS_MAP_SUBPORT then map the  egress SubTag CoE
 *          packet's internal priority and color to the subport tag's PCP and
 *          DE.
 *
 *\param    unit [IN]   Unit number.
 *\param    flags [IN]   Configuration flags
 *\param    map [IN]   Pointer to a opennsl_qos_map_t structure
 *\param    map_id [IN]   QoS map ID
 *
 *\retval    OPENNSL_E_INIT, OPENNSL_E_PARAM, OPENNSL_E_RESOURCE, OPENNSL_E_NONE
 ******************************************************************************/
extern int opennsl_qos_map_add(
    int unit, 
    uint32 flags, 
    opennsl_qos_map_t *map, 
    int map_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get an entire QoS mapping for the given QoS Map ID.
 *
 *\description Get an entire QoS mapping for the given QoS Map ID.  If zero is
 *          passed array_size, the API will set array_count to the number of
 *          elements required to satisfy the request.  Otherwise, the API will
 *          fill in the requested mapping, and set array_count to the number
 *          of elements set.  Exactly one map may be retrieved per call. .
 *
 *\param    unit [IN]   Unit number.
 *\param    flags [IN]   Configuration flags
 *\param    map_id [IN]   QoS map ID
 *\param    array_size [IN]   Number of elements in array parameter; 0 to query
 *\param    array [OUT]   Number of elements in array parameter; 0 to query
 *\param    array_count [OUT]   Number of mappings retrieved
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_qos_map_multi_get(
    int unit, 
    uint32 flags, 
    int map_id, 
    int array_size, 
    opennsl_qos_map_t *array, 
    int *array_count) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Deletes a specific mapping entry from a QoS map.
 *
 *\description The opennsl_qos_map_delete API deletes a specific mapping entry
 *          from the QoS map, identifies  by map_id.
 *
 *\param    unit [IN]   Unit number.
 *\param    flags [IN]   Configuration flags
 *\param    map [IN]   Pointer to a opennsl_qos_map_t structure
 *\param    map_id [IN]   QoS map ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_qos_map_delete(
    int unit, 
    uint32 flags, 
    opennsl_qos_map_t *map, 
    int map_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Associates a GPORT with a QoS map.
 *
 *\description This API associates a GPORT with an ingress and an egress QoS map.
 *          A map ID of zero  will clear the existing QoS map and a map ID of
 *          -1 will leave the existing map unchanged.
 *          If egress map id is zero, VLAN priority map will be restored to
 *          default (Trident2+), or be cleared to all-zero (other devices).
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   GPORT identifier
 *\param    ing_map [IN]   Ingress QoS map ID
 *\param    egr_map [IN]   Egress QoS map ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_qos_port_map_set(
    int unit, 
    opennsl_gport_t port, 
    int ing_map, 
    int egr_map) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Retrieves the configured QoS mapping matching a type for the given
 *       GPORT.
 *
 *\description Given some profile type, the configured QoS mapping for that GPORT
 *          matching the type will be returned. Useful when given gport has
 *          more than one QOS profile that can be associated to.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   GPORT identifier
 *\param    flags [IN]   Flags to specify the type
 *\param    map_id [OUT]   Ingress QoS map ID
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_qos_port_map_type_get(
    int unit, 
    opennsl_gport_t port, 
    uint32 flags, 
    int *map_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Retrieves the configured QoS mapping for the given GPORT.
 *
 *\description Retrieves the configured QoS mapping for the given GPORT.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   GPORT identifier
 *\param    ing_map [OUT]   Ingress QoS map ID
 *\param    egr_map [OUT]   Egress QoS map ID
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_qos_port_map_get(
    int unit, 
    opennsl_gport_t port, 
    int *ing_map, 
    int *egr_map) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Associate a port, vid with an ingress and egress QoS mapping.
 *
 *\description Associate a port, vid with an ingress and egress QoS mapping. A
 *          map ID of zero  will clear the existing QoS map and a map ID of -1
 *          will leave the existing map unchanged.   Values of vid cause the
 *          following behaviors:.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Port number
 *\param    vid [IN]   VLAN Identifier
 *\param    ing_map [IN]   Ingress QoS map ID.  0 to clear, -1 to preserve
 *\param    egr_map [IN]   Egress QoS map ID.  0 to clear, -1 to preserve
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_qos_port_vlan_map_set(
    int unit, 
    opennsl_port_t port, 
    opennsl_vlan_t vid, 
    int ing_map, 
    int egr_map) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the QoS map ID for a port, vid.
 *
 *\description Get the QoS map ID for a port, vid. .
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Port number
 *\param    vid [IN]   VLAN Identifier
 *\param    ing_map [OUT]   Ingress QoS map ID
 *\param    egr_map [OUT]   Egress QoS map ID
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_qos_port_vlan_map_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_vlan_t vid, 
    int *ing_map, 
    int *egr_map) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the list of all QoS Map IDs.
 *
 *\description Get the list of all QoS Map IDs. If zero is passed as array_size, 
 *          the API will set array_count to the number of all the map IDs.
 *          Otherwise, the API will fill in the map IDs and set array_count 
 *          to the number of map IDs whose info has been filled in.
 *
 *\param    unit [IN]   Unit number.
 *\param    array_size [IN]   Number of elements in array parameter; 0 to query
 *\param    map_ids_array [OUT]   Storage location for map ids
 *\param    flags_array [OUT]   Storage location for flags associated with the
 *          maps
 *\param    array_count [OUT]   Number of mappings retrieved
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_qos_multi_get(
    int unit, 
    int array_size, 
    int *map_ids_array, 
    int *flags_array, 
    int *array_count) LIB_DLL_EXPORTED ;

#endif /* __OPENNSL_QOSX_H__ */
/*@}*/
