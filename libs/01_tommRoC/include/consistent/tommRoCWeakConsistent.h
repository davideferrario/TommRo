
#ifndef TOMMROC_WEAK_CONSISTENT_H_
#define TOMMROC_WEAK_CONSISTENT_H_

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
 * @defgroup tommRoCWeakConsistent tommRoCWeakConsistent
 *
 * @brief  TommRoC library weak consistent module
 * @author TommRo Software Department
 *
 * This module is providing weak consistent variable functionality.
 *
 * A weak consistent variable is a variable with weak consistency.
 * The consistency is guaranteed by a boolean flag.
 *
 * Multi-thread consistency access is guaranteed only in get functionality.
 * Set functionality consistency access is guaranteed only if made by one thread.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCAssert.h"
#include "tommRoCErr.h"
#include "tommRoCUtil.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/
#define TOMMROC_WEAK_CONSISTENT_ARRAY_ELEM_AMOUNT   (2)

#define TOMMROC_WEAK_CONSISTENT_DECLARE_BUFFER_ELEMENT(consistentVar, elemSize)                                     \
        do {                                                                                                        \
            static uint8_t TOMMROC_UTIL_CONCAT_FOUR_ELEM_NO_EXPAND(__, consistentVar, Buffer, __)[(elemSize) * 2];  \
                                                                                                                    \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(                                                               \
                    tommRoCWeakConsistentInit(                                                                      \
                            (elemSize),                                                                             \
                            TOMMROC_UTIL_CONCAT_FOUR_ELEM_NO_EXPAND(__, consistentVar, Buffer, __),                 \
                            sizeof(TOMMROC_UTIL_CONCAT_FOUR_ELEM_NO_EXPAND(__, consistentVar, Buffer, __)),         \
                            &consistentVar));                                                                       \
        } while (0)

#define TOMMROC_WEAK_CONSISTENT_ALLOCATE_BUFFER_ELEMENT(consistentVar, elemSize)                                    \
        static tommRoC_weak_consistent_t consistentVar;                                                             \
                                                                                                                    \
        do {                                                                                                        \
            static uint8_t TOMMROC_UTIL_CONCAT_FOUR_ELEM_NO_EXPAND(__, consistentVar, Buffer, __)[(elemSize) * 2];  \
                                                                                                                    \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(                                                               \
                    tommRoCWeakConsistentInit(                                                                      \
                            (elemSize),                                                                             \
                            TOMMROC_UTIL_CONCAT_FOUR_ELEM_NO_EXPAND(__, consistentVar, Buffer, __),                 \
                            sizeof(TOMMROC_UTIL_CONCAT_FOUR_ELEM_NO_EXPAND(__, consistentVar, Buffer, __)),         \
                            &consistentVar));                                                                       \
        } while (0)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC weak consistent.
#define TOMMROC_WEAK_CONSISTENT_HANDLE_SIZE         (   TOMMROC_UTIL_BOOL_SIZE  +   \
                                                        TOMMROC_UTIL_U32_SIZE   +   \
                                                        TOMMROC_UTIL_PTR_SIZE       )

#define TOMMROC_WEAK_CONSISTENT_U16_HANDLE_SIZE     (TOMMROC_UTIL_BOOL_SIZE + (TOMMROC_UTIL_U16_SIZE    * TOMMROC_WEAK_CONSISTENT_ARRAY_ELEM_AMOUNT))
#define TOMMROC_WEAK_CONSISTENT_U32_HANDLE_SIZE     (TOMMROC_UTIL_BOOL_SIZE + (TOMMROC_UTIL_U32_SIZE    * TOMMROC_WEAK_CONSISTENT_ARRAY_ELEM_AMOUNT))
#define TOMMROC_WEAK_CONSISTENT_I16_HANDLE_SIZE     (TOMMROC_UTIL_BOOL_SIZE + (TOMMROC_UTIL_I16_SIZE    * TOMMROC_WEAK_CONSISTENT_ARRAY_ELEM_AMOUNT))
#define TOMMROC_WEAK_CONSISTENT_I32_HANDLE_SIZE     (TOMMROC_UTIL_BOOL_SIZE + (TOMMROC_UTIL_I32_SIZE    * TOMMROC_WEAK_CONSISTENT_ARRAY_ELEM_AMOUNT))
#define TOMMROC_WEAK_CONSISTENT_FLOAT_HANDLE_SIZE   (TOMMROC_UTIL_BOOL_SIZE + (TOMMROC_UTIL_FLOAT_SIZE  * TOMMROC_WEAK_CONSISTENT_ARRAY_ELEM_AMOUNT))
#define TOMMROC_WEAK_CONSISTENT_PTR_HANDLE_SIZE     (TOMMROC_UTIL_BOOL_SIZE + (TOMMROC_UTIL_PTR_SIZE    * TOMMROC_WEAK_CONSISTENT_ARRAY_ELEM_AMOUNT))


typedef struct {
    uint8_t data[TOMMROC_WEAK_CONSISTENT_HANDLE_SIZE];
} tommRoC_weak_consistent_t;

typedef struct {
    uint8_t data[TOMMROC_WEAK_CONSISTENT_U16_HANDLE_SIZE];
} tommRoC_weak_consistent_u16_t;

typedef struct {
    uint8_t data[TOMMROC_WEAK_CONSISTENT_U32_HANDLE_SIZE];
} tommRoC_weak_consistent_u32_t;

typedef struct {
    uint8_t data[TOMMROC_WEAK_CONSISTENT_I16_HANDLE_SIZE];
} tommRoC_weak_consistent_i16_t;

