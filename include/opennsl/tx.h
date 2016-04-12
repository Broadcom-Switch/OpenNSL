/** \addtogroup pkt Packet Transmit and Receive
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
 * \file			tx.h
 ******************************************************************************/

#ifndef __OPENNSL_TX_H__
#define __OPENNSL_TX_H__

#include <opennsl/pkt.h>

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Transmit one or more packets.
 *
 *\description See the =opennsl_tx_f documentation for more details about these
 *          function types.
 *          The opennsl_pkt_t structure is owned by the OPENNSL TX API until
 *          the API returns (if callback was NULL), or the callback is
 *          executed.
 *          For opennsl_tx only: if unit is a remote device, the packet will
 *          be automatically tunneled.  In this case, OPENNSL_TX_BEST_EFFORT
 *          and OPENNSL_TX_RELIABLE will be checked in the packet's flags. 
 *          See.
 *
 *\param    unit [IN]   Unit number.
 *\param    tx_pkt [IN]   A single packet structure
 *\param    cookie [IN]   Application data returned with callback
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_UNIT Invalid device ID
 *\retval    OPENNSL_E_MEMORY Unable to allocate necessary structures for transmit
 *\retval    OPENNSL_E_PARAM See
 ******************************************************************************/
extern int opennsl_tx(
    int unit, 
    opennsl_pkt_t *tx_pkt, 
    void *cookie) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#if defined(OPENNSL_RPC_SUPPORT)
#endif
#include <opennsl/txX.h>
#endif /* __OPENNSL_TX_H__ */
/*@}*/
