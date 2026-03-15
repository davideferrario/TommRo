
#ifndef TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_ST7789_H_
#define TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_ST7789_H_

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

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Some ready-made 16-bit ('565') color settings
#define TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_ST7789_COLOR_BLACK    (0x0000)
#define TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_ST7789_COLOR_WHITE    (0xFFFF)
#define TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_ST7789_COLOR_RED      (0xF800)
#define TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_ST7789_COLOR_GREEN    (0x07E0)
#define TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_ST7789_COLOR_BLUE     (0x001F)
#define TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_ST7789_COLOR_CYAN     (0x07FF)
#define TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_ST7789_COLOR_MAGENTA  (0xF81F)
#define TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_ST7789_COLOR_YELLOW   (0xFFE0)
#define TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_ST7789_COLOR_ORANGE   (0xFC00)


// Device data.
#define TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_ST7789_DEVICE_DATA_SIZE   (   TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                            TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                            TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                            TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                            TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                            TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                            TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                            TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                            TOMMROC_UTIL_U8_SIZE        +   \
                                                                            TOMMROC_UTIL_U16_SIZE       +   \
                                                                            TOMMROC_UTIL_U16_SIZE       +   \
                                                                            TOMMROC_UTIL_I16_SIZE       +   \
                                                                            TOMMROC_UTIL_I16_SIZE       +   \
                                                                            TOMMROC_UTIL_U8_SIZE        +   \
                                                                            TOMMROC_UTIL_U8_SIZE        +   \
                                                                            TOMMROC_UTIL_I16_SIZE       +   \
                                                                            TOMMROC_UTIL_I16_SIZE       +   \
                                                                            TOMMROC_UTIL_U8_SIZE        +   \
                                                                            TOMMROC_UTIL_U8_SIZE            )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_ST7789_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_display_dot_matrix_st7789_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixST7789InitSPI(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixST7789AttachDeviceData(
        const   tommRoC_hw_devices_display_dot_matrix_st7789_device_data_t* const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        DCLow                   set DC (data/command) pin low function pointer (low = command).
 * param[in]        DCHigh                  set DC (data/command) pin high function pointer (high = data).
 * param[in]        RSTLow                  set RST pin low function pointer.
 * param[in]        RSTHigh                 set RST pin high function pointer.
 * param[in]        LEDKLow                 set LEDK (backlight) pin low function pointer.
 * param[in]        LEDKHigh                set LEDK (backlight) pin high function pointer.
 * param[in]        displayWidth            display width [pixel].
 * param[in]        displayHeight           display height [pixel].
 * param[in]        orientation             display orientation.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixST7789Start(
        const   tommRoC_hw_gpio_set_cb_t                                            DCLow,
        const   tommRoC_hw_gpio_set_cb_t                                            DCHigh,
        const   tommRoC_hw_gpio_set_cb_t                                            RSTLow,
        const   tommRoC_hw_gpio_set_cb_t                                            RSTHigh,
        const   tommRoC_hw_gpio_set_cb_t                                            LEDKLow,
        const   tommRoC_hw_gpio_set_cb_t                                            LEDKHigh,
        const   uint16_t                                                            displayWidth,
        const   uint16_t                                                            displayHeight,
        const   tommRoC_hw_devices_display_def_orientation_enum_t                   orientation,
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Reset and configure as startup chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixST7789Reset(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Set chip frame memory with an image.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        imageBufferPtr          image data pointer pointer.
 * param[in]        imageWidth              image width [pixel].
 * param[in]        imageHeight             image height [pixel].
 * param[in]        colorType               how to print image color (original, inverted).
 * param[in]        x                       x coordinate to start set image [pixel].
 * param[in]        y                       y coordinate to start set image [pixel].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixST7789SetFrameMemory(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
        const   uint16_t*                                                   const   imageBufferPtr,
        const   uint16_t                                                            imageWidth,
        const   uint16_t                                                            imageHeight,
        const   tommRoC_hw_devices_display_def_color_type_enum_t                    colorType,
        const   int16_t                                                             x,
        const   int16_t                                                             y);

/**
 * Clear chip frame memory with a constant color.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        colorType               how to print color (original, inverted).
 * param[in]        color                   color [RGB] to be set.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixST7789ClearFrameMemory(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
        const   tommRoC_hw_devices_display_def_color_type_enum_t                    colorType,
        const   uint16_t                                                            color);

/**
 * Set chip frame memory with an image showing a string.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        stringPtr               string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        font                    font type/size.
 * param[in]        fontColorType           how to print font color (original, inverted).
 * param[in]        x                       x coordinate to start set image [pixel].
 * param[in]        y                       y coordinate to start set image [pixel].
 * param[in]        color                   color [RGB] to be set.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixST7789SetString(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
        const   char*                                                       const   stringPtr,
        const   tommRoC_hw_fonts_enum_t                                             font,
        const   tommRoC_hw_devices_display_def_color_type_enum_t                    fontColorType,
        const   int16_t                                                             x,
        const   int16_t                                                             y,
        const   uint16_t                                                            color);

/**
 * Set chip frame memory with an image showing a number.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        value                   number.
 * param[in]        font                    font type/size.
 * param[in]        fontColorType           how to print font color (original, inverted).
 * param[in]        x                       x coordinate to start set image [pixel].
 * param[in]        y                       y coordinate to start set image [pixel].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixST7789SetNumber(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
        const   uint32_t                                                            value,
        const   tommRoC_hw_fonts_enum_t                                             font,
        const   tommRoC_hw_devices_display_def_color_type_enum_t                    fontColorType,
        const   int16_t                                                             x,
        const   int16_t                                                             y,
        const   uint16_t                                                            color);

/**
 * Enable/Disable display.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixST7789EnableDisplay(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixST7789DisableDisplay(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Enable/Disable tearing.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixST7789EnableTearing(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixST7789DisableTearing(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Enable/Disable sleep.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixST7789EnableSleep(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixST7789DisableSleep(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

#endif
