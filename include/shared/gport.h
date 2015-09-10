/*********************************************************************
 *
 * (C) Copyright Broadcom Corporation 2013-2015
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
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
 **********************************************************************
 * File:        gport.h
 * Details:     This file defines common error codes to be shared
 *                              between API layers.
 *
 *             Its contents are not used directly by applications;
 *             it is used only by header files of parent APIs which
 *             need to define error codes.
 *********************************************************************/

#ifndef _SHR_GPORT_H
#define _SHR_GPORT_H

/*
 * Defines:
 *     _SHR_GPORT_*
 * Purpose:
 *     GPORT (Generic port) definitions. GPORT can be used to specify
 *     a {module, port} pair, trunk, and other port types.
 */

#define _SHR_GPORT_NONE             (0)
#define _SHR_GPORT_INVALID         (-1)
#define _SHR_GPORT_TYPE_LOCAL               1  /* Port on local unit     */
#define _SHR_GPORT_TYPE_MODPORT             2  /* Module ID and port     */
#define _SHR_GPORT_TYPE_TRUNK               3  /* Trunk ID               */

#define _SHR_GPORT_TYPE_SHIFT                           26
#define _SHR_GPORT_TYPE_MASK                            0x3f

#define _SHR_GPORT_MODID_SHIFT                          11
#define _SHR_GPORT_MODID_MASK                           0x7fff
#define _SHR_GPORT_PORT_SHIFT                           0
#define _SHR_GPORT_PORT_MASK                            0x7ff
#define _SHR_GPORT_TRUNK_SHIFT                          0
#define _SHR_GPORT_TRUNK_MASK                           0x3ffffff

#define _SHR_GPORT_IS_MODPORT(_gport)    \
        (((_gport) >> _SHR_GPORT_TYPE_SHIFT) == _SHR_GPORT_TYPE_MODPORT)

#define _SHR_GPORT_MODPORT_SET(_gport, _module, _port)                       \
        ((_gport) = (_SHR_GPORT_TYPE_MODPORT   << _SHR_GPORT_TYPE_SHIFT)   | \
         (((_module) & _SHR_GPORT_MODID_MASK)  << _SHR_GPORT_MODID_SHIFT)  | \
         (((_port) & _SHR_GPORT_PORT_MASK)     << _SHR_GPORT_PORT_SHIFT))

#define _SHR_GPORT_MODPORT_MODID_GET(_gport)    \
        (((_gport) >> _SHR_GPORT_MODID_SHIFT) & _SHR_GPORT_MODID_MASK)

#define _SHR_GPORT_MODPORT_PORT_GET(_gport)     \
        (((_gport) >> _SHR_GPORT_PORT_SHIFT) & _SHR_GPORT_PORT_MASK)

#endif  /* !_SHR_GPORT_H */
