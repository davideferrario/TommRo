
#ifndef TOMMROC_HW_DEVICES_GPIO_PCAL6524_H_
#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_H_

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
#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_I2C_7_BIT_ADDRESS_ADDR_PIN_VDD (0b0100011)
#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_I2C_7_BIT_ADDRESS_ADDR_PIN_GND (0b0100010)
#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_I2C_7_BIT_ADDRESS_ADDR_PIN_SDA (0b0100001)
#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_I2C_7_BIT_ADDRESS_ADDR_PIN_SCL (0b0100000)


// Device data.
#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_DEVICE_DATA_SIZE   (TOMMROC_UTIL_U24_SIZE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/**
 * tommRoC hardware PCAL6524 GPIO expander configuration.
 *
 * Direction configuration of the I/O pins.
 * If a bit is cleared ('0'), the corresponding port pin is enabled as an output.
 * If a bit is set ('1'), the corresponding port pin is enabled as a high-impedance input.
 * Most significative byte of uint32_t is not used; next byte is about IO2 port; next byte is about IO1 port; less significative byte is about IO0 port.
 * For every byte, most significative bit is about pin7; less significative bit is about pin0.
 * NOTE: At reset, the device's ports are inputs with a pull-up to VDD.
 *
 *  |-IO 2 P-|-IO 1 P-|-IO O P-|
 * 0bxxxxxxxx|xxxxxxxx|xxxxxxxx
 *   |      | |      | |      |
 *   |      | |      | |      --> configuration of IO0_0 pin
 *   |      | |      | ---------> configuration of IO0_7 pin
 *   |      | |      -----------> configuration of IO1_0 pin
 *   |      | ------------------> configuration of IO1_7 pin
 *   |      --------------------> configuration of IO2_0 pin
 *   ---------------------------> configuration of IO2_7 pin
 */
typedef uint32_t tommRoC_hw_devices_gpio_pcal6524_config_t;

#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_CONFIG_PIN_OUTPUT          (0b0)
#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_CONFIG_PIN_INPUT           (0b1)

#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_CONFIG_ALL_PIN_OUTPUT      ((tommRoC_hw_devices_gpio_pcal6524_config_t) 0x00000000)
#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_CONFIG_ALL_PIN_INPUT       ((tommRoC_hw_devices_gpio_pcal6524_config_t) 0x00FFFFFF)


/**
 * tommRoC hardware PCAL6524 GPIO expander input latch.
 *
 * Input latch configuration of the I/O pins.
 * If a bit is cleared ('0'), the corresponding input pin state is not latched.
 * A state change in the corresponding input pin generates an interrupt. A read of the input register clears the interrupt.
 * If the input goes back to its initial logic state before the input port register is read, then the interrupt is cleared.
 * If a bit is set ('1'), the corresponding input pin state is latched.
 * A change of state of the input generates an interrupt and the input logic value is loaded into the corresponding bit of the input port register.
 * A read of the input port register clears the interrupt.
 * If the input pin returns to its initial logic state before the input port register is read, then the interrupt is not cleared and the
 * corresponding bit of the input port register keeps the logic value that initiated the interrupt
 * Most significative byte of uint32_t is not used; next byte is about IO2 port; next byte is about IO1 port; less significative byte is about IO0 port.
 * For every byte, most significative bit is about pin7; less significative bit is about pin0.
 * NOTE: At reset, input latch registers are set to logic 0.
 *
 *  |-IO 2 P-|-IO 1 P-|-IO O P-|
 * 0bxxxxxxxx|xxxxxxxx|xxxxxxxx
 *   |      | |      | |      |
 *   |      | |      | |      --> configuration of IO0_0 pin
 *   |      | |      | ---------> configuration of IO0_7 pin
 *   |      | |      -----------> configuration of IO1_0 pin
 *   |      | ------------------> configuration of IO1_7 pin
 *   |      --------------------> configuration of IO2_0 pin
 *   ---------------------------> configuration of IO2_7 pin
 */
typedef uint32_t tommRoC_hw_devices_gpio_pcal6524_input_latch_t;

#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_INPUT_LATCH_PIN_DISABLED       (0b0)
#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_INPUT_LATCH_PIN_ENABLED        (0b1)

#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_INPUT_LATCH_ALL_PIN_DISABLED   ((tommRoC_hw_devices_gpio_pcal6524_input_latch_t) 0x00000000)
#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_INPUT_LATCH_ALL_PIN_ENABLED    ((tommRoC_hw_devices_gpio_pcal6524_input_latch_t) 0x00FFFFFF)


