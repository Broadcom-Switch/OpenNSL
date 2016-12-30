/** \addtogroup types Types
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
 * \file			typesX.h
 ******************************************************************************/

#ifndef __OPENNSL_TYPESX_H__
#define __OPENNSL_TYPESX_H__

#include <sal/types.h>
#include <sal/commdefs.h>
#include <shared/bitop.h>
#include <shared/pbmp.h>
#include <shared/gport.h>
#include <shared/types.h>
#include <shared/util.h>

#if !defined(OPENNSL_LOCAL_UNITS_MAX)
#endif
#if !defined(OPENNSL_UNITS_MAX)
#endif
#if defined(LE_HOST)
#endif
/** opennsl_field_stat_e */
typedef enum opennsl_field_stat_e {
    opennslFieldStatBytes = 0,          /**< Byte count of traffic of all colors. */
    opennslFieldStatPackets = 1,        /**< Packet count of traffic of all
                                           colors. */
    opennslFieldStatDefault = opennslFieldStatPackets, /**< Default stat mode. */
    opennslFieldStatGreenBytes = 2,     /**< Byte count of green traffic. */
    opennslFieldStatGreenPackets = 3,   /**< Packet count of green traffic. */
    opennslFieldStatYellowBytes = 4,    /**< Byte count of yellow traffic. */
    opennslFieldStatYellowPackets = 5,  /**< Packet count of yellow traffic. */
    opennslFieldStatRedBytes = 6,       /**< Byte count of red traffic. */
    opennslFieldStatRedPackets = 7,     /**< Packet count of red traffic. */
    opennslFieldStatNotGreenBytes = 8,  /**< Byte count of not green traffic. */
    opennslFieldStatNotGreenPackets = 9, /**< Packet count of not green traffic. */
    opennslFieldStatNotYellowBytes = 10, /**< Byte count of not yellow traffic. */
    opennslFieldStatNotYellowPackets = 11, /**< Packet count of not yellow traffic. */
    opennslFieldStatNotRedBytes = 12,   /**< Byte count of not red traffic. */
    opennslFieldStatNotRedPackets = 13, /**< Packet count of not red traffic. */
    opennslFieldStatAcceptedBytes = 14, /**< Byte count of accepted traffic of all
                                           colors. */
    opennslFieldStatAcceptedPackets = 15, /**< Packet count of accepted traffic of
                                           all colors. */
    opennslFieldStatAcceptedGreenBytes = 16, /**< Byte count of accepted green traffic. */
    opennslFieldStatAcceptedGreenPackets = 17, /**< Packet count of accepted green
                                           traffic. */
    opennslFieldStatAcceptedYellowBytes = 18, /**< Byte count of accepted yellow
                                           traffic. */
    opennslFieldStatAcceptedYellowPackets = 19, /**< Packet count of accepted yellow
                                           traffic. */
    opennslFieldStatAcceptedRedBytes = 20, /**< Byte count of accepted red traffic. */
    opennslFieldStatAcceptedRedPackets = 21, /**< Packet count of accepted red traffic. */
    opennslFieldStatAcceptedNotGreenBytes = 22, /**< Byte count of accepted not green
                                           traffic. */
    opennslFieldStatAcceptedNotGreenPackets = 23, /**< Packet count of accepted not green
                                           traffic. */
    opennslFieldStatAcceptedNotYellowBytes = 24, /**< Byte count of accepted not yellow
                                           traffic. */
    opennslFieldStatAcceptedNotYellowPackets = 25, /**< Packet count of accepted not yellow
                                           traffic. */
    opennslFieldStatAcceptedNotRedBytes = 26, /**< Byte count of accepted not red
                                           traffic. */
    opennslFieldStatAcceptedNotRedPackets = 27, /**< Packet count of accepted not red
                                           traffic. */
    opennslFieldStatDroppedBytes = 28,  /**< Byte count of dropped traffic of all
                                           colors. */
    opennslFieldStatDroppedPackets = 29, /**< Packet count of dropped traffic of
                                           all colors. */
    opennslFieldStatDroppedGreenBytes = 30, /**< Byte count of dropped green traffic. */
    opennslFieldStatDroppedGreenPackets = 31, /**< Packet count of dropped green
                                           traffic. */
    opennslFieldStatDroppedYellowBytes = 32, /**< Byte count of dropped yellow traffic. */
    opennslFieldStatDroppedYellowPackets = 33, /**< Packet count of dropped yellow
                                           traffic. */
    opennslFieldStatDroppedRedBytes = 34, /**< Byte count of dropped red traffic. */
    opennslFieldStatDroppedRedPackets = 35, /**< Packet count of dropped red traffic. */
    opennslFieldStatDroppedNotGreenBytes = 36, /**< Byte count of dropped not green
                                           traffic. */
    opennslFieldStatDroppedNotGreenPackets = 37, /**< Packet count of dropped not green
                                           traffic. */
    opennslFieldStatDroppedNotYellowBytes = 38, /**< Byte count of dropped not yellow
                                           traffic. */
    opennslFieldStatDroppedNotYellowPackets = 39, /**< Packet count of dropped not yellow
                                           traffic. */
    opennslFieldStatDroppedNotRedBytes = 40, /**< Byte count of dropped not red
                                           traffic. */
    opennslFieldStatDroppedNotRedPackets = 41, /**< Packet count of dropped not red
                                           traffic. */
    opennslFieldStatOffset0Bytes = 42,  /**< Byte count at configurable offset 0. */
    opennslFieldStatOffset0Packets = 43, /**< Packet count at configurable offset
                                           0. */
    opennslFieldStatOffset1Bytes = 44,  /**< Byte count at configurable offset 1. */
    opennslFieldStatOffset1Packets = 45, /**< Packet count at configurable offset
                                           1. */
    opennslFieldStatOffset2Bytes = 46,  /**< Byte count at configurable offset 2. */
    opennslFieldStatOffset2Packets = 47, /**< Packet count at configurable offset
                                           2. */
    opennslFieldStatOffset3Bytes = 48,  /**< Byte count at configurable offset 3. */
    opennslFieldStatOffset3Packets = 49, /**< Packet count at configurable offset
                                           3. */
    opennslFieldStatOffset4Bytes = 50,  /**< Byte count at configurable offset 4. */
    opennslFieldStatOffset4Packets = 51, /**< Packet count at configurable offset
                                           4. */
    opennslFieldStatOffset5Bytes = 52,  /**< Byte count at configurable offset 5. */
    opennslFieldStatOffset5Packets = 53, /**< Packet count at configurable offset
                                           5. */
    opennslFieldStatOffset6Bytes = 54,  /**< Byte count at configurable offset 6. */
    opennslFieldStatOffset6Packets = 55, /**< Packet count at configurable offset
                                           6. */
    opennslFieldStatOffset7Bytes = 56,  /**< Byte count at configurable offset 7. */
    opennslFieldStatOffset7Packets = 57, /**< Packet count at configurable offset
                                           7. */
    opennslFieldStatCount = 58          /**< Always Last. Not a usable value. */
} opennsl_field_stat_t;

#endif /* __OPENNSL_TYPESX_H__ */
/*@}*/
