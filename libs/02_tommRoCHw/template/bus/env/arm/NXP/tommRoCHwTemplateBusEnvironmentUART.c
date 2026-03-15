
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentUART.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_UART_IS_USED__)

#include "bus/common/uart/tommRoCHwTemplateBusCommonUARTFIFO.h"
#include "bus/common/uart/tommRoCHwTemplateBusCommonUARTFIFOCb.h"

#include "bus/env/arm/NXP/uart/tommRoCHwTemplateBusUARTNXPHal.h"
#include "bus/env/arm/NXP/uart/tommRoCHwTemplateBusUARTNXPLocation.h"

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
#include "fsl_uart.h"
#endif

#if defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
#include "fsl_usart.h"
#endif

#if defined (FSL_FEATURE_SOC_LPUART_COUNT) && FSL_FEATURE_SOC_LPUART_COUNT
#include "fsl_lpuart.h"
#endif

#include <stdbool.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __DEFAULT_BAUDRATE__            (115200)
#define __DEFAULT_ROUTE_LOCATION__      (TOMMROC_HW_TEMPLATE_LOCATION_0)

/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping exception return operation might vector to incorrect interrupt */
#if (defined __CORTEX_M) && ((__CORTEX_M == 4U) || (__CORTEX_M == 7U))
#define __ISR_EXIT_BARRIER__()      __DSB()
#else
#define __ISR_EXIT_BARRIER__()
#endif

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_UART_TEMPLATE_NOT_STANDARD_WORD_LENGTH_ENABLED__)
#error "not standard long UART frame supported"
#endif

typedef struct {

    tommRoC_hw_template_bus_uart_buffer_t   buffer;
    uint32_t                                baudRate;
    tommRoC_hw_template_bus_location_enum_t location;

} __tommRoC_hw_uart_config_t__;

#define __EMPTY___tommRoC_hw_uart_config_t____                              \
{                                                                           \
    /* .buffer */       __EMPTY_tommRoC_hw_template_bus_uart_buffer_t__,    \
    /* .baudRate */     __DEFAULT_BAUDRATE__,                               \
    /* .location */     __DEFAULT_ROUTE_LOCATION__,                         \
}

typedef struct {

    void*                                       usartPtr;   // Note: void* for compatibility with both:
                                                            // UART_Type*  USART
                                                            // LPUART_Type* low power UART
#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_AT_LEAST_ONE_UART_TEMPLATE_TX_BUFFER_IS_USED__)
    uint8_t*                                    txBufferPtr;
    uint32_t                                    txBufferSize;
    uint8_t*                                    txBufferToSendDataPtr;
    uint32_t                                    txBufferToSendDataAmount;
#endif
    tommRoC_hw_template_bus_common_uart_fifo_t  txUARTFifo;
    tommRoC_hw_template_bus_common_uart_fifo_t  rxUARTFifo;
    IRQn_Type                                   rxTxIRQn;
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
    /* .rxTxIRQn */                 NotAvail_IRQn,                                          \
    /* .isTxInProgress */           false,                                                  \
}
#else
#define __EMPTY___tommRoC_hw_uart_handle_t____                                              \
{                                                                                           \
    /* .usartPtr */                 NULL,                                                   \
    /* .txUARTFifo */               __EMPTY_tommRoC_hw_template_bus_common_uart_fifo_t__,   \
    /* .rxUARTFifo */               __EMPTY_tommRoC_hw_template_bus_common_uart_fifo_t__,   \
    /* .rxTxIRQn */                 NotAvail_IRQn,                                          \
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

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if (defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT) || \
    (defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT)
static void _usart_rx_handle(__tommRoC_hw_uart_handle_t__* const uartHandlePtr) {

    void* usartPtr = uartHandlePtr->usartPtr;
    tommRoC_hw_template_bus_common_uart_fifo_t* rxUARTFifoPtr = &uartHandlePtr->rxUARTFifo;

    uint8_t rxData;

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    rxData = UART_ReadByte((UART_Type*) usartPtr);
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    rxData = USART_ReadByte((USART_Type*) usartPtr);
#endif

    if (!rxUARTFifoPtr->fifoIsInit) {
        return;
    }

    // NOTE: don't use ASSERT_SUCCESS because can be possible that it return NOT_ENOUGH_RESOURCE
    tommRoCFIFOISRPush(&rxUARTFifoPtr->fifo, rxData);
}

static void _usart_tx_handle(__tommRoC_hw_uart_handle_t__* const uartHandlePtr) {

    void* usartPtr = uartHandlePtr->usartPtr;
    tommRoC_hw_template_bus_common_uart_fifo_t* txUARTFifoPtr = &uartHandlePtr->txUARTFifo;

    uint8_t txData;

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_AT_LEAST_ONE_UART_TEMPLATE_TX_BUFFER_IS_USED__)
    uint32_t inAmount;
    uint32_t toTxSize;
#endif

#if !defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_AT_LEAST_ONE_UART_TEMPLATE_TX_BUFFER_IS_USED__)
    if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRPop(&txUARTFifoPtr->fifo, &txData)) {
        tommRoCHwTemplateBusUARTNXPHalTxIRQDisable(usartPtr);
        uartHandlePtr->isTxInProgress = false;
        return;
    }

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    UART_WriteByte((UART_Type*) usartPtr, txData);
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    USART_WriteByte((USART_Type*) usartPtr, txData);
#endif
    return;
