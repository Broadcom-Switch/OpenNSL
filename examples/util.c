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
 **********************************************************************
 * \file     util.c
 *
 * \brief    OpenNSL utility routines required for example applications
 *
 * \details  OpenNSL utility routines required for example applications
 *
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sal/driver.h>
#include <opennsl/error.h>
#include <opennsl/init.h>
#include <opennsl/l2.h>
#include <opennsl/vlan.h>
#include <opennsl/stg.h>
#include <opennsl/link.h>
#include <examples/util.h>

#define DEFAULT_VLAN          1
#define MAX_DIGITS_IN_CHOICE  5

/*************************************************************************//**
 * \brief Returns true if the device belongs to DNX family of devices
 *
 * \param unit   [IN]    unit number
 *
 * \return TRUE          If the device belongs to DNX family
 * \return FALSE         Otherwise
 *
 * \notes  This API needs to be invoked after initializing the OpenNSL driver
 ****************************************************************************/
int example_is_dnx_device(int unit)
{
  int rv = FALSE;
  opennsl_info_t info;
  opennsl_info_get(unit, &info);

  if(info.device == 0x8375) /* Qumran MX */
  {
    rv = TRUE;
  }
  return rv;
}

/*************************************************************************//**
 * \brief Returns true if the device is Qumran-MX device
 *
 * \param unit   [IN]    unit number
 *
 * \return TRUE          If the device is Qumran-MX device 
 * \return FALSE         Otherwise
 *
 * \notes  This API needs to be invoked after initializing the OpenNSL driver
 ****************************************************************************/
int example_is_qmx_device(int unit)
{
  int rv = FALSE;
  opennsl_info_t info;
  opennsl_info_get(unit, &info);

  if(info.device == 0x8375) /* Qumran MX */
  {
    rv = TRUE;
  }
  return rv;
}

/*****************************************************************//**
 * \brief Set default configuration (like STP state, speed/duplex) for 
 *        all ports
 *
 * \param unit   [IN]    unit number
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_port_default_config(int unit)
{
  opennsl_port_config_t pcfg;
  opennsl_port_info_t info;
  int rv;
  int port;
  int stp_state = OPENNSL_STG_STP_FORWARD;
  int stg = 1;
  int dnx_device = FALSE;

  dnx_device = example_is_dnx_device(unit);
  /*
   * Create VLAN with id DEFAULT_VLAN and
   * add ethernet ports to the VLAN
   */
  opennsl_port_config_t_init(&pcfg);

  rv = opennsl_port_config_get(unit, &pcfg);
  if (rv != OPENNSL_E_NONE)
  {
    printf("Failed to get port configuration. Error %s\n", opennsl_errmsg(rv));
    return rv;
  }

  /* Set the STP state to forward in default STG for all ports */
  OPENNSL_PBMP_ITER(pcfg.e, port)
  {
    rv = opennsl_stg_stp_set(unit, stg, port, stp_state);
    if (rv != OPENNSL_E_NONE)
    {
      printf("Failed to set STP state for unit %d port %d, Error %s\n",
          unit, port, opennsl_errmsg(rv));
      return rv;
    }
  }

  /* Setup default configuration on the ports */
  opennsl_port_info_t_init(&info);

  if(dnx_device == FALSE)
  {
    info.speed        = 0;
  }
  info.duplex       = OPENNSL_PORT_DUPLEX_FULL;
  info.pause_rx     = OPENNSL_PORT_ABILITY_PAUSE_RX;
  info.pause_tx     = OPENNSL_PORT_ABILITY_PAUSE_TX;
  info.linkscan     = OPENNSL_LINKSCAN_MODE_SW;
  info.autoneg      = FALSE;
  info.enable = 1;

  info.action_mask |= ( OPENNSL_PORT_ATTR_AUTONEG_MASK |
      OPENNSL_PORT_ATTR_DUPLEX_MASK   |
      OPENNSL_PORT_ATTR_PAUSE_RX_MASK |
      OPENNSL_PORT_ATTR_PAUSE_TX_MASK |
      OPENNSL_PORT_ATTR_LINKSCAN_MASK |
      OPENNSL_PORT_ATTR_ENABLE_MASK   );

  if(dnx_device == FALSE)
  {
    info.action_mask |= OPENNSL_PORT_ATTR_SPEED_MASK;
  }
  OPENNSL_PBMP_ITER(pcfg.e, port)
  {
    rv = opennsl_port_selective_set(unit, port, &info);
    if (OPENNSL_FAILURE(rv))
    {
      printf("Failed to set port config for unit %d, port %d, Error %s",
          unit, port, opennsl_errmsg(rv));
      return rv;
    }
  }

  return OPENNSL_E_NONE;
}

