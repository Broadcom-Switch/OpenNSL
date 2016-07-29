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
 * \file         example_bst.c
 *
 * \brief        OpenNSL example program for showing statistics
 *
 * \details      OpenNSL example program for displaying and clearing BST
 *               statistics of a given interface.
 *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <opennsl/error.h>
#include <opennsl/cosq.h>
#include <opennsl/vlan.h>
#include <opennsl/switch.h>
#include <sal/driver.h>
#include <examples/util.h>

#define DEFAULT_VLAN 1
#define MAX_COUNTERS 4
#define MAX_COSQ_COUNT 8
#define DEFAULT_UNIT 0
#define MAX_DIGITS_IN_CHOICE 5

char example_usage[] =
"Syntax: example_bst                                                   \n\r"
"                                                                      \n\r"
"Paramaters: None                                                      \n\r"
"                                                                      \n\r"
"Example: The following command is used to see the bst stats of a port \n\r"
"         example_bst                                                  \n\r"
"                                                                      \n\r"
"Usage Guidelines: This program request the user to enter the port     \n\r"
"                  number interactively                                \n\r";

typedef struct {
  opennsl_bst_stat_id_t bid;
  char name[50];
} example_bst_counter_t;


#define _BST_STAT_ID_DEVICE                    opennslBstStatIdDevice
#define _BST_STAT_ID_EGR_POOL                  opennslBstStatIdEgrPool
#define _BST_STAT_ID_EGR_MCAST_POOL            opennslBstStatIdEgrMCastPool
#define _BST_STAT_ID_ING_POOL                  opennslBstStatIdIngPool
#define _BST_STAT_ID_PORT_POOL                 opennslBstStatIdPortPool
#define _BST_STAT_ID_PRI_GROUP_SHARED          opennslBstStatIdPriGroupShared
#define _BST_STAT_ID_PRI_GROUP_HEADROOM        opennslBstStatIdPriGroupHeadroom
#define _BST_STAT_ID_UCAST                     opennslBstStatIdUcast
#define _BST_STAT_ID_MCAST                     opennslBstStatIdMcast
#define _BST_STAT_ID_EGR_UCAST_PORT_SHARED     opennslBstStatIdEgrUCastPortShared
#define _BST_STAT_ID_EGR_PORT_SHARED           opennslBstStatIdEgrPortShared
#define _BST_STAT_ID_RQE_QUEUE                 opennslBstStatIdRQEQueue
#define _BST_STAT_ID_RQE_POOL                  opennslBstStatIdRQEPool
#define _BST_STAT_ID_UCAST_GROUP               opennslBstStatIdUcastGroup
#define _BST_STAT_ID_CPU                       opennslBstStatIdCpuQueue
#define _BST_STAT_ID_MAX_COUNT                 opennslBstStatIdMaxCount

/*****************************************************************//**
 * \brief To set the default BST profiles
 *
 * \param unit      [IN]    Unit number
 *
 * \return None
 * \remarks This function is currently support for Trident 2 silicon only
 ********************************************************************/
