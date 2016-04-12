/** \addtogroup l2 Layer 2 Address Management
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
 * \file			l2.h
 ******************************************************************************/

#ifndef __OPENNSL_L2_H__
#define __OPENNSL_L2_H__

#include <opennsl/types.h>

#define OPENNSL_L2_DISCARD_SRC  0x00000002 
#define OPENNSL_L2_DISCARD_DST  0x00000004 
#define OPENNSL_L2_L3LOOKUP     0x00000010 
#define OPENNSL_L2_STATIC       0x00000020 
#define OPENNSL_L2_MOVE_PORT    0x00100000 
#define OPENNSL_L2_CALLBACK_DELETE      0          
#define OPENNSL_L2_CALLBACK_ADD         1          
#define OPENNSL_L2_CALLBACK_MOVE_EVENT  5          
/** Device-independent L2 address structure. */
typedef struct opennsl_l2_addr_s {
    uint32 flags;                       /**< OPENNSL_L2_xxx flags. */
    uint32 reserved1; 
    opennsl_mac_t mac;                  /**< 802.3 MAC address. */
    opennsl_vlan_t vid;                 /**< VLAN identifier. */
    int port;                           /**< Zero-based port number. */
    int modid;                          /**< XGS: modid. */
    opennsl_trunk_t tgid;               /**< Trunk group ID. */
    opennsl_cos_t reserved2; 
    opennsl_cos_t reserved3; 
    opennsl_multicast_t reserved4; 
    opennsl_pbmp_t reserved5; 
    int reserved6; 
    int reserved7; 
    opennsl_fabric_distribution_t reserved8; 
    int reserved9; 
    int reserved10; 
} opennsl_l2_addr_t;

/***************************************************************************//** 
 *\brief Initialize an L2 address structure to a specified MAC address and VLAN
 *       ID.
 *
 *\description Setup L2 address structure with given MAC address and VLAN ID with
 *          all other fields  zeroing out.  After this call is made, the flags
 *          field can be modified with the fields  defined by
 *          opennsl_l2_addr_add().
 *
 *\param    l2addr [IN,OUT]   Pointer to layer 2 address type
 *\param    mac_addr [IN,OUT]
 *\param    vid [IN]   VLAN ID
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_l2_addr_t_init(
    opennsl_l2_addr_t *l2addr, 
    const opennsl_mac_t mac_addr, 
    opennsl_vlan_t vid) LIB_DLL_EXPORTED ;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Add an L2 address entry to the specified device.
 *
 *\description Add a MAC address to the switch Address Resolution Logic (ARL)
 *          port with the given VLAN ID and parameters.   Use CMIC_PORT for
 *          the port value to associate the entry with the CPU.  Use flag of
 *          OPENNSL_L2_COPY_TO_CPU to send a copy to the CPU. Use flag of
 *          OPENNSL_L2_TRUNK_MEMBER to set trunking (TGID must be passed as
 *          well with  a valid trunk group ID).
 *
 *\param    unit [IN]   Unit number.
 *\param    l2addr [IN]   L2 address which is properly initialized
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l2_addr_add(
    int unit, 
    opennsl_l2_addr_t *l2addr) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Delete an L2 address entry from the specified device.
 *
 *\description Delete the given MAC address with the specified VLAN ID from the
 *          device. If users want to know which entries are deleted, they
 *          should register  callback routines by API
 *          opennsl_l2_addr_register(). If L2_MOD_FIFO is used,  but the
 *          thread opennslL2MOD.x is stopped, users can not know which entries
 *          are deleted, even though they already had registered callback
 *          routines.
 *
 *\param    unit [IN]   Unit number.
 *\param    mac [IN]   802.3 MAC address
 *\param    vid [IN]   VLAN ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l2_addr_delete(
    int unit, 
    opennsl_mac_t mac, 
    opennsl_vlan_t vid) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Check if an L2 entry is present in the L2 table.
 *
 *\description Given a MAC address and VLAN ID, check if the entry is present in
 *          the L2 table, and  if so, return all associated information.
 *
 *\param    unit [IN]   Unit number.
 *\param    mac_addr [IN]   Input MAC address to search
 *\param    vid [IN]   Input VLAN ID to search
 *\param    l2addr [OUT]   Pointer to L2 address structure to receive results
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l2_addr_get(
    int unit, 
    opennsl_mac_t mac_addr, 
    opennsl_vlan_t vid, 
    opennsl_l2_addr_t *l2addr) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/** 
 * Callback function used for receiving notification about insertions
 * into and deletions from the L2 table dynamically as they occur. Valid
 * operations are: delete, add, and report. A report with l2addr=NULL
 * indicates a scan completion of the L2 table.
 */
