
#ifndef TOMMROC_GUARD_CONSISTENT_H_
#define TOMMROC_GUARD_CONSISTENT_H_

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
 * @defgroup tommRoCGuardConsistent tommRoCGuardConsistent
 *
 * @brief  TommRoC library guard consistent module
 * @author TommRo Software Department
 *
 * This module is providing guard consistent variable functionality.
 *
 * A guard consistent variable is a variable with strong consistency.
 * The consistency is guaranteed by a guard variable.
 *
 * Multi-thread consistency access is guaranteed in both get and set functionality.
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

/*******************************************************************************
 * defines
 ******************************************************************************/
#define TOMMROC_GUARD_CONSISTENT_ARRAY_ELEM_AMOUNT  (2)

#define TOMMROC_GUARD_CONSISTENT_DECLARE_BUFFER_ELEMENT(consistentVar, elemSize, guardPtr)                          \
        do {                                                                                                        \
            static uint8_t TOMMROC_UTIL_CONCAT_FOUR_ELEM_NO_EXPAND(__, consistentVar, Buffer, __)[(elemSize) * 2];  \
                                                                                                                    \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(                                                               \
                    tommRoCGuardConsistentInit(                                                                     \
                            (elemSize),                                                                             \
                            TOMMROC_UTIL_CONCAT_FOUR_ELEM_NO_EXPAND(__, consistentVar, Buffer, __),                 \
                            sizeof(TOMMROC_UTIL_CONCAT_FOUR_ELEM_NO_EXPAND(__, consistentVar, Buffer, __)),         \
                            (guardPtr),                                                                             \
                            &consistentVar));                                                                       \
        } while (0)

#define TOMMROC_GUARD_CONSISTENT_ALLOCATE_BUFFER_ELEMENT(consistentVar, elemSize, guardPtr)                         \
        static tommRoC_guard_consistent_t consistentVar;                                                            \
                                                                                                                    \
        do {                                                                                                        \
            static uint8_t TOMMROC_UTIL_CONCAT_FOUR_ELEM_NO_EXPAND(__, consistentVar, Buffer, __)[(elemSize) * 2];  \
                                                                                                                    \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(                                                               \
                    tommRoCGuardConsistentInit(                                                                     \
                            (elemSize),                                                                             \
                            TOMMROC_UTIL_CONCAT_FOUR_ELEM_NO_EXPAND(__, consistentVar, Buffer, __),                 \
                            sizeof(TOMMROC_UTIL_CONCAT_FOUR_ELEM_NO_EXPAND(__, consistentVar, Buffer, __)),         \
                            (guardPtr),                                                                             \
                            &consistentVar));                                                                       \
        } while (0)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC guard consistent.
#define TOMMROC_GUARD_CONSISTENT_HANDLE_SIZE        (   TOMMROC_UTIL_PTR_SIZE   +   \
                                                        TOMMROC_UTIL_BOOL_SIZE  +   \
                                                        TOMMROC_UTIL_U32_SIZE   +   \
                                                        TOMMROC_UTIL_PTR_SIZE       )

