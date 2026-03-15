
#ifndef TOMMROC_HW_TEMPLATE_BUS_SPI_NXP_HAL_H_
#define TOMMROC_HW_TEMPLATE_BUS_SPI_NXP_HAL_H_

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

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)

#include "bus/env/arm/NXP/spi/tommRoCHwTemplateBusSPINXPLocation.h"

#include "TOMMROCHw.h"

#include "fsl_clock.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/
typedef struct {

    void*                                       spiPtr;
    void*                                       configPtr;
    clock_name_t                                clockName;
    tommRoC_hw_template_bus_spi_nxp_location_t  location;

} tommRoC_hw_template_bus_spi_nxp_hal_config_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#if (defined (FSL_FEATURE_SOC_SPI_COUNT) && FSL_FEATURE_SOC_SPI_COUNT) || (defined (FSL_FEATURE_SOC_DSPI_COUNT) && FSL_FEATURE_SOC_DSPI_COUNT)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPINXPHalMasterInit(const tommRoC_hw_template_bus_spi_nxp_hal_config_t* const initConfigPtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPINXPHalSlaveInit(const tommRoC_hw_template_bus_spi_nxp_hal_config_t* const initConfigPtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPINXPHalSetForLowPowerEnter(const tommRoC_hw_template_bus_spi_nxp_location_t* const locationPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPINXPHalSetForLowPowerExit(const tommRoC_hw_template_bus_spi_nxp_location_t* const locationPtr);
#endif

#endif

#endif

#endif
