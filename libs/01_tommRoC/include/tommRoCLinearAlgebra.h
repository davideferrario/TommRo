
#ifndef TOMMROC_LINEAR_ALGEBRA_H_
#define TOMMROC_LINEAR_ALGEBRA_H_

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
 * @defgroup tommRoCLinearAlgebra tommRoCLinearAlgebra
 *
 * @brief  TommRoC library linear algebra module
 * @author TommRo Software Department
 *
 * This module is providing linear algebra functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "linearAlgebra/tommRoCLinearAlgebra2Dim.h"
#include "linearAlgebra/tommRoCLinearAlgebra3Dim.h"

#include "tommRoCErr.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/**
 * NOTE:
 * The compiler will allocate the memory for two dimensional array row-wise.
 * This mean that the first element of the second row will be placed after the last element of the first row.
 *
 * int num[3][4] = {
 *  { 10, 11, 12, 13 },
 *  { 14, 15, 16, 17 },
 *  { 18, 19, 20, 21 },
 * };
 *                  row-wise memory allocation
 * | <---- row 0 ----> | <---- row 1 ----> | <---- row 2 ----> |
 * | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 |
 */

typedef float tommRoC_linear_algebra_matrix_1x1_t[1][1];    // 1 row/1 column
#define __EMPTY_tommRoC_linear_algebra_matrix_1x1_t__   { { 0.0f, }, }
typedef float tommRoC_linear_algebra_matrix_1x2_t[1][2];    // 1 row/2 columns
#define __EMPTY_tommRoC_linear_algebra_matrix_1x2_t__   { { 0.0f, 0.0f, }, }
typedef float tommRoC_linear_algebra_matrix_1x3_t[1][3];    // 1 row/3 columns
#define __EMPTY_tommRoC_linear_algebra_matrix_1x3_t__   { { 0.0f, 0.0f, 0.0f, }, }

typedef float tommRoC_linear_algebra_matrix_2x1_t[2][1];    // 2 row/1 column
#define __EMPTY_tommRoC_linear_algebra_matrix_2x1_t__   { { 0.0f, }, { 0.0f, }, }
typedef float tommRoC_linear_algebra_matrix_2x2_t[2][2];    // 2 row/2 columns
#define __EMPTY_tommRoC_linear_algebra_matrix_2x2_t__   { { 0.0f, 0.0f, }, { 0.0f, 0.0f, }, }
typedef float tommRoC_linear_algebra_matrix_2x3_t[2][3];    // 2 row/3 columns
#define __EMPTY_tommRoC_linear_algebra_matrix_2x3_t__   { { 0.0f, 0.0f, 0.0f, }, { 0.0f, 0.0f, 0.0f, }, }

typedef float tommRoC_linear_algebra_matrix_3x1_t[3][1];    // 3 row/1 column
#define __EMPTY_tommRoC_linear_algebra_matrix_3x1_t__   { { 0.0f, }, { 0.0f, }, { 0.0f, }, }
typedef float tommRoC_linear_algebra_matrix_3x2_t[3][2];    // 3 row/2 column
#define __EMPTY_tommRoC_linear_algebra_matrix_3x2_t__   { { 0.0f, 0.0f, }, { 0.0f, 0.0f, }, { 0.0f, 0.0f, }, }
typedef float tommRoC_linear_algebra_matrix_3x3_t[3][3];    // 3 row/3 columns
#define __EMPTY_tommRoC_linear_algebra_matrix_3x3_t__   { { 0.0f, 0.0f, 0.0f, }, { 0.0f, 0.0f, 0.0f, }, { 0.0f, 0.0f, 0.0f, }, }

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Matrix sum.
 *
 * param[in]        matrix1                 matrix sum operator.
 * param[in]        matrix2                 matrix sum operator.
 * param[out]       matrixResult            matrix result.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix1x1Sum(
        const   tommRoC_linear_algebra_matrix_1x1_t matrix1,
        const   tommRoC_linear_algebra_matrix_1x1_t matrix2,
                tommRoC_linear_algebra_matrix_1x1_t matrixResult);
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix1x2Sum(
        const   tommRoC_linear_algebra_matrix_1x2_t matrix1,
        const   tommRoC_linear_algebra_matrix_1x2_t matrix2,
                tommRoC_linear_algebra_matrix_1x2_t matrixResult);
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix1x3Sum(
        const   tommRoC_linear_algebra_matrix_1x3_t matrix1,
        const   tommRoC_linear_algebra_matrix_1x3_t matrix2,
                tommRoC_linear_algebra_matrix_1x3_t matrixResult);

