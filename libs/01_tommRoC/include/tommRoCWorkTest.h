
#ifndef TOMMROC_WORK_TEST_H_
#define TOMMROC_WORK_TEST_H_

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
 * @defgroup tommRoCWorkTest tommRoCWorkTest
 *
 * @brief  TommRoC library work test module
 * @author TommRo Software Department
 *
 * This module is providing more accurate source code testing functionality.
 *
 * This will introduce some extra code.
 *
 * Please, remember to disable (not define __TOMMROC_WORK_TEST_ENABLE__) this in your application release version binaries
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"

/*******************************************************************************
 * defines
 ******************************************************************************/
 
/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC Work Test init environment resource to set.
typedef enum {

    /**
     * Context yield function environment resource.
     *
     * This will set the callback function that will be called for request context yield.
     * This is used for random thread yield in multithread environment (to provoke
     * multipath thread execution).
     * If enabled (defined __TOMMROC_WORK_TEST_ENABLE__) a random context yield
     * is called inside tommRoC library source code.
     *
     * initResourcePtr have to be tommRoC_work_test_context_yield_funct_t.
     */
    TOMMRO_C_WORK_TEST_CONTEXT_YIELD_FUNCT_RES = 0,

} tommRoC_work_test_environment_resource_enum_t;


// tommRoC Work Test context yield environment resource init data.
typedef void (*tommRoC_work_test_context_yield_funct_t)(void);

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Prepare single library Work Test environment.
 * NOTE: to be used for compiler (e.g.: XC8) that are not able to distinguish internal switch and generate recursive function error message.
 *
 * param[in]        initResourcePtr         pointer to environment resource init data.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCWorkTestInitContextYield(const tommRoC_work_test_context_yield_funct_t initResourcePtr);

/**
 * Close single library Work Test environment.
 * NOTE: to be used for compiler (e.g.: XC8) that are not able to distinguish internal switch and generate recursive function error message.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCWorkTestCloseContextYield(void);


/**
 * Prepare library Work Test environment.
 *
 * param[in]        resource                init environment resource to set
 * param[in]        initResourcePtr         pointer to environment resource init data.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCWorkTestInitEnv(
        const   tommRoC_work_test_environment_resource_enum_t           resource,
        const   void*                                           const   initResourcePtr);

/**
 * Close library Work Test environment.
 *
 * param[in]        resource                Test init environment resource to set
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCWorkTestCloseEnv(
        const   tommRoC_work_test_environment_resource_enum_t           resource);

/**
 * @}
 */

#endif
