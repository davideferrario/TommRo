
#ifndef TOMMROC_HW_TEMPLATE_BUS_I2C_ESP32_HAL_H_
#define TOMMROC_HW_TEMPLATE_BUS_I2C_ESP32_HAL_H_

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

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)

#include "TOMMROCHw.h"

#include "driver/gpio.h"
#include "driver/i2c.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/
typedef struct {

    i2c_port_t      i2cPort;
    i2c_config_t    i2cConfig;

} tommRoC_hw_template_bus_i2c_esp32_hal_config_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CESP32HalMasterInit(const tommRoC_hw_template_bus_i2c_esp32_hal_config_t* const initConfigPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CESP32HalSlaveInit(const tommRoC_hw_template_bus_i2c_esp32_hal_config_t* const initConfigPtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CESP32HalSetForLowPowerEnter(const i2c_port_t i2cPort, const gpio_num_t sdaGPIONum, const gpio_num_t sclGPIONum);
tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CESP32HalSetForLowPowerExit(const i2c_port_t i2cPort, const gpio_num_t sdaGPIONum, const gpio_num_t sclGPIONum);

#endif

#endif
