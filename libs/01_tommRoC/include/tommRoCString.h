
#ifndef TOMMROC_STRING_H_
#define TOMMROC_STRING_H_

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
 * @defgroup tommRoCString tommRoCString
 *
 * @brief  TommRoC library string module
 * @author TommRo Software Department
 *
 * This module is providing string functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCEnv.h"
#include "tommRoCUtil.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

#define TOMMROC_STRING_NULL_TERMINATOR_CHAR                     ('\0')
#define TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE                (TOMMROC_UTIL_CHAR_SIZE)

#define TOMMROC_STRING_SPACE_CHAR                               (' ')
#define TOMMROC_STRING_SPACE_CHAR_SIZE                          (TOMMROC_UTIL_CHAR_SIZE)
#define TOMMROC_STRING_SPACE_STR                                " "
#define TOMMROC_STRING_SPACE_STR_SIZE                           (sizeof(TOMMROC_STRING_SPACE_STR))
#define TOMMROC_STRING_SPACE_STR_LENGTH                         (TOMMROC_UTIL_STRING_ARR_LENGTH(TOMMROC_STRING_SPACE_STR))

#define TOMMROC_STRING_BACKSPACE_CHAR                           ('\b')
#define TOMMROC_STRING_BACKSPACE_CHAR_SIZE                      (TOMMROC_UTIL_CHAR_SIZE)
#define TOMMROC_STRING_BACKSPACE_STR                            "\b"
#define TOMMROC_STRING_BACKSPACE_STR_SIZE                       (sizeof(TOMMROC_STRING_BACKSPACE_STR))
#define TOMMROC_STRING_BACKSPACE_STR_LENGTH                     (TOMMROC_UTIL_STRING_ARR_LENGTH(TOMMROC_STRING_BACKSPACE_STR))

#define TOMMROC_STRING_NEW_LINE_CHAR                            ('\n')
#define TOMMROC_STRING_NEW_LINE_CHAR_SIZE                       (TOMMROC_UTIL_CHAR_SIZE)
#define TOMMROC_STRING_NEW_LINE_STR                             "\n"
#define TOMMROC_STRING_NEW_LINE_STR_SIZE                        (sizeof(TOMMROC_STRING_NEW_LINE_STR))
#define TOMMROC_STRING_NEW_LINE_STR_LENGTH                      (TOMMROC_UTIL_STRING_ARR_LENGTH(TOMMROC_STRING_NEW_LINE_STR))

#define TOMMROC_STRING_CARRIAGE_RETURN_CHAR                     ('\r')
#define TOMMROC_STRING_CARRIAGE_RETURN_CHAR_SIZE                (TOMMROC_UTIL_CHAR_SIZE)
#define TOMMROC_STRING_CARRIAGE_RETURN_STR                      "\r"
#define TOMMROC_STRING_CARRIAGE_RETURN_STR_SIZE                 (sizeof(TOMMROC_STRING_CARRIAGE_RETURN_STR))
#define TOMMROC_STRING_CARRIAGE_RETURN_STR_LENGTH               (TOMMROC_UTIL_STRING_ARR_LENGTH(TOMMROC_STRING_CARRIAGE_RETURN_STR))

#define TOMMROC_STRING_QUOTATION_MARKS_CHAR                     ('\"')
#define TOMMROC_STRING_QUOTATION_MARKS_CHAR_SIZE                (TOMMROC_UTIL_CHAR_SIZE)
#define TOMMROC_STRING_QUOTATION_MARKS_STR                      "\""
#define TOMMROC_STRING_QUOTATION_MARKS_STR_SIZE                 (sizeof(TOMMROC_STRING_QUOTATION_MARKS_STR))
#define TOMMROC_STRING_QUOTATION_MARKS_STR_LENGTH               (TOMMROC_UTIL_STRING_ARR_LENGTH(TOMMROC_STRING_QUOTATION_MARKS_STR))

#define TOMMROC_STRING_COMMA_CHAR                               (',')
#define TOMMROC_STRING_COMMA_CHAR_SIZE                          (TOMMROC_UTIL_CHAR_SIZE)
#define TOMMROC_STRING_COMMA_STR                                ","
#define TOMMROC_STRING_COMMA_STR_SIZE                           (sizeof(TOMMROC_STRING_COMMA_STR))
#define TOMMROC_STRING_COMMA_STR_LENGTH                         (TOMMROC_UTIL_STRING_ARR_LENGTH(TOMMROC_STRING_COMMA_STR))

#define TOMMROC_STRING_DOT_CHAR                                 ('.')
#define TOMMROC_STRING_DOT_CHAR_SIZE                            (TOMMROC_UTIL_CHAR_SIZE)
#define TOMMROC_STRING_DOT_STR                                  "."
#define TOMMROC_STRING_DOT_STR_SIZE                             (sizeof(TOMMROC_STRING_DOT_STR))
#define TOMMROC_STRING_DOT_STR_LENGTH                           (TOMMROC_UTIL_STRING_ARR_LENGTH(TOMMROC_STRING_DOT_STR))

#define TOMMROC_STRING_HASHTAG_CHAR                             ('#')
#define TOMMROC_STRING_HASHTAG_CHAR_SIZE                        (TOMMROC_UTIL_CHAR_SIZE)
#define TOMMROC_STRING_HASHTAG_STR                              "#"
#define TOMMROC_STRING_HASHTAG_STR_SIZE                         (sizeof(TOMMROC_STRING_HASHTAG_STR))
#define TOMMROC_STRING_HASHTAG_STR_LENGTH                       (TOMMROC_UTIL_STRING_ARR_LENGTH(TOMMROC_STRING_HASHTAG_STR))

