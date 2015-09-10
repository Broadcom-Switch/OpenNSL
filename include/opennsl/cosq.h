/** \addtogroup cosq Class of Service Queue Configuration
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
 * \file			cosq.h
 ******************************************************************************/

#ifndef __OPENNSL_COSQ_H__
#define __OPENNSL_COSQ_H__

#include <opennsl/types.h>

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Get or set the mapping from internal priority to CoS queue.
 *
 *\description Configure or retrieve the mapping from the internal priority value
 *          to Cos Queue. The internal priority is usually initialized from
 *          the packet priority.  For tagged packets the priority is extracted
 *          from the PRI field of the tag. For untagged packets, the priority
 *          is specified using the API =opennsl_port_untagged_priority_set .
 *          On some devices, the mapping tables may be shared among several
 *          ports, so setting one port's mappings may affect other ports'.
 *          On some devices, packets directed to the CPU interface port may
 *          have their priority assigned independent of this setting. For more
 *          information see =opennsl_switch_control_set .
 *          On some devices, a port value of -1 or gport type for system
 *          configuration will configure all ports.
 *          Some devices support Enhanced Transmission Selection (ETS) which
 *          requires to use GPORT ID for the port argument. When the ETS mode
 *          is enabled, they configure and retrive the mapping from the
 *          internal priority to the offset (which is equal to the value of
 *          cosq) of the unicast queues and multicast queues attached to the
 *          egress port.
 *          Most devices have 8 internal priorities (0 to 7).
 *
 *\param    unit [IN]   Unit number.
 *\param    priority [IN]   internal priority to map
 *\param    cosq [IN]   Cos queue to which to map the chosen priority
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_PARAM Invalid priority, or device not configured for the
 *          number of CoS queues specified.
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_mapping_set(
    int unit, 
    opennsl_cos_t priority, 
    opennsl_cos_queue_t cosq) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set the mapping from internal priority to CoS queue.
 *
 *\description Configure or retrieve the mapping from the internal priority value
 *          to Cos Queue. The internal priority is usually initialized from
 *          the packet priority.  For tagged packets the priority is extracted
 *          from the PRI field of the tag. For untagged packets, the priority
 *          is specified using the API =opennsl_port_untagged_priority_set .
 *          On some devices, the mapping tables may be shared among several
 *          ports, so setting one port's mappings may affect other ports'.
 *          On some devices, packets directed to the CPU interface port may
 *          have their priority assigned independent of this setting. For more
 *          information see =opennsl_switch_control_set .
 *          On some devices, a port value of -1 or gport type for system
 *          configuration will configure all ports.
 *          Some devices support Enhanced Transmission Selection (ETS) which
 *          requires to use GPORT ID for the port argument. When the ETS mode
 *          is enabled, they configure and retrive the mapping from the
 *          internal priority to the offset (which is equal to the value of
 *          cosq) of the unicast queues and multicast queues attached to the
 *          egress port.
 *          Most devices have 8 internal priorities (0 to 7).
 *
 *\param    unit [IN]   Unit number.
 *\param    priority [IN]   internal priority to map
 *\param    cosq [OUT]   Cos queue to which to map the chosen priority
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_PARAM Invalid priority, or device not configured for the
 *          number of CoS queues specified.
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_mapping_get(
    int unit, 
    opennsl_cos_t priority, 
    opennsl_cos_queue_t *cosq) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/** BST Tracing statistics resources type eumerations. */
typedef enum opennsl_bst_stat_id_e {
    opennslBstStatIdDevice = 0,         /**< Per device BST tracing resource */
    opennslBstStatIdEgrPool = 1,        /**< Per Egress Pool BST tracing resource */
    opennslBstStatIdEgrMCastPool = 2,   /**< Per Egress Pool BST tracing
                                           resource(Multicast) */
    opennslBstStatIdIngPool = 3,        /**< Per Ingress Pool BST tracing resource */
    opennslBstStatIdPortPool = 4,       /**< Per Port Pool BST tracing resource */
    opennslBstStatIdPriGroupShared = 5, /**< Per Shared Priority Group Pool BST
                                           tracing resource */
    opennslBstStatIdPriGroupHeadroom = 6, /**< Per Priority Group Headroom BST
                                           tracing resource */
    opennslBstStatIdUcast = 7,          /**< BST Tracing resource for unicast */
    opennslBstStatIdMcast = 8,          /**< BST Tracing resource for multicast */
    opennslBstStatIdHeadroomPool = 9,   /**< BST Tracing the Headroom Pool Usage
                                           Count */
    opennslBstStatIdEgrUCastPortShared = 10, /**< BST Tracing resource UC per egress
                                           port SP */
    opennslBstStatIdEgrPortShared = 11, /**< BST Tracing resource per egress port
                                           SP */
    opennslBstStatIdRQEQueue = 12,      /**< BST Tracing resource per RQE queue */
    opennslBstStatIdRQEPool = 13,       /**< BST tracing resource per RQE Pool */
    opennslBstStatIdUcastGroup = 14,    /**< BST Tracing resource per Ucast queue
                                           group */
    opennslBstStatIdCpuQueue = 15,      /**< BST Tracking resource per CPU queue */
    opennslBstStatIdMaxCount = 16       /**< Must be the last. Not a usable value. */
} opennsl_bst_stat_id_t;

