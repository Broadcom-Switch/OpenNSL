/*! \file ofdpa_api.h
 */

/*! @addtogroup GLOFDPAAPI OF-DPA APIs
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
* @filename     ofdpa_api.h
*
* @purpose      OF-DPA API header
*
* @component    OF-DPA
*
* @note         none
*
* @create       03/22/2013
*
* @end
*
**********************************************************************/
#ifndef INCLUDE_OFDPA_API_H
#define INCLUDE_OFDPA_API_H

#include <stdint.h>
#include <sys/time.h>
#include <netinet/in.h>
#include "ofdpa_datatypes.h"
#include <sal/commdefs.h>

/*****************************************************************//**
* @brief  To initialize the OFDPA component
*
* @returns  OFDPA_ERROR_t     OFDPA return code
*
*********************************************************************/
int ofdpaInit() LIB_DLL_EXPORTED;

/*
 * All clients must register first.
 */
/*****************************************************************//**
* @brief  Initialize OF-DPA client or user application. For OF-DPA Standalone
*           Application mode, sets up the RPC communication channel for the
*           client. For the statically linked User Application, initializes
*           the system.
*
* @param[in]    clientName     client name
*
* @retval   OFDPA_E_NONE  success
* @retval   OFDPA_E_PARAM error in parameter passed
* @retval   OFDPA_E_FAIL  failure
*
*********************************************************************/
OFDPA_ERROR_t ofdpaClientInitialize(char *clientName) LIB_DLL_EXPORTED;

/*
 * Debugging and Logging definitions
 */

/*****************************************************************//**
* @brief  Generate a log message using printf formatting
*
* @param[in]    priority     message priority (syslog values)
* @param[in]    fmt          format string
* @param[in]    ...          optional parameters for format string
*
* @returns  number of characters in log message
* @returns  value less than zero if error
*
*********************************************************************/
int ofdpaCltLogPrintf(int priority, char *fmt, ...) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Generate a debug message using printf formatting
*
* @param[in]    functionName  name of function generating message
* @param[in]    component     ID of component generating message
* @param[in]    verbosity     message severity
* @param[in]    format        format string
* @param[in]    ...           optional parameters for format string
*
* @returns  number of characters in debug message
* @returns  value less than zero if error
*
*********************************************************************/
int ofdpaCltDebugPrintf(const char *functionName, ofdpaComponentIds_t component, ofdpaDebugLevels_t verbosity, const char *format, ...) LIB_DLL_EXPORTED;

/* Flow Tables.
*/

/*****************************************************************//**
 * @brief  Checks whether a table ID is a supported on the platform.
 *
 * @param[in]    tableId           Flow Table ID
 *
 * @retval   OFDPA_E_UNAVAIL   the value in tableId is not a valid table ID number
 * @retval   OFDPA_E_NONE      the value in tableId is a valid table ID number
 *
 * @note Not every flow table defined in the OF-DPA Abstract Switch Specification
 *       is supported on all platforms. This function reports whether flows
 *       can be added to the flow table specified.
 *
  *********************************************************************/
