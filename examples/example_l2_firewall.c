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
 * \file     example_l2_firewall.c
 *
 * \brief    Example code for Layer2 firewall
 *
 * \details  This example demonstrates a simple Layer 2 Firewall use case,
 * where a network administrator can block unauthorized stations from accessing
 * the network. The match criteria for the firewall rules can be either source
 * MAC address or destination MAC address. Frames matching the firewall rule
 * can either be dropped or forwarded. A centralized firewall server can
 * maintain the firewall rules for all the Layer2 switches in the network.
 * If the match criteria is source MAC address, packets originating with that
 * MAC address are matched. If the match criteria is destination MAC address,
 * packets destined to that MAC address are matched.
 *
 * This application also supports Warmboot feature. Warmboot is the
 * process of restarting the device driver software while the hardware is
 * running without interrupting the dataplane.
 *
 * Setup the following envinonment variable before running the application.
 * For Cold boot mode, use "export OPENNSL_BOOT_FLAGS = 0x000000".
 * For Warm boot mode, use "export OPENNSL_BOOT_FLAGS = 0x200000".
 *
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sal/driver.h>
#include <opennsl/error.h>
#include <opennsl/l2.h>
#include <opennsl/switch.h>
#include <opennsl/vlan.h>
#include <examples/util.h>

#define DEFAULT_UNIT  0
#define DEFAULT_VLAN  1
#define MAX_DIGITS_IN_CHOICE 5

char example_usage[] =
"Syntax: example_l2_firewall                                           \n\r"
"                                                                      \n\r"
"Paramaters: None.                                                     \n\r"
"                                                                      \n\r"
"Example: The following command is used to allow or block station A    \n\r"
"and station D that are part of VLAN 1 with MAC addresses              \n\r"
"00:00:00:00:00:01 and 00:00:00:00:00:04 respectively.                 \n\r"
"         example_l2_firewall                                          \n\r"
"                                                                      \n\r"
"Usage Guidelines: None.                                               \n\r";

/*****************************************************************//**
 * \brief Block the given station MAC address in the given VLAN.
 *
 * \param unit      [IN]    Unit number
 * \param mac       [IN]    802.3 MAC address
 * \param vlan      [IN]    VLAN ID
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_l2_firewall_block_station(int unit, opennsl_mac_t mac,
    opennsl_vlan_t vlan)
{
  opennsl_error_t rv;
  opennsl_l2_addr_t addr;

  opennsl_l2_addr_t_init(&addr, mac, vlan);

  /* Set the static flag, discard flags */
  addr.flags = (OPENNSL_L2_STATIC | OPENNSL_L2_DISCARD_SRC |
      OPENNSL_L2_DISCARD_DST);

  rv = opennsl_l2_addr_add(unit, &addr);

  return rv;
}

/*****************************************************************//**
 * \brief Unblock the given station MAC address in the given VLAN.
 *
 * \param unit     [IN]     Unit number
 * \param mac      [IN]     802.3 MAC address
 * \param vlan     [IN]     VLAN ID
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_l2_firewall_allow_station(int unit, opennsl_mac_t mac,
    opennsl_vlan_t vlan)
{
  opennsl_error_t rv;
  opennsl_l2_addr_t addr;

  /* Check whether the station exists in the firewall rules */
  rv = opennsl_l2_addr_get(unit, mac, vlan, &addr);

  if (rv == OPENNSL_E_NONE) {
    rv = opennsl_l2_addr_delete(unit, mac, vlan);
  }

  return rv;
}

/*****************************************************************//**
 * \brief Callback function to show L2 table information
 *
 * \param unit       [IN]     unit number
 * \param info       [IN]     L2 address structure
 * \param *user_data [IN]     User specified cookie
 *
 * \return OPENNSL_E_NONE
 ********************************************************************/
int _opennsl_l2_traverse_cb(
    int unit,
    opennsl_l2_addr_t *info,
    void *user_data)
{
  printf("MAC=%02x:%02x:%02x:%02x:%02x:%02x VLAN=%d PORT=%d\n", info->mac[0],info->mac[1],info->mac[2],info->mac[3],info->mac[4],info->mac[5], info->vid, info->port);
  return OPENNSL_E_NONE;
}

