
#ifndef TOMMROC_HW_DEVICES_ADC_CHIP_HX711_H_
#define TOMMROC_HW_DEVICES_ADC_CHIP_HX711_H_

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
#include "tommRoCHwErr.h"
#include "tommRoCHwGPIO.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Device data.
#define TOMMROC_HW_DEVICES_ADC_CHIP_HX711_DEVICE_SIZE   (   TOMMROC_UTIL_PTR_SIZE       +   \
                                                            TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                            TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                            TOMMROC_UTIL_FUNCT_PTR_SIZE     )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of HX711 reading channels properties.
typedef enum {

    /**
     * Channel A with gain of 128 mode.
     * From datasheet: corresponding to a full-scale differential input voltage of +/-20mV when a 5V supply is connected to AVDD.
     *
     * Available:   get
     * Notes:       propValuePtr has to be int32_t*
     */
    TOMMROC_HW_DEVICES_ADC_CHIP_HX711_CHANNEL_A_GAIN_128 = 0,

    /**
     * Channel A with gain of 64 mode.
     * From datasheet: corresponding to a full-scale differential input voltage of +/-40mV when a 5V supply is connected to AVDD.
     *
     * Available:   set
     * Notes:       propValuePtr has to be int32_t*
     */
    TOMMROC_HW_DEVICES_ADC_CHIP_HX711_CHANNEL_A_GAIN_64,

    /**
     * Channel B with gain of 32 mode.
     * From datasheet: corresponding to a full-scale differential input voltage of +/-80mV when a 5V supply is connected to AVDD.
     *
     * Available:   set
     * Notes:       propValuePtr has to be int32_t*
     */
    TOMMROC_HW_DEVICES_ADC_CHIP_HX711_CHANNEL_B_GAIN_32,

} tommRoC_hw_devices_adc_chip_hx711_channel_enum_t;


// Device.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_ADC_CHIP_HX711_DEVICE_SIZE];
} tommRoC_hw_devices_adc_chip_hx711_device_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Start chip.
 *
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[in]        PDSCKLow                set PD_SCK pin low function pointer.
 * param[in]        PDSCKHigh               set PD_SCK pin high function pointer.
 * param[in]        DOUTStatus              get DOUT pin status function pointer.
 * param[out]       hx711DevicePtr          HX711 device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipHX711Start(
        const   tommRoC_guard_t*                                    const   guardPtr,
        const   tommRoC_hw_gpio_set_cb_t                                    PDSCKLow,
        const   tommRoC_hw_gpio_set_cb_t                                    PDSCKHigh,
        const   tommRoC_hw_gpio_get_cb_t                                    DOUTStatus,
                tommRoC_hw_devices_adc_chip_hx711_device_t*         const   hx711DevicePtr);

/**
 * Read ADC raw value.
 *
 * param[in]        hx711DevicePtr          HX711 device pointer.
 * param[in]        channel                 channel selection.
 * param[out]       rawValuePtr             output ADC raw value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipHX711Read(
        const   tommRoC_hw_devices_adc_chip_hx711_device_t*         const   hx711DevicePtr,
        const   tommRoC_hw_devices_adc_chip_hx711_channel_enum_t            channel,
                int32_t*                                            const   rawValuePtr);

#endif
