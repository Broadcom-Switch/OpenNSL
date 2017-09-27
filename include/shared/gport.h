/*********************************************************************
 *
 * (C) Copyright Broadcom Corporation 2013-2017
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 **********************************************************************
 * File:        gport.h
 * Details:     This file defines gport (generic port) parameters.
 *
 *             Its contents are not used directly by applications;
 *             it is used only by header files of parent APIs which
 *             need to define error codes.
 *********************************************************************/

#ifndef _SHR_GPORT_H
#define _SHR_GPORT_H

/*
 * Defines:
 *     _SHR_GPORT_*
 * Purpose:
 *     GPORT (Generic port) definitions. GPORT can be used to specify
 *     a {module, port} pair, trunk, and other port types.
 */

#define _SHR_GPORT_NONE             (0)
#define _SHR_GPORT_INVALID         (-1)

#define _SHR_GPORT_TYPE_LOCAL               1  /* Port on local unit     */
#define _SHR_GPORT_TYPE_MODPORT             2  /* Module ID and port     */
#define _SHR_GPORT_TYPE_TRUNK               3  /* Trunk ID               */
#define _SHR_GPORT_TYPE_BLACK_HOLE          4   /* Black hole destination */
#define _SHR_GPORT_TYPE_LOCAL_CPU           5  /* CPU destination        */
#define _SHR_GPORT_TYPE_UCAST_QUEUE_GROUP   9  /* Queue Group            */
#define _SHR_GPORT_TYPE_MCAST              11  /* Multicast Set          */
#define _SHR_GPORT_TYPE_MCAST_QUEUE_GROUP  12  /* Multicast Queue Group  */
#define _SHR_GPORT_TYPE_SCHEDULER          13  /* Scheduler              */
#define _SHR_GPORT_TYPE_MIRROR             15  /* Mirror destination.    */
#define _SHR_GPORT_TYPE_TUNNEL             19  /* Tunnel ID              */
#define _SHR_GPORT_TYPE_CHILD              20  /* Child port             */
#define _SHR_GPORT_TYPE_EGRESS_GROUP       21  /* Egress group port      */
#define _SHR_GPORT_TYPE_EGRESS_CHILD       22  /* Egress child port      */
#define _SHR_GPORT_TYPE_EGRESS_MODPORT     23  /* Egress Mod and port    */
#define _SHR_GPORT_TYPE_UCAST_SUBSCRIBER_QUEUE_GROUP  24  /* Local Queue Group */
#define _SHR_GPORT_TYPE_MCAST_SUBSCRIBER_QUEUE_GROUP  25  /* Local Multicast Queue Group  */
#define _SHR_GPORT_TYPE_SYSTEM_PORT        27  /* DPP System-Port        */ 
#define _SHR_GPORT_TYPE_COSQ               30  /* cosq gport */
#define _SHR_GPORT_TYPE_PROFILE            40
#define _SHR_GPORT_TYPE_DESTMOD_QUEUE_GROUP      41 /* DMVOQ gport */

/* definitions for cosq core handling */
#define _SHR_COSQ_GPORT_COMMON_QUEUE_BITS 18
#define _SHR_COSQ_GPORT_COMMON_QUEUE_MASK ((1 << _SHR_COSQ_GPORT_COMMON_QUEUE_BITS) - 1)
#define _SHR_COSQ_GPORT_COMMON_CORE_BITS 3
#define _SHR_COSQ_GPORT_COMMON_CORE_SHIFT _SHR_COSQ_GPORT_COMMON_QUEUE_BITS
#define _SHR_COSQ_GPORT_COMMON_CORE_MASK ((1 << _SHR_COSQ_GPORT_COMMON_CORE_BITS) - 1)
#define _SHR_COSQ_GPORT_COMMON_ALL_CORES_VALUE _SHR_COSQ_GPORT_COMMON_CORE_MASK
/*
 * Note that only the bits under _SHR_COSQ_GPORT_CORE_MASK are considred
 * See, e.g. _SHR_COSQ_GPORT_CORE_GET
 */
#define _SHR_CORE_ALL -17
#define _SHR_CORE_FIELD2ID(field) ((field) != _SHR_COSQ_GPORT_COMMON_ALL_CORES_VALUE ? field : _SHR_CORE_ALL)
#define _SHR_CORE_ID2FIELD(id) ((id) != _SHR_CORE_ALL ? id : _SHR_COSQ_GPORT_COMMON_ALL_CORES_VALUE)