#define TOMMROC_STRING_SLASH_CHAR                               ('/')
#define TOMMROC_STRING_SLASH_CHAR_SIZE                          (TOMMROC_UTIL_CHAR_SIZE)
#define TOMMROC_STRING_SLASH_STR                                "/"
#define TOMMROC_STRING_SLASH_STR_SIZE                           (sizeof(TOMMROC_STRING_SLASH_STR))
#define TOMMROC_STRING_SLASH_STR_LENGTH                         (TOMMROC_UTIL_STRING_ARR_LENGTH(TOMMROC_STRING_SLASH_STR))

#define TOMMROC_STRING_BACKSLASH_CHAR                           ('\\')
#define TOMMROC_STRING_BACKSLASH_CHAR_SIZE                      (TOMMROC_UTIL_CHAR_SIZE)
#define TOMMROC_STRING_BACKSLASH_STR                            "\\"
#define TOMMROC_STRING_BACKSLASH_STR_SIZE                       (sizeof(TOMMROC_STRING_BACKSLASH_STR))
#define TOMMROC_STRING_BACKSLASH_STR_LENGTH                     (TOMMROC_UTIL_STRING_ARR_LENGTH(TOMMROC_STRING_BACKSLASH_STR))

#define TOMMROC_STRING_CANC_CHAR                                (0x7F)
#define TOMMROC_STRING_CANC_CHAR_SIZE                           (TOMMROC_UTIL_CHAR_SIZE)

/******************* String array ('\0' included) max size regarding integer types in natural/hex format */

#define TOMMROC_STRING_U8_DEC_AS_STRING_MAX_ARRAY_SIZE_BYTE     (sizeof("255"))
#define TOMMROC_STRING_U16_DEC_AS_STRING_MAX_ARRAY_SIZE_BYTE    (sizeof("65535"))
#define TOMMROC_STRING_U32_DEC_AS_STRING_MAX_ARRAY_SIZE_BYTE    (sizeof("4294967295"))
#define TOMMROC_STRING_U64_DEC_AS_STRING_MAX_ARRAY_SIZE_BYTE    (sizeof("18446744073709551615"))

#define TOMMROC_STRING_U8_HEX_AS_STRING_MAX_ARRAY_SIZE_BYTE     (sizeof("FF"))
#define TOMMROC_STRING_U16_HEX_AS_STRING_MAX_ARRAY_SIZE_BYTE    (sizeof("FFFF"))
#define TOMMROC_STRING_U32_HEX_AS_STRING_MAX_ARRAY_SIZE_BYTE    (sizeof("FFFFFFFF"))
#define TOMMROC_STRING_U64_HEX_AS_STRING_MAX_ARRAY_SIZE_BYTE    (sizeof("FFFFFFFFFFFFFFFF"))

#define TOMMROC_STRING_I8_DEC_AS_STRING_MAX_ARRAY_SIZE_BYTE     (sizeof("-127"))
#define TOMMROC_STRING_I16_DEC_AS_STRING_MAX_ARRAY_SIZE_BYTE    (sizeof("-32767"))
#define TOMMROC_STRING_I32_DEC_AS_STRING_MAX_ARRAY_SIZE_BYTE    (sizeof("-2147483648"))
#define TOMMROC_STRING_I64_DEC_AS_STRING_MAX_ARRAY_SIZE_BYTE    (sizeof("-9223372036854775808"))


/******************* String array ('\0' excluded) max size regarding integer types in natural/hex format */

#define TOMMROC_STRING_U8_DEC_AS_STRING_MAX_LENGTH_BYTE         (TOMMROC_UTIL_STRING_ARR_LENGTH("255"))
#define TOMMROC_STRING_U16_DEC_AS_STRING_MAX_LENGTH_BYTE        (TOMMROC_UTIL_STRING_ARR_LENGTH("65535"))
#define TOMMROC_STRING_U32_DEC_AS_STRING_MAX_LENGTH_BYTE        (TOMMROC_UTIL_STRING_ARR_LENGTH("4294967295"))
#define TOMMROC_STRING_U64_DEC_AS_STRING_MAX_LENGTH_BYTE        (TOMMROC_UTIL_STRING_ARR_LENGTH("18446744073709551615"))

#define TOMMROC_STRING_U8_HEX_AS_STRING_MAX_LENGTH_BYTE         (TOMMROC_UTIL_STRING_ARR_LENGTH("FF"))
#define TOMMROC_STRING_U16_HEX_AS_STRING_MAX_LENGTH_BYTE        (TOMMROC_UTIL_STRING_ARR_LENGTH("FFFF"))
#define TOMMROC_STRING_U32_HEX_AS_STRING_MAX_LENGTH_BYTE        (TOMMROC_UTIL_STRING_ARR_LENGTH("FFFFFFFF"))
#define TOMMROC_STRING_U64_HEX_AS_STRING_MAX_LENGTH_BYTE        (TOMMROC_UTIL_STRING_ARR_LENGTH("FFFFFFFFFFFFFFFF"))

#define TOMMROC_STRING_I8_DEC_AS_STRING_MAX_LENGTH_BYTE         (TOMMROC_UTIL_STRING_ARR_LENGTH("-127"))
#define TOMMROC_STRING_I16_DEC_AS_STRING_MAX_LENGTH_BYTE        (TOMMROC_UTIL_STRING_ARR_LENGTH("-32767"))
#define TOMMROC_STRING_I32_DEC_AS_STRING_MAX_LENGTH_BYTE        (TOMMROC_UTIL_STRING_ARR_LENGTH("-2147483648"))
#define TOMMROC_STRING_I64_DEC_AS_STRING_MAX_LENGTH_BYTE        (TOMMROC_UTIL_STRING_ARR_LENGTH("-9223372036854775808"))


