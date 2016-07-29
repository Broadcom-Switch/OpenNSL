/*! \file ofdpa_datatypes.h
 */

/*! @addtogroup GLOFDPADT OF-DPA Datatypes
 *    @{
 */
/*********************************************************************
*
* (C) Copyright Broadcom Corporation 2003-2016
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
*
* @filename     ofdpa_datatypes.h
*
* @purpose      OF-DPA datatypes header
*
* @component    OF-DPA
*
* @note         none
*
* @create       27 June 2013
*
* @end
*
**********************************************************************/
#ifndef INCLUDE_OFDPA_DATATYPES_H
#define INCLUDE_OFDPA_DATATYPES_H

#include <stdint.h>
#include <sys/time.h>
#include <netinet/in.h>

/** OFDPA uses these enumerators to indicate the error codes. */
typedef enum
{
  /** Success. */
  OFDPA_E_NONE = 0,
  /** Error in RPC. */
  OFDPA_E_RPC                  = -20,
  /** Internal error. */
  OFDPA_E_INTERNAL             = -21,
  /** Invalid parameter. */
  OFDPA_E_PARAM                = -22,
  /** Parameter constraint violated. */
  OFDPA_E_ERROR                = -23,
  /** Maximum count is already reached or table full. */
  OFDPA_E_FULL                 = -24,
  /** Already exists. */
  OFDPA_E_EXISTS               = -25,
  /** Operation Timeout. */
  OFDPA_E_TIMEOUT              = -26,
  /** Operation Fail. */
  OFDPA_E_FAIL                 = -27,
  /** Disabled. */
  OFDPA_E_DISABLED             = -28,
  /** Parameter/feature is not supported. */
  OFDPA_E_UNAVAIL              = -29,
  /** Parameter not found. */
  OFDPA_E_NOT_FOUND            = -30,
  /** Nothing to report or table is empty. */
  OFDPA_E_EMPTY                = -31,
  /** Request denied. */
  OFDPA_E_REQUEST_DENIED       = -32,
  /** Not implemented. */
  OFDPA_NOT_IMPLEMENTED_YET    = -33,
} OFDPA_ERROR_t;

typedef enum
{
  OFDPA_FALSE = 0,
  OFDPA_TRUE
} OFDPA_BOOL;

/** MAC address length */
#define OFDPA_MAC_ADDR_LEN 6

/** Check if MAC address is NULL */
#define OFDPA_MAC_ADDR_IS_NULL(mac) \
   ((mac[0] == 0) && (mac[1] == 0) && (mac[2] == 0) && \
    (mac[3] == 0) && (mac[4] == 0) && (mac[5] == 0))

/** Check if MAC address is all ones */
#define OFDPA_MAC_ADDR_IS_ALL_ONES(mac) \
   ((mac[0] == 0xff) && (mac[1] == 0xff) && (mac[2] == 0xff) && \
    (mac[3] == 0xff) && (mac[4] == 0xff) && (mac[5] == 0xff))

/** IPv4 address length */
#define OFDPA_IP_ADDR_LEN    4

/** Open Flow Controller port */
#define OFDPA_PORT_CONTROLLER     0xfffffffdu

/** Open Flow Controller port */
#define OFDPA_PORT_LOCAL     0xfffffffeu

/** VLAN Id Field Mask */
#define OFDPA_VID_FIELD_MASK 0x0000
/** VLAN Id Exact Mask */
#define OFDPA_VID_EXACT_MASK 0x0fff

/** VLAN Id None */
#define OFDPA_VID_NONE    0x0000
/** VLAN Id present */
#define OFDPA_VID_PRESENT 0x1000

/** Exact Mask */
#define OFDPA_INPORT_EXACT_MASK  0xffffffffu
/** Field Mask */
#define OFDPA_INPORT_FIELD_MASK  0x00000000u

/** Ethertype Exact Mask */
#define OFDPA_ETHERTYPE_EXACT_MASK  0xffffu
/** Ethertype All Mask */
#define OFDPA_ETHERTYPE_ALL_MASK    0x0u

/** IPv4 Address Exact Mask */
#define OFDPA_IPV4_ADDR_EXACT_MASK  0xffffffffu
/** IPv4 Address Field Mask */
#define OFDPA_IPV4_ADDR_FIELD_MASK  0x00000000u