OFDPA_ERROR_t ofdpaFlowTableSupported(OFDPA_FLOW_TABLE_ID_t tableId) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Add a new entry to a flow table.
*
* @param[in]    flow     structure containing flow entry parameters
*
* @retval   OFDPA_E_NONE  flow entry added successfully
* @retval   OFDPA_E_PARAM error in flow entry parameters passed to function
* @retval   OFDPA_E_ERROR flow entry validity check failed
* @retval   OFDPA_E_FAIL  failure occurred during flow entry installation
* @retval   OFDPA_E_FULL  maximum number of flow entries already exist in table
* @retval   OFDPA_E_EXISTS an entry that overlaps the new entry already
*                          exists in the table
*
*********************************************************************/
OFDPA_ERROR_t ofdpaFlowAdd(ofdpaFlowEntry_t *flow) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Modify an existing entry in a flow table.
*
* @param[in]    flow     structure containing flow entry parameters
*
* @retval   OFDPA_E_NONE  flow entry added successfully
* @retval   OFDPA_E_PARAM error in flow entry parameters passed to function
* @retval   OFDPA_E_ERROR flow entry validity check failed
* @retval   OFDPA_E_FAIL  failure occurred during flow entry installation
*
*********************************************************************/
OFDPA_ERROR_t ofdpaFlowModify(ofdpaFlowEntry_t *flow) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief Delete an entry from a flow table.
*
* @param[in]    flow     structure containing flow entry parameters
*
* @retval   OFDPA_E_NONE  flow entry added successfully
* @retval   OFDPA_E_PARAM error in flow entry parameters passed to function
* @retval   OFDPA_E_FAIL  failure occurred during flow entry installation
* @retval   OFDPA_E_NOT_FOUND no matching flow entry found
* @retval   OFDPA_E_ERROR flow deletion validation failed
*
*********************************************************************/
OFDPA_ERROR_t ofdpaFlowDelete(ofdpaFlowEntry_t *flow) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief Retrieve the next flow entry in the specified flow table.
*          This API allows the client to walk the entries in a flow table.
*          In order to get the first entry in a flow table, the client
*          calls with the flow table identifier set and all other
*          parameters set to zero.  Table entries are walked in the
*          order the table is indexed.  If there are no entries in the
*          table after the entry specified, a return code indicates the
*          end of the flow table has been reached
*
* @param[in]    flow     structure containing flow entry parameters
* @param[out]    nextFlow  structure containing the next flow table
*                                 entry, if any
*
* @retval   OFDPA_E_NONE  the next flow entry was found and returned
* @retval   OFDPA_E_PARAM error in flow entry parameters passed to function
* @retval   OFDPA_E_NOT_FOUND  no next flow entry found
*
*********************************************************************/
OFDPA_ERROR_t ofdpaFlowNextGet(ofdpaFlowEntry_t *flow, ofdpaFlowEntry_t *nextFlow) LIB_DLL_EXPORTED;

/*------------------------------------------------------------------------------------*/
/* group table APIs */

/*
   The Group Table contains one entry for each Group.  The table is indexed
   by the groupId which identifies the group entry.  Data is encoded into the groupId to specify the OF-DPA
   group entry type and information required by OF-DPA to configure the datapath.

   The groupId encoding method is:

   L2 Interface, L2 Rewrite types:
        (MSB to LSB) 4 bits encode the Group Table Entry type |12 bits of VLAN ID | 16 bits of port identifier

   L2 Multicast, L2 Flood, L3 Multicast, and L3 Interface types:
        (MSB to LSB) 4 bits encode the Group Table Entry type |12 bits of VLAN ID | 16 bits of index

   L3 Unicast and L3 ECMP types:
        (MSB to LSB) 4 bits encode the Group Table Entry type | 28 bits of index

*/

/* APIs for getting/setting group IDs -- set APIs must set the type first. */

/*****************************************************************//**
* @brief  Get the Group Type encoded in the Group ID.
*
* @param[in]    groupId     group id
* @param[out]    type        group type
*
* @retval   OFDPA_E_NONE  Group Id returned successfully
*
* @note     Applicable for all group types
*
*********************************************************************/
OFDPA_ERROR_t ofdpaGroupTypeGet(uint32_t groupId, uint32_t *type) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Add Group.
*
* @param[in]    group     group entry
*
* @retval   OFDPA_E_NONE  Group added successfully
* @retval   OFDPA_E_PARAM error in parameters passed to function
* @retval   OFDPA_E_FULL  Group table full
* @retval   OFDPA_E_EXISTS  Group entry exists
* @retval   OFDPA_E_NOT_FOUND  port encoded in Group type L2
                               Interface not found