#define _SHR_GPORT_TYPE_SHIFT                           26
#define _SHR_GPORT_TYPE_MASK                            0x3f
#define _SHR_GPORT_MODID_SHIFT                          11
#define _SHR_GPORT_MODID_MASK                           0x7fff
#define _SHR_GPORT_PORT_SHIFT                           0
#define _SHR_GPORT_PORT_MASK                            0x7ff
#define _SHR_GPORT_TRUNK_SHIFT                          0
#define _SHR_GPORT_TRUNK_MASK                           0x3ffffff
#define _SHR_GPORT_UCAST_QUEUE_GROUP_SHIFT              0
#define _SHR_GPORT_UCAST_QUEUE_GROUP_MASK               0x3ffffff
#define _SHR_GPORT_UCAST_QUEUE_GROUP_QID_SHIFT          0
#define _SHR_GPORT_UCAST_QUEUE_GROUP_QID_MASK           0x3fff
#define _SHR_GPORT_UCAST_QUEUE_GROUP_SYSPORTID_SHIFT    14
#define _SHR_GPORT_UCAST_QUEUE_GROUP_SYSPORTID_MASK     0xfff
#define _SHR_GPORT_MCAST_QUEUE_GROUP_QID_SHIFT          0
#define _SHR_GPORT_MCAST_QUEUE_GROUP_QID_MASK           0x3fff
#define _SHR_GPORT_MCAST_QUEUE_GROUP_SYSPORTID_SHIFT    14
#define _SHR_GPORT_MCAST_QUEUE_GROUP_SYSPORTID_MASK     0xfff
#define _SHR_GPORT_SCHEDULER_SHIFT                      0
#define _SHR_GPORT_SCHEDULER_MASK                       0x7fffff
#define _SHR_GPORT_SCHEDULER_CORE_SHIFT                 23
#define _SHR_GPORT_SCHEDULER_CORE_MASK                  _SHR_COSQ_GPORT_COMMON_CORE_MASK
#define _SHR_GPORT_SCHEDULER_NODE_SHIFT                 0
#define _SHR_GPORT_SCHEDULER_NODE_MASK                  0xfffff
#define _SHR_GPORT_MIRROR_SHIFT                         0
#define _SHR_GPORT_MIRROR_MASK                          0xffff
#define _SHR_GPORT_TUNNEL_SHIFT                         0
#define _SHR_GPORT_TUNNEL_MASK                          0x3ffffff
#define _SHR_GPORT_SYSTEM_PORT_SHIFT                    0
#define _SHR_GPORT_SYSTEM_PORT_MASK                     0xffffff

#define _SHR_GPORT_TYPE_TRAP                            ((_SHR_GPORT_TYPE_LOCAL_CPU << 1) | 1) /* This will mark the CPU type, and
                                                                                                  the 1st bit in the value to indicate trap */
#define _SHR_GPORT_TYPE_TRAP_SHIFT                      (_SHR_GPORT_TYPE_SHIFT-1)   /* 25 */
#define _SHR_GPORT_TYPE_TRAP_MASK                       (_SHR_GPORT_TYPE_MASK<<1|1)     /* 0x4f */
#define _SHR_GPORT_TRAP_ID_SHIFT                         0
#define _SHR_GPORT_TRAP_ID_MASK                          0xfff
#define _SHR_GPORT_TRAP_STRENGTH_SHIFT                       12
#define _SHR_GPORT_TRAP_STRENGTH_MASK                        0xf
#define _SHR_GPORT_TRAP_SNOOP_STRENGTH_SHIFT             16
#define _SHR_GPORT_TRAP_SNOOP_STRENGTH_MASK              0xf

#define _SHR_GPORT_LOCAL_TYPE_COMMON (0)
#define _SHR_GPORT_LOCAL_TYPE_FABRIC (1)
#define _SHR_GPORT_LOCAL_TYPE_SHIFT (21)
#define _SHR_GPORT_LOCAL_TYPE_MASK (0x1f) 

