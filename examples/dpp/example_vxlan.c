/******************************************************************************
 *
 * (C) Copyright Broadcom Corporation 2017
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
 * This example application creates a VxLAN segment:
 *
 *   VM1 --- Access Port --> Segment (VPN) -> network UDP tunnel --- VM2
 *
 * Setup configuration:
 *   The following configuration needs to provided using platform configuration file (opennsl.cfg)
 *   to run the VxLAN the application.
 *     bcm886xx_ip4_tunnel_termination_mode=0
 *     bcm886xx_l2gre_enable=0
 *     bcm886xx_vxlan_enable=1
 *     bcm886xx_ether_ip_enable=0
 *     bcm886xx_vxlan_tunnel_lookup_mode=2
 *     split_horizon_forwarding_groups_mode=1
 *
 * Testing Description:
 *   Packet from Access Port to Network Port (Packet encapsulation):
 *     A packet sent from access port with parameters: Access VLAN = 200, SMAC = VM1 MAC,
 *     DMAC = VM2 MAC will be received on networking port with VxLAN encapsulation as follows:
 *     SMAC = Switch MAC (00:0c:00:02:00:00), DMAC = Nexthop MAC (20:00:00:00:cd:1d)
 *
 *   Packet from Network Port to Access Port (Packet decapsulation):
 *     A packet sent from network port with parameters: Tunnel VLAN = 20, SMAC = Router MAC
*     (20:00:00:00:cd:1d), DMAC = Switch MAC (00:0c:00:02:00:00), Destination UDP Port = 4789
       *     will be received on access port as follows:
       *     SMAC = VM2 MAC, DMAC = VM1 MAC
       *
       ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sal/driver.h>
#include <opennsl/error.h>
#include <opennsl/init.h>
#include <opennsl/l2.h>
#include <opennsl/switch.h>
#include <opennsl/vlan.h>
#include <opennsl/vswitch.h>
#include <opennsl/tunnel.h>
#include <opennsl/multicast.h>
#include <opennsl/vxlan.h>
#include <examples/util.h>

#define DEFAULT_UNIT  0

char example_usage[] =
"Syntax: example_vxlan                                                 \n\r"
"                                                                      \n\r"
"Paramaters: None.                                                     \n\r"
"                                                                      \n\r"
"Usage Guidelines: None.                                               \n\r";

/* Global Variables */
int verbose = 0; /* To enable debug prints */
int egress_mc = 0;
int outlif_to_count2;
int outlif_counting_profile = OPENNSL_STAT_LIF_COUNTING_PROFILE_NONE;

/* Configure vxlan port */
struct vxlan_port_add_s {
  /* INPUT */
  uint32 vpn;                   /* vpn to which we add the vxlan port  */
  opennsl_gport_t in_port;          /* network side port for learning info. */
  opennsl_gport_t in_tunnel;        /* ip tunnel terminator gport */
  opennsl_gport_t out_tunnel;       /* ip tunnel initiator gport */
  opennsl_if_t egress_if;           /* FEC entry, contains ip tunnel encapsulation information */
  uint32 flags;                 /* vxlan flags */
  int set_egress_orientation_using_vxlan_port_add;  /* egress orientation can be configured:
                                                       - using the api opennsl_vxlan_port_add,
                                                       when egress_tunnel_id (ip tunnel initiator gport, contains outlif) is valid (optional).
                                                       - using the api opennsl_port_class_set, update egress orientation.
                                                       By default: enabled */
  int network_group_id;         /* forwarding group for vxlan port. Used for orientation filter */

  /* If the FEC that is passed to vxlan port is an ECMP. We can't add directly the vxlan port to the
   * VSI flooding MC group.
   * We'll add instead the tunnel initiator interface to the VSI flooding MC group */
  int is_ecmp;                  /* indicate that FEC that is passed to vxlan port is an ECMP */
  opennsl_if_t out_tunnel_if;       /* ip tunnel initiator itf */

  /* OUTPUT */
  opennsl_gport_t vxlan_port_id;    /* returned vxlan gport */
};

/* Creating L3 interface */
struct create_l3_intf_s {
  /* Input */
  uint32 flags;                 /* OPENNSL_L3_XXX */
  uint32 ingress_flags;         /* OPENNSL_L3_INGRESS_XXX */
  int no_publc;                 /* Used to force no public, public is forced if vrf = 0 or scale feature is turned on */
  int vsi;
  opennsl_mac_t my_global_mac;
  opennsl_mac_t my_lsb_mac;
  int vrf_valid;                /* Do we need to set vrf */
  int vrf;
  int rpf_valid;                /* Do we need to set rpf */
  opennsl_l3_ingress_urpf_mode_t urpf_mode; /* avail. when OPENNSL_L3_RPF is set */
  int mtu_valid;
  int mtu;
  int mtu_forwarding;
  int qos_map_valid;
  int qos_map_id;
  int ttl_valid;
  int ttl;
  uint8 native_routing_vlan_tags;

  /* Output */
  int rif;
  uint8 skip_mymac;             /* If true, mymac will not be set. Make sure you set it elsewhere. */
};

/* Creating L3 egress */
struct create_l3_egress_s {
  /* Input */
  uint32 allocation_flags;      /* OPENNSL_L3_XXX */
  uint32 l3_flags;              /* OPENNSL_L3_XXX */
  uint32 l3_flags2;             /* OPENNSL_L3_FLAGS2_XXX */

  /* ARP */
  int vlan;                     /* Outgoing vlan-VSI, relevant for ARP creation. In case set then SA MAC address is retreived from this VSI. */
  opennsl_mac_t next_hop_mac_addr;  /* Next-hop MAC address, relevant for ARP creation */
  int qos_map_id;               /* General QOS map id */

  /* FEC */
  opennsl_if_t out_tunnel_or_rif;   /* *Outgoing intf, can be tunnel/rif, relevant for FEC creation */
  opennsl_gport_t out_gport;        /* *Outgoing port , relevant for FEC creation */

  /* Input/Output ID allocation */
  opennsl_if_t fec_id;              /* *FEC ID */
  opennsl_if_t arp_encap_id;        /* *ARP ID, may need for allocation ID or for FEC creation */
};

struct vxlan_s {
  int          vpn_id;
  int          vni;
  int          vxlan_vdc_enable;          /* Option to enable/disable VXLAN VDC support */
  int          vxlan_network_group_id;    /* ingress and egress orientation for VXLAN */
  int          dip_sip_vrf_using_my_vtep_index_mode; /* configure DIP-> my-vtep-index, tunnel term: my-vtep-index, SIP, VRF and
                                                        default tunnel term: DIP, SIP, VRF */
  int          my_vtep_index;             /* used in dip_sip_vrf_using_my_vtep_index_mode */
  int          access_port;               /* access port for the script */
  int          network_port;              /* Network port for the script */
  /* HW object created by the script */
  opennsl_gport_t  tunnel_init_gport;         /* GPORT for Tunnel initiator */
  opennsl_if_t     tunnel_init_intf_id;      /* Tunnel interface Id for vxlan Tunnel */
  opennsl_if_t     vxlan_fec_intf_id;         /* fec for the VXLAN tunnel, set at example_vxlan */
  int          mc_group_id;               /* Flood group created for VPN */
  opennsl_gport_t  tunnel_term_gport;         /* GPORT for tunnel terminator */
  opennsl_if_t     prov_vlan_l3_intf_id;      /* L3 interface on provider vlan */
  opennsl_gport_t  vlan_inLif;                /* InLif for the VLAN port on access port */
  opennsl_gport_t  vxlan_gport;               /* GPORT for the VXLAN */
  opennsl_mac_t    user_mac_address;          /* UC static MAC address for inLif */
  opennsl_mac_t    tunnel_mac_address;        /* UC static MAC address for VxLAN */
  opennsl_mac_t    mc_mac;                    /* reserved MAC for MC traffic */
};