* @retval   OFDPA_E_INTERNAL  internal error
*
*********************************************************************/
OFDPA_ERROR_t ofdpaGroupAdd(ofdpaGroupEntry_t *group) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Delete Group.
*
* @param[in]    groupId     group id
*
* @retval   OFDPA_E_NONE  Group deleted successfully
* @retval   OFDPA_E_PARAM error in parameters passed to function
* @retval   OFDPA_E_NOT_FOUND  group entry not found
* @retval   OFDPA_E_FAIL  failure; other errors
*
*********************************************************************/
OFDPA_ERROR_t ofdpaGroupDelete(uint32_t groupId) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Get the next Group entry.
*
* @param[in]    groupId     group id
* @param[out]    nextGroup   next group entry
*
* @retval   OFDPA_E_NONE  next group entry returned successfully
* @retval   OFDPA_E_PARAM error in parameters passed to function
* @retval   OFDPA_E_FAIL  next group does not exist
*
*********************************************************************/
OFDPA_ERROR_t ofdpaGroupNextGet(uint32_t groupId, ofdpaGroupEntry_t *nextGroup) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Get the next Group entry of a given type.
*
* @param[in]    groupId     group id
* @param[in]    groupType   group type
* @param[out]    nextGroup   next group entry
*
* @retval   OFDPA_E_NONE  next group entry returned successfully
* @retval   OFDPA_E_PARAM error in parameters passed to function
* @retval   OFDPA_E_FAIL  next group does not exist
*
*********************************************************************/
OFDPA_ERROR_t ofdpaGroupTypeNextGet(uint32_t groupId,
                                    OFDPA_GROUP_ENTRY_TYPE_t groupType,
                                    ofdpaGroupEntry_t *nextGroup) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Get Group statistics.
*
* @param[in]    groupId     group id
* @param[out]    groupStats  group statistics
*
* @retval   OFDPA_E_NONE  group statistics returned successfully
* @retval   OFDPA_E_PARAM error in parameters passed to function
* @retval   OFDPA_E_NOT_FOUND  group not found
*
*********************************************************************/
OFDPA_ERROR_t ofdpaGroupStatsGet(uint32_t groupId, ofdpaGroupEntryStats_t *groupStats) LIB_DLL_EXPORTED;

/*
   Group Table entries contain one or more Action Buckets depending on their type.
*/

/*****************************************************************//**
* @brief  Add a Group Bucket entry.
*
* @param[in]    bucket     group bucket entry
*
* @retval   OFDPA_E_NONE        group bucket entry added successfully
* @retval   OFDPA_E_PARAM       error in parameters passed to function
* @retval   OFDPA_E_FULL        group bucket table full
* @retval   OFDPA_E_NOT_FOUND   group not found
* @retval   OFDPA_E_EXISTS      group bucket entry exists
* @retval   OFDPA_E_INTERNAL    internal errors or failures
* @retval   OFDPA_E_FAIL        internal errors or failures
*
* @note For group table entries allowed to have multiple buckets,
*        this is called more than once
*
*********************************************************************/
OFDPA_ERROR_t ofdpaGroupBucketEntryAdd(ofdpaGroupBucketEntry_t *bucket) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Delete a Group Bucket entry.
*
* @param[in]    groupId       group id
* @param[in]    bucketIndex   group bucket index
*
* @retval   OFDPA_E_NONE        group bucket entry deleted successfully
* @retval   OFDPA_E_PARAM       error in parameters passed to function
* @retval   OFDPA_E_NOT_FOUND   group bucket entry not found
* @retval   OFDPA_E_EXISTS      group reference exists
* @retval   OFDPA_E_INTERNAL    internal errors or failures
* @retval   OFDPA_E_FAIL        internal errors or failures
*
*********************************************************************/
OFDPA_ERROR_t ofdpaGroupBucketEntryDelete(uint32_t groupId, uint32_t bucketIndex) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Delete all Buckets from a Group.
*
* @param[in]    groupId       group id
*
* @retval   OFDPA_E_NONE        group bucket entry deleted successfully
* @retval   OFDPA_E_PARAM       error in parameters passed to function
* @retval   OFDPA_E_EXISTS      group reference exists
* @retval   OFDPA_E_INTERNAL    internal errors or failures
* @retval   OFDPA_E_FAIL        internal errors or failures
*
*********************************************************************/
OFDPA_ERROR_t ofdpaGroupBucketsDeleteAll(uint32_t groupId) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Get the Group Bucket entry.
*
* @param[in]    groupId       group id
* @param[in]    bucketIndex   bucket index
* @param[out]    groupBucket   group bucket entry
*
* @retval   OFDPA_E_NONE        group bucket entry returned successfully
* @retval   OFDPA_E_PARAM       error in parameters passed to function
* @retval   OFDPA_E_FAIL        group bucket entry does not exist
*
*********************************************************************/
OFDPA_ERROR_t ofdpaGroupBucketEntryGet(uint32_t groupId, uint32_t bucketIndex,
                                       ofdpaGroupBucketEntry_t *groupBucket) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Get the first Group Bucket entry.
