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
 * \file         example_routing.c
 *
 * \brief        OPENNSL example program to demonstrate routing
 *
 * \details      This example demonstrates routing of packets across
 * two different VLAN's by using host route and default routes.
 * In the first case, switch installs a host route to route
 * packets from INGRESS_VLAN, destination MAC = MY_MAC to HOST1
 * attached to EGRESS_VLAN. But, in the second case a default
 * route is installed to route packets from INGRESS_VLAN,
 * destination MAC = MY_MAC destined to DEFAULT_SUBNET_IP to
 * egress port that is a member of EGRESS_VLAN.
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
#include <opennsl/vlan.h>
#include <opennsl/switch.h>
#include <opennsl/l2.h>
#include <opennsl/l3.h>
#include <examples/util.h>

char example_usage[] =
"Syntax: example_routing                                                \n\r"
"                                                                       \n\r"
"Paramaters:                                                            \n\r"
"       in_sysport  - Ingress port number on which test packet is       \n\r"
"                     received                                          \n\r"
"       out_sysport - Egress port number to which packet is routed.     \n\r"
"                                                                       \n\r"
"Example: The following command is used to demonstrate routing from     \n\r"
"         port 2 to port 6.                                             \n\r"
"         example_routing 2 6                                           \n\r"
"                                                                       \n\r"
"Usage Guidelines: This program request the user to enter the           \n\r"
"       ingress and egress port numbers. Using the host route, it routes\n\r"
"       the packets arrived on ingress port with VLAN = 10,             \n\r"
"       destination MAC = 00:11:22:33:99:58 to host 20.1.1.2 attached   \n\r"
"       to egress port that is a member of VLAN 20. Using the default   \n\r"
"       route, it also routes packets with VLAN = 10, destination       \n\r"
"       MAC = 00:11:22:33:99:58 destinated to subnet 55.0.0.0 to egress \n\r"
"       port that is a member of VLAN 20.                               \n\r"
"       The routed packet should have destination MAC same as           \n\r"
"       00:00:70:5B:C7:34 with TTL decremented by 1.                    \n\r";


#define INGRESS_VLAN    10
#define EGRESS_VLAN     20
#define HOST1           0x14010102         /* 20.1.1.2 */
#define DEFAULT_SUBNET_IP   0x37000000     /* 55.0.0.0 */
#define DEFAULT_SUBNET_MASK 0xff000000     /* /8 network */
#define MY_MAC          {0x00, 0x11, 0x22, 0x33, 0x99, 0x58}
#define NEXTHOP_MAC     {0x00, 0x00, 0x70, 0x5B, 0xC7, 0x34}
#define MAX_DIGITS_IN_CHOICE 5

/* debug prints */
int verbose = 3;

/**************************************************************************//**
 * \brief To add a given MAC and VID to the L2 forwarding database.
 *
 *
 * \param    unit [IN]    Unit number.
 * \param    mac  [IN]    MAC address
 * \param    port [IN]    Port number
 * \param    vid  [IN]    VLAN identifier
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
int example_l2_addr_add(int unit, opennsl_mac_t mac, int port, int vid) {

  int rv;
  opennsl_l2_addr_t l2addr;

  opennsl_l2_addr_t_init(&l2addr, mac, vid);
  l2addr.port  = port;
  l2addr.flags = (OPENNSL_L2_L3LOOKUP | OPENNSL_L2_STATIC);

  rv = opennsl_l2_addr_add(unit, &l2addr);
  if (rv != OPENNSL_E_NONE) {
    return rv;
  }

  return OPENNSL_E_NONE;
}

/**************************************************************************//**
 * \brief To add a port to the VLAN
 *
 *
 * \param    unit       [IN]    Unit number.
 * \param    open_vlan  [IN]    if TRUE create given vlan, FALSE: vlan already
 *                              opened juts use it
 * \param    vlan       [IN]    VLAN identifier
 * \param    port       [IN]    Port number
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
int example_vlan_port_add(int unit, int open_vlan,
    opennsl_vlan_t vlan, int port)
{
  opennsl_pbmp_t  pbmp, upbmp;
  int rc = OPENNSL_E_NONE;

  if(open_vlan) {
    rc = opennsl_vlan_create(unit, vlan);
    if (rc != OPENNSL_E_NONE) {
      printf("failed to create vlan(%d). Return code %s",
          vlan, opennsl_errmsg(rc));
      return rc;
    }
    if(verbose >= 3) {
      printf("Created VLAN: %d\n", vlan);
    }
  }

  /* Add the test ports to the vlan */
  OPENNSL_PBMP_CLEAR(pbmp);
  OPENNSL_PBMP_CLEAR(upbmp);
  OPENNSL_PBMP_PORT_ADD(pbmp, port);
  rc = opennsl_vlan_port_add(unit, vlan, pbmp, upbmp);
  if (rc != OPENNSL_E_NONE && rc != OPENNSL_E_EXISTS) {
    return rc;
  }
  return rc;
}