/** zero mask */
#define OFDPA_ZERO_MASK                0x0u
/** VLAN DEI value mask */
#define OFDPA_VLAN_DEI_VALUE_MASK      0x1u
/** VLAN CFI max vlue */
#define OFDPA_VLAN_DEI_MAX_VALUE       (OFDPA_VLAN_DEI_VALUE_MASK)
/** DSCP value mask */
#define OFDPA_DSCP_VALUE_MASK          0x3fu
/** DSCP max value */
#define OFDPA_DSCP_MAX_VALUE           (OFDPA_DSCP_VALUE_MASK)

/** MAC address */
typedef struct ofdpaMacAddr_s
{
  /** MAC address */
  uint8_t     addr[OFDPA_MAC_ADDR_LEN];
} ofdpaMacAddr_t;


/** Intrinsic buffer descriptor.
 *
 * NOTE: This is intended to be used as a basic data type that can be
 *       passed directly between functions -- keep it small and simple.
 *       To use this as an IN/OUT or OUT value, pass a pointer to the
 *       element so that the called routine can update the 'size' field
 *       with the actual content length being output.
 *
 * NOTE: When setting the 'size' field to indicate the amount of data
 *       contained in the buffer, the conventional usage is to account
 *       for all bytes including any string termination characters
 *       (e.g. strlen()+1).
 */
typedef struct
{
  uint32_t                size;
  char                   *pstart;
} ofdpa_buffdesc;

/**  enable or disable for config or status parameter. */
typedef enum
{
  OFDPA_DISABLE = 0,
  OFDPA_ENABLE = 1,

} OFDPA_CONTROL_t;

/*
 * Debugging and Logging definitions
 */

/** Component enumerator */
typedef enum
{
  /** First Component */
  OFDPA_COMPONENT_FIRST = 1,
    /** API Component */
  OFDPA_COMPONENT_API   = OFDPA_COMPONENT_FIRST,
    /** Mapping Component */
  OFDPA_COMPONENT_MAPPING,
    /** OFDB Component */
  OFDPA_COMPONENT_OFDB,
    /** Datapath Component */
  OFDPA_COMPONENT_DATAPATH,
  /** Must be last */
  OFDPA_COMPONENT_MAX
} ofdpaComponentIds_t;

/** Debug verbosity enumerator */
typedef enum
{
  /** Logging Always */
  OFDPA_DEBUG_ALWAYS = 0,
  /** Basic Logging */
  OFDPA_DEBUG_BASIC,
  /** Verbose Logging */
  OFDPA_DEBUG_VERBOSE,
  /** Very Verbose Logging */
  OFDPA_DEBUG_VERY_VERBOSE,
  /** Too Verbose Logging */
  OFDPA_DEBUG_TOO_VERBOSE,

  /** Must be last */
  OFDPA_DEBUG_MAX
} ofdpaDebugLevels_t;

/** Exact Mask */
#define OFDPA_TUNNEL_ID_EXACT_MASK  0xffffffffffffffffull
/** Field Mask */
#define OFDPA_TUNNEL_ID_FIELD_MASK  0x0000000000000000ull

/* Flow Tables.
*/

/** Flow Table Id enumerator */
typedef enum
{
  OFDPA_FLOW_TABLE_ID_INGRESS_PORT                      =    0,  /**< Ingress Port Table */
  OFDPA_FLOW_TABLE_ID_VLAN                              =   10,  /**< VLAN Table */
  OFDPA_FLOW_TABLE_ID_TERMINATION_MAC                   =   20,  /**< Termination MAC Table */
  OFDPA_FLOW_TABLE_ID_BRIDGING                          =   50,  /**< Bridging Table */
  OFDPA_FLOW_TABLE_ID_ACL_POLICY                        =   60,  /**< ACL Table */

} OFDPA_FLOW_TABLE_ID_t;

/*------------------------------------------------------------------------------------*/

/** VLAN Flow Table Match */
typedef struct ofdpaVlanFlowMatch_s
{
  /** OpenFlow Ingress Port number */
  uint32_t    inPort;
  uint32_t    inPortMask;

  uint16_t    vlanId;
  uint16_t    vlanIdMask;

} ofdpaVlanFlowMatch_t;

/** VLAN Flow Table Entry */
typedef struct ofdpaVlanFlowEntry_s
{
  /* Match Criteria  */
  ofdpaVlanFlowMatch_t  match_criteria;

  /* flow instructions  */
  OFDPA_FLOW_TABLE_ID_t gotoTableId;

  /** Apply Actions Instructions */

  uint32_t    tunnelIdAction;
  uint64_t    tunnelId;

} ofdpaVlanFlowEntry_t;

