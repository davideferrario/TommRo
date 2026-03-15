
#ifndef TOMMROC_UTIL_H_
#define TOMMROC_UTIL_H_

/*
 *******************************************************************************
 * License
 * (C) Copyright 2017
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications according to the supply agreement.
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: this software is provided
 * "AS IS", with no express or implied warranties of any kind, including,
 * but not limited to, any implied warranties of merchantability or
 * fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Supplier will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 */

/**
 * @defgroup tommRoCUtil tommRoCUtil
 *
 * @brief  TommRoC library util module
 * @author TommRo Software Department
 *
 * This module is providing common utility functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCEnv.h"
#include "tommRoCErr.h"
#include "tommRoCInt.h"
#include "tommRoCString.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/**
 * Compatibility attribute.
 */
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
#define TOMMRO_C_UTIL_INLINE_FUNCT                          inline
#define TOMMRO_C_UTIL_STATIC_INLINE_FUNCT                   static inline
#define TOMMRO_C_UTIL_STATIC_FORCEINLINE_FUNCT              __attribute__((always_inline)) static inline
#define TOMMRO_C_UTIL_FILE                                  __FILE__
#define TOMMRO_C_UTIL_FILE_NAME                             __FILE_NAME__
#define TOMMRO_C_UTIL_LINE                                  __LINE__
#define TOMMRO_C_UTIL_FUNCT_NAME                            __FUNCTION__
#define TOMMRO_C_UTIL_PACKED_PRE
#define TOMMRO_C_UTIL_PACKED_POST                           __attribute__((__packed__))
#define TOMMRO_C_UTIL_UNUSED_PRE                            __attribute__((unused))
#define TOMMRO_C_UTIL_UNUSED_POST
#define TOMMRO_C_UTIL_USED_PRE                              __attribute__((used))
#define TOMMRO_C_UTIL_USED_POST
#define TOMMRO_C_UTIL_WEAK_PRE                              __attribute__((weak))
#define TOMMRO_C_UTIL_WEAK_POST
#define TOMMRO_C_UTIL_SECTION_PRE(name)                     __attribute__((section(name)))
#define TOMMRO_C_UTIL_SECTION_POST(name)
#define TOMMRO_C_UTIL_ALIGN_PRE(N)                          __attribute__((aligned(N)))
#define TOMMRO_C_UTIL_ALIGN_POST(N)
#define TOMMRO_C_UTIL_NORETURN_FUNCTION_PRE                 __attribute__((noreturn))
#define TOMMRO_C_UTIL_NORETURN_FUNCTION_POST
#define TOMMRO_C_UTIL_NO_INIT_VAR_PRE(var)
#define TOMMRO_C_UTIL_NO_INIT_VAR_POST(var)                 var __attribute__((section(".noinit")))
#define TOMMRO_C_UTIL_OPTIMIZATION_NONE_PRE                 __attribute__((optimize("O0")))
#define TOMMRO_C_UTIL_OPTIMIZATION_NONE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_PRE             __attribute__((optimize("O1")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MORE_PRE        __attribute__((optimize("O2")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MORE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MOST_PRE        __attribute__((optimize("O3")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MOST_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_SIZE_PRE        __attribute__((optimize("Os")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_SIZE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FAST_PRE        __attribute__((optimize("Ofast")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FAST_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FOR_DEBUG_PRE   __attribute__((optimize("Og")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FOR_DEBUG_POST
#define TOMMRO_C_UTIL_COMPILE_DATE                          __DATE__        // Mmm dd yyyy (Jul 27 2012)
#define TOMMRO_C_UTIL_COMPILE_TIME                          __TIME__        // hh:mm:ss (Ex. 01:02:03)
#define TOMMRO_C_UTIL_COMPILE_TIMESTAMP                     __TIMESTAMP__   // (Ex. Sun Sep 16 01:03:52 1973)

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#define TOMMRO_C_UTIL_INLINE_FUNCT                          inline
#define TOMMRO_C_UTIL_STATIC_INLINE_FUNCT                   static inline
#define TOMMRO_C_UTIL_STATIC_FORCEINLINE_FUNCT              __attribute__((always_inline)) static inline
#define TOMMRO_C_UTIL_FILE                                  __FILE__
#define TOMMRO_C_UTIL_FILE_NAME                             __FILE_NAME__
#define TOMMRO_C_UTIL_LINE                                  __LINE__
#define TOMMRO_C_UTIL_FUNCT_NAME                            __FUNCTION__
#define TOMMRO_C_UTIL_PACKED_PRE
#define TOMMRO_C_UTIL_PACKED_POST                           __attribute__((__packed__))
#define TOMMRO_C_UTIL_UNUSED_PRE                            __attribute__((unused))
#define TOMMRO_C_UTIL_UNUSED_POST
#define TOMMRO_C_UTIL_USED_PRE                              __attribute__((used))
#define TOMMRO_C_UTIL_USED_POST
#define TOMMRO_C_UTIL_WEAK_PRE                              __attribute__((weak))
#define TOMMRO_C_UTIL_WEAK_POST
#define TOMMRO_C_UTIL_SECTION_PRE(name)                     __attribute__((section(name)))
#define TOMMRO_C_UTIL_SECTION_POST(name)
#define TOMMRO_C_UTIL_ALIGN_PRE(N)                          __attribute__((aligned(N)))
#define TOMMRO_C_UTIL_ALIGN_POST(N)
#define TOMMRO_C_UTIL_NORETURN_FUNCTION_PRE                 __attribute__((noreturn))
#define TOMMRO_C_UTIL_NORETURN_FUNCTION_POST
#define TOMMRO_C_UTIL_NO_INIT_VAR_PRE(var)
#define TOMMRO_C_UTIL_NO_INIT_VAR_POST(var)                 var __attribute__((section(".noinit")))
#define TOMMRO_C_UTIL_OPTIMIZATION_NONE_PRE                 __attribute__((optimize("O0")))
#define TOMMRO_C_UTIL_OPTIMIZATION_NONE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_PRE             __attribute__((optimize("O1")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MORE_PRE        __attribute__((optimize("O2")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MORE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MOST_PRE        __attribute__((optimize("O3")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MOST_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_SIZE_PRE        __attribute__((optimize("Os")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_SIZE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FAST_PRE        __attribute__((optimize("Ofast")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FAST_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FOR_DEBUG_PRE   __attribute__((optimize("Og")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FOR_DEBUG_POST
/**
 * NOTE:
 * __DATE__ is a preprocessor macro that expands to current date (at compile time) in the form mmm dd yyyy (e.g. "Jan 14 2012"), as a string.
 */
#define TOMMRO_C_UTIL_COMPILE_DATE                          __DATE__        // Mmm dd yyyy (Jul 27 2012)
/**
 * NOTE:
 * __TIME__ is a preprocessor macro that expands to current time (at compile time) in the form hh::mm::ss in 24 hour time (e.g. "22:29:12"), as a string.
 */
#define TOMMRO_C_UTIL_COMPILE_TIME                          __TIME__        // hh:mm:ss (Ex. 01:02:03)
/**
 * NOTE:
 * The __TIMESTAMP__ is ANSI-compliant predefined macro that contains the date/time of the last modification of the current header/source file.
 */
