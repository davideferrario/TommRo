
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusCommonUARTFIFO.h"

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
static tommRoC_hw_err_enum_t _fifo_single_init(
                uint8_t*                                    const   bufferPtr,
        const   uint16_t                                            bufferSize,
                tommRoC_hw_template_bus_common_uart_fifo_t* const   uartFifoPtr) {

    TOMMROC_ASSERT_NOT_NULL(uartFifoPtr);

    uartFifoPtr->fifoIsInit = false;

    if ((NULL != bufferPtr) && (0 != bufferSize)) {

        TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
                tommRoCFIFOISRInit(
                        bufferPtr,
                        bufferSize,
                        &uartFifoPtr->fifo),
                TOMMRO_C_HW_PARAM_ERR);

        uartFifoPtr->fifoIsInit = true;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonUARTFIFOInit(
        const   tommRoC_hw_template_bus_uart_buffer_t*      const   uartBufferPtr,
                tommRoC_hw_template_bus_common_uart_fifo_t* const   txUARTFifoPtr,
                tommRoC_hw_template_bus_common_uart_fifo_t* const   rxUARTFifoPtr) {

    TOMMROC_ASSERT_NOT_NULL(uartBufferPtr);
    TOMMROC_ASSERT_NOT_NULL(txUARTFifoPtr);
    TOMMROC_ASSERT_NOT_NULL(rxUARTFifoPtr);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
        _fifo_single_init(
                uartBufferPtr->txBufferPtr,
                uartBufferPtr->txBufferSize,
                txUARTFifoPtr));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
        _fifo_single_init(
                uartBufferPtr->rxBufferPtr,
                uartBufferPtr->rxBufferSize,
                rxUARTFifoPtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}
