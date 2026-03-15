
#ifndef TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_SSD1306_H_
#define TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_SSD1306_H_

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

// Compatible device I2C addresses.
#define TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_SSD1306_I2C_7_BIT_ADDRESS_SA0_PIN_GND (0b0111100)
#define TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_SSD1306_I2C_7_BIT_ADDRESS_SA0_PIN_VDD  (0b0111101)


// Device data.
#define TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_SSD1306_DEVICE_DATA_SIZE  (   TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                            TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                            TOMMROC_UTIL_U8_SIZE            )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_DISPLAY_DOT_MATRIX_SSD1306_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_display_dot_matrix_ssd1306_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1306InitI2C(
        const   uint8_t                                                                 i2c7BitSlaveAddress,
        const   tommRoC_hw_bus_t*                                               const   busHandlerPtr,
        const   tommRoC_guard_t*                                                const   guardPtr,
                tommRoC_hw_bus_device_specific_i2c_slave_t*                     const   specificSlavePtr,
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
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1306AttachDeviceData(
        const   tommRoC_hw_devices_display_dot_matrix_ssd1306_device_data_t*    const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        orientation             display orientation.
 * param[in]        resetLow                set RST pin low function pointer.
 * param[in]        resetHigh               set RST pin high function pointer
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1306Start(
        const   tommRoC_hw_devices_display_def_orientation_enum_t                       orientation,
        const   tommRoC_hw_gpio_set_cb_t                                                resetLow,
        const   tommRoC_hw_gpio_set_cb_t                                                resetHigh,
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Reset and configure as startup chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1306Reset(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

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
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1306SetFrameMemory(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   uint8_t*                                                        const   imageBufferPtr,
        const   uint8_t                                                                 imageWidth,
        const   uint8_t                                                                 imageHeight,
        const   tommRoC_hw_devices_display_def_color_type_enum_t                        colorType,
        const   uint8_t                                                                 x,
        const   uint8_t                                                                 y);

/**
 * Clear chip frame memory with a constant pattern [bit mask].
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        pattern                 pattern to be set.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1306ClearFrameMemory(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   uint8_t                                                                 pattern);

/**
 * Set chip frame memory with an image showing a string.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        stringPtr               string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        font                    font type/size.
 * param[in]        fontColorType           how to print font color (original, inverted).
 * param[in]        x                       x coordinate to start set image [pixel].
 * param[in]        y                       y coordinate to start set image [pixel].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1306SetString(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   char*                                                           const   stringPtr,
        const   tommRoC_hw_fonts_enum_t                                                 font,
        const   tommRoC_hw_devices_display_def_color_type_enum_t                        fontColorType,
        const   uint8_t                                                                 x,
        const   uint8_t                                                                 y);

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
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1306SetNumber(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   uint32_t                                                                value,
        const   tommRoC_hw_fonts_enum_t                                                 font,
        const   tommRoC_hw_devices_display_def_color_type_enum_t                        fontColorType,
        const   uint8_t                                                                 x,
        const   uint8_t                                                                 y);

/**
 * ON/OFF display chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1306ON(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayDotMatrixSSD1306OFF(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

#endif
