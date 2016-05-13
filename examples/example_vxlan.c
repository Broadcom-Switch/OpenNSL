/******************************************************************************
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
 ******************************************************************************
 * \file     example_vxlan.c
 *
 * \brief    Example code for VxLAN application
 *
 * VXLAN is a L2 VPN technology targeted for Data-Center communication 
 * between Virtual Machines (VM) assigned to the same customer(Tenant) that are 
 * distributed in various racks in the Data-Center. L2VPN over IP/UDP tunnels can provide 
 * E-LAN (similar to VPLS) and E-LINE (similar to VPWS) service. With VXLAN the ethernet 
 * packets are encapsulated in UDP tunnels over an IP network. VXLAN uses UDP Source_Port
 * as multiplexing field for multiplexing multiple VPNs into the same UDP Tunnel.
 * E-LINE is point-to-point service without support for Multicast traffic. In E-LINE, Ethernet
 * frames are mapped into a VXLAN Tunnel based on incoming port plus packet header information. 
 * At the end of Tunnel, forwarding of Ethernet frames after Tunnel decapsulation is based on 
 * VXLAN-VNID and Tunnel lookup.
 *
 * In E-LAN, Ethernet frames of interest are also identified by incoming port plus packet 
 * header information. Ethernet frames are switched into one or more VXLAN Tunnels based 
 * on the MAC DA lookup.  At the end of  Tunnel, forwarding of Ethernet frames after Tunnel 
 * decapsulation is based on the VXLAN-VNID and Tunnel lookup and frames are again forwarded 
 * based on MAC-DA lookup.
 *
 * VXLAN VPN can be of type ELINE or ELAN.
 *
 * For ELAN, a VPN is similar to a VLAN, which identifies a group of physical ports to be 
 * included in a broadcast domain. However, instead of physical ports, a ELAN VPN identifies 
 * a group of "virtual-ports" to be included in a broadcast domain. In the VXLAN APIs, 
 * a "virtual-port" is called an VXLAN port (see description below). The VPN ID is used to 
 * qualify MAC DA lookups within the VPN.
 *
 * For ELINE, a VPN consists of two VXLAN ports. Packets arriving on one VXLAN port are sent 
 * directly out the other VXLAN port.
 *
 * This example application creates 2 VxLAN segments, and two access ports that share 1 tunnel:
 *
 *   Access Port1 --> Segment 1 (VPN 1) \
 *                                       +-> share 1 network UDP tunnel
 *   Access Port2 --> Segment 2 (VPN 2) /
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sal/driver.h>
#include <opennsl/error.h>
#include <opennsl/l2.h>
#include <opennsl/switch.h>
#include <opennsl/vlan.h>
#include <opennsl/tunnel.h>
#include <opennsl/multicast.h>
#include <opennsl/vxlan.h>
#include <examples/util.h>

#define DEFAULT_UNIT  0
#define DEFAULT_VLAN  1
#define MAX_DIGITS_IN_CHOICE 5

char example_usage[] =
"Syntax: example_vxlan                                                 \n\r"
"                                                                      \n\r"
"Paramaters: None.                                                     \n\r"
"                                                                      \n\r"
"Usage Guidelines: None.                                               \n\r";

/* debug prints */
int verbose = 3;

#define TRUE  1
#define FALSE 0
#define VXLAN_UDP_DEST_PORT 4789

/*****************************************************************//**
 * \brief Apply global VXLAN settings for the switch device
 *
 * \param unit      [IN]    Unit number
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
static int do_vxlan_global_setting(int unit)
{
  /* Enable L3 Egress Mode */
  OPENNSL_IF_ERROR_RETURN
    (opennsl_switch_control_set(unit, opennslSwitchL3EgressMode, TRUE));

  /* Set UDP destination port for VXLAN */
  OPENNSL_IF_ERROR_RETURN
    (opennsl_switch_control_set(unit, opennslSwitchVxlanUdpDestPortSet,
                                VXLAN_UDP_DEST_PORT));

  /* Enable UDP Source port based HASH for VXLAN */
  OPENNSL_IF_ERROR_RETURN
    (opennsl_switch_control_set(unit, opennslSwitchVxlanEntropyEnable, TRUE));

  /* Enable VXLAN Tunnel lookup failure settings to send packets to CPU. */
  OPENNSL_IF_ERROR_RETURN
    (opennsl_switch_control_set(unit, opennslSwitchVxlanTunnelMissToCpu, TRUE));

  /* Enable VXLAN VN_ID lookup failure settings to send packets to CPU. */
  OPENNSL_IF_ERROR_RETURN
    (opennsl_switch_control_set(unit, opennslSwitchVxlanVnIdMissToCpu, TRUE));

  return OPENNSL_E_NONE;
}

