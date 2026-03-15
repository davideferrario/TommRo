
#ifndef TOMMROC_HW_TEMPLATE_BUS_UART_NORDIC_HAL_H_
#define TOMMROC_HW_TEMPLATE_BUS_UART_NORDIC_HAL_H_

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

#if (defined (UART_PRESENT) && UART_COUNT)
#include "nrfx_uart.h"
#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/
typedef struct {

    nrfx_uart_t                 nrfxUart;
    nrf_uart_baudrate_t         baudRate;
    uint32_t                    pselTXD;
    uint32_t                    pselRXD;
    nrfx_uart_event_handler_t   nrfxUartEventHandler;

} tommRoC_hw_template_bus_uart_nordic_hal_config_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#if (defined (UART_PRESENT) && UART_COUNT)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTNordicHalInit(const tommRoC_hw_template_bus_uart_nordic_hal_config_t* const initConfigPtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTNordicHalSetForLowPowerEnter(const uint32_t pselTXD, const uint32_t pselRXD);
tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTNordicHalSetForLowPowerExit(const uint32_t pselTXD, const uint32_t pselRXD);
#endif

#endif

#endif

#endif