typedef struct opennsl_cosq_bst_profile_s {
    uint32 byte;    
} opennsl_cosq_bst_profile_t;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Set/Get the BST profile for CosQ objects.
 *
 *\description Configure or retrieve the BST (buffer statistics tracking)
 *          configuration for the specified MMU resource. MMU resource is
 *          identified by the combination of port, cosq and bid parameters.
 *          port parameter can be port gport, queue gport. bid parameter
 *          identifies the MMU resource, for instance the bid
 *          opennslBstStatIdEgrPool identifies the egress service pool
 *          resource. cosq parameter identifies the object withing the various
 *          instances of resources within the identified resource. Note: For
 *          bid=opennslBstStatIdHeadroomPool, returns OPENNSL_E_PARAM as there
 *          is no BST configuration required for Headroom Pool
 *          The bid parameter can be one of the following from the table.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]
 *\param    cosq [IN]   Cosq object offset identifier
 *\param    bid [IN]   BST stat ID to identify the COSQ resource/object
 *\param    profile [IN]   BST profile configuration
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_bst_profile_set(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_queue_t cosq, 
    opennsl_bst_stat_id_t bid, 
    opennsl_cosq_bst_profile_t *profile) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set/Get the BST profile for CosQ objects.
 *
 *\description Configure or retrieve the BST (buffer statistics tracking)
 *          configuration for the specified MMU resource. MMU resource is
 *          identified by the combination of port, cosq and bid parameters.
 *          port parameter can be port gport, queue gport. bid parameter
 *          identifies the MMU resource, for instance the bid
 *          opennslBstStatIdEgrPool identifies the egress service pool
 *          resource. cosq parameter identifies the object withing the various
 *          instances of resources within the identified resource. Note: For
 *          bid=opennslBstStatIdHeadroomPool, returns OPENNSL_E_PARAM as there
 *          is no BST configuration required for Headroom Pool
 *          The bid parameter can be one of the following from the table.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]
 *\param    cosq [IN]   Cosq object offset identifier
 *\param    bid [IN]   BST stat ID to identify the COSQ resource/object
 *\param    profile [OUT]   BST profile configuration
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_bst_profile_get(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_queue_t cosq, 
    opennsl_bst_stat_id_t bid, 
    opennsl_cosq_bst_profile_t *profile) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Sync the HW stats value to SW copy for all or given BST resource.
 *
 *\description API to sync the Hardware stats for all or given BST resources to
 *          the Software copy. During this sync, BST status will be disabled,
 *          in order to maintain consistency of the stats to a defined time
 *          and Post sync, the BST status will be restored. This is required
 *          to be used before calling bst_stat_get() to get latest or updated
 *          stats value.
 *
 *\param    unit [IN]   Unit number.
 *\param    bid [IN]   BST stat ID to identify the COSQ resource/object
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_bst_stat_sync(
    int unit, 
    opennsl_bst_stat_id_t bid) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Clear the current statistic/count of specified BST profile.
 *
 *\description Clear the BST (buffer statistics tracking) statistic for the
 *          specified MMU resource. MMU resource is identified by the
 *          combination of port, cosq and bid parameters. port parameter can
 *          be port gport, queue gport. bid parameter identifies the MMU
 *          resource, for instance the bid opennslBstStatIdEgrPool identifies
 *          the egress service pool resource. cosq parameter identifies the
 *          object withing the various instances of resources within the
 *          identified resource.  gport value of -1 will clear stats on all
 *          ports.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   Device or logical port or GPORT ID
 *\param    cosq [IN]   Cosq object offset identifier
 *\param    bid [IN]   BST stat ID to identify the COSQ resource/object
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_bst_stat_clear(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_queue_t cosq, 
    opennsl_bst_stat_id_t bid) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the current statistic/count of specified BST profile.
 *
 *\description Retrieve the BST (buffer statistics tracking) statistic for the
 *          specified MMU resource. MMU resource is identified by the
 *          combination of port, cosq and bid parameters. port parameter can
 *          be port gport, queue gport. bid parameter identifies the MMU
 *          resource, for instance the flag opennslBstStatIdEgrPool identifies
 *          the egress service pool resource. cosq parameter identifies the
 *          object withing the various instances of resources within the
 *          identified resource. if option  OPENNSL_COSQ_STAT_CLEAR is
 *          present, a memory/register clear will be performed after stat
 *          reading. .
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]
 *\param    cosq [IN]   Cosq object offset identifier
 *\param    bid [IN]   BST stat ID to identify the COSQ resource/object
 *\param    options [IN]   options to perform clear-on-read
 *\param    value [OUT]
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_bst_stat_get(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_queue_t cosq, 
    opennsl_bst_stat_id_t bid, 
    uint32 options, 
    uint64 *value) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the current statistic/count of multiple specified BST profile.
 *
 *\description Retrieve the BST (buffer statistics tracking) statistic for
 *          multiple  specified MMU resource. MMU resource is identified by
 *          the combination of port, cosq and bid parameters. port parameter
 *          can be port gport, queue gport. bid parameter identifies the MMU
 *          resource, for instance the flag opennslBstStatIdEgrPool identifies
 *          the egress service pool resource. cosq parameter identifies the
 *          object withing the various instances of resources within the
 *          identified resource. if option  OPENNSL_COSQ_STAT_CLEAR is
 *          present, a memory/register clear will be performed after stat
 *          reading. .
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   Device or logical port or GPORT ID
 *\param    cosq [IN]   Cosq object offset identifier
 *\param    options [IN]   options to perform clear-on-read
 *\param    max_values [IN]   Number of elements in id_list and pvalue
 *\param    id_list [IN]   Array of BST stat ID list to identify the COSQ
 *          resource/object
 *\param    values [OUT]
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_bst_stat_multi_get(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_queue_t cosq, 
    uint32 options, 
    int max_values, 
    opennsl_bst_stat_id_t *id_list, 
    uint64 *values) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#endif /* __OPENNSL_COSQ_H__ */
/*@}*/