/*****************************************************************//**
 * \brief Add all ports to default vlan
 *
 * \param unit   [IN]    unit number
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_switch_default_vlan_config(int unit)
{
  opennsl_port_config_t pcfg;
  int port;
  int rv;

  /*
   * Create VLAN with id DEFAULT_VLAN and
   * add ethernet ports to the VLAN
   */
  rv = opennsl_port_config_get(unit, &pcfg);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to get port configuration. Error %s\n", opennsl_errmsg(rv));
    return rv;
  }

  rv = opennsl_vlan_port_add(unit, DEFAULT_VLAN, pcfg.e, pcfg.e);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to add ports to VLAN. Error %s\n", opennsl_errmsg(rv));
    return rv;
  }

  OPENNSL_PBMP_ITER(pcfg.e, port)
  {
    rv = opennsl_port_untagged_vlan_set(unit, port, DEFAULT_VLAN);
    if (OPENNSL_FAILURE(rv))
    {
      printf("Failed to set port untagged VLAN for unit %d, port %d, Error %s",
          unit, port, opennsl_errmsg(rv));
      return rv;
    }
  }

  return OPENNSL_E_NONE;
}

/**************************************************************************//**
 * \brief   Read a string from user.
 *
 * \param   buf            [IN/OUT] Buffer to store the string
 * \param   buflen         [IN]     Buffer length
 *
 * \return  Valid string if there are no errors. Otherwise, it returns 0
 *****************************************************************************/
char *example_read_user_string(char *buf, size_t buflen)
{
  int ch;

  if (fgets(buf, buflen, stdin) != 0)
  {
    size_t len = strlen(buf);
    if (len > 0 && buf[len-1] == '\n')
    {
      buf[len-1] = '\0';
    }
    else
    {
      while ((ch = getc(stdin)) != EOF && ch != '\n');
    }
    return buf;
  }
  return 0;
}
/**************************************************************************//**
 * \brief   Read numeric menu choice from user.
 *
 * \param   choice         [IN/OUT] choice
 *
 * \return  OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
int example_read_user_choice(int *choice)
{
  char val;
  char digits[MAX_DIGITS_IN_CHOICE + 1];
  int idx = 0;
  int valid = TRUE;

  /* parse input string until \n */
  while((val = getchar()) != '\n')
  {
    if ((val >= '0' && val <= '9') && idx < MAX_DIGITS_IN_CHOICE)
    {
      digits[idx++] = val;
    }
    else
    {
      valid = FALSE;
    }
  }
  if ((valid == TRUE) && idx != 0)
  {
    digits[idx] = '\0';
    *choice = atoi(digits);
    return(OPENNSL_E_NONE);
  }
  else
  {
    *choice = -1;
    return(OPENNSL_E_FAIL);
  }
}

/*****************************************************************//**
 * \brief Parse MAC address string
 *
 * \param buf      [IN]    MAC address in string format
 * \param macp     [OUT]   MAC address in integer format
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 *****************************************************************************/
int opennsl_mac_parse(char *buf, unsigned char *macp)
{
  int   i, c1, c2;
  char  *s;
#define MAC_ADDR_LEN 17

  macp[0] = macp[1] = macp[2] = 0;
  macp[3] = macp[4] = macp[5] = 0;

  if ((buf == NULL) || (strlen(buf) > MAC_ADDR_LEN)) {
    return OPENNSL_E_FAIL;
  }

  /* skip leading 0x if plain hex format */
  if (buf[0] == '0' && (buf[1] == 'x' || buf[1] == 'X')) {
    buf += 2;
  }

  /* start at end of string and work backwards */
  for (s = buf; *s; s++) {
    ;
  }
  for (i = 5; i >= 0 && s >= buf; i--) {
    c1 = c2 = 0;
    if (--s >= buf) {
      if (*s >= '0' && *s <= '9') {
        c2 = *s - '0';
      } else if (*s >= 'a' && *s <= 'f') {
        c2 = *s - 'a' + 10;
      } else if (*s >= 'A' && *s <= 'F') {
        c2 = *s - 'A' + 10;
      } else if (*s == ':') {
        ;
      } else {
        return OPENNSL_E_FAIL;
      }
    }
    if (*s != ':' && --s >= buf) {
      if (*s >= '0' && *s <= '9') {
        c1 = *s - '0';
      } else if (*s >= 'a' && *s <= 'f') {
        c1 = *s - 'a' + 10;
      } else if (*s >= 'A' && *s <= 'F') {
        c1 = *s - 'A' + 10;
      } else if (*s == ':') {
        ;
      } else {
        return OPENNSL_E_FAIL;
      }
    }

    if (s > buf && s[-1] == ':') {
      --s;
    }
    macp[i] = c1 << 4 | c2;
  }
  return OPENNSL_E_NONE;
}

