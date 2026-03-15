
#ifndef TOMMROC_MW_MUTEX_H_
#define TOMMROC_MW_MUTEX_H_

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
#define LOCK_MUTEX_NO_WAIT_TIMEOUT      ((uint32_t) 0)
#define LOCK_MUTEX_INFINITE_TIMEOUT     ((uint32_t) -1)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC middleware mutex functions.
typedef enum {

    /**
     * Mutex (not recursive) creation.
     */
    TOMMRO_C_MW_MUTEX_CREATE = 0,

    /**
     * Mutex (recursive) creation.
     */
    TOMMRO_C_MW_MUTEX_CREATE_RECURSIVE,

    /**
     * Mutex lock.
     */
    TOMMRO_C_MW_MUTEX_LOCK,

    /**
     * Mutex unlock.
     */
    TOMMRO_C_MW_MUTEX_UNLOCK,

    /**
     * Mutex destroy.
     */
    TOMMRO_C_MW_MUTEX_DESTROY,

} tommRoC_mw_mutex_operations_enum_t;


// Mutex create callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_mutex_create_cb_funct_t)(
                void*       const   mutexPtr);

// Mutex lock callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_mutex_lock_cb_funct_t)(
                void*       const   mutexPtr,
        const   uint32_t            waitTimeoutMs);

// Mutex unlock callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_mutex_un_lock_cb_funct_t)(
                void*       const   mutexPtr);

// Mutex destroy callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_mutex_destroy_cb_funct_t)(
                void*       const   mutexPtr);


// tommRoC middleware mutex environment init data.
typedef struct {

    /**
     * Each function pointer is specific to particular mutex operation.
     * Some functions could be NULL if none/not available.
     * Some functions could not be NULL (some base functions are needed).
     *
     * Every function got specific parameters input/result output pointers.
     * Specific cast and check have to be made by software high level.
     */

    /**
     * Mutex (not recursive) create.
     *
     * NOTE: NEEDED
     */
    tommRoC_mw_mutex_create_cb_funct_t  create;

    /**
     * Mutex (recursive) create.
     *
     * NOTE: could be NULL
     */
    tommRoC_mw_mutex_create_cb_funct_t  createRecursive;

    /**
     * Mutex lock.
     *
     * NOTE: NEEDED
     */
    tommRoC_mw_mutex_lock_cb_funct_t    lock;

    /**
     * Mutex unlock.
     *
     * NOTE: NEEDED
     */
    tommRoC_mw_mutex_un_lock_cb_funct_t unLock;

    /**
     * Mutex destroy.
     *
     * NOTE: could be NULL
     */
    tommRoC_mw_mutex_destroy_cb_funct_t destroy;

} tommRoC_mw_mutex_environment_init_t;

#define __EMPTY_tommRoC_mw_mutex_environment_init_t__   \
{                                                       \
    /* .create */           NULL,                       \
    /* .createRecursive */  NULL,                       \
    /* .lock */             NULL,                       \
    /* .unLock */           NULL,                       \
    /* .destroy */          NULL,                       \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Prepare library mutex environment.
 *
 * param[in]        initEnvironmentPtr      pointer to environment init data.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwMutexEnvironmentInit(
        const   tommRoC_mw_mutex_environment_init_t*    const   initEnvironmentPtr);

/**
 * Check mutex environment.
 *
 * param[in]        environmentPtr          pointer to environment data.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwMutexEnvironmentCheck(
        const   tommRoC_mw_mutex_environment_init_t*    const   environmentPtr);

/**
 * Close library mutex environment.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwMutexCloseEnvironment(void);

/**
 * Check if a specific mutex operation is available (has been initiated).
 *
 * param[in]        mutexOp                 mutex operation.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwMutexIsOpAvailable(
        const   tommRoC_mw_mutex_operations_enum_t  mutexOp);

/**
 * Mutex (not recursive) creation.
 *
 * param[out]       mutexPtr                created mutex pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwMutexCreate(
                void*       const   mutexPtr);

/**
 * Mutex (recursive) creation.
 *
 * param[out]       mutexPtr                created mutex pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwMutexCreateRecursive(
                void*       const   mutexPtr);

/**
 * Mutex lock.
 *
 * param[in/out]    mutexPtr                mutex pointer (retrived by mutex create funct).
 * param[in]        waitTimeoutMs           wait lock mutex timeout [msec].
 *                                          use LOCK_MUTEX_NO_WAIT_TIMEOUT for no wait.
 *                                          use LOCK_MUTEX_INFINITE_TIMEOUT for wait forever.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwMutexLock(
                void*       const   mutexPtr,
        const   uint32_t            waitTimeoutMs);

/**
 * Mutex unlock.
 *
 * param[in/out]    mutexPtr                mutex pointer (retrived by mutex create funct).
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwMutexUnLock(
                void*       const   mutexPtr);

/**
 * Mutex destroy.
 *
 * param[in/out]    mutexPtr                mutex pointer (retrived by mutex create funct).
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwMutexDestroy(
                void*       const   mutexPtr);

#endif
