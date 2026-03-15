
#ifndef TOMMROC_LIST_H_
#define TOMMROC_LIST_H_

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
 * @defgroup tommRoCList tommRoCList
 *
 * @brief  TommRoC library list module
 * @author TommRo Software Department
 *
 * This module is providing list functionality.
 *
 * List is a buffer where it can be added/removed/searched an element.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCGuard.h"
#include "tommRoCUtil.h"

#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

#define TOMMROC_LIST_MIN_BUF_SIZE   (1)

// tommRoC list.
#define TOMMROC_LIST_HANDLE_SIZE    (   TOMMROC_UTIL_U32_SIZE   +   \
                                        TOMMROC_UTIL_U32_SIZE   +   \
                                        TOMMROC_UTIL_U32_SIZE   +   \
                                        TOMMROC_UTIL_PTR_SIZE   +   \
                                        TOMMROC_UTIL_PTR_SIZE       )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC list.
typedef struct {
    uint8_t data[TOMMROC_LIST_HANDLE_SIZE];
} tommRoC_list_t;

#define __EMPTY_tommRoC_list_t_data_field__             TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_LIST_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_list_t__                        \
{                                                       \
    /* .data */ __EMPTY_tommRoC_list_t_data_field__,    \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init a list struct.
 *
 * param[in]        objBaseSize             list object size [byte].
 * param[in]        bufferPtr               list buffer pointer.
 * param[in]        bufferSize              list buffer size [byte].
 * param[in]        guardPtr                list guard pointer (set to NULL to disable).
 * param[out]       listPtr                 list handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCListInit(
        const   uint32_t                    objBaseSize,
                void*               const   bufferPtr,
        const   uint32_t                    bufferSize,
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_list_t*     const   listPtr);

/**
 * Add an object.
 * NOTE: duplicate object are not error.
 *
 * param[in/out]    listPtr                 list handle pointer.
 * param[in]        dataBufferPtr           list object data pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCListAdd(
                tommRoC_list_t*     const   listPtr,
        const   void*               const   dataBufferPtr);

/**
 * Remove an object (starting from element data).
 *
 * param[in/out]    listPtr                 list handle pointer.
 * param[in]        dataBufferPtr           list object data pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCListRemove(
                tommRoC_list_t*     const   listPtr,
        const   void*               const   dataBufferPtr);

/**
 * Remove an object (starting from element index).
 *
 * param[in/out]    listPtr                 list handle pointer.
 * param[in]        elemIdx                 element list index.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCListRemoveIdx(
                tommRoC_list_t*     const   listPtr,
        const   uint32_t                    elemIdx);

/**
 * Search for an object.
 *
 * param[in]        listPtr                 list handle pointer.
 * param[in]        dataBufferPtr           list object data pointer.
 * param[out]       elemIdxPtr              element list index pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCListSearch(
        const   tommRoC_list_t*     const   listPtr,
        const   void*               const   dataBufferPtr,
                uint32_t*           const   elemIdxPtr);

/**
 * Get an object (by element index).
 *
 * param[in]        listPtr                 list handle pointer.
 * param[in]        elemIdx                 element list index.
 * param[out]       dataBufferPtr           list object data pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCListGetIdx(
        const   tommRoC_list_t*     const   listPtr,
        const   uint32_t                    elemIdx,
                void*               const   dataBufferPtr);

/**
 * Get an object (by element index) pointer.
 *
 * param[in]        listPtr                 list handle pointer.
 * param[in]        elemIdx                 element list index.
 * param[out]       dataBufferPtr           pointer to list object data pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCListGetPtrIdx(
        const   tommRoC_list_t*     const   listPtr,
        const   uint32_t                    elemIdx,
                void**              const   dataBufferPtr);

/**
 * Clear a list struct.
 *
 * param[in/out]    listPtr                 list handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCListClear(
                tommRoC_list_t*     const   listPtr);

/**
 * Get empty status of a list struct.
 *
 * param[in]        listPtr                 list handle pointer.
 *
 * return bool
 */
bool tommRoCListIsEmpty(
        const   tommRoC_list_t*     const   listPtr);

/**
 * Get objects amount in a list struct.
 *
 * param[in]        listPtr                 list handle pointer.
 * param[out]       amountPtr               inside objects amount pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCListInsideObjAmount(
        const   tommRoC_list_t*     const   listPtr,
                uint32_t*           const   amountPtr);

/**
 * Get free objects amount in a list struct.
 *
 * param[in]        listPtr                 list handle pointer.
 * param[out]       amountPtr               free objects amount pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCListFreeObjAmount(
        const   tommRoC_list_t*     const   listPtr,
                uint32_t*           const   amountPtr);

/**
 * @}
 */

#endif
