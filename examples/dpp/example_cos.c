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
 * \file         example_cos.c
 *
 * \brief        OpenNSL example application for Class Of Service module
 *
 * \details       This example includes:
 *  o     Port shaper 
 *  o     Queue's weight (WFQ) 
 *  o     Strict priority 
 *  o     Incoming TC/DP mapping 
 *
 * It is assumed diag_init is executed.
 * 
 * Settings include:
 * Set the OFP Bandwidth to 5G using the port shaper.
 *  1.  Set the OFP Bandwidth to 5G using the port shaper. 
 *    2.    Set queues priorities WFQ/SP as follows:
 *         -    For the high-priority queues, WFQ is set: UC will get 2/3 of the BW and MC will get 1/3 of the BW.
 *         -    For the low-priority queues, SP UC is set over MC.
 *    3.    Configure TC/DP egress mapping. Map low-priority traffic (0 - 3 for UC, 0  - 5 for MC)
 *     to low-priority queues, and high-priority traffic (4  - 7 for UC, 6  - 7 for MC) to high-priority queues.
 * 
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  |                                                                        |
 *  |                                   |\                                   |
 *  |opennslCosqGportTypeUnicastEgress  | \                                  |
 *  |             +-----------+         |  \                                 |
 *  |   TC 0-3 -->| HP UC  || |---------|2/3\                                |
 *  |             +-----------+         |    |                               |
 *  |opennslCosqGportTypeMulticastEgress|WFQ |-----+                         |
 *  |             +-----------+         |    |     |     |\                  |
 *  |   TC 0-5 -->| HP MC  || |---------|1/3/      |     | \                 |
 *  |             +-----------+         |  /       +---->|H \                |
 *  |                                   | /              |   \               |
 *  |                                   |/               |    |    5G        |
 *  |                                                    | SP |----SPR---->  |
 *  |opennslCosqGportTypeUnicastEgress  |\               |    |              |
 *  |             +-----------+         | \              |   /               |
 *  |   TC 4-7 -->| LP UC  || |---------|H \       +---->|L /                |
 *  |             +-----------+         |   |      |     | /                 |
 *  |opennslCosqGportTypeMulticastEgress| SP|------+     |/                  |
 *  |             +-----------+         |   |                                |
 *  |   TC 6-7 -->| LP MC  || |---------|L /          +----------------+     |
 *  |             +-----------+         | /           |      KEY       |     |
 *  |                                   |/            +----------------+     |
 *  |                                                 |SPR- Rate Shaper|     |
 *  |                                                 |                |     |
 *  |                                                 +----------------+     |
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <opennsl/error.h>
#include <opennsl/init.h>
#include <opennsl/stack.h>
#include <opennsl/port.h>
#include <opennsl/l2.h>
#include <opennsl/vlan.h>
#include <opennsl/cosq.h>
#include <opennsl/multicast.h>
#include <examples/util.h>


char example_usage[] =
"Syntax: example_cos                                                    \n\r"
"                                                                       \n\r"
"Paramaters: None.                                                      \n\r"
"                                                                       \n\r"
"Example: The following command is used to test the CoS functionality   \n\r"
"                                                                       \n\r"
"         example_cos                                                   \n\r"
"                                                                       \n\r"
"Usage Guidelines: None.                                                \n\r";


#define DEFAULT_UNIT 0
#define DEFAULT_VLAN 1


int egress_mc = 0;

int multicast__open_mc_group(int unit, int *mc_group_id, int extra_flags) 
{
  int rv = OPENNSL_E_NONE;
  int flags;

  /* destroy before open, to ensure it not exist */
  rv = opennsl_multicast_destroy(unit, *mc_group_id);

  printf("egress_mc: %d \n", egress_mc);

  flags = OPENNSL_MULTICAST_WITH_ID | extra_flags;
  /* create ingress/egress MC */
  if (egress_mc) 
  {
    flags |= OPENNSL_MULTICAST_EGRESS_GROUP;
  } 
  else 
  {
    flags |= OPENNSL_MULTICAST_INGRESS_GROUP;
  }

  rv = opennsl_multicast_create(unit, flags, mc_group_id);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, opennsl_multicast_create, flags $flags mc_group_id $mc_group_id \n");
    return rv;
  }

  printf("Created mc_group %d \n", *mc_group_id);

  return rv;
}