struct vxlan_s g_vxlan = {
  15,                 /* vpn_id */
  5000,               /* vni    */
  0,                  /* enable vdc support */
  1,                  /* vxlan orientation */
  0,                  /* dip_sip_vrf_using_my_vtep_index_mode */
  0x2,                /* my_vtep_index */
  0,                  /* access port: Updated by script on execution */
  0,                  /* network port: Updated by script on execution */
  0,0,0,0,0,0,0,0,    /* Updatedd by script on execution */
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0 },
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0xf1 },
  { 0x01, 0x00, 0x5E, 0x01, 0x01, 0x14 }
};

uint32 vdc_port_class = 10;
#define MY_MAC          {0x00, 0x0c, 0x00, 0x02, 0x00, 0x00}

struct ip_tunnel_s {
  opennsl_mac_t da;                 /* ip tunnel da */
  opennsl_mac_t sa;                 /* ip tunnel my mac */
  int sip;                      /* ip tunnel sip */
  int sip_mask;
  int dip;                      /* ip tunnel dip */
  int dip_mask;
  int ttl;                      /* ip tunnel ttl */
  int dscp;                     /* ip tunnel dscp */
  opennsl_tunnel_dscp_select_t dscp_sel;    /* ip tunnel dscp_sel */
  int flags;
};

/*
 * struct include meta information.
 * where the cint logic pull data from this struct.
 * use to control differ runs of the cint, without changing the cint code
 */
struct ip_tunnel_glbl_info_s {
  opennsl_tunnel_type_t tunnel_type;
  struct ip_tunnel_s ip_tunnel_info;
  int tunnel_vlan;                     /* vlan for ip tunnels */
  int provider_vlan;
  int access_vlan;
};

struct ip_tunnel_glbl_info_s ip_tunnel_glbl_info = {
  /* tunnel type */
  opennslTunnelTypeVxlan,
  /* tunnel da                         |      sa               | sip: 170.0.0.17 | mask:0  */
  {{0x20, 0x00, 0x00, 0x00, 0xcd, 0x1d}, MY_MAC, 0xAA000011,       0,
    0xAB000011, 0xFFFFFFFF,    50,    11,   opennslTunnelDscpPacket, OPENNSL_TUNNEL_INIT_USE_INNER_DF},
  /* vlan for both ip tunnels */
  20,
  20,
  200
};

int example_ip_tunnel_add(int unit, opennsl_if_t *itf,
    opennsl_tunnel_initiator_t * tunnel);

/* Utility API */
int portmap[100] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
/*****************************************************************//**
 * \brief OTP portmap for DNX device
 *
 * \param unit      [IN]    Unit number
 *
 * \return void
 ********************************************************************/
void init_portmap(int unit)
{
  opennsl_info_t info;
  int rv = opennsl_info_get(unit, &info);
  if (rv != OPENNSL_E_NONE) {
    printf("Error in getting the chip info, Error = %s\n", opennsl_errmsg(rv));
    return;
  }

  if (example_is_qmx_device(unit))
  {
    portmap[1]=13;  portmap[2]=14;  portmap[3]=15;  portmap[4]=16;
    portmap[5]=17;  portmap[6]=18;  portmap[7]=19;  portmap[8]=20;
    portmap[9]=21;  portmap[10]=22; portmap[11]=23; portmap[12]=24;
    portmap[13]=25; portmap[14]=26; portmap[15]=27; portmap[16]=28;
    portmap[17]=29; portmap[18]=30; portmap[19]=31; portmap[20]=32;
  }
  else
  {
    printf("device is not QMX\n");
    int i;
    for (i=1;i<50;i++)
      portmap[i]=i;

  }
}

/*****************************************************************//**
 * \brief Utility function to print IP tunnel parameters
 *
 * \param type        [IN]    String token
 * \param tunnel_term [IN]    Tunnel terminator information
 *
 * \return void
 ********************************************************************/
void example_ip_tunnel_term_print_key(char *type,
    opennsl_tunnel_terminator_t *tunnel_term)
{
  printf("%s  key: ", type);

  if (tunnel_term->sip_mask == 0) {
    printf("SIP: masked    ");
  } else if (tunnel_term->sip_mask == 0xFFFFFFFF) {
    print_ip_addr("SIP:", tunnel_term->sip);
    printf("/0x%08x ", tunnel_term->sip_mask);
  }
  if (tunnel_term->dip_mask == 0) {
    printf("DIP: masked    ");
  } else if (tunnel_term->dip_mask == 0xFFFFFFFF) {
    print_ip_addr("DIP:", tunnel_term->dip);
    printf("/0x%08x ", tunnel_term->dip_mask);
  }

  printf("RIF: 0x%08x ", tunnel_term->tunnel_if);

  printf("\n\r");
}


/*
 * add entry to mac table <vlan,mac> --> port
 * <VID, MAC> --> port
 */
/*****************************************************************//**
 * \brief To update MAC table
 *
 * \param unit      [IN]    Unit number
 * \param mac       [IN]    MAC address
 * \param vid       [IN]    VLAN identifier
 * \param port      [IN]    Port number
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_l2_addr_add(int unit, opennsl_mac_t mac,
    uint16 vid, opennsl_gport_t port)
{

  int rv;

  opennsl_l2_addr_t l2addr;

  opennsl_l2_addr_t_init(&l2addr, mac, vid);

  l2addr.port = port;
  l2addr.vid = vid;
  l2addr.flags = OPENNSL_L2_STATIC;

  rv = opennsl_l2_addr_add(unit, &l2addr);
  if (rv != OPENNSL_E_NONE) {
    printf("Error, Failed to add L2 entry, Error %s\n", opennsl_errmsg(rv));
    return rv;
  }

  if (verbose > 2) {
    printf("l2 entry: fid = %d ", vid);
    l2_print_mac("mac =", mac);
    printf("  dest-port 0x%08x \n", port);
  }
  return OPENNSL_E_NONE;
}


/*****************************************************************//**
 * \brief Adding entries to MC group
 *
 * \param unit            [IN]    Unit number
 * \param ipmc_index      [IN]    Multicast group
 * \param port            [IN]    List of ports to add to the group
 * \param cud             [IN]    CUD
 * \param nof_mc_entries  [IN]    Number of multicast entries
 * \param is_egress       [IN]    If true, add ingress multicast entry
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_add_multicast_entry(int unit, int ipmc_index,
    int *ports, int *cud, int nof_mc_entries, int is_egress)
{
  int rv = OPENNSL_E_NONE;
  int i;

  for (i = 0; i < nof_mc_entries; i++) {
    /* egress MC */
    if (is_egress) {
      rv = opennsl_multicast_egress_add(unit, ipmc_index, ports[i], cud[i]);
      if (rv != OPENNSL_E_NONE) {
        printf("Failed to add egress multicast entry, port %d encap_id: %d, Error %s\n", ports[i],
            cud[i], opennsl_errmsg(rv));
        return rv;
      }
    }
    /* ingress MC */
    else {
      rv = opennsl_multicast_ingress_add(unit, ipmc_index, ports[i], cud[i]);
      if (rv != OPENNSL_E_NONE) {
        printf("Error, opennsl_multicast_ingress_add: port %d encap_id: %d \n",
            ports[i], cud[i]);
        return rv;
      }
    }
  }

  return rv;
}

