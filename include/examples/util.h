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
 * \file     util.h
 *
 * \brief    OpenNSL utility routines required for example applications
 *
 * \details  OpenNSL utility routines required for example applications
 *
 ************************************************************************/
#ifndef _OPENNSL_EXAMPLE_UTIL_H
#define _OPENNSL_EXAMPLE_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sal/driver.h>

#define OPENNSL_BOOT_F_DEFAULT          0x000000
#define OPENNSL_BOOT_F_WARM_BOOT        0x200000

/*****************************************************************//**
 * \brief Add all ports to default vlan
 *
 * \param unit   [IN]    unit number
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_switch_default_vlan_config(int unit);

/**************************************************************************//**
 * \brief   Read a string from user.
 *
 * \param   buf            [IN/OUT] Buffer to store the string
 * \param   buflen         [IN]     Buffer length
 *
 * \return  Valid string if there are no errors. Otherwise, it returns 0
 *****************************************************************************/
 char *example_read_user_string(char *buf, size_t buflen);

/**************************************************************************//**
 * \brief   Read numeric menu choice from user.
 *
 * \param   choice         [IN/OUT] choice
 *
 * \return  OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
int example_read_user_choice(int *choice);

/*****************************************************************//**
 * \brief Parse MAC address string
 *
 * \param buf      [IN]    MAC address in string format
 * \param macp     [OUT]   MAC address in integer format
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 *****************************************************************************/
int opennsl_mac_parse(char *buf, unsigned char *macp);

/*****************************************************************//**
 * \brief To print the MAC address
 *
 * \return void
 ********************************************************************/
void l2_print_mac(char *str, opennsl_mac_t mac_address);

/*****************************************************************//**
 * \brief Parse IP string into a IP value
 *
 * \param ip_str   [IN]    IP address in decimal dotted format
 * \param ip_val   [OUT]   IP address in integer format
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int opennsl_ip_parse(char *ip_str, unsigned int *ip_val);

/**************************************************************************//**
 * \brief To print IP address in dotted decimal format
 *
 *
 * \param    str  [OUT]   Buffer to store the IP address
 * \param    host [IN]    MAC address in integer format
 *
 * \return      void
 *****************************************************************************/
void print_ip_addr(char *str, unsigned int host);

/**************************************************************************//**
 * \brief To get the number of front panel ports
 *
 * \param    unit [IN]    unit number
 * \param    int  [OUT]   Number of front panel ports
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 *****************************************************************************/
int example_max_port_count_get(int unit, int *count);

#endif /* _OPENNSL_EXAMPLE_UTIL_H */