/* Adding entries to MC group
 * ipmc_index:  mc group
 * ports: array of ports to add to the mc group
 * cud 
 * nof_mc_entries: number of entries to add to the mc group
 * is_ingress:  if true, add ingress mc entry, otherwise, add egress mc 
 * see add_ingress_multicast_forwarding from cint_ipmc_flows.c
 * 
   */
int multicast__add_multicast_entry(int unit, int ipmc_index, int *ports, int *cud, int nof_mc_entries, int is_egress) 
{
  int rv = OPENNSL_E_NONE;
  int i;

  for (i=0;i<nof_mc_entries;i++) 
  {
    /* egress MC */
    if (is_egress) 
    {
      rv = opennsl_multicast_egress_add(unit,ipmc_index,ports[i],cud[i]);
      if (rv != OPENNSL_E_NONE) 
      {
        printf("Error, opennsl_multicast_egress_add: port %d encap_id: %d \n", ports[i], cud[i]);
        return rv;
      }
    } 
    /* ingress MC */
    else 
    {
      rv = opennsl_multicast_ingress_add(unit,ipmc_index,ports[i],cud[i]);
      if (rv != OPENNSL_E_NONE) 
      {
        printf("Error, opennsl_multicast_ingress_add: port %d encap_id: %d \n", ports[i], cud[i]);
        return rv;
      }
    }
  }

  return rv;
}

int multicast__open_egress_mc_group_with_local_ports(int unit, int mc_group_id, int *dest_local_port_id, int *cud, int num_of_ports, int extra_flags) 
{
  int i;
  opennsl_error_t rv = OPENNSL_E_NONE;
  opennsl_cosq_gport_info_t gport_info;
  opennsl_cosq_gport_type_t gport_type = opennslCosqGportTypeLocalPort;

  egress_mc = 1;

  rv = multicast__open_mc_group(unit, &mc_group_id, extra_flags);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, multicast__open_mc_group, extra_flags $extra_flags mc_group $mc_group_id \n");
    return rv;
  }

  for(i=0;i<num_of_ports;i++) 
  {
    OPENNSL_GPORT_LOCAL_SET(gport_info.in_gport,dest_local_port_id[i]); 
    rv = opennsl_cosq_gport_handle_get(unit,gport_type,&gport_info);
    if (rv != OPENNSL_E_NONE) 
    {
      printf("Error, opennsl_cosq_gport_handle_get, gport_type $gport_type \n");
      return rv;
    }

    rv = multicast__add_multicast_entry(unit, mc_group_id, &gport_info.out_gport, &cud[i], 1, egress_mc);
    if (rv != OPENNSL_E_NONE) 
    {
      printf("Error, multicast__add_multicast_entry, mc_group_id $mc_group_id dest_gport $gport_info.out_gport \n");
      return rv;
    }
  }

  return rv;
}

/* Set OFP Bandwidth (max KB per sec)
 * Configure the Port Shaper's max rate
 */
int example_set_ofp_bandwidth(int unit, int local_port_id, int max_kbits_sec)
{
  opennsl_error_t rv = OPENNSL_E_NONE;
  opennsl_cosq_gport_type_t gport_type;
  opennsl_cosq_gport_info_t gport_info;
  opennsl_gport_t out_gport;

  int min_kbits_rate = 0;
  int flags = 0;

  /* Set GPORT according to the given local_port_id */
  OPENNSL_GPORT_LOCAL_SET(gport_info.in_gport, local_port_id); 

  gport_type = opennslCosqGportTypeLocalPort; 

  rv = opennsl_cosq_gport_handle_get(unit, gport_type, &gport_info);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, in handle get, gport_type $gport_type \n");
    return rv;
  }

  out_gport = gport_info.out_gport;
  rv = opennsl_cosq_gport_bandwidth_set(unit, out_gport, 0, min_kbits_rate, max_kbits_sec, flags);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, in bandwidth set, out_gport $out_gport max_kbits_sec $max_kbits_sec \n");
    return rv;
  }

  return rv;
}

/* Set Strict Priority Configuration 
 * queue = OPENNSL_COSQ_LOW_PRIORITY
 *         OPENNSL_COSQ_HIGH_PRIORITY
 * SP_Type = 0 for UC over MC
 *           1 for MC over UC
 */
