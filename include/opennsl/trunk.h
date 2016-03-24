/** \addtogroup trunk Trunking APIs
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
 * \file			trunk.h
 ******************************************************************************/

#ifndef __OPENNSL_TRUNK_H__
#define __OPENNSL_TRUNK_H__

#include <opennsl/types.h>

#define OPENNSL_TRUNK_MAX_PORTCNT   256        /**< Maximum number of ports in a
                                                  trunk group */
#define OPENNSL_TRUNK_UNSPEC_INDEX  -1         /**< Let software set DLF/MC/IPMC. */
#define OPENNSL_TRUNK_PSC_SRCDSTMAC 3          /**< Source+dest MAC address. */
#define OPENNSL_TRUNK_PSC_DSTIP     5          /**< Destination IP address. */
#define OPENNSL_TRUNK_PSC_SRCDSTIP  6          /**< Source+dest IP address. */
#define OPENNSL_TRUNK_PSC_PORTFLOW  9          /**< Enhanced hashing. */
#define OPENNSL_TRUNK_FLAG_FAILOVER_NEXT    0x0001     /**< Failover port defaults
                                                          to the next port in
                                                          the trunk port list. */
#define OPENNSL_TRUNK_FLAG_FAILOVER_NEXT_LOCAL 0x0002     /**< Failover port defaults
                                                          to the next local port
                                                          in the trunk port
                                                          list, if any. */
#define OPENNSL_TRUNK_FLAG_FAILOVER         OPENNSL_TRUNK_FLAG_FAILOVER_NEXT_LOCAL /**< Enable trunk failover
                                                          support (deprecated). */
#define OPENNSL_TRUNK_FLAG_WITH_ID          0x0010     /**< Use the trunk ID
                                                          supplied by user. */
#define OPENNSL_TRUNK_FLAG_IPMC_CLEAVE      0x0020     /**< Disable trunk
                                                          resolution for IPMC
                                                          packets in hardware. */
#define OPENNSL_TRUNK_MEMBER_EGRESS_DISABLE 0x0002     /**< Member will not be a
                                                          part of the
                                                          distributor members to
                                                          be hashed. */
/** Trunk group attributes structure. */
typedef struct opennsl_trunk_info_s {
    int psc;            /**< Port selection criteria. */
    int dlf_index;      /**< DLF/broadcast port for trunk group. */
    int mc_index;       /**< Multicast port for trunk group. */
    int ipmc_index;     /**< IPMC port for trunk group. */
} opennsl_trunk_info_t;

/** Initialize a trunk chip information structure. */
typedef struct opennsl_trunk_chip_info_s {
    int trunk_group_count;      /**< Total number of (front panel) trunk groups. */
    int trunk_id_min;           /**< Minimum (front panel) trunk ID number. */
    int trunk_id_max;           /**< Maximum (front panel) trunk ID number. */
    int trunk_ports_max;        /**< Maximum number of ports per (front panel)
                                   trunk group. */
    int trunk_fabric_id_min;    /**< Minimum fabric trunk ID number. */
    int trunk_fabric_id_max;    /**< Maximum fabric trunk ID number. */
    int trunk_fabric_ports_max; /**< Maximum number of ports per fabric trunk
                                   group. */
    int vp_id_min;              /**< Minimum virtual port trunk ID number. */
    int vp_id_max;              /**< Maximum virtual port trunk ID number. */
    int vp_ports_max;           /**< Maximum number of virtual ports per virtual
                                   port trunk group. */
} opennsl_trunk_chip_info_t;

/** Structure describing a trunk member. */
typedef struct opennsl_trunk_member_s {
    uint32 flags;           /**< OPENNSL_TRUNK_MEMBER_xxx */
    opennsl_gport_t gport;  /**< Trunk member GPORT ID. */
    int reserved1; 
    int reserved2; 
} opennsl_trunk_member_t;

/***************************************************************************//** 
 *\brief Initializes the opennsl_trunk_info_t structure.
 *
 *\description Initializes the opennsl_trunk_info_t structure.
 *
 *\param    trunk_info [IN,OUT]   Pointer to trunk info structure (see
 *          =opennsl_trunk_info_t).
 *
 *\returns  Nothing
 ******************************************************************************/
