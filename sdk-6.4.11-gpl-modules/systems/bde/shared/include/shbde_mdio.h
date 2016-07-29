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
 * $Copyright: (c) 2015 Broadcom Corp.
 * All Rights Reserved.$
 *
 */

#ifndef __SHBDE_MDIO_H__
#define __SHBDE_MDIO_H__

#include <shbde.h>

typedef struct shbde_mdio_ctrl_s {

    /* Primary HAL*/
    shbde_hal_t *shbde;

    /* Context for iProc MDIO register access */
    void *regs;

    /* Base address for MDIO registers */
    unsigned int base_addr;

    /* iProc MDIO register access */
    unsigned int (*io32_read)(shbde_hal_t *shbde, void *iproc_regs, 
                              unsigned int addr);
    void (*io32_write)(shbde_hal_t *shbde, void *iproc_regs, 
                       unsigned int addr, unsigned int data);

} shbde_mdio_ctrl_t;


extern int
shbde_iproc_mdio_init(shbde_mdio_ctrl_t *smc);

extern int
shbde_iproc_mdio_read(shbde_mdio_ctrl_t *smc, unsigned int phy_addr,
                      unsigned int reg, unsigned int *val);

extern int
shbde_iproc_mdio_write(shbde_mdio_ctrl_t *smc, unsigned int phy_addr,
                       unsigned int reg, unsigned int val);

#endif /* __SHBDE_MDIO_H__ */
