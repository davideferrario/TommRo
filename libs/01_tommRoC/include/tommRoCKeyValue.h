
#ifndef TOMMROC_KEY_VALUE_H_
#define TOMMROC_KEY_VALUE_H_

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
 * @defgroup tommRoCKeyValue tommRoCKeyValue
 *
 * @brief  TommRoC library key/value module
 * @author TommRo Software Department
 *
 * This module is providing key/value functionality.
 *
 * @{
 */
/*******************************************************************************
 * includes
 ******************************************************************************/
#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Key/Value with int value type
typedef struct {
    char*       key;
    int         value;
} tommRoC_key_value_int_t;

// Key/Value with bool value type
typedef struct {
    char*       key;
    bool        value;
} tommRoC_key_value_bool_t;

// Key/Value with char value type
typedef struct {
    char*       key;
    char        value;
} tommRoC_key_value_char_t;

// Key/Value with uint8_t value type
typedef struct {
    char*       key;
    uint8_t     value;
} tommRoC_key_value_u8_t;

// Key/Value with uint16_t value type
typedef struct {
    char*       key;
    uint16_t    value;
} tommRoC_key_value_u16_t;

// Key/Value with uint32_t value type
typedef struct {
    char*       key;
    uint32_t    value;
} tommRoC_key_value_u32_t;

// Key/Value with int8_t value type
typedef struct {
    char*       key;
    int8_t      value;
} tommRoC_key_value_i8_t;

// Key/Value with int16_t value type
typedef struct {
    char*       key;
    int16_t     value;
} tommRoC_key_value_i16_t;

// Key/Value with int32_t value type
typedef struct {
    char*       key;
    int32_t     value;
} tommRoC_key_value_i32_t;

// Key/Value with float value type
typedef struct {
    char*       key;
    float       value;
} tommRoC_key_value_float_t;

// Key/Value with string (char* '\0' terminated) value type
typedef struct {
    char*       key;
    char*       value;
} tommRoC_key_value_string_t;


// Key/Value with void pointer value type
typedef struct {
    char*       key;
    struct {
        void*       dataPtr;
        uint32_t    dataSize;   // Data size [byte]
    }           value;
} tommRoC_key_value_void_ptr_t;

// Key/Value with int pointer value type
typedef struct {
    char*       key;
    struct {
        int*        dataPtr;
        uint32_t    dataSize;   // Data size [byte]
    }           value;
} tommRoC_key_value_int_ptr_t;

// Key/Value with bool pointer value type
typedef struct {
    char*       key;
    struct {
        bool*       dataPtr;
        uint32_t    dataSize;   // Data size [byte]
    }           value;
} tommRoC_key_value_bool_ptr_t;

// Key/Value with bool pointer value type
typedef struct {
    char*       key;
    struct {
        char*       dataPtr;
        uint32_t    dataSize;   // Data size [byte]
    }           value;
} tommRoC_key_value_char_ptr_t;

// Key/Value with uint8_t pointer value type
typedef struct {
    char*       key;
    struct {
        uint8_t*    dataPtr;
        uint32_t    dataSize;   // Data size [byte]
    }           value;
} tommRoC_key_value_u8_ptr_t;

// Key/Value with uint16_t pointer value type
typedef struct {
    char*       key;
    struct {
        uint16_t*   dataPtr;
        uint32_t    dataSize;   // Data size [byte]
    }           value;
} tommRoC_key_value_u16_ptr_t;

// Key/Value with uint32_t pointer value type
typedef struct {
    char*       key;
    struct {
        uint32_t*   dataPtr;
        uint32_t    dataSize;   // Data size [byte]
    }           value;
} tommRoC_key_value_u32_ptr_t;

// Key/Value with int8_t pointer value type
typedef struct {
    char*       key;
    struct {
        int8_t*     dataPtr;
        uint32_t    dataSize;   // Data size [byte]
    }           value;
} tommRoC_key_value_i8_ptr_t;

// Key/Value with iint16_t pointer value type
typedef struct {
    char*       key;
    struct {
        int16_t*    dataPtr;
        uint32_t    dataSize;   // Data size [byte]
    }           value;
} tommRoC_key_value_i16_ptr_t;

// Key/Value with int32_t pointer value type
typedef struct {
    char*       key;
    struct {
        int32_t*    dataPtr;
        uint32_t    dataSize;   // Data size [byte]
    }           value;
} tommRoC_key_value_i32_ptr_t;

// Key/Value with float pointer value type
typedef struct {
    char*       key;
    struct {
        float*      dataPtr;
        uint32_t    dataSize;   // Data size [byte]
    }           value;
} tommRoC_key_value_float_ptr_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * @}
 */

#endif
