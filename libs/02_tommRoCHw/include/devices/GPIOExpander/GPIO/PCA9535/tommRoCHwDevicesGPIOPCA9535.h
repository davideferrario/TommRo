
#ifndef TOMMROC_HW_DEVICES_GPIO_PCA9535_H_
#define TOMMROC_HW_DEVICES_GPIO_PCA9535_H_

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
#define TOMMROC_HW_DEVICES_GPIO_PCA9535_I2C_7_BIT_ADDRESS_A2A1A0_PIN_GNDGNDGND  (0b0100000)
#define TOMMROC_HW_DEVICES_GPIO_PCA9535_I2C_7_BIT_ADDRESS_A2A1A0_PIN_GNDGNDVDD  (0b0100001)
#define TOMMROC_HW_DEVICES_GPIO_PCA9535_I2C_7_BIT_ADDRESS_A2A1A0_PIN_GNDVDDGND  (0b0100010)
#define TOMMROC_HW_DEVICES_GPIO_PCA9535_I2C_7_BIT_ADDRESS_A2A1A0_PIN_GNDVDDVDD  (0b0100011)
#define TOMMROC_HW_DEVICES_GPIO_PCA9535_I2C_7_BIT_ADDRESS_A2A1A0_PIN_VDDGNDGND  (0b0100100)
#define TOMMROC_HW_DEVICES_GPIO_PCA9535_I2C_7_BIT_ADDRESS_A2A1A0_PIN_VDDGNDVDD  (0b0100101)
#define TOMMROC_HW_DEVICES_GPIO_PCA9535_I2C_7_BIT_ADDRESS_A2A1A0_PIN_VDDVDDGND  (0b0100110)
#define TOMMROC_HW_DEVICES_GPIO_PCA9535_I2C_7_BIT_ADDRESS_A2A1A0_PIN_VDDVDDVDD  (0b0100111)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/**
 * tommRoC hardware PCA9535 GPIO expander configuration.
 *
 * Direction configuration of the I/O pins.
 * If a bit is cleared ('0'), the corresponding port pin is enabled as an output.
 * If a bit is set ('1'), the corresponding port pin is enabled as an input with high-impedance output driver.
 * Most significative byte of uint16_t is about IO1 port; less significative byte of uint16_t is about IO0 port.
 * For every byte, most significative bit is about pin7; less significative bit is about pin0.
 * NOTE: At reset, the device's ports are inputs with a pull-up to VDD.
 *
 *  |-IO 1 P-|-IO O P-|
 * 0bxxxxxxxx|xxxxxxxx
 *   |      | |      |
 *   |      | |      --> configuration of IO0_0 pin
 *   |      | ---------> configuration of IO0_7 pin
 *   |      -----------> configuration of IO1_0 pin
 *   ------------------> configuration of IO1_7 pin
 */
typedef uint16_t tommRoC_hw_devices_gpio_pca9535_config_t;

#define TOMMROC_HW_DEVICES_GPIO_PCA9535_CONFIG_PIN_OUTPUT           (0b0)
#define TOMMROC_HW_DEVICES_GPIO_PCA9535_CONFIG_PIN_INPUT            (0b1)

#define TOMMROC_HW_DEVICES_GPIO_PCA9535_CONFIG_ALL_PIN_OUTPUT       ((tommRoC_hw_devices_gpio_pca9535_config_t) 0x0000)
#define TOMMROC_HW_DEVICES_GPIO_PCA9535_CONFIG_ALL_PIN_INPUT        ((tommRoC_hw_devices_gpio_pca9535_config_t) 0xFFFF)


/**
 * tommRoC hardware PCA9535 GPIO expander all pin status.
 *
 * If a bit is cleared ('0'), the corresponding port pin logic level is low.
 * If a bit is set ('1'), the corresponding port pin logic level is high.
 * Most significative byte of uint16_t is about IO1 port; less significative byte of uint16_t is about IO0 port.
 * For every byte, most significative bit is about pin7; less significative bit is about pin0.
 *
 *  |-IO 1 P-|-IO O P-|
 * 0bxxxxxxxx|xxxxxxxx
 *   |      | |      |
 *   |      | |      --> status of IO0_0 pin
 *   |      | ---------> status of IO0_7 pin
 *   |      -----------> status of IO1_0 pin
 *   ------------------> status of IO1_7 pin
 */
typedef uint16_t tommRoC_hw_devices_gpio_pca9535_status_t;

#define TOMMROC_HW_DEVICES_GPIO_PCA9535_STATUS_PIN_LOW              (0b0)
#define TOMMROC_HW_DEVICES_GPIO_PCA9535_STATUS_PIN_HIGH             (0b1)

#define TOMMROC_HW_DEVICES_GPIO_PCA9535_STATUS_ALL_OUTPUT_PIN_LOW   ((tommRoC_hw_devices_gpio_pca9535_status_t) 0x0000)
#define TOMMROC_HW_DEVICES_GPIO_PCA9535_STATUS_ALL_OUTPUT_PIN_HIGH  ((tommRoC_hw_devices_gpio_pca9535_status_t) 0xFFFF)


// Enumeration of tommRoC hardware PCA9535 GPIO properties.
typedef enum {

    /**
     * PCA9535 GPIO single pin status property.
     *
     * Available:   get/set
     * Notes:       propValuePtr has to be tommRoC_util_bit_status_enum_t*
     *              Get operation:  result reflects incoming logic levels of pin,
     *                              regardless of whether pin is defined as input/output.
     *              Set operation:  result reflects outgoing logic levels of the pins defined as output.
     *                              Have no effect on pins defined as inputs.
     */
    TOMMRO_C_HW_DEVICES_GPIO_PCA9535_IO0_0_STATUS_PROP = 0,
    TOMMRO_C_HW_DEVICES_GPIO_PCA9535_IO0_1_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCA9535_IO0_2_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCA9535_IO0_3_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCA9535_IO0_4_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCA9535_IO0_5_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCA9535_IO0_6_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCA9535_IO0_7_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCA9535_IO1_0_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCA9535_IO1_1_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCA9535_IO1_2_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCA9535_IO1_3_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCA9535_IO1_4_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCA9535_IO1_5_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCA9535_IO1_6_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCA9535_IO1_7_STATUS_PROP,

    /**
     * PCA9535 GPIO all pin status property.
     *
     * Available:   get/set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_gpio_pca9535_status_t*
     *              Get operation:  result reflects incoming logic levels of pin,
     *                              regardless of whether pin is defined as input/output.
     *              Set operation:  result reflects outgoing logic levels of the pins defined as output.
     *                              Have no effect on pins defined as inputs.
     */
    TOMMRO_C_HW_DEVICES_GPIO_PCA9535_ALL_IO_STATUS_PROP,

} tommRoC_hw_devices_gpio_pca9535_prop_enum_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPCA9535InitI2C(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPCA9535Start(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr);

/**
 * Configure GPIO pins of PCA9535 GPIO expander as input/output.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        gpioConfig              GPIO configuration.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPCA9535Config(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr,
        const   tommRoC_hw_devices_gpio_pca9535_config_t            gpioConfig);

/**
 * Get property.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPCA9535GetProp(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr,
        const   tommRoC_hw_devices_gpio_pca9535_prop_enum_t         property,
                void*                                       const   propValuePtr);

/**
 * Set property.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[in]        propValuePtr            value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPCA9535SetProp(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr,
        const   tommRoC_hw_devices_gpio_pca9535_prop_enum_t         property,
        const   void*                                       const   propValuePtr);

#endif