#define TOMMRO_C_UTIL_COMPILE_TIMESTAMP                     __TIMESTAMP__   // (Ex. Sun Sep 16 01:03:52 1973)

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)
#define TOMMRO_C_UTIL_INLINE_FUNCT                          inline
#define TOMMRO_C_UTIL_STATIC_INLINE_FUNCT                   static inline
#define TOMMRO_C_UTIL_STATIC_FORCEINLINE_FUNCT              __attribute__((always_inline)) static inline
#define TOMMRO_C_UTIL_FILE                                  __FILE__
#define TOMMRO_C_UTIL_FILE_NAME                             __FILE_NAME__
#define TOMMRO_C_UTIL_LINE                                  __LINE__
#define TOMMRO_C_UTIL_FUNCT_NAME                            __FUNCTION__
#define TOMMRO_C_UTIL_PACKED_PRE
#define TOMMRO_C_UTIL_PACKED_POST                           __attribute__((__packed__))
#define TOMMRO_C_UTIL_UNUSED_PRE                            __attribute__((unused))
#define TOMMRO_C_UTIL_UNUSED_POST
#define TOMMRO_C_UTIL_USED_PRE                              __attribute__((used))
#define TOMMRO_C_UTIL_USED_POST
#define TOMMRO_C_UTIL_WEAK_PRE                              __attribute__((weak))
#define TOMMRO_C_UTIL_WEAK_POST
#define TOMMRO_C_UTIL_SECTION_PRE(name)                     __attribute__((section(name)))
#define TOMMRO_C_UTIL_SECTION_POST(name)
#define TOMMRO_C_UTIL_ALIGN_PRE(N)                          __attribute__((aligned(N)))
#define TOMMRO_C_UTIL_ALIGN_POST(N)
#define TOMMRO_C_UTIL_NORETURN_FUNCTION_PRE                 __attribute__((noreturn))
#define TOMMRO_C_UTIL_NORETURN_FUNCTION_POST
#define TOMMRO_C_UTIL_NO_INIT_VAR_PRE(var)
#define TOMMRO_C_UTIL_NO_INIT_VAR_POST(var)                 var __attribute__((section(".noinit")))
#define TOMMRO_C_UTIL_OPTIMIZATION_NONE_PRE                 __attribute__((optimize("O0")))
#define TOMMRO_C_UTIL_OPTIMIZATION_NONE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_PRE             __attribute__((optimize("O1")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MORE_PRE        __attribute__((optimize("O2")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MORE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MOST_PRE        __attribute__((optimize("O3")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MOST_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_SIZE_PRE        __attribute__((optimize("Os")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_SIZE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FAST_PRE        __attribute__((optimize("Ofast")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FAST_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FOR_DEBUG_PRE   __attribute__((optimize("Og")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FOR_DEBUG_POST
#define TOMMRO_C_UTIL_COMPILE_DATE                          __DATE__        // Mmm dd yyyy (Jul 27 2012)
#define TOMMRO_C_UTIL_COMPILE_TIME                          __TIME__        // hh:mm:ss (Ex. 01:02:03)
#define TOMMRO_C_UTIL_COMPILE_TIMESTAMP                     __TIMESTAMP__   // (Ex. Sun Sep 16 01:03:52 1973)

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
#define TOMMRO_C_UTIL_INLINE_FUNCT                          inline
#define TOMMRO_C_UTIL_STATIC_INLINE_FUNCT                   static inline
#define TOMMRO_C_UTIL_STATIC_FORCEINLINE_FUNCT              __attribute__((always_inline)) static inline
#define TOMMRO_C_UTIL_FILE                                  __FILE__
#define TOMMRO_C_UTIL_FILE_NAME                             __FILE_NAME__
#define TOMMRO_C_UTIL_LINE                                  __LINE__
#define TOMMRO_C_UTIL_FUNCT_NAME                            __FUNCTION__
#define TOMMRO_C_UTIL_PACKED_PRE
#define TOMMRO_C_UTIL_PACKED_POST                           __attribute__((__packed__))
#define TOMMRO_C_UTIL_UNUSED_PRE                            __attribute__((unused))
#define TOMMRO_C_UTIL_UNUSED_POST
#define TOMMRO_C_UTIL_USED_PRE                              __attribute__((used))
#define TOMMRO_C_UTIL_USED_POST
#define TOMMRO_C_UTIL_WEAK_PRE                              __attribute__((weak))
#define TOMMRO_C_UTIL_WEAK_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_NONE_PRE                 __attribute__((optimize("O0")))
#define TOMMRO_C_UTIL_OPTIMIZATION_NONE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_PRE             __attribute__((optimize("O1")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MORE_PRE        __attribute__((optimize("O2")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MORE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MOST_PRE        __attribute__((optimize("O3")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MOST_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_SIZE_PRE        __attribute__((optimize("Os")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_SIZE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FAST_PRE        __attribute__((optimize("Ofast")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FAST_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FOR_DEBUG_PRE   __attribute__((optimize("Og")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FOR_DEBUG_POST
#define TOMMRO_C_UTIL_COMPILE_DATE                          __DATE__        // Mmm dd yyyy (Jul 27 2012)
#define TOMMRO_C_UTIL_COMPILE_TIME                          __TIME__        // hh:mm:ss (Ex. 01:02:03)
#define TOMMRO_C_UTIL_COMPILE_TIMESTAMP                     __TIMESTAMP__   // (Ex. Sun Sep 16 01:03:52 1973)

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)
#define TOMMRO_C_UTIL_INLINE_FUNCT                          inline
#define TOMMRO_C_UTIL_STATIC_INLINE_FUNCT                   static inline
#define TOMMRO_C_UTIL_STATIC_FORCEINLINE_FUNCT              TOMMRO_C_UTIL_STATIC_INLINE_FUNCT
#define TOMMRO_C_UTIL_FILE                                  __FILE__
#define TOMMRO_C_UTIL_FILE_NAME                             __FILE_NAME__
#define TOMMRO_C_UTIL_LINE                                  __LINE__
#define TOMMRO_C_UTIL_FUNCT_NAME                            __FUNCTION__
#define TOMMRO_C_UTIL_PACKED_PRE
#define TOMMRO_C_UTIL_PACKED_POST                           __attribute__((__packed__))
#define TOMMRO_C_UTIL_UNUSED_PRE                            __attribute__((unused))
#define TOMMRO_C_UTIL_UNUSED_POST
#define TOMMRO_C_UTIL_USED_PRE                              __attribute__((used))
#define TOMMRO_C_UTIL_USED_POST
#define TOMMRO_C_UTIL_WEAK_PRE                              __attribute__((weak))
#define TOMMRO_C_UTIL_WEAK_POST
#define TOMMRO_C_UTIL_SECTION_PRE(name)                     __attribute__((section(name)))
#define TOMMRO_C_UTIL_SECTION_POST(name)
#define TOMMRO_C_UTIL_ALIGN_PRE(N)                          __attribute__((aligned(N)))
#define TOMMRO_C_UTIL_ALIGN_POST(N)
#define TOMMRO_C_UTIL_NORETURN_FUNCTION_PRE                 __attribute__((noreturn))
#define TOMMRO_C_UTIL_NORETURN_FUNCTION_POST
#define TOMMRO_C_UTIL_NO_INIT_VAR_PRE(var)
#define TOMMRO_C_UTIL_NO_INIT_VAR_POST(var)                 var __attribute__((section(".noinit")))
#define TOMMRO_C_UTIL_OPTIMIZATION_NONE_PRE                 __attribute__((optimize("O0")))
#define TOMMRO_C_UTIL_OPTIMIZATION_NONE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_PRE             __attribute__((optimize("O1")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MORE_PRE        __attribute__((optimize("O2")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MORE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MOST_PRE        __attribute__((optimize("O3")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MOST_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_SIZE_PRE        __attribute__((optimize("Os")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_SIZE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FAST_PRE        __attribute__((optimize("Ofast")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FAST_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FOR_DEBUG_PRE   __attribute__((optimize("Og")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FOR_DEBUG_POST
#define TOMMRO_C_UTIL_COMPILE_DATE                          __DATE__        // Mmm dd yyyy (Jul 27 2012)
#define TOMMRO_C_UTIL_COMPILE_TIME                          __TIME__        // hh:mm:ss (Ex. 01:02:03)
#define TOMMRO_C_UTIL_COMPILE_TIMESTAMP                     __TIMESTAMP__   // (Ex. Sun Sep 16 01:03:52 1973)

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8) || defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC16) || defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC32)
#define TOMMRO_C_UTIL_INLINE_FUNCT                          inline
#define TOMMRO_C_UTIL_STATIC_INLINE_FUNCT                   static inline
#define TOMMRO_C_UTIL_STATIC_FORCEINLINE_FUNCT              TOMMRO_C_UTIL_STATIC_INLINE_FUNCT
#define TOMMRO_C_UTIL_FILE                                  __FILE__
#define TOMMRO_C_UTIL_FILE_NAME                             __FILE_NAME__
#define TOMMRO_C_UTIL_LINE                                  __LINE__
#define TOMMRO_C_UTIL_FUNCT_NAME                            ""
#define TOMMRO_C_UTIL_PACKED_PRE                            __pack
#define TOMMRO_C_UTIL_PACKED_POST
#define TOMMRO_C_UTIL_UNUSED_PRE                            __attribute__((unused))
#define TOMMRO_C_UTIL_UNUSED_POST
#define TOMMRO_C_UTIL_USED_PRE                              __attribute__((used))
#define TOMMRO_C_UTIL_USED_POST
#define TOMMRO_C_UTIL_WEAK_PRE                              __attribute__((weak))
#define TOMMRO_C_UTIL_WEAK_POST
#define TOMMRO_C_UTIL_SECTION_PRE(name)                     __attribute__((section(name)))
#define TOMMRO_C_UTIL_SECTION_POST(name)
#define TOMMRO_C_UTIL_ALIGN_PRE(N)                          __attribute__((aligned(N)))
#define TOMMRO_C_UTIL_ALIGN_POST(N)
#define TOMMRO_C_UTIL_NORETURN_FUNCTION_PRE                 __attribute__((noreturn))
#define TOMMRO_C_UTIL_NORETURN_FUNCTION_POST
#define TOMMRO_C_UTIL_NO_INIT_VAR_PRE(var)
#define TOMMRO_C_UTIL_NO_INIT_VAR_POST(var)                 var __attribute__((section(".noinit")))
#define TOMMRO_C_UTIL_OPTIMIZATION_NONE_PRE                 __attribute__((optimize("O0")))
#define TOMMRO_C_UTIL_OPTIMIZATION_NONE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_PRE             __attribute__((optimize("O1")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MORE_PRE        __attribute__((optimize("O2")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MORE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MOST_PRE        __attribute__((optimize("O3")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_MOST_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_SIZE_PRE        __attribute__((optimize("Os")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_SIZE_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FAST_PRE        __attribute__((optimize("Ofast")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FAST_POST
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FOR_DEBUG_PRE   __attribute__((optimize("Og")))
#define TOMMRO_C_UTIL_OPTIMIZATION_OPTIMIZE_FOR_DEBUG_POST
#define TOMMRO_C_UTIL_COMPILE_DATE                          __DATE__        // Mmm dd yyyy (Jul 27 2012)
#define TOMMRO_C_UTIL_COMPILE_TIME                          __TIME__        // hh:mm:ss (Ex. 01:02:03)
#define TOMMRO_C_UTIL_COMPILE_TIMESTAMP                     TOMMROC_UTIL_CONCAT_TWO_ELEM_WITH_EXPAND(TOMMRO_C_UTIL_COMPILE_DATE, TOMMRO_C_UTIL_COMPILE_TIME)

