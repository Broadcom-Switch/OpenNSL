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
 * \file     example_rpc_app.c
 *
 * \brief    Example code for testing OpenNSL client library
 *
 * \details  This example demonstrates the OpenNSL client library usage
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <opennsl/types.h>
#include <opennsl/error.h>
#include <opennsl/init.h>
#include <opennsl/port.h>
#include <sal/driver.h>

char example_usage[] =
"Syntax: example_rpc_app                                               \n\r"
"                                                                      \n\r"
"Paramaters: None.                                                     \n\r"
"                                                                      \n\r"
"Example: The following command is used to start the                   \n\r"
"opennsl RPC application.                                              \n\r"
"         example_rpc_app                                              \n\r"
"                                                                      \n\r"
"Usage Guidelines: None.                                               \n\r";


/*****************************************************************//**
 * \brief Main function for OpenNSL RPC client functionality testing 
 *  application
 *
 * \param argc, argv         commands line arguments
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int main(int argc, char *argv[])
{
  int unit = 0, index = 0;
  opennsl_error_t   rval;
  opennsl_info_t info;
  opennsl_gport_t gport;
  int max_units;
  opennsl_port_config_t port_config;

  if(strcmp(argv[0], "gdb") == 0)
  {
    index = 1;
  }

  if((argc != (index + 1)) || ((argc > (index + 1))
        && (strcmp(argv[index + 1], "--help") == 0))) {
    printf("%s\n\r", example_usage);
    return OPENNSL_E_PARAM;
  }

  /* Initialize the client library */
  opennsl_driver_init(NULL);

  printf("Invoking opennsl_info_get()\n");
  rval = opennsl_info_get(unit, &info);
  if (rval != OPENNSL_E_NONE)
  {
    printf("Failed to get the unit info:%d\n",rval);
  }
  else
  {
    printf("Device Info:%d %d\n",info.device,info.revision);
  }

  printf("Invoking opennsl_port_gport_get()\n");
  rval = opennsl_port_gport_get(unit, 2, &gport);
  if (rval != OPENNSL_E_NONE)
  {
    printf("Failed to get the gport:%d\n",rval);
  }
  else
  {
    printf("local port:2 gport:%d\n", gport);
  }

  printf("Invoking opennsl_attach_max()\n");
  rval = opennsl_attach_max(&max_units);
  if (rval != OPENNSL_E_NONE)
  {
    printf("Failed to get the max-units:%d\n",rval);
  }
  else
  {
    printf("max-units:%d\n", max_units);
  }

  printf("Invoking opennsl_port_config_get()\n");
  rval = opennsl_port_config_get(unit, &port_config);
  if (rval != OPENNSL_E_NONE)
  {
    printf("Failed to get the port-config:%d\n",rval);
  }
  else
  {
    printf("%s:%d:\n \
                  ge-bmp: [%u, %u, %u, %u, %u, %u, %u, %u]\n \
                  xe-bmp: [%u, %u, %u, %u, %u, %u, %u, %u]\n \
                  ce-bmp: [%u, %u, %u, %u, %u, %u, %u, %u]\n \
                  port-bmp: [%u, %u, %u, %u, %u, %u, %u, %u]\n \
                  cpu-bmp: [%u, %u, %u, %u, %u, %u, %u, %u]\n \
                  all-bmp: [%u, %u, %u, %u, %u, %u, %u, %u]\n \
                  \n",__FUNCTION__,__LINE__,
		  port_config.ge.pbits[0],port_config.ge.pbits[1],port_config.ge.pbits[2],port_config.ge.pbits[3],
		  port_config.ge.pbits[4],port_config.ge.pbits[5],port_config.ge.pbits[6],port_config.ge.pbits[7],
		  port_config.xe.pbits[0],port_config.xe.pbits[1],port_config.xe.pbits[2],port_config.xe.pbits[3],
		  port_config.xe.pbits[4],port_config.xe.pbits[5],port_config.xe.pbits[6],port_config.xe.pbits[7],
		  port_config.ce.pbits[0],port_config.ce.pbits[1],port_config.ce.pbits[2],port_config.ce.pbits[3],
		  port_config.ce.pbits[4],port_config.ce.pbits[5],port_config.ce.pbits[6],port_config.ce.pbits[7],
		  port_config.port.pbits[0],port_config.port.pbits[1],port_config.port.pbits[2],port_config.port.pbits[3],
		  port_config.port.pbits[4],port_config.port.pbits[5],port_config.port.pbits[6],port_config.port.pbits[7],
		  port_config.cpu.pbits[0],port_config.cpu.pbits[1],port_config.cpu.pbits[2],port_config.cpu.pbits[3],
		  port_config.cpu.pbits[4],port_config.cpu.pbits[5],port_config.cpu.pbits[6],port_config.cpu.pbits[7],
		  port_config.all.pbits[0],port_config.all.pbits[1],port_config.all.pbits[2],port_config.all.pbits[3],
		  port_config.all.pbits[4],port_config.all.pbits[5],port_config.all.pbits[6],port_config.all.pbits[7]
                  );
  }
  return OPENNSL_E_NONE;
}

