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


#define DEFAULT_UNIT         0
#define INGRESS_VLAN         10
#define EGRESS_VLAN          20
#define HOST1                0x14010102     /* 20.1.1.2 */
#define MY_MAC               {0x00, 0x11, 0x22, 0x33, 0x99, 0x58}
#define NEXTHOP_MAC          {0x00, 0x00, 0x70, 0x5B, 0xC7, 0x34}
#define DEFAULT_SUBNET_IP    0x37000000         /* 55.0.0.0 */
#define DEFAULT_SUBNET_MASK  0xff000000         /* /8 network */

/**************************************************************************//**
 * \brief To print the host entry
 *
 * \param    type       [IN]    string header
 * \param    host       [IN]    IPV4 host address
 * \param    vrf        [IN]    VRF ID
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
void print_host(char *type, opennsl_ip_t host, int vrf)
{
  printf("%s  vrf : %d   ", type, vrf);
  print_ip_addr("", host);
}

/**************************************************************************//**
 * \brief To print the route entry
 *
 * \param    type       [IN]    string header
 * \param    addr       [IN]    IPV4 host address
 * \param    mask       [IN]    IPV4 mask
 * \param    vrf        [IN]    VRF ID
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
void print_route(char *type, uint32 addr, uint32 mask, int vrf)
{
  printf("%s  vrf : %d   ", type, vrf);
  print_ip_addr("", addr);
  printf("/");
  print_ip_addr("", mask);
}

/**************************************************************************//**
 * \brief To add host based route
 *
 *
 * \param    unit       [IN]    Unit number.
 * \param    addr       [IN]    IPV4 host address
 * \param    vrf        [IN]    VRF ID
 * \param    intf       [IN]    egress interface
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
int example_host_add(int unit, uint32 addr, int vrf, int intf)
{
    int rc;
    opennsl_l3_host_t l3host;

    opennsl_l3_host_t_init(&l3host);

    l3host.l3a_flags = 0;
    l3host.l3a_ip_addr = addr;
    l3host.l3a_vrf = vrf;
    l3host.l3a_intf = intf;
    l3host.l3a_port_tgid = 0;

    rc = opennsl_l3_host_add(unit, &l3host);
    if (rc != OPENNSL_E_NONE) {
      printf ("opennsl_l3_host_add failed: %x \n", rc);
    }

    return rc;
}

/**************************************************************************//**
 * \brief To add subnet based route
 *
 *
 * \param    unit       [IN]    Unit number.
 * \param    addr       [IN]    IPV4 host address
 * \param    mask       [IN]    IPV4 mask. 1: to consider 0: to ingore, for 
 *                              example for /24 mask = 0xffffff00
 * \param    vrf        [IN]    VRF ID
 * \param    intf       [IN]    egress interface
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
int example_route_add(int unit, uint32 addr, uint32 mask, int vrf, int intf) {
  int rc;
  opennsl_l3_route_t l3rt;

  opennsl_l3_route_t_init(&l3rt);

  l3rt.l3a_flags = 0;
  l3rt.l3a_subnet = addr;
  l3rt.l3a_ip_mask = mask;
  l3rt.l3a_vrf = vrf;
  l3rt.l3a_intf = intf;
  l3rt.l3a_port_tgid = 0;

  rc = opennsl_l3_route_add(unit, &l3rt);
  if (rc != OPENNSL_E_NONE) {
    printf ("opennsl_l3_route_add failed: %x \n", rc);
  }

  print_route("add route", addr, mask, vrf);
  printf("---> egress-object=0x%08x, \n", intf);

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
 * \param    flags      [IN]    Flags
 * \param    port       [IN]    Port number
 * \param    vlan       [IN]    VLAN ID
 * \param    vrf        [IN]    Virtual Router Interface ID
 * \param    mac_addr   [IN]    my MAC address
 * \param    ttl        [IN]    Time To Live field value
 * \param    intf       [OUT]   returned handle of opened l3-interface
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
int example_create_l3_intf(int unit, uint32 flags, opennsl_gport_t port, int vlan,
    int vrf, opennsl_mac_t mac_addr, int ttl, int *intf)
{
  int rc, station_id;
  opennsl_l3_intf_t l3if;
  opennsl_l3_ingress_t l3_ing_if;
  opennsl_l2_station_t station;

  opennsl_l3_intf_t_init(&l3if);
  opennsl_l3_ingress_t_init(&l3_ing_if);
  opennsl_l2_station_t_init(&station);

  /* set my-Mac global MSB */
  station.flags = 0;
  memcpy(station.dst_mac, mac_addr, 6);
  station.vlan_mask = 0; /* vsi is not valid */
  station.dst_mac_mask[0] = 0xff; /* dst_mac my-Mac MSB mask is -1 */
  station.dst_mac_mask[1] = 0xff;
  station.dst_mac_mask[2] = 0xff;
  station.dst_mac_mask[3] = 0xff;
  station.dst_mac_mask[4] = 0xff;
  station.dst_mac_mask[5] = 0xff;

  rc = opennsl_l2_station_add(unit, &station_id, &station);
  if (rc != OPENNSL_E_NONE) {
    return rc;
  }

  rc = opennsl_vlan_create(unit, vlan);
  if (rc == OPENNSL_E_EXISTS) {
    printf("vlan (%d) already exists", vlan);
  }
  else if (rc != OPENNSL_E_NONE) {
    printf("fail open vlan (%d)", vlan);
    printf("    continue..\n");
  }

  rc = opennsl_vlan_gport_add(unit, vlan, port, 0);
  if (rc != OPENNSL_E_NONE) {
    printf("fail add port(0x%08x) to vlan(%d)\n", port, vlan);
    return rc;
  }

  memcpy(l3if.l3a_mac_addr, mac_addr, 6);
  l3if.l3a_vid = vlan;
  l3if.l3a_ttl = ttl;
  l3if.l3a_mtu = 1524;
  l3if.l3a_flags = flags;
  l3if.l3a_intf_id = *intf;

  rc = opennsl_l3_intf_create(unit, &l3if);
  if (rc != OPENNSL_E_NONE) {
    return rc;
  }
  *intf = l3if.l3a_intf_id;

  l3_ing_if.flags = OPENNSL_L3_INGRESS_WITH_ID | OPENNSL_L3_INGRESS_GLOBAL_ROUTE; /* must, as we update exist RIF */
  l3_ing_if.vrf = vrf;

  rc = opennsl_l3_ingress_create(unit, &l3_ing_if, &l3if.l3a_intf_id);
  if (rc != OPENNSL_E_NONE) {
    return rc;
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
 * \param    nhop_mac_addr     [IN]    next hop mac address
 * \param    *intf             [OUT]   returned interface ID
 * \param    *encap_id         [OUT]   returned encapsulation ID
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 ******************************************************************************/
int example_create_l3_egress(int unit, uint32 flags, int out_port, int vlan,
    int l3_eg_intf, opennsl_mac_t nhop_mac_addr, int *intf, int *encap_id)
{
  int rc;
  opennsl_l3_egress_t l3eg;
  opennsl_if_t l3egid;
  int mod = 0;

  opennsl_l3_egress_t_init(&l3eg);

  l3eg.intf = l3_eg_intf;
  memcpy(l3eg.mac_addr, nhop_mac_addr, 6);
  l3eg.vlan     = vlan;
  l3eg.module   = mod;
  l3eg.port     = out_port;
  l3eg.encap_id = *encap_id;
  l3egid        = *intf;
  l3eg.flags    = flags;

  rc = opennsl_l3_egress_create(unit, flags, &l3eg, &l3egid);
  if (rc != OPENNSL_E_NONE) {
    printf("Error, create egress object, out_port = %d, \n", out_port);
    return rc;
  }
  *encap_id = l3eg.encap_id;
  *intf = l3egid;

  return rc;
}

/**************************************************************************//**
 * \brief To setup host based IPv4 route
 *
 * \param    unit       [IN]    Unit number.
 * \param    in_port    [IN]    Incoming Port number
 * \param    out_port   [IN]    Outgoing Port number
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
int example_ipv4_route_setup(int unit, int in_port, int out_port)
{
  int rv;
  int ing_intf_in;
  int ing_intf_out;
  int fec[2];
  int encap_id[2];
  int flags = 0;
  int in_vlan = INGRESS_VLAN;
  int out_vlan = EGRESS_VLAN;
  int vrf = 0;
  opennsl_mac_t my_mac_address  = MY_MAC;
  opennsl_mac_t next_hop_mac    = NEXTHOP_MAC;
  uint32 host = HOST1;

  /*** create ingress router interface ***/
  rv = example_create_l3_intf(unit, flags, in_port, in_vlan, vrf, my_mac_address, 62, &ing_intf_in);
  if (rv != OPENNSL_E_NONE) {
    printf("Error, create ingress interface, in_port = %d, \n", in_port);
  }
  printf("---> Ingress router intf = 0x%08x created on port %d\n", ing_intf_in, in_port);

  /*** create egress router interface ***/
  rv = example_create_l3_intf(unit, flags, out_port, out_vlan, vrf, my_mac_address, 62, &ing_intf_out);
  if (rv != OPENNSL_E_NONE) {
    printf("Error, create ingress enterface, out_port = %d, \n", out_port);
  }
  printf("---> Ingress router intf = 0x%08x created on port %d\n", ing_intf_out, out_port);

  /*** create egress object 1 ***/
  fec[0] = 0;
  encap_id[0] = 0;
  /* built FEC points to out-RIF and MAC address */
  rv = example_create_l3_egress(unit, flags, out_port, out_vlan, ing_intf_out,
      next_hop_mac, &fec[0], &encap_id[0]);
  if (rv != OPENNSL_E_NONE) {
    printf("Error, create egress object, out_port = %d, \n", out_port);
  }
  printf("---> Egress interface = 0x%08x, \n", ing_intf_out);
  printf("     created FEC-id = 0x%08x, \n", fec[0]);
  printf("     next hop mac at encap-id %08x, \n", encap_id[0]);

  /*** add IPV4 host entry with OUT-RIF + MAC + eg-port ***/
  rv = example_host_add(unit, host, vrf, fec[0]);
  if (rv != OPENNSL_E_NONE) {
    printf("Error, example_host_add\n");
  }

  print_host("add host ", host, vrf);
  printf("---> egress-intf = 0x%08x, port = %d, \n", ing_intf_out, out_port);

  /*** add route point to FEC2 ***/
  int route = DEFAULT_SUBNET_IP;
  int mask  = DEFAULT_SUBNET_MASK;

  rv = example_route_add(unit, route, mask, vrf, fec[0]) ;
  if (rv != OPENNSL_E_NONE) {
    printf("Error, failed to add route\n");
    return rv;
  }

  return rv;
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
  int choice;
  int in_sysport;
  int out_sysport;
  int index = 0;
  int unit = DEFAULT_UNIT;

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

  rv = example_port_default_config(unit);
  if (rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to apply default config on ports, rc = %d (%s).\r\n",
        rv, opennsl_errmsg(rv));
  }

  rv = example_ipv4_route_setup(0, in_sysport, out_sysport);
  if (rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to configure routing, rc = %d (%s).\r\n",
        rv, opennsl_errmsg(rv));
  }

  while(1) {
    printf("\r\nUser menu: Select one of the following options\r\n");
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

  return rv;
}
