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
 * \file         example_link_monitor.c
 *
 * \brief        OpenNSL example application for link monitoring
 *
 * \details      Link monitoring can be used to detect uplink failures and
 *               to disable the associated downlink ports such that the
 *               traffic can failover to secondary link.
 *
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sal/driver.h>
#include <opennsl/error.h>
#include <opennsl/vlan.h>
#include <opennsl/link.h>
#include <examples/util.h>

char example_usage[] =
"Syntax: example_link_monitor uplink_port downlink_ports               \n\r"
"                                                                      \n\r"
"Paramaters:                                                           \n\r"
"            uplink_port    - Uplink port number to be monitored.      \n\r"
"            downlink_ports - List of ports that follow the link state \n\r"
"                             of uplink port.                          \n\r"
"                             Maximum of 10 ports supported.           \n\r"
"                                                                      \n\r"
"Example: The following command is used to configure ports 2 and 3     \n\r"
"         to follow the link state of port 1.                          \n\r"
"         example_link_monitor 1 2 3                                   \n\r"
"                                                                      \n\r"
"Usage Guidelines: This program assumes that software linkscan         \n\r"
"                  is enabled on the system.                           \n\r";

#define DEFAULT_VLAN             1
#define LINKMON_MAX_DOWN_PORTS  10
#define DEFAULT_UNIT             0
#define TRUE                     1
#define FALSE                    0
#define LINK_MON_ON              1
#define LINK_MON_OFF             2
#define MAX_DIGITS_IN_CHOICE     5

int uport = -1;

/* List of downlink ports that follow the link state of uplink ports */
int dport[LINKMON_MAX_DOWN_PORTS];
int dport_cnt;

/* debug prints */
int verbose = 2;

static void example_link_change_callback(int unit, opennsl_port_t port,
    opennsl_port_info_t *info);
static int example_link_monitor(int unit, int mode);

/*****************************************************************//**
 * \brief Main function for link monitoring application
 *
 * \param argc, argv         commands line arguments
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int main(int argc, char *argv[])
{
  int rv = 0;
  int i;
  int choice;

  /* Throw command usage here. This program excepts at least one
  down port from the user. */
  if((argc < 3) ||
      ((argc > 1) && (strcmp(argv[1], "--help") == 0))) {
    printf("%s\n\r", example_usage);
    return OPENNSL_E_PARAM;
  }

  if(argc > (2 + LINKMON_MAX_DOWN_PORTS)) {
    printf("Invalid number of arguments passed. Please see example help.\n\r");
    return OPENNSL_E_PARAM;
  }

  /* Extract input parameters */
  uport = atoi(argv[1]);
  for(i = 2, dport_cnt = 0; i < argc; i++) {
    dport[dport_cnt++] = atoi(argv[i]);
  }

  if(verbose > 1) {
    printf("Uplink Port     : %d\n\r", uport);
    printf("Downlink Ports  : ");
    for(i = 0; i < dport_cnt; i++) {
      printf("%2d ", dport[i]);
    }
    printf("\n\r");
  }

  /* Initialize the system */
  rv = opennsl_driver_init((opennsl_init_t *) NULL);
  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to initialize the system. Error %s \n\r",
           opennsl_errmsg(rv));
    return rv;
  }

  /* Setup link monitoring */
  rv = example_link_monitor(DEFAULT_UNIT, LINK_MON_ON);
  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to set link monitor mode. Error: %s.\n\r",
        opennsl_errmsg(rv));
  }

  printf("\r\nLink monitoring is enabled successfully.\n\r");

  while(1) {
    printf("\r\nUser menu: Select one of the following options\r\n");
    printf("1. Enable the link monitoring mode.\r\n");
    printf("2. Disable the link monitoring mode.\r\n");
#ifndef CDP_EXCLUDE
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
        rv = example_link_monitor(DEFAULT_UNIT, LINK_MON_ON);
        if(rv != OPENNSL_E_NONE) {
          printf("\r\nFailed to enable link monitor mode. Error: %s.\n\r",
              opennsl_errmsg(rv));
        }
        break;
      }
      case 2:
      {
        rv = example_link_monitor(DEFAULT_UNIT, LINK_MON_OFF);
        if(rv != OPENNSL_E_NONE) {
          printf("\r\nFailed to disable link monitor mode. Error: %s.\n\r",
              opennsl_errmsg(rv));
        }
        break;
      }

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
        return 0;
      }
      default:
        break;
    } /* End of switch */
  } /* End of while */

  return rv;
}

/**************************************************************************//**
 * \brief To add a given MAC and VID to the L2 forwarding database.
 *
 *
 * \param    unit [IN]    Unit number.
 * \param    mode [IN]    if TRUE, then register with linkscan. Otherwise,
                          de-register.
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
int example_link_monitor(int unit, int mode) {

  if((mode != LINK_MON_ON) && (mode != LINK_MON_OFF)) {
    return OPENNSL_E_PARAM;
  }

  if (mode == LINK_MON_ON) {

    /** register a function to be called whenever link change *
     * happens on a port. */
    OPENNSL_IF_ERROR_RETURN(opennsl_linkscan_register(unit,
          example_link_change_callback));

  } else {

    /** unregister the function */
    OPENNSL_IF_ERROR_RETURN(opennsl_linkscan_unregister(unit,
          example_link_change_callback));

  }

  printf("Link Monitor mode is %s.\n", (mode == LINK_MON_ON) ? "enabled" : "disabled");
  return OPENNSL_E_NONE;
}

/**************************************************************************//**
 * \brief To handle link change events
 *
 *
 * \param    unit [IN]    Unit number.
 * \param    port [IN]    Port on which link status change event happened
 * \param    info [IN]    Structure that has link change details
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
static void example_link_change_callback(int unit, opennsl_port_t port,
                                         opennsl_port_info_t *info)
{
  int mode = FALSE;
  int i;

  if(verbose > 2) {
    printf("Link on port %2d changed to %4s\n", port,
        info->linkstatus ? "UP" : "DOWN");
  }

  /* Ignore if the link change is not on the uplink port */
  if(port != uport) {
    return;
  }

  if(info->linkstatus) {
    mode = TRUE;
  }

  printf("Uplink port %2d link state transitioned to %4s.\n\r", port,
      (info->linkstatus) ? "UP" : "DOWN");

  /* Update the link status on the downlink ports as per the latest
   * uplink port link state.
   */
  for(i = 0; i < dport_cnt; i++) {

    if(opennsl_port_enable_set(unit, dport[i], mode) != OPENNSL_E_NONE) {
      printf("Failed to %s port %2d.\n", (mode == TRUE)? "enable" : "disable",
          dport[i]);
    }

    printf("%s port %2d.\n", (mode == TRUE) ? "Enabled" : "Disabled", dport[i]);
  }
}

