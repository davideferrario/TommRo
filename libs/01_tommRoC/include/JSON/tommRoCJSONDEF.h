
#ifndef TOMMROC_JSON_DEF_H_
#define TOMMROC_JSON_DEF_H_

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
 * @defgroup tommRoCJSONDEF tommRoCJSONDEF
 *
 * @brief  TommRoC library JSON define module
 * @author TommRo Software Department
 *
 * This module is providing JSON define and functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCEnv.h"
#include "tommRoCUtil.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// JSON token struct size.
#if defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_8_BIT_SIZE)
#define TOMMROC_JSON_DEF_TOKEN_HANDLE_SIZE  (10)

#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_16_BIT_SIZE)
#define TOMMROC_JSON_DEF_TOKEN_HANDLE_SIZE  (10)

#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE)
#define TOMMROC_JSON_DEF_TOKEN_HANDLE_SIZE  (20)

#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE)
#define TOMMROC_JSON_DEF_TOKEN_HANDLE_SIZE  (20)
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC JSON identifier type.
typedef enum {

    // JSON type is undefined.
    TOMMROC_JSON_DEF_UNDEFINED = 0,

    // JSON type is object.
    TOMMROC_JSON_DEF_OBJECT,

    // JSON type is array.
    TOMMROC_JSON_DEF_ARRAY,

    // JSON type is string.
    TOMMROC_JSON_DEF_STRING,

    // JSON type is primitive (number, boolean [true/false] or NULL).
    TOMMROC_JSON_DEF_PRIMITIVE,

} tommRoC_json_def_id_type_enum_t;


// tommRoC JSON token struct.
typedef struct {
    uint8_t data[TOMMROC_JSON_DEF_TOKEN_HANDLE_SIZE];
} tommRoC_json_def_token_t;

#define __EMPTY_tommRoC_json_def_token_t_data_field__           TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_JSON_DEF_TOKEN_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_json_def_token_t__                      \
{                                                               \
    /* .data */ __EMPTY_tommRoC_json_def_token_t_data_field__,  \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * @}
 */

#endif