#endif


/**
 * Base type sizes.
 */
#define TOMMROC_UTIL_INT_SIZE                               (sizeof(int))
#define TOMMROC_UTIL_BOOL_SIZE                              (sizeof(bool))              // 1 byte
#define TOMMROC_UTIL_CHAR_SIZE                              (sizeof(char))              // 1 byte
#define TOMMROC_UTIL_U8_SIZE                                (sizeof(uint8_t))           // 1 byte
#define TOMMROC_UTIL_U16_SIZE                               (sizeof(uint16_t))          // 2 byte
#define TOMMROC_UTIL_U24_SIZE                               (3 * TOMMROC_UTIL_U8_SIZE)  // 3 byte
#define TOMMROC_UTIL_U32_SIZE                               (sizeof(uint32_t))          // 4 byte
#define TOMMROC_UTIL_U64_SIZE                               (sizeof(uint64_t))          // 8 byte
#define TOMMROC_UTIL_I8_SIZE                                (sizeof(int8_t))            // 1 byte
#define TOMMROC_UTIL_I16_SIZE                               (sizeof(int16_t))           // 2 byte
#define TOMMROC_UTIL_I24_SIZE                               (3 * TOMMROC_UTIL_I8_SIZE)  // 3 byte
#define TOMMROC_UTIL_I32_SIZE                               (sizeof(int32_t))           // 4 byte
#define TOMMROC_UTIL_I64_SIZE                               (sizeof(int64_t))           // 8 byte
#define TOMMROC_UTIL_FLOAT_SIZE                             (sizeof(float))             // 4 byte
#define TOMMROC_UTIL_PTR_SIZE                               (sizeof(void*))
#define TOMMROC_UTIL_FUNCT_PTR_SIZE                         (sizeof(void (*)(void)))
#define TOMMROC_UTIL_ENUM_SIZE                              (sizeof(tommRoC_util_faked_enum_t))

/**
 * Macro to retrieve the element amount of an array.
 */
#define TOMMROC_UTIL_ARR_EAMOUNT(arr)                       (sizeof(arr) / sizeof(arr[0]))

/**
 * Macro to retrieve the string length starting from string array declaration.
 */
#define TOMMROC_UTIL_STRING_ARR_LENGTH(str)                 (sizeof(str) - TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)

/*
 * Concatenate preprocessor tokens without expanding macro definitions
 * (however, if invoked from a macro, macro arguments are expanded).
 */
