
#ifndef TOMMROC_QUEUE_MBED_H_
#define TOMMROC_QUEUE_MBED_H_

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
 * @defgroup tommRoCQueueMbed tommRoCQueueMbed
 *
 * @brief  TommRoC library embedded queue module
 * @author TommRo Software Department
 *
 * This module is providing library embedded FIFO queue functionality.
 * It can be used in case of application needs only one queue.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCQueue.h"

#include <stdbool.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init Mbed queue framework.
 * Mbed queue framework is a layer build over tommRoCQueue to be used when only one queue is needed by application.
 * The queue handler is hide to application by this layer.
 *
 * param[in/out]    queueHandlePtr          queue handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCQueueMbedInit(tommRoC_queue_t* const queueHandlePtr);

/**
 * Close Mbed queue framework.
 * The internal queue framework is resetted to initial value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCQueueMbedClose(void);

/**
 * Get Mbed queue framework init status.
 *
 * return bool
 */
bool tommRoCQueueMbedIsInit(void);

/**
 * Push a single object into Mbed queue framework.
 *
 * param[in]        queueID                 queue numeric ID.
 * param[in]        objBufferPtr            object data pointer.
 * param[in]        objBufferSize           object data size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCQueueMbedPush(
        const   uint8_t                     queueID,
        const   void*               const   objBufferPtr,
        const   uint32_t                    objBufferSize);

/**
 * Pop a single object from Mbed queue framework.
 *
 * param[in]        queueID                 queue numeric ID.
 * param[out]       objBufferPtr            object data pointer.
 * param[in]        objBufferSize           object data size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCQueueMbedPop(
        const   uint8_t                     queueID,
                void*               const   objBufferPtr,
        const   uint32_t                    objBufferSize);

/**
 * Get a single object from Mbed queue framework.
 *
 * param[in]        queueID                 queue numeric ID.
 * param[out]       objBufferPtr            object data pointer.
 * param[in]        objBufferSize           object data size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCQueueMbedGet(
        const   uint8_t                     queueID,
                void*               const   objBufferPtr,
        const   uint32_t                    objBufferSize);

/**
 * Get empty status of Mbed queue framework.
 *
 * param[in]        queueID                 queue numeric ID.
 *
 * return bool
 */
bool tommRoCQueueMbedIsEmpty(
        const   uint8_t                     queueID);

/**
 * Get objects amount in Mbed queue framework.
 *
 * param[in]        queueID                 queue numeric ID.
 * param[out]       amountPtr               inside objects amount pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCQueueMbedInsideObjAmount(
        const   uint8_t                     queueID,
                uint32_t*           const   amountPtr);

/**
 * Get free objects amount in Mbed queue framework.
 *
 * param[in]        queueID                 queue numeric ID.
 * param[out]       amountPtr               free objects amount pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCQueueMbedFreeObjAmount(
        const   uint8_t                     queueID,
                uint32_t*           const   amountPtr);

/**
 * Skip multiple object in Mbed queue framework.
 *
 * param[in]        queueID                 queue numeric ID.
 * param[in]        objAmount               object amount.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCQueueMbedSkip(
        const   uint8_t                     queueID,
        const   uint32_t                    objAmount);

/**
 * Clear a Mbed queue framework.
 *
 * param[in]        queueID                 queue numeric ID.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCQueueMbedClear(
        const   uint8_t                     queueID);

/**
 * @}
 */

#endif
