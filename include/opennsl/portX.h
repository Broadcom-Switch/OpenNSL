/** \addtogroup port Port Management
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
 * \file			portX.h
 ******************************************************************************/

#ifndef __OPENNSL_PORTX_H__
#define __OPENNSL_PORTX_H__

#include <shared/portmode.h>
#include <shared/port.h>
#include <shared/phyconfig.h>
#include <shared/phyreg.h>
#include <shared/switch.h>
#include <opennsl/types.h>
#include <opennsl/stat.h>
#include <shared/port_ability.h>

/***************************************************************************//** 
 *\brief Set or retrieve color assignment for a given port and Canonical Format
 *       Indicator (CFI).
 *
 *\description Assign or examine the color with which packets are marked when
 *          they arrive on the given port with the specified Canonical Format
 *          Indicator (CFI) in the VLAN control index.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    cfi [IN]   VLAN Canonical Format Indicator (CFI)
 *\param    color [IN]   One of the OPENNSL color selections: opennslColorGreen,
 *          opennslColorYellow, opennslColorRed, opennslColorDropFirst,
 *          opennslColorPreserve
 *
 *\retval    OPENNSL_E_UNAVAIL Not supported.
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_port_cfi_color_set(
    int unit, 
    opennsl_port_t port, 
    int cfi, 
    opennsl_color_t color) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set or retrieve color assignment for a given port and Canonical Format
 *       Indicator (CFI).
 *
 *\description Assign or examine the color with which packets are marked when
 *          they arrive on the given port with the specified Canonical Format
 *          Indicator (CFI) in the VLAN control index.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    cfi [IN]   VLAN Canonical Format Indicator (CFI)
 *\param    color [OUT]   One of the OPENNSL color selections: opennslColorGreen,
 *          opennslColorYellow, opennslColorRed, opennslColorDropFirst,
 *          opennslColorPreserve
 *
 *\retval    OPENNSL_E_UNAVAIL Not supported.
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_port_cfi_color_get(
    int unit, 
    opennsl_port_t port, 
    int cfi, 
    opennsl_color_t *color) LIB_DLL_EXPORTED ;

#endif /* __OPENNSL_PORTX_H__ */
/*@}*/
