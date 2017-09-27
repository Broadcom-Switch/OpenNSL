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
 * $Id: linux-bde.h,v 1.24 Broadcom SDK $
 * $Copyright: (c) 2005 Broadcom Corp.
 * All Rights Reserved.$
 *
 * Linux Broadcom Device Enumerators
 *
 *
 * There are two Linux BDEs:
 *
 * 1. Linux Kernel BDE
 *
 *	This is a kernel module implementing a BDE
 *	for the driver running as part of the kernel. 
 * 	
 *	It manages the devices through the linux PCI interfaces, 
 *	and manages a chunk of contiguous, boot-time allocated
 *	DMA memory. This is all that is needed if the BCM driver
 *	is run as part of the kernel (in another module). 
 *
 * 2. Linux User BDE
 *
 *	This is a kernel module and userland library which implement
 * 	a complete BDE for applications running in userland. 
 *	
 *	The kernel module relies upon the real kernel bde, 
 *	and allows a user space application (through the user library)
 *	to talk directly to the devices. It also virtualized the device 
 *	interrupts, so the entire driver can be run as a userspace 
 *	application. 
 *	
 *	While this causes a significant degradation in performance, 
 *	because the system runs as a user application, the development
 *	and debugging process is about a gillion times easier. 
 *	After the core logic is debugged, it can be retargeted using
 *	only the kernel bde and run in the kernel. 
 *	
 *
 **********************************************************************/

#ifndef __LINUX_BDE_H__
#define __LINUX_BDE_H__

#include <sal/types.h>

#include <ibde.h>


/* 
 * Device Major Numbers
 * 
 * The kernel and user bdes need unique major numbers
 * on systems that do not use devfs. 
 * 
 * They are defined here, along with the module names, 
 * to document them if you need to mknod them (or open) them, 
 * and to keep them unique. 
 *
 */

#include <linux/version.h>

#ifdef __KERNEL__
#include <linux/types.h>
/* Key stone and Raptor has 2.6.21 but don't have definition */
#if defined(KEYSTONE) || defined(RAPTOR)
#if (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,21))
    #ifdef PHYS_ADDRS_ARE_64BITS
    typedef u64 phys_addr_t;
    #else
    typedef u32 phys_addr_t;
    #endif
  #endif
#endif
#endif


#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,15))
#define LINUX_BDE_DMA_DEVICE_SUPPORT
#endif

#define LINUX_KERNEL_BDE_NAME 	"linux-kernel-bde"
#define LINUX_KERNEL_BDE_MAJOR 	127

#define LINUX_USER_BDE_NAME 	"linux-user-bde"
#define LINUX_USER_BDE_MAJOR   	126


/* Max devices */
/* 16 switch chips + 2 out-of-band Ethernet + 2 CPUs */
#define LINUX_BDE_MAX_SWITCH_DEVICES    16
#define LINUX_BDE_MAX_ETHER_DEVICES     2
#define LINUX_BDE_MAX_CPU_DEVICES       2
#define LINUX_BDE_MAX_DEVICES           (LINUX_BDE_MAX_SWITCH_DEVICES + \
                                         LINUX_BDE_MAX_ETHER_DEVICES + \
                                         LINUX_BDE_MAX_CPU_DEVICES) 

/* 
 * PCI devices will be initialized by the Linux Kernel, 
 * regardless of architecture.
 *
 * You need only provide bus endian settings. 
 */

typedef struct linux_bde_bus_s {
    int be_pio;
    int be_packet;
    int be_other;
} linux_bde_bus_t;



/* Device state used for PCI hot swap case. */
/*
 * BDE_DEV_STATE_NORMAL : A device is probed normally. Or when the device 
 * resource has been updated after "CHANGED", the state will move back to 
 * "NORMAL".
 */
#define BDE_DEV_STATE_NORMAL       (0)
/*
 * BDE_DEV_STATE_REMOVED : A previous probed device was removed.
 * We will avoid any device access while the device is in this state.
 * The state will be moved to "CHANGED" if the device is re-inserted
 * and re-probed.
 */
#define BDE_DEV_STATE_REMOVED      (1)
/* 
 * BDE_DEV_STATE_CHANGED : The device is re-probed after having been removed.
 * The resouces assigned to the device might have been changed after
 * re-probing, so we need to re-initialize our resource database accordingly. 
 * The state will change to "NORMAL" when the resource have been updated.
 */
#define BDE_DEV_STATE_CHANGED      (2)

