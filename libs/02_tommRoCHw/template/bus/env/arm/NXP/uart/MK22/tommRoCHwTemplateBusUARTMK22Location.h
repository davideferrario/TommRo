
#ifndef TOMMROC_HW_TEMPLATE_BUS_UART_MK22_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_UART_MK22_LOCATION_H_

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

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MK22_IS_USED__)

/*******************************************************************************
 * defines
 ******************************************************************************/

/******************* USART0 location */

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define UART_0_LOCATION_0_CLOCK_NAME                        (kCLOCK_PortA)
#define UART_0_LOCATION_0_TX_PORT                           (PORTA)
#define UART_0_LOCATION_0_TX_PIN                            (2U)
#define UART_0_LOCATION_0_TX_PORT_MUX                       (kPORT_MuxAlt2)
#define UART_0_LOCATION_0_RX_PORT                           (PORTA)
#define UART_0_LOCATION_0_RX_PIN                            (1U)
#define UART_0_LOCATION_0_RX_PORT_MUX                       (kPORT_MuxAlt2)

#define UART_0_LOCATION_0_TX_GPIO                           (GPIOA)
#define UART_0_LOCATION_0_RX_GPIO                           (GPIOA)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define UART_0_LOCATION_0_CLOCK_NAME                        (kCLOCK_Uart0)
#define UART_0_LOCATION_0_PORT_SET_PIN_SELECT_NEEDED        (true)
#define UART_0_LOCATION_0_PORT_MODULE                       (kPORT_UART0)
#define UART_0_LOCATION_0_PORT_PIN_SELECT                   (kPORT_UART0_RXPTA1_TXPTA2)

#define UART_0_LOCATION_0_TX_PORT                           (kGPIO_PORTA)
#define UART_0_LOCATION_0_TX_PIN                            (2U)
#define UART_0_LOCATION_0_RX_PORT                           (kGPIO_PORTA)
#define UART_0_LOCATION_0_RX_PIN                            (1U)
#endif

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define UART_0_LOCATION_1_CLOCK_NAME                        (kCLOCK_PortB)
#define UART_0_LOCATION_1_TX_PORT                           (PORTB)
#define UART_0_LOCATION_1_TX_PIN                            (17U)
#define UART_0_LOCATION_1_TX_PORT_MUX                       (kPORT_MuxAlt3)
#define UART_0_LOCATION_1_RX_PORT                           (PORTB)
#define UART_0_LOCATION_1_RX_PIN                            (16U)
#define UART_0_LOCATION_1_RX_PORT_MUX                       (kPORT_MuxAlt3)

#define UART_0_LOCATION_1_TX_GPIO                           (GPIOB)
#define UART_0_LOCATION_1_RX_GPIO                           (GPIOB)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define UART_0_LOCATION_1_CLOCK_NAME                        (kCLOCK_Uart0)
#define UART_0_LOCATION_1_PORT_SET_PIN_SELECT_NEEDED        (true)
#define UART_0_LOCATION_1_PORT_MODULE                       (kPORT_UART0)
#define UART_0_LOCATION_1_PORT_PIN_SELECT                   (kPORT_UART0_RXPTB16_TXPTB17)

#define UART_0_LOCATION_1_TX_PORT                           (kGPIO_PORTB)
#define UART_0_LOCATION_1_TX_PIN                            (17U)
#define UART_0_LOCATION_1_RX_PORT                           (kGPIO_PORTB)
#define UART_0_LOCATION_1_RX_PIN                            (16U)
#endif

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define UART_0_LOCATION_2_CLOCK_NAME                        (kCLOCK_PortD)
#define UART_0_LOCATION_2_TX_PORT                           (PORTD)
#define UART_0_LOCATION_2_TX_PIN                            (7U)
#define UART_0_LOCATION_2_TX_PORT_MUX                       (kPORT_MuxAlt3)
#define UART_0_LOCATION_2_RX_PORT                           (PORTD)
#define UART_0_LOCATION_2_RX_PIN                            (6U)
#define UART_0_LOCATION_2_RX_PORT_MUX                       (kPORT_MuxAlt3)

