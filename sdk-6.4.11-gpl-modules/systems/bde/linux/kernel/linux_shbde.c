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

#include <gmodule.h>
#include <shbde.h>
#include <shbde_iproc.h>
#include "linux_shbde.h"

/* Hardware abstractions for shared BDE functions */

static unsigned short
linux_pcic16_read(void *pci_dev, unsigned int addr)
{
    u16 data = 0;

    pci_read_config_word((struct pci_dev *)pci_dev, addr, &data);

    return data;
}

static void
linux_pcic16_write(void *pci_dev, unsigned int addr, unsigned short data)
{
    pci_write_config_word((struct pci_dev *)pci_dev, addr, (u16)data);
}

static unsigned int
linux_pcic32_read(void *pci_dev, unsigned int addr)
{
    u32 data = 0;

    pci_read_config_dword((struct pci_dev *)pci_dev, addr, &data);

    return data;
}

static void
linux_pcic32_write(void *pci_dev, unsigned int addr, unsigned int data)
{
    pci_write_config_dword((struct pci_dev *)pci_dev, addr, (u32)data);
}

static unsigned int
linux_io32_read(void *addr)
{
    return *((volatile u32 *)addr);
}

static void
linux_io32_write(void *addr, unsigned int data)
{
    *((volatile u32 *)addr) = data;
}

static void
linux_usleep(int usec)
{
    udelay(usec);
}


/* To get the PCI parent device under linux, from only the device pointer */
static void *
linux_pci_parent_device_get(void *pci_dev)
{
    return (void *)(((struct pci_dev *)pci_dev)->bus->self);
}


/*
 * Function:
 *      linux_shbde_hal_init
 * Purpose:
 *      Initialize hardware abstraction module for Linux kernel.
 * Parameters:
 *      shbde - pointer to uninitialized hardware abstraction module
 *      log_func - optional log output function
 * Returns:
 *      Always 0
 */
int
linux_shbde_hal_init(shbde_hal_t *shbde, shbde_log_func_t log_func)
{
    memset(shbde, 0, sizeof(*shbde));

    shbde->log_func = log_func;

    shbde->pcic16_read = linux_pcic16_read;
    shbde->pcic16_write = linux_pcic16_write;
    shbde->pcic32_read = linux_pcic32_read;
    shbde->pcic32_write = linux_pcic32_write;

    shbde->io32_read = linux_io32_read;
    shbde->io32_write = linux_io32_write;

    shbde->usleep = linux_usleep;

    shbde->pci_parent_device_get = linux_pci_parent_device_get;

    return 0;
}
