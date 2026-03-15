
#ifndef TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_SSD1309_H_
#define TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_SSD1309_H_

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
#include "devices/display/tommRoCHwDevicesDisplayU8G2DEF.h"
#include "devices/display/u8g2/tommRoCHwDevicesDisplayU8G2Font.h"

#include "tommRoCHwBus.h"
#include "tommRoCHwBusDevice.h"
#include "tommRoCHwErr.h"
#include "tommRoCHwGPIO.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Device data.
#define TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_SSD1309_DEVICE_DATA_SIZE  (TOMMROC_HW_DEVICES_DISPLAY_U8G2_DEF_DEVICE_DATA_SIZE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_SSD1309_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_display_dot_matrix_ssd1309_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1309InitSPI(
        const   tommRoC_hw_gpio_set_cb_t                                                chipSelect,
        const   tommRoC_hw_gpio_set_cb_t                                                chipDeSelect,
        const   tommRoC_hw_bus_t*                                               const   busHandlerPtr,
        const   tommRoC_guard_t*                                                const   guardPtr,
                tommRoC_hw_bus_device_specific_spi_slave_t*                     const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1309AttachDeviceData(
        const   tommRoC_hw_devices_display_dot_matrix_ssd1309_device_data_t*    const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        resetLow                set RST pin low function pointer (NULL if none).
 * param[in]        resetHigh               set RST pin high function pointer (NULL if none).
 * param[in]        DCLow                   set DC pin low function pointer.
 * param[in]        DCHigh                  set DC pin high function pointer.
 * param[in]        displayRotation         display rotation.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1309Start(
        const   tommRoC_hw_gpio_set_cb_t                                                resetLow,
        const   tommRoC_hw_gpio_set_cb_t                                                resetHigh,
        const   tommRoC_hw_gpio_set_cb_t                                                DCLow,
        const   tommRoC_hw_gpio_set_cb_t                                                DCHigh,
        const   tommRoC_hw_devices_display_u8g2_def_display_rotation_enum_t             displayRotation,
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Display power down.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1309PowerDown(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Display power up.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1309PowerUp(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Clear screen.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1309ClearScreen(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Get draw color (0 -> clear pixel; 1 -> set pixel).
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       colorPtr                color pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1309GetDrawColor(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
                uint8_t*                                                        const   colorPtr);

/**
 * Set draw color (0 -> clear pixel; 1 -> set pixel).
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        color                   color.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1309SetDrawColor(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   uint8_t                                                                 color);

/**
 * Draw a pixel on display.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        x                       x coordinate of pixel to draw.
 * param[in]        y                       y coordinate of pixel to draw.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1309DrawPixel(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   int16_t                                                                 x,
        const   int16_t                                                                 y);

/**
 * Draw a box on display.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        x                       x coordinate of box to draw.
 * param[in]        y                       y coordinate of box to draw.
 * param[in]        w                       width of box to draw.
 * param[in]        h                       height of box to draw.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1309DrawBox(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   int16_t                                                                 x,
        const   int16_t                                                                 y,
        const   int16_t                                                                 w,
        const   int16_t                                                                 h);

/**
 * Draw a string on display.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        x                       x coordinate of box to draw.
 * param[in]        y                       y coordinate of box to draw.
 * param[in]        strPtr                  string pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1309DrawString(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   int16_t                                                                 x,
        const   int16_t                                                                 y,
        const   char*                                                           const   strPtr);

#endif
