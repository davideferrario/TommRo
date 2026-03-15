
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentUART.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)

#include "TOMMROC.h"

#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_UART_IS_USED__)

#include "bus/common/uart/tommRoCHwTemplateBusCommonUARTFIFO.h"
#include "bus/common/uart/tommRoCHwTemplateBusCommonUARTFIFOCb.h"

#include "bus/env/arm/STM32/uart/tommRoCHwTemplateBusUARTSTM32DEF.h"
#include "bus/env/arm/STM32/uart/tommRoCHwTemplateBusUARTSTM32Hal.h"

#include "usart.h"

#include <stdbool.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    tommRoC_hw_template_bus_uart_buffer_t   buffer;

} __tommRoC_hw_uart_config_t__;

#define __EMPTY___tommRoC_hw_uart_config_t____                          \
{                                                                       \
    /* .buffer */   __EMPTY_tommRoC_hw_template_bus_uart_buffer_t__,    \
}

typedef struct {

    void*                                       usartPtr;   // Note: void* for compatibility with both:
                                                            // UART_HandleTypeDef*  USART
                                                            // LEUART_HandleTypeDef* low power UART
    uint8_t                                     txByte[2];
    uint8_t                                     rxByte[2];
#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_AT_LEAST_ONE_UART_TEMPLATE_TX_BUFFER_IS_USED__)
    uint8_t*                                    txBufferPtr;
    uint32_t                                    txBufferSize;
#endif
    tommRoC_hw_template_bus_common_uart_fifo_t  txUARTFifo;
    tommRoC_hw_template_bus_common_uart_fifo_t  rxUARTFifo;
    IRQn_Type                                   usartIRQn;
    bool                                        isTxInProgress;

} __tommRoC_hw_uart_handle_t__;

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_AT_LEAST_ONE_UART_TEMPLATE_TX_BUFFER_IS_USED__)
#define __EMPTY___tommRoC_hw_uart_handle_t____                                      \
{                                                                                   \
    /* .huartPtr */         NULL,                                                   \
    /* .txByte */           { 0x00, 0x00, },                                        \
    /* .rxByte */           { 0x00, 0x00, },                                        \
    /* .txBufferPtr */      NULL,                                                   \
    /* .txBufferSize */     0,                                                      \
    /* .txUARTFifo */       __EMPTY_tommRoC_hw_template_bus_common_uart_fifo_t__,   \
    /* .rxUARTFifo */       __EMPTY_tommRoC_hw_template_bus_common_uart_fifo_t__,   \
    /* .usartIRQn */        ((IRQn_Type) 0),                                        \
    /* .isTxInProgress */   false,                                                  \
}
#else
#define __EMPTY___tommRoC_hw_uart_handle_t____                                      \
{                                                                                   \
    /* .huartPtr */         NULL,                                                   \
    /* .txByte */           { 0x00, 0x00, },                                        \
    /* .rxByte */           { 0x00, 0x00, },                                        \
    /* .txUARTFifo */       __EMPTY_tommRoC_hw_template_bus_common_uart_fifo_t__,   \
    /* .rxUARTFifo */       __EMPTY_tommRoC_hw_template_bus_common_uart_fifo_t__,   \
    /* .usartIRQn */        ((IRQn_Type) 0),                                        \
    /* .isTxInProgress */   false,                                                  \
}
#endif

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
static __tommRoC_hw_uart_config_t__ _uart_config_1 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_config_t__);
static __tommRoC_hw_uart_handle_t__ _uart_handle_1 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
static __tommRoC_hw_uart_config_t__ _uart_config_2 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_config_t__);
static __tommRoC_hw_uart_handle_t__ _uart_handle_2 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
static __tommRoC_hw_uart_config_t__ _uart_config_3 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_config_t__);
static __tommRoC_hw_uart_handle_t__ _uart_handle_3 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
static __tommRoC_hw_uart_config_t__ _uart_config_4 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_config_t__);
static __tommRoC_hw_uart_handle_t__ _uart_handle_4 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_UART_5_TEMPLATE__)
static __tommRoC_hw_uart_config_t__ _uart_config_5 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_config_t__);
static __tommRoC_hw_uart_handle_t__ _uart_handle_5 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_UART_6_TEMPLATE__)
static __tommRoC_hw_uart_config_t__ _uart_config_6 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_config_t__);
static __tommRoC_hw_uart_handle_t__ _uart_handle_6 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_UART_7_TEMPLATE__)
static __tommRoC_hw_uart_config_t__ _uart_config_7 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_config_t__);
static __tommRoC_hw_uart_handle_t__ _uart_handle_7 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_UART_8_TEMPLATE__)
static __tommRoC_hw_uart_config_t__ _uart_config_8 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_config_t__);
static __tommRoC_hw_uart_handle_t__ _uart_handle_8 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)
static __tommRoC_hw_uart_config_t__ _leuart_config_1 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_config_t__);
static __tommRoC_hw_uart_handle_t__ _leuart_handle_1 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_handle_t__);
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/

/******************* Generic low level uart RXNE/TXE interrupt functs */

#if defined (__TOMMROC_HW_USE_UART_TEMPLATE_NOT_STANDARD_WORD_LENGTH_ENABLED__)
static uint8_t _get_usart_word_length(const UART_HandleTypeDef* const usartPtr) {
    return (UART_WORDLENGTH_8B == usartPtr->Init.WordLength) ? (TOMMROC_UTIL_U8_SIZE) : (TOMMROC_UTIL_U16_SIZE);
}
#endif

static void _irq_usart_rx_handle(__tommRoC_hw_uart_handle_t__* const uartHandlePtr) {

    UART_HandleTypeDef* uartHandleTypePtr = (UART_HandleTypeDef*) uartHandlePtr->usartPtr;
    tommRoC_hw_template_bus_common_uart_fifo_t* rxUARTFifoPtr = &uartHandlePtr->rxUARTFifo;

#if defined (__TOMMROC_HW_USE_UART_TEMPLATE_NOT_STANDARD_WORD_LENGTH_ENABLED__)
    uint8_t wordLength = _get_usart_word_length(uartHandleTypePtr);
#endif

    // NOTE: don't use ASSERT_SUCCESS because can be possible that it return NOT_ENOUGH_RESOURCE
#if defined (__TOMMROC_HW_USE_UART_TEMPLATE_NOT_STANDARD_WORD_LENGTH_ENABLED__)
    tommRoCFIFOISRMultiPush(&rxUARTFifoPtr->fifo, uartHandlePtr->rxByte, wordLength);
#else
    tommRoCFIFOISRPush(&rxUARTFifoPtr->fifo, uartHandlePtr->rxByte[0]);
#endif

    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(HAL_UART_Receive_IT(uartHandleTypePtr, uartHandlePtr->rxByte, 1), HAL_OK);
}