typedef struct {
    uint8_t data[TOMMROC_WEAK_CONSISTENT_I32_HANDLE_SIZE];
} tommRoC_weak_consistent_i32_t;

typedef struct {
    uint8_t data[TOMMROC_WEAK_CONSISTENT_FLOAT_HANDLE_SIZE];
} tommRoC_weak_consistent_float_t;

typedef struct {
    uint8_t data[TOMMROC_WEAK_CONSISTENT_PTR_HANDLE_SIZE];
} tommRoC_weak_consistent_ptr_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init a weak consistent struct.
 *
 * param[in]        elemSize                element size [byte].
 * param[in]        bufferPtr               buffer to be used pointer.
 * param[in]        bufferSize              buffer to be used size [byte]. NOTE: must be (element size * 2)
 * param[out]       weakConsistentPtr       weak consistent handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCWeakConsistentInit(
        const   uint32_t                                    elemSize,
                void*                               const   bufferPtr,
        const   uint32_t                                    bufferSize,
                tommRoC_weak_consistent_t*          const   weakConsistentPtr);

/**
 * Init a specific type weak consistent struct.
 *
 * param[out]       weakConsistentPtr       specific type weak consistent handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCWeakConsistentU16Init(tommRoC_weak_consistent_u16_t* const weakConsistentPtr);
tommRoC_err_enum_t tommRoCWeakConsistentU32Init(tommRoC_weak_consistent_u32_t* const weakConsistentPtr);
tommRoC_err_enum_t tommRoCWeakConsistentI16Init(tommRoC_weak_consistent_i16_t* const weakConsistentPtr);
tommRoC_err_enum_t tommRoCWeakConsistentI32Init(tommRoC_weak_consistent_i32_t* const weakConsistentPtr);
tommRoC_err_enum_t tommRoCWeakConsistentFloatInit(tommRoC_weak_consistent_float_t* const weakConsistentPtr);
tommRoC_err_enum_t tommRoCWeakConsistentPtrInit(tommRoC_weak_consistent_ptr_t* const weakConsistentPtr);

/**
 * Set element of weak consistent struct.
 *
 * param[in/out]    weakConsistentPtr       weak consistent handle pointer.
 * param[in]        bufferPtr               element buffer pointer.
 * param[in]        elemSize                element size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCWeakConsistentSet(
                tommRoC_weak_consistent_t*          const   weakConsistentPtr,
        const   void*                               const   bufferPtr,
        const   uint32_t                                    elemSize);

/**
 * Set element of a specific type weak consistent struct.
 *
 * param[in/out]    weakConsistentPtr       specific type weak consistent handle pointer.
 * param[in]        value                   value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCWeakConsistentU16Set(
                tommRoC_weak_consistent_u16_t*      const   weakConsistentPtr,
        const   uint16_t                                    value);
tommRoC_err_enum_t tommRoCWeakConsistentU32Set(
                tommRoC_weak_consistent_u32_t*      const   weakConsistentPtr,
        const   uint32_t                                    value);
tommRoC_err_enum_t tommRoCWeakConsistentI16Set(
                tommRoC_weak_consistent_i16_t*      const   weakConsistentPtr,
        const   int16_t                                     value);
tommRoC_err_enum_t tommRoCWeakConsistentI32Set(
                tommRoC_weak_consistent_i32_t*      const   weakConsistentPtr,
        const   int32_t                                     value);
tommRoC_err_enum_t tommRoCWeakConsistentFloatSet(
                tommRoC_weak_consistent_float_t*    const   weakConsistentPtr,
        const   float                                       value);
tommRoC_err_enum_t tommRoCWeakConsistentPtrSet(
                tommRoC_weak_consistent_ptr_t*      const   weakConsistentPtr,
        const   void*                               const   value);

/**
 * Get element of weak consistent struct.
 *
 * param[in]        weakConsistentPtr       weak consistent handle pointer.
 * param[out]       bufferPtr               element buffer pointer.
 * param[in]        elemSize                element size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCWeakConsistentGet(
        const   tommRoC_weak_consistent_t*          const   weakConsistentPtr,
                void*                               const   bufferPtr,
        const   uint32_t                                    elemSize);

/**
 * Get element of a specific type weak consistent struct.
 *
 * param[in]        weakConsistentPtr       specific type weak consistent handle pointer.
 * param[out]       valuePtr                value pointer.

 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCWeakConsistentU16Get(
        const   tommRoC_weak_consistent_u16_t*      const   weakConsistentPtr,
                uint16_t*                           const   valuePtr);
tommRoC_err_enum_t tommRoCWeakConsistentU32Get(
        const   tommRoC_weak_consistent_u32_t*      const   weakConsistentPtr,
                uint32_t*                           const   valuePtr);
tommRoC_err_enum_t tommRoCWeakConsistentI16Get(
        const   tommRoC_weak_consistent_i16_t*      const   weakConsistentPtr,
                int16_t*                            const   valuePtr);
tommRoC_err_enum_t tommRoCWeakConsistentI32Get(
        const   tommRoC_weak_consistent_i32_t*      const   weakConsistentPtr,
                int32_t*                            const   valuePtr);
tommRoC_err_enum_t tommRoCWeakConsistentFloatGet(
        const   tommRoC_weak_consistent_float_t*    const   weakConsistentPtr,
                float*                              const   valuePtr);
tommRoC_err_enum_t tommRoCWeakConsistentPtrGet(
        const   tommRoC_weak_consistent_ptr_t*      const   weakConsistentPtr,
                void**                              const   valuePtr);

/**
 * @}
 */

#endif