*
* @param[in]    groupId       group id
* @param[out]    firstGroupBucket   first group bucket entry
*
* @retval   OFDPA_E_NONE        group bucket entry returned successfully
* @retval   OFDPA_E_PARAM       error in parameters passed to function
* @retval   OFDPA_E_FAIL        group bucket entry does not exist
*
*********************************************************************/
OFDPA_ERROR_t ofdpaGroupBucketEntryFirstGet(uint32_t groupId,
                                            ofdpaGroupBucketEntry_t *firstGroupBucket) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Get the next Group Bucket entry.
*
* @param[in]    groupId       group id
* @param[in]    bucketIndex   bucket index
* @param[out]    nextBucketEntry   next group bucket entry
*
* @retval   OFDPA_E_NONE        next group bucket entry returned successfully
* @retval   OFDPA_E_PARAM       error in parameters passed to function
* @retval   OFDPA_E_FAIL        next group bucket entry does not exist
*
*********************************************************************/
OFDPA_ERROR_t ofdpaGroupBucketEntryNextGet(uint32_t groupId, uint32_t bucketIndex,
                                           ofdpaGroupBucketEntry_t *nextBucketEntry) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Reports the number of group entries of all types.
*
* @param[out]    entryCount         total number of group entries configured
*
* @retval   OFDPA_E_NONE        group entry count returned successfully
* @retval   OFDPA_E_PARAM       error in parameters passed to function
*
*********************************************************************/
OFDPA_ERROR_t ofdpaGroupTableTotalEntryCountGet(uint32_t *entryCount) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Get Group table info.
*
* @param[in]    groupId         group id
* @param[in]    info            info
*
* @retval   OFDPA_E_NONE        group info returned successfully
* @retval   OFDPA_E_PARAM       error in parameters passed to function
* @retval   OFDPA_E_NOT_FOUND   group type not found
*
*********************************************************************/
OFDPA_ERROR_t ofdpaGroupTableInfoGet(uint32_t groupId, ofdpaGroupTableInfo_t *info) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Create a port.
*
* @param[in]    portNum   OpenFlow port number
* @param[in]    portInfo  structure containing port parameters
*
* @retval   OFDPA_E_NONE  port successfully created
* @retval   OFDPA_E_PARAM error in parameters passed to function
* @retval   OFDPA_E_ERROR internal error
* @retval   OFDPA_E_FAIL  failure occurred during port creation
* @retval   OFDPA_E_FULL  maximum number of ports already created
* @retval   OFDPA_E_EXISTS an entry with the specified portnum already created
*
*********************************************************************/
OFDPA_ERROR_t ofdpaPortCreate(uint32_t portNum, ofdpaPortInfo_t *portInfo) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Delete a port.
*
* @param[in]    portNum   OpenFlow port number
*
* @retval   OFDPA_E_NONE  port successfully deleted
* @retval   OFDPA_E_PARAM error in parameters passed to function
* @retval   OFDPA_E_NOT_FOUND  port with identifier not configured
* @retval   OFDPA_E_FAIL  failure occurred during port deletion
*
*********************************************************************/
OFDPA_ERROR_t ofdpaPortDelete(uint32_t portNum) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Retrieve port configuration and/or status.
*
* @param[in]    portNum    unique identifier for the port within the switch
* @param[out]  portInfo    structure containing port info (optional)
* @param[out]    status    structure containing port status (optional)
*
* @retval   OFDPA_E_NONE  port data successfully retrieved
* @retval   OFDPA_E_PARAM error in parameters passed to function
* @retval   OFDPA_E_NOT_FOUND port with identifier not configured
*
* @note If the caller does not require the data in the info or
*        status structure, either or both parameters may be set to NULL.
*        An example of this type of invocation is if the caller is checking
*        on presence of a logical port, but has no need for the configuration or
*        status data.
*
*********************************************************************/
OFDPA_ERROR_t ofdpaPortGet(uint32_t portNum, ofdpaPortInfo_t *portInfo, ofdpaPortStatus_t *status) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Return the port identifier, if any, for the
*         port after the one specified in the port table.
*
* @param[in]    portNum       identifier for the port within the switch
* @param[out]   nextPortNum   identifier for the next port within the switch
*
* @retval   OFDPA_E_NONE  next logical port identifier found
* @retval   OFDPA_E_FAIL  no next logical port identifier found
*
*********************************************************************/
OFDPA_ERROR_t ofdpaPortNextGet(uint32_t portNum, uint32_t *nextPortNum) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Packet out API. Sends a packet out a switch port
*
* @param[in]    pkt  packet
* @param[in]    flags
* OFDPA_PACKET_LOOKUP_TX: Indicates that packet must go through a hardware lookup
*                          starting from the first table in the pipeline. The srcIfNum
*                          is used as the ingress port in table lookups.
*
*                          If this flag is not set, then the packet is sent unmodified
*                          out of the outIfNum
*
* @param[out]    outPortNum  Output port. Can be physical or logical or reserved
* @param[in]    inPortNum  Input port. Indicates the interface on which packet was
*                                 originally received.
*
* @retval   OFDPA_E_NONE if packet is transmitted successfully
* @retval   OFDPA_E_PARAM if an input parameter is bad
* @retval   OFDPA_E_NOT_FOUND if the input or output port parameter is bad
* @retval   OFDPA_E_INTERNAL if transmit DMA buffer has not been allocated
* @returns  Any other return code if there is a failure
*
* @note    DPA will not do any buffering of packets and it is expected to be done
*           at the agent if required
*
*********************************************************************/
OFDPA_ERROR_t ofdpaPktSend(ofdpa_buffdesc *pkt, uint32_t flags, uint32_t outPortNum, uint32_t inPortNum) LIB_DLL_EXPORTED;

