
#ifndef TOMMROC_MW_THREAD_H_
#define TOMMROC_MW_THREAD_H_

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
#define TOMMRO_C_MW_THREAD_STACK_SIZE_DEFAULT       ((uint32_t) -1)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC middleware thread functions.
typedef enum {

    /**
     * Thread creation (and start).
     */
    TOMMRO_C_MW_THREAD_CREATE = 0,

    /**
     * Thread get ID.
     */
    TOMMRO_C_MW_THREAD_GET_ID,

    /**
     * Thread destroy.
     */
    TOMMRO_C_MW_THREAD_DESTROY,

    /**
     * Caller thread destroy.
     */
    TOMMRO_C_MW_THREAD_EXIT,

    /**
     * Thread join.
     */
    TOMMRO_C_MW_THREAD_JOIN,

    /**
     * Thread try join.
     */
    TOMMRO_C_MW_THREAD_TRYJOIN,

    /**
     * Thread yield.
     */
    TOMMRO_C_MW_THREAD_YIELD,

    /**
     * Thread suspend all.
     */
    TOMMRO_C_MW_THREAD_SUSPEND_ALL,

    /**
     * Thread resume all.
     */
    TOMMRO_C_MW_THREAD_RESUME_ALL,

} tommRoC_mw_thread_operations_enum_t;


// Enumeration of tommRoC middleware thread priority.
typedef enum  {

    TOMMRO_C_MW_THREAD_PRIORITY_IDLE = 0,           // Lowest (background)
    TOMMRO_C_MW_THREAD_PRIORITY_LOW,
    TOMMRO_C_MW_THREAD_PRIORITY_BELOW_NORMAL,
    TOMMRO_C_MW_THREAD_PRIORITY_NORMAL,             // Normal
    TOMMRO_C_MW_THREAD_PRIORITY_ABOVE_NORMAL,
    TOMMRO_C_MW_THREAD_PRIORITY_HIGH,
    TOMMRO_C_MW_THREAD_PRIORITY_REALTIME,           // Realtime (critical)

    TOMMRO_C_MW_THREAD_PRIORITY_DEFAULT,            // Low level environment default value.

} tommRoC_mw_thread_priority_enum_t;


// tommRoC middleware thread configuration.
typedef struct {

    /**
     * Priority (if available).
     */
    tommRoC_mw_thread_priority_enum_t   priority;

    /**
     * Stack size (if available) [byte].
     */
    uint32_t                            stackSize;

} tommRoC_mw_thread_config_t;

#define __EMPTY_tommRoC_mw_thread_config_t__                    \
{                                                               \
    /* .priority */     TOMMRO_C_MW_THREAD_PRIORITY_DEFAULT,    \
    /* .stackSize */    TOMMRO_C_MW_THREAD_STACK_SIZE_DEFAULT,  \
}


// Thread main function type.
typedef void (*tommRoC_mw_thread_main_funct_t)(void* const arg);

// Thread create callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_thread_create_cb_funct_t)(
        const   tommRoC_mw_thread_main_funct_t          mainThread,
                void*                           const   mainThreadArgPtr,
        const   char*                           const   threadNameStrPtr,
        const   tommRoC_mw_thread_config_t*     const   configPtr,
                void*                           const   threadPtr);

// Thread get ID callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_thread_get_id_cb_funct_t)(
                void*                           const   threadIDPtr);

// Thread destroy callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_thread_destroy_cb_funct_t)(
                void*                           const   threadPtr);

// Caller thread destroy callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_thread_exit_cb_funct_t)(void);

// Thread join callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_thread_join_cb_funct_t)(
        const   void*                           const   threadPtr);

// Thread try join callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_thread_try_join_cb_funct_t)(
        const   void*                           const   threadPtr);

// Thread yield callback function type.
typedef tommRoC_work_test_context_yield_funct_t tommRoC_mw_thread_yield_cb_funct_t;

