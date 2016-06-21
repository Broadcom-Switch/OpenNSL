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
 * \file         example_knet.c
 *
 * \brief        OpenNSL example application to demonstrate KNET module
 *
 * \details      This application allows the user to
 *               1) Create KNET interfaces that map to switch physical
 *               interfaces. These can be configurable from Linux command
 *               line interface.
 *               2) Delete KNET interface.
 *               3) List KNET interfaces.
 *
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sal/driver.h>
#include <opennsl/error.h>
#include <opennsl/vlan.h>
#include <opennsl/knet.h>
#include <examples/util.h>

#define DEFAULT_UNIT 0
#define DEFAULT_PORT 1
#define DEFAULT_VLAN 1
#define MAX_DIGITS_IN_CHOICE 5
#define KNET_INTF_COUNT 20
#define IP_ADDR_LEN 16
#define NETMASK_LEN 16

char example_usage[] =
"Syntax: example_knet                                                  \n\r"
"                                                                      \n\r"
"Paramaters: None.                                                     \n\r"
"                                                                      \n\r"
"Example: The following command is used to create KNET interfaces      \n\r"
"         that can be configurable from Linux shell.                   \n\r"
"         example_knet                                                 \n\r"
"                                                                      \n\r"
"Usage Guidelines: This program request the user to enter the following\n\r"
"                  parameters interactively                            \n\r"
"       port    - port number                                          \n\r"
"       ifName  - interface name                                       \n\r"
"       ipaddr  - IP adddress to be assigned to the interface          \n\r"
"       netmask - IP netmask to be assigned to the interface           \n\r"
"                                                                      \n\r"
"       Testing:                                                       \n\r"
"       1) Assign IP address to the interface using Create KNET        \n\r"
"          interface option.                                           \n\r"
"       2) Assign IP address to the partner that is connected to       \n\r"
"          physical port in the same subnet.                           \n\r"
"       3) Verify that ping to the IP assigned in step 1 works fine.   \n\r"
"                                                                      \n\r";

/* KNET data structure to store the netif.id and filter.id for
 * KNET interfaces */
typedef struct
{
  int port;
  int netIfID;
  int filterID;
  char name[OPENNSL_KNET_NETIF_NAME_MAX];
} knet_if_data_t;

knet_if_data_t knet_if_data[KNET_INTF_COUNT];
int knet_intf_count = 0;

/**************************************************************************//**
 * \brief   Update KNET interface database.
 *
 * \param   port         [IN] port number
 * \param   ifName       [IN] interface name
 * \param   nID          [IN] KNET interface ID
 * \param   fID          [IN] KNET filter ID
 *
 * \returns None
 *****************************************************************************/
void example_knet_database_update(int port, char *ifName, int nID, int fID)
{
  int i;
  int entryFound = 0;

  for(i = 0; i < KNET_INTF_COUNT; i++)
  {
    /* Check if the entry for the given port is already present */
    if(port == knet_if_data[i].port)
    {
      entryFound = 1;
      break;
    }
  }

  if(entryFound == 0)
  {
    /* Find the first free entry */
    for(i = 0; i < KNET_INTF_COUNT; i++)
    {
      if(knet_if_data[i].port == 0)
      {
        break;
      }
    }
  }

  knet_if_data[i].port     = port;
  knet_if_data[i].netIfID  = nID;
  knet_if_data[i].filterID = fID;
  strcpy(knet_if_data[i].name, ifName);

  /* Updated the new entry. So, increment KNET interface count */
  if(entryFound == 0)
  {
    knet_intf_count++;
  }
  return;
}

/**************************************************************************//**
 * \brief   Update KNET interface database.
 *
 * \returns None
 *****************************************************************************/
void example_knet_database_show()
{
  int i;

  if(knet_intf_count == 0)
  {
    printf("KNET interface table is empty.\n\r");
    return;
  }

  printf("Number of KNET interfaces present: %d\n\n\r", knet_intf_count);
  for(i = 0; i < KNET_INTF_COUNT; i++)
  {
    if(knet_if_data[i].port != 0)
    {
      printf("Port: %d Interface Name: %s netifID: %d filterID: %d\n\r",
          knet_if_data[i].port, knet_if_data[i].name,
          knet_if_data[i].netIfID, knet_if_data[i].filterID);
    }
  }
  return;
}

