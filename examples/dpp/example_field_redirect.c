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
 *
 * \file         example_field_redirect.c
 *
 * \brief        OPENNSL example program to demonstrate field processor
 *
 * \details      This example demonstrates redirection of traffic with 
 *               destination MAC = MAC_DA to a given destination port 
 *               along with the option to display the number of redirected 
 *               packets
 *
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sal/driver.h>
#include <opennsl/error.h>
#include <opennsl/vlan.h>
#include <opennsl/port.h>
#include <opennsl/field.h>
#include <examples/util.h>

char example_usage[] =
"Syntax: example_field_redirect                                         \n\r"
"                                                                       \n\r"
"Paramaters: None.                                                      \n\r"
"                                                                       \n\r"
"Example: The following command is used to redirect traffic with        \n\r"
"         destination MAC = MAC_DA to a specified destination port.     \n\r"
"         It also provides an option to display the number of packets   \n\r"
"         redirected to destination port.                               \n\r"
"                                                                       \n\r"
"         example_field_redirect                                        \n\r"
"                                                                       \n\r"
"Usage Guidelines: None.                                                \n\r";

#define DEFAULT_UNIT  0
#define NEWCOS_VAL    3
#define MAC_DA        {0x00, 0x00, 0x01, 0x00, 0x02, 0x00}
#define MAC_MASK      {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}

opennsl_field_group_t grp  = 1;
opennsl_field_entry_t eid  = 0;
int stat_id                = 2;
opennsl_field_stat_t stats = opennslFieldStatPackets;

#define CALL_IF_ERROR_RETURN(op)                              \
  do                                                          \
  {                                                           \
    int __rv__;                                               \
      if ((__rv__ = (op)) < 0) {                              \
        printf("%s:%s: line %d rv: %d failed: %s\n",          \
            __FILE__, __FUNCTION__, __LINE__, __rv__,         \
            opennsl_errmsg(__rv__));                          \
      }                                                       \
  } while(0)

/**************************************************************************//**
 * \brief Install filters to redirect traffic to a destination port
 *
 * \param    unit              [IN]    Unit number
 * \param    port              [IN]    Port to which the traffic needs
 *                                     to redirected
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 ******************************************************************************/
int example_fp_redirect(int unit, int dport)
{
  int rv = OPENNSL_E_NONE;
  opennsl_field_qset_t qset;
  opennsl_field_aset_t aset;
  int pri = OPENNSL_FIELD_GROUP_PRIO_ANY;
  opennsl_mac_t bpdu_mac_da = MAC_DA;
  opennsl_mac_t mac_mask = MAC_MASK;
  int dest_gport;
  int cos = NEWCOS_VAL;

  /** Create qualification set */
  OPENNSL_FIELD_QSET_INIT(qset);
  OPENNSL_FIELD_QSET_ADD(qset, opennslFieldQualifyDstMac);

  /** Create action set */
  OPENNSL_FIELD_ASET_INIT(aset);
  OPENNSL_FIELD_ASET_ADD(aset, opennslFieldActionStat);
  OPENNSL_FIELD_ASET_ADD(aset, opennslFieldActionRedirectPort);
  OPENNSL_FIELD_ASET_ADD(aset, opennslFieldActionPrioIntNew);

  /** initialize a group with the create qset */
  CALL_IF_ERROR_RETURN(opennsl_field_group_create_id(unit, qset, pri, grp));

  CALL_IF_ERROR_RETURN(opennsl_field_group_action_set(unit, grp, aset));

  /** add entries to qualify the packets with configured MAC address and then
   * count it, redirect it to a destination port */

  /** add an entry to the group */
  CALL_IF_ERROR_RETURN(opennsl_field_entry_create_id(unit, grp, eid));
  CALL_IF_ERROR_RETURN(opennsl_field_qualify_DstMac(unit, eid,
        bpdu_mac_da, mac_mask));

  CALL_IF_ERROR_RETURN(opennsl_field_stat_create_id(unit, grp, 1,
        &stats, stat_id));

  /** add actions associated with this entry */
  CALL_IF_ERROR_RETURN(opennsl_field_action_add(unit, eid,
        opennslFieldActionStat, stat_id, 0));
  OPENNSL_GPORT_LOCAL_SET(dest_gport, dport);
  CALL_IF_ERROR_RETURN(opennsl_field_action_add(unit, eid,
        opennslFieldActionRedirectPort, 0, dest_gport));
  CALL_IF_ERROR_RETURN(opennsl_field_action_add(unit, eid,
        opennslFieldActionPrioIntNew, cos, 0));

  rv = opennsl_field_group_install(unit, grp);
  if (OPENNSL_E_NONE != rv)
  {
    printf("Failed to install the group, Error %s\n", opennsl_errmsg(rv));
    CALL_IF_ERROR_RETURN(opennsl_field_group_destroy(unit, grp));
    return rv;
  }

  printf("Packet qualification criteria: \n");
  l2_print_mac(" ==> MAC DA -", bpdu_mac_da);
  printf("\n");
  printf("Configured system to count and redirect qualified traffic to "
      "port %d", dport);

  return rv;
}

/********************************************************************//**
 * \brief Main function for redirecting traffic based on destination 
 *        MAC address
 *
 * \param argc, argv         commands line arguments
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ***********************************************************************/
int main(int argc, char *argv[])
{
  int rv = OPENNSL_E_NONE;
  int choice;
  int unit = DEFAULT_UNIT;
  uint64 val;
  int port;

  if((argc != 1) || ((argc > 1) && (strcmp(argv[1], "--help") == 0))) {
    printf("%s\n\r", example_usage);
    return OPENNSL_E_PARAM;
  }

  /* Initialize the system */
  rv = opennsl_driver_init((opennsl_init_t *) NULL);

  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to initialize the system.\r\n");
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
    printf("\r\nFailed to add ports to default VLAN. Error: %s\r\n",
        opennsl_errmsg(rv));
  }

  while(1) {
    printf("\r\nUser menu: Select one of the following options\r\n");
    printf("1. Apply filter to redirect traffic\n");
    printf("2. Remove redirection filter\n");
    printf("3. Display the number of packets redirected\n");
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
        printf("Enter port number to which traffic needs to be redirected:\n");
        if(example_read_user_choice(&port) != OPENNSL_E_NONE)
        {
          printf("Invalid option entered. Please re-enter.\n");
          continue;
        }
        rv = example_fp_redirect(unit, port);
        if (rv != OPENNSL_E_NONE) {
          printf("Failed to configure the system for traffic redirection, "
              "Error %s\n", opennsl_errmsg(rv));
          return rv;
        }
        break;
      }

      case 2:
      {
        CALL_IF_ERROR_RETURN(opennsl_field_entry_destroy(unit, eid));
        CALL_IF_ERROR_RETURN(opennsl_field_group_destroy(unit, grp));
        printf("Removed the redirection filter\n");
        break;
      }

      case 3:
      {
        rv = opennsl_field_stat_get(unit, stat_id, stats, &val);
        if (rv != OPENNSL_E_NONE) {
          printf("Failed to get the statistics, "
              "Error %s\n", opennsl_errmsg(rv));
          return rv;
        }
        printf("Number of packets redirected: %lld (0x%0x)\n", val, val);
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
        return OPENNSL_E_NONE;
      }
      default:
      break;
    } /* End of switch */
  } /* End of while */

  return rv;
}