#define _SHR_GPORT_IS_LOCAL(_gport) \
        (((((_gport) >> _SHR_GPORT_TYPE_SHIFT) & _SHR_GPORT_TYPE_MASK) == \
          _SHR_GPORT_TYPE_LOCAL) && \
        ((((_gport) >> _SHR_GPORT_LOCAL_TYPE_SHIFT) & _SHR_GPORT_LOCAL_TYPE_MASK) == \
          _SHR_GPORT_LOCAL_TYPE_COMMON)) 

#define _SHR_GPORT_LOCAL_SET(_gport, _port)\
        ((_gport) = (_SHR_GPORT_TYPE_LOCAL << _SHR_GPORT_TYPE_SHIFT) |\
        (_SHR_GPORT_LOCAL_TYPE_COMMON << _SHR_GPORT_LOCAL_TYPE_SHIFT)|\
        (((_port) & _SHR_GPORT_PORT_MASK) << _SHR_GPORT_PORT_SHIFT))

#define _SHR_GPORT_LOCAL_GET(_gport) \
        (((_gport) >> _SHR_GPORT_PORT_SHIFT) & _SHR_GPORT_PORT_MASK) 

#define _SHR_GPORT_IS_MODPORT(_gport)    \
        (((_gport) >> _SHR_GPORT_TYPE_SHIFT) == _SHR_GPORT_TYPE_MODPORT)

#define _SHR_GPORT_MODPORT_SET(_gport, _module, _port)                       \
        ((_gport) = (_SHR_GPORT_TYPE_MODPORT   << _SHR_GPORT_TYPE_SHIFT)   | \
         (((_module) & _SHR_GPORT_MODID_MASK)  << _SHR_GPORT_MODID_SHIFT)  | \
         (((_port) & _SHR_GPORT_PORT_MASK)     << _SHR_GPORT_PORT_SHIFT))

#define _SHR_GPORT_MODPORT_MODID_GET(_gport)    \
        (((_gport) >> _SHR_GPORT_MODID_SHIFT) & _SHR_GPORT_MODID_MASK)

#define _SHR_GPORT_MODPORT_PORT_GET(_gport)     \
        (((_gport) >> _SHR_GPORT_PORT_SHIFT) & _SHR_GPORT_PORT_MASK)

#define _SHR_GPORT_IS_TRUNK(_gport)    \
        (((_gport) >> _SHR_GPORT_TYPE_SHIFT) == _SHR_GPORT_TYPE_TRUNK)

#define _SHR_GPORT_TRUNK_SET(_gport, _trunk_id)                              \
        ((_gport) = (_SHR_GPORT_TYPE_TRUNK      << _SHR_GPORT_TYPE_SHIFT)  | \
         (((_trunk_id) & _SHR_GPORT_TRUNK_MASK) << _SHR_GPORT_TRUNK_SHIFT))

#define _SHR_GPORT_TRUNK_GET(_gport)   \
        (((_gport) >> _SHR_GPORT_TRUNK_SHIFT) & _SHR_GPORT_TRUNK_MASK)

#define _SHR_GPORT_IS_SCHEDULER(_gport)    \
        (((_gport) >> _SHR_GPORT_TYPE_SHIFT) == _SHR_GPORT_TYPE_SCHEDULER)

#define _SHR_GPORT_SCHEDULER_SET(_gport, _id)                            \
         _SHR_GPORT_SCHEDULER_CORE_SET(_gport, _id, _SHR_CORE_ALL)

#define _SHR_GPORT_SCHEDULER_GET(_gport)   \
         (((_gport) >> _SHR_GPORT_SCHEDULER_SHIFT) & _SHR_GPORT_SCHEDULER_MASK)

#define  _SHR_GPORT_SCHEDULER_CORE_GET(_gport) \
        _SHR_CORE_FIELD2ID((((_gport) >> _SHR_GPORT_SCHEDULER_CORE_SHIFT) & _SHR_GPORT_SCHEDULER_CORE_MASK))

#define _SHR_GPORT_SCHEDULER_CORE_SET(_gport, _scheduler_id, _core_id)       \
        ((_gport) = (_SHR_GPORT_TYPE_SCHEDULER << _SHR_GPORT_TYPE_SHIFT)  | \
        (((_scheduler_id) & _SHR_GPORT_SCHEDULER_MASK) << _SHR_GPORT_SCHEDULER_SHIFT) | \
        (((_SHR_CORE_ID2FIELD(_core_id)) & _SHR_GPORT_SCHEDULER_CORE_MASK) << _SHR_GPORT_SCHEDULER_CORE_SHIFT))

