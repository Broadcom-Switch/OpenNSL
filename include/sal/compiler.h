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
 ********************************************************************
 * File:        compiler.h
 * Details:     Compiler specific defines and options
 *******************************************************************/

#ifndef _SAL_COMPILER_H
#define _SAL_COMPILER_H

/*
 * Define attributes according to compiler.
 * Currently we have used GNU C, Diab Data, and Borland compilers.
 */

#define COMPILER_HAS_CONST
#define COMPILER_HAS_STATIC

#ifndef __KERNEL__
#define COMPILER_HAS_DOUBLE
#endif

/*
 * Return a string containing the current FILE:LINE location in the code. 
 *
 */
#ifndef FILE_LINE_STRING

#define __STRINGIFY(x) #x
#define _STRINGIFY(x) __STRINGIFY(x)

#define FILE_LINE_STRING() (__FILE__ ":" _STRINGIFY(__LINE__))

#endif /* FILE_LINE_STRING */


#if defined(__GNUC__) && !defined(__PEDANTIC__)

#define COMPILER_HAS_LONGLONG
#if defined(VXWORKS) && ((CPU == PPC860) || (CPU == PPC603) || (CPU == PPC32))
/*
 * WRS T2 (Cygnus 2.7.2) PPC compiler can't handle 64-bit properly.
 * It generates bad code for shift by 32.  It also generates false
 * "variable might be used initialized" warnings for COMPILER_ZERO.
 */
#if (VX_VERSION == 55) ||  (VX_VERSION >= 62)
# define COMPILER_HAS_LONGLONG_SHIFT
#else
# undef COMPILER_HAS_LONGLONG_SHIFT
#endif
#else
# define COMPILER_HAS_LONGLONG_SHIFT
#endif
#define COMPILER_HAS_LONGLONG_ADDSUB
#define COMPILER_HAS_LONGLONG_MUL
#define COMPILER_HAS_LONGLONG_DIV
#define COMPILER_HAS_LONGLONG_ANDOR
#define COMPILER_HAS_LONGLONG_COMPARE

#if ((__GNUC__ * 10000) + (__GNUC_MINOR__ * 100) + __GNUC_PATCHLEVEL__) >= 30201
/* gcc 3.2.1 is the earliest version known to support the format attribute
   when applied to function pointers. gcc 3.0.0 is known to *not* support
   this. */
#define COMPILER_HAS_FUNCTION_POINTER_FORMAT_ATTRIBUTE
#endif

#ifndef __STRICT_ANSI__
#define COMPILER_HAS_INLINE
#endif

#define COMPILER_ATTRIBUTE(_a)    __attribute__ (_a)
#define    COMPILER_REFERENCE(_a)    ((void)(_a))
#define FUNCTION_NAME() (__FUNCTION__)

#elif (defined(__DCC__) && (__DCC__ == 1)) && !defined(__PEDANTIC__)

#define COMPILER_HAS_LONGLONG
#define COMPILER_HAS_LONGLONG_SHIFT
#define COMPILER_HAS_LONGLONG_ADDSUB
#define COMPILER_HAS_LONGLONG_MUL
#define COMPILER_HAS_LONGLONG_DIV
#define COMPILER_HAS_LONGLONG_ANDOR
#define COMPILER_HAS_LONGLONG_COMPARE

#define COMPILER_ATTRIBUTE(_a)
#define    COMPILER_REFERENCE(_a)    ((void)(_a))

#if (defined(DIAB_VER)) && (DIAB_VER == 4)
/* Older versions of DCC do not support __FUNCTION__ */
#define FUNCTION_NAME() FILE_LINE_STRING()
#else
#define FUNCTION_NAME() (__FUNCTION__)
#endif

#else /* !defined(__GNUC__) */

#define COMPILER_ATTRIBUTE(_a)
#define    COMPILER_REFERENCE(_a)    ((void)(_a))

