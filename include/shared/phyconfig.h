/*********************************************************************
 *
 * (C) Copyright Broadcom Corporation 2013-2016
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
 * File:        phyconfig.h
 * Details:     This file defines PHY configuration modes.
 *
 * 				Its contents are not used directly by applications; 
 * 				it is used only by header files of parent APIs which
 * 				need to define port modes.
 *********************************************************************/

#ifndef _SHR_PHYCONFIG_H
#define _SHR_PHYCONFIG_H

#include <shared/port.h>
#include <shared/portmode.h>
#include <shared/port_ability.h>

/*
 * Structure:
 *	_shr_phy_config_t
 * Purpose:
 *	Defines the operating mode of a PHY.
 */

typedef struct _shr_phy_config_s {
    int			enable;
    int			preferred;
    int			autoneg_enable;
    _shr_port_mode_t	autoneg_advert;
    _shr_port_ability_t advert_ability;
    int			force_speed;
    int			force_duplex;
    int			master;
    _shr_port_mdix_t    mdix;
} _shr_phy_config_t;

typedef int (*_shr_port_phy_reset_cb_t)(int unit, _shr_port_t port, 
                                        void *user_data);

typedef void (*_shr_port_medium_status_cb_t)(int unit, int port, 
                                             _shr_port_medium_t medium,
                                             void *user_arg);

#endif	/* !_SHR_PHYCONFIG_H */