#define TOMMROC_UTIL_CONCAT_TWO_ELEM_NO_EXPAND(a, b)            a ## b
#define TOMMROC_UTIL_CONCAT_THREE_ELEM_NO_EXPAND(a, b, c)       a ## b ## c
#define TOMMROC_UTIL_CONCAT_FOUR_ELEM_NO_EXPAND(a, b, c, d)     a ## b ## c ## d
#define TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(a, b, c, d, e)  a ## b ## c ## d ## e

/*
 * Concatenate preprocessor tokens after macro-expanding them.
 */
#define TOMMROC_UTIL_CONCAT_TWO_ELEM_WITH_EXPAND(a, b)              TOMMROC_UTIL_CONCAT_TWO_ELEM_NO_EXPAND((a), (b))
#define TOMMROC_UTIL_CONCAT_THREE_ELEM_WITH_EXPAND(a, b, c)         TOMMROC_UTIL_CONCAT_THREE_ELEM_NO_EXPAND((a), (b), (c))
#define TOMMROC_UTIL_CONCAT_FOUR_ELEM_WITH_EXPAND(a, b, c, d)       TOMMROC_UTIL_CONCAT_FOUR_ELEM_NO_EXPAND((a), (b), (c), (d))
#define TOMMROC_UTIL_CONCAT_FIVE_ELEM_WITH_EXPAND(a, b, c, d, e)    TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND((a), (b), (c), (d), (e))

/**
 * Macro to convert macro name into a string.
 */
#define TOMMROC_UTIL_TO_STRING(str)                         #str

/**
 * Macro to convert the content of a define to a string.
 *
 * Please note that the intermediate step is required to ensure the define
 * is properly replaced with its content by the preprocessor.
 */
#define TOMMROC_UTIL_DEFINE_TO_STRING(def)                  TOMMROC_UTIL_TO_STRING(def)

/**
 * Macro to add leading "0x" to macro value.
 */
#define TOMMROC_UTIL_TO_HEX(val)                            0x##val

/**
 * Macro to be used to use C Designated Initializers - define the init section for an array.
 *
 * startIdx                     array variable start index element.
 * endIdx                       array variable end index element.
 * elemInitValue                value to assign to every element.
 */
#define TOMMROC_UTIL_DESIGNATED_SECTION(startIdx, endIdx, elemInitValue)        [ startIdx ... endIdx ] = elemInitValue

/**
 * Macro to be used to use C Designated Initializers - define and array as init section.
 *
 * startIdx                     array variable start index element.
 * endIdx                       array variable end index element.
 * elemInitValue                value to assign to every element.
 */
#define TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(startIdx, endIdx, elemInitValue)  { TOMMROC_UTIL_DESIGNATED_SECTION(startIdx, endIdx, elemInitValue) }

/**
 * Macro to be used to use C Designated Initializers for an array.
 *
 * varType                      array base variable type.
 * varName                      array variable name.
 * elemAmount                   array variable element amount.
 * elemInitValue                value to assign to every array element.
 */
#define TOMMROC_UTIL_DESIGNATED_INIT_ARRAY(                                     \
        varType,                                                                \
        varName,                                                                \
        elemAmount,                                                             \
        elemInitValue)                                                          \
        varType varName[elemAmount] =                                           \
        {                                                                       \
            TOMMROC_UTIL_DESIGNATED_SECTION(0, elemAmount - 1, elemInitValue)   \
        }

/**
 * Macro to be used to use C Designated Initializers for an array - two sections version.
 *
 * varType                      array base variable type.
 * varName                      array variable name.
 * sect1ElemAmount              first section array variable element amount.
 * sect1ElemInitValue           first section value to assign to every array element.
 * sect2ElemAmount              second section array variable element amount.
 * sect2ElemInitValue           second section value to assign to every array element.
 */
#define TOMMROC_UTIL_DESIGNATED_INIT_ARRAY_TWO_SECTIONS(                                                                    \
        varType,                                                                                                            \
        varName,                                                                                                            \
        sect1ElemAmount,                                                                                                    \
        sect1ElemInitValue,                                                                                                 \
        sect2ElemAmount,                                                                                                    \
        sect2ElemInitValue)                                                                                                 \
        varType varName[sect1ElemAmount + sect2ElemAmount] =                                                                \
        {                                                                                                                   \
            TOMMROC_UTIL_DESIGNATED_SECTION(0, sect1ElemAmount - 1, sect1ElemInitValue),                                    \
            TOMMROC_UTIL_DESIGNATED_SECTION(sect1ElemAmount, sect1ElemAmount + sect2ElemAmount - 1, sect2ElemInitValue)     \
        }

/**
 * Macro to be used to use C Designated Initializers for an array - three sections version.
 *
 * varType                      array base variable type.
 * varName                      array variable name.
 * sect1ElemAmount              first section array variable element amount.
 * sect1ElemInitValue           first section value to assign to every array element.
 * sect2ElemAmount              second section array variable element amount.
 * sect2ElemInitValue           second section value to assign to every array element.
 * sect3ElemAmount              third section array variable element amount.
 * sect3ElemInitValue           third section value to assign to every array element.
 */
#define TOMMROC_UTIL_DESIGNATED_INIT_ARRAY_THREE_SECTIONS(                                                                                                  \
        varType,                                                                                                                                            \
        varName,                                                                                                                                            \
        sect1ElemAmount,                                                                                                                                    \
        sect1ElemInitValue,                                                                                                                                 \
        sect2ElemAmount,                                                                                                                                    \
        sect2ElemInitValue,                                                                                                                                 \
        sect3ElemAmount,                                                                                                                                    \
        sect3ElemInitValue)                                                                                                                                 \
        varType varName[sect1ElemAmount + sect2ElemAmount + sect3ElemAmount] =                                                                              \
        {                                                                                                                                                   \
            TOMMROC_UTIL_DESIGNATED_SECTION(0, sect1ElemAmount - 1, sect1ElemInitValue),                                                                    \
            TOMMROC_UTIL_DESIGNATED_SECTION(sect1ElemAmount, sect1ElemAmount + sect2ElemAmount - 1, sect2ElemInitValue),                                    \
            TOMMROC_UTIL_DESIGNATED_SECTION(sect1ElemAmount + sect2ElemAmount, sect1ElemAmount + sect2ElemAmount + sect3ElemAmount - 1, sect3ElemInitValue) \
        }

/**
 * Macro to be used to avoid compile warning on not used parameter.
 */
#define TOMMROC_UTIL_UNUSED_PARAM(param)                    ((void) (param))

/**
 * Macro to define/init variables.
 */
#define TOMMROC_UTIL_EMPTY_VARIABLE(type)                               \
        TOMMROC_UTIL_CONCAT_THREE_ELEM_NO_EXPAND(__EMPTY_, type, __)

#define TOMMROC_UTIL_MANAGE_EXTENDED_FIRST_EXECUTE(                     \
        onNotFirstExecuteCodeReturn,                                    \
        onFirstExecuteCallFunct)                                        \
                                                                        \
        do {                                                            \
            static bool firstExecute = true;                            \
                                                                        \
            if (!firstExecute) {                                        \
                return onNotFirstExecuteCodeReturn;                     \
            }                                                           \
                                                                        \
            onFirstExecuteCallFunct;                                    \
                                                                        \
            firstExecute = false;                                       \
        } while (0)

