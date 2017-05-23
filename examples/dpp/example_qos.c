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
 * \file         example_qos.c
 *
 * \brief        OpenNSL example application for QoS based on port
 *
 * \details      In this example, we will map TC and DP from the packet PCP
 *               (targeted for tagged packet) including three modes:
 *               1. map dei without cfi for s tagged packet when use_de=0
 *               2. map dei with cfi for s tagged packet when use_de=1
 *               3. map up to dp for c tagged packet
 *
 *  use_de can be 0 or 1. 0 stands for not mapping dei without cfi; 1 stands for mapping dei with cfi.
 *  Send Traffic from input port, say 2 and receive it on port 3 when use_de is 0:
 *  1. In port 2 vid 100 prio 0 cfi 0  <-----CrossConnect----->  Out port 3 vid 300 prio 1 cfi 1
 *  2. In port 2 vid 100 prio 1 cfi 1  <-----CrossConnect----->  Out port 3 vid 300 prio 2 cfi 0
 *  3. In port 2 vid 100 prio 2 cfi 0  <-----CrossConnect----->  Out port 3 vid 300 prio 3 cfi 1
 *  4. In port 2 vid 100 prio 3 cfi 1  <-----CrossConnect----->  Out port 3 vid 300 prio 4 cfi 0
 *  5. In port 2 vid 100 prio 4 cfi 0  <-----CrossConnect----->  Out port 3 vid 300 prio 5 cfi 1
 *  6. In port 2 vid 100 prio 5 cfi 1  <-----CrossConnect----->  Out port 3 vid 300 prio 6 cfi 0
 *  7. In port 2 vid 100 prio 6 cfi 0  <-----CrossConnect----->  Out port 3 vid 300 prio 7 cfi 1
 *  8. In port 2 vid 100 prio 7 cfi 1  <-----CrossConnect----->  Out port 3 vid 300 prio 7 cfi 0
 *  Send Traffic from port 2 and receive it on port 3 when use_de is 1:
 *  1. In port 2 vid 100 prio 0 cfi 0  <-----CrossConnect----->  Out port 3 vid 300 prio 1 cfi 0
 *  2. In port 2 vid 100 prio 1 cfi 1  <-----CrossConnect----->  Out port 3 vid 300 prio 2 cfi 1
 *  3. In port 2 vid 100 prio 2 cfi 0  <-----CrossConnect----->  Out port 3 vid 300 prio 3 cfi 0
 *  4. In port 2 vid 100 prio 3 cfi 1  <-----CrossConnect----->  Out port 3 vid 300 prio 4 cfi 1
 *  5. In port 2 vid 100 prio 4 cfi 0  <-----CrossConnect----->  Out port 3 vid 300 prio 5 cfi 0
 *  6. In port 2 vid 100 prio 5 cfi 1  <-----CrossConnect----->  Out port 3 vid 300 prio 6 cfi 1
 *  7. In port 2 vid 100 prio 6 cfi 0  <-----CrossConnect----->  Out port 3 vid 300 prio 7 cfi 0
 *  8. In port 2 vid 100 prio 7 cfi 1  <-----CrossConnect----->  Out port 3 vid 300 prio 7 cfi 1
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
#include <opennsl/switch.h>
#include <opennsl/vswitch.h>
#include <opennsl/qos.h>
#include <examples/util.h>


char example_usage[] =
"Syntax: example_qos                                                    \n\r"
"                                                                       \n\r"
"Paramaters: None.                                                      \n\r"
"                                                                       \n\r"
"Example: The following command is used to map the TC and DP from the   \n\r"
"         VLAN tagged packet, with tag ID 100.                          \n\r"
"                                                                       \n\r"
"         example_qos                                                   \n\r"
"                                                                       \n\r"
"Usage Guidelines: None.                                                \n\r";

#define DEFAULT_UNIT 0
#define DEFAULT_VLAN 1
#define MAC_DA        {0x00, 0x00, 0x00, 0x00, 0x00, 0x01}
#define MAC_MASK      {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}

