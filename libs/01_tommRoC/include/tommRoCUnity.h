
#ifndef TOMMROC_UNITY_H_
#define TOMMROC_UNITY_H_

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
 * @defgroup tommRoCUnity tommRoCUnity
 *
 * @brief  TommRoC library unit test module
 * @author TommRo Software Department
 *
 * This module is providing source code unity testing functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCDateTime.h"
#include "tommRoCEnv.h"
#include "tommRoCInt.h"
#include "tommRoCVersion.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// Define if unity printf environment is enabled.
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)     ||  \
    defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)  ||  \
    defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)     ||  \
    defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)

#define TOMMRO_C_UNITY_PRINT_IS_ENABLED
#endif


/**
 * Basic success.
 * NOTE: DO NOT USE IN USER CODE; it's only for library internal use.
 */
#define UNITY_TEST_SUCCESS()                    do { tommRoCUnitySuccess(); } while (0)


/**
 * Basic Fail.
 * NOTE: DO NOT USE IN USER CODE; it's only for library internal use.
 */
#if defined (TOMMRO_C_UNITY_PRINT_IS_ENABLED)
#define UNITY_TEST_FAIL(message)                do { tommRoCUnityFail((TOMMRO_C_UTIL_FUNCT_NAME), (TOMMRO_C_UTIL_LINE), (message)); } while (0)
#else
#define UNITY_TEST_FAIL(message)                do { tommRoCUnityFail((NULL), (TOMMRO_C_UTIL_LINE), (NULL)); } while (0)
#endif


/**
 * Test Asserts.
 * NOTE: DO NOT USE IN USER CODE; it's only for library internal use.
 */
#define UNITY_TEST_ASSERT(condition, message)       \
        do {                                        \
            if (condition) {                        \
                UNITY_TEST_SUCCESS();               \
            }                                       \
            else {                                  \
                UNITY_TEST_FAIL((message));         \
            }                                       \
        } while (0)


/**
 * Test Asserts.
 * NOTE: USE THESE IN USER CODE.
 */

// Boolean
#define TEST_ASSERT(condition)                                                                                      UNITY_TEST_ASSERT(        (condition), "Expression Evaluated To FALSE")
#define TEST_ASSERT_TRUE(condition)                                                                                 UNITY_TEST_ASSERT(        (condition), "Expected TRUE Was FALSE")
#define TEST_ASSERT_UNLESS(condition)                                                                               UNITY_TEST_ASSERT(       !(condition), "Expression Evaluated To TRUE")
#define TEST_ASSERT_FALSE(condition)                                                                                UNITY_TEST_ASSERT(       !(condition), "Expected FALSE Was TRUE")
#define TEST_ASSERT_NULL(pointer)                                                                                   UNITY_TEST_ASSERT((NULL == (pointer)), "Expected NULL")
#define TEST_ASSERT_NOT_NULL(pointer)                                                                               UNITY_TEST_ASSERT((NULL != (pointer)), "Expected Non-NULL")

// Integers equal (of all sizes)
#define TEST_ASSERT_EQUAL(expected, actual)                                                                         UNITY_TEST_ASSERT(((expected) == (actual)), "Expected Equal")
#define TEST_ASSERT_EQUAL_CHAR(expected, actual)                                                                    TEST_ASSERT_EQUAL((char)     (expected), (char)     (actual))
#define TEST_ASSERT_EQUAL_INT8(expected, actual)                                                                    TEST_ASSERT_EQUAL((int8_t)   (expected), (int8_t)   (actual))
#define TEST_ASSERT_EQUAL_INT16(expected, actual)                                                                   TEST_ASSERT_EQUAL((int16_t)  (expected), (int16_t)  (actual))
#define TEST_ASSERT_EQUAL_INT32(expected, actual)                                                                   TEST_ASSERT_EQUAL((int32_t)  (expected), (int32_t)  (actual))
#if defined (TOMMROC_INT_INT64_SUPPORTED)
#define TEST_ASSERT_EQUAL_INT64(expected, actual)                                                                   TEST_ASSERT_EQUAL((int64_t)  (expected), (int64_t)  (actual))
#endif
#define TEST_ASSERT_EQUAL_UINT8(expected, actual)                                                                   TEST_ASSERT_EQUAL((uint8_t)  (expected), (uint8_t)  (actual))
#define TEST_ASSERT_EQUAL_UINT16(expected, actual)                                                                  TEST_ASSERT_EQUAL((uint16_t) (expected), (uint16_t) (actual))
#define TEST_ASSERT_EQUAL_UINT32(expected, actual)                                                                  TEST_ASSERT_EQUAL((uint32_t) (expected), (uint32_t) (actual))
#if defined (TOMMROC_INT_UINT64_SUPPORTED)
#define TEST_ASSERT_EQUAL_UINT64(expected, actual)                                                                  TEST_ASSERT_EQUAL((uint64_t) (expected), (uint64_t) (actual))
#endif

// Integers not equal (of all sizes)
#define TEST_ASSERT_NOT_EQUAL(expected, actual)                                                                     UNITY_TEST_ASSERT(((expected) != (actual)), "Expected Not-Equal")
#define TEST_ASSERT_NOT_EQUAL_CHAR(expected, actual)                                                                TEST_ASSERT_NOT_EQUAL((char)     (expected), (char)     (actual))
#define TEST_ASSERT_NOT_EQUAL_INT8(expected, actual)                                                                TEST_ASSERT_NOT_EQUAL((int8_t)   (expected), (int8_t)   (actual))
#define TEST_ASSERT_NOT_EQUAL_INT16(expected, actual)                                                               TEST_ASSERT_NOT_EQUAL((int16_t)  (expected), (int16_t)  (actual))
#define TEST_ASSERT_NOT_EQUAL_INT32(expected, actual)                                                               TEST_ASSERT_NOT_EQUAL((int32_t)  (expected), (int32_t)  (actual))
#if defined (TOMMROC_INT_INT64_SUPPORTED)
#define TEST_ASSERT_NOT_EQUAL_INT64(expected, actual)                                                               TEST_ASSERT_NOT_EQUAL((int64_t)  (expected), (int64_t)  (actual))
#endif
#define TEST_ASSERT_NOT_EQUAL_UINT8(expected, actual)                                                               TEST_ASSERT_NOT_EQUAL((uint8_t)  (expected), (uint8_t)  (actual))
#define TEST_ASSERT_NOT_EQUAL_UINT16(expected, actual)                                                              TEST_ASSERT_NOT_EQUAL((uint16_t) (expected), (uint16_t) (actual))
#define TEST_ASSERT_NOT_EQUAL_UINT32(expected, actual)                                                              TEST_ASSERT_NOT_EQUAL((uint32_t) (expected), (uint32_t) (actual))
#if defined (TOMMROC_INT_UINT64_SUPPORTED)
#define TEST_ASSERT_NOT_EQUAL_UINT64(expected, actual)                                                              TEST_ASSERT_NOT_EQUAL((uint64_t) (expected), (uint64_t) (actual))
#endif

