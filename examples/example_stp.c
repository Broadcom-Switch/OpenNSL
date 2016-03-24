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
 * \file         example_stp.c
 *
 * \brief        OPENNSL example program to demonstrate Spanning Tree
 *               application.
 *
 * \details      This example demonstrates on how to remove a loop by
 *               modifying the spanning tree state of a port.
 *
 *
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sal/driver.h>
#include <opennsl/types.h>
#include <opennsl/port.h>
#include <opennsl/vlan.h>
#include <opennsl/error.h>
#include <opennsl/stg.h>
#include <examples/util.h>

char example_usage[] =
"Syntax: example_stp                                                    \n\r"
"                                                                       \n\r"
"Paramaters:                                                            \n\r"
"       port1  - First port number.                                     \n\r"
"       port2  - Second port number.                                    \n\r"
"                                                                       \n\r"
"Example: The following command is used to demonstrate on how to remove \n\r"
"         loop by modifying the spanning tree state of a port.          \n\r"
"         example_stp 5 6                                               \n\r"
"                                                                       \n\r"
"Usage Guidelines: This program takes two ports numbers as input and    \n\r"
"       place them in VLAN 100 and by default put them in forwarding    \n\r"
"       state. This results in a loop if both the ports are connected   \n\r"
"       to a partner switch. Here the program provides the menu with    \n\r"
"       the following options.                                          \n\r"
"                                                                       \n\r"
"       1) Configure the STP state of a port.                           \n\r"
"       2) Display the STP state of ports.                              \n\r"
"       3) Quit the application.                                        \n\r"
"                                                                       \n\r";


#define DEFAULT_UNIT         0
#define VLANID               100
#define MAX_DIGITS_IN_CHOICE 5

typedef struct {
  int vlan_1;
  int port_1;
  int port_2;
  int stp_state_1;
  int stp_state_2;
  opennsl_stg_t stg;
} stg_info_s;

char *stp_state_str[] =
{
  "Disable", /* OPENNSL_STG_STP_DISABLE */
  "Block",   /* OPENNSL_STG_STP_BLOCK   */
  "Listen",  /* OPENNSL_STG_STP_LISTEN  */
  "Learn",   /* OPENNSL_STG_STP_LEARN   */
  "Forward"  /* OPENNSL_STG_STP_FORWARD */
};

/* debug prints */
int verbose = 3;

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
int example_stg_init(int unit, stg_info_s *info, int port1, int port2);
int example_stg_create(int unit, stg_info_s *info);

/**********************************************************************//**
 * \brief Main function for Spanning Tree Protocol (STP) sample application
 *
 * \param argc, argv         commands line arguments
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 *****************************************************i********************/
int main(int argc, char *argv[])
{
  int rv = OPENNSL_E_NONE;
  int unit = DEFAULT_UNIT;
  int port1;
  int port2;
  int port;
  int stp_mode;
  int stp_state;
  int choice;
  stg_info_s info;


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

  /* Extract inputs parameters */
  port1 = atoi(argv[1]);
  port2 = atoi(argv[2]);

  /* Call the STP action routines */
  CALL_IF_ERROR_RETURN(example_stg_init(unit, &info, port1, port2));
  CALL_IF_ERROR_RETURN(example_stg_create(unit, &info));

  /* Display the interactive user menu */
  while(1)
  {
    printf("Interactive User Menu:\n");
    printf("1. Configure STP state of a port\n");
    printf("2. Display the STP state of ports\n");
#ifndef CDP_EXCLUDE
    printf("9. Launch diagnostic shell\n");
#endif
    printf("0. Quit the application\n");

   if(example_read_user_choice(&choice) != OPENNSL_E_NONE)
   {
       printf("Invalid option entered. Please re-enter.\n");
       continue;
    }

    switch(choice)
    {
      case 1:
      {
        printf("1. Enter port number\n");
        if(example_read_user_choice(&port) != OPENNSL_E_NONE)
        {
            printf("Invalid option entered. Please re-enter.\n");
            continue;
        }
        printf("1. Enter STP state of the port\n");
        printf("   STP state: 1 - Forward, 2 - Block\n");
        if(example_read_user_choice(&stp_mode) != OPENNSL_E_NONE)
        {
            printf("Invalid option %d entered. Please re-enter.\n", stp_mode);
            continue;
        }

        if(stp_mode == 1) {
          stp_state = OPENNSL_STG_STP_FORWARD;
        } else if(stp_mode == 2) {
          stp_state = OPENNSL_STG_STP_BLOCK;
        }
        else {
          printf("Invalid option is entered. Please re-enter.\n");
          continue;
        }

        rv = opennsl_stg_stp_set(unit, info.stg, port, stp_state);
        if (rv != OPENNSL_E_NONE) {
          printf("Failed to set STP state of port %d to "
              "\"%s\" in STG %d, \n",
              port, stp_state_str[stp_state], info.stg);
          return rv;
        }
        if(verbose >= 2) {
          printf("STP state of port %d is set to \"%s\".\n",
              port, stp_state_str[stp_state]);
        }
        break;
      }
      case 2:
      {
        rv = opennsl_stg_stp_get(unit, info.stg, info.port_1, &stp_state);
        if (rv != OPENNSL_E_NONE) {
          printf("Failed to get STP state of port %d in STG %d, \n",
              port, info.stg);
          return rv;
        }
        printf("STP state of port %d is \"%s\" in STG %d.\n",
            info.port_1, stp_state_str[stp_state], info.stg);

        rv = opennsl_stg_stp_get(unit, info.stg, info.port_2, &stp_state);
        if (rv != OPENNSL_E_NONE) {
          printf("Failed to get STP state of port %d in STG %d, \n",
              info.port_2, info.stg);
          return rv;
        }
        printf("STP state of port %d is \"%s\" in STG %d.\n",
            info.port_2, stp_state_str[stp_state], info.stg);
        break;
      }

#ifndef CDP_EXCLUDE
      case 9:
      {
        opennsl_driver_shell();
        break;
      }
#endif

      case 0:
      {
        printf("User has requested to quit the application.\n");
        return rv;
        break;
      }
      default:
        printf("Invalid option is entered. Please re-enter.\n");

    } /* End of switch */

  } /* End of while */


  return rv;
}

