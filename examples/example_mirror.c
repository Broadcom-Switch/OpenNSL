/*********************************************************************
 *
 * (C) Copyright Broadcom Corporation 2013-2015
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
 * \file         example_mirror.c
 *
 * \brief        OpenNSL example application for port mirroring
 *
 * \details      Port mirroring application can be used to monitor packets
 *               received/transmitted by a given port.
 *
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sal/driver.h>
#include <opennsl/error.h>
#include <opennsl/stack.h>
#include <opennsl/vlan.h>
#include <opennsl/mirror.h>
#include <examples/util.h>

#define DEFAULT_UNIT 0
#define DEFAULT_VLAN 1

char example_usage[] =
"Syntax: example_mirror mode sport dport                               \n\r"
"                                                                      \n\r"
"Paramaters:                                                           \n\r"
"            mode    - 1, to turn on ingress mirroring.                \n\r"
"                      2, to turn on egress mirroring.                 \n\r"
"                      3, to turn on ingress and egress mirroring.     \n\r"
"            sport   - Port on which mirroring needs to be enabled.    \n\r"
"            dport   - Port on which traffic needs to be probed.       \n\r"
"                                                                      \n\r"
"Example: The following command is used to monitor ingress and egress  \n\r"
"         traffic from port 5 on port 10.                              \n\r"
"         example_mirror 3 5 10                                        \n\r"
"                                                                      \n\r"
"Usage Guidelines: None.                                               \n\r";

static int example_mirror_setup(int unit, int mode, int srcPort, int probePort);

/*****************************************************************//**
 * \brief Main function for mirroring application
 *
 * \param argc, argv         commands line arguments
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int main(int argc, char *argv[])
{
  int rv = 0;
  int choice;
  int mode;
  int srcPort;
  int probePort;
  int unit = DEFAULT_UNIT;

  if((argc != 4) || ((argc > 1) && (strcmp(argv[1], "--help") == 0))) {
    printf("%s\n\r", example_usage);
    return OPENNSL_E_PARAM;
  }

  /* Initialize the system. */
  rv = opennsl_driver_init((opennsl_init_t *) NULL);

  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to initialize the system. Error: %s\r\n",
           opennsl_errmsg(rv));
    return rv;
  }

  /* Add ports to default vlan. */
  printf("Adding ports to default vlan.\r\n");
  rv = example_switch_default_vlan_config(unit);
  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to add default ports. Error: %s\r\n",
        opennsl_errmsg(rv));
  }

  /* Extract input parameters */
  mode      = atoi(argv[1]);
  srcPort   = atoi(argv[2]);
  probePort = atoi(argv[3]);

  if(mode < 1 || mode > 3) {
    printf("Invalid mode is entered.\r\n");
    return OPENNSL_E_PARAM;
  }
  printf("\r\nInput parameters: Mode %d, Source Port %d,"
         " Probe Port %d.\r\n", mode, srcPort, probePort);

  /* Setup port mirroring */
  rv = example_mirror_setup(unit, mode, srcPort, probePort);
  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to set port mirroring. Error: %s.\r\n",
           opennsl_errmsg(rv));
  }
  else {
    printf("\r\nPort %d is mirrored to port %d successfully.\r\n",
           srcPort, probePort);
  }

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
        return OPENNSL_E_NONE;
      }
      default:
      break;
    } /* End of switch */
  }

  return rv;
}

/**************************************************************************//**
 * \brief To setup a port mirroring session
 *
 * \param    unit      [IN] Unit number
 * \param    mode      [IN] Off/ingress/egress/all
 * \param    srcPort   [IN] Source Port
 * \param    probePort [IN] Destination/Probe Port
 *
 * \return      OPENNSL_E_xxx  OpenNSL API return code
 *****************************************************************************/
static int example_mirror_setup(int unit, int mode, int srcPort, int probePort)
{
  int rv;
  opennsl_gport_t gport;
  unsigned int flags = 0;
  opennsl_mirror_destination_t mirror_dest;
  
  rv = opennsl_mirror_init(unit);
  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to init mirror module. Error: %s\r\n",
        opennsl_errmsg(rv));
  }

  opennsl_mirror_destination_t_init(&mirror_dest);
  OPENNSL_GPORT_MODPORT_SET(gport, 0, probePort);
  mirror_dest.gport = gport;

  rv = opennsl_mirror_destination_create(unit, &mirror_dest);
  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to create mirror dest. Error: %s\r\n",
        opennsl_errmsg(rv));
  }

  /* Configure the source port and mirror to port along with mirror mode */
  switch (mode)
  {
    case 1:
      /* Ingress mirroring only */
      flags |= OPENNSL_MIRROR_PORT_INGRESS;
      break;

    case 2:
      /* Egress mirroring only */
      flags |= OPENNSL_MIRROR_PORT_EGRESS;
      break;

    case 3:
      /* Both Ingress and Egress mirroring */
      flags |= (OPENNSL_MIRROR_PORT_INGRESS | OPENNSL_MIRROR_PORT_EGRESS);
      break;

    default:
      break;
  }

  rv = opennsl_mirror_port_dest_add(unit, srcPort, flags, mirror_dest.mirror_dest_id);
  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to enable mirroring on the port. Error: %s\r\n",
        opennsl_errmsg(rv));
  }

  return rv;
}