/*****************************************************************//**
 * \brief Setup configuration on access port
 *
 * \param unit      [IN]    Unit number
 * \param a_port    [IN]    Port number
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
static int do_vxlan_access_port_settings(int unit, opennsl_port_t a_port)
{
  /* Should disable Vxlan Processing on access port. VXLAN encapsulated packets are  
   * not expected on the access port.
   */
  OPENNSL_IF_ERROR_RETURN
    (opennsl_port_control_set(unit, a_port, opennslPortControlVxlanEnable, FALSE));

  /* Should disable Tunnel Based Vxlan-VnId lookup */
  OPENNSL_IF_ERROR_RETURN
    (opennsl_port_control_set(unit, a_port, opennslPortControlVxlanTunnelbasedVnId, FALSE));

  /* Should Enable VLAN translation if access port uses 802.1Q or QinQ */
  opennsl_vlan_control_set(unit, opennslVlanTranslate, TRUE);

  return OPENNSL_E_NONE;
}

/*****************************************************************//**
 * \brief Setup configuration on network port
 *
 * \param unit      [IN]    Unit number
 * \param n_port    [IN]    Port number
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
static int do_vxlan_net_port_settings(int unit, opennsl_port_t n_port)
{
  /* Enable VXLAN Processing on network port */
  OPENNSL_IF_ERROR_RETURN
    (opennsl_port_control_set(unit, n_port, opennslPortControlVxlanEnable, TRUE));

  /* Allow tunnel based VXLAN-VNID lookup */
  OPENNSL_IF_ERROR_RETURN
    (opennsl_port_control_set(unit, n_port, opennslPortControlVxlanTunnelbasedVnId, FALSE));

  /* Enable Default SVP on network side */
  OPENNSL_IF_ERROR_RETURN
    (opennsl_port_control_set(unit, n_port, opennslPortControlVxlanDefaultTunnelEnable, 0));

  return OPENNSL_E_NONE;
}

