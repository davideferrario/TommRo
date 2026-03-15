
#ifndef TOMMROC_HW_TEMPLATE_BUS_UART_QN908XC_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_UART_QN908XC_LOCATION_H_

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

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__)

#include "fsl_iocon.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/******************* USART0 location */

#define UART_0_LOCATION_0_CLOCK_NAME                        (kCLOCK_Flexcomm0)
#define UART_0_LOCATION_0_TX_PORT_IDX                       (0)
#define UART_0_LOCATION_0_TX_PIN                            (16U)
#define UART_0_LOCATION_0_TX_IOCON_FUNC                     (IOCON_FUNC4)
#define UART_0_LOCATION_0_RX_PORT_IDX                       (0)
#define UART_0_LOCATION_0_RX_PIN                            (17U)
#define UART_0_LOCATION_0_RX_IOCON_FUNC                     (IOCON_FUNC4)

#define UART_0_LOCATION_0_TX_GPIO                           (GPIOA)
#define UART_0_LOCATION_0_RX_GPIO                           (GPIOA)

#define UART_0_LOCATION_1_CLOCK_NAME                        (kCLOCK_Flexcomm0)
#define UART_0_LOCATION_1_TX_PORT_IDX                       (0)
#define UART_0_LOCATION_1_TX_PIN                            (4U)
#define UART_0_LOCATION_1_TX_IOCON_FUNC                     (IOCON_FUNC4)
#define UART_0_LOCATION_1_RX_PORT_IDX                       (0)
#define UART_0_LOCATION_1_RX_PIN                            (5U)
#define UART_0_LOCATION_1_RX_IOCON_FUNC                     (IOCON_FUNC4)

#define UART_0_LOCATION_1_TX_GPIO                           (GPIOA)
#define UART_0_LOCATION_1_RX_GPIO                           (GPIOA)


/******************* USART1 location */

#define UART_1_LOCATION_0_CLOCK_NAME                        (kCLOCK_Flexcomm1)
#define UART_1_LOCATION_0_TX_PORT_IDX                       (0)
#define UART_1_LOCATION_0_TX_PIN                            (12U)
#define UART_1_LOCATION_0_TX_IOCON_FUNC                     (IOCON_FUNC4)
#define UART_1_LOCATION_0_RX_PORT_IDX                       (0)
#define UART_1_LOCATION_0_RX_PIN                            (13U)
#define UART_1_LOCATION_0_RX_IOCON_FUNC                     (IOCON_FUNC4)

#define UART_1_LOCATION_0_TX_GPIO                           (GPIOA)
#define UART_1_LOCATION_0_RX_GPIO                           (GPIOA)

#define UART_1_LOCATION_1_CLOCK_NAME                        (kCLOCK_Flexcomm1)
#define UART_1_LOCATION_1_TX_PORT_IDX                       (0)
#define UART_1_LOCATION_1_TX_PIN                            (8U)
#define UART_1_LOCATION_1_TX_IOCON_FUNC                     (IOCON_FUNC4)
#define UART_1_LOCATION_1_RX_PORT_IDX                       (0)
#define UART_1_LOCATION_1_RX_PIN                            (9U)
#define UART_1_LOCATION_1_RX_IOCON_FUNC                     (IOCON_FUNC4)

#define UART_1_LOCATION_1_TX_GPIO                           (GPIOA)
#define UART_1_LOCATION_1_RX_GPIO                           (GPIOA)

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
