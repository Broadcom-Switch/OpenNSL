/*
 * $Id: pci_util.h Broadcom OpenNSL $
 * $Copyright: Copyright 2016-2017 Broadcom Corporation.
 * This program is the proprietary software of Broadcom Corporation
 * and/or its licensors, and may only be used, duplicated, modified
 * or distributed pursuant to the terms and conditions of a separate,
 * written license agreement executed between you and Broadcom
 * (an "Authorized License").  Except as set forth in an Authorized
 * License, Broadcom grants no license (express or implied), right
 * to use, or waiver of any kind with respect to the Software, and
 * Broadcom expressly reserves all rights in and to the Software
 * and all intellectual property rights therein.  IF YOU HAVE
 * NO AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO USE THIS SOFTWARE
 * IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY BROADCOM AND DISCONTINUE
 * ALL USE OF THE SOFTWARE.
 *
 * Except as expressly set forth in the Authorized License,
 *
 * 1.     This program, including its structure, sequence and organization,
 * constitutes the valuable trade secrets of Broadcom, and you shall use
 * all reasonable efforts to protect the confidentiality thereof,
 * and to use this information only in connection with your use of
 * Broadcom integrated circuit products.
 *
 * 2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS
 * PROVIDED "AS IS" AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES,
 * REPRESENTATIONS OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY,
 * OR OTHERWISE, WITH RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY
 * DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY,
 * NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES,
 * ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
 * CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING
 * OUT OF USE OR PERFORMANCE OF THE SOFTWARE.
 *
 * 3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL
 * BROADCOM OR ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL,
 * INCIDENTAL, SPECIAL, INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER
 * ARISING OUT OF OR IN ANY WAY RELATING TO YOUR USE OF OR INABILITY
 * TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF
 * THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE ITSELF OR USD 1.00,
 * WHICHEVER IS GREATER. THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING
 * ANY FAILURE OF ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.$
 *
 * File:        pci_util.h
 *
 * Purpose:     This file contains OpenNSL PCI utility functions.
 */
#ifndef PCI_UTIL_H
#define PCI_UTIL_H

#include <stdint.h>

#define OPENNSL_CMIC_LED_DATA_RAM_SIZE         0x100
#define OPENNSL_CMIC_LED_PROGRAM_RAM_SIZE      0x100
#define OPENNSL_CMIC_LED_REG_SIZE              4
#define OPENNSL_CMIC_LEDUP0_CTRL_OFFSET        0x20000
#define OPENNSL_CMIC_LEDUP0_STATUS_OFFSET      0x20004
#define OPENNSL_CMIC_LEDUP0_DATA_RAM_OFFSET    0x20400
#define OPENNSL_CMIC_LEDUP0_PROGRAM_RAM_OFFSET 0x20800
#define OPENNSL_CMIC_LEDUP1_CTRL_OFFSET        0x21000
#define OPENNSL_CMIC_LEDUP1_STATUS_OFFSET      0x21004
#define OPENNSL_CMIC_LEDUP1_DATA_RAM_OFFSET    0x21400
#define OPENNSL_CMIC_LEDUP1_PROGRAM_RAM_OFFSET 0x21800
#define OPENNSL_CMIC_MMU_COSLC_COUNT_ADDR      10341
#define OPENNSL_CMIC_MMU_COSLC_COUNT_DATA      10342

#define OPENNSL_LC_LED_ENABLE                  0x1



/*****************************************************************//**
* \brief Function to read from the PCI.
*
* \param unit       [IN]   The switch unit number
*        addr       [IN]   PCI address to read from
*
* \return OPENNSL_E_XXX     OpenNSL API return code
********************************************************************/
uint32_t opennsl_pci_read(int unit, uint32_t addr);

/*****************************************************************//**
* \brief Function to write to the PCI.
*
* \param unit       [IN]   The switch unit number
*        addr       [IN]   PCI address to write to
*        data       [IN]   Data value to write into PCI
*
* \return OPENNSL_E_XXX     OpenNSL API return code
********************************************************************/
int opennsl_pci_write(int unit, uint32_t addr, uint32_t data);


#endif  /* PCI_UTIL_H */