#define TOMMROC_UTIL_MANAGE_FIRST_EXECUTE(onNotFirstExecuteCodeReturn)  \
        do {                                                            \
            static bool firstExecute = true;                            \
                                                                        \
            if (!firstExecute) {                                        \
                return onNotFirstExecuteCodeReturn;                     \
            }                                                           \
                                                                        \
            firstExecute = false;                                       \
        } while (0)


/**
 * Block code no result void function execution
 * NOTE: no result return is done
 */
#define TOMMROC_UTIL_BLOCK_CODE_VOID_FUNCT(                             \
        onEnterCallFunctWithParam,                                      \
        onExitCallFunctWithParam,                                       \
        callFunctWithParam)                                             \
                                                                        \
        do {                                                            \
            onEnterCallFunctWithParam;                                  \
            callFunctWithParam;                                         \
            onExitCallFunctWithParam;                                   \
        } while (0)

/**
 * Block code with result function execution
 */
#define TOMMROC_UTIL_BLOCK_CODE_WITH_RESULT_FUNCT(                      \
        resultVarType,                                                  \
        onEnterCallFunctWithParam,                                      \
        onExitCallFunctWithParam,                                       \
        callFunctWithParam)                                             \
                                                                        \
        do {                                                            \
            resultVarType callFunctWithParamResult;                     \
                                                                        \
            onEnterCallFunctWithParam;                                  \
            callFunctWithParamResult = callFunctWithParam;              \
            onExitCallFunctWithParam;                                   \
                                                                        \
            return callFunctWithParamResult;                            \
        } while (0)

/**
 * Block code tommRoC error result function execution
 */
#define TOMMROC_UTIL_BLOCK_CODE_TOMMROC_LIB_FUNCT(                      \
        onEnterCallFunctWithParam,                                      \
        onExitCallFunctWithParam,                                       \
        callFunctWithParam)                                             \
        TOMMROC_UTIL_BLOCK_CODE_WITH_RESULT_FUNCT(                      \
                tommRoC_err_enum_t,                                     \
                onEnterCallFunctWithParam,                              \
                onExitCallFunctWithParam,                               \
                callFunctWithParam)


/**
 * Synchronized (guarded) tommRoC error result function execution.
 */
#define TOMMROC_UTIL_SYNCHRO_TOMMROC_LIB_FUNCT(guardPtr, callFunctWithParam)    \
        TOMMROC_GUARD_SYNCHRO_TOMMROC_LIB_FUNCT(guardPtr, callFunctWithParam)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of generic bit status.
typedef enum {

    /**
     * Low level.
     */
    TOMMRO_C_UTIL_LOW_LEVEL = 0,

    /**
     * High level.
     */
    TOMMRO_C_UTIL_HIGH_LEVEL,

} tommRoC_util_bit_status_enum_t;


// Enumeration of number format.
typedef enum {

    /**
     * Decimal number format.
     */
    TOMMRO_C_UTIL_DECIMAL_FORMAT = 0,

    /**
     * Hexadecimal number format.
     */
    TOMMRO_C_UTIL_HEXADECIMAL_FORMAT,

    /**
     * Decimal zero padded number format [2/3/4/5 digits].
     */
    TOMMRO_C_UTIL_2_DIGIT_ZERO_PADDED_DECIMAL_FORMAT,
    TOMMRO_C_UTIL_3_DIGIT_ZERO_PADDED_DECIMAL_FORMAT,
    TOMMRO_C_UTIL_4_DIGIT_ZERO_PADDED_DECIMAL_FORMAT,
    TOMMRO_C_UTIL_5_DIGIT_ZERO_PADDED_DECIMAL_FORMAT,

} tommRoC_util_number_format_enum_t;


// Enumeration of generic disabled/enabled status.
typedef enum {

    /**
     * Specific functionality disabled
     */
    TOMMRO_C_UTIL_DISABLED = 0,

    /**
     * Specific functionality enabled
     */
    TOMMRO_C_UTIL_ENABLED,

} tommRoC_util_enabled_status_enum_t;


// Faked enumeration used just to get size of enumeration for environment.
typedef enum {

    TOMMRO_C_UTIL_FAKED_ENUM = 0,

} tommRoC_util_faked_enum_t;


// Faked function pointer used just to get size of function pointer for environment.
typedef void (*tommRoC_util_funct_ptr_t)(void);

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* Memory functs */

/**
 * Check if two memory areas are overlapping.
 *
 * param[in]        ptr1                    first memory pointer.
 * param[in]        ptr2                    second memory pointer.
 * param[in]        sizeByte                size [byte] of memory area.
 *
 * return bool
 */
bool tommRoCUtilMemIsOverlapping(
        const   void*       const   ptr1,
        const   void*       const   ptr2,
        const   uint16_t            sizeByte);

/**
 * Copies "sizeByte" bytes from source pointer directly to destination pointer.
 * The underlying type of the objects are irrelevant for this function; the result is a binary copy of the data.
 * To avoid overflows, the size of the both arrays shall be at least sizeByte bytes, and should not overlap
 * (for overlapping memory blocks, tommRoCUtilMemMove is a safer approach).
 *
 * NOTE: if size is zero, SUCCESS result is returned.
 *
 * param[in/out]    destBufferPtr           destination memory buffer pointer.
 * param[in]        srcBufferPtr            source memory buffer pointer.
 * param[in]        sizeByte                size [byte] to be copied.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilMemCopy(
                void*       const   destBufferPtr,
        const   void*       const   srcBufferPtr,
        const   uint16_t            sizeByte);

/**
 * Copies "sizeByte" bytes from source pointer directly to destination pointer.
 * Version "safe" - with check of destination and source buffer size in order to avoid possible buffer overflows.
 * The underlying type of the objects are irrelevant for this function; the result is a binary copy of the data.
 * To avoid overflows, arrays should not overlap (for overlapping memory blocks, tommRoCUtilMemMoveSafe is a safer approach).
 *
 * NOTE: if size is zero, SUCCESS result is returned.
 *
 * param[in/out]    destBufferPtr           destination memory buffer pointer.
 * param[in]        destBufferSizeByte      destination memory buffer size [byte].
 * param[in]        srcBufferPtr            source memory buffer pointer.
 * param[in]        srcBufferSizeByte       source memory buffer size [byte].
 * param[in]        sizeByte                size [byte] to be copied.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilMemCopySafe(
                void*       const   destBufferPtr,
        const   uint32_t            destBufferSizeByte,
        const   void*       const   srcBufferPtr,
        const   uint32_t            srcBufferSizeByte,
        const   uint16_t            sizeByte);

/**
 * Compares the first "size" bytes of the block of memory pointed by ptr1 to the first "size" bytes pointed by ptr2.
 *
 * param[in]        ptr1                    first memory block pointer.
 * param[in]        ptr2                    second memory block pointer.
 * param[in]        sizeByte                size [byte] to compare.
 *
 * NOTE: if size is zero, SUCCESS result is returned.
 *
 * return tommRoC_err_enum_t
 *          TOMMRO_C_ERR_SUCCESS                                    -> compare success (all compared bytes are matching).
 *          TOMMRO_C_COMPARE_PARAM_1_LOWER_THAN_PARAM_2_ERR         -> param ptr1 is lower than param ptr2.
 *          TOMMRO_C_COMPARE_PARAM_1_GREATER_THAN_PARAM_2_ERR       -> param ptr1 is greater than param ptr2.
 *          TOMMRO_C_NULL_PARAM_ERR                                 -> NULL param error.
 *          TOMMRO_C_PARAM_ERR                                      -> param error.
 */