int example_set_sp(int unit, int local_port_id, int queue, int sp_type)
{
  opennsl_error_t rv = OPENNSL_E_NONE;
  opennsl_cosq_gport_type_t gport_type;
  opennsl_cosq_gport_info_t gport_info;
  opennsl_gport_t out_gport;

  /* Set GPORT according to the given local_port_id */
  OPENNSL_GPORT_LOCAL_SET(gport_info.in_gport,local_port_id); 

  /* We will define MC as high or low priority */
  gport_type = opennslCosqGportTypeMulticastEgress; 

  rv = opennsl_cosq_gport_handle_get(unit,gport_type,&gport_info);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, in handle get, gport_type $gport_type \n");
    return rv;
  }

  out_gport = gport_info.out_gport;
  if(sp_type == 0) 
  {
    /* Setting with OPENNSL_COSQ_SP1 will set the MC to be LOWER priority --> UC over MC */
    rv = opennsl_cosq_gport_sched_set(unit, out_gport, queue, OPENNSL_COSQ_SP1, -1);
  } 
  else 
  {
    /* Setting with OPENNSL_COSQ_SP0 will set the MC to be HIGHER priority --> MC over UC */
    rv = opennsl_cosq_gport_sched_set(unit, out_gport, queue, OPENNSL_COSQ_SP0, -1);
  }

  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, in SP set, out_gport $out_gport queue $queue sp_type  $sp_type \n");
  }

  return rv;
}

/* Generic set weight function 
 * queue = OPENNSL_COSQ_LOW_PRIORITY
 *         OPENNSL_COSQ_HIGH_PRIORITY
 * uc_mc = 0 for UC
 *         1 for MC 
 */
int example_set_weight(int unit, int local_port_id, int queue, int uc_mc, int weight)
{
  opennsl_error_t rv = OPENNSL_E_NONE;
  opennsl_cosq_gport_type_t gport_type;
  opennsl_cosq_gport_info_t gport_info;
  opennsl_gport_t out_gport;

  /* Set GPORT according to the given local_port_id */
  OPENNSL_GPORT_LOCAL_SET(gport_info.in_gport,local_port_id); 

  if(uc_mc == 0) 
  {
    gport_type = opennslCosqGportTypeUnicastEgress; 
  } 
  else 
  {
    gport_type = opennslCosqGportTypeMulticastEgress; 
  }

  rv = opennsl_cosq_gport_handle_get(unit,gport_type,&gport_info);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, in handle get, gport_type $gport_type \n");
    return rv;
  }

  out_gport = gport_info.out_gport;

  /* Set the weight of the designated queue
   * mode = -1 becuase we are setting weight and not strict priority
   */
  rv = opennsl_cosq_gport_sched_set(unit, out_gport, queue, -1, weight);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, in weight set, out_gport $out_gport queue $queue weight $weight \n");
  }

  return rv;
}

int
_opennsl_petra_egress_queue_from_cosq(int unit,
                                      int *queue_id,
                                      int cosq)
{
  opennsl_error_t rv = OPENNSL_E_NONE;

  switch (cosq) 
  {
    case OPENNSL_COSQ_HIGH_PRIORITY:
    case 0:
        *queue_id = 0;
        break;
    case OPENNSL_COSQ_LOW_PRIORITY:
    case 1:
        *queue_id = 1;
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        *queue_id = cosq;
        break;
  }

  return rv;
}

/* Map incoming UC TC/DP to L/H queue
 *  incoming_tc = 0-7
 *  incoming_dp = 0-3
 *  queue = OPENNSL_COSQ_LOW_PRIORITY
 *          OPENNSL_COSQ_HIGH_PRIORITY
 */
int example_set_uc_queue_mapping(int unit, int local_port_id, int incoming_tc, int incoming_dp, int queue)
{
  opennsl_error_t rv = OPENNSL_E_NONE;
  opennsl_cosq_gport_type_t gport_type;
  opennsl_cosq_gport_info_t gport_info;
  opennsl_gport_t out_gport;
  int queue_id;

  /* Set GPORT according to the given local_port_id */
  OPENNSL_GPORT_LOCAL_SET(gport_info.in_gport,local_port_id); 

  gport_type = opennslCosqGportTypeUnicastEgress; 

  rv = opennsl_cosq_gport_handle_get(unit,gport_type,&gport_info);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, in handle get, gport_type $gport_type \n");
    return rv;
  }

  out_gport = gport_info.out_gport;
  rv = _opennsl_petra_egress_queue_from_cosq(unit,&queue_id,queue);
  rv = opennsl_cosq_gport_egress_map_set(unit, out_gport, incoming_tc, incoming_dp, queue_id);

  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, in uc queue mapping, out_gport $out_gport incoming_tc $incoming_tc incoming_dp $incoming_dp queue $queue \n");
  }

  return rv;
}
 