/******************* Default array to string conversion functions */

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM) || defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX_AARCH32)

// Unsigned values

#define TOMMROC_STRING_U8_ARRAY_TO_STRING(                                  \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringU8ArrayToString(                                       \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%lu",                                                      \
                NULL,                                                       \
                outputStringMaxSize,                                        \
                outputStringPtr)

#define TOMMROC_STRING_U16_ARRAY_TO_STRING(                                 \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringU16ArrayToString(                                      \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%lu",                                                      \
                NULL,                                                       \
                outputStringMaxSize,                                        \
                outputStringPtr)

#define TOMMROC_STRING_U32_ARRAY_TO_STRING(                                 \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringU32ArrayToString(                                      \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%lu",                                                      \
                NULL,                                                       \
                outputStringMaxSize,                                        \
                outputStringPtr)


// Signed values

#define TOMMROC_STRING_I8_ARRAY_TO_STRING(                                  \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringI8ArrayToString(                                       \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%ld",                                                      \
                NULL,                                                       \
                outputStringMaxSize,                                        \
                outputStringPtr)

#define TOMMROC_STRING_I16_ARRAY_TO_STRING(                                 \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringI16ArrayToString(                                      \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%ld",                                                      \
                NULL,                                                       \
                outputStringMaxSize,                                        \
                outputStringPtr)

#define TOMMROC_STRING_I32_ARRAY_TO_STRING(                                 \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringI32ArrayToString(                                      \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%ld",                                                      \
                NULL,                                                       \
                outputStringMaxSize,                                        \
                outputStringPtr)
#else


// Unsigned values

#define TOMMROC_STRING_U8_ARRAY_TO_STRING(                                  \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringU8ArrayToString(                                       \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%u",                                                       \
                NULL,                                                       \
                outputStringMaxSize,                                        \
                outputStringPtr)

#define TOMMROC_STRING_U16_ARRAY_TO_STRING(                                 \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringU16ArrayToString(                                      \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%u",                                                       \
                NULL,                                                       \
                outputStringMaxSize,                                        \
                outputStringPtr)

#define TOMMROC_STRING_U32_ARRAY_TO_STRING(                                 \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringU32ArrayToString(                                      \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%u",                                                       \
                NULL,                                                       \
                outputStringMaxSize,                                        \
                outputStringPtr)


// Signed values

#define TOMMROC_STRING_I8_ARRAY_TO_STRING(                                  \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringI8ArrayToString(                                       \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%d",                                                       \
                NULL,                                                       \
                outputStringMaxSize,                                        \
                outputStringPtr)

#define TOMMROC_STRING_I16_ARRAY_TO_STRING(                                 \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringI16ArrayToString(                                      \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%d",                                                       \
                NULL,                                                       \
                outputStringMaxSize,                                        \
                outputStringPtr)

#define TOMMROC_STRING_I32_ARRAY_TO_STRING(                                 \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringI32ArrayToString(                                      \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%d",                                                       \
                NULL,                                                       \
                outputStringMaxSize,                                        \
                outputStringPtr)
#endif


// Unsigned HEX values - Upper case: default

#define TOMMROC_STRING_U8_ARRAY_TO_HEX_STRING(                              \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringU8ArrayToString(                                       \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%02X",                                                     \
                NULL,                                                       \
                outputStringMaxSize,                                        \
                outputStringPtr)

#define TOMMROC_STRING_U16_ARRAY_TO_HEX_STRING(                             \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringU16ArrayToString(                                      \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%04X",                                                     \
                NULL,                                                       \
                outputStringMaxSize,                                        \
                outputStringPtr)

#define TOMMROC_STRING_U32_ARRAY_TO_HEX_STRING(                             \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringU32ArrayToString(                                      \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%08X",                                                     \
                NULL,                                                       \
                outputStringMaxSize,                                        \
                outputStringPtr)


// Unsigned HEX values - Lower case

#define TOMMROC_STRING_U8_ARRAY_TO_LOWER_CASE_HEX_STRING(                   \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringU8ArrayToString(                                       \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%02x",                                                     \
                NULL,                                                       \
                outputStringMaxSize,                                        \
                outputStringPtr)

#define TOMMROC_STRING_U16_ARRAY_TO_LOWER_CASE_HEX_STRING(                  \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringU16ArrayToString(                                      \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%04x",                                                     \
                NULL,                                                       \
                outputStringMaxSize,                                        \
                outputStringPtr)

#define TOMMROC_STRING_U32_ARRAY_TO_LOWER_CASE_HEX_STRING(                  \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringU32ArrayToString(                                      \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%08x",                                                     \
                NULL,                                                       \
                outputStringMaxSize,                                        \
                outputStringPtr)


// Float values

#define TOMMROC_STRING_FLOAT_ARRAY_TO_STRING_1_DEC_DIGIT(                   \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringFloatArrayToString(                                    \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%.1f",                                                     \
                NULL,                                                       \
                TOMMROC_STRING_FLOAT_TO_STR_CONV_ZERO_NOT_SIGN_DONT_REMOVE, \
                outputStringMaxSize,                                        \
                outputStringPtr)

#define TOMMROC_STRING_FLOAT_ARRAY_TO_STRING_2_DEC_DIGIT(                   \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringFloatArrayToString(                                    \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%.2f",                                                     \
                NULL,                                                       \
                TOMMROC_STRING_FLOAT_TO_STR_CONV_ZERO_NOT_SIGN_DONT_REMOVE, \
                outputStringMaxSize,                                        \
                outputStringPtr)

