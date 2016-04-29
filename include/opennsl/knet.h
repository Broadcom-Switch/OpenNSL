/** \addtogroup knet Kernel Network (KNET) Configuration
 *  @{
 */
/*****************************************************************************
 * 
 * (C) Copyright Broadcom Corporation 2013-2016
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
 * \file			knet.h
 ******************************************************************************/

#ifndef __OPENNSL_KNET_H__
#define __OPENNSL_KNET_H__

#include <opennsl/types.h>
#include <opennsl/rx.h>

#define OPENNSL_KNET_NETIF_T_TX_CPU_INGRESS 1          /**< Tx packets are sent
                                                          through CPU port
                                                          ingress logic. */
#define OPENNSL_KNET_NETIF_T_TX_LOCAL_PORT  2          /**< Tx packets are sent to
                                                          local device port
                                                          bypassing switch
                                                          logic. */
#define OPENNSL_KNET_NETIF_F_ADD_TAG    0x00000001 /**< Add VLAN tag to packets
                                                      sent directly to physical
                                                      port. */
#define OPENNSL_KNET_NETIF_NAME_MAX 16         
/** Kernel network interface structure. */
typedef struct opennsl_knet_netif_s {
    int id;                             /**< Network interface ID. */
    int type;                           /**< Network interface type
                                           (OPENNSL_KNET_NETIF_T_XXX). */
    uint32 flags;                       /**< OPENNSL_KNET_NETIF_F_XXX flags. */
    opennsl_mac_t mac_addr;             /**< MAC address associated with this
                                           network interface. */
    opennsl_vlan_t vlan;                /**< VLAN ID associated with this
                                           interface. */
    opennsl_port_t port;                /**< Local port associated with this
                                           interface. */
    char name[OPENNSL_KNET_NETIF_NAME_MAX]; /**< Network interface name (assigned by
                                           kernel) */
} opennsl_knet_netif_t;

#define OPENNSL_KNET_FILTER_T_RX_PKT    1          /**< Rx packet filter. */
#define OPENNSL_KNET_DEST_T_NETIF           1          /**< Send packet to virtual
                                                          network interface. */
#define OPENNSL_KNET_DEST_T_OPENNSL_RX_API  2          /**< Send packet to OPENNSL
                                                          Rx API. */
#define OPENNSL_KNET_FILTER_F_STRIP_TAG 0x00000001 /**< Strip VLAN tag from
                                                      packets sent to vitual
                                                      network interfaces. */
#define OPENNSL_KNET_FILTER_DESC_MAX    32         
#define OPENNSL_KNET_FILTER_SIZE_MAX    256        
#define OPENNSL_KNET_FILTER_M_RAW       0x00000001 /**< Match raw packet data */
#define OPENNSL_KNET_FILTER_M_VLAN      0x00000002 /**< Match VLAN ID */
#define OPENNSL_KNET_FILTER_M_INGPORT   0x00000004 /**< Match local ingress port */
#define OPENNSL_KNET_FILTER_M_REASON    0x00000020 /**< Match copy-to-CPU reason
                                                      code */
#define OPENNSL_KNET_FILTER_M_FP_RULE   0x00000040 /**< Match filter processor
                                                      rule number */
/** Kernel packet filter structure. */
typedef struct opennsl_knet_filter_s {
    int id;                             /**< Filter ID. */
    int type;                           /**< Filter type
                                           (OPENNSL_KNET_FILTER_T_XXX). */
    uint32 flags;                       /**< OPENNSL_KNET_FILTER_F_XXX flags. */
    int priority;                       /**< Filter priority (0 is highest). */
    int dest_type;                      /**< Filter destination type. */
    int dest_id;                        /**< Filter destination ID. */
    int dest_proto;                     /**< If non-zero this value overrides the
                                           default protocol type when matching
                                           packet is passed to network stack. */
    int mirror_type;                    /**< Mirror destination type. */
    int mirror_id;                      /**< Mirror destination ID. */
    int mirror_proto;                   /**< If non-zero this value overrides the
                                           default protocol type when matching
                                           packet is passed to network stack. */
    uint32 match_flags;                 /**< OPENNSL_KNET_FILTER_M_XXX flags. */
    char desc[OPENNSL_KNET_FILTER_DESC_MAX]; /**< Filter description (optional) */
    opennsl_vlan_t m_vlan;              /**< VLAN ID to match. */
    opennsl_port_t m_ingport;           /**< Local ingress port to match. */
    int m_src_modport;                  /**< Source module port to match. */
    int m_src_modid;                    /**< Source module ID to match. */
    opennsl_rx_reasons_t m_reason;      /**< Copy-to-CPU reason to match. */
    int m_fp_rule;                      /**< Filter processor rule to match. */
    int raw_size;                       /**< Size of valid raw data and mask. */
    uint8 m_raw_data[OPENNSL_KNET_FILTER_SIZE_MAX]; /**< Raw data to match. */
    uint8 m_raw_mask[OPENNSL_KNET_FILTER_SIZE_MAX]; /**< Raw data mask for match. */
} opennsl_knet_filter_t;

/***************************************************************************//** 
 *\brief Initialize a opennsl_knet_netif_t structure.
 *
 *\description Initialize a opennsl_knet_netif_t structure.
 *
 *\param    netif [IN,OUT]   Pointer to struct to be initialized
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_knet_netif_t_init(
    opennsl_knet_netif_t *netif) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Initialize a opennsl_knet_filter_t structure.
 *
 *\description Initialize a opennsl_knet_filter_t structure.
 *
 *\param    filter [IN,OUT]   Pointer to struct to be initialized
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_knet_filter_t_init(
    opennsl_knet_filter_t *filter) LIB_DLL_EXPORTED ;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Initialize the kernel networking subsystem.
 *
 *\description Initialize the kernel networking subsystem.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_UNAVAIL
 *\retval    OPENNSL_E_CONFIG
 *\retval    OPENNSL_E_INTERNAL
 *\retval    OPENNSL_E_TIMEOUT
 *\retval    OPENNSL_E_PARAM
 *\retval    OPENNSL_E_RESOURCE
 *\retval    OPENNSL_E_NOT_FOUND
 ******************************************************************************/
