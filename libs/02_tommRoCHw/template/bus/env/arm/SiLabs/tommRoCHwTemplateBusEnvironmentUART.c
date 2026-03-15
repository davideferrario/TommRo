
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentUART.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_UART_IS_USED__)

#include "bus/common/uart/tommRoCHwTemplateBusCommonUARTFIFO.h"
#include "bus/common/uart/tommRoCHwTemplateBusCommonUARTFIFOCb.h"

#include "bus/env/arm/SiLabs/uart/tommRoCHwTemplateBusUARTSiLabsHal.h"
#include "bus/env/arm/SiLabs/uart/tommRoCHwTemplateBusUARTSiLabsLocation.h"

#if (defined (USART_PRESENT) && USART_COUNT)
#include "em_usart.h"
#endif
#if (defined (LEUART_PRESENT) && LEUART_COUNT)
#include "em_leuart.h"
#endif

#include <stdbool.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __DEFAULT_BAUDRATE__        (115200)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_UART_TEMPLATE_NOT_STANDARD_WORD_LENGTH_ENABLED__)
#error "not standard long UART frame supported"
#endif

typedef struct {

    tommRoC_hw_template_bus_uart_buffer_t           buffer;
    uint32_t                                        baudRate;
    tommRoC_hw_template_bus_uart_silabs_location_t  siLabsLocation;

} __tommRoC_hw_uart_config_t__;

#define __EMPTY___tommRoC_hw_uart_config_t____                                          \
{                                                                                       \
    /* .buffer */           __EMPTY_tommRoC_hw_template_bus_uart_buffer_t__,            \
    /* .baudRate */         __DEFAULT_BAUDRATE__,                                       \
    /* .siLabsLocation */   __EMPTY_tommRoC_hw_template_bus_uart_silabs_location_t__,   \
}

typedef struct {

    void*                                       usartPtr;   // Note: void* for compatibility with both:
                                                            // USART_TypeDef*  USART
                                                            // LEUART_TypeDef* low energy UART
#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_AT_LEAST_ONE_UART_TEMPLATE_TX_BUFFER_IS_USED__)
    uint8_t*                                    txBufferPtr;
    uint32_t                                    txBufferSize;
    uint8_t*                                    txBufferToSendDataPtr;
    uint32_t                                    txBufferToSendDataAmount;
#endif
    tommRoC_hw_template_bus_common_uart_fifo_t  txUARTFifo;
    tommRoC_hw_template_bus_common_uart_fifo_t  rxUARTFifo;
    IRQn_Type                                   txIRQn;
    bool                                        isTxInProgress;

} __tommRoC_hw_uart_handle_t__;

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_AT_LEAST_ONE_UART_TEMPLATE_TX_BUFFER_IS_USED__)
#define __EMPTY___tommRoC_hw_uart_handle_t____                                              \
{                                                                                           \
    /* .usartPtr */                 NULL,                                                   \
    /* .txBufferPtr */              NULL,                                                   \
    /* .txBufferSize */             0,                                                      \
    /* .txBufferToSendDataPtr */    NULL,                                                   \
    /* .txBufferToSendDataAmount */ 0,                                                      \
    /* .txUARTFifo */               __EMPTY_tommRoC_hw_template_bus_common_uart_fifo_t__,   \
    /* .rxUARTFifo */               __EMPTY_tommRoC_hw_template_bus_common_uart_fifo_t__,   \
    /* .txIRQn */                   NonMaskableInt_IRQn,                                    \
    /* .isTxInProgress */           false,                                                  \
}
#else
#define __EMPTY___tommRoC_hw_uart_handle_t____                                              \
{                                                                                           \
    /* .usartPtr */                 NULL,                                                   \
    /* .txUARTFifo */               __EMPTY_tommRoC_hw_template_bus_common_uart_fifo_t__,   \
    /* .rxUARTFifo */               __EMPTY_tommRoC_hw_template_bus_common_uart_fifo_t__,   \
    /* .txIRQn */                   NonMaskableInt_IRQn,                                    \
    /* .isTxInProgress */           false,                                                  \
}
#endif

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
static __tommRoC_hw_uart_config_t__ _uart_config_0 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_config_t__);
static __tommRoC_hw_uart_handle_t__ _uart_handle_0 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
static __tommRoC_hw_uart_config_t__ _uart_config_1 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_config_t__);
static __tommRoC_hw_uart_handle_t__ _uart_handle_1 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
static __tommRoC_hw_uart_config_t__ _uart_config_2 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_config_t__);
static __tommRoC_hw_uart_handle_t__ _uart_handle_2 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_LEUART_0_TEMPLATE__)
static __tommRoC_hw_uart_config_t__ _leuart_config_0 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_config_t__);
static __tommRoC_hw_uart_handle_t__ _leuart_handle_0 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)
static __tommRoC_hw_uart_config_t__ _leuart_config_1 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_config_t__);
static __tommRoC_hw_uart_handle_t__ _leuart_handle_1 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_handle_t__);
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if (defined (USART_PRESENT) && USART_COUNT)
static void _usart_rx_IRQ(__tommRoC_hw_uart_handle_t__* const uartHandlePtr) {

    USART_TypeDef* uartPtr = (USART_TypeDef*) uartHandlePtr->usartPtr;
    tommRoC_hw_template_bus_common_uart_fifo_t* rxUARTFifoPtr = &uartHandlePtr->rxUARTFifo;

    uint8_t rxData;

    if (!(uartPtr->STATUS & USART_STATUS_RXDATAV)) {
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        return;
    }

    rxData = (uint8_t) uartPtr->RXDATA;

    if (!rxUARTFifoPtr->fifoIsInit) {
        return;
    }

    // NOTE: don't use ASSERT_SUCCESS because can be possible that it return NOT_ENOUGH_RESOURCE
    tommRoCFIFOISRPush(&rxUARTFifoPtr->fifo, rxData);
}