/*****************************************************************//**
 * \brief Add gport of type vlan-port to the multicast
 *
 * \param unit            [IN]    Unit number
 * \param mc_group_id     [IN]    Multicast group ID
 * \param sys_port        [IN]    System port
 * \param gport           [IN]    gport
 * \param is_egress       [IN]    Is multicast group egress
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_vlan_port_add( int unit, int mc_group_id,
    int sys_port, int gport, uint8 is_egress)
{
  int encap_id;
  int rv;

  rv = opennsl_multicast_vlan_encap_get(unit, mc_group_id, sys_port, gport, &encap_id);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to get multicast encapsulation ID for Multicast group 0x%08x"
        " phy_port: 0x%08x  gport: 0x%08x, Error %s\n",
        mc_group_id, sys_port, gport, opennsl_errmsg(rv));
    return rv;
  }

  rv = example_add_multicast_entry(unit, mc_group_id, &sys_port,
      &encap_id, 1, is_egress);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to add multicast entry for mc_group_id: 0x%08x "
        "phy_port: 0x%08x gport: 0x%08x, Error %s \n",
        mc_group_id, sys_port, gport, opennsl_errmsg(rv));
    return rv;
  }

  return rv;
}

/*****************************************************************//**
 * \brief Add gport of type vlan-port to the multicast
 *
 * \param unit            [IN]    Unit number
 * \param vsi             [IN]    Virtual Switch ID
 * \param phy_port        [IN]    Physical port
 * \param gport           [IN]    gport
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_add_inLif_to_vswitch(int unit, opennsl_vlan_t vsi,
    opennsl_port_t phy_port, opennsl_gport_t gport)
{
  int rv;

  /* add to vswitch */
  rv = opennsl_vswitch_port_add(unit, vsi, gport);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to add a port to vswitch, Error %s\n", opennsl_errmsg(rv));
    return rv;
  }
  if (verbose) {
    printf("add access port 0x%08x to vswitch %d (0x%08x) \n\r", gport, vsi, vsi);
  }

  /* update Multicast to have the added port  */
  rv = example_vlan_port_add(unit, g_vxlan.mc_group_id, phy_port, gport, 0);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to add a port to multicast group, phy_port: 0x%08x "
        "gport: 0x%08x, Error %s\n", phy_port, gport, opennsl_errmsg(rv));
    return rv;
  }
  if (verbose) {
    printf("add access port 0x%08x to multicast in unit %d\n", gport, unit);
  }
  return OPENNSL_E_NONE;
}

/*****************************************************************//**
 * \brief Remove gport of type vlan-port from the multicast group
 *
 * \param unit            [IN]    Unit number
 * \param vsi             [IN]    Virtual Switch ID
 * \param phy_port        [IN]    Physical port
 * \param vlan_port       [IN]    VLAN port ID
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int remove_inLif_from_vswitch(int unit, opennsl_vlan_t  vsi,
    opennsl_port_t  phy_port, opennsl_gport_t vlan_port)
{
  int rv;
  int encap_id;

  rv = opennsl_multicast_vlan_encap_get(unit, g_vxlan.mc_group_id, phy_port, vlan_port, &encap_id);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to get encapsulation ID for mc_group_id: 0x%08x "
        "phy_port: 0x%08x vlan_port: 0x%08x, Error %s \n",
        g_vxlan.mc_group_id, phy_port, vlan_port, opennsl_errmsg(rv));
    return rv;
  }

  rv = opennsl_multicast_ingress_delete(unit, g_vxlan.mc_group_id, phy_port, encap_id);
  if (rv == OPENNSL_E_NOT_FOUND) {
    printf("Failed to delete phy_port: 0x%08x from multicast group ID %d, Error %s\n",
        phy_port, g_vxlan.mc_group_id, opennsl_errmsg(rv));
    rv = OPENNSL_E_NONE;
  }
  printf ("Deleted phy_port: 0x%08x, encap_id:0x%08x from multicast group with ID: 0x%08x\n",
      phy_port, encap_id, g_vxlan.mc_group_id);


  /* remove from vswitch */
  rv = opennsl_vswitch_port_delete(unit, vsi, vlan_port);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to remove port 0x%08x from vsi 0x%08x, Error %s\n",
        vlan_port, vsi, opennsl_errmsg(rv));
    return rv;
  }
  if (verbose) {
    printf("Removed port 0x%08x from vswitch 0x%08x\n\r", vlan_port, vsi);
  }

  return OPENNSL_E_NONE;
}

/*****************************************************************//**
 * \brief Create new VSI
 *
 * \param unit            [IN]    Unit number
 * \param vlan            [IN]    VLAN ID
 * \param mc_group        [IN]    The multicast group to be assigned
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_open_vlan_per_mc(
    int unit, int vlan, opennsl_multicast_t mc_group)
{
  int rv;

  /* The vlan in this case may also represent a vsi. in that case, it should be created with a different api */
  if (vlan <= OPENNSL_VLAN_MAX) {
    rv = opennsl_vlan_create(unit, vlan);
  } else {
    rv = opennsl_vswitch_create_with_id(unit, vlan);
  }
  if ((rv != OPENNSL_E_NONE) && (rv != OPENNSL_E_EXISTS)) {
    printf("Failed to opensl vlan(%d), Error %s", vlan, opennsl_errmsg(rv));
    return rv;
  }

  /* Set VLAN with MC is not required for VXLAN, removed below calls */
  if (verbose >= 3) {
    printf("Created vlan:%d \n", vlan);
  }

  return rv;
}

/*****************************************************************//**
 * \brief Open new vsi and attach it to the give mc_group
 *
 * \param unit    [IN]    Unit number
 * \param vlan    [IN]    VLAN ID
 * \param port    [IN]    Port number
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
void example_add_vlan_on_port(
    int unit,
    int vlan,
    int port)
{
  int rv;
  /* create vlan and add port to it */
  rv = example_open_vlan_per_mc(unit, vlan, 0);
  if (rv != OPENNSL_E_NONE) {
    return;
  }
  rv = opennsl_vlan_gport_add(unit, vlan, port, 0);
  if ((rv != OPENNSL_E_NONE) && (rv != OPENNSL_E_EXISTS)) {
    printf("Failed to add port(0x%08x) to vlan %d, Error %s\n",
        port, vlan, opennsl_errmsg(rv));
  }
  printf("Added port %d (0x%08x) to vlan %d\n", port, port, vlan);
  return;
}

/*****************************************************************//**
 * \brief Utility function to add ports to relevant VLAN's
 *
 * \param unit            [IN]    Unit number
 * \param network_port    [IN]    Network port number
 * \param access_port     [IN]    Access port number
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
void example_add_ports_to_vlans(
    int unit, int network_port, int access_port)
{
  /*** create tunnel_vlan and add the network port  ***/
  if (ip_tunnel_glbl_info.tunnel_vlan != ip_tunnel_glbl_info.provider_vlan) 
  {
    example_add_vlan_on_port(unit, ip_tunnel_glbl_info.tunnel_vlan, network_port);
  }

  /*** create provider_vlan and add network port to it ***/
  example_add_vlan_on_port(unit, ip_tunnel_glbl_info.provider_vlan, network_port);

  /*** create access_vlan and add user port to it ***/
  example_add_vlan_on_port(unit, ip_tunnel_glbl_info.access_vlan, access_port);
}