/**************************************************************************//**
 * \brief Creates Router interface
 *       - packets sent in from this interface identified by <port, vlan> with
 *         specificed MAC address is subject of routing
 *       - packets sent out through this interface will be encapsulated with
 *         <vlan, mac_addr>
 *
 *
 * \param    unit       [IN]    Unit number.
 * \param    open_vlan  [IN]    if TRUE create given vlan, FALSE: vlan already
 *                              opened juts use it
 * \param    port       [IN]    Port number
 * \param    vid        [IN]    router interface VLAN
 * \param    mac_addr   [IN]    my MAC address
 * \param    l3_id      [OUT]   returned handle of opened l3-interface
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
int example_create_l3_intf(int unit, int open_vlan, opennsl_gport_t port,
    opennsl_vlan_t vid, opennsl_mac_t mac_addr, int *l3_id) {

  int rc;
  opennsl_l3_intf_t l3_intf;

  /* Create VLAN and add port to the VLAN membership */
  rc = example_vlan_port_add(unit, open_vlan, vid, port);
  if (rc != OPENNSL_E_NONE && rc != OPENNSL_E_EXISTS) {
    printf("Fail to add port %d to vlan %d. Return Code: %s\n", port, vid, opennsl_errmsg(rc));
    return rc;
  }
  if(verbose >= 2) {
    printf("Port %d is participating in VLAN: %d\n", port, vid);
  }

  /* Create L3 interface */
  opennsl_l3_intf_t_init(&l3_intf);
  memcpy(l3_intf.l3a_mac_addr, mac_addr, 6);
  l3_intf.l3a_vid = vid;
  rc = opennsl_l3_intf_create(unit, &l3_intf);
  if (rc != OPENNSL_E_NONE) {
    printf("l3_setup: opennsl_l3_intf_create failed: %s\n", opennsl_errmsg(rc));
    return rc;
  }

  *l3_id = l3_intf.l3a_intf_id;

  if(verbose >= 3) {
    printf("L3 interface is created with parameters: \n  VLAN %d \n", vid);
    l2_print_mac("  MAC Address: ", mac_addr);
    printf("\n\r");
    printf("  L3 Interface ID: %d\r\n", l3_intf.l3a_intf_id);
  }

  return rc;
}

