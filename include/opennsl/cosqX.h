/** \addtogroup cosq Class of Service Queue Configuration
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
 * \file			cosqX.h
 ******************************************************************************/

#ifndef __OPENNSL_COSQX_H__
#define __OPENNSL_COSQX_H__

#include <opennsl/types.h>
#include <opennsl/switch.h>
#include <shared/port.h>

/***************************************************************************//** 
 *\brief Initialize the CoSQ subsystem.
 *
 *\description Initialize the CoSQ configuration and scheduling module.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_init(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief De-initialize the CoSQ subsystem.
 *
 *\description De-initialize the CoSQ and scheduling for the specified unit. Any
 *          held resources associated with the module are released.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_detach(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure the number of Class of Service Queues (COSQs).
 *
 *\description Configure or retrieve the number of CoS queues. Different devices
 *          support different numbers of queues.  1, 2, 4 or 8 class CoS
 *          queues may be configured depending on the underlying device.
 *          Configuring the number of CoS queues affects the configuration and
 *          utilization of several internal resources in the device.
 *          opennsl_cosq_config_set configures the device to operate properly
 *          for the number of CoS Queues. The CPU CoS queue mapping is also
 *          reconfigured to adjust for the numq. For more information
 *          regarding user defined CPU CoS queue mappings see
 *          =opennsl_rx_cosq_mapping_set .
 *          After configuration of the number of CoS Queues, the application
 *          must call =opennsl_cosq_mapping_set to map the packet priorities
 *          into the desired CoS queues. opennsl_cosq_config_set configures
 *          the mapping to be functional but the priority to CoS Queue mapping
 *          is not defined.
 *          The number of CoS queues must be configured during system
 *          initialization. It is invalid to configure the CoS queues on a
 *          system with traffic flowing. The API does not check for this
 *          condition and the results are undefined if it occurs.
 *          On the chip network switch the default number of CoS queues is 8.
 *
 *\param    unit [IN]   Unit number.
 *\param    numq [IN]   Number of Class of Service Queues
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_UNAVAIL Requested number of CoS queues not supported on this
 *          device.
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_config_set(
    int unit, 
    int numq) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure the number of Class of Service Queues (COSQs).
 *
 *\description Configure or retrieve the number of CoS queues. Different devices
 *          support different numbers of queues.  1, 2, 4 or 8 class CoS
 *          queues may be configured depending on the underlying device.
 *          Configuring the number of CoS queues affects the configuration and
 *          utilization of several internal resources in the device.
 *          opennsl_cosq_config_set configures the device to operate properly
 *          for the number of CoS Queues. The CPU CoS queue mapping is also
 *          reconfigured to adjust for the numq. For more information
 *          regarding user defined CPU CoS queue mappings see
 *          =opennsl_rx_cosq_mapping_set .
 *          After configuration of the number of CoS Queues, the application
 *          must call =opennsl_cosq_mapping_set to map the packet priorities
 *          into the desired CoS queues. opennsl_cosq_config_set configures
 *          the mapping to be functional but the priority to CoS Queue mapping
 *          is not defined.
 *          The number of CoS queues must be configured during system
 *          initialization. It is invalid to configure the CoS queues on a
 *          system with traffic flowing. The API does not check for this
 *          condition and the results are undefined if it occurs.
 *          On the chip network switch the default number of CoS queues is 8.
 *
 *\param    unit [IN]   Unit number.
 *\param    numq [OUT]   Number of Class of Service Queues
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_UNAVAIL Requested number of CoS queues not supported on this
 *          device.
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_config_get(
    int unit, 
    int *numq) LIB_DLL_EXPORTED ;

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
 *\param    port [IN]   Device or logical port or GPORT ID
 *\param    priority [IN]   internal priority to map
 *\param    cosq [IN]   Cos queue to which to map the chosen priority
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_PARAM Invalid priority, or device not configured for the
 *          number of CoS queues specified.
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_port_mapping_set(
    int unit, 
    opennsl_port_t port, 
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
 *\param    port [IN]   Device or logical port or GPORT ID
 *\param    priority [IN]   internal priority to map
 *\param    cosq [OUT]   Cos queue to which to map the chosen priority
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_PARAM Invalid priority, or device not configured for the
 *          number of CoS queues specified.
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_port_mapping_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_cos_t priority, 
    opennsl_cos_queue_t *cosq) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set the mapping of multiple internal priorities to their
 *       corresponding CoS queues.
 *
 *\description Configure or retrieve the mapping of multiple internal priority
 *          value to their corresponding  Cos Queue. The internal priority is
 *          usually initialized from the packet priority.  For tagged packets
 *          the priority is extracted from the PRI field of the tag. For
 *          untagged packets, the priority is specified using the API
 *          =opennsl_port_untagged_priority_set .
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
 *\param    port [IN]   Device or logical port or GPORT ID
 *\param    count [IN]   number of elements in priority array and cosq array in
 *          case of multi get or set
 *\param    priority_array [IN]   array of internal priority to map
 *\param    cosq_array [IN]   array of Cos queue where each element of cosq_array
 *          (cos) corresponds to the respective element of priority_array
 *          (internal priority)
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_PARAM Invalid priority, or device not configured for the
 *          number of CoS queues specified.
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_port_mapping_multi_set(
    int unit, 
    opennsl_port_t port, 
    int count, 
    opennsl_cos_t *priority_array, 
    opennsl_cos_queue_t *cosq_array) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set the mapping of multiple internal priorities to their
 *       corresponding CoS queues.
 *
 *\description Configure or retrieve the mapping of multiple internal priority
 *          value to their corresponding  Cos Queue. The internal priority is
 *          usually initialized from the packet priority.  For tagged packets
 *          the priority is extracted from the PRI field of the tag. For
 *          untagged packets, the priority is specified using the API
 *          =opennsl_port_untagged_priority_set .
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
 *\param    port [IN]   Device or logical port or GPORT ID
 *\param    count [IN]   number of elements in priority array and cosq array in
 *          case of multi get or set
 *\param    priority_array [IN]   array of internal priority to map
 *\param    cosq_array [OUT]   array of Cos queue where each element of cosq_array
 *          (cos) corresponds to the respective element of priority_array
 *          (internal priority)
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_PARAM Invalid priority, or device not configured for the
 *          number of CoS queues specified.
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_port_mapping_multi_get(
    int unit, 
    opennsl_port_t port, 
    int count, 
    opennsl_cos_t *priority_array, 
    opennsl_cos_queue_t *cosq_array) LIB_DLL_EXPORTED ;

#define OPENNSL_COSQ_NONE                   0x0        /**< Pass through. */
#define OPENNSL_COSQ_STRICT                 0x01       /**< Weights are ignored. */
#define OPENNSL_COSQ_ROUND_ROBIN            0x02       /**< Weights are ignored. */
#define OPENNSL_COSQ_WEIGHTED_ROUND_ROBIN   0x03       
#define OPENNSL_COSQ_WEIGHTED_FAIR_QUEUING  0x04       
#define OPENNSL_COSQ_DEFICIT_ROUND_ROBIN    0x05       /**< XGS3 only. */
#define OPENNSL_COSQ_SP0                    0x0C       /**< Strict priority level
                                                          0. */
#define OPENNSL_COSQ_SP1                    0x0D       /**< Strict priority level
                                                          1. */
#define OPENNSL_COSQ_WEIGHT_UNLIMITED   -1         
#define OPENNSL_COSQ_WEIGHT_STRICT      0          
#define OPENNSL_COSQ_WEIGHT_MIN         1          
#define OPENNSL_COSQ_PRIO_VALID(prio)  ((prio) >= 0 && (prio < 8)) 
#define OPENNSL_COSQ_QUEUE_VALID(unit, numq)  \
    ((numq) >= 0 && (numq) < NUM_COS(unit)) 
