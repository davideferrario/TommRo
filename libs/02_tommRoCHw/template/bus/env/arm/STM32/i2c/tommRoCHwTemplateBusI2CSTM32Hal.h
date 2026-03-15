
#ifndef TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_HAL_H_
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_HAL_H_

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

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)

#include "bus/i2c/master/tommRoCHwTemplateBusI2CMasterDEF.h"
#include "bus/i2c/slave/tommRoCHwTemplateBusI2CSlaveDEF.h"

#if defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_DEF_AT_LEAST_ONE_IS_USED__) || defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_SLAVE_DEF_AT_LEAST_ONE_IS_USED__)

#include "TOMMROCHw.h"

#include "i2c.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSTM32HalSetForLowPowerEnter(I2C_HandleTypeDef* const i2cHandlePtr, const tommRoC_util_enabled_status_enum_t mcuPullUpStatus);
tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSTM32HalSetForLowPowerExit(I2C_HandleTypeDef* const i2cHandlePtr, const tommRoC_util_enabled_status_enum_t mcuPullUpStatus);

#endif

#endif

#endif

#endif
