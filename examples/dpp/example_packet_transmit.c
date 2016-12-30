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
#include <opennsl/stack.h>
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
 * \brief print packet contents
 *
 * \param data	[IN]	buffer holding the packet content.
 * \param len 	[IN]	Size of the packet data.
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_pkt_dump(uint8 *data, int len)
{
    int i;
    int line_len = 16;

    printf ("\n packet dump for len = %d\n", len);

    for (i = 0; i < len; i++)
    {
      if (i % line_len == 0)
      {
        if (i !=0) printf("\n");
        printf("%04x  ", i);
      }
      printf ("%02x ", (data[i]) & 0xff);
    }

    printf ("\n\n");
    return 0;
}


/*****************************************************************//**
 * \brief Send a packet on the specified port and VLAN
 *
 * \param unit	[IN]	Unit number.
 * \param port	[IN]	Port number.
 * \param vlan	[IN]	VLAN ID.
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_pkt_send(int unit, opennsl_port_t port, opennsl_vlan_t vlan)
{
  int rv = OPENNSL_E_NONE;
  int pkt_flags;
  int pkt_len = 128;
  int pkt_header_len = 0;
  uint8 pkt_header[64];
  uint8 pkt_tagged_data[64] =
  {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, /* DA */
    0x00, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, /* SA */
    0x81, 0x00, 0x00, 0x01, /* TPID + VID */
    0x08, 0x00, 0x45, 0x10, 0x00, 0x46, 0x00, 0x00, 0x00, 0x00, 0x32, 0x06,
    0x82, 0xab, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02,
    0x03, 0x04, 0x00, 0x04, 0x01, 0x00, 0x56, 0xf1, 0x39, 0x00, 0x00,
    0x11, 0x22, 0x33, 0x44, 0x55, 0x66
  };
  uint8 pkt_buf[128];
  opennsl_gport_t sysport = 0;

  pkt_flags = OPENNSL_TX_CRC_ALLOC;

  opennsl_pkt_t *tx_pkt;
  rv = opennsl_pkt_alloc(unit, pkt_len, pkt_flags, &tx_pkt);
  if (rv != OPENNSL_E_NONE)
  {
    printf("Failed to allocate pkt memory, rv %s\n", opennsl_errmsg(rv));
    return rv;
  }

  rv = opennsl_stk_gport_sysport_get(unit, port, &sysport);
  if (rv != OPENNSL_E_NONE)
  {
    printf("Failed to get system port for unit %d port %d, rv %s\n", unit, port, opennsl_errmsg(rv));
    return rv;
  }

  void * cookie = (void *)1;
  tx_pkt->call_back = 0;
  tx_pkt->blk_count = 1;
  tx_pkt->unit = 0;

  /* PTCH */
  pkt_header[pkt_header_len++] = 0x50;
  pkt_header[pkt_header_len++] = 0;
  /* ITMH */
  pkt_header[pkt_header_len++] = 0x01;
  pkt_header[pkt_header_len++] = 0x00;
  pkt_header[pkt_header_len++] = (sysport & 0xff);
  pkt_header[pkt_header_len++] = 0x00;

  pkt_len =  pkt_header_len + 64;
  /* VID */
  pkt_tagged_data[14] = (vlan & 0xff00) >> 8;
  pkt_tagged_data[15] = (vlan & 0x00ff);

  memset(pkt_buf, 0, 128);
  memcpy(pkt_buf, pkt_header, pkt_header_len);
  memcpy(&pkt_buf[pkt_header_len], pkt_tagged_data, 64);
  pkt_len = pkt_header_len + 64;
  opennsl_pkt_memcpy (tx_pkt, 0, pkt_buf, pkt_len);

  rv = opennsl_tx (unit, tx_pkt, cookie);
  if (rv != OPENNSL_E_NONE)
  {
    printf("Failed to transmit packet, rv %s\n", opennsl_errmsg(rv));
    return rv;
  }

  example_pkt_dump (pkt_buf, pkt_len);

  rv = opennsl_pkt_free(unit, tx_pkt);
  if (rv != OPENNSL_E_NONE)
  {
    printf("Failed to free up packet memory, rv %s\n", opennsl_errmsg(rv));
    return rv;
  }

  return rv;
}

/*****************************************************************//**
* \brief Form a packet and send multiple packets from the specified port
*
* \param unit	  [IN]	Unit number.
* \param port  	[IN]	Port number.
* \param port	  [IN]	VLAN ID.
* \param count	[IN]	Number of packets to be transmitted.
*
* \return OPENNSL_E_XXX     OpenNSL API return code
********************************************************************/
void example_multi_pkt_send(int unit, opennsl_port_t port,
    opennsl_vlan_t vlan,  int count)
{
  int i;
  int rv;

  for (i = 0; i < count; i++)
  {
    rv = example_pkt_send(unit, port, vlan);

    if (!OPENNSL_SUCCESS(rv))
    {
      printf("Error Sending Packet: %d.  Error: %s\n", i + 1, opennsl_errmsg(rv));
    }
    else
    {
      printf("Transmitted Packet %d\n", i + 1);
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
  opennsl_vlan_t vlan;
  int unit = DEFAULT_UNIT;
  int choice;
  int index = 0;

  if(strcmp(argv[0], "gdb") == 0)
  {
    index = 1;
  }

  if((argc != (index + 1)) || ((argc > (index + 1)) && (strcmp(argv[index + 1], "--help") == 0)))
  {
    printf("%s\n\r", example_usage);
    return OPENNSL_E_PARAM;
  }

  /* Initialize the system. */
  printf("Initializing the system.\r\n");
  rv = opennsl_driver_init((opennsl_init_t *) NULL);

  if(rv != OPENNSL_E_NONE)
  {
    printf("\r\nFailed to initialize the system. Error %s\r\n",
        opennsl_errmsg(rv));
    return rv;
  }

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

  while (1)
  {
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

          printf("\r\nEnter VLAN ID of the packet.\r\n");
          if(example_read_user_choice(&choice) != OPENNSL_E_NONE)
          {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
          }
          vlan = (opennsl_vlan_t) choice;

          printf("\r\nEnter number of packets to be sent.\r\n");
          if(example_read_user_choice(&count) != OPENNSL_E_NONE)
          {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
          }

          /* Transmit packet(s) on the specified port */
          example_multi_pkt_send(unit, port, vlan, count);

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
