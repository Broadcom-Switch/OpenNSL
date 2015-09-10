/** \addtogroup switch Switch Management
 *  @{
 */
/*****************************************************************************
 * 
 * (C) Copyright Broadcom Corporation 2013-2015
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * 
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 ***************************************************************************//**
 * \file			switch.h
 ******************************************************************************/

#ifndef __OPENNSL_SWITCH_H__
#define __OPENNSL_SWITCH_H__

#include <opennsl/types.h>
#include <opennsl/port.h>
#include <opennsl/error.h>
#include <opennsl/stg.h>
#include <shared/switch.h>
#include <shared/bitop.h>

/** Switch controls. */
typedef enum opennsl_switch_control_e {
    opennslswitchReservedEnum1 = 0, 
    opennslswitchReservedEnum2 = 1, 
    opennslswitchReservedEnum3 = 2, 
    opennslswitchReservedEnum4 = 3, 
    opennslswitchReservedEnum5 = 4, 
    opennslswitchReservedEnum6 = 5, 
    opennslswitchReservedEnum7 = 6, 
    opennslswitchReservedEnum8 = 7, 
    opennslswitchReservedEnum9 = 8, 
    opennslswitchReservedEnum10 = 9, 
    opennslswitchReservedEnum11 = 10, 
    opennslswitchReservedEnum12 = 11, 
    opennslswitchReservedEnum13 = 12, 
    opennslswitchReservedEnum14 = 13, 
    opennslswitchReservedEnum15 = 14, 
    opennslswitchReservedEnum16 = 15, 
    opennslswitchReservedEnum17 = 16, 
    opennslswitchReservedEnum18 = 17, 
    opennslswitchReservedEnum19 = 18, 
    opennslswitchReservedEnum20 = 19, 
    opennslswitchReservedEnum21 = 20, 
    opennslswitchReservedEnum22 = 21, 
    opennslswitchReservedEnum23 = 22, 
    opennslswitchReservedEnum24 = 23, 
    opennslswitchReservedEnum25 = 24, 
    opennslswitchReservedEnum26 = 25, 
    opennslSwitchUnknownL3DestToCpu = 26, /**< DIP not found in L3/LPM tables. */
    opennslswitchReservedEnum27 = 27, 
    opennslswitchReservedEnum28 = 28, 
    opennslswitchReservedEnum29 = 29, 
    opennslswitchReservedEnum30 = 30, 
    opennslswitchReservedEnum31 = 31, 
    opennslswitchReservedEnum32 = 32, 
    opennslswitchReservedEnum33 = 33, 
    opennslswitchReservedEnum34 = 34, 
    opennslswitchReservedEnum35 = 35, 
    opennslswitchReservedEnum36 = 36, 
    opennslswitchReservedEnum37 = 37, 
    opennslswitchReservedEnum38 = 38, 
    opennslswitchReservedEnum39 = 39, 
    opennslSwitchV6L3DstMissToCpu = 40, /**< IPv6 unknown dest packets to CPU. */
    opennslswitchReservedEnum40 = 41, 
    opennslswitchReservedEnum41 = 42, 
    opennslSwitchV4L3DstMissToCpu = 43, /**< IPv6 unknown dest packets to CPU. */
    opennslswitchReservedEnum42 = 44, 
    opennslswitchReservedEnum43 = 45, 
    opennslswitchReservedEnum44 = 46, 
    opennslswitchReservedEnum45 = 47, 
    opennslSwitchL3SlowpathToCpu = 48,  /**< Slowpath packets to CPU. */
    opennslswitchReservedEnum46 = 49, 
    opennslswitchReservedEnum47 = 50, 
    opennslswitchReservedEnum48 = 51, 
    opennslswitchReservedEnum49 = 52, 
    opennslswitchReservedEnum50 = 53, 
    opennslswitchReservedEnum51 = 54, 
    opennslswitchReservedEnum52 = 55, 
    opennslswitchReservedEnum53 = 56, 
    opennslswitchReservedEnum54 = 57, 
    opennslswitchReservedEnum55 = 58, 
    opennslswitchReservedEnum56 = 59, 
    opennslswitchReservedEnum57 = 60, 
    opennslswitchReservedEnum58 = 61, 
    opennslswitchReservedEnum59 = 62, 
    opennslswitchReservedEnum60 = 63, 
    opennslswitchReservedEnum61 = 64, 
    opennslswitchReservedEnum62 = 65, 
    opennslswitchReservedEnum63 = 66, 
    opennslswitchReservedEnum64 = 67, 
    opennslswitchReservedEnum65 = 68, 
    opennslswitchReservedEnum66 = 69, 
    opennslswitchReservedEnum67 = 70, 
    opennslswitchReservedEnum68 = 71, 
    opennslswitchReservedEnum69 = 72, 
    opennslswitchReservedEnum70 = 73, 
    opennslswitchReservedEnum71 = 74, 
    opennslswitchReservedEnum72 = 75, 
    opennslswitchReservedEnum73 = 76, 
    opennslswitchReservedEnum74 = 77, 
    opennslswitchReservedEnum75 = 78, 
    opennslswitchReservedEnum76 = 79, 
    opennslswitchReservedEnum77 = 80, 
    opennslswitchReservedEnum78 = 81, 
    opennslswitchReservedEnum79 = 82, 
    opennslswitchReservedEnum80 = 83, 
    opennslSwitchArpReplyToCpu = 84,    /**< ARP replies to CPU. */
    opennslswitchReservedEnum81 = 85, 
    opennslSwitchArpRequestToCpu = 86,  /**< ARP requests to CPU. */
    opennslswitchReservedEnum82 = 87, 
    opennslswitchReservedEnum83 = 88, 
    opennslSwitchNdPktToCpu = 89,       /**< ND packets to CPU. */
    opennslswitchReservedEnum84 = 90, 
    opennslswitchReservedEnum85 = 91, 
    opennslSwitchIgmpPktToCpu = 92,     /**< IGMP packets to CPU. */
    opennslSwitchIgmpToCPU = opennslSwitchIgmpPktToCpu, /**< Legacy support for IGMP packets to
                                           CPU. */
    opennslswitchReservedEnum86 = 93, 
    opennslSwitchDhcpPktToCpu = 94,     /**< DHCP packets to CPU. */
    opennslSwitchDhcpPktDrop = 95,      /**< DHCP packets dropped. */
    opennslswitchReservedEnum87 = 96, 
    opennslswitchReservedEnum88 = 97, 
    opennslSwitchV4ResvdMcPktToCpu = 98, /**< IPv4 reserved MC packets to CPU. */
    opennslswitchReservedEnum89 = 99, 
    opennslswitchReservedEnum90 = 100, 
    opennslswitchReservedEnum91 = 101, 
    opennslswitchReservedEnum92 = 102, 
    opennslswitchReservedEnum93 = 103, 
    opennslswitchReservedEnum94 = 104, 
    opennslswitchReservedEnum95 = 105, 
    opennslswitchReservedEnum96 = 106, 
    opennslswitchReservedEnum97 = 107, 
    opennslswitchReservedEnum98 = 108, 
    opennslswitchReservedEnum99 = 109, 
    opennslswitchReservedEnum100 = 110, 
    opennslswitchReservedEnum101 = 111, 
    opennslswitchReservedEnum102 = 112, 
    opennslswitchReservedEnum103 = 113, 
    opennslswitchReservedEnum104 = 114, 
    opennslswitchReservedEnum105 = 115, 
    opennslswitchReservedEnum106 = 116, 
    opennslswitchReservedEnum107 = 117, 
    opennslswitchReservedEnum108 = 118, 
    opennslswitchReservedEnum109 = 119, 
    opennslswitchReservedEnum110 = 120, 
    opennslswitchReservedEnum111 = 121, 
    opennslswitchReservedEnum112 = 122, 
    opennslswitchReservedEnum113 = 123, 
    opennslswitchReservedEnum114 = 124, 
    opennslswitchReservedEnum115 = 125, 
    opennslswitchReservedEnum116 = 126, 
    opennslswitchReservedEnum117 = 127, 
    opennslswitchReservedEnum118 = 128, 
    opennslswitchReservedEnum119 = 129, 
    opennslswitchReservedEnum120 = 130, 
    opennslswitchReservedEnum121 = 131, 
    opennslswitchReservedEnum122 = 132, 
    opennslswitchReservedEnum123 = 133, 
    opennslswitchReservedEnum124 = 134, 
    opennslswitchReservedEnum125 = 135, 
    opennslSwitchHashControl = 136,     /**< Hash Control of fields. */
    opennslswitchReservedEnum126 = 137, 
    opennslswitchReservedEnum127 = 138, 
    opennslswitchReservedEnum128 = 139, 
    opennslswitchReservedEnum129 = 140, 
    opennslswitchReservedEnum130 = 141, 
    opennslswitchReservedEnum131 = 142, 
    opennslswitchReservedEnum132 = 143, 
    opennslswitchReservedEnum133 = 144, 
    opennslswitchReservedEnum134 = 145, 
    opennslswitchReservedEnum135 = 146, 
    opennslSwitchHashSeed0 = 147,       /**< network switch hash seeds. */
    opennslSwitchHashSeed1 = 148,       /**< For enhanced hashing algoithm. */
    opennslSwitchHashField0PreProcessEnable = 149, /**< Enable pre-processing for enhanced
                                           hash mode 0. */
    opennslSwitchHashField1PreProcessEnable = 150, /**< Enable pre-processing for enhanced
                                           hash mode 1. */
    opennslSwitchHashField0Config = 151, /**< network switch enhanced hash mode 0
                                           config. */
    opennslSwitchHashField0Config1 = 152, /**< network switch enhanced hash mode 0
                                           config 1. */
    opennslSwitchHashField1Config = 153, /**< network switch enhanced hash mode 1
                                           config. */
    opennslSwitchHashField1Config1 = 154, /**< network switch enhanced hash mode 1
                                           config 1. */
    opennslswitchReservedEnum136 = 155, 
    opennslSwitchHashSelectControl = 156, /**< network switch field selection
                                           control. */
    opennslSwitchHashIP4Field0 = 157,   /**< network switch enhanced hash field. */
    opennslSwitchHashIP4Field1 = 158,   /**< Selections for IPv4 packets. */
    opennslSwitchHashIP4TcpUdpField0 = 159, /**< network switch enhanced hash field. */
    opennslSwitchHashIP4TcpUdpField1 = 160, /**< Selections for IPv4 TCP/UDP packets. */
    opennslSwitchHashIP4TcpUdpPortsEqualField0 = 161, /**< network switch enhanced hash field. */
    opennslSwitchHashIP4TcpUdpPortsEqualField1 = 162, /**< Selections for IPv4 TCP/UDP packets
                                           with source L4 port equals to
                                           destination L4 port. */
    opennslSwitchHashIP6Field0 = 163,   /**< network switch enhanced hash field. */
    opennslSwitchHashIP6Field1 = 164,   /**< Selections for IPv6 packets. */
    opennslSwitchHashIP6TcpUdpField0 = 165, /**< network switch enhanced hash field. */
    opennslSwitchHashIP6TcpUdpField1 = 166, /**< Selections for IPv6 TCP/UDP packets. */
    opennslSwitchHashIP6TcpUdpPortsEqualField0 = 167, /**< network switch enhanced hash field. */
    opennslSwitchHashIP6TcpUdpPortsEqualField1 = 168, /**< Selections for IPv6 TCP/UDP packets
                                           with source L4 port equals to
                                           destination L4 port. */
    opennslswitchReservedEnum137 = 169, 
    opennslswitchReservedEnum138 = 170, 
    opennslswitchReservedEnum139 = 171, 
    opennslswitchReservedEnum140 = 172, 
    opennslswitchReservedEnum141 = 173, 
    opennslswitchReservedEnum142 = 174, 
    opennslswitchReservedEnum143 = 175, 
    opennslswitchReservedEnum144 = 176, 
    opennslswitchReservedEnum145 = 177, 
    opennslswitchReservedEnum146 = 178, 
    opennslswitchReservedEnum147 = 179, 
    opennslswitchReservedEnum148 = 180, 
    opennslswitchReservedEnum149 = 181, 
    opennslswitchReservedEnum150 = 182, 
    opennslswitchReservedEnum151 = 183, 
    opennslswitchReservedEnum152 = 184, 
    opennslswitchReservedEnum153 = 185, 
    opennslswitchReservedEnum154 = 186, 
    opennslswitchReservedEnum155 = 187, 
    opennslswitchReservedEnum156 = 188, 
    opennslswitchReservedEnum157 = 189, 
    opennslswitchReservedEnum158 = 190, 
    opennslswitchReservedEnum159 = 191, 
    opennslswitchReservedEnum160 = 192, 
    opennslswitchReservedEnum161 = 193, 
    opennslswitchReservedEnum162 = 194, 
    opennslswitchReservedEnum163 = 195, 
    opennslswitchReservedEnum164 = 196, 
    opennslswitchReservedEnum165 = 197, 
    opennslswitchReservedEnum166 = 198, 
    opennslswitchReservedEnum167 = 199, 
    opennslswitchReservedEnum168 = 200, 
    opennslswitchReservedEnum169 = 201, 
    opennslswitchReservedEnum170 = 202, 
    opennslswitchReservedEnum171 = 203, 
    opennslswitchReservedEnum172 = 204, 
    opennslswitchReservedEnum173 = 205, 
    opennslswitchReservedEnum174 = 206, 
    opennslswitchReservedEnum175 = 207, 
    opennslswitchReservedEnum176 = 208, 
    opennslswitchReservedEnum177 = 209, 
    opennslSwitchECMPHashSet0Offset = 210, /**< network switch enhanced hash bits. */
    opennslSwitchECMPHashSet1Offset = 211, /**< Selections for ECMP. */
    opennslswitchReservedEnum178 = 212, 
    opennslswitchReservedEnum179 = 213, 
    opennslswitchReservedEnum180 = 214, 
    opennslswitchReservedEnum181 = 215, 
    opennslswitchReservedEnum182 = 216, 
    opennslswitchReservedEnum183 = 217, 
    opennslswitchReservedEnum184 = 218, 
    opennslswitchReservedEnum185 = 219, 
    opennslswitchReservedEnum186 = 220, 
    opennslswitchReservedEnum187 = 221, 
    opennslswitchReservedEnum188 = 222, 
    opennslswitchReservedEnum189 = 223, 
    opennslswitchReservedEnum190 = 224, 
    opennslswitchReservedEnum191 = 225, 
    opennslswitchReservedEnum192 = 226, 
    opennslswitchReservedEnum193 = 227, 
    opennslswitchReservedEnum194 = 228, 
    opennslswitchReservedEnum195 = 229, 
    opennslSwitchL3EgressMode = 230,    /**< Enable advanced egress management. */
    opennslswitchReservedEnum196 = 231, 
    opennslSwitchL3IngressMode = 232,   /**< Enable advanced Ingress-interface
                                           management. */
    opennslswitchReservedEnum197 = 233, 
    opennslswitchReservedEnum198 = 234, 
    opennslswitchReservedEnum199 = 235, 
    opennslswitchReservedEnum200 = 236, 
    opennslswitchReservedEnum201 = 237, 
    opennslSwitchWarmBoot = 238,        /**< Set Warm boot state. */
    opennslSwitchStableSelect = 239,    /**< Select the storage (or stable)
                                           location for Level 2 Warm Boot. */
    opennslSwitchStableSize = 240,      /**< Select the storage (or stable) size
                                           (bytes) for Level 2 Warm Boot. */
    opennslSwitchStableUsed = 241,      /**< Query the storage (or stable) usage
                                           (bytes) for Level 2 Warm Boot. */
    opennslSwitchStableConsistent = 242, /**< Query the storage (or stable) for
                                           whether state is believed consistent
                                           with hardware (API completed prior to
                                           warmboot). */
    opennslSwitchControlSync = 243,     /**< Force a sync of the Level 2 warm boot
                                           state on demand. */
    opennslSwitchControlAutoSync = 244, /**< Perform a sync of the Level 2 warm
                                           boot state after every API. */
    opennslswitchReservedEnum202 = 245, 
    opennslswitchReservedEnum203 = 246, 
    opennslswitchReservedEnum204 = 247, 
    opennslswitchReservedEnum205 = 248, 
    opennslswitchReservedEnum206 = 249, 
    opennslSwitchL3UcastTtl1ToCpu = 250, /**< Copy L3 Ucast with TTL 1 to CPU. */
    opennslswitchReservedEnum207 = 251, 
    opennslswitchReservedEnum208 = 252, 
    opennslswitchReservedEnum209 = 253, 
    opennslswitchReservedEnum210 = 254, 
    opennslswitchReservedEnum211 = 255, 
    opennslswitchReservedEnum212 = 256, 
    opennslswitchReservedEnum213 = 257, 
    opennslswitchReservedEnum214 = 258, 
    opennslswitchReservedEnum215 = 259, 
    opennslswitchReservedEnum216 = 260, 
    opennslswitchReservedEnum217 = 261, 
    opennslswitchReservedEnum218 = 262, 
    opennslswitchReservedEnum219 = 263, 
    opennslswitchReservedEnum220 = 264, 
    opennslswitchReservedEnum221 = 265, 
    opennslswitchReservedEnum222 = 266, 
    opennslswitchReservedEnum223 = 267, 
    opennslswitchReservedEnum224 = 268, 
    opennslswitchReservedEnum225 = 269, 
    opennslswitchReservedEnum226 = 270, 
    opennslswitchReservedEnum227 = 271, 
    opennslswitchReservedEnum228 = 272, 
    opennslswitchReservedEnum229 = 273, 
    opennslswitchReservedEnum230 = 274, 
    opennslswitchReservedEnum231 = 275, 
    opennslswitchReservedEnum232 = 276, 
    opennslswitchReservedEnum233 = 277, 
    opennslswitchReservedEnum234 = 278, 
    opennslswitchReservedEnum235 = 279, 
    opennslswitchReservedEnum236 = 280, 
    opennslswitchReservedEnum237 = 281, 
    opennslswitchReservedEnum238 = 282, 
    opennslswitchReservedEnum239 = 283, 
    opennslswitchReservedEnum240 = 284, 
    opennslswitchReservedEnum241 = 285, 
    opennslswitchReservedEnum242 = 286, 
    opennslswitchReservedEnum243 = 287, 
    opennslswitchReservedEnum244 = 288, 
    opennslswitchReservedEnum245 = 289, 
    opennslswitchReservedEnum246 = 290, 
    opennslswitchReservedEnum247 = 291, 
    opennslswitchReservedEnum248 = 292, 
    opennslswitchReservedEnum249 = 293, 
    opennslswitchReservedEnum250 = 294, 
    opennslswitchReservedEnum251 = 295, 
    opennslswitchReservedEnum252 = 296, 
    opennslswitchReservedEnum253 = 297, 
    opennslswitchReservedEnum254 = 298, 
    opennslswitchReservedEnum255 = 299, 
    opennslswitchReservedEnum256 = 300, 
    opennslswitchReservedEnum257 = 301, 
    opennslswitchReservedEnum258 = 302, 
    opennslswitchReservedEnum259 = 303, 
    opennslswitchReservedEnum260 = 304, 
    opennslswitchReservedEnum261 = 305, 
    opennslswitchReservedEnum262 = 306, 
    opennslswitchReservedEnum263 = 307, 
    opennslswitchReservedEnum264 = 308, 
    opennslswitchReservedEnum265 = 309, 
    opennslswitchReservedEnum266 = 310, 
    opennslswitchReservedEnum267 = 311, 
    opennslswitchReservedEnum268 = 312, 
    opennslswitchReservedEnum269 = 313, 
    opennslswitchReservedEnum270 = 314, 
    opennslswitchReservedEnum271 = 315, 
    opennslswitchReservedEnum272 = 316, 
    opennslswitchReservedEnum273 = 317, 
    opennslswitchReservedEnum274 = 318, 
    opennslswitchReservedEnum275 = 319, 
    opennslswitchReservedEnum276 = 320, 
    opennslswitchReservedEnum277 = 321, 
    opennslswitchReservedEnum278 = 322, 
    opennslswitchReservedEnum279 = 323, 
    opennslswitchReservedEnum280 = 324, 
    opennslswitchReservedEnum281 = 325, 
    opennslswitchReservedEnum282 = 326, 
    opennslswitchReservedEnum283 = 327, 
    opennslswitchReservedEnum284 = 328, 
    opennslswitchReservedEnum285 = 329, 
    opennslswitchReservedEnum286 = 330, 
    opennslswitchReservedEnum287 = 331, 
    opennslswitchReservedEnum288 = 332, 
    opennslswitchReservedEnum289 = 333, 
    opennslswitchReservedEnum290 = 334, 
    opennslswitchReservedEnum291 = 335, 
    opennslswitchReservedEnum292 = 336, 
    opennslswitchReservedEnum293 = 337, 
    opennslswitchReservedEnum294 = 338, 
    opennslswitchReservedEnum295 = 339, 
    opennslswitchReservedEnum296 = 340, 
    opennslswitchReservedEnum297 = 341, 
    opennslswitchReservedEnum298 = 342, 
    opennslswitchReservedEnum299 = 343, 
    opennslswitchReservedEnum300 = 344, 
    opennslswitchReservedEnum301 = 345, 
    opennslswitchReservedEnum302 = 346, 
    opennslswitchReservedEnum303 = 347, 
    opennslswitchReservedEnum304 = 348, 
    opennslswitchReservedEnum305 = 349, 
    opennslswitchReservedEnum306 = 350, 
    opennslswitchReservedEnum307 = 351, 
    opennslswitchReservedEnum308 = 352, 
    opennslswitchReservedEnum309 = 353, 
    opennslswitchReservedEnum310 = 354, 
    opennslswitchReservedEnum311 = 355, 
    opennslswitchReservedEnum312 = 356, 
    opennslswitchReservedEnum313 = 357, 
    opennslswitchReservedEnum314 = 358, 
    opennslswitchReservedEnum315 = 359, 
    opennslswitchReservedEnum316 = 360, 
    opennslswitchReservedEnum317 = 361, 
    opennslswitchReservedEnum318 = 362, 
    opennslswitchReservedEnum319 = 363, 
    opennslswitchReservedEnum320 = 364, 
    opennslswitchReservedEnum321 = 365, 
    opennslswitchReservedEnum322 = 366, 
    opennslswitchReservedEnum323 = 367, 
    opennslswitchReservedEnum324 = 368, 
    opennslswitchReservedEnum325 = 369, 
    opennslswitchReservedEnum326 = 370, 
    opennslswitchReservedEnum327 = 371, 
    opennslswitchReservedEnum328 = 372, 
    opennslswitchReservedEnum329 = 373, 
    opennslswitchReservedEnum330 = 374, 
    opennslswitchReservedEnum331 = 375, 
    opennslswitchReservedEnum332 = 376, 
    opennslswitchReservedEnum333 = 377, 
    opennslswitchReservedEnum334 = 378, 
    opennslswitchReservedEnum335 = 379, 
    opennslswitchReservedEnum336 = 380, 
    opennslswitchReservedEnum337 = 381, 
    opennslswitchReservedEnum338 = 382, 
    opennslswitchReservedEnum339 = 383, 
    opennslswitchReservedEnum340 = 384, 
    opennslswitchReservedEnum341 = 385, 
    opennslswitchReservedEnum342 = 386, 
    opennslswitchReservedEnum343 = 387, 
    opennslswitchReservedEnum344 = 388, 
    opennslswitchReservedEnum345 = 389, 
    opennslswitchReservedEnum346 = 390, 
    opennslswitchReservedEnum347 = 391, 
    opennslswitchReservedEnum348 = 392, 
    opennslswitchReservedEnum349 = 393, 
    opennslswitchReservedEnum350 = 394, 
    opennslswitchReservedEnum351 = 395, 
    opennslswitchReservedEnum352 = 396, 
    opennslswitchReservedEnum353 = 397, 
    opennslswitchReservedEnum354 = 398, 
    opennslswitchReservedEnum355 = 399, 
    opennslswitchReservedEnum356 = 400, 
    opennslswitchReservedEnum357 = 401, 
    opennslswitchReservedEnum358 = 402, 
    opennslswitchReservedEnum359 = 403, 
    opennslswitchReservedEnum360 = 404, 
    opennslswitchReservedEnum361 = 405, 
    opennslswitchReservedEnum362 = 406, 
    opennslswitchReservedEnum363 = 407, 
    opennslswitchReservedEnum364 = 408, 
    opennslswitchReservedEnum365 = 409, 
    opennslswitchReservedEnum366 = 410, 
    opennslswitchReservedEnum367 = 411, 
    opennslswitchReservedEnum368 = 412, 
    opennslswitchReservedEnum369 = 413, 
    opennslswitchReservedEnum370 = 414, 
    opennslswitchReservedEnum371 = 415, 
    opennslswitchReservedEnum372 = 416, 
    opennslswitchReservedEnum373 = 417, 
    opennslswitchReservedEnum374 = 418, 
    opennslswitchReservedEnum375 = 419, 
    opennslswitchReservedEnum376 = 420, 
    opennslswitchReservedEnum377 = 421, 
    opennslswitchReservedEnum378 = 422, 
    opennslswitchReservedEnum379 = 423, 
    opennslswitchReservedEnum380 = 424, 
    opennslswitchReservedEnum381 = 425, 
    opennslswitchReservedEnum382 = 426, 
    opennslswitchReservedEnum383 = 427, 
    opennslswitchReservedEnum384 = 428, 
    opennslswitchReservedEnum385 = 429, 
    opennslswitchReservedEnum386 = 430, 
    opennslswitchReservedEnum387 = 431, 
    opennslswitchReservedEnum388 = 432, 
    opennslswitchReservedEnum389 = 433, 
    opennslswitchReservedEnum390 = 434, 
    opennslswitchReservedEnum391 = 435, 
    opennslswitchReservedEnum392 = 436, 
    opennslswitchReservedEnum393 = 437, 
    opennslswitchReservedEnum394 = 438, 
    opennslswitchReservedEnum395 = 439, 
    opennslswitchReservedEnum396 = 440, 
    opennslswitchReservedEnum397 = 441, 
    opennslswitchReservedEnum398 = 442, 
    opennslswitchReservedEnum399 = 443, 
    opennslswitchReservedEnum400 = 444, 
    opennslswitchReservedEnum401 = 445, 
    opennslswitchReservedEnum402 = 446, 
    opennslswitchReservedEnum403 = 447, 
    opennslswitchReservedEnum404 = 448, 
    opennslswitchReservedEnum405 = 449, 
    opennslswitchReservedEnum406 = 450, 
    opennslswitchReservedEnum407 = 451, 
    opennslswitchReservedEnum408 = 452, 
    opennslswitchReservedEnum409 = 453, 
    opennslswitchReservedEnum410 = 454, 
    opennslswitchReservedEnum411 = 455, 
    opennslswitchReservedEnum412 = 456, 
    opennslswitchReservedEnum413 = 457, 
    opennslswitchReservedEnum414 = 458, 
    opennslswitchReservedEnum415 = 459, 
    opennslswitchReservedEnum416 = 460, 
    opennslswitchReservedEnum417 = 461, 
    opennslswitchReservedEnum418 = 462, 
    opennslswitchReservedEnum419 = 463, 
    opennslswitchReservedEnum420 = 464, 
    opennslswitchReservedEnum421 = 465, 
    opennslswitchReservedEnum422 = 466, 
    opennslswitchReservedEnum423 = 467, 
    opennslswitchReservedEnum424 = 468, 
    opennslswitchReservedEnum425 = 469, 
    opennslswitchReservedEnum426 = 470, 
    opennslswitchReservedEnum427 = 471, 
    opennslswitchReservedEnum428 = 472, 
    opennslswitchReservedEnum429 = 473, 
    opennslswitchReservedEnum430 = 474, 
    opennslswitchReservedEnum431 = 475, 
    opennslswitchReservedEnum432 = 476, 
    opennslswitchReservedEnum433 = 477, 
    opennslswitchReservedEnum434 = 478, 
    opennslswitchReservedEnum435 = 479, 
    opennslswitchReservedEnum436 = 480, 
    opennslswitchReservedEnum437 = 481, 
    opennslswitchReservedEnum438 = 482, 
    opennslswitchReservedEnum439 = 483, 
    opennslswitchReservedEnum440 = 484, 
    opennslswitchReservedEnum441 = 485, 
    opennslswitchReservedEnum442 = 486, 
    opennslswitchReservedEnum443 = 487, 
    opennslswitchReservedEnum444 = 488, 
    opennslswitchReservedEnum445 = 489, 
    opennslswitchReservedEnum446 = 490, 
    opennslswitchReservedEnum447 = 491, 
    opennslswitchReservedEnum448 = 492, 
    opennslswitchReservedEnum449 = 493, 
    opennslswitchReservedEnum450 = 494, 
    opennslswitchReservedEnum451 = 495, 
    opennslswitchReservedEnum452 = 496, 
    opennslswitchReservedEnum453 = 497, 
    opennslswitchReservedEnum454 = 498, 
    opennslswitchReservedEnum455 = 499, 
    opennslswitchReservedEnum456 = 500, 
    opennslswitchReservedEnum457 = 501, 
    opennslswitchReservedEnum458 = 502, 
    opennslswitchReservedEnum459 = 503, 
    opennslswitchReservedEnum460 = 504, 
    opennslswitchReservedEnum461 = 505, 
    opennslswitchReservedEnum462 = 506, 
    opennslswitchReservedEnum463 = 507, 
    opennslswitchReservedEnum464 = 508, 
    opennslswitchReservedEnum465 = 509, 
    opennslswitchReservedEnum466 = 510, 
    opennslswitchReservedEnum467 = 511, 
    opennslswitchReservedEnum468 = 512, 
    opennslswitchReservedEnum469 = 513, 
    opennslswitchReservedEnum470 = 514, 
    opennslswitchReservedEnum471 = 515, 
    opennslswitchReservedEnum472 = 516, 
    opennslswitchReservedEnum473 = 517, 
    opennslswitchReservedEnum474 = 518, 
    opennslswitchReservedEnum475 = 519, 
    opennslswitchReservedEnum476 = 520, 
    opennslswitchReservedEnum477 = 521, 
    opennslswitchReservedEnum478 = 522, 
    opennslswitchReservedEnum479 = 523, 
    opennslswitchReservedEnum480 = 524, 
    opennslswitchReservedEnum481 = 525, 
    opennslswitchReservedEnum482 = 526, 
    opennslswitchReservedEnum483 = 527, 
    opennslswitchReservedEnum484 = 528, 
    opennslswitchReservedEnum485 = 529, 
    opennslswitchReservedEnum486 = 530, 
    opennslswitchReservedEnum487 = 531, 
    opennslswitchReservedEnum488 = 532, 
    opennslswitchReservedEnum489 = 533, 
    opennslswitchReservedEnum490 = 534, 
    opennslswitchReservedEnum491 = 535, 
    opennslswitchReservedEnum492 = 536, 
    opennslswitchReservedEnum493 = 537, 
    opennslswitchReservedEnum494 = 538, 
    opennslswitchReservedEnum495 = 539, 
    opennslswitchReservedEnum496 = 540, 
    opennslswitchReservedEnum497 = 541, 
    opennslswitchReservedEnum498 = 542, 
    opennslswitchReservedEnum499 = 543, 
    opennslswitchReservedEnum500 = 544, 
    opennslswitchReservedEnum501 = 545, 
    opennslswitchReservedEnum502 = 546, 
    opennslswitchReservedEnum503 = 547, 
    opennslswitchReservedEnum504 = 548, 
    opennslswitchReservedEnum505 = 549, 
    opennslswitchReservedEnum506 = 550, 
    opennslswitchReservedEnum507 = 551, 
    opennslswitchReservedEnum508 = 552, 
    opennslswitchReservedEnum509 = 553, 
    opennslswitchReservedEnum510 = 554, 
    opennslswitchReservedEnum511 = 555, 
    opennslswitchReservedEnum512 = 556, 
    opennslswitchReservedEnum513 = 557, 
    opennslswitchReservedEnum514 = 558, 
    opennslswitchReservedEnum515 = 559, 
    opennslswitchReservedEnum516 = 560, 
    opennslswitchReservedEnum517 = 561, 
    opennslswitchReservedEnum518 = 562, 
    opennslswitchReservedEnum519 = 563, 
    opennslswitchReservedEnum520 = 564, 
    opennslswitchReservedEnum521 = 565, 
    opennslswitchReservedEnum522 = 566, 
    opennslswitchReservedEnum523 = 567, 
    opennslswitchReservedEnum524 = 568, 
    opennslswitchReservedEnum525 = 569, 
    opennslswitchReservedEnum526 = 570, 
    opennslswitchReservedEnum527 = 571, 
    opennslswitchReservedEnum528 = 572, 
    opennslswitchReservedEnum529 = 573, 
    opennslswitchReservedEnum530 = 574, 
    opennslswitchReservedEnum531 = 575, 
    opennslswitchReservedEnum532 = 576, 
    opennslswitchReservedEnum533 = 577, 
    opennslswitchReservedEnum534 = 578, 
    opennslswitchReservedEnum535 = 579, 
    opennslswitchReservedEnum536 = 580, 
    opennslswitchReservedEnum537 = 581, 
    opennslswitchReservedEnum538 = 582, 
    opennslswitchReservedEnum539 = 583, 
    opennslswitchReservedEnum540 = 584, 
    opennslswitchReservedEnum541 = 585, 
    opennslswitchReservedEnum542 = 586, 
    opennslswitchReservedEnum543 = 587, 
    opennslswitchReservedEnum544 = 588, 
    opennslswitchReservedEnum545 = 589, 
    opennslswitchReservedEnum546 = 590, 
    opennslswitchReservedEnum547 = 591, 
    opennslswitchReservedEnum548 = 592, 
    opennslswitchReservedEnum549 = 593, 
    opennslswitchReservedEnum550 = 594, 
    opennslswitchReservedEnum551 = 595, 
    opennslswitchReservedEnum552 = 596, 
    opennslswitchReservedEnum553 = 597, 
    opennslswitchReservedEnum554 = 598, 
    opennslswitchReservedEnum555 = 599, 
    opennslswitchReservedEnum556 = 600, 
    opennslswitchReservedEnum557 = 601, 
    opennslswitchReservedEnum558 = 602, 
    opennslswitchReservedEnum559 = 603, 
    opennslswitchReservedEnum560 = 604, 
    opennslswitchReservedEnum561 = 605, 
    opennslswitchReservedEnum562 = 606, 
    opennslswitchReservedEnum563 = 607, 
    opennslswitchReservedEnum564 = 608, 
    opennslswitchReservedEnum565 = 609, 
    opennslswitchReservedEnum566 = 610, 
    opennslswitchReservedEnum567 = 611, 
    opennslswitchReservedEnum568 = 612, 
    opennslswitchReservedEnum569 = 613, 
    opennslswitchReservedEnum570 = 614, 
    opennslswitchReservedEnum571 = 615, 
    opennslswitchReservedEnum572 = 616, 
    opennslswitchReservedEnum573 = 617, 
    opennslswitchReservedEnum574 = 618, 
    opennslswitchReservedEnum575 = 619, 
    opennslswitchReservedEnum576 = 620, 
    opennslswitchReservedEnum577 = 621, 
    opennslswitchReservedEnum578 = 622, 
    opennslswitchReservedEnum579 = 623, 
    opennslswitchReservedEnum580 = 624, 
    opennslswitchReservedEnum581 = 625, 
    opennslswitchReservedEnum582 = 626, 
    opennslswitchReservedEnum583 = 627, 
    opennslswitchReservedEnum584 = 628, 
    opennslswitchReservedEnum585 = 629, 
    opennslswitchReservedEnum586 = 630, 
    opennslswitchReservedEnum587 = 631, 
    opennslswitchReservedEnum588 = 632, 
    opennslswitchReservedEnum589 = 633, 
    opennslswitchReservedEnum590 = 634, 
    opennslswitchReservedEnum591 = 635, 
    opennslswitchReservedEnum592 = 636, 
    opennslswitchReservedEnum593 = 637, 
    opennslswitchReservedEnum594 = 638, 
    opennslswitchReservedEnum595 = 639, 
    opennslswitchReservedEnum596 = 640, 
    opennslswitchReservedEnum597 = 641, 
    opennslswitchReservedEnum598 = 642, 
    opennslswitchReservedEnum599 = 643, 
    opennslswitchReservedEnum600 = 644, 
    opennslswitchReservedEnum601 = 645, 
    opennslswitchReservedEnum602 = 646, 
    opennslswitchReservedEnum603 = 647, 
    opennslswitchReservedEnum604 = 648, 
    opennslswitchReservedEnum605 = 649, 
    opennslswitchReservedEnum606 = 650, 
    opennslswitchReservedEnum607 = 651, 
    opennslswitchReservedEnum608 = 652, 
    opennslswitchReservedEnum609 = 653, 
    opennslswitchReservedEnum610 = 654, 
    opennslswitchReservedEnum611 = 655, 
    opennslswitchReservedEnum612 = 656, 
    opennslswitchReservedEnum613 = 657, 
    opennslswitchReservedEnum614 = 658, 
    opennslswitchReservedEnum615 = 659, 
    opennslswitchReservedEnum616 = 660, 
    opennslswitchReservedEnum617 = 661, 
    opennslswitchReservedEnum618 = 662, 
    opennslswitchReservedEnum619 = 663, 
    opennslswitchReservedEnum620 = 664, 
    opennslswitchReservedEnum621 = 665, 
    opennslswitchReservedEnum622 = 666, 
    opennslswitchReservedEnum623 = 667, 
    opennslswitchReservedEnum624 = 668, 
    opennslswitchReservedEnum625 = 669, 
    opennslswitchReservedEnum626 = 670, 
    opennslswitchReservedEnum627 = 671, 
    opennslswitchReservedEnum628 = 672, 
    opennslswitchReservedEnum629 = 673, 
    opennslswitchReservedEnum630 = 674, 
    opennslswitchReservedEnum631 = 675, 
    opennslswitchReservedEnum632 = 676, 
    opennslswitchReservedEnum633 = 677, 
    opennslswitchReservedEnum634 = 678, 
    opennslswitchReservedEnum635 = 679, 
    opennslswitchReservedEnum636 = 680, 
    opennslswitchReservedEnum637 = 681, 
    opennslswitchReservedEnum638 = 682, 
    opennslswitchReservedEnum639 = 683, 
    opennslswitchReservedEnum640 = 684, 
    opennslswitchReservedEnum641 = 685, 
    opennslswitchReservedEnum642 = 686, 
    opennslswitchReservedEnum643 = 687, 
    opennslswitchReservedEnum644 = 688, 
    opennslswitchReservedEnum645 = 689, 
    opennslswitchReservedEnum646 = 690, 
    opennslswitchReservedEnum647 = 691, 
    opennslswitchReservedEnum648 = 692, 
    opennslswitchReservedEnum649 = 693, 
    opennslswitchReservedEnum650 = 694, 
    opennslswitchReservedEnum651 = 695, 
    opennslswitchReservedEnum652 = 696, 
    opennslswitchReservedEnum653 = 697, 
    opennslswitchReservedEnum654 = 698, 
    opennslswitchReservedEnum655 = 699, 
    opennslswitchReservedEnum656 = 700, 
    opennslswitchReservedEnum657 = 701, 
    opennslswitchReservedEnum658 = 702, 
    opennslswitchReservedEnum659 = 703, 
    opennslswitchReservedEnum660 = 704, 
    opennslswitchReservedEnum661 = 705, 
    opennslswitchReservedEnum662 = 706, 
    opennslswitchReservedEnum663 = 707, 
    opennslswitchReservedEnum664 = 708, 
    opennslswitchReservedEnum665 = 709, 
    opennslswitchReservedEnum666 = 710, 
    opennslswitchReservedEnum667 = 711, 
    opennslswitchReservedEnum668 = 712, 
    opennslswitchReservedEnum669 = 713, 
    opennslswitchReservedEnum670 = 714, 
    opennslswitchReservedEnum671 = 715, 
    opennslswitchReservedEnum672 = 716, 
    opennslSwitchBstEnable = 717,       /**< Enable BST tracking. */
    opennslSwitchBstTrackingMode = 718, /**< BST resource usage tracking mode. */
    opennslswitchReservedEnum673 = 719, 
    opennslswitchReservedEnum674 = 720, 
    opennslswitchReservedEnum675 = 721, 
    opennslswitchReservedEnum676 = 722, 
    opennslswitchReservedEnum677 = 723, 
    opennslswitchReservedEnum678 = 724, 
    opennslswitchReservedEnum679 = 725, 
    opennslswitchReservedEnum680 = 726, 
    opennslswitchReservedEnum681 = 727, 
    opennslswitchReservedEnum682 = 728, 
    opennslswitchReservedEnum683 = 729, 
    opennslswitchReservedEnum684 = 730, 
    opennslswitchReservedEnum685 = 731, 
    opennslswitchReservedEnum686 = 732, 
    opennslswitchReservedEnum687 = 733, 
    opennslswitchReservedEnum688 = 734, 
    opennslswitchReservedEnum689 = 735, 
    opennslswitchReservedEnum690 = 736, 
    opennslswitchReservedEnum691 = 737, 
    opennslswitchReservedEnum692 = 738, 
    opennslswitchReservedEnum693 = 739, 
    opennslswitchReservedEnum694 = 740, 
    opennslswitchReservedEnum695 = 741, 
    opennslswitchReservedEnum696 = 742, 
    opennslswitchReservedEnum697 = 743, 
    opennslswitchReservedEnum698 = 744, 
    opennslswitchReservedEnum699 = 745, 
    opennslswitchReservedEnum700 = 746, 
    opennslswitchReservedEnum701 = 747, 
    opennslswitchReservedEnum702 = 748, 
    opennslswitchReservedEnum703 = 749, 
    opennslswitchReservedEnum704 = 750, 
    opennslswitchReservedEnum705 = 751, 
    opennslswitchReservedEnum706 = 752, 
    opennslswitchReservedEnum707 = 753, 
    opennslswitchReservedEnum708 = 754, 
    opennslswitchReservedEnum709 = 755, 
    opennslswitchReservedEnum710 = 756, 
    opennslswitchReservedEnum711 = 757, 
    opennslswitchReservedEnum712 = 758, 
    opennslswitchReservedEnum713 = 759, 
    opennslswitchReservedEnum714 = 760, 
    opennslswitchReservedEnum715 = 761, 
    opennslswitchReservedEnum716 = 762, 
    opennslswitchReservedEnum717 = 763, 
    opennslswitchReservedEnum718 = 764, 
    opennslswitchReservedEnum719 = 765, 
    opennslswitchReservedEnum720 = 766, 
    opennslswitchReservedEnum721 = 767, 
    opennslswitchReservedEnum722 = 768, 
    opennslswitchReservedEnum723 = 769, 
    opennslswitchReservedEnum724 = 770, 
    opennslswitchReservedEnum725 = 771, 
    opennslswitchReservedEnum726 = 772, 
    opennslswitchReservedEnum727 = 773, 
    opennslswitchReservedEnum728 = 774, 
    opennslswitchReservedEnum729 = 775, 
    opennslswitchReservedEnum730 = 776, 
    opennslswitchReservedEnum731 = 777, 
    opennslswitchReservedEnum732 = 778, 
    opennslswitchReservedEnum733 = 779, 
    opennslswitchReservedEnum734 = 780, 
    opennslswitchReservedEnum735 = 781, 
    opennslSwitchEcmpMacroFlowHashEnable = 782, /**< Enable ECMP macro-flow hashing. */
    opennslswitchReservedEnum736 = 783, 
    opennslswitchReservedEnum737 = 784, 
    opennslswitchReservedEnum738 = 785, 
    opennslswitchReservedEnum739 = 786, 
    opennslswitchReservedEnum740 = 787, 
    opennslswitchReservedEnum741 = 788, 
    opennslswitchReservedEnum742 = 789, 
    opennslswitchReservedEnum743 = 790, 
    opennslswitchReservedEnum744 = 791, 
    opennslswitchReservedEnum745 = 792, 
    opennslswitchReservedEnum746 = 793, 
    opennslswitchReservedEnum747 = 794, 
    opennslswitchReservedEnum748 = 795, 
    opennslswitchReservedEnum749 = 796, 
    opennslswitchReservedEnum750 = 797, 
    opennslswitchReservedEnum751 = 798, 
    opennslswitchReservedEnum752 = 799, 
    opennslswitchReservedEnum753 = 800, 
    opennslswitchReservedEnum754 = 801, 
    opennslswitchReservedEnum755 = 802, 
    opennslswitchReservedEnum756 = 803, 
    opennslswitchReservedEnum757 = 804, 
    opennslswitchReservedEnum758 = 805, 
    opennslswitchReservedEnum759 = 806, 
    opennslswitchReservedEnum760 = 807, 
    opennslswitchReservedEnum761 = 808, 
    opennslswitchReservedEnum762 = 809, 
    opennslswitchReservedEnum763 = 810, 
    opennslswitchReservedEnum764 = 811, 
    opennslswitchReservedEnum765 = 812, 
    opennslswitchReservedEnum766 = 813, 
    opennslswitchReservedEnum767 = 814, 
    opennslswitchReservedEnum768 = 815, 
    opennslswitchReservedEnum769 = 816, 
    opennslswitchReservedEnum770 = 817, 
    opennslswitchReservedEnum771 = 818, 
    opennslswitchReservedEnum772 = 819, 
    opennslswitchReservedEnum773 = 820, 
    opennslswitchReservedEnum774 = 821, 
    opennslswitchReservedEnum775 = 822, 
    opennslswitchReservedEnum776 = 823, 
    opennslswitchReservedEnum777 = 824, 
    opennslswitchReservedEnum778 = 825, 
    opennslswitchReservedEnum779 = 826, 
    opennslswitchReservedEnum780 = 827, 
    opennslswitchReservedEnum781 = 828, 
    opennslswitchReservedEnum782 = 829, 
    opennslswitchReservedEnum783 = 830, 
    opennslswitchReservedEnum784 = 831, 
    opennslswitchReservedEnum785 = 832, 
    opennslswitchReservedEnum786 = 833, 
    opennslswitchReservedEnum787 = 834, 
    opennslswitchReservedEnum788 = 835, 
    opennslswitchReservedEnum789 = 836, 
    opennslswitchReservedEnum790 = 837, 
    opennslswitchReservedEnum791 = 838, 
    opennslswitchReservedEnum792 = 839, 
    opennslswitchReservedEnum793 = 840, 
    opennslswitchReservedEnum794 = 841, 
    opennslswitchReservedEnum795 = 842, 
    opennslswitchReservedEnum796 = 843, 
    opennslswitchReservedEnum797 = 844, 
    opennslswitchReservedEnum798 = 845, 
    opennslswitchReservedEnum799 = 846, 
    opennslswitchReservedEnum800 = 847, 
    opennslswitchReservedEnum801 = 848, 
    opennslswitchReservedEnum802 = 849, 
    opennslswitchReservedEnum803 = 850, 
    opennslswitchReservedEnum804 = 851, 
    opennslswitchReservedEnum805 = 852, 
    opennslswitchReservedEnum806 = 853, 
    opennslswitchReservedEnum807 = 854, 
    opennslswitchReservedEnum808 = 855, 
    opennslswitchReservedEnum809 = 856, 
    opennslswitchReservedEnum810 = 857, 
    opennslswitchReservedEnum811 = 858, 
    opennslswitchReservedEnum812 = 859, 
    opennslswitchReservedEnum813 = 860, 
    opennslswitchReservedEnum814 = 861, 
    opennslswitchReservedEnum815 = 862, 
    opennslswitchReservedEnum816 = 863, 
    opennslswitchReservedEnum817 = 864, 
    opennslswitchReservedEnum818 = 865, 
    opennslswitchReservedEnum819 = 866, 
    opennslswitchReservedEnum820 = 867, 
    opennslswitchReservedEnum821 = 868, 
    opennslswitchReservedEnum822 = 869, 
    opennslswitchReservedEnum823 = 870, 
    opennslswitchReservedEnum824 = 871, 
    opennslswitchReservedEnum825 = 872, 
    opennslswitchReservedEnum826 = 873, 
    opennslswitchReservedEnum827 = 874, 
    opennslswitchReservedEnum828 = 875, 
    opennslswitchReservedEnum829 = 876, 
    opennslswitchReservedEnum830 = 877, 
    opennslswitchReservedEnum831 = 878, 
    opennslswitchReservedEnum832 = 879, 
    opennslswitchReservedEnum833 = 880, 
    opennslswitchReservedEnum834 = 881, 
    opennslswitchReservedEnum835 = 882, 
    opennslswitchReservedEnum836 = 883, 
    opennslswitchReservedEnum837 = 884, 
    opennslswitchReservedEnum838 = 885, 
    opennslswitchReservedEnum839 = 886, 
    opennslswitchReservedEnum840 = 887, 
    opennslswitchReservedEnum841 = 888, 
    opennslswitchReservedEnum842 = 889, 
    opennslswitchReservedEnum843 = 890, 
    opennslswitchReservedEnum844 = 891, 
    opennslswitchReservedEnum845 = 892, 
    opennslswitchReservedEnum846 = 893, 
    opennslswitchReservedEnum847 = 894, 
    opennslswitchReservedEnum848 = 895, 
    opennslswitchReservedEnum849 = 896, 
    opennslswitchReservedEnum850 = 897, 
    opennslswitchReservedEnum851 = 898, 
    opennslswitchReservedEnum852 = 899, 
    opennslswitchReservedEnum853 = 900, 
    opennslswitchReservedEnum854 = 901, 
    opennslswitchReservedEnum855 = 902, 
    opennslswitchReservedEnum856 = 903, 
    opennslswitchReservedEnum857 = 904, 
    opennslswitchReservedEnum858 = 905, 
    opennslswitchReservedEnum859 = 906, 
    opennslswitchReservedEnum860 = 907, 
    opennslswitchReservedEnum861 = 908, 
    opennslswitchReservedEnum862 = 909, 
    opennslswitchReservedEnum863 = 910, 
    opennslswitchReservedEnum864 = 911, 
    opennslswitchReservedEnum865 = 912, 
    opennslswitchReservedEnum866 = 913, 
    opennslswitchReservedEnum867 = 914, 
    opennslswitchReservedEnum868 = 915, 
    opennslswitchReservedEnum869 = 916, 
    opennslswitchReservedEnum870 = 917, 
    opennslswitchReservedEnum871 = 918, 
    opennslswitchReservedEnum872 = 919, 
    opennslswitchReservedEnum873 = 920, 
    opennslswitchReservedEnum874 = 921, 
    opennslswitchReservedEnum875 = 922, 
    opennslswitchReservedEnum876 = 923, 
    opennslswitchReservedEnum877 = 924, 
    opennslswitchReservedEnum878 = 925, 
    opennslswitchReservedEnum879 = 926, 
    opennslswitchReservedEnum880 = 927, 
    opennslswitchReservedEnum881 = 928, 
    opennslswitchReservedEnum882 = 929, 
    opennslswitchReservedEnum883 = 930, 
    opennslswitchReservedEnum884 = 931, 
    opennslswitchReservedEnum885 = 932, 
    opennslswitchReservedEnum886 = 933, 
    opennslswitchReservedEnum887 = 934, 
    opennslswitchReservedEnum888 = 935, 
    opennslswitchReservedEnum889 = 936, 
    opennslswitchReservedEnum890 = 937, 
    opennslswitchReservedEnum891 = 938, 
    opennslswitchReservedEnum892 = 939, 
    opennslswitchReservedEnum893 = 940, 
    opennslswitchReservedEnum894 = 941, 
    opennslswitchReservedEnum895 = 942, 
    opennslswitchReservedEnum896 = 943, 
    opennslswitchReservedEnum897 = 944, 
    opennslswitchReservedEnum898 = 945, 
    opennslswitchReservedEnum899 = 946, 
    opennslswitchReservedEnum900 = 947, 
    opennslswitchReservedEnum901 = 948, 
    opennslswitchReservedEnum902 = 949, 
    opennslswitchReservedEnum903 = 950, 
    opennslswitchReservedEnum904 = 951, 
    opennslswitchReservedEnum905 = 952, 
    opennslswitchReservedEnum906 = 953, 
    opennslswitchReservedEnum907 = 954, 
    opennslswitchReservedEnum908 = 955, 
    opennslswitchReservedEnum909 = 956, 
    opennslswitchReservedEnum910 = 957, 
    opennslswitchReservedEnum911 = 958, 
    opennslswitchReservedEnum912 = 959, 
    opennslswitchReservedEnum913 = 960 
} opennsl_switch_control_t;

