
#ifndef TOMMROC_HW_DEVICES_GPIO_PCA9570_H_
#define TOMMROC_HW_DEVICES_GPIO_PCA9570_H_

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

/*************************1******************************************************
 * defines
 ******************************************************************************/

// Compatible device I2C addresses.
#define TOMMROC_HW_DEVICES_GPIO_PCA9570_I2C_7_BIT_ADDRESS   (0b0100100)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/**
 * tommRoC hardware PCA9570 GPIO expander all pin status.
 *
 * If a bit is cleared ('0'), the corresponding port state at the pin is low.
 * If a bit is set ('1'), the corresponding port state at the pin is high.
 * Most significative bit is about P7; less significative bit is about P0.
 * NOTES:
 *      - writes to P7 to P4 are ignored in the PCA9570 as only P3 through P0 are available.
 *      - when the PCA9570 is read, P7 through P4 return logic '1'.
 *
 * 0bxxxxxxxx
 *   |      |
 *   |      |
 *   |      |
 *   |      -----------> status of P0 pin
 *   ------------------> status of P7 pin
 */
typedef uint8_t tommRoC_hw_devices_gpio_pca9570_status_t;

#define TOMMROC_HW_DEVICES_GPIO_PCA9570_STATUS_PIN_LOW                  (0b0)
#define TOMMROC_HW_DEVICES_GPIO_PCA9570_STATUS_PIN_HIGH                 (0b1)

#define TOMMROC_HW_DEVICES_GPIO_PCA9570_STATUS_ALL_OUTPUT_PIN_LOW       ((tommRoC_hw_devices_gpio_pca9570_status_t) 0x00)
#define TOMMROC_HW_DEVICES_GPIO_PCA9570_STATUS_ALL_OUTPUT_PIN_HIGH      ((tommRoC_hw_devices_gpio_pca9570_status_t) 0xFF)


// Enumeration of tommRoC hardware PCA9570 GPIO properties.
typedef enum {

    /**
     * PCA9570 GPIO single pin status property.
     *
     * Available:   get/set
     * Notes:       propValuePtr has to be tommRoC_util_bit_status_enum_t*
     *              Get operation:  result reflects port state at the pin.
     *              Set operation:  result reflects outgoing logic levels of the pins.
     */
    TOMMRO_C_HW_DEVICES_GPIO_PCA9570_P0_STATUS_PROP = 0,
    TOMMRO_C_HW_DEVICES_GPIO_PCA9570_P1_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCA9570_P2_STATUS_PROP,
    TOMMRO_C_HW_DEVICES_GPIO_PCA9570_P3_STATUS_PROP,

    /**
     * PCA9570 GPIO all pin status property.
     *
     * Available:   get/set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_gpio_pca9570_status_t*
     *              Get operation:  result reflects port state at the pin.
     *              Set operation:  result reflects outgoing logic levels of the pins.
     */
    TOMMRO_C_HW_DEVICES_GPIO_PCA9570_ALL_IO_STATUS_PROP,

} tommRoC_hw_devices_gpio_pca9570_prop_enum_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPCA9570InitI2C(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPCA9570Start(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr);

/**
 * Get property.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPCA9570GetProp(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr,
        const   tommRoC_hw_devices_gpio_pca9570_prop_enum_t         property,
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
tommRoC_hw_err_enum_t tommRoCHwDevicesGPIOPCA9570SetProp(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr,
        const   tommRoC_hw_devices_gpio_pca9570_prop_enum_t         property,
        const   void*                                       const   propValuePtr);

#endif
