
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentUART.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_UART_IS_USED__)

#include "bus/common/uart/tommRoCHwTemplateBusCommonUARTFIFO.h"
#include "bus/common/uart/tommRoCHwTemplateBusCommonUARTFIFOCb.h"

#include "bus/env/arm/Nordic/uart/tommRoCHwTemplateBusUARTNordicHal.h"

#if (defined (UART_PRESENT) && UART_COUNT)
#include "nrfx_uart.h"
#endif

#include <stdbool.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __DEFAULT_BAUDRATE__            (NRF_UART_BAUDRATE_115200)
#define __DEFAULT_TXD_PIN_NUM__         (NRF_UART_PSEL_DISCONNECTED)
#define __DEFAULT_RXD_PIN_NUM__         (NRF_UART_PSEL_DISCONNECTED)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    tommRoC_hw_template_bus_uart_buffer_t   buffer;
    nrf_uart_baudrate_t                     baudRate;
    uint32_t                                pselTXD;
    uint32_t                                pselRXD;

} __tommRoC_hw_uart_config_t__;

#define __EMPTY___tommRoC_hw_uart_config_t____                              \
{                                                                           \
    /* .buffer */       __EMPTY_tommRoC_hw_template_bus_uart_buffer_t__,    \
    /* .baudRate */     __DEFAULT_BAUDRATE__,                               \
    /* .pselTXD */      __DEFAULT_TXD_PIN_NUM__,                            \
    /* .pselRXD */      __DEFAULT_RXD_PIN_NUM__,                            \
}

typedef struct {

    nrfx_uart_t                                 nrfxUart;
    uint8_t                                     txByte;
    uint8_t                                     rxByte;
    tommRoC_hw_template_bus_common_uart_fifo_t  txUARTFifo;
    tommRoC_hw_template_bus_common_uart_fifo_t  rxUARTFifo;
    bool                                        isTxInProgress;

} __tommRoC_hw_uart_handle_t__;

#define __EMPTY___tommRoC_hw_uart_handle_t____                                      \
{                                                                                   \
    /* .nrfxUart */         NRFX_UART_INSTANCE(0),                                  \
    /* .txByte */           0x00,                                                   \
    /* .rxByte */           0x00,                                                   \
    /* .txUARTFifo */       __EMPTY_tommRoC_hw_template_bus_common_uart_fifo_t__,   \
    /* .rxUARTFifo */       __EMPTY_tommRoC_hw_template_bus_common_uart_fifo_t__,   \
    /* .isTxInProgress */   false,                                                  \
}

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
static __tommRoC_hw_uart_config_t__ _uart_config_0 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_config_t__);
static __tommRoC_hw_uart_handle_t__ _uart_handle_0 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_handle_t__);
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if (defined (UART_PRESENT) && UART_COUNT)
static void _uart_rx_handle(
                __tommRoC_hw_uart_handle_t__*   const   uartHandlePtr,
                nrfx_uart_event_t               const*  p_event) {

    if (!uartHandlePtr->rxUARTFifo.fifoIsInit) {
        return;
    }

    // NOTE: don't use ASSERT_SUCCESS because can be possible that it return NOT_ENOUGH_RESOURCE
    tommRoCFIFOISRMultiPush(&uartHandlePtr->rxUARTFifo.fifo, p_event->data.rxtx.p_data, p_event->data.rxtx.bytes);
}

static void _uart_tx_handle(
                __tommRoC_hw_uart_handle_t__*   const   uartHandlePtr,
                nrfx_uart_event_t               const*  p_event) {

    TOMMROC_UTIL_UNUSED_PARAM(p_event);

    if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRPop(&uartHandlePtr->txUARTFifo.fifo, &uartHandlePtr->txByte)) {
        uartHandlePtr->isTxInProgress = false;
        return;
    }

    nrfx_uart_tx(&uartHandlePtr->nrfxUart, &uartHandlePtr->txByte, sizeof(uartHandlePtr->txByte));
}

static void _nrfx_uart_event_handler(
                __tommRoC_hw_uart_handle_t__*   const   uartHandlePtr,
                nrfx_uart_event_t               const*  p_event,
                void*                                   p_context) {

    TOMMROC_UTIL_UNUSED_PARAM(p_context);

    if (NRFX_UART_EVT_RX_DONE == p_event->type) {

        // Received bytes counter has to be checked, because there could be event from RXTO interrupt
        if (p_event->data.rxtx.bytes) {
            _uart_rx_handle(uartHandlePtr, p_event);
        }

        // Restart receiver
        nrfx_uart_rx(&uartHandlePtr->nrfxUart, &uartHandlePtr->rxByte, sizeof(uartHandlePtr->rxByte));
    }
    else if (NRFX_UART_EVT_ERROR == p_event->type) {
        // Restart receiver
        nrfx_uart_rx(&uartHandlePtr->nrfxUart, &uartHandlePtr->rxByte, sizeof(uartHandlePtr->rxByte));
    }
    else if (NRFX_UART_EVT_TX_DONE == p_event->type) {
        _uart_tx_handle(uartHandlePtr, p_event);
    }
}
#endif

/******************* Driver IRQ event Handler */

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
static void _nrfx_uart0_event_handler(
                nrfx_uart_event_t   const*  p_event,
                void*                       p_context) {

    _nrfx_uart_event_handler(&_uart_handle_0, p_event, p_context);
}
#endif


/******************* Common BUS functions */