#else

    if ((NULL == uartHandlePtr->txBufferPtr) || (0 == uartHandlePtr->txBufferSize)) {

        if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRPop(&txUARTFifoPtr->fifo, &txData)) {
            tommRoCHwTemplateBusUARTNXPHalTxIRQDisable(usartPtr);
            uartHandlePtr->isTxInProgress = false;
            return;
        }

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
        UART_WriteByte((UART_Type*) usartPtr, txData);
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
        USART_WriteByte((USART_Type*) usartPtr, txData);
#endif
        return;
    }
    else {

        --uartHandlePtr->txBufferToSendDataAmount;
        if (uartHandlePtr->txBufferToSendDataAmount > 0) {
            ++uartHandlePtr->txBufferToSendDataPtr;
#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
            UART_WriteByte((UART_Type*) usartPtr, *(uartHandlePtr->txBufferToSendDataPtr));
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
            USART_WriteByte((USART_Type*) usartPtr, *(uartHandlePtr->txBufferToSendDataPtr));
#endif
            return;
        }

        if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRInsideObjAmount(&txUARTFifoPtr->fifo, &inAmount)) {
            tommRoCHwTemplateBusUARTNXPHalTxIRQDisable(usartPtr);
            uartHandlePtr->isTxInProgress = false;
            return;
        }

        if (0 == inAmount) {
            tommRoCHwTemplateBusUARTNXPHalTxIRQDisable(usartPtr);
            uartHandlePtr->isTxInProgress = false;
            return;
        }

        toTxSize = tommRoCMathMin(inAmount, uartHandlePtr->txBufferSize);

        if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRMultiPop(&txUARTFifoPtr->fifo, uartHandlePtr->txBufferPtr, toTxSize)) {
            tommRoCHwTemplateBusUARTNXPHalTxIRQDisable(usartPtr);
            uartHandlePtr->isTxInProgress = false;
            return;
        }

        uartHandlePtr->txBufferToSendDataPtr    = uartHandlePtr->txBufferPtr;
        uartHandlePtr->txBufferToSendDataAmount = toTxSize;

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
        UART_WriteByte((UART_Type*) usartPtr, *(uartHandlePtr->txBufferToSendDataPtr));
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
        USART_WriteByte((USART_Type*) usartPtr, *(uartHandlePtr->txBufferToSendDataPtr));
#endif
        return;
    }
#endif
}

static void _usart_rx_IRQ(__tommRoC_hw_uart_handle_t__* const uartHandlePtr) {

    void* usartPtr = uartHandlePtr->usartPtr;

    uint32_t statusFlag;

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    statusFlag = UART_GetStatusFlags((UART_Type*) usartPtr);
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    statusFlag = USART_GetStatusFlags((USART_Type*) usartPtr);
#endif

    // If RX overrun.
#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    if (kUART_RxOverrunFlag & statusFlag) {
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    if (kUSART_RxError & statusFlag) {
#endif

        // Read DATA, otherwise the RX does not work.
#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
        UART_ReadByte((UART_Type*) usartPtr);
        UART_ClearStatusFlags((UART_Type*) usartPtr, kUART_RxOverrunFlag);
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
        USART_ReadByte((USART_Type*) usartPtr);
        USART_ClearStatusFlags((USART_Type*) usartPtr, kUSART_RxError);
#endif
    }

    // If new data arrived
#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    if (kUART_RxDataRegFullFlag & statusFlag) {
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
   if (kUSART_RxFifoNotEmptyFlag & statusFlag) {
#endif

        _usart_rx_handle(uartHandlePtr);
    }
}

static void _usart_tx_IRQ(__tommRoC_hw_uart_handle_t__* const uartHandlePtr) {

    void* usartPtr = uartHandlePtr->usartPtr;

    uint32_t statusFlag;

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    statusFlag = UART_GetStatusFlags((UART_Type*) usartPtr);
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    statusFlag = USART_GetStatusFlags((USART_Type*) usartPtr);
#endif

    // If tx complete.
#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    if (kUART_TxDataRegEmptyFlag & statusFlag) {
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    if (kUSART_TxFifoEmptyFlag & statusFlag) {
#endif

        _usart_tx_handle(uartHandlePtr);
    }
}

static void _usart_IRQ(__tommRoC_hw_uart_handle_t__* const uartHandlePtr) {

    _usart_rx_IRQ(uartHandlePtr);
    _usart_tx_IRQ(uartHandlePtr);
}
#endif

#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_LEUART_IS_USED__)
static void _leuart_rx_handle(__tommRoC_hw_uart_handle_t__* const uartHandlePtr) {

    LPUART_Type* lpuartPtr = (LPUART_Type*) uartHandlePtr->usartPtr;
    tommRoC_hw_template_bus_common_uart_fifo_t* rxUARTFifoPtr = &uartHandlePtr->rxUARTFifo;

    uint8_t rxData;

    rxData = LPUART_ReadByte(lpuartPtr);

    if (!rxUARTFifoPtr->fifoIsInit) {
        return;
    }

    // NOTE: don't use ASSERT_SUCCESS because can be possible that it return NOT_ENOUGH_RESOURCE
    tommRoCFIFOISRPush(&rxUARTFifoPtr->fifo, rxData);
}