#ifndef FUNCTION_NAME
/*
 * No portable ANSI method to accomplish this. 
 * Just return the location in the code instead. 
 */
#define FUNCTION_NAME() FILE_LINE_STRING()

#endif /* FUNCTION_NAME */

#endif /* !defined(__GNUC__) */

/* GreenHills compiler */
#ifdef GHS
#define COMPILER_HAS_LONGLONG
#define COMPILER_HAS_LONGLONG_SHIFT
#define COMPILER_HAS_LONGLONG_ADDSUB
#define COMPILER_HAS_LONGLONG_MUL
#define COMPILER_HAS_LONGLONG_DIV
#define COMPILER_HAS_LONGLONG_ANDOR
#define COMPILER_HAS_LONGLONG_COMPARE

/* GreenHills compiler has __FUNCTION__ built-in macro not __func__ */
#define __func__ __FUNCTION__
#endif

/*
 * __attribute__ for function pointers
 */
#ifdef COMPILER_HAS_FUNCTION_POINTER_FORMAT_ATTRIBUTE
#define COMPILER_ATTRIBUTE_FUNCTION_POINTER(_a)  COMPILER_ATTRIBUTE(_a)
#else
#define COMPILER_ATTRIBUTE_FUNCTION_POINTER(_a)
#endif


#ifdef __PEDANTIC__
#define COMPILER_STRING_CONST_LIMIT    509
#endif

/*
 * Compiler overrides that can be configured in Make.local
 */
#ifdef    COMPILER_OVERRIDE_NO_LONGLONG
#undef    COMPILER_HAS_LONGLONG
#undef    COMPILER_HAS_LONGLONG_SHIFT
#undef    COMPILER_HAS_LONGLONG_ADDSUB
#undef    COMPILER_HAS_LONGLONG_MUL
#undef    COMPILER_HAS_LONGLONG_DIV
#undef    COMPILER_HAS_LONGLONG_ANDOR
#undef    COMPILER_HAS_LONGLONG_COMPARE
#endif

#ifdef    COMPILER_OVERRIDE_NO_DOUBLE
#undef    COMPILER_HAS_DOUBLE
#endif

#ifdef    COMPILER_OVERRIDE_NO_INLINE
#undef    COMPILER_HAS_INLINE
#endif

#ifdef    COMPILER_OVERRIDE_NO_CONST
#undef    COMPILER_HAS_CONST
#endif

#ifdef    COMPILER_OVERRIDE_NO_STATIC
#undef    COMPILER_HAS_STATIC
#endif

/*
 * 64-bit word order
 */

#ifdef __BORLAND__
/* The Borland cpp does not expand correctly in the macros below...sigh */
static int u64_MSW = 1;
static int u64_LSW = 0;
#else
# ifdef BE_HOST
#  define u64_MSW    0
#  define u64_LSW    1
# else /* LE_HOST */
#  define u64_MSW    1
#  define u64_LSW    0
# endif /* LE_HOST */
#endif /* __BORLAND__ */

/*
 * 64-bit type
 */

#ifdef LONGS_ARE_64BITS

#define COMPILER_64BIT
#define    COMPILER_UINT64            unsigned long
#define COMPILER_INT64                  long
#define u64_H(v)            (((uint32 *) &(v))[u64_MSW])
#define u64_L(v)            (((uint32 *) &(v))[u64_LSW])
#define COMPILER_64_INIT(_hi, _lo)      ( (((long) (_hi)) << 32) | (_lo))

#else /* !LONGS_ARE_64BITS */

#ifdef COMPILER_HAS_LONGLONG

#define COMPILER_64BIT
#define    COMPILER_UINT64            unsigned long long
#define COMPILER_INT64                  long long
#define u64_H(v)            (((uint32 *) &(v))[u64_MSW])
#define u64_L(v)            (((uint32 *) &(v))[u64_LSW])
#define COMPILER_64_INIT(_hi, _lo)      ( (((long long) (_hi)) << 32) | (_lo))