static void _irq_usart_tx_handle(__tommRoC_hw_uart_handle_t__* const uartHandlePtr) {

    UART_HandleTypeDef* uartHandleTypePtr = (UART_HandleTypeDef*) uartHandlePtr->usartPtr;
    tommRoC_hw_template_bus_common_uart_fifo_t* txUARTFifoPtr = &uartHandlePtr->txUARTFifo;

#if defined (__TOMMROC_HW_USE_UART_TEMPLATE_NOT_STANDARD_WORD_LENGTH_ENABLED__)
    uint8_t wordLength = _get_usart_word_length(uartHandleTypePtr);
#else
    static const uint8_t wordLength = TOMMROC_UTIL_U8_SIZE;
#endif

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_AT_LEAST_ONE_UART_TEMPLATE_TX_BUFFER_IS_USED__)
    uint32_t inAmount;
    uint32_t toTxSize;
#endif

#if !defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_AT_LEAST_ONE_UART_TEMPLATE_TX_BUFFER_IS_USED__)
#if defined (__TOMMROC_HW_USE_UART_TEMPLATE_NOT_STANDARD_WORD_LENGTH_ENABLED__)
    if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRMultiPop(&txUARTFifoPtr->fifo, uartHandlePtr->txByte, wordLength)) {
        uartHandlePtr->isTxInProgress = false;
        return;
    }
#else
    TOMMROC_UTIL_UNUSED_PARAM(wordLength);
    if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRPop(&txUARTFifoPtr->fifo, uartHandlePtr->txByte)) {
        uartHandlePtr->isTxInProgress = false;
        return;
    }
#endif

    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(HAL_UART_Transmit_IT(uartHandleTypePtr, uartHandlePtr->txByte, 1), HAL_OK);
    return;
#else
    if ((TOMMROC_UTIL_U8_SIZE != wordLength) || (NULL == uartHandlePtr->txBufferPtr) || (0 == uartHandlePtr->txBufferSize)) {

        if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRMultiPop(&txUARTFifoPtr->fifo, uartHandlePtr->txByte, wordLength)) {
            uartHandlePtr->isTxInProgress = false;
            return;
        }

        TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(HAL_UART_Transmit_IT(uartHandleTypePtr, uartHandlePtr->txByte, 1), HAL_OK);
    }
    else {

        if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRInsideObjAmount(&txUARTFifoPtr->fifo, &inAmount)) {
            uartHandlePtr->isTxInProgress = false;
            return;
        }

        if (0 == inAmount) {
            uartHandlePtr->isTxInProgress = false;
            return;
        }

        toTxSize = tommRoCMathMin(inAmount, uartHandlePtr->txBufferSize);

        if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRMultiPop(&txUARTFifoPtr->fifo, uartHandlePtr->txBufferPtr, toTxSize)) {
            uartHandlePtr->isTxInProgress = false;
            return;
        }

        TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(HAL_UART_Transmit_IT(uartHandleTypePtr, uartHandlePtr->txBufferPtr, toTxSize), HAL_OK);
    }
#endif
}

static void _irq_usart_error_handle(__tommRoC_hw_uart_handle_t__* const uartHandlePtr) {
    TOMMROC_UTIL_UNUSED_PARAM(uartHandlePtr);
}

/******************* Low level uart RXNE/TXE interrupt functs */

// UART receive Interrupt callback routine
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huartPtr) {

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_1.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_rx_handle(&_uart_handle_1);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_2.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_rx_handle(&_uart_handle_2);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_3.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_rx_handle(&_uart_handle_3);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_4.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_rx_handle(&_uart_handle_4);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_5_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_5.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_rx_handle(&_uart_handle_5);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_6_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_6.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_rx_handle(&_uart_handle_6);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_7_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_7.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_rx_handle(&_uart_handle_7);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_8_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_8.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_rx_handle(&_uart_handle_8);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)
    if (((UART_HandleTypeDef*) _leuart_handle_1.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_rx_handle(&_leuart_handle_1);
    }
    else
#endif

    {}
}

// UART empty transmit Interrupt callback routine
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huartPtr) {

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_1.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_tx_handle(&_uart_handle_1);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_2.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_tx_handle(&_uart_handle_2);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_3.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_tx_handle(&_uart_handle_3);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_4.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_tx_handle(&_uart_handle_4);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_5_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_5.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_tx_handle(&_uart_handle_5);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_6_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_6.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_tx_handle(&_uart_handle_6);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_7_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_7.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_tx_handle(&_uart_handle_7);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_8_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_8.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_tx_handle(&_uart_handle_8);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)
    if (((UART_HandleTypeDef*) _leuart_handle_1.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_tx_handle(&_leuart_handle_1);
    }
    else
#endif

    {}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huartPtr) {

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_1.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_error_handle(&_uart_handle_1);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_2.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_error_handle(&_uart_handle_2);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_3.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_error_handle(&_uart_handle_3);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_4.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_error_handle(&_uart_handle_4);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_5_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_5.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_error_handle(&_uart_handle_5);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_6_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_6.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_error_handle(&_uart_handle_6);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_7_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_7.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_error_handle(&_uart_handle_7);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_UART_8_TEMPLATE__)
    if (((UART_HandleTypeDef*) _uart_handle_8.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_error_handle(&_uart_handle_8);
    }
    else
#endif

#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)
    if (((UART_HandleTypeDef*) _leuart_handle_1.usartPtr)->Instance == huartPtr->Instance) {
        _irq_usart_error_handle(&_leuart_handle_1);
    }
    else
#endif

    {}
}


/******************* Common BUS functions */