static void _leuart_tx_handle(__tommRoC_hw_uart_handle_t__* const uartHandlePtr) {

    LPUART_Type* lpuartPtr = (LPUART_Type*) uartHandlePtr->usartPtr;
    tommRoC_hw_template_bus_common_uart_fifo_t* txUARTFifoPtr = &uartHandlePtr->txUARTFifo;

    uint8_t txData;

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_AT_LEAST_ONE_UART_TEMPLATE_TX_BUFFER_IS_USED__)
    uint32_t inAmount;
    uint32_t toTxSize;
#endif

#if !defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_AT_LEAST_ONE_UART_TEMPLATE_TX_BUFFER_IS_USED__)
    if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRPop(&txUARTFifoPtr->fifo, &txData)) {
        tommRoCHwTemplateBusUARTNXPHalLETxIRQDisable(lpuartPtr);
        uartHandlePtr->isTxInProgress = false;
        return;
    }

    LPUART_WriteByte(lpuartPtr, txData);
    return;
#else

    if ((NULL == uartHandlePtr->txBufferPtr) || (0 == uartHandlePtr->txBufferSize)) {

        if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRPop(&txUARTFifoPtr->fifo, &txData)) {
            tommRoCHwTemplateBusUARTNXPHalLETxIRQDisable(lpuartPtr);
            uartHandlePtr->isTxInProgress = false;
            return;
        }

        LPUART_WriteByte(lpuartPtr, txData);
        return;
    }
    else {

        --uartHandlePtr->txBufferToSendDataAmount;
        if (uartHandlePtr->txBufferToSendDataAmount > 0) {
            ++uartHandlePtr->txBufferToSendDataPtr;
            LPUART_WriteByte(lpuartPtr, *(uartHandlePtr->txBufferToSendDataPtr));
            return;
        }

        if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRInsideObjAmount(&txUARTFifoPtr->fifo, &inAmount)) {
            tommRoCHwTemplateBusUARTNXPHalLETxIRQDisable(lpuartPtr);
            uartHandlePtr->isTxInProgress = false;
            return;
        }

        if (0 == inAmount) {
            tommRoCHwTemplateBusUARTNXPHalLETxIRQDisable(lpuartPtr);
            uartHandlePtr->isTxInProgress = false;
            return;
        }

        toTxSize = tommRoCMathMin(inAmount, uartHandlePtr->txBufferSize);

        if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRMultiPop(&txUARTFifoPtr->fifo, uartHandlePtr->txBufferPtr, toTxSize)) {
            tommRoCHwTemplateBusUARTNXPHalLETxIRQDisable(lpuartPtr);
            uartHandlePtr->isTxInProgress = false;
            return;
        }

        uartHandlePtr->txBufferToSendDataPtr    = uartHandlePtr->txBufferPtr;
        uartHandlePtr->txBufferToSendDataAmount = toTxSize;

        LPUART_WriteByte(lpuartPtr, *(uartHandlePtr->txBufferToSendDataPtr));
        return;
    }
#endif
}

static void _leuart_rx_IRQ(__tommRoC_hw_uart_handle_t__* const uartHandlePtr) {

    LPUART_Type* lpuartPtr = (LPUART_Type*) uartHandlePtr->usartPtr;

    uint32_t statusFlag;

    statusFlag = LPUART_GetStatusFlags(lpuartPtr);

    // If RX overrun.
    if (kLPUART_RxOverrunFlag & statusFlag) {
        // Read DATA, otherwise the RX does not work.
        LPUART_ReadByte(lpuartPtr);
        LPUART_ClearStatusFlags(lpuartPtr, kLPUART_RxOverrunFlag);
    }

    // If new data arrived
    if (kLPUART_RxDataRegFullFlag & statusFlag) {
        _leuart_rx_handle(uartHandlePtr);
    }
}

static void _leuart_tx_IRQ(__tommRoC_hw_uart_handle_t__* const uartHandlePtr) {

    LPUART_Type* lpuartPtr = (LPUART_Type*) uartHandlePtr->usartPtr;

    uint32_t statusFlag;

    statusFlag = LPUART_GetStatusFlags(lpuartPtr);

    // If tx complete.
    if (kLPUART_TxDataRegEmptyFlag & statusFlag) {
        _leuart_tx_handle(uartHandlePtr);
    }
}

static void _leuart_IRQ(__tommRoC_hw_uart_handle_t__* const uartHandlePtr) {

    _leuart_rx_IRQ(uartHandlePtr);
    _leuart_tx_IRQ(uartHandlePtr);
}
#endif


