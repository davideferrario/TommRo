
#ifndef TOMMROC_HW_TEMPLATE_BUS_UART_EFR32_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_UART_EFR32_LOCATION_H_

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

#if defined (__TOMMROC_TEMPLATE_ARM_EFR32_IS_USED__)

#if (defined (USART_PRESENT) && USART_COUNT)
#include "em_usart.h"
#endif
#if (defined (LEUART_PRESENT) && LEUART_COUNT)
#include "em_leuart.h"
#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

#if defined (_EFR32_MG_FAMILY)

#define UART_0_LOCATION_TX_PORT             { gpioPortA, gpioPortB, gpioPortC, gpioPortD, }
#define UART_0_LOCATION_RX_PORT             { gpioPortA, gpioPortB, gpioPortC, gpioPortD, }

#define UART_1_LOCATION_TX_PORT             { gpioPortA, gpioPortB, }
#define UART_1_LOCATION_RX_PORT             { gpioPortA, gpioPortB, }

#define UART_2_LOCATION_TX_PORT             { gpioPortC, gpioPortD, }
#define UART_2_LOCATION_RX_PORT             { gpioPortC, gpioPortD, }

#endif

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
