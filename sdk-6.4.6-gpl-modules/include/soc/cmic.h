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
 * $Id: cmic.h,v 1.1 Broadcom SDK $
 * $Copyright: (c) 2005 Broadcom Corp.
 * All Rights Reserved.$
 *
 * File:        cmic.h
 * Purpose:     Maps out structures used for CMIC operations and
 *              exports routines and constants.
 */

#ifndef _SOC_CMIC_H
#define _SOC_CMIC_H

/* IRQ Register (RO) */
#define CMIC_IRQ_STAT                   0x00000144

/* IRQ Mask Registers (R/W) */
#define CMIC_IRQ_MASK                   0x00000148
#define CMIC_IRQ_MASK_1                 0x0000006C
#define CMIC_IRQ_MASK_2                 0x00000070

#endif  /* !_SOC_CMIC_H */