#define TOMMROC_STRING_FLOAT_ARRAY_TO_STRING_3_DEC_DIGIT(                   \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringFloatArrayToString(                                    \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%.3f",                                                     \
                NULL,                                                       \
                TOMMROC_STRING_FLOAT_TO_STR_CONV_ZERO_NOT_SIGN_DONT_REMOVE, \
                outputStringMaxSize,                                        \
                outputStringPtr)

#define TOMMROC_STRING_FLOAT_ARRAY_TO_STRING_4_DEC_DIGIT(                   \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringFloatArrayToString(                                    \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%.4f",                                                     \
                NULL,                                                       \
                TOMMROC_STRING_FLOAT_TO_STR_CONV_ZERO_NOT_SIGN_DONT_REMOVE, \
                outputStringMaxSize,                                        \
                outputStringPtr)

#define TOMMROC_STRING_FLOAT_ARRAY_TO_STRING_5_DEC_DIGIT(                   \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringFloatArrayToString(                                    \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%.5f",                                                     \
                NULL,                                                       \
                TOMMROC_STRING_FLOAT_TO_STR_CONV_ZERO_NOT_SIGN_DONT_REMOVE, \
                outputStringMaxSize,                                        \
                outputStringPtr)

#define TOMMROC_STRING_FLOAT_ARRAY_TO_STRING_6_DEC_DIGIT(                   \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        tommRoCStringFloatArrayToString(                                    \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                NULL,                                                       \
                "%.6f",                                                     \
                NULL,                                                       \
                TOMMROC_STRING_FLOAT_TO_STR_CONV_ZERO_NOT_SIGN_DONT_REMOVE, \
                outputStringMaxSize,                                        \
                outputStringPtr)

#define TOMMROC_STRING_FLOAT_ARRAY_TO_STRING(                               \
        inputArrayPtr,                                                      \
        inputArrayElemAmount,                                               \
        outputStringMaxSize,                                                \
        outputStringPtr)                                                    \
        TOMMROC_STRING_FLOAT_ARRAY_TO_STRING_3_DEC_DIGIT(                   \
                inputArrayPtr,                                              \
                inputArrayElemAmount,                                       \
                outputStringMaxSize,                                        \
                outputStringPtr)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC string float to string conversion - remove not significant zeros.
typedef enum {

    TOMMROC_STRING_FLOAT_TO_STR_CONV_ZERO_NOT_SIGN_DONT_REMOVE = 0, // Don't remove not significant zeros - default.
    TOMMROC_STRING_FLOAT_TO_STR_CONV_ZERO_NOT_SIGN_REMOVE,          // Remove not significant zeros.

} tommRoC_string_float_to_str_conv_zero_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Get string length.
 *
 * param[in]        stringPtr               string pointer [NOTE: string have to be terminated with '\0'].
 *
 * return uint16_t
 *          UINT16_MAX                              -> Error detected (not '\0' found).
 */
uint16_t tommRoCStringStrLen(const char* const stringPtr);

/**
 * Check if a string is a numeric base-10 string.
 * NOTE: only numeric characters (0,1,..,8,9) are valid.
 *
 * param[in]        stringPtr               string pointer [NOTE: string have to be terminated with '\0'].
 *
 * return bool
 */
bool tommRoCStringIsNumericDecStr(const char* const stringPtr);

/**
 * Check if a string is a numeric base-10 string - string with length version.
 * NOTE: only numeric characters (0,1,..,8,9) are valid.
 *
 * param[in]        stringPtr               string pointer.
 * param[in]        stringLen               string length.
 *
 * return bool
 */
bool tommRoCStringIsNumericDecStrLen(
        const   char*       const   stringPtr,
        const   uint16_t            stringLen);

/**
 * Check if a is string a numeric base-16 string.
 * NOTE: only HEX numeric characters (0,1,..,8,9,a,b,c,d,e,f,A,B,C,D,E,F) are valid.
 *
 * param[in]        stringPtr               string pointer [NOTE: string have to be terminated with '\0'].
 *
 * return bool
 */
bool tommRoCStringIsNumericHexStr(const char* const stringPtr);

/**
 * Check if a string is a numeric base-16 string - string with length version.
 * NOTE: only HEX numeric characters (0,1,..,8,9,a,b,c,d,e,f,A,B,C,D,E,F) are valid.
 *
 * param[in]        stringPtr               string pointer.
 * param[in]        stringLen               string length.
 *
 * return bool
 */
bool tommRoCStringIsNumericHexStrLen(
        const   char*       const   stringPtr,
        const   uint16_t            stringLen);

/**
 * Check if a character is printable.
 *
 * param[in]        ch                      character.
 *
 * return bool
 */
bool tommRoCStringIsPrintCh(const char ch);

/**
 * Check if a string is totally a printable string.
 *
 * param[in]        stringPtr               string pointer [NOTE: string have to be terminated with '\0'].
 *
 * return bool
 */
bool tommRoCStringIsPrintStr(const char* const stringPtr);

/**
 * Check if a string is totally a printable string - string with length version.
 *
 * param[in]        stringPtr               string pointer.
 * param[in]        stringLen               string length.
 *
 * return bool
 */
bool tommRoCStringIsPrintStrLen(
        const   char*       const   stringPtr,
        const   uint16_t            stringLen);