tommRoC_err_enum_t tommRoCUtilMemCompare(
        const   void*       const   ptr1,
        const   void*       const   ptr2,
        const   uint16_t            sizeByte);

/**
 * Copies "sizeByte" bytes from source pointer directly to destination pointer.
 * Copying takes place as if an intermediate buffer were used, allowing the destination and source to overlap.
 * The underlying type of the objects are irrelevantsize for this function; the result is a binary copy of the data.
 * To avoid overflows, the size of the both arrays shall be at least sizeByte bytes.
 *
 * NOTE: if size is zero, SUCCESS result is returned.
 *
 * param[in/out]    destBufferPtr           destination memory buffer pointer.
 * param[in]        srcBufferPtr            source memory buffer pointer.
 * param[in]        sizeByte                size [byte] to be copied.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilMemMove(
                void*       const   destBufferPtr,
        const   void*       const   srcBufferPtr,
        const   uint16_t            sizeByte);

/**
 * Copies "sizeByte" bytes from source pointer directly to destination pointer.
 * Version "safe" - with check of destination and source buffer size in order to avoid possible buffer overflows.
 * Copying takes place as if an intermediate buffer were used, allowing the destination and source to overlap.
 * The underlying type of the objects are irrelevant for this function; the result is a binary copy of the data.
 * To avoid overflows, the size of the both arrays shall be at least sizeByte bytes.
 *
 * NOTE: if size is zero, SUCCESS result is returned.
 *
 * param[in/out]    destBufferPtr           destination memory buffer pointer.
 * param[in]        destBufferSizeByte      destination memory buffer size [byte].
 * param[in]        srcBufferPtr            source memory buffer pointer.
 * param[in]        srcBufferSizeByte       source memory buffer size [byte].
 * param[in]        sizeByte                size [byte] to be copied.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilMemMoveSafe(
                void*       const   destBufferPtr,
        const   uint32_t            destBufferSizeByte,
        const   void*       const   srcBufferPtr,
        const   uint32_t            srcBufferSizeByte,
        const   uint16_t            sizeByte);

/**
 * Sets the first "size" bytes of the block of memory pointed to the specified value (interpreted as uint8_t).
 *
 * NOTE: if size is zero, SUCCESS result is returned.
 *
 * param[in/out]    destBufferPtr           destination memory buffer pointer.
 * param[in]        value                   byte value data.
 * param[in]        sizeByte                size [byte] to be set.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilMemSet(
                void*       const   destBufferPtr,
        const   uint8_t             value,
        const   uint16_t            sizeByte);

/**
 * Compares the first "size" bytes of the block of memory pointed by ptr with specified value (interpreted as uint8_t).
 *
 * param[in]        ptr                     memory block pointer.
 * param[in]        value                   byte value data.
 * param[in]        sizeByte                size [byte] to be compared.
 *
 * NOTE: if size is zero, SUCCESS result is returned.
 *
 * return tommRoC_err_enum_t
 *          TOMMRO_C_ERR_SUCCESS                                    -> compare success (all compared bytes are matching).
 *          TOMMRO_C_COMPARE_PARAM_1_LOWER_THAN_PARAM_2_ERR         -> found a byte that is lower than value.
 *          TOMMRO_C_COMPARE_PARAM_1_GREATER_THAN_PARAM_2_ERR       -> found a byte that is greater than value.
 *          TOMMRO_C_NULL_PARAM_ERR                                 -> NULL param error.
 *          TOMMRO_C_PARAM_ERR                                      -> param error.
 */
tommRoC_err_enum_t tommRoCUtilMemCheck(
        const   void*       const   ptr,
        const   uint8_t             value,
        const   uint16_t            sizeByte);

/**
 * Swap (copy in inverted order) a memory area.
 *
 * If destination and source pointers are different, copies "size" swapped bytes from source pointer directly to destination pointer.
 * If destination and source pointers are equal, swap the memory area.
 *
 * NOTE: if size is zero, SUCCESS result is returned.
 *
 * param[in/out]    destinationPtr          destination memory pointer.
 * param[in]        sourcePtr               source memory pointer.
 * param[in]        sizeByte                size [byte] to be copied.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilMemSwap(
                void*       const   destinationPtr,
        const   void*       const   sourcePtr,
        const   uint16_t            sizeByte);


/******************* Search functs */

/**
 * Starting from left/right, get index of first occurrence of a buffer inside another buffer.
 *
 * param[in]        bufferPtr               buffer pointer.
 * param[in]        bufferSize              buffer size [byte].
 * param[in]        toFindPtr               to find buffer pointer.
 * param[in]        toFindSize              to find buffer size [byte].
 * param[in]        searchStepSize          on search, increment step size [byte].
 * param[out]       indexPtr                index found.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilSearchFromLeft(
        const   void*       const   bufferPtr,
        const   uint16_t            bufferSize,
        const   void*       const   toFindPtr,
        const   uint16_t            toFindSize,
        const   uint16_t            searchStepSize,
                uint16_t*   const   indexPtr);

tommRoC_err_enum_t tommRoCUtilSearchFromRight(
        const   void*       const   bufferPtr,
        const   uint16_t            bufferSize,
        const   void*       const   toFindPtr,
        const   uint16_t            toFindSize,
        const   uint16_t            searchStepSize,
                uint16_t*   const   indexPtr);

/**
 * Starting from left/right, and skipping some data, get index of first occurrence of a buffer inside another buffer.
 *
 * param[in]        bufferPtr               buffer pointer.
 * param[in]        bufferSize              buffer size [byte].
 * param[in]        skipSize                data to skip on searching size [byte].
 * param[in]        toFindPtr               to find buffer pointer.
 * param[in]        toFindSize              to find buffer size [byte].
 * param[in]        searchStepSize          on search, increment step size [byte].
 * param[out]       indexPtr                index found.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilSearchFromLeftSkip(
        const   void*       const   bufferPtr,
        const   uint16_t            bufferSize,
        const   uint16_t            skipSize,
        const   void*       const   toFindPtr,
        const   uint16_t            toFindSize,
        const   uint16_t            searchStepSize,
                uint16_t*   const   indexPtr);

tommRoC_err_enum_t tommRoCUtilSearchFromRightSkip(
        const   void*       const   bufferPtr,
        const   uint16_t            bufferSize,
        const   uint16_t            skipSize,
        const   void*       const   toFindPtr,
        const   uint16_t            toFindSize,
        const   uint16_t            searchStepSize,
                uint16_t*   const   indexPtr);


/******************* Split functs */