#define UART_0_LOCATION_2_TX_GPIO                           (GPIOD)
#define UART_0_LOCATION_2_RX_GPIO                           (GPIOD)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define UART_0_LOCATION_2_CLOCK_NAME                        (kCLOCK_Uart0)
#define UART_0_LOCATION_2_PORT_SET_PIN_SELECT_NEEDED        (true)
#define UART_0_LOCATION_2_PORT_MODULE                       (kPORT_UART0)
#define UART_0_LOCATION_2_PORT_PIN_SELECT                   (kPORT_UART0_RXPTD6_TXPTD7)

#define UART_0_LOCATION_2_TX_PORT                           (kGPIO_PORTD)
#define UART_0_LOCATION_2_TX_PIN                            (7U)
#define UART_0_LOCATION_2_RX_PORT                           (kGPIO_PORTD)
#define UART_0_LOCATION_2_RX_PIN                            (6U)
#endif


/******************* USART1 location */

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define UART_1_LOCATION_0_CLOCK_NAME                        (kCLOCK_PortE)
#define UART_1_LOCATION_0_TX_PORT                           (PORTE)
#define UART_1_LOCATION_0_TX_PIN                            (0U)
#define UART_1_LOCATION_0_TX_PORT_MUX                       (kPORT_MuxAlt3)
#define UART_1_LOCATION_0_RX_PORT                           (PORTE)
#define UART_1_LOCATION_0_RX_PIN                            (1U)
#define UART_1_LOCATION_0_RX_PORT_MUX                       (kPORT_MuxAlt3)

#define UART_1_LOCATION_0_TX_GPIO                           (GPIOE)
#define UART_1_LOCATION_0_RX_GPIO                           (GPIOE)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define UART_1_LOCATION_0_CLOCK_NAME                        (kCLOCK_Uart1)
#define UART_1_LOCATION_0_PORT_SET_PIN_SELECT_NEEDED        (true)
#define UART_1_LOCATION_0_PORT_MODULE                       (kPORT_UART1)
#define UART_1_LOCATION_0_PORT_PIN_SELECT                   (kPORT_UART0_RXPTE1_TXPTE0)

#define UART_1_LOCATION_0_TX_PORT                           (kGPIO_PORTE)
#define UART_1_LOCATION_0_TX_PIN                            (0U)
#define UART_1_LOCATION_0_RX_PORT                           (kGPIO_PORTE)
#define UART_1_LOCATION_0_RX_PIN                            (1U)
#endif

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define UART_1_LOCATION_1_CLOCK_NAME                        (kCLOCK_PortC)
#define UART_1_LOCATION_1_TX_PORT                           (PORTC)
#define UART_1_LOCATION_1_TX_PIN                            (4U)
#define UART_1_LOCATION_1_TX_PORT_MUX                       (kPORT_MuxAlt3)
#define UART_1_LOCATION_1_RX_PORT                           (PORTC)
#define UART_1_LOCATION_1_RX_PIN                            (3U)
#define UART_1_LOCATION_1_RX_PORT_MUX                       (kPORT_MuxAlt3)

#define UART_1_LOCATION_1_TX_GPIO                           (GPIOC)
#define UART_1_LOCATION_1_RX_GPIO                           (GPIOC)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define UART_1_LOCATION_2_CLOCK_NAME                        (kCLOCK_Uart1)
#define UART_1_LOCATION_1_PORT_SET_PIN_SELECT_NEEDED        (true)
#define UART_1_LOCATION_1_PORT_MODULE                       (kPORT_UART1)
#define UART_1_LOCATION_1_PORT_PIN_SELECT                   (kPORT_UART0_RXPTC3_TXPTC4)

#define UART_1_LOCATION_1_TX_PORT                           (kGPIO_PORTC)
#define UART_1_LOCATION_1_TX_PIN                            (4U)
#define UART_1_LOCATION_1_RX_PORT                           (kGPIO_PORTC)
#define UART_1_LOCATION_1_RX_PIN                            (3U)
#endif


/******************* USART2 location */

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define UART_2_LOCATION_0_CLOCK_NAME                        (kCLOCK_PortD)
#define UART_2_LOCATION_0_TX_PORT                           (PORTD)
#define UART_2_LOCATION_0_TX_PIN                            (3U)
#define UART_2_LOCATION_0_TX_PORT_MUX                       (kPORT_MuxAlt3)
#define UART_2_LOCATION_0_RX_PORT                           (PORTD)
#define UART_2_LOCATION_0_RX_PIN                            (2U)
#define UART_2_LOCATION_0_RX_PORT_MUX                       (kPORT_MuxAlt3)