/***************************************************************************//** 
 *\brief Get or set Class of Service policy, weights and delay.
 *
 *\description Configure or retrieve the Class of Service policy, weights, and
 *          delay for a device or port.  The mode options are listed in the
 *          table below.  For modes which use weights, the weights may range
 *          between OPENNSL_COSQ_WEIGHT_MIN and the value of weight_max
 *          returned by =opennsl_cosq_sched_weight_max_get for the mode. If
 *          weight_max = OPENNSL_COSQ_WEIGHT_UNLIMITED, then any positive
 *          weight is acceptable.  In OPENNSL_COSQ_BOUNDED_DELAY mode, a
 *          negative value for an element of the weight array indicates that
 *          the weight and delay value for that Class of Service should remain
 *          unchanged, while the non-negative elements of the weight array are
 *          updated and assigned the given delay value. For modes which use
 *          weights, OPENNSL_COSQ_WEIGHT_STRICT may be supplied for some of
 *          the weights, indicating these queues should behave as in strict
 *          priority mode. On the chips network switch, the queues in strict
 *          priority mode must be in consecutive order. The chips network
 *          switch does not support the scheduling modes
 *          OPENNSL_COSQ_WEIGHTED_FAIR_QUEUING and OPENNSL_COSQ_BOUNDED_DELAY.
 *          Note: In all devices supporting Enhanced Transmission Selection
 *          (ETS) hierarchical scheduling, opennsl_cosq_sched_set and
 *          opennsl_cosq_sched_get API is used to configure and retrieve the
 *          Class of Service policy, weights, and delay for CPU(CMIC) port
 *          only.
 *
 *\param    unit [IN]   Unit number.
 *\param    mode [IN]   Scheduling mode, see table =OPENNSL_COSQ_table
 *\param    weights [IN]   Array of relative weights indexed by CoS queue. Use
 *          depends on the selected mode.  See =OPENNSL_COSQ_COMBO . Note: Be
 *          aware that despite of OPENNSL_COS_COUNT is 8, it supports up to 10
 *          weights arrays in network switch devices if and only if
 *          opennsl_num_cos=10 is configured.
 *\param    delay [IN]   Used only if scheduling algorithm is
 *          OPENNSL_COSQ_BOUNDED_DELAY to indicate the maximum amount of time
 *          before returning to the highest priority CoS queue.  This value is
 *          only used for non-negative elements of the weights array.
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_cosq_sched_set(
    int unit, 
    int mode, 
    const int weights[OPENNSL_COS_COUNT], 
    int delay) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set Class of Service policy, weights and delay.
 *
 *\description Configure or retrieve the Class of Service policy, weights, and
 *          delay for a device or port.  The mode options are listed in the
 *          table below.  For modes which use weights, the weights may range
 *          between OPENNSL_COSQ_WEIGHT_MIN and the value of weight_max
 *          returned by =opennsl_cosq_sched_weight_max_get for the mode. If
 *          weight_max = OPENNSL_COSQ_WEIGHT_UNLIMITED, then any positive
 *          weight is acceptable.  In OPENNSL_COSQ_BOUNDED_DELAY mode, a
 *          negative value for an element of the weight array indicates that
 *          the weight and delay value for that Class of Service should remain
 *          unchanged, while the non-negative elements of the weight array are
 *          updated and assigned the given delay value. For modes which use
 *          weights, OPENNSL_COSQ_WEIGHT_STRICT may be supplied for some of
 *          the weights, indicating these queues should behave as in strict
 *          priority mode. On the chips network switch, the queues in strict
 *          priority mode must be in consecutive order. The chips network
 *          switch does not support the scheduling modes
 *          OPENNSL_COSQ_WEIGHTED_FAIR_QUEUING and OPENNSL_COSQ_BOUNDED_DELAY.
 *          Note: In all devices supporting Enhanced Transmission Selection
 *          (ETS) hierarchical scheduling, opennsl_cosq_sched_set and
 *          opennsl_cosq_sched_get API is used to configure and retrieve the
 *          Class of Service policy, weights, and delay for CPU(CMIC) port
 *          only.
 *
 *\param    unit [IN]   Unit number.
 *\param    pbm [IN]   Port bit map of ports to configure
 *\param    mode [IN]   Scheduling mode, see table =OPENNSL_COSQ_table
 *\param    weights [IN]   Array of relative weights indexed by CoS queue. Use
 *          depends on the selected mode.  See =OPENNSL_COSQ_COMBO . Note: Be
 *          aware that despite of OPENNSL_COS_COUNT is 8, it supports up to 10
 *          weights arrays in network switch devices if and only if
 *          opennsl_num_cos=10 is configured.
 *\param    delay [IN]   Used only if scheduling algorithm is
 *          OPENNSL_COSQ_BOUNDED_DELAY to indicate the maximum amount of time
 *          before returning to the highest priority CoS queue.  This value is
 *          only used for non-negative elements of the weights array.
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_cosq_port_sched_set(
    int unit, 
    opennsl_pbmp_t pbm, 
    int mode, 
    const int weights[OPENNSL_COS_COUNT], 
    int delay) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set Class of Service policy, weights and delay.
 *
 *\description Configure or retrieve the Class of Service policy, weights, and
 *          delay for a device or port.  The mode options are listed in the
 *          table below.  For modes which use weights, the weights may range
 *          between OPENNSL_COSQ_WEIGHT_MIN and the value of weight_max
 *          returned by =opennsl_cosq_sched_weight_max_get for the mode. If
 *          weight_max = OPENNSL_COSQ_WEIGHT_UNLIMITED, then any positive
 *          weight is acceptable.  In OPENNSL_COSQ_BOUNDED_DELAY mode, a
 *          negative value for an element of the weight array indicates that
 *          the weight and delay value for that Class of Service should remain
 *          unchanged, while the non-negative elements of the weight array are
 *          updated and assigned the given delay value. For modes which use
 *          weights, OPENNSL_COSQ_WEIGHT_STRICT may be supplied for some of
 *          the weights, indicating these queues should behave as in strict
 *          priority mode. On the chips network switch, the queues in strict
 *          priority mode must be in consecutive order. The chips network
 *          switch does not support the scheduling modes
 *          OPENNSL_COSQ_WEIGHTED_FAIR_QUEUING and OPENNSL_COSQ_BOUNDED_DELAY.
 *          Note: In all devices supporting Enhanced Transmission Selection
 *          (ETS) hierarchical scheduling, opennsl_cosq_sched_set and
 *          opennsl_cosq_sched_get API is used to configure and retrieve the
 *          Class of Service policy, weights, and delay for CPU(CMIC) port
 *          only.
 *
 *\param    unit [IN]   Unit number.
 *\param    mode [OUT]   Scheduling mode, see table =OPENNSL_COSQ_table
 *\param    weights [OUT]   Array of relative weights indexed by CoS queue. Use
 *          depends on the selected mode.  See =OPENNSL_COSQ_COMBO . Note: Be
 *          aware that despite of OPENNSL_COS_COUNT is 8, it supports up to 10
 *          weights arrays in network switch devices if and only if
 *          opennsl_num_cos=10 is configured.
 *\param    delay [OUT]   Used only if scheduling algorithm is
 *          OPENNSL_COSQ_BOUNDED_DELAY to indicate the maximum amount of time
 *          before returning to the highest priority CoS queue.  This value is
 *          only used for non-negative elements of the weights array.
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_cosq_sched_get(
    int unit, 
    int *mode, 
    int weights[OPENNSL_COS_COUNT], 
    int *delay) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set Class of Service policy, weights and delay.
 *
 *\description Configure or retrieve the Class of Service policy, weights, and
 *          delay for a device or port.  The mode options are listed in the
 *          table below.  For modes which use weights, the weights may range
 *          between OPENNSL_COSQ_WEIGHT_MIN and the value of weight_max
 *          returned by =opennsl_cosq_sched_weight_max_get for the mode. If
 *          weight_max = OPENNSL_COSQ_WEIGHT_UNLIMITED, then any positive
 *          weight is acceptable.  In OPENNSL_COSQ_BOUNDED_DELAY mode, a
 *          negative value for an element of the weight array indicates that
 *          the weight and delay value for that Class of Service should remain
 *          unchanged, while the non-negative elements of the weight array are
 *          updated and assigned the given delay value. For modes which use
 *          weights, OPENNSL_COSQ_WEIGHT_STRICT may be supplied for some of
 *          the weights, indicating these queues should behave as in strict
 *          priority mode. On the chips network switch, the queues in strict
 *          priority mode must be in consecutive order. The chips network
 *          switch does not support the scheduling modes
 *          OPENNSL_COSQ_WEIGHTED_FAIR_QUEUING and OPENNSL_COSQ_BOUNDED_DELAY.
 *          Note: In all devices supporting Enhanced Transmission Selection
 *          (ETS) hierarchical scheduling, opennsl_cosq_sched_set and
 *          opennsl_cosq_sched_get API is used to configure and retrieve the
 *          Class of Service policy, weights, and delay for CPU(CMIC) port
 *          only.
 *
 *\param    unit [IN]   Unit number.
 *\param    pbm [IN]   Port bit map of ports to configure
 *\param    mode [OUT]   Scheduling mode, see table =OPENNSL_COSQ_table
 *\param    weights [OUT]   Array of relative weights indexed by CoS queue. Use
 *          depends on the selected mode.  See =OPENNSL_COSQ_COMBO . Note: Be
 *          aware that despite of OPENNSL_COS_COUNT is 8, it supports up to 10
 *          weights arrays in network switch devices if and only if
 *          opennsl_num_cos=10 is configured.
 *\param    delay [OUT]   Used only if scheduling algorithm is
 *          OPENNSL_COSQ_BOUNDED_DELAY to indicate the maximum amount of time
 *          before returning to the highest priority CoS queue.  This value is
 *          only used for non-negative elements of the weights array.
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_cosq_port_sched_get(
    int unit, 
    opennsl_pbmp_t pbm, 
    int *mode, 
    int weights[OPENNSL_COS_COUNT], 
    int *delay) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Retrieve maximum weights for given CoS policy.
 *
 *\description Retrieve the maximum allowed weight value for the weights array
 *          in.
 *
 *\param    unit [IN]   Unit number.
 *\param    mode [IN]   Scheduling mode, see table =OPENNSL_COSQ_table
 *\param    weight_max [OUT]   Maximum weight value for opennsl_cosq_sched_set.
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_cosq_sched_weight_max_get(
    int unit, 
    int mode, 
    int *weight_max) LIB_DLL_EXPORTED ;

#define OPENNSL_COSQ_ALL            0x00000001 
#define OPENNSL_COSQ_BW_EAV_MODE    0x00000008 /**< Prioritize selected queue(s)
                                                  for bandwidth before
                                                  non-selected queue(s). */
#define OPENNSL_COSQ_BW_LLFC        0x00000010 /**< Link Level Flow Control
                                                  setting */
#define OPENNSL_COSQ_BW_PACKET_MODE 0x00000020 /**< The bandwidth specified is in
                                                  packets per second instead of
                                                  kbits per second */
#define OPENNSL_COSQ_BW_NOT_COMMIT  0x00000040 /**< Set rate to SW DB only, commit
                                                  to HW is done when calling the
                                                  API with the same GPort type
                                                  and without NOT_COMMIT flag. */
