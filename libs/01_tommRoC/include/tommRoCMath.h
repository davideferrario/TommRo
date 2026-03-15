
#ifndef TOMMROC_MATH_H_
#define TOMMROC_MATH_H_

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
 * @defgroup tommRoCMath tommRoCMath
 *
 * @brief  TommRoC library math module
 * @author TommRo Software Department
 *
 * This module is providing math functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCEnv.h"
#include "tommRoCErr.h"
#include "tommRoCInt.h"
#include "tommRoCUtil.h"

#include <float.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/**
 * Limits values.
 */
#define UINT8_MIN_VALUE     (0)
#define UINT16_MIN_VALUE    (0)
#define UINT24_MIN_VALUE    (0)
#define UINT32_MIN_VALUE    (0)
#define UINT64_MIN_VALUE    (0)
#define FLOAT_MIN_VALUE     (FLT_MIN)

#define UINT8_MAX_VALUE     (0xFF)
#define UINT16_MAX_VALUE    (0xFFFF)
#define UINT24_MAX_VALUE    (0xFFFFFF)
#define UINT32_MAX_VALUE    (0xFFFFFFFF)
#define UINT64_MAX_VALUE    (0xFFFFFFFFFFFFFFFF)
#define FLOAT_MAX_VALUE     (FLT_MAX)

#define INT8_MIN_VALUE      (-127 - 1)
#define INT16_MIN_VALUE     (-32767 - 1)
#define INT24_MIN_VALUE     (-8388607 - 1)
#define INT32_MIN_VALUE     (-2147483647 -1)
#define INT64_MIN_VALUE     (-9223372036854775807 -1)

#define INT8_MAX_VALUE      (127)
#define INT16_MAX_VALUE     (32767)
#define INT24_MAX_VALUE     (8388607)
#define INT32_MAX_VALUE     (2147483647)
#define INT64_MAX_VALUE     (9223372036854775807)

/**
 * Minimum uintx_t values.
 */
#ifndef UINT8_MIN
#define UINT8_MIN   ((uint8_t) 0)
#endif

#ifndef UINT16_MIN
#define UINT16_MIN  ((uint16_t) 0)
#endif

#ifndef UINT24_MIN
#define UINT24_MIN  (0UL)
#endif

#ifndef UINT32_MIN
#define UINT32_MIN  ((uint32_t) 0)
#endif

#ifdef TOMMROC_INT_UINT64_SUPPORTED
#ifndef UINT64_MIN
#define UINT64_MIN  ((uint64_t) 0)
#endif
#endif

/**
 * Maximum uintx_t values.
 */
#ifndef UINT8_MAX
#define UINT8_MAX   ((uint8_t) 0xFFU)
#endif

#ifndef UINT16_MAX
#define UINT16_MAX  ((uint16_t) 0xFFFFU)
#endif

#ifndef UINT24_MAX
#define UINT24_MAX  (0xFFFFFFUL)
#endif

#ifndef UINT32_MAX
#define UINT32_MAX  ((uint32_t) 0xFFFFFFFFUL)
#endif

#ifdef TOMMROC_INT_UINT64_SUPPORTED
#ifndef UINT64_MAX
#define UINT64_MAX  ((uint64_t) 0xFFFFFFFFFFFFFFFFULL)
#endif
#endif

/**
 * Minimum intx_t values.
 */
#ifndef INT8_MIN
#define INT8_MIN    ((int8_t) (-127 - 1))
#endif

#ifndef INT16_MIN
#define INT16_MIN   ((int16_t) (-32767 - 1))
#endif

#ifndef INT24_MIN
#define INT24_MIN   (-8388607UL - 1UL)
#endif

#ifndef INT32_MIN
#define INT32_MIN   ((int32_t) (-2147483647 -1))
#endif

#ifdef TOMMROC_INT_INT64_SUPPORTED
#ifndef INT64_MIN
#define INT64_MIN   ((int64_t) (-9223372036854775807LL -1))
#endif
#endif

/**
 * Maximum intx_t values.
 */
#ifndef INT8_MAX
#define INT8_MAX    ((int8_t) 127)
#endif

#ifndef INT16_MAX
#define INT16_MAX   ((int16_t) 32767)
#endif

#ifndef INT24_MAX
#define INT24_MAX   (8388607UL)
#endif

#ifndef INT32_MAX
#define INT32_MAX   ((int32_t) 2147483647)
#endif

#ifdef TOMMROC_INT_INT64_SUPPORTED
#ifndef INT64_MAX
#define INT64_MAX   ((int64_t) 9223372036854775807LL)
#endif
#endif

/**
 * Minimum/Maximum float values.
 */
#ifndef FLOAT_MIN
#define FLOAT_MIN   ((float) FLT_MIN)
#endif

#ifndef FLOAT_MAX
#define FLOAT_MAX   ((float) FLT_MAX)
#endif

#define TOMMROC_MATH_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define TOMMROC_MATH_MIN(a, b) (((a) < (b)) ? (a) : (b))