#define UART_2_LOCATION_0_TX_GPIO                           (GPIOD)
#define UART_2_LOCATION_0_RX_GPIO                           (GPIOD)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define UART_2_LOCATION_0_CLOCK_NAME                        (kCLOCK_Uart2)
#define UART_2_LOCATION_0_PORT_SET_PIN_SELECT_NEEDED        (false)
#define UART_2_LOCATION_0_PORT_MODULE                       (0)
#define UART_2_LOCATION_0_PORT_PIN_SELECT                   (0)

#define UART_2_LOCATION_0_TX_PORT                           (kGPIO_PORTD)
#define UART_2_LOCATION_0_TX_PIN                            (3U)
#define UART_2_LOCATION_0_RX_PORT                           (kGPIO_PORTD)
#define UART_2_LOCATION_0_RX_PIN                            (2U)
#endif


/******************* LEUART0 location */

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define LEUART_0_LOCATION_0_CLOCK_NAME                      (kCLOCK_PortC)
#define LEUART_0_LOCATION_0_TX_PORT                         (PORTC)
#define LEUART_0_LOCATION_0_TX_PIN                          (4U)
#define LEUART_0_LOCATION_0_TX_PORT_MUX                     (kPORT_MuxAlt7)
#define LEUART_0_LOCATION_0_RX_PORT                         (PORTC)
#define LEUART_0_LOCATION_0_RX_PIN                          (3U)
#define LEUART_0_LOCATION_0_RX_PORT_MUX                     (kPORT_MuxAlt7)

#define LEUART_0_LOCATION_0_TX_GPIO                         (GPIOC)
#define LEUART_0_LOCATION_0_RX_GPIO                         (GPIOC)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define LEUART_0_LOCATION_0_CLOCK_NAME                      (kCLOCK_Lpuart0)
#define LEUART_0_LOCATION_0_PORT_SET_PIN_SELECT_NEEDED      (true)
#define LEUART_0_LOCATION_0_PORT_MODULE                     (kPORT_LPUART0)
#define LEUART_0_LOCATION_0_PORT_PIN_SELECT                 (kPORT_LPUART0_RXPTC3_TXPTC4)

#define LEUART_0_LOCATION_0_TX_PORT                         (kGPIO_PORTC)
#define LEUART_0_LOCATION_0_TX_PIN                          (4U)
#define LEUART_0_LOCATION_0_RX_PORT                         (kGPIO_PORTC)
#define LEUART_0_LOCATION_0_RX_PIN                          (3U)
#endif

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define LEUART_0_LOCATION_1_CLOCK_NAME                      (kCLOCK_PortD)
#define LEUART_0_LOCATION_1_TX_PORT                         (PORTD)
#define LEUART_0_LOCATION_1_TX_PIN                          (3U)
#define LEUART_0_LOCATION_1_TX_PORT_MUX                     (kPORT_MuxAlt6)
#define LEUART_0_LOCATION_1_RX_PORT                         (PORTD)
#define LEUART_0_LOCATION_1_RX_PIN                          (2U)
#define LEUART_0_LOCATION_1_RX_PORT_MUX                     (kPORT_MuxAlt6)

#define LEUART_0_LOCATION_1_TX_GPIO                         (GPIOD)
#define LEUART_0_LOCATION_1_RX_GPIO                         (GPIOD)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define LEUART_0_LOCATION_0_CLOCK_NAME                      (kCLOCK_Lpuart0)
#define LEUART_0_LOCATION_1_PORT_SET_PIN_SELECT_NEEDED      (true)
#define LEUART_0_LOCATION_1_PORT_MODULE                     (kPORT_LPUART0)
#define LEUART_0_LOCATION_1_PORT_PIN_SELECT                 (kPORT_LPUART0_RXPTD2_TXPTD3)

#define LEUART_0_LOCATION_1_TX_PORT                         (kGPIO_PORTD)
#define LEUART_0_LOCATION_1_TX_PIN                          (3U)
#define LEUART_0_LOCATION_1_RX_PORT                         (kGPIO_PORTD)
#define LEUART_0_LOCATION_1_RX_PIN                          (2U)
#endif

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