opennsl_vlan_t up_ovlan = 100;
opennsl_vlan_t down_ovlan1 = 200;
opennsl_vlan_t down_ovlan2 = 300;
opennsl_vlan_port_t in_vlan_port1, in_vlan_port2, out_vlan_port1, out_vlan_port2;
opennsl_vswitch_cross_connect_t gports_untag, gports_tag;
int qos_eg_map_id_dft[2];

int pkt_pri[8] = {0,1,2,3,4,5,6,7};
int pkt_cfi[8] = {0,1,0,1,0,1,0,1};
int internal_pri[8] = {1,2,3,4,5,6,7,7};
int internal_color_stag_with_use_de[8] = {0,1,0,1,0,1,0,1};
int internal_color_stag_with_no_use_de[8] = {1,0,1,0,1,0,1,0};
int internal_color_ctag[8] = {0,0,0,0,1,1,1,1};           
         
enum service_type_e {
    match_untag,
    match_otag
};
 
enum use_de_type_e {
    with_no_use_de,
    with_use_de
};
 

/* Map TC and DP from the packet PCP */ 
int qos_pcp_map_create(int unit, int port, int is_use_de) 
{
  int color = 0;
  int mode = 0;
  int rv = OPENNSL_E_NONE;
  int idx;

  /* set the mode of mapping pcp */
  mode = OPENNSL_PORT_DSCP_MAP_NONE;
  rv = opennsl_port_dscp_map_mode_set(unit, -1, mode);    /* global configuration, port has to be -1 */
  if (rv != OPENNSL_E_NONE) 
  {
    printf("error in opennsl_port_dscp_map_mode_set() $rv\n");
    return rv;
  }

  switch (is_use_de) 
  {
    case with_no_use_de:
      /* set the mode of mapping dei without cfi for s tagged pkt */
      rv = opennsl_switch_control_port_set(unit, port, opennslSwitchColorSelect, OPENNSL_COLOR_PRIORITY);
      if (rv != OPENNSL_E_NONE) 
      {
        printf("error in opennsl_switch_control_port_set() $rv\n");
        return rv;
      }

      /* set the mapping of TC and DP for tagged packet */
      for (idx = 0; idx < 8; idx++) 
      {               
        /* map tc and dp from PCP for tagged pkt */
        rv = opennsl_port_vlan_priority_map_set(unit, port, pkt_pri[idx], 0, internal_pri[idx], internal_color_stag_with_no_use_de[idx]);   /* cfi must be 0 because it isn't used */
        if (rv != OPENNSL_E_NONE) 
        {
          printf("error in opennsl_port_vlan_priority_map_set() $rv\n");
          return rv;
        }
      }
      break;
    case with_use_de:
      /* set the mapping of TC for tagged packet */
      for (idx = 0; idx < 8; idx++) 
      {              
        /* map tc from PCP for tagged packet*/
        rv = opennsl_port_vlan_priority_map_set(unit, port, pkt_pri[idx], 0, internal_pri[idx], color); /* cfi must be 0 because it isn't used */
        if (rv != OPENNSL_E_NONE) 
        {
          printf("error in opennsl_port_vlan_priority_map_set() $rv\n");
          return rv;
        }

        /* set the mode of mapping dei with cfi */
        rv = opennsl_switch_control_port_set(unit,port,opennslSwitchColorSelect,OPENNSL_COLOR_OUTER_CFI);
        if (rv != OPENNSL_E_NONE) 
        {
          printf("error in opennsl_switch_control_port_set() $rv\n");
          return rv;
        }

        /* map dei with cfi for s tagged pkt */
        rv = opennsl_port_cfi_color_set(unit, -1, pkt_cfi[idx], internal_color_stag_with_use_de[idx]);  /* global configuration, port has to be -1 */
        if (rv != OPENNSL_E_NONE) 
        {
          printf("error in opennsl_port_cfi_color_set() $rv\n");
          return rv;
        }
      }
      break;
    default:
      return OPENNSL_E_PARAM;    
  }

  /* map up to dp for c tagged pkt */
  for (idx = 0x0; idx < 0x8; idx++) 
  {
    rv = opennsl_port_priority_color_set(unit, port, pkt_pri[idx], internal_color_ctag[idx]);
    if (rv != OPENNSL_E_NONE) 
    {
      printf("error in opennsl_port_priority_color_set() $rv\n");
      return rv;
    }
  }

  return rv;
} 

