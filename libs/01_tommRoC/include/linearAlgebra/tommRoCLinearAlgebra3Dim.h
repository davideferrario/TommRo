
#ifndef TOMMROC_LINEAR_ALGEBRA_3_DIM_H_
#define TOMMROC_LINEAR_ALGEBRA_3_DIM_H_

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
 * @defgroup tommRoCLinearAlgebra3Dim tommRoCLinearAlgebra3Dim
 *
 * @brief  TommRoC library three dimension linear algebra module
 * @author TommRo Software Department
 *
 * This module is providing three dimension linear algebra functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCUnitMeasure.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// 3 dimension vector.
typedef float tommRoC_linear_algebra_3_dim_vector_t[3];

#define __EMPTY_tommRoC_linear_algebra_3_dim_vector_t__ { 0.0f, 0.0f, 0.0f, }

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Get module of a 3 dimension vector.
 *
 * param[in]        vector                  3 dimension vector.
 *
 * return float
 */
float tommRoCLinearAlgebra3DimVectorModule(
        const   tommRoC_linear_algebra_3_dim_vector_t   vector);

/**
 * 3 dimension vector sum.
 *
 * param[in]        vector1                 vector sum operator.
 * param[in]        vector2                 vector sum operator.
 * param[out]       vectorResult            vector result.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLinearAlgebra3DimVectorSum(
        const   tommRoC_linear_algebra_3_dim_vector_t   vector1,
        const   tommRoC_linear_algebra_3_dim_vector_t   vector2,
                tommRoC_linear_algebra_3_dim_vector_t   vectorResult);

/**
 * 3 dimension vector multiplication for a factor.
 *
 * param[in]        vector                  vector operator.
 * param[in]        factor                  multiplication factor.
 * param[out]       vectorResult            vector result.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLinearAlgebra3DimVectorFactorMul(
        const   tommRoC_linear_algebra_3_dim_vector_t   vector,
        const   float                                   factor,
                tommRoC_linear_algebra_3_dim_vector_t   vectorResult);

/**
 * 3 dimension vector rotation.
 *
 * param[in]        vector                  vector operator.
 * param[in]        angleX                  counterclockwise angle of rotation over X axis [radian].
 * param[in]        angleX                  counterclockwise angle of rotation over Y axis [radian].
 * param[in]        angleX                  counterclockwise angle of rotation over Z axis [radian].
 * param[out]       vectorResult            vector result.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLinearAlgebra3DimVectorRotate(
        const   tommRoC_linear_algebra_3_dim_vector_t   vector,
        const   tommRoC_unit_measure_angle_radian_t     angleX,
        const   tommRoC_unit_measure_angle_radian_t     angleY,
        const   tommRoC_unit_measure_angle_radian_t     angleZ,
                tommRoC_linear_algebra_3_dim_vector_t   vectorResult);

/**
 * 3 dimension vector scalar product.
 *
 * param[in]        vector1                 vector scalar product operator.
 * param[in]        vector2                 vector scalar product operator.
 *
 * return float
 */
float tommRoCLinearAlgebra3DimVectorScalarProduct(
        const   tommRoC_linear_algebra_3_dim_vector_t   vector1,
        const   tommRoC_linear_algebra_3_dim_vector_t   vector2);

/**
 * Get angle between two 3 dimension vector.
 *
 * param[in]        vector1                 vector scalar product operator.
 * param[in]        vector2                 vector scalar product operator.
 *
 * return tommRoC_unit_measure_angle_radian_t
 */
tommRoC_unit_measure_angle_radian_t tommRoCLinearAlgebra3DimVectorAngle(
        const   tommRoC_linear_algebra_3_dim_vector_t   vector1,
        const   tommRoC_linear_algebra_3_dim_vector_t   vector2);

/**
 * 3 dimension vector product.
 * NOTE: vector product is significative only in 3 dimension
 *
 * param[in]        vector1                 vector product operator.
 * param[in]        vector2                 vector product operator.
 * param[out]       vectorResult            vector result.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLinearAlgebra3DimVectorProduct(
        const   tommRoC_linear_algebra_3_dim_vector_t   vector1,
        const   tommRoC_linear_algebra_3_dim_vector_t   vector2,
                tommRoC_linear_algebra_3_dim_vector_t   vectorResult);

/**
 * @}
 */

#endif
