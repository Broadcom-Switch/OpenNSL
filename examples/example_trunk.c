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
 * \file     example_trunk.c
 *
 * \brief    Example code for Trunk application
 *
 * \details  This example demonstrates a simple trunk API scenario.
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
#include <opennsl/vlan.h>
#include <opennsl/port.h>
#include <opennsl/switch.h>
#include <opennsl/trunk.h>
#include <examples/util.h>

#define DEFAULT_UNIT  0
#define DEFAULT_VLAN  1
#define MAX_DIGITS_IN_CHOICE 5
#define MAX_TRUNK_MEMBER 8

char example_usage[] =
"Syntax: example_trunk                                                 \n\r"
"                                                                      \n\r"
"Paramaters: None.                                                     \n\r"
"                                                                      \n\r"
"Example: The following command is used to demonstrate trunk API       \n\r"
"calls. The interactive user interface allows the user to get          \n\r"
"the trunk information, add, delete ports and destroy a trunk.         \n\r"
"         example_trunk                                                \n\r"
"                                                                      \n\r"
"Usage Guidelines: None.                                               \n\r";

/*****************************************************************//**
 * \brief Create a default trunk
 *
 * \param unit	[IN]	Unit number.
 * \param tid	[IN,OUT]	Pointer to caller-specified trunk ID if
 *        OPENNSL_TRUNK_FLAG_WITH_ID is set, else pointer to next available
 *        trunk ID.
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_trunk_create(int unit, opennsl_trunk_t *tid)
{
  opennsl_error_t rv;

  rv = opennsl_trunk_create(unit, 0, tid);
  return rv;
}

/*****************************************************************//**
 * \brief Set hash controls
 *
 * \param unit	[IN]	Unit number.
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_trunk_hash_controls_set(int unit)
{
  opennsl_error_t rv = OPENNSL_E_NONE;
  int hashControl = 0;

  /* Set the ECMP hashControl to include dstip also - for XGS3 only */
  OPENNSL_IF_ERROR_RETURN(opennsl_switch_control_get(unit,
        opennslSwitchHashControl, &hashControl));

  /* Set the L2 hash controls first. */
  hashControl |= (OPENNSL_HASH_CONTROL_TRUNK_NUC_DST
      | OPENNSL_HASH_CONTROL_TRUNK_NUC_SRC
      | OPENNSL_HASH_CONTROL_TRUNK_UC_SRCPORT);

  OPENNSL_IF_ERROR_RETURN(opennsl_switch_control_set(unit,
        opennslSwitchHashControl, hashControl));

  /* Set the L3 hash controls next. */
  /* L4 ports hashControl below is valid for ECMP as well as regular UC
   * trunk load balacing
   */
  hashControl |=  (OPENNSL_HASH_CONTROL_MULTIPATH_L4PORTS
      | OPENNSL_HASH_CONTROL_MULTIPATH_DIP);

  OPENNSL_IF_ERROR_RETURN(opennsl_switch_control_set(unit,
        opennslSwitchHashControl, hashControl));

  return rv;
}

