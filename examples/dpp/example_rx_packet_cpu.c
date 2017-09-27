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
 * \file     example_rx_packet_cpu.c
 *
 * \brief    Example code for packet transmission
 *
 * \details  This example demonstrates the reception of a CPU bound packet.
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
#include <opennsl/rx.h>
#include <examples/util.h>

#define DEFAULT_UNIT  0
#define DEFAULT_VLAN  1
#define MAX_DIGITS_IN_CHOICE 5

char example_usage[] =
"Syntax: example_rx_packet_cpu                                         \n\r"
"                                                                      \n\r"
"Paramaters: None.                                                     \n\r"
"                                                                      \n\r"
"Example: The following command is used to demonstrate receiving a     \n\r"
"         packet to CPU.                                               \n\r"
"         example_rx_packet_cpu                                        \n\r"
"                                                                      \n\r"
"Usage Guidelines: None.                                               \n\r";


/*****************************************************************//**
 * \brief  Strip FTMH and User Header etc and get the start ethernet 
 *         packet
 *
 * \param  [IN]  unit          unit number
 * \param  [IN]  pkt           Pointer to packet data
 * \param  [IN]  len           Length of the packet
 * \param  [OUT] user_header   Pointer to User Header start
 * \param  [OUT] offset        Offset to ethernet header
 *                             length of FTMH+ User Header etc
 *                             *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_pkt_start_get (unsigned int unit, unsigned char *pkt,
                           int len, unsigned char *user_header,
                           unsigned int *offset)
{
  unsigned char        pph_type;
  unsigned int         pph_offset;
  unsigned int         lb_ext_offset = 0;
  unsigned char        eei_ext_present;
  unsigned char        lrn_ext_present;
  unsigned char        fhei_size;

  /* Initialize offset to account for the FTMH base header size */
  *offset = 9;

  /* Set to 1 if config property "system_ftmh_load_balancing_ext_mode" is *
   * defined. Otherwise, set it to zero */
  lb_ext_offset = 1;
  *offset += lb_ext_offset;

  /*
   * Need to parse the FTMH Base header to determine if Dest System Port
   * Ext(16bits) is included. This is bit 3 of the 72bit FTMH base header.
   */
  if (pkt[8] & 0x08)
  {
    *offset += 2;
  }

  /* Parse the PPH_TYPE in the FTMH header to see how much, *
   * if any, PPH to parse */
  pph_type = (pkt[5] & 0x06) >> 1;
  switch(pph_type)
  {
    case 0: /* No PPH */
      pph_offset = 0;
      break;

    case 1: /* PPH Base */
      /* PPH Base size = 56bits */
      pph_offset = 7;

      /* Is EEI-Extension-Present 24bits */
      eei_ext_present = (pkt[*offset+0] & 0x80) >> 7;
      if (eei_ext_present)
      {
        pph_offset += 3;
      }

      /* Is Learn-Extension-Present 40bits */
      lrn_ext_present = (pkt[*offset+0] & 0x40) >> 6;
      if (lrn_ext_present)
      {
        pph_offset += 5;
      }

      /* FHEI-Size? */
      fhei_size = (pkt[*offset+0] & 0x30) >> 4;
      switch(fhei_size)
      {
        case 0:
          /* No fhei header */
          break;
        case 1:
          /* 3 Byte fhei header */
          pph_offset += 3;
          break;
        case 2:
          /* 5 Byte fhei header */
          pph_offset += 5;
          break;
        case 3:
          /* 8 Byte fhei header */
          pph_offset += 8;
          break;
      }
      break;

    case 2: /* PPH OAM-TS only */
      pph_offset = 0;
      break;

    case 3: /* PPH Base + PAM-TS */
      pph_offset = 0;
      break;
   }

  *offset += pph_offset;

  return 0;
}

/*****************************************************************//**
 * \brief Packet receive callback function
 *
 * \param unit	 [IN]	Unit number
 * \param pkt 	 [IN]	Pointer to packet data
 * \param cookie [IN]	Cookie
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
opennsl_rx_t example_rx_packet_receive(int unit, opennsl_pkt_t *pkt,
                                       void *cookie)
{
  int i;
  uint8 *data;
  unsigned int offset = 0;
  opennsl_pkt_t pkt_l;
  unsigned char user_header[8];

  /* print the packet received from driver */
  printf("Packet received with pkt->rx_port:%hhu pkt->src_port:%hhu\n",
      pkt->rx_port, pkt->src_port);
  printf("Packet received with pkt->pkt_len : %d pkt->tot_len : %d cos: %d\n",
      pkt->pkt_len, pkt->tot_len, pkt->cos);

  data = pkt->pkt_data->data;

  for(i = 0; i < pkt->tot_len; i++)
  {
    if ((i % 4) == 0)
      printf(" ");
    if ((i % 32) == 0)
      printf("\n\t");

    printf("%02hhx", data[i]);
  }
  printf("\n\n");

  /* Remove device specific header from the received packet */
  memset (&pkt_l, 0x00, sizeof(pkt_l));
  example_pkt_start_get(unit, pkt->pkt_data->data,
      pkt->pkt_data->len,
      user_header,
      &offset);

  memcpy (&pkt_l, pkt, sizeof(pkt_l));
  pkt_l.pkt_data->data = &pkt->pkt_data->data[offset];
  pkt_l.tot_len        =  pkt->tot_len - offset;
  pkt = &pkt_l;