/***************************************************************************//** 
 *\brief Configure a port's bandwidth distribution among CoS queues.
 *
 *\description On some devices, the bandwidth allocated to each CoS queue may be
 *          configured. The maximum bandwidth setting is applicable to any
 *          mode on these devices. However, for non-XCore (tm) and non-XGS
 *          devices, the minimum bandwidth settings and the preference flags
 *          are only valid when the WEIGHTED_FAIR_QUEUING mode is selected. 
 *          The order of the calls opennsl_cosq_port_bandwidth_set and
 *          opennsl_cosq_port_sched_set is not important.  A port value of -1
 *          or gport type for system configuration will configure all ports,
 *          and a cosq value of -1 will configure all cosq's.
 *          The supplied bandwidth values may be rounded up to the nearest
 *          value supported by the HW.
 *          On network switch devices, while using this API kbits_sec_min
 *          should be used for specifying rate and kbits_sec_max for
 *          specifying the burst.
 *          The available flags for bandwidth response tuning are
 *          =OPENNSL_COSQ_BW_f.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port
 *\param    cosq [IN]   Cos Queue to configure
 *\param    kbits_sec_min [IN]   Minimum bandwidth in kbits/sec.
 *\param    kbits_sec_max [IN]   Maximum bandwidth in kbits/sec.
 *\param    flags [IN]   Bandwidth tuning parameters.
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_cosq_port_bandwidth_set(
    int unit, 
    opennsl_port_t port, 
    opennsl_cos_queue_t cosq, 
    uint32 kbits_sec_min, 
    uint32 kbits_sec_max, 
    uint32 flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure a port's bandwidth distribution among CoS queues.
 *
 *\description On some devices, the bandwidth allocated to each CoS queue may be
 *          configured. The maximum bandwidth setting is applicable to any
 *          mode on these devices. However, for non-XCore (tm) and non-XGS
 *          devices, the minimum bandwidth settings and the preference flags
 *          are only valid when the WEIGHTED_FAIR_QUEUING mode is selected. 
 *          The order of the calls opennsl_cosq_port_bandwidth_set and
 *          opennsl_cosq_port_sched_set is not important.  A port value of -1
 *          or gport type for system configuration will configure all ports,
 *          and a cosq value of -1 will configure all cosq's.
 *          The supplied bandwidth values may be rounded up to the nearest
 *          value supported by the HW.
 *          On network switch devices, while using this API kbits_sec_min
 *          should be used for specifying rate and kbits_sec_max for
 *          specifying the burst.
 *          The available flags for bandwidth response tuning are
 *          =OPENNSL_COSQ_BW_f.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port
 *\param    cosq [IN]   Cos Queue to configure
 *\param    kbits_sec_min [OUT]   Minimum bandwidth in kbits/sec.
 *\param    kbits_sec_max [OUT]   Maximum bandwidth in kbits/sec.
 *\param    flags [OUT]   Bandwidth tuning parameters.
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_cosq_port_bandwidth_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_cos_queue_t cosq, 
    uint32 *kbits_sec_min, 
    uint32 *kbits_sec_max, 
    uint32 *flags) LIB_DLL_EXPORTED ;

#define OPENNSL_COSQ_DISCARD_ENABLE         0x0001     
#define OPENNSL_COSQ_DISCARD_NONTCP         0x0004     
#define OPENNSL_COSQ_DISCARD_COLOR_GREEN    0x0100     
#define OPENNSL_COSQ_DISCARD_COLOR_YELLOW   0x0200     
#define OPENNSL_COSQ_DISCARD_COLOR_RED      0x0400     
#define OPENNSL_COSQ_DISCARD_COLOR_BLACK    0x0800     
#define OPENNSL_COSQ_DISCARD_COLOR_ALL      0x0F00     
#define OPENNSL_COSQ_DISCARD_DROP_FIRST     OPENNSL_COSQ_DISCARD_COLOR_RED 
#define OPENNSL_COSQ_DISCARD_PACKETS        0x1000     
#define OPENNSL_COSQ_DISCARD_BYTES          0x2000     
#define OPENNSL_COSQ_DISCARD_MARK_CONGESTION 0x4000     
#define OPENNSL_COSQ_DISCARD_PORT           0x8000     
#define OPENNSL_COSQ_DISCARD_DEVICE         0x10000    
#define OPENNSL_COSQ_DISCARD_TCP            0x40000    
#define OPENNSL_COSQ_DISCARD_SYSTEM         0x80000    
#define OPENNSL_COSQ_DISCARD_PROBABILITY1   0x100000   
#define OPENNSL_COSQ_DISCARD_PROBABILITY2   0x200000   
#define OPENNSL_COSQ_DISCARD_IFP            0x400000   
#define OPENNSL_COSQ_DISCARD_OUTER_CFI      0x800000   
/***************************************************************************//** 
 *\brief Configure Weighted Random Early Discard (WRED).
 *
 *\description Configure the Weighted Random Early Discard (WRED) features.
 *          The available flags for discard are =OPENNSL_COSQ_DISCARD_f.
 *
 *\param    unit [IN]   Unit number.
 *\param    flags [IN]   Enable parameters
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_cosq_discard_set(
    int unit, 
    uint32 flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure Weighted Random Early Discard (WRED).
 *
 *\description Configure the Weighted Random Early Discard (WRED) features.
 *          The available flags for discard are =OPENNSL_COSQ_DISCARD_f.
 *
 *\param    unit [IN]   Unit number.
 *\param    flags [OUT]   Enable parameters
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_cosq_discard_get(
    int unit, 
    uint32 *flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure a port's Weighted Random Early Discard (WRED) parameters.
 *
 *\description Configure the port's Weighted Random Early Discard (WRED)
 *          parameters. Some vendors do WRED (Weighted Random Early Detection)
 *          based on  IP precedence per cos, with non-IP packets treated as
 *          precedence 0. This implementation does WRED (Weighted Random Early
 *          Discard) based on cosq and treats all packets in a queue equally.
 *          The parameters are specified for a given port, cosq, and color
 *          (green, yellow,  or red).  A port value of -1 will configure all
 *          ports, and a cosq value of -1 will configure all cosq's. The drop
 *          start specifies the queue size where drops will begin in terms of
 *          percent of max queue size. The drop slope specifies the angle in
 *          degrees describing the drop probability  slope. The average_time
 *          specifies the time in microseconds used in the  calculation of
 *          average queue depth.
 *          This set of APIs is also used for configuring the Simple Random
 *          Early Discard (RED) parameters for network switch. For a given
 *          port, cosq and color, the user can configure the drop_start
 *          (percentage of queue size) and the drop probability in increments
 *          of one-tenths of a percentage. The drop_slope parameter is
 *          overloaded  to encode the percentage and must be negative. The
 *          average_time parameter is ignored.
 *          This set of APIs is also used for configuring the System-RED
 *          parameters. System-wide RED control scheme to ensure that on a
 *          system level  (with multiple devices) color priority will remain.
 *          In that case, user should set  OPENNSL_COSQ_DISCARD_SYSTEM flag in
 *          order to indicate System-RED configuration.
 *          In case RED test support more than one slot test. User should set
 *          each slot by using flags OPENNSL_COSQ_DISCARD_PROBABILITY. Where
 *          each flag indicate slot number (first from above). In case RED
 *          test support more than one slot test by user set without
 *          OPENNSL_COSQ_DISCARD_PROBABILITY flags HW configuration assume as
 *          there only one slot test.
 *          network switch introduces an additional Weighted Curve Set (WCS)
 *          profile for ECN Capable transport (ECT). For network switch, the
 *          packet classifications are for ECT and non-ECT traffic. Non-ECT
 *          traffic gets further classified based on congestion control
 *          algorithm which reacts to packet drops, into Responsive &
 *          Non-Responsive dropping.
 *          To support the new WCS profiles, three new packet classification
 *          flags have been introduced:.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port
 *\param    cosq [IN]   Cos Queue to configure
 *\param    color [IN]   OPENNSL_COSQ_DISCARD_COLOR_*
 *\param    drop_start [IN]   Percentage of queue size to start dropping
 *\param    drop_slope [IN]   Degrees 0..90 describing the drop probability slope
 *          for  WRED. For network switch and network switch, this parameter must
 *          be negative and each unit describes one-tenths of a percentage of the
 *          simple RED drop probability.
 *\param    average_time [IN]   Time in microseconds used in avg queue depth
 *          calculation for WRED. For simple RED (network switch) this is ignored.
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_cosq_discard_port_set(
    int unit, 
    opennsl_port_t port, 
    opennsl_cos_queue_t cosq, 
    uint32 color, 
    int drop_start, 
    int drop_slope, 
    int average_time) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure a port's Weighted Random Early Discard (WRED) parameters.
 *
 *\description Configure the port's Weighted Random Early Discard (WRED)
 *          parameters. Some vendors do WRED (Weighted Random Early Detection)
 *          based on  IP precedence per cos, with non-IP packets treated as
 *          precedence 0. This implementation does WRED (Weighted Random Early
 *          Discard) based on cosq and treats all packets in a queue equally.
 *          The parameters are specified for a given port, cosq, and color
 *          (green, yellow,  or red).  A port value of -1 will configure all
 *          ports, and a cosq value of -1 will configure all cosq's. The drop
 *          start specifies the queue size where drops will begin in terms of
 *          percent of max queue size. The drop slope specifies the angle in
 *          degrees describing the drop probability  slope. The average_time
 *          specifies the time in microseconds used in the  calculation of
 *          average queue depth.
 *          This set of APIs is also used for configuring the Simple Random
 *          Early Discard (RED) parameters for network switch. For a given
 *          port, cosq and color, the user can configure the drop_start
 *          (percentage of queue size) and the drop probability in increments
 *          of one-tenths of a percentage. The drop_slope parameter is
 *          overloaded  to encode the percentage and must be negative. The
 *          average_time parameter is ignored.
 *          This set of APIs is also used for configuring the System-RED
 *          parameters. System-wide RED control scheme to ensure that on a
 *          system level  (with multiple devices) color priority will remain.
 *          In that case, user should set  OPENNSL_COSQ_DISCARD_SYSTEM flag in
 *          order to indicate System-RED configuration.
 *          In case RED test support more than one slot test. User should set
 *          each slot by using flags OPENNSL_COSQ_DISCARD_PROBABILITY. Where
 *          each flag indicate slot number (first from above). In case RED
 *          test support more than one slot test by user set without
 *          OPENNSL_COSQ_DISCARD_PROBABILITY flags HW configuration assume as
 *          there only one slot test.
 *          network switch introduces an additional Weighted Curve Set (WCS)
 *          profile for ECN Capable transport (ECT). For network switch, the
 *          packet classifications are for ECT and non-ECT traffic. Non-ECT
 *          traffic gets further classified based on congestion control
 *          algorithm which reacts to packet drops, into Responsive &
 *          Non-Responsive dropping.
 *          To support the new WCS profiles, three new packet classification
 *          flags have been introduced:.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port
 *\param    cosq [IN]   Cos Queue to configure
 *\param    color [IN]   OPENNSL_COSQ_DISCARD_COLOR_*
 *\param    drop_start [OUT]   Percentage of queue size to start dropping
 *\param    drop_slope [OUT]   Degrees 0..90 describing the drop probability slope
 *          for  WRED. For network switch and network switch, this parameter must
 *          be negative and each unit describes one-tenths of a percentage of the
 *          simple RED drop probability.
 *\param    average_time [OUT]   Time in microseconds used in avg queue depth
 *          calculation for WRED. For simple RED (network switch) this is ignored.
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_cosq_discard_port_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_cos_queue_t cosq, 
    uint32 color, 
    int *drop_start, 
    int *drop_slope, 
    int *average_time) LIB_DLL_EXPORTED ;

#define OPENNSL_COSQ_HIGH_PRIORITY  -4         
#define OPENNSL_COSQ_LOW_PRIORITY   -5         
/** Features that can be controlled on a gport/cosq  basis. */
typedef enum opennsl_cosq_control_e {
    opennslCosqControlEgressUCQueueSharedLimitBytes = 79, /**< Egress UC Shared Queue limit setting */
    opennslCosqControlEgressMCQueueMinLimitBytes = 84, /**< MC Min Queue limit setting */
    opennslCosqControlPortQueueUcast = 103, /**< retrieve port, cosq queue number of
                                           PBSMH UC packet headers */
    opennslCosqControlPortQueueMcast = 104, /**< retrieve port, cosq queue number of
                                           PBSMH MC packet headers */
} opennsl_cosq_control_t;

/***************************************************************************//** 
 *\brief Set various features at the gport/cosq level.
 *
 *\description Features that can be controlled on a gport/cosq  basis.
 *          On some devices and for some cosq control types, a port value of
 *          -1 or gport type for system configuration will configure system
 *          based cosq control.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   GPORT ID for a queue group
 *\param    cosq [IN]   CoS Queue
 *\param    type [IN]   type of operation (see =OPENNSL_COSQ_CONTROL_table)
 *\param    arg [IN]   (for _set) Argument whose meaning is dependent on type
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_control_set(
    int unit, 
    opennsl_gport_t port, 
    opennsl_cos_queue_t cosq, 
    opennsl_cosq_control_t type, 
    int arg) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set various features at the gport/cosq level.
 *
 *\description Features that can be controlled on a gport/cosq  basis.
 *          On some devices and for some cosq control types, a port value of
 *          -1 or gport type for system configuration will configure system
 *          based cosq control.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   GPORT ID for a queue group
 *\param    cosq [IN]   CoS Queue
 *\param    type [IN]   type of operation (see =OPENNSL_COSQ_CONTROL_table)
 *\param    arg [OUT]   (for _set) Argument whose meaning is dependent on type
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_control_get(
    int unit, 
    opennsl_gport_t port, 
    opennsl_cos_queue_t cosq, 
    opennsl_cosq_control_t type, 
    int *arg) LIB_DLL_EXPORTED ;

/** For Virtual output queues (system ports) */
typedef struct opennsl_cosq_gport_discard_s {
    uint32 flags;           
    int min_thresh;         /**< Queue depth in bytes to begin dropping. */
    int max_thresh;         /**< Queue depth in bytes to drop all packets. */
    int drop_probability;   /**< Drop probability at max threshold. */
} opennsl_cosq_gport_discard_t;

