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
* \file         driver.h
*
* \brief        This file contains utility functions called externally
*
**********************************************************************/
#ifndef DRIVER_H
#define DRIVER_H

#include <sal/commdefs.h>

extern int opennsl_driver_init(void) LIB_DLL_EXPORTED ;
#ifndef CDP_EXCLUDE
extern int opennsl_driver_shell() LIB_DLL_EXPORTED;
#endif
extern int opennsl_driver_process_command(char *commandBuf) LIB_DLL_EXPORTED;

#endif  /* DRIVER_H */
