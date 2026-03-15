
#ifndef TOMMROC_CTA_H_
#define TOMMROC_CTA_H_

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
 * @defgroup tommRoCCTA tommRoCCTA
 *
 * @brief  TommRoC library compile time assert module
 * @author TommRo Software Department
 *
 * This module is providing compile time assert functionality.
 *
 * A compile time assert is an assertion checked at compile time - not at runtime.
 * Assertions checked at compile time do not consume any code and do not affect performance.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCEnv.h"
#include "tommRoCUtil.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/**
 * @brief This can be used to create an error message at compile time with the size of a type.
 */
#define TOMMROC_CTA_ERROR_FOR_PRINT_SIZE_OF(t)              char __kaboom[sizeof(t) + 1] = {[sizeof(t)] = ""}

/**
 * Basic CTA/SCTA defines.
 * NOTE: DO NOT USE IN USER CODE; it's only for library internal use (avoid token pasting madness).
 */
#define __TOMMROC_SCTA_ASSERT_LEVEL_0__(cond, msg)          typedef char msg[1 - 2*!!!(cond)]
#define __TOMMROC_SCTA_ASSERT_LEVEL_1__(cond, line)         __TOMMROC_SCTA_ASSERT_LEVEL_0__(cond, static_assert_at_line_ ## line)
#define __TOMMROC_SCTA_ASSERT_LEVEL_2__(cond, line)         __TOMMROC_SCTA_ASSERT_LEVEL_1__(cond, line)


/******************* Compile time assert */

/**
 * Macro for compile time assert.
 *
 * This macro needs to be placed into functions.
 * Example call : TOMMROC_CTA(sizeof(buffer) == sizeof(uint32_t));
 */
#define TOMMROC_CTA(condition)                              ((void)sizeof(char[1 - 2*!!!(condition)]))

#define TOMMROC_CTA_TEST(e1, test, e2)                      TOMMROC_CTA((e1) test (e2))

#define TOMMROC_CTA_EQUALS(e1, e2)                          TOMMROC_CTA_TEST(((long int) (e1)), ==, ((long int) (e2)))
#define TOMMROC_CTA_NOT_EQUALS(e1, e2)                      TOMMROC_CTA_TEST(((long int) (e1)), !=, ((long int) (e2)))
#define TOMMROC_CTA_LESS_THAN(e1, e2)                       TOMMROC_CTA_TEST(((long int) (e1)), < , ((long int) (e2)))
#define TOMMROC_CTA_LESS_OR_EQUALS_THAN(e1, e2)             TOMMROC_CTA_TEST(((long int) (e1)), <=, ((long int) (e2)))
#define TOMMROC_CTA_MORE_THAN(e1, e2)                       TOMMROC_CTA_TEST(((long int) (e1)), > , ((long int) (e2)))
#define TOMMROC_CTA_MORE_OR_EQUALS_THAN(e1, e2)             TOMMROC_CTA_TEST(((long int) (e1)), >=, ((long int) (e2)))

#define TOMMROC_CTA_TRUE(e)                                 TOMMROC_CTA(e)
#define TOMMROC_CTA_FALSE(e)                                TOMMROC_CTA((!!!(e)))

#define TOMMROC_CTA_NULL(e)                                 TOMMROC_CTA_TEST(NULL, ==, e)
#define TOMMROC_CTA_NOT_NULL(e)                             TOMMROC_CTA_TEST(NULL, !=, e)
#define TOMMROC_CTA_ZERO(e)                                 TOMMROC_CTA_EQUALS(e, 0)
#define TOMMROC_CTA_NOT_ZERO(e)                             TOMMROC_CTA_NOT_EQUALS(e, 0)

/**
 * Check the size of two structures/types/variables.
 */