/* 
 * Create default l2 egress mapping profile.
 * When adding or modifying a new VLAN tag, cos of the new tag is based on the default mapping profile.
 */
int qos_map_l2_eg_dft_profile(int unit, int service_type)
{
  opennsl_qos_map_t l2_eg_map;
  int flags = 0;
  int idx = 0;
  int rv = OPENNSL_E_NONE;

  /* Clear structure */
  rv = opennsl_qos_map_create(unit, OPENNSL_QOS_MAP_EGRESS|OPENNSL_QOS_MAP_L2_VLAN_PCP, &qos_eg_map_id_dft[service_type]);

  if (rv != OPENNSL_E_NONE) 
  {
    printf("error in egress PCP opennsl_qos_map_create() $rv\n");
    return rv;
  }

  for (idx=0; idx<16; idx++) 
  {  
    opennsl_qos_map_t_init(&l2_eg_map);

    /* Set ingress pkt_pri/cfi Priority */
    l2_eg_map.pkt_pri = idx>>1;
    l2_eg_map.pkt_cfi = idx&1;

    /* Set internal priority for this ingress pri */
    l2_eg_map.int_pri = idx>>1;

    /* Set color for this ingress Priority 0:opennslColorGreen 1:opennslColorYellow */
    l2_eg_map.color = idx&1;

    if (service_type == match_untag) 
    {
      flags = OPENNSL_QOS_MAP_L2|OPENNSL_QOS_MAP_L2_VLAN_PCP|OPENNSL_QOS_MAP_L2_UNTAGGED|OPENNSL_QOS_MAP_EGRESS;        
    } 
    else if (service_type == match_otag) 
    {
      flags = OPENNSL_QOS_MAP_L2|OPENNSL_QOS_MAP_L2_VLAN_PCP|OPENNSL_QOS_MAP_L2_OUTER_TAG|OPENNSL_QOS_MAP_EGRESS;
    }

    rv = opennsl_qos_map_add(unit, flags, &l2_eg_map, qos_eg_map_id_dft[service_type]);    
    if (rv != OPENNSL_E_NONE) 
    {
      printf("error in PCP egress opennsl_qos_map_add() $rv\n");
      return rv;
    }  
  }

  return rv;
}

/* edit the eve action, map internal tc and dp to pkt_pri and pkt_cfi */
int initial_qos_service_vlan_action_set(int unit, int service_type)
{
  int rv = OPENNSL_E_NONE;
  opennsl_vlan_port_t *vlan_port = NULL;
  opennsl_vlan_action_set_t action;
  opennsl_vlan_action_set_t_init(&action);

  switch (service_type)
  {
      case match_untag:
          /* eve action for untagged service */
          action.ut_outer = opennslVlanActionAdd;
          action.new_outer_vlan = down_ovlan1;                
          action.ut_outer_pkt_prio = opennslVlanActionAdd;
          action.priority = qos_eg_map_id_dft[service_type];
          vlan_port = &out_vlan_port1;
          break;
      case match_otag:
          /* eve action for tagged service */
          action.ot_outer = opennslVlanActionReplace; 
          action.new_outer_vlan = down_ovlan2;
          action.ot_outer_pkt_prio = opennslVlanActionReplace; /* priority is set according to pcp_vlan_profile mapping */
          action.priority = qos_eg_map_id_dft[match_untag];
          vlan_port = &out_vlan_port2;
          break;
      default:
          return OPENNSL_E_PARAM;
  }

  rv = opennsl_vlan_translate_egress_action_add(unit, vlan_port->vlan_port_id, OPENNSL_VLAN_NONE, OPENNSL_VLAN_NONE, &action);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("error in eve translation opennsl_vlan_translate_egress_action_add() $rv\n");
  }

  return rv;
}