/******************* IRQ Handler */
#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
#if defined (FSL_FEATURE_UART_HAS_SEPARATE_RX_TX_IRQ) && FSL_FEATURE_UART_HAS_SEPARATE_RX_TX_IRQ
void UART0_RX_IRQHandler(void) {

    _usart_rx_IRQ(&_uart_handle_0);

    __ISR_EXIT_BARRIER__();
}
void UART0_TX_IRQHandler(void) {

    _usart_tx_IRQ(&_uart_handle_0);

    __ISR_EXIT_BARRIER__();
}
#else
void UART0_RX_TX_IRQHandler(void) {

    _usart_IRQ(&_uart_handle_0);

    __ISR_EXIT_BARRIER__();
}
void UART0_IRQHandler(void) {
    UART0_RX_TX_IRQHandler();
}
void USART0_IRQHandler(void) {
    UART0_RX_TX_IRQHandler();
}
void FLEXCOMM0_IRQHandler(void) {
    UART0_RX_TX_IRQHandler();
}
#endif
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
#if defined (FSL_FEATURE_UART_HAS_SEPARATE_RX_TX_IRQ) && FSL_FEATURE_UART_HAS_SEPARATE_RX_TX_IRQ
void UART1_RX_IRQHandler(void) {

    _usart_rx_IRQ(&_uart_handle_1);

    __ISR_EXIT_BARRIER__();
}
void UART1_TX_IRQHandler(void) {

    _usart_tx_IRQ(&_uart_handle_1);

    __ISR_EXIT_BARRIER__();
}
#else
void UART1_RX_TX_IRQHandler(void) {

    _usart_IRQ(&_uart_handle_1);

    __ISR_EXIT_BARRIER__();
}
void UART1_IRQHandler(void) {
    UART1_RX_TX_IRQHandler();
}
void USART1_IRQHandler(void) {
    UART1_RX_TX_IRQHandler();
}
void FLEXCOMM1_IRQHandler(void) {
    UART1_RX_TX_IRQHandler();
}
#endif
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
#if defined (FSL_FEATURE_UART_HAS_SEPARATE_RX_TX_IRQ) && FSL_FEATURE_UART_HAS_SEPARATE_RX_TX_IRQ
void UART2_RX_IRQHandler(void) {

    _usart_rx_IRQ(&_uart_handle_2);

    __ISR_EXIT_BARRIER__();
}
void UART2_TX_IRQHandler(void) {

    _usart_tx_IRQ(&_uart_handle_2);

    __ISR_EXIT_BARRIER__();
}
#else
void UART2_RX_TX_IRQHandler(void) {

    _usart_IRQ(&_uart_handle_2);

    __ISR_EXIT_BARRIER__();
}
void UART2_IRQHandler(void) {
    UART2_RX_TX_IRQHandler();
}
void USART2_IRQHandler(void) {
    UART2_RX_TX_IRQHandler();
}
void FLEXCOMM2_IRQHandler(void) {
    UART2_RX_TX_IRQHandler();
}
#endif
#endif

#if defined (__TOMMROC_HW_USE_LEUART_0_TEMPLATE__)
#if defined (FSL_FEATURE_LPUART_HAS_SEPARATE_RX_TX_IRQ) && FSL_FEATURE_LPUART_HAS_SEPARATE_RX_TX_IRQ
void LPUART0_RX_IRQHandler(void) {

    _leuart_rx_IRQ(&_leuart_handle_0);

    __ISR_EXIT_BARRIER__();
}
void LPUART0_TX_IRQHandler(void) {

    _leuart_tx_IRQ(&_leuart_handle_0);

    __ISR_EXIT_BARRIER__();
}
#else
void LPUART0_IRQHandler(void) {

    _leuart_IRQ(&_leuart_handle_0);

    __ISR_EXIT_BARRIER__();
}
#endif
#endif


/******************* Common BUS functions */

#if (defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT) || \
    (defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT)
static tommRoC_hw_err_enum_t _usart_write_buffer(
                __tommRoC_hw_uart_handle_t__*   const   uartHandlePtr,
        const   uint8_t*                        const   writeBufferPtr,
        const   uint16_t                                writeBufferLen) {

    tommRoC_fifo_ISR_t* txFifoPtr = &uartHandlePtr->txUARTFifo.fifo;
    uint8_t txByte;

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_AT_LEAST_ONE_UART_TEMPLATE_TX_BUFFER_IS_USED__)
    uint32_t inAmount;
    uint32_t toTxSize;
#endif

    // NOTE: ASSERT_SUCCESS is used because higher level function (tommRoCHwTemplateBusCommonUARTFIFOCbWriteBuffers) check for free space available
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCFIFOISRMultiPush(txFifoPtr, writeBufferPtr, writeBufferLen));

    // If uart TX already in progress
    if (tommRoCHwTemplateBusUARTNXPHalTxIRQIsEnabled(uartHandlePtr->usartPtr)) {
        // Next transmission managed by interrupt
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

#if !defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_AT_LEAST_ONE_UART_TEMPLATE_TX_BUFFER_IS_USED__)
#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
    // NOTE: workaround for MKE02Z4 first byte TX lost
    static bool firstExecute = true;

    if (firstExecute) {
        if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRGet(txFifoPtr, &txByte)) {
            return TOMMRO_C_HW_ERR_SUCCESS;
        }

        firstExecute = false;
    }
    else {
#endif

    // If pop fails, it means that already tx in interrupt (maybe a thread switch context).
    if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRPop(txFifoPtr, &txByte)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
    }
