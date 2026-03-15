
#ifndef TOMMROC_HW_DEVICES_ADC_CHIP_AD7796_H_
#define TOMMROC_HW_DEVICES_ADC_CHIP_AD7796_H_

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
//
//// Enumeration of AD7796 properties.
//typedef enum {
//
//    /**
//     * Chip reset.
//     *
//     * Available:   set
//     * Notes:       propValuePtr has to be bool*.
//     *              Set *propValuePtr to TRUE, will reset chip; set to FALSE no operation is done.
//     */
//    TOMMRO_C_HW_DEVICES_ADC_CHIP_AD7796_RESET_PROP = 0,
//
//} tommRoC_hw_devices_adc_chip_ad7796_prop_enum_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipAD7796InitSPI(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipAD7796Start(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr);













//
///**
// * Read value.
// *
// * param[in]        busDevicePtr            bus device pointer.
// * param[in]        valueType               value types.
// * param[out]       valuePtr                output value pointer.
// *
// * return tommRoC_hw_err_enum_t
// */
//tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipAD7796Read(
//        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
//        const   tommRoC_hw_devices_adc_chip_ad7796_value_type_enum_t            valueType,
//                void*                                                   const   valuePtr);
//
///**
// * Get property.
// *
// * param[in]        busDevicePtr            bus device pointer.
// * param[in]        property                property.
// * param[out]       propValuePtr            value pointer.
// *
// * return tommRoC_hw_err_enum_t
// */
//tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipAD7796GetProp(
//        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr,
//        const   tommRoC_hw_devices_adc_chip_ad7796_prop_enum_t          property,
//                void*                                           const   propValuePtr);
//
///**
// * Set property.
// *
// * param[in]        busDevicePtr            bus device pointer.
// * param[in]        property                property.
// * param[in]        propValuePtr            value pointer.
// *
// * return tommRoC_hw_err_enum_t
// */
//tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipAD7796SetProp(
//        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr,
//        const   tommRoC_hw_devices_adc_chip_ad7796_prop_enum_t          property,
//        const   void*                                           const   propValuePtr);

#endif
