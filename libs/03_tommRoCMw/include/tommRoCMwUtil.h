
#ifndef TOMMROC_MW_UTIL_H_
#define TOMMROC_MW_UTIL_H_

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

#include "TOMMROC.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/**
 * Block code tommRoC MW error result function execution
 */
#define TOMMROC_MW_UTIL_BLOCK_CODE_TOMMROC_MW_LIB_FUNCT(    \
        onEnterCallFunctWithParam,                          \
        onExitCallFunctWithParam,                           \
        callFunctWithParam)                                 \
        TOMMROC_UTIL_BLOCK_CODE_WITH_RESULT_FUNCT(          \
                tommRoC_mw_err_enum_t,                      \
                onEnterCallFunctWithParam,                  \
                onExitCallFunctWithParam,                   \
                callFunctWithParam)

/**
 * Synchronized (guarded) tommRoC MW error result function execution.
 */
#define TOMMROC_MW_UTIL_SYNCHRO_TOMMROC_MW_LIB_FUNCT(guardPtr, callFunctWithParam)  \
        TOMMROC_GUARD_SYNCHRO_WITH_RESULT_FUNCT(                                    \
                tommRoC_mw_err_enum_t,                                              \
                guardPtr,                                                           \
                TOMMRO_C_MW_GENERIC_ERR,                                            \
                callFunctWithParam);

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC middleware user interface type.
typedef enum {

    /**
     * Console user interface type.
     */
    TOMMRO_C_MW_UTIL_CONSOLE_INTERFACE_TYPE = 0,

    /**
     * Graphical user interface type.
     */
    TOMMRO_C_MW_UTIL_GRAPHICAL_INTERFACE_TYPE,

} tommRoC_mw_util_user_interface_type_enum_t;


// Enumeration of tommRoC middleware utility properties.
typedef enum {

    /**
     * User interface interface type.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be tommRoC_mw_util_user_interface_type_enum_t*
     */
    TOMMRO_C_MW_UTIL_USER_INTERFACE_PROP = 0,

} tommRoC_mw_util_prop_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Execute a shell command.
 *
 * param[in]    cmdStringPtr            shell command string.
 * param[out]   resultStringPtr         shell command result output string (NULL if not needed).
 * param[in]    resultStringMaxSize     shell command result output string max size [byte] (0 if not needed).
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwUtilShellCommand(
        const   char*       const   cmdStringPtr,
                char*       const   resultStringPtr,
        const   uint16_t            resultStringMaxSize);

/**
 * Get middleware utility property.
 *
 * param[in]    property                property.
 * param[out]   propValuePtr            result value pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwUtilGetProp(
        const   tommRoC_mw_util_prop_enum_t         property,
                void*                       const   propValuePtr);

/**
 * Set middleware utility property.
 *
 * param[in]    property                property.
 * param[in]    propValuePtr            result value pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwUtilSetProp(
        const   tommRoC_mw_util_prop_enum_t         property,
        const   void*                       const   propValuePtr);

#endif
