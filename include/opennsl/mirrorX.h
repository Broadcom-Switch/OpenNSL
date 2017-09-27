/** \addtogroup mirror Mirroring
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
 * \file			mirrorX.h
 ******************************************************************************/

#ifndef __OPENNSL_MIRRORX_H__
#define __OPENNSL_MIRRORX_H__

#include <opennsl/types.h>
#include <opennsl/pkt.h>

#define OPENNSL_MIRROR_DEST_REPLACE         (1 << 0)   /**< Replace mirror
                                                          destination. */
#define OPENNSL_MIRROR_DEST_WITH_ID         (1 << 1)   /**< Mirror destination id
                                                          is valid. */
#define OPENNSL_MIRROR_DEST_TUNNEL_L2       (1 << 2)   /**< Mirrored packet should
                                                          be L2 tunneled. */
#define OPENNSL_MIRROR_DEST_TUNNEL_IP_GRE   (1 << 3)   /**< Mirrored packet should
                                                          be L3 GRE tunneled. */
#define OPENNSL_MIRROR_DEST_PAYLOAD_UNTAGGED (1 << 4)   /**< Strip vlan tag from
                                                          mirrored packet. */
#define OPENNSL_MIRROR_DEST_TUNNEL_TRILL    (1 << 5)   /**< Mirrored packet should
                                                          be TRILL tunneled. */
#define OPENNSL_MIRROR_DEST_TUNNEL_NIV      (1 << 6)   /**< Mirrored packet should
                                                          be NIV tunneled. */
#define OPENNSL_MIRROR_DEST_UPDATE_POLICER  (1 << 7)   /**< update policer using
                                                          policer_id */
#define OPENNSL_MIRROR_DEST_UPDATE_COUNTER  (1 << 8)   /**< update counter using
                                                          stat_id */
#define OPENNSL_MIRROR_DEST_DEST_MULTICAST  (1 << 9)   /**< destination is ingress
                                                          multicast */
#define OPENNSL_MIRROR_DEST_TUNNEL_WITH_ENCAP_ID (1 << 10)  /**< Mirror destination
                                                          encap_id is valid */
#define OPENNSL_MIRROR_DEST_TUNNEL_RSPAN    (1 << 12)  /**< Mirrored packet should
                                                          be RSPAN (VLAN)
                                                          tunneled */
#define OPENNSL_MIRROR_DEST_INT_PRI_SET     (1 << 13)  /**< Mirrored packet should
                                                          set with internal
                                                          priority */
#define OPENNSL_MIRROR_DEST_TUNNEL_ETAG     (1 << 14)  /**< Mirrored packet should
                                                          be ETAG tunneled. */
#define OPENNSL_MIRROR_DEST_TUNNEL_SFLOW    (1 << 15)  /**< Mirrored packet should
                                                          be with sFlow
                                                          encapsulation */
#define OPENNSL_MIRROR_DEST_IS_SNOOP        (1 << 16)  /**< Specify that the
                                                          destination type is a
                                                          snoop destination. */
#define OPENNSL_MIRROR_DEST_IS_TRAP         (1 << 17)  /**< Specify that the
                                                          destination is a trap
                                                          destination. */
#define OPENNSL_MIRROR_DEST_EGRESS_ADD_ORIG_SYSTEM_HEADER (1 << 18)  /**< The start of the
                                                          original packet system
                                                          header will be
                                                          included in the
                                                          outbound mirrored
                                                          packets. */
#define OPENNSL_MIRROR_DEST_FIELD           (1 << 19)  /**< Specify that mirror
                                                          destination owner is
                                                          FP. */
#define OPENNSL_MIRROR_DEST_PORT            (1 << 20)  /**< Specify that mirror
                                                          destination owner is
                                                          PORT. */
#define OPENNSL_MIRROR_DEST_UPDATE_COUNTER_1 (1 << 21)  /**< update counter No.1 */
#define OPENNSL_MIRROR_DEST_UPDATE_COUNTER_2 (1 << 22)  /**< update counter No.2 */
#define OPENNSL_MIRROR_DEST_ID_SHARE        (1 << 24)  /**< Share mirror
                                                          destination id among
                                                          multi ports */
#define OPENNSL_MIRROR_DEST_MTP_ADD         (1 << 25)  /**< Add an MTP into a
                                                          shared-id mirror
                                                          destination */
#define OPENNSL_MIRROR_DEST_MTP_DELETE      (1 << 26)  /**< Delete an MTP from a
                                                          shared-id mirror
                                                          destination */
#define OPENNSL_MIRROR_DEST_MTP_REPLACE     (1 << 27)  /**< REPLACE an MTP of a
                                                          shared-id mirror
                                                          destination */
#define OPENNSL_MIRROR_DEST_EGRESS_TRAP_WITH_SYSTEM_HEADER (1 << 28)  /**< For packets recycled
                                                          by egress applications
                                                          and not forwarded,
                                                          retain the incoming
                                                          packet's system
                                                          headers as received
                                                          from the fabric, and
                                                          in case of an Egress
                                                          MC packet, stamp the
                                                          FTMH.OutLIF field with
                                                          the CUD. */