static void _usart_tx_IRQ(__tommRoC_hw_uart_handle_t__* const uartHandlePtr) {

    USART_TypeDef* uartPtr = (USART_TypeDef*) uartHandlePtr->usartPtr;
    tommRoC_hw_template_bus_common_uart_fifo_t* txUARTFifoPtr = &uartHandlePtr->txUARTFifo;

    uint8_t txData;

    if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRPop(&txUARTFifoPtr->fifo, &txData)) {
        tommRoCHwTemplateBusUARTSiLabsHalTxIRQDisable(uartPtr);
        uartHandlePtr->isTxInProgress = false;
        return;
    }

    USART_Tx(uartPtr, txData);
}
#endif

#if (defined (LEUART_PRESENT) && LEUART_COUNT)
#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_LEUART_IS_USED__)
static void _leuart_rx_handle(__tommRoC_hw_uart_handle_t__* const uartHandlePtr) {

    LEUART_TypeDef* uartPtr = (LEUART_TypeDef*) uartHandlePtr->usartPtr;
    tommRoC_hw_template_bus_common_uart_fifo_t* rxUARTFifoPtr = &uartHandlePtr->rxUARTFifo;

    uint8_t rxData;

    if (!(uartPtr->STATUS & LEUART_STATUS_RXDATAV)) {
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        return;
    }

    rxData = (uint8_t) uartPtr->RXDATA;

    if (!rxUARTFifoPtr->fifoIsInit) {
        return;
    }

    // NOTE: don't use ASSERT_SUCCESS because can be possible that it return NOT_ENOUGH_RESOURCE
    tommRoCFIFOISRPush(&rxUARTFifoPtr->fifo, rxData);
}

static void _leuart_tx_handle(__tommRoC_hw_uart_handle_t__* const uartHandlePtr) {

    LEUART_TypeDef* uartPtr = (LEUART_TypeDef*) uartHandlePtr->usartPtr;
    tommRoC_hw_template_bus_common_uart_fifo_t* txUARTFifoPtr = &uartHandlePtr->txUARTFifo;

    uint8_t txData;

    if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRPop(&txUARTFifoPtr->fifo, &txData)) {
        tommRoCHwTemplateBusUARTSiLabsHalLETxIRQDisable(uartPtr);
        uartHandlePtr->isTxInProgress = false;
        return;
    }

    LEUART_Tx(uartPtr, txData);
}