#define TOMMROC_GUARD_CONSISTENT_U16_HANDLE_SIZE    (TOMMROC_UTIL_PTR_SIZE + TOMMROC_UTIL_BOOL_SIZE + (TOMMROC_UTIL_U16_SIZE    * TOMMROC_GUARD_CONSISTENT_ARRAY_ELEM_AMOUNT))
#define TOMMROC_GUARD_CONSISTENT_U32_HANDLE_SIZE    (TOMMROC_UTIL_PTR_SIZE + TOMMROC_UTIL_BOOL_SIZE + (TOMMROC_UTIL_U32_SIZE    * TOMMROC_GUARD_CONSISTENT_ARRAY_ELEM_AMOUNT))
#define TOMMROC_GUARD_CONSISTENT_I16_HANDLE_SIZE    (TOMMROC_UTIL_PTR_SIZE + TOMMROC_UTIL_BOOL_SIZE + (TOMMROC_UTIL_I16_SIZE    * TOMMROC_GUARD_CONSISTENT_ARRAY_ELEM_AMOUNT))
#define TOMMROC_GUARD_CONSISTENT_I32_HANDLE_SIZE    (TOMMROC_UTIL_PTR_SIZE + TOMMROC_UTIL_BOOL_SIZE + (TOMMROC_UTIL_I32_SIZE    * TOMMROC_GUARD_CONSISTENT_ARRAY_ELEM_AMOUNT))
#define TOMMROC_GUARD_CONSISTENT_FLOAT_HANDLE_SIZE  (TOMMROC_UTIL_PTR_SIZE + TOMMROC_UTIL_BOOL_SIZE + (TOMMROC_UTIL_FLOAT_SIZE  * TOMMROC_GUARD_CONSISTENT_ARRAY_ELEM_AMOUNT))
#define TOMMROC_GUARD_CONSISTENT_PTR_HANDLE_SIZE    (TOMMROC_UTIL_PTR_SIZE + TOMMROC_UTIL_BOOL_SIZE + (TOMMROC_UTIL_PTR_SIZE    * TOMMROC_GUARD_CONSISTENT_ARRAY_ELEM_AMOUNT))


typedef struct {
    uint8_t data[TOMMROC_GUARD_CONSISTENT_HANDLE_SIZE];
} tommRoC_guard_consistent_t;

typedef struct {
    uint8_t data[TOMMROC_GUARD_CONSISTENT_U16_HANDLE_SIZE];
} tommRoC_guard_consistent_u16_t;

typedef struct {
    uint8_t data[TOMMROC_GUARD_CONSISTENT_U32_HANDLE_SIZE];
} tommRoC_guard_consistent_u32_t;

typedef struct {
    uint8_t data[TOMMROC_GUARD_CONSISTENT_I16_HANDLE_SIZE];
} tommRoC_guard_consistent_i16_t;

typedef struct {
    uint8_t data[TOMMROC_GUARD_CONSISTENT_I32_HANDLE_SIZE];
} tommRoC_guard_consistent_i32_t;

typedef struct {
    uint8_t data[TOMMROC_GUARD_CONSISTENT_FLOAT_HANDLE_SIZE];
} tommRoC_guard_consistent_float_t;

typedef struct {
    uint8_t data[TOMMROC_GUARD_CONSISTENT_PTR_HANDLE_SIZE];
} tommRoC_guard_consistent_ptr_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init a guard consistent struct.
 *
 * param[in]        elemSize                element size [byte].
 * param[in]        bufferPtr               buffer to be used pointer.
 * param[in]        bufferSize              buffer to be used size [byte]. NOTE: must be (element size * 2)
 * param[in]        guardPtr                guard pointer (NULL if not used - a weak consistent struct is used).
 * param[out]       guardConsistentPtr      guard consistent handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCGuardConsistentInit(
        const   uint32_t                            elemSize,
                void*                       const   bufferPtr,
        const   uint32_t                            bufferSize,
        const   tommRoC_guard_t*            const   guardPtr,
                tommRoC_guard_consistent_t* const   guardConsistentPtr);