#else /* !COMPILER_HAS_LONGLONG */
typedef struct sal_uint64_s { unsigned int u64_w[2]; } sal_uint64_t;
typedef struct sal_int64_s  { int u64_w[2]; } sal_int64_t;

#define COMPILER_UINT64     sal_uint64_t
#define COMPILER_INT64      sal_int64_t
#define u64_H(v)            ((v).u64_w[u64_MSW])
#define u64_L(v)            ((v).u64_w[u64_LSW])

#ifdef BE_HOST
#define COMPILER_64_INIT(_hi, _lo)        { { _hi, _lo } }
#else
#define COMPILER_64_INIT(_hi, _lo)         { { _lo, _hi } }
#endif

#endif /* !COMPILER_HAS_LONGLONG */
#endif /* LONGS_ARE_64BITS */

/*
 * 32-/64-bit type conversions
 */

#ifdef COMPILER_HAS_LONGLONG_SHIFT

#define COMPILER_64_TO_32_LO(dst, src)  ((dst) = (uint32) (src))
#define COMPILER_64_TO_32_HI(dst, src)  ((dst) = (uint32) ((src) >> 32))
#define COMPILER_64_HI(src)     ((uint32) ((src) >> 32))
#define COMPILER_64_LO(src)     ((uint32) (src))
#define COMPILER_64_ZERO(dst)       ((dst) = 0)
#define COMPILER_64_IS_ZERO(src)    ((src) == 0)
                                       

#define COMPILER_64_SET(dst, src_hi, src_lo)                \
    ((dst) = (((uint64) ((uint32)(src_hi))) << 32) | ((uint64) ((uint32)(src_lo))))

#else /* !COMPILER_HAS_LONGLONG_SHIFT */

#define COMPILER_64_TO_32_LO(dst, src)    ((dst) = u64_L(src))
#define COMPILER_64_TO_32_HI(dst, src)    ((dst) = u64_H(src))
#define COMPILER_64_HI(src)        u64_H(src)
#define COMPILER_64_LO(src)        u64_L(src)
#define COMPILER_64_ZERO(dst)        (u64_H(dst) = u64_L(dst) = 0)
#define COMPILER_64_IS_ZERO(src)    (u64_H(src) == 0 && u64_L(src) == 0)

#define COMPILER_64_SET(dst, src_hi, src_lo)                \
        do {                                \
            u64_H(dst) = (src_hi);                                  \
            u64_L(dst) = (src_lo);                                  \
        } while (0)

#endif /* !COMPILER_HAS_LONGLONG_SHIFT */

/*
 * 64-bit addition and subtraction
 */

#ifdef COMPILER_HAS_LONGLONG_ADDSUB

#define COMPILER_64_ADD_64(dst, src)    ((dst) += (src))
#define COMPILER_64_ADD_32(dst, src)    ((dst) += (src))
#define COMPILER_64_SUB_64(dst, src)    ((dst) -= (src))
#define COMPILER_64_SUB_32(dst, src)    ((dst) -= (src))

#else /* !COMPILER_HAS_LONGLONG_ADDSUB */

#define COMPILER_64_ADD_64(dst, src)                    \
        do {                                \
        uint32 __t = u64_L(dst);                    \
        u64_L(dst) += u64_L(src);                    \
        if (u64_L(dst) < __t) {                    \
            u64_H(dst) += u64_H(src) + 1;                \
        } else {                            \
            u64_H(dst) += u64_H(src);                \
        }                                \
    } while (0)
#define COMPILER_64_ADD_32(dst, src)                    \
        do {                                \
        uint32 __t = u64_L(dst);                    \
        u64_L(dst) += (src);                    \
        if (u64_L(dst) < __t) {                    \
            u64_H(dst)++;                        \
        }                                \
    } while (0)