/**
 * tommRoC hardware PCAL6524 GPIO expander interrupt mask.
 *
 * Interrupt mask configuration of the I/O pins.
 * If a bit is cleared ('0'), the corresponding input port pin will generate an interrupt if the state change.
 * If a bit is set ('1'), the corresponding input port pin will NOT generate an interrupt if the state change (interrupt masked).
 * Most significative byte of uint32_t is not used; next byte is about IO2 port; next byte is about IO1 port; less significative byte is about IO0 port.
 * For every byte, most significative bit is about pin7; less significative bit is about pin0.
 * NOTE: At reset, interrupt mask registers are set to logic 1, disabling interrupts during system start-up.
 *
 *  |-IO 2 P-|-IO 1 P-|-IO O P-|
 * 0bxxxxxxxx|xxxxxxxx|xxxxxxxx
 *   |      | |      | |      |
 *   |      | |      | |      --> configuration of IO0_0 pin
 *   |      | |      | ---------> configuration of IO0_7 pin
 *   |      | |      -----------> configuration of IO1_0 pin
 *   |      | ------------------> configuration of IO1_7 pin
 *   |      --------------------> configuration of IO2_0 pin
 *   ---------------------------> configuration of IO2_7 pin
 */
typedef uint32_t tommRoC_hw_devices_gpio_pcal6524_int_mask_t;

#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_INT_MASK_INT_PIN_ENABLED       (0b0)
#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_INT_MASK_INT_PIN_DISABLED      (0b1)

#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_INT_MASK_INT_ALL_PIN_ENABLED   ((tommRoC_hw_devices_gpio_pcal6524_int_mask_t) 0x00000000)
#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_INT_MASK_INT_ALL_PIN_DISABLED  ((tommRoC_hw_devices_gpio_pcal6524_int_mask_t) 0x00FFFFFF)


/**
 * tommRoC hardware PCAL6524 GPIO expander pull enable.
 *
 * Pull enable configuration of the I/O pins.
 * Setting the bit to logic 0 disconnects the pull-up/pull-down resistors from the I/O pins. Also, the resistors will be disconnected when the outputs are configured as open-drain outputs.
 * Setting the bit to logic 1 enables the selection of pull-up/pull-down resistors
 * Most significative byte of uint32_t is not used; next byte is about IO2 port; next byte is about IO1 port; less significative byte is about IO0 port.
 * For every byte, most significative bit is about pin7; less significative bit is about pin0.
 * NOTE: At reset, pull enable registers are set to logic 0, disabling pull during system start-up.
 *
 *  |-IO 2 P-|-IO 1 P-|-IO O P-|
 * 0bxxxxxxxx|xxxxxxxx|xxxxxxxx
 *   |      | |      | |      |
 *   |      | |      | |      --> configuration of IO0_0 pin
 *   |      | |      | ---------> configuration of IO0_7 pin
 *   |      | |      -----------> configuration of IO1_0 pin
 *   |      | ------------------> configuration of IO1_7 pin
 *   |      --------------------> configuration of IO2_0 pin
 *   ---------------------------> configuration of IO2_7 pin
 */
typedef uint32_t tommRoC_hw_devices_gpio_pcal6524_pull_enable_t;

#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_PULL_ENABLE_PULL_DISABLED      (0b0)
#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_PULL_ENABLE_PULL_ENABLED       (0b1)

#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_PULL_ENABLE_ALL_PIN_DISABLED   ((tommRoC_hw_devices_gpio_pcal6524_pull_enable_t) 0x00000000)
#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_PULL_ENABLE_ALL_PIN_ENABLED    ((tommRoC_hw_devices_gpio_pcal6524_pull_enable_t) 0x00FFFFFF)


/**
 * tommRoC hardware PCAL6524 GPIO expander pull selection.
 *
 * Pull selection configuration of the I/O pins.
 * Setting a bit to logic 0 selects a 100 k-ohm pull-down resistor for that I/O pin.
 * Setting a bit to logic 1 selects a 100 k-ohm pull-up resistor for that I/O pin
 * Most significative byte of uint32_t is not used; next byte is about IO2 port; next byte is about IO1 port; less significative byte is about IO0 port.
 * For every byte, most significative bit is about pin7; less significative bit is about pin0.
 * NOTE: At reset, pull enable registers are set to logic 0, disabling pull during system start-up.
 *
 *  |-IO 2 P-|-IO 1 P-|-IO O P-|
 * 0bxxxxxxxx|xxxxxxxx|xxxxxxxx
 *   |      | |      | |      |
 *   |      | |      | |      --> configuration of IO0_0 pin
 *   |      | |      | ---------> configuration of IO0_7 pin
 *   |      | |      -----------> configuration of IO1_0 pin
 *   |      | ------------------> configuration of IO1_7 pin
 *   |      --------------------> configuration of IO2_0 pin
 *   ---------------------------> configuration of IO2_7 pin
 */
typedef uint32_t tommRoC_hw_devices_gpio_pcal6524_pull_selection_t;

#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_PULL_SELECTION_PULL_DOWN       (0b0)
#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_PULL_SELECTION_PULL_UP         (0b1)

#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_PULL_SELECTION_ALL_PULL_DOWN   ((tommRoC_hw_devices_gpio_pcal6524_pull_selection_t) 0x00000000)
#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_PULL_SELECTION_ALL_PULL_UP     ((tommRoC_hw_devices_gpio_pcal6524_pull_selection_t) 0x00FFFFFF)


