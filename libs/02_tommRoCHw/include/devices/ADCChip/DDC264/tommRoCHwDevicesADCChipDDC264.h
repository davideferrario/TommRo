
#ifndef TOMMROC_HW_DEVICES_ADC_CHIP_DDC264_H_
#define TOMMROC_HW_DEVICES_ADC_CHIP_DDC264_H_

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

/**
 * DDC264 ADC chip available channels amount
 */
#define TOMMRO_C_HW_DEVICES_ADC_CHIP_DDC264_CHANNELS_AMOUNT     (64)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of supported full scale range.
typedef enum {

    /**
     * FSR = 12.5 pC (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_DDC264_FSR_12_5_PC = 0,

    /**
     * FSR = 50.0 pC
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_DDC264_FSR_50_PC,

    /**
     * FSR = 100.0 pC
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_DDC264_FSR_100_PC,

    /**
     * FSR = 150.0 pC
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_DDC264_FSR_150_PC,

} tommRoC_hw_devices_adc_chip_ddc264_full_scale_range_enum_t;


// tommRoC hardware adc chip driver DDC264.
typedef struct {

    /**
     * Config bus.
     * NOTE: only SPI bus supported.
     * NOTE: only SPI transmission bus is needed.
     */
    tommRoC_hw_bus_t*               configBusPtr;

    /**
     * Data bus.
     * NOTE: only SPI bus supported.
     */
    tommRoC_hw_bus_t*               dataBusPtr;

    /**
     * Guard (NULL if disabled).
     */
    tommRoC_guard_t*                guardPtr;

    /*
     * Disable clock pin callback;
     */
    tommRoC_hw_gpio_common_cb_t     disableClk;

    /*
     * Enable clock pin callback;
     */
    tommRoC_hw_gpio_common_cb_t     enableClk;

    /**
     * Put in reset pin callback.
     */
    tommRoC_hw_gpio_set_cb_t        putInReset;

    /**
     * Remove from reset pin callback.
     */
    tommRoC_hw_gpio_set_cb_t        removeFromReset;

    /**
     * Conversion pin set to low callback.
     */
    tommRoC_hw_gpio_set_cb_t        convToLow;

    /**
     * Conversion pin toggle callback.
     */
    tommRoC_hw_gpio_set_cb_t        convToggle;

    /**
     * Get data valid pin status.
     */
    tommRoC_hw_gpio_get_cb_t        dataValidStatus;

    /**
     * Full scale range.
     */
    tommRoC_hw_devices_adc_chip_ddc264_full_scale_range_enum_t  fsRange;

} tommRoC_hw_devices_adc_chip_ddc264_t;

#define __EMPTY_tommRoC_hw_devices_adc_chip_ddc264_t__                              \
{                                                                                   \
    /* .configBusPtr */         NULL,                                               \
    /* .dataBusPtr */           NULL,                                               \
    /* .guardPtr */             NULL,                                               \
    /* .disableClk */           NULL,                                               \
    /* .enableClk */            NULL,                                               \
    /* .putInReset */           NULL,                                               \
    /* .removeFromReset */      NULL,                                               \
    /* .convToLow */            NULL,                                               \
    /* .convToggle */           NULL,                                               \
    /* .dataValidStatus */      NULL,                                               \
    /* .fsRange */              TOMMRO_C_HW_DEVICES_ADC_CHIP_DDC264_FSR_12_5_PC,    \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Start chip.
 *
 * param[in]        configBusPtr            configuration bus pointer.
 * param[in]        dataBusPtr              data bus pointer.
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[in]        disableClk              disable clock function pointer.
 * param[in]        enableClk               enable clock function pointer.
 * param[in]        putInReset              put in reset function pointer.
 * param[in]        removeFromReset         remove from reset function pointer.
 * param[in]        convToLow               pin conversion set low function pointer.
 * param[in]        convToggle              pin conversion toggle function pointer.
 * param[in]        dataValidStatus         read data valid status function pointer.
 * param[in]        fsRange                 full scale range.
 * param[out]       adcChipPtr              output chip pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipDDC264Start(
        const   tommRoC_hw_bus_t*                                           const   configBusPtr,
        const   tommRoC_hw_bus_t*                                           const   dataBusPtr,
        const   tommRoC_guard_t*                                            const   guardPtr,
        const   tommRoC_hw_gpio_common_cb_t                                         disableClk,
        const   tommRoC_hw_gpio_common_cb_t                                         enableClk,
        const   tommRoC_hw_gpio_set_cb_t                                            putInReset,
        const   tommRoC_hw_gpio_set_cb_t                                            removeFromReset,
        const   tommRoC_hw_gpio_set_cb_t                                            convToLow,
        const   tommRoC_hw_gpio_set_cb_t                                            convToggle,
        const   tommRoC_hw_gpio_get_cb_t                                            dataValidStatus,
        const   tommRoC_hw_devices_adc_chip_ddc264_full_scale_range_enum_t          fsRange,
                tommRoC_hw_devices_adc_chip_ddc264_t*                       const   adcChipPtr);

/**
 * Get all values.
 *
 * param[in]        adcChipPtr              chip pointer.
 * param[in]        skipSampleAmount        skip sample amount (before read).
 * param[in]        integrationTimeMsec     integration time [msec].
 * param[out]       samplesPicoCPtr         output samples result pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipDDC264GetAll(
        const   tommRoC_hw_devices_adc_chip_ddc264_t*                       const   adcChipPtr,
        const   uint8_t                                                             skipSampleAmount,
        const   uint32_t                                                            integrationTimeMsec,
                float*                                                      const   samplesPicoCPtr);

#endif