#define COMPILER_64_SUB_64(dst, src)                    \
        do {                                \
        uint32 __t = u64_L(dst);                    \
        u64_L(dst) -= u64_L(src);                    \
        if (u64_L(dst) > __t) {                    \
            u64_H(dst) -= u64_H(src) + 1;                \
        } else {                            \
            u64_H(dst) -= u64_H(src);                \
        }                                \
    } while (0)
#define COMPILER_64_SUB_32(dst, src)                    \
        do {                                \
        uint32 __t = u64_L(dst);                    \
        u64_L(dst) -= (src);                    \
        if (u64_L(dst) > __t) {                    \
            u64_H(dst)--;                        \
        }                                \
    } while (0)

#endif /* !COMPILER_HAS_LONGLONG_ADDSUB */

/*
 * 64-bit multiplication
 */

#ifdef COMPILER_HAS_LONGLONG_MUL

#define COMPILER_64_UMUL_32(dst, src)    ((dst) *= (src))

#else /* !COMPILER_HAS_LONGLONG_MUL */

/* Multiply of unsigned 64-bit and unsigned 32-bit integers, no overflow handling  */
#define COMPILER_64_UMUL_32(dst, src)                                   \
    do {                                                                \
        uint32 __d[4];                                                  \
        uint32 __s[2];                                                  \
        uint32 __r[4];                                                  \
        uint32 __t[2];                                                  \
        __d[0] = u64_L(dst) & 0xffff;                                   \
        __d[1] = u64_L(dst) >> 16;                                      \
        __d[2] = u64_H(dst) & 0xffff;                                   \
        __d[3] = u64_H(dst) >> 16;                                      \
        __s[0] = (src) & 0xffff;                                        \
        __s[1] = (src) >> 16;                                           \
        __r[0] = __d[0] * __s[0];                                       \
        __r[1] = __d[1] * __s[0] + __d[0] * __s[1];                     \
        __r[2] = __d[2] * __s[0] + __d[1] * __s[1];                     \
        __r[3] = __d[3] * __s[0] + __d[2] * __s[1];                     \
        __t[0] = __r[1] << 16;                                          \
        __t[1] = __t[0] + __r[0];                                       \
        COMPILER_64_SET((dst), (__r[3] << 16) + __r[2] + (__r[1] >> 16) + (__t[1] < __t[0] ? 1 : 0), \
                        __t[1]                                          \
                        );                                              \
    } while (0);

#endif /* !COMPILER_HAS_LONGLONG_MUL */

/*
 * 64-bit logical operations
 */

#ifdef COMPILER_HAS_LONGLONG_ANDOR

#define COMPILER_64_AND(dst, src)    ((dst) &= (src))
#define COMPILER_64_OR(dst, src)    ((dst) |= (src))
#define COMPILER_64_XOR(dst, src)    ((dst) ^= (src))
#define COMPILER_64_NOT(dst)        ((dst) = ~(dst))

#else /* !COMPILER_HAS_LONGLONG_ANDOR */

#define COMPILER_64_AND(dst, src)                    \
    do {                                \
        u64_H((dst)) &= u64_H((src));                    \
        u64_L((dst)) &= u64_L((src));                    \
    } while (0)
#define COMPILER_64_OR(dst, src)                    \
    do {                                \
        u64_H((dst)) |= u64_H((src));                    \
        u64_L((dst)) |= u64_L((src));                    \
    } while (0)
#define COMPILER_64_XOR(dst, src)                    \
    do {                                \
        u64_H((dst)) ^= u64_H((src));                    \
        u64_L((dst)) ^= u64_L((src));                    \
    } while (0)
#define COMPILER_64_NOT(dst)                        \
    do {                                \
        u64_H((dst)) = ~u64_H((dst));                    \
        u64_L((dst)) = ~u64_L((dst));                    \
    } while (0)

#endif /* !COMPILER_HAS_LONGLONG_ANDOR */

#define COMPILER_64_ALLONES(dst)   \
    COMPILER_64_ZERO((dst));\
    COMPILER_64_NOT((dst))

/*
 * 64-bit shift
 */

