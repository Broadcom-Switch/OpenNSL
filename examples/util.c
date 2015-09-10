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
#include <opennsl/l2.h>
#include <opennsl/vlan.h>
#include <examples/util.h>

#define DEFAULT_VLAN          1
#define MAX_DIGITS_IN_CHOICE  5

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

  return OPENNSL_E_NONE;
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
 * \brief To get boot flags fetched from environment
 *
 * \return      unsigned int    Boot flags
 *****************************************************************************/
unsigned int opennsl_boot_flags_get(void)
{
  unsigned int boot_flags = 0;

  char *s = getenv("SOC_BOOT_FLAGS");

  if (s == NULL) {
    boot_flags = OPENNSL_BOOT_F_DEFAULT;
  } else {
    boot_flags = opennsl_ctoi(s, NULL);
  }

  return boot_flags;
}