/*****************************************************************//**
 * @brief  Report the size in bytes of the largest packet that can be received.
 *
 * @param[out]    pktSize      The maximum packet size, in bytes.
 *
 * @retval   OFDPA_E_NONE
 *
 * @note    A client can use the returned value to size a packet receive buffer.
 *
  * ********************************************************************/
OFDPA_ERROR_t ofdpaMaxPktSizeGet(uint32_t *pktSize) LIB_DLL_EXPORTED;

/*------------------------------------------------------------------------------------*/
/* Event APIs */

/*
   Asynchronous events: Have classified them into two broad category:
   Packet In : Packet received from the hardware to be sent to the controller
   Control messages: Events like Port creation, deletion, link state, Flow age and Error

   The packet In events can have a high frequency, so we want to ensure that there is
   separate control for polling of these two event types to give flexibility to the agent
*/

/*****************************************************************//**
 * @brief  Opens and binds OF-DPA Client's packet socket.
 *
  *
 * @returns  event socket fd
 *
 * @note This function must be called before calls to ofdpaPktReceive() or
 *        ofdpaClientPktSockFdGet().
 *
 *        Only one process in the system should bind the event socket at
 *        any one time. If multiple running processes have called this function,
 *        unpredictable results may occur.
 *
  *********************************************************************/
OFDPA_ERROR_t ofdpaClientPktSockBind(void) LIB_DLL_EXPORTED;

/*****************************************************************//**
 * @brief  Get OF-DPA Client's packet socket fd
 *
  *
 * @returns  packet socket fd
 *
  *********************************************************************/
int ofdpaClientPktSockFdGet(void) LIB_DLL_EXPORTED;