/**
 * Init a specific type guard consistent struct.
 *
 * param[in]        guardPtr                guard pointer (NULL if not used - a weak consistent struct is used).
 * param[out]       guardConsistentPtr      specific type guard consistent handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCGuardConsistentU16Init(const tommRoC_guard_t* const guardPtr, tommRoC_guard_consistent_u16_t* const guardConsistentPtr);
tommRoC_err_enum_t tommRoCGuardConsistentU32Init(const tommRoC_guard_t* const guardPtr, tommRoC_guard_consistent_u32_t* const guardConsistentPtr);
tommRoC_err_enum_t tommRoCGuardConsistentI16Init(const tommRoC_guard_t* const guardPtr, tommRoC_guard_consistent_i16_t* const guardConsistentPtr);
tommRoC_err_enum_t tommRoCGuardConsistentI32Init(const tommRoC_guard_t* const guardPtr, tommRoC_guard_consistent_i32_t* const guardConsistentPtr);
tommRoC_err_enum_t tommRoCGuardConsistentFloatInit(const tommRoC_guard_t* const guardPtr, tommRoC_guard_consistent_float_t* const guardConsistentPtr);
tommRoC_err_enum_t tommRoCGuardConsistentPtrInit(const tommRoC_guard_t* const guardPtr, tommRoC_guard_consistent_ptr_t* const guardConsistentPtr);

/**
 * Set element of guard consistent struct.
 *
 * param[in/out]    guardConsistentPtr      guard consistent handle pointer.
 * param[in]        bufferPtr               element buffer pointer.
 * param[in]        elemSize                element size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCGuardConsistentSet(
                tommRoC_guard_consistent_t* const   guardConsistentPtr,
        const   void*                       const   bufferPtr,
        const   uint32_t                            elemSize);

/**
 * Set element of a specific type guard consistent struct.
 *
 * param[in/out]    guardConsistentPtr       specific type guard consistent handle pointer.
 * param[in]        value                   value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCGuardConsistentU16Set(
                tommRoC_guard_consistent_u16_t*     const   guardConsistentPtr,
        const   uint16_t                                    value);
tommRoC_err_enum_t tommRoCGuardConsistentU32Set(
                tommRoC_guard_consistent_u32_t*     const   guardConsistentPtr,
        const   uint32_t                                    value);
tommRoC_err_enum_t tommRoCGuardConsistentI16Set(
                tommRoC_guard_consistent_i16_t*     const   guardConsistentPtr,
        const   int16_t                                     value);
tommRoC_err_enum_t tommRoCGuardConsistentI32Set(
                tommRoC_guard_consistent_i32_t*     const   guardConsistentPtr,
        const   int32_t                                     value);
tommRoC_err_enum_t tommRoCGuardConsistentFloatSet(
                tommRoC_guard_consistent_float_t*   const   guardConsistentPtr,
        const   float                                       value);
tommRoC_err_enum_t tommRoCGuardConsistentPtrSet(
                tommRoC_guard_consistent_ptr_t*     const   guardConsistentPtr,
        const   void*                               const   value);

/**
 * Get element of guard consistent struct.
 *
 * param[in]        guardConsistentPtr      guard consistent handle pointer.
 * param[out]       bufferPtr               element buffer pointer.
 * param[in]        elemSize                element size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCGuardConsistentGet(
        const   tommRoC_guard_consistent_t* const   guardConsistentPtr,
                void*                       const   bufferPtr,
        const   uint32_t                            elemSize);

/**
 * Get element of a specific type guard consistent struct.
 *
 * param[in]        guardConsistentPtr      specific type guard consistent handle pointer.
 * param[out]       valuePtr                value pointer.

 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCGuardConsistentU16Get(
        const   tommRoC_guard_consistent_u16_t*     const   guardConsistentPtr,
                uint16_t*                           const   valuePtr);
tommRoC_err_enum_t tommRoCGuardConsistentU32Get(
        const   tommRoC_guard_consistent_u32_t*     const   guardConsistentPtr,
                uint32_t*                           const   valuePtr);
tommRoC_err_enum_t tommRoCGuardConsistentI16Get(
        const   tommRoC_guard_consistent_i16_t*     const   guardConsistentPtr,
                int16_t*                            const   valuePtr);
tommRoC_err_enum_t tommRoCGuardConsistentI32Get(
        const   tommRoC_guard_consistent_i32_t*     const   guardConsistentPtr,
                int32_t*                            const   valuePtr);
tommRoC_err_enum_t tommRoCGuardConsistentFloatGet(
        const   tommRoC_guard_consistent_float_t*   const   guardConsistentPtr,
                float*                              const   valuePtr);
tommRoC_err_enum_t tommRoCGuardConsistentPtrGet(
        const   tommRoC_guard_consistent_ptr_t*     const   guardConsistentPtr,
                void**                              const   valuePtr);

/**
 * @}
 */

#endif