#define OPENNSL_SWITCH_CONTROL_STR \
    "opennslswitchReservedEnum1", \
    "opennslswitchReservedEnum2", \
    "opennslswitchReservedEnum3", \
    "opennslswitchReservedEnum4", \
    "opennslswitchReservedEnum5", \
    "opennslswitchReservedEnum6", \
    "opennslswitchReservedEnum7", \
    "opennslswitchReservedEnum8", \
    "opennslswitchReservedEnum9", \
    "opennslswitchReservedEnum10", \
    "opennslswitchReservedEnum11", \
    "opennslswitchReservedEnum12", \
    "opennslswitchReservedEnum13", \
    "opennslswitchReservedEnum14", \
    "opennslswitchReservedEnum15", \
    "opennslswitchReservedEnum16", \
    "opennslswitchReservedEnum17", \
    "opennslswitchReservedEnum18", \
    "opennslswitchReservedEnum19", \
    "opennslswitchReservedEnum20", \
    "opennslswitchReservedEnum21", \
    "opennslswitchReservedEnum22", \
    "opennslswitchReservedEnum23", \
    "opennslswitchReservedEnum24", \
    "opennslswitchReservedEnum25", \
    "opennslswitchReservedEnum26", \
    "UnknownL3DestToCpu", \
    "opennslswitchReservedEnum27", \
    "opennslswitchReservedEnum28", \
    "opennslswitchReservedEnum29", \
    "opennslswitchReservedEnum30", \
    "opennslswitchReservedEnum31", \
    "opennslswitchReservedEnum32", \
    "opennslswitchReservedEnum33", \
    "opennslswitchReservedEnum34", \
    "opennslswitchReservedEnum35", \
    "opennslswitchReservedEnum36", \
    "opennslswitchReservedEnum37", \
    "opennslswitchReservedEnum38", \
    "opennslswitchReservedEnum39", \
    "V6L3DstMissToCpu", \
    "opennslswitchReservedEnum40", \
    "opennslswitchReservedEnum41", \
    "V4L3DstMissToCpu", \
    "opennslswitchReservedEnum42", \
    "opennslswitchReservedEnum43", \
    "opennslswitchReservedEnum44", \
    "opennslswitchReservedEnum45", \
    "L3SlowpathToCpu", \
    "opennslswitchReservedEnum46", \
    "opennslswitchReservedEnum47", \
    "opennslswitchReservedEnum48", \
    "opennslswitchReservedEnum49", \
    "opennslswitchReservedEnum50", \
    "opennslswitchReservedEnum51", \
    "opennslswitchReservedEnum52", \
    "opennslswitchReservedEnum53", \
    "opennslswitchReservedEnum54", \
    "opennslswitchReservedEnum55", \
    "opennslswitchReservedEnum56", \
    "opennslswitchReservedEnum57", \
    "opennslswitchReservedEnum58", \
    "opennslswitchReservedEnum59", \
    "opennslswitchReservedEnum60", \
    "opennslswitchReservedEnum61", \
    "opennslswitchReservedEnum62", \
    "opennslswitchReservedEnum63", \
    "opennslswitchReservedEnum64", \
    "opennslswitchReservedEnum65", \
    "opennslswitchReservedEnum66", \
    "opennslswitchReservedEnum67", \
    "opennslswitchReservedEnum68", \
    "opennslswitchReservedEnum69", \
    "opennslswitchReservedEnum70", \
    "opennslswitchReservedEnum71", \
    "opennslswitchReservedEnum72", \
    "opennslswitchReservedEnum73", \
    "opennslswitchReservedEnum74", \
    "opennslswitchReservedEnum75", \
    "opennslswitchReservedEnum76", \
    "opennslswitchReservedEnum77", \
    "opennslswitchReservedEnum78", \
    "opennslswitchReservedEnum79", \
    "opennslswitchReservedEnum80", \
    "ArpReplyToCpu", \
    "opennslswitchReservedEnum81", \
    "ArpRequestToCpu", \
    "opennslswitchReservedEnum82", \
    "opennslswitchReservedEnum83", \
    "NdPktToCpu", \
    "opennslswitchReservedEnum84", \
    "opennslswitchReservedEnum85", \
    "IgmpPktToCpu", \
    "opennslswitchReservedEnum86", \
    "DhcpPktToCpu", \
    "DhcpPktDrop", \
    "opennslswitchReservedEnum87", \
    "opennslswitchReservedEnum88", \
    "V4ResvdMcPktToCpu", \
    "opennslswitchReservedEnum89", \
    "opennslswitchReservedEnum90", \
    "opennslswitchReservedEnum91", \
    "opennslswitchReservedEnum92", \
    "opennslswitchReservedEnum93", \
    "opennslswitchReservedEnum94", \
    "opennslswitchReservedEnum95", \
    "opennslswitchReservedEnum96", \
    "opennslswitchReservedEnum97", \
    "opennslswitchReservedEnum98", \
    "opennslswitchReservedEnum99", \
    "opennslswitchReservedEnum100", \
    "opennslswitchReservedEnum101", \
    "opennslswitchReservedEnum102", \
    "opennslswitchReservedEnum103", \
    "opennslswitchReservedEnum104", \
    "opennslswitchReservedEnum105", \
    "opennslswitchReservedEnum106", \
    "opennslswitchReservedEnum107", \
    "opennslswitchReservedEnum108", \
    "opennslswitchReservedEnum109", \
    "opennslswitchReservedEnum110", \
    "opennslswitchReservedEnum111", \
    "opennslswitchReservedEnum112", \
    "opennslswitchReservedEnum113", \
    "opennslswitchReservedEnum114", \
    "opennslswitchReservedEnum115", \
    "opennslswitchReservedEnum116", \
    "opennslswitchReservedEnum117", \
    "opennslswitchReservedEnum118", \
    "opennslswitchReservedEnum119", \
    "opennslswitchReservedEnum120", \
    "opennslswitchReservedEnum121", \
    "opennslswitchReservedEnum122", \
    "opennslswitchReservedEnum123", \
    "opennslswitchReservedEnum124", \
    "opennslswitchReservedEnum125", \
    "HashControl", \
    "opennslswitchReservedEnum126", \
    "opennslswitchReservedEnum127", \
    "opennslswitchReservedEnum128", \
    "opennslswitchReservedEnum129", \
    "opennslswitchReservedEnum130", \
    "opennslswitchReservedEnum131", \
    "opennslswitchReservedEnum132", \
    "opennslswitchReservedEnum133", \
    "opennslswitchReservedEnum134", \
    "opennslswitchReservedEnum135", \
    "HashSeed0", \
    "HashSeed1", \
    "HashField0PreProcessEnable", \
    "HashField1PreProcessEnable", \
    "HashField0Config", \
    "HashField0Config1", \
    "HashField1Config", \
    "HashField1Config1", \
    "opennslswitchReservedEnum136", \
    "HashSelectControl", \
    "HashIP4Field0", \
    "HashIP4Field1", \
    "HashIP4TcpUdpField0", \
    "HashIP4TcpUdpField1", \
    "HashIP4TcpUdpPortsEqualField0", \
    "HashIP4TcpUdpPortsEqualField1", \
    "HashIP6Field0", \
    "HashIP6Field1", \
    "HashIP6TcpUdpField0", \
    "HashIP6TcpUdpField1", \
    "HashIP6TcpUdpPortsEqualField0", \
    "HashIP6TcpUdpPortsEqualField1", \
    "opennslswitchReservedEnum137", \
    "opennslswitchReservedEnum138", \
    "opennslswitchReservedEnum139", \
    "opennslswitchReservedEnum140", \
    "opennslswitchReservedEnum141", \
    "opennslswitchReservedEnum142", \
    "opennslswitchReservedEnum143", \
    "opennslswitchReservedEnum144", \
    "opennslswitchReservedEnum145", \
    "opennslswitchReservedEnum146", \
    "opennslswitchReservedEnum147", \
    "opennslswitchReservedEnum148", \
    "opennslswitchReservedEnum149", \
    "opennslswitchReservedEnum150", \
    "opennslswitchReservedEnum151", \
    "opennslswitchReservedEnum152", \
    "opennslswitchReservedEnum153", \
    "opennslswitchReservedEnum154", \
    "opennslswitchReservedEnum155", \
    "opennslswitchReservedEnum156", \
    "opennslswitchReservedEnum157", \
    "opennslswitchReservedEnum158", \
    "opennslswitchReservedEnum159", \
    "opennslswitchReservedEnum160", \
    "opennslswitchReservedEnum161", \
    "opennslswitchReservedEnum162", \
    "opennslswitchReservedEnum163", \
    "opennslswitchReservedEnum164", \
    "opennslswitchReservedEnum165", \
    "opennslswitchReservedEnum166", \
    "opennslswitchReservedEnum167", \
    "opennslswitchReservedEnum168", \
    "opennslswitchReservedEnum169", \
    "opennslswitchReservedEnum170", \
    "opennslswitchReservedEnum171", \
    "opennslswitchReservedEnum172", \
    "opennslswitchReservedEnum173", \
    "opennslswitchReservedEnum174", \
    "opennslswitchReservedEnum175", \
    "opennslswitchReservedEnum176", \
    "opennslswitchReservedEnum177", \
    "ECMPHashSet0Offset", \
    "ECMPHashSet1Offset", \
    "opennslswitchReservedEnum178", \
    "opennslswitchReservedEnum179", \
    "opennslswitchReservedEnum180", \
    "opennslswitchReservedEnum181", \
    "opennslswitchReservedEnum182", \
    "opennslswitchReservedEnum183", \
    "opennslswitchReservedEnum184", \
    "opennslswitchReservedEnum185", \
    "opennslswitchReservedEnum186", \
    "opennslswitchReservedEnum187", \
    "opennslswitchReservedEnum188", \
    "opennslswitchReservedEnum189", \
    "opennslswitchReservedEnum190", \
    "opennslswitchReservedEnum191", \
    "opennslswitchReservedEnum192", \
    "opennslswitchReservedEnum193", \
    "opennslswitchReservedEnum194", \
    "opennslswitchReservedEnum195", \
    "L3EgressMode", \
    "opennslswitchReservedEnum196", \
    "L3IngressMode", \
    "opennslswitchReservedEnum197", \
    "opennslswitchReservedEnum198", \
    "opennslswitchReservedEnum199", \
    "opennslswitchReservedEnum200", \
    "opennslswitchReservedEnum201", \
    "WarmBoot", \
    "StableSelect", \
    "StableSize", \
    "StableUsed", \
    "StableConsistent", \
    "ControlSync", \
    "ControlAutoSync", \
    "opennslswitchReservedEnum202", \
    "opennslswitchReservedEnum203", \
    "opennslswitchReservedEnum204", \
    "opennslswitchReservedEnum205", \
    "opennslswitchReservedEnum206", \
    "L3UcastTtl1ToCpu", \
    "opennslswitchReservedEnum207", \
    "opennslswitchReservedEnum208", \
    "opennslswitchReservedEnum209", \
    "opennslswitchReservedEnum210", \
    "opennslswitchReservedEnum211", \
    "opennslswitchReservedEnum212", \
    "opennslswitchReservedEnum213", \
    "opennslswitchReservedEnum214", \
    "opennslswitchReservedEnum215", \
    "opennslswitchReservedEnum216", \
    "opennslswitchReservedEnum217", \
    "opennslswitchReservedEnum218", \
    "opennslswitchReservedEnum219", \
    "opennslswitchReservedEnum220", \
    "opennslswitchReservedEnum221", \
    "opennslswitchReservedEnum222", \
    "opennslswitchReservedEnum223", \
    "opennslswitchReservedEnum224", \
    "opennslswitchReservedEnum225", \
    "opennslswitchReservedEnum226", \
    "opennslswitchReservedEnum227", \
    "opennslswitchReservedEnum228", \
    "opennslswitchReservedEnum229", \
    "opennslswitchReservedEnum230", \
    "opennslswitchReservedEnum231", \
    "opennslswitchReservedEnum232", \
    "opennslswitchReservedEnum233", \
    "opennslswitchReservedEnum234", \
    "opennslswitchReservedEnum235", \
    "opennslswitchReservedEnum236", \
    "opennslswitchReservedEnum237", \
    "opennslswitchReservedEnum238", \
    "opennslswitchReservedEnum239", \
    "opennslswitchReservedEnum240", \
    "opennslswitchReservedEnum241", \
    "opennslswitchReservedEnum242", \
    "opennslswitchReservedEnum243", \
    "opennslswitchReservedEnum244", \
    "opennslswitchReservedEnum245", \
    "opennslswitchReservedEnum246", \
    "opennslswitchReservedEnum247", \
    "opennslswitchReservedEnum248", \
    "opennslswitchReservedEnum249", \
    "opennslswitchReservedEnum250", \
    "opennslswitchReservedEnum251", \
    "opennslswitchReservedEnum252", \
    "opennslswitchReservedEnum253", \
    "opennslswitchReservedEnum254", \
    "opennslswitchReservedEnum255", \
    "opennslswitchReservedEnum256", \
    "opennslswitchReservedEnum257", \
    "opennslswitchReservedEnum258", \
    "opennslswitchReservedEnum259", \
    "opennslswitchReservedEnum260", \
    "opennslswitchReservedEnum261", \
    "opennslswitchReservedEnum262", \
    "opennslswitchReservedEnum263", \
    "opennslswitchReservedEnum264", \
    "opennslswitchReservedEnum265", \
    "opennslswitchReservedEnum266", \
    "opennslswitchReservedEnum267", \
    "opennslswitchReservedEnum268", \
    "opennslswitchReservedEnum269", \
    "opennslswitchReservedEnum270", \
    "opennslswitchReservedEnum271", \
    "opennslswitchReservedEnum272", \
    "opennslswitchReservedEnum273", \
    "opennslswitchReservedEnum274", \
    "opennslswitchReservedEnum275", \
    "opennslswitchReservedEnum276", \
    "opennslswitchReservedEnum277", \
    "opennslswitchReservedEnum278", \
    "opennslswitchReservedEnum279", \
    "opennslswitchReservedEnum280", \
    "opennslswitchReservedEnum281", \
    "opennslswitchReservedEnum282", \
    "opennslswitchReservedEnum283", \
    "opennslswitchReservedEnum284", \
    "opennslswitchReservedEnum285", \
    "opennslswitchReservedEnum286", \
    "opennslswitchReservedEnum287", \
    "opennslswitchReservedEnum288", \
    "opennslswitchReservedEnum289", \
    "opennslswitchReservedEnum290", \
    "opennslswitchReservedEnum291", \
    "opennslswitchReservedEnum292", \
    "opennslswitchReservedEnum293", \
    "opennslswitchReservedEnum294", \
    "opennslswitchReservedEnum295", \
    "opennslswitchReservedEnum296", \
    "opennslswitchReservedEnum297", \
    "opennslswitchReservedEnum298", \
    "opennslswitchReservedEnum299", \
    "opennslswitchReservedEnum300", \
    "opennslswitchReservedEnum301", \
    "opennslswitchReservedEnum302", \
    "opennslswitchReservedEnum303", \
    "opennslswitchReservedEnum304", \
    "opennslswitchReservedEnum305", \
    "opennslswitchReservedEnum306", \
    "opennslswitchReservedEnum307", \
    "opennslswitchReservedEnum308", \
    "opennslswitchReservedEnum309", \
    "opennslswitchReservedEnum310", \
    "opennslswitchReservedEnum311", \
    "opennslswitchReservedEnum312", \
    "opennslswitchReservedEnum313", \
    "opennslswitchReservedEnum314", \
    "opennslswitchReservedEnum315", \
    "opennslswitchReservedEnum316", \
    "opennslswitchReservedEnum317", \
    "opennslswitchReservedEnum318", \
    "opennslswitchReservedEnum319", \
    "opennslswitchReservedEnum320", \
    "opennslswitchReservedEnum321", \
    "opennslswitchReservedEnum322", \
    "opennslswitchReservedEnum323", \
    "opennslswitchReservedEnum324", \
    "opennslswitchReservedEnum325", \
    "opennslswitchReservedEnum326", \
    "opennslswitchReservedEnum327", \
    "opennslswitchReservedEnum328", \
    "opennslswitchReservedEnum329", \
    "opennslswitchReservedEnum330", \
    "opennslswitchReservedEnum331", \
    "opennslswitchReservedEnum332", \
    "opennslswitchReservedEnum333", \
    "opennslswitchReservedEnum334", \
    "opennslswitchReservedEnum335", \
    "opennslswitchReservedEnum336", \
    "opennslswitchReservedEnum337", \
    "opennslswitchReservedEnum338", \
    "opennslswitchReservedEnum339", \
    "opennslswitchReservedEnum340", \
    "opennslswitchReservedEnum341", \
    "opennslswitchReservedEnum342", \
    "opennslswitchReservedEnum343", \
    "opennslswitchReservedEnum344", \
    "opennslswitchReservedEnum345", \
    "opennslswitchReservedEnum346", \
    "opennslswitchReservedEnum347", \
    "opennslswitchReservedEnum348", \
    "opennslswitchReservedEnum349", \
    "opennslswitchReservedEnum350", \
    "opennslswitchReservedEnum351", \
    "opennslswitchReservedEnum352", \
    "opennslswitchReservedEnum353", \
    "opennslswitchReservedEnum354", \
    "opennslswitchReservedEnum355", \
    "opennslswitchReservedEnum356", \
    "opennslswitchReservedEnum357", \
    "opennslswitchReservedEnum358", \
    "opennslswitchReservedEnum359", \
    "opennslswitchReservedEnum360", \
    "opennslswitchReservedEnum361", \
    "opennslswitchReservedEnum362", \
    "opennslswitchReservedEnum363", \
    "opennslswitchReservedEnum364", \
    "opennslswitchReservedEnum365", \
    "opennslswitchReservedEnum366", \
    "opennslswitchReservedEnum367", \
    "opennslswitchReservedEnum368", \
    "opennslswitchReservedEnum369", \
    "opennslswitchReservedEnum370", \
    "opennslswitchReservedEnum371", \
    "opennslswitchReservedEnum372", \
    "opennslswitchReservedEnum373", \
    "opennslswitchReservedEnum374", \
    "opennslswitchReservedEnum375", \
    "opennslswitchReservedEnum376", \
    "opennslswitchReservedEnum377", \
    "opennslswitchReservedEnum378", \
    "opennslswitchReservedEnum379", \
    "opennslswitchReservedEnum380", \
    "opennslswitchReservedEnum381", \
    "opennslswitchReservedEnum382", \
    "opennslswitchReservedEnum383", \
    "opennslswitchReservedEnum384", \
    "opennslswitchReservedEnum385", \
    "opennslswitchReservedEnum386", \
    "opennslswitchReservedEnum387", \
    "opennslswitchReservedEnum388", \
    "opennslswitchReservedEnum389", \
    "opennslswitchReservedEnum390", \
    "opennslswitchReservedEnum391", \
    "opennslswitchReservedEnum392", \
    "opennslswitchReservedEnum393", \
    "opennslswitchReservedEnum394", \
    "opennslswitchReservedEnum395", \
    "opennslswitchReservedEnum396", \
    "opennslswitchReservedEnum397", \
    "opennslswitchReservedEnum398", \
    "opennslswitchReservedEnum399", \
    "opennslswitchReservedEnum400", \
    "opennslswitchReservedEnum401", \
    "opennslswitchReservedEnum402", \
    "opennslswitchReservedEnum403", \
    "opennslswitchReservedEnum404", \
    "opennslswitchReservedEnum405", \
    "opennslswitchReservedEnum406", \
    "opennslswitchReservedEnum407", \
    "opennslswitchReservedEnum408", \
    "opennslswitchReservedEnum409", \
    "opennslswitchReservedEnum410", \
    "opennslswitchReservedEnum411", \
    "opennslswitchReservedEnum412", \
    "opennslswitchReservedEnum413", \
    "opennslswitchReservedEnum414", \
    "opennslswitchReservedEnum415", \
    "opennslswitchReservedEnum416", \
    "opennslswitchReservedEnum417", \
    "opennslswitchReservedEnum418", \
    "opennslswitchReservedEnum419", \
    "opennslswitchReservedEnum420", \
    "opennslswitchReservedEnum421", \
    "opennslswitchReservedEnum422", \
    "opennslswitchReservedEnum423", \
    "opennslswitchReservedEnum424", \
    "opennslswitchReservedEnum425", \
    "opennslswitchReservedEnum426", \
    "opennslswitchReservedEnum427", \
    "opennslswitchReservedEnum428", \
    "opennslswitchReservedEnum429", \
    "opennslswitchReservedEnum430", \
    "opennslswitchReservedEnum431", \
    "opennslswitchReservedEnum432", \
    "opennslswitchReservedEnum433", \
    "opennslswitchReservedEnum434", \
    "opennslswitchReservedEnum435", \
    "opennslswitchReservedEnum436", \
    "opennslswitchReservedEnum437", \
    "opennslswitchReservedEnum438", \
    "opennslswitchReservedEnum439", \
    "opennslswitchReservedEnum440", \
    "opennslswitchReservedEnum441", \
    "opennslswitchReservedEnum442", \
    "opennslswitchReservedEnum443", \
    "opennslswitchReservedEnum444", \
    "opennslswitchReservedEnum445", \
    "opennslswitchReservedEnum446", \
    "opennslswitchReservedEnum447", \
    "opennslswitchReservedEnum448", \
    "opennslswitchReservedEnum449", \
    "opennslswitchReservedEnum450", \
    "opennslswitchReservedEnum451", \
    "opennslswitchReservedEnum452", \
    "opennslswitchReservedEnum453", \
    "opennslswitchReservedEnum454", \
    "opennslswitchReservedEnum455", \
    "opennslswitchReservedEnum456", \
    "opennslswitchReservedEnum457", \
    "opennslswitchReservedEnum458", \
    "opennslswitchReservedEnum459", \
    "opennslswitchReservedEnum460", \
    "opennslswitchReservedEnum461", \
    "opennslswitchReservedEnum462", \
    "opennslswitchReservedEnum463", \
    "opennslswitchReservedEnum464", \
    "opennslswitchReservedEnum465", \
    "opennslswitchReservedEnum466", \
    "opennslswitchReservedEnum467", \
    "opennslswitchReservedEnum468", \
    "opennslswitchReservedEnum469", \
    "opennslswitchReservedEnum470", \
    "opennslswitchReservedEnum471", \
    "opennslswitchReservedEnum472", \
    "opennslswitchReservedEnum473", \
    "opennslswitchReservedEnum474", \
    "opennslswitchReservedEnum475", \
    "opennslswitchReservedEnum476", \
    "opennslswitchReservedEnum477", \
    "opennslswitchReservedEnum478", \
    "opennslswitchReservedEnum479", \
    "opennslswitchReservedEnum480", \
    "opennslswitchReservedEnum481", \
    "opennslswitchReservedEnum482", \
    "opennslswitchReservedEnum483", \
    "opennslswitchReservedEnum484", \
    "opennslswitchReservedEnum485", \
    "opennslswitchReservedEnum486", \
    "opennslswitchReservedEnum487", \
    "opennslswitchReservedEnum488", \
    "opennslswitchReservedEnum489", \
    "opennslswitchReservedEnum490", \
    "opennslswitchReservedEnum491", \
    "opennslswitchReservedEnum492", \
    "opennslswitchReservedEnum493", \
    "opennslswitchReservedEnum494", \
    "opennslswitchReservedEnum495", \
    "opennslswitchReservedEnum496", \
    "opennslswitchReservedEnum497", \
    "opennslswitchReservedEnum498", \
    "opennslswitchReservedEnum499", \
    "opennslswitchReservedEnum500", \
    "opennslswitchReservedEnum501", \
    "opennslswitchReservedEnum502", \
    "opennslswitchReservedEnum503", \
    "opennslswitchReservedEnum504", \
    "opennslswitchReservedEnum505", \
    "opennslswitchReservedEnum506", \
    "opennslswitchReservedEnum507", \
    "opennslswitchReservedEnum508", \
    "opennslswitchReservedEnum509", \
    "opennslswitchReservedEnum510", \
    "opennslswitchReservedEnum511", \
    "opennslswitchReservedEnum512", \
    "opennslswitchReservedEnum513", \
    "opennslswitchReservedEnum514", \
    "opennslswitchReservedEnum515", \
    "opennslswitchReservedEnum516", \
    "opennslswitchReservedEnum517", \
    "opennslswitchReservedEnum518", \
    "opennslswitchReservedEnum519", \
    "opennslswitchReservedEnum520", \
    "opennslswitchReservedEnum521", \
    "opennslswitchReservedEnum522", \
    "opennslswitchReservedEnum523", \
    "opennslswitchReservedEnum524", \
    "opennslswitchReservedEnum525", \
    "opennslswitchReservedEnum526", \
    "opennslswitchReservedEnum527", \
    "opennslswitchReservedEnum528", \
    "opennslswitchReservedEnum529", \
    "opennslswitchReservedEnum530", \
    "opennslswitchReservedEnum531", \
    "opennslswitchReservedEnum532", \
    "opennslswitchReservedEnum533", \
    "opennslswitchReservedEnum534", \
    "opennslswitchReservedEnum535", \
    "opennslswitchReservedEnum536", \
    "opennslswitchReservedEnum537", \
    "opennslswitchReservedEnum538", \
    "opennslswitchReservedEnum539", \
    "opennslswitchReservedEnum540", \
    "opennslswitchReservedEnum541", \
    "opennslswitchReservedEnum542", \
    "opennslswitchReservedEnum543", \
    "opennslswitchReservedEnum544", \
    "opennslswitchReservedEnum545", \
    "opennslswitchReservedEnum546", \
    "opennslswitchReservedEnum547", \
    "opennslswitchReservedEnum548", \
    "opennslswitchReservedEnum549", \
    "opennslswitchReservedEnum550", \
    "opennslswitchReservedEnum551", \
    "opennslswitchReservedEnum552", \
    "opennslswitchReservedEnum553", \
    "opennslswitchReservedEnum554", \
    "opennslswitchReservedEnum555", \
    "opennslswitchReservedEnum556", \
    "opennslswitchReservedEnum557", \
    "opennslswitchReservedEnum558", \
    "opennslswitchReservedEnum559", \
    "opennslswitchReservedEnum560", \
    "opennslswitchReservedEnum561", \
    "opennslswitchReservedEnum562", \
    "opennslswitchReservedEnum563", \
    "opennslswitchReservedEnum564", \
    "opennslswitchReservedEnum565", \
    "opennslswitchReservedEnum566", \
    "opennslswitchReservedEnum567", \
    "opennslswitchReservedEnum568", \
    "opennslswitchReservedEnum569", \
    "opennslswitchReservedEnum570", \
    "opennslswitchReservedEnum571", \
    "opennslswitchReservedEnum572", \
    "opennslswitchReservedEnum573", \
    "opennslswitchReservedEnum574", \
    "opennslswitchReservedEnum575", \
    "opennslswitchReservedEnum576", \
    "opennslswitchReservedEnum577", \
    "opennslswitchReservedEnum578", \
    "opennslswitchReservedEnum579", \
    "opennslswitchReservedEnum580", \
    "opennslswitchReservedEnum581", \
    "opennslswitchReservedEnum582", \
    "opennslswitchReservedEnum583", \
    "opennslswitchReservedEnum584", \
    "opennslswitchReservedEnum585", \
    "opennslswitchReservedEnum586", \
    "opennslswitchReservedEnum587", \
    "opennslswitchReservedEnum588", \
    "opennslswitchReservedEnum589", \
    "opennslswitchReservedEnum590", \
    "opennslswitchReservedEnum591", \
    "opennslswitchReservedEnum592", \
    "opennslswitchReservedEnum593", \
    "opennslswitchReservedEnum594", \
    "opennslswitchReservedEnum595", \
    "opennslswitchReservedEnum596", \
    "opennslswitchReservedEnum597", \
    "opennslswitchReservedEnum598", \
    "opennslswitchReservedEnum599", \
    "opennslswitchReservedEnum600", \
    "opennslswitchReservedEnum601", \
    "opennslswitchReservedEnum602", \
    "opennslswitchReservedEnum603", \
    "opennslswitchReservedEnum604", \
    "opennslswitchReservedEnum605", \
    "opennslswitchReservedEnum606", \
    "opennslswitchReservedEnum607", \
    "opennslswitchReservedEnum608", \
    "opennslswitchReservedEnum609", \
    "opennslswitchReservedEnum610", \
    "opennslswitchReservedEnum611", \
    "opennslswitchReservedEnum612", \
    "opennslswitchReservedEnum613", \
    "opennslswitchReservedEnum614", \
    "opennslswitchReservedEnum615", \
    "opennslswitchReservedEnum616", \
    "opennslswitchReservedEnum617", \
    "opennslswitchReservedEnum618", \
    "opennslswitchReservedEnum619", \
    "opennslswitchReservedEnum620", \
    "opennslswitchReservedEnum621", \
    "opennslswitchReservedEnum622", \
    "opennslswitchReservedEnum623", \
    "opennslswitchReservedEnum624", \
    "opennslswitchReservedEnum625", \
    "opennslswitchReservedEnum626", \
    "opennslswitchReservedEnum627", \
    "opennslswitchReservedEnum628", \
    "opennslswitchReservedEnum629", \
    "opennslswitchReservedEnum630", \
    "opennslswitchReservedEnum631", \
    "opennslswitchReservedEnum632", \
    "opennslswitchReservedEnum633", \
    "opennslswitchReservedEnum634", \
    "opennslswitchReservedEnum635", \
    "opennslswitchReservedEnum636", \
    "opennslswitchReservedEnum637", \
    "opennslswitchReservedEnum638", \
    "opennslswitchReservedEnum639", \
    "opennslswitchReservedEnum640", \
    "opennslswitchReservedEnum641", \
    "opennslswitchReservedEnum642", \
    "opennslswitchReservedEnum643", \
    "opennslswitchReservedEnum644", \
    "opennslswitchReservedEnum645", \
    "opennslswitchReservedEnum646", \
    "opennslswitchReservedEnum647", \
    "opennslswitchReservedEnum648", \
    "opennslswitchReservedEnum649", \
    "opennslswitchReservedEnum650", \
    "opennslswitchReservedEnum651", \
    "opennslswitchReservedEnum652", \
    "opennslswitchReservedEnum653", \
    "opennslswitchReservedEnum654", \
    "opennslswitchReservedEnum655", \
    "opennslswitchReservedEnum656", \
    "opennslswitchReservedEnum657", \
    "opennslswitchReservedEnum658", \
    "opennslswitchReservedEnum659", \
    "opennslswitchReservedEnum660", \
    "opennslswitchReservedEnum661", \
    "opennslswitchReservedEnum662", \
    "opennslswitchReservedEnum663", \
    "opennslswitchReservedEnum664", \
    "opennslswitchReservedEnum665", \
    "opennslswitchReservedEnum666", \
    "opennslswitchReservedEnum667", \
    "opennslswitchReservedEnum668", \
    "opennslswitchReservedEnum669", \
    "opennslswitchReservedEnum670", \
    "opennslswitchReservedEnum671", \
    "opennslswitchReservedEnum672", \
    "BstEnable", \
    "BstTrackingMode", \
    "opennslswitchReservedEnum673", \
    "opennslswitchReservedEnum674", \
    "opennslswitchReservedEnum675", \
    "opennslswitchReservedEnum676", \
    "opennslswitchReservedEnum677", \
    "opennslswitchReservedEnum678", \
    "opennslswitchReservedEnum679", \
    "opennslswitchReservedEnum680", \
    "opennslswitchReservedEnum681", \
    "opennslswitchReservedEnum682", \
    "opennslswitchReservedEnum683", \
    "opennslswitchReservedEnum684", \
    "opennslswitchReservedEnum685", \
    "opennslswitchReservedEnum686", \
    "opennslswitchReservedEnum687", \
    "opennslswitchReservedEnum688", \
    "opennslswitchReservedEnum689", \
    "opennslswitchReservedEnum690", \
    "opennslswitchReservedEnum691", \
    "opennslswitchReservedEnum692", \
    "opennslswitchReservedEnum693", \
    "opennslswitchReservedEnum694", \
    "opennslswitchReservedEnum695", \
    "opennslswitchReservedEnum696", \
    "opennslswitchReservedEnum697", \
    "opennslswitchReservedEnum698", \
    "opennslswitchReservedEnum699", \
    "opennslswitchReservedEnum700", \
    "opennslswitchReservedEnum701", \
    "opennslswitchReservedEnum702", \
    "opennslswitchReservedEnum703", \
    "opennslswitchReservedEnum704", \
    "opennslswitchReservedEnum705", \
    "opennslswitchReservedEnum706", \
    "opennslswitchReservedEnum707", \
    "opennslswitchReservedEnum708", \
    "opennslswitchReservedEnum709", \
    "opennslswitchReservedEnum710", \
    "opennslswitchReservedEnum711", \
    "opennslswitchReservedEnum712", \
    "opennslswitchReservedEnum713", \
    "opennslswitchReservedEnum714", \
    "opennslswitchReservedEnum715", \
    "opennslswitchReservedEnum716", \
    "opennslswitchReservedEnum717", \
    "opennslswitchReservedEnum718", \
    "opennslswitchReservedEnum719", \
    "opennslswitchReservedEnum720", \
    "opennslswitchReservedEnum721", \
    "opennslswitchReservedEnum722", \
    "opennslswitchReservedEnum723", \
    "opennslswitchReservedEnum724", \
    "opennslswitchReservedEnum725", \
    "opennslswitchReservedEnum726", \
    "opennslswitchReservedEnum727", \
    "opennslswitchReservedEnum728", \
    "opennslswitchReservedEnum729", \
    "opennslswitchReservedEnum730", \
    "opennslswitchReservedEnum731", \
    "opennslswitchReservedEnum732", \
    "opennslswitchReservedEnum733", \
    "opennslswitchReservedEnum734", \
    "opennslswitchReservedEnum735", \
    "EcmpMacroFlowHashEnable", \
    "opennslswitchReservedEnum736", \
    "opennslswitchReservedEnum737", \
    "opennslswitchReservedEnum738", \
    "opennslswitchReservedEnum739", \
    "opennslswitchReservedEnum740", \
    "opennslswitchReservedEnum741", \
    "opennslswitchReservedEnum742", \
    "opennslswitchReservedEnum743", \
    "opennslswitchReservedEnum744", \
    "opennslswitchReservedEnum745", \
    "opennslswitchReservedEnum746", \
    "opennslswitchReservedEnum747", \
    "opennslswitchReservedEnum748", \
    "opennslswitchReservedEnum749", \
    "opennslswitchReservedEnum750", \
    "opennslswitchReservedEnum751", \
    "opennslswitchReservedEnum752", \
    "opennslswitchReservedEnum753", \
    "opennslswitchReservedEnum754", \
    "opennslswitchReservedEnum755", \
    "opennslswitchReservedEnum756", \
    "opennslswitchReservedEnum757", \
    "opennslswitchReservedEnum758", \
    "opennslswitchReservedEnum759", \
    "opennslswitchReservedEnum760", \
    "opennslswitchReservedEnum761", \
    "opennslswitchReservedEnum762", \
    "opennslswitchReservedEnum763", \
    "opennslswitchReservedEnum764", \
    "opennslswitchReservedEnum765", \
    "opennslswitchReservedEnum766", \
    "opennslswitchReservedEnum767", \
    "opennslswitchReservedEnum768", \
    "opennslswitchReservedEnum769", \
    "opennslswitchReservedEnum770", \
    "opennslswitchReservedEnum771", \
    "opennslswitchReservedEnum772", \
    "opennslswitchReservedEnum773", \
    "opennslswitchReservedEnum774", \
    "opennslswitchReservedEnum775", \
    "opennslswitchReservedEnum776", \
    "opennslswitchReservedEnum777", \
    "opennslswitchReservedEnum778", \
    "opennslswitchReservedEnum779", \
    "opennslswitchReservedEnum780", \
    "opennslswitchReservedEnum781", \
    "opennslswitchReservedEnum782", \
    "opennslswitchReservedEnum783", \
    "opennslswitchReservedEnum784", \
    "opennslswitchReservedEnum785", \
    "opennslswitchReservedEnum786", \
    "opennslswitchReservedEnum787", \
    "opennslswitchReservedEnum788", \
    "opennslswitchReservedEnum789", \
    "opennslswitchReservedEnum790", \
    "opennslswitchReservedEnum791", \
    "opennslswitchReservedEnum792", \
    "opennslswitchReservedEnum793", \
    "opennslswitchReservedEnum794", \
    "opennslswitchReservedEnum795", \
    "opennslswitchReservedEnum796", \
    "opennslswitchReservedEnum797", \
    "opennslswitchReservedEnum798", \
    "opennslswitchReservedEnum799", \
    "opennslswitchReservedEnum800", \
    "opennslswitchReservedEnum801", \
    "opennslswitchReservedEnum802", \
    "opennslswitchReservedEnum803", \
    "opennslswitchReservedEnum804", \
    "opennslswitchReservedEnum805", \
    "opennslswitchReservedEnum806", \
    "opennslswitchReservedEnum807", \
    "opennslswitchReservedEnum808", \
    "opennslswitchReservedEnum809", \
    "opennslswitchReservedEnum810", \
    "opennslswitchReservedEnum811", \
    "opennslswitchReservedEnum812", \
    "opennslswitchReservedEnum813", \
    "opennslswitchReservedEnum814", \
    "opennslswitchReservedEnum815", \
    "opennslswitchReservedEnum816", \
    "opennslswitchReservedEnum817", \
    "opennslswitchReservedEnum818", \
    "opennslswitchReservedEnum819", \
    "opennslswitchReservedEnum820", \
    "opennslswitchReservedEnum821", \
    "opennslswitchReservedEnum822", \
    "opennslswitchReservedEnum823", \
    "opennslswitchReservedEnum824", \
    "opennslswitchReservedEnum825", \
    "opennslswitchReservedEnum826", \
    "opennslswitchReservedEnum827", \
    "opennslswitchReservedEnum828", \
    "opennslswitchReservedEnum829", \
    "opennslswitchReservedEnum830", \
    "opennslswitchReservedEnum831", \
    "opennslswitchReservedEnum832", \
    "opennslswitchReservedEnum833", \
    "opennslswitchReservedEnum834", \
    "opennslswitchReservedEnum835", \
    "opennslswitchReservedEnum836", \
    "opennslswitchReservedEnum837", \
    "opennslswitchReservedEnum838", \
    "opennslswitchReservedEnum839", \
    "opennslswitchReservedEnum840", \
    "opennslswitchReservedEnum841", \
    "opennslswitchReservedEnum842", \
    "opennslswitchReservedEnum843", \
    "opennslswitchReservedEnum844", \
    "opennslswitchReservedEnum845", \
    "opennslswitchReservedEnum846", \
    "opennslswitchReservedEnum847", \
    "opennslswitchReservedEnum848", \
    "opennslswitchReservedEnum849", \
    "opennslswitchReservedEnum850", \
    "opennslswitchReservedEnum851", \
    "opennslswitchReservedEnum852", \
    "opennslswitchReservedEnum853", \
    "opennslswitchReservedEnum854", \
    "opennslswitchReservedEnum855", \
    "opennslswitchReservedEnum856", \
    "opennslswitchReservedEnum857", \
    "opennslswitchReservedEnum858", \
    "opennslswitchReservedEnum859", \
    "opennslswitchReservedEnum860", \
    "opennslswitchReservedEnum861", \
    "opennslswitchReservedEnum862", \
    "opennslswitchReservedEnum863", \
    "opennslswitchReservedEnum864", \
    "opennslswitchReservedEnum865", \
    "opennslswitchReservedEnum866", \
    "opennslswitchReservedEnum867", \
    "opennslswitchReservedEnum868", \
    "opennslswitchReservedEnum869", \
    "opennslswitchReservedEnum870", \
    "opennslswitchReservedEnum871", \
    "opennslswitchReservedEnum872", \
    "opennslswitchReservedEnum873", \
    "opennslswitchReservedEnum874", \
    "opennslswitchReservedEnum875", \
    "opennslswitchReservedEnum876", \
    "opennslswitchReservedEnum877", \
    "opennslswitchReservedEnum878", \
    "opennslswitchReservedEnum879", \
    "opennslswitchReservedEnum880", \
    "opennslswitchReservedEnum881", \
    "opennslswitchReservedEnum882", \
    "opennslswitchReservedEnum883", \
    "opennslswitchReservedEnum884", \
    "opennslswitchReservedEnum885", \
    "opennslswitchReservedEnum886", \
    "opennslswitchReservedEnum887", \
    "opennslswitchReservedEnum888", \
    "opennslswitchReservedEnum889", \
    "opennslswitchReservedEnum890", \
    "opennslswitchReservedEnum891", \
    "opennslswitchReservedEnum892", \
    "opennslswitchReservedEnum893", \
    "opennslswitchReservedEnum894", \
    "opennslswitchReservedEnum895", \
    "opennslswitchReservedEnum896", \
    "opennslswitchReservedEnum897", \
    "opennslswitchReservedEnum898", \
    "opennslswitchReservedEnum899", \
    "opennslswitchReservedEnum900", \
    "opennslswitchReservedEnum901", \
    "opennslswitchReservedEnum902", \
    "opennslswitchReservedEnum903", \
    "opennslswitchReservedEnum904", \
    "opennslswitchReservedEnum905", \
    "opennslswitchReservedEnum906", \
    "opennslswitchReservedEnum907", \
    "opennslswitchReservedEnum908", \
    "opennslswitchReservedEnum909", \
    "opennslswitchReservedEnum910", \
    "opennslswitchReservedEnum911", \
    "opennslswitchReservedEnum912" 

