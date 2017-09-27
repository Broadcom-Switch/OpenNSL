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
/***********************************************************************
 *
 * $Id: linux_dma.h,v 1.24 Broadcom SDK $
 * $Copyright: (c) 2016 Broadcom Corp.
 * All Rights Reserved.$
 *
 **********************************************************************/

#ifndef __LINUX_DMA_H__
#define __LINUX_DMA_H__

#include <sal/types.h>

#ifdef __KERNEL__

#ifdef SAL_BDE_XLP
#define KMALLOC(size, flags)    __kmalloc(size, flags)
#else
#define KMALLOC(size, flags)    kmalloc(size, flags)
#endif

#if defined(CONFIG_IDT_79EB334) || defined(CONFIG_BCM4702)
/* ioremap is broken in kernel */
#define IOREMAP(addr, size) ((void *)KSEG1ADDR(addr))
#else
#define IOREMAP(addr, size) ioremap_nocache(addr, size)
#endif

#if defined (__mips__)
#if defined(CONFIG_NONCOHERENT_IO) || defined(CONFIG_DMA_NONCOHERENT)
/* Use flush/invalidate for cached memory */
#define NONCOHERENT_DMA_MEMORY
/* Remap virtual DMA addresses to non-cached segment */
#define REMAP_DMA_NONCACHED
#endif /* CONFIG_NONCOHERENT_IO || CONFIG_DMA_NONCOHERENT */
#endif /* __mips__ */

#if defined(BCM958525) && (LINUX_VERSION_CODE <= KERNEL_VERSION(3,6,5))
#define REMAP_DMA_NONCACHED
#endif

#ifndef DMA_BIT_MASK
#define DMA_BIT_MASK(n) (((n) == 64) ? ~0ULL : ((1ULL<<(n))-1))
#endif

extern void _dma_init(int robo_switch);
extern int _dma_cleanup(void);
extern void _dma_pprint(void);
extern uint32_t *_salloc(int d, int size, const char *name);
extern void _sfree(int d, void *ptr);
extern int _sinval(int d, void *ptr, int length);
extern int _sflush(int d, void *ptr, int length);
extern sal_paddr_t _l2p(int d, void *vaddr);
extern void *_p2l(int d, sal_paddr_t paddr);
extern int _dma_pool_allocated(void);
extern int _dma_range_valid(unsigned long phys_addr, unsigned long size);

#endif /* __KERNEL__ */

#endif /* __LINUX_DMA_H__ */
