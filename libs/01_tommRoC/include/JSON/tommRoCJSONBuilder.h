
#ifndef TOMMROC_JSON_BUILDER_H_
#define TOMMROC_JSON_BUILDER_H_

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
 * @defgroup tommRoCJSONBuilder tommRoCJSONBuilder
 *
 * @brief  TommRoC library JSON builder module
 * @author TommRo Software Department
 *
 * This module is providing JSON builder functionality.
 * JSON builder is a module to build JSON formatted strings.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCAssert.h"
#include "tommRoCErr.h"
#include "tommRoCString.h"
#include "tommRoCUtil.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// Default data buffer size [byte] for a JSON builder object.
#define TOMMROC_JSON_BUILDER_DEFAULT_DATA_BUFFER_SIZE   (512)


#define TOMMROC_JSON_BUILDER_HANDLE_SIZE                (TOMMROC_UTIL_PTR_SIZE + TOMMROC_UTIL_U16_SIZE + TOMMROC_UTIL_U16_SIZE)

/******************* Not static */

#define TOMMROC_JSON_BUILDER_DECLARE(jsonBuilderName, elemDataBufferSize)                                                                       \
        char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, jsonBuilderName, _, DataBuffer, __)[elemDataBufferSize];                               \
        tommRoC_json_builder_t jsonBuilderName

#define TOMMROC_JSON_BUILDER_ARRAY_DECLARE(jsonBuilderName, elemDataBufferSize, elemAmount)                                                     \
        char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, jsonBuilderName, _, DataBuffer, __)[elemDataBufferSize * elemAmount];                  \
        tommRoC_json_builder_t jsonBuilderName[elemAmount]

#define TOMMROC_JSON_BUILDER_DECLARE_AND_INIT(jsonBuilderName, elemDataBufferSize)                                                              \
        TOMMROC_JSON_BUILDER_DECLARE(jsonBuilderName, elemDataBufferSize);                                                                      \
                                                                                                                                                \
        do {                                                                                                                                    \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(                                                                                           \
                    tommRoCJSONBuilderInit(                                                                                                     \
                            TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, jsonBuilderName, _, DataBuffer, __),                                    \
                            elemDataBufferSize,                                                                                                 \
                            &jsonBuilderName));                                                                                                 \
        } while (0)

#define TOMMROC_JSON_BUILDER_ARRAY_DECLARE_AND_INIT(jsonBuilderName, elemDataBufferSize, elemAmount)                                            \
        TOMMROC_JSON_BUILDER_ARRAY_DECLARE(jsonBuilderName, elemDataBufferSize, elemAmount);                                                    \
                                                                                                                                                \
        do {                                                                                                                                    \
            uint32_t idx;                                                                                                                       \
                                                                                                                                                \
            for (idx = 0; idx < elemAmount; ++idx) {                                                                                            \
                                                                                                                                                \
                TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(                                                                                       \
                        tommRoCJSONBuilderInit(                                                                                                 \
                                TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, jsonBuilderName, _, DataBuffer, __) + (elemDataBufferSize * idx),   \
                                elemDataBufferSize,                                                                                             \
                                &jsonBuilderName[idx]));                                                                                        \
            }                                                                                                                                   \
        } while (0)


/******************* Static */

#define TOMMROC_JSON_BUILDER_STATIC_DECLARE(jsonBuilderName, elemDataBufferSize)                                                                \
        static char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, jsonBuilderName, _, DataBuffer, __)[elemDataBufferSize];                        \
        static tommRoC_json_builder_t jsonBuilderName

#define TOMMROC_JSON_BUILDER_STATIC_ARRAY_DECLARE(jsonBuilderName, elemDataBufferSize, elemAmount)                                              \
        static char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, jsonBuilderName, _, DataBuffer, __)[elemDataBufferSize * elemAmount];           \
        static tommRoC_json_builder_t jsonBuilderName[elemAmount]