#define OPENNSL_SWITCH_STABLE_APPLICATION   (_SHR_SWITCH_STABLE_APPLICATION) 
#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Configure port-specific and device-wide operating modes. Device wide
 *       operating modes are configured on all ports, except the stack ports.
 *
 *\description These APIs set parameters related to general device operation such
 *          as controlling whether certain types of packets should be sent to
 *          the local CPU, or setting the priority to be used when such
 *          packets are forwarded to the CPU.  The port specific operations
 *          affect only the indicated port (where possible) while the general
 *          APIs affect all ports.  Not all operations can be carried out on
 *          individual ports on all devices.
 *
 *\param    unit [IN]   Unit number.
 *\param    type [IN]   Switch control parameter (see =opennsl_switchs)
 *\param    arg [OUT]   (for _set) Argument whose meaning is dependent on type
 *
 *\retval    OPENNSL_E_UNAVAIL	Feature not available on this device
 *\retval    OPENNSL_E_XXX		Other error
 ******************************************************************************/
extern int opennsl_switch_control_get(
    int unit, 
    opennsl_switch_control_t type, 
    int *arg) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure port-specific and device-wide operating modes. Device wide
 *       operating modes are configured on all ports, except the stack ports.
 *
 *\description These APIs set parameters related to general device operation such
 *          as controlling whether certain types of packets should be sent to
 *          the local CPU, or setting the priority to be used when such
 *          packets are forwarded to the CPU.  The port specific operations
 *          affect only the indicated port (where possible) while the general
 *          APIs affect all ports.  Not all operations can be carried out on
 *          individual ports on all devices.
 *
 *\param    unit [IN]   Unit number.
 *\param    type [IN]   Switch control parameter (see =opennsl_switchs)
 *\param    arg [IN]   (for _set) Argument whose meaning is dependent on type
 *
 *\retval    OPENNSL_E_UNAVAIL	Feature not available on this device
 *\retval    OPENNSL_E_XXX		Other error
 ******************************************************************************/
