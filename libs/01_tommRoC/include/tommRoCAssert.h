
#ifndef TOMMROC_ASSERT_H_
#define TOMMROC_ASSERT_H_

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
 * @defgroup tommRoCAssert tommRoCAssert
 *
 * @brief  TommRoC library assert module
 * @author TommRo Software Department
 *
 * This module is providing assert functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCEnv.h"
#include "tommRoCErr.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * Avoid default XC compiler assert include.
 * NOTE: default XC compiler assert function use too much memory code!!!
 */
#if !(defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8) || defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC16) || defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC32))
#include <assert.h>
#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

/**
 * Assert function definition if using XC compiler.
 */
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8) || defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC16) || defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC32)

#undef assert
#define assert(e)                   do { if (!(e)) { asm("reset"); } } while (0)

#endif

/**
 * Macro to assert conditions in source code.
 *
 * To enable library assert, the definition of "__TOMMROC_ASSERT_ENABLE__"
 * in high level source code or framework is needed
 */
#if defined (__TOMMROC_ASSERT_ENABLE__)
#define TOMMROC_ASSERT(e)                                           \
        do {                                                        \
            if (!(e)) {                                             \
                if (TOMMRO_C_ERR_SUCCESS != tommRoCAssertCb()) {    \
                    assert(e);                                      \
                }                                                   \
            }                                                       \
        } while (0)
#else
#define TOMMROC_ASSERT(e)
#endif

#define TOMMROC_ASSERT_TEST(e1, test, e2)                   TOMMROC_ASSERT((e1) test (e2))

#define TOMMROC_ASSERT_EQUALS(e1, e2)                       TOMMROC_ASSERT_TEST(((long int) (e2)), ==, ((long int) (e1)))
#define TOMMROC_ASSERT_NOT_EQUALS(e1, e2)                   TOMMROC_ASSERT_TEST(((long int) (e2)), !=, ((long int) (e1)))
#define TOMMROC_ASSERT_LESS_THAN(e1, e2)                    TOMMROC_ASSERT_TEST(((long int) (e1)), <,  ((long int) (e2)))
#define TOMMROC_ASSERT_LESS_OR_EQUALS_THAN(e1, e2)          TOMMROC_ASSERT_TEST(((long int) (e1)), <=, ((long int) (e2)))
#define TOMMROC_ASSERT_MORE_THAN(e1, e2)                    TOMMROC_ASSERT_TEST(((long int) (e1)), >,  ((long int) (e2)))
#define TOMMROC_ASSERT_MORE_OR_EQUALS_THAN(e1, e2)          TOMMROC_ASSERT_TEST(((long int) (e1)), >=, ((long int) (e2)))

#define TOMMROC_ASSERT_TRUE(e)                              TOMMROC_ASSERT(e)
#define TOMMROC_ASSERT_FALSE(e)                             TOMMROC_ASSERT((!!!(e)))

#define TOMMROC_ASSERT_NULL(e)                              TOMMROC_ASSERT_TEST(NULL, ==, e)
#define TOMMROC_ASSERT_NOT_NULL(e)                          TOMMROC_ASSERT_TEST(NULL, !=, e)
#define TOMMROC_ASSERT_ZERO(e)                              TOMMROC_ASSERT_EQUALS(e, 0)
#define TOMMROC_ASSERT_NOT_ZERO(e)                          TOMMROC_ASSERT_NOT_EQUALS(e, 0)

#if defined (__TOMMROC_ASSERT_ENABLE__)
#define TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(funct, result)   TOMMROC_ASSERT_TEST(result, ==, funct)
#else
#define TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(funct, result)   funct
#endif

#define TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(funct)     TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(funct, TOMMRO_C_ERR_SUCCESS)


/**
 * Macro to init assert on-error callback framework.
 * NOTE: USE THIS IN USER CODE.
 */
#if defined (__TOMMROC_ASSERT_ENABLE__)
#define ASSERT_CB_INIT(onErrorCallback)                     tommRoCAssertCbInit((onErrorCallback))
#else
#define ASSERT_CB_INIT(onErrorCallback)                     (TOMMRO_C_ERR_SUCCESS)
#endif

/**
 * Macro to close assert on-error callback framework.
 * NOTE: USE THIS IN USER CODE.
 */
#if defined (__TOMMROC_ASSERT_ENABLE__)
#define ASSERT_CB_CLOSE()                                   tommRoCAssertCbClose()
#else
#define ASSERT_CB_CLOSE()                                   (TOMMRO_C_ERR_SUCCESS)
#endif

/**
 * Macro to get on-error callback function pointer.
 * NOTE: USE THIS IN USER CODE.
 */
#if defined (__TOMMROC_ASSERT_ENABLE__)
#define ASSERT_CB_GET()                                     tommRoCAssertCbGet()
#else
#define ASSERT_CB_GET()                                     (TOMMRO_C_ERR_SUCCESS)
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/**
 * On error callback function type.
 */
typedef void (*tommRoC_assert_on_error_callback_funct_t)(void);

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init assert on-error callback function. After init, the callback is enabled by default.
 * NOTE: DO NOT USE IN USER CODE; it's for internal use.
 */
tommRoC_err_enum_t tommRoCAssertCbInit(
        const   tommRoC_assert_on_error_callback_funct_t    onErrorCallback);

/**
 * Close (clear) assert on-error callback function.
 * NOTE: DO NOT USE IN USER CODE; it's for internal use.
 */
tommRoC_err_enum_t tommRoCAssertCbClose(void);

/**
 * Return on-error callback function pointer.
 * NOTE: DO NOT USE IN USER CODE; it's for internal use.
 */
tommRoC_assert_on_error_callback_funct_t tommRoCAssertCbGet(void);

/**
 * If init, assert on-error callback function is called.
 * NOTE: DO NOT USE IN USER CODE; it's for internal use.
 */
tommRoC_err_enum_t tommRoCAssertCb(void);

/**
 * @}
 */

#endif