/*****************************************************************//**
 * \brief Create the ELAN VPN based on the given VPN ID and VN_ID
 *
 * \param unit      [IN]    Unit number
 * \param vpnd_id   [IN]    VPN Identifier
 * \param vnid      [IN]    VxLAN network Identifier
 * \param bc        [IN]    Broadcast group Identifier
 * \param mc        [IN]    Multicast group Identifier
 * \param uuc       [IN]    Unknown Unicast group Identifier
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
static int create_vxlan_vpn(int unit, int vpn_id, int vnid, opennsl_multicast_t bc,
                            opennsl_multicast_t mc, opennsl_multicast_t uuc)
{
  opennsl_vxlan_vpn_config_t vpn_info;
  opennsl_error_t rv = OPENNSL_E_NONE;

  opennsl_vxlan_vpn_config_t_init(&vpn_info);
  vpn_info.flags = OPENNSL_VXLAN_VPN_ELAN | OPENNSL_VXLAN_VPN_WITH_ID |
                   OPENNSL_VXLAN_VPN_WITH_VPNID;
  vpn_info.vpn  = vpn_id;
  vpn_info.vnid = vnid;
  vpn_info.broadcast_group         = bc;
  vpn_info.unknown_multicast_group = mc;
  vpn_info.unknown_unicast_group   = uuc;
  rv = opennsl_vxlan_vpn_create(unit, &vpn_info);

  if (rv != OPENNSL_E_NONE)
  {
    printf("create_vxlan_vpn: failed to create VXLAN VPN rv %d\n", rv);
  }
  return rv;
}


/*****************************************************************//**
 * \brief Create an access virtual port based on the physical port,
 *        egress nexthop and VPN ID
 *
 * \param unit      [IN]    Unit number
 * \param vpn       [IN]    VPN Identifier
 * \param flags     [IN]    Flags
 * \param port      [IN]    Port number
 * \param criteria  [IN]    Match Criteria
 * \param egr_obj   [IN]    Egress object information
 * \param vid       [IN]    VLAN identifier
 * \param vp        [OUT]   To store virtual port handle
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
static int create_vxlan_acc_vp(int unit, opennsl_vpn_t vpn, uint32 flags, 
                               opennsl_gport_t port,
                               opennsl_vxlan_port_match_t criteria,
                               opennsl_if_t egr_obj, opennsl_vlan_t vid, 
                               opennsl_gport_t *vp)
{
  opennsl_vxlan_port_t vxlan_port;
  opennsl_error_t rv = OPENNSL_E_NONE;

  opennsl_vxlan_port_t_init(&vxlan_port);
  vxlan_port.flags = OPENNSL_VXLAN_PORT_SERVICE_TAGGED | flags;
  vxlan_port.match_port =        port;
  vxlan_port.criteria =          criteria;
  vxlan_port.egress_if =         egr_obj;
  vxlan_port.match_vlan =        vid;
  rv = opennsl_vxlan_port_add(unit, vpn, &vxlan_port);
  *vp = vxlan_port.vxlan_port_id;

  if (rv != OPENNSL_E_NONE)
  {
    printf("create_vxlan_acc_vp: failed to create vxlan port rv %d\n", rv);
  }

  return rv;
}

/*****************************************************************//**
 * \brief Create a network virtual port based on the physical port, VPN ID,
 *        egress nextop, tunnel info
 *
 * \param unit      [IN]    Unit number
 * \param vpn       [IN]    VPN Identifier
 * \param flags     [IN]    Flags
 * \param port      [IN]    Port number
 * \param criteria  [IN]    Match Criteria
 * \param egr_obj   [IN]    Egress object information
 * \param tun_init  [IN]    Tunnel initiator ID
 * \param tun_term  [IN]    Tunnel terminator ID
 * \param vp        [OUT]   To store virtual port handle
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
static int create_vxlan_net_vp(int unit, opennsl_vpn_t vpn, uint32 flags, opennsl_gport_t port,
                               opennsl_vxlan_port_match_t criteria, opennsl_if_t egr_obj,
                               opennsl_gport_t tun_init, opennsl_gport_t tun_term, 
                               opennsl_gport_t *vp)
{
  opennsl_vxlan_port_t vxlan_port;
  opennsl_error_t rv = OPENNSL_E_NONE;

  opennsl_vxlan_port_t_init(&vxlan_port);
  vxlan_port.flags = OPENNSL_VXLAN_PORT_NETWORK | 
                     OPENNSL_VXLAN_PORT_EGRESS_TUNNEL |
                     OPENNSL_VXLAN_PORT_SERVICE_TAGGED | flags;
  vxlan_port.match_port =        port;
  vxlan_port.criteria =          criteria;
  vxlan_port.egress_if =         egr_obj;
  vxlan_port.egress_tunnel_id =  tun_init;
  vxlan_port.match_tunnel_id =   tun_term;
  rv = opennsl_vxlan_port_add(unit, vpn, &vxlan_port);
  *vp = vxlan_port.vxlan_port_id;

  if (rv != OPENNSL_E_NONE)
  {
    printf("create_vxlan_net_vp: failed to create vxlan port rv %d\n", rv);
  }

  return rv;
}

/*****************************************************************//**
 * \brief Add L2 station entry based on the given MAC and VLAN ID to
 *        terminate IPv4 packets
 *
 * \param unit      [IN]    Unit number
 * \param mac       [IN]    802.3 MAC address
 * \param vlan      [IN]    VLAN ID
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
static int add_to_l2_station(int unit, opennsl_mac_t mac, opennsl_vlan_t vid)
{
  opennsl_l2_station_t l2_station;
  int station_id;
  opennsl_error_t rv = OPENNSL_E_NONE;
  opennsl_mac_t bc_mac_mask = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

  opennsl_l2_station_t_init(&l2_station);
  memcpy(l2_station.dst_mac, mac, sizeof(opennsl_mac_t));
  memcpy(l2_station.dst_mac_mask, bc_mac_mask, sizeof(opennsl_mac_t));
  l2_station.vlan         = vid;
  l2_station.vlan_mask    = 0xfff;
  l2_station.flags        = OPENNSL_L2_STATION_IPV4;
  rv = opennsl_l2_station_add(unit, &station_id, &l2_station);

  if (rv != OPENNSL_E_NONE)
  {
    printf("add_to_l2_station: failed to create l2 entry rv %d\n", rv);
  }

  return rv;
}

/*****************************************************************//**
 * \brief Add L2 entry based on the MAC, VPN and physical port
 *
 * \param unit      [IN]    Unit number
 * \param mac       [IN]    802.3 MAC address
 * \param vpn_id    [IN]    VPN Identifier
 * \param port      [IN]    Port number
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int add_to_l2_table(int unit, opennsl_mac_t mac, opennsl_vpn_t vpn_id, int port)
{
  int rv;
  opennsl_l2_addr_t l2_addr;

  opennsl_l2_addr_t_init(&l2_addr, mac, vpn_id);
  l2_addr.flags = OPENNSL_L2_STATIC;
  l2_addr.port = port;
  rv =  opennsl_l2_addr_add(unit, &l2_addr);
  if (rv != OPENNSL_E_NONE)
  {
    printf("add_to_l2_table: failed to create l2 entry rv %d\n", rv);
  }
  return rv;
}

/*****************************************************************//**
 * \brief Create VLAN and add a port to it
 *
 * \param unit      [IN]    Unit number
 * \param vid       [IN]    VLAN Identifier
 * \param port      [IN]    Port number
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int vlan_create_add_port(int unit, int vid, int port)
{
  opennsl_pbmp_t pbmp, upbmp;

  OPENNSL_IF_ERROR_RETURN(opennsl_vlan_create(unit, vid));
  OPENNSL_PBMP_CLEAR(pbmp);
  OPENNSL_PBMP_CLEAR(upbmp);
  OPENNSL_PBMP_PORT_ADD(pbmp, port);
  return opennsl_vlan_port_add(unit, vid, pbmp, upbmp);
}

/*****************************************************************//**
 * \brief Create an L3 interface based on the incoming VLAN ID and MAC address
 *
 * \param unit      [IN]    Unit number
 * \param mac       [IN]    802.3 MAC address
 * \param vid       [IN]    VLAN Identifier
 * \param intf_id   [OUT]   L3 interface identifier
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
static int create_l3_interface(int unit, opennsl_mac_t local_mac, int vid,
                               opennsl_if_t *intf_id)
{
  opennsl_l3_intf_t l3_intf;
  opennsl_error_t rv = OPENNSL_E_NONE;

  /* L3 interface and egress object for access */
  opennsl_l3_intf_t_init(&l3_intf);
  memcpy(l3_intf.l3a_mac_addr, local_mac, sizeof(opennsl_mac_t));
  l3_intf.l3a_vid = vid;
  rv = opennsl_l3_intf_create(unit, &l3_intf);
  *intf_id = l3_intf.l3a_intf_id;

  if (rv != OPENNSL_E_NONE)
  {
    printf("create_l3_interface: failed to create L3 intf rv %d\n", rv);
  }

  return rv;
}