extern int opennsl_switch_control_set(
    int unit, 
    opennsl_switch_control_t type, 
    int arg) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure port-specific and device-wide operating modes. Device wide
 *       operating modes are configured on all ports, except the stack ports.
 *
 *\description These APIs set parameters related to general device operation such
 *          as controlling whether certain types of packets should be sent to
 *          the local CPU, or setting the priority to be used when such
 *          packets are forwarded to the CPU.  The port specific operations
 *          affect only the indicated port (where possible) while the general
 *          APIs affect all ports.  Not all operations can be carried out on
 *          individual ports on all devices.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    type [IN]   Switch control parameter (see =opennsl_switchs)
 *\param    arg [OUT]   (for _set) Argument whose meaning is dependent on type
 *
 *\retval    OPENNSL_E_UNAVAIL	Feature not available on this device
 *\retval    OPENNSL_E_XXX		Other error
 ******************************************************************************/
extern int opennsl_switch_control_port_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_switch_control_t type, 
    int *arg) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure port-specific and device-wide operating modes. Device wide
 *       operating modes are configured on all ports, except the stack ports.
 *
 *\description These APIs set parameters related to general device operation such
 *          as controlling whether certain types of packets should be sent to
 *          the local CPU, or setting the priority to be used when such
 *          packets are forwarded to the CPU.  The port specific operations
 *          affect only the indicated port (where possible) while the general
 *          APIs affect all ports.  Not all operations can be carried out on
 *          individual ports on all devices.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    type [IN]   Switch control parameter (see =opennsl_switchs)
 *\param    arg [IN]   (for _set) Argument whose meaning is dependent on type
 *
 *\retval    OPENNSL_E_UNAVAIL	Feature not available on this device
 *\retval    OPENNSL_E_XXX		Other error
 ******************************************************************************/