#define TOMMROC_MATH_PI         (3.14159265358979323846f)       // 3.141592653  180 degree
#define TOMMROC_MATH_PI_DIV_2   (TOMMROC_MATH_PI / (2.0f))      // 1.570796327  90 degree
#define TOMMROC_MATH_PI_DIV_3   (TOMMROC_MATH_PI / (3.0f))      // 1.047197551  60 degree
#define TOMMROC_MATH_PI_DIV_4   (TOMMROC_MATH_PI / (4.0f))      // 0.785398163  45 degree
#define TOMMROC_MATH_PI_DIV_6   (TOMMROC_MATH_PI / (6.0f))      // 0.523598776  30 degree
#define TOMMROC_MATH_PI_DIV_180 (TOMMROC_MATH_PI / (180.0f))    // 0.017453293  1 degree
#define TOMMROC_MATH_PI_MUL_2   (TOMMROC_MATH_PI * (2.0f))      // 6.283185306  360 degree

#define TOMMROC_MATH_SQUARE_ROOT_2          (1.414213562f)                          // SquareRoot(2)        1.414213562
#define TOMMROC_MATH_SQUARE_ROOT_2_DIV_2    (TOMMROC_MATH_SQUARE_ROOT_2 / (2.0f))   // SquareRoot(2) / 2    0.707106781
#define TOMMROC_MATH_SQUARE_ROOT_2_MUL_2    (TOMMROC_MATH_SQUARE_ROOT_2 * (2.0f))   // SquareRoot(2) * 2    2.828427125
#define TOMMROC_MATH_SQUARE_ROOT_3          (1.732050808f)                          // SquareRoot(3)        1.732050808
#define TOMMROC_MATH_SQUARE_ROOT_3_DIV_2    (TOMMROC_MATH_SQUARE_ROOT_3 / (2.0f))   // SquareRoot(3) / 2    0.866025404
#define TOMMROC_MATH_SQUARE_ROOT_3_DIV_3    (TOMMROC_MATH_SQUARE_ROOT_3 / (3.0f))   // SquareRoot(3) / 3    0.577350269
#define TOMMROC_MATH_SQUARE_ROOT_3_DIV_4    (TOMMROC_MATH_SQUARE_ROOT_3 / (4.0f))   // SquareRoot(3) / 4    0.433012702
#define TOMMROC_MATH_SQUARE_ROOT_3_MUL_2    (TOMMROC_MATH_SQUARE_ROOT_3 * (2.0f))   // SquareRoot(3) * 2    3.464101615

/**
 * Macro to divide integers value with approximation.
 * Example:
 *      value   = 222
 *      divider = 7
 *      222 / 7 = 31,714285714 -> APPROX = 32                   (222 + (7 / 2)) / 7 = (222 + 3) / 7 = 225 / 7 = 32
 */
#define TOMMROC_MATH_UINT_DIVIDE_APPROX(value, divider)         ((((value) + ((divider) / 2)) / (divider)))
#define TOMMROC_MATH_INT_DIVIDE_APPROX(value, divider)          (((value >= 0) == (divider >= 0)) ? ((((value) + ((divider) / 2)) / (divider))) : ((((value) - ((divider) / 2)) / (divider))))

/**
 * Macro to approximate integer value to nearest with a specific resolution.
 * Example:
 *      value       = 461
 *      resolution  = 20
 *      APPROX      = 460                                       461 % 20 = 1 < 20 / 2 -> 461 - 1 = 460
 *
 *      value       = 475
 *      resolution  = 20
 *      APPROX      = 480                                       475 % 20 = 15 > 20 / 2 -> 475 - 15 + 20 = 480
 */
#define TOMMROC_MATH_INT_NEAREST_APPROX(value, resolution)      ((((value) % (resolution)) <= ((resolution) / 2)) ? ((value) - ((value) % (resolution))) : ((value) - ((value) % (resolution)) + (resolution)))

/**
 * Macro to approximate integer value to largest integer value less than or equal to with a specific resolution.
 * Example:
 *      value       = 460
 *      resolution  = 20
 *      APPROX      = 460                                       (460 / 20) * 20 = 23 * 20 = 460
 *
 *      value       = 461
 *      resolution  = 20
 *      APPROX      = 460                                       (461 / 20) * 20 = 23 * 20 = 460
 *
 *      value       = 479
 *      resolution  = 20
 *      APPROX      = 460                                       (479 / 20) * 20 = 23 * 20 = 460
 */
#define TOMMROC_MATH_INT_BY_DEFAULT_APPROX(value, resolution)   ((((value) / (resolution)) * (resolution)))

/**
 * Macro to c integer value to largest integer value less than or equal to with a specific resolution.
 * Example:
 *      value       = 460
 *      resolution  = 20
 *      APPROX      = 460                                       460 % 20 = 0 == 0 -> 460
 *
 *      value       = 461
 *      resolution  = 20
 *      APPROX      = 480                                       461 % 20 = 1 != 0 -> 461 - (461 % 20) + 20 = 461 - 1 + 20 = 480
 *
 *      value       = 479
 *      resolution  = 20
 *      APPROX      = 480                                       479 % 20 = 19 != 0 -> 479 - (479 % 20) + 20 = 479 - 19 + 20 = 480
 */