/**************************************************************************//**
 * \brief Initialization routine to create spanning tree instance and initialize
 *        the structures.
 *
 * \param    unit      [IN] Unit number.
 * \param    *info     [IN] Pointer to a location where STG information
 *                          is stored
 * \param    port1     [IN] First port number.
 * \param    port2     [IN] Second port number.
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/

int example_stg_init(int unit, stg_info_s *info, int port1, int port2) {
  int rv;

  info->vlan_1 = VLANID;
  info->port_1 = port1;
  info->port_2 = port2;
  info->stp_state_1 = OPENNSL_STG_STP_FORWARD;
  info->stp_state_2 = OPENNSL_STG_STP_FORWARD;
  rv = opennsl_stg_create(unit,&(info->stg));
  return rv;
}

/**************************************************************************//**
 * \brief To add a given set of ports and VLAN to spanning tree instance.
 *
 * \param    unit      [IN] Unit number.
 * \param    *info     [IN] Pointer to a location where STG information
 *                          is stored
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
int example_stg_create(int unit, stg_info_s *info) {
  int rv;
  opennsl_pbmp_t pbmp;

  /* create VLAN */
  rv = opennsl_vlan_create(DEFAULT_UNIT, info->vlan_1);
  if (rv != OPENNSL_E_NONE) {
    printf("Error, in opennsl_vlan_create, vid=%d, \n", info->vlan_1);
    return rv;
  }

  if(verbose >= 2) {
    printf("VLAN %d is created.\n", info->vlan_1);
  }

  OPENNSL_PBMP_CLEAR(pbmp);
  OPENNSL_PBMP_PORT_ADD(pbmp, info->port_1);
  OPENNSL_PBMP_PORT_ADD(pbmp, info->port_2);

  rv = opennsl_vlan_port_add(unit, info->vlan_1, pbmp, pbmp);
  if (rv != OPENNSL_E_NONE) {
    printf("OPENNSL FAIL %d: %s\n", rv, opennsl_errmsg(rv));
    return rv;
  }

  if(verbose >= 2) {
    printf("Added ports %d, %d to VLAN %d.\n",
           info->port_1, info->port_2, info->vlan_1);
  }

  /* add the vlans to the stg */
  rv = opennsl_stg_vlan_add(unit, info->stg, info->vlan_1);
  if (rv != OPENNSL_E_NONE) {
    printf("Error, in opennsl_stg_vlan_add, vid=%d, \n", info->vlan_1);
    return rv;
  }

  if(verbose >= 2) {
    printf("Attached VLAN %d to Spanning Tree Group %d.\n",
           info->vlan_1, info->stg);
  }

  /* add two ports to the stg and attach stp state for each of them */
  rv = opennsl_stg_stp_set(unit, info->stg, info->port_1, info->stp_state_1);
  if (rv != OPENNSL_E_NONE) {
    printf("Error, in opennsl_stg_stp_set, stg=%d, \n", info->stg);
    return rv;
  }

  if(verbose >= 2) {
    printf("STP state of port %d is set to \"%s\".\n", 
           info->port_1, stp_state_str[info->stp_state_1]);
  }

  rv = opennsl_stg_stp_set(unit, info->stg, info->port_2, info->stp_state_2);
  if (rv != OPENNSL_E_NONE) {
    printf("Error, in opennsl_stg_stp_set, stg=%d, \n", info->stg);
    return rv;
  }
  if(verbose >= 2) {
    printf("STP state of port %d is set to \"%s\".\n",
           info->port_2, stp_state_str[info->stp_state_2]);
  }

  return OPENNSL_E_NONE;
}

/**************************************************************************//**
 * \brief To destroy the spanning tree instance and VLAN's associate with it.
 *
 * \param    unit      [IN] Unit number.
 * \param    *info     [IN] Pointer to a location where STG information
 *                          is stored
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
int revert_stg(int unit, stg_info_s *info) {
  int rv = OPENNSL_E_NONE;

  rv = opennsl_stg_destroy(unit,info->stg);
  if (rv != OPENNSL_E_NONE) {
    printf("Error, in opennsl_stg_destroy\n");
    return rv;
  }

  rv = opennsl_vlan_destroy(unit,info->vlan_1);
  if (rv != OPENNSL_E_NONE) {
    printf("Error, in opennsl_vlan_destroy, vid=%d, \n", info->vlan_1);
    return rv;
  }

  return rv;
}
