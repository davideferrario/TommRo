
#ifndef TOMMROC_HW_DEVICES_DAC_CHIP_AD5686_H_
#define TOMMROC_HW_DEVICES_DAC_CHIP_AD5686_H_

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
#include "tommRoCHwGPIO.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of power down mode.
typedef enum {

    /**
     * All 4 VOUTx are in normal operation.
     */
    TOMMRO_C_HW_DEVICES_DAC_CHIP_AD5685_POWER_DOWN_MODE_ALL_NORMAL = 0,

    /**
     * Only VOUTA is in normal operation.
     */
    TOMMRO_C_HW_DEVICES_DAC_CHIP_AD5685_POWER_DOWN_MODE_ONLY_VOUTA_NORMAL,

    /**
     * Only VOUTB is in normal operation.
     */
    TOMMRO_C_HW_DEVICES_DAC_CHIP_AD5685_POWER_DOWN_MODE_ONLY_VOUTB_NORMAL,

    /**
     * Only VOUTC is in normal operation.
     */
    TOMMRO_C_HW_DEVICES_DAC_CHIP_AD5685_POWER_DOWN_MODE_ONLY_VOUTC_NORMAL,

    /**
     * Only VOUTD is in normal operation.
     */
    TOMMRO_C_HW_DEVICES_DAC_CHIP_AD5685_POWER_DOWN_MODE_ONLY_VOUTD_NORMAL,

} tommRoC_hw_devices_dac_chip_ad5686_power_down_mode_enum_t;


// Enumeration of AD5686 properties.
typedef enum {

    /**
     * Power down mode.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_dac_chip_ad5686_power_down_mode_enum_t*
     */
    TOMMRO_C_HW_DEVICES_DAC_CHIP_AD5686_POWER_DOWN_MODE_PROP = 0,

} tommRoC_hw_devices_dac_chip_ad5686_prop_enum_t;


// Enumeration of AD5686 VOUTx.
typedef enum {

    /**
     * VOUTA
     */
    TOMMRO_C_HW_DEVICES_DAC_CHIP_AD5686_VOUTA = 0,

    /**
     * VOUTB
     */
    TOMMRO_C_HW_DEVICES_DAC_CHIP_AD5686_VOUTB,

    /**
     * VOUTC
     */
    TOMMRO_C_HW_DEVICES_DAC_CHIP_AD5686_VOUTC,

    /**
     * VOUTD
     */
    TOMMRO_C_HW_DEVICES_DAC_CHIP_AD5686_VOUTD,

} tommRoC_hw_devices_dac_chip_ad5686_value_type_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

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
tommRoC_hw_err_enum_t tommRoCHwDevicesDACChipAD5686InitSPI(
        const   tommRoC_hw_gpio_set_cb_t                            chipSelect,
        const   tommRoC_hw_gpio_set_cb_t                            chipDeSelect,
        const   tommRoC_hw_bus_t*                           const   busHandlerPtr,
        const   tommRoC_guard_t*                            const   guardPtr,
                tommRoC_hw_bus_device_specific_spi_slave_t* const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                    const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDACChipAD5686Start(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr);

/**
 * Set DAC Chip value.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        valueType               value type.
 * param[in]        value                   value.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDACChipAD5686Set(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   tommRoC_hw_devices_dac_chip_ad5686_value_type_enum_t            valueType,
        const   uint16_t                                                        value);

/**
 * Get property.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDACChipAD5686GetProp(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr,
        const   tommRoC_hw_devices_dac_chip_ad5686_prop_enum_t          property,
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
tommRoC_hw_err_enum_t tommRoCHwDevicesDACChipAD5686SetProp(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr,
        const   tommRoC_hw_devices_dac_chip_ad5686_prop_enum_t          property,
        const   void*                                           const   propValuePtr);

#endif