#define TOMMROC_MATH_INT_BY_EXCESS_APPROX(value, resolution)    ((((value) % (resolution)) == (0)) ? (value) : (((value) - ((value) % (resolution))) + (resolution)))


/**
 * Macro for integer division with approximation.
 */
#define TOMMROC_MATH_INT_DIVIDE_NEAREST(value, divider)     (TOMMROC_MATH_INT_NEAREST_APPROX(value, divider) / (divider))
#define TOMMROC_MATH_INT_DIVIDE_BY_EXCESS(value, divider)   (TOMMROC_MATH_INT_BY_EXCESS_APPROX(value, divider) / (divider))


/**
 * Float square root accuracy level
 */
#define TOMMROC_MATH_FLOAT_SQUARE_ROOT_ACCURACY_LEVEL   (0.0000001f)
#define TOMMROC_MATH_FLOAT_TRIGONOMETRY_ACCURACY_LEVEL  (0.000001f)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of bit status.
typedef enum {

    /**
     * Low level.
     */
    TOMMRO_C_MATH_LOW_LEVEL = TOMMRO_C_UTIL_LOW_LEVEL,

    /**
     * High level.
     */
    TOMMRO_C_MATH_HIGH_LEVEL = TOMMRO_C_UTIL_HIGH_LEVEL,

    /**
     * Param error.
     */
    TOMMRO_C_MATH_PARAM_ERROR,

} tommRoC_math_bit_status_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Get a 8 bit variable from 32 bit value.
 *
 * param[in]        data                    32 bit value.
 * param[in]        offset                  byte offset (0, 1, 2, 3).
 *
 * return uint8_t
 */
uint8_t tommRoCMathMake8(
        const   uint32_t    data,
        const   uint8_t     offset);

/**
 * Get a 16 bit variable from 2 8 bit values.
 *
 * param[in]        dataHigh                higher 8 bit.
 * param[in]        dataLow                 lower 8 bit.
 *
 * return uint16_t
 */
uint16_t tommRoCMathMake16(
        const   uint8_t     dataHigh,
        const   uint8_t     dataLow);

/**
 * Get a 32 bit variable from 4 8 bit values.
 *
 * param[in]        dataHigh                higher 8 bit.
 * param[in]        dataMiddleHigh          middle higher 8 bit.
 * param[in]        dataMiddleLow           middle lower 8 bit.
 * param[in]        dataLow                 lower 8 bit.
 *
 * return uint32_t
 */
uint32_t tommRoCMathMake32(
        const   uint8_t     dataHigh,
        const   uint8_t     dataMiddleHigh,
        const   uint8_t     dataMiddleLow,
        const   uint8_t     dataLow);

#if defined (TOMMROC_INT_UINT64_SUPPORTED)
/**
 * Get a 8 bit variable from 64 bit value.
 *
 * param[in]        data                    64 bit value.
 * param[in]        offset                  byte offset (0, 1, 2, 3, 4, 5, 6, 7).
 *
 * return uint8_t
 */
uint8_t tommRoCMathMake8U64(
        const   uint64_t    data,
        const   uint8_t     offset);

/**
 * Get a 64 bit variable from 8 8 bit values.
 *
 * param[in]        dataHigh                higher 8 bit.
 * param[in]        data1,..,data6          middle 8 bit.
 * param[in]        dataLow                 lower 8 bit.
 *
 * return uint64_t
 */
uint64_t tommRoCMathMake64(
        const   uint8_t     dataHigh,
        const   uint8_t     data1,
        const   uint8_t     data2,
        const   uint8_t     data3,
        const   uint8_t     data4,
        const   uint8_t     data5,
        const   uint8_t     data6,
        const   uint8_t     dataLow);

/**
 * Get a 64 bit variable from 4 16 bit values.
 *
 * param[in]        dataHigh                higher 16 bit.
 * param[in]        dataMiddleHigh          middle higher 16 bit.
 * param[in]        dataMiddleLow           middle lower 16 bit.
 * param[in]        dataLow                 lower 16 bit.
 *
 * return uint64_t
 */
uint64_t tommRoCMathMake64From16(
        const   uint16_t    dataHigh,
        const   uint16_t    dataMiddleHigh,
        const   uint16_t    dataMiddleLow,
        const   uint16_t    dataLow);

/**
 * Get a 64 bit variable from 2 32 bit values.
 *
 * param[in]        dataHigh                higher 32 bit.
 * param[in]        dataLow                 lower 32 bit.
 *
 * return uint64_t
 */
uint64_t tommRoCMathMake64From32(
        const   uint32_t    dataHigh,
        const   uint32_t    dataLow);
#endif

/**
 * Count the amount of bits set within a 32bit integer.
 *
 * param[in]        data                    32 bit value.
 *
 * return uint8_t
 */
uint8_t tommRoCMathCountBitsSet(const uint32_t data);