/******************************************************************************
 * \brief     Creates linux interfaces and corresponding KNET filters to map
 *           each front panel interface to these linux interfaces.
 *
 * \param   port         [IN] port number
 * \param   unit         [IN] unit number
 * \param   ifName       [IN] interface name
 *
 * \return  None
 *
 *****************************************************************************/
int example_linux_interface_create(int unit, int port, char *ifName)
{
  int rv;
  opennsl_knet_netif_t  netif;
  opennsl_knet_filter_t filter;
  unsigned char baseMac[6] = { 0x02, 0x10, 0x18, 0x00, 0x00, 0x01 };

  opennsl_knet_netif_t_init(&netif);
  netif.type = OPENNSL_KNET_NETIF_T_TX_LOCAL_PORT;
  netif.port = port; /* Egress port */
  strcpy(netif.name, ifName); /* Copy the base interface name */
  /* Set MAC address associated with this interface */
  memcpy(netif.mac_addr, baseMac, 6);
  rv = opennsl_knet_netif_create(unit, &netif);
  if (rv >= 0)
  {
    printf("Created Interface ID %d for interface name \"%s\" \n",
        netif.id, ifName);
  }
  else
  {
    printf("rv = %d Error creating KNET interface \"%s\" \n", rv, ifName);
    return rv;
  }

  /* Add filter for packets from port */
  opennsl_knet_filter_t_init(&filter);

  filter.type = OPENNSL_KNET_FILTER_T_RX_PKT;

  /*
     This filter is modified to **NOT** STRIP VLAN TAG when this port is
     attached to a bridge
   */

  filter.flags = OPENNSL_KNET_FILTER_F_STRIP_TAG;
  filter.priority = 0;
  /* Send packet to network interface */
  filter.dest_type = OPENNSL_KNET_DEST_T_NETIF;
  filter.dest_id = netif.id;
  filter.match_flags = OPENNSL_KNET_FILTER_M_INGPORT;
  filter.m_ingport = port;

  rv = opennsl_knet_filter_create(unit, &filter);
  if (rv >= 0)
  {
    printf("Created Filter ID %d for interface name \"%s\" \n",
        filter.id, ifName);
  }
  else
  {
    printf("rv  = %d Error creating filter for interface \"%s\" \n",
        rv, ifName);
    return rv;
  }

  /* Update the database */
  example_knet_database_update(port, ifName, netif.id, filter.id);

  return rv;
}

/******************************************************************************
 * \brief   Configure IP address and netmask on the KNET interface.
 *
 * \param   port         [IN] port number
 * \param   unit         [IN] unit number
 * \param   ifName       [IN] interface name
 *
 * \return  None
 *
 *****************************************************************************/
void example_ip_config(char *ifName, char* ip, char* netmask)
{
  char cmd[100];

  memset(cmd, 0, sizeof(cmd));

  sprintf(cmd, "ifconfig %s %s netmask %s", ifName, ip, netmask);
  if(system(cmd) == -1)
  {
    printf("Failed to configure interface \"%s\" with IP: %s Netmask: %s\n",
        ifName, ip, netmask);
    return;
  };

  sprintf(cmd, "ifconfig %s up > /dev/null", ifName);
  if(system(cmd) == -1)
  {
    printf("Failed to bringup interface \"%s\"\n", ifName);
    return;
  };

  printf("Configured interface \"%s\" with IP: %s Netmask: %s\n",
      ifName, ip, netmask);
}

/******************************************************************************
 * \brief   To create KNET interface by taking inputs from the user
 *
 * \param   unit         [IN] unit number
 *
 * \return  None
 *
 *****************************************************************************/
