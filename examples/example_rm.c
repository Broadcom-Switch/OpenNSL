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
 * \file     example_rm.c
 *
 * \brief    Example code for Resource Manager functionality
 *
 * \details  This example demonstrates the Resource Manager functionality
 *           in OpenNSL.
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <opennsl/types.h>
#include <opennsl/error.h>
#include <opennsl/l2.h>
#include <examples/util.h>
#include <opennsl/rmapi.h>

#define EXAMPLE_RM_PORT_PBMP_FORMAT "%08X %08X %08X %08X %08X %08X %08X %08X"
#define EXAMPLE_RM_PORT_PBMP_SHOW(pbmp) \
                             _SHR_PBMP_WORD_GET(pbmp,7), \
                             _SHR_PBMP_WORD_GET(pbmp,6), \
                             _SHR_PBMP_WORD_GET(pbmp,5), \
                             _SHR_PBMP_WORD_GET(pbmp,4), \
                             _SHR_PBMP_WORD_GET(pbmp,3), \
                             _SHR_PBMP_WORD_GET(pbmp,2), \
                             _SHR_PBMP_WORD_GET(pbmp,1), \
                             _SHR_PBMP_WORD_GET(pbmp,0)

#define DEFAULT_UNIT        0
#define DEFAULT_RM_CLIENTID 0

char example_usage[] =
"Syntax: example_rm                                                    \n\r"
"                                                                      \n\r"
"Paramaters: None.                                                     \n\r"
"                                                                      \n\r"
"Example: The following command is used to start the                   \n\r"
"resource manager test application.                                    \n\r"
"         example_rm                                                   \n\r"
"                                                                      \n\r"
"Usage Guidelines: None.                                               \n\r";

/*****************************************************************//**
* \brief Callback function to show L2 table information
*
* \param unit       [IN]     unit number
* \param info       [IN]     L2 address structure
* \param *user_data [IN]     User specified cookie
*
* \return OPENNSL_E_NONE
********************************************************************/
int _opennsl_l2_traverse_cb(
    int unit,
    opennsl_l2_addr_t *info,
    void *user_data)
{
  printf("MAC=%02x:%02x:%02x:%02x:%02x:%02x VLAN=%d PORT=%d\n",
      info->mac[0], info->mac[1], info->mac[2], info->mac[3],
      info->mac[4], info->mac[5], info->vid, info->port);
  return OPENNSL_E_NONE;
}

/*****************************************************************//**
* \brief Utility function to take L2 parameters from the user
*
* \param unit       [IN]     unit number
* \param vlan       [IN]     VLAN identifier
* \param port       [IN]     port number
* \param mac        [IN]     MAC address
*
* \return OPENNSL_E_NONE
  ********************************************************************/
int example_l2_params_get(uint16 *vlan, int *port, opennsl_mac_t mac)
{
  int val;
  char macstr[18];

  printf("Enter VLAN: \n");
  if(example_read_user_choice(&val) != OPENNSL_E_NONE)
  {
    printf("Invalid value entered. Please re-enter.\n");
    return OPENNSL_E_FAIL;
  }
  *vlan = (uint16) val;

  printf("Enter Port Number: \n");
  if(example_read_user_choice(&val) != OPENNSL_E_NONE)
  {
    printf("Invalid value entered. Please re-enter.\n");
    return OPENNSL_E_FAIL;
  }
  *port = val;

  printf("Enter MAC address in xx:xx:xx:xx:xx:xx format: \n");
  if(example_read_user_string(macstr, sizeof(macstr)) == NULL)
  {
    printf("\n\rInvalid MAC address entered.\n\r");
    return OPENNSL_E_FAIL;
  }

  if(opennsl_mac_parse(macstr, mac) != OPENNSL_E_NONE)
  {
    printf("\n\rFailed to parse input MAC address.\n\r");
    return OPENNSL_E_FAIL;
  }
  return OPENNSL_E_NONE;
}

/*****************************************************************//**
 * \brief Display the RM profile parameters of a registered client
 *
 * \param profile     [IN]     RM profile structure pointer
 *
 * \return None
 ********************************************************************/
void example_rm_show_profile(opennsl_rm_profile_t *profile)
{
  int jj;

  for(jj=0; jj < RM_MAX_UNITS;jj++)
  {
    printf("Unit:%d Ports = ",jj);
    printf(EXAMPLE_RM_PORT_PBMP_FORMAT,
	   EXAMPLE_RM_PORT_PBMP_SHOW(profile->port_bitmap[jj]));
    printf("\n");
  }

  printf("\nVLANs : ");
  for(jj = (_SHR_BITDCLSIZE(OPENNSL_VLAN_COUNT) - 1);jj >= 0;jj--)
  {
    printf("%08X ",profile->vlan_bitmap[jj]);
  }
  printf("\n");

  return;
}