#endif

    uartHandlePtr->isTxInProgress = true;

    // Start interrupt transmission
#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    UART_WriteByte((UART_Type*) uartHandlePtr->usartPtr, txByte);
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    USART_WriteByte((USART_Type*) uartHandlePtr->usartPtr, txByte);
#endif

    tommRoCHwTemplateBusUARTNXPHalTxIRQEnable(uartHandlePtr->usartPtr);

    return TOMMRO_C_HW_ERR_SUCCESS;
#else

    if ((NULL == uartHandlePtr->txBufferPtr) || (0 == uartHandlePtr->txBufferSize)) {
#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
        // NOTE: workaround for MKE02Z4 first byte TX lost
        static bool firstExecute = true;

        if (firstExecute) {
            if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRGet(txFifoPtr, &txByte)) {
                return TOMMRO_C_HW_ERR_SUCCESS;
            }

            firstExecute = false;
        }
        else {
#endif

        // If pop fails, it means that already tx in interrupt (maybe a thread switch context).
        if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRPop(txFifoPtr, &txByte)) {
            return TOMMRO_C_HW_ERR_SUCCESS;
        }

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
        }
#endif

        uartHandlePtr->isTxInProgress = true;

        // Start interrupt transmission
#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
        UART_WriteByte((UART_Type*) uartHandlePtr->usartPtr, txByte);
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
        USART_WriteByte((USART_Type*) uartHandlePtr->usartPtr, txByte);
#endif

        tommRoCHwTemplateBusUARTNXPHalTxIRQEnable(uartHandlePtr->usartPtr);

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

        uartHandlePtr->txBufferToSendDataPtr    = uartHandlePtr->txBufferPtr;
        uartHandlePtr->txBufferToSendDataAmount = toTxSize;

        uartHandlePtr->isTxInProgress = true;

        // Start interrupt transmission
#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
        UART_WriteByte((UART_Type*) uartHandlePtr->usartPtr, txByte);
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
        USART_WriteByte((USART_Type*) uartHandlePtr->usartPtr, txByte);
#endif

        tommRoCHwTemplateBusUARTNXPHalTxIRQEnable(uartHandlePtr->usartPtr);

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif
}

static tommRoC_hw_err_enum_t _usart_irq_write_buffer(
                __tommRoC_hw_uart_handle_t__*   const   uartHandlePtr,
        const   uint8_t*                        const   writeBufferPtr,
        const   uint16_t                                writeBufferLen) {

    tommRoC_hw_err_enum_t res;

    DisableIRQ(uartHandlePtr->rxTxIRQn);

    res = _usart_write_buffer(uartHandlePtr, writeBufferPtr, writeBufferLen);

    EnableIRQ(uartHandlePtr->rxTxIRQn);

    return res;
}
#endif

#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_LEUART_IS_USED__)
static tommRoC_hw_err_enum_t _leuart_write_buffer(
                __tommRoC_hw_uart_handle_t__*   const   uartHandlePtr,
        const   uint8_t*                        const   writeBufferPtr,
        const   uint16_t                                writeBufferLen) {

    tommRoC_fifo_ISR_t* txFifoPtr = &uartHandlePtr->txUARTFifo.fifo;
    uint8_t txByte;

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_AT_LEAST_ONE_UART_TEMPLATE_TX_BUFFER_IS_USED__)
    uint32_t inAmount;
    uint32_t toTxSize;
#endif

    // NOTE: ASSERT_SUCCESS is used because higher level function (tommRoCHwTemplateBusCommonUARTFIFOCbWriteBuffers) check for free space available
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCFIFOISRMultiPush(txFifoPtr, writeBufferPtr, writeBufferLen));

    // If uart TX already in progress
    if (tommRoCHwTemplateBusUARTNXPHalLETxIRQIsEnabled(uartHandlePtr->usartPtr)) {
        // Next transmission managed by interrupt
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

#if !defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_AT_LEAST_ONE_UART_TEMPLATE_TX_BUFFER_IS_USED__)
#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
    // NOTE: workaround for MKE02Z4 first byte TX lost
    static bool firstExecute = true;

    if (firstExecute) {
        if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRGet(txFifoPtr, &txByte)) {
            return TOMMRO_C_HW_ERR_SUCCESS;
        }

        firstExecute = false;
    }
    else {
#endif

    // If pop fails, it means that already tx in interrupt (maybe a thread switch context).
    if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRPop(txFifoPtr, &txByte)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
    }
#endif

    uartHandlePtr->isTxInProgress = true;

    // Start interrupt transmission
    LPUART_WriteByte((LPUART_Type*) uartHandlePtr->usartPtr, txByte);

    tommRoCHwTemplateBusUARTNXPHalLETxIRQEnable(uartHandlePtr->usartPtr);

    return TOMMRO_C_HW_ERR_SUCCESS;
