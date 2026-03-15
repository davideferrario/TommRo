
#ifndef TOMMROC_HW_TEMPLATE_UART_DEBUG_H_
#define TOMMROC_HW_TEMPLATE_UART_DEBUG_H_

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
#include "TOMMROCHw.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugInit(const tommRoC_hw_bus_t* const busPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugOnlyTxInit(const tommRoC_hw_bus_t* const busPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugOnlyTxNoClearRxInit(const tommRoC_hw_bus_t* const busPtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugClose(void);

tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugSetRawType(const bool rawType);

tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugIsDataAvailable(void);
tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugDataReady(uint16_t* const availableAmountPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugIsDataToTxPending(void);
tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugDataToTxPendingAmount(uint16_t* const availableAmountPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugReadByte(uint8_t* const readDataPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugReadBuffer(uint8_t* const readBufferPtr, const uint16_t toReadAmount, uint16_t* const readedAmountPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugReadBuffers(tommRoC_hw_bus_read_buf_t* const readBuffersPtr, const uint8_t readBuffersAmount);

#endif