// Thread suspend all callback function type.
typedef void (*tommRoC_mw_thread_suspend_all_cb_funct_t)(void);

// Thread resume all callback function type.
typedef void (*tommRoC_mw_thread_resume_all_cb_funct_t)(void);


// tommRoC middleware thread environment init data.
typedef struct {

    /**
     * Each function pointer is specific to particular thread operation.
     * Some functions could be NULL if none/not available.
     * Some functions could not be NULL (some base functions are needed).
     *
     * Every function got specific parameters input/result output pointers.
     * Specific cast and check have to be made by software high level.
     */

    /**
     * Thread create.
     *
     * NOTE: NEEDED
     */
    tommRoC_mw_thread_create_cb_funct_t         create;

    /**
     * Thread get ID.
     *
     * NOTE: could be NULL
     */
    tommRoC_mw_thread_get_id_cb_funct_t         getID;

    /**
     * Thread destroy.
     * This will cancel thread, but you MUST be sure that the thread has released any
     * resources that it has obtained before it actually dies.
     *
     * NOTE: could be NULL
     */
    tommRoC_mw_thread_destroy_cb_funct_t        destroy;

    /**
     * Caller thread destroy.
     * This will exit - cancel - caller thread, but you MUST be sure that the thread has released any
     * resources that it has obtained before it actually dies.
     *
     * NOTE: could be NULL
     */
    tommRoC_mw_thread_exit_cb_funct_t           exit;

    /**
     * Thread join (wait for the thread to terminate).
     *
     * NOTE: could be NULL
     */
    tommRoC_mw_thread_join_cb_funct_t           join;

    /**
     * Thread try join (non blocking check for the thread to terminate).
     *
     * NOTE: could be NULL
     */
    tommRoC_mw_thread_try_join_cb_funct_t       tryJoin;

    /**
     * Thread yield.
     *
     * NOTE: NEEDED
     */
    tommRoC_mw_thread_yield_cb_funct_t          yield;

    /**
     * Thread suspend all.
     *
     * NOTE: could be NULL
     */
    tommRoC_mw_thread_suspend_all_cb_funct_t    suspendAll;

    /**
     * Thread resume all.
     *
     * NOTE: could be NULL
     */
    tommRoC_mw_thread_resume_all_cb_funct_t     resumeAll;

} tommRoC_mw_thread_environment_init_t;

