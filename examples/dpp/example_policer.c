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
 * \file         example_policer.c
 *
 * \brief        OpenNSL example application for policer or service meter
 *
 * \details       In this example, we will create a simple single rate, three color policer. 
 *                This policer will be attached to a Field Processor rule that counts 
 *                packets ingressing with a specific destination MAC address. 
 * 
 *                If single_rate=1 - meter mode is opennslPolicerModeSrTcm (single rate 3 colors), 
 *                the excess bucket has no credits of its own and it only receives excess credits 
 *                from the committed bucket run ethernet packet with DA 1 and vlan tag id 1 from 
 *                in_port, with:
 *
 *                1) priority = 1:
 *                     the stream will go through the committed bucket and afterwards also through 
 *                     the excess bucket for single_rate: the stream will arrive at out_port with 
 *                     30M rate (EIR has no credits).
 *
 *                2) priority = 4: 
 *                     the stream will go straight to the excess bucket and arrive at out_port with 
 *                     20M rate
 *
 *      Note: Stats processor is set based on the core. Use ports belonging to core=0(1 through 20)
 *      Create VLAN 100 and add input port and output port in the VLAN
 *             vlan create 100 PortBitMap=xe2,xe3 
 *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <opennsl/error.h>
#include <opennsl/init.h>
#include <opennsl/port.h>
#include <opennsl/l2.h>
#include <opennsl/vlan.h>
#include <opennsl/field.h>
#include <opennsl/policer.h>
#include <opennsl/cosqX.h>
#include <examples/util.h>


char example_usage[] =
"Syntax: example_policer                                                \n\r"
"                                                                       \n\r"
"Paramaters: None.                                                      \n\r"
"                                                                       \n\r"
"Example: The following command is used to create a policer and attach  \n\r"
"         it to a field processor rule matching traffic with            \n\r"
"         destination MAC = MAC_DA.                                     \n\r"
"         It also provides an option to display the number of packets   \n\r"
"         redirected to destination port.                               \n\r"
"                                                                       \n\r"
"         example_policer                                               \n\r"
"                                                                       \n\r"
"Usage Guidelines: None.                                                \n\r";

#define DEFAULT_UNIT 0
#define DEFAULT_VLAN 1
#define MAC_DA        {0x00, 0x00, 0x00, 0x00, 0x00, 0x01}
#define MAC_MASK      {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}


opennsl_policer_t policer_id;
int stat_id                = 2;
opennsl_field_stat_t accept_stats = opennslFieldStatAcceptedPackets;
opennsl_field_stat_t drop_stats = opennslFieldStatDroppedPackets;

opennsl_error_t
example_create_meter(int unit) 
{
  int rv;
  opennsl_info_t info;
  opennsl_policer_config_t pol_cfg;

  rv = opennsl_info_get(unit, &info);
  if (OPENNSL_FAILURE(rv)) 
  {
    printf("Error in opennsl_info_get, rv=%d\n", rv);
    return rv;
  }

  /* create policer 1 */
  opennsl_policer_config_t_init(&pol_cfg);
  pol_cfg.mode = opennslPolicerModeSrTcm; /* single rate three colors mode */

  pol_cfg.ckbits_sec = 30000; /* 30Mbps */
  pol_cfg.ckbits_burst = 1000;
  pol_cfg.pkbits_burst = 1000;
  pol_cfg.max_pkbits_sec = 20000; /* 20Mbps max */

  rv = opennsl_policer_create(unit, &(pol_cfg), &(policer_id));
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error in opennsl_policer_create no. 1, rv=%d\n",rv);
    return rv;
  }
  printf("policer_id1: %d\n", policer_id);

  return rv;
}