/*****************************************************************//**
 * \brief Create an VXLAN L3 egress object
 *
 * \param unit       [IN]    Unit number
 * \param flag       [IN]    Flags
 * \param l3_if      [IN]    L3 interface ID
 * \param nh_mac     [IN]    Next HOP mac address
 * \param port       [IN]    Port number
 * \param vid        [IN]    VLAN ID
 * \param egr_obj_id [OUT]   Egress object identifier
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
static int create_egr_obj(int unit, uint32 flag, int l3_if, opennsl_mac_t nh_mac,
                          opennsl_gport_t gport, int vid, opennsl_if_t *egr_obj_id)
{
  opennsl_error_t rv = OPENNSL_E_NONE;
  opennsl_l3_egress_t l3_egress;

  opennsl_l3_egress_t_init(&l3_egress);
  l3_egress.flags = OPENNSL_L3_VXLAN_ONLY | flag;
  l3_egress.intf  = l3_if;
  memcpy(l3_egress.mac_addr,  nh_mac, sizeof(opennsl_mac_t));
  l3_egress.vlan = vid;
  l3_egress.port = gport;
  rv = opennsl_l3_egress_create(unit, flag, &l3_egress, egr_obj_id);

  if (rv != OPENNSL_E_NONE)
  {
    printf("create_egr_obj: failed to create L3 egress object rv %d\n", rv);
  }

  return rv;
}

/*****************************************************************//**
 * \brief Create tunnel initiator of VXLAN type to encapsulate VXLAN header
 *
 * \param unit       [IN]    Unit number
 * \param lip        [IN]    Local IP address
 * \param rip        [IN]    Remote IP address
 * \param dp         [IN]    Destination UDP port
 * \param sp         [IN]    Source UDP port
 * \param tt;        [IN]    TTL value
 * \param tid        [OUT]   Tunnel identifier
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
static int tunnel_initiator_setup(int unit, opennsl_ip_t lip, opennsl_ip_t rip,
                                  int dp, int sp, int ttl, int *tid)
{
  opennsl_tunnel_initiator_t tnl_init;
  opennsl_error_t rv = OPENNSL_E_NONE;

  opennsl_tunnel_initiator_t_init(&tnl_init);
  tnl_init.type  = opennslTunnelTypeVxlan;
  tnl_init.ttl = ttl;
  tnl_init.sip = lip;
  tnl_init.dip = rip;
  tnl_init.udp_dst_port = dp;
  tnl_init.udp_src_port = sp;
  rv = opennsl_vxlan_tunnel_initiator_create(unit, &tnl_init);

  if (rv != OPENNSL_E_NONE)
  {
    printf("tunnel_initiator_setup: failed to create VXLAN tunnel initiator rv %d\n", rv);
  }

  *tid = tnl_init.tunnel_id;


  return rv;
}

/*****************************************************************//**
 * \brief Create a tunnel terminator of VXLAN type to terminate VXLAN
 *        encapsulated packets
 *
 * \param unit           [IN]    Unit number
 * \param rip            [IN]    Remote IP address
 * \param lip            [IN]    Local IP address
 * \param net_vid        [IN]    Destination UDP port
 * \param tunnel_init_id [IN]    Tunnel initiator ID
 * \param term_id        [OUT]   Tunnel terminator identifier
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
static int tunnel_terminator_setup(int unit, opennsl_ip_t rip, opennsl_ip_t lip,
    opennsl_vlan_t net_vid, int tunnel_init_id, int *term_id)
{
  opennsl_tunnel_terminator_t tnl_term;
  opennsl_error_t rv = OPENNSL_E_NONE;

  opennsl_tunnel_terminator_t_init(&tnl_term);
  tnl_term.type = opennslTunnelTypeVxlan;
  tnl_term.sip = rip;    /* For MC tunnel, Don't care */
  tnl_term.dip = lip;
  tnl_term.tunnel_id = tunnel_init_id;
  tnl_term.flags = OPENNSL_TUNNEL_TERM_TUNNEL_WITH_ID;
  if (net_vid != -1) {
    tnl_term.vlan = net_vid;  /* MC tunnel only - for Bud check */
  }
  rv = opennsl_vxlan_tunnel_terminator_create(unit, &tnl_term);
  *term_id = tnl_term.tunnel_id;

  if (rv != OPENNSL_E_NONE)
  {
    printf("tunnel_terminator_setup: failed to create VXLAN tunnel terminator rv %d\n", rv);
  }

  return rv;
}


