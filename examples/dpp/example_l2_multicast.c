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
 *
 * \file         example_l2_multicast.c
 *
 * \brief        OpenNSL example application for Layer 2 multicast
 *
 * \details      This application allows the user to
 *               1) Create multicast group
 *               2) Add a port to multicast group
 *               3) Remove a port from multicast group
 *
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sal/driver.h>
#include <opennsl/error.h>
#include <opennsl/l2.h>
#include <opennsl/multicast.h>
#include <examples/util.h>

#define DEFAULT_UNIT 0
#define DEFAULT_VLAN 1
#define MCAST_GROUP_ID  10

char example_usage[] =
"Syntax: example_l2_multicast                                          \n\r"
"                                                                      \n\r"
"Paramaters: None                                                      \n\r"
"                                                                      \n\r"
"Example: The following command is used to create a multicast group    \n\r"
"         and add or delete multicast members.                         \n\r"
"         example_l2_multicast                                         \n\r"
"                                                                      \n\r"
"Usage Guidelines: This program request the user to enter the following\n\r"
"                  parameters interactively                            \n\r"
"       MAC address - Multicast group MAC address                      \n\r"
"       port        - Multicast group port members                     \n\r"
"                                                                      \n\r"
"       Testing:                                                       \n\r"
"       1) Add ports to the multicast group and verify that traffic    \n\r"
"          destined to Multicast MAC address is received by all        \n\r"
"          multicast group members.                                    \n\r"
"       2) Remove a port from the multicast group and verify that      \n\r"
"          traffic destined to Multicast MAC address is not received   \n\r"
"          by removed multicast group member.                          \n\r"
"       3) Verify that traffic to unknown unicast MAC address is       \n\r"
"          received by all ports in the VLAN.                          \n\r"
"                                                                      \n\r";

/**************************************************************************//**
 * \brief To add an FDB entry
 *
 * \param    unit          [IN] Unit number
 * \param    mac           [IN] MAC address
 * \param    vlan          [IN] VLAN ID
 * \param    is_mc         [IN] Is MAC address a multicast
 * \param    dest_gport    [IN] destination port
 * \param    dest_mcg      [IN] destination multicast group
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
int example_l2_entry_add(int unit, opennsl_mac_t mac, opennsl_vlan_t vlan,
    int is_mc, int dest_gport, int dest_mcg)
{
  int rv = OPENNSL_E_NONE;
  opennsl_l2_addr_t l2_addr;

  opennsl_l2_addr_t_init(&l2_addr, mac, vlan);
  if(is_mc == 1) {
    /* add multicast entry */
    l2_addr.flags = OPENNSL_L2_STATIC | OPENNSL_L2_MCAST;
    l2_addr.l2mc_group = dest_mcg;
  } else {
    /* add static entry */
    l2_addr.flags = OPENNSL_L2_STATIC;
    l2_addr.port = dest_gport;
  }
  rv = opennsl_l2_addr_add(unit,&l2_addr);
  return rv;
}