static void _leuart_IRQ(__tommRoC_hw_uart_handle_t__* const uartHandlePtr) {

    LEUART_TypeDef* leuartPtr = (LEUART_TypeDef*) uartHandlePtr->usartPtr;

    uint32_t leuartif;

    leuartif = LEUART_IntGet(leuartPtr);
    LEUART_IntClear(leuartPtr, leuartif);

    // If RX overrun.
    if (LEUART_IF_RXOF & leuartif) {
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
    }

    // If new data arrived
    else if (LEUART_IF_RXDATAV & leuartif) {
        _leuart_rx_handle(uartHandlePtr);
    }

    // If tx complete.
    else if (LEUART_IF_TXBL & leuartif) {
        _leuart_tx_handle(uartHandlePtr);
    }

    // Ensure TXC is properly reset, needs to be handled by software
    if (LEUART_IF_TXC & leuartif) {
        LEUART_IntClear(leuartPtr, LEUART_IFC_TXC);
    }
}
#endif
#endif

/******************* IRQ Handler */
#if (defined (USART_PRESENT) && USART_COUNT)
#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
void USART0_RX_IRQHandler(void) {

    _usart_rx_IRQ(&_uart_handle_0);

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}

void USART0_TX_IRQHandler(void) {

    _usart_tx_IRQ(&_uart_handle_0);

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
void USART1_RX_IRQHandler(void) {

    _usart_rx_IRQ(&_uart_handle_1);

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}

void USART1_TX_IRQHandler(void) {

    _usart_tx_IRQ(&_uart_handle_1);

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
void USART2_RX_IRQHandler(void) {

    _usart_rx_IRQ(&_uart_handle_2);

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}

void USART2_TX_IRQHandler(void) {

    _usart_tx_IRQ(&_uart_handle_2);

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}
#endif
#endif

#if (defined (LEUART_PRESENT) && LEUART_COUNT)
#if defined (__TOMMROC_HW_USE_LEUART_0_TEMPLATE__)
void LEUART0_IRQHandler(void) {

    _leuart_IRQ(&_leuart_handle_0);

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}
#endif

#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)
void LEUART1_IRQHandler(void) {

    _leuart_IRQ(&_leuart_handle_1);

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}
#endif
#endif


/******************* Common BUS functions */

static tommRoC_hw_err_enum_t _usart_write_buffer(
                __tommRoC_hw_uart_handle_t__*   const   uartHandlePtr,
        const   uint8_t*                        const   writeBufferPtr,
        const   uint16_t                                writeBufferLen) {

    tommRoC_fifo_ISR_t* txFifoPtr = &uartHandlePtr->txUARTFifo.fifo;
    uint8_t txByte;

    // NOTE: ASSERT_SUCCESS is used because higher level function (tommRoCHwTemplateBusCommonUARTFIFOCbWriteBuffers) check for free space available
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCFIFOISRMultiPush(txFifoPtr, writeBufferPtr, writeBufferLen));

    // If uart TX already in progress
    if (tommRoCHwTemplateBusUARTSiLabsHalTxIRQIsEnabled(uartHandlePtr->usartPtr)) {
        // Next transmission managed by interrupt
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    // If pop fails, it means that already tx in interrupt (maybe a thread switch context).
    if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRPop(txFifoPtr, &txByte)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    uartHandlePtr->isTxInProgress = true;

    // Start interrupt transmission
    USART_Tx((USART_TypeDef*) uartHandlePtr->usartPtr, txByte);

    tommRoCHwTemplateBusUARTSiLabsHalTxIRQEnable(uartHandlePtr->usartPtr);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _usart_irq_write_buffer(
                __tommRoC_hw_uart_handle_t__*   const   uartHandlePtr,
        const   uint8_t*                        const   writeBufferPtr,
        const   uint16_t                                writeBufferLen) {

    tommRoC_hw_err_enum_t res;

    NVIC_DisableIRQ(uartHandlePtr->txIRQn);

    res = _usart_write_buffer(uartHandlePtr, writeBufferPtr, writeBufferLen);

    NVIC_EnableIRQ(uartHandlePtr->txIRQn);

    return res;
}

#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_LEUART_IS_USED__)
static tommRoC_hw_err_enum_t _leuart_write_buffer(
                __tommRoC_hw_uart_handle_t__*   const   uartHandlePtr,
        const   uint8_t*                        const   writeBufferPtr,
        const   uint16_t                                writeBufferLen) {

    tommRoC_fifo_ISR_t* txFifoPtr = &uartHandlePtr->txUARTFifo.fifo;
    uint8_t txByte;

    // NOTE: ASSERT_SUCCESS is used because higher level function (tommRoCHwTemplateBusCommonUARTFIFOCbWriteBuffers) check for free space available
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCFIFOISRMultiPush(txFifoPtr, writeBufferPtr, writeBufferLen));

    // If uart TX already in progress
    if (tommRoCHwTemplateBusUARTSiLabsHalLETxIRQIsEnabled(uartHandlePtr->usartPtr)) {
        // Next transmission managed by interrupt
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    // If pop fails, it means that already tx in interrupt (maybe a thread switch context).
    if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRPop(txFifoPtr, &txByte)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    uartHandlePtr->isTxInProgress = true;

    // Start interrupt transmission
    LEUART_Tx((LEUART_TypeDef*) uartHandlePtr->usartPtr, txByte);

    tommRoCHwTemplateBusUARTSiLabsHalLETxIRQEnable(uartHandlePtr->usartPtr);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _leuart_irq_write_buffer(
                __tommRoC_hw_uart_handle_t__*   const   uartHandlePtr,
        const   uint8_t*                        const   writeBufferPtr,
        const   uint16_t                                writeBufferLen) {

    tommRoC_hw_err_enum_t res;

    NVIC_DisableIRQ(uartHandlePtr->txIRQn);

    res = _leuart_write_buffer(uartHandlePtr, writeBufferPtr, writeBufferLen);

    NVIC_EnableIRQ(uartHandlePtr->txIRQn);

    return res;
}
#endif


/******************* BUS implementation functs */

#define __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(                                 \
                uartPrefix,                                                                         \
                uart,                                                                               \
                uartConfig,                                                                         \
                uartHandle,                                                                         \
                irqWriteBuffer,                                                                     \
                uartClock)                                                                          \
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
    TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                            \
    TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                           \
                                                                                                    \
    return tommRoCHwTemplateBusCommonUARTFIFOCbDataAmount(                                          \
            &uartHandle.txUARTFifo,                                                                 \
            availableAmountPtr);                                                                    \
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
            const   void*       const   inputPtr,                                                   \
                    void*       const   resultPtr) {                                                \
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
        return tommRoCHwTemplateBusUARTSiLabsHalSetForLowPowerEnter(                                \
                uartClock,                                                                          \
                &uartConfig.siLabsLocation);                                                        \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _low_power_exit_ARM(                            \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusUARTSiLabsHalSetForLowPowerExit(                                 \
                uartClock,                                                                          \
                &uartConfig.siLabsLocation);                                                        \
    }                                                                                               \
                                                                                                    \
    static void _ ## uartPrefix ## _get_callback_ARM(                                               \
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
    }


#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART0, TOMMROC_HW_TEMPLATE_BUS_UART_0, _uart_config_0, _uart_handle_0, _usart_irq_write_buffer, cmuClock_USART0);
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART1, TOMMROC_HW_TEMPLATE_BUS_UART_1, _uart_config_1, _uart_handle_1, _usart_irq_write_buffer, cmuClock_USART1);
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART2, TOMMROC_HW_TEMPLATE_BUS_UART_2, _uart_config_2, _uart_handle_2, _usart_irq_write_buffer, cmuClock_USART2);
#endif