// Integer Greater/Less Than (of all sizes)
#define TEST_ASSERT_GREATER_THAN(threshold, actual)                                                                 UNITY_TEST_ASSERT(((actual) > (threshold)), "Expected Greater than")
#define TEST_ASSERT_GREATER_THAN_CHAR(threshold, actual)                                                            TEST_ASSERT_GREATER_THAN((char)     (threshold), (char)     (actual))
#define TEST_ASSERT_GREATER_THAN_INT8(threshold, actual)                                                            TEST_ASSERT_GREATER_THAN((int8_t)   (threshold), (int8_t)   (actual))
#define TEST_ASSERT_GREATER_THAN_INT16(threshold, actual)                                                           TEST_ASSERT_GREATER_THAN((int16_t)  (threshold), (int16_t)  (actual))
#define TEST_ASSERT_GREATER_THAN_INT32(threshold, actual)                                                           TEST_ASSERT_GREATER_THAN((int32_t)  (threshold), (int32_t)  (actual))
#if defined (TOMMROC_INT_INT64_SUPPORTED)
#define TEST_ASSERT_GREATER_THAN_INT64(threshold, actual)                                                           TEST_ASSERT_GREATER_THAN((int64_t)  (threshold), (int64_t)  (actual))
#endif
#define TEST_ASSERT_GREATER_THAN_UINT8(threshold, actual)                                                           TEST_ASSERT_GREATER_THAN((uint8_t)  (threshold), (uint8_t)  (actual))
#define TEST_ASSERT_GREATER_THAN_UINT16(threshold, actual)                                                          TEST_ASSERT_GREATER_THAN((uint16_t) (threshold), (uint16_t) (actual))
#define TEST_ASSERT_GREATER_THAN_UINT32(threshold, actual)                                                          TEST_ASSERT_GREATER_THAN((uint32_t) (threshold), (uint32_t) (actual))
#if defined (TOMMROC_INT_UINT64_SUPPORTED)
#define TEST_ASSERT_GREATER_THAN_UINT64(threshold, actual)                                                          TEST_ASSERT_GREATER_THAN((uint64_t) (threshold), (uint64_t) (actual))
#endif

#define TEST_ASSERT_LESS_THAN(threshold, actual)                                                                    UNITY_TEST_ASSERT(((actual) < (threshold)), "Expected Less than")
#define TEST_ASSERT_LESS_THAN_CHAR(threshold, actual)                                                               TEST_ASSERT_LESS_THAN((char)     (threshold), (char)     (actual))
#define TEST_ASSERT_LESS_THAN_INT8(threshold, actual)                                                               TEST_ASSERT_LESS_THAN((int8_t)   (threshold), (int8_t)   (actual))
#define TEST_ASSERT_LESS_THAN_INT16(threshold, actual)                                                              TEST_ASSERT_LESS_THAN((int16_t)  (threshold), (int16_t)  (actual))
#define TEST_ASSERT_LESS_THAN_INT32(threshold, actual)                                                              TEST_ASSERT_LESS_THAN((int32_t)  (threshold), (int32_t)  (actual))
#if defined (TOMMROC_INT_INT64_SUPPORTED)
#define TEST_ASSERT_LESS_THAN_INT64(threshold, actual)                                                              TEST_ASSERT_LESS_THAN((int64_t)  (threshold), (int64_t)  (actual))
#endif
#define TEST_ASSERT_LESS_THAN_UINT8(threshold, actual)                                                              TEST_ASSERT_LESS_THAN((uint8_t)  (threshold), (uint8_t)  (actual))
#define TEST_ASSERT_LESS_THAN_UINT16(threshold, actual)                                                             TEST_ASSERT_LESS_THAN((uint16_t) (threshold), (uint16_t) (actual))
#define TEST_ASSERT_LESS_THAN_UINT32(threshold, actual)                                                             TEST_ASSERT_LESS_THAN((uint32_t) (threshold), (uint32_t) (actual))
#if defined (TOMMROC_INT_UINT64_SUPPORTED)
#define TEST_ASSERT_LESS_THAN_UINT64(threshold, actual)                                                             TEST_ASSERT_LESS_THAN((uint64_t) (threshold), (uint64_t) (actual))
#endif

// Integer Greater/Less or Equal Than (of all sizes)
#define TEST_ASSERT_GREATER_OR_EQUAL_THAN(threshold, actual)                                                        UNITY_TEST_ASSERT(((actual) >= (threshold)), "Expected Greater or Equal than")
#define TEST_ASSERT_GREATER_OR_EQUAL_THAN_CHAR(threshold, actual)                                                   TEST_ASSERT_GREATER_OR_EQUAL_THAN((char)     (threshold), (char)     (actual))
#define TEST_ASSERT_GREATER_OR_EQUAL_THAN_INT8(threshold, actual)                                                   TEST_ASSERT_GREATER_OR_EQUAL_THAN((int8_t)   (threshold), (int8_t)   (actual))
#define TEST_ASSERT_GREATER_OR_EQUAL_THAN_INT16(threshold, actual)                                                  TEST_ASSERT_GREATER_OR_EQUAL_THAN((int16_t)  (threshold), (int16_t)  (actual))
#define TEST_ASSERT_GREATER_OR_EQUAL_THAN_INT32(threshold, actual)                                                  TEST_ASSERT_GREATER_OR_EQUAL_THAN((int32_t)  (threshold), (int32_t)  (actual))
#if defined (TOMMROC_INT_INT64_SUPPORTED)
#define TEST_ASSERT_GREATER_OR_EQUAL_THAN_INT64(threshold, actual)                                                  TEST_ASSERT_GREATER_OR_EQUAL_THAN((int64_t)  (threshold), (int64_t)  (actual))
#endif
#define TEST_ASSERT_GREATER_OR_EQUAL_THAN_UINT8(threshold, actual)                                                  TEST_ASSERT_GREATER_OR_EQUAL_THAN((uint8_t)  (threshold), (uint8_t)  (actual))
#define TEST_ASSERT_GREATER_OR_EQUAL_THAN_UINT16(threshold, actual)                                                 TEST_ASSERT_GREATER_OR_EQUAL_THAN((uint16_t) (threshold), (uint16_t) (actual))
#define TEST_ASSERT_GREATER_OR_EQUAL_THAN_UINT32(threshold, actual)                                                 TEST_ASSERT_GREATER_OR_EQUAL_THAN((uint32_t) (threshold), (uint32_t) (actual))
#if defined (TOMMROC_INT_UINT64_SUPPORTED)
#define TEST_ASSERT_GREATER_OR_EQUAL_THAN_UINT64(threshold, actual)                                                 TEST_ASSERT_GREATER_OR_EQUAL_THAN((uint64_t) (threshold), (uint64_t) (actual))
#endif

