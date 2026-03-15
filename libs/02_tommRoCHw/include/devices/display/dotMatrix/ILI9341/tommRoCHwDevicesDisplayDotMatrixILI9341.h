
#ifndef TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_ILI9341_H_
#define TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_ILI9341_H_

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
#include "devices/display/tommRoCHwDevicesDisplayUCGLibDEF.h"
#include "devices/display/ucglib/tommRoCHwDevicesDisplayUCGLibFont.h"

#include "tommRoCHwBus.h"
#include "tommRoCHwBusDevice.h"
#include "tommRoCHwErr.h"
#include "tommRoCHwGPIO.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Device data.
#define TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_ILI9341_DEVICE_DATA_SIZE  (TOMMROC_HW_DEVICES_DISPLAY_UCGLIB_DEF_DEVICE_DATA_SIZE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_ILI9341_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_display_dot_matrix_ili9341_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixILI9341InitSPI(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixILI9341AttachDeviceData(
        const   tommRoC_hw_devices_display_dot_matrix_ili9341_device_data_t*    const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        resetLow                set RST pin low function pointer (NULL if none).
 * param[in]        resetHigh               set RST pin high function pointer (NULL if none).
 * param[in]        DCLow                   set DC pin low function pointer.
 * param[in]        DCHigh                  set DC pin high function pointer.
 * param[in]        clearScreen             clear screen on init flag.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixILI9341Start(
        const   tommRoC_hw_gpio_set_cb_t                                                resetLow,
        const   tommRoC_hw_gpio_set_cb_t                                                resetHigh,
        const   tommRoC_hw_gpio_set_cb_t                                                DCLow,
        const   tommRoC_hw_gpio_set_cb_t                                                DCHigh,
        const   bool                                                                    clearScreen,
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Display power down.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixILI9341PowerDown(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Display power up.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixILI9341PowerUp(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Clear screen.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixILI9341ClearScreen(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Set RGB color used for future display operations.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        colorType               color type (foreground or background).
 * param[in]        R                       red part of RGB color.
 * param[in]        G                       green part of RGB color.
 * param[in]        B                       blue part of RGB color.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixILI9341SetColor(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   tommRoC_hw_devices_display_ucglib_def_color_type_enum_t                 colorType,
        const   uint8_t                                                                 R,
        const   uint8_t                                                                 G,
        const   uint8_t                                                                 B);

/**
 * Draw a pixel on display.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        x                       x coordinate of pixel to draw.
 * param[in]        y                       y coordinate of pixel to draw.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixILI9341DrawPixel(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   int16_t                                                                 x,
        const   int16_t                                                                 y);

/**
 * Draw a line pixel on display.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        x                       x coordinate of line pixel to draw.
 * param[in]        y                       y coordinate of line pixel to draw.
 * param[in]        len                     length of line pixel to draw [pixel].
 * param[in]        bitmapLinePtr           line pixel bitmap pointer to draw.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixILI9341DrawLinePixel(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   int16_t                                                                 x,
        const   int16_t                                                                 y,
        const   uint16_t                                                                len,
        const   uint8_t*                                                        const   bitmapLinePtr);

/**
 * Draw a full display bitmap on display.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        bitmapPtr               pixel bitmap pointer to draw.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixILI9341DrawFullDisplayBitmap(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   uint8_t*                                                        const   bitmapPtr);

/**
 * Draw a bitmap on display.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        x                       x coordinate of bitmap to draw.
 * param[in]        y                       y coordinate of bitmap to draw.
 * param[in]        w                       width of bitmap to draw.
 * param[in]        h                       height of bitmap to draw.
 * param[in]        bitmapPtr               pixel bitmap pointer to draw.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixILI9341DrawBitmap(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   int16_t                                                                 x,
        const   int16_t                                                                 y,
        const   int16_t                                                                 w,
        const   int16_t                                                                 h,
        const   uint8_t*                                                        const   bitmapPtr);

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
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixILI9341DrawBox(
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
 * param[in]        direction               direction of the string draw.
 * param[in]        strPtr                  string pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixILI9341DrawString(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   int16_t                                                                 x,
        const   int16_t                                                                 y,
        const   tommRoC_hw_devices_display_ucglib_font_direction_enum_t                 direction,
        const   char*                                                           const   strPtr);

#endif