/** For Virtual output queues (system ports) */
typedef enum opennsl_cosq_gport_stats_e {
    opennslCosqGportGreenAcceptedPkts = 0, /**< Green/DP0, accepted packet count. */
    opennslCosqGportGreenAcceptedBytes = 1, /**< Green/DP0, accepted byte count. */
    opennslCosqGportNotGreenAcceptedPkts = 2, /**< Not Green/DP1-3, accepted packet
                                           count. */
    opennslCosqGportNotGreenAcceptedBytes = 3, /**< Not Green/DP1-3, accepted byte count. */
    opennslCosqGportGreenCongestionMarkedPkts = 4, /**< Green/DP0, ECN Marked packets. */
    opennslCosqGportGreenCongestionMarkedBytes = 5, /**< Green/DP0, ECN Marked bytes. */
    opennslCosqGportGreenDiscardDroppedPkts = 6, /**< Green/DP0, WRED dropped packets. */
    opennslCosqGportGreenDiscardDroppedBytes = 7, /**< Green/DP0, WRED dropped bytes. */
    opennslCosqGportYellowAcceptedPkts = 8, /**< Yellow/DP1, accepted packet count. */
    opennslCosqGportYellowAcceptedBytes = 9, /**< Yellow/DP1, accepted byte count. */
    opennslCosqGportYellowCongestionMarkedPkts = 10, /**< Yellow/DP1, ECN Marked packets. */
    opennslCosqGportYellowCongestionMarkedBytes = 11, /**< Yellow/DP1, ECN nMarked bytes. */
    opennslCosqGportYellowDiscardDroppedPkts = 12, /**< Yellow/DP1, WRED dropped packets. */
    opennslCosqGportYellowDiscardDroppedBytes = 13, /**< Yellow/DP1, WRED dropped bytes. */
    opennslCosqGportRedAcceptedPkts = 14, /**< Red/DP2, accepted packet count. */
    opennslCosqGportRedAcceptedBytes = 15, /**< Red/DP2, accepted byte count. */
    opennslCosqGportRedCongestionMarkedPkts = 16, /**< Red/DP2, ECN Marked packets. */
    opennslCosqGportRedCongestionMarkedBytes = 17, /**< Red/DP2, ECN Marked bytes. */
    opennslCosqGportRedDiscardDroppedPkts = 18, /**< Red/DP2, WRED dropped packets. */
    opennslCosqGportRedDiscardDroppedBytes = 19, /**< Red/DP2, WRED dropped bytes. */
    opennslCosqGportBlackAcceptedPkts = 20, /**< Black/DP3, accepted packet count. */
    opennslCosqGportBlackAcceptedBytes = 21, /**< Black/DP3, accepted byte count. */
    opennslCosqGportNonWredDroppedPkts = 22, /**< NON-WRED dropped packet count. */
    opennslCosqGportNonWredDroppedBytes = 23, /**< NON-WRED dropped byte count. */
    opennslCosqGportDequeuedPkts = 24,  /**< dequeued packets. */
    opennslCosqGportDequeuedBytes = 25, /**< dequeued bytes. */
    opennslCosqGportGreenDroppedPkts = 26, /**< Green/DP0, non-WRED dropped pkts. */
    opennslCosqGportGreenDroppedBytes = 27, /**< Green/DP0, non-WRED dropped bytes. */
    opennslCosqGportNotGreenDroppedPkts = 28, /**< Not Green/DP1-3 dropped pkts. */
    opennslCosqGportNotGreenDroppedBytes = 29, /**< Not Green/DP1-3 dropped bytes. */
    opennslCosqGportYellowDroppedPkts = 30, /**< Yellow/DP1, non-WRED dropped pkts. */
    opennslCosqGportYellowDroppedBytes = 31, /**< Yellow/DP1, non-WRED dropped bytes. */
    opennslCosqGportRedDroppedPkts = 32, /**< Red/DP2, non-WRED dropped pkts. */
    opennslCosqGportRedDroppedBytes = 33, /**< Red/DP2, non-WRED dropped bytes. */
    opennslCosqGportBlackCongestionMarkedPkts = 34, /**< Black/DP3, ECN Marked packets. */
    opennslCosqGportBlackCongestionMarkedBytes = 35, /**< Black/DP3, ECN Marked bytes. */
    opennslCosqGportBlackDiscardDroppedPkts = 36, /**< Black/DP3, WRED dropped at packets. */
    opennslCosqGportBlackDiscardDroppedBytes = 37, /**< Black/DP3, WRED dropped bytes. */
    opennslCosqGportBlackDroppedPkts = 38, /**< Black/DP3, non-WRED dropped at
                                           packets. */
    opennslCosqGportBlackDroppedBytes = 39, /**< Black/DP3, non-WRED dropped bytes. */
    opennslCosqGportOverSubscribeTotelDroppedPkts = 40, /**< Free list underflow, pkts dropped. */
    opennslCosqGportOverSubscribeTotalDroppedBytes = 41, /**< Free list underflow, bytes dropped. */
    opennslCosqGportOverSubscribeGuaranteeDroppedPkts = 42, /**< Gbl buf thres guarantee, pkts
                                           dropped. */
    opennslCosqGportOverSubscribeGuaranteedDroppedBytes = 43, /**< Gbl buf thres guarantee, bytes
                                           dropped. */
    opennslCosqGportDiscardDroppedPkts = 44, /**< discarded packets */
    opennslCosqGportDiscardDroppedBytes = 45, /**< discarded bytes */
    opennslCosqGportYellowRedDiscardDroppedPkts = 46, /**< Yellow and Red dropped packets */
    opennslCosqGportYellowRedDiscardDroppedBytes = 47, /**< Yellow and Red dropped bytes */
    opennslCosqGportEnqueuedPkts = 48,  /**< enqueued packets */
    opennslCosqGportEnqueuedBytes = 49, /**< enqueued bytes */
    opennslCosqGportOutLimitDroppedPkts = 50, /**< Egress Admission Control (EAC)
                                           dropped pkts */
    opennslCosqGportOutLimitDroppedBytes = 51, /**< EAC dropped bytes */
    opennslCosqGportOutLimitDroppedGreenPkts = 52, /**< EAC dropped green pkts */
    opennslCosqGportOutLimitDroppedGreenBytes = 53, /**< EAC dropped green bytes */
    opennslCosqGportOutLimitDroppedYellowPkts = 54, /**< EAC dropped yellow pkts */
    opennslCosqGportOutLimitDroppedYellowBytes = 55, /**< EAC dropped yellow bytes */
    opennslCosqGportOutLimitDroppedRedPkts = 56, /**< EAC dropped red pkts */
    opennslCosqGportOutLimitDroppedRedBytes = 57, /**< EAC dropped red bytes */
    opennslCosqGportOutLimitDroppedMulticastPkts = 58, /**< EAC dropped multicast pkts */
    opennslCosqGportOutLimitDroppedMulticastBytes = 59, /**< EAC dropped multicast bytes */
    opennslCosqGportOutPkts = 60,       /**< Egress Interface. */
    opennslCosqGportOutBytes = 61,      /**< Egress Interface. */
    opennslCosqGportReceivedBytes = 62, /**< Bytes received into queue. */
    opennslCosqGportReceivedPkts = 63,  /**< Pkts received into queue. */
    opennslCosqGportDroppedBytes = 64,  /**< Bytes dropped in queue. */
    opennslCosqGportDroppedPkts = 65,   /**< Pkts dropped in queue. */
    opennslCosqGportDelayedBytes = 66,  /**< Delayed bytes. */
    opennslCosqGportDelayedHundredUs = 67, /**< Maximum Pkts delay. */
    opennslCosqGportGreenPkts = 68,     /**< Green/DP0 packet count. */
    opennslCosqGportGreenBytes = 69,    /**< Green/DP0 byte count. */
    opennslCosqGportNotGreenPkts = 70,  /**< Not-Green/DP0 packet count. */
    opennslCosqGportNotGreenBytes = 71, /**< Not-Green/DP0 byte count. */
    opennslCosqGportOffset0Bytes = 72,  /**< Byte count at configurable offset 0. */
    opennslCosqGportOffset0Packets = 73, /**< Packet count at configurable offset
                                           0. */
    opennslCosqGportOffset1Bytes = 74,  /**< Byte count at configurable offset 1. */
    opennslCosqGportOffset1Packets = 75, /**< Packet count at configurable offset
                                           1. */
    opennslCosqGportOffset2Bytes = 76,  /**< Byte count at configurable offset 2. */
    opennslCosqGportOffset2Packets = 77, /**< Packet count at configurable offset
                                           2. */
    opennslCosqGportOffset3Bytes = 78,  /**< Byte count at configurable offset 3. */
    opennslCosqGportOffset3Packets = 79, /**< Packet count at configurable offset
                                           3. */
    opennslCosqGportOffset4Bytes = 80,  /**< Byte count at configurable offset 4. */
    opennslCosqGportOffset4Packets = 81, /**< Packet count at configurable offset
                                           4. */
    opennslCosqGportOffset5Bytes = 82,  /**< Byte count at configurable offset 5. */
    opennslCosqGportOffset5Packets = 83, /**< Packet count at configurable offset
                                           5. */
    opennslCosqGportOffset6Bytes = 84,  /**< Byte count at configurable offset 6. */
    opennslCosqGportOffset6Packets = 85, /**< Packet count at configurable offset
                                           6. */
    opennslCosqGportOffset7Bytes = 86,  /**< Byte count at configurable offset 7. */
    opennslCosqGportOffset7Packets = 87, /**< Packet count at configurable offset
                                           7. */
    opennslCosqGportStatCount = 88      /**< Must be the last entry ! */
} opennsl_cosq_gport_stats_t;

#define OPENNSL_COSQ_GPORT_STATS_SHARED 0x00000001 
/** Statistics Profile */
typedef struct opennsl_cosq_gport_stat_profile_s {
    SHR_BITDCL stats[_SHR_BITDCLSIZE(opennslCosqGportOutBytes)]; /**< Use Gport Stats Enumeration */
} opennsl_cosq_gport_stat_profile_t;