/*  Map incoming MC TC/DP to L/H queue
 *  incoming_tc = 0-7
 *  incoming_dp = 0-3
 *  queue = OPENNSL_COSQ_LOW_PRIORITY
 *          OPENNSL_COSQ_HIGH_PRIORITY
 */
int example_set_mc_queue_mapping(int unit, int local_port_id, int incoming_tc, int incoming_dp, int queue)
{
  opennsl_error_t rv = OPENNSL_E_NONE;
  opennsl_cosq_gport_type_t gport_type;
  opennsl_cosq_gport_info_t gport_info;
  opennsl_gport_t out_gport;
  int queue_id;

  /* Set GPORT according to the given local_port_id */
  OPENNSL_GPORT_LOCAL_SET(gport_info.in_gport,local_port_id); 

  gport_type = opennslCosqGportTypeLocalPort; 

  rv = opennsl_cosq_gport_handle_get(unit,gport_type,&gport_info);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, in handle get, gport_type $gport_type \n");
    return rv;
  }

  out_gport = gport_info.out_gport;

  rv = _opennsl_petra_egress_queue_from_cosq(unit,&queue_id,queue);
  opennsl_cosq_egress_multicast_config_t  multicast_egress_mapping =  { 0, queue_id,-1,-1};

  rv = opennsl_cosq_gport_egress_multicast_config_set(unit, out_gport, incoming_tc, incoming_dp, 
						  OPENNSL_COSQ_MULTICAST_SCHEDULED, 
						  &multicast_egress_mapping );

  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, in mc queue mapping, out_gport $out_gport incoming_tc $incoming_tc incoming_dp $incoming_dp queue $queue \n");
  }

  return rv;
}

/* Setup MAC forwading
 * dest_type = 0 for Local Port
 *             1 for MC Group
 */
int example_setup_mac_forwarding(int unit, opennsl_mac_t mac, opennsl_vlan_t vlan, int dest_type, int dest_id)
{
  opennsl_error_t rv = OPENNSL_E_NONE;
  opennsl_gport_t dest_gport;
  opennsl_l2_addr_t l2_addr;

  opennsl_l2_addr_t_init(&l2_addr, mac, vlan);   
  /* Create MC or PORT address forwarding */
  if(dest_type == 0) 
  {
    l2_addr.flags = OPENNSL_L2_STATIC;
    OPENNSL_GPORT_LOCAL_SET(dest_gport, dest_id);
    l2_addr.port = dest_gport;
  } 
  else 
  {
    l2_addr.flags = OPENNSL_L2_STATIC | OPENNSL_L2_MCAST;
    l2_addr.l2mc_group = dest_id;
  }

  rv = opennsl_l2_addr_add(unit,&l2_addr);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, in example_setup_mac_forwarding, dest_type $dest_type dest_id $dest_id \n");
  }

  return rv;
}

/*  Main function
 *  opennsl_local_port_id = The desiganted port we want to configure
 *  is_tm = 0 for PP Ports
 *          1 for TM ports
 * 
 */
