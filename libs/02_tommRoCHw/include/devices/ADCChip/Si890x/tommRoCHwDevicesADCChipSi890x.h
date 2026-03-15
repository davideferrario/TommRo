
#ifndef TOMMROC_HW_DEVICES_ADC_CHIP_SI890x_H_
#define TOMMROC_HW_DEVICES_ADC_CHIP_SI890x_H_

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
#define TOMMROC_HW_DEVICES_ADC_CHIP_SI890x_I2C_7_BIT_ADDRESS    (0b1111000)


typedef enum {

    // ADC analog input channel 0.
    TOMMROC_HW_DEVICES_ADC_CHIP_SI890x_CHANNEL_AIN0 = 0,

    // ADC analog input channel 1.
    TOMMROC_HW_DEVICES_ADC_CHIP_SI890x_CHANNEL_AIN1,

    // ADC analog input channel 2.
    TOMMROC_HW_DEVICES_ADC_CHIP_SI890x_CHANNEL_AIN2,

} tommRoC_hw_devices_adc_chip_si890x_channel_enum_t;

/*******************************************************************************
 * typedefs
 ******************************************************************************/

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
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipSi890xInitI2C(
        const   uint8_t                                                     i2c7BitSlaveAddress,
        const   tommRoC_hw_bus_t*                                   const   busHandlerPtr,
        const   tommRoC_guard_t*                                    const   guardPtr,
                tommRoC_hw_bus_device_specific_i2c_slave_t*         const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Init bus device as for SPI master bus.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        chipSelect              chip select function pointer.
 * param[in]        chipDeSelect            chip de-select function pointer.
 * param[in]        busHandlerPtr           bus pointer.
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[out]       specificSlavePtr        output specific SPI slave pointer [needed as static because linked by bus device].
 * param[out]       busDevicePtr            output bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipSi890xInitSPI(
        const   tommRoC_hw_gpio_set_cb_t                                    chipSelect,
        const   tommRoC_hw_gpio_set_cb_t                                    chipDeSelect,
        const   tommRoC_hw_bus_t*                                   const   busHandlerPtr,
        const   tommRoC_guard_t*                                    const   guardPtr,
                tommRoC_hw_bus_device_specific_spi_slave_t*         const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipSi890xStart(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Read ADC [raw] value.
 * NOTE: the reading is done in Demand Mode.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        channel                 ADC channel.
 * param[out]       valuePtr                output value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipSi890xGetADC(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   tommRoC_hw_devices_adc_chip_si890x_channel_enum_t           channel,
                uint16_t*                                           const   valuePtr);

#endif