/**************************************************************************//**
 * \brief create l3 egress object
 *       object includes next hop information.
 *       - packets sent to this interface will be send through out_port over
 *         given l3_eg_intf with next next_hop_mac_addr VLAN. SA is driven from
 *         l3_eg_intf as configure in example_create_l3_intf().
 *
 *
 * \param    unit              [IN]    Unit number
 * \param    flags             [IN]    special controls set to zero
 * \param    out_port          [IN]    egress port
 * \param    vlan              [IN]    VLAN identifier
 * \param    l3_eg_intf        [IN]    egress router interface will
 *                                     derive (VLAN, SA)
 * \param    next_hop_mac_addr [IN]    next hop mac address
 * \param    *intf             [OUT]   returned interface ID
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 ******************************************************************************/
int example_create_l3_egress(int unit, unsigned int flags, int out_port, int vlan,
    int l3_eg_intf, opennsl_mac_t next_hop_mac_addr,
    int *intf) {
  int rc;
  opennsl_l3_egress_t l3eg;
  opennsl_if_t l3egid;
  int mod = 0;

  opennsl_l3_egress_t_init(&l3eg);
  l3eg.intf = l3_eg_intf;
  memcpy(l3eg.mac_addr, next_hop_mac_addr, 6);

  l3eg.vlan   = vlan;
  l3eg.module = mod;
  l3eg.port   = out_port;

  l3egid = *intf;

  rc = opennsl_l3_egress_create(unit, flags, &l3eg, &l3egid);
  if (rc != OPENNSL_E_NONE) {
    return rc;
  }

  *intf = l3egid;

  if(verbose >= 2) {
    printf("Created L3 egress ID %d for out_port: %d vlan: %d "
        "L3 egress intf: %d\n",
        *intf, out_port, vlan, l3_eg_intf);
  }

  return rc;
}