/**
 * Compares two strings.
 * NOTE: two strings are equal if:
 *      - have same string length.
 *      - all characters are matching.
 *
 * param[in]        str1Ptr                 first string pointer.
 * param[in]        str2Ptr                 second string pointer.
 *
 * return tommRoC_err_enum_t
 *          TOMMRO_C_ERR_SUCCESS                                    -> compare success.
 *          TOMMRO_C_COMPARE_PARAM_1_LOWER_THAN_PARAM_2_ERR         -> param ptr1 is lower than param ptr2.
 *          TOMMRO_C_COMPARE_PARAM_1_GREATER_THAN_PARAM_2_ERR       -> param ptr1 is greater than param ptr2.
 *          TOMMRO_C_NULL_PARAM_ERR                                 -> NULL param error.
 *          TOMMRO_C_PARAM_ERR                                      -> param error.
 *
 * NOTE:
 *      - if strings length are different, TOMMRO_C_PARAM_ERR is returned.
 *      - if strings length are the same, memory comparing result is returned.
 */
tommRoC_err_enum_t tommRoCStringCompare(
        const   char*       const   str1Ptr,
        const   char*       const   str2Ptr);

/**
 * Compares two strings of known length.
 * NOTE: two strings are equal if:
 *      - all characters are matching.
 *
 * param[in]        str1Ptr                 first string pointer.
 * param[in]        str2Ptr                 second string pointer.
 * param[in]        strLen                  string length.
 *
 * return tommRoC_err_enum_t
 *          TOMMRO_C_ERR_SUCCESS                                    -> compare success.
 *          TOMMRO_C_COMPARE_PARAM_1_LOWER_THAN_PARAM_2_ERR         -> param ptr1 is lower than param ptr2.
 *          TOMMRO_C_COMPARE_PARAM_1_GREATER_THAN_PARAM_2_ERR       -> param ptr1 is greater than param ptr2.
 *          TOMMRO_C_NULL_PARAM_ERR                                 -> NULL param error.
 *          TOMMRO_C_PARAM_ERR                                      -> param error.
 */
tommRoC_err_enum_t tommRoCStringNCompare(
        const   char*       const   str1Ptr,
        const   char*       const   str2Ptr,
        const   uint16_t            strLen);

/**
 * Check if source string contains another string.
 *
 * param[in]        sourcePtr               source string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        toFindPtr               to find string pointer [NOTE: string have to be terminated with '\0'].
 *
 * return tommRoC_err_enum_t
 *          TOMMRO_C_ERR_SUCCESS                                    -> source string contains toFind string.
 *          TOMMRO_C_NOT_FOUND_ERR                                  -> source string doesn't contains toFind string.
 *          TOMMRO_C_NULL_PARAM_ERR                                 -> NULL param error.
 *          TOMMRO_C_PARAM_ERR                                      -> param error.
 */
tommRoC_err_enum_t tommRoCStringContains(
        const   char*       const   sourcePtr,
        const   char*       const   toFindPtr);