#else

    if ((NULL == uartHandlePtr->txBufferPtr) || (0 == uartHandlePtr->txBufferSize)) {
#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
        // NOTE: workaround for MKE02Z4 first byte TX lost
        static bool firstExecute = true;

        if (firstExecute) {
            if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRGet(txFifoPtr, &txByte)) {
                return TOMMRO_C_HW_ERR_SUCCESS;
            }

            firstExecute = false;
        }
        else {
#endif

        // If pop fails, it means that already tx in interrupt (maybe a thread switch context).
        if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRPop(txFifoPtr, &txByte)) {
            return TOMMRO_C_HW_ERR_SUCCESS;
        }

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
        }
#endif

        uartHandlePtr->isTxInProgress = true;

        // Start interrupt transmission
        LPUART_WriteByte((LPUART_Type*) uartHandlePtr->usartPtr, txByte);

        tommRoCHwTemplateBusUARTNXPHalLETxIRQEnable(uartHandlePtr->usartPtr);

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

        uartHandlePtr->txBufferToSendDataPtr    = uartHandlePtr->txBufferPtr;
        uartHandlePtr->txBufferToSendDataAmount = toTxSize;

        uartHandlePtr->isTxInProgress = true;

        // Start interrupt transmission
        LPUART_WriteByte((LPUART_Type*) uartHandlePtr->usartPtr, *(uartHandlePtr->txBufferToSendDataPtr));

        tommRoCHwTemplateBusUARTNXPHalLETxIRQEnable(uartHandlePtr->usartPtr);

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif
}

static tommRoC_hw_err_enum_t _leuart_irq_write_buffer(
                __tommRoC_hw_uart_handle_t__*   const   uartHandlePtr,
        const   uint8_t*                        const   writeBufferPtr,
        const   uint16_t                                writeBufferLen) {

    tommRoC_hw_err_enum_t res;

    DisableIRQ(uartHandlePtr->rxTxIRQn);

    res = _leuart_write_buffer(uartHandlePtr, writeBufferPtr, writeBufferLen);

    EnableIRQ(uartHandlePtr->rxTxIRQn);

    return res;
}
#endif

#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_UART_IS_USED__)
static tommRoC_hw_err_enum_t _phy_low_power_enter(
        const   tommRoC_hw_template_bus_uart_enum_t         uart,
        const   tommRoC_hw_template_bus_location_enum_t     location) {

    tommRoC_hw_template_bus_uart_nxp_location_t locationConfig;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwTemplateBusUARTNXPLocationGet(
                    uart,
                    location,
                    &locationConfig));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusUARTNXPHalSetForLowPowerEnter(
                    &locationConfig));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_low_power_exit(
        const   tommRoC_hw_template_bus_uart_enum_t         uart,
        const   tommRoC_hw_template_bus_location_enum_t     location) {

    tommRoC_hw_template_bus_uart_nxp_location_t locationConfig;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwTemplateBusUARTNXPLocationGet(
                    uart,
                    location,
                    &locationConfig));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusUARTNXPHalSetForLowPowerExit(
                    &locationConfig));

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif


/******************* BUS implementation functs */

#define __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(                                 \
                uartPrefix,                                                                         \
                uart,                                                                               \
                uartConfig,                                                                         \
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
        return _phy_low_power_enter(uart, uartConfig.location);                                     \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _low_power_exit_ARM(                            \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _phy_low_power_exit(uart, uartConfig.location);                                      \
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
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART0, TOMMROC_HW_TEMPLATE_BUS_UART_0, _uart_config_0, _uart_handle_0, _usart_irq_write_buffer);
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART1, TOMMROC_HW_TEMPLATE_BUS_UART_1, _uart_config_1, _uart_handle_1, _usart_irq_write_buffer);
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART2, TOMMROC_HW_TEMPLATE_BUS_UART_2, _uart_config_2, _uart_handle_2, _usart_irq_write_buffer);
#endif

#if defined (__TOMMROC_HW_USE_LEUART_0_TEMPLATE__)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(LEUART0, TOMMROC_HW_TEMPLATE_BUS_LEUART_0, _leuart_config_0, _leuart_handle_0, _leuart_irq_write_buffer);
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

