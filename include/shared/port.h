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
 ********************************************************************
 * File:        port.h
 * Details:     This file defines common network port parameters.
 *
 * 				Its contents are not used directly by applications;
 * 				it is used only by header files of parent APIs 
 * 				which need to define port parameters.
 * *******************************************************************/

#ifndef _SHR_PORT_H
#define _SHR_PORT_H

/*
 * Typedef:
 *    _shr_port_t
 * Purpose:
 *    Port number type for shared definitions
 */
#include <sal/types.h>

typedef int _shr_port_t;

/*
 * Defines:
 *	_SHR_PORT_DUPLEX_*
 * Purpose:
 *	Defines duplexity of a port
 */

typedef enum _shr_port_duplex_e {
    _SHR_PORT_DUPLEX_HALF,
    _SHR_PORT_DUPLEX_FULL,
    _SHR_PORT_DUPLEX_COUNT	/* last, please */
} _shr_port_duplex_t;

/*
 * Defines:
 *  _SHR_PORT_IF_*
 * Purpose:
 *  Defines interface type between MAC and PHY.
 */

typedef enum _shr_port_if_e {
    _SHR_PORT_IF_NOCXN, /* No physical connection */
    _SHR_PORT_IF_NULL,  /* Pass-through connection without PHY */
    _SHR_PORT_IF_MII,
    _SHR_PORT_IF_GMII,
    _SHR_PORT_IF_SGMII,
    _SHR_PORT_IF_TBI,
    _SHR_PORT_IF_XGMII,
    _SHR_PORT_IF_RGMII,
    _SHR_PORT_IF_RvMII,
    _SHR_PORT_IF_SFI,
    _SHR_PORT_IF_XFI,
    _SHR_PORT_IF_KR,
    _SHR_PORT_IF_KR4,
    _SHR_PORT_IF_CR,
    _SHR_PORT_IF_CR4,
    _SHR_PORT_IF_XLAUI,
    _SHR_PORT_IF_SR,
    _SHR_PORT_IF_RXAUI,
    _SHR_PORT_IF_XAUI,
    _SHR_PORT_IF_SPAUI,
    _SHR_PORT_IF_QSGMII,
    _SHR_PORT_IF_ILKN,
    _SHR_PORT_IF_RCY,
    _SHR_PORT_IF_FAT_PIPE,
    _SHR_PORT_IF_CGMII,
    _SHR_PORT_IF_CAUI,
    _SHR_PORT_IF_LR,
    _SHR_PORT_IF_LR4,
    _SHR_PORT_IF_SR4,
    _SHR_PORT_IF_KX,
    _SHR_PORT_IF_ZR,
    _SHR_PORT_IF_SR10,
    _SHR_PORT_IF_OTL,
    _SHR_PORT_IF_CPU,
    _SHR_PORT_IF_OLP,
    _SHR_PORT_IF_OAMP,
    _SHR_PORT_IF_ERP,
    _SHR_PORT_IF_TM_INTERNAL_PKT,   
    _SHR_PORT_IF_SR2,
    _SHR_PORT_IF_KR2,
    _SHR_PORT_IF_CR2,
    _SHR_PORT_IF_XFI2,
    _SHR_PORT_IF_XLAUI2,
    _SHR_PORT_IF_CR10,
    _SHR_PORT_IF_KR10,
    _SHR_PORT_IF_LR10,
    _SHR_PORT_IF_ER,
    _SHR_PORT_IF_ER2,
    _SHR_PORT_IF_ER4,
    _SHR_PORT_IF_CX,
    _SHR_PORT_IF_CX2,
    _SHR_PORT_IF_CX4,
    _SHR_PORT_IF_CAUI_C2C,
    _SHR_PORT_IF_CAUI_C2M,
    _SHR_PORT_IF_VSR,
    _SHR_PORT_IF_LR2,
    _SHR_PORT_IF_LRM,
    _SHR_PORT_IF_XLPPI,
    _SHR_PORT_IF_2500X,
    _SHR_PORT_IF_SAT,
    _SHR_PORT_IF_IPSEC,
    _SHR_PORT_IF_LBG,
    _SHR_PORT_IF_CAUI4,
    _SHR_PORT_IF_5000X,
    _SHR_PORT_IF_EVENTOR,
    _SHR_PORT_IF_COUNT /* last, please */
} _shr_port_if_t;

/*
 * Defines:
 *  _SHR_PORT_STP_*
 * Purpose:
 *  Defines the spanning tree states of a port.
 */

