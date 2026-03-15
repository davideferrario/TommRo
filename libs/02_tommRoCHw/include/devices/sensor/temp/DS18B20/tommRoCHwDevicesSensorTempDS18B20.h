
#ifndef TOMMROC_HW_DEVICES_SENSOR_TEMP_DS18B20_H_
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_DS18B20_H_

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
#include "tommRoCHwErr.h"
#include "tommRoCHwOneWire.h"
#include "tommRoCHwOneWireDevice.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init one wire device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        oneWirePtr              one wire handle pointer.
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[out]       oneWireDevicePtr        output one wire device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempDS18B20InitOneWire(
        const   tommRoC_hw_one_wire_t*                      const   oneWirePtr,
        const   tommRoC_guard_t*                            const   guardPtr,
                tommRoC_hw_one_wire_device_t*               const   oneWireDevicePtr);

/**
 * Start chip.
 *
 * param[in]        oneWireDevicePtr        one wire device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempDS18B20Start(
        const   tommRoC_hw_one_wire_device_t*               const   oneWireDevicePtr);

/**
 * Get temperature.
 *
 * param[in]        oneWireDevicePtr        one wire device pointer.
 * param[out]       valuePtr                output temperature pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempDS18B20GetT(
        const   tommRoC_hw_one_wire_device_t*               const   oneWireDevicePtr,
                tommRoC_unit_measure_temperature_celsius_t* const   valuePtr);

#endif
