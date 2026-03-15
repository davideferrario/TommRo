
#ifndef TOMMROC_HW_DEVICES_DISPLAY_E_INK_NE040N001GD_H_
#define TOMMROC_HW_DEVICES_DISPLAY_E_INK_NE040N001GD_H_

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
#include "tommRoCHwFonts.h"
#include "tommRoCHwGPIO.h"

#include "devices/display/tommRoCHwDevicesDisplayDEF.h"
#include "devices/display/eInk/tommRoCHwDevicesDisplayEInkDEF.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Device data.
// NOTE: HAVE to be a static variable.
typedef tommRoC_hw_devices_display_e_ink_def_device_data_t tommRoC_hw_devices_display_e_ink_ne040n001gd_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayEInkNE040N001GDInitSPI(
        const   tommRoC_hw_gpio_set_cb_t                                            chipSelect,
        const   tommRoC_hw_gpio_set_cb_t                                            chipDeSelect,
        const   tommRoC_hw_bus_t*                                           const   busHandlerPtr,
        const   tommRoC_guard_t*                                            const   guardPtr,
                tommRoC_hw_bus_device_specific_spi_slave_t*                 const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayEInkNE040N001GDAttachDeviceData(
        const   tommRoC_hw_devices_display_e_ink_ne040n001gd_device_data_t* const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        orientation             display orientation.
 * param[in]        busyStatus              get pin busy status function pointer.
 * param[in]        resetLow                set RESET pin low function pointer.
 * param[in]        resetHigh               set RESET pin high function pointer..
 * param[in]        resetLow                set DATA/COMMAND pin low function pointer.
 * param[in]        resetHigh               set DATA/COMMAND pin high function pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayEInkNE040N001GDStart(
        const   tommRoC_hw_devices_display_def_orientation_enum_t                   orientation,
        const   tommRoC_hw_gpio_get_cb_t                                            busyStatus,
        const   tommRoC_hw_gpio_set_cb_t                                            resetLow,
        const   tommRoC_hw_gpio_set_cb_t                                            resetHigh,
        const   tommRoC_hw_gpio_set_cb_t                                            DCLow,
        const   tommRoC_hw_gpio_set_cb_t                                            DCHigh,
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Sleep/wake chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayEInkNE040N001GDSleep(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayEInkNE040N001GDWake(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

#endif