/*****************************************************************//**
 * \brief Utility function to create multicast group
 *
 * \param unit            [IN]    Unit number
 * \param mc_group_id     [IN]    Multicast group ID
 * \param extra_flags     [IN]    flags
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_multicast_group_open(
    int unit, int *mc_group_id, int extra_flags)
{
  int rv = OPENNSL_E_NONE;
  int flags;

  flags = OPENNSL_MULTICAST_WITH_ID | extra_flags;
  /* create ingress/egress MC */
  if (egress_mc) {
    flags |= OPENNSL_MULTICAST_EGRESS_GROUP;
  } else {
    flags |= OPENNSL_MULTICAST_INGRESS_GROUP;
  }

  rv = opennsl_multicast_create(unit, flags, mc_group_id);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to create multicast group with ID %d, Error %s\n",
        *mc_group_id, opennsl_errmsg(rv));
    return rv;
  }

  if (egress_mc) {
    printf("Created egress mc_group %d (0x%x) \n", *mc_group_id, *mc_group_id);
  } else {
    printf("Created ingress mc_group %d (0x%x) \n", *mc_group_id, *mc_group_id);
  }
  /* save multicast group id */
  g_vxlan.mc_group_id = *mc_group_id;

  return rv;
}

/*****************************************************************//**
 * \brief Create L3 egress object for FEC and ARP entry
 *
 * \param unit       [IN]      Unit number
 * \param l3_egress  [IN/OUT]  L3 egress object holding next hop information
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_l3_egress_create(int unit, struct create_l3_egress_s *l3_egress)
{
  int rv;
  opennsl_l3_egress_t l3eg;
  opennsl_if_t l3egid;
  opennsl_l3_egress_t_init(&l3eg);

  /* FEC properties */
  l3eg.intf = l3_egress->out_tunnel_or_rif;
  l3eg.port = l3_egress->out_gport;
  l3eg.encap_id = l3_egress->arp_encap_id;

  /* ARP */
  memcpy(&l3eg.mac_addr, &l3_egress->next_hop_mac_addr, sizeof(opennsl_mac_t));
  l3eg.vlan = l3_egress->vlan;
  l3eg.qos_map_id = l3_egress->qos_map_id;

  l3eg.flags = l3_egress->l3_flags;
  l3eg.flags2 = l3_egress->l3_flags2;
  l3egid = l3_egress->fec_id;

  rv = opennsl_l3_egress_create(unit, l3_egress->allocation_flags, &l3eg, &l3egid);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to create egress egress object, Error %s\n", opennsl_errmsg(rv));
    return rv;
  }

  l3_egress->fec_id = l3egid;
  l3_egress->arp_encap_id = l3eg.encap_id;

  if (verbose >= 1) {
    printf("VLAN:%d created FEC-id = 0x%08x, ", l3eg.vlan,
        l3_egress->fec_id);
    printf("encap-id = 0x%08x ", l3_egress->arp_encap_id);
  }

  if (verbose >= 2) {
    printf("\n\toutRIF = 0x%08x out-port =%d ", l3_egress->out_tunnel_or_rif,
        l3_egress->out_gport);
    printf("mac-address: %02x:%02x:%02x:%02x:%02x:%02x",
        l3eg.mac_addr[0], l3eg.mac_addr[1], l3eg.mac_addr[2],
        l3eg.mac_addr[3], l3eg.mac_addr[4], l3eg.mac_addr[5]);
  }

  if (verbose >= 1) {
    printf("\n");
  }

  return rv;
}

/*****************************************************************//**
 * \brief Create Router interface
 * - packets sent in from this interface identified by <port, vlan> with
 *   specificed MAC address is subject of routing
 * - packets sent out through this interface will be encapsulated with <vlan, mac_addr>
 *
 * \param unit      [IN]      Unit number
 * \param l3_intf   [IN/OUT]  L3 interface object holding routing interface information
 *    - flags: special controls set to zero.
 *    - open_vlan - if TRUE create given vlan, FALSE: vlan already opened juts use it
 *    - port - where interface is defined
 *    - vlan - router interface vlan
 *    - vrf - VRF to map to.
 *    - mac_addr - my MAC
 *    - intf - returned handle of opened l3-interface
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_l3_intf_rif_create(
    int unit, struct create_l3_intf_s * l3_intf)
{
  opennsl_l3_intf_t l3if, l3if_old;
  int rv, station_id;
  opennsl_l2_station_t station;
  opennsl_l3_ingress_t l3_ing_if;
  int is_urpf_mode_per_rif = 0;
  int enable_public = 0;

  /* Initialize a opennsl_l3_intf_t structure. */
  opennsl_l3_intf_t_init(&l3if);
  opennsl_l3_intf_t_init(&l3if_old);
  opennsl_l2_station_t_init(&station);
  opennsl_l3_ingress_t_init(&l3_ing_if);

  if (!l3_intf->skip_mymac) {
    /* set my-Mac global MSB */
    station.flags = 0;
    memcpy(station.dst_mac, l3_intf->my_global_mac, sizeof(opennsl_mac_t));
    station.src_port_mask = 0;  /* port is not valid */
    station.vlan_mask = 0;      /* vsi is not valid */
    station.dst_mac_mask[0] = 0xff; /* dst_mac my-Mac MSB mask is -1 */
    station.dst_mac_mask[1] = 0xff;
    station.dst_mac_mask[2] = 0xff;
    station.dst_mac_mask[3] = 0xff;
    station.dst_mac_mask[4] = 0xff;
    station.dst_mac_mask[5] = 0xff;

    rv = opennsl_l2_station_add(unit, &station_id, &station);
    if (rv != OPENNSL_E_NONE) {
      printf("Failed to add L2 station, Error %s\n", opennsl_errmsg(rv));
      return rv;
    }
  }

  l3if.l3a_flags = OPENNSL_L3_WITH_ID;  /* WITH-ID or without-ID does not really matter. Anyway for now RIF equal VSI */
  if ((l3_intf->no_publc == 0) && ( /* Update the in_rif to have public searches enabled for vrf == 0 */
        (l3_intf->vrf == 0 && example_is_qmx_device(unit)) ))
  {
    l3_intf->vrf_valid = 1;
    enable_public = 1;
  }

  l3if.l3a_vid = l3_intf->vsi;
  l3if.l3a_ttl = 31;            /* default settings */
  if (l3_intf->ttl_valid) {
    l3if.l3a_ttl = l3_intf->ttl;
  }
  l3if.l3a_mtu = 1524;          /* default settings */
  if (l3_intf->mtu_valid) {
    l3if.l3a_mtu = l3_intf->mtu;
    l3if.l3a_mtu_forwarding = l3_intf->mtu_forwarding;
  }
  l3if.native_routing_vlan_tags = l3_intf->native_routing_vlan_tags;
  l3_intf->rif = l3if.l3a_intf_id = l3_intf->vsi;   /* In DNX Arch VSI always equal RIF */

  memcpy(l3if.l3a_mac_addr, l3_intf->my_lsb_mac, 6);
  memcpy(l3if.l3a_mac_addr, l3_intf->my_global_mac, 4); /* ovewriting 4 MSB bytes with global MAC configuration */

  l3if.native_routing_vlan_tags = l3_intf->native_routing_vlan_tags;

  l3if_old.l3a_intf_id = l3_intf->vsi;
  rv = opennsl_l3_intf_get(unit, &l3if_old);
  if (rv == OPENNSL_E_NONE) {
    /* if L3 INTF already exists, replace it */
    l3if.l3a_flags = l3if.l3a_flags | OPENNSL_L3_REPLACE;
    printf("intf 0x%x already exist, just replacing\n",
        l3if_old.l3a_intf_id);
  }

  if (l3_intf->qos_map_valid) {
    l3if.dscp_qos.qos_map_id = l3_intf->qos_map_id;
  }

  rv = opennsl_l3_intf_create(unit, &l3if);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to create L3 interface, Error %s\n", opennsl_errmsg(rv));
    return rv;
  }

  if (l3_intf->vrf_valid || l3_intf->rpf_valid) {
    l3_ing_if.flags = OPENNSL_L3_INGRESS_WITH_ID;   /* must, as we update exist RIF */
    l3_ing_if.vrf = l3_intf->vrf;

    if (l3_intf->rpf_valid && !is_urpf_mode_per_rif) {
      /* Set uRPF global configuration */
      rv = opennsl_switch_control_set(unit, opennslSwitchL3UrpfMode, l3_intf->urpf_mode);
      if (rv != OPENNSL_E_NONE) {
        return rv;
      }
    }
    if (l3_intf->flags & OPENNSL_L3_RPF) {
      l3_ing_if.urpf_mode = l3_intf->urpf_mode;
    } else {
      l3_ing_if.urpf_mode = opennslL3IngressUrpfDisable;
    }

    if ((l3_intf->ingress_flags & OPENNSL_L3_INGRESS_GLOBAL_ROUTE)
        || ((enable_public == 1) && example_is_qmx_device(unit))) {
      l3_ing_if.flags |= OPENNSL_L3_INGRESS_GLOBAL_ROUTE;
    }
    if (l3_intf->ingress_flags & OPENNSL_L3_INGRESS_DSCP_TRUST) {
      l3_ing_if.flags |= OPENNSL_L3_INGRESS_DSCP_TRUST;
    }

    if (l3_intf->qos_map_valid) {
      l3_ing_if.qos_map_id = l3_intf->qos_map_id;
    }

    rv = opennsl_l3_ingress_create(unit, &l3_ing_if, &l3if.l3a_intf_id);
    if (rv != OPENNSL_E_NONE) {
      printf("Failed to create L3 ingress interface, Error %s\n", opennsl_errmsg(rv));
      return rv;
    }
    l3_intf->rif = l3if.l3a_intf_id;
  }

  printf
    ("created ingress interface = %d, on vlan = %d in unit %d, vrf = %d, skip_mymac:%d  ",
     l3_intf->rif, l3_intf->vsi, unit, l3_intf->vrf, l3_intf->skip_mymac);
  printf("mac: %02x:%02x:%02x:%02x:%02x:%02x\n\r",
      l3_intf->my_global_mac[0], l3_intf->my_global_mac[1],
      l3_intf->my_global_mac[2], l3_intf->my_global_mac[3],
      l3_intf->my_global_mac[4], l3_intf->my_global_mac[5]);

  return rv;
}

