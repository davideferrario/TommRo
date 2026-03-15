
#ifndef TOMMROC_MW_PARAM_CHECK_H_
#define TOMMROC_MW_PARAM_CHECK_H_

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

#include <stddef.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/**
 * True test parameter check.
 * NOTE: if condition is true, TOMMRO_C_MW_PARAM_ERR is returned.
 */
#define TOMMROC_MW_PARAM_CHECK_ON_TRUE_RETURN_ERR(condition)            \
        do {                                                            \
            if ((condition)) {                                          \
                return TOMMRO_C_MW_PARAM_ERR;                           \
            }                                                           \
        } while (0)

/**
 * False test parameter check.
 * NOTE: if condition is false, TOMMRO_C_MW_PARAM_ERR is returned.
 */
#define TOMMROC_MW_PARAM_CHECK_ON_FALSE_RETURN_ERR(condition)           \
        do {                                                            \
            if ((!(condition))) {                                       \
                return TOMMRO_C_MW_PARAM_ERR;                           \
            }                                                           \
        } while (0)

/**
 * Generic test parameter check.
 * NOTE: if test success, TOMMRO_C_MW_PARAM_ERR is returned.
 */
#define TOMMROC_MW_PARAM_CHECK_ON_TEST_RETURN_ERR(param, test, value)   \
        do {                                                            \
            if ((param) test (value)) {                                 \
                return TOMMRO_C_MW_PARAM_ERR;                           \
            }                                                           \
        } while (0)

/**
 * Not NULL parameter check.
 * NOTE: if parameter is NULL, TOMMRO_C_MW_NULL_PARAM_ERR is returned.
 */
#define TOMMROC_MW_PARAM_CHECK_ON_NULL_RETURN_ERR(param)                \
        do {                                                            \
            if (NULL == param) {                                        \
                return TOMMRO_C_MW_NULL_PARAM_ERR;                      \
            }                                                           \
        } while (0)

/**
 * Not NULL parameter check.
 * NOTE: if parameter is not NULL, TOMMRO_C_MW_NULL_PARAM_ERR is returned.
 */
#define TOMMROC_MW_PARAM_CHECK_ON_NOT_NULL_RETURN_ERR(param)            \
        do {                                                            \
            if (NULL != param) {                                        \
                return TOMMRO_C_MW_NULL_PARAM_ERR;                      \
            }                                                           \
        } while (0)

/**
 * Zero parameter check.
 * NOTE: if parameter is zero, TOMMRO_C_MW_PARAM_ERR is returned.
 */
#define TOMMROC_MW_PARAM_CHECK_ON_ZERO_RETURN_ERR(param)                \
        TOMMROC_MW_PARAM_CHECK_ON_TEST_RETURN_ERR(param, ==, 0)

/**
 * Not zero parameter check.
 * NOTE: if parameter is not zero, TOMMRO_C_MW_PARAM_ERR is returned.
 */
#define TOMMROC_MW_PARAM_CHECK_ON_NOT_ZERO_RETURN_ERR(param)            \
        TOMMROC_MW_PARAM_CHECK_ON_TEST_RETURN_ERR(param, !=, 0)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