static tommRoC_hw_err_enum_t _usart_write_buffer(
                __tommRoC_hw_uart_handle_t__*   const   uartHandlePtr,
        const   uint8_t*                        const   writeBufferPtr,
        const   uint16_t                                writeBufferLen) {

    tommRoC_fifo_ISR_t* txFifoPtr           = &uartHandlePtr->txUARTFifo.fifo;
    UART_HandleTypeDef* uartHandleTypePtr   = (UART_HandleTypeDef*) uartHandlePtr->usartPtr;

    HAL_UART_StateTypeDef uartState;

#if defined (__TOMMROC_HW_USE_UART_TEMPLATE_NOT_STANDARD_WORD_LENGTH_ENABLED__)
    uint8_t wordLength = _get_usart_word_length(uartHandleTypePtr);
#else
    static const uint8_t wordLength = TOMMROC_UTIL_U8_SIZE;
#endif

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_AT_LEAST_ONE_UART_TEMPLATE_TX_BUFFER_IS_USED__)
    uint32_t inAmount;
    uint32_t toTxSize;
#endif

    // NOTE: ASSERT_SUCCESS is used because higher level function (tommRoCHwTemplateBusCommonUARTFIFOCbWriteBuffers) check for free space available
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCFIFOISRMultiPush(txFifoPtr, writeBufferPtr, writeBufferLen));

    uartState = HAL_UART_GetState(uartHandleTypePtr);

    // If uart TX already in progress
    if ((HAL_UART_STATE_BUSY_TX == uartState) || (HAL_UART_STATE_BUSY_TX_RX == uartState)) {
        // Next transmission managed by interrupt
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

#if !defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_AT_LEAST_ONE_UART_TEMPLATE_TX_BUFFER_IS_USED__)
#if defined (__TOMMROC_HW_USE_UART_TEMPLATE_NOT_STANDARD_WORD_LENGTH_ENABLED__)
    // If pop fails, it means that already tx in interrupt (maybe a thread switch context).
    if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRMultiPop(txFifoPtr, uartHandlePtr->txByte, wordLength)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#else
    TOMMROC_UTIL_UNUSED_PARAM(wordLength);
    // If pop fails, it means that already tx in interrupt (maybe a thread switch context).
    if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRPop(txFifoPtr, uartHandlePtr->txByte)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

    uartHandlePtr->isTxInProgress = true;

    // Start interrupt transmission
    if (HAL_OK != HAL_UART_Transmit_IT(uartHandleTypePtr, uartHandlePtr->txByte, 1)) {
        uartHandlePtr->isTxInProgress = false;
        return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    if ((TOMMROC_UTIL_U8_SIZE != wordLength) || (NULL == uartHandlePtr->txBufferPtr) || (0 == uartHandlePtr->txBufferSize)) {

        // If pop fails, it means that already tx in interrupt (maybe a thread switch context).
        if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRMultiPop(txFifoPtr, uartHandlePtr->txByte, wordLength)) {
            return TOMMRO_C_HW_ERR_SUCCESS;
        }

        uartHandlePtr->isTxInProgress = true;

        // Start interrupt transmission
        if (HAL_OK != HAL_UART_Transmit_IT(uartHandleTypePtr, uartHandlePtr->txByte, 1)) {
            uartHandlePtr->isTxInProgress = false;
            return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
        }

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
    else {

        if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRInsideObjAmount(txFifoPtr, &inAmount)) {
            return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
        }

        toTxSize = tommRoCMathMin(inAmount, uartHandlePtr->txBufferSize);

        // If pop fails, it means that already tx in interrupt (maybe a thread switch context).
        if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRMultiPop(txFifoPtr, uartHandlePtr->txBufferPtr, toTxSize)) {
            return TOMMRO_C_HW_ERR_SUCCESS;
        }

        uartHandlePtr->isTxInProgress = true;

        // Start interrupt transmission
        if (HAL_OK != HAL_UART_Transmit_IT(uartHandleTypePtr, uartHandlePtr->txBufferPtr, toTxSize)) {
            uartHandlePtr->isTxInProgress = false;
            return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
        }

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif
}

static tommRoC_hw_err_enum_t _usart_irq_write_buffer(
                __tommRoC_hw_uart_handle_t__*   const   uartHandlePtr,
        const   uint8_t*                        const   writeBufferPtr,
        const   uint16_t                                writeBufferLen) {

    tommRoC_hw_err_enum_t res;

    HAL_NVIC_DisableIRQ(uartHandlePtr->usartIRQn);

    res = _usart_write_buffer(uartHandlePtr, writeBufferPtr, writeBufferLen);

    HAL_NVIC_EnableIRQ(uartHandlePtr->usartIRQn);

    return res;
}

