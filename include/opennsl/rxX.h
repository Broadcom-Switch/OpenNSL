/** \addtogroup pkt Packet Transmit and Receive
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
 * \file			rxX.h
 ******************************************************************************/

#ifndef __OPENNSL_RXX_H__
#define __OPENNSL_RXX_H__

#include <opennsl/types.h>
#include <opennsl/pkt.h>
#include <opennsl/tx.h>

/***************************************************************************//** 
 *\brief Set/get the RX per-Cos rate limiting value.
 *
 *\description These functions configure rate limiting on a
 *          per-software-Cos-queue basis.  If packets for the given CoS are
 *          received at a rate higher than this setting,  they will be
 *          discarded in the interrupt handler.
 *          Both functions support a value of OPENNSL_RX_RATE_NOLIMIT for pps
 *          to indicate rate limiting is disabled.
 *          Setting the unit number to OPENNSL_RX_SYSTEM_UNIT (only in
 *          SDK-5.3.0 or SDK-5.2.4; see =opennsl_rx_rate_set ) will result in
 *          an error returned because system wide burst settings are not
 *          supported. .
 *
 *\param    unit [IN]   Unit number.
 *\param    cos [IN]   CoS to configure
 *\param    pps [IN]   Rate in packets/second
 *
 *\retval    OPENNSL_E_XXX Error during required initialization
 ******************************************************************************/
extern int opennsl_rx_cos_rate_set(
    int unit, 
    int cos, 
    int pps) LIB_DLL_EXPORTED ;

#if defined(OPENNSL_RPC_SUPPORT) || defined(OPENNSL_RCPU_SUPPORT)
#endif
#endif /* __OPENNSL_RXX_H__ */
/*@}*/
