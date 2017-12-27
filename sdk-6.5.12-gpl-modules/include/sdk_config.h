/*
 * Copyright 2017 Broadcom
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as
 * published by the Free Software Foundation (the "GPL").
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License version 2 (GPLv2) for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * version 2 (GPLv2) along with this source code.
 */
/*
 * $Id: sdk_config.h,v 1.5 Broadcom SDK $
 * $Copyright: (c) 2006 Broadcom Corp.
 * All Rights Reserved.$
 *
 *
 */

#ifndef __SDK_CONFIG_H__
#define __SDK_CONFIG_H__

/*
 * Include custom overrides
 */
#ifdef SDK_INCLUDE_CUSTOM_CONFIG
#include <sdk_custom_config.h>
#endif


/*
 * Memory Barrier operation if required. 
 * Defaults to nothing. 
 */
#ifndef SDK_CONFIG_MEMORY_BARRIER
#define SDK_CONFIG_MEMORY_BARRIER
#endif



#endif /* __SDK_CONFIG_H__ */
