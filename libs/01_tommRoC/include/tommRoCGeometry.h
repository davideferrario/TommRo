
#ifndef TOMMROC_GEOMETRY_H_
#define TOMMROC_GEOMETRY_H_

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
 * @defgroup tommRoCGeometry tommRoCGeometry
 *
 * @brief  TommRoC library geometry module
 * @author TommRo Software Department
 *
 * This module is providing geometry functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCUnitMeasure.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC geometry 3 axes vector float structure.
typedef struct {

    /**
     * NOTE: every axis is in natural signed float format.
     */
    float   xAxis;
    float   yAxis;
    float   zAxis;

} tommRoC_geometry_vector_t;

#define __EMPTY_tommRoC_geometry_vector_t__ \
{                                           \
    /* .xAxis */    0.0f,                   \
    /* .yAxis */    0.0f,                   \
    /* .zAxis */    0.0f,                   \
}


// tommRoC geometry 3 axes signed 16-bit vector structure.
typedef struct {

    /**
     * NOTE: every axis is in signed 16-bit format [value * 1000].
     */
    int16_t xAxis;
    int16_t yAxis;
    int16_t zAxis;

} tommRoC_geometry_vector_16bit_t;

#define __EMPTY_tommRoC_geometry_vector_16bit_t__   \
{                                                   \
    /* .xAxis */    ((int16_t) 0),                  \
    /* .yAxis */    ((int16_t) 0),                  \
    /* .zAxis */    ((int16_t) 0),                  \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Get module of a 3 axes vector.
 *
 * param[in]        vectorPtr               geometry 3 axes vector pointer.
 *
 * return float
 */
float tommRoCGeometryVectorModule(const tommRoC_geometry_vector_t* const vectorPtr);

/**
 * Get module of a 3 axes signed 16-bit vector.
 *
 * param[in]        vector16BitPtr          geometry 3 axes signed 16-bit vector pointer.
 *
 * return uint32_t
 */
uint32_t tommRoCGeometryVector16BitModule(const tommRoC_geometry_vector_16bit_t* const vector16BitPtr);

/**
 * 3 axes vector rotation.
 *
 * param[in]        vectorPtr               geometry 3 axes vector pointer.
 * param[in]        angleX                  counterclockwise angle of rotation over X axis [radian].
 * param[in]        angleX                  counterclockwise angle of rotation over Y axis [radian].
 * param[in]        angleX                  counterclockwise angle of rotation over Z axis [radian].
 * param[out]       vectorResultPtr         geometry 3 axes vector result pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCGeometryVectorRotate(
        const   tommRoC_geometry_vector_t*              const   vectorPtr,
        const   tommRoC_unit_measure_angle_radian_t             angleX,
        const   tommRoC_unit_measure_angle_radian_t             angleY,
        const   tommRoC_unit_measure_angle_radian_t             angleZ,
                tommRoC_geometry_vector_t*              const   vectorResultPtr);

/**
 * Get scalar product of two 3 axes vector.
 *
 * param[in]        vector1Ptr              geometry 3 axes first vector pointer.
 * param[in]        vector2Ptr              geometry 3 axes second vector pointer.
 *
 * return float
 */
float tommRoCGeometryVectorScalarProduct(
        const   tommRoC_geometry_vector_t*              const   vector1Ptr,
        const   tommRoC_geometry_vector_t*              const   vector2Ptr);

/**
 * Get angle between two 3 axes vector.
 *
 * param[in]        vector1Ptr              geometry 3 axes first vector pointer.
 * param[in]        vector2Ptr              geometry 3 axes second vector pointer.
 *
 * return tommRoC_unit_measure_angle_radian_t
 */
tommRoC_unit_measure_angle_radian_t tommRoCGeometryVectorAngle(
        const   tommRoC_geometry_vector_t*              const   vector1Ptr,
        const   tommRoC_geometry_vector_t*              const   vector2Ptr);

/**
 * Get vector product between two 3 axes vector.
 * NOTE: result vector (n) is normal to both the input vector (a and b) such that a, b, and n form a right-handed triplet.
 *
 * param[in]        vector1Ptr              geometry 3 axes first vector pointer.
 * param[in]        vector2Ptr              geometry 3 axes second vector pointer.
 * param[out]       vectorProductPtr        output geometry 3 axes vector product pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCGeometryVectorVectorProduct(
        const   tommRoC_geometry_vector_t*              const   vector1Ptr,
        const   tommRoC_geometry_vector_t*              const   vector2Ptr,
                tommRoC_geometry_vector_t*              const   vectorProductPtr);

/**
 * Get roll/pitch angles of a 3 axes accelerometer vector.
 *
 * NOTE: from application note.
 * The device coordinates X/Y/Z are defined as forward/right/down based on the right-hand rule.
 *
 * Roll is defined as the angle between the Y axis and the horizontal plane.
 * When rotating the device around the X axis with the Y axis moving downwards, roll is positive and increasing.
 *
 * Pitch is defined as the angle between the X axis and the horizontal plane.
 * When rotating the device around the Y axis with the X axis moving upwards, pitch is positive and increasing.
 *
 * param[in]        vectorGravityPtr        geometry 3 axes accelerometer vector pointer.
 * param[out]       pitchAnglePtr           pitch angle pointer.
 * param[out]       rollAnglePtr            roll angle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCGeometryGetRollPitchAngles(
        const   tommRoC_geometry_vector_t*              const   vectorGravityPtr,
                tommRoC_unit_measure_angle_radian_t*    const   rollAnglePtr,
                tommRoC_unit_measure_angle_radian_t*    const   pitchAnglePtr);

/**
 * Get attitude angles (heading, pitch and roll) of a 3 axes accelerometer/compass vector.
 *
 * NOTE: from application note.
 * The device coordinates X/Y/Z are defined as forward/right/down based on the right-hand rule.
 * Three attitude angles are referenced to the local horizontal plane which is perpendicular to earth’s gravity.
 *
 * Heading is defined as the angle between the X axis and the magnetic north on the horizontal plane measured in a clockwise direction
 * when viewing from the top of the device.
 *
 * Pitch is defined as the angle between the X axis and the horizontal plane.
 * When rotating the device around the Y axis with the X axis moving upwards, pitch is positive and increasing.
 *
 * Roll is defined as the angle between the Y axis and the horizontal plane.
 * When rotating the device around the X axis with the Y axis moving downwards, roll is positive and increasing.
 *
 * param[in]        vectorGravityPtr        geometry 3 axes accelerometer vector pointer.
 * param[in]        vectorCompassPtr        geometry 3 axes compass vector pointer.
 * param[out]       headingAnglePtr         heading angle pointer.
 * param[out]       pitchAnglePtr           pitch angle pointer.
 * param[out]       rollAnglePtr            roll angle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCGeometryGetAttitudeAngles(
        const   tommRoC_geometry_vector_t*              const   vectorGravityPtr,
        const   tommRoC_geometry_vector_t*              const   vectorCompassPtr,
                tommRoC_unit_measure_angle_radian_t*    const   headingAnglePtr,
                tommRoC_unit_measure_angle_radian_t*    const   pitchAnglePtr,
                tommRoC_unit_measure_angle_radian_t*    const   rollAnglePtr);

/**
 * Get vector mean value of a 3 axes vector array.
 *
 * param[in]        vectorArrayPtr          geometry 3 axes vector array pointer.
 * param[in]        vectorArrayElemAmount   geometry 3 axes vector array elem amount.
 * param[out]       vectorResultPtr         geometry 3 axes vector mean result pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCGeometryVectorMean(
        const   tommRoC_geometry_vector_t*              const   vectorArrayPtr,
        const   uint16_t                                        vectorArrayElemAmount,
                tommRoC_geometry_vector_t*              const   vectorResultPtr);

/**
 * @}
 */

#endif