/* initialize the vlan port and set the default egress qos profile
   service model:  untag pkt -> vid 200
                   vid 100 -> vid 300 
*/
int initial_qos_service_init(int unit, opennsl_port_t port_in, opennsl_port_t port_out) 
{
  /* initialize the vlan ports */
  int rv = OPENNSL_E_NONE;
  opennsl_vlan_port_t_init(&in_vlan_port1);
  in_vlan_port1.criteria = OPENNSL_VLAN_PORT_MATCH_PORT;
  in_vlan_port1.port = port_in;
  in_vlan_port1.flags = (OPENNSL_VLAN_PORT_OUTER_VLAN_PRESERVE | OPENNSL_VLAN_PORT_INNER_VLAN_PRESERVE);

  opennsl_vlan_port_t_init(&out_vlan_port1);
  out_vlan_port1.criteria = OPENNSL_VLAN_PORT_MATCH_PORT_VLAN;
  out_vlan_port1.match_vlan = down_ovlan1;
  out_vlan_port1.egress_vlan = down_ovlan1;
  out_vlan_port1.port = port_out;

  opennsl_vlan_port_t_init(&in_vlan_port2);
  in_vlan_port2.criteria = OPENNSL_VLAN_PORT_MATCH_PORT_VLAN;
  in_vlan_port2.match_vlan = up_ovlan;
  in_vlan_port2.egress_vlan = up_ovlan;
  in_vlan_port2.port = port_in;
  in_vlan_port2.flags = (OPENNSL_VLAN_PORT_OUTER_VLAN_PRESERVE | OPENNSL_VLAN_PORT_INNER_VLAN_PRESERVE);

  opennsl_vlan_port_t_init(&out_vlan_port2);
  out_vlan_port2.criteria = OPENNSL_VLAN_PORT_MATCH_PORT_VLAN;
  out_vlan_port2.match_vlan = down_ovlan2;
  out_vlan_port2.egress_vlan = down_ovlan2;
  out_vlan_port2.port = port_out;

  /* set port VLAN domain */
  rv = opennsl_port_class_set(unit, port_in, opennslPortClassId, port_in);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("error in opennsl_port_class_set() $rv\n");
    return rv;
  }

  rv = opennsl_port_class_set(unit, port_out, opennslPortClassId, port_out);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("error in opennsl_port_class_set() $rv\n");
    return rv;
  }

  /* create default egress qos profile */
  qos_map_l2_eg_dft_profile(unit, match_untag);
  qos_map_l2_eg_dft_profile(unit, match_otag);

  return rv;
}

/*
* Set up tagged and untagged sercies, using port cross connect. 
*/ 
int initial_qos_service(int unit)
{
  int rv = OPENNSL_E_NONE;
  opennsl_gport_t in_gport1, in_gport2, out_gport1, out_gport2;
  in_gport1 = 0;
  in_gport2 = 0;
  out_gport1 = 0;    
  out_gport2 = 0;

  /* create inLIF for untagged service */
  rv = opennsl_vlan_port_create(unit, &in_vlan_port1);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("lif_create failed! %s\n", opennsl_errmsg(rv));
    return rv;
  }
  in_gport1 = in_vlan_port1.vlan_port_id;
  printf("%d\n", in_gport1);

  /* create inLIF for tagged service */
  rv = opennsl_vlan_port_create(unit, &in_vlan_port2);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("lif_create failed! %s\n", opennsl_errmsg(rv));
    return rv;
  }
  in_gport2 = in_vlan_port2.vlan_port_id;
  printf("%d\n", in_gport2);

  /* create outLIF for untagged service */
  rv = opennsl_vlan_port_create(unit, &out_vlan_port1);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("lif_create failed! %s\n", opennsl_errmsg(rv));
    return rv;
  }
  out_gport1 = out_vlan_port1.vlan_port_id;
  printf("%d\n", out_gport1);

  /* create outLIF for tagged service */
  rv = opennsl_vlan_port_create(unit, &out_vlan_port2);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("lif_create failed! %s\n", opennsl_errmsg(rv));
    return rv;
  }
  out_gport2 = out_vlan_port2.vlan_port_id;
  printf("%d\n", out_gport2);

  /* add eve action for untagged service */
  initial_qos_service_vlan_action_set(unit, match_untag);
  opennsl_vswitch_cross_connect_t_init(&gports_untag);

  gports_untag.port1 = in_gport1;
  gports_untag.port2 = out_gport1;

  /* cross connect two lifs for untagged service */
  rv = opennsl_vswitch_cross_connect_add(unit, &gports_untag);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("error in opennsl_vswitch_cross_connect_add() $rv\n");
    return rv;
  }

  /* add eve action for tagged service */
  initial_qos_service_vlan_action_set(unit, match_otag);

  opennsl_vswitch_cross_connect_t_init(&gports_tag);
  gports_tag.port1 = in_gport2;
  gports_tag.port2 = out_gport2;

  /* cross connect two lifs for tagged service */
  rv = opennsl_vswitch_cross_connect_add(unit, &gports_tag);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("error in opennsl_vswitch_cross_connect_add() $rv\n");
  }

  return rv;
}

