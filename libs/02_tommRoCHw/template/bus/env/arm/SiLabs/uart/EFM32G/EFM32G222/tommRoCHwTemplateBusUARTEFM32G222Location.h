
#ifndef TOMMROC_HW_TEMPLATE_BUS_UART_EFM32G222_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_UART_EFM32G222_LOCATION_H_

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
#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_EFM32G_IS_USED__)

#if (defined (USART_PRESENT) && USART_COUNT)
#include "em_usart.h"
#endif
#if (defined (LEUART_PRESENT) && LEUART_COUNT)
#include "em_leuart.h"
#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

#if defined (EFM32G222F128)         ||  \
    defined (EFM32G222F32)          ||  \
    defined (EFM32G222F64)

/******************* USART0 location */

#define UART_0_LOCATION_0_TX_PORT           (gpioPortE)
#define UART_0_LOCATION_0_TX_PIN            (10)
#define UART_0_LOCATION_0_RX_PORT           (gpioPortE)
#define UART_0_LOCATION_0_RX_PIN            (11)

#define UART_0_LOCATION_2_TX_PORT           (gpioPortC)
#define UART_0_LOCATION_2_TX_PIN            (11)
#define UART_0_LOCATION_2_RX_PORT           (gpioPortC)
#define UART_0_LOCATION_2_RX_PIN            (10)


/******************* USART1 location */

#define UART_1_LOCATION_0_TX_PORT           (gpioPortC)
#define UART_1_LOCATION_0_TX_PIN            (0)
#define UART_1_LOCATION_0_RX_PORT           (gpioPortC)
#define UART_1_LOCATION_0_RX_PIN            (1)


/******************* LEUART0 location */

#define LEUART_0_LOCATION_0_TX_PORT         (gpioPortD)
#define LEUART_0_LOCATION_0_TX_PIN          (4)
#define LEUART_0_LOCATION_0_RX_PORT         (gpioPortD)
#define LEUART_0_LOCATION_0_RX_PIN          (5)

#define LEUART_0_LOCATION_1_TX_PORT         (gpioPortB)
#define LEUART_0_LOCATION_1_TX_PIN          (13)
#define LEUART_0_LOCATION_1_RX_PORT         (gpioPortB)
#define LEUART_0_LOCATION_1_RX_PIN          (14)

#endif

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