#define OPENNSL_MIRROR_DEST_TUNNEL_PSAMP    (1 << 29)  /**< Update mirror
                                                          destination with PSAMP
                                                          encapsulation */
#define OPENNSL_MIRROR_DEST_OUT_MIRROR_DISABLE (1 << 30)  /**< Assert out mirror
                                                          disable */
/**  represents the options for the mirroring of packets */
typedef struct opennsl_mirror_options_s {
    uint32 flags;           
    uint8 forward_strength; 
    uint8 copy_strength;    
    uint32 recycle_cmd;     /**< dedicated for ETPP traps */
} opennsl_mirror_options_t;

/** 
 * Mirror destination Structure
 * 
 * Contains information required for manipulating mirror destinations.
 */
typedef struct opennsl_mirror_destination_s {
    opennsl_gport_t mirror_dest_id;     /**< Unique mirror destination and
                                           encapsulation identifier. */
    uint32 flags;                       /**< See OPENNSL_MIRROR_DEST_xxx flag
                                           definitions. */
    opennsl_gport_t gport;              /**< Mirror destination. */
    uint8 version;                      /**< IP header version. */
    uint8 tos;                          /**< Traffic Class/Tos byte. */
    uint8 ttl;                          /**< Hop limit. */
    opennsl_ip_t src_addr;              /**< Tunnel source ip address (IPv4). */
    opennsl_ip_t dst_addr;              /**< Tunnel destination ip address (IPv4). */
    opennsl_ip6_t src6_addr;            /**< Tunnel source ip address (IPv6). */
    opennsl_ip6_t dst6_addr;            /**< Tunnel destination ip address (IPv6). */
    uint32 flow_label;                  /**< IPv6 header flow label field. */
    opennsl_mac_t src_mac;              /**< L2 source mac address. */
    opennsl_mac_t dst_mac;              /**< L2 destination mac address. */
    uint16 tpid;                        /**< L2 header outer TPID. */
    opennsl_vlan_t vlan_id;             /**< Vlan id. */
    opennsl_trill_name_t trill_src_name; /**< TRILL source bridge nickname */
    opennsl_trill_name_t trill_dst_name; /**< TRILL destination bridge nickname */
    int trill_hopcount;                 /**< TRILL hop count */
    uint16 niv_src_vif;                 /**< Source Virtual Interface of NIV tag */
    uint16 niv_dst_vif;                 /**< Destination Virtual Interface of NIV
                                           tag */
    uint32 niv_flags;                   /**< NIV flags OPENNSL_MIRROR_NIV_XXX */
    uint16 gre_protocol;                /**< L3 GRE header protocol */
    opennsl_policer_t policer_id;       /**< policer_id */
    int stat_id;                        /**< stat_id */
    int reserved1; 
    opennsl_if_t encap_id;              /**< Encapsulation index */
    opennsl_if_t tunnel_id;             /**< IP tunnel for encapsulation. Valid
                                           only if
                                           OPENNSL_MIRROR_DEST_TUNNEL_IP_GRE is
                                           set */
    uint16 reserved2; 
    uint8 pkt_prio;                     /**< L2 header PCP */
    uint32 reserved3; 
    uint32 reserved4; 
    uint8 int_pri;                      /**< Internal Priority */
    uint16 etag_src_vid;                /**< Extended (source) port vlan id */
    uint16 etag_dst_vid;                /**< Extended (destination) port vlan id */
    uint16 udp_src_port;                /**< UDP source port */
    uint16 udp_dst_port;                /**< UDP destination port */
    uint32 reserved5; 
    uint32 reserved6; 
    uint8 recycle_context;              /**< recycle context of egress originating
                                           packets */
    uint16 packet_copy_size;            /**<  If non zero, the copied packet will
                                           be truncated to the first
                                           packet_copy_size . Current supported
                                           values for DNX are 0, 64, 128, 192 */
    uint16 egress_packet_copy_size;     /**< If non zero and the packet is copied
                                           from the egress, the packet will be
                                           truncated to the first
                                           packet_copy_size . Current supported
                                           values for DNX are 0, 256. */
    opennsl_reserved_enum_t reserved7; 
    uint8 reserved8; 
    uint8 reserved9; 
    uint16 reserved10; 
    uint32 reserved11; 
} opennsl_mirror_destination_t;

typedef int (*opennsl_mirror_destination_traverse_cb)(
    int unit, 
    opennsl_mirror_destination_t *mirror_dest, 
    void *user_data);