/*------------------------------------------------------------------------------------*/

/** Bridging Flow Table Match */
typedef struct ofdpaBridgingFlowMatch_s
{
  uint64_t    tunnelId;
  uint64_t    tunnelIdMask;

  ofdpaMacAddr_t destMac;
  ofdpaMacAddr_t destMacMask;    /**< Field maskable, DLF rule if masked */

} ofdpaBridgingFlowMatch_t;

/** Bridging Flow Table Entry */
typedef struct ofdpaBridgingFlowEntry_s
{
  /* Match Criteria  */
  ofdpaBridgingFlowMatch_t  match_criteria;

  /* flow instructions  */
  /** Goto-Table instruction */
  /** must be OFDPA_FLOW_TABLE_ID_ACL_POLICY,
      setting to 0 indicates drop action */

  OFDPA_FLOW_TABLE_ID_t gotoTableId;

  /** Write-Action(s) instruction */
  /** data for GROUP action must be a L2 Interface, L2 Multicast, L2 Flood,
   *  or L2 Overlay group entry as appropriate */
  uint32_t    groupID;

  /** Apply-Action(s) instruction */
  /** data for OUTPUT action, restricted to CONTROLLER, set to 0 otherwise */

  uint32_t    outputPort;

} ofdpaBridgingFlowEntry_t;

/*------------------------------------------------------------------------------------*/

/** This structure is used to add a new flow or modify an existing flow.
*/
typedef struct ofdpaFlowEntry_s
{
  /** Flow Table Id */
  OFDPA_FLOW_TABLE_ID_t      tableId;

  /** Flow priority */
  uint32_t                   priority;

  union
  {
    /** VLAN Port Table Flow Entry */
    ofdpaVlanFlowEntry_t             vlanFlowEntry;

    /** Bridging Table Flow Entry */
    ofdpaBridgingFlowEntry_t         bridgingFlowEntry;

  } flowData;

  /** Hard timeout for the flow entry */
  uint32_t   hard_time;

  /** Idle timeout for the flow entry */
  uint32_t   idle_time;

  /** cookie */
  uint64_t   cookie;

} ofdpaFlowEntry_t;

/** Flow Stats information. */
typedef struct ofdpaFlowEntryStats_s
{
  /** flow duration */
  uint32_t  durationSec;

  /** not all flow tables support these counters; for flow tables that do not support
     the counters, 0 is returned */
  uint64_t  receivedPackets;

  /** not all flow tables support these counters; for flow tables that do not support
     the counters, 0 is returned */
  uint64_t  receivedBytes;

} ofdpaFlowEntryStats_t;

/*------------------------------------------------------------------------------------*/
/* group table APIs */

/** Group Type Enumerator */
typedef enum
{
  /** Group type L2 Interface */
  OFDPA_GROUP_ENTRY_TYPE_L2_INTERFACE = 0,
  /** Must be last */
  OFDPA_GROUP_ENTRY_TYPE_LAST
} OFDPA_GROUP_ENTRY_TYPE_t;

/**
   The Group Table contains one entry for each Group.  The table is indexed
   by the groupId which identifies the group entry.  Data is encoded into the groupId to specify the OF-DPA
   group entry type and information required by OF-DPA to configure the datapath.

   The groupId encoding method is:

   L2 Interface and L2 Unfiltered Interface type:
        (MSB to LSB) 4 bits encode the Group Table Entry type | 12 bits of VLAN ID | 16 bits of port identifier
*/

/** Group Table Entry */
typedef struct ofdpaGroupEntry_s
{
  /** Group Id */
  uint32_t    groupId;

} ofdpaGroupEntry_t;

/** Group Table Entry Statistics */
typedef struct ofdpaGroupEntryStats_s
{
  uint32_t                  refCount;

  /** time in seconds since the Group was added */
  uint32_t                  duration;

  /** number of buckets in the Group */
  uint32_t                  bucketCount;
} ofdpaGroupEntryStats_t;

/** L2 Interface Group Bucket */
typedef struct ofdpaL2InterfaceGroupBucketData_s
{
  /** bucket action set */
  /** controller responsible for assuring data in outputPort
      and the port identifier data encoded in the groupId are equal */

  uint32_t       outputPort;

  /** controller responsible for assuring vlan is identified in groupId */
  /** flag indicating if outer VLAN tag should be stripped
  (0 - do not strip VLAN tag, 1 - strip VLAN tag) */

  uint32_t       popVlanTag;

} ofdpaL2InterfaceGroupBucketData_t;