/*****************************************************************//**
 * \brief Main function for Trunk application
 *
 * \param argc, argv         commands line arguments
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int main(int argc, char *argv[])
{
  opennsl_error_t   rv;
  opennsl_trunk_t tid;
  opennsl_gport_t gport;
  opennsl_port_t port;
  int unit = DEFAULT_UNIT;
  int member_max = MAX_TRUNK_MEMBER, member_count, i;
  opennsl_trunk_member_t member;
  opennsl_trunk_member_t member_arr[member_max];
  opennsl_trunk_info_t t_data;
  unsigned int warm_boot;
  int choice;
  int index = 0;
  int psc = 0;

  if(strcmp(argv[0], "gdb") == 0)
  {
    index = 1;
  }

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

  if(!warm_boot)
  {
   /* cold boot initialization commands */
    rv = example_port_default_config(unit);
    if (rv != OPENNSL_E_NONE)
    {
      printf("\r\nFailed to apply default config on ports, rc = %d (%s).\r\n",
             rv, opennsl_errmsg(rv));
    }

    /* Add ports to default vlan. */
    printf("Adding ports to default vlan.\r\n");
    rv = example_switch_default_vlan_config(unit);
    if(rv != OPENNSL_E_NONE)
    {
      printf("\r\nFailed to add default ports. rv: %s\r\n", opennsl_errmsg(rv));
      return rv;
    }

    printf("Setting Hash controls for Trunk.\r\n");
    rv = example_trunk_hash_controls_set(unit);
    if(rv != OPENNSL_E_NONE)
    {
      printf("\r\nFailed to hash control for Trunk. Error %s\r\n",
          opennsl_errmsg(rv));
    }
  }

  while (1) {
    printf("\r\nUser menu: Select one of the following options\r\n");
    printf("1. Create trunk\n");
    printf("2. Add port to trunk\n");
    printf("3. Delete port from trunk\n");
    printf("4. Get trunk info\n");
    printf("5. Delete trunk\n");
    printf("6. Save the configuration to scache\n");
    printf("7. Set port selection criteria (PSC)\n");
#ifdef INCLUDE_DIAG_SHELL
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
        /* Create default trunk */
        rv = example_trunk_create(unit, &tid);
        if (rv == OPENNSL_E_NONE) {
          printf("Trunk %d created successfully\n", tid);
        } else {
          printf("Failed to create trunk. Error %s\n",
                 opennsl_errmsg(rv));
          continue;
        }

        break;
      } /* End of case 1 */

      case 2:
      {
        /* Add port to trunk*/
        printf("\r\nEnter the port number.\r\n");
        if(example_read_user_choice(&port) != OPENNSL_E_NONE)
        {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
        }
        rv = opennsl_port_gport_get (unit, port, &gport);
        if (rv != OPENNSL_E_NONE)
        {
          return OPENNSL_E_FAIL;
        }

        opennsl_trunk_member_t_init(&member);
        member.gport = gport;

        printf("\r\nEnter the trunk id.\r\n");
        if(example_read_user_choice(&tid) != OPENNSL_E_NONE)
        {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
        }

        printf("member_add: Adding port %d to trunk-id %d\n", port, tid);
        rv = opennsl_trunk_member_add(unit, tid, &member);
        if ((rv == OPENNSL_E_NONE)) {
          printf("Port %d added successfully to trunk %d\n", port, tid);
        } else {
          printf("Failed to add port. Error %s\n",
                 opennsl_errmsg(rv));
          continue;
        }

        break;
      } /* End of case 2 */

      case 3:
      {
        /* Delete port from trunk*/
        printf("\r\nEnter the port number.\r\n");
        if(example_read_user_choice(&port) != OPENNSL_E_NONE)
        {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
        }
        rv = opennsl_port_gport_get (unit, port, &gport);
        if (rv != OPENNSL_E_NONE)
        {
          return OPENNSL_E_FAIL;
        }

        opennsl_trunk_member_t_init(&member);
        member.gport = gport;

        printf("\r\nEnter the trunk id.\r\n");
        if(example_read_user_choice(&tid) != OPENNSL_E_NONE)
        {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
        }

        printf("member_delete: Deleting port %d from trunk-id %d\n", port, tid);
        rv = opennsl_trunk_member_delete(unit, tid, &member);
        if ((rv == OPENNSL_E_NONE)) {
          printf("Port %d deleted successfully from trunk %d\n", port, tid);
        } else {
          printf("Failed to delete port. Error %s\n",
                 opennsl_errmsg(rv));
          continue;
        }

        break;
      } /* End of case 3 */

      case 4:
      {
        /* Get trunk info*/
        printf("\r\nEnter the trunk id.\r\n");
        if(example_read_user_choice(&tid) != OPENNSL_E_NONE)
        {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
        }

        for (i = 0; i < member_max; i++)
        {
          opennsl_trunk_member_t_init(&member_arr[i]);
        }
        opennsl_trunk_info_t_init(&t_data);

        rv = opennsl_trunk_get(unit, tid, &t_data, member_max,
            member_arr, &member_count);
        if ((rv != OPENNSL_E_NONE)) {
          printf("Failed to get trunk info. Error %s\n",
                 opennsl_errmsg(rv));
          continue;
        }
        printf("trunk %d has %d members, psc %d\n", tid ,member_count, t_data.psc);
        for( i = 0; i < member_count; i++)
        {
          opennsl_port_local_get(unit, member_arr[i].gport, &port);
          printf("port %d\n",port);
        }

        break;
      } /* End of case 4 */

      case 5:
      {
        /* Delete a trunk */
        printf("\r\nEnter the trunk id.\r\n");
        if(example_read_user_choice(&tid) != OPENNSL_E_NONE)
        {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
        }

        rv = opennsl_trunk_destroy(unit, tid);
        if ((rv == OPENNSL_E_NONE)) {
          printf("trunk %d successfully deleted\n", tid);
        } else {
          printf("Failed to delete trunk. Error %s\n",
                 opennsl_errmsg(rv));
          continue;
        }

        break;
      } /* End of case 5 */

      case 6:
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
      } /* End of case 6 */

      case 7:
      {
        printf("\r\nEnter the trunk id.\r\n");
        if(example_read_user_choice(&tid) != OPENNSL_E_NONE)
        {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
        }

        printf("\r\nEnter the PSC.\r\n");
        if(example_read_user_choice(&psc) != OPENNSL_E_NONE)
        {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
        }

        rv = opennsl_trunk_psc_set(unit, tid, psc);
        if(rv != OPENNSL_E_NONE) {
          printf("Failed to set the PSC. Error %s\n", opennsl_errmsg(rv));
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
  } /* End of while */

  return OPENNSL_E_NONE;
}
