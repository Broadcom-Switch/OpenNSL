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
 * \file         example_led.c
 *
 * \brief        OpenNSL example application for LED programming
 *
 * \details      Example program for demonstrating the programmability of
 *               LED processor using OpenNSL APIs
 *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sal/driver.h>
#include <sal/pci.h>
#include <opennsl/port.h>
#include <opennsl/error.h>
#include <examples/util.h>

#define DEFAULT_UNIT 0

char example_usage[] =
"Syntax: example_led                                                   \n\r"
"                                                                      \n\r"
"Paramaters: None                                                      \n\r"
"                                                                      \n\r"
"Example: The following command is used to run the led programming     \n\r"
" application.                                                         \n\r"
"         example_led                                                  \n\r"
"                                                                      \n\r";


#define EXAMPLE_LED0_PROGRAM_RAM_SIZE  112
#define EXAMPLE_LED1_PROGRAM_RAM_SIZE  176

typedef struct led_info_s {
    uint32 ctrl;
    uint32 status;
    uint32 pram_base;
    uint32 dram_base;
} led_info_t;

static led_info_t led_info_cmicm[] = {
  {OPENNSL_CMIC_LEDUP0_CTRL_OFFSET, OPENNSL_CMIC_LEDUP0_STATUS_OFFSET, OPENNSL_CMIC_LEDUP0_PROGRAM_RAM_OFFSET,
   OPENNSL_CMIC_LEDUP0_DATA_RAM_OFFSET},
  {OPENNSL_CMIC_LEDUP1_CTRL_OFFSET,OPENNSL_CMIC_LEDUP1_STATUS_OFFSET,OPENNSL_CMIC_LEDUP1_PROGRAM_RAM_OFFSET,
   OPENNSL_CMIC_LEDUP1_DATA_RAM_OFFSET}
};

uint8 led0_program[EXAMPLE_LED0_PROGRAM_RAM_SIZE] = {\
      0x06,0xFE,0x80,0xD2,0x19,0x71,0x08,0xE0,0x60,0xFE,0xE9,0xD2,0x0F,0x75,0x10,0x81,\
      0x61,0xFD,0x02,0x3F,0x60,0xFF,0x28,0x32,0x0F,0x87,0x67,0x4A,0x96,0xFF,0x06,0xFF,\
      0xD2,0x2B,0x74,0x16,0x02,0x1F,0x60,0xFF,0x28,0x32,0x0F,0x87,0x67,0x4A,0x96,0xFF,\
      0x06,0xFF,0xD2,0x13,0x74,0x28,0x02,0x0F,0x60,0xFF,0x28,0x32,0x0F,0x87,0x67,0x4A,\
      0x96,0xFF,0x06,0xFF,0xD2,0x0B,0x74,0x3A,0x3A,0x48,0x32,0x07,0x32,0x08,0xC7,0x32,\
      0x04,0xC7,0x97,0x71,0x57,0x77,0x69,0x32,0x00,0x32,0x01,0xB7,0x97,0x71,0x63,0x32,\
      0x0E,0x77,0x6B,0x26,0xFD,0x97,0x27,0x77,0x6B,0x32,0x0F,0x87,0x57,0x00,0x00,0x00};

uint8 led1_program[EXAMPLE_LED1_PROGRAM_RAM_SIZE] = {\
     0x06,0xFE,0x80,0xD2,0x19,0x71,0x08,0xE0,0x60,0xFE,0xE9,0xD2,0x0F,0x75,0x10,0x81,\
     0x61,0xFD,0x02,0x20,0x67,0x89,0x02,0x24,0x67,0x89,0x02,0x10,0x67,0x89,0x02,0x28,\
     0x67,0x89,0x02,0x2C,0x67,0x89,0x02,0x0C,0x67,0x89,0x02,0x2C,0x67,0x79,0x02,0x28,\
     0x67,0x79,0x02,0x24,0x67,0x79,0x02,0x20,0x67,0x79,0x02,0x10,0x67,0x79,0x02,0x0C,\
     0x67,0x79,0x02,0x0B,0x60,0xFF,0x28,0x32,0x0F,0x87,0x67,0x56,0x96,0xFF,0x06,0xFF,\
     0xD2,0xFF,0x74,0x46,0x3A,0x36,0x32,0x07,0x32,0x08,0xC7,0x32,0x04,0xC7,0x97,0x71,\
     0x63,0x77,0x75,0x32,0x00,0x32,0x01,0xB7,0x97,0x71,0x6F,0x32,0x0E,0x77,0x77,0x26,\
     0xFD,0x97,0x27,0x77,0x77,0x32,0x0F,0x87,0x57,0x12,0xA0,0xF8,0x15,0x1A,0x01,0x75,\
     0x85,0x28,0x67,0x56,0x57,0x32,0x0F,0x87,0x57,0x12,0xA0,0xF8,0x15,0x1A,0x01,0x71,\
     0xA1,0x28,0x67,0x56,0x80,0x28,0x67,0x56,0x80,0x28,0x67,0x56,0x80,0x28,0x67,0x56,\
     0x57,0x32,0x0F,0x87,0x32,0x0F,0x87,0x32,0x0F,0x87,0x32,0x0F,0x87,0x57,0x00,0x00};