#ifdef COMPILER_HAS_LONGLONG_SHIFT

#define COMPILER_64_SHL(dst, bits)    ((dst) <<= (bits))
#define COMPILER_64_SHR(dst, bits)    ((dst) >>= (bits))

#define COMPILER_64_BITTEST(val, n)     \
    ((((uint64)val) & (((uint64) 1)<<(n))) != ((uint64) 0))

#else /* !COMPILER_HAS_LONGLONG_SHIFT */

#define COMPILER_64_SHL(dst, bits)                    \
    do {                                \
        int __b = (bits);                        \
        if (__b >= 32) {                        \
        u64_H(dst) = u64_L(dst);                \
        u64_L(dst) = 0;                        \
        __b -= 32;                        \
        }                                \
        u64_H(dst) = (u64_H(dst) << __b) |                \
        (__b ? u64_L(dst) >> (32 - __b) : 0);            \
        u64_L(dst) <<= __b;                        \
    } while (0)

#define COMPILER_64_SHR(dst, bits)                    \
    do {                                \
        int __b = (bits);                        \
        if (__b >= 32) {                        \
        u64_L(dst) = u64_H(dst);                \
        u64_H(dst) = 0;                        \
        __b -= 32;                        \
        }                                \
        u64_L(dst) = (u64_L(dst) >> __b) |                \
        (__b ? u64_H(dst) << (32 - __b) : 0);            \
        u64_H(dst) >>= __b;                        \
    } while (0)

#define COMPILER_64_BITTEST(val, n)     \
    ( (((n) < 32) && (u64_L(val) & (1 << (n)))) || \
      (((n) >= 32) && (u64_H(val) & (1 << ((n) - 32)))) )

#endif /* !COMPILER_HAS_LONGLONG_SHIFT */

/*
 * 64-bit compare operations
 */

#ifdef COMPILER_HAS_LONGLONG_COMPARE

#define COMPILER_64_EQ(src1, src2)    ((src1) == (src2))
#define COMPILER_64_NE(src1, src2)    ((src1) != (src2))
#define COMPILER_64_LT(src1, src2)    ((src1) <  (src2))
#define COMPILER_64_LE(src1, src2)    ((src1) <= (src2))
#define COMPILER_64_GT(src1, src2)    ((src1) >  (src2))
#define COMPILER_64_GE(src1, src2)    ((src1) >= (src2))

#else /* !COMPILER_HAS_LONGLONG_COMPARE */

#define COMPILER_64_EQ(src1, src2)    (u64_H(src1) == u64_H(src2) && \
                     u64_L(src1) == u64_L(src2))
#define COMPILER_64_NE(src1, src2)    (u64_H(src1) != u64_H(src2) || \
                     u64_L(src1) != u64_L(src2))
#define COMPILER_64_LT(src1, src2)    (u64_H(src1) < u64_H(src2) || \
                     ((u64_H(src1) == u64_H(src2) && \
                       u64_L(src1) < u64_L(src2))))
#define COMPILER_64_LE(src1, src2)    (u64_H(src1) < u64_H(src2) || \
                     ((u64_H(src1) == u64_H(src2) && \
                       u64_L(src1) <= u64_L(src2))))
#define COMPILER_64_GT(src1, src2)    (u64_H(src1) > u64_H(src2) || \
                     ((u64_H(src1) == u64_H(src2) && \
                       u64_L(src1) > u64_L(src2))))
#define COMPILER_64_GE(src1, src2)    (u64_H(src1) > u64_H(src2) || \
                     ((u64_H(src1) == u64_H(src2) && \
                       u64_L(src1) >= u64_L(src2))))

#endif /* !COMPILER_HAS_LONGLONG_COMPARE */

/* Set up a mask of width bits offset lft_shft.  No error checking */
#define COMPILER_64_MASK_CREATE(dst, width, lft_shift)                  \
    do {                                                                \
        COMPILER_64_ALLONES(dst);                                       \
        COMPILER_64_SHR((dst), (64 - (width)));                         \
        COMPILER_64_SHL((dst), (lft_shift));                            \
    } while (0)

