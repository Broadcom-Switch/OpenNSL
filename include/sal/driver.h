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
* \file         driver.h
*
* \brief        This file contains utility functions called externally
*
**********************************************************************/
#ifndef DRIVER_H
#define DRIVER_H

#define OPENNSL_F_FAST_BOOT   0x00000001  /* Fast boot mode */

typedef struct opennsl_config_s
{
  char         *cfg_fname;  /* Configuration file name along with the path */
  unsigned int flags;       /* OpenNSL boot up flags */
  char         *wb_fname;   /* File to store warmboot configuration *
                            * along with the path */
  char         *rmcfg_fname; /* RM config file name along with the path */
  char         *cfg_post_fname;  /* Post init configuration file name *
                                  * along with the path */
  unsigned int opennsl_flags;  /* OpenNSL flags */
} opennsl_init_t;

/*****************************************************************//**
* \brief Function to initialize the switch.
*
* \param init       [IN]   pointer to structure that contains path to
*                          platform customization config file, boot flags.
*
* \return OPENNSL_E_XXX     OpenNSL API return code
********************************************************************/
extern int opennsl_driver_init(opennsl_init_t *init);

/*****************************************************************//**
* \brief Function to free up the resources and exit the driver
*
* \return OPENNSL_E_XXX     OpenNSL API return code
********************************************************************/
extern int opennsl_driver_exit();

/**************************************************************************//**
 * \brief To get platform boot flags
 *
 * \return      unsigned int    Boot flags
 *****************************************************************************/
extern unsigned int opennsl_driver_boot_flags_get(void);

#ifdef INCLUDE_DIAG_SHELL
/*****************************************************************//**
* \brief Bringup diagnostic shell prompt and process the input commands.
*
* \return OPENNSL_E_XXX     OpenNSL API return code
********************************************************************/
extern int opennsl_driver_shell();

/*****************************************************************//**
* \brief Process diagnostic shell command.
*
* \param commandBuf    [IN]    pointer to hold the diagnostic shell command
*
* \return OPENNSL_E_XXX     OpenNSL API return code
********************************************************************/
extern int opennsl_driver_process_command(char *commandBuf);
#endif

/*****************************************************************//**
* \brief Get a line from a user with editing
*
* \param prompt    [IN]    prompt string
*
* \return char*     NULL, if the line is empty
*                   empty string, if the line is blank
*                   text of the line read, otherwise.
********************************************************************/
extern char *readline(const char *prompt);

extern void platform_phy_cleanup();

#endif  /* DRIVER_H */