#define TEST_ASSERT_LESS_OR_EQUAL_THAN(threshold, actual)                                                           UNITY_TEST_ASSERT(((actual) <= (threshold)), "Expected Less or Equal than")
#define TEST_ASSERT_LESS_OR_EQUAL_THAN_CHAR(threshold, actual)                                                      TEST_ASSERT_LESS_OR_EQUAL_THAN((char)     (threshold), (char)     (actual))
#define TEST_ASSERT_LESS_OR_EQUAL_THAN_INT8(threshold, actual)                                                      TEST_ASSERT_LESS_OR_EQUAL_THAN((int8_t)   (threshold), (int8_t)   (actual))
#define TEST_ASSERT_LESS_OR_EQUAL_THAN_INT16(threshold, actual)                                                     TEST_ASSERT_LESS_OR_EQUAL_THAN((int16_t)  (threshold), (int16_t)  (actual))
#define TEST_ASSERT_LESS_OR_EQUAL_THAN_INT32(threshold, actual)                                                     TEST_ASSERT_LESS_OR_EQUAL_THAN((int32_t)  (threshold), (int32_t)  (actual))
#if defined (TOMMROC_INT_INT64_SUPPORTED)
#define TEST_ASSERT_LESS_OR_EQUAL_THAN_INT64(threshold, actual)                                                     TEST_ASSERT_LESS_OR_EQUAL_THAN((int64_t)  (threshold), (int64_t)  (actual))
#endif
#define TEST_ASSERT_LESS_OR_EQUAL_THAN_UINT8(threshold, actual)                                                     TEST_ASSERT_LESS_OR_EQUAL_THAN((uint8_t)  (threshold), (uint8_t)  (actual))
#define TEST_ASSERT_LESS_OR_EQUAL_THAN_UINT16(threshold, actual)                                                    TEST_ASSERT_LESS_OR_EQUAL_THAN((uint16_t) (threshold), (uint16_t) (actual))
#define TEST_ASSERT_LESS_OR_EQUAL_THAN_UINT32(threshold, actual)                                                    TEST_ASSERT_LESS_OR_EQUAL_THAN((uint32_t) (threshold), (uint32_t) (actual))
#if defined (TOMMROC_INT_UINT64_SUPPORTED)
#define TEST_ASSERT_LESS_OR_EQUAL_THAN_UINT64(threshold, actual)                                                    TEST_ASSERT_LESS_OR_EQUAL_THAN((uint64_t) (threshold), (uint64_t) (actual))
#endif

// Integer positive/negative (of all sizes)
#define TEST_ASSERT_POSITIVE(actual)                                                                                TEST_ASSERT_GREATER_THAN(0, actual)
#define TEST_ASSERT_POSITIVE_INT8(actual)                                                                           TEST_ASSERT_GREATER_THAN_INT8(0, actual)
#define TEST_ASSERT_POSITIVE_INT16(actual)                                                                          TEST_ASSERT_GREATER_THAN_INT16(0, actual)
#define TEST_ASSERT_POSITIVE_INT32(actual)                                                                          TEST_ASSERT_GREATER_THAN_INT32(0, actual)
#if defined (TOMMROC_INT_INT64_SUPPORTED)
#define TEST_ASSERT_POSITIVE_INT64(actual)                                                                          TEST_ASSERT_GREATER_THAN_INT64(0, actual)
#endif
#define TEST_ASSERT_POSITIVE_UINT8(actual)                                                                          TEST_ASSERT_GREATER_THAN_UINT8(0, actual)
#define TEST_ASSERT_POSITIVE_UINT16(actual)                                                                         TEST_ASSERT_GREATER_THAN_UINT16(0, actual)
#define TEST_ASSERT_POSITIVE_UINT32(actual)                                                                         TEST_ASSERT_GREATER_THAN_UINT32(0, actual)
#if defined (TOMMROC_INT_UINT64_SUPPORTED)
#define TEST_ASSERT_POSITIVE_UINT64(actual)                                                                         TEST_ASSERT_GREATER_THAN_UINT64(0, actual)
#endif

#define TEST_ASSERT_NEGATIVE(actual)                                                                                TEST_ASSERT_LESS_THAN(0, actual)
#define TEST_ASSERT_NEGATIVE_INT8(actual)                                                                           TEST_ASSERT_LESS_THAN_INT8(0, actual)
#define TEST_ASSERT_NEGATIVE_INT16(actual)                                                                          TEST_ASSERT_LESS_THAN_INT16(0, actual)
#define TEST_ASSERT_NEGATIVE_INT32(actual)                                                                          TEST_ASSERT_LESS_THAN_INT32(0, actual)
#if defined (TOMMROC_INT_INT64_SUPPORTED)
#define TEST_ASSERT_NEGATIVE_INT64(actual)                                                                          TEST_ASSERT_LESS_THAN_INT64(0, actual)
#endif
#define TEST_ASSERT_NEGATIVE_UINT8(actual)                                                                          TEST_ASSERT_LESS_THAN_UINT8(0, actual)
#define TEST_ASSERT_NEGATIVE_UINT16(actual)                                                                         TEST_ASSERT_LESS_THAN_UINT16(0, actual)
#define TEST_ASSERT_NEGATIVE_UINT32(actual)                                                                         TEST_ASSERT_LESS_THAN_UINT32(0, actual)
#if defined (TOMMROC_INT_UINT64_SUPPORTED)
#define TEST_ASSERT_NEGATIVE_UINT64(actual)                                                                         TEST_ASSERT_LESS_THAN_UINT64(0, actual)
#endif

