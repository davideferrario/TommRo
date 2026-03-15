
#ifndef TOMMROC_JSON_PARSER_H_
#define TOMMROC_JSON_PARSER_H_

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
 * @defgroup tommRoCJSONParser tommRoCJSONParser
 *
 * @brief  TommRoC library JSON parser module
 * @author TommRo Software Department
 *
 * This module is providing JSON parser functionality.
 * JSON builder is a module to extract data from JSON formatted strings.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "JSON/tommRoCJSONDEF.h"

#include "tommRoCErr.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* JSON string functions */

/**
 * Parse a JSON token array and extract a string value.
 *
 * param[in]        jsonStringPtr           input JSON string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        tokenArrayPtr           JSON token array pointer.
 * param[in]        tokenArrayEAmount       JSON token array element amount.
 * param[in]        fieldNameStrPtr         to be extracted field name string pointer.
 * param[out]       stringValuePtr          string value pointer [NOTE: string will be terminated with '\0'].
 * param[in]        stringValueMaxSize      string value max size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONParserExtractString(
        const   char*                       const   jsonStringPtr,
        const   tommRoC_json_def_token_t*   const   tokenArrayPtr,
        const   uint16_t                            tokenArrayEAmount,
        const   char*                       const   fieldNameStrPtr,
                char*                       const   stringValuePtr,
        const   uint16_t                            stringValueMaxSize);

/**
 * Parse a JSON token array and extract a boolean value.
 *
 * param[in]        jsonStringPtr           input JSON string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        tokenArrayPtr           JSON token array pointer.
 * param[in]        tokenArrayEAmount       JSON token array element amount.
 * param[in]        fieldNameStrPtr         to be extracted field name string pointer.
 * param[out]       valuePtr                boolean value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONParserExtractBool(
        const   char*                       const   jsonStringPtr,
        const   tommRoC_json_def_token_t*   const   tokenArrayPtr,
        const   uint16_t                            tokenArrayEAmount,
        const   char*                       const   fieldNameStrPtr,
                bool*                       const   valuePtr);

/**
 * Parse a JSON token array and extract a uint32_t value.
 *
 * param[in]        jsonStringPtr           input JSON string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        tokenArrayPtr           JSON token array pointer.
 * param[in]        tokenArrayEAmount       JSON token array element amount.
 * param[in]        fieldNameStrPtr         to be extracted field name string pointer.
 * param[out]       valuePtr                uint32_t value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONParserExtractU32(
        const   char*                       const   jsonStringPtr,
        const   tommRoC_json_def_token_t*   const   tokenArrayPtr,
        const   uint16_t                            tokenArrayEAmount,
        const   char*                       const   fieldNameStrPtr,
                uint32_t*                   const   valuePtr);

/**
 * Parse a JSON token array and extract a int32_t value.
 *
 * param[in]        jsonStringPtr           input JSON string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        tokenArrayPtr           JSON token array pointer.
 * param[in]        tokenArrayEAmount       JSON token array element amount.
 * param[in]        fieldNameStrPtr         to be extracted field name string pointer.
 * param[out]       valuePtr                int32_t value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONParserExtractI32(
        const   char*                       const   jsonStringPtr,
        const   tommRoC_json_def_token_t*   const   tokenArrayPtr,
        const   uint16_t                            tokenArrayEAmount,
        const   char*                       const   fieldNameStrPtr,
                int32_t*                    const   valuePtr);

/**
 * Parse a JSON token array and extract a float value.
 *
 * param[in]        jsonStringPtr           input JSON string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        tokenArrayPtr           JSON token array pointer.
 * param[in]        tokenArrayEAmount       JSON token array element amount.
 * param[in]        fieldNameStrPtr         to be extracted field name string pointer.
 * param[out]       valuePtr                float value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONParserExtractFloat(
        const   char*                       const   jsonStringPtr,
        const   tommRoC_json_def_token_t*   const   tokenArrayPtr,
        const   uint16_t                            tokenArrayEAmount,
        const   char*                       const   fieldNameStrPtr,
                float*                      const   valuePtr);

/**
 * Parse a JSON token array and extract a JSON object (as JSON string).
 * NOTE: characters '{' and '}' at the beginning and end of the string are included in result.
 *
 * param[in]        jsonStringPtr           input JSON string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        tokenArrayPtr           JSON token array pointer.
 * param[in]        tokenArrayEAmount       JSON token array element amount.
 * param[in]        fieldNameStrPtr         to be extracted field name string pointer.
 * param[out]       jsonObjStringPtr        JSON object (as JSON string) pointer [NOTE: string will be terminated with '\0'].
 * param[in]        jsonObjStringMaxSize    JSON object (as JSON string) buffer max size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONParserExtractObject(
        const   char*                       const   jsonStringPtr,
        const   tommRoC_json_def_token_t*   const   tokenArrayPtr,
        const   uint16_t                            tokenArrayEAmount,
        const   char*                       const   fieldNameStrPtr,
                char*                       const   jsonObjStringPtr,
        const   uint16_t                            jsonObjStringMaxSize);

/**
 * Parse a JSON token array and extract a JSON array (as JSON string).
 * NOTE: characters '[' and ']' at the beginning and end of the string are included in result.
 *
 * param[in]        jsonStringPtr           input JSON string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        tokenArrayPtr           JSON token array pointer.
 * param[in]        tokenArrayEAmount       JSON token array element amount.
 * param[in]        fieldNameStrPtr         to be extracted field name string pointer.
 * param[out]       jsonArrayStringPtr      JSON array (as JSON string) pointer [NOTE: string will be terminated with '\0'].
 * param[in]        jsonArrayStringMaxSize  JSON array (as JSON string) buffer max size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONParserExtractArray(
        const   char*                       const   jsonStringPtr,
        const   tommRoC_json_def_token_t*   const   tokenArrayPtr,
        const   uint16_t                            tokenArrayEAmount,
        const   char*                       const   fieldNameStrPtr,
                char*                       const   jsonArrayStringPtr,
        const   uint16_t                            jsonArrayStringMaxSize);


/******************* JSON string with length functions */