extern void opennsl_trunk_info_t_init(
    opennsl_trunk_info_t *trunk_info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Initializes the opennsl_trunk_member_t structure.
 *
 *\description Initializes the opennsl_trunk_member_t structure.
 *
 *\param    trunk_member [IN,OUT]   Pointer to trunk member structure (see
 *          =opennsl_trunk_member_t).
 *
 *\returns  Nothing
 ******************************************************************************/
extern void opennsl_trunk_member_t_init(
    opennsl_trunk_member_t *trunk_member) LIB_DLL_EXPORTED ;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Initialize the trunk module and SoC trunk hardware.
 *
 *\description Initialize the trunk module. The SoC hardware and the software
 *          data structure are both set to their initialized states (no trunks
 *          configured). .
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_XXX Other possible errors; for details, see
 ******************************************************************************/
extern int opennsl_trunk_init(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Shut down (uninitialize) the trunk module.
 *
 *\description Shut down (uninitializes) the trunk module. Frees up any memory
 *          previously allocated to the trunk module.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_NONE Success
 ******************************************************************************/
extern int opennsl_trunk_detach(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Create the software data structure for a new trunk, using
 *       caller-specified or next available trunk ID.
 *
 *\description To create a front-panel trunk group, the
 *          OPENNSL_TRUNK_FLAG_WITH_ID flag may be set. If the
 *          OPENNSL_TRUNK_FLAG_WITH_ID flag is set, the caller-specified trunk
 *          ID must be within the range specified by the members trunk_id_min
 *          and trunk_id_max of the opennsl_trunk_chip_info_t structure,
 *          returned by.
 *
 *\param    unit [IN]   Unit number.
 *\param    flags [IN]   OPENNSL_TRUNK_FLAG_*
 *\param    tid [IN,OUT]   Pointer to caller-specified trunk ID if
 *          OPENNSL_TRUNK_FLAG_WITH_ID is set, else pointer to next available
 *          trunk ID.
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_INIT Trunk module has not been initialized
 *\retval    OPENNSL_E_BADID Invalid or unsupported trunk ID
 *\retval    OPENNSL_E_EXISTS Specified trunk ID is already in use
 *\retval    OPENNSL_E_FULL No available trunk IDs
 *\retval    OPENNSL_E_XXX Other possible errors; for details, see
 ******************************************************************************/
extern int opennsl_trunk_create(
    int unit, 
    uint32 flags, 
    opennsl_trunk_t *tid) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set a trunk's Port Selection Criteria (PSC).
 *
 *\description Set a trunk's Port Selection Criteria (PSC). Assigns a particular
 *          load balancing algorithm to the specified trunk.
 *
 *\param    unit [IN]   Unit number.
 *\param    tid [IN]   Trunk ID.
 *\param    psc [IN]   PSC to apply to specified trunk (see =PSC_macros).
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_INIT Trunk module has not been initialized
 *\retval    OPENNSL_E_BADID Invalid or unsupported trunk ID
 *\retval    OPENNSL_E_NOT_FOUND Specified trunk ID is not currently defined
 *\retval    OPENNSL_E_XXX Other possible errors; for details, see
 ******************************************************************************/
extern int opennsl_trunk_psc_set(
    int unit, 
    opennsl_trunk_t tid, 
    int psc) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Gets the underlying SoC device's trunk support limits.
 *
 *\description Gets the underlying SoC device's trunk support limits. These
 *          include such data as maximum number of trunks supported and
 *          maximum number of ports per trunk.
 *
 *\param    unit [IN]   Unit number.
 *\param    ta_info [OUT]   Pointer to returned chip info structure (see
 *          =opennsl_trunk_chip_info_t).
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_INIT Trunk module has not been initialized
 ******************************************************************************/
extern int opennsl_trunk_chip_info_get(
    int unit, 
    opennsl_trunk_chip_info_t *ta_info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the current attributes and member ports for the specified trunk
 *       group.
 *
 *\description Fills in the caller-allocated trunk_info structure with the
 *          current attributes of the specified trunk group. Fill in the
 *          caller-allocated member_array with the current member list. If
 *          member_max is zero and member_array is NULL, the number of members
 *          in the given trunk group is returned in member_count.
 *
 *\param    unit [IN]   Unit number.
 *\param    tid [IN]   Trunk ID.
 *\param    t_data [OUT]
 *\param    member_max [IN]   Maximum number of members in provided member_array.
 *\param    member_array [OUT]   Member list.
 *\param    member_count [OUT]   Number of members returned in member_array.
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_INIT Trunk module has not been initialized
 *\retval    OPENNSL_E_BADID Invalid or unsupported trunk ID
 *\retval    OPENNSL_E_NOT_FOUND Specified trunk ID is not currently defined
 *\retval    OPENNSL_E_XXX Other possible errors; for details, see
 ******************************************************************************/
extern int opennsl_trunk_get(
    int unit, 
    opennsl_trunk_t tid, 
    opennsl_trunk_info_t *t_data, 
    int member_max, 
    opennsl_trunk_member_t *member_array, 
    int *member_count) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Specify the ports in a trunk group.
 *
 *\description Configure the set of ports in a trunk group. The specified trunk
 *          ID must be one returned from =opennsl_trunk_create . If the trunk
 *          already has member ports, they will be replaced by the new list of
 *          ports contained in the member_array.
 *
 *\param    unit [IN]   Unit number.
 *\param    tid [IN]   Trunk ID
 *\param    trunk_info [IN]   Pointer to trunk info structure (see
 *          =opennsl_trunk_info_t)
 *\param    member_count [IN]   Number of members in member_array.
 *\param    member_array [IN]   Member list.
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_INIT Trunk module has not been initialized
 *\retval    OPENNSL_E_BADID Invalid or unsupported trunk ID, port or PSC
 *\retval    OPENNSL_E_NOT_FOUND Specified trunk ID is not currently defined
 *\retval    OPENNSL_E_PARAM Invalid number of member ports specified
 *\retval    OPENNSL_E_XXX Other possible errors; for details, see
 ******************************************************************************/
extern int opennsl_trunk_set(
    int unit, 
    opennsl_trunk_t tid, 
    opennsl_trunk_info_t *trunk_info, 
    int member_count, 
    opennsl_trunk_member_t *member_array) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Removes a trunk group.
 *
 *\description Removes all current trunk member ports from the trunk group and
 *          marks the trunk ID as invalid (available for reuse).
 *
 *\param    unit [IN]   Unit number.
 *\param    tid [IN]   Trunk ID.
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_INIT Trunk module has not been initialized
 *\retval    OPENNSL_E_BADID Invalid or unsupported trunk ID
 *\retval    OPENNSL_E_NOT_FOUND Specified trunk ID is not currently defined
 *\retval    OPENNSL_E_XXX Other possible errors; for details, see
 ******************************************************************************/
extern int opennsl_trunk_destroy(
    int unit, 
    opennsl_trunk_t tid) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Get the trunk group ID for a given system port, specified by Module ID
 *       and Port number.
 *
 *\description Retrieve the trunk group ID for a given system port, specified by
 *          its Module ID and Port number.
 *
 *\param    unit [IN]   Unit number.
 *\param    modid [IN]   Module ID
 *\param    port [IN]   Port ID.
 *\param    tid [OUT]   Trunk ID
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_UNAVAIL Feature not supported by the SoC hardware
 *\retval    OPENNSL_E_INIT Trunk module has not been initialized
 *\retval    OPENNSL_E_BADID Invalid or unsupported Module ID or Port number
 *\retval    OPENNSL_E_NOT_FOUND Trunk ID not found
 *\retval    OPENNSL_E_XXX Other possible errors; for details, see
 ******************************************************************************/
extern int opennsl_trunk_find(
    int unit, 
    opennsl_module_t modid, 
    opennsl_port_t port, 
    opennsl_trunk_t *tid) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Assign the failover port list for a specific trunk port.
 *
 *\description Configure the set of failover ports for a specific port in the
 *          indicated trunk group.  For fabric trunks, all of the ports in the
 *          list must be HiGig ports on the local device.  For non-fabric
 *          trunks, the failover ports may be on remote devices.  If a flag is
 *          provided, then the count and fail_to_array argument are ignored;
 *          the failover port list is constructed from the trunk port
 *          membership according to the selected failover description.  (If a
 *          OPENNSL_TRUNK_FLAG_FAILOVER_XXX flag is provided to
 *          =opennsl_trunk_set in the trunk_info structure, all of the local
 *          ports in the trunk will be configured for failover in the selected
 *          method.) If the flags argument is zero, then the port list from
 *          count and fail_to_array is used.  This arbitrary list may include
 *          ports outside of the trunk.  A count of zero indicates that
 *          failover should be disabled on failport.
 *
 *\param    unit [IN]   Unit number.
 *\param    tid [IN]   Trunk ID.
 *\param    failport [IN]   Port in trunk for which to specify failover port list.
 *\param    psc [IN]   Port selection criteria for failover port list.
 *\param    flags [IN]   OPENNSL_TRUNK_FLAG_FAILOVER_xxx.
 *\param    count [IN]   Number of ports in failover port list.
 *\param    fail_to_array [IN]   Failover port list.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_trunk_failover_set(
    int unit, 
    opennsl_trunk_t tid, 
    opennsl_gport_t failport, 
    int psc, 
    uint32 flags, 
    int count, 
    opennsl_gport_t *fail_to_array) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Retrieve the failover port list for a specific trunk port.
 *
 *\description Retrieve the configured set of failover ports for a specific port
 *          in the indicated trunk group. If a flag was provided to configure
 *          the failover list, then only the flag and psc return values are
 *          valid.  If the returned flags argument is zero, then fail_to_array
 *          is filled with the port list up to a maximum list length of
 *          array_size.  array_count contains the actual length of the
 *          returned list.  If array_count is zero in addition to flags, trunk
 *          failover is not enabled on failport.
 *
 *\param    unit [IN]   Unit number.
 *\param    tid [IN]   Trunk ID.
 *\param    failport [IN]   Port in trunk for which to retrieve failover port
 *          list.
 *\param    psc [OUT]   Port selection criteria for failover port list.
 *\param    flags [OUT]   OPENNSL_TRUNK_FLAG_FAILOVER_xxx.
 *\param    array_size [IN]   Maximum number of ports in provided failover port
 *          list.
 *\param    fail_to_array [OUT]   Failover port list.
 *\param    array_count [OUT]   Number of ports in returned failover port list.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_trunk_failover_get(
    int unit, 
    opennsl_trunk_t tid, 
    opennsl_gport_t failport, 
    int *psc, 
    uint32 *flags, 
    int array_size, 
    opennsl_gport_t *fail_to_array, 
    int *array_count) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Add a member to a trunk group.
 *
 *\description This API is used to add a member to a trunk group. The specified
 *          trunk group must be one returned from =opennsl_trunk_create . If
 *          the trunk already has members, they will be retained.
 *          A membmer should not be added to different trunk groups, which
 *          must be  guaranteed by the applications.
 *
 *\param    unit [IN]   Unit number.
 *\param    tid [IN]   Trunk ID.
 *\param    member [IN]   Trunk member to add.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_trunk_member_add(
    int unit, 
    opennsl_trunk_t tid, 
    opennsl_trunk_member_t *member) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete a member from a trunk group.
 *
 *\description Delete a member from a trunk group. The specified trunk group must
 *          be one returned from =opennsl_trunk_create .
 *
 *\param    unit [IN]   Unit number.
 *\param    tid [IN]   Trunk ID.
 *\param    member [IN]   Trunk member to delete.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_trunk_member_delete(
    int unit, 
    opennsl_trunk_t tid, 
    opennsl_trunk_member_t *member) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#include <opennsl/trunkX.h>
#endif /* __OPENNSL_TRUNK_H__ */
/*@}*/