#if (defined (UART_PRESENT) && UART_COUNT)
static tommRoC_hw_err_enum_t _uart_irq_write_buffer(
                __tommRoC_hw_uart_handle_t__*   const   uartHandlePtr,
        const   uint8_t*                        const   writeBufferPtr,
        const   uint16_t                                writeBufferLen) {

    tommRoC_fifo_ISR_t* txFifoPtr = &uartHandlePtr->txUARTFifo.fifo;

    // NOTE: ASSERT_SUCCESS is used because higher level function (tommRoCHwTemplateBusCommonUARTFIFOCbWriteBuffers) check for free space available
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCFIFOISRMultiPush(txFifoPtr, writeBufferPtr, writeBufferLen));

    // If uart TX already in progress
    if (nrfx_uart_tx_in_progress(&uartHandlePtr->nrfxUart)) {
        // Next transmission managed by interrupt
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    // If pop fails, it means that already tx in interrupt (maybe a thread switch context).
    if (TOMMRO_C_ERR_SUCCESS != tommRoCFIFOISRPop(txFifoPtr, &uartHandlePtr->txByte)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    uartHandlePtr->isTxInProgress = true;

    // Start interrupt transmission
    if (NRFX_SUCCESS != nrfx_uart_tx(&uartHandlePtr->nrfxUart, &uartHandlePtr->txByte, sizeof(uartHandlePtr->txByte))) {
        uartHandlePtr->isTxInProgress = false;
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif


/******************* BUS implementation functs */

#define __TOMMROC_HW_UART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(                                  \
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
        return tommRoCHwTemplateBusUARTNordicHalSetForLowPowerEnter(                                \
                uartConfig.pselTXD,                                                                 \
                uartConfig.pselRXD);                                                                \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _low_power_exit_ARM(                            \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusUARTNordicHalSetForLowPowerExit(                                 \
                uartConfig.pselTXD,                                                                 \
                uartConfig.pselRXD);                                                                \
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
    __TOMMROC_HW_UART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(UART0, TOMMROC_HW_TEMPLATE_BUS_UART_0, _uart_config_0, _uart_handle_0, _uart_irq_write_buffer);
#endif


/******************* BUS set prop functs */

static nrf_uart_baudrate_t _baudRate_convert(const uint32_t baudRateU32) {

    switch (baudRateU32) {

    case 1200UL:    return NRF_UART_BAUDRATE_1200;
    case 2400UL:    return NRF_UART_BAUDRATE_2400;
    case 4800UL:    return NRF_UART_BAUDRATE_4800;
    case 9600UL:    return NRF_UART_BAUDRATE_9600;
    case 14400UL:   return NRF_UART_BAUDRATE_14400;
    case 19200UL:   return NRF_UART_BAUDRATE_19200;
    case 28800UL:   return NRF_UART_BAUDRATE_28800;
    case 31250UL:   return NRF_UART_BAUDRATE_31250;
    case 38400UL:   return NRF_UART_BAUDRATE_38400;
    case 56000UL:   return NRF_UART_BAUDRATE_56000;
    case 57600UL:   return NRF_UART_BAUDRATE_57600;
    case 76800UL:   return NRF_UART_BAUDRATE_76800;
    case 115200UL:  return NRF_UART_BAUDRATE_115200;
    case 230400UL:  return NRF_UART_BAUDRATE_230400;
    case 250000UL:  return NRF_UART_BAUDRATE_250000;
    case 460800UL:  return NRF_UART_BAUDRATE_460800;
    case 921600UL:  return NRF_UART_BAUDRATE_921600;
    case 1000000UL: return NRF_UART_BAUDRATE_1000000;

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;

    }

    return __DEFAULT_BAUDRATE__;
}

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
        _uart_config_0.baudRate = _baudRate_convert(*propValuePtr);
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_psel_txd(
        const   tommRoC_hw_template_bus_uart_enum_t             bus,
        const   uint32_t*                               const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_0:
        _uart_config_0.pselTXD = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_psel_rxd(
        const   tommRoC_hw_template_bus_uart_enum_t             bus,
        const   uint32_t*                               const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_0:
        _uart_config_0.pselRXD = *propValuePtr;
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

    case TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_TX_PIN:
        return _set_psel_txd(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_RX_PIN:
        return _set_psel_rxd(bus, propValuePtr);

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

    tommRoC_hw_template_bus_uart_nordic_hal_config_t halConfig;

    halConfig.nrfxUart.p_reg        = NRF_UART0;
    halConfig.nrfxUart.drv_inst_idx = NRFX_UART0_INST_IDX;
    halConfig.baudRate              = _uart_config_0.baudRate;
    halConfig.pselTXD               = _uart_config_0.pselTXD;
    halConfig.pselRXD               = _uart_config_0.pselRXD;
    halConfig.nrfxUartEventHandler  = _nrfx_uart0_event_handler;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusUARTNordicHalInit(&halConfig));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwTemplateBusCommonUARTFIFOInit(
                    &_uart_config_0.buffer,
                    &_uart_handle_0.txUARTFifo,
                    &_uart_handle_0.rxUARTFifo));

    _UART0_get_callback_ARM(cbFunctPtr);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&_uart_handle_0.nrfxUart, &halConfig.nrfxUart, sizeof(nrfx_uart_t)));

    // If RX pin is connected, turn on receiver and start receives byte in non blocking mode
    if (NRF_UART_PSEL_DISCONNECTED != _uart_config_0.pselRXD) {

        // Turn ON receiver
        if (NRFX_SUCCESS != nrfx_uart_rx(&_uart_handle_0.nrfxUart, &_uart_handle_0.rxByte, sizeof(_uart_handle_0.rxByte))) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif

#endif
