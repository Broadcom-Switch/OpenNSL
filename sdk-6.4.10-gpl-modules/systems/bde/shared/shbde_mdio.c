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

#include <shbde_mdio.h>

/* iProc MDIO register offset */
#define MII_MGMT_CTRL                       0x0
#define MII_MGMT_CMD_DATA                   0x4

/* iProc MII register with fields definition */
#define MII_MGMT_CTRLr_MDCDIVf_SHFT         0
#define MII_MGMT_CTRLr_MDCDIVf_MASK         0x7f
#define MII_MGMT_CTRLr_BSYf_SHFT            8
#define MII_MGMT_CTRLr_BSYf_MASK            0x1

#define MII_MGMT_CMD_DATAr_DATAf_SHFT       0
#define MII_MGMT_CMD_DATAr_DATAf_MASK       0xffff
#define MII_MGMT_CMD_DATAr_TAf_SHFT         16
#define MII_MGMT_CMD_DATAr_TAf_MASK         0x3
#define MII_MGMT_CMD_DATAr_RAf_SHFT         18
#define MII_MGMT_CMD_DATAr_RAf_MASK         0x1f
#define MII_MGMT_CMD_DATAr_PAf_SHFT         23
#define MII_MGMT_CMD_DATAr_PAf_MASK         0x1f
#define MII_MGMT_CMD_DATAr_OPf_SHFT         28
#define MII_MGMT_CMD_DATAr_OPf_MASK         0x3
#define MII_MGMT_CMD_DATAr_SBf_SHFT         30
#define MII_MGMT_CMD_DATAr_SBf_MASK         0x3

/* Register field value set/get */
#define REG_FIELD_SET(_r, _f, _r_val, _f_val) \
        _r_val = ((_r_val) & ~(_r##_##_f##_MASK << _r##_##_f##_SHFT)) | \
                 (((_f_val) & _r##_##_f##_MASK) << _r##_##_f##_SHFT)
#define REG_FIELD_GET(_r, _f, _r_val) \
        (((_r_val) >> _r##_##_f##_SHFT) & _r##_##_f##_MASK)

#define LOG_OUT(_shbde, _lvl, _str, _prm)             \
    if ((_shbde)->log_func) {                         \
        (_shbde)->log_func(_lvl, _str, _prm);         \
    }
#define LOG_ERR(_shbde, _str, _prm)     LOG_OUT(_shbde, SHBDE_ERR, _str, _prm)
#define LOG_WARN(_shbde, _str, _prm)    LOG_OUT(_shbde, SHBDE_WARN, _str, _prm)
#define LOG_DBG(_shbde, _str, _prm)     LOG_OUT(_shbde, SHBDE_DBG, _str, _prm)

static unsigned int
mdio32_read(shbde_mdio_ctrl_t *smc, unsigned int offset)
{
    if (!smc || !smc->io32_read) {
        return 0;
    }
    return smc->io32_read(smc->shbde, smc->regs, smc->base_addr + offset);
}

static void
mdio32_write(shbde_mdio_ctrl_t *smc, unsigned int offset, unsigned int data)
{
    if (!smc || !smc->io32_read) {
        return;
    }
    smc->io32_write(smc->shbde, smc->regs, smc->base_addr + offset, data);
}

static void
wait_usec(shbde_mdio_ctrl_t *smc, int usec)
{
    shbde_hal_t *shbde = smc->shbde;

    if (shbde && shbde->usleep) {
        shbde->usleep(usec);
    } else {
        int idx;
        volatile int count;
        for (idx = 0; idx < usec; idx++) {
            for (count = 0; count < 100; count++);
        }
    }
}

static int
iproc_mdio_wait_for_busy(shbde_mdio_ctrl_t *smc)
{
    int mii_busy;
    unsigned int reg_val;
    int count = 1000;

    /* Wait until MII is not busy */
    do {
        reg_val = mdio32_read(smc, MII_MGMT_CTRL);
        mii_busy = REG_FIELD_GET(MII_MGMT_CTRLr, BSYf, reg_val);
        if (!mii_busy) {
            break;
        }
        wait_usec(smc, 10);
        count --;
    } while (count > 0);

    return mii_busy;
}

int
shbde_iproc_mdio_init(shbde_mdio_ctrl_t *smc)
{
    shbde_hal_t *shbde = smc->shbde;
    unsigned int reg_val = 0;

    /* Enable the iProc internal MDIO interface */
    REG_FIELD_SET(MII_MGMT_CTRLr, MDCDIVf, reg_val, 0x7f);
    mdio32_write(smc, MII_MGMT_CTRL, reg_val);

    if (shbde && !shbde->usleep) {
        LOG_DBG(shbde, "shbde_mdio: no registration of usleep vector", 0);
    }

    wait_usec(smc, 100);

    return 0;
}

int
shbde_iproc_mdio_read(shbde_mdio_ctrl_t *smc, unsigned int phy_addr,
                      unsigned int reg, unsigned int *val)
{
    unsigned int reg_val = 0;

    REG_FIELD_SET(MII_MGMT_CMD_DATAr, SBf, reg_val, 0x1);
    REG_FIELD_SET(MII_MGMT_CMD_DATAr, TAf, reg_val, 0x2);
    REG_FIELD_SET(MII_MGMT_CMD_DATAr, OPf, reg_val, 0x2);
    REG_FIELD_SET(MII_MGMT_CMD_DATAr, PAf, reg_val, phy_addr);
    REG_FIELD_SET(MII_MGMT_CMD_DATAr, RAf, reg_val, reg);
    mdio32_write(smc, MII_MGMT_CMD_DATA, reg_val);

    if (iproc_mdio_wait_for_busy(smc)) {
        *val = 0;
        LOG_DBG(smc->shbde, "shbde_iproc_mdio_read busy", reg);
        return -1;
    }

    reg_val = mdio32_read(smc, MII_MGMT_CMD_DATA);
    *val = REG_FIELD_GET(MII_MGMT_CMD_DATAr, DATAf, reg_val);

    return 0;
}

int
shbde_iproc_mdio_write(shbde_mdio_ctrl_t *smc, unsigned int phy_addr,
                       unsigned int reg, unsigned int val)
{
    unsigned int reg_val = 0;

    REG_FIELD_SET(MII_MGMT_CMD_DATAr, SBf, reg_val, 0x1);
    REG_FIELD_SET(MII_MGMT_CMD_DATAr, TAf, reg_val, 0x2);
    REG_FIELD_SET(MII_MGMT_CMD_DATAr, OPf, reg_val, 0x1);
    REG_FIELD_SET(MII_MGMT_CMD_DATAr, PAf, reg_val, phy_addr);
    REG_FIELD_SET(MII_MGMT_CMD_DATAr, RAf, reg_val, reg);
    REG_FIELD_SET(MII_MGMT_CMD_DATAr, DATAf, reg_val, val);
    mdio32_write(smc, MII_MGMT_CMD_DATA, reg_val);

    if (iproc_mdio_wait_for_busy(smc)) {
        LOG_DBG(smc->shbde, "shbde_iproc_mdio_write busy", reg);
        return -1;
    }

    /* Wait for some time for the write to take effect */
    wait_usec(smc, 100);

    return 0;
}