int example_bst_default_profile_set (int unit)
{
  int rc;
  int bid;
  int depth;
  int index;
  int max_threshold;
  int max_ports;
  int gport;
  int port;
  opennsl_cosq_bst_profile_t profile;

  /* Get maximum number of front panel ports available */
  if((rc = example_max_port_count_get(unit, &max_ports)) != OPENNSL_E_NONE)
  {
    printf("\r\nFailed to get number of front panel ports, rc = %d (%s).\r\n",
        rc, opennsl_errmsg(rc));
    return OPENNSL_E_FAIL;
  }

  for (bid = 0; bid < opennslBstStatIdMaxCount; bid++) {

    /* Find out the maximum threshold for a bid */
    if (bid == opennslBstStatIdUcast              ||
        bid == opennslBstStatIdEgrUCastPortShared ||
        bid == opennslBstStatIdUcastGroup) {
      max_threshold =  0x3FFF * 208;
    } else if (bid == opennslBstStatIdPriGroupHeadroom) {
      max_threshold =  0xFFF * 208;
    } else {
      max_threshold =  0x1FFFF * 208;
    }

    profile.byte = max_threshold;

    if (bid == _BST_STAT_ID_EGR_POOL              ||
        bid == _BST_STAT_ID_EGR_MCAST_POOL        ||
        bid == _BST_STAT_ID_EGR_UCAST_PORT_SHARED ||
        bid == _BST_STAT_ID_EGR_PORT_SHARED       ||
        bid == _BST_STAT_ID_UCAST_GROUP           ||
        bid == _BST_STAT_ID_PORT_POOL             ||
        bid == _BST_STAT_ID_ING_POOL)
    {
      depth = 4;
    }
    else if (bid == _BST_STAT_ID_PRI_GROUP_SHARED ||
        bid == _BST_STAT_ID_PRI_GROUP_HEADROOM    ||
        bid == _BST_STAT_ID_UCAST                 ||
        bid == _BST_STAT_ID_MCAST)
    {
      depth = 8;
    }
    else if (bid == _BST_STAT_ID_RQE_QUEUE)
    {
      depth = 11;
    }
    else
    {
      depth = 1;
    }

    /* Set default BST profiles */
    if (bid == _BST_STAT_ID_ING_POOL       ||
        bid == _BST_STAT_ID_EGR_MCAST_POOL ||
        bid == _BST_STAT_ID_EGR_POOL       ||
        bid == _BST_STAT_ID_RQE_QUEUE      ||
        bid == _BST_STAT_ID_UCAST_GROUP    ||
        bid == _BST_STAT_ID_DEVICE)
    {
       gport = 0;
       for (index = 0; index < depth; index++)
       {
         rc = opennsl_cosq_bst_profile_set (unit, gport, index, bid, &profile);
         if (rc != OPENNSL_E_NONE)
         {
           printf("\r\nFailed to set the BST profile for gport %d bid %d index %d, rc = %d (%s).\r\n",
               gport, bid, index, rc, opennsl_errmsg(rc));
           return rc;
         }
       } /* Iter ... Cosq*/
    }
    else if (bid == _BST_STAT_ID_PRI_GROUP_SHARED      ||
             bid == _BST_STAT_ID_PRI_GROUP_HEADROOM    ||
             bid == _BST_STAT_ID_UCAST                 ||
             bid == _BST_STAT_ID_MCAST                 ||
             bid == _BST_STAT_ID_PORT_POOL             ||
             bid == _BST_STAT_ID_EGR_PORT_SHARED       ||
             bid == _BST_STAT_ID_EGR_UCAST_PORT_SHARED)
    {
      for(port = 1; port < max_ports; port++)
      {
        /* Get GPORT*/
        rc = opennsl_port_gport_get (unit, port, &gport);
        if (rc != OPENNSL_E_NONE)
        {
           printf("\r\nFailed to get gport for port %d, rc = %d (%s).\r\n",
               port, rc, opennsl_errmsg(rc));
           return rc;
        }

        for (index = 0; index < depth; index++)
        {
          rc = opennsl_cosq_bst_profile_set (unit, gport, index, bid, &profile);
          if (rc != OPENNSL_E_NONE)
          {
            printf("\r\nFailed to set the BST profile for gport %d bid %d index %d, rc = %d (%s).\r\n",
                gport, bid, index, rc, opennsl_errmsg(rc));
            return rc;
          }
        } /* Iter ... index */
      } /* Iter ... port */
    }

  } /* Iter ... bid */

  return 0;
}

/*****************************************************************//**
 * \brief Callback function to capture BST triggers
 *
 * \param unit      [IN]    Unit number
 * \param event     [IN]    BST event
 * \param bid       [IN]    BST ID
 * \param port      [IN]    Port number
 * \param cosq      [IN]    COS queue
 * \param cookie    [IN]    To hold the data from register function
 *
 * \return None
 ********************************************************************/
void example_bst_trigger_callback (int unit, opennsl_switch_event_t event,
    uint32 bid, uint32 port, uint32 cosq, void *cookie)
{
  printf("BST trigger kicked in, event %d port %d bid %d cosq %d\n", event, port, bid, cosq);
  printf("BST feature is disabled.\n");
  return;
}