extern int opennsl_switch_control_port_set(
    int unit, 
    opennsl_port_t port, 
    opennsl_switch_control_t type, 
    int arg) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

typedef void (*opennsl_switch_event_cb_t)(
    int unit, 
    opennsl_switch_event_t event, 
    uint32 arg1, 
    uint32 arg2, 
    uint32 arg3, 
    void *userdata);

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Registers/Unregisters a callback function for switch critical events.
 *
 *\description These APIs allow to register a callback function which will be
 *          called upon a critical event on the chip.  By registering a
 *          callback function application can be notified upon critical errors
 *          described in table below. If such callback been called, it is
 *          strongly recommend to log all the information provided in arg1,
 *          arg2 and arg3 and reboot the chip.
 *          Call back function is defined as following .
 *
 *\param    unit [IN]   Unit number.
 *\param    cb [IN]   A callback function to be called upon critical event
 *\param    userdata [IN]   Pointer to any provided user data to be called with a
 *          callback
 *
 *\retval    OPENNSL_E_NONE - Success
 *\retval    OPENNSL_E_UNIT - Invalid unit provided
 *\retval    OPENNSL_E_PARAM - Invalid callback function provided.
 *\retval    OPENNSL_E_MEMORY - Not enough memory to register callback
 ******************************************************************************/
