
#ifndef TOMMROC_MW_TIMER_H_
#define TOMMROC_MW_TIMER_H_

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

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC middleware timer functions.
typedef enum {

    /**
     * Timer creation.
     * NOTE: timer is only created; not started.
     */
    TOMMRO_C_MW_TIMER_CREATE = 0,
    
    /**
     * Timer start.
     */
    TOMMRO_C_MW_TIMER_START,
    
    /**
     * Timer stop.
     */
    TOMMRO_C_MW_TIMER_STOP,

    /**
     * Timer destroy.
     */
    TOMMRO_C_MW_TIMER_DESTROY,

} tommRoC_mw_timer_operations_enum_t;


// Enumeration of tommRoC middleware timer type.
typedef enum  {

    TOMMRO_C_MW_TIMER_TYPE_ONE_SHOT = 0,
    TOMMRO_C_MW_TIMER_TYPE_PERIODIC,
    
} tommRoC_mw_timer_type_enum_t;


// Timer callback function type.
typedef void (*tommRoC_mw_timer_cb_funct_t)(void* const arg);

// Timer create callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_timer_create_cb_funct_t)(
        const   uint32_t                                periodMsec,
        const   tommRoC_mw_timer_type_enum_t            type,
        const   tommRoC_mw_timer_cb_funct_t             cbFunctPtr,
                void*                           const   timerPtr);

// Timer destroy callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_timer_destroy_cb_funct_t)(
                void*                           const   timerPtr);

// Timer start callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_timer_start_cb_funct_t)(
                void*                           const   timerPtr);

// Timer stop callback function type.
typedef tommRoC_mw_err_enum_t (*tommRoC_mw_timer_stop_cb_funct_t)(
                void*                           const   timerPtr);


// tommRoC middleware timer environment init data.
typedef struct {

    /**
     * Each function pointer is specific to particular timer operation.
     * Some functions could be NULL if none/not available.
     * Some functions could not be NULL (some base functions are needed).
     *
     * Every function got specific parameters input/result output pointers.
     * Specific cast and check have to be made by software high level.
     */

    /**
     * Timer create.
     *
     * NOTE: NEEDED
     */
    tommRoC_mw_timer_create_cb_funct_t  create;

    /**
     * Timer destroy.
     *
     * NOTE: could be NULL
     */
    tommRoC_mw_timer_destroy_cb_funct_t destroy;

    /**
     * Timer start.
     *
     * NOTE: NEEDED
     */
    tommRoC_mw_timer_start_cb_funct_t   start;

    /**
     * Timer stop.
     *
     * NOTE: could be NULL
     */
    tommRoC_mw_timer_stop_cb_funct_t    stop;

} tommRoC_mw_timer_environment_init_t;

#define __EMPTY_tommRoC_mw_timer_environment_init_t__   \
{                                                       \
    /* .create */   NULL,                               \
    /* .destroy */  NULL,                               \
    /* .start */    NULL,                               \
    /* .stop */     NULL,                               \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Prepare library timer environment.
 *
 * param[in]        initEnvironmentPtr      pointer to environment init data.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwTimerEnvironmentInit(
        const   tommRoC_mw_timer_environment_init_t*    const   initEnvironmentPtr);

/**
 * Check timer environment.
 *
 * param[in]        environmentPtr          pointer to environment data.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwTimerEnvironmentCheck(
        const   tommRoC_mw_timer_environment_init_t*    const   environmentPtr);

/**
 * Close library timer environment.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwTimerCloseEnvironment(void);

/**
 * Check if a specific timer operation is available (has been initiated).
 *
 * param[in]        timerOp                 timer operation.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwTimerIsOpAvailable(
        const   tommRoC_mw_timer_operations_enum_t  timerOp);

/**
 * Timer creation.
 * param[in]        periodMsec              timer period [msec].
 * param[in]        type                    timer type.
 * param[in]        cbFunctPtr              timer callback function to call when the timer expires pointer.
 * param[out]       timerPtr                created timer pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwTimerCreate(
        const   uint32_t                                periodMsec,
        const   tommRoC_mw_timer_type_enum_t            type,
        const   tommRoC_mw_timer_cb_funct_t             cbFunctPtr,
                void*                           const   timerPtr);

/**
 * Timer destroy.
 *
 * param[in/out]    timerPtr                timer pointer (retrived by timer create funct).
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwTimerDestroy(
                void*                           const   timerPtr);

/**
 * Timer start.
 *
 * param[in/out]    timerPtr                timer pointer (retrived by timer create funct).
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwTimerStart(
                void*                           const   timerPtr);

/**
 * Timer stop.
 *
 * param[in/out]    timerPtr                timer pointer (retrived by timer create funct).
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwTimerStop(
                void*                           const   timerPtr);

#endif