#define TEST_ASSERT_ZERO_OR_POSITIVE(actual)                                                                        TEST_ASSERT_GREATER_OR_EQUAL_THAN(0, actual)
#define TEST_ASSERT_ZERO_OR_POSITIVE_INT8(actual)                                                                   TEST_ASSERT_GREATER_OR_EQUAL_THAN_INT8(0, actual)
#define TEST_ASSERT_ZERO_OR_POSITIVE_INT16(actual)                                                                  TEST_ASSERT_GREATER_OR_EQUAL_THAN_INT16(0, actual)
#define TEST_ASSERT_ZERO_OR_POSITIVE_INT32(actual)                                                                  TEST_ASSERT_GREATER_OR_EQUAL_THAN_INT32(0, actual)
#if defined (TOMMROC_INT_INT64_SUPPORTED)
#define TEST_ASSERT_ZERO_OR_POSITIVE_INT64(actual)                                                                  TEST_ASSERT_GREATER_OR_EQUAL_THAN_INT64(0, actual)
#endif
#define TEST_ASSERT_ZERO_OR_POSITIVE_UINT8(actual)                                                                  TEST_ASSERT_GREATER_OR_EQUAL_THAN_UINT8(0, actual)
#define TEST_ASSERT_ZERO_OR_POSITIVE_UINT16(actual)                                                                 TEST_ASSERT_GREATER_OR_EQUAL_THAN_UINT16(0, actual)
#define TEST_ASSERT_ZERO_OR_POSITIVE_UINT32(actual)                                                                 TEST_ASSERT_GREATER_OR_EQUAL_THAN_UINT32(0, actual)
#if defined (TOMMROC_INT_UINT64_SUPPORTED)
#define TEST_ASSERT_ZERO_OR_POSITIVE_UINT64(actual)                                                                 TEST_ASSERT_GREATER_OR_EQUAL_THAN_UINT64(0, actual)
#endif

#define TEST_ASSERT_ZERO_OR_NEGATIVE(actual)                                                                        TEST_ASSERT_LESS_OR_EQUAL_THAN(0, actual)
#define TEST_ASSERT_ZERO_OR_NEGATIVE_INT8(actual)                                                                   TEST_ASSERT_LESS_OR_EQUAL_THAN_INT8(0, actual)
#define TEST_ASSERT_ZERO_OR_NEGATIVE_INT16(actual)                                                                  TEST_ASSERT_LESS_OR_EQUAL_THAN_INT16(0, actual)
#define TEST_ASSERT_ZERO_OR_NEGATIVE_INT32(actual)                                                                  TEST_ASSERT_LESS_OR_EQUAL_THAN_INT32(0, actual)
#if defined (TOMMROC_INT_INT64_SUPPORTED)
#define TEST_ASSERT_ZERO_OR_NEGATIVE_INT64(actual)                                                                  TEST_ASSERT_LESS_OR_EQUAL_THAN_INT64(0, actual)
#endif
#define TEST_ASSERT_ZERO_OR_NEGATIVE_UINT8(actual)                                                                  TEST_ASSERT_LESS_OR_EQUAL_THAN_UINT8(0, actual)
#define TEST_ASSERT_ZERO_OR_NEGATIVE_UINT16(actual)                                                                 TEST_ASSERT_LESS_OR_EQUAL_THAN_UINT16(0, actual)
#define TEST_ASSERT_ZERO_OR_NEGATIVE_UINT32(actual)                                                                 TEST_ASSERT_LESS_OR_EQUAL_THAN_UINT32(0, actual)
#if defined (TOMMROC_INT_UINT64_SUPPORTED)
#define TEST_ASSERT_ZERO_OR_NEGATIVE_UINT64(actual)                                                                 TEST_ASSERT_LESS_OR_EQUAL_THAN_UINT64(0, actual)
#endif

#define TEST_ASSERT_ZERO(actual)                                                                                    TEST_ASSERT_EQUAL(0, actual)
#define TEST_ASSERT_ZERO_INT8(actual)                                                                               TEST_ASSERT_EQUAL_INT8(0, actual)
#define TEST_ASSERT_ZERO_INT16(actual)                                                                              TEST_ASSERT_EQUAL_INT16(0, actual)
#define TEST_ASSERT_ZERO_INT32(actual)                                                                              TEST_ASSERT_EQUAL_INT32(0, actual)
#if defined (TOMMROC_INT_INT64_SUPPORTED)
#define TEST_ASSERT_ZERO_INT64(actual)                                                                              TEST_ASSERT_EQUAL_INT64(0, actual)
#endif
#define TEST_ASSERT_ZERO_UINT8(actual)                                                                              TEST_ASSERT_EQUAL_UINT8(0, actual)
#define TEST_ASSERT_ZERO_UINT16(actual)                                                                             TEST_ASSERT_EQUAL_UINT16(0, actual)
#define TEST_ASSERT_ZERO_UINT32(actual)                                                                             TEST_ASSERT_EQUAL_UINT32(0, actual)
#if defined (TOMMROC_INT_UINT64_SUPPORTED)
#define TEST_ASSERT_ZERO_UINT64(actual)                                                                             TEST_ASSERT_EQUAL_UINT64(0, actual)
#endif

#define TEST_ASSERT_NOT_ZERO(actual)                                                                                TEST_ASSERT_NOT_EQUAL(0, actual)
#define TEST_ASSERT_NOT_ZERO_INT8(actual)                                                                           TEST_ASSERT_NOT_EQUAL_INT8(0, actual)
#define TEST_ASSERT_NOT_ZERO_INT16(actual)                                                                          TEST_ASSERT_NOT_EQUAL_INT16(0, actual)
#define TEST_ASSERT_NOT_ZERO_INT32(actual)                                                                          TEST_ASSERT_NOT_EQUAL_INT32(0, actual)
#if defined (TOMMROC_INT_INT64_SUPPORTED)
#define TEST_ASSERT_NOT_ZERO_INT64(actual)                                                                          TEST_ASSERT_NOT_EQUAL_INT64(0, actual)
#endif
#define TEST_ASSERT_NOT_ZERO_UINT8(actual)                                                                          TEST_ASSERT_NOT_EQUAL_UINT8(0, actual)
#define TEST_ASSERT_NOT_ZERO_UINT16(actual)                                                                         TEST_ASSERT_NOT_EQUAL_UINT16(0, actual)
#define TEST_ASSERT_NOT_ZERO_UINT32(actual)                                                                         TEST_ASSERT_NOT_EQUAL_UINT32(0, actual)
#if defined (TOMMROC_INT_UINT64_SUPPORTED)
#define TEST_ASSERT_NOT_ZERO_UINT64(actual)                                                                         TEST_ASSERT_NOT_EQUAL_UINT64(0, actual)
#endif