#define TOMMROC_CTA_SIZE_OF_EQUALS(t1, t2)                  TOMMROC_CTA_EQUALS(sizeof(t1), sizeof(t2))
#define TOMMROC_CTA_SIZE_OF_NOT_EQUALS(t1, t2)              TOMMROC_CTA_NOT_EQUALS(sizeof(t1), sizeof(t2))
#define TOMMROC_CTA_SIZE_OF_LESS_THAN(t1, t2)               TOMMROC_CTA_LESS_THAN(sizeof(t1), sizeof(t2))
#define TOMMROC_CTA_SIZE_OF_LESS_OR_EQUALS_THAN(t1, t2)     TOMMROC_CTA_LESS_OR_EQUALS_THAN(sizeof(t1), sizeof(t2))
#define TOMMROC_CTA_SIZE_OF_MORE_THAN(t1, t2)               TOMMROC_CTA_MORE_THAN(sizeof(t1), sizeof(t2))
#define TOMMROC_CTA_SIZE_OF_MORE_OR_EQUALS_THAN(t1, t2)     TOMMROC_CTA_MORE_OR_EQUALS_THAN(sizeof(t1), sizeof(t2))

#define TOMMROC_CTA_SIZE_OF_ZERO(t)                         TOMMROC_CTA_EQUALS(sizeof(t), 0)
#define TOMMROC_CTA_SIZE_OF_NOT_ZERO(t)                     TOMMROC_CTA_NOT_EQUALS(sizeof(t), 0)

/**
 * Check the element amount of an array.
 */
#define TOMMROC_CTA_EAMOUNT_EQUALS(t1, t2)                  TOMMROC_CTA_EQUALS(TOMMROC_UTIL_ARR_EAMOUNT(t1), TOMMROC_UTIL_ARR_EAMOUNT(t2))
#define TOMMROC_CTA_EAMOUNT_NOT_EQUALS(t1, t2)              TOMMROC_CTA_NOT_EQUALS(TOMMROC_UTIL_ARR_EAMOUNT(t1), TOMMROC_UTIL_ARR_EAMOUNT(t2))
#define TOMMROC_CTA_EAMOUNT_LESS_THAN(t1, t2)               TOMMROC_CTA_LESS_THAN(TOMMROC_UTIL_ARR_EAMOUNT(t1), TOMMROC_UTIL_ARR_EAMOUNT(t2))
#define TOMMROC_CTA_EAMOUNT_LESS_OR_EQUALS_THAN(t1, t2)     TOMMROC_CTA_LESS_OR_EQUALS_THAN(TOMMROC_UTIL_ARR_EAMOUNT(t1), TOMMROC_UTIL_ARR_EAMOUNT(t2))
#define TOMMROC_CTA_EAMOUNT_MORE_THAN(t1, t2)               TOMMROC_CTA_MORE_THAN(TOMMROC_UTIL_ARR_EAMOUNT(t1), TOMMROC_UTIL_ARR_EAMOUNT(t2))
#define TOMMROC_CTA_EAMOUNT_MORE_OR_EQUALS_THAN(t1, t2)     TOMMROC_CTA_MORE_OR_EQUALS_THAN(TOMMROC_UTIL_ARR_EAMOUNT(t1), TOMMROC_UTIL_ARR_EAMOUNT(t2))

#define TOMMROC_CTA_EAMOUNT_ZERO(t)                         TOMMROC_CTA_EQUALS(TOMMROC_UTIL_ARR_EAMOUNT(t), 0)
#define TOMMROC_CTA_EAMOUNT_NOT_ZERO(t)                     TOMMROC_CTA_NOT_EQUALS(TOMMROC_UTIL_ARR_EAMOUNT(t), 0)

#define TOMMROC_CTA_SIZE_OF_SMEMBER_EQUALS(t1, memberT1, t2, memberT2)      \
        TOMMROC_CTA_SIZE_OF_EQUALS(((t1*)NULL)->memberT1, ((t2*)NULL)->memberT2)

// NOTE: XC8 compiler does not support
#if !defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)
#define TOMMROC_CTA_OFFSET_OF_SMEMBER_EQUALS(t1, memberT1, t2, memberT2)    \
        TOMMROC_CTA_EQUALS(&((t1*)NULL)->memberT1, &((t2*)NULL)->memberT2)
