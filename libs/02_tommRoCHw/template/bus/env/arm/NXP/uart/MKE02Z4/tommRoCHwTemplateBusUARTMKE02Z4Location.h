
#ifndef TOMMROC_HW_TEMPLATE_BUS_UART_MKE02Z4_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_UART_MKE02Z4_LOCATION_H_

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

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)

/*******************************************************************************
 * defines
 ******************************************************************************/

/******************* USART0 location */

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define UART_0_LOCATION_0_CLOCK_NAME                        (kCLOCK_PortB)
#define UART_0_LOCATION_0_TX_PORT                           (PORTB)
#define UART_0_LOCATION_0_TX_PIN                            (1U)
#define UART_0_LOCATION_0_TX_PORT_MUX                       (kPORT_MuxAlt2)
#define UART_0_LOCATION_0_RX_PORT                           (PORTB)
#define UART_0_LOCATION_0_RX_PIN                            (0U)
#define UART_0_LOCATION_0_RX_PORT_MUX                       (kPORT_MuxAlt2)

#define UART_0_LOCATION_0_TX_GPIO                           (GPIOB)
#define UART_0_LOCATION_0_RX_GPIO                           (GPIOB)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION) || (MAKE_VERSION(2, 0, 2) == FSL_PORT_DRIVER_VERSION)
#define UART_0_LOCATION_0_CLOCK_NAME                        (kCLOCK_Uart0)
#define UART_0_LOCATION_0_PORT_SET_PIN_SELECT_NEEDED        (true)
#define UART_0_LOCATION_0_PORT_MODULE                       (kPORT_UART0)
#define UART_0_LOCATION_0_PORT_PIN_SELECT                   (kPORT_UART0_RXPTB0_TXPTB1)

#define UART_0_LOCATION_0_TX_PORT                           (kGPIO_PORTB)
#define UART_0_LOCATION_0_TX_PIN                            (1U)
#define UART_0_LOCATION_0_RX_PORT                           (kGPIO_PORTB)
#define UART_0_LOCATION_0_RX_PIN                            (0U)
#endif

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define UART_0_LOCATION_1_CLOCK_NAME                        (kCLOCK_PortA)
#define UART_0_LOCATION_1_TX_PORT                           (PORTA)
#define UART_0_LOCATION_1_TX_PIN                            (3U)
#define UART_0_LOCATION_1_TX_PORT_MUX                       (kPORT_MuxAlt2)
#define UART_0_LOCATION_1_RX_PORT                           (PORTA)
#define UART_0_LOCATION_1_RX_PIN                            (2U)
#define UART_0_LOCATION_1_RX_PORT_MUX                       (kPORT_MuxAlt2)

#define UART_0_LOCATION_1_TX_GPIO                           (GPIOA)
#define UART_0_LOCATION_1_RX_GPIO                           (GPIOA)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION) || (MAKE_VERSION(2, 0, 2) == FSL_PORT_DRIVER_VERSION)
#define UART_0_LOCATION_1_CLOCK_NAME                        (kCLOCK_Uart0)
#define UART_0_LOCATION_1_PORT_SET_PIN_SELECT_NEEDED        (true)
#define UART_0_LOCATION_1_PORT_MODULE                       (kPORT_UART0)
#define UART_0_LOCATION_1_PORT_PIN_SELECT                   (kPORT_UART0_RXPTA2_TXPTA3)

#define UART_0_LOCATION_1_TX_PORT                           (kGPIO_PORTA)
#define UART_0_LOCATION_1_TX_PIN                            (3U)
#define UART_0_LOCATION_1_RX_PORT                           (kGPIO_PORTA)
#define UART_0_LOCATION_1_RX_PIN                            (2U)
#endif


/******************* USART1 location */

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define UART_1_LOCATION_0_CLOCK_NAME                        (kCLOCK_PortC)
#define UART_1_LOCATION_0_TX_PORT                           (PORTC)
#define UART_1_LOCATION_0_TX_PIN                            (7U)
#define UART_1_LOCATION_0_TX_PORT_MUX                       (kPORT_MuxAlt2)
#define UART_1_LOCATION_0_RX_PORT                           (PORTC)
#define UART_1_LOCATION_0_RX_PIN                            (6U)
#define UART_1_LOCATION_0_RX_PORT_MUX                       (kPORT_MuxAlt2)

#define UART_1_LOCATION_0_TX_GPIO                           (GPIOC)
#define UART_1_LOCATION_0_RX_GPIO                           (GPIOC)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION) || (MAKE_VERSION(2, 0, 2) == FSL_PORT_DRIVER_VERSION)
#define UART_1_LOCATION_0_CLOCK_NAME                        (kCLOCK_Uart1)
#define UART_1_LOCATION_0_PORT_SET_PIN_SELECT_NEEDED        (false)
#define UART_1_LOCATION_0_PORT_MODULE                       (0)
#define UART_1_LOCATION_0_PORT_PIN_SELECT                   (0)

#define UART_1_LOCATION_0_TX_PORT                           (kGPIO_PORTC)
#define UART_1_LOCATION_0_TX_PIN                            (7U)
#define UART_1_LOCATION_0_RX_PORT                           (kGPIO_PORTC)
#define UART_1_LOCATION_0_RX_PIN                            (6U)
#endif


/******************* USART2 location */

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define UART_2_LOCATION_0_CLOCK_NAME                        (kCLOCK_PortD)
#define UART_2_LOCATION_0_TX_PORT                           (PORTD)
#define UART_2_LOCATION_0_TX_PIN                            (7U)
#define UART_2_LOCATION_0_TX_PORT_MUX                       (kPORT_MuxAlt2)
#define UART_2_LOCATION_0_RX_PORT                           (PORTD)
#define UART_2_LOCATION_0_RX_PIN                            (6U)
#define UART_2_LOCATION_0_RX_PORT_MUX                       (kPORT_MuxAlt2)

#define UART_2_LOCATION_0_TX_GPIO                           (GPIOD)
#define UART_2_LOCATION_0_RX_GPIO                           (GPIOD)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION) || (MAKE_VERSION(2, 0, 2) == FSL_PORT_DRIVER_VERSION)
#define UART_2_LOCATION_0_CLOCK_NAME                        (kCLOCK_Uart2)
#define UART_2_LOCATION_0_PORT_SET_PIN_SELECT_NEEDED        (false)
#define UART_2_LOCATION_0_PORT_MODULE                       (0)
#define UART_2_LOCATION_0_PORT_PIN_SELECT                   (0)

#define UART_2_LOCATION_0_TX_PORT                           (kGPIO_PORTD)
#define UART_2_LOCATION_0_TX_PIN                            (7U)
#define UART_2_LOCATION_0_RX_PORT                           (kGPIO_PORTD)
#define UART_2_LOCATION_0_RX_PIN                            (6U)
#endif

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
