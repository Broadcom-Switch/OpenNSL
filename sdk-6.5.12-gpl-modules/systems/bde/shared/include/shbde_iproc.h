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

#ifndef __SHBDE_IPROC_H__
#define __SHBDE_IPROC_H__

#include <shbde.h>

extern int
shbde_iproc_config_init(shbde_iproc_config_t *icfg,
                        unsigned int dev_id, unsigned int dev_rev);

extern int
shbde_iproc_paxb_init(shbde_hal_t *shbde, void *iproc_regs,
                      shbde_iproc_config_t *icfg);

extern unsigned int
shbde_iproc_pci_read(shbde_hal_t *shbde, void *iproc_regs,
                     unsigned int addr);

extern void
shbde_iproc_pci_write(shbde_hal_t *shbde, void *iproc_regs,
                      unsigned int addr, unsigned int data);

extern int
shbde_iproc_pcie_preemphasis_set(shbde_hal_t *shbde, void *iproc_regs,
                                 shbde_iproc_config_t *icfg, void *pci_dev);

#endif /* __SHBDE_IPROC_H__ */
