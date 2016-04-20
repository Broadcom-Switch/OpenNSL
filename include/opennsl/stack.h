/** \addtogroup stack Stack control
 *  @{
 */
/*****************************************************************************
 * 
 * (C) Copyright Broadcom Corporation 2013-2015
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * 
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 ***************************************************************************//**
 * \file			stack.h
 ******************************************************************************/

#ifndef __OPENNSL_STACK_H__
#define __OPENNSL_STACK_H__

#include <opennsl/types.h>

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Get or set the module ID of the local device.
 *
 *\description    Set or get the device's module identifier.  Each device in a   
 *             system must have a unique module number.  Some devices, such   
 *             as switch family fabric switches, do not have a module
 *          identifier, and will return OPENNSL_E_UNAVAIL.
 *          opennsl_stk_modid_set and opennsl_stk_modid_get will do module
 *          mapping by calling =opennsl_stk_modmap_map .
 *          opennsl_stk_my_modid_set and opennsl_stk_my_modid_get control the
 *          non mapped module identifier for the device.
 *
 *\param    unit [IN]   Unit number.
 *\param    my_modid [OUT]
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_stk_my_modid_get(
    int unit, 
    int *my_modid) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#include <opennsl/stackX.h>
#endif /* __OPENNSL_STACK_H__ */
/*@}*/
