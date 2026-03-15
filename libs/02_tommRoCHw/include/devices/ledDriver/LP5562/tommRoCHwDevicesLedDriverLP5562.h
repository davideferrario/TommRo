
#ifndef TOMMROC_HW_DEVICES_LED_DRIVER_LP5562_H_
#define TOMMROC_HW_DEVICES_LED_DRIVER_LP5562_H_

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
#define TOMMROC_HW_DEVICES_LED_DRIVER_LP5562_I2C_7_BIT_ADDRESS_ADDRSEL1_ADDRSEL0_PIN_GND_GND    (0b0110000)
#define TOMMROC_HW_DEVICES_LED_DRIVER_LP5562_I2C_7_BIT_ADDRESS_ADDRSEL1_ADDRSEL0_PIN_GND_VDD    (0b0110001)
#define TOMMROC_HW_DEVICES_LED_DRIVER_LP5562_I2C_7_BIT_ADDRESS_ADDRSEL1_ADDRSEL0_PIN_VDD_GND    (0b0110010)
#define TOMMROC_HW_DEVICES_LED_DRIVER_LP5562_I2C_7_BIT_ADDRESS_ADDRSEL1_ADDRSEL0_PIN_VDD_VDD    (0b0110011)

// Maximum step delay parameter for SetRamp function (63 * 15.6 msec = 982,8 see datasheet)
#define TOMMROC_HW_DEVICES_LED_DRIVER_LP5562_MAX_STEP_DELAY_MSEC    (983)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef enum {

    TOMMROC_HW_DEVICES_LED_DRIVER_LP5562_LED_B = 0,
    TOMMROC_HW_DEVICES_LED_DRIVER_LP5562_LED_G,
    TOMMROC_HW_DEVICES_LED_DRIVER_LP5562_LED_R,
    TOMMROC_HW_DEVICES_LED_DRIVER_LP5562_LED_W,

} tommRoC_hw_devices_led_driver_lp5562_leds_enum_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesLedDriverLP5562InitI2C(
        const   uint8_t                                             i2c7BitSlaveAddress,
        const   tommRoC_hw_bus_t*                           const   busHandlerPtr,
        const   tommRoC_guard_t*                            const   guardPtr,
                tommRoC_hw_bus_device_specific_i2c_slave_t* const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                    const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesLedDriverLP5562Start(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr);

/**
 * Set current/PWM of a single led (parameters are passed as raw).
 * NOTE:
 * Input parameters range is [0, 255].
 * LED driver output current can be programmed from 0mA up to 25.5mA. Current setting resolution is 25.5mA/255 = 100uA (8-bit control).
 * LED driver output PWM can be programmed from 0% up to 100%. PWM setting resolution is 100%/255 (8-bit control).
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        led                     selected led.
 * param[in]        currentRaw              current raw value [0, 255].
 * param[in]        pwmRaw                  PWM raw value [0, 255].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesLedDriverLP5562SetRaw(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   tommRoC_hw_devices_led_driver_lp5562_leds_enum_t            led,
        const   uint8_t                                                     currentRaw,
        const   uint8_t                                                     pwmRaw);

/**
 * Setup a ramp program for one or more leds.
 * NOTE:
 * Ramp is PWM related.
 * PWM starts from minimum value and reach maximum value.
 * If stay in PWM max value delay not 0, a delay is executed with PWM max value.
 * PWM decrease until reach minimum value.
 * If stay in PWM min value delay not 0, a delay is executed with PWM min value.
 * The cycle as infinite loop.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        ledsPtr                 selected led array pointer.
 * param[in]        ledsAmount              selected led array element amount.
 * param[in]        currentRaw              current raw value [0, 255].
 * param[in]        pwmRawMin               PWM raw minimum (starting) value [0, 255].
 * param[in]        pwmRawMax               PWM raw maximum value [0, 255].
 * param[in]        stepDelayMsec           delay between single PWM update [msec].
 * param[in]        stayInPWMMinMsec        stay in PWM minimum value delay [msec] (0 if none).
 * param[in]        stayInPWMMaxMsec        stay in PWM maximum value delay [msec] (0 if none).
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesLedDriverLP5562SetRamp(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   tommRoC_hw_devices_led_driver_lp5562_leds_enum_t*   const   ledsPtr,
        const   uint8_t                                                     ledsAmount,
        const   uint8_t                                                     currentRaw,
        const   uint8_t                                                     pwmRawMin,
        const   uint8_t                                                     pwmRawMax,
        const   uint32_t                                                    stepDelayMsec,
        const   uint32_t                                                    stayInPWMMinMsec,
        const   uint32_t                                                    stayInPWMMaxMsec);

#endif