void example_knet_intf_create(int unit)
{
  int port;
  int rv;
  char ifName[OPENNSL_KNET_NETIF_NAME_MAX];
  char ip[IP_ADDR_LEN];
  char netmask[NETMASK_LEN];

  if(knet_intf_count == KNET_INTF_COUNT)
  {
    printf("Maximum number of KNET interfaces are already present.\r\n");
    return;
  }

  printf("\n\rEnter port number: \n");
  if(example_read_user_choice(&port) != OPENNSL_E_NONE)
  {
    printf("Invalid option entered.\n");
    return;
  }
  printf("\n\rEnter knet interface name: ");
  if(example_read_user_string(ifName, sizeof(ifName)) == NULL)
  {
    printf("\n\rInvalid KNET interface is entered.\n\r");
    return;
  }
  printf("\n\rEnter IP address in dotted decimal format: ");
  if(example_read_user_string(ip, sizeof(ip)) == NULL)
  {
    printf("\n\rInvalid IP address is entered.\n\r");
    return;
  }
  printf("\n\rEnter IP netmask in dotted decimal format: ");
  if(example_read_user_string(netmask, sizeof(netmask)) == NULL)
  {
    printf("\n\rInvalid IP netmask is entered.\n\r");
    return;
  }

  /* Create Linux interface. */
  rv = example_linux_interface_create(unit, port, ifName);
  if(rv < 0) {
    printf("Failed to create Linux interface \"%s\". rv: %d\r\n", ifName, rv);
    return;
  }

  printf("Created Linux interface \"%s\" successfully.\r\n", ifName);
  example_ip_config(ifName, ip, netmask);
  return;
}

/******************************************************************************
 * \brief   To delete KNET interface.
 *
 * \param   unit         [IN] unit number
 *
 * \return  None
 *
 *****************************************************************************/
void example_knet_intf_delete(int unit)
{
  int rv;
  int i;
  char ifName[OPENNSL_KNET_NETIF_NAME_MAX];

  if(knet_intf_count == 0)
  {
    printf("\n\rThere are no KNET interfaces present in the system.\n\r");
  }
  printf("\n\rEnter KNET interface name: ");
  if(example_read_user_string(ifName, sizeof(ifName)) == NULL)
  {
    printf("\n\rInvalid KNET interface is entered.\n\r");
    return;
  }

  for(i = 0; i < KNET_INTF_COUNT; i++)
  {
    if(strcmp(ifName, knet_if_data[i].name) == 0)
    {
      break;
    }
  }

  if (i == KNET_INTF_COUNT)
  {
    printf("\n\rThe specific interface is not found.\n\r");
    return;
  }

  /* Destroy KNET interface. */
  rv = opennsl_knet_netif_destroy(unit, knet_if_data[i].netIfID);
  if(rv < 0) {
    printf("Error destroying network interface: %s\n",
        opennsl_errmsg(rv));
    return;
  }

  rv = opennsl_knet_filter_destroy(unit, knet_if_data[i].filterID);
  if(rv < 0) {
    printf("Error destroying packet filter: %s\n",
        opennsl_errmsg(rv));
    return;
  }

  /* Clear the database for the deleted port */
  memset(&knet_if_data[i], 0, sizeof(knet_if_data_t));
  knet_intf_count--;
}

/*****************************************************************//**
 * \brief Main function for KNET sample application
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

  if((argc != 1) || ((argc > 1) && (strcmp(argv[1], "--help") == 0))) {
    printf("%s\n\r", example_usage);
    return OPENNSL_E_PARAM;
  }

  /* Initialize the system */
  rv = opennsl_driver_init((opennsl_init_t *) NULL);

  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to initialize the system. Error %s\r\n",
        opennsl_errmsg(rv));
    return rv;
  }

  /* Add ports to default vlan. */
  printf("Adding ports to default VLAN %d.\r\n", DEFAULT_VLAN);
  rv = example_switch_default_vlan_config(unit);
  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to add ports to default VLAN %d. rv: %d\r\n",
        DEFAULT_VLAN,  rv);
    return rv;
  }

  while(1) {

    printf("\nUser Menu: Select one of the following options\n");
    printf("1. Create KNET interface\n");
    printf("2. Delete KNET interface\n");
    printf("3. Display KNET interface database\n");
#ifdef INCLUDE_DIAG_SHELL
    printf("9. Launch diagnostic shell\n");
#endif
    printf("0. Quit the application.\n");

    if(example_read_user_choice(&choice) != OPENNSL_E_NONE)
    {
      printf("Invalid option entered. Please re-enter.\n");
      continue;
    }
    switch(choice) {
      case 1:
      {
        example_knet_intf_create(unit);
        break;
      }

      case 2:
      {
        example_knet_intf_delete(unit);
        break;
      }

      case 3:
      {
        example_knet_database_show();
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
        break;;
    } /* End of switch */
  } /* End of while */

  return rv;
}
