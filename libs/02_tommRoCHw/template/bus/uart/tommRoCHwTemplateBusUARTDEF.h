
#ifndef TOMMROC_HW_TEMPLATE_BUS_UART_DEF_H_
#define TOMMROC_HW_TEMPLATE_BUS_UART_DEF_H_

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

/*******************************************************************************
 * defines
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)    ||  \
    defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)    ||  \
    defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)    ||  \
    defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)    ||  \
    defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)    ||  \
    defined (__TOMMROC_HW_USE_UART_5_TEMPLATE__)    ||  \
    defined (__TOMMROC_HW_USE_UART_6_TEMPLATE__)    ||  \
    defined (__TOMMROC_HW_USE_UART_7_TEMPLATE__)    ||  \
    defined (__TOMMROC_HW_USE_UART_8_TEMPLATE__)    ||  \
    defined (__TOMMROC_HW_USE_LEUART_0_TEMPLATE__)  ||  \
    defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)

#define __TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_UART_IS_USED__
#endif

#if defined (__TOMMROC_HW_USE_LEUART_0_TEMPLATE__)  ||  \
    defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)

#define __TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_LEUART_IS_USED__
#endif

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_0_TEMPLATE_TX_BUFFER_SIZE_BYTE__) && (0 == __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_0_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
#error "__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_0_TEMPLATE_TX_BUFFER_SIZE_BYTE__ MUST be greater than 0"
#endif
#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_1_TEMPLATE_TX_BUFFER_SIZE_BYTE__) && (0 == __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_1_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
#error "__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_1_TEMPLATE_TX_BUFFER_SIZE_BYTE__ MUST be greater than 0"
#endif
#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_2_TEMPLATE_TX_BUFFER_SIZE_BYTE__) && (0 == __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_2_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
#error "__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_2_TEMPLATE_TX_BUFFER_SIZE_BYTE__ MUST be greater than 0"
#endif
#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_3_TEMPLATE_TX_BUFFER_SIZE_BYTE__) && (0 == __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_3_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
#error "__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_3_TEMPLATE_TX_BUFFER_SIZE_BYTE__ MUST be greater than 0"
#endif
#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_4_TEMPLATE_TX_BUFFER_SIZE_BYTE__) && (0 == __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_4_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
#error "__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_4_TEMPLATE_TX_BUFFER_SIZE_BYTE__ MUST be greater than 0"
#endif
#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_5_TEMPLATE_TX_BUFFER_SIZE_BYTE__) && (0 == __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_5_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
#error "__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_5_TEMPLATE_TX_BUFFER_SIZE_BYTE__ MUST be greater than 0"
#endif
#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_6_TEMPLATE_TX_BUFFER_SIZE_BYTE__) && (0 == __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_6_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
#error "__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_6_TEMPLATE_TX_BUFFER_SIZE_BYTE__ MUST be greater than 0"
#endif
#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_7_TEMPLATE_TX_BUFFER_SIZE_BYTE__) && (0 == __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_7_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
#error "__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_7_TEMPLATE_TX_BUFFER_SIZE_BYTE__ MUST be greater than 0"
#endif
#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_8_TEMPLATE_TX_BUFFER_SIZE_BYTE__) && (0 == __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_8_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
#error "__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_8_TEMPLATE_TX_BUFFER_SIZE_BYTE__ MUST be greater than 0"
#endif
#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_LEUART_0_TEMPLATE_TX_BUFFER_SIZE_BYTE__) && (0 == __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_LEUART_0_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
#error "__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_LEUART_0_TEMPLATE_TX_BUFFER_SIZE_BYTE__ MUST be greater than 0"
#endif
#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_LEUART_1_TEMPLATE_TX_BUFFER_SIZE_BYTE__) && (0 == __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_LEUART_1_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
#error "__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_LEUART_1_TEMPLATE_TX_BUFFER_SIZE_BYTE__ MUST be greater than 0"
#endif

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_0_TEMPLATE_TX_BUFFER_SIZE_BYTE__)     ||  \
    defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_1_TEMPLATE_TX_BUFFER_SIZE_BYTE__)     ||  \
    defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_2_TEMPLATE_TX_BUFFER_SIZE_BYTE__)     ||  \
    defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_3_TEMPLATE_TX_BUFFER_SIZE_BYTE__)     ||  \
    defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_4_TEMPLATE_TX_BUFFER_SIZE_BYTE__)     ||  \
    defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_5_TEMPLATE_TX_BUFFER_SIZE_BYTE__)     ||  \
    defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_6_TEMPLATE_TX_BUFFER_SIZE_BYTE__)     ||  \
    defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_7_TEMPLATE_TX_BUFFER_SIZE_BYTE__)     ||  \
    defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_8_TEMPLATE_TX_BUFFER_SIZE_BYTE__)     ||  \
    defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_LEUART_0_TEMPLATE_TX_BUFFER_SIZE_BYTE__)   ||  \
    defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_LEUART_1_TEMPLATE_TX_BUFFER_SIZE_BYTE__)

#define __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_AT_LEAST_ONE_UART_TEMPLATE_TX_BUFFER_IS_USED__
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
