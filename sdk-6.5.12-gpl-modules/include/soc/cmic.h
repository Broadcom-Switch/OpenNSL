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
