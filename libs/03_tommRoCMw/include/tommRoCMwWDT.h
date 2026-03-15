
#ifndef TOMMROC_MW_WDT_H_
#define TOMMROC_MW_WDT_H_

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
 * Author
 * TommRo Software Department
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwErr.h"

#include "TOMMROC.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

#define TOMMROC_MW_WDT_HANDLE_SIZE  (sizeof(tommRoC_timer_t) + TOMMROC_UTIL_BOOL_SIZE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC middleware layer multitask watchdog system watchdog refresh functions type definition.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_wdt_refresh_funct_t)(void* const inOutPtr);

typedef struct {
    uint8_t data[TOMMROC_MW_WDT_HANDLE_SIZE];
} tommRoC_mw_wdt_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Prepare library multitask watchdog timer environment.
 * NOTE: a tommRoC_mw_wdt_t element is needed for every task that MUST be checked.
 *
 * param[in]        guardPtr                multitask watchdog timer guard (NULL if none).
 * param[in]        refreshFunctPtr         system watchdog refresh function pointer.
 * param[in]        refreshFunctInOutPtr    system watchdog refresh function in/out parameter pointer (NULL if none).
 * param[in]        WDTArrayPtr             multitask watchdog timer array pointer.
 * param[in]        WDTArrayAmount          multitask watchdog timer array element amount.
 * param[in]        WDTTimeoutMsec          multitask watchdog timer timeout [msec].
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwWDTInit(
        const   tommRoC_guard_t*                const   guardPtr,
        const   tommRoC_mw_wdt_refresh_funct_t          refreshFunctPtr,
                void*                           const   refreshFunctInOutPtr,
                tommRoC_mw_wdt_t*               const   WDTArrayPtr,
        const   uint8_t                                 WDTArrayAmount,
        const   uint32_t                                WDTTimeoutMsec);

/**
 * Close library multitask watchdog timer environment.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwWDTClose(void);

/**
 * Check the status of multitask watchdog timer environment.
 * NOTE: this MUST be periodically called from the watchdog task.
 *
 * param[out]       wdtExpiredAmountPtr     amount of tasks with watchdog timer expired pointer.
 * param[out]       expiredTaskIDArrayPtr   task ID with watchdog timer expired array pointer.
 * param[in]        expiredTaskIDArraySize  task ID with watchdog timer expired array size [byte].
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwWDTCheck(
                uint8_t*    const   wdtExpiredAmountPtr,
                uint8_t*    const   expiredTaskIDArrayPtr,
        const   uint8_t             expiredTaskIDArraySize);

/**
 * Disable globally library multitask watchdog timer environment.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwWDTDisable(void);

/**
 * Enable globally library multitask watchdog timer environment.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwWDTEnable(void);

/**
 * Disable library multitask watchdog timer environment for a specific task.
 * NOTE: this can be used to disable watchdog for a specific task in case of the task enter in a blocking code.
 *
 * param[in]        taskID                  task ID.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwWDTTaskDisable(const uint8_t taskID);

/**
 * Enable library multitask watchdog timer environment for a specific task.
 * NOTE: this can be used to re-enable watchdog for a specific task when the task exits from a blocking code.
 *
 * param[in]        taskID                  task ID.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwWDTTaskEnable(const uint8_t taskID);

/**
 * Watchdog refresh for a specific task.
 * NOTE: this MUST be periodically called from task.
 *
 * param[in]        taskID                  task ID.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwWDTTaskRefresh(const uint8_t taskID);

#endif