extern int opennsl_switch_event_register(
    int unit, 
    opennsl_switch_event_cb_t cb, 
    void *userdata) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Registers/Unregisters a callback function for switch critical events.
 *
 *\description These APIs allow to register a callback function which will be
 *          called upon a critical event on the chip.  By registering a
 *          callback function application can be notified upon critical errors
 *          described in table below. If such callback been called, it is
 *          strongly recommend to log all the information provided in arg1,
 *          arg2 and arg3 and reboot the chip.
 *          Call back function is defined as following .
 *
 *\param    unit [IN]   Unit number.
 *\param    cb [IN]   A callback function to be called upon critical event
 *\param    userdata [IN]   Pointer to any provided user data to be called with a
 *          callback
 *
 *\retval    OPENNSL_E_NONE - Success
 *\retval    OPENNSL_E_UNIT - Invalid unit provided
 *\retval    OPENNSL_E_PARAM - Invalid callback function provided.
 *\retval    OPENNSL_E_MEMORY - Not enough memory to register callback
 ******************************************************************************/
extern int opennsl_switch_event_unregister(
    int unit, 
    opennsl_switch_event_cb_t cb, 
    void *userdata) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#define OPENNSL_HASH_CONTROL_ECMP_ENHANCE   0x0080     /**< Use enhanced ECMP
                                                          hashing. */