tommRoC_err_enum_t tommRoCLinearAlgebraMatrix2x1Sum(
        const   tommRoC_linear_algebra_matrix_2x1_t matrix1,
        const   tommRoC_linear_algebra_matrix_2x1_t matrix2,
                tommRoC_linear_algebra_matrix_2x1_t matrixResult);
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix2x2Sum(
        const   tommRoC_linear_algebra_matrix_2x2_t matrix1,
        const   tommRoC_linear_algebra_matrix_2x2_t matrix2,
                tommRoC_linear_algebra_matrix_2x2_t matrixResult);
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix2x3Sum(
        const   tommRoC_linear_algebra_matrix_2x3_t matrix1,
        const   tommRoC_linear_algebra_matrix_2x3_t matrix2,
                tommRoC_linear_algebra_matrix_2x3_t matrixResult);

tommRoC_err_enum_t tommRoCLinearAlgebraMatrix3x1Sum(
        const   tommRoC_linear_algebra_matrix_3x1_t matrix1,
        const   tommRoC_linear_algebra_matrix_3x1_t matrix2,
                tommRoC_linear_algebra_matrix_3x1_t matrixResult);
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix3x2Sum(
        const   tommRoC_linear_algebra_matrix_3x2_t matrix1,
        const   tommRoC_linear_algebra_matrix_3x2_t matrix2,
                tommRoC_linear_algebra_matrix_3x2_t matrixResult);
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix3x3Sum(
        const   tommRoC_linear_algebra_matrix_3x3_t matrix1,
        const   tommRoC_linear_algebra_matrix_3x3_t matrix2,
                tommRoC_linear_algebra_matrix_3x3_t matrixResult);


