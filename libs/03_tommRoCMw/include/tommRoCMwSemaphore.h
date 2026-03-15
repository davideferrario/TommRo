
#ifndef TOMMROC_MW_SEMAPHORE_H_
#define TOMMROC_MW_SEMAPHORE_H_

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
#define WAIT_SEMAPHORE_NO_WAIT_TIMEOUT      ((uint32_t) 0)
#define WAIT_SEMAPHORE_INFINITE_TIMEOUT     ((uint32_t) -1)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC semaphore functions.
typedef enum {

    /**
     * Semaphore creation.
     */
    TOMMRO_C_MW_SEMAPHORE_CREATE = 0,

    /**
     * Semaphore wait.
     */
    TOMMRO_C_MW_SEMAPHORE_WAIT,

    /**
     * Semaphore release.
     */
    TOMMRO_C_MW_SEMAPHORE_RELEASE,

    /**
     * Semaphore try wait.
     */
    TOMMRO_C_MW_SEMAPHORE_TRYWAIT,

    /**
     * Semaphore destroy.
     */
    TOMMRO_C_MW_SEMAPHORE_DESTROY,

} tommRoC_mw_semaphore_operations_enum_t;


// Semaphore create callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_semaphore_create_cb_funct_t)(
                void*       const   semaphorePtr,
        const   uint32_t            availableRes);

// Semaphore wait callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_semaphore_wait_cb_funct_t)(
                void*       const   semaphorePtr,
        const   uint32_t            waitTimeoutMs);

// Semaphore release callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_semaphore_release_cb_funct_t)(
                void*       const   semaphorePtr);

// Semaphore try wait callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_semaphore_try_wait_cb_funct_t)(
                void*       const   semaphorePtr);

// Semaphore destroy callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_semaphore_destroy_cb_funct_t)(
                void*       const   semaphorePtr);


// tommRoC middleware semaphore environment init data.
typedef struct {

    /**
     * Each function pointer is specific to particular semaphore operation.
     * Some functions could be NULL if none/not available.
     * Some functions could not be NULL (some base functions are needed).
     *
     * Every function got specific parameters input/result output pointers.
     * Specific cast and check have to be made by software high level.
     */

    /**
     * Semaphore create.
     *
     * NOTE: NEEDED
     */
    tommRoC_mw_semaphore_create_cb_funct_t      create;

    /**
     * Semaphore wait.
     *
     * NOTE: NEEDED
     */
    tommRoC_mw_semaphore_wait_cb_funct_t        wait;

    /**
     * Semaphore release.
     *
     * NOTE: NEEDED
     */
    tommRoC_mw_semaphore_release_cb_funct_t     release;

    /**
     * Semaphore try wait.
     *
     * NOTE: could be NULL
     */
    tommRoC_mw_semaphore_try_wait_cb_funct_t    tryWait;

    /**
     * Semaphore destroy.
     *
     * NOTE: could be NULL
     */
    tommRoC_mw_semaphore_destroy_cb_funct_t     destroy;

} tommRoC_mw_semaphore_environment_init_t;

#define __EMPTY_tommRoC_mw_semaphore_environment_init_t__   \
{                                                           \
    /* .create */   NULL,                                   \
    /* .wait */     NULL,                                   \
    /* .release */  NULL,                                   \
    /* .tryWait */  NULL,                                   \
    /* .destroy */  NULL,                                   \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Prepare library semaphore environment.
 *
 * param[in]        initEnvironmentPtr      pointer to environment init data.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwSemaphoreEnvironmentInit(
        const   tommRoC_mw_semaphore_environment_init_t*    const   initEnvironmentPtr);

/**
 * Check semaphore environment.
 *
 * param[in]        environmentPtr          pointer to environment.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwSemaphoreEnvironmentCheck(
        const   tommRoC_mw_semaphore_environment_init_t*    const   environmentPtr);

/**
 * Close library semaphore environment.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwSemaphoreCloseEnvironment(void);

/**
 * Check if a specific semaphore operation is available (has been initiated).
 *
 * param[in]        semaphoreOp             semaphore operation.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwSemaphoreIsOpAvailable(
        const   tommRoC_mw_semaphore_operations_enum_t  semaphoreOp);

/**
 * Semaphore creation.
 *
 * param[out]       semaphorePtr            semaphore pointer.
 * param[in]        availableRes            number of available resources.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwSemaphoreCreate(
                void*       const   semaphorePtr,
        const   uint32_t            availableRes);

/**
 * Semaphore wait.
 *
 * param[in/out]    semaphorePtr            semaphore pointer.
 * param[in]        waitTimeoutMs           wait sempahore timeout [msec].
 *                                          use WAIT_SEMAPHORE_NO_WAIT_TIMEOUT for no wait.
 *                                          use WAIT_SEMAPHORE_INFINITE_TIMEOUT for wait forever.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwSemaphoreWait(
                void*       const   semaphorePtr,
        const   uint32_t            waitTimeoutMs);

/**
 * Semaphore release.
 *
 * param[in/out]    semaphorePtr            semaphore pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwSemaphoreRelease(
                void*       const   semaphorePtr);

/**
 * Semaphore try wait.
 *
 * param[in/out]    semaphorePtr            semaphore pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwSemaphoreTryWait(
                void*       const   semaphorePtr);

/**
 * Semaphore destroy.
 *
 * param[in/out]    semaphorePtr            semaphore pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwSemaphoreDestroy(
                void*       const   semaphorePtr);

#endif
