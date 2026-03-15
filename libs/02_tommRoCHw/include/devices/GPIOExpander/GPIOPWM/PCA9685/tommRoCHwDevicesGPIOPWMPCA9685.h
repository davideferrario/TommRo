
#ifndef TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_H_
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_H_

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
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_00    (0b1000000)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_01    (0b1000001)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_02    (0b1000010)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_03    (0b1000011)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_04    (0b1000100)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_05    (0b1000101)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_06    (0b1000110)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_07    (0b1000111)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_08    (0b1001000)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_09    (0b1001001)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_0A    (0b1001010)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_0B    (0b1001011)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_0C    (0b1001100)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_0D    (0b1001101)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_0E    (0b1001110)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_0F    (0b1001111)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_10    (0b1010000)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_11    (0b1010001)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_12    (0b1010010)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_13    (0b1010011)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_14    (0b1010100)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_15    (0b1010101)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_16    (0b1010110)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_17    (0b1010111)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_18    (0b1011000)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_19    (0b1011001)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_1A    (0b1011010)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_1B    (0b1011011)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_1C    (0b1011100)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_1D    (0b1011101)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_1E    (0b1011110)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_1F    (0b1011111)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_20    (0b1100000)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_21    (0b1100001)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_22    (0b1100010)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_23    (0b1100011)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_24    (0b1100100)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_25    (0b1100101)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_26    (0b1100110)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_27    (0b1100111)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_28    (0b1101000)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_29    (0b1101001)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_2A    (0b1101010)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_2B    (0b1101011)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_2C    (0b1101100)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_2D    (0b1101101)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_2E    (0b1101110)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_2F    (0b1101111)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_30    (0b1110000)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_31    (0b1110001)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_32    (0b1110010)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_33    (0b1110011)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_34    (0b1110100)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_35    (0b1110101)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_36    (0b1110110)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_37    (0b1110111)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_38    (0b1111000)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_39    (0b1111001)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_3A    (0b1111010)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_3B    (0b1111011)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_3C    (0b1111100)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_3D    (0b1111101)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_3E    (0b1111110)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_I2C_7_BIT_ADDRESS_3F    (0b1111111)


#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_DUTY_GPIO_OFF           (0)
#define TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_DUTY_GPIO_ON            (1000)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC hardware PCA9685 GPIO PWM number.
typedef enum {

    // GPIO number (0 - 15).
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_0 = 0,
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_1,
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_2,
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_3,
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_4,
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_5,
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_6,
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_7,
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_8,
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_9,
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_10,
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_11,
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_12,
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_13,
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_14,
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_15,

    // All.
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_ALL,

} tommRoC_hw_devices_gpio_pwm_pca9685_gpio_number_enum_t;

// Enumeration of tommRoC hardware PCA9685 GPIO output structure.
typedef enum {

    // All GPIO output are configurated with a open drain struct.
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_OUTPUT_STRUCT_OPEN_DRAIN = 0,

    // All GPIO output are configurated with a totem pole struct.
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_OUTPUT_STRUCT_TOTEM_POLE,

} tommRoC_hw_devices_gpio_pwm_pca9685_output_structure_enum_t;


// tommRoC hardware PCA9685 GPIO PWM structure.
typedef struct {

    tommRoC_hw_devices_gpio_pwm_pca9685_gpio_number_enum_t  gpio;           // GPIO
    uint16_t                                                dutyCycleX10;   // Duty cycle x 10.
                                                                            // 1    -> duty cycle 0.1%
                                                                            // 10   -> duty cycle 1.0%
                                                                            // 999  -> duty cycle 99.9%
                                                                            // 0    -> GPIO always OFF  (TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_DUTY_GPIO_OFF)
                                                                            // 1000 -> GPIO always ON   (TOMMROC_HW_DEVICES_GPIO_PWM_PCA9685_DUTY_GPIO_ON)

} tommRoC_hw_devices_gpio_pwm_pca9685_pwm_config_t;

// Enumeration of tommRoC hardware PCA9685 GPIO PWM properties.
typedef enum {

    /**
     * PCA9685 GPIO PWM hardware GPIO output structure property.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_gpio_pwm_pca9685_output_structure_enum_t*
     */
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_GPIO_OUTPUT_STRUCTURE_PROP = 0,

    /**
     * PCA9685 GPIO PWM output frequency property.
     *
     * Available:   set
     * Notes:       propValuePtr has to be uint16_t*
     *              If internal 25 MHz oscillator is used (default):
     *                  - Min. PWM frequency is 24 Hz.
     *                  - Max. PWM frequency is 1526 Hz
     *              At reset, default frequency is 200 Hz
     */
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_OUTPUT_FREQUENCY_HZ_PROP,

    /**
     * PCA9685 GPIO PWM output property.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_gpio_pwm_pca9685_pwm_config_t*
     */
    TOMMRO_C_HW_DEVICES_GPIO_PWM_PCA9685_OUTPUT_PROP,

} tommRoC_hw_devices_gpio_pwm_pca9685_prop_enum_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPWMPCA9685InitI2C(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPWMPCA9685Start(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr);

/**
 * Get property.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPWMPCA9685GetProp(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr,
        const   tommRoC_hw_devices_gpio_pwm_pca9685_prop_enum_t         property,
                void*                                           const   propValuePtr);

/**
 * Set property.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[in]        propValuePtr            value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPWMPCA9685SetProp(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr,
        const   tommRoC_hw_devices_gpio_pwm_pca9685_prop_enum_t         property,
        const   void*                                           const   propValuePtr);

/**
 * Sleep/wake chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPWMPCA9685Sleep(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPWMPCA9685Wake(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr);

#endif