/**************************************************************************//**
 * \brief Add host address to the routing table
 *
 * \param    unit [IN]    Unit number.
 * \param    addr [IN]    32 bit IP address value
 * \param    intf [IN]    egress object created using example_create_l3_egress
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
int example_add_host(int unit, unsigned int addr, int intf) {
  int rc;
  opennsl_l3_host_t l3host;
  opennsl_l3_host_t_init(&l3host);

  l3host.l3a_flags = 0;
  l3host.l3a_ip_addr = addr;
  l3host.l3a_intf = intf;
  l3host.l3a_port_tgid = 0;

  rc = opennsl_l3_host_add(unit, &l3host);
  if (rc != OPENNSL_E_NONE) {
    printf ("opennsl_l3_host_add failed. Return Code: %s \n",
        opennsl_errmsg(rc));
    return rc;
  }

  if(verbose >= 1) {
    print_ip_addr("add host ", addr);
    printf(" ---> egress-object = %d\n", intf);
  }

  return rc;
}

/**************************************************************************//**
 * \brief Add default route to a subnet
 *
 * \param    unit      [IN] Unit number.
 * \param    subnet    [IN] 32 bit IP subnet
 * \param    mask      [IN] 32 bit value network mask
 * \param    intf      [IN] Egress object created using example_create_l3_egress
 * \param    trap_port [IN] Trap destination. if trap_port is valid trap then it
 *                         used for default destination. otherwise intf
 *                         (egress-object) is used
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
int example_set_default_route(int unit, int subnet, int mask,
    int intf, opennsl_gport_t trap_port) {
  int rc;
  opennsl_l3_route_t l3rt;

  opennsl_l3_route_t_init(&l3rt);

  l3rt.l3a_flags = 0;

  /* to indicate it's default route, set subnet to zero */
  l3rt.l3a_subnet = subnet;
  l3rt.l3a_ip_mask = mask;

  l3rt.l3a_intf = intf;
  l3rt.l3a_port_tgid = trap_port;

  rc = opennsl_l3_route_add(unit, &l3rt);
  if (rc != OPENNSL_E_NONE) {
    printf ("opennsl_l3_route_add failed. Return Code: %s \n",
        opennsl_errmsg(rc));
    return rc;
  }

  if(verbose >= 1) {
    print_ip_addr("add default route for subnet ", subnet);
    print_ip_addr(" with mask ", mask);
    printf(" ---> egress-object = %d\n", intf);
  }
  return rc;
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
  int ing_intf_in = 0;
  int ing_intf_out = 0;
  int l3egid;
  int flags = 0;
  int open_vlan = 1;
  int in_sysport;
  int out_sysport;
  int in_vlan  = INGRESS_VLAN;
  int out_vlan = EGRESS_VLAN;
  int host, subnet, mask;
  opennsl_mac_t my_mac  = MY_MAC;  /* my-MAC */
  opennsl_mac_t next_hop_mac  = NEXTHOP_MAC; /* next_hop_mac1 */
  unsigned int warm_boot;
  int index = 0;

  if(strcmp(argv[0], "gdb") == 0)
  {
    index = 1;
  }
  if((argc != (index + 3)) || ((argc > (index + 1)) 
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

  /* Extract inputs parameters */
  in_sysport   = atoi(argv[index + 1]);
  out_sysport  = atoi(argv[index + 2]);

  warm_boot = opennsl_driver_boot_flags_get() & OPENNSL_BOOT_F_WARM_BOOT;

  if(!warm_boot)
  {
    /* Set L3 Egress Mode */
    rv =  opennsl_switch_control_set(unit, opennslSwitchL3EgressMode, 1);
    if (rv != OPENNSL_E_NONE) {
      return rv;
    }
    if(verbose >= 3) {
      printf("\nL3 Egress mode is set succesfully\n");
    }

    /*** create ingress router interface ***/
    rv = example_create_l3_intf(unit, open_vlan, in_sysport, in_vlan,
        my_mac, &ing_intf_in);
    if (rv != OPENNSL_E_NONE) {
      printf("Error, create ingress interface-1, in_sysport=%d. "
          "Return code %s \n", in_sysport, opennsl_errmsg(rv));
      return rv;
    }

    /*** create egress router interface ***/
    rv = example_create_l3_intf(unit, open_vlan, out_sysport, out_vlan,
        my_mac, &ing_intf_out);
    if (rv != OPENNSL_E_NONE) {
      printf("Error, create egress interface-1, out_sysport=%d. "
          "Return code %s \n", out_sysport, opennsl_errmsg(rv));
      return rv;
    }

    /*** Make the address learn on a VLAN and port */
    rv = example_l2_addr_add(unit, my_mac, in_sysport, in_vlan);
    if (rv != OPENNSL_E_NONE) {
      printf("Failed to add L2 address. Return Code: %s\n", opennsl_errmsg(rv));
      return rv;
    }

    rv = example_l2_addr_add(unit, my_mac, out_sysport, out_vlan);
    if (rv != OPENNSL_E_NONE) {
      printf("Failed to add L2 address. Return Code: %s\n", opennsl_errmsg(rv));
      return rv;
    }

    /*** create egress object 1 ***/
    flags = 0;
    rv = example_create_l3_egress(unit, flags, out_sysport, out_vlan, ing_intf_out,
        next_hop_mac, &l3egid);
    if (rv != OPENNSL_E_NONE) {
      printf("Error, create egress object, out_sysport=%d. Return code %s \n",
          out_sysport, opennsl_errmsg(rv));
      return rv;
    }

    /*** add host point ***/
    host = HOST1;
    rv = example_add_host(unit, host, l3egid);
    if (rv != OPENNSL_E_NONE) {
      printf("Error, host add. Return code %s\n",
          opennsl_errmsg(rv));
      return rv;
    }


    /* With ALPM enabled, switch expects a default route to be 
     installed before adding a LPM route */
    subnet = 0x00000000;
    mask   = 0x00000000;
    rv = example_set_default_route(unit, subnet, mask, l3egid, 0);
    if (rv != OPENNSL_E_NONE) {
      printf("Error, default route add. Return code %s \n",
          opennsl_errmsg(rv));
      return rv;
    }

    /*** add default route ***/
    subnet = DEFAULT_SUBNET_IP;
    mask   = DEFAULT_SUBNET_MASK;
    rv = example_set_default_route(unit, subnet, mask, l3egid, 0);
    if (rv != OPENNSL_E_NONE) {
      printf("Error, default route add. Return code %s\n",
          opennsl_errmsg(rv));
      return rv;
    }
  }

  while(1) {
    printf("\r\nUser menu: Select one of the following options\r\n");
    printf("1. Save the configuration to scache\n");
    printf("9. Launch diagnostic shell\n");
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

      case 9:
      {
        opennsl_driver_shell();
        break;
      }

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
