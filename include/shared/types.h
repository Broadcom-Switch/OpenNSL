/*********************************************************************
 *
 * (C) Copyright Broadcom Corporation 2013-2015
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
 * File:        types.h
 * Details:     Shared data types
 *********************************************************************/
#ifndef   _SHR_TYPES_H_
#define   _SHR_TYPES_H_

typedef enum  {
    _SHR_FORWARDING_TYPE_L2 = 0,            /* L2 switching forwarding. */
    _SHR_FORWARDING_TYPE_IP4UCAST = 1,      /* IPv4 Unicast Routing forwarding. */
    _SHR_FORWARDING_TYPE_IP4MCAST = 2,      /* IPv4 Multicast Routing forwarding. */
    _SHR_FORWARDING_TYPE_IP6UCAST = 3,      /* IPv6 Unicast Routing forwarding. */
    _SHR_FORWARDING_TYPE_IP6MCAST = 4,      /* IPv6 Multicast Routing forwarding. */
    _SHR_FORWARDING_TYPE_MPLS = 5,          /* MPLS Switching forwarding. */
    _SHR_FORWARDING_TYPE_TRILL = 6,         /* Trill forwarding. */
    _SHR_FORWARDING_TYPE_RXREASON = 7,      /* Forwarding according to a RxReason. */
    _SHR_FORWARDING_TYPE_TRAFFIC_MANAGMENT = 8, /* Traffic Management forwarding, when
                                           an external Packet Processor sets the
                                           forwarding decision. */
    _SHR_FORWARDING_TYPE_SNOOP = 9,         /* Snooped packet. */
    _SHR_FORWARDING_TYPE_FCoE = 10,         /* Fiber Channel over Ethernet
                                           forwarding. */
    _SHR_FORWARDING_TYPE_COUNT = 11         /* Always Last. Not a usable value. */
} _shr_forwarding_type_t;

#endif /* _SHR_TYPES_H_ */
