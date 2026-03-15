
#ifndef TOMMROC_QUEUE_H_
#define TOMMROC_QUEUE_H_

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
 * @defgroup tommRoCQueue tommRoCQueue
 *
 * @brief  TommRoC library queue module
 * @author TommRo Software Department
 *
 * This module is providing FIFO queue functionality.
 *
 * It is based on objects (tasks) that push some data into queue (FIFO/FIFOISR) and objects (tasks) that pop data from queue (FIFO/FIFOISR).
 * The identification of queue (FIFO/FIFOISR) to push/pop is made by numeric ID.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCFIFO.h"
#include "tommRoCGuard.h"
#include "tommRoCUtil.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

#define TOMMROC_QUEUE_HANDLE_SIZE   (   TOMMROC_UTIL_PTR_SIZE   +   \
                                        TOMMROC_UTIL_PTR_SIZE   +   \
                                        TOMMROC_UTIL_U8_SIZE    +   \
                                        TOMMROC_UTIL_PTR_SIZE       )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC queue struct.
typedef struct {
    uint8_t data[TOMMROC_QUEUE_HANDLE_SIZE];
} tommRoC_queue_t;

#define __EMPTY_tommRoC_queue_t_data_field__            TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_QUEUE_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_queue_t__                       \
{                                                       \
    /* .data */ __EMPTY_tommRoC_queue_t_data_field__,   \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init a queue structure (using FIFO structure).
 * NOTE: FIFO (not FIFO ISR) is used. If a guard is not used for queue, check if single FIFO guard is used if it is used in case of multiple producer/consumer.
 *
 * param[in]        fifoPtr                 FIFO to be used for queue pointer.
 * param[in]        fifoAmount              FIFO amount.
 * param[in]        guardPtr                queue guard pointer (set to NULL to disable).
 * param[out]       queueHandlePtr          queue handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCQueueInit(
        const   tommRoC_fifo_t*     const   fifoPtr,
        const   uint8_t                     fifoAmount,
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_queue_t*    const   queueHandlePtr);

/**
 * Init a queue structure (using FIFO ISR structure).
 * NOTE: FIFO ISR is faster than FIFO but it is not thread safe. If a guard is not used for queue, use this only if there is only one producer and one consumer for every queue.
 *
 * param[in]        fifoISRPtr              FIFO ISR to be used for queue pointer.
 * param[in]        fifoAmount              FIFO ISR amount.
 * param[in]        guardPtr                queue guard pointer (set to NULL to disable).
 * param[out]       queueHandlePtr          queue handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCQueueISRInit(
        const   tommRoC_fifo_ISR_t* const   fifoISRPtr,
        const   uint8_t                     fifoAmount,
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_queue_t*    const   queueHandlePtr);

/**
 * Push a single object into queue.
 *
 * param[in]        queueHandlePtr          queue handle pointer.
 * param[in]        queueID                 queue numeric ID.
 * param[in]        objBufferPtr            object data pointer.
 * param[in]        objBufferSize           object data size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCQueuePush(
        const   tommRoC_queue_t*    const   queueHandlePtr,
        const   uint8_t                     queueID,
        const   void*               const   objBufferPtr,
        const   uint32_t                    objBufferSize);

/**
 * Pop a single object from queue.
 *
 * param[in]        queueHandlePtr          queue handle pointer.
 * param[in]        queueID                 queue numeric ID.
 * param[out]       objBufferPtr            object data pointer.
 * param[in]        objBufferSize           object data size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCQueuePop(
        const   tommRoC_queue_t*    const   queueHandlePtr,
        const   uint8_t                     queueID,
                void*               const   objBufferPtr,
        const   uint32_t                    objBufferSize);

/**
 * Get a single object from queue.
 *
 * param[in]        queueHandlePtr          queue handle pointer.
 * param[in]        queueID                 queue numeric ID.
 * param[out]       objBufferPtr            object data pointer.
 * param[in]        objBufferSize           object data size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCQueueGet(
        const   tommRoC_queue_t*    const   queueHandlePtr,
        const   uint8_t                     queueID,
                void*               const   objBufferPtr,
        const   uint32_t                    objBufferSize);

/**
 * Get empty status of a queue.
 *
 * param[in]        queueHandlePtr          queue handle pointer.
 * param[in]        queueID                 queue numeric ID.
 *
 * return bool
 */
bool tommRoCQueueIsEmpty(
        const   tommRoC_queue_t*    const   queueHandlePtr,
        const   uint8_t                     queueID);

/**
 * Get objects amount in a queue.
 *
 * param[in]        queueHandlePtr          queue handle pointer.
 * param[in]        queueID                 queue numeric ID.
 * param[out]       amountPtr               inside objects amount pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCQueueInsideObjAmount(
        const   tommRoC_queue_t*    const   queueHandlePtr,
        const   uint8_t                     queueID,
                uint32_t*           const   amountPtr);

/**
 * Get free objects amount in a queue.
 *
 * param[in]        queueHandlePtr          queue handle pointer.
 * param[in]        queueID                 queue numeric ID.
 * param[out]       amountPtr               free objects amount pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCQueueFreeObjAmount(
        const   tommRoC_queue_t*    const   queueHandlePtr,
        const   uint8_t                     queueID,
                uint32_t*           const   amountPtr);

/**
 * Skip multiple object in queue.
 *
 * param[in]        queueHandlePtr          queue handle pointer.
 * param[in]        queueID                 queue numeric ID.
 * param[in]        objAmount               object amount.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCQueueSkip(
        const   tommRoC_queue_t*    const   queueHandlePtr,
        const   uint8_t                     queueID,
        const   uint32_t                    objAmount);

/**
 * Clear a queue.
 *
 * param[in]        queueHandlePtr          queue handle pointer.
 * param[in]        queueID                 queue numeric ID.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCQueueClear(
        const   tommRoC_queue_t*    const   queueHandlePtr,
        const   uint8_t                     queueID);

/**
 * @}
 */

#endif