/**
 * Clear a bit of a 32 bit value.
 *
 * param[in]        data                    32 bit value.
 * param[in]        bitOffset               bit offset (0 - least significant bit,..,31).
 *
 * return uint32_t
 */
uint32_t tommRoCMathBitClear(
        const   uint32_t    data,
        const   uint8_t     bitOffset);

/**
 * Set a bit of a 32 bit value.
 *
 * param[in]        data                    32 bit value.
 * param[in]        bitOffset               bit offset (0 - least significant bit,..,31).
 *
 * return uint32_t
 */
uint32_t tommRoCMathBitSet(
        const   uint32_t    data,
        const   uint8_t     bitOffset);

/**
 * Test a bit of a 32 bit value.
 *
 * param[in]        data                    32 bit value.
 * param[in]        bitOffset               bit offset (0 - least significant bit,..,31).
 *
 * return tommRoC_math_bit_status_enum_t
 */
tommRoC_math_bit_status_enum_t tommRoCMathBitTest(
        const   uint32_t    data,
        const   uint8_t     bitOffset);

/**
 * Set a 8 bit nibble into a 16 bit value.
 *
 * param[in]        data                    16 bit value.
 * param[in]        value                   8 bit nibble.
 * param[in]        offset                  byte offset (0, 1).
 *
 * return uint16_t
 */
uint16_t tommRoCMathByteSet16(
        const   uint16_t    data,
        const   uint8_t     value,
        const   uint8_t     offset);

/**
 * Set a 8 bit nibble into a 32 bit value.
 *
 * param[in]        data                    32 bit value.
 * param[in]        value                   8 bit nibble.
 * param[in]        offset                  byte offset (0, 1, 2, 3).
 *
 * return uint32_t
 */
uint32_t tommRoCMathByteSet32(
        const   uint32_t    data,
        const   uint8_t     value,
        const   uint8_t     offset);

/**
 * Get min value of xint32_t params.
 *
 * param[in]        value1                  param 1.
 * param[in]        value2                  param 2.
 *
 * return xint32_t
 */
uint32_t tommRoCMathMin(const uint32_t value1, const uint32_t value2);
int32_t tommRoCMathMinI32(const int32_t value1, const int32_t value2);

/**
 * Get max value of xint32_t params.
 *
 * param[in]        value1                  param 1.
 * param[in]        value2                  param 2.
 *
 * return xint32_t
 */
uint32_t tommRoCMathMax(const uint32_t value1, const uint32_t value2);
int32_t tommRoCMathMaxI32(const int32_t value1, const int32_t value2);

