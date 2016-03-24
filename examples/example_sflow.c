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
 * \file         example_sflow.c
 *
 * \brief        OPENNSL example program to demonstrate sFlow
 *
 * \details      sFlow is a statistical sampling technology for monitoring
 * traffic in data networks. On average, one packet in N is sampled for 
 * analysis. This example demonstrates configuration of sFlow on the 
 * ingress ports and displays the part of the sampled packets
 * on the console.
 *
 * This application also supports Warmboot feature. Warmboot is
 * the process of restarting the device driver software while
 * the hardware is running without interrupting the dataplane.
 *
 * Setup the following envinonment variable before running the application.
 * For Cold boot mode, use "export OPENNSL_BOOT_FLAGS = 0x000000".
 * For Warm boot mode, use "export OPENNSL_BOOT_FLAGS = 0x200000".
 *
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sal/driver.h>
#include <opennsl/error.h>
#include <opennsl/switch.h>
#include <opennsl/rx.h>
#include <examples/util.h>

char example_usage[] =
"Syntax: example_sflow                                                  \n\r"
"                                                                       \n\r"
"Paramaters: None                                                       \n\r"
"                                                                       \n\r"
"Example: The following command is used to demonstrate sFlow            \n\r"
"         example_sflow                                                 \n\r"
"                                                                       \n\r"
"Usage Guidelines: This program allows the user to configure sFlow      \n\r"
"parameters. It also has a provision to display the sFlow sampled       \n\r"
"packet on the console.                                                 \n\r"
"                                                                       \n\r"
"Note: Configure sFlow in such a way that less number of packets are    \n\r"
"sampled, as it prints the packet on the console which is time consuming\n\r";


int verbose = 4;

/**************************************************************************//**
 * \brief Callback function to handle CPU bound packets
 *
 *
 * \param    unit   [IN]  Unit number.
 * \param    pkt    [IN]  sampled packet description structure
 * \param    cookie [IN]  cookie passed to this function
 *
 * \return   OPENNSL_RX_HANDLED  OpenNSL API return code
 *****************************************************************************/
opennsl_rx_t example_sflow_handle_rx_event(int unit, opennsl_pkt_t *pkt,
    void *cookie)
{
  static int pkt_total_count   = 0;
  static int pkt_sflow_count = 0;
  int i;

  /* Increment the receive packet count */
  pkt_total_count++;

  if(verbose > 3)
  {
    /* Print first 32 bytes of the received packet */
    printf("==========================================\n\r");
    printf("Packet %d of length %d is received:\n\r",
        pkt_total_count, pkt->pkt_len);

    for (i = 0; i < 32; i++)
    {
      printf("%02x ", pkt->pkt_data->data[i]);
      if(((i + 1) % 16) == 0)
      {
        printf("\n\r");
      }
    }
    printf("\n\r");

  }

  printf("Received pkt on rx_port %d, src_port %d "
      "flags 0x%x, vlan %d cos %d\n",
      pkt->rx_port, pkt->src_port, pkt->flags,
      pkt->vlan, pkt->cos);

  if(pkt->rx_reason & opennslRxReasonSampleSource)
  {
    /* we are here as the packets received is sFlow sampled packet */
    pkt_sflow_count++;
    printf("The received packet is sFlow sampled packet. "
        "Sample packet count: %d\n\r", pkt_sflow_count);
  }

  if(verbose > 3)
  {
    printf("==========================================\n\r");
  }
  printf("\n\r");

  return OPENNSL_RX_HANDLED;
}