/*****************************************************************//**
 * \brief Create L3 interface on provider_vlan
 *
 * \param unit          [IN]     Unit number
 * \param provider_vlan [IN]     Provider VLAN
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_ip_tunnel_term_create_l3_intf(
    int unit, int provider_vlan)
{
  int rv;
  /* my-mac for LL termination */
  opennsl_mac_t my_mac = MY_MAC;
  struct create_l3_intf_s intf;

  memset(&intf, 0, sizeof(intf));
  /* packets income on this vlan with my-mac will be LL termination */
  intf.vsi           = provider_vlan;
  memcpy(intf.my_global_mac, my_mac, sizeof(opennsl_mac_t));
  memcpy(intf.my_lsb_mac, my_mac, sizeof(opennsl_mac_t));
  intf.ingress_flags = OPENNSL_L3_INGRESS_GLOBAL_ROUTE; /* enable public searches */

  rv = example_l3_intf_rif_create(unit, &intf);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to create L3 interface, Error %s\n", opennsl_errmsg(rv));
  }
  g_vxlan.prov_vlan_l3_intf_id = intf.rif;

  return rv;
}

/*****************************************************************//**
 * \brief Create IP tunnel termination interface
 *
 * \param unit              [IN]     Unit number
 * \param in_tunnel_gport_p [IN/OUT] Tunnel termination interface information
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_vxlan_tunnel_terminator_create(
    int unit, opennsl_gport_t *in_tunnel_gport_p)
{
  int rv;
  /* tunnel term info: according to DIP  only */
  opennsl_tunnel_terminator_t ip_tunnel_term;
  struct ip_tunnel_s ip_tunnel_info = ip_tunnel_glbl_info.ip_tunnel_info;
  /*** create IP tunnel terminator ***/
  opennsl_tunnel_terminator_t_init(&ip_tunnel_term);
  ip_tunnel_term.dip       = ip_tunnel_info.sip;      /* 170.0.0.17 */
  ip_tunnel_term.dip_mask  = 0xFFFFFFFF;
  ip_tunnel_term.sip       = ip_tunnel_info.dip;      /* 171.0.0.17 */
  ip_tunnel_term.sip_mask  = 0xFFFFFFFF;
  ip_tunnel_term.tunnel_if = -1;    /* means don't overwite RIF */
  ip_tunnel_term.type = opennslTunnelTypeVxlan;

  rv = opennsl_tunnel_terminator_create(unit, &ip_tunnel_term);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to create tunnel terminator, Error %s\n", opennsl_errmsg(rv));
  }
  if (verbose >= 1) {
    printf("created tunnel terminator = 0x%08x \n", ip_tunnel_term.tunnel_id);
    example_ip_tunnel_term_print_key("created tunnel term ", &ip_tunnel_term);
  }
  *in_tunnel_gport_p = ip_tunnel_term.tunnel_id;

  return rv;
}

/*****************************************************************//**
 * \brief Build IP tunnel
 *
 * \param unit            [IN]     Unit number
 * \param tunnel_gportp   [IN/OUT] IP Tunnel information. Returns gport-id
 *                                 pointing to the IP tunnels
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_vxlan_egress_tunnel_create(
    int unit, int tunnel_vlan, opennsl_gport_t *tunnel_gportp)
{
  int rv;

  /* tunnel info */
  opennsl_tunnel_initiator_t ip_tunnel;
  struct ip_tunnel_s ip_tunnel_info = ip_tunnel_glbl_info.ip_tunnel_info;
  int tunnel_itf = 0;

  /*** create tunnel ***/
  opennsl_tunnel_initiator_t_init(&ip_tunnel);
  ip_tunnel.dip       = ip_tunnel_info.dip;   /* default: 171.0.0.17 */
  ip_tunnel.sip       = ip_tunnel_info.sip;   /* default: 170.0.0.17 */
  ip_tunnel.flags    |= ip_tunnel_info.flags;
  ip_tunnel.ttl       = ip_tunnel_info.ttl;   /* default: 50 */
  ip_tunnel.type      = ip_tunnel_glbl_info.tunnel_type; /* default: opennslTunnelTypeIpAnyIn4 */
  ip_tunnel.vlan      = tunnel_vlan;
  ip_tunnel.dscp_sel  = ip_tunnel_info.dscp_sel; /* default: opennslTunnelDscpAssign */
  if (opennslTunnelDscpAssign == ip_tunnel.dscp_sel)
  {
    ip_tunnel.dscp  = ip_tunnel_info.dscp; /* default: 11 */
  }
  ip_tunnel.outlif_counting_profile = outlif_counting_profile;
  rv = example_ip_tunnel_add(unit, &tunnel_itf, &ip_tunnel);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to add IP tunnel, Error %s\n", opennsl_errmsg(rv));
  }
  if (verbose >= 1) {
    printf("Created IP tunnel on intf : 0x%08x ", tunnel_itf);
    print_ip_addr(" SIP:", ip_tunnel.sip);
    print_ip_addr(" DIP:", ip_tunnel.dip);
    printf("\n");
  }
  if (outlif_counting_profile != OPENNSL_STAT_LIF_COUNTING_PROFILE_NONE) {
    outlif_to_count2 = ip_tunnel.tunnel_id;
  }
  /*** save it in global data */
  g_vxlan.tunnel_init_intf_id = tunnel_itf;

  /* refernces to created tunnels as gport */
  *tunnel_gportp = ip_tunnel.tunnel_id;
  if (verbose >= 1) {
    printf("created tunnel initiator gport : 0x%08x vlan : %d "
        "g_vxlan.tunnel_init_intf_id : 0x%08x\n", *tunnel_gportp,
        tunnel_vlan, g_vxlan.tunnel_init_intf_id);
  }

  return rv;
}