typedef void (*opennsl_l2_addr_callback_t)(
    int unit, 
    opennsl_l2_addr_t *l2addr, 
    int operation, 
    void *userdata);

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Register/Unregister a callback routine for OPENNSL L2 subsystem.
 *
 *\description Register/Unregister a callback routine that will be called
 *          whenever an entry is  added into or deleted from the L2 address
 *          table. Both callback and userdata  must match for register and
 *          unregister calls. If there is l2xmsg_mode=1 in file
 *          config.opennsl, the thread opennslL2MOD.x may be triggered/stopped
 *          when register/unregister  a callback routine.
 *
 *\param    unit [IN]   Unit number.
 *\param    callback [IN]   Callback function of type opennsl_l2_addr_callback_t
 *\param    userdata [IN]   Arbitrary value passed to callback along with messages
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l2_addr_register(
    int unit, 
    opennsl_l2_addr_callback_t callback, 
    void *userdata) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set/Get the age timer.
 *
 *\description Set/Get the age timer of the specified switch unit. Setting the
 *          age_seconds value to 0 disables the age timer. If age_seconds is
 *          other than 0 Every specified interval aging task will iterate over
 *          L2 table entries and do the following:  If the entry is active
 *          (one of the hit bit is set) it will mark the entry as inactive
 *          (clear the hit bit) otherwise it will remove the entry from the
 *          table. Thus if entry with one of the hit bits set added to L2
 *          table and aging interval set to X seconds then the entry should be
 *          expected to completely disappear from L2 table after 2X seconds if
 *          not hit during this period. .
 *
 *\param    unit [IN]   Unit number.
 *\param    age_seconds [IN]   Age timer value in seconds (0 to disable)
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l2_age_timer_set(
    int unit, 
    int age_seconds) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set/Get the age timer.
 *
 *\description Set/Get the age timer of the specified switch unit. Setting the
 *          age_seconds value to 0 disables the age timer. If age_seconds is
 *          other than 0 Every specified interval aging task will iterate over
 *          L2 table entries and do the following:  If the entry is active
 *          (one of the hit bit is set) it will mark the entry as inactive
 *          (clear the hit bit) otherwise it will remove the entry from the
 *          table. Thus if entry with one of the hit bits set added to L2
 *          table and aging interval set to X seconds then the entry should be
 *          expected to completely disappear from L2 table after 2X seconds if
 *          not hit during this period. .
 *
 *\param    unit [IN]   Unit number.
 *\param    age_seconds [OUT]   Age timer value in seconds (0 to disable)
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l2_age_timer_get(
    int unit, 
    int *age_seconds) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

typedef int (*opennsl_l2_traverse_cb)(
    int unit, 
    opennsl_l2_addr_t *info, 
    void *user_data);

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Iterates over all entries in the L2 table and executes user callback
 *       function for each entry.
 *
 *\description Iterates over all valid entries in the L2 table and executes user
 *          provided callback function that defined as following:  typedef int
 *          (*opennsl_l2_traverse_cb)(int unit, opennsl_l2_addr_t *info, void
 *          *user_data); .
 *
 *\param    unit [IN]   Unit number.
 *\param    trav_fn [IN]   Call back function provided by API caller
 *\param    user_data [IN]   Pointer to any data provided by API caller
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l2_traverse(
    int unit, 
    opennsl_l2_traverse_cb trav_fn, 
    void *user_data) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/** L2 Station address info. */
