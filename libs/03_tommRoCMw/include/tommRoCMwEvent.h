
#ifndef TOMMROC_MW_EVENT_H_
#define TOMMROC_MW_EVENT_H_

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
#define WAIT_EVENT_NO_WAIT_TIMEOUT      ((uint32_t) 0)
#define WAIT_EVENT_INFINITE_TIMEOUT     ((uint32_t) -1)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC middleware events functions.
typedef enum {

    /**
     * Event creation.
     */
    TOMMRO_C_MW_EVENT_CREATE = 0,

    /**
     * Event signal.
     */
    TOMMRO_C_MW_EVENT_SIGNAL,

    /**
     * Event wait.
     */
    TOMMRO_C_MW_EVENT_WAIT,

    /**
     * Event wait for all.
     */
    TOMMRO_C_MW_EVENT_WAIT_FOR_ALL,

    /**
     * Event wait for any.
     */
    TOMMRO_C_MW_EVENT_WAIT_FOR_ANY,

    /**
     * Event clear.
     */
    TOMMRO_C_MW_EVENT_CLEAR,

    /**
     * Event destroy.
     */
    TOMMRO_C_MW_EVENT_DESTROY,

} tommRoC_mw_event_operations_enum_t;


// Event create callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_event_create_cb_funct_t)(
                void*       const   eventPtr);

// Event signal callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_event_signal_cb_funct_t)(
                void*       const   eventPtr);

// Event wait callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_event_wait_cb_funct_t)(
                void*       const   eventPtr,
        const   uint32_t            waitTimeoutMs);

// Events wait for all callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_event_wait_for_all_cb_funct_t)(
                void*       const   eventsPtr,
        const   uint8_t             eventsAmount,
        const   uint32_t            waitTimeoutMs);

// Events wait for any callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_event_wait_for_any_cb_funct_t)(
                void*       const   eventsPtr,
        const   uint8_t             eventsAmount,
        const   uint32_t            waitTimeoutMs,
                void*       const   signaledEventsPtr,
        const   uint8_t             signaledEventsAmount,
                uint8_t*    const   signaledEventsAmountPtr);

// Events clear callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_event_clear_cb_funct_t)(
                void*       const   eventsPtr,
        const   uint8_t             eventsAmount);

// Event destroy callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_event_destroy_cb_funct_t)(
                void*       const   eventPtr);


// tommRoC middleware event environment init data.
typedef struct {

    /**
     * Each function pointer is specific to particular event operation.
     * Some functions could be NULL if none/not available.
     * Some functions could not be NULL (some base functions are needed).
     *
     * Every function got specific parameters input/result output pointers.
     * Specific cast and check have to be made by software high level.
     */

    /**
     * Event create.
     *
     * NOTE: NEEDED
     */
    tommRoC_mw_event_create_cb_funct_t          create;

    /**
     * Event signal.
     *
     * NOTE: NEEDED
     */
    tommRoC_mw_event_signal_cb_funct_t          signal;

    /**
     * Event wait.
     *
     * NOTE: NEEDED
     */
    tommRoC_mw_event_wait_cb_funct_t            wait;

    /**
     * Event wait for all.
     *
     * NOTE: could be NULL
     */
    tommRoC_mw_event_wait_for_all_cb_funct_t    waitForAll;

    /**
     * Event wait for any.
     *
     * NOTE: could be NULL
     */
    tommRoC_mw_event_wait_for_any_cb_funct_t    waitForAny;

    /**
     * Event clear.
     *
     * NOTE: NEEDED
     */
    tommRoC_mw_event_clear_cb_funct_t           clear;

    /**
     * Event destroy.
     *
     * NOTE: NEEDED
     */
    tommRoC_mw_event_destroy_cb_funct_t         destroy;

} tommRoC_mw_event_environment_init_t;

#define __EMPTY_tommRoC_mw_event_environment_init_t__       \
{                                                           \
    /* .create */       NULL,                               \
    /* .signal */       NULL,                               \
    /* .wait */         NULL,                               \
    /* .waitForAll */   NULL,                               \
    /* .waitForAny */   NULL,                               \
    /* .clear */        NULL,                               \
    /* .destroy */      NULL,                               \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Prepare library event environment.
 *
 * param[in]        initEnvironmentPtr      pointer to environment init data.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwEventEnvironmentInit(
        const   tommRoC_mw_event_environment_init_t*    const   initEnvironmentPtr);

/**
 * Check event environment.
 *
 * param[in]        environmentPtr          pointer to environment data.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwEventEnvironmentCheck(
        const   tommRoC_mw_event_environment_init_t*    const   environmentPtr);

/**
 * Close library event environment.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwEventCloseEnvironment(void);

/**
 * Check if a specific event operation is available (has been initiated).
 *
 * param[in]        eventOp                 event operation.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwEventIsOpAvailable(
        const   tommRoC_mw_event_operations_enum_t  eventOp);

/**
 * Event creation.
 *
 * param[out]       eventPtr                created event pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwEventCreate(
                void*       const   eventPtr);

/**
 * Event signal.
 *
 * param[in/out]    eventPtr                event pointer (retrived by event create funct).
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwEventSignal(
                void*       const   eventPtr);

/**
 * Single event wait.
 *
 * param[in/out]    eventPtr                event pointer (retrived by event create funct).
 * param[in]        waitTimeoutMs           wait event timeout [msec].
 *                                          use WAIT_EVENT_NO_WAIT_TIMEOUT for no wait.
 *                                          use WAIT_EVENT_INFINITE_TIMEOUT for wait forever.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwEventWait(
                void*       const   eventPtr,
        const   uint32_t            waitTimeoutMs);

/**
 * Multiple event wait.
 * NOTE: wait for all events.
 *
 * param[in/out]    eventPtr                events pointer (retrived by event create funct).
 * param[in]        eventsAmount            events amount.
 * param[in]        waitTimeoutMs           wait event timeout [msec].
 *                                          use WAIT_EVENT_NO_WAIT_TIMEOUT for no wait.
 *                                          use WAIT_EVENT_INFINITE_TIMEOUT for wait forever.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwEventWaitForAll(
                void*       const   eventsPtr,
        const   uint8_t             eventsAmount,
        const   uint32_t            waitTimeoutMs);

/**
 * Multiple event wait.
 * NOTE: wait for any events.
 *
 * param[in]        eventsPtr               events pointer array (retrived by event create funct).
 * param[in]        eventsAmount            events array amount.
 * param[in]        waitTimeoutMs           wait event timeout [msec].
 *                                          use WAIT_EVENT_NO_WAIT_TIMEOUT for no wait.
 *                                          use WAIT_EVENT_INFINITE_TIMEOUT for wait forever.
 * param[out]       signaledEventsPtr       output signaled events pointer array.
 * param[in]        signaledEventsAmount    signaled events array amount.
 * param[out]       signaledEventsAmountPtr output signaled events amount pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwEventWaitForAny(
                void*       const   eventsPtr,
        const   uint8_t             eventsAmount,
        const   uint32_t            waitTimeoutMs,
                void*       const   signaledEventsPtr,
        const   uint8_t             signaledEventsAmount,
                uint8_t*    const   signaledEventsAmountPtr);

/**
 * Events clear.
 *
 * param[in]        eventsPtr               events pointer array (retrived by event create funct).
 * param[in]        eventsAmount            events array amount.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwEventClear(
                void*       const   eventsPtr,
        const   uint8_t             eventsAmount);

/**
 * Event destroy.
 *
 * param[in/out]    eventPtr                event pointer (retrived by event create funct).
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwEventDestroy(
                void*       const   eventPtr);

#endif