extern int linux_bde_create(linux_bde_bus_t* bus, ibde_t** bde);
extern int linux_bde_destroy(ibde_t* bde);
#ifdef BCM_INSTANCE_SUPPORT
extern int linux_bde_instance_attach(unsigned int dev_mask,unsigned int dma_size);
#endif

#ifdef __KERNEL__

/*
 *  Backdoors provided by the kernel bde
 *
 */

/*
 * The user bde needs to get cpu physical address for
 * the userland code to mmap.
 * And the second address is bus address, it is either
 * identical to cpu physical address or another address
 * (IOVA) translated by IOMMU.
 */
extern int lkbde_get_dma_info(phys_addr_t *cpu_pbase, phys_addr_t *dma_pbase, ssize_t *size);
extern uint32 lkbde_get_dev_phys(int d);
extern uint32 lkbde_get_dev_phys_hi(int d);

/*
 * Virtual device address needed by kernel space
 * interrupt handler.
 */
extern void *lkbde_get_dev_virt(int d);

/*
 * The user bde needs to get some physical addresses for
 * the userland code to mmap. The following functions
 * supports multiple resources for a single device.
 */
extern int lkbde_get_dev_resource(int d, int rsrc, uint32 *flags,
                                  uint32 *phys_lo, uint32 *phys_hi); 

/*
 * Backdoor to retrieve OS device structure to be used for
 * DMA operations.
 */
extern void *lkbde_get_dma_dev(int d);

/*
 * Backdoor to retrieve original hardware/OS device.
 */
extern void *lkbde_get_hw_dev(int d);

/*
 * Retrive the device state from Kernel BDE.
 * Used for KNET and User BDE for pci hot swap case.
 */
extern int lkbde_dev_state_get(int d, uint32 *state);
extern int lkbde_dev_state_set(int d, uint32 state);

/*
 * Retrive the mapping between emulated HW device and instance id
 */
extern int lkbde_dev_instid_get(int d, uint32 *instid);
extern int lkbde_dev_instid_set(int d, uint32 instid);

/*
 * Functions that allow an interrupt handler in user mode to
 * coexist with interrupt handler in kernel module.
 */
extern int lkbde_irq_mask_set(int d, uint32 addr, uint32 mask, uint32 fmask);
extern int lkbde_irq_mask_get(int d, uint32 *mask, uint32 *fmask);

#if (defined(BCM_PETRA_SUPPORT) || defined(BCM_DFE_SUPPORT))
extern int lkbde_cpu_write(int d, uint32 addr, uint32 *buf);
extern int lkbde_cpu_read(int d, uint32 addr, uint32 *buf);
extern int lkbde_cpu_pci_register(int d);
#endif

/*
 * This flag must be OR'ed onto the device number when calling
 * interrupt_connect/disconnect and irq_mask_set functions from
 * a secondary device driver.
 */
#define LKBDE_ISR2_DEV  0x8000

#if defined(BCM_PETRA_SUPPORT) || defined(BCM_DFE_SUPPORT)
#include <linux/version.h>
#if defined(__DUNE_LINUX_BCM_CPU_PCIE__) && LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,26)
#ifndef _SIMPLE_MEMORY_ALLOCATION_
#define _SIMPLE_MEMORY_ALLOCATION_ 1
#endif
#ifndef USE_LINUX_BDE_MMAP
#define USE_LINUX_BDE_MMAP 1
#endif
#endif
#endif

#if defined(IPROC_CMICD) && defined(CONFIG_CMA)
#ifndef _SIMPLE_MEMORY_ALLOCATION_
#define _SIMPLE_MEMORY_ALLOCATION_ 1
#endif
#endif

/* Don't use _SIMPLE_MEMORY_ALLOCATION_ method for newer kernel than 3.10.0 */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0))
#ifndef _SIMPLE_MEMORY_ALLOCATION_
#define _SIMPLE_MEMORY_ALLOCATION_ 0
#endif
#endif

/* Allocation via dma_alloc_coherent is turned off by default */
#ifndef _SIMPLE_MEMORY_ALLOCATION_
#define _SIMPLE_MEMORY_ALLOCATION_ 9 /* compile in the allocation method, but do not use it by default */
#endif

/* By default we use our private mmap only if /dev/mem mmap has restrictions */
#ifndef USE_LINUX_BDE_MMAP
#ifdef CONFIG_STRICT_DEVMEM
#define USE_LINUX_BDE_MMAP 1
#else
#define USE_LINUX_BDE_MMAP 0
#endif
#endif

#endif /* __KERNEL__ */

#endif /* __LINUX_BDE_H__ */