// Structs and Strings
#define TEST_ASSERT_EQUAL_PTR(expected, actual)                                                                     TEST_ASSERT_EQUAL((void*) (expected), (void*) (actual))
#define TEST_ASSERT_EQUAL_STRING(expected, actual)                                                                  UNITY_TEST_ASSERT(tommRoCUnityEqualString((expected), (actual)), "Expected string Equal")
#define TEST_ASSERT_EQUAL_STRING_LEN(expected, actual, len)                                                         UNITY_TEST_ASSERT(tommRoCUnityEqualStringLen((expected), (actual), (len)), "Expected string length Equal")
#define TEST_ASSERT_EQUAL_MEMORY(expected, actual, len)                                                             UNITY_TEST_ASSERT(tommRoCUnityEqualMemory((expected), (actual), (len)), "Expected memory Equal")
#define TEST_ASSERT_EQUAL_MEMORY_GET_ERROR_1ST_IDX(expected, actual, len, error1stIdx)                              UNITY_TEST_ASSERT(tommRoCUnityEqualMemoryGetError1stIdx((expected), (actual), (len), (&error1stIdx)), "Expected memory Equal")
#define TEST_ASSERT_NOT_EQUAL_PTR(expected, actual)                                                                 TEST_ASSERT_NOT_EQUAL((void*) (expected), (void*) (actual))
#define TEST_ASSERT_NOT_EQUAL_STRING(expected, actual)                                                              UNITY_TEST_ASSERT(!tommRoCUnityEqualString((expected), (actual)), "Expected string Not-Equal")
#define TEST_ASSERT_NOT_EQUAL_STRING_LEN(expected, actual, len)                                                     UNITY_TEST_ASSERT(!tommRoCUnityEqualStringLen((expected), (actual), (len)), "Expected string length Not-Equal")
#define TEST_ASSERT_NOT_EQUAL_MEMORY(expected, actual, len)                                                         UNITY_TEST_ASSERT(!tommRoCUnityEqualMemory((expected), (actual), (len)), "Expected memory Not-Equal")
#define TEST_ASSERT_START_WITH_STRING(expected, actual)                                                             UNITY_TEST_ASSERT(tommRoCUnityStartWithString((expected), (actual)), "Expected string Equal")
#define TEST_ASSERT_END_WITH_STRING(expected, actual)                                                               UNITY_TEST_ASSERT(tommRoCUnityEndWithString((expected), (actual)), "Expected string Equal")


// Arrays Compared To Single Value
#define TEST_ASSERT_IN_ARRAY_EACH_EQUAL_CHAR(expectedValue, actual, num_elements)                                   UNITY_TEST_ASSERT(tommRoCUnityEachEqualU8((uint8_t) (expectedValue), (actual), (num_elements)), "Expected memory Equal")
#define TEST_ASSERT_IN_ARRAY_EACH_EQUAL_CHAR_GET_ERROR_1ST_IDX(expectedValue, actual, num_elements, error1stIdx)    UNITY_TEST_ASSERT(tommRoCUnityEachEqualU8GetError1stIdx((uint8_t) (expectedValue), (actual), (num_elements), (&error1stIdx)), "Expected memory Equal")
#define TEST_ASSERT_IN_ARRAY_EACH_EQUAL_UINT8(expectedValue, actual, num_elements)                                  UNITY_TEST_ASSERT(tommRoCUnityEachEqualU8((expectedValue), (actual), (num_elements)), "Expected memory Equal")
#define TEST_ASSERT_IN_ARRAY_EACH_EQUAL_UINT8_GET_ERROR_1ST_IDX(expectedValue, actual, num_elements, error1stIdx)   UNITY_TEST_ASSERT(tommRoCUnityEachEqualU8GetError1stIdx((expectedValue), (actual), (num_elements), (&error1stIdx)), "Expected memory Equal")
#define TEST_ASSERT_IN_ARRAY_EACH_EQUAL_UINT16(expectedValue, actual, num_elements)                                 UNITY_TEST_ASSERT(tommRoCUnityEachEqualU16((expectedValue), (actual), (num_elements)), "Expected memory Equal")
#define TEST_ASSERT_IN_ARRAY_EACH_EQUAL_UINT16_GET_ERROR_1ST_IDX(expectedValue, actual, num_elements, error1stIdx)  UNITY_TEST_ASSERT(tommRoCUnityEachEqualU16GetError1stIdx((expectedValue), (actual), (num_elements), (&error1stIdx)), "Expected memory Equal")
#define TEST_ASSERT_IN_ARRAY_EACH_EQUAL_UINT32(expectedValue, actual, num_elements)                                 UNITY_TEST_ASSERT(tommRoCUnityEachEqualU32((expectedValue), (actual), (num_elements)), "Expected memory Equal")
#define TEST_ASSERT_IN_ARRAY_EACH_EQUAL_UINT32_GET_ERROR_1ST_IDX(expectedValue, actual, num_elements, error1stIdx)  UNITY_TEST_ASSERT(tommRoCUnityEachEqualU32GetError1stIdx((expectedValue), (actual), (num_elements), (&error1stIdx)), "Expected memory Equal")

// Floating Point
#define TEST_ASSERT_EQUAL_FLOAT(expected, actual)                                                                   TEST_ASSERT_EQUAL(                          (float) (expected),     (float) (actual))
#define TEST_ASSERT_NOT_EQUAL_FLOAT(expected, actual)                                                               TEST_ASSERT_NOT_EQUAL(                      (float) (expected),     (float) (actual))
#define TEST_ASSERT_GREATER_THAN_FLOAT(threshold, actual)                                                           TEST_ASSERT_GREATER_THAN(                   (float) (threshold),    (float) (actual))
#define TEST_ASSERT_LESS_THAN_FLOAT(threshold, actual)                                                              TEST_ASSERT_LESS_THAN(                      (float) (threshold),    (float) (actual))
#define TEST_ASSERT_GREATER_OR_EQUAL_THAN_FLOAT(threshold, actual)                                                  TEST_ASSERT_GREATER_OR_EQUAL_THAN(          (float) (threshold),    (float) (actual))
#define TEST_ASSERT_LESS_OR_EQUAL_THAN_FLOAT(threshold, actual)                                                     TEST_ASSERT_LESS_OR_EQUAL_THAN(             (float) (threshold),    (float) (actual))
#define TEST_ASSERT_POSITIVE_FLOAT(actual)                                                                          TEST_ASSERT_GREATER_THAN_FLOAT(             (float) (0.0f),         (float) (actual))
#define TEST_ASSERT_NEGATIVE_FLOAT(actual)                                                                          TEST_ASSERT_LESS_THAN_FLOAT(                (float) (0.0f),         (float) (actual))
#define TEST_ASSERT_POSITIVE_OR_ZERO_FLOAT(actual)                                                                  TEST_ASSERT_GREATER_OR_EQUAL_THAN_FLOAT(    (float) (0.0f),         (float) (actual))
#define TEST_ASSERT_NEGATIVE_OR_ZERO_FLOAT(actual)                                                                  TEST_ASSERT_LESS_OR_EQUAL_THAN_FLOAT(       (float) (0.0f),         (float) (actual))
#define TEST_ASSERT_WITHIN_FLOAT(delta, expected, actual)                                                           do {                                                                                                        \
                                                                                                                        TEST_ASSERT_POSITIVE_OR_ZERO_FLOAT((delta));                                                            \
                                                                                                                        TEST_ASSERT_GREATER_OR_EQUAL_THAN_FLOAT(    (float) (expected) - (float) (delta),   (float) (actual));  \
                                                                                                                        TEST_ASSERT_LESS_OR_EQUAL_THAN_FLOAT(       (float) (expected) + (float) (delta),   (float) (actual));  \
                                                                                                                    } while (0)