/**
 * Matrix multiplication for a factor.
 *
 * param[in]        matrix                  matrix operator.
 * param[in]        factor                  multiplication factor.
 * param[out]       matrixResult            matrix result.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix1x1FactorMul(
        const   tommRoC_linear_algebra_matrix_1x1_t matrix,
        const   float                               factor,
                tommRoC_linear_algebra_matrix_1x1_t matrixResult);
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix1x2FactorMul(
        const   tommRoC_linear_algebra_matrix_1x2_t matrix,
        const   float                               factor,
                tommRoC_linear_algebra_matrix_1x2_t matrixResult);
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix1x3FactorMul(
        const   tommRoC_linear_algebra_matrix_1x3_t matrix,
        const   float                               factor,
                tommRoC_linear_algebra_matrix_1x3_t matrixResult);

tommRoC_err_enum_t tommRoCLinearAlgebraMatrix2x1FactorMul(
        const   tommRoC_linear_algebra_matrix_2x1_t matrix,
        const   float                               factor,
                tommRoC_linear_algebra_matrix_2x1_t matrixResult);
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix2x2FactorMul(
        const   tommRoC_linear_algebra_matrix_2x2_t matrix,
        const   float                               factor,
                tommRoC_linear_algebra_matrix_2x2_t matrixResult);
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix2x3FactorMul(
        const   tommRoC_linear_algebra_matrix_2x3_t matrix,
        const   float                               factor,
                tommRoC_linear_algebra_matrix_2x3_t matrixResult);

tommRoC_err_enum_t tommRoCLinearAlgebraMatrix3x1FactorMul(
        const   tommRoC_linear_algebra_matrix_3x1_t matrix,
        const   float                               factor,
                tommRoC_linear_algebra_matrix_3x1_t matrixResult);
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix3x2FactorMul(
        const   tommRoC_linear_algebra_matrix_3x2_t matrix,
        const   float                               factor,
                tommRoC_linear_algebra_matrix_3x2_t matrixResult);
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix3x3FactorMul(
        const   tommRoC_linear_algebra_matrix_3x3_t matrix,
        const   float                               factor,
                tommRoC_linear_algebra_matrix_3x3_t matrixResult);


/**
 * Matrix multiplication.
 *
 * param[in]        matrix1                 matrix multiplication operator.
 * param[in]        matrix2                 matrix multiplication operator.
 * param[out]       matrixResult            matrix result.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix1x1Mul(
        const   tommRoC_linear_algebra_matrix_1x1_t matrix1,
        const   tommRoC_linear_algebra_matrix_1x1_t matrix2,
                tommRoC_linear_algebra_matrix_1x1_t matrixResult);
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix2x2Mul(
        const   tommRoC_linear_algebra_matrix_2x2_t matrix1,
        const   tommRoC_linear_algebra_matrix_2x2_t matrix2,
                tommRoC_linear_algebra_matrix_2x2_t matrixResult);
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix3x3Mul(
        const   tommRoC_linear_algebra_matrix_3x3_t matrix1,
        const   tommRoC_linear_algebra_matrix_3x3_t matrix2,
                tommRoC_linear_algebra_matrix_3x3_t matrixResult);

tommRoC_err_enum_t tommRoCLinearAlgebraMatrix1x22x1Mul(
        const   tommRoC_linear_algebra_matrix_1x2_t matrix1,
        const   tommRoC_linear_algebra_matrix_2x1_t matrix2,
                tommRoC_linear_algebra_matrix_1x1_t matrixResult);
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix1x33x1Mul(
        const   tommRoC_linear_algebra_matrix_1x3_t matrix1,
        const   tommRoC_linear_algebra_matrix_3x1_t matrix2,
                tommRoC_linear_algebra_matrix_1x1_t matrixResult);

tommRoC_err_enum_t tommRoCLinearAlgebraMatrix2x11x2Mul(
        const   tommRoC_linear_algebra_matrix_2x1_t matrix1,
        const   tommRoC_linear_algebra_matrix_1x2_t matrix2,
                tommRoC_linear_algebra_matrix_2x2_t matrixResult);
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix2x22x1Mul(
        const   tommRoC_linear_algebra_matrix_2x2_t matrix1,
        const   tommRoC_linear_algebra_matrix_2x1_t matrix2,
                tommRoC_linear_algebra_matrix_2x1_t matrixResult);
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix2x33x2Mul(
        const   tommRoC_linear_algebra_matrix_2x3_t matrix1,
        const   tommRoC_linear_algebra_matrix_3x2_t matrix2,
                tommRoC_linear_algebra_matrix_2x2_t matrixResult);

tommRoC_err_enum_t tommRoCLinearAlgebraMatrix3x11x3Mul(
        const   tommRoC_linear_algebra_matrix_3x1_t matrix1,
        const   tommRoC_linear_algebra_matrix_1x3_t matrix2,
                tommRoC_linear_algebra_matrix_3x3_t matrixResult);
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix3x22x3Mul(
        const   tommRoC_linear_algebra_matrix_3x2_t matrix1,
        const   tommRoC_linear_algebra_matrix_2x3_t matrix2,
                tommRoC_linear_algebra_matrix_3x3_t matrixResult);
tommRoC_err_enum_t tommRoCLinearAlgebraMatrix3x33x1Mul(
        const   tommRoC_linear_algebra_matrix_3x3_t matrix1,
        const   tommRoC_linear_algebra_matrix_3x1_t matrix2,
                tommRoC_linear_algebra_matrix_3x1_t matrixResult);

/**
 * @}
 */

#endif
