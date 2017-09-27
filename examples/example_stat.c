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
 * \file         example_stat.c
 *
 * \brief        OpenNSL example program for showing statistics
 *
 * \details      OpenNSL example program for displaying and clearing statistics
 *               of a given interface.
 *               interface.
 *
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sal/driver.h>
#include <opennsl/error.h>
#include <opennsl/stat.h>
#include <opennsl/vlan.h>
#include <opennsl/stat.h>
#include <examples/util.h>

#define DEFAULT_UNIT 0
#define DEFAULT_VLAN 1
#define MAX_COUNTERS 30
#define MAX_DIGITS_IN_CHOICE 5

char example_usage[] =
"Syntax: example_stat                                                  \n\r"
"                                                                      \n\r"
"Paramaters: None                                                      \n\r"
"                                                                      \n\r"
"Example: The following command is used to see the statistics of a port\n\r"
"         example_stat                                                 \n\r"
"                                                                      \n\r"
"Usage Guidelines: This program request the user to enter the port     \n\r"
"                  number interactively                                \n\r";

/*****************************************************************//**
 * \brief Main function for statistics sample application
 *
 * \param argc, argv         commands line arguments
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
/* Main function for Statistics application */
int main(int argc, char *argv[])
{
  opennsl_error_t   rc;
  int choice;
  int unit = DEFAULT_UNIT;
  int i;
  int nstat;
  opennsl_port_t port;
  opennsl_stat_val_t stat_arr[] = {
    opennsl_spl_snmpIfInUcastPkts,
    opennsl_spl_snmpIfInNUcastPkts,
    opennsl_spl_snmpIfInDiscards,
    opennsl_spl_snmpIfInErrors,
    opennsl_spl_snmpIfInMulticastPkts,
    opennsl_spl_snmpIfInBroadcastPkts,
    snmpOpenNSLReceivedPkts64Octets,
    snmpOpenNSLReceivedPkts65to127Octets,
    snmpOpenNSLReceivedPkts128to255Octets,
    snmpOpenNSLReceivedPkts256to511Octets,
    snmpOpenNSLReceivedPkts512to1023Octets,
    snmpOpenNSLReceivedPkts1024to1518Octets,
    snmpOpenNSLReceivedPkts1519to2047Octets,
    snmpOpenNSLReceivedPkts2048to4095Octets,
    snmpOpenNSLReceivedPkts4095to9216Octets,
    opennsl_spl_snmpIfOutUcastPkts,
    opennsl_spl_snmpIfOutNUcastPkts,
    opennsl_spl_snmpIfOutDiscards,
    opennsl_spl_snmpIfOutErrors,
    opennsl_spl_snmpIfOutMulticastPkts,
    opennsl_spl_snmpIfOutBroadcastPkts,
    snmpOpenNSLTransmittedPkts64Octets,
    snmpOpenNSLTransmittedPkts65to127Octets,
    snmpOpenNSLTransmittedPkts128to255Octets,
    snmpOpenNSLTransmittedPkts256to511Octets,
    snmpOpenNSLTransmittedPkts512to1023Octets,
    snmpOpenNSLTransmittedPkts1024to1518Octets,
    snmpOpenNSLTransmittedPkts1519to2047Octets,
    snmpOpenNSLTransmittedPkts2048to4095Octets,
    snmpOpenNSLTransmittedPkts4095to9216Octets,};
  uint64 val[MAX_COUNTERS] = {0};

  nstat = (sizeof(stat_arr) / sizeof(opennsl_stat_val_t));

  if((argc != 1) || ((argc > 1) && (strcmp(argv[1], "--help") == 0))) {
    printf("%s\n\r", example_usage);
    return OPENNSL_E_PARAM;
  }

  /* Initialize the system. */
  printf("Initializing the system.\r\n");
  rc = opennsl_driver_init((opennsl_init_t *) NULL);

  if(rc != OPENNSL_E_NONE) {
    printf("\r\nFailed to initialize the system, rc = %d (%s).\r\n",
           rc, opennsl_errmsg(rc));
    return 0;
  }

  /* cold boot initialization commands */
  rc = example_port_default_config(unit);
  if (rc != OPENNSL_E_NONE) {
    printf("\r\nFailed to apply default config on ports, rc = %d (%s).\r\n",
           rc, opennsl_errmsg(rc));
  }

  /* Add ports to default vlan. */
  printf("Adding ports to default vlan.\r\n");
  rc = example_switch_default_vlan_config(unit);
  if(rc != OPENNSL_E_NONE) {
    printf("\r\nFailed to add default ports, rc = %d (%s).\r\n",
           rc, opennsl_errmsg(rc));
  }

  /* Initialize stat module. */
  printf("Initializing the stat module.\r\n");
  rc = opennsl_stat_init(unit);

  if(rc != OPENNSL_E_NONE) {
    printf("\r\nFailed to initialise stat module, rc = %d (%s).\r\n",
           rc, opennsl_errmsg(rc));
    return 0;
  }


  while (1) {
    printf("\nUser Menu: Select one of the following options\n");
    printf("1. Display statistics of a port.\n");
    printf("2. Clear statistics of a port.\n");
#ifdef INCLUDE_DIAG_SHELL
    printf("9. Launch diagnostic shell\n");
#endif
    printf("0. Quit the application.\n");

    if(example_read_user_choice(&choice) != OPENNSL_E_NONE)
    {
        printf("Invalid option entered. Please re-enter.\n");
        continue;
    }
    switch(choice) {

      case 1:
      {
        printf("\r\nEnter the port number.\r\n");
        if(example_read_user_choice(&port) != OPENNSL_E_NONE)
        {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
        }
        rc = (opennsl_stat_sync(unit));
        if(rc != OPENNSL_E_NONE) {
          printf("\r\nFailed to sync the state of port, rc = %d (%s).\r\n",
                 rc, opennsl_errmsg(rc));
          break;
        }

        rc = opennsl_stat_multi_get(unit, port, nstat, stat_arr, val);
 
        if (rc == OPENNSL_E_UNAVAIL) {
           for (i=0; i < nstat; i++) {
              rc = opennsl_stat_get(unit, port, stat_arr[i], &val[i]);
           }          
        }

        if(rc != OPENNSL_E_NONE) {
          printf("\r\nFailed to get the port stats, rc = %d (%s).\r\n",
                 rc, opennsl_errmsg(rc));
          break;
        }

        printf("Count of Ingress Unicast packets    .......   %llu\n", val[0]);
        printf("Count of Ingress Non-unicast packets.......   %llu\n", val[1]);
        printf("Count of Ingress Discard packets    .......   %llu\n", val[2]);
        printf("Count of Ingress Error packets      .......   %llu\n", val[3]);
        printf("Count of Ingress Multicast packets  .......   %llu\n", val[4]);
        printf("Count of Ingress Broadcast packets  .......   %llu\n", val[5]);
        printf("Count of Received 64 octets         .......   %llu\n", val[6]);
        printf("Count of Received 65-127 octets     .......   %llu\n", val[7]);
        printf("Count of Received 128-255 octets    .......   %llu\n", val[8]);
        printf("Count of Received 256-511 octets    .......   %llu\n", val[9]);
        printf("Count of Received 512-1023 octets   .......   %llu\n", val[10]);
        printf("Count of Received 1024-1518 octets  .......   %llu\n", val[11]);
        printf("Count of Received 1519-2047 octets  .......   %llu\n", val[12]);
        printf("Count of Received 2048-4095 octets  .......   %llu\n", val[13]);
        printf("Count of Received 4096-9216 octets  .......   %llu\n", val[14]);
        printf("Count of Egress Unicast packets     .......   %llu\n", val[15]);
        printf("Count of Egress Non-unicast packets .......   %llu\n", val[16]);
        printf("Count of Egress Discards packets    .......   %llu\n", val[17]);
        printf("Count of Egress Error packets       .......   %llu\n", val[18]);
        printf("Count of Egress Multicast packets   .......   %llu\n", val[19]);
        printf("Count of Egress Broadcast packets   .......   %llu\n", val[20]);
        printf("Count of Transmitted 64 octets      .......   %llu\n", val[21]);
        printf("Count of Transmitted 65-127 octets  .......   %llu\n", val[22]);
        printf("Count of Transmitted 128-255 octets .......   %llu\n", val[23]);
        printf("Count of Transmitted 256-511 octets .......   %llu\n", val[24]);
        printf("Count of Transmitted 512-1023 octet .......   %llu\n", val[25]);
        printf("Count of Transmitted 1024-1518 octets .....   %llu\n", val[26]);
        printf("Count of Transmitted 1519-2047 octets .....   %llu\n", val[27]);
        printf("Count of Transmitted 2048-4095 octets .....   %llu\n", val[28]);
        break;
      } /* End of case 1 */

      case 2:
      {
        printf("\r\nEnter the port number.\r\n");
        if(example_read_user_choice(&port) != OPENNSL_E_NONE)
        {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
        }
        rc = opennsl_stat_clear(unit, port);
        if(rc != OPENNSL_E_NONE) {
          printf("\r\nFailed to clear the port stats, rc = %d (%s).\r\n",
                 rc, opennsl_errmsg(rc));
          break;
        }

        printf("\r\nPort %d stats cleared\r\n", port);
        break;
      } /* End of case 2 */

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
        rc = opennsl_driver_exit();
        return rc;
      }

      default :
        break;
    } /* End of switch */
  } /* End of while */

  return 0;
}

