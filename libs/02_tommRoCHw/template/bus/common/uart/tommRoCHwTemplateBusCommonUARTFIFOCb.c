
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusCommonUARTFIFOCb.h"

#include "TOMMROC.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_hw_err_enum_t _write_buffer(
                tommRoC_hw_template_bus_common_uart_fifo_t* const   txUARTFifoPtr,
        const   uint8_t*                                    const   writeBufferPtr,
        const   uint16_t                                            writeBufferLen,
                tommRoC_hw_template_bus_common_uart_fifo_cb_irq_write_t irqWrite) {

    uint16_t toWriteAmount;
    uint16_t singleWriteAmount;
    uint32_t fifoFreeAmount;
    uint8_t* ptr;

    ptr             = (uint8_t*) writeBufferPtr;
    toWriteAmount   = writeBufferLen;

    while (0 != toWriteAmount) {

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCFIFOISRFreeObjAmount(&txUARTFifoPtr->fifo, &fifoFreeAmount));

        if (0 != fifoFreeAmount) {

            singleWriteAmount = tommRoCMathMin(fifoFreeAmount, toWriteAmount);

            TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(irqWrite(ptr, singleWriteAmount));

            toWriteAmount   -= singleWriteAmount;
            ptr             += singleWriteAmount;
        }
        else {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1));
        }
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _read_buffer(
                tommRoC_hw_template_bus_common_uart_fifo_t* const   rxUARTFifoPtr,
                uint8_t*                                    const   readBufferPtr,
        const   uint16_t                                            toReadAmount,
                uint16_t*                                   const   readedAmountPtr) {

    uint16_t inFifoAvailableAmount;
    uint16_t toRead;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusCommonUARTFIFOCbDataAmount(
                    rxUARTFifoPtr,
                    &inFifoAvailableAmount));

    toRead = tommRoCMathMin(toReadAmount, inFifoAvailableAmount);

    if (0 == toRead) {
        return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
    }

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCFIFOISRMultiPop(&rxUARTFifoPtr->fifo, readBufferPtr, toRead),
            TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR);

    *readedAmountPtr = toRead;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _get_buffer(
                tommRoC_hw_template_bus_common_uart_fifo_t* const   rxUARTFifoPtr,
                uint8_t*                                    const   getBufferPtr,
        const   uint16_t                                            toGetAmount,
                uint16_t*                                   const   getAmountPtr) {

    uint16_t inFifoAvailableAmount;
    uint16_t toGet;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusCommonUARTFIFOCbDataAmount(
                    rxUARTFifoPtr,
                    &inFifoAvailableAmount));

    toGet = tommRoCMathMin(toGetAmount, inFifoAvailableAmount);

    if (0 == toGet) {
        return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
    }

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCFIFOISRMultiGet(&rxUARTFifoPtr->fifo, getBufferPtr, toGet),
            TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR);

    *getAmountPtr = toGet;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonUARTFIFOCbIsDataAvailable(
        const   tommRoC_hw_template_bus_common_uart_fifo_t* const   uartFifoPtr) {

    TOMMROC_ASSERT_NOT_NULL(uartFifoPtr);

    if (!uartFifoPtr->fifoIsInit) {
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
    }

    if (tommRoCFIFOISRIsEmpty(&uartFifoPtr->fifo)) {
        return TOMMRO_C_HW_BUS_DATA_NOT_AVAILABLE_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonUARTFIFOCbDataAmount(
        const   tommRoC_hw_template_bus_common_uart_fifo_t* const   uartFifoPtr,
                uint16_t*                                   const   availableAmountPtr) {

    uint32_t availableAmount;

    TOMMROC_ASSERT_NOT_NULL(uartFifoPtr);
    TOMMROC_ASSERT_NOT_NULL(availableAmountPtr);

    if (!uartFifoPtr->fifoIsInit) {
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
    }

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCFIFOISRInsideObjAmount(&uartFifoPtr->fifo, &availableAmount),
            TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR);

    *availableAmountPtr = (uint16_t) availableAmount;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonUARTFIFOCbWriteBuffers(
                tommRoC_hw_template_bus_common_uart_fifo_t* const   txUARTFifoPtr,
        const   tommRoC_hw_bus_write_buf_t*                 const   writeBuffersPtr,
        const   uint8_t                                             writeBuffersAmount,
                tommRoC_hw_template_bus_common_uart_fifo_cb_irq_write_t irqWrite) {

    const tommRoC_hw_bus_write_buf_t* writeBufferPtr;
    uint8_t index;

    TOMMROC_ASSERT_NOT_NULL(txUARTFifoPtr);
    TOMMROC_ASSERT_NOT_NULL(writeBuffersPtr);
    TOMMROC_ASSERT_NOT_ZERO(writeBuffersAmount);
    TOMMROC_ASSERT_NOT_NULL(irqWrite);

    if (!txUARTFifoPtr->fifoIsInit) {
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
    }

    for (index = 0, writeBufferPtr = writeBuffersPtr; index < writeBuffersAmount; ++index, ++writeBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _write_buffer(
                        txUARTFifoPtr,
                        writeBufferPtr->bufferPtr,
                        writeBufferPtr->toWriteAmount,
                        irqWrite));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonUARTFIFOCbReadBuffers(
                tommRoC_hw_template_bus_common_uart_fifo_t* const   rxUARTFifoPtr,
                tommRoC_hw_bus_read_buf_t*                  const   readBuffersPtr,
        const   uint8_t                                             readBuffersAmount) {

    tommRoC_hw_bus_read_buf_t* readBufferPtr;
    uint8_t index;

    TOMMROC_ASSERT_NOT_NULL(rxUARTFifoPtr);
    TOMMROC_ASSERT_NOT_NULL(readBuffersPtr);
    TOMMROC_ASSERT_NOT_ZERO(readBuffersAmount);

    if (!rxUARTFifoPtr->fifoIsInit) {
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
    }

    for (index = 0, readBufferPtr = readBuffersPtr; index < readBuffersAmount; ++index, ++readBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _read_buffer(
                        rxUARTFifoPtr,
                        readBufferPtr->bufferPtr,
                        readBufferPtr->toReadAmount,
                        readBufferPtr->readedAmountPtr));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonUARTFIFOCbGetBuffers(
                tommRoC_hw_template_bus_common_uart_fifo_t* const   rxUARTFifoPtr,
                tommRoC_hw_bus_read_buf_t*                  const   getBuffersPtr,
        const   uint8_t                                             getBuffersAmount) {

    tommRoC_hw_bus_read_buf_t* readBufferPtr;
    uint8_t index;

    TOMMROC_ASSERT_NOT_NULL(rxUARTFifoPtr);
    TOMMROC_ASSERT_NOT_NULL(getBuffersPtr);
    TOMMROC_ASSERT_NOT_ZERO(getBuffersAmount);

    if (!rxUARTFifoPtr->fifoIsInit) {
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
    }

    for (index = 0, readBufferPtr = getBuffersPtr; index < getBuffersAmount; ++index, ++readBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _get_buffer(
                        rxUARTFifoPtr,
                        readBufferPtr->bufferPtr,
                        readBufferPtr->toReadAmount,
                        readBufferPtr->readedAmountPtr));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonUARTFIFOCbClearBothData(
                tommRoC_hw_template_bus_common_uart_fifo_t* const   txUARTFifoPtr,
                tommRoC_hw_template_bus_common_uart_fifo_t* const   rxUARTFifoPtr) {

    TOMMROC_ASSERT_NOT_NULL(txUARTFifoPtr);
    TOMMROC_ASSERT_NOT_NULL(rxUARTFifoPtr);

    if (!txUARTFifoPtr->fifoIsInit) {
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
    }

    if (!rxUARTFifoPtr->fifoIsInit) {
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
    }

    if (!tommRoCFIFOISRIsEmpty(&txUARTFifoPtr->fifo) || !tommRoCFIFOISRIsEmpty(&rxUARTFifoPtr->fifo)) {

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1));

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCFIFOISRClear(&txUARTFifoPtr->fifo));
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCFIFOISRClear(&rxUARTFifoPtr->fifo));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonUARTFIFOCbClearSingleData(
                tommRoC_hw_template_bus_common_uart_fifo_t* const   uartFifoPtr) {

    TOMMROC_ASSERT_NOT_NULL(uartFifoPtr);

    if (!uartFifoPtr->fifoIsInit) {
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
    }

    if (!tommRoCFIFOISRIsEmpty(&uartFifoPtr->fifo)) {

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1));

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCFIFOISRClear(&uartFifoPtr->fifo));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}