#define __EMPTY_tommRoC_mw_thread_environment_init_t__  \
{                                                       \
    /* .create */       NULL,                           \
    /* .getID */        NULL,                           \
    /* .destroy */      NULL,                           \
    /* .exit */         NULL,                           \
    /* .join */         NULL,                           \
    /* .tryJoin */      NULL,                           \
    /* .yield */        NULL,                           \
    /* .suspendAll */   NULL,                           \
    /* .resumeAll */    NULL,                           \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Prepare library thread environment.
 *
 * param[in]        initEnvironmentPtr      pointer to environment init data.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwThreadEnvironmentInit(
        const   tommRoC_mw_thread_environment_init_t*   const   initEnvironmentPtr);

/**
 * Check thread environment.
 *
 * param[in]        environmentPtr          pointer to environment data.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwThreadEnvironmentCheck(
        const   tommRoC_mw_thread_environment_init_t*   const   environmentPtr);

/**
 * Close library thread environment.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwThreadCloseEnvironment(void);

/**
 * Check if a specific thread operation is available (has been initiated).
 *
 * param[in]        threadOp                thread operation.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwThreadIsOpAvailable(
        const   tommRoC_mw_thread_operations_enum_t threadOp);

/**
 * Thread creation.
 *
 * param[in]        mainThread              function pointer to thread main funct.
 * param[in]        mainThreadArgPtr        thread main funct args pointer.
 *                                          NOTE: use to pass input param and pass pointer to thread result.
 * param[in]        threadNameStrPtr        thread name string pointer (NULL if using default).
 * param[in]        configPtr               thread configuration pointer.
 * param[out]       threadPtr               created thread pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwThreadCreate(
        const   tommRoC_mw_thread_main_funct_t          mainThread,
                void*                           const   mainThreadArgPtr,
        const   char*                           const   threadNameStrPtr,
        const   tommRoC_mw_thread_config_t*     const   configPtr,
                void*                           const   threadPtr);

/**
 * Thread creation with specific config.
 *
 * param[in]        mainThread              function pointer to thread main funct.
 * param[in]        mainThreadArgPtr        thread main funct args pointer.
 *                                          NOTE: use to pass input param and pass pointer to thread result.
 * param[in]        threadNameStrPtr        thread name string pointer (NULL if using default).
 * param[in]        priority                thread priority (if available).
 * param[in]        stackSize               thread stack size (if available) [byte].
 * param[out]       threadPtr               created thread pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwThreadCreateConfig(
        const   tommRoC_mw_thread_main_funct_t          mainThread,
                void*                           const   mainThreadArgPtr,
        const   char*                           const   threadNameStrPtr,
        const   tommRoC_mw_thread_priority_enum_t       priority,
        const   uint32_t                                stackSize,
                void*                           const   threadPtr);

/**
 * Thread as default creation.
 *
 * param[in]        mainThread              function pointer to thread main funct.
 * param[in]        threadNameStrPtr        thread name string pointer (NULL if using default).
 * param[out]       threadPtr               created thread pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwThreadCreateAsDefault(
        const   tommRoC_mw_thread_main_funct_t          mainThread,
        const   char*                           const   threadNameStrPtr,
                void*                           const   threadPtr);

/**
 * Get the thread ID of the current running thread.
 * NOTE: MUST REMAIN UNCHANGED.
 *
 * param[out]       threadIDPtr             thread ID pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwThreadGetID(
                void*                           const   threadIDPtr);

/**
 * Compare thread IDs.
 *
 * param[in]        thread1IDPtr            thread 1 ID pointer.
 * param[in]        thread2IDPtr            thread 2 ID pointer.
 * param[in]        threadIDSize            thread ID size [byte].
 *
 * return tommRoC_mw_err_enum_t
 *          TOMMRO_C_MW_ERR_SUCCESS     -> compare success.
 *          TOMMRO_C_MW_GENERIC_ERR     -> compare fails.
 *          TOMMRO_C_MW_NULL_PARAM_ERR  -> NULL param error.
 *          TOMMRO_C_MW_PARAM_ERR       -> param error.
 */
tommRoC_mw_err_enum_t tommRoCMwThreadCompareID(
        const   void*                           const   thread1IDPtr,
        const   void*                           const   thread2IDPtr,
        const   uint32_t                                threadIDSize);

/**
 * Thread destroy.
 * NOTE: this will cancel thread, but you MUST be sure that the thread has released any resources that it has obtained before it actually dies.
 *
 * param[in]        threadPtr               thread pointer (retrived by thread create funct).
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwThreadDestroy(
                void*                           const   threadPtr);

/**
 * Caller thread destroy.
 * NOTE: this will exit - cancel - caller thread, but you MUST be sure that the thread has released any resources that it has obtained before it actually dies.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwThreadExit(void);

/**
 * Thread join (wait for thread termination).
 *
 * param[in]        threadPtr               thread pointer (retrived by thread create funct).
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwThreadJoin(
        const   void*                           const   threadPtr);

/**
 * Thread try join (non blocking check for the thread to terminate).
 *
 * param[in]        threadPtr               thread pointer (retrived by thread create funct).
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwThreadTryJoin(
        const   void*                           const   threadPtr);

/**
 * Calling thread yield.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwThreadYield(void);

/**
 * Thread suspend all.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwThreadSuspendAll(void);

/**
 * Thread resume all.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwThreadResumeAll(void);

#endif
