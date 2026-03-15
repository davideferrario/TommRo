
#ifndef TOMMROC_GUARD_H_
#define TOMMROC_GUARD_H_

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
 * @defgroup tommRoCGuard tommRoCGuard
 *
 * @brief  TommRoC library guard module
 * @author TommRo Software Department
 *
 * This module is providing RTOS abstracted multi-thread guard functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCAssert.h"
#include "tommRoCErr.h"
#include "tommRoCUtil.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/**
 * Synchronized (guarded) no result void function execution
 * NOTE: no result return is done
 */
#define TOMMROC_GUARD_SYNCHRO_VOID_FUNCT(                                                       \
        guardPtr,                                                                               \
        callFunctWithParam)                                                                     \
                                                                                                \
        do {                                                                                    \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCGuardLockIfPossible(guardPtr));     \
            callFunctWithParam;                                                                 \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCGuardUnLockIfPossible(guardPtr));   \
        } while (0)

/**
 * Synchronized (guarded) with result function execution
 */
#define TOMMROC_GUARD_SYNCHRO_WITH_RESULT_FUNCT(                                                                                            \
        resultVarType,                                                                                                                      \
        guardPtr,                                                                                                                           \
        onGuardErrorResult,                                                                                                                 \
        callFunctWithParam)                                                                                                                 \
                                                                                                                                            \
        do {                                                                                                                                \
            resultVarType callFunctWithParamResult;                                                                                         \
                                                                                                                                            \
            TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCGuardLockIfPossible(guardPtr), onGuardErrorResult);  \
            callFunctWithParamResult = callFunctWithParam;                                                                                  \
            TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCGuardUnLockIfPossible(guardPtr), onGuardErrorResult);\
                                                                                                                                            \
            return callFunctWithParamResult;                                                                                                \
        } while (0)

/**
 * Synchronized (guarded) tommRoC_err_enum_t result function execution
 */
#define TOMMROC_GUARD_SYNCHRO_TOMMROC_LIB_FUNCT(                                                                \
        guardPtr,                                                                                               \
        callFunctWithParam)                                                                                     \
                                                                                                                \
        do {                                                                                                    \
            tommRoC_err_enum_t callFunctWithParamResult;                                                        \
                                                                                                                \
            TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCGuardLockIfPossible(guardPtr));   \
            callFunctWithParamResult = callFunctWithParam;                                                      \
            TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCGuardUnLockIfPossible(guardPtr)); \
                                                                                                                \
            return callFunctWithParamResult;                                                                    \
        } while (0)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/**
 * Guard lock/unlock function type.
 */
typedef tommRoC_err_enum_t (*tommRoC_guard_funct_t)(void);


// tommRoC guard.
#define TOMMROC_GUARD_HANDLE_SIZE           (   TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                TOMMROC_UTIL_FUNCT_PTR_SIZE     )
typedef struct {
    uint8_t data[TOMMROC_GUARD_HANDLE_SIZE];
} tommRoC_guard_t;

#define __EMPTY_tommRoC_guard_t_data_field__            TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_GUARD_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_guard_t__                       \
{                                                       \
    /* .data */ __EMPTY_tommRoC_guard_t_data_field__,   \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init a guard
 *
 * param[in]        lockFunct               guard lock function pointer (could not be NULL).
 * param[in]        unlockFunct             guard unlock function pointer (could not be NULL).
 * param[out]       guardPtr                output guard pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCGuardInit(
        const   tommRoC_guard_funct_t           lockFunct,
        const   tommRoC_guard_funct_t           unlockFunct,
                tommRoC_guard_t*        const   guardPtr);

/**
 * Clear guard
 *
 * param[out]       guardPtr                output guard pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCGuardClear(
                tommRoC_guard_t*    const   guardPtr);

/**
 * Check if a guard is valid.
 *
 * param[in]        guardPtr                input guard pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCGuardCheck(
        const   tommRoC_guard_t*    const   guardPtr);

/**
 * Lock a guard.
 * NOTE: if guard is not valid, error result is returned.
 *       if guard is valid, the lock method is called.
 *
 * param[in]        guardPtr                input guard pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCGuardLock(
        const   tommRoC_guard_t*    const   guardPtr);

/**
 * Unlock a guard.
 * NOTE: if guard is not valid, error result is returned.
 *       if guard is valid, the unlock method is called.
 *
 * param[in]        guardPtr                input guard pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCGuardUnLock(
        const   tommRoC_guard_t*    const   guardPtr);

/**
 * Lock a guard (if possible)
 *
 * param[in]        guardPtr                input guard pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCGuardLockIfPossible(
        const   tommRoC_guard_t*    const   guardPtr);

/**
 * Unlock a guard (if possible)
 *
 * param[in]        guardPtr                input guard pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCGuardUnLockIfPossible(
        const   tommRoC_guard_t*    const   guardPtr);

/**
 * @}
 */

#endif