/*****************************************************************//**
 * \brief Create 2 VxLAN segments, and two access ports:
 *
 *   Access Port1 --> Segment 1 (VPN 1) \
 *                                       +-> share 1 network UDP tunnel
 *   Access Port2 --> Segment 2 (VPN 2) /
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
static void example_vxlan(opennsl_port_t a_port1, opennsl_port_t a_port2,
    opennsl_port_t n_port)
{
  int unit = DEFAULT_UNIT;

  /* VPN IDs */
  opennsl_vpn_t vpn_id_1 = 0x7010, vpn_id_2 = 0x7020;
  int vnid_1 = 0x12345, vnid_2 = 0x53535;
  opennsl_multicast_t bc_group_1 = 0, bc_group_2 = 0;

  /* Used to create a dummy VPN that is used to create network VP */
  int rsvd_network_vpn = 0x7001;
  int rsvd_network_vpn_vnid = 0xeeee;

  /* Access side */
  /* Access side MAC addresses are not really used */
  opennsl_mac_t acc_dummy_mac = {0x00, 0x00, 0x01, 0x00, 0x00, 0x01};

  opennsl_port_t acc_port_1 = a_port1;          /* access 1 */
  opennsl_vlan_t acc_vid_1 = 21;
  opennsl_if_t acc_intf_id_1 = a_port1;
  opennsl_gport_t acc_gport_1 = OPENNSL_GPORT_INVALID;
  opennsl_if_t acc_egr_obj_1;
  int acc_vxlan_port_1;
  opennsl_if_t acc_encap_id_1;

  opennsl_port_t acc_port_2 = a_port2;          /* access 2 */
  opennsl_vlan_t acc_vid_2 = 20;
  opennsl_if_t acc_intf_id_2 = a_port2;
  opennsl_gport_t acc_gport_2 = OPENNSL_GPORT_INVALID;
  opennsl_if_t acc_egr_obj_2;
  int acc_vxlan_port_2;
  opennsl_if_t acc_encap_id_2;

  /* Network side */
  opennsl_port_t net_port = n_port;
  opennsl_vlan_t net_vid = 22;
  opennsl_if_t net_intf_id = n_port;
  opennsl_gport_t net_gport = OPENNSL_GPORT_INVALID;
  opennsl_if_t net_egr_obj;
  int net_vxlan_port;

  /* UC Tunnel */
  uint8 ttl = 16;
  uint16 udp_dp = VXLAN_UDP_DEST_PORT;
  uint16 udp_sp = 0xffff;
  opennsl_mac_t net_local_mac = {0x00, 0x00, 0x00, 0x00, 0x22, 0x22};
  opennsl_mac_t net_remote_mac = {0x00, 0x00, 0x00, 0x00, 0x00, 0x02};
  opennsl_ip_t tnl_local_ip = 0x0a0a0a01;     /* 10.10.10.1 */
  opennsl_ip_t tnl_remote_ip = 0xC0A80101;    /* 192.168.1.1 */
  int tunnel_init_id, tunnel_term_id;

  /* DLF/BC tunnel and virtual port */
  opennsl_mac_t dlf_mac = {0x01, 0x00, 0x5e, 0x00, 0x00, 0x0A}; /* 224.0.0.10 */
  opennsl_ip_t tnl_mc_dip = 0xe000000A; /* 224.0.0.10 */
  opennsl_if_t egr_obj_mc;
  int vxlan_port_mc;
  opennsl_if_t encap_id_mc;
  int tunnel_mc_init_id, tunnel_mc_term_id;

  /* Payment MAC from access 1 */
  opennsl_mac_t payload_sa_1 = {0x00, 0x00, 0x00, 0x00, 0x11, 0xaa};
  opennsl_mac_t payload_da_1 = {0x00, 0x00, 0x00, 0x00, 0x11, 0xbb};

  /* Payment MAC from access 2 */
  opennsl_mac_t payload_sa_2 = {0x00, 0x00, 0x00, 0x00, 0x22, 0xaa};
  opennsl_mac_t payload_da_2 = {0x00, 0x00, 0x00, 0x00, 0x22, 0xbb};


  /* Global settings */
  do_vxlan_global_setting(unit);

  /* Access port settings */
  do_vxlan_access_port_settings(unit, acc_port_1);
  do_vxlan_access_port_settings(unit, acc_port_2);

  /* Network port settings */
  do_vxlan_net_port_settings(unit, net_port);

  opennsl_port_gport_get(unit, acc_port_1, &acc_gport_1);
  opennsl_port_gport_get(unit, acc_port_2, &acc_gport_2);
  opennsl_port_gport_get(unit, net_port, &net_gport);

  /* Multicast group for segment BC/DLF/MC */
  opennsl_multicast_create(unit, OPENNSL_MULTICAST_TYPE_VXLAN, &bc_group_1);
  opennsl_multicast_create(unit, OPENNSL_MULTICAST_TYPE_VXLAN, &bc_group_2);

  /* Create VXLAN VPNs */
  create_vxlan_vpn(unit, vpn_id_1, vnid_1, bc_group_1, bc_group_1, bc_group_1);
  create_vxlan_vpn(unit, vpn_id_2, vnid_2, bc_group_2, bc_group_2, bc_group_2);

  /* Create VXLAN VPN for assigning Network-VP */
  create_vxlan_vpn(unit, rsvd_network_vpn, rsvd_network_vpn_vnid, bc_group_2,
                   bc_group_2, bc_group_2);

  /* Create access side VXLAN port 1 (belongs to VPN 1) */

  /* VLAN settings */
  vlan_create_add_port(unit, acc_vid_1, acc_port_1);

  /* L3 interface and egress object for access 1 - note use a dummy MAC address */
  create_l3_interface(unit, acc_dummy_mac, acc_vid_1, &acc_intf_id_1);
  create_egr_obj(unit, 0, acc_intf_id_1, acc_dummy_mac,
                 acc_gport_1, acc_vid_1, &acc_egr_obj_1);

  /* Create VXLAN VP for access port 1 */
  create_vxlan_acc_vp(unit, vpn_id_1, 0, acc_gport_1, OPENNSL_VXLAN_PORT_MATCH_PORT,
                      acc_egr_obj_1, acc_vid_1, &acc_vxlan_port_1);

  /* Create access side VXLAN port 2 (belongs to VPN 2) */

  /* VLAN settings */
  vlan_create_add_port(unit, acc_vid_2, acc_port_2);

  /* L3 interface and egress object for access 2 - note use a dummy MAC address */
  create_l3_interface(unit, acc_dummy_mac, acc_vid_2, &acc_intf_id_2);
  create_egr_obj(unit, 0, acc_intf_id_2, acc_dummy_mac,
                 acc_gport_2, acc_vid_2, &acc_egr_obj_2);

  /* Create VXLAN VP for access port 2 */
  create_vxlan_acc_vp(unit, vpn_id_2, 0, acc_gport_2, OPENNSL_VXLAN_PORT_MATCH_PORT,
                      acc_egr_obj_2, acc_vid_2, &acc_vxlan_port_2);

  /* The network tunnel is shared by the two VPNs */

  /* VLAN settings */
  vlan_create_add_port(unit, net_vid, net_port);

  /* L3 interface and egress object for network */
  create_l3_interface(unit, net_local_mac, net_vid, &net_intf_id);
  create_egr_obj(unit, 0, net_intf_id, net_remote_mac, net_gport,
                 net_vid, &net_egr_obj);

  /* Tunnel Setup (Initiator & Terminator - UC) */
  tunnel_initiator_setup(unit, tnl_local_ip, tnl_remote_ip, udp_dp, udp_sp, ttl, &tunnel_init_id);
  tunnel_terminator_setup(unit, tnl_remote_ip, tnl_local_ip, -1, tunnel_init_id, &tunnel_term_id);

  /* Create VXLAN VP for network port */
  create_vxlan_net_vp(unit, rsvd_network_vpn, 0, net_gport, OPENNSL_VXLAN_PORT_MATCH_VN_ID, net_egr_obj,
                      tunnel_init_id, tunnel_term_id, &net_vxlan_port);

  /* Station MAC set up - this will terminate incoming L3 packets on network port */
  add_to_l2_station(unit, net_local_mac, net_vid);

  /*
   * DLF/BC network port set up
   */

  /* Egress object for non-UC VXLAN VP, use same interface as UC VXLAN network */
  create_egr_obj(unit, OPENNSL_L3_IPMC, net_intf_id, dlf_mac, net_gport, net_vid, &egr_obj_mc);

  /* Tunnel Setup (Initiator & Terminator - non-UC) */
  tunnel_initiator_setup(unit, tnl_local_ip, tnl_mc_dip, udp_dp, udp_sp, ttl, &tunnel_mc_init_id);
  tunnel_terminator_setup(unit, tnl_remote_ip, tnl_mc_dip, net_vid,
      tunnel_mc_init_id, &tunnel_mc_term_id);

  /* Create non-UC VXLAN VP for network port */
  create_vxlan_net_vp(unit, rsvd_network_vpn, OPENNSL_VXLAN_PORT_MULTICAST, net_gport,
      OPENNSL_VXLAN_PORT_MATCH_NONE, egr_obj_mc,
      tunnel_mc_init_id, tunnel_mc_term_id, &vxlan_port_mc);

  /* Station MAC set up */
  add_to_l2_station(unit, dlf_mac, net_vid);

  /*
   * MC group set up - MC group should contains all Access ports and Network non-UC port
   */

  /* BC group 1 (VPN 1)*/
  opennsl_multicast_vxlan_encap_get(unit, bc_group_1, net_gport, vxlan_port_mc, &encap_id_mc);
  opennsl_multicast_egress_add(unit, bc_group_1, vxlan_port_mc, encap_id_mc);

  opennsl_multicast_vxlan_encap_get(unit, bc_group_1, acc_gport_1, acc_vxlan_port_1, &acc_encap_id_1);
  opennsl_multicast_egress_add(unit, bc_group_1, acc_vxlan_port_1, acc_encap_id_1);

  /* BC group 2 (VPN 2) */
  opennsl_multicast_vxlan_encap_get(unit, bc_group_2, net_gport, vxlan_port_mc, &encap_id_mc);
  opennsl_multicast_egress_add(unit, bc_group_2, vxlan_port_mc, encap_id_mc);

  opennsl_multicast_vxlan_encap_get(unit, bc_group_2, acc_gport_2, acc_vxlan_port_2, &acc_encap_id_2);
  opennsl_multicast_egress_add(unit, bc_group_2, acc_vxlan_port_2, acc_encap_id_2);

  /*
   * Add Payload L2 address to L2 table
   */

  /* Access 1 => Network */
  add_to_l2_table(unit, payload_da_1, vpn_id_1, net_vxlan_port);

  /* Network => Access 1 */
  add_to_l2_table(unit, payload_sa_1, vpn_id_1, acc_vxlan_port_1);

  /* Access 2 => Network */
  add_to_l2_table(unit, payload_da_2, vpn_id_2, net_vxlan_port);

  /* Network => Access 2 */
  add_to_l2_table(unit, payload_sa_2, vpn_id_2, acc_vxlan_port_2);

}

/*****************************************************************//**
 * \brief Main function for VxLAN application
 *
 * \param argc, argv         commands line arguments
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int main(int argc, char *argv[])
{
  opennsl_error_t   rv;
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
  printf("Initializing the switch device.\r\n");
  rv = opennsl_driver_init((opennsl_init_t *) NULL);

  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to initialize the switch device. Error %s\r\n",
        opennsl_errmsg(rv));
    return rv;
  }

  /* Configure VXLAN settings for access and network ports */
  example_vxlan(1, 2, 3);

  printf("\r\nVxLAN configuration is done successfully\n");

  while (1) {
    printf("\r\nUser menu: Select one of the following options\r\n");
#ifndef CDP_EXCLUDE
    printf("9. Launch diagnostic shell\n");
#endif
    printf("0. Quit the application\n");

    if(example_read_user_choice(&choice) != OPENNSL_E_NONE)
    {
        printf("Invalid option entered. Please re-enter.\n");
        continue;
    }
    switch(choice){

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

  return OPENNSL_E_NONE;
}