static tommRoC_hw_err_enum_t _set_location(
        const   tommRoC_hw_template_bus_uart_enum_t                 bus,
        const   tommRoC_hw_template_bus_location_enum_t*    const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_0:
        _uart_config_0.location = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_1:
        _uart_config_1.location = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_2:
        _uart_config_2.location = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_LEUART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_LEUART_0:
        _leuart_config_0.location = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_LEUART_1:
        _leuart_config_1.location = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
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

    case TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_BAUD_RATE:
        return _set_baudrate(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_LOCATION:
        return _set_location(bus, propValuePtr);

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

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    const UART_Type* const usartBase[] = UART_BASE_PTRS;
    const IRQn_Type usartIRQ[] = UART_RX_TX_IRQS;

    uart_config_t config;

#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    const USART_Type* const usartBase[] = USART_BASE_PTRS;
    const IRQn_Type usartIRQ[] = USART_IRQS;

    usart_config_t config;
#endif
    tommRoC_hw_template_bus_uart_nxp_hal_config_t halConfig;

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_0_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
    static uint8_t txBuffer[__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_0_TEMPLATE_TX_BUFFER_SIZE_BYTE__];
    _uart_handle_0.txBufferPtr  = txBuffer;
    _uart_handle_0.txBufferSize = __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_0_TEMPLATE_TX_BUFFER_SIZE_BYTE__;
#endif

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    UART_GetDefaultConfig(&config);
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    USART_GetDefaultConfig(&config);
#endif

    config.baudRate_Bps     = _uart_config_0.baudRate;
#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    config.parityMode       = kUART_ParityDisabled;
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    config.parityMode       = kUSART_ParityDisabled;
#endif
    config.enableTx         = true;
    config.enableRx         = true;
#if defined (FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
    config.rxFifoWatermark  = FSL_FEATURE_UART_FIFO_SIZEn(usartBase[0]);
#elif defined (FSL_FEATURE_USART_HAS_FIFO) && FSL_FEATURE_USART_HAS_FIFO
    config.rxFifoWatermark  = FSL_FEATURE_USART_FIFO_SIZEn(usartBase[0]);
#endif

    halConfig.usartPtr      = (void*) usartBase[0];
    halConfig.configPtr     = (void*) &config;
#if defined (UART0_CLK_SRC)
    halConfig.clockName     = UART0_CLK_SRC;
#elif defined (USART0_CLK_SRC)
    halConfig.clockName     = USART0_CLK_SRC;
#else
    halConfig.clockName     = kCLOCK_BusClk;
#endif
    halConfig.rxTxIRQn      = usartIRQ[0];

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwTemplateBusUARTNXPLocationGet(
                    TOMMROC_HW_TEMPLATE_BUS_UART_0,
                    _uart_config_0.location,
                    &halConfig.location));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusUARTNXPHalInit(&halConfig));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwTemplateBusCommonUARTFIFOInit(
                    &_uart_config_0.buffer,
                    &_uart_handle_0.txUARTFifo,
                    &_uart_handle_0.rxUARTFifo));

    _EUSART0_get_callback_ARM(cbFunctPtr);

    tommRoCHwTemplateBusUARTNXPHalRxIRQEnable(halConfig.usartPtr);

    _uart_handle_0.usartPtr = halConfig.usartPtr;
    _uart_handle_0.rxTxIRQn = halConfig.rxTxIRQn;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    const UART_Type* const usartBase[] = UART_BASE_PTRS;
    const IRQn_Type usartIRQ[] = UART_RX_TX_IRQS;

    uart_config_t config;

#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    const USART_Type* const usartBase[] = USART_BASE_PTRS;
    const IRQn_Type usartIRQ[] = USART_IRQS;

    usart_config_t config;
#endif
    tommRoC_hw_template_bus_uart_nxp_hal_config_t halConfig;

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_1_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
    static uint8_t txBuffer[__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_1_TEMPLATE_TX_BUFFER_SIZE_BYTE__];
    _uart_handle_1.txBufferPtr  = txBuffer;
    _uart_handle_1.txBufferSize = __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_1_TEMPLATE_TX_BUFFER_SIZE_BYTE__;
#endif

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    UART_GetDefaultConfig(&config);
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    USART_GetDefaultConfig(&config);
#endif

    config.baudRate_Bps     = _uart_config_1.baudRate;
#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    config.parityMode       = kUART_ParityDisabled;
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    config.parityMode       = kUSART_ParityDisabled;
#endif
    config.enableTx         = true;
    config.enableRx         = true;
#if defined (FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
    config.rxFifoWatermark  = FSL_FEATURE_UART_FIFO_SIZEn(usartBase[1]);
#elif defined (FSL_FEATURE_USART_HAS_FIFO) && FSL_FEATURE_USART_HAS_FIFO
    config.rxFifoWatermark  = FSL_FEATURE_USART_FIFO_SIZEn(usartBase[1]);
#endif

    halConfig.usartPtr      = (void*) usartBase[1];
    halConfig.configPtr     = (void*) &config;
#if defined (UART1_CLK_SRC)
    halConfig.clockName     = UART1_CLK_SRC;
#elif defined (USART1_CLK_SRC)
    halConfig.clockName     = USART1_CLK_SRC;
#else
    halConfig.clockName     = kCLOCK_BusClk;
#endif
    halConfig.rxTxIRQn      = usartIRQ[1];

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwTemplateBusUARTNXPLocationGet(
                    TOMMROC_HW_TEMPLATE_BUS_UART_1,
                    _uart_config_1.location,
                    &halConfig.location));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusUARTNXPHalInit(&halConfig));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwTemplateBusCommonUARTFIFOInit(
                    &_uart_config_1.buffer,
                    &_uart_handle_1.txUARTFifo,
                    &_uart_handle_1.rxUARTFifo));

    _EUSART1_get_callback_ARM(cbFunctPtr);

    tommRoCHwTemplateBusUARTNXPHalRxIRQEnable(halConfig.usartPtr);

    _uart_handle_1.usartPtr = halConfig.usartPtr;
    _uart_handle_1.rxTxIRQn = halConfig.rxTxIRQn;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART2Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    const UART_Type* const usartBase[] = UART_BASE_PTRS;
    const IRQn_Type usartIRQ[] = UART_RX_TX_IRQS;

    uart_config_t config;