/*****************************************************************//**
 * \brief Create Egress FEC object
 *
 * \param unit           [IN]     Unit number
 * \param tunnel_vlan    [IN]     Tunnel VLAN ID
 * \param tunnel_port    [IN]     Tunnel Port
 * \param tunnel_fec_p   [IN/OUT] Parameters required to hold FEC object
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_vxlan_egress_tunnel_fec_create(
    int unit, int tunnel_vlan,
    int tunnel_port, opennsl_if_t * tunnel_fec_p)
{
  int rv;

  /* tunnel info */
  opennsl_mac_t next_hop_mac;

  /*** create egress object: points into tunnel, with allocating FEC, and da-mac = next_hop_mac  ***/
  struct create_l3_egress_s l3eg1;

  memcpy(next_hop_mac, ip_tunnel_glbl_info.ip_tunnel_info.da, sizeof(opennsl_mac_t));
  memset(&l3eg1, 0, sizeof(l3eg1));
  memcpy(l3eg1.next_hop_mac_addr, next_hop_mac, sizeof(opennsl_mac_t));
  l3eg1.out_tunnel_or_rif = g_vxlan.tunnel_init_intf_id;
  l3eg1.out_gport         = portmap[tunnel_port];
  l3eg1.vlan              = tunnel_vlan;
  l3eg1.fec_id = 0;             /* This may not matter so much, sarath */
  l3eg1.arp_encap_id = 0;

  rv = example_l3_egress_create(unit, &l3eg1);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to create L3 egress object, Error %s\n", opennsl_errmsg(rv));
    return rv;
  }

  /* interface for ip_tunnel is egress-object (FEC) */
  *tunnel_fec_p = l3eg1.fec_id;
  if (verbose >= 1) {
    printf("Created FEC-id = 0x%08x\n", *tunnel_fec_p);
  }

  return rv;
}

/*****************************************************************//**
 * \brief Create ipv4 tunnel
 *
 * \param unit    [IN]     Unit number
 * \param itf     [IN/OUT] Placement of the tunnel as encap-id
 * \param tunnel  [IN]     Update to include the placement of the created
 *                          tunnel as gport
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_ip_tunnel_add(int unit, opennsl_if_t * itf,
    opennsl_tunnel_initiator_t * tunnel)
{

  opennsl_l3_intf_t l3_intf;
  int rv = OPENNSL_E_NONE;

  opennsl_l3_intf_t_init(&l3_intf);

  /* if given ID is set, then use it as placement of the ipv4-tunnel */
  if (*itf != 0) {
    OPENNSL_GPORT_TUNNEL_ID_SET(tunnel->tunnel_id, *itf);
    tunnel->flags |= OPENNSL_TUNNEL_WITH_ID;
  }

  rv = opennsl_tunnel_initiator_create(unit, &l3_intf, tunnel);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to create tunnel initiator, Error %s\n", opennsl_errmsg(rv));
    return rv;
  }

  /* include interface-id points to the tunnel */
  *itf = l3_intf.l3a_intf_id;
  return rv;
}

/*****************************************************************//**
 * \brief To initialize vxlan_port_add_s
 *
 * \param vxlan_port_add  [IN/OUT] vxlan_port_add_s structure
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_vxlan_port_s_clear(
    struct vxlan_port_add_s * vxlan_port_add)
{

  memset(vxlan_port_add, 0, sizeof(*vxlan_port_add));

  /* by default, egress orientatino is set by vxlan port */
  vxlan_port_add->set_egress_orientation_using_vxlan_port_add = 1;

  return OPENNSL_E_NONE;
}

/*****************************************************************//**
 * \brief Add gport of type vlan-port to the multicast
 *
 * \param unit         [IN]  Unit number
 * \param mc_group_id  [IN]  Multicast group ID
 * \param sys_port     [IN]  System Port
 * \param gport        [IN]  gport
 * \param is_egress    [IN]  If true, add ingress multicast entry
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_multicast_vxlan_port_add(int unit, int mc_group_id,
    int sys_port, int gport, uint8 is_egress)
{

  int encap_id;
  int rv = OPENNSL_E_NONE;

  rv = opennsl_multicast_vxlan_encap_get(unit, mc_group_id, sys_port, gport, &encap_id);
  if (rv != OPENNSL_E_NONE) {
    printf
      ("Failed to vxlan encapsulation ID for mc_group_id: 0x%08x "
       "phy_port: 0x%08x gport: 0x%08x, Error %s\n",
       mc_group_id, sys_port, gport, opennsl_errmsg(rv));
    return rv;
  }
  rv = opennsl_multicast_ingress_add(unit, mc_group_id, sys_port, encap_id);
  /* if the MC entry already exist, then we shouldn't add it twice to the multicast group */
  if (rv == OPENNSL_E_EXISTS) {
    printf("The multicast entry already exists \n");
    rv = OPENNSL_E_NONE;
  } else if (rv != OPENNSL_E_NONE) {
    printf("Failed to update ingress multicast group for mc_group_id: 0x%08x "
        "phy_port: 0x%08x encap_id: 0x%08x, Error %s\n",
        mc_group_id, sys_port, encap_id, opennsl_errmsg(rv));
    return rv;
  }
  printf("Added sys_port %d to mc_group_id %d encap_id: 0x%08x\n", sys_port, mc_group_id, encap_id);

  return rv;
}

