
#ifndef TOMMROC_HW_TEMPLATE_BUS_I2C_NORDIC_HAL_H_
#define TOMMROC_HW_TEMPLATE_BUS_I2C_NORDIC_HAL_H_

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

#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)

#include "TOMMROCHw.h"

#if (defined (TWI_PRESENT) && TWI_COUNT)
#include "nrfx_twi.h"
#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/
typedef struct {

    nrfx_twi_t              nrfxTwi;
    nrf_twi_frequency_t     frequency;
    uint32_t                sclPin;
    uint32_t                sdaPin;
    nrfx_twi_evt_handler_t  nrfxTwiEvtHandler;

} tommRoC_hw_template_bus_i2c_nordic_hal_config_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#if (defined (TWI_PRESENT) && TWI_COUNT)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CNordicHalMasterInit(const tommRoC_hw_template_bus_i2c_nordic_hal_config_t* const initConfigPtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CNordicHalSetForLowPowerEnter(const uint32_t sclPin, const uint32_t sdaPin);
tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CNordicHalSetForLowPowerExit(const uint32_t sclPin, const uint32_t sdaPin);
#endif

#endif

#endif

#endif
