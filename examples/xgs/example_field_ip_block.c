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
 * \file         example_field_ip_block.c
 *
 * \brief        OPENNSL example program to demonstrate field processor
 *
 * \details      This example demonstrates blocking of traffic from
 *               hosts with IP addresses 192.168.199.36 to 192.168.199.47
 *               with the exception of 192.168.199.40.
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
"Syntax: example_field_ip_block                                         \n\r"
"                                                                       \n\r"
"Paramaters: None.                                                      \n\r"
"                                                                       \n\r"
"Example: The following command is used to block traffic from hosts with\n\r"
"         IP addresses 192.168.199.36 to 192.168.199.47 with the        \n\r"
"         exception of 192.168.199.40. The traffic should be of VLAN 1. \n\r"
"         example_field_ip_block                                        \n\r"
"                                                                       \n\r"
"Usage Guidelines: None.                                                \n\r";

#define DEFAULT_UNIT  0
#define DEFAULT_VLAN  1
#define MAX_DIGITS_IN_CHOICE 5

#define ETHERTYPE           0x0800
#define ETHERMASK           0xffff
#define IPADDR_36           0xC0A8C724 /* 192.168.199.36 */
#define IPADDR_39           0xC0A8C727 /* 192.168.199.39 */
#define IPMASK_BLOCK_36_39  0xFFFFFFFC /* Mask: 192.168.199.36-39 */
#define IPADDR_40           0xC0A8C728 /* 192.168.199.40 */
#define IPMASK_BLOCK_40_47  0xFFFFFFF8 /* Mask: 192.168.199.40-47 */
#define IPMASK_HOST_UNBLOCK 0xFFFFFFFF /* Unblock host mask */
#define IPADDR_47           0xC0A8C72F /* 192.168.199.47 */

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

/* debug prints */
int verbose = 3;

/**************************************************************************//**
 * \brief Install filters to block traffic
 *
 * \param    unit              [IN]    Unit number
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 ******************************************************************************/
int example_fp_ip_block(int unit) {
  opennsl_field_qset_t qset;
  opennsl_field_group_t group;
  opennsl_field_entry_t entry;

  OPENNSL_FIELD_QSET_INIT( qset );

  /** Create qualification set */
  OPENNSL_FIELD_QSET_ADD(qset, opennslFieldQualifyEtherType);
  OPENNSL_FIELD_QSET_ADD(qset, opennslFieldQualifySrcIp);

  /** initialize a group with the create qset */
  OPENNSL_IF_ERROR_RETURN(opennsl_field_group_create(unit, qset,
        OPENNSL_FIELD_GROUP_PRIO_ANY, &group));


  /** add entries to not drop traffic from IP: 192.168.199.40 */
  {
    /** add an entry to the group */
    OPENNSL_IF_ERROR_RETURN(opennsl_field_entry_create(unit, group, &entry));

    opennsl_field_qualify_EtherType(unit, entry, ETHERTYPE, ETHERMASK);
    opennsl_field_qualify_SrcIp(unit, entry, IPADDR_40, IPMASK_HOST_UNBLOCK);
    opennsl_field_entry_install(unit, entry);

    /** add action associate with this entry */
    OPENNSL_IF_ERROR_RETURN(opennsl_field_action_add(unit, entry,
          opennslFieldActionDropCancel, 0, 0));

    OPENNSL_IF_ERROR_RETURN(opennsl_field_entry_install(unit, entry));

    if(verbose >= 2) {
      printf("Updated Field Processor to unblock host");
      print_ip_addr("", IPADDR_40);
      printf("\n");
    }

  }

  /** add entries to drop traffic from IP address range: 192.168.199.36-39 */
  {
    /** add an entry to the group */
    OPENNSL_IF_ERROR_RETURN(opennsl_field_entry_create(unit, group, &entry));

    opennsl_field_qualify_EtherType(unit, entry, ETHERTYPE, ETHERMASK);
    opennsl_field_qualify_SrcIp(unit, entry, IPADDR_36, IPMASK_BLOCK_36_39);
    opennsl_field_entry_install(unit, entry);

    /** add drop action associate with this entry */
    OPENNSL_IF_ERROR_RETURN(opennsl_field_action_add(unit, entry,
          opennslFieldActionDrop, 0, 0));

    OPENNSL_IF_ERROR_RETURN(opennsl_field_entry_install(unit, entry));

    if(verbose >= 2) {
      printf("Updated Field Processor to block hosts with IP addresses");
      print_ip_addr(" from", IPADDR_36);
      print_ip_addr(" to", IPADDR_39);
      printf("\n");
    }
  }

  /** add entries to drop traffic from IP address range: 192.168.199.40-47 */
  {
    /** add an entry to the group */
    OPENNSL_IF_ERROR_RETURN(opennsl_field_entry_create(unit, group, &entry));

    opennsl_field_qualify_EtherType(unit, entry, ETHERTYPE, ETHERMASK);
    opennsl_field_qualify_SrcIp(unit, entry, IPADDR_40, IPMASK_BLOCK_40_47);
    opennsl_field_entry_install(unit, entry);

    /** add drop action associate with this entry */
    OPENNSL_IF_ERROR_RETURN(opennsl_field_action_add(unit, entry,
          opennslFieldActionDrop, 0, 0));

    OPENNSL_IF_ERROR_RETURN(opennsl_field_entry_install(unit, entry));

    if(verbose >= 2) {
      printf("Updated Field Processor to block hosts with IP addresses");
      print_ip_addr(" from", IPADDR_40);
      print_ip_addr(" to", IPADDR_47);
      printf("\n");
    }

  }

  return OPENNSL_E_NONE;
}

/********************************************************************//**
 * \brief Main function for blocking traffic based on source IP addresses
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

  /* cold boot initialization commands */
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

  rv = example_fp_ip_block(unit);

  while(1) {
    printf("\r\nUser menu: Select one of the following options\r\n");
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