/*  pkt->src_port = pkt->src_port - 12; */

  /* print the packet after removing device specific header */
  printf("Packet after stripping the device specific header\n");
  data = pkt->pkt_data->data;

  for(i = 0; i < pkt->tot_len; i++)
  {
    if ((i % 4) == 0)
      printf(" ");
    if ((i % 32) == 0)
      printf("\n\t");

    printf("%02hhx", data[i]);
  }

  printf("\n\n");

  return OPENNSL_RX_HANDLED;
}

/*****************************************************************//**
 * \brief Setup up the system for packet reception
 *
 * \param unit	 [IN]	Unit number
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_rx_setup(int unit)
{
  /* RX Configuration Structure */
  opennsl_rx_cfg_t rx_cfg;
  int rv = OPENNSL_E_NONE;
  int priority = 10;

  opennsl_rx_cfg_t_init(&rx_cfg);
  rx_cfg.pkt_size = 16*1024;
  rx_cfg.pkts_per_chain = 15;
  rx_cfg.global_pps = 0;
  rx_cfg.max_burst = 200;
  /* Strip CRC from incoming packets          *
   * rx_cfg.flags |= OPENNSL_RX_F_CRC_STRIP;  */
  rx_cfg.chan_cfg[1].chains = 4;
  /* Packets with all CoS values come through this channel */
  rx_cfg.chan_cfg[1].cos_bmp = 0xFFFFFFff;

  /* Register to receive packets punted to CPU */
  rv = opennsl_rx_register(unit, "sample application",
      example_rx_packet_receive, priority, NULL, OPENNSL_RCO_F_ALL_COS);
  if (OPENNSL_FAILURE(rv))
  {
    printf("Failed to register packet receive callback for unit %d,"
        "rv = %d (%s).\r\n", unit, rv, opennsl_errmsg(rv));
  }

  if (!opennsl_rx_active(unit))
  {
    rv = opennsl_rx_start(unit, &rx_cfg);
    if (OPENNSL_FAILURE(rv))
    {
      printf("opennsl_rx_start() failed on unit %d with rv %d (%s).\r\n",
          unit, rv, opennsl_errmsg(rv));
    }
  }
  return rv;
}

/*****************************************************************//**
 * \brief Main function for packet reception
 *
 * \param argc, argv         commands line arguments
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int main(int argc, char *argv[])
{
  opennsl_error_t   rv;
  int unit = DEFAULT_UNIT;
  int choice;
  int index = 0;
  opennsl_port_config_t pcfg;


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

  rv = example_port_default_config(unit);
  if (rv != OPENNSL_E_NONE)
  {
    printf("\r\nFailed to apply default config on ports, rv = %d (%s).\r\n",
           rv, opennsl_errmsg(rv));
  }

  /* Add ports to default VLAN. */
  printf("Adding ports to default VLAN.\r\n");
  rv = example_switch_default_vlan_config(unit);
  if(rv != OPENNSL_E_NONE)
  {
    printf("\r\nFailed to add default ports. rv: %s\r\n", opennsl_errmsg(rv));
    return rv;
  }

  /* Add CPU port to default VLAN */
  rv = opennsl_port_config_get(unit, &pcfg);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to get port configuration. Error %s\n", opennsl_errmsg(rv));
    return rv;
  }

  rv = opennsl_vlan_port_add(unit, DEFAULT_VLAN, pcfg.cpu, pcfg.cpu);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to add ports to VLAN. Error %s\n", opennsl_errmsg(rv));
    return rv;
  }
  printf("CPU port is added to default VLAN.\r\n");

  rv = example_rx_setup(unit);
  if(rv != OPENNSL_E_NONE)
  {
    printf("\r\nFailed to setup system for packet reception. rv: %s\r\n",
        opennsl_errmsg(rv));
    return rv;
  }

  while (1)
  {
    printf("\r\nUser menu: Select one of the following options\r\n");
    printf("1. Display OpenNSL version\n");
#ifdef INCLUDE_DIAG_SHELL
    printf("9. Launch diagnostic shell\n");
#endif
    printf("0. Quit the application\n");

    if(example_read_user_choice(&choice) != OPENNSL_E_NONE)
    {
        printf("Invalid option entered. Please re-enter.\n");
        continue;
    }
    switch(choice)
    {
      case 1:
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
        rv = opennsl_driver_exit();
        return rv;
      }

      default:
        break;
    } /* End of switch */
  } /* End of while */

  return OPENNSL_E_NONE;
}