/**
 * Macro to begin unity framework.
 * NOTE: USE THIS IN USER CODE at application startup and before every other unity calls.
 */
#define UNITY_BEGIN()                               tommRoCUnityBegin()

/**
 * Macro to end unity framework.
 * NOTE: USE THIS IN USER CODE at application finish and after don't use no more unity calls.
 */
#define UNITY_END()                                 tommRoCUnityEnd()

/**
 * Macro to check if unity test framework has been started.
 * NOTE: USE THIS IN USER CODE at application finish and after don't use no more unity calls.
 */
#define UNITY_IS_BEGIN()                            tommRoCUnityIsBegin()


/**
 * Macro to run a function based test.
 * NOTE: USE THIS IN USER CODE.
 */
#if defined (TOMMRO_C_UNITY_PRINT_IS_ENABLED)
#define RUN_TEST(funct)                             do { tommRoCUnityRunTest((#funct)); funct(); } while (0)
#else
#define RUN_TEST(funct)                             do { tommRoCUnityRunTest(NULL); funct(); } while (0)
#endif

#if defined (TOMMRO_C_UNITY_PRINT_IS_ENABLED)
#define RUN_TEST_WITH_PARAM(functWithParam)         do { tommRoCUnityRunTest((#functWithParam)); functWithParam; } while (0)
#else
#define RUN_TEST_WITH_PARAM(functWithParam)         do { tommRoCUnityRunTest(NULL); functWithParam; } while (0)
#endif


/**
 * Macro to ignore a function based test.
 * NOTE: USE THIS IN USER CODE.
 */
#if defined (TOMMRO_C_UNITY_PRINT_IS_ENABLED)
#define IGNORE_TEST(funct)                          do { tommRoCUnityIgnoreTest((#funct)); } while (0)
#else
#define IGNORE_TEST(funct)                          do { tommRoCUnityIgnoreTest(NULL); } while (0)
#endif

#if defined (TOMMRO_C_UNITY_PRINT_IS_ENABLED)
#define IGNORE_TEST_WITH_PARAM(functWithParam)      do { tommRoCUnityIgnoreTest((#functWithParam)); } while (0)
#else
#define IGNORE_TEST_WITH_PARAM(functWithParam)      do { tommRoCUnityIgnoreTest(NULL); } while (0)
#endif


/**
 * Macro to print a unity framework message.
 * NOTE: USE THIS IN USER CODE.
 */
