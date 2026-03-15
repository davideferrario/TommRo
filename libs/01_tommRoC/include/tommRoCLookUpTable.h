
#ifndef TOMMROC_LOOKUP_TABLE_H_
#define TOMMROC_LOOKUP_TABLE_H_

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
 * @defgroup tommRoCLookUpTable tommRoCLookUpTable
 *
 * @brief  TommRoC library look up table module
 * @author TommRo Software Department
 *
 * This module is providing look up table functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCUtil.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

#define TOMMROC_LOOKUP_TABLE_DECLARE_KEY(type, var, initKey)                                \
        static const type var = initKey

#define TOMMROC_LOOKUP_TABLE_DECLARE_SIMPLE_VALUE(type, var, initValue)                     \
        static const type var = initValue

#define TOMMROC_LOOKUP_TABLE_DECLARE_FUNCT_POINTER_VALUE(outType, var, initValue)           \
        static outType var = initValue

#define TOMMROC_LOOKUP_TABLE_TABLE_ELEMENT(key, value)                                      \
        { &key, sizeof(key), &value, sizeof(value), }

#define TOMMROC_LOOKUP_TABLE_DECLARE_TABLE(var)                                             \
        static const tommRoC_look_up_table_element_handle_t __ ## var ## _elements__[] =    \
                { __TOMMRO_C_VA_ARGS__ };                                                   \
                                                                                            \
        static const tommRoC_look_up_table_handle_t var =                                   \
                {                                                                           \
                    __ ## var ## _elements__,                                               \
                    TOMMROC_UTIL_ARR_EAMOUNT(__ ## var ## _elements__),                     \
                }

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC look up table element handle.
typedef struct {

    const void* const   keyPtr;
    const uint8_t       keySize;

    const void* const   valuePtr;
    const uint8_t       valueSize;

} tommRoC_look_up_table_element_handle_t;

#define __EMPTY_tommRoC_look_up_table_element_handle_t__    \
{                                                           \
    /* .keyPtr */       NULL,                               \
    /* .keySize */      0,                                  \
    /* .valuePtr */     NULL,                               \
    /* .valueSize */    0,                                  \
}


// tommRoC look up table handle.
typedef struct {

    const tommRoC_look_up_table_element_handle_t* const elements;
    const uint8_t                                       elementsAmount;

} tommRoC_look_up_table_handle_t;

#define __EMPTY_tommRoC_look_up_table_handle_t__    \
{                                                   \
    /* .elements */         NULL,                   \
    /* .elementsAmount */   0,                      \
}


/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Search a key inside a look up table struct.
 *
 * param[in]        lookUpTablePtr          look up table handle.
 * param[in]        keyPtr                  key pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLookUpTableSearchKey(
        const   tommRoC_look_up_table_handle_t* const   lookUpTablePtr,
        const   void*                           const   keyPtr);


/**
 * Search a value inside a look up table struct.
 *
 * param[in]        lookUpTablePtr          look up table handle.
 * param[in]        valuePtr                value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLookUpTableSearchValue(
        const   tommRoC_look_up_table_handle_t* const   lookUpTablePtr,
        const   void*                           const   valuePtr);


/**
 * Get a value indexed by a key from a look up table struct.
 *
 * param[in]        lookUpTablePtr          look up table handle.
 * param[in]        keyPtr                  key pointer.
 * param[out]       valuePtr                value result pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLookUpTableGetValue(
        const   tommRoC_look_up_table_handle_t* const   lookUpTablePtr,
        const   void*                           const   keyPtr,
                void*                           const   valuePtr);

/**
 * @}
 */

#endif
