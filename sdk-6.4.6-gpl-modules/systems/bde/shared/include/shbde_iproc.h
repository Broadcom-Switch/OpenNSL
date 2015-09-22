/*
 * Unless you and Broadcom execute a separate written software license
 * agreement governing use of this software, this software is licensed to
 * you under the terms of the GNU General Public License version 2 (the
 * "GPL"), available at http://www.broadcom.com/licenses/GPLv2.php,
 * with the following added to such license:
 * 
 * As a special exception, the copyright holders of this software give
 * you permission to link this software with independent modules, and to
 * copy and distribute the resulting executable under terms of your
 * choice, provided that you also meet, for each linked independent
 * module, the terms and conditions of the license of that module.  An
 * independent module is a module which is not derived from this
 * software.  The special exception does not apply to any modifications
 * of the software.
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
