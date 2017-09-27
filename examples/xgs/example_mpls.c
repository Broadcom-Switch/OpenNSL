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
 * \file         example_mpls.c
 *
 * \brief        OPENNSL example program to demonstrate MPLS
 *
 * \details      This example demonstrates swapping of an incoming MPLS label
 *               in addition to pushing of a new label for MPLS packets.
 *
 *
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sal/driver.h>
#include <opennsl/types.h>
#include <opennsl/error.h>
#include <opennsl/vlan.h>
#include <opennsl/l2.h>
#include <opennsl/l3.h>
#include <opennsl/mpls.h>
#include <examples/util.h>


char example_usage[] =
"Syntax: example_mpls                                                   \n\r"
"                                                                       \n\r"
"Paramaters: None.                                                      \n\r"
"                                                                       \n\r"
"Example: The following command is used to demonstrate MPLS by taking   \n\r"
"         ingress and egress port numbers as input.                     \n\r"
"         example_mpls 5 6                                              \n\r"
"                                                                       \n\r"
"Usage Guidelines: This program request the user to enter the           \n\r"
"                  ingress and egress port numbers.                     \n\r"
"                                                                       \n\r"
"       in_sysport  - Ingress port number on which test packet is       \n\r"
"                     received.                                         \n\r"
"       out_sysport - Egress port number to which packet is forwarded.  \n\r"
"                                                                       \n\r"
"       It looks for MPLS packets arrived on in_sysport with            \n\r"
"       VLAN = 10, destination MAC = 00:00:00:00:11:11 and take the     \n\r"
"       following actions before forwarding the packet to out_sysport.  \n\r"
"                                                                       \n\r"
"       1a) Swap incoming label 200 with 300                            \n\r"
"       1b) Update TTL in this label to 33                              \n\r"
"       2a) Push/Add label 400 with TTL 64                              \n\r"
"                                                                       \n\r";


/* debug prints */
int verbose = 3;


#define DEFAULT_UNIT         0
#define MY_MAC               {0x00, 0x00, 0x00, 0x00, 0x11, 0x11}
#define MAC_SA               {0x00, 0x11, 0x11, 0x11, 0x11, 0x0e}
#define MAC_DA               {0x00, 0x11, 0x11, 0x11, 0x11, 0x0f}

#define VRF_ID               0
#define VPN_ID_OFFSET        (1 << 12)
#define VPN_ID               (VRF_ID + VPN_ID_OFFSET)

#define IN_VLAN              10
#define OUT_VLAN             20

#define L3_OUT_INTF_ID       31

#define INGRESS_LABEL1_ID    200
#define EGRESS_LABEL1_ID     300
#define LABEL1_TTL           33
#define EGRESS_LABEL2_ID     400
#define LABEL2_TTL           64
#define MAX_DIGITS_IN_CHOICE 5

#define CALL_IF_ERROR_RETURN(op)                            \
  do {                                                      \
    int __rv__;                                             \
    if ((__rv__ = (op)) < 0) {                              \
      printf("%s:%s: line %d rv: %d failed: %s\n",          \
          __FILE__, __FUNCTION__, __LINE__, __rv__,         \
          opennsl_errmsg(__rv__));                          \
    }                                                       \
  } while(0)


/* Declarations below */
static int mpls_lsr_term(int unit, int in_sysport, int out_sysport);

/*****************************************************************//**
 * \brief Main function for MPLS sample application
 *
 * \param argc, argv         commands line arguments
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int main(int argc, char *argv[])
{
  int rv = 0;
  int choice;
  int unit = DEFAULT_UNIT;
  int in_sysport;
  int out_sysport;


  if((argc != 3) || ((argc > 1) && (strcmp(argv[1], "--help") == 0))) {
    printf("%s\n\r", example_usage);
    return OPENNSL_E_PARAM;
  }

  /* Initialize the system */
  rv = opennsl_driver_init((opennsl_init_t *) NULL);

  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to initialize the system.\r\n");
    return rv;
  }
  
  /* cold boot initialization commands */
  rv = example_port_default_config(unit);
  if (rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to apply default config on ports, rc = %d (%s).\r\n",
           rv, opennsl_errmsg(rv));
  }

  /* Add ports to default vlan. */
  printf("Adding ports to default vlan.\r\n");
  rv = example_switch_default_vlan_config(unit);
  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to add default ports. Error: %s\r\n",
        opennsl_errmsg(rv));
  }

  /* Extract inputs parameters */
  in_sysport   = atoi(argv[1]);
  out_sysport  = atoi(argv[2]);

  /* Call the MPLS action routine */
  mpls_lsr_term(unit, in_sysport, out_sysport);

  while(1) {
    printf("\r\nUser menu: Select one of the following options\r\n");
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
        rv = opennsl_driver_exit();
        return rv;
      }
      default:
      break;
    } /* End of switch */
  } /* End of while */
  return rv;
}