/***************************************************************************//** 
 *\brief Associate a priority profile with a queue range.
 *
 *\description Associate one of 4 priority profiles with a queue range.
 *
 *\param    unit [IN]   Unit number.
 *\param    start_queue [IN]   starting queue (must be multiple of 64)
 *\param    end_queue [IN]   ending queue (must be multiple of 64 then -1)
 *\param    pri_profile_id [IN]   priority profile id (0-3)
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_priority_set(
    int unit, 
    int start_queue, 
    int end_queue, 
    int pri_profile_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the priority profile associated with a queue range.
 *
 *\description Return one of 4 priority profiles associated with the given queue
 *          range.
 *
 *\param    unit [IN]   Unit number.
 *\param    start_queue [IN]   starting queue (must be multiple of 64)
 *\param    end_queue [IN]   ending queue (must be multiple of 64 then -1)
 *\param    pri_profile_id [OUT]   priority profile id (0-3)
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_priority_get(
    int unit, 
    int start_queue, 
    int end_queue, 
    int *pri_profile_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Allocate/Retrieve unicast queue group and scheduler queue group
 *       configuration.
 *
 *\description These APIs are used to allocate/retrieve unicast or multicast
 *          queue group or a scheduler queue group configuration. Scheduler
 *          queue groups are used to implement H-QoS. The set of CoS queues
 *          are uniquely identified with a GPORT ID, which represents the base
 *          CoS queue in the set. The GPORT ID is allocated from the next
 *          available queue in group of queues for the port or specified by
 *          the  input when the OPENNSL_COSQ_GPORT_WITH_ID flag is set. But
 *          the  flag OPENNSL_COSQ_GPORT_WITH_ID is only supported for a few
 *          devices. OPENNSL_GPORT_TYPE_UCAST_QUEUE_GROUP,
 *          OPENNSL_GPORT_TYPE_MCAST_QUEUE_GROUP, or
 *          OPENNSL_GPORT_TYPE_SCHEDULER type of GPORT can be added for
 *          hierarchical queuing (see also, =opennsl_cosq_gport_attach API).
 *          Depending on the functionality physical_port parameter can have
 *          one of the following values       unicast queue group   =>
 *          OPENNSL_GPORT_MODPORT_SET()            multicast queue group =>
 *          OPENNSL_GPORT_MODPORT_SET()            scheduler queue group =>
 *          OPENNSL_GPORT_NULL
 *          When allocating a queue group the req_gport parameter direction
 *          depends on the flags. If OPENNSL_COSQ_GPORT_WITH_ID is specified
 *          the input direction is valid. Depending on the functionality the
 *          following macros can be used to create the req_gport.      
 *          unicast queue group   => OPENNSL_GPORT_UCAST_QUEUE_GROUP_SET()    
 *                 multicast queue group =>
 *          OPENNSL_GPORT_MCAST_QUEUE_GROUP_SET()            scheduler queue
 *          group => OPENNSL_GPORT_SCHEDULER_SET()      req_gport parameter is
 *          always updated and should be subsequently used by the user.
 *          When the OPENNSL_COSQ_GPORT_WITH_ID flag is set, the value
 *          provided in the gport parameter is used as the GPORT ID, otherwise
 *          a unique GPORT ID will be allocated and returned. The feature
 *          using OPENNSL_COSQ_GPORT_WITH_ID to allocate a queue group is only
 *          supported for a few devices.
 *          For some devices that may not have the ability to shape every port
 *          or queue, the application can control whether the gport must be
 *          allocated from a shapeable or non-shapeable area.  This can be
 *          done by specifying the flags OPENNSL_COSQ_GPORT_WITH_SHAPING or
 *          OPENNSL_COSQ_GPORT_WITHOUT_SHAPING, respectively.  If neither flag
 *          is specified, the API will allocate a gport without paying any
 *          attention to whether it would be possible to configure a shaper on
 *          such port later.
 *          When the OPENNSL_COSQ_GPORT_OVERLAY flag is set, it allows overlay
 *          of queues that were previously allocated.
 *          When the OPENNSL_COSQ_GPORT_SUBSCRIBER flag is set, scheduling for
 *          the queue group will be done locally and will not involve the
 *          central arbiter. A local gport should be added only for ports
 *          which are local to that device.
 *          When the OPENNSL_COSQ_GPORT_MULTIPATH flag is set, a multipath
 *          shaper gport is created. Scheduler nodes  on the same level could
 *          be added to the multipath shaper gport. The aggregated traffic
 *          from all nodes is shaped by the multipath shaper. The shaping rate
 *          of multipath shaper is controlled by calling
 *          =opennsl_cosq_gport_bandwidth_set API with the multipath shaper
 *          gport
 *          When the config.opennsl variable fabric_egress_setup=0 is set,
 *          FIFO-level egress support becomes available.  The
 *          OPENNSL_COSQ_GPORT_EGRESS_GROUP flag is used to enable egress
 *          group support. Egress Group gports are similar to egress child
 *          gports in all other aspects. The egress group  gport connects a
 *          number of fifos to a subport and allows access at the FIFO-level.
 *          Multiple egress groups can be connected to the same subport up to
 *          sixteen fifos. In the case of egress gports, the num_cos_levels
 *          field is used to indicate the number of fifos to be associated
 *          with that egress gport.
 *          When the OPENNSL_COSQ_GPORT_DESTMOD_UCAST_QUEUE_GROUP flag is set,
 *          a set of virtual queue group (DMVOQ)  is allocated.
 *          On network switch chips, When the
 *          OPENNSL_COSQ_GPORT_DESTMOD_UCAST_QUEUE_GROUP flag is used with the
 *          combination of OPENNSL_COSQ_GPORT_WITH_ID,          the value
 *          provided in gport parameters is used as the GPORT_ID.          
 *          But scheduling mode need to programmed again as per the scheduling
 *          hierarchy.  API opennsl_cosq_port_sched_set() can be used to set
 *          the scheduling mode to be Strict/WRR.
 *          When the OPENNSL_COSQ_GPORT_VLAN_UCAST_QUEUE_GROUP flag is set, a
 *          queue to support service based queuing is allocated
 *          When a parent node is created by using opennsl_cosq_gport_add API
 *          call by passing num_cos_levels = -1 then that node can have any
 *          number of child nodes.
 *          On the chips network switch, default schedule hierarchies are set
 *          up at SDK initialization. Default schedule hierarchy elements
 *          cannot be managed except using non-gport APIs to configure COSQs
 *          at port level. The first call to the API opennsl_cosq_gport_add
 *          will destroy the default schedule hierarchies for all of ports and
 *          traffic will not flow on those ports until new schedule
 *          hierarchies for those ports are built.
 *          On the chips network switch and network switch API
 *          opennsl_cosq_gport_add return OPENNSL_E_PARAM because of fixed
 *          hierarchy. Gport tree is created during init. On the chips network
 *          switch and network switch because of fixed hierarchy scheduler the
 *          scope of COSQ GPORT is not global but it is local to per unit. So
 *          we should not modify the MODID dynamically.
 *          Some device configuration support multiple queue groups on a
 *          physical port.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   (for _get) GPORT ID for a queue group
 *\param    physical_port [OUT]   (for _get) GPORT ID for physical port
 *\param    num_cos_levels [OUT]   (for _add) number of cos levels
 *\param    flags [OUT]   (for _add) Specifies configuration. Valid flags listed
 *          at =OPENNSL_COSQ_GPORT_FLAGS_table
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_get(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_gport_t *physical_port, 
    int *num_cos_levels, 
    uint32 *flags) LIB_DLL_EXPORTED ;

typedef int (*opennsl_cosq_gport_traverse_cb)(
    int unit, 
    opennsl_gport_t port, 
    int numq, 
    uint32 flags, 
    opennsl_gport_t gport, 
    void *user_data);

/***************************************************************************//** 
 *\brief Traverse all added CoS queue GPORTs and call the supplied callback
 *       routine for each one.
 *
 *\description Traverse all added CoS queue GPORTs and call the supplied callback
 *           routine for each one.
 *
 *\param    unit [IN]   Unit number.
 *\param    cb [IN]   User-supplied callback function
 *\param    user_data [IN]   User-supplied data passed back in callback function
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_cosq_gport_traverse(
    int unit, 
    opennsl_cosq_gport_traverse_cb cb, 
    void *user_data) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure/Retrieve enable/disable state of a cos level in a queue group.
 *       OPENNSL88230 only: Also configure/Retrieve enable/disable state of a
 *       FIFO in an egress group.
 *
 *\description Configure/Retrieve enable/disable state of a cos level in a queue
 *          group. To enable/disable entire queue group, set cosq to -1. For
 *          OPENNSL88230, this API also supports enable and disable of an
 *          Egress Fifo. .
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID for a queue group
 *\param    cosq [IN]   CoS Queue, -1 for Queue Group (set only)
 *\param    enable [IN]   (for _set) TRUE to enable, FALSE to disable
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_enable_set(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_queue_t cosq, 
    int enable) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Force an immediate counter update and retrieve statistics.
 *
 *\description Similar to opennsl_cosq_gport_stat_get(), value returned is
 *          software accumulated  counter synced with the hardware counter.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID for a queue group
 *\param    cosq [IN]   CoS Queue
 *\param    stat [IN]   statistic to be retrieved. see table
 *          =OPENNSL_COSQ_GPORT_STATISTICS_table .
 *\param    value [OUT]   (for _get) statistic value
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_stat_sync_get(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_queue_t cosq, 
    opennsl_cosq_gport_stats_t stat, 
    uint64 *value) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure/Retrieve enable/disable state of a cos level in a queue group.
 *       OPENNSL88230 only: Also configure/Retrieve enable/disable state of a
 *       FIFO in an egress group.
 *
 *\description Configure/Retrieve enable/disable state of a cos level in a queue
 *          group. To enable/disable entire queue group, set cosq to -1. For
 *          OPENNSL88230, this API also supports enable and disable of an
 *          Egress Fifo. .
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID for a queue group
 *\param    cosq [IN]   CoS Queue, -1 for Queue Group (set only)
 *\param    enable [OUT]   (for _set) TRUE to enable, FALSE to disable
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_enable_get(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_queue_t cosq, 
    int *enable) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Enable/Disable statistics for queue group.
 *
 *\description Enables or disables statistics for a queue group.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID for a queue group
 *\param    enable [IN]   TRUE to enable, FALSE to disable
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_stat_enable_set(
    int unit, 
    opennsl_gport_t gport, 
    int enable) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Retrieve queue group statistic setting.
 *
 *\description Retrieve queue group statistic setting.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID for a queue group
 *\param    enable [OUT]   TRUE for enable, FALSE for disable
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_stat_enable_get(
    int unit, 
    opennsl_gport_t gport, 
    int *enable) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Retrieve/Set Statistics.
 *
 *\description Retrieve/Set statistics. If a statistic is not valid for a
 *          particular device a value of zero will be returned. The type
 *          opennsl_cosq_gport_stats_t is an enumeration of the available
 *          statistics.
 *          The set functionality only allows clearing of statistics.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID for a queue group
 *\param    cosq [IN]   CoS Queue
 *\param    stat [IN]   statistic to be retrieved. see table
 *          =OPENNSL_COSQ_GPORT_STATISTICS_table .
 *\param    value [OUT]   (for _get) statistic value
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_stat_get(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_queue_t cosq, 
    opennsl_cosq_gport_stats_t stat, 
    uint64 *value) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Retrieve/Set Statistics.
 *
 *\description Retrieve/Set statistics. If a statistic is not valid for a
 *          particular device a value of zero will be returned. The type
 *          opennsl_cosq_gport_stats_t is an enumeration of the available
 *          statistics.
 *          The set functionality only allows clearing of statistics.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID for a queue group
 *\param    cosq [IN]   CoS Queue
 *\param    stat [IN]   statistic to be retrieved. see table
 *          =OPENNSL_COSQ_GPORT_STATISTICS_table .
 *\param    value [IN]   (for _get) statistic value
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_stat_set(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_queue_t cosq, 
    opennsl_cosq_gport_stats_t stat, 
    uint64 value) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get a previously-configured Central Statistic profile that captures WRED
 *       packets.
 *
 *\description Get a configured WRED profile for the specific physical gport or
 *          ingress queue group. To retrieve Ingress physical profiles, the
 *          ingress gport must be set to a specific interface gport of type
 *          OPENNSL_GPORT_TYPE_MODPORT and the Ingress queue group gport must
 *          be OPENNSL_GPORT_TYPE_NONE. For all egress statistics profiles,
 *          the Ingress queue group gport must be set to
 *          OPENNSL_GPORT_TYPE_NONE.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID for Ingress interface. Valid types:
 *          OPENNSL_GPORT_TYPE_MODPORT, OPENNSL_GPORT_TYPE_EGRESS_MODPORT,
 *          OPENNSL_GPORT_TYPE_EGRESS_CHILD, OPENNSL_GPORT_TYPE_EGRESS_GROUP
 *\param    lgl_gport [IN]   GPORT ID for Ingress queue group. Valid types:
 *          OPENNSL_GPORT_TYPE_UCAST_QUEUE_GROUP,
 *          OPENNSL_GPORT_TYPE_MAST_QUEUE_GROUP, OPENNSL_GPORT_TYPE_NONE
 *\param    cosq [IN]   CoS Queue
 *\param    flags [IN]   Specifies configuration. Valid flags:
 *          OPENNSL_COSQ_GPORT_STATS_SHARED
 *\param    profile [OUT]   opennsl_cosq_gport_stats bitmap. see table
 *          =OPENNSL_COSQ_GPORT_STATISTICS_table .
 *
 *\retval     OPENNSL_E_NONE
 *\retval     OPENNSL_E_UNAVAIL
 *\retval     OPENNSL_E_PARAM
 *\retval     OPENNSL_E_PORT
 ******************************************************************************/
extern int opennsl_cosq_gport_stat_config_get(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_gport_t lgl_gport, 
    opennsl_cos_queue_t cosq, 
    uint32 flags, 
    opennsl_cosq_gport_stat_profile_t *profile) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set up a Central Statistic profile to capture WRED packets.
 *
 *\description Configure a profile of WRED statistics to capture on Ingress or
 *          Egress.  To configure Ingress physical statistics, the ingress
 *          gport must be set to a specific interface gport of type
 *          OPENNSL_GPORT_TYPE_MODPORT and the Ingress queue group gport must
 *          be OPENNSL_GPORT_TYPE_NONE. For all egress statistics, the Ingress
 *          queue group gport must be set to OPENNSL_GPORT_TYPE_NONE. To set
 *          up a profile to generate Egress physical statistics,  set gport
 *          type to OPENNSL_GPORT_TYPE_EGRESS_MODPORT. For Egress subport
 *          statistics,  use OPENNSL_GPORT_TYPE_EGRESS_CHILD. For specific
 *          FIFO-based statistics, use OPENNSL_GPORT_TYPE_EGRESS_GROUP. When
 *          creating a profile for FIFO-based statistics, the CoSQ field
 *          represents the specific FIFO number.
 *          The OPENNSL_COSQ_GPORT_STATS_SHARED flag is used to save resources
 *          by sharing common profiles over different queue ranges. This is
 *          the most common scenario. For example,  a profile that captures
 *          all green, yellow, and red accepted packets over a specific queue
 *          range can share the same resources. However, should a user wish to
 *          simultaneously capture red dropped packets over the same queue
 *          range, then the SHARED flag would not be used and a separate
 *          buffer will be allocated to store the dropped red packets over the
 *          queue range.
 *          The minimum granularity for a data collection is 1024 counters.
 *          When allocating counters for ingress queue groups, for example,
 *          creating a profile for base queue 16 will enable statistics
 *          gathering on all queues between 0 and 1023, because of the minimum
 *          granularity. The next queue group begins at 1024. To allocate a
 *          profile to collect statistics for 16K queues, the user only need
 *          execute this command 16 times. .
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID for Ingress interface. Valid types:
 *          OPENNSL_GPORT_TYPE_MODPORT, OPENNSL_GPORT_TYPE_EGRESS_MODPORT,
 *          OPENNSL_GPORT_TYPE_EGRESS_CHILD, OPENNSL_GPORT_TYPE_EGRESS_GROUP
 *\param    lgl_gport [IN]   GPORT ID for Ingress queue group. Valid types:
 *          OPENNSL_GPORT_TYPE_UCAST_QUEUE_GROUP,
 *          OPENNSL_GPORT_TYPE_MAST_QUEUE_GROUP, OPENNSL_GPORT_TYPE_NONE
 *\param    cosq [IN]   CoS Queue
 *\param    flags [IN]   Specifies configuration. Valid flags:
 *          OPENNSL_COSQ_GPORT_STATS_SHARED
 *\param    profile [IN]   opennsl_cosq_gport_stats bitmap. see table
 *          =OPENNSL_COSQ_GPORT_STATISTICS_table .
 *
 *\retval     OPENNSL_E_NONE
 *\retval     OPENNSL_E_UNAVAIL
 *\retval     OPENNSL_E_PARAM
 *\retval     OPENNSL_E_PORT
 *\retval     OPENNSL_E_NOT_FOUND
 *\retval     OPENNSL_E_RESOURCE
 *\retval     OPENNSL_E_MEMORY
 ******************************************************************************/
extern int opennsl_cosq_gport_stat_config_set(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_gport_t lgl_gport, 
    opennsl_cos_queue_t cosq, 
    uint32 flags, 
    opennsl_cosq_gport_stat_profile_t profile) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the value associated with a Central Statistics Index.
 *
 *\description Get a specific statistic value. For Ingress physical statistics,
 *          gport must be set to a specific physical interface using
 *          OPENNSL_GPORT_TYPE_MODPORT and Ingress queue group must be
 *          OPENNSL_GPORT_TYPE_NONE. For a specific Egress statistic, Ingress
 *          queue group must always be OPENNSL_GPORT_TYPE_NONE. Physical
 *          egress statistics are associated with
 *          OPENNSL_GPORT_TYPE_EGRESS_MODPORT. Egress subport statistics are 
 *          associated with OPENNSL_GPORT_TYPE_EGRESS_CHILD. Egress FIFO
 *          statistics are  associated with OPENNSL_GPORT_TYPE_EGRESS_GROUP.
 *          The specific FIFO is indexed using cosq parameter such that 0 and
 *          1 indicate unicast EF and non-EF packets, respectively, while 2
 *          and 3  correspond to multicast EF and non-EF packets,
 *          respectively. .
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID for Ingress interface. Valid types:
 *          OPENNSL_GPORT_TYPE_MODPORT, OPENNSL_GPORT_TYPE_EGRESS_MODPORT,
 *          OPENNSL_GPORT_TYPE_EGRESS_CHILD, OPENNSL_GPORT_TYPE_EGRESS_GROUP
 *\param    lgl_gport [IN]   GPORT ID for Ingress queue group. Valid types:
 *          OPENNSL_GPORT_TYPE_UCAST_QUEUE_GROUP,
 *          OPENNSL_GPORT_TYPE_MAST_QUEUE_GROUP, OPENNSL_GPORT_TYPE_NONE
 *\param    cosq [IN]   CoS Queue
 *\param    flags [IN]   Specifies configuration. Valid flags:
 *          OPENNSL_COSQ_GPORT_STATS_SHARED
 *\param    stat [IN]   See table =OPENNSL_COSQ_GPORT_STATISTICS_table .
 *\param    value [OUT]   statistic value
 *
 *\retval     OPENNSL_E_NONE
 *\retval     OPENNSL_E_UNAVAIL
 *\retval     OPENNSL_E_PARAM
 *\retval     OPENNSL_E_PORT
 ******************************************************************************/
