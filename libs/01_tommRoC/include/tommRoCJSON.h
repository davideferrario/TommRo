
#ifndef TOMMROC_JSON_H_
#define TOMMROC_JSON_H_

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
 * @defgroup tommRoCJSON tommRoCJSON
 *
 * @brief  TommRoC library JSON module
 * @author TommRo Software Department
 *
 * This module is providing JSON parser functionality.
 * Please note that it is based on jsmn (https://github.com/zserge/jsmn) library.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "JSON/tommRoCJSONBuilder.h"
#include "JSON/tommRoCJSONParser.h"

#include "JSON/tommRoCJSONDEF.h"

#include "tommRoCEnv.h"
#include "tommRoCErr.h"
#include "tommRoCUtil.h"

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

/**
 * Parse a JSON string and extract tokens.
 *
 * param[in]        jsonStringPtr           input JSON string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        jsonStringLen           JSON string length [byte].
 * param[out]       tokenArrayPtr           output token array pointer.
 * param[in]        tokenArrayMaxAmount     token array max amount [unit].
 * param[out]       tokenAmountPtr          amount of token into output array [unit].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONParse(
        const   char*                       const   jsonStringPtr,
        const   uint16_t                            jsonStringLen,
                tommRoC_json_def_token_t*   const   tokenArrayPtr,
        const   uint16_t                            tokenArrayMaxAmount,
                uint16_t*                   const   tokenAmountPtr);

/**
 * Parse a JSON string and extract tokens.
 *
 * param[in]        jsonStringPtr           input JSON string pointer [NOTE: string have to be terminated with '\0'].
 * param[out]       tokenArrayPtr           output token array pointer.
 * param[in]        tokenArrayMaxAmount     token array max amount [unit].
 * param[out]       tokenAmountPtr          amount of token into output array [unit].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONParseString(
        const   char*                       const   jsonStringPtr,
                tommRoC_json_def_token_t*   const   tokenArrayPtr,
        const   uint16_t                            tokenArrayMaxAmount,
                uint16_t*                   const   tokenAmountPtr);

/**
 * Get JSON identifier type/start index in JSON string/end index from JSON token.
 *
 * param[in]        tokenPtr                token pointer.
 *
 * return tommRoC_json_def_id_type_enum_t/uint16_t
 */
tommRoC_json_def_id_type_enum_t tommRoCJSONTokenGetIDType(const tommRoC_json_def_token_t* const tokenPtr);
uint16_t tommRoCJSONTokenGetStartIdx(const tommRoC_json_def_token_t* const tokenPtr);
uint16_t tommRoCJSONTokenGetEndIdx(const tommRoC_json_def_token_t* const tokenPtr);

/**
 * Extract JSON string object from JSON token.
 *
 * param[in]        jsonStringPtr           input JSON string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        tokenPtr                token pointer.
 * param[out]       stringPtr               JSON string object pointer [NOTE: string will be terminated with '\0'].
 * param[in]        stringMaxSize           JSON string buffer max size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONTokenExtractString(
        const   char*                       const   jsonStringPtr,
        const   tommRoC_json_def_token_t*   const   tokenPtr,
                char*                       const   stringPtr,
        const   uint16_t                            stringMaxSize);

/**
 * Extract JSON primitive object (as boolean) from JSON token.
 *
 * param[in]        jsonStringPtr           input JSON string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        tokenPtr                token pointer.
 * param[out]       primitivePtr            JSON primitive object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONTokenExtractPrimitiveBool(
        const   char*                       const   jsonStringPtr,
        const   tommRoC_json_def_token_t*   const   tokenPtr,
                bool*                       const   primitivePtr);

/**
 * Extract JSON primitive object (as uint32_t) from JSON token.
 *
 * param[in]        jsonStringPtr           input JSON string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        tokenPtr                token pointer.
 * param[out]       primitivePtr            JSON primitive object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONTokenExtractPrimitiveU32(
        const   char*                       const   jsonStringPtr,
        const   tommRoC_json_def_token_t*   const   tokenPtr,
                uint32_t*                   const   primitivePtr);

/**
 * Extract JSON primitive object (as int32_t) from JSON token.
 *
 * param[in]        jsonStringPtr           input JSON string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        tokenPtr                token pointer.
 * param[out]       primitivePtr            JSON primitive object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONTokenExtractPrimitiveI32(
        const   char*                       const   jsonStringPtr,
        const   tommRoC_json_def_token_t*   const   tokenPtr,
                int32_t*                    const   primitivePtr);

/**
 * Extract JSON primitive object (as float) from JSON token.
 *
 * param[in]        jsonStringPtr           input JSON string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        tokenPtr                token pointer.
 * param[out]       primitivePtr            JSON primitive object pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONTokenExtractPrimitiveFloat(
        const   char*                       const   jsonStringPtr,
        const   tommRoC_json_def_token_t*   const   tokenPtr,
                float*                      const   primitivePtr);

/**
 * Extract JSON object (as JSON string) from JSON token.
 * NOTE: characters '{' and '}' at the beginning and end of the string are included in result.
 *
 * param[in]        jsonStringPtr           input JSON string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        tokenPtr                token pointer.
 * param[out]       jsonObjStringPtr        JSON object (as JSON string) pointer [NOTE: string will be terminated with '\0'].
 * param[in]        stringMaxSize           JSON object (as JSON string) buffer max size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONTokenExtractObject(
        const   char*                       const   jsonStringPtr,
        const   tommRoC_json_def_token_t*   const   tokenPtr,
                char*                       const   jsonObjStringPtr,
        const   uint16_t                            jsonObjStringMaxSize);

/**
 * Extract JSON array (as JSON string) from JSON token.
 * NOTE: characters '[' and ']' at the beginning and end of the string are included in result.
 *
 * param[in]        jsonStringPtr           input JSON string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        tokenPtr                token pointer.
 * param[out]       jsonArrayStringPtr      JSON array (as JSON string) pointer [NOTE: string will be terminated with '\0'].
 * param[in]        jsonArrayStringMaxSize  JSON array (as JSON string) buffer max size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCJSONTokenExtractArray(
        const   char*                       const   jsonStringPtr,
        const   tommRoC_json_def_token_t*   const   tokenPtr,
                char*                       const   jsonArrayStringPtr,
        const   uint16_t                            jsonArrayStringMaxSize);

/**
 * @}
 */

#endif