#define OPENNSL_HASH_FIELD_CONFIG_CRC16CCITT 0x00000007 /**< 16-bit CRC using CCITT
                                                          polynomial. */
#define OPENNSL_HASH_FIELD_DSTL4        0x00000020 /**< Destination L4 port. */
#define OPENNSL_HASH_FIELD_SRCL4        0x00000040 /**< Source L4 port. */
#define OPENNSL_HASH_FIELD_IP4DST_LO    0x00000100 /**< IPv4 destination address
                                                      lower 16 bits. */
#define OPENNSL_HASH_FIELD_IP4DST_HI    0x00000200 /**< IPv4 destination address
                                                      upper 16 bits. */
#define OPENNSL_HASH_FIELD_IP4SRC_LO    0x00000400 /**< IPv4 source address lower
                                                      16 bits. */
#define OPENNSL_HASH_FIELD_IP4SRC_HI    0x00000800 /**< IPv4 source address upper
                                                      16 bits. */
#define OPENNSL_HASH_FIELD_IP6DST_LO    0x00001000 /**< IPv6 collapsed destination
                                                      address lower 16 bits. */
#define OPENNSL_HASH_FIELD_IP6DST_HI    0x00002000 /**< IPv6 collapsed destination
                                                      address upper 16 bits. */