extern int opennsl_cosq_gport_statistic_get(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_gport_t lgl_gport, 
    opennsl_cos_queue_t cosq, 
    uint32 flags, 
    opennsl_cosq_gport_stats_t stat, 
    uint64 *value) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Reset the value of a Central Statistics stat to zero.
 *
 *\description Reset a specific statistic value to zero. For Ingress physical
 *          statistics, gport must be set to a specific physical interface
 *          using OPENNSL_GPORT_TYPE_MODPORT and Ingress queue group must be
 *          OPENNSL_GPORT_TYPE_NONE. For a specific Egress statistic, Ingress
 *          queue group must always be OPENNSL_GPORT_TYPE_NONE. Physical
 *          egress statistics are associated with
 *          OPENNSL_GPORT_TYPE_EGRESS_MODPORT. Egress subport statistics are 
 *          associated with OPENNSL_GPORT_TYPE_EGRESS_CHILD. Egress FIFO
 *          statistics are  associated with OPENNSL_GPORT_TYPE_EGRESS_GROUP.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID for Ingress interface. Valid types:
 *          OPENNSL_GPORT_TYPE_MODPORT, OPENNSL_GPORT_TYPE_EGRESS_MODPORT,
 *          OPENNSL_GPORT_TYPE_EGRESS_CHILD, OPENNSL_GPORT_TYPE_EGRESS_GROUP
 *\param    lgl_gport [IN]   GPORT ID for Ingress queue group. Valid types:
 *          OPENNSL_GPORT_TYPE_UCAST_QUEUE_GROUP,
 *          OPENNSL_GPORT_TYPE_MAST_QUEUE_GROUP, OPENNSL_GPORT_TYPE_NONE
 *\param    cosq [IN]   CoS Queue
 *\param    flags [IN]   Specifies configuration. Valid flags:
 *          OPENNSL_COSQ_GPORT_STATS_SHARED
 *\param    stat [IN]   See table =OPENNSL_COSQ_GPORT_STATISTICS_table .
 *\param    value [IN]
 *
 *\retval     OPENNSL_E_NONE
 *\retval     OPENNSL_E_UNAVAIL
 *\retval     OPENNSL_E_PARAM
 *\retval     OPENNSL_E_PORT
 ******************************************************************************/
extern int opennsl_cosq_gport_statistic_set(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_gport_t lgl_gport, 
    opennsl_cos_queue_t cosq, 
    uint32 flags, 
    opennsl_cosq_gport_stats_t stat, 
    uint64 value) LIB_DLL_EXPORTED ;

#define OPENNSL_COSQ_GPORT_WITH_ID          0x00000001 
#define OPENNSL_COSQ_GPORT_SCHEDULER        0x00000002 
#define OPENNSL_COSQ_GPORT_OVERLAY          0x00000004 
#define OPENNSL_COSQ_GPORT_UCAST_QUEUE_GROUP 0x00000008 
#define OPENNSL_COSQ_GPORT_DESTMOD_UCAST_QUEUE_GROUP 0x00000010 
#define OPENNSL_COSQ_GPORT_MCAST_QUEUE      0x00000010 
#define OPENNSL_COSQ_GPORT_MCAST_QUEUE_GROUP 0x00000020 
#define OPENNSL_COSQ_GPORT_SUBSCRIBER       0x00000040 
#define OPENNSL_COSQ_GPORT_EGRESS_GROUP     0x00000080 
#define OPENNSL_COSQ_GPORT_DISABLE          0x00000100 /**< Disable queue, used
                                                          for
                                                          OPENNSL_COSQ_GPORT_CALENDAR
                                                          scheduling discipline */
