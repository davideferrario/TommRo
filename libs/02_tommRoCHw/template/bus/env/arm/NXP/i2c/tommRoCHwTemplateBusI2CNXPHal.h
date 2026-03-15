
#ifndef TOMMROC_HW_TEMPLATE_BUS_I2C_NXP_HAL_H_
#define TOMMROC_HW_TEMPLATE_BUS_I2C_NXP_HAL_H_

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

#include "bus/env/arm/NXP/i2c/tommRoCHwTemplateBusI2CNXPLocation.h"

#include "TOMMROCHw.h"

#include "fsl_clock.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/
typedef struct {

    void*                                       i2cPtr;
    void*                                       configPtr;
    clock_name_t                                clockName;
    tommRoC_hw_template_bus_i2c_nxp_location_t  location;
    tommRoC_util_enabled_status_enum_t          mcuPullUpStatus;

} tommRoC_hw_template_bus_i2c_nxp_hal_config_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (FSL_FEATURE_SOC_I2C_COUNT) && FSL_FEATURE_SOC_I2C_COUNT
tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CNXPHalMasterInit(const tommRoC_hw_template_bus_i2c_nxp_hal_config_t* const initConfigPtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CNXPHalSlaveInit(const tommRoC_hw_template_bus_i2c_nxp_hal_config_t* const initConfigPtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CNXPHalSetForLowPowerEnter(const tommRoC_hw_template_bus_i2c_nxp_location_t* const locationPtr, const tommRoC_util_enabled_status_enum_t mcuPullUpStatus);
tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CNXPHalSetForLowPowerExit(const tommRoC_hw_template_bus_i2c_nxp_location_t* const locationPtr, const tommRoC_util_enabled_status_enum_t mcuPullUpStatus);
#endif

#endif

#endif

#endif

