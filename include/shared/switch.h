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
 *********************************************************************
 * File:        switch.h
 ********************************************************************/


#ifndef _SHR_SWITCH_H
#define _SHR_SWITCH_H

#define _SHR_SWITCH_MAX_PIPES                 4  /* Max number of pipes (or slices) */

#define _SHR_SWITCH_STABLE_NONE               0  /* No storage */
#define _SHR_SWITCH_STABLE_DEVICE_NEXT_HOP    1  /* Use next hop table */
#define _SHR_SWITCH_STABLE_DEVICE_EXT_MEM     2  /* Use external TCAM/SRAM */
#define _SHR_SWITCH_STABLE_APPLICATION        3  /* Use application storage */
#define _SHR_SWITCH_STABLE_SHARED_MEM         4  /* Use Linux shmem for internal proccess NV storage */ 

/*
 * structure:
 *      _shr_temperature_monitor_t
 * Purpose:
 *      entry type for retrieving temperature monitor value
 *
 */
typedef struct _shr_switch_temperature_monitor_s {
    int curr;
    int peak;
} _shr_switch_temperature_monitor_t;

#endif  /* !_SHR_SWITCH_H */
