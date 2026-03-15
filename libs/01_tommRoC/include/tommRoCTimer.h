
#ifndef TOMMROC_TIMER_H_
#define TOMMROC_TIMER_H_

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
 * @defgroup tommRoCTimer tommRoCTimer
 *
 * @brief  TommRoC library timer module
 * @author TommRo Software Department
 *
 * This module is providing timer functionality.
 * A timer is an object that can be used for timeout and/or timing measure functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCUnitMeasure.h"
#include "tommRoCUtil.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

#define TOMMROC_TIMER_SEC_TO_mSEC_TIMEOUT(sec)      (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(sec))
#define TOMMROC_TIMER_MIN_TO_mSEC_TIMEOUT(min)      (TOMMROC_UNIT_MEASURE_TIME_MIN_TO_mSEC(min))
#define TOMMROC_TIMER_HRS_TO_mSEC_TIMEOUT(hrs)      (TOMMROC_UNIT_MEASURE_TIME_HRS_TO_mSEC(hrs))
#define TOMMROC_TIMER_DAYS_TO_mSEC_TIMEOUT(days)    (TOMMROC_UNIT_MEASURE_TIME_DAYS_TO_mSEC(days))

#define TOMMROC_TIMER_MAX_TIMEOUT_mSEC              (UINT32_MAX - (uint32_t) TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(1))


// tommRoC timer.
#define TOMMROC_TIMER_HANDLE_SIZE   (TOMMROC_UTIL_U32_SIZE + TOMMROC_UTIL_U32_SIZE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC timer.
typedef struct {
    uint8_t data[TOMMROC_TIMER_HANDLE_SIZE];
} tommRoC_timer_t;

#define __EMPTY_tommRoC_timer_t_data_field__            TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_TIMER_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_timer_t__                       \
{                                                       \
    /* .data */ __EMPTY_tommRoC_timer_t_data_field__,   \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Start/Restart a timer.
 *
 * param[in/out]    timerPtr                timer pointer.
 * param[in]        timeoutMsec             timeout [msec].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCTimerStart(
                tommRoC_timer_t*    const   timerPtr,
        const   uint32_t                    timeoutMsec);

/**
 * Stop a timer.
 *
 * param[in/out]    timerPtr                timer pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCTimerStop(
                tommRoC_timer_t*    const   timerPtr);

/**
 * Check if a timer has been started.
 *
 * param[in]        timerPtr                timer pointer.
 *
 * return tommRoC_err_enum_t
 */
bool tommRoCTimerIsStarted(
        const   tommRoC_timer_t*    const   timerPtr);

/**
 * Refresh (restart with previous timeout) a timer.
 *
 * param[in/out]    timerPtr                timer pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCTimerRefresh(
                tommRoC_timer_t*    const   timerPtr);

/**
 * Set timer duration.
 * NOTE: if timer is not started, it will be started.
 *
 * param[in]        timerPtr                timer pointer.
 * param[in]        timeoutMsec             timer duration [msec].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCTimerSetDuration(
                tommRoC_timer_t*    const   timerPtr,
        const   uint32_t                    timeoutMsec);

/**
 * Get timer duration.
 *
 * param[in]        timerPtr                timer pointer.
 * param[out]       timeoutMsecPtr          timer duration pointer [msec].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCTimerGetDuration(
        const   tommRoC_timer_t*    const   timerPtr,
                uint32_t*           const   timeoutMsecPtr);

/**
 * Check if the specified timer expired.
 *
 * param[in]        timerPtr                timer pointer.
 *
 * return tommRoC_err_enum_t
 *          TOMMRO_C_NULL_PARAM_ERR                 -> NULL param error.
 *          TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR       -> Os uptime environment not available.
 *          TOMMRO_C_TIMER_NOT_START_ERR            -> timer not started.
 *          TOMMRO_C_TIMER_NOT_EXPIRED_ERR          -> timer not expired.
 *          TOMMRO_C_TIMER_EXPIRED_ERR              -> timer expired.
 */
tommRoC_err_enum_t tommRoCTimerIsExpired(
        const   tommRoC_timer_t*    const   timerPtr);

/**
 * Retrieve the elapsed time.
 *
 * param[in]        timerPtr                timer pointer.
 * param[out]       elapsedMsecPtr          elapsed msec.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCTimerElapsed(
        const   tommRoC_timer_t*    const   timerPtr,
                uint32_t*           const   elapsedMsecPtr);

/**
 * Retrieve the remaining time until the timeout will be expired.
 *
 * param[in]        timerPtr                timer pointer.
 * param[out]       remainingMsecPtr        remaining msec until the timeout will be expired pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCTimerRemaining(
        const   tommRoC_timer_t*    const   timerPtr,
                uint32_t*           const   remainingMsecPtr);

/**
 * Update (add or substract) a timer timeout.
 *
 * param[in/out]    timerPtr                timer pointer.
 * param[in]        timeoutDiffMsec         timeout difference [msec].
 *                                          if (timeout difference > 0) -> increase timer timeout.
 *                                          if (timeout difference < 0) -> decrease timer timeout.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCTimerUpdate(
                tommRoC_timer_t*    const   timerPtr,
        const   int32_t                     timeoutDiffMsec);

/**
 * @}
 */

#endif
