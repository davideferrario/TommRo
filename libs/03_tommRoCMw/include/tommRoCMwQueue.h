
#ifndef TOMMROC_MW_QUEUE_H_
#define TOMMROC_MW_QUEUE_H_

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

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/
#define QUEUE_NO_WAIT_TIMEOUT       ((uint32_t) 0)
#define QUEUE_INFINITE_TIMEOUT      ((uint32_t) -1)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC middleware queue functions.
typedef enum {

    /**
     * Queue creation.
     */
    TOMMRO_C_MW_QUEUE_CREATE = 0,

    /**
     * Queue put.
     */
    TOMMRO_C_MW_QUEUE_PUT,

    /**
     * Queue get.
     */
    TOMMRO_C_MW_QUEUE_GET,

    /**
     * Queue inside amount.
     */
    TOMMRO_C_MW_QUEUE_INSIDE_AMOUNT,

    /**
     * Queue free amount.
     */
    TOMMRO_C_MW_QUEUE_FREE_AMOUNT,

    /**
     * Queue destroy.
     */
    TOMMRO_C_MW_QUEUE_DESTROY,

} tommRoC_mw_queue_operations_enum_t;


// Queue create callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_queue_create_cb_funct_t)(
                void*       const   queuePtr,
        const   uint32_t            msgSizeByte,
        const   uint32_t            queueSizeByte);

// Queue put callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_queue_put_cb_funct_t)(
                void*       const   queuePtr,
        const   void*       const   dataPtr,
        const   uint32_t            waitTimeoutMs);

// Queue get callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_queue_get_cb_funct_t)(
                void*       const   queuePtr,
                void*       const   dataPtr,
        const   uint32_t            waitTimeoutMs);

// Queue inside amount callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_queue_inside_amount_cb_funct_t)(
                void*       const   queuePtr,
                uint32_t*   const   amountPtr);

// Queue free amount callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_queue_free_amount_cb_funct_t)(
                void*       const   queuePtr,
                uint32_t*   const   amountPtr);

// Queue destroy callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_queue_destroy_cb_funct_t)(
                void*       const   queuePtr);


// tommRoC middleware queue environment init data.
typedef struct {

    /**
     * Each function pointer is specific to particular queue operation.
     * Some functions could be NULL if none/not available.
     * Some functions could not be NULL (some base functions are needed).
     *
     * Every function got specific parameters input/result output pointers.
     * Specific cast and check have to be made by software high level.
     */

    /**
     * Queue create.
     *
     * NOTE: NEEDED
     */
    tommRoC_mw_queue_create_cb_funct_t          create;

    /**
     * Queue put.
     *
     * NOTE: NEEDED
     */
    tommRoC_mw_queue_put_cb_funct_t             put;

    /**
     * Queue get.
     *
     * NOTE: NEEDED
     */
    tommRoC_mw_queue_get_cb_funct_t             get;

    /**
     * Queue inside amount.
     *
     * NOTE: could be NULL
     */
    tommRoC_mw_queue_inside_amount_cb_funct_t   insideAmount;

    /**
     * Queue free amount.
     *
     * NOTE: could be NULL
     */
    tommRoC_mw_queue_free_amount_cb_funct_t     freeAmount;

    /**
     * Queue destroy.
     *
     * NOTE: could be NULL
     */
    tommRoC_mw_queue_destroy_cb_funct_t         destroy;

} tommRoC_mw_queue_environment_init_t;

#define __EMPTY_tommRoC_mw_queue_environment_init_t__       \
{                                                           \
    /* .create */       NULL,                               \
    /* .put */          NULL,                               \
    /* .get */          NULL,                               \
    /* .insideAmount */ NULL,                               \
    /* .freeAmount */   NULL,                               \
    /* .destroy */      NULL,                               \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Prepare library queue environment.
 *
 * param[in]        initEnvironmentPtr      pointer to environment init data.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwQueueEnvironmentInit(
        const   tommRoC_mw_queue_environment_init_t*    const   initEnvironmentPtr);

/**
 * Check queue environment.
 *
 * param[in]        environmentPtr          pointer to environment data.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwQueueEnvironmentCheck(
        const   tommRoC_mw_queue_environment_init_t*    const   environmentPtr);

/**
 * Close library queue environment.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwQueueCloseEnvironment(void);

/**
 * Check if a specific queue operation is available (has been initiated).
 *
 * param[in]        queueOp                 queue operation.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwQueueIsOpAvailable(
        const   tommRoC_mw_queue_operations_enum_t  queueOp);

/**
 * Queue creation.
 *
 * param[out]       queuePtr                created queue pointer.
 * param[in]        msgSizeByte             size of each queue message [byte].
 * param[in]        queueSizeByte           size of all the queue buffer [byte].
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwQueueCreate(
                void*       const   queuePtr,
        const   uint32_t            msgSizeByte,
        const   uint32_t            queueSizeByte);

/**
 * Queue put.
 *
 * param[in/out]    queuePtr                queue pointer (retrived by queue create funct).
 * param[in]        waitTimeoutMs           wait lock queue timeout [msec].
 *                                          use QUEUE_NO_WAIT_TIMEOUT for no wait.
 *                                          use QUEUE_INFINITE_TIMEOUT for wait forever.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwQueuePut(
                void*       const   queuePtr,
        const   void*       const   dataPtr,
        const   uint32_t            waitTimeoutMs);

/**
 * Queue get.
 *
 * param[in/out]    queuePtr                queue pointer (retrived by queue create funct).
 * param[in]        waitTimeoutMs           wait lock queue timeout [msec].
 *                                          use QUEUE_NO_WAIT_TIMEOUT for no wait.
 *                                          use QUEUE_INFINITE_TIMEOUT for wait forever.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwQueueGet(
                void*       const   queuePtr,
                void*       const   dataPtr,
        const   uint32_t            waitTimeoutMs);

/**
 * Get number of queued messages in a queue.
 *
 * param[in/out]    queuePtr                queue pointer (retrived by queue create funct).
 * param[out]       amountPtr               number of queued messages pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwQueueInsideAmount(
                void*       const   queuePtr,
                uint32_t*   const   amountPtr);

/**
 * Get number of available slots for messages in a queue.
 *
 * param[in/out]    queuePtr                queue pointer (retrived by queue create funct).
 * param[out]       amountPtr               number of available slots for messages pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwQueueFreeAmount(
                void*       const   queuePtr,
                uint32_t*   const   amountPtr);

/**
 * Queue destroy.
 *
 * param[in/out]    queuePtr                queue pointer (retrived by queue create funct).
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwQueueDestroy(
                void*       const   queuePtr);

#endif