/***************************************************************************//** 
 *\brief Initialize a mirror destination structure.
 *
 *\description Initialize a mirror destination structure.
 *
 *\param    mirror_dest [IN,OUT]   Pointer to the struct to be initialized
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_mirror_destination_t_init(
    opennsl_mirror_destination_t *mirror_dest) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Add mirror destination descriptor.
 *
 *\description Add mirroring destination descriptor. Descriptor contains mirrored
 *          traffic  destination (gport) and mirrored traffic encapsulation. 
 *          mirror_dest_id: is returned to application to  be used in
 *          mirror_port_dest_add/delete APIs. If the destination has already
 *          been created, a OPENNSL_E_EXISTS error will be returned. But the
 *          matching mirror destinations with tunnel type will be skipped. The
 *          mirror_dest_id for such a destination may be recovered with
 *          =opennsl_mirror_destination_get . .
 *
 *\param    unit [IN]   Unit number.
 *\param    mirror_dest [IN,OUT]   Mirrored destination and encapsulation
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mirror_destination_create(
    int unit, 
    opennsl_mirror_destination_t *mirror_dest) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Read content of mirror destination descriptor.
 *
 *\description Read content of mirror destination descriptor corresponding to the
 *          provided mirror_dest_id.  If the mirror_dest_id argument is
 *          OPENNSL_GPORT_INVALID, then the mirror_dest information is checked
 *          to match an existing mirror destination. But the matching mirror
 *          destinations with tunnel type will be skipped. If a match is
 *          found, the mirror_dest.mirror_dest_id field is updated with the ID
 *          for this destination description.  This will recover the
 *          mirror_dest_id when =opennsl_mirror_destination_create returns a
 *          OPENNSL_E_EXISTS error.
 *
 *\param    unit [IN]   Unit number.
 *\param    mirror_dest_id [IN]   Mirrored destination ID to be removed.
 *\param    mirror_dest [IN,OUT]   Mirrored destination ID to be removed.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mirror_destination_get(
    int unit, 
    opennsl_gport_t mirror_dest_id, 
    opennsl_mirror_destination_t *mirror_dest) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Remove mirror destination descriptor.
 *
 *\description Remove mirroring destination descriptor. OPENNSL_E_BUSY will be
 *          returned  if descriptor is in use. .
 *
 *\param    unit [IN]   Unit number.
 *\param    mirror_dest_id [IN]   Mirrored destination ID to be removed.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mirror_destination_destroy(
    int unit, 
    opennsl_gport_t mirror_dest_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Traverse over all installed mirror destination descriptors.
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    cb [IN]   Traverse callback.
 *\param    user_data [IN]   User provided cookie.
 *
 *\retval    OPENNSL_E_XXX Traverse over all installed mirror destination
 *          descriptors. For each valid destination user callback is called with
 *          user_data provided in function call.
 ******************************************************************************/
extern int opennsl_mirror_destination_traverse(
    int unit, 
    opennsl_mirror_destination_traverse_cb cb, 
    void *user_data) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set the mirror-to port bitmap for the device.
 *
 *\description Set the mirror-to port bitmap for the device. This API interface
 *          is only supported on network switch fabric chips.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    pbmp [IN]   The port bitmap of mirror-to ports for this port
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNIT Invalid OPENNSL device ID.
 *\retval    OPENNSL_E_PORT Invalid port
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_mirror_to_pbmp_set(
    int unit, 
    opennsl_port_t port, 
    opennsl_pbmp_t pbmp) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the mirror-to port bitmap for the device.
 *
 *\description Get the mirror-to port bitmap for the device. This API interface
 *          is only supported on network switch fabric chips.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    pbmp [OUT]   The port bitmap of mirror-to ports for this port
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNIT Invalid OPENNSL device ID
 *\retval    OPENNSL_E_PORT Invalid port
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_mirror_to_pbmp_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_pbmp_t *pbmp) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set VLAN for egressing mirrored packets on a port (RSPAN).
 *
 *\description When a tag protocol ID and VLAN is configured for a port, all
 *          packets mirrored to this port will be tagged with the
 *          corresponding RSPAN tag.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Port number to configure
 *\param    tpid [IN]   Tag protocol ID (0 to disable)
 *\param    vlan [IN]   VLAN number (0 to disable)
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNIT Invalid OPENNSL device ID
 *\retval    OPENNSL_E_PORT Invalid port
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_mirror_vlan_set(
    int unit, 
    opennsl_port_t port, 
    uint16 tpid, 
    uint16 vlan) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get VLAN for egressing mirrored packets on a port (RSPAN).
 *
 *\description When a tag protocol ID and VLAN is configured for a port, all
 *          packets mirrored to this port will be tagged with the
 *          corresponding RSPAN tag.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Port number to configure
 *\param    tpid [OUT]   Tag protocol ID
 *\param    vlan [OUT]   VLAN number
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNIT Invalid OPENNSL device ID
 *\retval    OPENNSL_E_PORT Invalid port
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_mirror_vlan_get(
    int unit, 
    opennsl_port_t port, 
    uint16 *tpid, 
    uint16 *vlan) LIB_DLL_EXPORTED ;

#define OPENNSL_MIRROR_DEST_NO_COUNT    -2         /**< Value to disable counting
                                                      of the snooped/mirrored
                                                      copy. */
#endif /* __OPENNSL_MIRRORX_H__ */
/*@}*/
