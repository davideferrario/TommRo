
#ifndef TOMMROC_HW_DEVICES_DISPLAY_E_INK_2INCH9_H_
#define TOMMROC_HW_DEVICES_DISPLAY_E_INK_2INCH9_H_

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

/**
 * NOTE:
 * Chip has two RAM image data.
 * One set of RAM is built for historical data; the other is built for the current image data.
 */

/**
 * NOTE:
 * For eInk hardware chip:
 * - a bit set ('1') stands for a white pixel;
 * - a bit reset ('0') stands for a black pixel.
 *
 * TommRo libraries uses inverted setting:
 * - a bit reset ('0') stands for a white pixel;
 * - a bit set ('1') stands for a black pixel.
 *
 * To be compatible for TommRo libraries, all the following functions make
 * binary ones complement operator on input frame data before send to hardware chip.
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
typedef tommRoC_hw_devices_display_e_ink_def_device_data_t tommRoC_hw_devices_display_e_ink_2inch9_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayEInk2Inch9InitSPI(
        const   tommRoC_hw_gpio_set_cb_t                                        chipSelect,
        const   tommRoC_hw_gpio_set_cb_t                                        chipDeSelect,
        const   tommRoC_hw_bus_t*                                       const   busHandlerPtr,
        const   tommRoC_guard_t*                                        const   guardPtr,
                tommRoC_hw_bus_device_specific_spi_slave_t*             const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayEInk2Inch9AttachDeviceData(
        const   tommRoC_hw_devices_display_e_ink_2inch9_device_data_t*  const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                const   busDevicePtr);

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
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayEInk2Inch9Start(
        const   tommRoC_hw_devices_display_def_orientation_enum_t               orientation,
        const   tommRoC_hw_gpio_get_cb_t                                        busyStatus,
        const   tommRoC_hw_gpio_set_cb_t                                        resetLow,
        const   tommRoC_hw_gpio_set_cb_t                                        resetHigh,
        const   tommRoC_hw_gpio_set_cb_t                                        DCLow,
        const   tommRoC_hw_gpio_set_cb_t                                        DCHigh,
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Set chip frame memory with an image.
 * NOTE: image is not show; displayFrame function need to be called.
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
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayEInk2Inch9SetFrameMemory(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   uint8_t*                                                const   imageBufferPtr,
        const   uint16_t                                                        imageWidth,
        const   uint16_t                                                        imageHeight,
        const   tommRoC_hw_devices_display_def_color_type_enum_t                colorType,
        const   uint16_t                                                        x,
        const   uint16_t                                                        y);

/**
 * Clear chip frame memory with a constant pattern [bit mask].
 * NOTE: pattern is not show; displayFrame function need to be called.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        pattern                 pattern to be set.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayEInk2Inch9ClearFrameMemory(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   uint8_t                                                         pattern);

/**
 * Set chip frame memory with an image showing a string.
 * NOTE: image is not show; displayFrame function need to be called.
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
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayEInk2Inch9SetString(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   char*                                                   const   stringPtr,
        const   tommRoC_hw_fonts_enum_t                                         font,
        const   tommRoC_hw_devices_display_def_color_type_enum_t                fontColorType,
        const   uint16_t                                                        x,
        const   uint16_t                                                        y);

/**
 * Set chip frame memory with an image showing a number.
 * NOTE: image is not show; displayFrame function need to be called.
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
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayEInk2Inch9SetNumber(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   uint32_t                                                        value,
        const   tommRoC_hw_fonts_enum_t                                         font,
        const   tommRoC_hw_devices_display_def_color_type_enum_t                fontColorType,
        const   uint16_t                                                        x,
        const   uint16_t                                                        y);

/**
 * Display the data from the frame memory.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayEInk2Inch9DisplayFrame(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Sleep/wake chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayEInk2Inch9Sleep(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesDisplayEInk2Inch9Wake(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

#endif
