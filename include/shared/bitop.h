/*********************************************************************
 *
 * (C) Copyright Broadcom Corporation 2013-2016
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
 * File:        bitop.h
 * Details:		Bit Array Operations
 *********************************************************************/

#ifndef _SHR_BITOP_H
#define _SHR_BITOP_H

#include <sal/types.h>

/* Base type for declarations */
#define    SHR_BITDCL        uint32
#define    SHR_BITWID        32

/* (internal) Number of SHR_BITDCLs needed to contain _max bits */
#define    _SHR_BITDCLSIZE(_max)    (((_max) + SHR_BITWID - 1) / SHR_BITWID)

/* Size for giving to malloc and memset to handle _max bits */
#define    SHR_BITALLOCSIZE(_max) (_SHR_BITDCLSIZE(_max) * sizeof (SHR_BITDCL))


/* (internal) Number of SHR_BITDCLs needed to contain from start bit to start bit + range */
#define _SHR_BITDCLSIZE_FROM_START_BIT(_start_bit, _range) (_range + _start_bit -1)/SHR_BITWID - _start_bit/SHR_BITWID + 1

/* Size of SHR_BITDCLs needed to contain from start bit to start bit + range.
   Needed when you want to do autosync */
#define SHR_BITALLOCSIZE_FROM_START_BIT(_start_bit, _range) (_SHR_BITDCLSIZE_FROM_START_BIT(_start_bit, _range) * sizeof (SHR_BITDCL))



/* Declare bit array _n of size _max bits */
#define    SHR_BITDCLNAME(_n, _max) SHR_BITDCL    _n[_SHR_BITDCLSIZE(_max)]
/* Declare bit array _n of size _max bits, and clear it */
#define    SHR_BIT_DCL_CLR_NAME(_n, _max) SHR_BITDCL _n[_SHR_BITDCLSIZE(_max)] = {0}

/* (internal) Generic operation macro on bit array _a, with bit _b */
#define    _SHR_BITOP(_a, _b, _op)    \
        (((_a)[(_b) / SHR_BITWID]) _op (1U << ((_b) % SHR_BITWID)))

/* Specific operations */
#define    SHR_BITGET(_a, _b)    _SHR_BITOP(_a, _b, &)
#define    SHR_BITSET(_a, _b)    _SHR_BITOP(_a, _b, |=)
#define    SHR_BITCLR(_a, _b)    _SHR_BITOP(_a, _b, &= ~)
#define    SHR_BITWRITE(_a, _b, _val)    ((_val) ? SHR_BITSET(_a, _b) : SHR_BITCLR(_a, _b))
#define    SHR_BIT_ITER(_a, _max, _b)            \
           for ((_b) = 0; (_b) < (_max); (_b)++) \
               if ((_a)[(_b) / SHR_BITWID] == 0) \
                   (_b) += (SHR_BITWID - 1);     \
               else if (SHR_BITGET((_a), (_b)))


/* clear _c bits starting from _b in bit array _a */
extern void shr_bitop_range_clear(SHR_BITDCL *a, CONST int b, CONST int c);
#define SHR_BITCLR_RANGE(_a, _b, _c)            \
    (shr_bitop_range_clear(_a, _b, _c))

/* set _c bits starting from _b in bit array _a */
extern void shr_bitop_range_set(SHR_BITDCL *a, CONST int b, CONST int c);
#define SHR_BITSET_RANGE(_a, _b, _c)            \
    (shr_bitop_range_set(_a, _b, _c))

/*
 * Copy _num_bits bits from bit array _src offset _src_offset to bit array _dest offset _dest_offset
 * There should be no overlap between source _src and desstination _dest
 * _dest[_dest_offset:_dest_offset + _num_bits] = _src[_src_offset:_src_offset + _num_bits]
 */
extern void shr_bitop_range_copy(SHR_BITDCL *a,
                                 CONST int b,
                                 CONST SHR_BITDCL *c,
                                 CONST int d,
                                 CONST int e);
#define SHR_BITCOPY_RANGE(_dest, _dest_offset,_src, _src_offset, _num_bits)   \
    (shr_bitop_range_copy(_dest, _dest_offset, _src, _src_offset, _num_bits))

/* Result is 0 only if all bits in the range are 0 */
#define SHR_BITTEST_RANGE(_bits, _first, _bit_count, _result) \
    (_result) = !(shr_bitop_range_null(_bits, _first, _bit_count))

extern void shr_bitop_range_and(CONST SHR_BITDCL *bits1,
                                CONST SHR_BITDCL *bits2,
                                CONST int first,
                                CONST int bit_count,
                                SHR_BITDCL *dest);
extern void shr_bitop_range_or(CONST SHR_BITDCL *bits1,
                               CONST SHR_BITDCL *bits2,
                               CONST int first,
                               CONST int bit_count,
                               SHR_BITDCL *dest);
extern void shr_bitop_range_xor(CONST SHR_BITDCL *bits1,
                                CONST SHR_BITDCL *bits2,
                                CONST int first,
                                CONST int bit_count,
                                SHR_BITDCL *dest);
extern void shr_bitop_range_remove(CONST SHR_BITDCL *bits1,
                                   CONST SHR_BITDCL *bits2,
                                   CONST int first,
                                   CONST int bit_count,
                                   SHR_BITDCL *dest);

#define SHR_BITAND_RANGE(_bits1, _bits2, _first, _bit_count, _dest) \
    (shr_bitop_range_and(_bits1, _bits2, _first, _bit_count, _dest))

#define SHR_BITOR_RANGE(_bits1, _bits2, _first, _bit_count, _dest) \
    (shr_bitop_range_or(_bits1, _bits2, _first, _bit_count, _dest))

#define SHR_BITXOR_RANGE(_bits1, _bits2, _first, _bit_count, _dest) \
    (shr_bitop_range_xor(_bits1, _bits2, _first, _bit_count, _dest))

#define SHR_BITREMOVE_RANGE(_bits1, _bits2, _first, _bit_count, _dest) \
    (shr_bitop_range_remove(_bits1, _bits2, _first, _bit_count, _dest))

extern void shr_bitop_range_negate(CONST SHR_BITDCL *bits1,
                                   CONST int first,
                                   CONST int bit_count,
                                   SHR_BITDCL *dest);

#define SHR_BITNEGATE_RANGE(_bits1, _first, _bit_count, _dest) \
    (shr_bitop_range_negate(_bits1, _first, _bit_count, _dest))

extern int shr_bitop_range_null(CONST SHR_BITDCL *a, CONST int first, CONST int bit_count);
extern int shr_bitop_range_eq(CONST SHR_BITDCL *bits1, CONST SHR_BITDCL *bits2,
                         CONST int first, CONST int range);
extern void shr_bitop_range_count(CONST SHR_BITDCL *bits, CONST int first,
                                 CONST int range, int *count);
#define SHR_BITNULL_RANGE(_bits, _first, _range) \
    (shr_bitop_range_null(_bits, _first, _range))
#define SHR_BITEQ_RANGE(_bits1, _bits2, _first, _range) \
    (shr_bitop_range_eq(_bits1, _bits2, _first, _range))
#define SHR_BITCOUNT_RANGE(_bits, _count, _first, _range) \
    shr_bitop_range_count(_bits, _first, _range, &(_count))

#endif    /* !_SHR_BITOP_H */