/*****************************************************************//**
 * \brief To create VxLAN port
 *
 * \param unit            [IN]      Unit number
 * \param vxlan_port_add  [IN/OUT]  VxLAN Port information
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_vxlan_port_add(
    int unit, struct vxlan_port_add_s *vxlan_port_add)
{
  int rv = OPENNSL_E_NONE;
  opennsl_vxlan_port_t vxlan_port;

  opennsl_vxlan_port_t_init(&vxlan_port);

  vxlan_port.criteria         = OPENNSL_VXLAN_PORT_MATCH_VN_ID;
  vxlan_port.match_port       = vxlan_port_add->in_port;
  vxlan_port.match_tunnel_id  = vxlan_port_add->in_tunnel;
  vxlan_port.egress_if        = vxlan_port_add->egress_if;
  vxlan_port.egress_tunnel_id = vxlan_port_add->out_tunnel;
  vxlan_port.flags            = vxlan_port_add->flags | OPENNSL_VXLAN_PORT_EGRESS_TUNNEL;

  /* set orientation, work for Jericho.
   * For Jericho, we configure orientation at ingress (inLif) and egress (outLif): 
   * ingress orientation is configured at opennsl_vxlan_port_add. 
   * egress orientation can be configured using opennsl_vxlan_port_add or at opennsl_port_class_set
   */
  /* flag indicating network orientation.
   * Used to configure ingress orientation and optionally egress orientation */
  vxlan_port.flags |= OPENNSL_VXLAN_PORT_NETWORK;
  vxlan_port.network_group_id = vxlan_port_add->network_group_id; /* TO FIX g_vxlan.vxlan_network_group_id;  */

  rv = opennsl_vxlan_port_add(unit, vxlan_port_add->vpn, &vxlan_port);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to add vxlan port, Error %s\n", opennsl_errmsg(rv));
    return rv;
  }

  vxlan_port_add->vxlan_port_id = vxlan_port.vxlan_port_id;

  if (verbose >= 2) {
    printf("vxlan port created, vxlan_port_id: 0x%08x \n",
        vxlan_port.vxlan_port_id);
    printf("vxlan port is config with:\n");
    printf("  ip in tunnel termination gport:0x%08x  \n", vxlan_port_add->in_tunnel);
    if (vxlan_port_add->egress_if != 0) {
      printf("  FEC entry (contains ip tunnel encapsulation information):0x%08x \n",
          vxlan_port_add->egress_if);
    } else {
      printf("  ip tunnel initiator gport:0x%08x\n", vxlan_port_add->out_tunnel);
    }
    printf("  vpn: 0x%08x\n\r", vxlan_port_add->vpn);
    printf("  vxlan lif orientation: network_group_id = %d\n\r", vxlan_port_add->network_group_id);
  }

  rv = example_multicast_vxlan_port_add(unit, g_vxlan.mc_group_id,
      vxlan_port.match_port, vxlan_port.vxlan_port_id, egress_mc);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to add vxlan port to multicast group, Error %s\n", opennsl_errmsg(rv));
    return rv;
  }
  if (verbose >= 2) {
    printf("add vxlan-port 0x%08x to VPN flooding group %d (0x%08x)\n\r",
        vxlan_port.vxlan_port_id, g_vxlan.mc_group_id, g_vxlan.mc_group_id);
  }

  return rv;
}

/*****************************************************************//**
 * \brief To initialize the global VxLAN structure
 *
 * \param unit     [IN]  Unit number
 * \param vx_info  [IN]  VxLAN structure
 *
 * \return void
 ********************************************************************/
void vxlan_init(int unit, struct vxlan_s *vx_info)
{
  if (vx_info != NULL) {
    memcpy(&g_vxlan, vx_info, sizeof(g_vxlan));
  }
}

/*****************************************************************//**
 * \brief To copy the global VxLAN structure
 *
 * \param unit     [IN]  Unit number
 * \param vx_info  [IN]  VxLAN structure
 *
 * \return void
 ********************************************************************/
void vxlan_struct_get(struct vxlan_s *vx_info)
{
  memcpy(vx_info, &g_vxlan, sizeof(g_vxlan));
}

/*****************************************************************//**
 * \brief To build L2 VPN
 *
 * \param unit            [IN]      Unit number
 * \param vpn             [IN]      VPN ID
 * \param vni             [IN]      VN ID
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_vxlan_open_vpn(int unit, int vpn, int vni)
{
  int rv = OPENNSL_E_NONE;
  int mc_group_id = vpn;

  egress_mc = 0;
  rv = example_multicast_group_open(unit, &mc_group_id,
      OPENNSL_MULTICAST_TYPE_L2);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to create multicast group, Error %s\n", opennsl_errmsg(rv));
    return rv;
  }

  opennsl_vxlan_vpn_config_t vpn_config;
  opennsl_vxlan_vpn_config_t_init(&vpn_config);

  vpn_config.flags =
    OPENNSL_VXLAN_VPN_ELAN | OPENNSL_VXLAN_VPN_WITH_ID | OPENNSL_VXLAN_VPN_WITH_VPNID;
  vpn_config.vpn                      = vpn;
  vpn_config.broadcast_group          = mc_group_id;
  vpn_config.unknown_unicast_group    = mc_group_id;
  vpn_config.unknown_multicast_group  = mc_group_id;
  vpn_config.vnid                     = vni;
  if (g_vxlan.vxlan_vdc_enable) {
    vpn_config.match_port_class = vdc_port_class;
  }

  rv = opennsl_vxlan_vpn_create(unit, &vpn_config);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to create vxlan vpn, Error %s\n", opennsl_errmsg(rv));
    return rv;
  }
  if (verbose >= 1) {
    printf("Created vpn %d (0x%08x)\n\r", vpn, vpn);
  }

  return rv;
}

/*****************************************************************//**
 * \brief To create inLif for a port
 *
 * \param unit       [IN]      Unit number
 * \param in_port    [IN]      Port number
 * \param port_id    [OUT]     inLif port idenfier
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_vlan_inLif_create(int unit, opennsl_gport_t in_port,
    opennsl_gport_t *port_id)
{
  int rv;
  opennsl_vlan_port_t vport1;
  opennsl_vlan_port_t_init(&vport1);
  vport1.criteria        = OPENNSL_VLAN_PORT_MATCH_PORT_VLAN;
  vport1.port            = in_port;
  vport1.match_vlan      = ip_tunnel_glbl_info.access_vlan;
  vport1.egress_vlan     = ip_tunnel_glbl_info.access_vlan;
  vport1.flags           = 0;
  vport1.vsi             = 0;
  rv = opennsl_vlan_port_create(unit, &vport1);

  if (rv != OPENNSL_E_NONE) {
    printf("Failed to create vlan_port filter, Error %s\n", opennsl_errmsg(rv));
    return rv;
  }

  if (verbose >= 2) {
    printf
      ("Add vlan-port-id: 0x%08x in-port: %d (0x%08x) match_vlan: %d "
       "egress_vlan: %d match_inner_vlan: %d\n\r", vport1.vlan_port_id,
       vport1.port, vport1.port, vport1.match_vlan, vport1.egress_vlan,
       vport1.match_inner_vlan);
  }

  /* handle of the created gport */
  *port_id = vport1.vlan_port_id;

  return rv;
}

