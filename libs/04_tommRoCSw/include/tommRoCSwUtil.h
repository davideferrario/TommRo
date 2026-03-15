
#ifndef TOMMROC_SW_UTIL_H_
#define TOMMROC_SW_UTIL_H_

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
#include "tommRoCSwErr.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/**
 * Block code tommRoC SW error result function execution
 */
#define TOMMROC_SW_UTIL_BLOCK_CODE_TOMMROC_SW_LIB_FUNCT(    \
        onEnterCallFunctWithParam,                          \
        onExitCallFunctWithParam,                           \
        callFunctWithParam)                                 \
        TOMMROC_UTIL_BLOCK_CODE_WITH_RESULT_FUNCT(          \
                tommRoC_sw_err_enum_t,                      \
                onEnterCallFunctWithParam,                  \
                onExitCallFunctWithParam,                   \
                callFunctWithParam)

/**
 * Synchronized (guarded) tommRoC SW error result function execution.
 */
#define TOMMROC_SW_UTIL_SYNCHRO_TOMMROC_SW_LIB_FUNCT(guardPtr, callFunctWithParam)  \
        TOMMROC_GUARD_SYNCHRO_WITH_RESULT_FUNCT(                                    \
                tommRoC_sw_err_enum_t,                                              \
                guardPtr,                                                           \
                TOMMRO_C_SW_GENERIC_ERR,                                            \
                callFunctWithParam);

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