#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    const USART_Type* const usartBase[] = USART_BASE_PTRS;
    const IRQn_Type usartIRQ[] = USART_IRQS;

    usart_config_t config;
#endif
    tommRoC_hw_template_bus_uart_nxp_hal_config_t halConfig;

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_2_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
    static uint8_t txBuffer[__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_2_TEMPLATE_TX_BUFFER_SIZE_BYTE__];
    _uart_handle_2.txBufferPtr  = txBuffer;
    _uart_handle_2.txBufferSize = __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_2_TEMPLATE_TX_BUFFER_SIZE_BYTE__;
#endif

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    UART_GetDefaultConfig(&config);
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    USART_GetDefaultConfig(&config);
#endif

    config.baudRate_Bps     = _uart_config_2.baudRate;
#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    config.parityMode       = kUART_ParityDisabled;
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    config.parityMode       = kUSART_ParityDisabled;
#endif
    config.enableTx         = true;
    config.enableRx         = true;
#if defined (FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
    config.rxFifoWatermark  = FSL_FEATURE_UART_FIFO_SIZEn(usartBase[2]);
#elif defined (FSL_FEATURE_USART_HAS_FIFO) && FSL_FEATURE_USART_HAS_FIFO
    config.rxFifoWatermark  = FSL_FEATURE_USART_FIFO_SIZEn(usartBase[2]);
#endif

    halConfig.usartPtr      = (void*) usartBase[2];
    halConfig.configPtr     = (void*) &config;
#if defined (UART2_CLK_SRC)
    halConfig.clockName     = UART2_CLK_SRC;
#elif defined (USART2_CLK_SRC)
    halConfig.clockName     = USART2_CLK_SRC;
#else
    halConfig.clockName     = kCLOCK_BusClk;
#endif
    halConfig.rxTxIRQn      = usartIRQ[2];

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwTemplateBusUARTNXPLocationGet(
                    TOMMROC_HW_TEMPLATE_BUS_UART_2,
                    _uart_config_2.location,
                    &halConfig.location));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusUARTNXPHalInit(&halConfig));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwTemplateBusCommonUARTFIFOInit(
                    &_uart_config_2.buffer,
                    &_uart_handle_2.txUARTFifo,
                    &_uart_handle_2.rxUARTFifo));

    _EUSART2_get_callback_ARM(cbFunctPtr);

    tommRoCHwTemplateBusUARTNXPHalRxIRQEnable(halConfig.usartPtr);

    _uart_handle_2.usartPtr = halConfig.usartPtr;
    _uart_handle_2.rxTxIRQn = halConfig.rxTxIRQn;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_LEUART_0_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentLEUART0Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    const LPUART_Type* const lpuartBase[] = LPUART_BASE_PTRS;
    const IRQn_Type lpuartIRQ[] = LPUART_RX_TX_IRQS;

    lpuart_config_t config;
    tommRoC_hw_template_bus_uart_nxp_hal_config_t halConfig;

#if defined (__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_LEUART_0_TEMPLATE_TX_BUFFER_SIZE_BYTE__)
    static uint8_t txBuffer[__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_LEUART_0_TEMPLATE_TX_BUFFER_SIZE_BYTE__];
    _leuart_handle_0.txBufferPtr    = txBuffer;
    _leuart_handle_0.txBufferSize   = __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_LEUART_0_TEMPLATE_TX_BUFFER_SIZE_BYTE__;
#endif

    LPUART_GetDefaultConfig(&config);

    config.baudRate_Bps     = _leuart_config_0.baudRate;
    config.parityMode       = kLPUART_ParityDisabled;
    config.enableTx         = true;
    config.enableRx         = true;
#if defined (FSL_FEATURE_LPUART_HAS_FIFO) && FSL_FEATURE_LPUART_HAS_FIFO
    config.rxFifoWatermark  = FSL_FEATURE_LPUART_FIFO_SIZEn(LPUART0);
#endif

    halConfig.usartPtr      = (void*) lpuartBase[0];
    halConfig.configPtr     = (void*) &config;
#if defined (SYS_CLK)
    halConfig.clockName     = SYS_CLK;
#else
    halConfig.clockName     = kCLOCK_CoreSysClk;
#endif
    halConfig.rxTxIRQn      = lpuartIRQ[0];

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwTemplateBusUARTNXPLocationGet(
                    TOMMROC_HW_TEMPLATE_BUS_LEUART_0,
                    _leuart_config_0.location,
                    &halConfig.location));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwTemplateBusUARTNXPHalLEInit(&halConfig));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwTemplateBusCommonUARTFIFOInit(
                    &_leuart_config_0.buffer,
                    &_leuart_handle_0.txUARTFifo,
                    &_leuart_handle_0.rxUARTFifo));

    _LEUART0_get_callback_ARM(cbFunctPtr);

    tommRoCHwTemplateBusUARTNXPHalLERxIRQEnable((LPUART_Type*) halConfig.usartPtr);

    _leuart_handle_0.usartPtr   = halConfig.usartPtr;
    _leuart_handle_0.rxTxIRQn   = halConfig.rxTxIRQn;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif

#endif