/*****************************************************************//**
 * \brief Main function for LED programming application
 *
 * \param argc, argv         commands line arguments
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int main(int argc, char *argv[])
{
  int rv = OPENNSL_E_NONE;
  int unit = DEFAULT_UNIT;
  int choice, led_max, ix;
  led_info_t *led_info_cur, *led_info;
  uint32 led_ctrl;
  int	offset;


  if((argc != 1) || ((argc > 1) && (strcmp(argv[1], "--help") == 0))) {
    printf("%s\n\r", example_usage);
    return OPENNSL_E_PARAM;
  }

  /* Initialize the system. */
  rv = opennsl_driver_init((opennsl_init_t *) NULL);
  if(rv != OPENNSL_E_NONE) 
  {
    printf("\r\nFailed to initialize the system. Error: %s\r\n",
           opennsl_errmsg(rv));
    return rv;
  }

  /* cold boot initialization commands */
  rv = example_port_default_config(unit);
  if (rv != OPENNSL_E_NONE) 
  {
    printf("\r\nFailed to apply default config on ports, rc = %d (%s).\r\n",
           rv, opennsl_errmsg(rv));
  }

  /* Add ports to default vlan. */
  printf("Adding ports to default vlan.\r\n");
  rv = example_switch_default_vlan_config(unit);
  if(rv != OPENNSL_E_NONE) 
  {
    printf("\r\nFailed to add default ports. Error: %s\r\n",
        opennsl_errmsg(rv));

    return rv;
  }

  while(1) {
    printf("\r\nUser menu: Select one of the following options\r\n");
    printf("1. Program the LED processor\r\n");
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
      case 1:
      {
        led_info = led_info_cmicm;
        led_max = 2;

        for(ix = 0; ix < led_max; ix++)
        {
          led_info_cur = led_info+ix;
          led_ctrl = opennsl_pci_read(unit, led_info_cur->ctrl);

          led_ctrl &= ~OPENNSL_LC_LED_ENABLE;
          if(OPENNSL_E_NONE != opennsl_pci_write(unit, led_info_cur->ctrl, led_ctrl))
          {
            printf("opennsl_pci_write returns failure:%d\n",rv);
          }

          for (offset = 0; offset < OPENNSL_CMIC_LED_PROGRAM_RAM_SIZE; offset++) 
          {
            if(ix == 0)
            {
              opennsl_pci_write(unit,
                            led_info_cur->pram_base + OPENNSL_CMIC_LED_REG_SIZE * offset,
                            (offset < EXAMPLE_LED0_PROGRAM_RAM_SIZE) ? (uint32) led0_program[offset] : 0);
            }
            else 
            {
              opennsl_pci_write(unit,
                            led_info_cur->pram_base + OPENNSL_CMIC_LED_REG_SIZE * offset,
                            (offset < EXAMPLE_LED1_PROGRAM_RAM_SIZE) ? (uint32) led1_program[offset] : 0);
            }
          }

          for (offset = 0x80; offset < OPENNSL_CMIC_LED_DATA_RAM_SIZE; offset++) 
          {
            opennsl_pci_write(unit,
                          led_info_cur->dram_base + OPENNSL_CMIC_LED_REG_SIZE * offset,
                          0);
          }

          /* The LED data area should be clear whenever program starts */
          led_ctrl = opennsl_pci_read(unit, led_info_cur->ctrl);
          opennsl_pci_write(unit, led_info_cur->ctrl, led_ctrl & ~OPENNSL_LC_LED_ENABLE);

          for (offset = 0x80; offset < OPENNSL_CMIC_LED_DATA_RAM_SIZE; offset++) {
               opennsl_pci_write(unit,
                          led_info_cur->dram_base + OPENNSL_CMIC_LED_REG_SIZE * offset,
                          0);
          }

          led_ctrl |= OPENNSL_LC_LED_ENABLE;
          opennsl_pci_write(unit, led_info_cur->ctrl, led_ctrl);
        }

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
        rv = opennsl_driver_exit();
        return rv;
      }
      default:
      break;
    } /* End of switch */
  } /* End of while */

  return rv;
}
