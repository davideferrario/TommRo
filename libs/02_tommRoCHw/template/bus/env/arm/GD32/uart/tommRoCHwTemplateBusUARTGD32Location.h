
#ifndef TOMMROC_HW_TEMPLATE_BUS_UART_GD32_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_UART_GD32_LOCATION_H_

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

#if defined (__TOMMROC_TEMPLATE_ARM_GD32_IS_USED__)

#include "TOMMROCHw.h"
#include "TOMMROCHwTemplate.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/
TOMMRO_C_UTIL_PACKED_PRE typedef struct TOMMRO_C_UTIL_PACKED_POST {

    GPIO_Port_TypeDef   gpioTxPort;
    uint32_t            gpioTxPin;

    GPIO_Port_TypeDef   gpioRxPort;
    uint32_t            gpioRxPin;

} tommRoC_hw_template_bus_uart_gd32_location_t;

#define __EMPTY_tommRoC_hw_template_bus_uart_gd32_location_t__  \
{                                                               \
    /* .gpioTxPort */   gpioPortA,                              \
    /* .gpioTxPin */    0,                                      \
    /* .gpioRxPort */   gpioPortA,                              \
    /* .gpioRxPin */    0,                                      \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif

#endif

#endif
