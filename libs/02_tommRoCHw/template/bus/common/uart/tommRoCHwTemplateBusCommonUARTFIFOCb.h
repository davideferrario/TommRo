
#ifndef TOMMROC_HW_TEMPLATE_BUS_COMMON_UART_FIFO_CB_H_
#define TOMMROC_HW_TEMPLATE_BUS_COMMON_UART_FIFO_CB_H_

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

#include "bus/common/uart/tommRoCHwTemplateBusCommonUARTFIFO.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_template_bus_common_uart_fifo_cb_irq_write_t) (
        const   uint8_t*    const   writeBufferPtr,
        const   uint16_t            writeBufferLen);

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonUARTFIFOCbIsDataAvailable(
        const   tommRoC_hw_template_bus_common_uart_fifo_t* const   uartFifoPtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonUARTFIFOCbDataAmount(
        const   tommRoC_hw_template_bus_common_uart_fifo_t* const   uartFifoPtr,
                uint16_t*                                   const   availableAmountPtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonUARTFIFOCbWriteBuffers(
                tommRoC_hw_template_bus_common_uart_fifo_t* const   txUARTFifoPtr,
        const   tommRoC_hw_bus_write_buf_t*                 const   writeBuffersPtr,
        const   uint8_t                                             writeBuffersAmount,
                tommRoC_hw_template_bus_common_uart_fifo_cb_irq_write_t irqWrite);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonUARTFIFOCbReadBuffers(
                tommRoC_hw_template_bus_common_uart_fifo_t* const   rxUARTFifoPtr,
                tommRoC_hw_bus_read_buf_t*                  const   readBuffersPtr,
        const   uint8_t                                             readBuffersAmount);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonUARTFIFOCbGetBuffers(
                tommRoC_hw_template_bus_common_uart_fifo_t* const   rxUARTFifoPtr,
                tommRoC_hw_bus_read_buf_t*                  const   getBuffersPtr,
        const   uint8_t                                             getBuffersAmount);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonUARTFIFOCbClearBothData(
                tommRoC_hw_template_bus_common_uart_fifo_t* const   txUARTFifoPtr,
                tommRoC_hw_template_bus_common_uart_fifo_t* const   rxUARTFifoPtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonUARTFIFOCbClearSingleData(
                tommRoC_hw_template_bus_common_uart_fifo_t* const   uartFifoPtr);

#endif
