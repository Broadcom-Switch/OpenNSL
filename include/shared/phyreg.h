/******************************************************************************
 *
 * (C) Copyright Broadcom Corporation 2013-2016
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************
 * File:        phyreg.h
 * Details:     This file defines common PHY register definition.
 *
 *             Its contents are not used directly by applications;
 *             it is used only by header files of parent APIs which
 *             need to define PHY register definition.
 ******************************************************************************/

#ifndef _SHR_PHYREG_H
#define _SHR_PHYREG_H

#define _SHR_PORT_PHY_INTERNAL        0x00000001
#define _SHR_PORT_PHY_NOMAP           0x00000002
#define _SHR_PORT_PHY_CLAUSE45        0x00000004
#define _SHR_PORT_PHY_I2C_DATA8       0x00000008
#define _SHR_PORT_PHY_I2C_DATA16      0x00000010

#define _SHR_PORT_PHY_CLAUSE45_ADDR(_devad, _regad)     \
            ((((_devad) & 0x3F) << 16) |                \
             ((_regad) & 0xFFFF))

#endif  /* !_SHR_PHYREG_H */