typedef enum _shr_port_stp_e {
    _SHR_PORT_STP_DISABLE   = 0,
    _SHR_PORT_STP_BLOCK     = 1,
    _SHR_PORT_STP_LISTEN    = 2,
    _SHR_PORT_STP_LEARN     = 3,
    _SHR_PORT_STP_FORWARD   = 4,
    _SHR_PORT_STP_COUNT = 5   /* last, please */
} _shr_port_stp_t;

/*
 * Defines:
 *      _SHR_PORT_MDIX_*
 * Purpose:
 *      Defines the MDI crossover (MDIX) modes for the port
 */
typedef enum _shr_port_mdix_e {
    _SHR_PORT_MDIX_AUTO,
    _SHR_PORT_MDIX_FORCE_AUTO,
    _SHR_PORT_MDIX_NORMAL,
    _SHR_PORT_MDIX_XOVER,
    _SHR_PORT_MDIX_COUNT    /* last, please */
} _shr_port_mdix_t;

/*
 * Defines:
 *      _SHR_PORT_MDIX_STATUS_*
 * Purpose:
 *      Defines the MDI crossover state
 */
typedef enum _shr_port_mdix_status_e {
    _SHR_PORT_MDIX_STATUS_NORMAL,
    _SHR_PORT_MDIX_STATUS_XOVER,
    _SHR_PORT_MDIX_STATUS_COUNT       /* last, please */
} _shr_port_mdix_status_t;

/*
 * Defines:
 *      _SHR_PORT_MEDIUM_*
 * Purpose:
 *      Supported physical mediums
 */
typedef enum _shr_port_medium_e {
    _SHR_PORT_MEDIUM_NONE              = 0,
    _SHR_PORT_MEDIUM_COPPER            = 1,
    _SHR_PORT_MEDIUM_FIBER             = 2,
    _SHR_PORT_MEDIUM_COUNT             /* last, please */
} _shr_port_medium_t;

/*
 * Defines:
 *     _SHR_PORT_PHY_CONTROL_*
 * Purpose:
 *     PHY specific control settings
 */
typedef enum _shr_port_phy_control_e {
    _SHR_PORT_PHY_CONTROL_FORWARD_ERROR_CORRECTION = 74,
    _SHR_PORT_PHY_CONTROL_SOFTWARE_RX_LOS = 214,
    _SHR_PORT_PHY_CONTROL_SOFTWARE_RX_LOS_LINK_WAIT_TIMER_US = 328,
    _SHR_PORT_PHY_CONTROL_SOFTWARE_RX_LOS_RESTART_TIMER_US = 329
} _shr_port_phy_control_t;

/*
 * Defines:
 *     _SHR_PORT_PRBS_POLYNOMIAL_*
 * Purpose:
 *     PRBS polynomial type
 */
typedef enum _shr_port_prbs_polynomial_e {
    _SHR_PORT_PRBS_POLYNOMIAL_X7_X6_1      = 0,
    _SHR_PORT_PRBS_POLYNOMIAL_X15_X14_1    = 1,
    _SHR_PORT_PRBS_POLYNOMIAL_X23_X18_1    = 2,
    _SHR_PORT_PRBS_POLYNOMIAL_X31_X28_1    = 3,
    _SHR_PORT_PRBS_POLYNOMIAL_X9_X5_1      = 4,
    _SHR_PORT_PRBS_POLYNOMIAL_X11_X9_1     = 5,
    _SHR_PORT_PRBS_POLYNOMIAL_X58_X31_1    = 6
} _shr_port_prbs_polynomial_t;

/*
 * Defines:
 *     _SHR_PORT_PHY_CONTROL_FEC_*
 * Purpose:
 *     PHY specific values for _SHR_PORT_PHY_CONTROL_FORWARD_ERROR_CORRECTION
 */
typedef enum _shr_port_phy_control_fec_e {
    _SHR_PORT_PHY_CONTROL_FEC_OFF,
    _SHR_PORT_PHY_CONTROL_FEC_ON,
    _SHR_PORT_PHY_CONTROL_FEC_AUTO
} _shr_port_phy_control_fec_t;

typedef enum _shr_port_phy_control_rx_los_e {
    _SHR_PORT_PHY_CONTROL_RX_LOS_NONE,
    _SHR_PORT_PHY_CONTROL_RX_LOS_SOFTWARE,
    _SHR_PORT_PHY_CONTROL_RX_LOS_FIRMWARE
} _shr_port_phy_control_rx_los_t;

#endif	/* !_SHR_PORT_H */