#if defined (TOMMRO_C_UNITY_PRINT_IS_ENABLED)
#define UNITY_PRINTLN(msgStrPtr)                                            do { tommRoCUnityPrintln((msgStrPtr)); } while (0)
#define UNITY_PRINTLN_PLUS_STRING(msgStrPtr, strPtr)                        do { tommRoCUnityPrintlnPlusString((msgStrPtr), (strPtr)); } while (0)
#define UNITY_PRINTLN_PLUS_CH(msgStrPtr, ch)                                do { tommRoCUnityPrintlnPlusCh((msgStrPtr),     (ch)); } while (0)
#define UNITY_PRINTLN_PLUS_U8(msgStrPtr, value)                             do { tommRoCUnityPrintlnPlusU8((msgStrPtr),     ((uint8_t) (value))); } while (0)
#define UNITY_PRINTLN_PLUS_U16(msgStrPtr, value)                            do { tommRoCUnityPrintlnPlusU16((msgStrPtr),    ((uint16_t) (value))); } while (0)
#define UNITY_PRINTLN_PLUS_U32(msgStrPtr, value)                            do { tommRoCUnityPrintlnPlusU32((msgStrPtr),    ((uint32_t) (value))); } while (0)
#define UNITY_PRINTLN_PLUS_I8(msgStrPtr, value)                             do { tommRoCUnityPrintlnPlusI8((msgStrPtr),     ((int8_t) (value))); } while (0)
#define UNITY_PRINTLN_PLUS_I16(msgStrPtr, value)                            do { tommRoCUnityPrintlnPlusI16((msgStrPtr),    ((int16_t) (value))); } while (0)
#define UNITY_PRINTLN_PLUS_I32(msgStrPtr, value)                            do { tommRoCUnityPrintlnPlusI32((msgStrPtr),    ((int32_t) (value))); } while (0)
#define UNITY_PRINTLN_PLUS_VERSION(msgStrPtr, version)                      do { tommRoCUnityPrintlnPlusVersion((msgStrPtr), (&version)); } while (0)
#define UNITY_PRINTLN_PLUS_DATE_TIME(msgStrPtr, dateTime)                   do { tommRoCUnityPrintlnPlusDateTime((msgStrPtr), (&dateTime)); } while (0)
#define UNITY_PRINTLN_PLUS_STRING_PLUS_STRING(msgStrPtr, strPtr, str1Ptr)   do { tommRoCUnityPrintlnPlusStringPlusString((msgStrPtr),   (strPtr),   (str1Ptr)); } while (0)
#define UNITY_PRINTLN_PLUS_STRING_PLUS_CH(msgStrPtr, strPtr, ch)            do { tommRoCUnityPrintlnPlusStringPlusCh((msgStrPtr),       (strPtr),   (ch)); } while (0)
#define UNITY_PRINTLN_PLUS_STRING_PLUS_U8(msgStrPtr, strPtr, value)         do { tommRoCUnityPrintlnPlusStringPlusU8((msgStrPtr),       (strPtr),   ((uint8_t) (value))); } while (0)
#define UNITY_PRINTLN_PLUS_STRING_PLUS_U16(msgStrPtr, strPtr, value)        do { tommRoCUnityPrintlnPlusStringPlusU16((msgStrPtr),      (strPtr),   ((uint16_t) (value))); } while (0)
#define UNITY_PRINTLN_PLUS_STRING_PLUS_U32(msgStrPtr, strPtr, value)        do { tommRoCUnityPrintlnPlusStringPlusU32((msgStrPtr),      (strPtr),   ((uint32_t) (value))); } while (0)
#define UNITY_PRINTLN_PLUS_STRING_PLUS_I8(msgStrPtr, strPtr, value)         do { tommRoCUnityPrintlnPlusStringPlusI8((msgStrPtr),       (strPtr),   ((int8_t) (value))); } while (0)
#define UNITY_PRINTLN_PLUS_STRING_PLUS_I16(msgStrPtr, strPtr, value)        do { tommRoCUnityPrintlnPlusStringPlusI16((msgStrPtr),      (strPtr),   ((int16_t) (value))); } while (0)
#define UNITY_PRINTLN_PLUS_STRING_PLUS_I32(msgStrPtr, strPtr, value)        do { tommRoCUnityPrintlnPlusStringPlusI32((msgStrPtr),      (strPtr),   ((int32_t) (value))); } while (0)
#else
#define UNITY_PRINTLN(msgStrPtr)                                            do { TOMMROC_UTIL_UNUSED_PARAM((msgStrPtr)); } while (0)
#define UNITY_PRINTLN_PLUS_STRING(msgStrPtr, strPtr)                        do { TOMMROC_UTIL_UNUSED_PARAM((msgStrPtr)); TOMMROC_UTIL_UNUSED_PARAM((strPtr)); } while (0)
#define UNITY_PRINTLN_PLUS_CH(msgStrPtr, ch)                                do { TOMMROC_UTIL_UNUSED_PARAM((msgStrPtr)); TOMMROC_UTIL_UNUSED_PARAM((ch)); } while (0)
#define UNITY_PRINTLN_PLUS_U8(msgStrPtr, value)                             do { TOMMROC_UTIL_UNUSED_PARAM((msgStrPtr)); TOMMROC_UTIL_UNUSED_PARAM((value)); } while (0)
#define UNITY_PRINTLN_PLUS_U16(msgStrPtr, value)                            do { TOMMROC_UTIL_UNUSED_PARAM((msgStrPtr)); TOMMROC_UTIL_UNUSED_PARAM((value)); } while (0)
#define UNITY_PRINTLN_PLUS_U32(msgStrPtr, value)                            do { TOMMROC_UTIL_UNUSED_PARAM((msgStrPtr)); TOMMROC_UTIL_UNUSED_PARAM((value)); } while (0)
#define UNITY_PRINTLN_PLUS_I8(msgStrPtr, value)                             do { TOMMROC_UTIL_UNUSED_PARAM((msgStrPtr)); TOMMROC_UTIL_UNUSED_PARAM((value)); } while (0)
#define UNITY_PRINTLN_PLUS_I16(msgStrPtr, value)                            do { TOMMROC_UTIL_UNUSED_PARAM((msgStrPtr)); TOMMROC_UTIL_UNUSED_PARAM((value)); } while (0)
#define UNITY_PRINTLN_PLUS_I32(msgStrPtr, value)                            do { TOMMROC_UTIL_UNUSED_PARAM((msgStrPtr)); TOMMROC_UTIL_UNUSED_PARAM((value)); } while (0)
#define UNITY_PRINTLN_PLUS_VERSION(msgStrPtr, version)                      do { TOMMROC_UTIL_UNUSED_PARAM((msgStrPtr)); TOMMROC_UTIL_UNUSED_PARAM((version)); } while (0)
#define UNITY_PRINTLN_PLUS_DATE_TIME(msgStrPtr, dateTime)                   do { TOMMROC_UTIL_UNUSED_PARAM((msgStrPtr)); TOMMROC_UTIL_UNUSED_PARAM((dateTime)); } while (0)
#define UNITY_PRINTLN_PLUS_STRING_PLUS_STRING(msgStrPtr, strPtr, str1Ptr)   do { TOMMROC_UTIL_UNUSED_PARAM((msgStrPtr)); TOMMROC_UTIL_UNUSED_PARAM((strPtr)); TOMMROC_UTIL_UNUSED_PARAM((str1Ptr)); } while (0)
#define UNITY_PRINTLN_PLUS_STRING_PLUS_CH(msgStrPtr, strPtr, ch)            do { TOMMROC_UTIL_UNUSED_PARAM((msgStrPtr)); TOMMROC_UTIL_UNUSED_PARAM((strPtr)); TOMMROC_UTIL_UNUSED_PARAM((ch)); } while (0)
#define UNITY_PRINTLN_PLUS_STRING_PLUS_U8(msgStrPtr, strPtr, value)         do { TOMMROC_UTIL_UNUSED_PARAM((msgStrPtr)); TOMMROC_UTIL_UNUSED_PARAM((strPtr)); TOMMROC_UTIL_UNUSED_PARAM((value)); } while (0)
#define UNITY_PRINTLN_PLUS_STRING_PLUS_U16(msgStrPtr, strPtr, value)        do { TOMMROC_UTIL_UNUSED_PARAM((msgStrPtr)); TOMMROC_UTIL_UNUSED_PARAM((strPtr)); TOMMROC_UTIL_UNUSED_PARAM((value)); } while (0)
#define UNITY_PRINTLN_PLUS_STRING_PLUS_U32(msgStrPtr, strPtr, value)        do { TOMMROC_UTIL_UNUSED_PARAM((msgStrPtr)); TOMMROC_UTIL_UNUSED_PARAM((strPtr)); TOMMROC_UTIL_UNUSED_PARAM((value)); } while (0)
#define UNITY_PRINTLN_PLUS_STRING_PLUS_I8(msgStrPtr, strPtr, value)         do { TOMMROC_UTIL_UNUSED_PARAM((msgStrPtr)); TOMMROC_UTIL_UNUSED_PARAM((strPtr)); TOMMROC_UTIL_UNUSED_PARAM((value)); } while (0)
#define UNITY_PRINTLN_PLUS_STRING_PLUS_I16(msgStrPtr, strPtr, value)        do { TOMMROC_UTIL_UNUSED_PARAM((msgStrPtr)); TOMMROC_UTIL_UNUSED_PARAM((strPtr)); TOMMROC_UTIL_UNUSED_PARAM((value)); } while (0)
#define UNITY_PRINTLN_PLUS_STRING_PLUS_I32(msgStrPtr, strPtr, value)        do { TOMMROC_UTIL_UNUSED_PARAM((msgStrPtr)); TOMMROC_UTIL_UNUSED_PARAM((strPtr)); TOMMROC_UTIL_UNUSED_PARAM((value)); } while (0)
#endif