#else
#define TOMMROC_CTA_OFFSET_OF_SMEMBER_EQUALS(t1, memberT1, t2, memberT2)
#endif

/**
 * Check if the members of two structure types are equal in size and offset.
 */
#define TOMMROC_CTA_SMEMBER_EQUALS(t1, memberT1, t2, memberT2)              \
        TOMMROC_CTA_SIZE_OF_SMEMBER_EQUALS(t1, memberT1, t2, memberT2);     \
        TOMMROC_CTA_OFFSET_OF_SMEMBER_EQUALS(t1, memberT1, t2, memberT2)


/******************* Static compile time assert */

/**
 * Macro for static compile time assert.
 *
 * This macro needs to be placed outside of functions.
 * Example call : TOMMROC_SCTA_TRUE(sizeof(buffer) == sizeof(uint32_t));
 */
#define TOMMROC_SCTA(condition)                             __TOMMROC_SCTA_ASSERT_LEVEL_2__(condition, TOMMRO_C_UTIL_LINE)

#define TOMMROC_SCTA_TEST(e1, test, e2)                     TOMMROC_SCTA((e1) test (e2))

#define TOMMROC_SCTA_EQUALS(e1, e2)                         TOMMROC_SCTA_TEST(((long int) (e1)), ==, ((long int) (e2)))
#define TOMMROC_SCTA_NOT_EQUALS(e1, e2)                     TOMMROC_SCTA_TEST(((long int) (e1)), !=, ((long int) (e2)))
#define TOMMROC_SCTA_LESS_THAN(e1, e2)                      TOMMROC_SCTA_TEST(((long int) (e1)), < , ((long int) (e2)))
#define TOMMROC_SCTA_LESS_OR_EQUALS_THAN(e1, e2)            TOMMROC_SCTA_TEST(((long int) (e1)), <=, ((long int) (e2)))
#define TOMMROC_SCTA_MORE_THAN(e1, e2)                      TOMMROC_SCTA_TEST(((long int) (e1)), > , ((long int) (e2)))
#define TOMMROC_SCTA_MORE_OR_EQUALS_THAN(e1, e2)            TOMMROC_SCTA_TEST(((long int) (e1)), >=, ((long int) (e2)))

#define TOMMROC_SCTA_TRUE(e)                                TOMMROC_SCTA(e)
#define TOMMROC_SCTA_FALSE(e)                               TOMMROC_SCTA((!!!(e)))

#define TOMMROC_SCTA_NULL(e)                                TOMMROC_SCTA_TEST(NULL, ==, e)
#define TOMMROC_SCTA_NOT_NULL(e)                            TOMMROC_SCTA_TEST(NULL, !=, e)
#define TOMMROC_SCTA_ZERO(e)                                TOMMROC_SCTA_EQUALS(e, 0)
#define TOMMROC_SCTA_NOT_ZERO(e)                            TOMMROC_SCTA_NOT_EQUALS(e, 0)

/**
 * Check the size of two structures/types/variables.
 */
#define TOMMROC_SCTA_SIZE_OF_EQUALS(t1, t2)                 TOMMROC_SCTA_EQUALS(sizeof(t1), sizeof(t2))
#define TOMMROC_SCTA_SIZE_OF_NOT_EQUALS(t1, t2)             TOMMROC_SCTA_NOT_EQUALS(sizeof(t1), sizeof(t2))
#define TOMMROC_SCTA_SIZE_OF_LESS_THAN(t1, t2)              TOMMROC_SCTA_LESS_THAN(sizeof(t1), sizeof(t2))
#define TOMMROC_SCTA_SIZE_OF_LESS_OR_EQUALS_THAN(t1, t2)    TOMMROC_SCTA_LESS_OR_EQUALS_THAN(sizeof(t1), sizeof(t2))
#define TOMMROC_SCTA_SIZE_OF_MORE_THAN(t1, t2)              TOMMROC_SCTA_MORE_THAN(sizeof(t1), sizeof(t2))
#define TOMMROC_SCTA_SIZE_OF_MORE_OR_EQUALS_THAN(t1, t2)    TOMMROC_SCTA_MORE_OR_EQUALS_THAN(sizeof(t1), sizeof(t2))