#if defined (__TOMMROC_HW_USE_LEUART_0_TEMPLATE__)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(LEUART0, TOMMROC_HW_TEMPLATE_BUS_LEUART_0, _leuart_config_0, _leuart_handle_0, _leuart_irq_write_buffer, cmuClock_LEUART0);
#endif

#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(LEUART1, TOMMROC_HW_TEMPLATE_BUS_LEUART_1, _leuart_config_1, _leuart_handle_1, _leuart_irq_write_buffer, cmuClock_LEUART1);
#endif


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

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_0:
        return _set_buffer_specific(propValuePtr, &_uart_config_0.buffer);
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_1:
        return _set_buffer_specific(propValuePtr, &_uart_config_1.buffer);
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_2:
        return _set_buffer_specific(propValuePtr, &_uart_config_2.buffer);
#endif

#if defined (__TOMMROC_HW_USE_LEUART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_LEUART_0:
        return _set_buffer_specific(propValuePtr, &_leuart_config_0.buffer);
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

static tommRoC_hw_err_enum_t _set_baudrate(
        const   tommRoC_hw_template_bus_uart_enum_t             bus,
        const   uint32_t*                               const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_0:
        _uart_config_0.baudRate = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_1:
        _uart_config_1.baudRate = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_2:
        _uart_config_2.baudRate = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_LEUART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_LEUART_0:
        _leuart_config_0.baudRate = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_LEUART_1:
        _leuart_config_1.baudRate = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

#if defined (_USART_ROUTE_LOCATION_MASK)
static tommRoC_hw_err_enum_t _set_location(
        const   tommRoC_hw_template_bus_uart_enum_t                 bus,
        const   tommRoC_hw_template_bus_location_enum_t*    const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_0:
        return tommRoCHwTemplateBusUARTSiLabsLocationGet(bus, *propValuePtr, &_uart_config_0.siLabsLocation);
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_1:
        return tommRoCHwTemplateBusUARTSiLabsLocationGet(bus, *propValuePtr, &_uart_config_1.siLabsLocation);
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_2:
        return tommRoCHwTemplateBusUARTSiLabsLocationGet(bus, *propValuePtr, &_uart_config_2.siLabsLocation);
#endif

#if defined (__TOMMROC_HW_USE_LEUART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_LEUART_0:
        return tommRoCHwTemplateBusUARTSiLabsLocationGet(bus, *propValuePtr, &_leuart_config_0.siLabsLocation);
#endif

#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_LEUART_1:
        return tommRoCHwTemplateBusUARTSiLabsLocationGet(bus, *propValuePtr, &_leuart_config_1.siLabsLocation);
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (_GPIO_USART_ROUTEEN_RESETVALUE)
static tommRoC_hw_err_enum_t _set_tx_port(
        const   tommRoC_hw_template_bus_uart_enum_t                 bus,
        const   GPIO_Port_TypeDef*                          const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_0:
        _uart_config_0.siLabsLocation.gpioTxPort = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_1:
        _uart_config_1.siLabsLocation.gpioTxPort = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_2:
        _uart_config_2.siLabsLocation.gpioTxPort = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_LEUART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_LEUART_0:
        _leuart_config_0.siLabsLocation.gpioTxPort = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_LEUART_1:
        _leuart_config_1.siLabsLocation.gpioTxPort = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_rx_port(
        const   tommRoC_hw_template_bus_uart_enum_t                 bus,
        const   GPIO_Port_TypeDef*                          const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_0:
        _uart_config_0.siLabsLocation.gpioRxPort = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_1:
        _uart_config_1.siLabsLocation.gpioRxPort = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_2:
        _uart_config_2.siLabsLocation.gpioRxPort = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_LEUART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_LEUART_0:
        _leuart_config_0.siLabsLocation.gpioRxPort = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_LEUART_1:
        _leuart_config_1.siLabsLocation.gpioRxPort = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_tx_pin(
        const   tommRoC_hw_template_bus_uart_enum_t                 bus,
        const   uint32_t*                                   const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_0:
        _uart_config_0.siLabsLocation.gpioTxPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_1:
        _uart_config_1.siLabsLocation.gpioTxPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_2:
        _uart_config_2.siLabsLocation.gpioTxPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_LEUART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_LEUART_0:
        _leuart_config_0.siLabsLocation.gpioTxPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_LEUART_1:
        _leuart_config_1.siLabsLocation.gpioTxPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_rx_pin(
        const   tommRoC_hw_template_bus_uart_enum_t                 bus,
        const   uint32_t*                                   const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_0:
        _uart_config_0.siLabsLocation.gpioRxPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_1:
        _uart_config_1.siLabsLocation.gpioRxPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_2:
        _uart_config_2.siLabsLocation.gpioRxPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_LEUART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_LEUART_0:
        _leuart_config_0.siLabsLocation.gpioRxPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_LEUART_1:
        _leuart_config_1.siLabsLocation.gpioRxPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif


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

    case TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_BAUD_RATE:
        return _set_baudrate(bus, propValuePtr);

#if defined (_USART_ROUTE_LOCATION_MASK)
    case TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_LOCATION:
        return _set_location(bus, propValuePtr);
#endif

#if defined (_GPIO_USART_ROUTEEN_RESETVALUE)
    case TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_TX_PORT:
        return _set_tx_port(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_RX_PORT:
        return _set_rx_port(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_TX_PIN:
        return _set_tx_pin(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_RX_PIN:
        return _set_rx_pin(bus, propValuePtr);
#endif

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;
    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART0Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_0_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
    static uint8_t txBuffer[__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_0_TEMPLATE_TX_BUFFER_SIZE_BYTE__];
    _uart_handle_0.txBufferPtr  = txBuffer;
    _uart_handle_0.txBufferSize = __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_0_TEMPLATE_TX_BUFFER_SIZE_BYTE__;
#endif

    tommRoC_hw_template_bus_uart_silabs_hal_config_t halConfig;

    halConfig.clock     = cmuClock_USART0;
    halConfig.usartPtr  = (void*) USART0;
    halConfig.baudRate  = _uart_config_0.baudRate;
    halConfig.rxIRQn    = USART0_RX_IRQn;
    halConfig.txIRQn    = USART0_TX_IRQn;
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&halConfig.location, &_uart_config_0.siLabsLocation, sizeof(tommRoC_hw_template_bus_uart_silabs_location_t)));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwTemplateBusUARTSiLabsHalInit(&halConfig));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusCommonUARTFIFOInit(
                    &_uart_config_0.buffer,
                    &_uart_handle_0.txUARTFifo,
                    &_uart_handle_0.rxUARTFifo));

    _EUSART0_get_callback_ARM(cbFunctPtr);

    tommRoCHwTemplateBusUARTSiLabsHalRxIRQEnable((USART_TypeDef*) halConfig.usartPtr);

    _uart_handle_0.usartPtr = halConfig.usartPtr;
    _uart_handle_0.txIRQn   = halConfig.txIRQn;

    return TOMMRO_C_HW_ERR_SUCCESS;
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

    tommRoC_hw_template_bus_uart_silabs_hal_config_t halConfig;

    halConfig.clock     = cmuClock_USART1;
    halConfig.usartPtr  = (void*) USART1;
    halConfig.baudRate  = _uart_config_1.baudRate;
    halConfig.rxIRQn    = USART1_RX_IRQn;
    halConfig.txIRQn    = USART1_TX_IRQn;
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&halConfig.location, &_uart_config_1.siLabsLocation, sizeof(tommRoC_hw_template_bus_uart_silabs_location_t)));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwTemplateBusUARTSiLabsHalInit(&halConfig));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusCommonUARTFIFOInit(
                    &_uart_config_1.buffer,
                    &_uart_handle_1.txUARTFifo,
                    &_uart_handle_1.rxUARTFifo));

    _EUSART1_get_callback_ARM(cbFunctPtr);

    tommRoCHwTemplateBusUARTSiLabsHalRxIRQEnable((USART_TypeDef*) halConfig.usartPtr);

    _uart_handle_1.usartPtr = halConfig.usartPtr;
    _uart_handle_1.txIRQn   = halConfig.txIRQn;

    return TOMMRO_C_HW_ERR_SUCCESS;
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

    tommRoC_hw_template_bus_uart_silabs_hal_config_t halConfig;

    halConfig.clock     = cmuClock_USART2;
    halConfig.usartPtr  = (void*) USART2;
    halConfig.baudRate  = _uart_config_2.baudRate;
    halConfig.rxIRQn    = USART2_RX_IRQn;
    halConfig.txIRQn    = USART2_TX_IRQn;
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&halConfig.location, &_uart_config_2.siLabsLocation, sizeof(tommRoC_hw_template_bus_uart_silabs_location_t)));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwTemplateBusUARTSiLabsHalInit(&halConfig));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusCommonUARTFIFOInit(
                    &_uart_config_2.buffer,
                    &_uart_handle_2.txUARTFifo,
                    &_uart_handle_2.rxUARTFifo));

    _EUSART2_get_callback_ARM(cbFunctPtr);

    tommRoCHwTemplateBusUARTSiLabsHalRxIRQEnable((USART_TypeDef*) halConfig.usartPtr);

    _uart_handle_2.usartPtr = halConfig.usartPtr;
    _uart_handle_2.txIRQn   = halConfig.txIRQn;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_LEUART_0_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentLEUART0Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_LEUART_0_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
    static uint8_t txBuffer[__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_LEUART_0_TEMPLATE_TX_BUFFER_SIZE_BYTE__];
    _leuart_handle_0.txBufferPtr    = txBuffer;
    _leuart_handle_0.txBufferSize   = __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_LEUART_0_TEMPLATE_TX_BUFFER_SIZE_BYTE__;
