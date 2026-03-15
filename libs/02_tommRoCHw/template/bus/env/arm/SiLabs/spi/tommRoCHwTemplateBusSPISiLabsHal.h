
#ifndef TOMMROC_HW_TEMPLATE_BUS_SPI_SILABS_HAL_H_
#define TOMMROC_HW_TEMPLATE_BUS_SPI_SILABS_HAL_H_

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
#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)

#include "bus/env/arm/SiLabs/spi/tommRoCHwTemplateBusSPISiLabsLocation.h"

#include "TOMMROCHw.h"

#if (defined (USART_PRESENT) && USART_COUNT)
#include "em_usart.h"
#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/
typedef struct {

    CMU_Clock_TypeDef                               clock;
    void*                                           spiPtr;
    uint32_t                                        baudRate;
    USART_ClockMode_TypeDef                         clockMode;
    tommRoC_hw_template_bus_spi_silabs_location_t   location;

} tommRoC_hw_template_bus_spi_silabs_hal_config_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (USART_PRESENT) && USART_COUNT
tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISiLabsHalMasterInit(const tommRoC_hw_template_bus_spi_silabs_hal_config_t* const initConfigPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISiLabsHalSlaveInit(const tommRoC_hw_template_bus_spi_silabs_hal_config_t* const initConfigPtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISiLabsHalSetForLowPowerEnter(const CMU_Clock_TypeDef clock, const tommRoC_hw_template_bus_spi_silabs_location_t* const locationPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISiLabsHalSetForLowPowerExit(const CMU_Clock_TypeDef clock, const tommRoC_hw_template_bus_spi_silabs_location_t* const locationPtr);
#endif

#endif

#endif

#endif