/*****************************************************************//**
 * @brief  The client calls this function to retrieve a single packet that the hardware
 *           has punted to the CPU.
 *
 * @param[in]    timeout    If NULL, the function blocks until a packet is received.
 *                                 If the timeout value is zero, the function returns immediately,
 *                                 whether or not a packet is available. The return code
 *                                 indicates whether a packet has been received. If the timeout
 *                                 value is non-zero, the function blocks up to this length of
 *                                 time if a packet is not immediately available. Again, the
 *                                 return code indicates whether a packet was received.
 * @param[out]    pkt       A packet structure allocated by the caller and used to
 *                                 return a received packet. The packet structure includes some
 *                                 metadata to indicate properties like why the packet came to
 *                                 the CPU and the ingress port. On input, the caller must set
 *                                 pkt-\>pktData.size to the size in bytes of the buffer allocated
 *                                 to hold the received packet. On output, pkt-\>pktData.size
 *                                 specifies the length of the packet in bytes. pkt-\>pktData.pstart
 *                                 on input must point to a buffer large enough to hold the largest
 *                                 possible received packet (OFDPA_MAX_PKT_LEN). This function copies
 *                                 the packet into this buffer, starting with the Ethernet header
 *                                 (the destination MAC address). The trailing Ethernet CRC is not
 *                                 included.
 *
 * @retval   OFDPA_E_NONE     if a packet is returned
 * @retval   OFDPA_E_TIMEOUT  if no packet is available within the specified timeout
 * @retval   OFDPA_E_PARAM    if an input parameter is invalid (e.g., pkt is NULL)
 * @retval   OFDPA_E_FAIL     for any other failure
 *
 * @note    This function runs in the client's own context and is not an RPC API.
 *
  * ********************************************************************/
OFDPA_ERROR_t ofdpaPktReceive(struct timeval *timeout, ofdpaPacket_t *pkt) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Get the next port event.
*
* @param[in,out]    eventData     event data
*
* @retval   OFDPA_E_NONE        port event data returned successfully
* @retval   OFDPA_E_PARAM       error in parameters passed to function
* @retval   OFDPA_E_NOT_FOUND   next port event not found
*
* @note     populate the port number in eventData to get the
*           event for the next port
*
*********************************************************************/
OFDPA_ERROR_t ofdpaPortEventNextGet(ofdpaPortEvent_t *eventData) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Get the port event.
*
* @param[in,out]    eventData     event data
*
* @retval   OFDPA_E_NONE        port event data returned successfully
* @retval   OFDPA_E_PARAM       error in parameters passed to function
* @retval   OFDPA_E_NOT_FOUND   next port event not found
*
* @note     get the event for the port
*
*********************************************************************/
OFDPA_ERROR_t ofdpaPortEventGet(ofdpaPortEvent_t *eventData) LIB_DLL_EXPORTED;

/*****************************************************************//**
* @brief  Get the next flow event.
*
* @param[in,out]    eventData     event data
*
* @retval   OFDPA_E_NONE        flow event data returned successfully
* @retval   OFDPA_E_PARAM       error in parameters passed to function
* @retval   OFDPA_E_NOT_FOUND   next port event not found
*
* @note     populate the table id in eventData to get the
*           events for the flow table
*
*********************************************************************/
OFDPA_ERROR_t ofdpaFlowEventNextGet(ofdpaFlowEvent_t *eventData) LIB_DLL_EXPORTED;

/*------------------------------------------------------------------------------------*/
/* Table APIs */

/* Get information for a given table Id */

/*****************************************************************//**
* @brief  Get Flow Table Info.
*
* @param[in]    tableId     flow table Id
* @param[out]    info        flow table info
*
* @retval   OFDPA_E_NONE        table info returned successfully
* @retval   OFDPA_E_PARAM       error in parameters passed to function
* @retval   OFDPA_E_NOT_FOUND   table id not found
*
*********************************************************************/
OFDPA_ERROR_t ofdpaFlowTableInfoGet(OFDPA_FLOW_TABLE_ID_t tableId, ofdpaFlowTableInfo_t *info) LIB_DLL_EXPORTED;

#endif /* INCLUDE_OFDPA_API_H */
/*!  @}
 */