/**
 * Get min value of uintx_t/intx_t array
 *
 * param[in]        dataBufferPtr           data buffer pointer.
 * param[in]        dataBufferAmount        data buffer elem amount.
 * param[out]       resPtr                  min value result pointer.
 * param[out]       resIdxPtr               min value result array index pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCMathU8ArrayMin(
        const   uint8_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                uint8_t*    const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathU16ArrayMin(
        const   uint16_t*   const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                uint16_t*   const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathU32ArrayMin(
        const   uint32_t*   const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                uint32_t*   const   resPtr,
                uint16_t*   const   resIdxPtr);

tommRoC_err_enum_t tommRoCMathI8ArrayMin(
        const   int8_t*     const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                int8_t*     const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathI16ArrayMin(
        const   int16_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                int16_t*    const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathI32ArrayMin(
        const   int32_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                int32_t*    const   resPtr,
                uint16_t*   const   resIdxPtr);

/**
 * Get max value of uintx_t/intx_t array
 *
 * param[in]        dataBufferPtr           data buffer pointer.
 * param[in]        dataBufferAmount        data buffer elem amount.
 * param[out]       resPtr                  max value result pointer.
 * param[out]       resIdxPtr               max value result array index pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCMathU8ArrayMax(
        const   uint8_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                uint8_t*    const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathU16ArrayMax(
        const   uint16_t*   const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                uint16_t*   const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathU32ArrayMax(
        const   uint32_t*   const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                uint32_t*   const   resPtr,
                uint16_t*   const   resIdxPtr);

tommRoC_err_enum_t tommRoCMathI8ArrayMax(
        const   int8_t*     const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                int8_t*     const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathI16ArrayMax(
        const   int16_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                int16_t*    const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathI32ArrayMax(
        const   int32_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                int32_t*    const   resPtr,
                uint16_t*   const   resIdxPtr);

/**
 * Get min/max value of uintx_t/intx_t array
 *
 * param[in]        dataBufferPtr           data buffer pointer.
 * param[in]        dataBufferAmount        data buffer elem amount.
 * param[out]       minPtr                  min value result pointer.
 * param[out]       maxPtr                  max value result pointer.
 * param[out]       minIdxPtr               min value result array index pointer.
 * param[out]       maxIdxPtr               max value result array index pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCMathU8ArrayMinMax(
        const   uint8_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                uint8_t*    const   minPtr,
                uint8_t*    const   maxPtr,
                uint16_t*   const   minIdxPtr,
                uint16_t*   const   maxIdxPtr);
tommRoC_err_enum_t tommRoCMathU16ArrayMinMax(
        const   uint16_t*   const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                uint16_t*   const   minPtr,
                uint16_t*   const   maxPtr,
                uint16_t*   const   minIdxPtr,
                uint16_t*   const   maxIdxPtr);
tommRoC_err_enum_t tommRoCMathU32ArrayMinMax(
        const   uint32_t*   const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                uint32_t*   const   minPtr,
                uint32_t*   const   maxPtr,
                uint16_t*   const   minIdxPtr,
                uint16_t*   const   maxIdxPtr);

tommRoC_err_enum_t tommRoCMathI8ArrayMinMax(
        const   int8_t*     const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                int8_t*     const   minPtr,
                int8_t*     const   maxPtr,
                uint16_t*   const   minIdxPtr,
                uint16_t*   const   maxIdxPtr);
tommRoC_err_enum_t tommRoCMathI16ArrayMinMax(
        const   int16_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                int16_t*    const   minPtr,
                int16_t*    const   maxPtr,
                uint16_t*   const   minIdxPtr,
                uint16_t*   const   maxIdxPtr);
tommRoC_err_enum_t tommRoCMathI32ArrayMinMax(
        const   int32_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                int32_t*    const   minPtr,
                int32_t*    const   maxPtr,
                uint16_t*   const   minIdxPtr,
                uint16_t*   const   maxIdxPtr);

/**
 * Get sum value of uintx_t/intx_t array
 *
 * param[in]        dataBufferPtr           data buffer pointer.
 * param[in]        dataBufferAmount        data buffer elem amount.
 * param[out]       resPtr                  sum value result pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCMathU8ArraySum(
        const   uint8_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                uint32_t*   const   resPtr);
tommRoC_err_enum_t tommRoCMathU16ArraySum(
        const   uint16_t*   const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                uint32_t*   const   resPtr);
tommRoC_err_enum_t tommRoCMathU32ArraySum(
        const   uint32_t*   const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                uint32_t*   const   resPtr);

tommRoC_err_enum_t tommRoCMathI8ArraySum(
        const   int8_t*     const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                int32_t*    const   resPtr);
tommRoC_err_enum_t tommRoCMathI16ArraySum(
        const   int16_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                int32_t*    const   resPtr);
tommRoC_err_enum_t tommRoCMathI32ArraySum(
        const   int32_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                int32_t*    const   resPtr);

/**
 * Get mean value of uintx_t/intx_t array
 *
 * param[in]        dataBufferPtr           data buffer pointer.
 * param[in]        dataBufferAmount        data buffer elem amount.
 * param[out]       resPtr                  mean value result pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCMathU8ArrayMean(
        const   uint8_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                uint8_t*    const   resPtr);
tommRoC_err_enum_t tommRoCMathU16ArrayMean(
        const   uint16_t*   const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                uint16_t*   const   resPtr);
tommRoC_err_enum_t tommRoCMathU32ArrayMean(
        const   uint32_t*   const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                uint32_t*   const   resPtr);

tommRoC_err_enum_t tommRoCMathI8ArrayMean(
        const   int8_t*     const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                int8_t*     const   resPtr);
tommRoC_err_enum_t tommRoCMathI16ArrayMean(
        const   int16_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                int16_t*    const   resPtr);
tommRoC_err_enum_t tommRoCMathI32ArrayMean(
        const   int32_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                int32_t*    const   resPtr);

/**
 * Reflect (bit oriented) uintx_t values.
 * Example: 0b11000110 -> 0b01100011
 *
 * param[in]        value                   value to be reflected.
 *
 * return uintx_t
 */
uint8_t tommRoCMathReflectBitU8(const uint8_t value);
uint16_t tommRoCMathReflectBitU16(const uint16_t value);
uint32_t tommRoCMathReflectBitU32(const uint32_t value);
#if defined (TOMMROC_INT_UINT64_SUPPORTED)
uint64_t tommRoCMathReflectBitU64(const uint64_t value);
#endif

/**
 * Reflect (byte oriented) uintx_t values.
 * Example: 0x12345678 -> 0x78563412
 *
 * param[in]        value                   value to be reflected.
 *
 * return uintx_t
 */
uint8_t tommRoCMathReflectByteU8(const uint8_t value);
uint16_t tommRoCMathReflectByteU16(const uint16_t value);
uint32_t tommRoCMathReflectByteU32(const uint32_t value);
#if defined (TOMMROC_INT_UINT64_SUPPORTED)
uint64_t tommRoCMathReflectByteU64(const uint64_t value);
#endif

/**
 * Swap each others two uintx_t values.
 * NOTE: *value1Ptr <-> *value2Ptr
 *
 * param[in]        value1Ptr               param 1 pointer.
 * param[in]        value2Ptr               param 2 pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCMathSwapU8(
        uint8_t*    const   value1Ptr,
        uint8_t*    const   value2Ptr);

tommRoC_err_enum_t tommRoCMathSwapU16(
        uint16_t*   const   value1Ptr,
        uint16_t*   const   value2Ptr);

tommRoC_err_enum_t tommRoCMathSwapU32(
        uint32_t*   const   value1Ptr,
        uint32_t*   const   value2Ptr);

/**
 * Get round difference value of uintx_t params.
 *
 * param[in]        minus                   minus param.
 * param[in]        subtracting             subtracting param.
 *
 * return uintx_t
 */