opennsl_error_t 
example_create_policy(int unit, opennsl_port_t in_port, opennsl_port_t out_port) 
{
  int rv;
  int group_priority = 6;
  opennsl_field_group_t grp = 1;
  opennsl_field_qset_t qset;
  opennsl_field_aset_t aset;
  opennsl_field_entry_t ent;
  opennsl_field_stat_t stats[2];
  int statId;
  opennsl_l2_addr_t l2addr;
  opennsl_mac_t mac = MAC_DA;
  opennsl_mac_t mask = MAC_MASK;


  /* map packet to meter_id, according to in-port and dst-port */
  OPENNSL_FIELD_QSET_INIT(qset);
  OPENNSL_FIELD_QSET_ADD(qset, opennslFieldQualifyDstMac);
  rv = opennsl_field_group_create_mode_id(unit, qset, group_priority, opennslFieldGroupModeAuto, grp);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error in opennsl_field_group_create_mode_id. rv=%d \n",rv);
    return rv;
  }

  OPENNSL_FIELD_ASET_INIT(aset);
  OPENNSL_FIELD_ASET_ADD(aset, opennslFieldActionPolicerLevel0);
  OPENNSL_FIELD_ASET_ADD(aset, opennslFieldActionUsePolicerResult);
  OPENNSL_FIELD_ASET_ADD(aset, opennslFieldActionStat0);
  rv = opennsl_field_group_action_set(unit, grp, aset);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error in opennsl_field_group_action_set. rv=%d \n",rv);
    return rv;
  }

  rv = opennsl_field_entry_create(unit, grp, &ent);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error in opennsl_field_entry_create. rv=%d\n",rv);
    return rv;
  }

  rv = opennsl_field_qualify_DstMac(unit, ent, mac, mask);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error in opennsl_field_qualify_DstMac. rv=%d\n",rv);
    return rv;
  }

  stats[0] = opennslFieldStatAcceptedPackets;
  stats[1] = opennslFieldStatDroppedPackets;
  statId = stat_id;
  rv = opennsl_field_stat_create_id(unit, grp, 2, &(stats[0]), statId);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error in opennsl_field_stat_create. rv=%d \n", rv);
    return rv;
  }

  rv = opennsl_field_entry_stat_attach(unit, ent, statId);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error in opennsl_field_entry_stat_attach with ent %d. rv=%d\n", ent, rv);
    return rv;
  }

  /* Create the policer */
  rv = example_create_meter(unit);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("\r\nFailed to create the meter. Error: %s\r\n",
	opennsl_errmsg(rv));
    return rv;
  }  

  rv = opennsl_field_entry_policer_attach(unit, ent, 0, (policer_id & 0xffff));
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error in opennsl_field_entry_policer_attach with policer_id %d. rv=%d \n", policer_id, rv);
    return rv;
  }

  rv = opennsl_field_group_install(unit, grp);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error in opennsl_field_group_install. rv=%d \n", rv);
    return rv;
  }

  /* send traffic with DA=1 and Vlan tag id 100 to out_port */
  opennsl_l2_addr_t_init(&l2addr, mac, 100);
  l2addr.port = out_port;
  rv = opennsl_l2_addr_add(unit, &l2addr);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, opennsl_l2_addr_add with vid 1. rv=%d \n", rv);
    return rv;
  }

  /* 
   * map Vlan tag proirity=4 and cfi=0 to yellow color:
   * this will mean that the packet will arrive with a yellow color instead of green 
   * if meter mode is not COLOR_BLIND, the packet will go straight to the excess bucket 
   * (without going through the committed bucket) 
   */
  rv = opennsl_port_vlan_priority_map_set(unit, in_port, 4 /* priority */, 0 /* cfi */, 
					    1 /* internal priority */, opennslColorYellow /* color */);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, opennsl_port_vlan_priority_map_set with prio 4. rv=%d \n", rv);
    return rv;
  }

  /* 
   * map Vlan tag proirity=1 and cfi=0 to green color:
   * packet that will arrive with a green color will go through the committed bucket 
   * and the excess bucket 
   */
  rv = opennsl_port_vlan_priority_map_set(unit, in_port, 1 /* priority */, 0 /* cfi */, 
					    0 /* internal priority */, opennslColorGreen /* color */);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, opennsl_port_vlan_priority_map_set with prio 1. rv=%d \n", rv);
    return rv;
  }

  /* set discard DP to drop all packets with DP = 3 */
  rv = opennsl_cosq_discard_set(unit, OPENNSL_COSQ_DISCARD_ENABLE | OPENNSL_COSQ_DISCARD_COLOR_BLACK);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, opennsl_cosq_discard_set. rv=%d \n", rv);
  }

  return rv;
}

/*****************************************************************//**
 * \brief Main function for policer application
 *
 * \param argc, argv         commands line arguments
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int main(int argc, char *argv[])
{
  int rv = 0;
  int unit = DEFAULT_UNIT;
  int choice;
  uint64 val;
  int inport, outport;

  if((argc != 1) || ((argc > 1) && (strcmp(argv[1], "--help") == 0))) 
  {
    printf("%s\n\r", example_usage);
    return OPENNSL_E_PARAM;
  }

  /* Initialize the system. */
  rv = opennsl_driver_init((opennsl_init_t *) NULL);
  if(rv != OPENNSL_E_NONE) 
  {
    printf("\r\nFailed to initialize the system. Error: %s\r\n",
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
    printf("\r\nFailed to add default ports. Error: %s\r\n",
        opennsl_errmsg(rv));
  }

  while(1) {
    printf("\r\nUser menu: Select one of the following options\r\n");
    printf("1. Apply policer to the traffic\n");
    printf("2. Retrieve statistics of the policer\n");
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
        printf("Enter the input port number(belonging to core-0):\n");
        if(example_read_user_choice(&inport) != OPENNSL_E_NONE)
        {
          printf("Invalid value entered. Please re-enter.\n");
          continue;
        }

        printf("Enter the output port number(belonging to core-0):\n");
        if(example_read_user_choice(&outport) != OPENNSL_E_NONE)
        {
          printf("Invalid value entered. Please re-enter.\n");
          continue;
        }

	/* Create policer and test traffic rate */
	rv = example_create_policy(unit, inport, outport);
	if (rv != OPENNSL_E_NONE) 
	{
	  printf("\r\nFailed to create the policer. Error: %s\r\n",
	      opennsl_errmsg(rv));
	}  

        break;
      }

      case 2:
      {
        rv = opennsl_field_stat_get(unit, stat_id, accept_stats, &val);
        if (rv != OPENNSL_E_NONE) {
          printf("Failed to get the accepted packets statistics, "
              "Error %s\n", opennsl_errmsg(rv));
          return rv;
        }
        printf("Number of packets accepted: %lld (0x%0x)\n", val, val);

        val = 0;
        rv = opennsl_field_stat_get(unit, stat_id, drop_stats, &val);
        if (rv != OPENNSL_E_NONE) {
          printf("Failed to get the dropped packets statistics, "
              "Error %s\n", opennsl_errmsg(rv));
          return rv;
        }
        printf("Number of packets dropped: %lld (0x%0x)\n", val, val);
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