/**
 * Split (get index of all occurrences) of a buffer based on another buffer.
 *
 * param[in]        bufferPtr               to split buffer pointer.
 * param[in]        bufferSize              to split buffer size [byte].
 * param[in]        toFindPtr               to find (used to split) buffer pointer.
 * param[in]        toFindSize              to find (used to split) buffer size [byte].
 * param[out]       indexBufferPtr          index buffer found pointer.
 * param[in]        indexBufferAmount       index buffer found max element amount.
 * param[out]       indexBufferAmountPtr    index buffer found element amount pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilSplit(
        const   void*       const   bufferPtr,
        const   uint16_t            bufferSize,
        const   void*       const   toFindPtr,
        const   uint16_t            toFindSize,
                uint16_t*   const   indexBufferPtr,
        const   uint16_t            indexBufferAmount,
                uint16_t*   const   indexBufferAmountPtr);


/******************* Buffer array functs */

/**
 * Append uint8_t/int8_t in pointed memory and return next pointer.
 *
 * param[in]        bufferInPtr             input memory position pointer.
 * param[in]        bufferInSize            input buffer size [byte].
 * param[in]        data                    uint8_t/int8_t to store.
 * param[out]       bufferOutPtr            next memory position pointer.
 * param[out]       bufferOutSizePtr        buffer output size [byte] pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilBufferAppendU8(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        const   uint8_t             data,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferAppendI8(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        const   int8_t              data,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

/**
 * Append uint16_t/int16_t in pointed memory and return next pointer.
 *
 * param[in]        bufferInPtr             input memory position pointer.
 * param[in]        bufferInSize            input buffer size [byte].
 * param[in]        data                    uint16_t/int16_t to store.
 * param[out]       bufferOutPtr            next memory position pointer.
 * param[out]       bufferOutSizePtr        buffer output size [byte] pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilBufferAppendU16MSB(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        const   uint16_t            data,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferAppendU16LSB(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        const   uint16_t            data,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferAppendI16MSB(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        const   int16_t             data,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferAppendI16LSB(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        const   int16_t             data,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

/**
 * Append uint32_t/int32_t in pointed memory and return next pointer.
 *
 * param[in]        bufferInPtr             input memory position pointer.
 * param[in]        bufferInSize            input buffer size [byte].
 * param[in]        data                    uint32_t/int32_t to store.
 * param[out]       bufferOutPtr            next memory position pointer.
 * param[out]       bufferOutSizePtr        buffer output size [byte] pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilBufferAppendU32MSB(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        const   uint32_t            data,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferAppendU32LSB(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        const   uint32_t            data,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferAppendI32MSB(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        const   int32_t             data,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferAppendI32LSB(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        const   int32_t             data,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

/**
 * Append uint64_t/int64_t in pointed memory and return next pointer.
 *
 * param[in]        bufferInPtr             input memory position pointer.
 * param[in]        bufferInSize            input buffer size [byte].
 * param[in]        data                    uint64_t/int64_t to store.
 * param[out]       bufferOutPtr            next memory position pointer.
 * param[out]       bufferOutSizePtr        buffer output size [byte] pointer.
 *
 * return tommRoC_err_enum_t
 */