uint8_t tommRoCMathRoundDiffU8(
        const   uint8_t     minus,
        const   uint8_t     subtracting);

uint16_t tommRoCMathRoundDiffU16(
        const   uint16_t    minus,
        const   uint16_t    subtracting);

uint32_t tommRoCMathRoundDiffU32(
        const   uint32_t    minus,
        const   uint32_t    subtracting);

/**
 * Get round difference (with limit) value of uintx_t params.
 *
 * param[in]        minus                   minus param.
 * param[in]        subtracting             subtracting param.
 * param[in]        limit                   difference limit.
 *
 * return uintx_t
 */
uint8_t tommRoCMathRoundDiffLimitU8(
        const   uint8_t     minus,
        const   uint8_t     subtracting,
        const   uint8_t     limit);

uint16_t tommRoCMathRoundDiffLimitU16(
        const   uint16_t    minus,
        const   uint16_t    subtracting,
        const   uint16_t    limit);

uint32_t tommRoCMathRoundDiffLimitU32(
        const   uint32_t    minus,
        const   uint32_t    subtracting,
        const   uint32_t    limit);

/**
 * Get abs difference value of uintx_t/intx_t params.
 *
 * param[in]        value1                  first value.
 * param[in]        value2                  second value.
 *
 * return uintx_t
 */
uint8_t tommRoCMathABSDiffU8(
        const   uint8_t     value1,
        const   uint8_t     value2);
int8_t tommRoCMathABSDiffI8(
        const   int8_t      value1,
        const   int8_t      value2);

uint16_t tommRoCMathABSDiffU16(
        const   uint16_t    value1,
        const   uint16_t    value2);
int16_t tommRoCMathABSDiffI16(
        const   int16_t     value1,
        const   int16_t     value2);

uint32_t tommRoCMathABSDiffU32(
        const   uint32_t    value1,
        const   uint32_t    value2);
int32_t tommRoCMathABSDiffI32(
        const   int32_t    value1,
        const   int32_t    value2);

/**
 * Get abs value of intx_t/float params.
 *
 * param[in]        value                   value.
 *
 * return uintx_t/float
 */
uint8_t tommRoCMathABSI8(const int8_t value);
uint16_t tommRoCMathABSI16(const int16_t value);
uint32_t tommRoCMathABSI32(const int32_t value);
float tommRoCMathABSFloat(const float value);

/**
 * Square root of uintx_t param.
 *
 * param[in]        value                   value.
 *
 * return uintx_t
 */
uint8_t tommRoCMathSqrtU8(const uint8_t value);
uint16_t tommRoCMathSqrtU16(const uint16_t value);
uint32_t tommRoCMathSqrtU32(const uint32_t value);

/**
 * Get min value of float params.
 *
 * param[in]        value1                  param 1.
 * param[in]        value2                  param 2.
 *
 * return float
 */
float tommRoCMathFloatMin(const float value1, const float value2);

/**
 * Get max value of float params.
 *
 * param[in]        value1                  param 1.
 * param[in]        value2                  param 2.
 *
 * return float
 */
float tommRoCMathFloatMax(const float value1, const float value2);