#define TOMMROC_SCTA_SIZE_OF_ZERO(t)                        TOMMROC_SCTA_EQUALS(sizeof(t), 0)
#define TOMMROC_SCTA_SIZE_OF_NOT_ZERO(t)                    TOMMROC_SCTA_NOT_EQUALS(sizeof(t), 0)

/**
 * Check the element amount of an array.
 */
#define TOMMROC_SCTA_EAMOUNT_EQUALS(t1, t2)                 TOMMROC_SCTA_EQUALS(TOMMROC_UTIL_ARR_EAMOUNT(t1), TOMMROC_UTIL_ARR_EAMOUNT(t2))
#define TOMMROC_SCTA_EAMOUNT_NOT_EQUALS(t1, t2)             TOMMROC_SCTA_NOT_EQUALS(TOMMROC_UTIL_ARR_EAMOUNT(t1), TOMMROC_UTIL_ARR_EAMOUNT(t2))
#define TOMMROC_SCTA_EAMOUNT_LESS_THAN(t1, t2)              TOMMROC_SCTA_LESS_THAN(TOMMROC_UTIL_ARR_EAMOUNT(t1), TOMMROC_UTIL_ARR_EAMOUNT(t2))
#define TOMMROC_SCTA_EAMOUNT_LESS_OR_EQUALS_THAN(t1, t2)    TOMMROC_SCTA_LESS_OR_EQUALS_THAN(TOMMROC_UTIL_ARR_EAMOUNT(t1), TOMMROC_UTIL_ARR_EAMOUNT(t2))
#define TOMMROC_SCTA_EAMOUNT_MORE_THAN(t1, t2)              TOMMROC_SCTA_MORE_THAN(TOMMROC_UTIL_ARR_EAMOUNT(t1), TOMMROC_UTIL_ARR_EAMOUNT(t2))
#define TOMMROC_SCTA_EAMOUNT_MORE_OR_EQUALS_THAN(t1, t2)    TOMMROC_SCTA_MORE_OR_EQUALS_THAN(TOMMROC_UTIL_ARR_EAMOUNT(t1), TOMMROC_UTIL_ARR_EAMOUNT(t2))

#define TOMMROC_SCTA_EAMOUNT_ZERO(t)                        TOMMROC_SCTA_EQUALS(TOMMROC_UTIL_ARR_EAMOUNT(t), 0)
#define TOMMROC_SCTA_EAMOUNT_NOT_ZERO(t)                    TOMMROC_SCTA_NOT_EQUALS(TOMMROC_UTIL_ARR_EAMOUNT(t), 0)

#define TOMMROC_SCTA_SIZE_OF_SMEMBER_EQUALS(t1, memberT1, t2, memberT2)     \
        TOMMROC_SCTA_SIZE_OF_EQUALS(((t1*)NULL)->memberT1, ((t2*)NULL)->memberT2)

// NOTE: XC8 compiler does not support
#if !defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)
#define TOMMROC_SCTA_OFFSET_OF_SMEMBER_EQUALS(t1, memberT1, t2, memberT2)   \
        TOMMROC_SCTA_EQUALS(&((t1*)NULL)->memberT1, &((t2*)NULL)->memberT2)
#else
#define TOMMROC_SCTA_OFFSET_OF_SMEMBER_EQUALS(t1, memberT1, t2, memberT2)
#endif

/**
 * Check if the members of two structure types are equal in size and offset.
 */
#define TOMMROC_SCTA_SMEMBER_EQUALS(t1, memberT1, t2, memberT2)             \
        TOMMROC_SCTA_SIZE_OF_SMEMBER_EQUALS(t1, memberT1, t2, memberT2);    \
        TOMMROC_SCTA_OFFSET_OF_SMEMBER_EQUALS(t1, memberT1, t2, memberT2)


/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * @}
 */

#endif
