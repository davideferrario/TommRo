
#ifndef TOMMROC_HW_TEMPLATE_BUS_UART_MKWx1Z_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_UART_MKWx1Z_LOCATION_H_

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

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKWx1Z_IS_USED__)

/*******************************************************************************
 * defines
 ******************************************************************************/

/******************* LEUART0 location */

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define LEUART_0_LOCATION_0_CLOCK_NAME                      (kCLOCK_PortC)
#define LEUART_0_LOCATION_0_TX_PORT                         (PORTC)
#define LEUART_0_LOCATION_0_TX_PIN                          (3U)
#define LEUART_0_LOCATION_0_TX_PORT_MUX                     (kPORT_MuxAlt4)
#define LEUART_0_LOCATION_0_RX_PORT                         (PORTC)
#define LEUART_0_LOCATION_0_RX_PIN                          (2U)
#define LEUART_0_LOCATION_0_RX_PORT_MUX                     (kPORT_MuxAlt4)

#define LEUART_0_LOCATION_0_TX_GPIO                         (GPIOC)
#define LEUART_0_LOCATION_0_RX_GPIO                         (GPIOC)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define LEUART_0_LOCATION_0_CLOCK_NAME                      (kCLOCK_Lpuart0)
#define LEUART_0_LOCATION_0_PORT_SET_PIN_SELECT_NEEDED      (true)
#define LEUART_0_LOCATION_0_PORT_MODULE                     (kPORT_LPUART0)
#define LEUART_0_LOCATION_0_PORT_PIN_SELECT                 (kPORT_LPUART0_RXPTC2_TXPTC3)

#define LEUART_0_LOCATION_0_TX_PORT                         (kGPIO_PORTC)
#define LEUART_0_LOCATION_0_TX_PIN                          (3U)
#define LEUART_0_LOCATION_0_RX_PORT                         (kGPIO_PORTC)
#define LEUART_0_LOCATION_0_RX_PIN                          (2U)
#endif

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define LEUART_0_LOCATION_1_CLOCK_NAME                      (kCLOCK_PortC)
#define LEUART_0_LOCATION_1_TX_PORT                         (PORTC)
#define LEUART_0_LOCATION_1_TX_PIN                          (7U)
#define LEUART_0_LOCATION_1_TX_PORT_MUX                     (kPORT_MuxAlt4)
#define LEUART_0_LOCATION_1_RX_PORT                         (PORTC)
#define LEUART_0_LOCATION_1_RX_PIN                          (6U)
#define LEUART_0_LOCATION_1_RX_PORT_MUX                     (kPORT_MuxAlt4)

#define LEUART_0_LOCATION_1_TX_GPIO                         (GPIOC)
#define LEUART_0_LOCATION_1_RX_GPIO                         (GPIOC)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define LEUART_0_LOCATION_0_CLOCK_NAME                      (kCLOCK_Lpuart0)
#define LEUART_0_LOCATION_1_PORT_SET_PIN_SELECT_NEEDED      (true)
#define LEUART_0_LOCATION_1_PORT_MODULE                     (kPORT_LPUART0)
#define LEUART_0_LOCATION_1_PORT_PIN_SELECT                 (kPORT_LPUART0_RXPTC6_TXPTC7)

#define LEUART_0_LOCATION_1_TX_PORT                         (kGPIO_PORTC)
#define LEUART_0_LOCATION_1_TX_PIN                          (7U)
#define LEUART_0_LOCATION_1_RX_PORT                         (kGPIO_PORTC)
#define LEUART_0_LOCATION_1_RX_PIN                          (6U)
#endif

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define LEUART_0_LOCATION_2_CLOCK_NAME                      (kCLOCK_PortC)
#define LEUART_0_LOCATION_2_TX_PORT                         (PORTC)
#define LEUART_0_LOCATION_2_TX_PIN                          (18U)
#define LEUART_0_LOCATION_2_TX_PORT_MUX                     (kPORT_MuxAlt4)
#define LEUART_0_LOCATION_2_RX_PORT                         (PORTC)
#define LEUART_0_LOCATION_2_RX_PIN                          (17U)
#define LEUART_0_LOCATION_2_RX_PORT_MUX                     (kPORT_MuxAlt4)

#define LEUART_0_LOCATION_2_TX_GPIO                         (GPIOC)
#define LEUART_0_LOCATION_2_RX_GPIO                         (GPIOC)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define LEUART_0_LOCATION_0_CLOCK_NAME                      (kCLOCK_Lpuart0)
#define LEUART_0_LOCATION_2_PORT_SET_PIN_SELECT_NEEDED      (true)
#define LEUART_0_LOCATION_2_PORT_MODULE                     (kPORT_LPUART0)
#define LEUART_0_LOCATION_2_PORT_PIN_SELECT                 (kPORT_LPUART0_RXPTC17_TXPTC18)

#define LEUART_0_LOCATION_2_TX_PORT                         (kGPIO_PORTC)
#define LEUART_0_LOCATION_2_TX_PIN                          (18U)
#define LEUART_0_LOCATION_2_RX_PORT                         (kGPIO_PORTC)
#define LEUART_0_LOCATION_2_RX_PIN                          (17U)
#endif

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