/**
 * Macro to init unity test on-error callback framework.
 * NOTE: USE THIS IN USER CODE.
 */
#define UNITY_CB_INIT(onErrorCallback)              tommRoCUnityCbInit((onErrorCallback))

/**
 * Macro to close unity test on-error callback framework.
 * NOTE: USE THIS IN USER CODE.
 */
#define UNITY_CB_CLOSE()                            tommRoCUnityCbClose()

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/**
 * On error callback function type.
 */
typedef void (*tommRoC_unity_on_error_callback_funct_t)(void);

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Called when unity test success..
 * NOTE: DO NOT USE IN USER CODE; it's only for library internal use.
 */
void tommRoCUnitySuccess(void);

/**
 * Called when unity test fails.
 * NOTE: DO NOT USE IN USER CODE; it's only for library internal use.
 */
void tommRoCUnityFail(const char* const functNameStrPtr, const uint16_t line, const char* const msgStrPtr);

/**
 * Called to run a unity test funct.
 * NOTE: DO NOT USE IN USER CODE; it's only for library internal use.
 */
void tommRoCUnityRunTest(const char* const functNameStrPtr);

/**
 * Called to ignore a unity test funct.
 * NOTE: DO NOT USE IN USER CODE; it's only for library internal use.
 */
void tommRoCUnityIgnoreTest(const char* const functNameStrPtr);

/**
 * Called to print a unity framework message.
 * NOTE: DO NOT USE IN USER CODE; it's only for library internal use.
 */
void tommRoCUnityPrintln(const char* const msgStrPtr);
void tommRoCUnityPrintlnPlusString(const char* const msgStrPtr, const char* const strPtr);
void tommRoCUnityPrintlnPlusCh(const char* const msgStrPtr, const char ch);
void tommRoCUnityPrintlnPlusU8(const char* const msgStrPtr, const uint8_t value);
void tommRoCUnityPrintlnPlusU16(const char* const msgStrPtr, const uint16_t value);
void tommRoCUnityPrintlnPlusU32(const char* const msgStrPtr, const uint32_t value);
void tommRoCUnityPrintlnPlusI8(const char* const msgStrPtr, const int8_t value);
void tommRoCUnityPrintlnPlusI16(const char* const msgStrPtr, const int16_t value);
void tommRoCUnityPrintlnPlusI32(const char* const msgStrPtr, const int32_t value);
void tommRoCUnityPrintlnPlusVersion(const char* const msgStrPtr, const tommRoC_version_t* const versionPtr);
void tommRoCUnityPrintlnPlusDateTime(const char* const msgStrPtr, const tommRoC_date_time_t* const dateTimePtr);
void tommRoCUnityPrintlnPlusStringPlusString(const char* const msgStrPtr, const char* const strPtr, const char* const str1Ptr);
void tommRoCUnityPrintlnPlusStringPlusCh(const char* const msgStrPtr, const char* const strPtr, const char ch);
void tommRoCUnityPrintlnPlusStringPlusU8(const char* const msgStrPtr, const char* const strPtr, const uint8_t value);
void tommRoCUnityPrintlnPlusStringPlusU16(const char* const msgStrPtr, const char* const strPtr, const uint16_t value);
void tommRoCUnityPrintlnPlusStringPlusU32(const char* const msgStrPtr, const char* const strPtr, const uint32_t value);
void tommRoCUnityPrintlnPlusStringPlusI8(const char* const msgStrPtr, const char* const strPtr, const int8_t value);
void tommRoCUnityPrintlnPlusStringPlusI16(const char* const msgStrPtr, const char* const strPtr, const int16_t value);
void tommRoCUnityPrintlnPlusStringPlusI32(const char* const msgStrPtr, const char* const strPtr, const int32_t value);


/**
 * Called to begin unity test framework.
 * NOTE: DO NOT USE IN USER CODE; it's only for library internal use.
 */
bool tommRoCUnityBegin(void);

/**
 * Called to end unity test framework.
 * NOTE: DO NOT USE IN USER CODE; it's only for library internal use.
 */
bool tommRoCUnityEnd(void);

/**
 * Get if unity test framework has been started.
 * NOTE: DO NOT USE IN USER CODE; it's only for library internal use.
 */
bool tommRoCUnityIsBegin(void);

/**
 * Init unity test on-error callback function.
 * NOTE: DO NOT USE IN USER CODE; it's only for library internal use.
 */
bool tommRoCUnityCbInit(const tommRoC_unity_on_error_callback_funct_t onErrorCallback);

/**
 * Close (clear) unity test on-error callback function.
 * NOTE: DO NOT USE IN USER CODE; it's only for library internal use.
 */
bool tommRoCUnityCbClose(void);

/**
 * Utility functions.
 * NOTE: DO NOT USE IN USER CODE; it's only for library internal use.
 */
bool tommRoCUnityEqualString(const char* const expectedPtr, const char* const actualPtr);
bool tommRoCUnityEqualStringLen(const char* const expectedPtr, const char* const actualPtr, const uint32_t length);
bool tommRoCUnityStartWithString(const char* const expectedPtr, const char* const actualPtr);
bool tommRoCUnityEndWithString(const char* const expectedPtr, const char* const actualPtr);
bool tommRoCUnityEqualMemory(const void* const expectedPtr, const void* const actualPtr, const uint32_t length);
bool tommRoCUnityEqualMemoryGetError1stIdx(const void* const expectedPtr, const void* const actualPtr, const uint32_t length, uint32_t* const error1stIdxPtr);
bool tommRoCUnityEachEqualU8(const uint8_t expectedValue, const void* const actualPtr, const uint32_t numElements);
bool tommRoCUnityEachEqualU8GetError1stIdx(const uint8_t expectedValue, const void* const actualPtr, const uint32_t numElements, uint32_t* const error1stIdxPtr);
bool tommRoCUnityEachEqualU16(const uint16_t expectedValue, const void* const actualPtr, const uint32_t numElements);
bool tommRoCUnityEachEqualU16GetError1stIdx(const uint16_t expectedValue, const void* const actualPtr, const uint32_t numElements, uint32_t* const error1stIdxPtr);
bool tommRoCUnityEachEqualU32(const uint32_t expectedValue, const void* const actualPtr, const uint32_t numElements);
bool tommRoCUnityEachEqualU32GetError1stIdx(const uint32_t expectedValue, const void* const actualPtr, const uint32_t numElements, uint32_t* const error1stIdxPtr);

/**
 * @}
 */

#endif
