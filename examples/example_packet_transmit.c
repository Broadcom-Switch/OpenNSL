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
 * \file     example_packet_transmit.c
 *
 * \brief    Example code for packet transmission
 *
 * \details  This example demonstrates the transmission of a packet
 *           through a specified port.
 *
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sal/driver.h>
#include <sal/version.h>
#include <opennsl/error.h>
#include <opennsl/vlan.h>
#include <opennsl/port.h>
#include <opennsl/switch.h>
#include <opennsl/pkt.h>
#include <opennsl/tx.h>
#include <examples/util.h>

#define DEFAULT_UNIT  0
#define DEFAULT_VLAN  1
#define MAX_DIGITS_IN_CHOICE 5

char example_usage[] =
"Syntax: example_packet_transmit                                       \n\r"
"                                                                      \n\r"
"Paramaters: None.                                                     \n\r"
"                                                                      \n\r"
"Example: The following command is used to demonstrate transmit and    \n\r"
"         packet API's.                                                \n\r"
"         example_packet_transmit                                      \n\r"
"                                                                      \n\r"
"Usage Guidelines: None.                                               \n\r";

/*****************************************************************//**
 * \brief Send a packet on the specified port
 *
 * \param unit	[IN]	Unit number.
 * \param port	[IN]	Port number.
 * \param data	[IN]	Pointer to packet data.
 * \param len 	[IN]	Size of the packet data.
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_pkt_send(int unit, int port, char *data, int len)
{
  opennsl_pkt_t *pkt;
  int rv;

  rv = opennsl_pkt_alloc(unit, len, 0, &pkt);

  if (OPENNSL_SUCCESS(rv))
  {
    rv = opennsl_pkt_memcpy(pkt, 0, data, len);
    if (!OPENNSL_SUCCESS(rv))
    {
      opennsl_pkt_free(unit, pkt);
      return rv;
    }

    OPENNSL_PBMP_PORT_SET(pkt->tx_pbmp, port);

    rv = opennsl_tx(unit, pkt, NULL);
    if (!OPENNSL_SUCCESS(rv))
    {
      opennsl_pkt_free(unit, pkt);
      return rv;
    }
  }
  opennsl_pkt_free(unit, pkt);
  return rv;
}


/*****************************************************************//**
 * \brief Form a packet and send multiple packets from the specified port
 *
 * \param unit	[IN]	Unit number.
 * \param port	[IN]	Port number.
 * \param count	[IN]	Number of packets to be transmitted.
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
void example_multi_pkt_send(int unit, int port, int count)
{
  int i;
  int rv;
  char data[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x82, 0x2f,
                 0x2e, 0x42, 0x46, 0x74, 0x08, 0x06, 0x00, 0x01,
                 0x08, 0x00, 0x06, 0x04, 0x00, 0x01, 0x82, 0x2f,
                 0x2e, 0x42, 0x46, 0x74, 0x0a, 0x00, 0x00, 0x01,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00,
                 0x00, 0x02, 0x00, 0x00, 0x00, 0x00 };

  for (i = 0; i < count; i++)
  {
    rv = example_pkt_send(unit, port, data, (int) sizeof(data));

    if (!OPENNSL_SUCCESS(rv))
    {
      printf("Error Sending Packet: %d.  Error: %s\n", i + 1, opennsl_errmsg(rv));
    }
    else
    {
      printf("Transmitted Packet %d of size %zu\n", i + 1, sizeof(data));
    }
  }
}

/*****************************************************************//**
 * \brief Main function for packet transmission
 *
 * \param argc, argv         commands line arguments
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int main(int argc, char *argv[])
{
  opennsl_error_t   rv;
  int count;
  opennsl_port_t port;
  int unit = DEFAULT_UNIT;
  int choice;
  int index = 0;

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

  /* Add ports to default vlan. */
  printf("Adding ports to default vlan.\r\n");
  rv = example_switch_default_vlan_config(unit);
  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to add default ports. rv: %s\r\n", opennsl_errmsg(rv));
    return rv;
  }

  while (1) {
    printf("\r\nUser menu: Select one of the following options\r\n");
    printf("1. Transmit a packet\n");
    printf("2. Display OpenNSL version\n");
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
        printf("\r\nEnter the port on which packet needs to be transmitted.\r\n");
        if(example_read_user_choice(&port) != OPENNSL_E_NONE)
        {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
        }

        printf("\r\nEnter number of packets to be sent.\r\n");
        if(example_read_user_choice(&count) != OPENNSL_E_NONE)
        {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
        }

        /* Transmit packet(s) on the specified port */
        example_multi_pkt_send(unit, port, count);

        break;
      } /* End of case 1 */

      case 2:
      {
        printf("OpenNSL version: %s\n", opennsl_version_get());
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

  return OPENNSL_E_NONE;
}
