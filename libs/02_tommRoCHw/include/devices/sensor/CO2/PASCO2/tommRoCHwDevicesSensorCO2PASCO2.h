
#ifndef TOMMROC_HW_DEVICES_SENSOR_CO2_PASCO2_H_
#define TOMMROC_HW_DEVICES_SENSOR_CO2_PASCO2_H_

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
#include "tommRoCHwBus.h"
#include "tommRoCHwBusDevice.h"
#include "tommRoCHwErr.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Compatible device I2C addresses.
#define TOMMROC_HW_DEVICES_SENSOR_CO2_PASCO2_I2C_7_BIT_ADDRESS  (0b0101000)

// Minimum/Maximum measurement period when the device is working in continuous mode.
#define TOMMROC_HW_DEVICES_SENSOR_CO2_PASCO2_OP_MODE_CONTINUOUS_MEAS_PERIOD_MIN_SEC (5)
#define TOMMROC_HW_DEVICES_SENSOR_CO2_PASCO2_OP_MODE_CONTINUOUS_MEAS_PERIOD_MAX_SEC (4095)


// Device data.
#if defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_8_BIT_SIZE)
#define TOMMROC_HW_DEVICES_SENSOR_CO2_PASCO2_DEVICE_DATA_SIZE   ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_16_BIT_SIZE)
#define TOMMROC_HW_DEVICES_SENSOR_CO2_PASCO2_DEVICE_DATA_SIZE   ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE)
#define TOMMROC_HW_DEVICES_SENSOR_CO2_PASCO2_DEVICE_DATA_SIZE   (16)
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE)
#define TOMMROC_HW_DEVICES_SENSOR_CO2_PASCO2_DEVICE_DATA_SIZE   (32)
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef enum {

    /**
     * NOTE: from datasheet.
     * The sensor module supports three operating modes:
     * - Idle mode: the device does not perform any CO2 concentration measurement.
     * - Continuous mode: the device periodically triggers a CO2 concentration measurement sequence. Measurement period is programmable from 5 s to 4095 s
     * - Single-shot mode: the device triggers a single measurement sequence.
     */

    TOMMROC_HW_DEVICES_SENSOR_CO2_PASCO2_OP_MODE_IDLE = 0,
    TOMMROC_HW_DEVICES_SENSOR_CO2_PASCO2_OP_MODE_CONTINUOUS,
    TOMMROC_HW_DEVICES_SENSOR_CO2_PASCO2_OP_MODE_SINGLE_SHOT,

} tommRoC_hw_devices_sensor_co2_pasco2_op_mode_enum_t;

typedef struct {

    tommRoC_hw_devices_sensor_co2_pasco2_op_mode_enum_t opMode;
    uint16_t measRateSec;   // Measurement rate to apply in case of continuous mode [5-4095 sec]

} tommRoC_hw_devices_sensor_co2_pasco2_config_t;

#define __EMPTY_tommRoC_hw_devices_sensor_co2_pasco2_config_t__                                         \
{                                                                                                       \
    /* .opMode */       TOMMROC_HW_DEVICES_SENSOR_CO2_PASCO2_OP_MODE_SINGLE_SHOT,                       \
    /* .measRateSec */  TOMMROC_HW_DEVICES_SENSOR_CO2_PASCO2_OP_MODE_CONTINUOUS_MEAS_PERIOD_MIN_SEC,    \
}


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_SENSOR_CO2_PASCO2_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_sensor_co2_pasco2_device_data_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init bus device as for I2C master bus.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        i2c7BitSlaveAddress     I2C 7 bit slave address.
 * param[in]        busHandlerPtr           bus pointer.
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[out]       specificSlavePtr        output specific I2C slave pointer [needed as static because linked by bus device].
 * param[out]       busDevicePtr            output bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorCO2PASCO2InitI2C(
        const   uint8_t                                                     i2c7BitSlaveAddress,
        const   tommRoC_hw_bus_t*                                   const   busHandlerPtr,
        const   tommRoC_guard_t*                                    const   guardPtr,
                tommRoC_hw_bus_device_specific_i2c_slave_t*         const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Init bus device as for UART bus.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        busHandlerPtr           bus pointer.
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[out]       specificPtr             output specific UART pointer [needed as static because linked by bus device].
 * param[out]       busDevicePtr            output bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorCO2PASCO2InitUART(
        const   tommRoC_hw_bus_t*                                   const   busHandlerPtr,
        const   tommRoC_guard_t*                                    const   guardPtr,
                tommRoC_hw_bus_device_specific_uart_t*              const   specificPtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorCO2PASCO2AttachDeviceData(
        const   tommRoC_hw_devices_sensor_co2_pasco2_device_data_t* const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        configPtr               chip configuration pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorCO2PASCO2Start(
        const   tommRoC_hw_devices_sensor_co2_pasco2_config_t*      const   configPtr,
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Get CO2 ppm value.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       co2ppmPtr               output CO2 [ppm] pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorCO2PASCO2Get(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
                tommRoC_unit_measure_co2_ppm_t*                     const   co2ppmPtr);

#endif