int example_egress_transmit_application(int unit, int opennsl_local_port_id, int is_tm)
{
  opennsl_error_t rv = OPENNSL_E_NONE;
  int tc = 0;
  int dp = 0;
  int my_modid = 0;

  /* Init */
  printf("Starting Egress Transmit Application\n");
  rv = opennsl_stk_modid_get(unit, &my_modid);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("opennsl_stk_my_modid_get failed $rv\n");
    return rv;
  }

  /* Create MC group */
  printf("Setting up Multicast Groups.\n");
  int mc_group_id = 5005;
  int cud = 0;
  opennsl_multicast_t mc_group = mc_group_id;

  /* We want to overwrite any existing group */
  opennsl_multicast_destroy(unit, mc_group);

  /* Open Egress MC with the designated port as destination and 0 as cud */
  rv = multicast__open_egress_mc_group_with_local_ports(unit, mc_group_id, &opennsl_local_port_id, &cud, 1, 0);
  if (rv != OPENNSL_E_NONE) return rv;

  /* Forwarding Setup, only relevant for PP ports */
  if(is_tm == 0) 
  {
    printf("Setting up MAC Forwarding for PP Ports.\n");
    opennsl_mac_t incoming_mac_uc;
    opennsl_mac_t incoming_mac_mc;
    incoming_mac_uc[5] = 0x1;
    int incoming_vlan_uc = 1;
    incoming_mac_mc[5] = 0x2;
    int incoming_vlan_mc = 1;

    rv = example_setup_mac_forwarding(unit, incoming_mac_uc, incoming_vlan_uc, 0, opennsl_local_port_id);
    if (rv != OPENNSL_E_NONE) return rv;
    rv = example_setup_mac_forwarding(unit, incoming_mac_mc, incoming_vlan_mc, 1, mc_group_id);
    if (rv != OPENNSL_E_NONE) return rv;
  }

  /* Set OFP Bandwidth to 5G */
  printf("Setting Port Bandwidth.\n");
  int max_bandwidth = 5000000; 
  rv = example_set_ofp_bandwidth(unit, opennsl_local_port_id, max_bandwidth);
  if (rv != OPENNSL_E_NONE) return rv;

  /* Set Weight for the Low Priority Queues */
  printf("Setting Weight for low priority queues.\n");
  int uc_weight =1;
  int mc_weight = 2;
  rv = example_set_weight(unit, opennsl_local_port_id, OPENNSL_COSQ_LOW_PRIORITY, 0, uc_weight); 
  if (rv != OPENNSL_E_NONE) return rv;
  rv = example_set_weight(unit, opennsl_local_port_id, OPENNSL_COSQ_LOW_PRIORITY, 1, mc_weight); 
  if (rv != OPENNSL_E_NONE) return rv;

  /* Set UC over MC for the High Priority Queues */
  printf("Setting Strict Priority for high priority queues.\n");
  rv = example_set_sp(unit,opennsl_local_port_id, OPENNSL_COSQ_HIGH_PRIORITY, 0);
  if (rv != OPENNSL_E_NONE) return rv;

  /* Set UC Queue Mapping */
  printf("Setting UC queue mapping.\n");
  for (tc=0; tc <= 3 ; tc++) 
  { 
    for(dp = 0; dp <=3; dp++ ) 
    {
      /* printf("\t TC $tc DP $dp --> Low Priority.\n"); */
      rv = example_set_uc_queue_mapping(unit, opennsl_local_port_id, tc, dp, OPENNSL_COSQ_LOW_PRIORITY);
      if (rv != OPENNSL_E_NONE) return rv;
    }
  }

  for (tc=4; tc <= 7 ; tc++) 
  {
    for(dp = 0; dp <=3; dp++ ) 
    {
      /* printf("\t TC $tc DP $dp --> High Priority.\n"); */
      rv = example_set_uc_queue_mapping(unit, opennsl_local_port_id, tc, dp, OPENNSL_COSQ_HIGH_PRIORITY);
      if (rv != OPENNSL_E_NONE) return rv;
    }
  }

  /* Set MC Queue Mapping */
  printf("Setting MC queue mapping.\n");
  for (tc=0; tc <= 5 ; tc++) 
  {
    for(dp = 0; dp <=3; dp++ ) 
    {
      /*printf("\t TC $tc DP $dp --> Low Priority.\n"); */
      rv = example_set_mc_queue_mapping(unit, opennsl_local_port_id, tc, dp, OPENNSL_COSQ_LOW_PRIORITY);
      if (rv != OPENNSL_E_NONE) return rv;
    }
  }

  for (tc=6; tc <= 7 ; tc++) 
  {
    for(dp = 0; dp <=3; dp++ ) 
    {
      /* printf("\t TC $tc DP $dp --> High Priority.\n"); */
      rv = example_set_mc_queue_mapping(unit, opennsl_local_port_id, tc, dp, OPENNSL_COSQ_HIGH_PRIORITY);
      if (rv != OPENNSL_E_NONE) return rv;
    }
  }

  printf("Engress Transmit Application Completed Successfully.\n");

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
  int outport;

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
    printf("1. Apply CoS mapping to the traffic\n");
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
        printf("Enter the egress port number(belonging to core-0):\n");
        if(example_read_user_choice(&outport) != OPENNSL_E_NONE)
        {
          printf("Invalid value entered. Please re-enter.\n");
          continue;
        }

        /* Create CoS mapping to test with traffic */
        rv = example_egress_transmit_application(0, outport, 0);
        if (rv != OPENNSL_E_NONE) 
        {
          printf("\r\nFailed to create the CoS mapping. Error: %s\r\n",
              opennsl_errmsg(rv));
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
        return OPENNSL_E_NONE;
      }
      default:
      break;
    } /* End of switch */
  } /* End of while */

  return rv;
}