#define _SHR_GPORT_SCHEDULER_NODE_SET(_gport, _level, _node)    \
         ((_gport) = (_SHR_GPORT_TYPE_SCHEDULER << _SHR_GPORT_TYPE_SHIFT)  | \
          (((_level) & _SHR_GPORT_SCHEDULER_LEVEL_MASK) << _SHR_GPORT_SCHEDULER_LEVEL_SHIFT) | \
          (((_node) & _SHR_GPORT_SCHEDULER_NODE_MASK) << _SHR_GPORT_SCHEDULER_NODE_SHIFT))

#define _SHR_GPORT_SCHEDULER_NODE_GET(_gport)   \
         (((_gport) >> _SHR_GPORT_SCHEDULER_NODE_SHIFT) & _SHR_GPORT_SCHEDULER_NODE_MASK)

#define _SHR_GPORT_BLACK_HOLE    \
        (_SHR_GPORT_TYPE_BLACK_HOLE << _SHR_GPORT_TYPE_SHIFT)

#define _SHR_GPORT_IS_BLACK_HOLE(_gport)  ((_gport) == _SHR_GPORT_BLACK_HOLE)

#define _SHR_GPORT_LOCAL_CPU        \
        (_SHR_GPORT_TYPE_LOCAL_CPU << _SHR_GPORT_TYPE_SHIFT)

#define _SHR_GPORT_IS_UCAST_QUEUE_GROUP(_gport)    \
        (((_gport) >> _SHR_GPORT_TYPE_SHIFT) == _SHR_GPORT_TYPE_UCAST_QUEUE_GROUP)

#define _SHR_GPORT_UCAST_QUEUE_GROUP_SET(_gport, _qid)                           \
             _SHR_GPORT_UCAST_QUEUE_GROUP_SYSQID_SET(_gport,                      \
             _SHR_GPORT_UCAST_QUEUE_GROUP_SYSPORTID_MASK, \
              _qid)

#define _SHR_GPORT_UCAST_QUEUE_GROUP_SYSQID_SET(_gport, _sysport_id, _qid)                       \
        ((_gport) = (_SHR_GPORT_TYPE_UCAST_QUEUE_GROUP << _SHR_GPORT_TYPE_SHIFT)   | \
         (((_sysport_id) & _SHR_GPORT_UCAST_QUEUE_GROUP_SYSPORTID_MASK)  << _SHR_GPORT_UCAST_QUEUE_GROUP_SYSPORTID_SHIFT)  | \
         (((_qid) & _SHR_GPORT_UCAST_QUEUE_GROUP_QID_MASK)     << _SHR_GPORT_UCAST_QUEUE_GROUP_QID_SHIFT))

#define _SHR_GPORT_UCAST_QUEUE_GROUP_SYSPORTID_GET(_gport)                       \
        (((_gport) >> _SHR_GPORT_UCAST_QUEUE_GROUP_SYSPORTID_SHIFT) & _SHR_GPORT_UCAST_QUEUE_GROUP_SYSPORTID_MASK)

#define _SHR_GPORT_UCAST_QUEUE_GROUP_QID_GET(_gport)                       \
        (((_gport) >> _SHR_GPORT_UCAST_QUEUE_GROUP_QID_SHIFT) & _SHR_GPORT_UCAST_QUEUE_GROUP_QID_MASK)

#define _SHR_GPORT_IS_MCAST_QUEUE_GROUP(_gport) \
        (((_gport) >> _SHR_GPORT_TYPE_SHIFT) == _SHR_GPORT_TYPE_MCAST_QUEUE_GROUP)

#define _SHR_GPORT_MCAST_QUEUE_GROUP_SET(_gport, _qid)            \
        _SHR_GPORT_MCAST_QUEUE_GROUP_SYSQID_SET(_gport,           \
        _SHR_GPORT_MCAST_QUEUE_GROUP_SYSPORTID_MASK,              \
         _qid)