/***************************************************************************//** 
 *\brief Allocate/Retrieve unicast queue group and scheduler queue group
 *       configuration.
 *
 *\description These APIs are used to allocate/retrieve unicast or multicast
 *          queue group or a scheduler queue group configuration. Scheduler
 *          queue groups are used to implement H-QoS. The set of CoS queues
 *          are uniquely identified with a GPORT ID, which represents the base
 *          CoS queue in the set. The GPORT ID is allocated from the next
 *          available queue in group of queues for the port or specified by
 *          the  input when the OPENNSL_COSQ_GPORT_WITH_ID flag is set. But
 *          the  flag OPENNSL_COSQ_GPORT_WITH_ID is only supported for a few
 *          devices. OPENNSL_GPORT_TYPE_UCAST_QUEUE_GROUP,
 *          OPENNSL_GPORT_TYPE_MCAST_QUEUE_GROUP, or
 *          OPENNSL_GPORT_TYPE_SCHEDULER type of GPORT can be added for
 *          hierarchical queuing (see also, =opennsl_cosq_gport_attach API).
 *          Depending on the functionality physical_port parameter can have
 *          one of the following values       unicast queue group   =>
 *          OPENNSL_GPORT_MODPORT_SET()            multicast queue group =>
 *          OPENNSL_GPORT_MODPORT_SET()            scheduler queue group =>
 *          OPENNSL_GPORT_NULL
 *          When allocating a queue group the req_gport parameter direction
 *          depends on the flags. If OPENNSL_COSQ_GPORT_WITH_ID is specified
 *          the input direction is valid. Depending on the functionality the
 *          following macros can be used to create the req_gport.      
 *          unicast queue group   => OPENNSL_GPORT_UCAST_QUEUE_GROUP_SET()    
 *                 multicast queue group =>
 *          OPENNSL_GPORT_MCAST_QUEUE_GROUP_SET()            scheduler queue
 *          group => OPENNSL_GPORT_SCHEDULER_SET()      req_gport parameter is
 *          always updated and should be subsequently used by the user.
 *          When the OPENNSL_COSQ_GPORT_WITH_ID flag is set, the value
 *          provided in the gport parameter is used as the GPORT ID, otherwise
 *          a unique GPORT ID will be allocated and returned. The feature
 *          using OPENNSL_COSQ_GPORT_WITH_ID to allocate a queue group is only
 *          supported for a few devices.
 *          For some devices that may not have the ability to shape every port
 *          or queue, the application can control whether the gport must be
 *          allocated from a shapeable or non-shapeable area.  This can be
 *          done by specifying the flags OPENNSL_COSQ_GPORT_WITH_SHAPING or
 *          OPENNSL_COSQ_GPORT_WITHOUT_SHAPING, respectively.  If neither flag
 *          is specified, the API will allocate a gport without paying any
 *          attention to whether it would be possible to configure a shaper on
 *          such port later.
 *          When the OPENNSL_COSQ_GPORT_OVERLAY flag is set, it allows overlay
 *          of queues that were previously allocated.
 *          When the OPENNSL_COSQ_GPORT_SUBSCRIBER flag is set, scheduling for
 *          the queue group will be done locally and will not involve the
 *          central arbiter. A local gport should be added only for ports
 *          which are local to that device.
 *          When the OPENNSL_COSQ_GPORT_MULTIPATH flag is set, a multipath
 *          shaper gport is created. Scheduler nodes  on the same level could
 *          be added to the multipath shaper gport. The aggregated traffic
 *          from all nodes is shaped by the multipath shaper. The shaping rate
 *          of multipath shaper is controlled by calling
 *          =opennsl_cosq_gport_bandwidth_set API with the multipath shaper
 *          gport
 *          When the config.opennsl variable fabric_egress_setup=0 is set,
 *          FIFO-level egress support becomes available.  The
 *          OPENNSL_COSQ_GPORT_EGRESS_GROUP flag is used to enable egress
 *          group support. Egress Group gports are similar to egress child
 *          gports in all other aspects. The egress group  gport connects a
 *          number of fifos to a subport and allows access at the FIFO-level.
 *          Multiple egress groups can be connected to the same subport up to
 *          sixteen fifos. In the case of egress gports, the num_cos_levels
 *          field is used to indicate the number of fifos to be associated
 *          with that egress gport.
 *          When the OPENNSL_COSQ_GPORT_DESTMOD_UCAST_QUEUE_GROUP flag is set,
 *          a set of virtual queue group (DMVOQ)  is allocated.
 *          On network switch chips, When the
 *          OPENNSL_COSQ_GPORT_DESTMOD_UCAST_QUEUE_GROUP flag is used with the
 *          combination of OPENNSL_COSQ_GPORT_WITH_ID,          the value
 *          provided in gport parameters is used as the GPORT_ID.          
 *          But scheduling mode need to programmed again as per the scheduling
 *          hierarchy.  API opennsl_cosq_port_sched_set() can be used to set
 *          the scheduling mode to be Strict/WRR.
 *          When the OPENNSL_COSQ_GPORT_VLAN_UCAST_QUEUE_GROUP flag is set, a
 *          queue to support service based queuing is allocated
 *          When a parent node is created by using opennsl_cosq_gport_add API
 *          call by passing num_cos_levels = -1 then that node can have any
 *          number of child nodes.
 *          On the chips network switch, default schedule hierarchies are set
 *          up at SDK initialization. Default schedule hierarchy elements
 *          cannot be managed except using non-gport APIs to configure COSQs
 *          at port level. The first call to the API opennsl_cosq_gport_add
 *          will destroy the default schedule hierarchies for all of ports and
 *          traffic will not flow on those ports until new schedule
 *          hierarchies for those ports are built.
 *          On the chips network switch and network switch API
 *          opennsl_cosq_gport_add return OPENNSL_E_PARAM because of fixed
 *          hierarchy. Gport tree is created during init. On the chips network
 *          switch and network switch because of fixed hierarchy scheduler the
 *          scope of COSQ GPORT is not global but it is local to per unit. So
 *          we should not modify the MODID dynamically.
 *          Some device configuration support multiple queue groups on a
 *          physical port.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   (for _add) GPORT ID physical port (For DNX, this should be
 *          local port)
 *\param    numq [IN]
 *\param    flags [IN]   (for _add) Specifies configuration. Valid flags listed at
 *          =OPENNSL_COSQ_GPORT_FLAGS_table
 *\param    gport [IN,OUT]   (for _get) GPORT ID for a queue group
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_add(
    int unit, 
    opennsl_gport_t port, 
    int numq, 
    uint32 flags, 
    opennsl_gport_t *gport) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Deletes queue group.
 *
 *\description Deletes queue group. It could be a unicast, scheduler or a
 *          multicast queue group.
 *          On the chips network switch and network switch API
 *          opennsl_cosq_gport_delete return OPENNSL_E_PARAM because of fixed
 *          hierarchy. Gport tree is created during init.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID of the queue group that has to be deleted
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_delete(
    int unit, 
    opennsl_gport_t gport) LIB_DLL_EXPORTED ;

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
 *          They can be used only on chips which support ETS(Enhanced
 *          Transmission Selection) feature regardless of that the ETS mode is
 *          enabled.
 *
 *\param    unit [IN]   Unit number.
 *\param    ing_port [IN]   Ingress device or logical port or GPORT ID
 *\param    int_pri [IN]
 *\param    flags [IN]   Can be one of following
 *          OPENNSL_COSQ_GPORT_UCAST_QUEUE_GROUP,
 *          OPENNSL_COSQ_GPORT_DESTMOD_UCAST_QUEUE_GROUP,
 *          OPENNSL_COSQ_GPORT_MCAST_QUEUE_GROUP
 *\param    gport [IN]   GPORT ID for a queue group
 *\param    cosq [IN]   CoS queue to which to map the chosen priority
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_PARAM
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_mapping_set(
    int unit, 
    opennsl_port_t ing_port, 
    opennsl_cos_t int_pri, 
    uint32 flags, 
    opennsl_gport_t gport, 
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
 *          They can be used only on chips which support ETS(Enhanced
 *          Transmission Selection) feature regardless of that the ETS mode is
 *          enabled.
 *
 *\param    unit [IN]   Unit number.
 *\param    ing_port [IN]   Ingress device or logical port or GPORT ID
 *\param    int_pri [IN]
 *\param    flags [IN]   Can be one of following
 *          OPENNSL_COSQ_GPORT_UCAST_QUEUE_GROUP,
 *          OPENNSL_COSQ_GPORT_DESTMOD_UCAST_QUEUE_GROUP,
 *          OPENNSL_COSQ_GPORT_MCAST_QUEUE_GROUP
 *\param    gport [OUT]   GPORT ID for a queue group
 *\param    cosq [OUT]   CoS queue to which to map the chosen priority
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_PARAM
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_mapping_get(
    int unit, 
    opennsl_port_t ing_port, 
    opennsl_cos_t int_pri, 
    uint32 flags, 
    opennsl_gport_t *gport, 
    opennsl_cos_queue_t *cosq) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure/Retrieve bandwidth setting.
 *
 *\description Configure/retrieve bandwidth setting. If OPENNSL_COSQ_ALL is
 *          specified the configuration applies to the entire queue group.
 *          On some devices, the bandwidth allocated to each CoS queue may be
 *          configured. The gport parameter can be a physical port, in which
 *          case the CoS queue specified by the cosq parameter is one of the
 *          default CoS queues assigned to the port during initialization.
 *          Alternatively, the gport parameter can  be a GPORT that was
 *          dynamically added with =opennsl_cosq_gport_add or.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID for a queue group
 *\param    cosq [IN]   CoS Queue
 *\param    kbits_sec_min [IN]   (for _set) CIR (Bandwidth guarantee)
 *\param    kbits_sec_max [IN]   (for _set) PIR (Traffic shaping)
 *\param    flags [IN]   (for _set) Specifies bandwidth configuration. Can be
 *          logical OR of of values defined in table  =OPENNSL_COSQ_BW_f
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_bandwidth_set(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_queue_t cosq, 
    uint32 kbits_sec_min, 
    uint32 kbits_sec_max, 
    uint32 flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure/Retrieve bandwidth setting.
 *
 *\description Configure/retrieve bandwidth setting. If OPENNSL_COSQ_ALL is
 *          specified the configuration applies to the entire queue group.
 *          On some devices, the bandwidth allocated to each CoS queue may be
 *          configured. The gport parameter can be a physical port, in which
 *          case the CoS queue specified by the cosq parameter is one of the
 *          default CoS queues assigned to the port during initialization.
 *          Alternatively, the gport parameter can  be a GPORT that was
 *          dynamically added with =opennsl_cosq_gport_add or.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID for a queue group
 *\param    cosq [IN]   CoS Queue
 *\param    kbits_sec_min [OUT]   (for _set) CIR (Bandwidth guarantee)
 *\param    kbits_sec_max [OUT]   (for _set) PIR (Traffic shaping)
 *\param    flags [OUT]   (for _set) Specifies bandwidth configuration. Can be
 *          logical OR of of values defined in table  =OPENNSL_COSQ_BW_f
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_bandwidth_get(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_queue_t cosq, 
    uint32 *kbits_sec_min, 
    uint32 *kbits_sec_max, 
    uint32 *flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure/retrieve scheduling policy.
 *
 *\description Configure/Retrieve scheduling modes.
 *          Set or Get the Class of Service policy and weight for the
 *          specified GPORT. The gport parameter can be a physical port, in
 *          which case the CoS queue specified by the cosq parameter is one of
 *          the default CoS queues assigned to the port during initialization.
 *          Alternatively, the gport parameter can  be a scheduler GPORT that
 *          was dynamically added with =opennsl_cosq_gport_add  or.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID for a queue group
 *\param    cosq [IN]   CoS Queue
 *\param    mode [IN]   (for _set) scheduling mode
 *\param    weight [IN]   (for _set) weight. This is applicable for some
 *          scheduling modes
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_sched_set(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_queue_t cosq, 
    int mode, 
    int weight) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure/retrieve scheduling policy.
 *
 *\description Configure/Retrieve scheduling modes.
 *          Set or Get the Class of Service policy and weight for the
 *          specified GPORT. The gport parameter can be a physical port, in
 *          which case the CoS queue specified by the cosq parameter is one of
 *          the default CoS queues assigned to the port during initialization.
 *          Alternatively, the gport parameter can  be a scheduler GPORT that
 *          was dynamically added with =opennsl_cosq_gport_add  or.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID for a queue group
 *\param    cosq [IN]   CoS Queue
 *\param    mode [OUT]   (for _set) scheduling mode
 *\param    weight [OUT]   (for _set) weight. This is applicable for some
 *          scheduling modes
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_sched_get(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_queue_t cosq, 
    int *mode, 
    int *weight) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure/Retrieve discard setting.
 *
 *\description Configures discard/WRED setting.  The port parameter can be a
 *          physical port, in which case the CoS queue specified by the cosq
 *          parameter is one of the default Cos queues assigned to the port
 *          during initialization. Alternatively, the port parameter can be a
 *          GPORT that was dynamically added with =opennsl_cosq_gport_add or.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID for a queue group
 *\param    cosq [IN]   CoS Queue
 *\param    discard [IN]   (for _set) discard configuration
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_discard_set(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_queue_t cosq, 
    opennsl_cosq_gport_discard_t *discard) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure/Retrieve discard setting.
 *
 *\description Configures discard/WRED setting.  The port parameter can be a
 *          physical port, in which case the CoS queue specified by the cosq
 *          parameter is one of the default Cos queues assigned to the port
 *          during initialization. Alternatively, the port parameter can be a
 *          GPORT that was dynamically added with =opennsl_cosq_gport_add or.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID for a queue group
 *\param    cosq [IN]   CoS Queue
 *\param    discard [IN,OUT]   (for _set) discard configuration
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_discard_get(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_queue_t cosq, 
    opennsl_cosq_gport_discard_t *discard) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Mapping/redirecting scheduling discipline to Egress FIFO.
 *
 *\description This API maps scheduling discipline to Egress FIFO. This is valid
 *          on XCore fabric devices. gport parameter value of
 *          OPENNSL_GPORT_INVALID configures a device wide setting.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   fabric gport
 *\param    sched_mode [IN]   scheduling discipline
 *\param    int_pri [IN]   internal priority on fabric device
 *\param    flags [IN]   (for _set) flags =SCHED_CONFIG_FLAGS_table
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_sched_config_set(
    int unit, 
    opennsl_gport_t gport, 
    int sched_mode, 
    int int_pri, 
    uint32 flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Mapping/redirecting scheduling discipline to Egress FIFO.
 *
 *\description This API maps scheduling discipline to Egress FIFO. This is valid
 *          on XCore fabric devices. gport parameter value of
 *          OPENNSL_GPORT_INVALID configures a device wide setting.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   fabric gport
 *\param    sched_mode [IN]   scheduling discipline
 *\param    int_pri [IN]   internal priority on fabric device
 *\param    flags [OUT]   (for _set) flags =SCHED_CONFIG_FLAGS_table
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_sched_config_get(
    int unit, 
    opennsl_gport_t gport, 
    int sched_mode, 
    int int_pri, 
    uint32 *flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Attach/Detach the output of a GPORT to the input of a scheduler GPORT.
 *
 *\description These APIs can be used to attach/detach a sched GPORT (sched_port)
 *          to the  parent GPORT (input_port) to form a queuing hierarchy. The
 *          connect is done at the specified CoS queue of the parent GPORT. A
 *          cosq value of -1 will attach the sched GPORT to the first unused
 *          CoS queue of the parent GPORT (going from higher to lower CoS
 *          queue priority).
 *          On the chip network switch: opennsl_cosq_gport_attach_get can be
 *          used to get the parent node gport and cosq value will represent
 *          the CoS queue value of the parent node i.e. the index at which
 *          parent is attached.
 *          opennsl_cosq_gport_attach and opennsl_cosq_gport_detach APIs are
 *          only supported for CPU port.
 *          CPU Queues needed to be mapped to CMC0 Channel 0 should be
 *          attached to 3rd index of L0 level scheduler node of CPU port. CPU
 *          Queues needed to be mapped to CMC0 Channel 1 should be attached to
 *          0th index of L0 level scheduler node of CPU port. CPU Queues
 *          needed to be mapped to CMC0 Channel 2 should be attached to 1st
 *          index of L0 level scheduler node of CPU port. CPU Queues needed to
 *          be mapped to CMC0 Channel 3 should be attached to 2nd index of L0
 *          level scheduler node of CPU port. CPU Queues needed to be mapped
 *          to CMC1 Channel 1 should be attached to 7th index of L0 level
 *          scheduler node of CPU port. CPU Queues needed to be mapped to CMC2
 *          Channel 1 should be attached to 8th index of L0 level scheduler
 *          node of CPU port. And CPU Queues after detach using
 *          opennsl_cosq_gport_detach API will get attached to 9th index of L0
 *          level scheduler node CPU port.
 *
 *\param    unit [IN]   Unit number.
 *\param    sched_port [IN]   GPORT ID that gets attached to input_port
 *\param    input_port [IN]   GPORT ID to which sched_port gets attached
 *\param    cosq [IN]   CoS queue to attach to
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_cosq_gport_attach(
    int unit, 
    opennsl_gport_t sched_port, 
    opennsl_gport_t input_port, 
    opennsl_cos_queue_t cosq) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Attach/Detach the output of a GPORT to the input of a scheduler GPORT.
 *
 *\description These APIs can be used to attach/detach a sched GPORT (sched_port)
 *          to the  parent GPORT (input_port) to form a queuing hierarchy. The
 *          connect is done at the specified CoS queue of the parent GPORT. A
 *          cosq value of -1 will attach the sched GPORT to the first unused
 *          CoS queue of the parent GPORT (going from higher to lower CoS
 *          queue priority).
 *          On the chip network switch: opennsl_cosq_gport_attach_get can be
 *          used to get the parent node gport and cosq value will represent
 *          the CoS queue value of the parent node i.e. the index at which
 *          parent is attached.
 *          opennsl_cosq_gport_attach and opennsl_cosq_gport_detach APIs are
 *          only supported for CPU port.
 *          CPU Queues needed to be mapped to CMC0 Channel 0 should be
 *          attached to 3rd index of L0 level scheduler node of CPU port. CPU
 *          Queues needed to be mapped to CMC0 Channel 1 should be attached to
 *          0th index of L0 level scheduler node of CPU port. CPU Queues
 *          needed to be mapped to CMC0 Channel 2 should be attached to 1st
 *          index of L0 level scheduler node of CPU port. CPU Queues needed to
 *          be mapped to CMC0 Channel 3 should be attached to 2nd index of L0
 *          level scheduler node of CPU port. CPU Queues needed to be mapped
 *          to CMC1 Channel 1 should be attached to 7th index of L0 level
 *          scheduler node of CPU port. CPU Queues needed to be mapped to CMC2
 *          Channel 1 should be attached to 8th index of L0 level scheduler
 *          node of CPU port. And CPU Queues after detach using
 *          opennsl_cosq_gport_detach API will get attached to 9th index of L0
 *          level scheduler node CPU port.
 *
 *\param    unit [IN]   Unit number.
 *\param    sched_port [IN]   GPORT ID that gets attached to input_port
 *\param    input_port [IN]   GPORT ID to which sched_port gets attached
 *\param    cosq [IN]   CoS queue to attach to
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_cosq_gport_detach(
    int unit, 
    opennsl_gport_t sched_port, 
    opennsl_gport_t input_port, 
    opennsl_cos_queue_t cosq) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Attach/Detach the output of a GPORT to the input of a scheduler GPORT.
 *
 *\description These APIs can be used to attach/detach a sched GPORT (sched_port)
 *          to the  parent GPORT (input_port) to form a queuing hierarchy. The
 *          connect is done at the specified CoS queue of the parent GPORT. A
 *          cosq value of -1 will attach the sched GPORT to the first unused
 *          CoS queue of the parent GPORT (going from higher to lower CoS
 *          queue priority).
 *          On the chip network switch: opennsl_cosq_gport_attach_get can be
 *          used to get the parent node gport and cosq value will represent
 *          the CoS queue value of the parent node i.e. the index at which
 *          parent is attached.
 *          opennsl_cosq_gport_attach and opennsl_cosq_gport_detach APIs are
 *          only supported for CPU port.
 *          CPU Queues needed to be mapped to CMC0 Channel 0 should be
 *          attached to 3rd index of L0 level scheduler node of CPU port. CPU
 *          Queues needed to be mapped to CMC0 Channel 1 should be attached to
 *          0th index of L0 level scheduler node of CPU port. CPU Queues
 *          needed to be mapped to CMC0 Channel 2 should be attached to 1st
 *          index of L0 level scheduler node of CPU port. CPU Queues needed to
 *          be mapped to CMC0 Channel 3 should be attached to 2nd index of L0
 *          level scheduler node of CPU port. CPU Queues needed to be mapped
 *          to CMC1 Channel 1 should be attached to 7th index of L0 level
 *          scheduler node of CPU port. CPU Queues needed to be mapped to CMC2
 *          Channel 1 should be attached to 8th index of L0 level scheduler
 *          node of CPU port. And CPU Queues after detach using
 *          opennsl_cosq_gport_detach API will get attached to 9th index of L0
 *          level scheduler node CPU port.
 *
 *\param    unit [IN]   Unit number.
 *\param    sched_port [IN]   GPORT ID that gets attached to input_port
 *\param    input_port [OUT]   GPORT ID to which sched_port gets attached
 *\param    cosq [OUT]   CoS queue to attach to
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_cosq_gport_attach_get(
    int unit, 
    opennsl_gport_t sched_port, 
    opennsl_gport_t *input_port, 
    opennsl_cos_queue_t *cosq) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the child node GPORT atatched to N-th index (cosq) of the scheduler
 *       GPORT.
 *
 *\description This API can be used to get child node GPORT atatched to N-th
 *          index (cosq) of the scheduler GPORT.
 *
 *\param    unit [IN]   Unit number.
 *\param    in_gport [IN]   Scheduler GPORT ID
 *\param    cosq [IN]   COS queue attached to.
 *\param    out_gport [OUT]   Child GPORT ID.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_child_get(
    int unit, 
    opennsl_gport_t in_gport, 
    opennsl_cos_queue_t cosq, 
    opennsl_gport_t *out_gport) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure/retrieve {traffic class, dp} mapping to egress queue on a
 *       port.
 *
 *\description Configure/retrieve {traffic class, dp} mapping to egress queue on
 *          a port. The gport identifies the underlying resource. The resource
 *          will be either Unicast or Multicast egress queues for a port.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   gport referencing unicast or multicast egress queues on a
 *          port
 *\param    ingress_pri [IN]   packet priority/traffic class
 *\param    ingress_dp [IN]   packet drop precedence
 *\param    offset [IN]   (for _set) queue offset from base
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_egress_map_set(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_t ingress_pri, 
    opennsl_color_t ingress_dp, 
    opennsl_cos_queue_t offset) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure/retrieve {traffic class, dp} mapping to egress queue on a
 *       port.
 *
 *\description Configure/retrieve {traffic class, dp} mapping to egress queue on
 *          a port. The gport identifies the underlying resource. The resource
 *          will be either Unicast or Multicast egress queues for a port.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   gport referencing unicast or multicast egress queues on a
 *          port
 *\param    ingress_pri [IN]   packet priority/traffic class
 *\param    ingress_dp [IN]   packet drop precedence
 *\param    offset [OUT]   (for _set) queue offset from base
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_egress_map_get(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_t ingress_pri, 
    opennsl_color_t ingress_dp, 
    opennsl_cos_queue_t *offset) LIB_DLL_EXPORTED ;

#define OPENNSL_COSQ_MULTICAST_SCHEDULED    0x00000001 /**< multicast scheduled
                                                          values are valid */