#if defined (TOMMROC_INT_UINT64_SUPPORTED)
tommRoC_err_enum_t tommRoCUtilBufferAppendU64MSB(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        const   uint64_t            data,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferAppendU64LSB(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        const   uint64_t            data,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);
#endif

#if defined (TOMMROC_INT_INT64_SUPPORTED)
tommRoC_err_enum_t tommRoCUtilBufferAppendI64MSB(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        const   int64_t             data,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferAppendI64LSB(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        const   int64_t             data,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);
#endif

/**
 * Append float in pointed memory and return next pointer.
 *
 * param[in]        bufferInPtr             input memory position pointer.
 * param[in]        bufferInSize            input buffer size [byte].
 * param[in]        data                    float to store.
 * param[out]       bufferOutPtr            next memory position pointer.
 * param[out]       bufferOutSizePtr        buffer output size [byte] pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilBufferAppendFloatMSB(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        const   float               data,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferAppendFloatLSB(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        const   float               data,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

/**
 * Append an array in pointed memory and return next pointer.
 *
 * param[in]        bufferInPtr             input memory position pointer.
 * param[in]        bufferInSize            input buffer size [byte].
 * param[in]        dataBufferPtr           data buffer pointer.
 * param[in]        dataBufferLen           data buffer pointer size [byte]
 * param[out]       bufferOutPtr            next memory position pointer.
 * param[out]       bufferOutSizePtr        buffer output size [byte] pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilBufferAppendArray(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        const   void*       const   dataBufferPtr,
        const   uint16_t            dataBufferSize,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

/**
 * Append a string in pointed memory and return next pointer.
 * NOTE: string terminator char ('\0') not included.
 *
 * param[in]        bufferInPtr             input memory position pointer.
 * param[in]        bufferInSize            input buffer size [byte].
 * param[in]        stringPtr               string ptr [NOTE: string have to be terminated with '\0'; '\0' char is not appended].
 * param[out]       bufferOutPtr            next memory position pointer.
 * param[out]       bufferOutSizePtr        buffer output size [byte] pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilBufferAppendString(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        const   char*       const   stringPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

/**
 * Append a string in pointed memory and return next pointer.
 * NOTE: string terminator char ('\0') included.
 *
 * param[in]        bufferInPtr             input memory position pointer.
 * param[in]        bufferInSize            input buffer size [byte].
 * param[in]        stringPtr               string ptr [NOTE: string have to be terminated with '\0'; '\0' char is not appended].
 * param[out]       bufferOutPtr            next memory position pointer.
 * param[out]       bufferOutSizePtr        buffer output size [byte] pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilBufferAppendStringTerm(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        const   char*       const   stringPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

/**
 * Append a pointer in pointed memory and return next pointer.
 *
 * param[in]        bufferInPtr             input memory position pointer.
 * param[in]        bufferInSize            input buffer size [byte].
 * param[in]        pointer                 pointer.
 * param[out]       bufferOutPtr            next memory position pointer.
 * param[out]       bufferOutSizePtr        buffer output size [byte] pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilBufferAppendPtr(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        const   void*       const   pointer,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

/**
 * Append a funct pointer in pointed memory and return next pointer.
 *
 * param[in]        bufferInPtr             input memory position pointer.
 * param[in]        bufferInSize            input buffer size [byte].
 * param[in]        pointer                 pointer.
 * param[out]       bufferOutPtr            next memory position pointer.
 * param[out]       bufferOutSizePtr        buffer output size [byte] pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilBufferAppendFunctPtr(
                void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        tommRoC_util_funct_ptr_t    functPointer,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

/**
 * Extract uint8_t/int8_t from pointed memory and return next pointer.
 *
 * param[in]        bufferInPtr             input memory position pointer.
 * param[in]        bufferInSize            input buffer size [byte].
 * param[out]       dataPtr                 uint8_t/int8_t data read pointer.
 * param[out]       bufferOutPtr            next memory position pointer.
 * param[out]       bufferOutSizePtr        buffer output size [byte] pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilBufferExtractU8(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                uint8_t*    const   dataPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferExtractI8(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                int8_t*     const   dataPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

/**
 * Extract uint16_t/int16_t from pointed memory and return next pointer.
 *
 * param[in]        bufferInPtr             input memory position pointer.
 * param[in]        bufferInSize            input buffer size [byte].
 * param[out]       dataPtr                 uint16_t/int16_t data read pointer.
 * param[out]       bufferOutPtr            next memory position pointer.
 * param[out]       bufferOutSizePtr        buffer output size [byte] pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilBufferExtractU16MSB(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                uint16_t*   const   dataPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferExtractU16LSB(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                uint16_t*   const   dataPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferExtractI16MSB(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                int16_t*    const   dataPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferExtractI16LSB(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                int16_t*    const   dataPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

/**
 * Extract uint32_t/int32_t from pointed memory and return next pointer.
 *
 * param[in]        bufferInPtr             input memory position pointer.
 * param[in]        bufferInSize            input buffer size [byte].
 * param[out]       dataPtr                 uint32_t/int32_t data read pointer.
 * param[out]       bufferOutPtr            next memory position pointer.
 * param[out]       bufferOutSizePtr        buffer output size [byte] pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilBufferExtractU32MSB(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                uint32_t*   const   dataPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferExtractU32LSB(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                uint32_t*   const   dataPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferExtractI32MSB(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                int32_t*    const   dataPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferExtractI32LSB(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                int32_t*    const   dataPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

/**
 * Extract uint32_t/int32_t as 24-bit data from pointed memory and return next pointer.
 * NOTE: only 3 bytes are extracted from buffer and converted to uint32_t/int32_t.
 *
 * param[in]        bufferInPtr             input memory position pointer.
 * param[in]        bufferInSize            input buffer size [byte].
 * param[out]       dataPtr                 uint32_t/int32_t data read pointer.
 * param[out]       bufferOutPtr            next memory position pointer.
 * param[out]       bufferOutSizePtr        buffer output size [byte] pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilBufferExtractU32AsU24MSB(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                uint32_t*   const   dataPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferExtractU32AsU24LSB(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                uint32_t*   const   dataPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferExtractI32AsI24MSB(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                int32_t*    const   dataPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferExtractI32AsI24LSB(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                int32_t*    const   dataPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

/**
 * Extract uint64_t/int64_t from pointed memory and return next pointer.
 *
 * param[in]        bufferInPtr             input memory position pointer.
 * param[in]        bufferInSize            input buffer size [byte].
 * param[out]       dataPtr                 uint64_t/int64_t data read pointer.
 * param[out]       bufferOutPtr            next memory position pointer.
 * param[out]       bufferOutSizePtr        buffer output size [byte] pointer.
 *
 * return tommRoC_err_enum_t
 */
#if defined (TOMMROC_INT_UINT64_SUPPORTED)
tommRoC_err_enum_t tommRoCUtilBufferExtractU64MSB(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                uint64_t*   const   dataPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferExtractU64LSB(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                uint64_t*   const   dataPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);
#endif

#if defined (TOMMROC_INT_INT64_SUPPORTED)
tommRoC_err_enum_t tommRoCUtilBufferExtractI64MSB(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                int64_t*    const   dataPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferExtractI64LSB(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                int64_t*    const   dataPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);
#endif

/**
 * Extract float from pointed memory and return next pointer.
 *
 * param[in]        bufferInPtr             input memory position pointer.
 * param[in]        bufferInSize            input buffer size [byte].
 * param[out]       dataPtr                 float data read pointer.
 * param[out]       bufferOutPtr            next memory position pointer.
 * param[out]       bufferOutSizePtr        buffer output size [byte] pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilBufferExtractFloatMSB(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                float*      const   dataPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

tommRoC_err_enum_t tommRoCUtilBufferExtractFloatLSB(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                float*      const   dataPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

/**
 * Extract an array from pointed memory and return next pointer.
 *
 * param[in]        bufferInPtr             input memory position pointer.
 * param[in]        bufferInSize            input buffer size [byte].
 * param[out]       dataBufferPtr           output data buffer pointer.
 * param[in]        dataBufferLen           output data buffer length.
 * param[out]       bufferOutPtr            next memory position pointer.
 * param[out]       bufferOutSizePtr        buffer output size [byte] pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilBufferExtractArray(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                void*       const   dataBufferPtr,
        const   uint16_t            dataBufferLen,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

/**
 * Extract a pointer from pointed memory and return next pointer.
 *
 * param[in]        bufferInPtr             input memory position pointer.
 * param[in]        bufferInSize            input buffer size [byte].
 * param[out]       pointerPtr              pointer data read pointer.
 * param[out]       bufferOutPtr            next memory position pointer.
 * param[out]       bufferOutSizePtr        buffer output size [byte] pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilBufferExtractPtr(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
                void**      const   pointerPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);

/**
 * Extract a function pointer from pointed memory and return next pointer.
 *
 * param[in]        bufferInPtr             input memory position pointer.
 * param[in]        bufferInSize            input buffer size [byte].
 * param[out]       functPointerPtr         function pointer data read pointer.
 * param[out]       bufferOutPtr            next memory position pointer.
 * param[out]       bufferOutSizePtr        buffer output size [byte] pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilBufferExtractFunctPtr(
        const   void*       const   bufferInPtr,
        const   uint16_t            bufferInSize,
        tommRoC_util_funct_ptr_t*   functPointerPtr,
                void**      const   bufferOutPtr,
                uint16_t*   const   bufferOutSizePtr);


/******************* Pseudo random number generation functs */

/**
 * Init the random number generator.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilPrngInit(void);

/**
 * Close the random number generator.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilPrngClose(void);

/**
 * Add seed to the random number generator.
 *
 * param[in]        seedDataPtr             PRNG seed data.
 * param[in]        seedDataSize            PRNG seed data size.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUtilPrngAddSeed(
        const   void*       const   seedDataPtr,
        const   uint8_t             seedDataSize);

/**
 * Get a 8-bit pseudo random number.
 *
 * return uint8_t
 */
uint8_t tommRoCUtilU8Prng(void);

/**
 * Get a 16-bit pseudo random number.
 *
 * return uint16_t
 */
uint16_t tommRoCUtilU16Prng(void);

/**
 * Get a 32-bit pseudo random number.
 *
 * return uint32_t
 */
uint32_t tommRoCUtilU32Prng(void);


/******************* CLI util functs */

/**
 * Return the number of parameters that follow the command name.
 *
 * param[in]        commandStrPtr           command string pointer [NOTE: string have to be terminated with '\0'].
 *
 * return int8_t
 */
int8_t tommRoCUtilCLIGetNumberOfParameters(const char* const commandStrPtr);

/**
 * Return a pointer to a parameter index in command string.
 *
 * param[in]        commandStrPtr           command string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        wantedParamIdx          wanted parameter index [NOTE: 1 for first parameter; 2 for second parameter;...].
 * param[out]       paramStrLenPtr          wanted parameter string length.
 * return const char*
 */
const char* tommRoCUtilCLIGetParameter(const char* const commandStrPtr, const uint32_t wantedParamIdx, uint32_t* const paramStrLenPtr);

/**
 * @}
 */

#endif