#define COMPILER_64_DELTA(src, last, new)\
        do { \
            COMPILER_64_ZERO(src);\
            COMPILER_64_ADD_64(src, new);\
            COMPILER_64_SUB_64(src, last);\
        } while(0)

#define COMPILER_64_BITSET(dst, n)              \
        do {                                    \
            uint64 temp64;                      \
            COMPILER_64_SET(temp64, 0, 1);      \
            COMPILER_64_SHL(temp64, n);         \
            COMPILER_64_OR(dst, temp64);        \
        } while(0)

#define COMPILER_64_BITCLR(dst, n)              \
        do {                                    \
            uint64 temp64;                      \
            COMPILER_64_SET(temp64, 0, 1);      \
            COMPILER_64_SHL(temp64, n);         \
            COMPILER_64_NOT(temp64);            \
            COMPILER_64_AND(dst, temp64);       \
        } while(0)


 /*
 * 64-bit division
 */

#if defined COMPILER_HAS_LONGLONG_DIV && ! defined (__KERNEL__)

#define COMPILER_64_UDIV_64(dst, src)    ((dst) /= (src))

#else /* !(defined COMPILER_HAS_LONGLONG_DIV && ! defined (__KERNEL__)) */

/* Divide of unsigned 64-bit and unsigned 64-bit integers, no overflow handling  */
#define COMPILER_64_UDIV_64(dst, src)                                       \
    do {                                                                \
        uint32 q_hi = 0, q_lo = 0;                                      \
        while( COMPILER_64_GE(dst, src) )                               \
            {                                                           \
                COMPILER_64_SUB_64(dst, src);                           \
                if (++q_lo == 0) ++q_hi;                                \
            }                                                           \
        COMPILER_64_SET(dst, q_hi, q_lo);                               \
    } while (0)

#endif /* defined COMPILER_HAS_LONGLONG_DIV && ! defined (__KERNEL__) */
/*
 * Some macros for double support
 *
 * You can use the COMPILER_DOUBLE macro
 * if you would prefer double precision, but it is not necessary.
 * If you need more control (or you need to print :), then
 * then you should use the COMPILER_HAS_DOUBLE macro explicitly.
 *
 */
#ifdef COMPILER_HAS_DOUBLE
#define COMPILER_DOUBLE double
#define COMPILER_DOUBLE_FORMAT "f"
#define COMPILER_64_TO_DOUBLE(f, i64) \
    ((f) = COMPILER_64_HI(i64) * 4294967296.0 + COMPILER_64_LO(i64))
#define COMPILER_32_TO_DOUBLE(f, i32) \
    ((f) = (double) (i32))
#else
#define COMPILER_DOUBLE uint32
#define COMPILER_DOUBLE_FORMAT "u"
#define COMPILER_64_TO_DOUBLE(f, i64) ((f) = COMPILER_64_LO(i64))
#define COMPILER_32_TO_DOUBLE(f, i32) ((f) = (i32))
#endif

/*
 * Version of inline that is turned off for compilers that do
 * not support inline.
 */

#ifndef INLINE
# ifdef COMPILER_HAS_INLINE
#  define INLINE    inline
# else
#  define INLINE
# endif
#endif /* !INLINE */

/*
 * Version of const that is turned off for compilers that do
 * not support const.
 */

#ifndef CONST
# ifdef COMPILER_HAS_CONST
#  define CONST        const
# else
#  define CONST
# endif
#endif /* !CONST */

/*
 * Some compilers/linkers/OSs do not put static symbols in the
 * symbol table, which can make debugging harder.
 */

#ifndef STATIC
# if    defined(COMPILER_HAS_STATIC)
#  define STATIC    static
# else
#  define STATIC
# endif
#endif /* !STATIC */

#endif    /* !_SAL_COMPILER_H */