static tommRoC_hw_err_enum_t _phy_low_power_enter(
                __tommRoC_hw_uart_handle_t__*       const   uartHandlePtr,
        const   tommRoC_util_enabled_status_enum_t          rxEnabledStatus) {

    UART_HandleTypeDef* uartHandleTypePtr = (UART_HandleTypeDef*) uartHandlePtr->usartPtr;

    if (TOMMRO_C_UTIL_ENABLED == rxEnabledStatus) {
        if (HAL_OK != HAL_UART_AbortReceive_IT(uartHandleTypePtr)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }
    }

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusUARTSTM32HalSetForLowPowerEnter(
                    uartHandleTypePtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_low_power_exit(
                __tommRoC_hw_uart_handle_t__*       const   uartHandlePtr,
        const   tommRoC_util_enabled_status_enum_t          rxEnabledStatus) {

    UART_HandleTypeDef* uartHandleTypePtr = (UART_HandleTypeDef*) uartHandlePtr->usartPtr;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusUARTSTM32HalSetForLowPowerExit(
                    uartHandleTypePtr));

    if (TOMMRO_C_UTIL_ENABLED == rxEnabledStatus) {
        if (HAL_OK != HAL_UART_Receive_IT(uartHandleTypePtr, uartHandlePtr->rxByte, 1)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_set_prop(
                __tommRoC_hw_uart_handle_t__*       const   uartHandlePtr,
        const   tommRoC_util_enabled_status_enum_t          rxEnabledStatus,
        const   tommRoC_hw_bus_prop_enum_t                  property,
        const   void*                               const   propValuePtr) {

    UART_HandleTypeDef* uartHandleTypePtr = (UART_HandleTypeDef*) uartHandlePtr->usartPtr;

    if (TOMMRO_C_UTIL_ENABLED == rxEnabledStatus) {
        if (HAL_OK != HAL_UART_AbortReceive_IT(uartHandleTypePtr)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }
    }

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusUARTSTM32HalPropSet(
                    uartHandleTypePtr,
                    property,
                    propValuePtr));

    if (TOMMRO_C_UTIL_ENABLED == rxEnabledStatus) {
        if (HAL_OK != HAL_UART_Receive_IT(uartHandleTypePtr, uartHandlePtr->rxByte, 1)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}


/******************* BUS implementation functs */

#define __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(                                 \
                uartPrefix,                                                                         \
                uartHandle,                                                                         \
                irqWriteBuffer)                                                                     \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _IRQ_write_buffer_ARM(                          \
            const   uint8_t*    const   writeBufferPtr,                                             \
            const   uint16_t            writeBufferLen) {                                           \
                                                                                                    \
        return irqWriteBuffer(&uartHandle, writeBufferPtr, writeBufferLen);                         \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _is_data_available_ARM(                         \
            const   void*       const   inputPtr,                                                   \
                    void*       const   resultPtr) {                                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonUARTFIFOCbIsDataAvailable(                                 \
                &uartHandle.rxUARTFifo);                                                            \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _data_ready_ARM(                                \
                    uint16_t*   const   availableAmountPtr,                                         \
            const   void*       const   inputPtr,                                                   \
                    void*       const   resultPtr) {                                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonUARTFIFOCbDataAmount(                                      \
                &uartHandle.rxUARTFifo,                                                             \
                availableAmountPtr);                                                                \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _is_data_to_tx_pending_ARM(                     \
            const   void*       const   inputPtr,                                                   \
                    void*       const   resultPtr) {                                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        if (uartHandle.isTxInProgress) {                                                            \
            return TOMMRO_C_HW_ERR_SUCCESS;                                                         \
        }                                                                                           \
                                                                                                    \
        return TOMMRO_C_HW_BUS_DATA_NOT_AVAILABLE_ERR;                                              \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _data_to_tx_pending_amount_ARM(                 \
                    uint16_t*   const   availableAmountPtr,                                         \
            const   void*       const   inputPtr,                                                   \
                    void*       const   resultPtr) {                                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonUARTFIFOCbDataAmount(                                      \
                &uartHandle.txUARTFifo,                                                             \
                availableAmountPtr);                                                                \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _write_buffers_ARM(                             \
            const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,                            \
            const   uint8_t                             writeBuffersAmount,                         \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonUARTFIFOCbWriteBuffers(                                    \
                &uartHandle.txUARTFifo,                                                             \
                writeBuffersPtr,                                                                    \
                writeBuffersAmount,                                                                 \
                _ ## uartPrefix ## _IRQ_write_buffer_ARM);                                          \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _read_buffers_ARM(                              \
                    tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,                             \
            const   uint8_t                             readBuffersAmount,                          \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonUARTFIFOCbReadBuffers(                                     \
                &uartHandle.rxUARTFifo,                                                             \
                readBuffersPtr,                                                                     \
                readBuffersAmount);                                                                 \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _get_buffers_ARM(                               \
                    tommRoC_hw_bus_read_buf_t*  const   getBuffersPtr,                              \
            const   uint8_t                             getBuffersAmount,                           \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonUARTFIFOCbGetBuffers(                                      \
                &uartHandle.rxUARTFifo,                                                             \
                getBuffersPtr,                                                                      \
                getBuffersAmount);                                                                  \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _clear_data_ARM(                                \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonUARTFIFOCbClearBothData(                                   \
                &uartHandle.txUARTFifo,                                                             \
                &uartHandle.rxUARTFifo);                                                            \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _clear_to_send_data_ARM(                        \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonUARTFIFOCbClearSingleData(                                 \
                &uartHandle.txUARTFifo);                                                            \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _clear_received_data_ARM(                       \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonUARTFIFOCbClearSingleData(                                 \
                &uartHandle.rxUARTFifo);                                                            \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _low_power_enter_ARM(                           \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _phy_low_power_enter(                                                                \
                &uartHandle,                                                                        \
                TOMMRO_C_UTIL_ENABLED);                                                             \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _low_power_exit_ARM(                            \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _phy_low_power_exit(                                                                 \
                &uartHandle,                                                                        \
                TOMMRO_C_UTIL_ENABLED);                                                             \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _set_prop_ARM(                                  \
            const   tommRoC_hw_bus_prop_enum_t          property,                                   \
            const   void*                       const   propValuePtr,                               \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _phy_set_prop(                                                                       \
                &uartHandle,                                                                        \
                TOMMRO_C_UTIL_ENABLED,                                                              \
                property,                                                                           \
                propValuePtr);                                                                      \
    }                                                                                               \
                                                                                                    \
    static void _ ## uartPrefix ## _get_callback_TX_RX_ARM(                                         \
                    tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {                               \
                                                                                                    \
        cbFunctPtr->isDataAvailable         = _ ## uartPrefix ## _is_data_available_ARM;            \
        cbFunctPtr->dataReady               = _ ## uartPrefix ## _data_ready_ARM;                   \
        cbFunctPtr->isDataToTxPending       = _ ## uartPrefix ## _is_data_to_tx_pending_ARM;        \
        cbFunctPtr->dataToTxPendingAmount   = _ ## uartPrefix ## _data_to_tx_pending_amount_ARM;    \
        cbFunctPtr->writeBuffers            = _ ## uartPrefix ## _write_buffers_ARM;                \
        cbFunctPtr->readBuffers             = _ ## uartPrefix ## _read_buffers_ARM;                 \
        cbFunctPtr->getBuffers              = _ ## uartPrefix ## _get_buffers_ARM;                  \
        cbFunctPtr->clearData               = _ ## uartPrefix ## _clear_data_ARM;                   \
        cbFunctPtr->clearToSendData         = _ ## uartPrefix ## _clear_to_send_data_ARM;           \
        cbFunctPtr->clearReceivedData       = _ ## uartPrefix ## _clear_received_data_ARM;          \
        cbFunctPtr->lowPowerEnter           = _ ## uartPrefix ## _low_power_enter_ARM;              \
        cbFunctPtr->lowPowerExit            = _ ## uartPrefix ## _low_power_exit_ARM;               \
        cbFunctPtr->setProp                 = _ ## uartPrefix ## _set_prop_ARM;                     \
    }

#define __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_ONLY_TX_TEMPLATE__(                         \
                uartPrefix,                                                                         \
                uartHandle,                                                                         \
                irqWriteBuffer)                                                                     \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _IRQ_write_buffer_ARM(                          \
            const   uint8_t*    const   writeBufferPtr,                                             \
            const   uint16_t            writeBufferLen) {                                           \
                                                                                                    \
        return irqWriteBuffer(&uartHandle, writeBufferPtr, writeBufferLen);                         \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _is_data_to_tx_pending_ARM(                     \
            const   void*       const   inputPtr,                                                   \
                    void*       const   resultPtr) {                                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        if (uartHandle.isTxInProgress) {                                                            \
            return TOMMRO_C_HW_ERR_SUCCESS;                                                         \
        }                                                                                           \
                                                                                                    \
        return TOMMRO_C_HW_BUS_DATA_NOT_AVAILABLE_ERR;                                              \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _data_to_tx_pending_amount_ARM(                 \
                    uint16_t*   const   availableAmountPtr,                                         \
            const   void*       const   inputPtr,                                                   \
                    void*       const   resultPtr) {                                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonUARTFIFOCbDataAmount(                                      \
                &uartHandle.txUARTFifo,                                                             \
                availableAmountPtr);                                                                \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _write_buffers_ARM(                             \
            const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,                            \
            const   uint8_t                             writeBuffersAmount,                         \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonUARTFIFOCbWriteBuffers(                                    \
                &uartHandle.txUARTFifo,                                                             \
                writeBuffersPtr,                                                                    \
                writeBuffersAmount,                                                                 \
                _ ## uartPrefix ## _IRQ_write_buffer_ARM);                                          \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _clear_data_ARM(                                \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonUARTFIFOCbClearBothData(                                   \
                &uartHandle.txUARTFifo,                                                             \
                &uartHandle.rxUARTFifo);                                                            \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _clear_to_send_data_ARM(                        \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonUARTFIFOCbClearSingleData(                                 \
                &uartHandle.txUARTFifo);                                                            \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _low_power_enter_ARM(                           \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _phy_low_power_enter(                                                                \
                &uartHandle,                                                                        \
                TOMMRO_C_UTIL_DISABLED);                                                            \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _low_power_exit_ARM(                            \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _phy_low_power_exit(                                                                 \
                &uartHandle,                                                                        \
                TOMMRO_C_UTIL_DISABLED);                                                            \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _set_prop_ARM(                                  \
            const   tommRoC_hw_bus_prop_enum_t          property,                                   \
            const   void*                       const   propValuePtr,                               \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _phy_set_prop(                                                                       \
                &uartHandle,                                                                        \
                TOMMRO_C_UTIL_DISABLED,                                                             \
                property,                                                                           \
                propValuePtr);                                                                      \
    }                                                                                               \
                                                                                                    \
    static void _ ## uartPrefix ## _get_callback_ONLY_TX_ARM(                                       \
                    tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {                               \
                                                                                                    \
        cbFunctPtr->isDataToTxPending       = _ ## uartPrefix ## _is_data_to_tx_pending_ARM;        \
        cbFunctPtr->dataToTxPendingAmount   = _ ## uartPrefix ## _data_to_tx_pending_amount_ARM;    \
        cbFunctPtr->writeBuffers            = _ ## uartPrefix ## _write_buffers_ARM;                \
        cbFunctPtr->clearData               = _ ## uartPrefix ## _clear_data_ARM;                   \
        cbFunctPtr->clearToSendData         = _ ## uartPrefix ## _clear_to_send_data_ARM;           \
        cbFunctPtr->lowPowerEnter           = _ ## uartPrefix ## _low_power_enter_ARM;              \
        cbFunctPtr->lowPowerExit            = _ ## uartPrefix ## _low_power_exit_ARM;               \
        cbFunctPtr->setProp                 = _ ## uartPrefix ## _set_prop_ARM;                     \
    }

#define __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_ONLY_RX_TEMPLATE__(                         \
                uartPrefix,                                                                         \
                uartHandle)                                                                         \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _is_data_available_ARM(                         \
            const   void*       const   inputPtr,                                                   \
                    void*       const   resultPtr) {                                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonUARTFIFOCbIsDataAvailable(                                 \
                &uartHandle.rxUARTFifo);                                                            \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _data_ready_ARM(                                \
                    uint16_t*   const   availableAmountPtr,                                         \
            const   void*       const   inputPtr,                                                   \
                    void*       const   resultPtr) {                                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonUARTFIFOCbDataAmount(                                      \
                &uartHandle.rxUARTFifo,                                                             \
                availableAmountPtr);                                                                \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _read_buffers_ARM(                              \
                    tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,                             \
            const   uint8_t                             readBuffersAmount,                          \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonUARTFIFOCbReadBuffers(                                     \
                &uartHandle.rxUARTFifo,                                                             \
                readBuffersPtr,                                                                     \
                readBuffersAmount);                                                                 \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _get_buffers_ARM(                               \
                    tommRoC_hw_bus_read_buf_t*  const   getBuffersPtr,                              \
            const   uint8_t                             getBuffersAmount,                           \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonUARTFIFOCbGetBuffers(                                      \
                &uartHandle.rxUARTFifo,                                                             \
                getBuffersPtr,                                                                      \
                getBuffersAmount);                                                                  \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _clear_data_ARM(                                \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonUARTFIFOCbClearBothData(                                   \
                &uartHandle.txUARTFifo,                                                             \
                &uartHandle.rxUARTFifo);                                                            \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _clear_received_data_ARM(                       \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonUARTFIFOCbClearSingleData(                                 \
                &uartHandle.rxUARTFifo);                                                            \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _low_power_enter_ARM(                           \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _phy_low_power_enter(                                                                \
                &uartHandle,                                                                        \
                TOMMRO_C_UTIL_ENABLED);                                                             \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _low_power_exit_ARM(                            \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _phy_low_power_exit(                                                                 \
                &uartHandle,                                                                        \
                TOMMRO_C_UTIL_ENABLED);                                                             \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _set_prop_ARM(                                  \
            const   tommRoC_hw_bus_prop_enum_t          property,                                   \
            const   void*                       const   propValuePtr,                               \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _phy_set_prop(                                                                       \
                &uartHandle,                                                                        \
                TOMMRO_C_UTIL_ENABLED,                                                              \
                property,                                                                           \
                propValuePtr);                                                                      \
    }                                                                                               \
                                                                                                    \
    static void _ ## uartPrefix ## _get_callback_ONLY_RX_ARM(                                       \
                    tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {                               \
                                                                                                    \
        cbFunctPtr->isDataAvailable         = _ ## uartPrefix ## _is_data_available_ARM;            \
        cbFunctPtr->dataReady               = _ ## uartPrefix ## _data_ready_ARM;                   \
        cbFunctPtr->readBuffers             = _ ## uartPrefix ## _read_buffers_ARM;                 \
        cbFunctPtr->getBuffers              = _ ## uartPrefix ## _get_buffers_ARM;                  \
        cbFunctPtr->clearData               = _ ## uartPrefix ## _clear_data_ARM;                   \
        cbFunctPtr->clearReceivedData       = _ ## uartPrefix ## _clear_received_data_ARM;          \
        cbFunctPtr->lowPowerEnter           = _ ## uartPrefix ## _low_power_enter_ARM;              \
        cbFunctPtr->lowPowerExit            = _ ## uartPrefix ## _low_power_exit_ARM;               \
        cbFunctPtr->setProp                 = _ ## uartPrefix ## _set_prop_ARM;                     \
    }

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_TX_GPIO_PORT) && defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_RX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART1, _uart_handle_1, _usart_irq_write_buffer);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_TX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_ONLY_TX_TEMPLATE__(EUSART1, _uart_handle_1, _usart_irq_write_buffer);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_RX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_ONLY_RX_TEMPLATE__(EUSART1, _uart_handle_1);
#endif
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_TX_GPIO_PORT) && defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_RX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART2, _uart_handle_2, _usart_irq_write_buffer);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_TX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_ONLY_TX_TEMPLATE__(EUSART2, _uart_handle_2, _usart_irq_write_buffer);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_RX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_ONLY_RX_TEMPLATE__(EUSART2, _uart_handle_2);
#endif
#endif

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_TX_GPIO_PORT) && defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_RX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART3, _uart_handle_3, _usart_irq_write_buffer);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_TX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_ONLY_TX_TEMPLATE__(EUSART3, _uart_handle_3, _usart_irq_write_buffer);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_RX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_ONLY_RX_TEMPLATE__(EUSART3, _uart_handle_3);
#endif
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_TX_GPIO_PORT) && defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_RX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART4, _uart_handle_4, _usart_irq_write_buffer);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_TX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_ONLY_TX_TEMPLATE__(EUSART4, _uart_handle_4, _usart_irq_write_buffer);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_RX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_ONLY_RX_TEMPLATE__(EUSART4, _uart_handle_4);
#endif
#endif

#if defined (__TOMMROC_HW_USE_UART_5_TEMPLATE__)
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_TX_GPIO_PORT) && defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_RX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART5, _uart_handle_5, _usart_irq_write_buffer);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_TX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_ONLY_TX_TEMPLATE__(EUSART5, _uart_handle_5, _usart_irq_write_buffer);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_RX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_ONLY_RX_TEMPLATE__(EUSART5, _uart_handle_5);
#endif
#endif

#if defined (__TOMMROC_HW_USE_UART_6_TEMPLATE__)
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_TX_GPIO_PORT) && defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_RX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART6, _uart_handle_6, _usart_irq_write_buffer);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_TX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_ONLY_TX_TEMPLATE__(EUSART6, _uart_handle_6, _usart_irq_write_buffer);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_RX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_ONLY_RX_TEMPLATE__(EUSART6, _uart_handle_6);
#endif
#endif

#if defined (__TOMMROC_HW_USE_UART_7_TEMPLATE__)
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_TX_GPIO_PORT) && defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_RX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART7, _uart_handle_7, _usart_irq_write_buffer);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_TX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_ONLY_TX_TEMPLATE__(EUSART7, _uart_handle_7, _usart_irq_write_buffer);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_RX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_ONLY_RX_TEMPLATE__(EUSART7, _uart_handle_7);
#endif
#endif

#if defined (__TOMMROC_HW_USE_UART_8_TEMPLATE__)
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_TX_GPIO_PORT) && defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_RX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART8, _uart_handle_8, _usart_irq_write_buffer);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_TX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_ONLY_TX_TEMPLATE__(EUSART8, _uart_handle_8, _usart_irq_write_buffer);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_RX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_ONLY_RX_TEMPLATE__(EUSART8, _uart_handle_8);
#endif
#endif

#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_TX_GPIO_PORT) && defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_RX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(LEUART1, _leuart_handle_1, _usart_irq_write_buffer);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_TX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_ONLY_TX_TEMPLATE__(LEUART1, _leuart_handle_1, _usart_irq_write_buffer);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_RX_GPIO_PORT)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_ONLY_RX_TEMPLATE__(LEUART1, _leuart_handle_1);
#endif
#endif

#define __TOMMROC_HW_TEMPLATE_BUS_UART_START_TX_RX_ARM__(uartPrefix, hUart, uartHandle, cbFunctPtr, uartConfig, IRQn)   \
                                                                                                                        \
        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(                                               \
                tommRoCHwTemplateBusCommonUARTFIFOInit(                                                                 \
                        &uartConfig.buffer,                                                                             \
                        &uartHandle.txUARTFifo,                                                                         \
                        &uartHandle.rxUARTFifo));                                                                       \
                                                                                                                        \
        _ ## uartPrefix ## _get_callback_TX_RX_ARM(cbFunctPtr);                                                         \
                                                                                                                        \
        uartHandle.usartPtr     = &hUart;                                                                               \
        uartHandle.usartIRQn    = IRQn;                                                                                 \
                                                                                                                        \
        /* If needed, start receives byte in non blocking mode (interrupt) */                                           \
        if ((NULL != uartConfig.buffer.rxBufferPtr) && (0 != uartConfig.buffer.rxBufferSize)) {                         \
                                                                                                                        \
            if (HAL_OK != HAL_UART_Receive_IT(uartHandle.usartPtr, uartHandle.rxByte, 1)) {                             \
                return TOMMRO_C_HW_LOW_LEVEL_ERR;                                                                       \
            }                                                                                                           \
        }                                                                                                               \
                                                                                                                        \
        return TOMMRO_C_HW_ERR_SUCCESS;

#define __TOMMROC_HW_TEMPLATE_BUS_UART_START_ONLY_TX_ARM__(uartPrefix, hUart, uartHandle, cbFunctPtr, uartConfig, IRQn) \
                                                                                                                        \
        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(                                               \
                tommRoCHwTemplateBusCommonUARTFIFOInit(                                                                 \
                        &uartConfig.buffer,                                                                             \
                        &uartHandle.txUARTFifo,                                                                         \
                        &uartHandle.rxUARTFifo));                                                                       \
                                                                                                                        \
        _ ## uartPrefix ## _get_callback_ONLY_TX_ARM(cbFunctPtr);                                                       \
                                                                                                                        \
        uartHandle.usartPtr     = &hUart;                                                                               \
        uartHandle.usartIRQn    = IRQn;                                                                                 \
                                                                                                                        \
        return TOMMRO_C_HW_ERR_SUCCESS;

#define __TOMMROC_HW_TEMPLATE_BUS_UART_START_ONLY_RX_ARM__(uartPrefix, hUart, uartHandle, cbFunctPtr, uartConfig, IRQn) \
                                                                                                                        \
        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(                                               \
                tommRoCHwTemplateBusCommonUARTFIFOInit(                                                                 \
                        &uartConfig.buffer,                                                                             \
                        &uartHandle.txUARTFifo,                                                                         \
                        &uartHandle.rxUARTFifo));                                                                       \
                                                                                                                        \
        _ ## uartPrefix ## _get_callback_ONLY_RX_ARM(cbFunctPtr);                                                       \
                                                                                                                        \
        uartHandle.usartPtr     = &hUart;                                                                               \
        uartHandle.usartIRQn    = IRQn;                                                                                 \
                                                                                                                        \
        /* If needed, start receives byte in non blocking mode (interrupt) */                                           \
        if ((NULL != uartConfig.buffer.rxBufferPtr) && (0 != uartConfig.buffer.rxBufferSize)) {                         \
                                                                                                                        \
            if (HAL_OK != HAL_UART_Receive_IT(uartHandle.usartPtr, uartHandle.rxByte, 1)) {                             \
                return TOMMRO_C_HW_LOW_LEVEL_ERR;                                                                       \
            }                                                                                                           \
        }                                                                                                               \
                                                                                                                        \
        return TOMMRO_C_HW_ERR_SUCCESS;


/******************* BUS set prop functs */

static tommRoC_hw_err_enum_t _set_buffer_specific(
        const   tommRoC_hw_template_bus_uart_buffer_t*  const   propValuePtr,
                tommRoC_hw_template_bus_uart_buffer_t*  const   uartBufferPtr) {

    const tommRoC_hw_template_bus_uart_buffer_t empty = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_hw_template_bus_uart_buffer_t);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(uartBufferPtr, &empty, sizeof(empty)));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(uartBufferPtr, propValuePtr, sizeof(tommRoC_hw_template_bus_uart_buffer_t)));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _set_buffer(
        const   tommRoC_hw_template_bus_uart_enum_t             bus,
        const   tommRoC_hw_template_bus_uart_buffer_t*  const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_1:
        return _set_buffer_specific(propValuePtr, &_uart_config_1.buffer);
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_2:
        return _set_buffer_specific(propValuePtr, &_uart_config_2.buffer);
#endif

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_3:
        return _set_buffer_specific(propValuePtr, &_uart_config_3.buffer);
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_4:
        return _set_buffer_specific(propValuePtr, &_uart_config_4.buffer);
#endif

#if defined (__TOMMROC_HW_USE_UART_5_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_5:
        return _set_buffer_specific(propValuePtr, &_uart_config_5.buffer);
#endif

#if defined (__TOMMROC_HW_USE_UART_6_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_6:
        return _set_buffer_specific(propValuePtr, &_uart_config_6.buffer);
#endif

#if defined (__TOMMROC_HW_USE_UART_7_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_7:
        return _set_buffer_specific(propValuePtr, &_uart_config_7.buffer);
#endif

#if defined (__TOMMROC_HW_USE_UART_8_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_8:
        return _set_buffer_specific(propValuePtr, &_uart_config_8.buffer);
#endif

#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_LEUART_1:
        return _set_buffer_specific(propValuePtr, &_leuart_config_1.buffer);
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_UART_IS_USED__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUARTSetProp(
        const   tommRoC_hw_template_bus_uart_prop_enum_t            property,
        const   tommRoC_hw_template_bus_uart_enum_t                 bus,
        const   void*                                       const   propValuePtr) {

    switch (property) {

    case TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_BUFFER:
        return _set_buffer(bus, propValuePtr);

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;
    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_1_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
    static uint8_t txBuffer[__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_1_TEMPLATE_TX_BUFFER_SIZE_BYTE__];
    _uart_handle_1.txBufferPtr  = txBuffer;
    _uart_handle_1.txBufferSize = __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_1_TEMPLATE_TX_BUFFER_SIZE_BYTE__;
#endif

#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_TX_GPIO_PORT) && defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_RX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_TX_RX_ARM__(EUSART1, huart1, _uart_handle_1, cbFunctPtr, _uart_config_1, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_IRQn);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_TX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_ONLY_TX_ARM__(EUSART1, huart1, _uart_handle_1, cbFunctPtr, _uart_config_1, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_IRQn);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_RX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_ONLY_RX_ARM__(EUSART1, huart1, _uart_handle_1, cbFunctPtr, _uart_config_1, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_IRQn);
#endif
}
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART2Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_2_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
    static uint8_t txBuffer[__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_2_TEMPLATE_TX_BUFFER_SIZE_BYTE__];
    _uart_handle_2.txBufferPtr  = txBuffer;
    _uart_handle_2.txBufferSize = __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_2_TEMPLATE_TX_BUFFER_SIZE_BYTE__;
#endif

#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_TX_GPIO_PORT) && defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_RX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_TX_RX_ARM__(EUSART2, huart2, _uart_handle_2, cbFunctPtr, _uart_config_2, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_IRQn);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_TX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_ONLY_TX_ARM__(EUSART2, huart2, _uart_handle_2, cbFunctPtr, _uart_config_2, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_IRQn);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_RX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_ONLY_RX_ARM__(EUSART2, huart2, _uart_handle_2, cbFunctPtr, _uart_config_2, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_IRQn);
#endif
}
#endif

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART3Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_3_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
    static uint8_t txBuffer[__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_3_TEMPLATE_TX_BUFFER_SIZE_BYTE__];
    _uart_handle_3.txBufferPtr  = txBuffer;
    _uart_handle_3.txBufferSize = __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_3_TEMPLATE_TX_BUFFER_SIZE_BYTE__;
#endif

#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_TX_GPIO_PORT) && defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_RX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_TX_RX_ARM__(EUSART3, huart3, _uart_handle_3, cbFunctPtr, _uart_config_3, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_IRQn);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_TX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_ONLY_TX_ARM__(EUSART3, huart3, _uart_handle_3, cbFunctPtr, _uart_config_3, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_IRQn);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_RX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_ONLY_RX_ARM__(EUSART3, huart3, _uart_handle_3, cbFunctPtr, _uart_config_3, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_IRQn);
#endif
}
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART4Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_4_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
    static uint8_t txBuffer[__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_4_TEMPLATE_TX_BUFFER_SIZE_BYTE__];
    _uart_handle_4.txBufferPtr  = txBuffer;
    _uart_handle_4.txBufferSize = __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_4_TEMPLATE_TX_BUFFER_SIZE_BYTE__;
#endif

#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_TX_GPIO_PORT) && defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_RX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_TX_RX_ARM__(EUSART4, huart4, _uart_handle_4, cbFunctPtr, _uart_config_4, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_IRQn);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_TX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_ONLY_TX_ARM__(EUSART4, huart4, _uart_handle_4, cbFunctPtr, _uart_config_4, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_IRQn);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_RX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_ONLY_RX_ARM__(EUSART4, huart4, _uart_handle_4, cbFunctPtr, _uart_config_4, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_IRQn);
#endif
}
#endif

#if defined (__TOMMROC_HW_USE_UART_5_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART5Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_5_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
    static uint8_t txBuffer[__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_5_TEMPLATE_TX_BUFFER_SIZE_BYTE__];
    _uart_handle_5.txBufferPtr  = txBuffer;
    _uart_handle_5.txBufferSize = __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_5_TEMPLATE_TX_BUFFER_SIZE_BYTE__;
#endif

#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_TX_GPIO_PORT) && defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_RX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_TX_RX_ARM__(EUSART5, huart5, _uart_handle_5, cbFunctPtr, _uart_config_5, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_IRQn);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_TX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_ONLY_TX_ARM__(EUSART5, huart5, _uart_handle_5, cbFunctPtr, _uart_config_5, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_IRQn);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_RX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_ONLY_RX_ARM__(EUSART5, huart5, _uart_handle_5, cbFunctPtr, _uart_config_5, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_IRQn);
#endif
}
#endif

#if defined (__TOMMROC_HW_USE_UART_6_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART6Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_6_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
    static uint8_t txBuffer[__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_6_TEMPLATE_TX_BUFFER_SIZE_BYTE__];
    _uart_handle_6.txBufferPtr  = txBuffer;
    _uart_handle_6.txBufferSize = __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_6_TEMPLATE_TX_BUFFER_SIZE_BYTE__;
#endif

#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_TX_GPIO_PORT) && defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_RX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_TX_RX_ARM__(EUSART6, huart6, _uart_handle_6, cbFunctPtr, _uart_config_6, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_IRQn);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_TX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_ONLY_TX_ARM__(EUSART6, huart6, _uart_handle_6, cbFunctPtr, _uart_config_6, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_IRQn);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_RX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_ONLY_RX_ARM__(EUSART6, huart6, _uart_handle_6, cbFunctPtr, _uart_config_6, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_IRQn);
#endif
}
#endif

#if defined (__TOMMROC_HW_USE_UART_7_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART7Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_7_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
    static uint8_t txBuffer[__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_7_TEMPLATE_TX_BUFFER_SIZE_BYTE__];
    _uart_handle_7.txBufferPtr  = txBuffer;
    _uart_handle_7.txBufferSize = __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_7_TEMPLATE_TX_BUFFER_SIZE_BYTE__;
#endif

#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_TX_GPIO_PORT) && defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_RX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_TX_RX_ARM__(EUSART7, huart7, _uart_handle_7, cbFunctPtr, _uart_config_7, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_IRQn);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_TX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_ONLY_TX_ARM__(EUSART7, huart7, _uart_handle_7, cbFunctPtr, _uart_config_7, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_IRQn);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_RX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_ONLY_RX_ARM__(EUSART7, huart7, _uart_handle_7, cbFunctPtr, _uart_config_7, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_IRQn);
#endif
}
#endif

#if defined (__TOMMROC_HW_USE_UART_8_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART8Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_8_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
    static uint8_t txBuffer[__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_8_TEMPLATE_TX_BUFFER_SIZE_BYTE__];
    _uart_handle_8.txBufferPtr  = txBuffer;
    _uart_handle_8.txBufferSize = __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_8_TEMPLATE_TX_BUFFER_SIZE_BYTE__;
#endif

#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_TX_GPIO_PORT) && defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_RX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_TX_RX_ARM__(EUSART8, huart8, _uart_handle_8, cbFunctPtr, _uart_config_8, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_IRQn);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_TX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_ONLY_TX_ARM__(EUSART8, huart8, _uart_handle_8, cbFunctPtr, _uart_config_8, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_IRQn);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_RX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_ONLY_RX_ARM__(EUSART8, huart8, _uart_handle_8, cbFunctPtr, _uart_config_8, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_IRQn);
#endif
}
#endif

#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentLEUART1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_LEUART_1_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
    static uint8_t txBuffer[__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_LEUART_1_TEMPLATE_TX_BUFFER_SIZE_BYTE__];
    _leuart_handle_1.txBufferPtr    = txBuffer;
    _leuart_handle_1.txBufferSize   = __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_LEUART_1_TEMPLATE_TX_BUFFER_SIZE_BYTE__;
#endif

#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_TX_GPIO_PORT) && defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_RX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_TX_RX_ARM__(LEUART1, hlpuart1, _leuart_handle_1, cbFunctPtr, _leuart_config_1, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_IRQn);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_TX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_ONLY_TX_ARM__(LEUART1, hlpuart1, _leuart_handle_1, cbFunctPtr, _leuart_config_1, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_IRQn);
#elif defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_RX_GPIO_PORT)
    __TOMMROC_HW_TEMPLATE_BUS_UART_START_ONLY_RX_ARM__(LEUART1, hlpuart1, _leuart_handle_1, cbFunctPtr, _leuart_config_1, TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_IRQn);
#endif
}
#endif
#endif

#endif