/**
 * Parse a JSON token array and extract a string value.
 *
 * param[in]        jsonStringPtr           input JSON string pointer.
 * param[in]        jsonStringLen           JSON string length [byte].
 * param[in]        tokenArrayPtr           JSON token array pointer.
 * param[in]        tokenArrayEAmount       JSON token array element amount.
 * param[in]        fieldNameStrPtr         to be extracted field name string pointer.
 * param[out]       stringValuePtr          string value pointer [NOTE: string will be terminated with '\0'].
 * param[in]        stringValueMaxSize      string value max size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONParserLenExtractString(
        const   char*                       const   jsonStringPtr,
        const   uint16_t                            jsonStringLen,
        const   tommRoC_json_def_token_t*   const   tokenArrayPtr,
        const   uint16_t                            tokenArrayEAmount,
        const   char*                       const   fieldNameStrPtr,
                char*                       const   stringValuePtr,
        const   uint16_t                            stringValueMaxSize);

/**
 * Parse a JSON token array and extract a boolean value.
 *
 * param[in]        jsonStringPtr           input JSON string pointer.
 * param[in]        jsonStringLen           JSON string length [byte].
 * param[in]        tokenArrayPtr           JSON token array pointer.
 * param[in]        tokenArrayEAmount       JSON token array element amount.
 * param[in]        fieldNameStrPtr         to be extracted field name string pointer.
 * param[out]       valuePtr                boolean value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONParserLenExtractBool(
        const   char*                       const   jsonStringPtr,
        const   uint16_t                            jsonStringLen,
        const   tommRoC_json_def_token_t*   const   tokenArrayPtr,
        const   uint16_t                            tokenArrayEAmount,
        const   char*                       const   fieldNameStrPtr,
                bool*                       const   valuePtr);

/**
 * Parse a JSON token array and extract a uint32_t value.
 *
 * param[in]        jsonStringPtr           input JSON string pointer.
 * param[in]        jsonStringLen           JSON string length [byte].
 * param[in]        tokenArrayPtr           JSON token array pointer.
 * param[in]        tokenArrayEAmount       JSON token array element amount.
 * param[in]        fieldNameStrPtr         to be extracted field name string pointer.
 * param[out]       valuePtr                uint32_t value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONParserLenExtractU32(
        const   char*                       const   jsonStringPtr,
        const   uint16_t                            jsonStringLen,
        const   tommRoC_json_def_token_t*   const   tokenArrayPtr,
        const   uint16_t                            tokenArrayEAmount,
        const   char*                       const   fieldNameStrPtr,
                uint32_t*                   const   valuePtr);

/**
 * Parse a JSON token array and extract a int32_t value.
 *
 * param[in]        jsonStringPtr           input JSON string pointer.
 * param[in]        jsonStringLen           JSON string length [byte].
 * param[in]        tokenArrayPtr           JSON token array pointer.
 * param[in]        tokenArrayEAmount       JSON token array element amount.
 * param[in]        fieldNameStrPtr         to be extracted field name string pointer.
 * param[out]       valuePtr                int32_t value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONParserLenExtractI32(
        const   char*                       const   jsonStringPtr,
        const   uint16_t                            jsonStringLen,
        const   tommRoC_json_def_token_t*   const   tokenArrayPtr,
        const   uint16_t                            tokenArrayEAmount,
        const   char*                       const   fieldNameStrPtr,
                int32_t*                    const   valuePtr);

/**
 * Parse a JSON token array and extract a float value.
 *
 * param[in]        jsonStringPtr           input JSON string pointer.
 * param[in]        jsonStringLen           JSON string length [byte].
 * param[in]        tokenArrayPtr           JSON token array pointer.
 * param[in]        tokenArrayEAmount       JSON token array element amount.
 * param[in]        fieldNameStrPtr         to be extracted field name string pointer.
 * param[out]       valuePtr                float value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONParserLenExtractFloat(
        const   char*                       const   jsonStringPtr,
        const   uint16_t                            jsonStringLen,
        const   tommRoC_json_def_token_t*   const   tokenArrayPtr,
        const   uint16_t                            tokenArrayEAmount,
        const   char*                       const   fieldNameStrPtr,
                float*                      const   valuePtr);

/**
 * Parse a JSON token array and extract a JSON object (as JSON string).
 * NOTE: characters '{' and '}' at the beginning and end of the string are included in result.
 *
 * param[in]        jsonStringPtr           input JSON string pointer.
 * param[in]        jsonStringLen           JSON string length [byte].
 * param[in]        tokenArrayPtr           JSON token array pointer.
 * param[in]        tokenArrayEAmount       JSON token array element amount.
 * param[in]        fieldNameStrPtr         to be extracted field name string pointer.
 * param[out]       jsonObjStringPtr        JSON object (as JSON string) pointer [NOTE: string will be terminated with '\0'].
 * param[in]        jsonObjStringMaxSize    JSON object (as JSON string) buffer max size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONParserLenExtractObject(
        const   char*                       const   jsonStringPtr,
        const   uint16_t                            jsonStringLen,
        const   tommRoC_json_def_token_t*   const   tokenArrayPtr,
        const   uint16_t                            tokenArrayEAmount,
        const   char*                       const   fieldNameStrPtr,
                char*                       const   jsonObjStringPtr,
        const   uint16_t                            jsonObjStringMaxSize);

/**
 * Parse a JSON token array and extract a JSON array (as JSON string).
 * NOTE: characters '[' and ']' at the beginning and end of the string are included in result.
 *
 * param[in]        jsonStringPtr           input JSON string pointer.
 * param[in]        jsonStringLen           JSON string length [byte].
 * param[in]        tokenArrayPtr           JSON token array pointer.
 * param[in]        tokenArrayEAmount       JSON token array element amount.
 * param[in]        fieldNameStrPtr         to be extracted field name string pointer.
 * param[out]       jsonArrayStringPtr      JSON array (as JSON string) pointer [NOTE: string will be terminated with '\0'].
 * param[in]        jsonArrayStringMaxSize  JSON array (as JSON string) buffer max size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONParserLenExtractArray(
        const   char*                       const   jsonStringPtr,
        const   uint16_t                            jsonStringLen,
        const   tommRoC_json_def_token_t*   const   tokenArrayPtr,
        const   uint16_t                            tokenArrayEAmount,
        const   char*                       const   fieldNameStrPtr,
                char*                       const   jsonArrayStringPtr,
        const   uint16_t                            jsonArrayStringMaxSize);

/**
 * @}
 */

#endif
