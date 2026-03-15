
#ifndef TOMMROC_HW_TEMPLATE_BUS_UART_ESP32_HAL_H_
#define TOMMROC_HW_TEMPLATE_BUS_UART_ESP32_HAL_H_

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
#include "bus/env/esp32/uart/prop/tommRoCHwTemplateBusUARTESP32HalPropGet.h"
#include "bus/env/esp32/uart/prop/tommRoCHwTemplateBusUARTESP32HalPropSet.h"

#include "env/tommRoCTemplateEnv.h"

#include "TOMMROCHw.h"

#if (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
#include "soc/gpio_num.h"
#endif

#include "driver/gpio.h"
#include "driver/uart.h"

/*******************************************************************************
 * defines
 ******************************************************************************/
#define TOMMROC_HW_TEMPLATE_BUS_UART_ESP32_HAL_MINIMUM_BUFFER_SIZE  (SOC_UART_FIFO_LEN + TOMMROC_UTIL_U32_SIZE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/
typedef struct {

    uart_port_t     uartPort;
    uart_config_t   uartConfig;
    uint16_t        txBufferSize;
    uint16_t        rxBufferSize;
    gpio_num_t      txGPIONum;
    gpio_num_t      rxGPIONum;

} tommRoC_hw_template_bus_uart_esp32_hal_config_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTESP32HalInit(const tommRoC_hw_template_bus_uart_esp32_hal_config_t* const initConfigPtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTESP32HalSetForLowPowerEnter(const uart_port_t uartPort, const gpio_num_t txGPIONum, const gpio_num_t rxGPIONum);
tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTESP32HalSetForLowPowerExit(const uart_port_t uartPort, const gpio_num_t txGPIONum, const gpio_num_t rxGPIONum);

#endif

#endif