/**
 * Get min/max value of float array
 *
 * param[in]        dataBufferPtr           data buffer pointer.
 * param[in]        dataBufferAmount        data buffer elem amount.
 * param[out]       resPtr                  min value result pointer.
 * param[out]       resIdxPtr               min value result array index pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCMathFloatArrayMin(
        const   float*      const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                float*      const   resPtr,
                uint16_t*   const   resIdxPtr);

tommRoC_err_enum_t tommRoCMathFloatArrayMax(
        const   float*      const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                float*      const   resPtr,
                uint16_t*   const   resIdxPtr);

/**
 * Get min/max value of float array
 *
 * param[in]        dataBufferPtr           data buffer pointer.
 * param[in]        dataBufferAmount        data buffer elem amount.
 * param[out]       minPtr                  min value result pointer.
 * param[out]       maxPtr                  max value result pointer.
 * param[out]       minIdxPtr               min value result array index pointer.
 * param[out]       maxIdxPtr               max value result array index pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCMathFloatArrayMinMax(
        const   float*      const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                float*      const   minPtr,
                float*      const   maxPtr,
                uint16_t*   const   minIdxPtr,
                uint16_t*   const   maxIdxPtr);

/**
 * Get sum value of float array.
 *
 * param[in]        dataBufferPtr           data buffer pointer.
 * param[in]        dataBufferAmount        data buffer elem amount.
 * param[out]       resPtr                  sum value result pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCMathFloatArraySum(
        const   float*      const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                float*      const   resPtr);

/**
 * Get sum value of float (absolute value) array.
 * NOTE: every array element, is used in absolute value.
 *
 * param[in]        dataBufferPtr           data buffer pointer.
 * param[in]        dataBufferAmount        data buffer elem amount.
 * param[out]       resPtr                  sum value result pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCMathFloatArrayABSSum(
        const   float*      const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                float*      const   resPtr);

/**
 * Get mean value of float array.
 *
 * param[in]        dataBufferPtr           data buffer pointer.
 * param[in]        dataBufferAmount        data buffer elem amount.
 * param[out]       resPtr                  mean value result pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCMathFloatArrayMean(
        const   float*      const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                float*      const   resPtr);

/**
 * Get mean value of float (absolute value) array.
 * NOTE: every array element, is used in absolute value.
 *
 * param[in]        dataBufferPtr           data buffer pointer.
 * param[in]        dataBufferAmount        data buffer elem amount.
 * param[out]       resPtr                  mean value result pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCMathFloatArrayABSMean(
        const   float*      const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
                float*      const   resPtr);

/**
 * Get first maximum peak value of uintx_t/intx_t/float array.
 * NOTE: to be a valid peak, all peakWindowAmount / 2 elements before and after selected value MUST be less or equal then value.
 *
 * param[in]        dataBufferPtr           data buffer pointer.
 * param[in]        dataBufferAmount        data buffer elem amount.
 * param[out]       resPtr                  min value result pointer.
 * param[out]       resIdxPtr               min value result array index pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCMathU8ArrayMaxPeak(
        const   uint8_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   uint16_t            peakWindowAmount,
                uint8_t*    const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathU16ArrayMaxPeak(
        const   uint16_t*   const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   uint16_t            peakWindowAmount,
                uint16_t*   const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathU32ArrayMaxPeak(
        const   uint32_t*   const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   uint16_t            peakWindowAmount,
                uint32_t*   const   resPtr,
                uint16_t*   const   resIdxPtr);

tommRoC_err_enum_t tommRoCMathI8ArrayMaxPeak(
        const   int8_t*     const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   uint16_t            peakWindowAmount,
                int8_t*     const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathI16ArrayMaxPeak(
        const   int16_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   uint16_t            peakWindowAmount,
                int16_t*    const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathI32ArrayMaxPeak(
        const   int32_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   uint16_t            peakWindowAmount,
                int32_t*    const   resPtr,
                uint16_t*   const   resIdxPtr);

tommRoC_err_enum_t tommRoCMathFloatArrayMaxPeak(
        const   float*      const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   uint16_t            peakWindowAmount,
                float*      const   resPtr,
                uint16_t*   const   resIdxPtr);

/**
 * Get first minimum peak value of uintx_t/intx_t/float array.
 * NOTE: to be a valid peak, all peakWindowAmount / 2 elements before and after selected value MUST be greater or equal then value.
 *
 * param[in]        dataBufferPtr           data buffer pointer.
 * param[in]        dataBufferAmount        data buffer elem amount.
 * param[out]       resPtr                  min value result pointer.
 * param[out]       resIdxPtr               min value result array index pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCMathU8ArrayMinPeak(
        const   uint8_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   uint16_t            peakWindowAmount,
                uint8_t*    const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathU16ArrayMinPeak(
        const   uint16_t*   const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   uint16_t            peakWindowAmount,
                uint16_t*   const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathU32ArrayMinPeak(
        const   uint32_t*   const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   uint16_t            peakWindowAmount,
                uint32_t*   const   resPtr,
                uint16_t*   const   resIdxPtr);

tommRoC_err_enum_t tommRoCMathI8ArrayMinPeak(
        const   int8_t*     const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   uint16_t            peakWindowAmount,
                int8_t*     const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathI16ArrayMinPeak(
        const   int16_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   uint16_t            peakWindowAmount,
                int16_t*    const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathI32ArrayMinPeak(
        const   int32_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   uint16_t            peakWindowAmount,
                int32_t*    const   resPtr,
                uint16_t*   const   resIdxPtr);

tommRoC_err_enum_t tommRoCMathFloatArrayMinPeak(
        const   float*      const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   uint16_t            peakWindowAmount,
                float*      const   resPtr,
                uint16_t*   const   resIdxPtr);

/**
 * Get first maximum peak (with threshold) value of uintx_t/intx_t/float array.
 * NOTE: to be a valid peak, value MUST be greater than threshold and all peakWindowAmount / 2 elements before and after selected value MUST be less or equal then value.
 *
 * param[in]        dataBufferPtr           data buffer pointer.
 * param[in]        dataBufferAmount        data buffer elem amount.
 * param[in]        thresholdValue          threshold value.
 * param[out]       resPtr                  min value result pointer.
 * param[out]       resIdxPtr               min value result array index pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCMathU8ArrayMaxPeakWithThs(
        const   uint8_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   uint8_t             thresholdValue,
        const   uint16_t            peakWindowAmount,
                uint8_t*    const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathU16ArrayMaxPeakWithThs(
        const   uint16_t*   const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   uint16_t            thresholdValue,
        const   uint16_t            peakWindowAmount,
                uint16_t*   const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathU32ArrayMaxPeakWithThs(
        const   uint32_t*   const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   uint32_t            thresholdValue,
        const   uint16_t            peakWindowAmount,
                uint32_t*   const   resPtr,
                uint16_t*   const   resIdxPtr);

tommRoC_err_enum_t tommRoCMathI8ArrayMaxPeakWithThs(
        const   int8_t*     const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   int8_t              thresholdValue,
        const   uint16_t            peakWindowAmount,
                int8_t*     const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathI16ArrayMaxPeakWithThs(
        const   int16_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   int16_t             thresholdValue,
        const   uint16_t            peakWindowAmount,
                int16_t*    const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathI32ArrayMaxPeakWithThs(
        const   int32_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   int32_t             thresholdValue,
        const   uint16_t            peakWindowAmount,
                int32_t*    const   resPtr,
                uint16_t*   const   resIdxPtr);

tommRoC_err_enum_t tommRoCMathFloatArrayMaxPeakWithThs(
        const   float*      const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   float               thresholdValue,
        const   uint16_t            peakWindowAmount,
                float*      const   resPtr,
                uint16_t*   const   resIdxPtr);

/**
 * Get first minimum peak (with threshold) value of uintx_t/intx_t/float array.
 * NOTE: to be a valid peak, value MUST be less than threshold and all peakWindowAmount / 2 elements before and after selected value MUST be greater or equal then value.
 *
 * param[in]        dataBufferPtr           data buffer pointer.
 * param[in]        dataBufferAmount        data buffer elem amount.
 * param[in]        thresholdValue          threshold value.
 * param[out]       resPtr                  min value result pointer.
 * param[out]       resIdxPtr               min value result array index pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCMathU8ArrayMinPeakWithThs(
        const   uint8_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   uint8_t             thresholdValue,
        const   uint16_t            peakWindowAmount,
                uint8_t*    const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathU16ArrayMinPeakWithThs(
        const   uint16_t*   const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   uint16_t            thresholdValue,
        const   uint16_t            peakWindowAmount,
                uint16_t*   const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathU32ArrayMinPeakWithThs(
        const   uint32_t*   const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   uint32_t            thresholdValue,
        const   uint16_t            peakWindowAmount,
                uint32_t*   const   resPtr,
                uint16_t*   const   resIdxPtr);

tommRoC_err_enum_t tommRoCMathI8ArrayMinPeakWithThs(
        const   int8_t*     const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   int8_t              thresholdValue,
        const   uint16_t            peakWindowAmount,
                int8_t*     const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathI16ArrayMinPeakWithThs(
        const   int16_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   int16_t             thresholdValue,
        const   uint16_t            peakWindowAmount,
                int16_t*    const   resPtr,
                uint16_t*   const   resIdxPtr);
tommRoC_err_enum_t tommRoCMathI32ArrayMinPeakWithThs(
        const   int32_t*    const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   int32_t             thresholdValue,
        const   uint16_t            peakWindowAmount,
                int32_t*    const   resPtr,
                uint16_t*   const   resIdxPtr);

tommRoC_err_enum_t tommRoCMathFloatArrayMinPeakWithThs(
        const   float*      const   dataBufferPtr,
        const   uint16_t            dataBufferAmount,
        const   float               thresholdValue,
        const   uint16_t            peakWindowAmount,
                float*      const   resPtr,
                uint16_t*   const   resIdxPtr);

/**
 * Get whole (pre decimal point part)/decimal (post decimal point part) of float param.
 *
 * param[in]        value                   value.
 *
 * return float
 */