/*****************************************************************//**
 * \brief Main function for routing sample application
 *
 * \param argc, argv         commands line arguments
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int main(int argc, char *argv[])
{
  int rv = 0;
  int unit = 0;
  int choice;
  unsigned int warm_boot;
  int index = 0;
  int port;
  int irate, erate;

  if(strcmp(argv[0], "gdb") == 0)
  {
    index = 1;
  }
  if((argc != (index + 1)) || ((argc > (index + 1))
        && (strcmp(argv[index + 1], "--help") == 0))) {
    printf("%s\n\r", example_usage);
    return OPENNSL_E_PARAM;
  }

  /* Initialize the system */
  rv = opennsl_driver_init((opennsl_init_t *) NULL);

  if(rv != 0) {
    printf("\r\nFailed to initialize the system.\r\n");
    return rv;
  }

  warm_boot = opennsl_driver_boot_flags_get() & OPENNSL_BOOT_F_WARM_BOOT;

  if(!warm_boot)
  {
    /* Add ports to default vlan. */
    printf("Adding ports to default vlan.\r\n");
    rv = example_switch_default_vlan_config(unit);
    if(rv != OPENNSL_E_NONE) {
      printf("\r\nFailed to add default ports. rv: %s\r\n", opennsl_errmsg(rv));
      return rv;
    }

  }

  rv = opennsl_rx_register(
      unit,
      "sflow_rx_callback_function",
      example_sflow_handle_rx_event, /*(opennsl_rx_cb_f) */
      100,
      NULL,
      OPENNSL_RCO_F_ALL_COS /*| OPENNSL_RCO_F_INTR*/);

  if(rv != OPENNSL_E_NONE) {
    printf("Failed to register sFlow Rx callback function. Error %s\n",
        opennsl_errmsg(rv));
    return rv;
  }
  printf("Registered callback function to received sFlow sampled packets\n");

  while(1) {
    printf("\r\nUser menu: Select one of the following options\r\n");
    printf("1. Enable sFlow and configure sFlow sampling rate\n");
    printf("2. Disable sFlow\n");
    printf("3. Display sFlow configuration\n");
    printf("4. Save the configuration to scache\n");
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
          printf("Enter port number\n");
          if(example_read_user_choice(&port) != OPENNSL_E_NONE)
          {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
          }

          printf("Enter ingress sampling rate\n");
          if(example_read_user_choice(&irate) != OPENNSL_E_NONE)
          {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
          }

          rv = opennsl_port_sample_rate_set(unit, port, irate, 0);
          if(rv != OPENNSL_E_NONE) {
            printf("Failed to configure sFlow. Error %s\n", opennsl_errmsg(rv));
            return rv;
          }
          printf("Enabled sFlow on port %d with sample rate of %d\n",
              port, irate);

          break;
        }

      case 2:
        {
          printf("Enter port number\n");
          if(example_read_user_choice(&port) != OPENNSL_E_NONE)
          {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
          }

          rv = opennsl_port_sample_rate_set(unit, port, 0, 0);
          if(rv != OPENNSL_E_NONE) {
            printf("Failed to disabled sFlow. Error %s\n", opennsl_errmsg(rv));
            return rv;
          }
          printf("Disabled sFlow on port %d successfully\n", port);

          break;
        }

      case 3:
        {
          printf("Enter port number\n");
          if(example_read_user_choice(&port) != OPENNSL_E_NONE)
          {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
          }

          rv = opennsl_port_sample_rate_get(unit, port, &irate, &erate);
          if(rv != OPENNSL_E_NONE) {
            printf("Failed to get sFlow configuration. Error %s\n",
                opennsl_errmsg(rv));
            return rv;
          }
          printf("sFlow configuration parameters on port: %d\n", port);
          printf("  Ingress sampling rate: %d Egress sampling rate: %d\n",
              irate, erate);

          break;
        }

      case 4:
        {
          /* Sync the current configuration */
          rv = opennsl_switch_control_set(unit, opennslSwitchControlSync, 1);
          if(rv != OPENNSL_E_NONE) {
            printf("Failed to synchronize the configuration to scache. "
                "Error %s\n", opennsl_errmsg(rv));
            return rv;
          }
          printf("Warmboot configuration is saved successfully.\n");
          break;
        } /* End of case 1 */

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

  return rv;
}