/*****************************************************************//**
 * \brief Main function to build VxLAN IP tunnel
 *     - build IP tunnels.
 *     - add ip routes/host points to the tunnels
 *
 * \param unit          [IN]      Unit number
 * \param network_port  [IN]      Network Port number
 * \param access_port   [IN]      Access Port number
 * \param vpn_id        [IN]      VPN ID
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int example_vxlan(
    int unit,
    int network_port,
    int access_port,
    int vpn_id)
{
  int rv = OPENNSL_E_NONE;
  int vxlan_port_flags = 0;
  struct vxlan_port_add_s vxlan_port_add;

  /* init vxlan global */
  struct vxlan_s vxlan_param;
  vxlan_struct_get(&vxlan_param);
  if (vpn_id >= 0) {
    vxlan_param.vpn_id = vpn_id;
  }
  vxlan_init(unit, &vxlan_param);
  vpn_id = g_vxlan.vpn_id;
  init_portmap(unit);

  printf("Parameters \n");
  printf("Ports (Network: %d, Access: %d)\n", network_port, access_port);
  printf("Vlans (Provider:%d Tunnel:%d Access:%d)\n",
      ip_tunnel_glbl_info.provider_vlan,
      ip_tunnel_glbl_info.tunnel_vlan,
      ip_tunnel_glbl_info.access_vlan);
  printf("VPN: %d VNI: %d(0x%x)\n", vpn_id, g_vxlan.vni, g_vxlan.vni);
  g_vxlan.access_port  = access_port;
  g_vxlan.network_port = network_port;

  example_vxlan_port_s_clear(&vxlan_port_add);
  /* config ports as local ports i.e Works as egress port */
  opennsl_switch_control_set(unit, opennslSwitchVxlanUdpDestPortSet, 0x12b5);

  verbose = 10;

  /* init L2 VXLAN module */
  rv = opennsl_vxlan_init(unit);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to initialize vxlan, Error %s\n", opennsl_errmsg(rv));
  }

  /*** Add the ports to VLANs ***/
  example_add_ports_to_vlans(unit, network_port, access_port);

  /* build L2 VPN */
  rv = example_vxlan_open_vpn(unit, vpn_id, g_vxlan.vni);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to open vpn %d, Error %s\n", vpn_id, opennsl_errmsg(rv));
  }

  /* Create inLif for access port */
  rv = example_vlan_inLif_create(unit, access_port, &g_vxlan.vlan_inLif);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to create VLAN inLIF 0x%08x, Error %s\n", g_vxlan.vlan_inLif,
        opennsl_errmsg(rv));
  }

  /* Add inLif to VSI and add it flood MC group */
  rv = example_add_inLif_to_vswitch(unit, vpn_id, access_port, g_vxlan.vlan_inLif);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to add inLif to VSI or adding access port to multicast "
        "group, Error %s\n", opennsl_errmsg(rv));
    return rv;
  }

  /*** build tunnel initiator ***/
  rv = example_vxlan_egress_tunnel_create(unit, ip_tunnel_glbl_info.tunnel_vlan,
      &g_vxlan.tunnel_init_gport);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to build tunnel initiator network_port %d, Error %s\n",
        network_port, opennsl_errmsg(rv));
  }

  /*** build tunnel FEC ***/
  rv = example_vxlan_egress_tunnel_fec_create(unit, ip_tunnel_glbl_info.tunnel_vlan,
      network_port, &g_vxlan.vxlan_fec_intf_id);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to create FEC, network_port %d, Error %s\n",
        network_port, opennsl_errmsg(rv));
  }

  if (verbose >= 2) {
    printf("out-tunnel gport-id: 0x%08x FEC-id:0x%08x\n\r",
        g_vxlan.tunnel_init_gport, g_vxlan.vxlan_fec_intf_id);
  }

  /* tunnel termination configuration */
  if (g_vxlan.dip_sip_vrf_using_my_vtep_index_mode == 0) {
    /*** build tunnel termination  ***/
    rv = example_vxlan_tunnel_terminator_create(unit, &g_vxlan.tunnel_term_gport);
    if (rv != OPENNSL_E_NONE) {
      printf("Failed to build tunnel termination, Error %s\n", opennsl_errmsg(rv));
      return rv;
    }

    /*** create L3 interface on provider_vlan, not using it explicitly, but used in pipeline */
    rv = example_ip_tunnel_term_create_l3_intf(unit, ip_tunnel_glbl_info.provider_vlan);
    if (rv != OPENNSL_E_NONE) {
      printf("Failed to create L3 interface on provider VLAN, Error %s\n", opennsl_errmsg(rv));
    }

    if (verbose >= 2) {
      printf("in-tunnel gport-id: 0x%08x L3 itf:%x\r", g_vxlan.tunnel_term_gport, g_vxlan.prov_vlan_l3_intf_id);
    }
    /* build l2 vxlan ports */
    vxlan_port_add.network_group_id = g_vxlan.vxlan_network_group_id;
  }
  /* create VxLAN gport using tunnel inlif */
  vxlan_port_add.vpn         = vpn_id;
  vxlan_port_add.in_port     = network_port;
  vxlan_port_add.in_tunnel   = g_vxlan.tunnel_term_gport;
  vxlan_port_add.out_tunnel  = g_vxlan.tunnel_init_gport;
  vxlan_port_add.egress_if   = g_vxlan.vxlan_fec_intf_id;
  vxlan_port_add.flags       = vxlan_port_flags;

  rv = example_vxlan_port_add(unit, &vxlan_port_add);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to add vxlan tunnel, in_gport=0x%08x --> out_intf=0x%08x, "
        "Error %s\n", g_vxlan.tunnel_term_gport,
        g_vxlan.vxlan_fec_intf_id, opennsl_errmsg(rv));
    return rv;
  }

  g_vxlan.vxlan_gport = vxlan_port_add.vxlan_port_id;

  if (verbose >= 2) {
    printf("vxlan port created, vxlan_port_id: 0x%08x \n", g_vxlan.vxlan_gport);
  }

  /* add mact entries point to created gports */
  rv = example_l2_addr_add(unit, g_vxlan.user_mac_address, vpn_id, g_vxlan.vlan_inLif);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to update FDB for vlan %d port 0x%08x, Error %s\n",
        vpn_id, g_vxlan.vlan_inLif, opennsl_errmsg(rv));
    return rv;
  }

  rv = example_l2_addr_add(unit, g_vxlan.tunnel_mac_address, vpn_id, g_vxlan.vxlan_gport);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to update FDB for vlan %d port 0x%08x, Error %s\n",
        vpn_id, g_vxlan.vxlan_gport, opennsl_errmsg(rv));
    return rv;
  }

  /* adding a registered MC using flood MC */
  opennsl_l2_addr_t l2addr;
  opennsl_l2_addr_t_init(&l2addr, g_vxlan.mc_mac, vpn_id);

  l2addr.l2mc_group = g_vxlan.mc_group_id;
  l2addr.flags      = OPENNSL_L2_STATIC | OPENNSL_L2_MCAST;

  rv = opennsl_l2_addr_add(unit, &l2addr);
  if (rv != OPENNSL_E_NONE) {
    printf("Failed to FDB with multicast entry, Error %s\n", opennsl_errmsg(rv));
    return rv;
  }

  return rv;
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
  int unit = DEFAULT_UNIT;
  int port_a;
  int port_n;
  int vpn_id;

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

  /* cold boot initialization commands */
  rv = example_port_default_config(unit);
  if (rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to apply default config on ports, rv = %d (%s).\r\n",
        rv, opennsl_errmsg(rv));
  }

  while (1) {
    printf("\r\nUser menu: Select one of the following options\r\n");
    printf("1. Configure VxLAN segment\n");
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
          /* Configure VXLAN settings for access and network ports */
          printf("a. Enter Access port number\n");
          if(example_read_user_choice(&port_a) != OPENNSL_E_NONE)
          {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
          }

          printf("b. Enter Network port number\n");
          if(example_read_user_choice(&port_n) != OPENNSL_E_NONE)
          {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
          }

          printf("c. Enter VPN ID (Ex: 9216)\n");
          if(example_read_user_choice(&vpn_id) != OPENNSL_E_NONE)
          {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
          }

          rv = example_vxlan(unit, port_n, port_a, vpn_id); 
          if(rv != OPENNSL_E_NONE)
          {
            printf("\r\nVxLAN configuration has failed.\n");
            return rv;
          }

          printf("\r\nVxLAN configuration is done successfully\n");
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