/*****************************************************************//**
 * \brief Main function for RM functionality testing application
 *
 * \param argc, argv         commands line arguments
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int main(int argc, char *argv[])
{
  int choice;
  int rval;
  opennsl_error_t   rv;
  opennsl_vlan_t vlan = 1;
  opennsl_port_t port;
  opennsl_mac_t mac;
  opennsl_l2_addr_t addr;
  int mod_id = 0;
  int unit = DEFAULT_UNIT;
  void *user_data = NULL;
  int index = 0;
  opennsl_pbmp_t port_bitmap;
  opennsl_vlan_vector_t vlan_bitmap;
  opennsl_rm_profile_t profile;

  if(strcmp(argv[0], "gdb") == 0)
  {
    index = 1;
  }

  if((argc != (index + 1)) || ((argc > (index + 1))
        && (strcmp(argv[index + 1], "--help") == 0))) {
    printf("%s\n\r", example_usage);
    return OPENNSL_E_PARAM;
  }

  /* OpenNSL initialization is needed for RM initialization to succeed. */
  printf("Initializing the system.This will also initialize RM\r\n");
  rv = opennsl_driver_init((opennsl_init_t *) NULL);
  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to initialize the system. Error %s\r\n",
        opennsl_errmsg(rv));
    return rv;
  }

  while (1) {
    printf("\r\nUser menu: Select one of the following options\r\n");
    printf(" 1. Show the NOS Profile values\n");
    printf(" 2. Add L2 entry\n");
    printf(" 3. Remove L2 entry\n");
    printf(" 4. Show L2 table\n");
    printf(" 5. Update the Ports of the default client\n");
    printf(" 6. Update the VLANs of the default client\n");
    printf(" 9. Launch diagnostic shell\n");
    printf(" 0. Quit the application\n");

    if(example_read_user_choice(&choice) != OPENNSL_E_NONE)
    {
        printf("Invalid option entered. Please re-enter.\n");
        continue;
    }

    switch(choice){
      case 1:
      {
        memset(&profile,0,sizeof(opennsl_rm_profile_t));
        rval = opennsl_rm_profile_get(DEFAULT_RM_CLIENTID,&profile);
        if (rval == OPENNSL_RM_E_NONE)
        {
          printf("RM profile get is successful\n");
          example_rm_show_profile(&profile);
        }
        else
        {
          printf("RM profile get failed:%d\n",rval);
        }

        break;
      } /* End of case 1 */

      case 2:
      {
        if(example_l2_params_get(&vlan, &port, mac) != OPENNSL_E_NONE)
        {
          continue;
        }

        opennsl_l2_addr_t_init(&addr, mac, vlan);

        OPENNSL_GPORT_MODPORT_SET(addr.port, mod_id, port);
        addr.flags = OPENNSL_L2_STATIC;

        rv = opennsl_l2_addr_add(unit, &addr);
        if (rv == OPENNSL_E_NONE) 
        {
          printf("L2 static entry added successfully\n");
          printf("  VLAN  : %d\n", addr.vid);
          printf("  Gport : 0x%0x\n", addr.port);
          printf("  MAC   : %02x:%02x:%02x:%02x:%02x:%02x\n",
              mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        } 
        else 
        {
          printf("Failed to add L2 static entry. Error %s\n",
              opennsl_errmsg(rv));
        }
        break;
      } /* End of case 2 */

      case 3:
      {
        if(example_l2_params_get(&vlan, &port, mac) != OPENNSL_E_NONE)
        {
          continue;
        }

        /* Check whether the station exists in the firewall rules */
        rv = opennsl_l2_addr_get(unit, mac, vlan, &addr);

        if (rv != OPENNSL_E_NONE) 
        {
          printf("\n\rFailed to get L2 entry with the input parameters. "
              "Error %s\n\r", opennsl_errmsg(rv));
          continue;
        }

        OPENNSL_GPORT_MODPORT_SET(addr.port, mod_id, port);
        addr.flags = OPENNSL_L2_STATIC;

        rv = opennsl_l2_addr_delete(unit, mac, vlan);
        if (rv == OPENNSL_E_NONE) 
        {
          printf("L2 static entry deleted successfully\n");
          printf("  VLAN  : %d\n", addr.vid);
          printf("  Gport : 0x%0x\n", addr.port);
          printf("  MAC   : %02x:%02x:%02x:%02x:%02x:%02x\n",
                  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        } 
        else 
        {
          printf("Failed to delete L2 static entry. Error %s\n",
              opennsl_errmsg(rv));
	}
        break;
      } /* End of case 3 */

      case 4:
      {
        /* Iterate over all valid entries in the L2 table */
        rv = opennsl_l2_traverse(unit, &_opennsl_l2_traverse_cb, user_data);
        if(rv != OPENNSL_E_NONE) 
        {
          printf("\r\nFailed to iterate over L2 table. rv: %s\r\n",
                  opennsl_errmsg(rv));
        }
        break;
      } /* End of case 4 */

      case 5:
      {
        /* Update the default profile with ports - 21-40 */
        OPENNSL_PBMP_CLEAR(port_bitmap);
        for(index = 21; index <= 40; index++)
        {
          OPENNSL_PBMP_PORT_ADD(port_bitmap, index);
        }

        if(OPENNSL_RM_E_NONE != 
           opennsl_rm_profile_ports_update(DEFAULT_RM_CLIENTID, unit, port_bitmap))
        {
          printf("RM profile update failed.\n");
        }
        else
        {
          printf("RM profile successfully updated.\n");
        }
        break;
      } /* End of case 5 */

      case 6:
      {
        /* Update the default profile with VLANS - 101-200 */
        OPENNSL_VLAN_VEC_ZERO(vlan_bitmap);
        for(index = 101; index <= 200; index++)
        {
          OPENNSL_VLAN_VEC_SET(vlan_bitmap, index);
        }

        if(OPENNSL_RM_E_NONE != 
           opennsl_rm_profile_vlans_update(DEFAULT_RM_CLIENTID, vlan_bitmap))
        {
          printf("RM profile update failed.\n");
        }
        else
        {
          printf("RM profile successfully updated.\n");
        }

        break;
      } /* End of case 6 */

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

  return OPENNSL_E_NONE;
}