#define _SHR_GPORT_MCAST_QUEUE_GROUP_GET(_gport)   \
        _SHR_GPORT_MCAST_QUEUE_GROUP_QID_GET(_gport)

#define _SHR_GPORT_MCAST_QUEUE_GROUP_SYSQID_SET(_gport, _sysport_id, _qid)                       \
        ((_gport) = (_SHR_GPORT_TYPE_MCAST_QUEUE_GROUP << _SHR_GPORT_TYPE_SHIFT)   | \
         (((_sysport_id) & _SHR_GPORT_MCAST_QUEUE_GROUP_SYSPORTID_MASK)  << _SHR_GPORT_MCAST_QUEUE_GROUP_SYSPORTID_SHIFT)  | \
         (((_qid) & _SHR_GPORT_MCAST_QUEUE_GROUP_QID_MASK)     << _SHR_GPORT_MCAST_QUEUE_GROUP_QID_SHIFT))

#define _SHR_GPORT_MCAST_QUEUE_GROUP_SYSPORTID_GET(_gport)                       \
        (((_gport) >> _SHR_GPORT_MCAST_QUEUE_GROUP_SYSPORTID_SHIFT) & _SHR_GPORT_MCAST_QUEUE_GROUP_SYSPORTID_MASK)

#define _SHR_GPORT_MCAST_QUEUE_GROUP_QID_GET(_gport)                       \
         (((_gport) >> _SHR_GPORT_MCAST_QUEUE_GROUP_QID_SHIFT) & _SHR_GPORT_MCAST_QUEUE_GROUP_QID_MASK)

/* for multicast queue gports representing queue ID + core ID */
#define _SHR_GPORT_MCAST_QUEUE_GROUP_QUEUE_SET(_gport, _qid) \
        ((_gport) = (_SHR_GPORT_TYPE_MCAST_QUEUE_GROUP << _SHR_GPORT_TYPE_SHIFT) | \
         (_SHR_COSQ_GPORT_COMMON_ALL_CORES_VALUE << _SHR_COSQ_GPORT_COMMON_CORE_SHIFT) | \
         (((_qid) & _SHR_COSQ_GPORT_COMMON_QUEUE_MASK) << _SHR_GPORT_MCAST_QUEUE_GROUP_QID_SHIFT))

#define _SHR_GPORT_MCAST_QUEUE_GROUP_CORE_QUEUE_SET(_gport, _core, _qid) \
        ((_gport) = (_SHR_GPORT_TYPE_MCAST_QUEUE_GROUP << _SHR_GPORT_TYPE_SHIFT) | \
         (_SHR_CORE_ID2FIELD(_core) << _SHR_COSQ_GPORT_COMMON_CORE_SHIFT) | \
         (((_qid) & _SHR_COSQ_GPORT_COMMON_QUEUE_MASK) << _SHR_GPORT_MCAST_QUEUE_GROUP_QID_SHIFT))

#define _SHR_GPORT_MCAST_QUEUE_GROUP_QUEUE_GET(_gport) \
        (_SHR_GPORT_MCAST_QUEUE_GROUP_SYSPORTID_GET(_gport) == _SHR_GPORT_MCAST_QUEUE_GROUP_SYSPORTID_MASK ? \
        _SHR_GPORT_MCAST_QUEUE_GROUP_QID_GET(_gport) : \
        (((_gport) >> _SHR_GPORT_MCAST_QUEUE_GROUP_QID_SHIFT) & _SHR_COSQ_GPORT_COMMON_QUEUE_MASK))

#define _SHR_GPORT_MCAST_QUEUE_GROUP_CORE_GET(_gport) \
        _SHR_CORE_FIELD2ID(((_gport) >> _SHR_COSQ_GPORT_COMMON_CORE_SHIFT) & _SHR_COSQ_GPORT_COMMON_CORE_MASK)

#define _SHR_GPORT_IS_MIRROR(_gport)    \
        (((_gport) >> _SHR_GPORT_TYPE_SHIFT) == _SHR_GPORT_TYPE_MIRROR)

#define _SHR_GPORT_MIRROR_SET(_gport, _value)                               \
        ((_gport) = (_SHR_GPORT_TYPE_MIRROR << _SHR_GPORT_TYPE_SHIFT)   | \
         (((_value) & _SHR_GPORT_MIRROR_MASK) << _SHR_GPORT_MIRROR_SHIFT))