/*****************************************************************//**
 * \brief Main function for bst sample application
 *
 * \param argc, argv         commands line arguments
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
/* Main function for BST application */
int main(int argc, char *argv[])
{
  opennsl_error_t   rc;
  int choice;
  int unit = DEFAULT_UNIT;
  int index,i,j;
  opennsl_gport_t gport;
  opennsl_port_t port;
  opennsl_cos_queue_t cosq;
  uint32 options = 0;
  void *user_data = NULL;

  example_bst_counter_t id_list[MAX_COUNTERS] = {
    {opennslBstStatIdUcast,            "opennslBstStatIdUcast"},
    {opennslBstStatIdMcast,            "opennslBstStatIdMcast"},
    {opennslBstStatIdPriGroupShared,   "opennslBstStatIdPriGroupShared"},
    {opennslBstStatIdPriGroupHeadroom, "opennslBstStatIdPriGroupHeadroom"}
  };
  uint64 val[MAX_COUNTERS][MAX_COSQ_COUNT];

  /* Intitializing val array */
  for (i = 0; i < MAX_COUNTERS; i++) {
    for (j = 0; j < MAX_COSQ_COUNT; j++) {
        val[i][j] = 0;
    }
  }

  if ((argc != 1) || ((argc > 1) && (strcmp(argv[1], "--help") == 0))) {
    printf("%s\n\r", example_usage);
    return OPENNSL_E_PARAM;
  }

  /* Initialize the system. */
  printf("Initializing the system.\r\n");
  rc = opennsl_driver_init((opennsl_init_t *) NULL);

  if (rc != OPENNSL_E_NONE) {
    printf("\r\nFailed to initialize the system, rc = %d (%s).\r\n",
           rc, opennsl_errmsg(rc));
    return 0;
  }

  /* Add ports to default vlan. */
  printf("Adding ports to default vlan.\r\n");
  rc = example_switch_default_vlan_config(unit);
  if (rc != OPENNSL_E_NONE) {
    printf("\r\nFailed to add default ports, rc = %d (%s).\r\n",
           rc, opennsl_errmsg(rc));
  }

  rc = example_port_default_config(unit);
  if (rc != OPENNSL_E_NONE)
  {   
    printf("\r\nFailed to apply default config on ports, rc = %d (%s).\r\n",
        rc, opennsl_errmsg(rc));
  } 

  /* Set default BST profiles */
  rc = example_bst_default_profile_set (unit);
  if (rc != OPENNSL_E_NONE) {
    printf("\r\nFailed to set default profile for BST, rc = %d (%s).\r\n",
        rc, opennsl_errmsg(rc));
  }
  printf("Default BST profiles are set successfully.\r\n");

  /* Register Hw trigger callback*/
  rc = opennsl_switch_event_register (unit,
      example_bst_trigger_callback,
      user_data);
  if (rc != OPENNSL_E_NONE)
  {
    printf("\r\nFailed to register BST callback, rc = %d (%s).\r\n",
        rc, opennsl_errmsg(rc));
    return OPENNSL_E_FAIL;
  }
  printf("BST callback for triggers is registered.\r\n");

  /* Enabling bst module. */
  rc = opennsl_switch_control_set(unit, opennslSwitchBstEnable, 1);
  if (rc != OPENNSL_E_NONE) {
    printf("\r\nFailed to Enable bst, rc = %d (%s).\r\n",
        rc, opennsl_errmsg(rc));
    return 0;
  }
  printf("BST feature is enabled.\r\n");


  while (1) {
    printf("\nUser Menu: Select one of the following options\n");
    printf("1. Enable/Disable BST feature.\n");
    printf("2. Display BST statistics of a port.\n");
    printf("3. Clear BST statistics of a port.\n");
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
          printf("\r\nConfigure BST feature: 1-Enable, 0-Disable.\r\n");
          if(example_read_user_choice(&choice) != OPENNSL_E_NONE)
          {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
          }
          if((choice != 0) && (choice != 1))
          {
            printf("Invalid input. Please re-enter.\n");
            continue;
          }

          rc = opennsl_switch_control_set(unit, opennslSwitchBstEnable, choice);
          if (rc != OPENNSL_E_NONE) {
            printf("\r\nFailed to %s BST feature, rc = %d (%s).\r\n",
                (choice == 0)? "Disable" : "Enable", rc, opennsl_errmsg(rc));
            return OPENNSL_E_FAIL;
          }

          printf("BST feature is %s.\r\n", (choice == 0)? "Disabled" : "Enabled");
          break;
        } /* End of case 1 */

      case 2:
        {
          printf("\r\nEnter the port number.\r\n");
          if(example_read_user_choice(&port) != OPENNSL_E_NONE)
          {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
          }
          rc = opennsl_port_gport_get (unit, port, &gport);
          if (rc != OPENNSL_E_NONE)
          {
            return OPENNSL_E_FAIL;
          }
          for (index = 0; index < MAX_COUNTERS; index++)
          {
            rc = (opennsl_cosq_bst_stat_sync(unit, id_list[index].bid));
            if (rc != OPENNSL_E_NONE) {
            printf("\r\nFailed to sync the state of port, rc = %d (%s).\r\n",
                   rc, opennsl_errmsg(rc));
            break;
          }
        }

        for (index = 0; index < MAX_COUNTERS; index++)
        {
          for (cosq = 0; cosq <=7; cosq++)
          {
            rc = opennsl_cosq_bst_stat_get(unit, gport, cosq,
                id_list[index].bid, options, &val[index][cosq]);
            if (rc != OPENNSL_E_NONE) {
              printf("\r\nFailed to get the port stats, rc = %d (%s).\r\n",
                     rc, opennsl_errmsg(rc));
              break;
            }
            printf("BST Counter: %s for COS queue: %d is : %llu\n",
                id_list[index].name, cosq, val[index][cosq]);
          }
          printf("\n");
        }

        break;
      } /* End of case 2 */

      case 3:
      {
        printf("\r\nEnter the port number.\r\n");
        if(example_read_user_choice(&port) != OPENNSL_E_NONE)
        {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
        }
        rc = opennsl_port_gport_get (unit, port, &gport);
        if (rc!= OPENNSL_E_NONE)
        {
          return OPENNSL_E_FAIL;
        }

        for (index = 0; index < MAX_COUNTERS; index++)
        {
          for (cosq = 0; cosq <= 7; cosq++)
          {
            rc = opennsl_cosq_bst_stat_clear(unit, gport, cosq,
                id_list[index].bid);
            if (rc != OPENNSL_E_NONE) {
              printf("\r\nFailed to clear the port stats, rc = %d (%s).\r\n",
                     rc, opennsl_errmsg(rc));
              break;
            }
          }
          printf("\n");
        }

        printf("\r\nPort %d stats cleared\r\n", port);
        break;
      } /* End of case 3 */

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

      default :
        break;
    } /* End of switch */
  } /* End of while */

  return 0;
}