#define TOMMROC_JSON_BUILDER_STATIC_DECLARE_AND_INIT(jsonBuilderName, elemDataBufferSize)                                                       \
        TOMMROC_JSON_BUILDER_STATIC_DECLARE(jsonBuilderName, elemDataBufferSize);                                                               \
                                                                                                                                                \
        do {                                                                                                                                    \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(                                                                                           \
                    tommRoCJSONBuilderInit(                                                                                                     \
                            TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, jsonBuilderName, _, DataBuffer, __),                                    \
                            elemDataBufferSize,                                                                                                 \
                            &jsonBuilderName));                                                                                                 \
        } while (0)

#define TOMMROC_JSON_BUILDER_STATIC_ARRAY_DECLARE_AND_INIT(jsonBuilderName, elemDataBufferSize, elemAmount)                                     \
        TOMMROC_JSON_BUILDER_STATIC_ARRAY_DECLARE(jsonBuilderName, elemDataBufferSize, elemAmount);                                             \
                                                                                                                                                \
        do {                                                                                                                                    \
            uint32_t idx;                                                                                                                       \
                                                                                                                                                \
            for (idx = 0; idx < elemAmount; ++idx) {                                                                                            \
                                                                                                                                                \
                TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(                                                                                       \
                        tommRoCJSONBuilderInit(                                                                                                 \
                                TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, jsonBuilderName, _, DataBuffer, __) + (elemDataBufferSize * idx),   \
                                elemDataBufferSize,                                                                                             \
                                &jsonBuilderName[idx]));                                                                                        \
            }                                                                                                                                   \
        } while (0)


/******************* Not static default size */

#define TOMMROC_JSON_BUILDER_DECLARE_DEFAULT_DATA_BUFFER_SIZE(jsonBuilderName)                                                                  \
        TOMMROC_JSON_BUILDER_DECLARE(jsonBuilderName, TOMMROC_JSON_BUILDER_DEFAULT_DATA_BUFFER_SIZE)

#define TOMMROC_JSON_BUILDER_ARRAY_DECLARE_DEFAULT_DATA_BUFFER_SIZE(jsonBuilderName, elemAmount)                                                \
        TOMMROC_JSON_BUILDER_ARRAY_DECLARE(jsonBuilderName, TOMMROC_JSON_BUILDER_DEFAULT_DATA_BUFFER_SIZE, elemAmount)

#define TOMMROC_JSON_BUILDER_DECLARE_AND_INIT_DEFAULT_DATA_BUFFER_SIZE(jsonBuilderName)                                                         \
        TOMMROC_JSON_BUILDER_DECLARE_AND_INIT(jsonBuilderName, TOMMROC_JSON_BUILDER_DEFAULT_DATA_BUFFER_SIZE)

#define TOMMROC_JSON_BUILDER_ARRAY_DECLARE_AND_INIT_DEFAULT_DATA_BUFFER_SIZE(jsonBuilderName, elemAmount)                                       \
        TOMMROC_JSON_BUILDER_ARRAY_DECLARE_AND_INIT(jsonBuilderName, TOMMROC_JSON_BUILDER_DEFAULT_DATA_BUFFER_SIZE, elemAmount)


/******************* Static default size */

#define TOMMROC_JSON_BUILDER_STATIC_DECLARE_DEFAULT_DATA_BUFFER_SIZE(jsonBuilderName)                                                           \
        TOMMROC_JSON_BUILDER_STATIC_DECLARE(jsonBuilderName, TOMMROC_JSON_BUILDER_DEFAULT_DATA_BUFFER_SIZE)

#define TOMMROC_JSON_BUILDER_STATIC_ARRAY_DECLARE_DEFAULT_DATA_BUFFER_SIZE(jsonBuilderName, elemAmount)                                         \
        TOMMROC_JSON_BUILDER_STATIC_ARRAY_DECLARE(jsonBuilderName, TOMMROC_JSON_BUILDER_DEFAULT_DATA_BUFFER_SIZE, elemAmount)