float tommRoCMathFloatWholePart(const float value);
float tommRoCMathFloatDecimalPart(const float value);

/**
 * Square root of float param.
 * NOTE: function accuracy level is TOMMROC_MATH_FLOAT_SQUARE_ROOT_ACCURACY_LEVEL.
 *
 * param[in]        value                   value.
 *
 * return float
 */
float tommRoCMathFloatSqrt(const float value);

/**
 * Returns the value of number rounded to the nearest integer.
 *
 * param[in]        value                   value.
 *
 * return float
 */
float tommRoCMathFloatRound(const float value);

/**
 * Returns number up to the next largest integer.
 *
 * param[in]        value                   value.
 *
 * return float
 */
float tommRoCMathFloatCeil(const float value);

/**
 * Returns largest integer less than or equal to a given number.
 *
 * param[in]        value                   value.
 *
 * return float
 */
float tommRoCMathFloatFloor(const float value);

/**
 * Trigonometric functions float param.
 *
 * param[in]        value(s)                value(s) [radian for angle].
 *
 * return float
 */
float tommRoCMathFloatCos(const float value);
float tommRoCMathFloatSin(const float value);
float tommRoCMathFloatTan(const float value);

float tommRoCMathFloatAcos(const float value);
float tommRoCMathFloatAsin(const float value);
float tommRoCMathFloatAtan(const float value);
float tommRoCMathFloatAtan2(const float value1, const float value2);    // NOTE: atan2(y,x)=atan(y/x)

/**
 * @}
 */

#endif