/*****************************************************************//**
 * \brief To print the MAC address
 *
 * \return void
 ********************************************************************/
void l2_print_mac(char *str, opennsl_mac_t mac_address){
  unsigned int a,b,c,d,e,f;
  a = 0xff & mac_address[0];
  b = 0xff & mac_address[1];
  c = 0xff & mac_address[2];
  d = 0xff & mac_address[3];
  e = 0xff & mac_address[4];
  f = 0xff & mac_address[5];
  printf("%s %02x:%02x:%02x:%02x:%02x:%02x",
      str,
      a,b,c,
      d,e,f);
  return;
}

/*****************************************************************//**
 * \brief Parse IP string into a IP value
 *
 * \param ip_str   [IN]    IP address in decimal dotted format
 * \param ip_val   [OUT]   IP address in integer format
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int opennsl_ip_parse(char *ip_str, unsigned int *ip_val)
{
  unsigned int num = 0, val;
  char *tok;
  int count = 0;
  char buf[16]; /* Maximum length of IP address in dotten notation */

  if((ip_str == NULL) || (ip_val == NULL) || (strlen(ip_str) > 16))
  {
    return -1;
  }
  strcpy(buf, ip_str);
  tok = strtok(buf, ".");
  while(tok != NULL)
  {
    count++;
    val = atoi(tok);
    if((val < 0) || (val > 0xff))
    {
      return -1;
    }
    num = (num << 8) + val;
    tok = strtok(NULL, ".");
  }
  if(count != 4)
  {
    return -1;
  }
  *ip_val = num;

  return 0;
}

/**************************************************************************//**
 * \brief To print IP address in dotted decimal format
 *
 *
 * \param    str  [OUT]   Buffer to store the IP address
 * \param    host [IN]    MAC address in integer format
 *
 * \return      void
 *****************************************************************************/
void print_ip_addr(char *str, unsigned int host)
{
  int a,b,c,d;

  a = (host >> 24) & 0xff;
  b = (host >> 16) & 0xff;
  c = (host >> 8 ) & 0xff;
  d = host & 0xff;
  printf("%s %d.%d.%d.%d", str, a,b,c,d);
}

/**************************************************************************//**
 * \brief To convert a C-style constant to integer.
 *
 *
 * \param    str  [OUT]   Buffer to store the IP address
 * \param    host [IN]    MAC address in integer format
 *
 * \return      void
 *****************************************************************************/
int opennsl_ctoi(const char *s, char **end)
{
  unsigned int  n, neg;
  int base = 10;

  if (s == 0) {
    if (end != 0) {
      end = 0;
    }
    return 0;
  }

  s += (neg = (*s == '-'));

  if (*s == '0') {
    s++;
    if (*s == 'x' || *s == 'X') {
      base = 16;
      s++;
    } else if (*s == 'b' || *s == 'B') {
      base = 2;
      s++;
    } else {
      base = 8;
    }
  }

  for (n = 0; ((*s >= 'a' && *s < 'a' + base - 10) ||
        (*s >= 'A' && *s < 'A' + base - 10) ||
        (*s >= '0' && *s <= '9')); s++) {
    n = n * base + ((*s <= '9' ? *s : *s + 9) & 15);
  }

  if (end != 0) {
    *end = (char *) s;
  }

  return (int) (neg ? -n : n);
}

/**************************************************************************//**
 * \brief To get the number of front panel ports
 *
 * \param    unit [IN]    unit number
 * \param    int  [OUT]   Number of front panel ports
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 *****************************************************************************/
int example_max_port_count_get(int unit, int *count)
{
  int rc;
  opennsl_port_config_t pcfg;
  int num_ports;
  int num_front_panel_ports;

  rc = opennsl_port_config_get(unit, &pcfg);
  if (rc != OPENNSL_E_NONE) {
    printf("Failed to get port configuration. Error %s\n", opennsl_errmsg(rc));
    return rc;
  }

  OPENNSL_PBMP_COUNT(pcfg.ge, num_ports);
  num_front_panel_ports = num_ports;
  OPENNSL_PBMP_COUNT(pcfg.xe, num_ports);
  num_front_panel_ports += num_ports;

  *count = num_front_panel_ports;
  return rc;
}