/**************************************************************************//**
 * \brief Create MPLS flow to swap incoming label and push a second label
 *
 * \param    unit      [IN] Unit number.
 * \param    in_port   [IN] In port.
 * \param    out_port  [IN] Out port.
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
static int mpls_lsr_term(int unit, int in_port, int out_port)
{

  opennsl_vpn_t vpn_type_id;
  opennsl_mpls_vpn_config_t vpn_info;
  opennsl_pbmp_t pbmp, ubmp;
  opennsl_mpls_tunnel_switch_t tunnel_switch;
  opennsl_l3_intf_t l3_intf;
  opennsl_mac_t mac_sa = MAC_SA;
  opennsl_l3_egress_t l3_egress;
  opennsl_gport_t  gport = OPENNSL_GPORT_INVALID;
  opennsl_mac_t mac_da = MAC_DA;
  opennsl_mac_t local_mac = MY_MAC;
  opennsl_if_t egr_obj_1;
  opennsl_mpls_egress_label_t tun_label;

  CALL_IF_ERROR_RETURN(opennsl_switch_control_set(unit,
        opennslSwitchL3EgressMode, 1));

  CALL_IF_ERROR_RETURN(opennsl_port_control_set(unit, out_port,
        opennslPortControlDoNotCheckVlan, 1));

  CALL_IF_ERROR_RETURN(opennsl_port_control_set(unit, in_port,
        opennslPortControlDoNotCheckVlan, 1));

  /*  Create L3 MPLS vpn */
  opennsl_mpls_vpn_config_t_init(&vpn_info);
  vpn_info.flags = OPENNSL_MPLS_VPN_L3 | OPENNSL_MPLS_VPN_WITH_ID;
  vpn_info.vpn = VPN_ID;
  vpn_info.lookup_id = 0;
  CALL_IF_ERROR_RETURN(opennsl_mpls_vpn_id_create(unit, &vpn_info));
  vpn_type_id = vpn_info.vpn;

  if(verbose >= 2) {
    printf("VPN is created with ID: %d\n", vpn_type_id);
  }

  /*  Create Incoming VLAN and ingress port to the incoming VLAN */
  opennsl_vlan_create(unit, IN_VLAN);
  OPENNSL_PBMP_CLEAR(ubmp);
  OPENNSL_PBMP_CLEAR(pbmp);
  OPENNSL_PBMP_PORT_ADD(pbmp, in_port);
  CALL_IF_ERROR_RETURN(opennsl_vlan_port_add(unit, IN_VLAN, pbmp, ubmp));

  if(verbose >= 2) {
    printf("Port %d is added to Ingress VLAN %d\n", in_port, IN_VLAN);
  }

  /*  Create egress VLAN and egress port to the egress VLAN */
  opennsl_vlan_create(unit, OUT_VLAN);
  OPENNSL_PBMP_CLEAR(ubmp);
  OPENNSL_PBMP_CLEAR(pbmp);
  OPENNSL_PBMP_PORT_ADD(pbmp, out_port);
  CALL_IF_ERROR_RETURN(opennsl_vlan_port_add(unit, OUT_VLAN, pbmp, ubmp));

  if(verbose >= 2) {
    printf("Port %d is added to Egress VLAN %d\n", out_port, OUT_VLAN);
  }

  /*  Create outgoing L3 interface */
  opennsl_l3_intf_t_init(&l3_intf);
  l3_intf.l3a_flags  = OPENNSL_L3_WITH_ID;
  l3_intf.l3a_intf_id = L3_OUT_INTF_ID;
  l3_intf.l3a_vid = OUT_VLAN;
  l3_intf.l3a_vrf = VRF_ID;
  memcpy(l3_intf.l3a_mac_addr, mac_sa, sizeof(opennsl_mac_t));
  CALL_IF_ERROR_RETURN(opennsl_l3_intf_create(unit, &l3_intf));

  if(verbose >= 2) {
    printf("\r\nOutgoing L3 interface %d is created with the following "
        "parameters\n", l3_intf.l3a_intf_id);
    printf("    Egress VLAN %d\n", OUT_VLAN);
    l2_print_mac("    MAC address:", mac_sa);
    printf("\r\n");
  }

  /* Create outgoing egress object */
  opennsl_l3_egress_t_init(&l3_egress);
  CALL_IF_ERROR_RETURN(opennsl_port_gport_get(unit, out_port, &gport));
  l3_egress.intf     =  L3_OUT_INTF_ID;
  memcpy(l3_egress.mac_addr, mac_da , sizeof(opennsl_mac_t));
  l3_egress.vlan     =  OUT_VLAN;
  l3_egress.port     =  gport;
  CALL_IF_ERROR_RETURN(opennsl_l3_egress_create(unit, 0, &l3_egress,
        &egr_obj_1));
  if(verbose >= 2) {
    printf("\r\n");
    printf("Outgoing Egress object %d is created with the "
        "following parameters\n", egr_obj_1);
    printf("    Port %d Egress VLAN %d L3 interface %d\n", OUT_VLAN,
        gport, L3_OUT_INTF_ID);
    l2_print_mac("    Next hop MAC address:", mac_da);
    printf("\r\n");
  }

  /*  Add Entry for Incoming label Matching and SWAP */
  opennsl_mpls_tunnel_switch_t_init(&tunnel_switch);
  tunnel_switch.label  =  INGRESS_LABEL1_ID;
  tunnel_switch.port   =  OPENNSL_GPORT_INVALID;
  tunnel_switch.action =  OPENNSL_MPLS_SWITCH_ACTION_SWAP;
  tunnel_switch.vpn =     vpn_type_id;
  tunnel_switch.egress_if = egr_obj_1;
  tunnel_switch.egress_label.flags = OPENNSL_MPLS_EGRESS_LABEL_TTL_SET;
  tunnel_switch.egress_label.label = EGRESS_LABEL1_ID;
  tunnel_switch.egress_label.exp = 0;
  tunnel_switch.egress_label.ttl = LABEL1_TTL;
  tunnel_switch.egress_label.pkt_pri = 0;
  tunnel_switch.egress_label.pkt_cfi = 0;
  CALL_IF_ERROR_RETURN(opennsl_mpls_tunnel_switch_add(unit, &tunnel_switch));

  if(verbose >= 2) {
    printf("\r\n");
    printf("Added entry for incoming label matching and Swap with the "
        "following parameters\n");
    printf("    Incoming label %d (0x%x)\n", INGRESS_LABEL1_ID,
        INGRESS_LABEL1_ID);
    printf("    Action SWAP\n");
    printf("    Egress label: %d (0x%x) TTL: %d\n", EGRESS_LABEL1_ID,
        EGRESS_LABEL1_ID,
        LABEL1_TTL);
  }

  /* Install L2 tunnel MAC */
  CALL_IF_ERROR_RETURN(opennsl_l2_tunnel_add(unit, local_mac, IN_VLAN));

  if(verbose >= 2) {
    printf("\n\r");
    printf("Installed L2 tunnel for Ingress VLAN %d ", IN_VLAN);
    l2_print_mac("MAC address:", local_mac);
    printf("\n\r");
  }

  /* Add MPLS label to packet */
  opennsl_mpls_egress_label_t_init(&tun_label);
  tun_label.flags   =   OPENNSL_MPLS_EGRESS_LABEL_TTL_SET;
  tun_label.label   =   EGRESS_LABEL2_ID;
  tun_label.ttl     =   LABEL2_TTL;
  CALL_IF_ERROR_RETURN(opennsl_mpls_tunnel_initiator_set(unit, L3_OUT_INTF_ID,
        1, &tun_label));
  if(verbose >= 2) {
    printf("Updated tunnel to add MPLS label %d with TTL %d to the packet\n",
        tun_label.label, tun_label.ttl);
  }

  return OPENNSL_E_NONE;
}