#define OPENNSL_HASH_FIELD_IP6SRC_LO    0x00004000 /**< IPv6 collapsed source
                                                      address lower 16 bits. */
#define OPENNSL_HASH_FIELD_IP6SRC_HI    0x00008000 /**< IPv6 collapsed source
                                                      address upper 16 bits. */
/** packet trace lookup result enums */
typedef enum opennsl_switch_pkt_trace_lookup_e {
    opennslswitchReservedEnum914 = 0, 
    opennslswitchReservedEnum915 = 1, 
    opennslswitchReservedEnum916 = 2, 
    opennslswitchReservedEnum917 = 3, 
    opennslswitchReservedEnum918 = 6, 
    opennslswitchReservedEnum919 = 7, 
    opennslswitchReservedEnum920 = 8, 
    opennslswitchReservedEnum921 = 9, 
    opennslswitchReservedEnum922 = 10, 
    opennslswitchReservedEnum923 = 11, 
    opennslswitchReservedEnum924 = 12, 
    opennslswitchReservedEnum925 = 13, 
    opennslswitchReservedEnum926 = 14, 
    opennslswitchReservedEnum927 = 15, 
    opennslswitchReservedEnum928 = 16, 
    opennslswitchReservedEnum929 = 17, 
    opennslswitchReservedEnum930 = 18, 
    opennslswitchReservedEnum931 = 19, 
    opennslSwitchPktTraceLookupCount = 20 
} opennsl_switch_pkt_trace_lookup_t;

/** lookup result set bit map */
typedef struct opennsl_switch_pkt_trace_lookup_result_s {
    SHR_BITDCL pkt_trace_status_bitmap[_SHR_BITDCLSIZE(opennslSwitchPktTraceLookupCount)]; /**< bit map for packet trace lookup
                                           result set */
} opennsl_switch_pkt_trace_lookup_result_t;

/** packet trace resolution enums */
typedef enum opennsl_switch_pkt_trace_resolution_e {
    opennslswitchReservedEnum932, 
    opennslswitchReservedEnum933, 
    opennslswitchReservedEnum934, 
    opennslswitchReservedEnum935, 
    opennslswitchReservedEnum936, 
    opennslswitchReservedEnum937, 
    opennslswitchReservedEnum938, 
    opennslswitchReservedEnum939, 
    opennslswitchReservedEnum940, 
    opennslswitchReservedEnum941, 
    opennslswitchReservedEnum942, 
    opennslswitchReservedEnum943, 
    opennslswitchReservedEnum944, 
    opennslswitchReservedEnum945, 
    opennslswitchReservedEnum946, 
    opennslswitchReservedEnum947, 
    opennslswitchReservedEnum948, 
    opennslswitchReservedEnum949, 
    opennslswitchReservedEnum950, 
    opennslswitchReservedEnum951, 
    opennslswitchReservedEnum952, 
    opennslswitchReservedEnum953, 
    opennslswitchReservedEnum954, 
    opennslswitchReservedEnum955, 
    opennslswitchReservedEnum956, 
    opennslswitchReservedEnum957, 
    opennslswitchReservedEnum958, 
    opennslswitchReservedEnum959 
} opennsl_switch_pkt_trace_resolution_t;

#define OPENNSL_SWITCH_PKT_TRACE_ECMP_1     0x0001     /**< level 1 ecmp hashing
                                                          resolution done */
#define OPENNSL_SWITCH_PKT_TRACE_ECMP_2     0x0002     /**< level 2 ecmp hashing
                                                          resolution done */
#define OPENNSL_SWITCH_PKT_TRACE_TRUNK      0x0004     /**< trunk hashing
                                                          resolution done */
#define OPENNSL_SWITCH_PKT_TRACE_FABRIC_TRUNK 0x0008     /**< hg trunk hashing
                                                          resolution done */
/** packet hashing resolution information */
typedef struct opennsl_switch_pkt_trace_hashing_info_s {
    uint32 flags;                       /**< flag containing
                                           OPENNSL_SWITCH_PKT_TRACE_ECMP/TRUNK/FABRIC_TRUNK,
                                           0 == no hashing resolution done */
    opennsl_if_t ecmp_1_group;          /**< multipath egress forwarding object. */
    opennsl_if_t ecmp_1_egress;         /**< ecmp destination interface */
    opennsl_if_t ecmp_2_group;          /**< multipath egress forwarding object. */
    opennsl_if_t ecmp_2_egress;         /**< ecmp destination interface */
    opennsl_gport_t trunk;              /**< destination trunk group */
    opennsl_gport_t trunk_member;       /**< destination member port which packet
                                           egress. */
    opennsl_gport_t fabric_trunk;       /**< destination hg trunk group */
    opennsl_gport_t fabric_trunk_member; /**< destination member hg port which
                                           packet will egress. */
} opennsl_switch_pkt_trace_hashing_info_t;

#define OPENNSL_SWITCH_PKT_TRACE_RAW_DATA_MAX 112        /**< max bytes of
                                                          pkt_trace_info.raw_data */
/** packet trace ingress process data */
typedef struct opennsl_switch_pkt_trace_info_s {
    opennsl_switch_pkt_trace_lookup_result_t pkt_trace_lookup_status; /**< packet trace lookup status set */
    opennsl_switch_pkt_trace_resolution_t pkt_trace_resolution; /**< packet trace resolution result */
    opennsl_switch_pkt_trace_hashing_info_t pkt_trace_hash_info; /**< packet trace hashing information */
    opennsl_stg_stp_t pkt_trace_stp_state; /**< packet trace ingress stp state */
    uint32 dest_pipe_num;               /**< ingress pipeline number of the pkt
                                           trace packet */
    uint32 raw_data_length;             /**< number of bytes returned as raw_data */
    uint8 raw_data[OPENNSL_SWITCH_PKT_TRACE_RAW_DATA_MAX]; /**< packet trace process result data in
                                           raw format */
} opennsl_switch_pkt_trace_info_t;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Generate a visibility trace packet and then read the result of the
 *       packets ingress processing information.
 *
 *\description Generate a visibility packet. Read visibility packet process data
 *          from PTR_RESULTS_BUFFER_IVP, ISW1, and ISW2 then store the raw
 *          data into opennsl_pkt_trace_info_t*  Last, convert the raw data
 *          into abstracted format and store into opennsl_pkt_trace_info_t*
 *          These profile options are used to set loopback headers
 *          cpu_pkt_profile field.
 *
 *\param    unit [IN]   Unit number.
 *\param    options [IN]   FLAGS to select pre-configured cpu_pkt_profile register
 *          values
 *\param    port [IN]
 *\param    len [IN]   Number of bytes to copy from data
 *\param    data [IN]   Source packet buffer to copy from
 *\param    pkt_trace_info [IN,OUT]   visibility packet process information in
 *          opennsl_pkt_trace_info_s format
 *
 *\retval    OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_switch_pkt_trace_info_get(
    int unit, 
    uint32 options, 
    uint8 port, 
    int len, 
    uint8 *data, 
    opennsl_switch_pkt_trace_info_t *pkt_trace_info) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#endif /* __OPENNSL_SWITCH_H__ */
/*@}*/
