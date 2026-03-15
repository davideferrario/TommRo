
#ifndef TOMMROC_HW_TEMPLATE_BUS_I2C_SILABS_HAL_H_
#define TOMMROC_HW_TEMPLATE_BUS_I2C_SILABS_HAL_H_

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

#include "bus/env/arm/SiLabs/i2c/tommRoCHwTemplateBusI2CSiLabsLocation.h"

#include "TOMMROCHw.h"

#if (defined (I2C_PRESENT) && I2C_COUNT)
#include "em_i2c.h"
#endif

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/
typedef struct {

    CMU_Clock_TypeDef                               clock;
    void*                                           i2cPtr;
    uint32_t                                        baudRate;
    IRQn_Type                                       IRQn;
    tommRoC_hw_template_bus_i2c_silabs_location_t   location;
    tommRoC_util_enabled_status_enum_t              mcuPullUpStatus;

} tommRoC_hw_template_bus_i2c_silabs_hal_config_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (I2C_PRESENT) && I2C_COUNT
tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSiLabsHalMasterInit(const tommRoC_hw_template_bus_i2c_silabs_hal_config_t* const initConfigPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSiLabsHalSlaveInit(const tommRoC_hw_template_bus_i2c_silabs_hal_config_t* const initConfigPtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSiLabsHalSetForLowPowerEnter(const CMU_Clock_TypeDef clock, const tommRoC_hw_template_bus_i2c_silabs_location_t* const locationPtr, const tommRoC_util_enabled_status_enum_t mcuPullUpStatus);
tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSiLabsHalSetForLowPowerExit(const CMU_Clock_TypeDef clock,const tommRoC_hw_template_bus_i2c_silabs_location_t* const locationPtr, const tommRoC_util_enabled_status_enum_t mcuPullUpStatus);
#endif

#endif

#endif

#endif
