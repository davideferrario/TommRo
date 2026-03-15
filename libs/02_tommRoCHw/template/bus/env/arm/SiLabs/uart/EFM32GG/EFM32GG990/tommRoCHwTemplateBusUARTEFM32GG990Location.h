
#ifndef TOMMROC_HW_TEMPLATE_BUS_UART_EFM32GG990_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_UART_EFM32GG990_LOCATION_H_

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

#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_EFM32GG_IS_USED__)

#if (defined (USART_PRESENT) && USART_COUNT)
#include "em_usart.h"
#endif
#if (defined (LEUART_PRESENT) && LEUART_COUNT)
#include "em_leuart.h"
#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

#if defined (EFM32GG990F1024)       ||  \
    defined (EFM32GG990F512)

/******************* USART0 location */

#define UART_0_LOCATION_0_TX_PORT           (gpioPortE)
#define UART_0_LOCATION_0_TX_PIN            (10)
#define UART_0_LOCATION_0_RX_PORT           (gpioPortE)
#define UART_0_LOCATION_0_RX_PIN            (11)

#define UART_0_LOCATION_1_TX_PORT           (gpioPortE)
#define UART_0_LOCATION_1_TX_PIN            (7)
#define UART_0_LOCATION_1_RX_PORT           (gpioPortE)
#define UART_0_LOCATION_1_RX_PIN            (6)

#define UART_0_LOCATION_2_TX_PORT           (gpioPortC)
#define UART_0_LOCATION_2_TX_PIN            (11)
#define UART_0_LOCATION_2_RX_PORT           (gpioPortC)
#define UART_0_LOCATION_2_RX_PIN            (10)

#define UART_0_LOCATION_3_TX_PORT           (gpioPortE)
#define UART_0_LOCATION_3_TX_PIN            (13)
#define UART_0_LOCATION_3_RX_PORT           (gpioPortE)
#define UART_0_LOCATION_3_RX_PIN            (12)

#define UART_0_LOCATION_4_TX_PORT           (gpioPortB)
#define UART_0_LOCATION_4_TX_PIN            (7)
#define UART_0_LOCATION_4_RX_PORT           (gpioPortB)
#define UART_0_LOCATION_4_RX_PIN            (8)

#define UART_0_LOCATION_5_TX_PORT           (gpioPortC)
#define UART_0_LOCATION_5_TX_PIN            (0)
#define UART_0_LOCATION_5_RX_PORT           (gpioPortC)
#define UART_0_LOCATION_5_RX_PIN            (1)


/******************* USART1 location */

#define UART_1_LOCATION_0_TX_PORT           (gpioPortC)
#define UART_1_LOCATION_0_TX_PIN            (0)
#define UART_1_LOCATION_0_RX_PORT           (gpioPortC)
#define UART_1_LOCATION_0_RX_PIN            (1)

#define UART_1_LOCATION_1_TX_PORT           (gpioPortD)
#define UART_1_LOCATION_1_TX_PIN            (0)
#define UART_1_LOCATION_1_RX_PORT           (gpioPortD)
#define UART_1_LOCATION_1_RX_PIN            (1)

#define UART_1_LOCATION_2_TX_PORT           (gpioPortD)
#define UART_1_LOCATION_2_TX_PIN            (7)
#define UART_1_LOCATION_2_RX_PORT           (gpioPortD)
#define UART_1_LOCATION_2_RX_PIN            (6)


/******************* USART2 location */

#define UART_2_LOCATION_0_TX_PORT           (gpioPortC)
#define UART_2_LOCATION_0_TX_PIN            (2)
#define UART_2_LOCATION_0_RX_PORT           (gpioPortC)
#define UART_2_LOCATION_0_RX_PIN            (3)

#define UART_2_LOCATION_1_TX_PORT           (gpioPortB)
#define UART_2_LOCATION_1_TX_PIN            (3)
#define UART_2_LOCATION_1_RX_PORT           (gpioPortB)
#define UART_2_LOCATION_1_RX_PIN            (4)


/******************* LEUART0 location */

#define LEUART_0_LOCATION_0_TX_PORT         (gpioPortD)
#define LEUART_0_LOCATION_0_TX_PIN          (4)
#define LEUART_0_LOCATION_0_RX_PORT         (gpioPortD)
#define LEUART_0_LOCATION_0_RX_PIN          (5)

#define LEUART_0_LOCATION_1_TX_PORT         (gpioPortB)
#define LEUART_0_LOCATION_1_TX_PIN          (13)
#define LEUART_0_LOCATION_1_RX_PORT         (gpioPortB)
#define LEUART_0_LOCATION_1_RX_PIN          (14)

#define LEUART_0_LOCATION_2_TX_PORT         (gpioPortE)
#define LEUART_0_LOCATION_2_TX_PIN          (14)
#define LEUART_0_LOCATION_2_RX_PORT         (gpioPortE)
#define LEUART_0_LOCATION_2_RX_PIN          (15)

#define LEUART_0_LOCATION_3_TX_PORT         (gpioPortF)
#define LEUART_0_LOCATION_3_TX_PIN          (0)
#define LEUART_0_LOCATION_3_RX_PORT         (gpioPortF)
#define LEUART_0_LOCATION_3_RX_PIN          (1)

#define LEUART_0_LOCATION_4_TX_PORT         (gpioPortF)
#define LEUART_0_LOCATION_4_TX_PIN          (2)
#define LEUART_0_LOCATION_4_RX_PORT         (gpioPortA)
#define LEUART_0_LOCATION_4_RX_PIN          (0)


/******************* LEUART1 location */

#define LEUART_1_LOCATION_0_TX_PORT         (gpioPortC)
#define LEUART_1_LOCATION_0_TX_PIN          (6)
#define LEUART_1_LOCATION_0_RX_PORT         (gpioPortC)
#define LEUART_1_LOCATION_0_RX_PIN          (7)

#define LEUART_1_LOCATION_1_TX_PORT         (gpioPortA)
#define LEUART_1_LOCATION_1_TX_PIN          (5)
#define LEUART_1_LOCATION_1_RX_PORT         (gpioPortA)
#define LEUART_1_LOCATION_1_RX_PIN          (6)

#endif

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