#define TOMMROC_JSON_BUILDER_STATIC_DECLARE_AND_INIT_DEFAULT_DATA_BUFFER_SIZE(jsonBuilderName)                                                  \
        TOMMROC_JSON_BUILDER_STATIC_DECLARE_AND_INIT(jsonBuilderName, TOMMROC_JSON_BUILDER_DEFAULT_DATA_BUFFER_SIZE)

#define TOMMROC_JSON_BUILDER_STATIC_ARRAY_DECLARE_AND_INIT_DEFAULT_DATA_BUFFER_SIZE(jsonBuilderName, elemAmount)                                \
        TOMMROC_JSON_BUILDER_STATIC_ARRAY_DECLARE_AND_INIT(jsonBuilderName, TOMMROC_JSON_BUILDER_DEFAULT_DATA_BUFFER_SIZE, elemAmount)


/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC JSON builder struct.
typedef struct {
    char data[TOMMROC_JSON_BUILDER_HANDLE_SIZE];
} tommRoC_json_builder_t;

#define __EMPTY_tommRoC_json_builder_t_data_field__             TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_JSON_BUILDER_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_json_builder_t__                        \
{                                                               \
    /* .data */ __EMPTY_tommRoC_json_builder_t_data_field__,    \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init a JSON builder object.
 *
 * param[in]        dataBufferPtr           JSON builder used data buffer pointer.
 * param[in]        dataBufferSize          JSON builder used data buffer size [byte].
 * param[out]       jsonBuilderPtr          output JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderInit(
                char*                                           const   dataBufferPtr,
        const   uint16_t                                                dataBufferSize,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Clean a JSON builder object.
 *
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderClear(
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add a null field to a JSON builder object.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return daos_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddNull(
        const   char*                                           const   fieldNameStrPtr,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add a null field array to a JSON builder object.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        nullArrayElAmnt         null array elements amount.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddNullArray(
        const   char*                                           const   fieldNameStrPtr,
        const   uint16_t                                                nullArrayElAmnt,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add a string to a JSON builder object.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        valueStrPtr             value string pointer.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddString(
        const   char*                                           const   fieldNameStrPtr,
        const   char*                                           const   valueStrPtr,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add a string (with known length) to a JSON builder object.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        valueStrPtr             value string pointer.
 * param[in]        valueStrLen             value string length [byte].
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddStringLen(
        const   char*                                           const   fieldNameStrPtr,
        const   char*                                           const   valueStrPtr,
        const   uint16_t                                                valueStrLen,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add a string array to a JSON builder object.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        valueArrayStrPtr        value string array pointer.
 * param[in]        valueArrayElAmnt        value array elements amount.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddStringArray(
        const   char*                                           const   fieldNameStrPtr,
        const   char**                                          const   valueArrayStrPtr,
        const   uint16_t                                                valueArrayElAmnt,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add a string (with known length) array to a JSON builder object.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        valueArrayStrPtr        value string array pointer.
 * param[in]        valueArrayStrLenPtr     value string length [byte] array pointer.
 * param[in]        valueArrayElAmnt        value array elements amount.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddStringLenArray(
        const   char*                                           const   fieldNameStrPtr,
        const   char**                                          const   valueArrayStrPtr,
        const   uint16_t*                                       const   valueArrayStrLenPtr,
        const   uint16_t                                                valueArrayElAmnt,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add an unsigned number to a JSON builder object.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        value                   number value.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddUnsignedNumber(
        const   char*                                           const   fieldNameStrPtr,
        const   uint32_t                                                value,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add an unsigned number array to a JSON builder object.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        valueArrayPtr           number value array pointer.
 * param[in]        valueArrayElAmnt        number value array elements amount.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddUnsignedNumberArray(
        const   char*                                           const   fieldNameStrPtr,
        const   uint32_t*                                       const   valueArrayPtr,
        const   uint16_t                                                valueArrayElAmnt,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add an unsigned number array to a JSON builder object - uint8_t data based.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        valueArrayPtr           number value array pointer.
 * param[in]        valueArrayElAmnt        number value array elements amount.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddUnsignedNumberArrayU8(
        const   char*                                           const   fieldNameStrPtr,
        const   uint8_t*                                        const   valueArrayPtr,
        const   uint16_t                                                valueArrayElAmnt,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add an unsigned number array to a JSON builder object - uint16_t data based.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        valueArrayPtr           number value array pointer.
 * param[in]        valueArrayElAmnt        number value array elements amount.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddUnsignedNumberArrayU16(
        const   char*                                           const   fieldNameStrPtr,
        const   uint16_t*                                       const   valueArrayPtr,
        const   uint16_t                                                valueArrayElAmnt,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add a signed number to a JSON builder object.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        value                   number value.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddSignedNumber(
        const   char*                                           const   fieldNameStrPtr,
        const   int32_t                                                 value,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add a signed number array to a JSON builder object.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        valueArrayPtr           number value array pointer.
 * param[in]        valueArrayElAmnt        number value array elements amount.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddSignedNumberArray(
        const   char*                                           const   fieldNameStrPtr,
        const   int32_t*                                        const   valueArrayPtr,
        const   uint16_t                                                valueArrayElAmnt,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add a signed number array to a JSON builder object - int8_t data based.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        valueArrayPtr           number value array pointer.
 * param[in]        valueArrayElAmnt        number value array elements amount.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddSignedNumberArrayI8(
        const   char*                                           const   fieldNameStrPtr,
        const   int8_t*                                         const   valueArrayPtr,
        const   uint16_t                                                valueArrayElAmnt,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add a signed number array to a JSON builder object - int16_t data based.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        valueArrayPtr           number value array pointer.
 * param[in]        valueArrayElAmnt        number value array elements amount.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddSignedNumberArrayI16(
        const   char*                                           const   fieldNameStrPtr,
        const   int16_t*                                        const   valueArrayPtr,
        const   uint16_t                                                valueArrayElAmnt,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add a float number to a JSON builder object.
 * NOTE: default decimal digit amount (3) version.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        value                   number value.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddFloatNumber(
        const   char*                                           const   fieldNameStrPtr,
        const   float                                                   value,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add a float number to a JSON builder object.
 * NOTE: decimal digit amount parameter version.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        value                   number value.
 * param[in]        decDgtAmount            decimal digit amount.
 * param[in]        strConvZero             remove not significant zeros.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 *
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddDecimalDigitAmountFloatNumber(
        const   char*                                           const   fieldNameStrPtr,
        const   float                                                   value,
        const   uint8_t                                                 decDgtAmount,
        const   tommRoC_string_float_to_str_conv_zero_enum_t            strConvZero,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add a float number array to a JSON builder object.
 * NOTE: default decimal digit amount (3) version.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        valueArrayPtr           number value array pointer.
 * param[in]        valueArrayElAmnt        number value array elements amount.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddFloatNumberArray(
        const   char*                                           const   fieldNameStrPtr,
        const   float*                                          const   valueArrayPtr,
        const   uint16_t                                                valueArrayElAmnt,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add a float number array to a JSON builder object.
 * NOTE: decimal digit amount parameter version.
 * SPECIAL CASE: decimal digit amount and remove not significant zeros array amount can be different from number value array amount. They are handled with two different indexes.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        valueArrayPtr           number value array pointer.
 * param[in]        valueArrayElAmnt        number value array elements amount.
 * param[in]        decDgtAmountArrayPtr    decimal digit amount array pointer.
 * param[in]        decDgtAmountArrayElAmnt decimal digit amount array elements amount.
 * param[in]        strConvZeroArrayPtr     remove not significant zeros array pointer.
 * param[in]        strConvZeroArrayElAmnt  remove not significant zeros array elements amount.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddDecimalDigitAmountFloatNumberArray(
        const   char*                                           const   fieldNameStrPtr,
        const   float*                                          const   valueArrayPtr,
        const   uint16_t                                                valueArrayElAmnt,
        const   uint8_t*                                        const   decDgtAmountArrayPtr,
        const   uint16_t                                                decDgtAmountArrayElAmnt,
        const   tommRoC_string_float_to_str_conv_zero_enum_t*   const   strConvZeroArrayPtr,
        const   uint16_t                                                strConvZeroArrayElAmnt,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add a boolean to a JSON builder object.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        value                   boolean value.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddBool(
        const   char*                                           const   fieldNameStrPtr,
        const   bool                                                    value,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add a boolean array to a JSON builder object.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        value                   boolean value array pointer.
 * param[in]        valueArrayElAmnt        number value array elements amount.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddBoolArray(
        const   char*                                           const   fieldNameStrPtr,
        const   bool*                                           const   valueArrayPtr,
        const   uint16_t                                                valueArrayElAmnt,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add an object (JSON builder) to a JSON builder object.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        objectPtr               object (JSON builder) pointer.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddObject(
        const   char*                                           const   fieldNameStrPtr,
        const   tommRoC_json_builder_t*                         const   objectPtr,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add an object array (JSON string presentation) to a JSON builder object.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        jsonObjectStrPtr        object (JSON string presentation) string array pointer.
 * param[in]        valueArrayElAmnt        value array elements amount.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddObjectArray(
        const   char*                                           const   fieldNameStrPtr,
        const   tommRoC_json_builder_t*                         const   objectArrayPtr,
        const   uint16_t                                                valueArrayElAmnt,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add a string as object to a JSON builder object.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        strAsObjectPtr          string as object (JSON builder) pointer.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddStringAsObject(
        const   char*                                           const   fieldNameStrPtr,
        const   char*                                           const   strAsObjectPtr,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add a string (with known length) as object to a JSON builder object.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        strAsObjectPtr          string as object (JSON builder) pointer.
 * param[in]        strAsObjectLen          string as object (JSON builder) length [byte].
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddStringLenAsObject(
        const   char*                                           const   fieldNameStrPtr,
        const   char*                                           const   strAsObjectPtr,
        const   uint16_t                                                strAsObjectLen,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add a string array as object array to a JSON builder object.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        valueArrayStrPtr        value string array pointer.
 * param[in]        valueArrayElAmnt        value array elements amount.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddStringArrayAsObjectArray(
        const   char*                                           const   fieldNameStrPtr,
        const   char**                                          const   valueArrayStrPtr,
        const   uint16_t                                                valueArrayElAmnt,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Add a string (with known length) array as object array to a JSON builder object.
 *
 * param[in]        fieldNameStrPtr         field name string pointer.
 * param[in]        valueArrayStrPtr        value string array pointer.
 * param[in]        valueArrayStrLenPtr     value string length [byte] array pointer.
 * param[in]        valueArrayElAmnt        value array elements amount.
 * param[in/out]    jsonBuilderPtr          JSON builder object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONBuilderAddStringLenArrayAsObjectArray(
        const   char*                                           const   fieldNameStrPtr,
        const   char**                                          const   valueArrayStrPtr,
        const   uint16_t*                                       const   valueArrayStrLenPtr,
        const   uint16_t                                                valueArrayElAmnt,
                tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * Get the JSON string build with JSON builder object.
 *
 * param[in]        jsonBuilderPtr          JSON builder object pointer.
 *
 * return char*
 */
const char* tommRoCJSONBuilderBuild(
        const   tommRoC_json_builder_t*                         const   jsonBuilderPtr);

/**
 * @}
 */

#endif