/**
 * Get index of first occurrence of a string inside another string.
 *
 * param[in]        sourcePtr               source string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        startIndex              start search index of string.
 * param[in]        toFindPtr               to find string pointer [NOTE: string have to be terminated with '\0'].
 * param[out]       indexPtr                index found.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringIndexOf(
        const   char*       const   sourcePtr,
        const   uint16_t            startIndex,
        const   char*       const   toFindPtr,
                uint16_t*   const   indexPtr);

/**
 * Get index of first occurrence of a string inside another string.
 *
 * param[in]        sourcePtr               source string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        toFindPtr               to find string pointer [NOTE: string have to be terminated with '\0'].
 * param[out]       indexPtr                index found.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringFirstIndexOf(
        const   char*       const   sourcePtr,
        const   char*       const   toFindPtr,
                uint16_t*   const   indexPtr);

/**
 * Chech if a string starts with another string.
 *
 * param[in]        sourcePtr               source string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        toFindPtr               to find string pointer [NOTE: string have to be terminated with '\0'].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringStartWith(
        const   char*       const   sourcePtr,
        const   char*       const   toFindPtr);

/**
 * Get index of last occurrence of a string inside another string.
 *
 * param[in]        sourcePtr               source string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        toFindPtr               to find string pointer [NOTE: string have to be terminated with '\0'].
 * param[out]       indexPtr                index found.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringLastIndexOf(
        const   char*       const   sourcePtr,
        const   char*       const   toFindPtr,
                uint16_t*   const   indexPtr);

/**
 * Chech if a string ends with another string.
 *
 * param[in]        sourcePtr               source string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        toFindPtr               to find string pointer [NOTE: string have to be terminated with '\0'].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringEndWith(
        const   char*       const   sourcePtr,
        const   char*       const   toFindPtr);

/**
 * Split (get index of all occurrences) of a string based on another string.
 *
 * param[in]        sourcePtr               to split string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        toFindPtr               to find (used to split) string pointer [NOTE: string have to be terminated with '\0'].
 * param[out]       indexBufferPtr          index buffer found pointer.
 * param[in]        indexBufferAmount       index buffer found max element amount.
 * param[out]       indexBufferAmountPtr    index buffer found element amount pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringSplit(
        const   char*       const   sourcePtr,
        const   char*       const   toFindPtr,
                uint16_t*   const   indexBufferPtr,
        const   uint16_t            indexBufferAmount,
                uint16_t*   const   indexBufferAmountPtr);

/**
 * Split (get index of all occurrences) of a string based on another string - string length/not terminated with '\0' version.
 *
 * param[in]        sourcePtr               to split string pointer.
 * param[in]        sourceLen               to split string length.
 * param[in]        toFindPtr               to find (used to split) string pointer [NOTE: string have to be terminated with '\0'].
 * param[out]       indexBufferPtr          index buffer found pointer.
 * param[in]        indexBufferAmount       index buffer found max element amount.
 * param[out]       indexBufferAmountPtr    index buffer found element amount pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringSplitLen(
        const   char*       const   sourcePtr,
        const   uint16_t            sourceLen,
        const   char*       const   toFindPtr,
                uint16_t*   const   indexBufferPtr,
        const   uint16_t            indexBufferAmount,
                uint16_t*   const   indexBufferAmountPtr);

/**
 * Remove all occurrences of a string inside another string.
 *
 * param[in]        sourcePtr               source string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        removePtr               to remove string pointer [NOTE: string have to be terminated with '\0'].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringRemove(
                char*       const   sourcePtr,
        const   char*       const   removePtr);

/**
 * Replace all occurrences of a string with another string.
 *
 * param[in/out]    sourcePtr               source string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        sourceMaxSize           source string buffer max size.
 * param[in]        replacePtr              to replace string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        replaceWithPtr          to replace with string pointer [NOTE: string have to be terminated with '\0'].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringReplace(
                char*       const   sourcePtr,
        const   uint16_t            sourceMaxSize,
        const   char*       const   replacePtr,
        const   char*       const   replaceWithPtr);

/**
 * Get index of first occurrence of an array inside another array.
 *
 * param[in]        sourcePtr               source array pointer.
 * param[in]        sourceLen               source array len.
 * param[in]        startIndex              start search index of string.
 * param[in]        toFindPtr               to find array pointer.
 * param[in]        toFindLen               to find array len.
 * param[out]       indexPtr                index found.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringArrayIndexOf(
        const   uint8_t*    const   sourcePtr,
        const   uint16_t            sourceLen,
        const   uint16_t            startIndex,
        const   uint8_t*    const   toFindPtr,
        const   uint16_t            toFindLen,
                uint16_t*   const   indexPtr);

/**
 * Get index of first occurrence of an array inside another array.
 *
 * param[in]        sourcePtr               source array pointer.
 * param[in]        sourceLen               source array len.
 * param[in]        toFindPtr               to find array pointer.
 * param[in]        toFindLen               to find array len.
 * param[out]       indexPtr                index found.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringArrayFirstIndexOf(
        const   uint8_t*    const   sourcePtr,
        const   uint16_t            sourceLen,
        const   uint8_t*    const   toFindPtr,
        const   uint16_t            toFindLen,
                uint16_t*   const   indexPtr);

/**
 * Get index of last occurrence of an array inside another array.
 *
 * param[in]        sourcePtr               source array pointer.
 * param[in]        sourceLen               source array len.
 * param[in]        toFindPtr               to find array pointer.
 * param[in]        toFindLen               to find array len.
 * param[out]       indexPtr                index found.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringArrayLastIndexOf(
        const   uint8_t*    const   sourcePtr,
        const   uint16_t            sourceLen,
        const   uint8_t*    const   toFindPtr,
        const   uint16_t            toFindLen,
                uint16_t*   const   indexPtr);

/**
 * Remove all occurrences of an array inside another array.
 *
 * param[in/out]    sourcePtr               source array pointer.
 * param[in]        sourceLen               source array len.
 * param[in]        removePtr               to remove array pointer.
 * param[in]        removeLen               to remove array len.
 * param[out]       newSourceLenPtr         new source array len pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringArrayRemove(
                uint8_t*    const   sourcePtr,
        const   uint16_t            sourceLen,
        const   uint8_t*    const   removePtr,
        const   uint16_t            removeLen,
                uint16_t*   const   newSourceLenPtr);

/**
 * Replace all occurrences of a array with another array.
 *
 * param[in/out]    sourcePtr               source array pointer.
 * param[in]        sourceLen               source array len.
 * param[in]        sourceMaxSize           source string buffer max size.
 * param[in]        replacePtr              to replace array pointer.
 * param[in]        replaceLen              to replace array len.
 * param[in]        replaceWithPtr          to replace with array pointer.
 * param[in]        replaceWithLen          to replace with array len.
 * param[out]       newSourceLenPtr         new source array len pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringArrayReplace(
                uint8_t*    const   sourcePtr,
        const   uint16_t            sourceLen,
        const   uint16_t            sourceMaxSize,
        const   uint8_t*    const   replacePtr,
        const   uint16_t            replaceLen,
        const   uint8_t*    const   replaceWithPtr,
        const   uint16_t            replaceWithLen,
                uint16_t*   const   newSourceLenPtr);

/**
 * Convert an uintx_t array into string.
 *
 * param[in]        inputArrayPtr           uintx_t array pointer.
 * param[in]        inputArrayElemAmount    uintx_t array elements amount [count].
 * param[in]        headerStringPtr         string header pointer (NULL for none).
 * param[in]        formatStringPtr         single uintx_t conversion format (reference: sprintf "%" format).
 * param[in]        footerStringPtr         string footer pointer (NULL for none).
 * param[in]        outputStringMaxSize     output string buffer max size [byte].
 * param[out]       outputStringPtr         output string pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringU8ArrayToString(
        const   uint8_t*    const   inputArrayPtr,
        const   uint16_t            inputArrayElemAmount,
        const   char*       const   headerStringPtr,
        const   char*       const   formatStringPtr,
        const   char*       const   footerStringPtr,
        const   uint16_t            outputStringMaxSize,
                char*       const   outputStringPtr);

tommRoC_err_enum_t tommRoCStringU16ArrayToString(
        const   uint16_t*   const   inputArrayPtr,
        const   uint16_t            inputArrayElemAmount,
        const   char*       const   headerStringPtr,
        const   char*       const   formatStringPtr,
        const   char*       const   footerStringPtr,
        const   uint16_t            outputStringMaxSize,
                char*       const   outputStringPtr);

tommRoC_err_enum_t tommRoCStringU32ArrayToString(
        const   uint32_t*   const   inputArrayPtr,
        const   uint16_t            inputArrayElemAmount,
        const   char*       const   headerStringPtr,
        const   char*       const   formatStringPtr,
        const   char*       const   footerStringPtr,
        const   uint16_t            outputStringMaxSize,
                char*       const   outputStringPtr);

/**
 * Convert an intx_t array into string.
 *
 * param[in]        inputArrayPtr           intx_t array pointer.
 * param[in]        inputArrayElemAmount    intx_t array elements amount [count].
 * param[in]        headerStringPtr         string header pointer (NULL for none).
 * param[in]        formatStringPtr         single intx_t conversion format (reference: sprintf "%" format).
 * param[in]        footerStringPtr         string footer pointer (NULL for none).
 * param[in]        outputStringMaxSize     output string buffer max size [byte].
 * param[out]       outputStringPtr         output string pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringI8ArrayToString(
        const   int8_t*     const   inputArrayPtr,
        const   uint16_t            inputArrayElemAmount,
        const   char*       const   headerStringPtr,
        const   char*       const   formatStringPtr,
        const   char*       const   footerStringPtr,
        const   uint16_t            outputStringMaxSize,
                char*       const   outputStringPtr);

tommRoC_err_enum_t tommRoCStringI16ArrayToString(
        const   int16_t*    const   inputArrayPtr,
        const   uint16_t            inputArrayElemAmount,
        const   char*       const   headerStringPtr,
        const   char*       const   formatStringPtr,
        const   char*       const   footerStringPtr,
        const   uint16_t            outputStringMaxSize,
                char*       const   outputStringPtr);

tommRoC_err_enum_t tommRoCStringI32ArrayToString(
        const   int32_t*    const   inputArrayPtr,
        const   uint16_t            inputArrayElemAmount,
        const   char*       const   headerStringPtr,
        const   char*       const   formatStringPtr,
        const   char*       const   footerStringPtr,
        const   uint16_t            outputStringMaxSize,
                char*       const   outputStringPtr);

/**
 * Convert an float array into string.
 *
 * param[in]        inputArrayPtr           float array pointer.
 * param[in]        inputArrayElemAmount    float array elements amount [count].
 * param[in]        headerStringPtr         string header pointer (NULL for none).
 * param[in]        formatStringPtr         single float conversion format (reference: sprintf "%" format).
 * param[in]        footerStringPtr         string footer pointer (NULL for none).
 * param[in]        strConvZero             remove not significant zeros.
 * param[in]        outputStringMaxSize     output string buffer max size [byte].
 * param[out]       outputStringPtr         output string pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringFloatArrayToString(
        const   float*      const   inputArrayPtr,
        const   uint16_t            inputArrayElemAmount,
        const   char*       const   headerStringPtr,
        const   char*       const   formatStringPtr,
        const   char*       const   footerStringPtr,
        const   tommRoC_string_float_to_str_conv_zero_enum_t strConvZero,
        const   uint16_t            outputStringMaxSize,
                char*       const   outputStringPtr);

/**
 * Convert a string into boolean value.
 *
 * param[in]        inputStringPtr          input string pointer.
 * param[in]        inputStringLen          input string length.
 * param[out]       resultPtr               output result pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringStringToBool(
        const   char*       const   inputStringPtr,
        const   uint8_t             inputStringLen,
                bool*       const   resultPtr);

/**
 * Convert a string into uintx_t value.
 *
 * param[in]        inputStringPtr          input string pointer.
 * param[in]        inputStringLen          input string length.
 * param[in]        conversionBase          uintx_t conversion base (reference: strtol base).
 * param[out]       resultPtr               output result pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringStringToU8(
        const   char*       const   inputStringPtr,
        const   uint8_t             inputStringLen,
        const   uint8_t             conversionBase,
                uint8_t*    const   resultPtr);

tommRoC_err_enum_t tommRoCStringStringToU16(
        const   char*       const   inputStringPtr,
        const   uint8_t             inputStringLen,
        const   uint8_t             conversionBase,
                uint16_t*   const   resultPtr);

tommRoC_err_enum_t tommRoCStringStringToU32(
        const   char*       const   inputStringPtr,
        const   uint8_t             inputStringLen,
        const   uint8_t             conversionBase,
                uint32_t*   const   resultPtr);

/**
 * Convert a string into uintx_t array.
 *
 * param[in]        inputStringPtr          input string pointer.
 * param[in]        baseElemStringLen       base element string length.
 * param[in]        conversionBase          single uintx_t conversion base (reference: strtol base).
 * param[in]        outputArrayMaxSize      output array buffer max size [byte].
 * param[out]       outputArrayPtr          output array pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringStringToU8Array(
        const   char*       const   inputStringPtr,
        const   uint8_t             baseElemStringLen,
        const   uint8_t             conversionBase,
        const   uint16_t            outputArrayMaxSize,
                uint8_t*    const   outputArrayPtr);

tommRoC_err_enum_t tommRoCStringStringToU16Array(
        const   char*       const   inputStringPtr,
        const   uint8_t             baseElemStringLen,
        const   uint8_t             conversionBase,
        const   uint16_t            outputArrayMaxSize,
                uint16_t*   const   outputArrayPtr);

tommRoC_err_enum_t tommRoCStringStringToU32Array(
        const   char*       const   inputStringPtr,
        const   uint8_t             baseElemStringLen,
        const   uint8_t             conversionBase,
        const   uint16_t            outputArrayMaxSize,
                uint32_t*   const   outputArrayPtr);

/**
 * Convert a string into uintx_t array.
 * NOTE: numbers in string separated by a separator character.
 *
 * param[in]        inputStringPtr          input string pointer.
 * param[in]        inputStringLen          input string length.
 * param[in]        separatorChar           separator char.
 * param[in]        conversionBase          single uintx_t conversion base (reference: strtol base).
 * param[in]        outputArrayMaxSize      output array buffer max size [byte].
 * param[out]       outputArrayPtr          output array pointer.
 * param[out]       outputArrayLenPtr       output array length pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringStringWithSeparatorToU8Array(
        const   char*       const   inputStringPtr,
        const   uint16_t            inputStringLen,
        const   char                separatorChar,
        const   uint8_t             conversionBase,
        const   uint16_t            outputArrayMaxSize,
                uint8_t*    const   outputArrayPtr,
                uint16_t*   const   outputArrayLenPtr);

tommRoC_err_enum_t tommRoCStringStringWithSeparatorToU16Array(
        const   char*       const   inputStringPtr,
        const   uint16_t            inputStringLen,
        const   char                separatorChar,
        const   uint8_t             conversionBase,
        const   uint16_t            outputArrayMaxSize,
                uint16_t*   const   outputArrayPtr,
                uint16_t*   const   outputArrayLenPtr);

tommRoC_err_enum_t tommRoCStringStringWithSeparatorToU32Array(
        const   char*       const   inputStringPtr,
        const   uint16_t            inputStringLen,
        const   char                separatorChar,
        const   uint8_t             conversionBase,
        const   uint16_t            outputArrayMaxSize,
                uint32_t*   const   outputArrayPtr,
                uint16_t*   const   outputArrayLenPtr);

/**
 * Convert a string into intx_t array.
 * NOTE: numbers in string separated by a separator character.
 *
 * param[in]        inputStringPtr          input string pointer.
 * param[in]        inputStringLen          input string length.
 * param[in]        separatorChar           separator char.
 * param[in]        conversionBase          single intx_t conversion base (reference: strtol base).
 * param[in]        outputArrayMaxSize      output array buffer max size [byte].
 * param[out]       outputArrayPtr          output array pointer.
 * param[out]       outputArrayLenPtr       output array length pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringStringWithSeparatorToI8Array(
        const   char*       const   inputStringPtr,
        const   uint16_t            inputStringLen,
        const   char                separatorChar,
        const   uint8_t             conversionBase,
        const   uint16_t            outputArrayMaxSize,
                int8_t*     const   outputArrayPtr,
                uint16_t*   const   outputArrayLenPtr);

tommRoC_err_enum_t tommRoCStringStringWithSeparatorToI16Array(
        const   char*       const   inputStringPtr,
        const   uint16_t            inputStringLen,
        const   char                separatorChar,
        const   uint8_t             conversionBase,
        const   uint16_t            outputArrayMaxSize,
                int16_t*    const   outputArrayPtr,
                uint16_t*   const   outputArrayLenPtr);

tommRoC_err_enum_t tommRoCStringStringWithSeparatorToI32Array(
        const   char*       const   inputStringPtr,
        const   uint16_t            inputStringLen,
        const   char                separatorChar,
        const   uint8_t             conversionBase,
        const   uint16_t            outputArrayMaxSize,
                int32_t*    const   outputArrayPtr,
                uint16_t*   const   outputArrayLenPtr);

/**
 * Convert a string into intx_t value.
 *
 * param[in]        inputStringPtr          input string pointer.
 * param[in]        inputStringLen          input string length.
 * param[in]        conversionBase          uintx_t conversion base (reference: strtol base).
 * param[out]       resultPtr               output result pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringStringToI8(
        const   char*       const   inputStringPtr,
        const   uint8_t             inputStringLen,
        const   uint8_t             conversionBase,
                int8_t*     const   resultPtr);

tommRoC_err_enum_t tommRoCStringStringToI16(
        const   char*       const   inputStringPtr,
        const   uint8_t             inputStringLen,
        const   uint8_t             conversionBase,
                int16_t*    const   resultPtr);

tommRoC_err_enum_t tommRoCStringStringToI32(
        const   char*       const   inputStringPtr,
        const   uint8_t             inputStringLen,
        const   uint8_t             conversionBase,
                int32_t*    const   resultPtr);

/**
 * Convert a string into float value.
 *
 * param[in]        inputStringPtr          input string pointer.
 * param[in]        inputStringLen          input string length.
 * param[out]       resultPtr               output result pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringStringToFloat(
        const   char*       const   inputStringPtr,
        const   uint8_t             inputStringLen,
                float*      const   resultPtr);

/**
 * Convert a string into float array.
 *
 * param[in]        inputStringPtr          input string pointer.
 * param[in]        baseElemStringLen       base element string length.
 * param[in]        outputArrayMaxSize      output array buffer max size [byte].
 * param[out]       outputArrayPtr          output array pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringStringToFloatArray(
        const   char*       const   inputStringPtr,
        const   uint8_t             baseElemStringLen,
        const   uint16_t            outputArrayMaxSize,
                float*      const   outputArrayPtr);

/**
 * Convert a string into float array.
 * NOTE: numbers in string separated by a separator character.
 *
 * param[in]        inputStringPtr          input string pointer.
 * param[in]        inputStringLen          input string length.
 * param[in]        separatorChar           separator char.
 * param[in]        outputArrayMaxSize      output array buffer max size [byte].
 * param[out]       outputArrayPtr          output array pointer.
 * param[out]       outputArrayLenPtr       output array length pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCStringStringWithSeparatorToFloatArray(
        const   char*       const   inputStringPtr,
        const   uint16_t            inputStringLen,
        const   char                separatorChar,
        const   uint16_t            outputArrayMaxSize,
                float*      const   outputArrayPtr,
                uint16_t*   const   outputArrayLenPtr);

/**
 * @}
 */

#endif