/*****************************************************************//**
 * \brief Main function for Layer2 firewall application
 *
 * \param argc, argv         commands line arguments
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int main(int argc, char *argv[])
{
  opennsl_error_t   rv;
  opennsl_vlan_t vlan = 1;
  int choice;
  int unit = DEFAULT_UNIT;
  void *user_data = NULL;
  unsigned int warm_boot;
  int index = 0;

  if(strcmp(argv[0], "gdb") == 0)
  {
    index = 1;
  }

  /* Example MAC address of stations A, B, C and D */
  opennsl_mac_t station_a = {0x00, 0x00, 0x00, 0x00, 0x00, 0x1};
  opennsl_mac_t station_d = {0x00, 0x00, 0x00, 0x00, 0x00, 0x4};

  if((argc != (index + 1)) || ((argc > (index + 1)) && (strcmp(argv[index + 1], "--help") == 0))) {
    printf("%s\n\r", example_usage);
    return OPENNSL_E_PARAM;
  }

  /* Initialize the system. */
  printf("Initializing the system.\r\n");
  rv = opennsl_driver_init((opennsl_init_t *) NULL);

  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to initialize the system. Error %s\r\n",
        opennsl_errmsg(rv));
    return rv;
  }

  warm_boot = opennsl_driver_boot_flags_get() & OPENNSL_BOOT_F_WARM_BOOT;

  if (!warm_boot)
  {

    /* Add ports to default vlan. */
    printf("Adding ports to default vlan.\r\n");
    rv = example_switch_default_vlan_config(unit);
    if(rv != OPENNSL_E_NONE) {
      printf("\r\nFailed to add default ports. rv: %s\r\n", opennsl_errmsg(rv));
      return rv;
    }
  }

  while (1) {
    printf("\r\nUser menu: Select one of the following options\r\n");
    printf("1. Apply firewall\n");
    printf("2. Remove firewall\n");
    printf("3. Show L2 table\n");
    printf("4. Save the configuration to scache\n");
#ifndef CDP_EXCLUDE
    printf("9. Launch diagnostic shell\n");
#endif
    printf("0. Quit the application\n");

    if(example_read_user_choice(&choice) != OPENNSL_E_NONE)
    {
        printf("Invalid option entered. Please re-enter.\n");
        continue;
    }
    switch(choice){

      case 1:
      {
        /* Apply firewall rules to block station A and D */
        rv = example_l2_firewall_block_station(unit, station_a, vlan);
        if (rv == OPENNSL_E_NONE) {
          printf("L2 firewall: station A blocked successfully\n");
        } else {
          printf("L2 firewall: failed to apply rule. Error %s\n",
                 opennsl_errmsg(rv));
          return rv;
        }

        rv = example_l2_firewall_block_station(unit, station_d, vlan);
        if (rv == OPENNSL_E_NONE) {
          printf("L2 firewall rule: station D blocked successfully\n");
        } else {
          printf("L2 firewall: failed to apply rule. Error %s\n",
                 opennsl_errmsg(rv));
          return rv;
        }
        break;
      } /* End of case 1 */

      case 2:
      {
        /* Remove the firewall rules applied to station A and D */
        rv = example_l2_firewall_allow_station(unit, station_a, vlan);
        if ((rv == OPENNSL_E_NONE) || (rv == OPENNSL_E_NOT_FOUND)) {
          printf("L2 firewall: station A un-blocked successfully\n");
        } else {
          printf("L2 firewall: failed to apply rule. Error %s\n",
                 opennsl_errmsg(rv));
          return rv;
        }

        rv = example_l2_firewall_allow_station(unit, station_d, vlan);
        if ((rv == OPENNSL_E_NONE) || (rv == OPENNSL_E_NOT_FOUND)) {
          printf("L2 firewall rule: station D un-blocked successfully\n");
        }  else {
          printf("L2 firewall: failed to apply rule. Error %s\n",
                 opennsl_errmsg(rv));
          return rv;
        }
        break;
      } /* End of case 2 */

      case 3:
      {
        /* Iterate over all valid entries in the L2 table */
        rv = opennsl_l2_traverse(unit, &_opennsl_l2_traverse_cb, user_data);
        if(rv != OPENNSL_E_NONE) {
          printf("\r\nFailed to iterate over L2 table. rv: %s\r\n", opennsl_errmsg(rv));
        }
        break;
      } /* End of case 3 */

      case 4:
      {
        /* Sync the current configuration */
        rv = opennsl_switch_control_set(DEFAULT_UNIT, opennslSwitchControlSync, 1);
        if(rv != OPENNSL_E_NONE) {
          printf("Failed to synchronize the configuration to scache. "
              "Error %s\n", opennsl_errmsg(rv));
          return rv;
        }
        printf("Warmboot configuration is saved successfully.\n");
        break;
      } /* End of case 4 */

#ifndef CDP_EXCLUDE
      case 9:
      {
        opennsl_driver_shell();
        break;
      }
#endif

      case 0:
      {
        printf("Exiting the application.\n");
        return OPENNSL_E_NONE;
      }
      default:
        break;
    } /* End of switch */
  } /* End of while */

  return OPENNSL_E_NONE;
}