/** multicast configuration settings */
typedef struct opennsl_cosq_egress_multicast_config_s {
    opennsl_color_t scheduled_dp;   /**< drop precedence */
    opennsl_cos_t priority;         /**< TC */
    int unscheduled_se;             /**< shared resource eligibility */
    int unscheduled_sp;             /**< service pool ID */
} opennsl_cosq_egress_multicast_config_t;

/***************************************************************************//** 
 *\brief Configure/retrieve {traffic class, dp} mapping to multicast egress
 *       configuration on a port.
 *
 *\description Configure/retrieve {traffic class, dp} mapping to multicast egress
 *          configuration on a port. The gport identifies the underlying
 *          resource. The resource will be local gport. When gport is local
 *          port, flags should be OPENNSL_COSQ_MULTICAST_SCHEDULED, and only
 *          scheduled fields of opennsl_cosq_egress_multicast_config_t
 *          structure are valid. When gport is null, flags should be
 *          OPENNSL_COSQ_MULTICAST_UNSCHEDULED, and only unscheduled fields of
 *          opennsl_cosq_egress_multicast_config_t structure are valid.
 *          Gport parameter identifies the mapping to be for scheduled
 *          multicast or unscheduled multicast. The flags parameter is
 *          redundant. However the flag value identifies what fields of
 *          opennsl_cosq_egress_multicast_config_t structure are valid.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   gport referencing unicast or multicast egress queues on a
 *          port
 *\param    ingress_pri [IN]   packet priority/traffic class
 *\param    ingress_dp [IN]   packet drop precedence
 *\param    flags [IN]   Specifies configuration. Valid flags:
 *          OPENNSL_COSQ_MULTICAST_SCHEDULED, OPENNSL_COSQ_MULTICAST_UNSCHEDULED
 *\param    config [IN]   (for _set)  multicast egress configuration
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_egress_multicast_config_set(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_t ingress_pri, 
    opennsl_color_t ingress_dp, 
    uint32 flags, 
    opennsl_cosq_egress_multicast_config_t *config) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure/retrieve {traffic class, dp} mapping to multicast egress
 *       configuration on a port.
 *
 *\description Configure/retrieve {traffic class, dp} mapping to multicast egress
 *          configuration on a port. The gport identifies the underlying
 *          resource. The resource will be local gport. When gport is local
 *          port, flags should be OPENNSL_COSQ_MULTICAST_SCHEDULED, and only
 *          scheduled fields of opennsl_cosq_egress_multicast_config_t
 *          structure are valid. When gport is null, flags should be
 *          OPENNSL_COSQ_MULTICAST_UNSCHEDULED, and only unscheduled fields of
 *          opennsl_cosq_egress_multicast_config_t structure are valid.
 *          Gport parameter identifies the mapping to be for scheduled
 *          multicast or unscheduled multicast. The flags parameter is
 *          redundant. However the flag value identifies what fields of
 *          opennsl_cosq_egress_multicast_config_t structure are valid.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   gport referencing unicast or multicast egress queues on a
 *          port
 *\param    ingress_pri [IN]   packet priority/traffic class
 *\param    ingress_dp [IN]   packet drop precedence
 *\param    flags [IN]   Specifies configuration. Valid flags:
 *          OPENNSL_COSQ_MULTICAST_SCHEDULED, OPENNSL_COSQ_MULTICAST_UNSCHEDULED
 *\param    config [OUT]   (for _set)  multicast egress configuration
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_egress_multicast_config_get(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_t ingress_pri, 
    opennsl_color_t ingress_dp, 
    uint32 flags, 
    opennsl_cosq_egress_multicast_config_t *config) LIB_DLL_EXPORTED ;

/** cosq gport type eumerations */
typedef enum opennsl_cosq_gport_type_e {
    opennslCosqGportTypeUnicastEgress = 1, /**< Unicast Egress Queues - Port
                                           hierarchy */
    opennslCosqGportTypeMulticastEgress = 2, /**< Multicast Egress Queues - Port
                                           Hierarchy */
    opennslCosqGportTypeLocalPort = 6,  /**< Ports in Egress transmit hierarchy */
} opennsl_cosq_gport_type_t;

/** gport information related to getting a handle */
typedef struct opennsl_cosq_gport_info_s {
    opennsl_gport_t in_gport;   /**< gport to be converted. NULL for global gports
                                   (i.e. single instance on a device) */
    opennsl_cos_queue_t cosq;   /**< Num of cosq levels */
    opennsl_gport_t out_gport;  /**< retreived gport */
} opennsl_cosq_gport_info_t;

/***************************************************************************//** 
 *\brief Getting a gport handle.
 *
 *\description Getting a gport handle. This could be either a global gport
 *          (single instance on a device) or converting a gport to the desired
 *          type .
 *
 *\param    unit [IN]   Unit number.
 *\param    gport_type [IN]   gport type.  see table =OPENNSL_COSQ_GPORT_type
 *\param    gport_info [IN,OUT]   gport info.  see table
 *          =OPENNSL_COSQ_GPORT_INFO_table in_gport parameter is an input
 *          parameter
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_gport_handle_get(
    int unit, 
    opennsl_cosq_gport_type_t gport_type, 
    opennsl_cosq_gport_info_t *gport_info) LIB_DLL_EXPORTED ;

/** XGS3 cosq counters */
typedef enum opennsl_cosq_stat_e {
    opennslCosqStatDroppedPackets = 0,  /**< Dropped packet count. */
    opennslCosqStatDroppedBytes = 1,    /**< Dropped byte count. */
    opennslCosqStatYellowCongestionDroppedPackets = 2, /**< Dropped yellow packets due to
                                           congestion. */
    opennslCosqStatRedCongestionDroppedPackets = 3, /**< Dropped red packets due to
                                           congestion. */
    opennslCosqStatGreenDiscardDroppedPackets = 4, /**< WRED green packets. */
    opennslCosqStatYellowDiscardDroppedPackets = 5, /**< WRED yellow packets. */
    opennslCosqStatRedDiscardDroppedPackets = 6, /**< WRED red packets. */
    opennslCosqStatOutPackets = 7,      /**< Transmit packet count. */
    opennslCosqStatOutBytes = 8,        /**< Transmit byte count. */
} opennsl_cosq_stat_t;

/***************************************************************************//** 
 *\brief Retrieve/set various MMU statistics based on stat type.
 *
 *\description Retrieve/set various MMU statistics. The type opennsl_cosq_stat_t
 *          is an enumeration of the available statistics. For _get functions,
 *          if the given cosq is -1, then the sum of the values of all the
 *          given port's CoS queues will be returned. For _set functions, if
 *          the given cosq is -1, the value of the port's first CoS queue will
 *          be set to the given value; the value of the port's all other CoS
 *          queues will be kept as untouched except for device network switch,
 *          on which the value of the port's all other CoS queues will be set
 *          to zero.
 *          When setting the non-zero value, if the device supports separate
 *          unicast and multicast queues, the value being set is evenly
 *          distributed between unicast and multicast counter.
 *          This is applicable to switch family-III devices only.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID.
 *\param    cosq [IN]   CoS Queue.
 *\param    stat [IN]   Statistic to be retrieved. See table
 *          =OPENNSL_COSQ_STAT_table .
 *\param    value [OUT]   (for _get) statistic value.
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_stat_get(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_queue_t cosq, 
    opennsl_cosq_stat_t stat, 
    uint64 *value) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Force an immediate counter update and retrieve various MMU statistics.
 *
 *\description Similar to opennsl_cosq_stat_get(), value returned is software
 *          accumulated  counter synced with the hardware counter.
 *          On the chip network switch, for stat
 *          opennslCosqStatOutPackets/opennslCosqStatOutBytes because of clear
 *          on read implementation in hardware, opennsl_cosq_stat_sync_get on
 *          OutPackets will have impact on OutBytes counters and vice-versa.
 *          Hence recommendation is to use  opennsl_stat_sync(unit) api before
 *          the opennsl_cosq_stat_get API instead of using 
 *          opennsl_cosq_stat_sync_get API.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID.
 *\param    cosq [IN]   CoS Queue.
 *\param    stat [IN]   Statistic to be retrieved. See table
 *          =OPENNSL_COSQ_STAT_table .
 *\param    value [OUT]   (for _get) statistic value.
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_stat_sync_get(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_queue_t cosq, 
    opennsl_cosq_stat_t stat, 
    uint64 *value) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Retrieve/set various MMU statistics based on stat type.
 *
 *\description Retrieve/set various MMU statistics. The type opennsl_cosq_stat_t
 *          is an enumeration of the available statistics. For _get functions,
 *          if the given cosq is -1, then the sum of the values of all the
 *          given port's CoS queues will be returned. For _set functions, if
 *          the given cosq is -1, the value of the port's first CoS queue will
 *          be set to the given value; the value of the port's all other CoS
 *          queues will be kept as untouched except for device network switch,
 *          on which the value of the port's all other CoS queues will be set
 *          to zero.
 *          When setting the non-zero value, if the device supports separate
 *          unicast and multicast queues, the value being set is evenly
 *          distributed between unicast and multicast counter.
 *          This is applicable to switch family-III devices only.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID.
 *\param    cosq [IN]   CoS Queue.
 *\param    stat [IN]   Statistic to be retrieved. See table
 *          =OPENNSL_COSQ_STAT_table .
 *\param    value [IN]   (for _get) statistic value.
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_cosq_stat_set(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_cos_queue_t cosq, 
    opennsl_cosq_stat_t stat, 
    uint64 value) LIB_DLL_EXPORTED ;

#if defined(INCLUDE_TCB)
#endif
#if defined(INCLUDE_TCB)
#endif
#if defined(INCLUDE_TCB)
#endif
#endif /* __OPENNSL_COSQX_H__ */
/*@}*/