/** Group Bucket Table Entry */
typedef struct ofdpaGroupBucketEntry_s
{
  /** Group Id */
  uint32_t    groupId;

  /** Bucket Index */
  uint32_t    bucketIndex;

  /** bucket action set */
  union
  {
    ofdpaL2InterfaceGroupBucketData_t  l2Interface;
  } bucketData;

} ofdpaGroupBucketEntry_t;

/** Group table information */
typedef struct ofdpaGroupTableInfo_s
{
  /** Current number of group entries of a given type */
  uint32_t     numGroupEntries;

  /** Max number of group entries of a given type */
  uint32_t     maxGroupEntries;

  /** Max number of group bucket entries per group for a given group type */
  uint32_t     maxBucketEntries;

} ofdpaGroupTableInfo_t;


/*------------------------------------------------------------------------------------*/
/* Port Table */

typedef enum
{
  OFDPA_PORT_TYPE_PHYSICAL,

} OFDPA_PORT_TYPE_t;


typedef struct
{
  int           hw_unit;
  int           hw_port;

} ofdpaPhysicalPortInfo_t;

typedef struct
{
  OFDPA_PORT_TYPE_t  type;

  union
  {
    ofdpaPhysicalPortInfo_t      physical;
  } portInfo;

} ofdpaPortInfo_t;

typedef struct
{
  uint32_t refCount;

} ofdpaPortStatus_t;

/** Flags field in ofdpaPktSend() */
#define OFDPA_PKT_LOOKUP  1

/** Packet In reason codes  */
typedef enum
{
  /** No Match */
  OFDPA_PACKET_IN_REASON_NO_MATCH = 0,
  /** Action */
  OFDPA_PACKET_IN_REASON_ACTION,
  /** Invalid TTL */
  OFDPA_PACKET_IN_REASON_INVALID_TTL,

  OFDPA_PACKET_IN_REASON_OAM,

} OFDPA_PACKET_IN_REASON_t;

/** Packet  */
typedef struct ofdpaPacket_s
{
  /** Reason */
  OFDPA_PACKET_IN_REASON_t  reason;

  /** Flow Table Id */
  OFDPA_FLOW_TABLE_ID_t     tableId;

  /** Input port */
  uint32_t                  inPortNum;

  /** Packet */
  ofdpa_buffdesc            pktData;
} ofdpaPacket_t;

/* Asynchronous Control Events */

/** Port event type */
typedef enum
{
  /** Port created */
  OFDPA_EVENT_PORT_CREATE = 1 << 0,

  /** Port deleted */
  OFDPA_EVENT_PORT_DELETE = 1 << 1,

  /** Port link state has changed */
  OFDPA_EVENT_PORT_STATE = 1 << 2,

} OFDPA_PORT_EVENT_MASK_t;

/** Port events */
typedef struct ofdpaPortEvent_s
{
  /** Event mask indication the event type */
  OFDPA_PORT_EVENT_MASK_t eventMask;

  /** Port number associated with the port event */
  uint32_t                portNum;

#ifdef OFDPA_TBD
  /** Port Link state */
  OFDPA_PORT_STATE_t      state;
#endif
} ofdpaPortEvent_t;

/** Flow event type */
typedef enum
{
  /** Flow idle timeout event */
  OFDPA_FLOW_EVENT_IDLE_TIMEOUT = 1 << 0,

  /** Flow hard timeout event */
  OFDPA_FLOW_EVENT_HARD_TIMEOUT = 1 << 1

} OFDPA_FLOW_EVENT_MASK_t;

/** Flow events */
typedef struct ofdpaFlowEvent_s
{
  /** events that have occurred for this flow */
  OFDPA_FLOW_EVENT_MASK_t   eventMask;

  /** Flow match criteria */
  ofdpaFlowEntry_t flowMatch;

} ofdpaFlowEvent_t;

/*------------------------------------------------------------------------------------*/
/* Table APIs */

/** Table name maximum string length */
#define OFDPA_TABLE_NAME_LEN 32

/** Flow table information */
typedef struct ofdpaFlowTableInfo_s
{
  /** Current number of entries in the table */
  uint32_t     numEntries;

  /** Max number of entries in the table */
  uint32_t     maxEntries;

  /* Not supporting any features etc as they will be well documented in programmers
     guide
  */
} ofdpaFlowTableInfo_t;

#endif /* INCLUDE_OFDPA_DATATYPES_H */
/*!  @}
 */