/*
* clean tagged and untagged sercies 
*/
int initial_qos_service_cleanup(int unit)
{
  int rv = OPENNSL_E_NONE;


  gports_untag.port1 = in_vlan_port1.vlan_port_id;
  gports_untag.port2 = out_vlan_port1.vlan_port_id;
  gports_tag.port1 = in_vlan_port2.vlan_port_id;
  gports_tag.port2 = out_vlan_port2.vlan_port_id;

  /* Delete the cross connected LIFs for untagged service */
  rv = opennsl_vswitch_cross_connect_delete(unit, &gports_untag);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, opennsl_vswitch_cross_connect_delete() $rv\n");
    return rv;
  }

  /* Delete the cross connected LIFs for tagged service */
  rv = opennsl_vswitch_cross_connect_delete(unit, &gports_tag);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, opennsl_vswitch_cross_connect_delete() $rv\n");
    return rv;
  }

  /* Delete inLIF for untagged service */
  rv = opennsl_vlan_port_destroy(unit, in_vlan_port1.vlan_port_id);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, opennsl_vlan_port_destroy() $rv\n");
    return rv;
  }

  /* Delete outLIF for untagged service */
  rv = opennsl_vlan_port_destroy(unit, out_vlan_port1.vlan_port_id);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, opennsl_vlan_port_destroy() $rv\n");
    return rv;
  }

  /* Delete inLIF for tagged service */
  rv = opennsl_vlan_port_destroy(unit, in_vlan_port2.vlan_port_id);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, opennsl_vlan_port_destroy() $rv\n");
    return rv;
  }

  /* Delete outLIF for tagged service*/
  rv = opennsl_vlan_port_destroy(unit, out_vlan_port2.vlan_port_id);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("Error, opennsl_vlan_port_destroy() $rv\n");
    return rv;
  }

  /* destroy the qos profile */
  opennsl_qos_map_destroy(unit, qos_eg_map_id_dft[match_untag]);
  opennsl_qos_map_destroy(unit, qos_eg_map_id_dft[match_otag]);

  return rv;        
}


/*****************************************************************//**
 * \brief Main function for QoS application
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
  int inport, outport, use_de;

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

    return rv;
  }

  while(1) {
    printf("\r\nUser menu: Select one of the following options\r\n");
    printf("1. Create QoS mapping\n");
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

        printf("Enter whether to use DEI for QoS mapping(0/1):\n");
        if((example_read_user_choice(&use_de) != OPENNSL_E_NONE) ||
           ((use_de != 0) && (use_de != 1)))
        {
          printf("Invalid value entered. Please re-enter.\n");
          continue;
        }

        rv = initial_qos_service_init(unit, inport, outport); 
        if (rv != OPENNSL_E_NONE) 
        {
          printf("\r\nFailed to initialize the QoS service. Error: %s\r\n",
             opennsl_errmsg(rv));
          break;
	}  

        rv = initial_qos_service(unit); 
        if (rv != OPENNSL_E_NONE) 
        {
          printf("\r\nFailed to start the initial QoS service. Error: %s\r\n",
              opennsl_errmsg(rv));
          break;
        }  

        rv = qos_pcp_map_create(unit, inport, use_de);
        if (rv != OPENNSL_E_NONE) 
        {
          printf("\r\nFailed to create the QoS PCP mapping. Error: %s\r\n",
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
