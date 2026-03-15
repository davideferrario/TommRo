
#ifndef TOMMROC_HW_DEVICES_DISPLAY_SEPS525_H_
#define TOMMROC_HW_DEVICES_DISPLAY_SEPS525_H_

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
#include "tommRoCHwColor.h"
#include "tommRoCHwDisplay.h"
#include "tommRoCHwErr.h"
#include "tommRoCHwGPIO.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC hardware display driver SEPS525.
typedef struct {

    /**
     * Bus device.
     * NOTE: only SPI bus supported.
     */
    tommRoC_hw_bus_device_t*        busDevicePtr;

    /**
     * Guard (NULL if disabled).
     */
    tommRoC_guard_t*                guardPtr;

    /**
     * Put in reset pin callback.
     */
    tommRoC_hw_gpio_set_cb_t        putInReset;

    /**
     * Remove from reset pin callback.
     */
    tommRoC_hw_gpio_set_cb_t        removeFromReset;

    /**
     * Register select command signal callback.
     */
    tommRoC_hw_gpio_set_cb_t        selectCommand;

    /**
     * Register select data signal callback.
     */
    tommRoC_hw_gpio_set_cb_t        selectData;

} tommRoC_hw_devices_display_seps525_t;

#define __EMPTY_tommRoC_hw_devices_display_seps525_t__      \
{                                                           \
    /* .busDevicePtr */     NULL,                           \
    /* .guardPtr */         NULL,                           \
    /* .putInReset */       NULL,                           \
    /* .removeFromReset */  NULL,                           \
    /* .selectCommand */    NULL,                           \
    /* .selectData */       NULL,                           \
}

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
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplaySEPS525InitSPI(
        const   tommRoC_hw_gpio_set_cb_t                            chipSelect,
        const   tommRoC_hw_gpio_set_cb_t                            chipDeSelect,
        const   tommRoC_hw_bus_t*                           const   busHandlerPtr,
        const   tommRoC_guard_t*                            const   guardPtr,
                tommRoC_hw_bus_device_specific_spi_slave_t* const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                    const   busDevicePtr);

/**
 * Start a SEPS525 based display.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        guardPtr                guard (NULL if none).
 * param[in]        putInReset              display put in reset function.
 * param[in]        removeFromReset         display remove from reset function.
 * param[in]        selectCommand           display select command function.
 * param[in]        selectData              display select data function.
 * param[out]       dpyPtr                  display handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplaySEPS525Start(
        const   tommRoC_hw_bus_device_t*                const   busDevicePtr,
        const   tommRoC_guard_t*                        const   guardPtr,
        const   tommRoC_hw_gpio_set_cb_t                        putInReset,
        const   tommRoC_hw_gpio_set_cb_t                        removeFromReset,
        const   tommRoC_hw_gpio_set_cb_t                        selectCommand,
        const   tommRoC_hw_gpio_set_cb_t                        selectData,
                tommRoC_hw_devices_display_seps525_t*   const   dpyPtr);

/**
 * Select a pixel of a SEPS525 based display.
 *
 * param[in]        dpyPtr                  display handle pointer.
 * param[in]        x                       x coordinate.
 * param[in]        y                       y coordinate.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplaySEPS525Goto(
        const   tommRoC_hw_devices_display_seps525_t*   const   dpyPtr,
        const   uint16_t                                        x,
        const   uint16_t                                        y);

/**
 * Put (draw) a pixel in current coordinate of a SEPS525 based display.
 *
 * param[in]        dpyPtr                  display handle pointer.
 * param[in]        colorPtr                8 bit RGB color structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplaySEPS525PutPixel(
        const   tommRoC_hw_devices_display_seps525_t*   const   dpyPtr,
        const   tommRoC_hw_color_rgb_8bit_t*            const   colorPtr);

/**
 * Draw a pixel in x/y coordinate of a SEPS525 based display.
 *
 * param[in]        dpyPtr                  display handle pointer.
 * param[in]        x                       x coordinate.
 * param[in]        y                       y coordinate.
 * param[in]        colorPtr                8 bit RGB color structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplaySEPS525DrawPixel(
        const   tommRoC_hw_devices_display_seps525_t*   const   dpyPtr,
        const   uint16_t                                        x,
        const   uint16_t                                        y,
        const   tommRoC_hw_color_rgb_8bit_t*            const   colorPtr);

/**
 * Draw a rectangle on a SEPS525 based display.
 *
 * param[in]        dpyPtr                  display handle pointer.
 * param[in]        x                       rectangle start x coordinate.
 * param[in]        y                       rectangle start y coordinate.
 * param[in]        width                   rectangle width.
 * param[in]        height                  rectangle height.
 * param[in]        colorPtr                8 bit RGB color structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplaySEPS525DrawRect(
        const   tommRoC_hw_devices_display_seps525_t*   const   dpyPtr,
        const   uint16_t                                        x,
        const   uint16_t                                        y,
        const   uint16_t                                        width,
        const   uint16_t                                        height,
        const   tommRoC_hw_color_rgb_8bit_t*            const   colorPtr);

/**
 * Draw an image on a SEPS525 based display.
 * NOTE: image data have to be an array or tommRoC_hw_color_rgb_8bit_t of size (width * height).
 *
 * param[in]        dpyPtr                  display handle pointer.
 * param[in]        x                       image start x coordinate.
 * param[in]        y                       image start y coordinate.
 * param[in]        width                   image width.
 * param[in]        height                  image height.
 * param[in]        imagePtr                8 bit RGB color structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplaySEPS525DrawImg(
        const   tommRoC_hw_devices_display_seps525_t*   const   dpyPtr,
        const   uint16_t                                        x,
        const   uint16_t                                        y,
        const   uint16_t                                        width,
        const   uint16_t                                        height,
        const   tommRoC_hw_color_rgb_8bit_t*            const   imagePtr);

/**
 * Get SEPS525 based display property.
 *
 * param[in]    dpyPtr                  display handle pointer.
 * param[in]    property                property.
 * param[out]   propValuePtr            result value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplaySEPS525GetProp(
        const   tommRoC_hw_devices_display_seps525_t*   const   dpyPtr,
        const   tommRoC_hw_display_prop_enum_t                  property,
                void*                                   const   propValuePtr);

/**
 * Set SEPS525 based display property.
 *
 * param[in]    dpyPtr                  display handle pointer.
 * param[in]    property                property.
 * param[in]    propValuePtr            value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesDisplaySEPS525SetProp(
        const   tommRoC_hw_devices_display_seps525_t*   const   dpyPtr,
        const   tommRoC_hw_display_prop_enum_t                  property,
        const   void*                                   const   propValuePtr);

#endif