#endif

    tommRoC_hw_template_bus_uart_silabs_hal_config_t halConfig;

    halConfig.clock     = cmuClock_LEUART0;
    halConfig.usartPtr  = (void*) LEUART0;
    halConfig.baudRate  = _leuart_config_0.baudRate;
    halConfig.rxIRQn    = LEUART0_IRQn;
    halConfig.txIRQn    = LEUART0_IRQn;
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&halConfig.location, &_leuart_config_0.siLabsLocation, sizeof(tommRoC_hw_template_bus_uart_silabs_location_t)));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwTemplateBusUARTSiLabsHalLEInit(&halConfig));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusCommonUARTFIFOInit(
                    &_leuart_config_0.buffer,
                    &_leuart_handle_0.txUARTFifo,
                    &_leuart_handle_0.rxUARTFifo));

    _LEUART0_get_callback_ARM(cbFunctPtr);

    tommRoCHwTemplateBusUARTSiLabsHalLERxIRQEnable((LEUART_TypeDef*) halConfig.usartPtr);

    _leuart_handle_0.usartPtr   = halConfig.usartPtr;
    _leuart_handle_0.txIRQn     = halConfig.txIRQn;

    return TOMMRO_C_HW_ERR_SUCCESS;
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

    tommRoC_hw_template_bus_uart_silabs_hal_config_t halConfig;

    halConfig.clock     = cmuClock_LEUART1;
    halConfig.usartPtr  = (void*) LEUART1;
    halConfig.baudRate  = _leuart_config_1.baudRate;
    halConfig.rxIRQn    = LEUART1_IRQn;
    halConfig.txIRQn    = LEUART1_IRQn;
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&halConfig.location, &_leuart_config_1.siLabsLocation, sizeof(tommRoC_hw_template_bus_uart_silabs_location_t)));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwTemplateBusUARTSiLabsHalLEInit(&halConfig));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusCommonUARTFIFOInit(
                    &_leuart_config_1.buffer,
                    &_leuart_handle_1.txUARTFifo,
                    &_leuart_handle_1.rxUARTFifo));

    _LEUART1_get_callback_ARM(cbFunctPtr);

    tommRoCHwTemplateBusUARTSiLabsHalLERxIRQEnable((LEUART_TypeDef*) halConfig.usartPtr);

    _leuart_handle_1.usartPtr   = halConfig.usartPtr;
    _leuart_handle_1.txIRQn     = halConfig.txIRQn;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif

#endif
