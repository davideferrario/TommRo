
#ifndef TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_SW_MODE_3_H_
#define TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_SW_MODE_3_H_

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
#include <stdint.h>

#include "bus/spi/master/sw/base/gpio/tommRoCHwTemplateBusSPIMasterSwBaseGPIO.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

void tommRoCHwTemplateBusSPIMasterSwMode3WriteByte(
        const   uint8_t                                                     data,
        const   tommRoC_hw_template_bus_spi_master_sw_base_gpio_t*  const   spiMasterSwBaseGpioPtr);

void tommRoCHwTemplateBusSPIMasterSwMode3WriteByteNoDelay(
        const   uint8_t                                                     data,
        const   tommRoC_hw_template_bus_spi_master_sw_base_gpio_t*  const   spiMasterSwBaseGpioPtr);

uint8_t tommRoCHwTemplateBusSPIMasterSwMode3ReadByte(
        const   tommRoC_hw_template_bus_spi_master_sw_base_gpio_t*  const   spiMasterSwBaseGpioPtr);

uint8_t tommRoCHwTemplateBusSPIMasterSwMode3ReadByteNoDelay(
        const   tommRoC_hw_template_bus_spi_master_sw_base_gpio_t*  const   spiMasterSwBaseGpioPtr);

#endif