#define _SHR_GPORT_MIRROR_GET(_gport)    \
        (((_gport) >> _SHR_GPORT_MIRROR_SHIFT) & _SHR_GPORT_MIRROR_MASK)

#define _SHR_GPORT_IS_TUNNEL(_gport)    \
        (((_gport) >> _SHR_GPORT_TYPE_SHIFT) == _SHR_GPORT_TYPE_TUNNEL)

#define _SHR_GPORT_TUNNEL_ID_SET(_gport, _tunnel_id)                       \
        ((_gport) = (_SHR_GPORT_TYPE_TUNNEL   << _SHR_GPORT_TYPE_SHIFT)  | \
         (((_tunnel_id) & _SHR_GPORT_TUNNEL_MASK) << _SHR_GPORT_TUNNEL_SHIFT))

#define _SHR_GPORT_TUNNEL_ID_GET(_gport)   \
        (((_gport) >> _SHR_GPORT_TUNNEL_SHIFT) & _SHR_GPORT_TUNNEL_MASK)

#define _SHR_GPORT_IS_SYSTEM_PORT(_gport) \
        (((_gport) >> _SHR_GPORT_TYPE_SHIFT) == _SHR_GPORT_TYPE_SYSTEM_PORT)
#define _SHR_GPORT_SYSTEM_PORT_ID_GET(_gport)   \
        (((_gport) >> _SHR_GPORT_SYSTEM_PORT_SHIFT) & _SHR_GPORT_SYSTEM_PORT_MASK)
#define _SHR_GPORT_SYSTEM_PORT_ID_SET(_gport, _id)                            \
        ((_gport) = (_SHR_GPORT_TYPE_SYSTEM_PORT << _SHR_GPORT_TYPE_SHIFT)  | \
         (((_id) & _SHR_GPORT_SYSTEM_PORT_MASK) << _SHR_GPORT_SYSTEM_PORT_SHIFT))

#define _SHR_GPORT_IS_COSQ(_gport) \
        (((_gport) >> _SHR_GPORT_TYPE_SHIFT) == _SHR_GPORT_TYPE_COSQ)

#define _SHR_GPORT_TRAP_SET(_gport, _trap_id, _trap_strength, _snoop_strength)     \
        ((_gport) = (_SHR_GPORT_TYPE_TRAP << _SHR_GPORT_TYPE_TRAP_SHIFT)   |      \
         (((_trap_id) & _SHR_GPORT_TRAP_ID_MASK) << _SHR_GPORT_TRAP_ID_SHIFT)  |    \
         (((_trap_strength) & _SHR_GPORT_TRAP_STRENGTH_MASK) << _SHR_GPORT_TRAP_STRENGTH_SHIFT)  |  \
         (((_snoop_strength) & _SHR_GPORT_TRAP_SNOOP_STRENGTH_MASK) << _SHR_GPORT_TRAP_SNOOP_STRENGTH_SHIFT) )

#define _SHR_GPORT_TRAP_GET_ID(_gport)    \
        (((_gport) >> _SHR_GPORT_TRAP_ID_SHIFT) & _SHR_GPORT_TRAP_ID_MASK)

#define _SHR_GPORT_TRAP_GET_STRENGTH(_gport)    \
        (((_gport) >> _SHR_GPORT_TRAP_STRENGTH_SHIFT & _SHR_GPORT_TRAP_STRENGTH_MASK))

#define _SHR_GPORT_TRAP_GET_SNOOP_STRENGTH(_gport)    \
        (((_gport) >> _SHR_GPORT_TRAP_SNOOP_STRENGTH_SHIFT & _SHR_GPORT_TRAP_SNOOP_STRENGTH_MASK))

#define _SHR_GPORT_IS_TRAP(_gport)    \
        (((_gport) >> _SHR_GPORT_TYPE_TRAP_SHIFT) == _SHR_GPORT_TYPE_TRAP)

#define _SHR_FIELD_CTR_PROC_MASK_LEGACY ((1 << 2) - 1) /*2 bits for counter engines in Arad */
#define _SHR_FIELD_CTR_PROC_SHIFT_LEGACY 29 /* minimum 20 for the Statistic-Report Counter in Arad */
#define _SHR_FIELD_CTR_SET_MASK_LEGACY ((1 << _SHR_FIELD_CTR_PROC_SHIFT_LEGACY) - 1)
#define _SHR_FIELD_CTR_SET_SHIFT_LEGACY 0