/**************************************************************************//**
 * \brief To create multicast group
 *
 * \param    unit          [IN] Unit number
 * \param    mcg           [IN] Multicast group ID
 * \param    egress_mc     [IN] Egress/Ingress multicast
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
int example_multicast_create(int unit, int mcg, int egress_mc)
{
  int rv = OPENNSL_E_NONE;
  int flags;
  opennsl_multicast_t mc_group = mcg;

  flags = OPENNSL_MULTICAST_WITH_ID | OPENNSL_MULTICAST_TYPE_L2;
  if (egress_mc)
  {
    flags |= OPENNSL_MULTICAST_EGRESS_GROUP;
  }
  else
  {
    flags |= OPENNSL_MULTICAST_INGRESS_GROUP;
  }
  rv = opennsl_multicast_create(unit, flags, &mc_group);
  return rv;
}

/*****************************************************************//**
 * \brief Main function for Layer 2 multicast application
 *
 * \param argc, argv         commands line arguments
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int main(int argc, char *argv[])
{
  int rv = 0;
  int choice;
  int unit = DEFAULT_UNIT;
  int port;
  int mcg = MCAST_GROUP_ID;
  int encap_id = NULL;
  opennsl_gport_t gport;
  char macstr[18];
  opennsl_mac_t mac;
  opennsl_vlan_t vlan = DEFAULT_VLAN;

  if((argc != 1) || ((argc > 1) && (strcmp(argv[1], "--help") == 0))) {
    printf("%s\n\r", example_usage);
    return OPENNSL_E_PARAM;
  }

  /* Initialize the system. */
  rv = opennsl_driver_init((opennsl_init_t *) NULL);

  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to initialize the system. Error: %s\r\n",
           opennsl_errmsg(rv));
    return rv;
  }

  rv = example_port_default_config(unit);
  if (rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to apply default config on ports, rc = %d (%s).\r\n",
           rv, opennsl_errmsg(rv));
  }

  /* Add ports to default vlan. */
  printf("Adding ports to default vlan.\r\n");
  rv = example_switch_default_vlan_config(unit);
  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to add default ports. Error: %s\r\n",
        opennsl_errmsg(rv));
  }

  if(example_multicast_create(unit, mcg, 0) != OPENNSL_E_NONE)
  {
    printf("\r\nFailed to create multicast group. Error: %s\r\n",
        opennsl_errmsg(rv));
    return OPENNSL_E_FAIL;
  }

  printf("Enter multicast MAC address in xx:xx:xx:xx:xx:xx format "
      "(Ex: 01:00:00:01:02:03): \n");
  if(example_read_user_string(macstr, sizeof(macstr)) == NULL)
  {
    printf("\n\rInvalid MAC address entered.\n\r");
    return OPENNSL_E_FAIL;
  }

  if(opennsl_mac_parse(macstr, mac) != OPENNSL_E_NONE)
  {
    printf("\n\rFailed to parse input MAC address.\n\r");
    return OPENNSL_E_FAIL;
  }

  rv = example_l2_entry_add(unit, mac, vlan, 1, 0, mcg);
  if(rv != OPENNSL_E_NONE)
  {
    printf("\n\rFailed to update FDB with multicast MAC address. "
        "Error: %s\n\r", opennsl_errmsg(rv));
    return OPENNSL_E_FAIL;
  }

  while(1) {
    printf("\r\nUser menu: Select one of the following options\r\n");
    printf("1. Add port to multicast group\n");
    printf("2. Remove port from multicast group\n");
#ifdef INCLUDE_DIAG_SHELL
    printf("9. Launch diagnostic shell\n");
#endif
    printf("0. Quit the application.\r\n");

    if(example_read_user_choice(&choice) != OPENNSL_E_NONE)
    {
      printf("Invalid option entered. Please re-enter.\n");
      continue;
    }

    switch(choice)
    {
      case 1:
      {
        printf("Enter multicast group member port number: \n");
        if(example_read_user_choice(&port) != OPENNSL_E_NONE)
        {
          printf("Invalid option entered. Please re-enter.\n");
          continue;
        }

        if(encap_id == NULL)
        {
          rv = opennsl_multicast_l2_encap_get(0, mcg, 3, vlan, &encap_id);
          if(rv != OPENNSL_E_NONE)
          {
            printf("Failed to get encapsulation ID, Error: %d\r\n",
                opennsl_errmsg(rv));
            return rv;
          }
        }
        OPENNSL_GPORT_LOCAL_SET(gport, port);
        rv = opennsl_multicast_ingress_add(0, mcg, gport, encap_id);
        if(rv != OPENNSL_E_NONE && rv != OPENNSL_E_EXISTS)
        {
          printf("\r\nFailed to add the port to multicast group. "
              "Error: %s\r\n", opennsl_errmsg(rv));
        }
        else
        {
          printf("Port %d is added to Multicast group successfully\n", port);
        }
        break;
      }
      case 2:
      {
        printf("Enter multicast group member port number: \n");
        if(example_read_user_choice(&port) != OPENNSL_E_NONE)
        {
          printf("Invalid option entered. Please re-enter.\n");
          continue;
        }

        OPENNSL_GPORT_LOCAL_SET(gport, port);
        rv = opennsl_multicast_ingress_delete(0, mcg, gport, encap_id);
        if(rv != OPENNSL_E_NONE && rv != OPENNSL_E_NOT_FOUND)
        {
          printf("\r\nFailed to remove the port from multicast group. "
              "Error: %s\r\n", opennsl_errmsg(rv));
        }
        else
        {
          printf("Port %d is removed from Multicast group "
              "successfully\n", port);
        }
        break;
      }
#ifdef INCLUDE_DIAG_SHELL
      case 9:
      {
        opennsl_driver_shell();
        break;
      }
#endif

      case 0:
      {
        printf("Exiting the application.\n");
        rv = opennsl_driver_exit();
        return rv;
      }
      default:
      break;
    } /* End of switch */
  }

  return rv;
}