extern int opennsl_knet_init(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create a kernel network interface.
 *
 *\description Create a virtual network interface in the kernel (operating
 *          system). The ID and name fields of the structure will be assigned
 *          be the API. Once created, the application is responsible for
 *          managing the network interface through the appropriate system
 *          calls such as the POSIX sockets interface.
 *          For RCPU mode use network interface type
 *          OPENNSL_KNET_NETIF_T_TX_META_DATA and add
 *          OPENNSL_KNET_NETIF_F_RCPU_ENCAP to the network interface flags.
 *
 *\param    unit [IN]   Unit number.
 *\param    netif [IN,OUT]   Network interface configuration
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_UNAVAIL
 *\retval    OPENNSL_E_INTERNAL
 *\retval    OPENNSL_E_TIMEOUT
 *\retval    OPENNSL_E_PARAM
 *\retval    OPENNSL_E_RESOURCE
 ******************************************************************************/
extern int opennsl_knet_netif_create(
    int unit, 
    opennsl_knet_netif_t *netif) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroy a kernel network interface.
 *
 *\description Remove a previously created virtual network interface from the
 *          kernel (operating system). The application is responsible for
 *          properly shutting down the network interface prior to calling this
 *          API.
 *
 *\param    unit [IN]   Unit number.
 *\param    netif_id [IN]   Network interface ID
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_UNAVAIL
 *\retval    OPENNSL_E_INTERNAL
 *\retval    OPENNSL_E_TIMEOUT
 *\retval    OPENNSL_E_PARAM
 *\retval    OPENNSL_E_NOT_FOUND
 ******************************************************************************/
extern int opennsl_knet_netif_destroy(
    int unit, 
    int netif_id) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

typedef int (*opennsl_knet_netif_traverse_cb)(
    int unit, 
    opennsl_knet_netif_t *netif, 
    void *user_data);

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Traverse kernel network interface objects.
 *
 *\description Iterates over virtual network interfaces for this unit and
 *          executes user callback function for each interface. The callback
 *          function is defined as follows:
 *          typedef int (*opennsl_knet_netif_traverse_cb)(     int unit,     
 *          opennsl_knet_netif_t *netif,      void *user_data); .
 *
 *\param    unit [IN]   Unit number.
 *\param    trav_fn [IN]   User provided callback function
 *\param    user_data [IN]   User provided data used as input param for callback
 *          function
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_UNAVAIL
 *\retval    OPENNSL_E_INTERNAL
 *\retval    OPENNSL_E_TIMEOUT
 *\retval    OPENNSL_E_PARAM
 *\retval    OPENNSL_E_NOT_FOUND
 ******************************************************************************/
extern int opennsl_knet_netif_traverse(
    int unit, 
    opennsl_knet_netif_traverse_cb trav_fn, 
    void *user_data) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create a kernel packet filter.
 *
 *\description Create a kernel packet filter that will direct packets received
 *          from the CPU port to a virtual network interface (or the OPENNSL
 *          Rx API) based on out-of-band data and/or packet data.
 *
 *\param    unit [IN]   Unit number.
 *\param    filter [IN,OUT]   Rx packet filter configuration
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_UNAVAIL
 *\retval    OPENNSL_E_INTERNAL
 *\retval    OPENNSL_E_TIMEOUT
 *\retval    OPENNSL_E_PARAM
 *\retval    OPENNSL_E_RESOURCE
 ******************************************************************************/
extern int opennsl_knet_filter_create(
    int unit, 
    opennsl_knet_filter_t *filter) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Destroy a kernel packet filter.
 *
 *\description Destroy a kernel packet filter.
 *
 *\param    unit [IN]   Unit number.
 *\param    filter_id [IN]   Rx packet filter ID
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_UNAVAIL
 *\retval    OPENNSL_E_INTERNAL
 *\retval    OPENNSL_E_TIMEOUT
 *\retval    OPENNSL_E_PARAM
 *\retval    OPENNSL_E_NOT_FOUND
 ******************************************************************************/
extern int opennsl_knet_filter_destroy(
    int unit, 
    int filter_id) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

typedef int (*opennsl_knet_filter_traverse_cb)(
    int unit, 
    opennsl_knet_filter_t *filter, 
    void *user_data);

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Traverse kernel packet filter objects.
 *
 *\description Iterates over kernel packet filters for this unit and executes
 *          user callback function for each packet filter. The callback
 *          function is defined as follows:
 *          typedef int (*opennsl_knet_filter_traverse_cb)(     int unit,     
 *          opennsl_knet_filter_t *filter,      void *user_data);
 *          .
 *
 *\param    unit [IN]   Unit number.
 *\param    trav_fn [IN]   User provided callback function
 *\param    user_data [IN]   User provided data used as input param for callback
 *          function
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_UNAVAIL
 *\retval    OPENNSL_E_INTERNAL
 *\retval    OPENNSL_E_TIMEOUT
 *\retval    OPENNSL_E_PARAM
 *\retval    OPENNSL_E_NOT_FOUND
 ******************************************************************************/
extern int opennsl_knet_filter_traverse(
    int unit, 
    opennsl_knet_filter_traverse_cb trav_fn, 
    void *user_data) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#include <opennsl/knetX.h>
#endif /* __OPENNSL_KNET_H__ */
/*@}*/