#define _SHR_FIELD_STAT_ID_PROC_LEGACY_GET(_stat_id) \
    (((_stat_id) >> _SHR_FIELD_CTR_PROC_SHIFT_LEGACY) & _SHR_FIELD_CTR_PROC_MASK_LEGACY)

#define _SHR_FIELD_STAT_ID_CNTR_LEGACY_GET(_stat_id) \
    (((_stat_id) >> _SHR_FIELD_CTR_SET_SHIFT_LEGACY) & _SHR_FIELD_CTR_SET_MASK_LEGACY)

#define _SHR_FIELD_STAT_ID_LEGACY_SET(_proc, _ctr) \
    ((((_proc) & _SHR_FIELD_CTR_PROC_MASK_LEGACY) << _SHR_FIELD_CTR_PROC_SHIFT_LEGACY)\
    | (((_ctr) & _SHR_FIELD_CTR_SET_MASK_LEGACY) << _SHR_FIELD_CTR_SET_SHIFT_LEGACY))

#define _SHR_FIELD_STAT_ID_IS_LEGACY(_stat_id) (!((_stat_id >> 31) & 0x1))
#define _SHR_FIELD_STAT_ID_LEGACY              (0x1 << 31)

/* minimum 20 for the Statistic-Report Counter in Arad */
#define _SHR_FIELD_CTR_PROC_MASK ((1 << 4) - 1) /*4 bits for counter engines in Arad */

#define _SHR_FIELD_CTR_PROC_SHIFT 27 /* minimum 20 for the Statistic-Report Counter in Jericho */
#define _SHR_FIELD_CTR_SET_MASK ((1 << _SHR_FIELD_CTR_PROC_SHIFT) - 1)
#define _SHR_FIELD_CTR_SET_SHIFT 0

#define _SHR_FIELD_CTR_PROC_SHIFT_GET(_stat_id) (_SHR_FIELD_STAT_ID_IS_LEGACY(_stat_id) ? _SHR_FIELD_CTR_PROC_SHIFT_LEGACY : _SHR_FIELD_CTR_PROC_SHIFT)
#define _SHR_FIELD_STAT_ID_PROC_NEW_GET(_stat_id) \
    (((_stat_id) >> _SHR_FIELD_CTR_PROC_SHIFT) & _SHR_FIELD_CTR_PROC_MASK)

#define _SHR_FIELD_STAT_ID_CNTR_NEW_GET(_stat_id) \
    (((_stat_id) >> _SHR_FIELD_CTR_SET_SHIFT) & _SHR_FIELD_CTR_SET_MASK)

#define _SHR_FIELD_STAT_ID_NEW_SET(_proc, _ctr) \
    (_SHR_FIELD_STAT_ID_LEGACY | \
    (((_proc) & _SHR_FIELD_CTR_PROC_MASK) << _SHR_FIELD_CTR_PROC_SHIFT)|\
     (((_ctr) & _SHR_FIELD_CTR_SET_MASK) << _SHR_FIELD_CTR_SET_SHIFT))

#define _SHR_FIELD_STAT_ID_PROCESSOR_GET(_stat_id) \
             (_SHR_FIELD_STAT_ID_IS_LEGACY(_stat_id) ? \
             _SHR_FIELD_STAT_ID_PROC_LEGACY_GET(_stat_id) : \
             _SHR_FIELD_STAT_ID_PROC_NEW_GET(_stat_id))

#define _SHR_FIELD_STAT_ID_COUNTER_GET(_stat_id) \
             (_SHR_FIELD_STAT_ID_IS_LEGACY(_stat_id) ? \
             _SHR_FIELD_STAT_ID_CNTR_LEGACY_GET(_stat_id) : \
             _SHR_FIELD_STAT_ID_CNTR_NEW_GET(_stat_id))

#define _SHR_FIELD_STAT_ID_SET(_stat_id, _proc, _ctr) \
    (_stat_id = _SHR_FIELD_STAT_ID_NEW_SET(_proc, _ctr))

#endif  /* !_SHR_GPORT_H */
