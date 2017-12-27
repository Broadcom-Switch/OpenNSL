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
 * $Id: $
 * $Copyright: (c) 2014 Broadcom Corp.
 * All Rights Reserved.$
 *
 */

#ifndef __LINUX_SHBDE_H__
#define __LINUX_SHBDE_H__

#include <shbde.h>
#include <shbde_pci.h>
#include <shbde_iproc.h>

extern int
linux_shbde_hal_init(shbde_hal_t *shbde, shbde_log_func_t log_func);

#endif /* __LINUX_SHBDE_H__ */