/**
 * tommRoC hardware PCAL6524 GPIO expander all pin status.
 *
 * If a bit is cleared ('0'), the corresponding port pin logic level is low.
 * If a bit is set ('1'), the corresponding port pin logic level is high.
 * Most significative byte of uint32_t is not used; next byte is about IO2 port; next byte is about IO1 port; less significative byte is about IO0 port.
 * For every byte, most significative bit is about pin7; less significative bit is about pin0.
 *
 *  |-IO 2 P-|-IO 1 P-|-IO O P-|
 * 0bxxxxxxxx|xxxxxxxx|xxxxxxxx
 *   |      | |      | |      |
 *   |      | |      | |      --> status of IO0_0 pin
 *   |      | |      | ---------> status of IO0_0 pin
 *   |      | |      -----------> status of IO1_0 pin
 *   |      | ------------------> status of IO1_7 pin
 *   |      --------------------> status of IO2_0 pin
 *   ---------------------------> status of IO2_7 pin
 */
typedef uint32_t tommRoC_hw_devices_gpio_pcal6524_status_t;

#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_STATUS_PIN_LOW             (0b0)
#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_STATUS_PIN_HIGH            (0b1)

#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_STATUS_ALL_OUTPUT_PIN_LOW  ((tommRoC_hw_devices_gpio_pcal6524_status_t) 0x00000000)
#define TOMMROC_HW_DEVICES_GPIO_PCAL6524_STATUS_ALL_OUTPUT_PIN_HIGH ((tommRoC_hw_devices_gpio_pcal6524_status_t) 0x00FFFFFF)


// Enumeration of tommRoC hardware PCAL6524 GPIO properties.
typedef enum {

    /**
     * PCAL6524 GPIO single pin status property.
     *
     * Available:   get/set
     * Notes:       propValuePtr has to be tommRoC_util_bit_status_enum_t*
     *              Get operation:  result reflects incoming logic levels of pin,
     *                              regardless of whether pin is defined as input/output.
     *              Set operation:  result reflects outgoing logic levels of the pins defined as output.
     *                              Have no effect on pins defined as inputs.
     */
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO0_0_STATUS_PROP = 0,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO0_1_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO0_2_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO0_3_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO0_4_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO0_5_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO0_6_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO0_7_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO1_0_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO1_1_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO1_2_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO1_3_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO1_4_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO1_5_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO1_6_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO1_7_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO2_0_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO2_1_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO2_2_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO2_3_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO2_4_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO2_5_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO2_6_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_IO2_7_STATUS_PROP,

    /**
     * PCAL6524 GPIO all pin status property.
     *
     * Available:   get/set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_gpio_pcal6524_status_t*
     *              Get operation:  result reflects incoming logic levels of pin, regardless of whether pin is defined as input/output.
     *                              If a pin is configured as an output, the port value is equal to the actual voltage level on that pin.
     *                              If the output is configured as open-drain, the input port value is forced to 0.
     *              Set operation:  result reflects outgoing logic levels of the pins defined as output. Have no effect on pins defined as inputs.
     */
    TOMMRO_C_HW_DEVICES_GPIO_PCAL6524_ALL_IO_STATUS_PROP,

} tommRoC_hw_devices_gpio_pcal6524_prop_enum_t;


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_GPIO_PCAL6524_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_gpio_pcal6524_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPCAL6524InitI2C(
        const   uint8_t                                                 i2c7BitSlaveAddress,
        const   tommRoC_hw_bus_t*                               const   busHandlerPtr,
        const   tommRoC_guard_t*                                const   guardPtr,
                tommRoC_hw_bus_device_specific_i2c_slave_t*     const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                        const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPCAL6524AttachDeviceData(
        const   tommRoC_hw_devices_gpio_pcal6524_device_data_t* const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                        const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPCAL6524Start(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr);

/**
 * Configure GPIO pins of PCAL6524 GPIO expander as input/output.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        gpioConfig              GPIO configuration.
 * param[in]        gpioInputLatch          GPIO input latch config.
 * param[in]        gpioIntMask             GPIO interrupt mask config.
 * param[in]        gpioPullEnable          GPIO pull enable config.
 * param[in]        gpioPullSelection       GPIO pull selection config.

 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPCAL6524Config(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr,
        const   tommRoC_hw_devices_gpio_pcal6524_config_t               gpioConfig,
        const   tommRoC_hw_devices_gpio_pcal6524_input_latch_t          gpioInputLatch,
        const   tommRoC_hw_devices_gpio_pcal6524_int_mask_t             gpioIntMask,
        const   tommRoC_hw_devices_gpio_pcal6524_pull_enable_t          gpioPullEnable,
        const   tommRoC_hw_devices_gpio_pcal6524_pull_selection_t       gpioPullSelection);

/**
 * Get property.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPCAL6524GetProp(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr,
        const   tommRoC_hw_devices_gpio_pcal6524_prop_enum_t            property,
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
tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPCAL6524SetProp(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr,
        const   tommRoC_hw_devices_gpio_pcal6524_prop_enum_t            property,
        const   void*                                           const   propValuePtr);

#endif