typedef struct opennsl_l2_station_s {
    uint32 flags;               /**< OPENNSL_L2_STATION_xxx flags. */
    opennsl_mac_t dst_mac;      /**< Destination MAC address to match. */
    opennsl_mac_t dst_mac_mask; /**< Destination MAC address mask value. */
} opennsl_l2_station_t;

#define OPENNSL_L2_STATION_WITH_ID  (1 << 0)   /**< Use the specified Station ID. */
#define OPENNSL_L2_STATION_IPV4     (1 << 2)   /**< Subject packets matching this
                                                  entry to L3 processing. */
#define OPENNSL_L2_STATION_IPV6     (1 << 3)   /**< Subject packets matching this
                                                  entry to L3 processing. */
#define OPENNSL_L2_STATION_ARP_RARP (1 << 4)   /**< Subject packets matching this
                                                  entry to ARP/RARP processing. */
/***************************************************************************//** 
 *\brief Initialize L2 Station structure.
 *
 *\description All members of the opennsl_l2_station_t structure are cleared and
 *          initialized to zero.
 *
 *\param    addr [IN,OUT]   Pointer to L2 station structure
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern void opennsl_l2_station_t_init(
    opennsl_l2_station_t *addr) LIB_DLL_EXPORTED ;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Add an entry to L2 Station table.
 *
 *\description Use this API to create an entry in hardware for lookup based on
 *          MAC destination address and VLAN ID. For element-encapsulated
 *          packets, ingress port is used as an endpoint during lookup. To
 *          create an entry with a desired ID, set the ID value in station_id
 *          parameter and set the OPENNSL_L2_STATION_WITH_ID flag bit in flags
 *          structure member variable. If OPENNSL_L2_STATION_WITH_ID flag is
 *          not set, API internally generates an ID and returns this value in
 *          station_id parameter.
 *          The packet termination settings for an entry are specified in the
 *          flags structure member variable.
 *          OPENNSL_L2_STATION_IPV4/IPV6/ARP_RARP/MPLS/MIM/TRILL/FCOE and
 *          OPENNSL_L2_STATION_OAM are allowed termination settings. But
 *          actual support depends on the device capability. OPENNSL_E_UNAVAIL
 *          error will be returned if a device does not support a termination
 *          option.
 *          The entries in TCAM are ordered based on priority value specified
 *          during entry create process. Default priority value is zero after
 *          initializing station variable with opennsl_l2_station_t_init()
 *          API. Application can specify a value different from the default
 *          priority value to manage the order of entries in TCAM. When there
 *          are multiple matches for a packet in TCAM, then termination
 *          settings from the highest priority rule will take effect. So,
 *          application must intelligently manage entries that have same data
 *          value but different mask values.
 *
 *\param    unit [IN]   Unit number.
 *\param    station_id [IN,OUT]   Station ID
 *\param    station [IN]   Station ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l2_station_add(
    int unit, 
    int *station_id, 
    opennsl_l2_station_t *station) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete an entry from L2 Station Table.
 *
 *\description Delete an entry from L2 station table with specified Station ID.
 *
 *\param    unit [IN]   Unit number.
 *\param    station_id [IN]   L2 station ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l2_station_delete(
    int unit, 
    int station_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get L2 station entry details from Station Table.
 *
 *\description Get L2 station entry details from Station Table.
 *
 *\param    unit [IN]   Unit number.
 *\param    station_id [IN]   L2 station ID
 *\param    station [OUT]   L2 station ID
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_l2_station_get(
    int unit, 
    int station_id, 
    opennsl_l2_station_t *station) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#endif /* __OPENNSL_L2_H__ */
/*@}*/
