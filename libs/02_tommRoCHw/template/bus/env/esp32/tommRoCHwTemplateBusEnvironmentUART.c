
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentUART.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_UART_IS_USED__)

#include "bus/env/esp32/uart/tommRoCHwTemplateBusUARTESP32Hal.h"

#if (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
#include "soc/gpio_num.h"
#endif

#include "driver/gpio.h"
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __DEFAULT_TX_BUFFER_SIZE__  (SOC_UART_FIFO_LEN * 2)
#define __DEFAULT_RX_BUFFER_SIZE__  (SOC_UART_FIFO_LEN * 2)
#define __DEFAULT_BAUDRATE__        (115200)
#define __DEFAULT_TX_IO_NUM__       (GPIO_NUM_NC)
#define __DEFAULT_RX_IO_NUM__       (GPIO_NUM_NC)

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
#define __SOURCE_CLK__              (UART_SCLK_APB)
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
#define __SOURCE_CLK__              (UART_SCLK_DEFAULT)
#endif

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    uint16_t    txBufferSize;
    uint16_t    rxBufferSize;
    uint32_t    baudRate;
    gpio_num_t  txGPIONum;
    gpio_num_t  rxGPIONum;

} __tommRoC_hw_uart_config_t__;

#define __EMPTY___tommRoC_hw_uart_config_t____      \
{                                                   \
    /* .txBufferSize */ __DEFAULT_TX_BUFFER_SIZE__, \
    /* .rxBufferSize */ __DEFAULT_RX_BUFFER_SIZE__, \
    /* .baudRate */     __DEFAULT_BAUDRATE__,       \
    /* .txGPIONum */    __DEFAULT_TX_IO_NUM__,      \
    /* .rxGPIONum */    __DEFAULT_RX_IO_NUM__,      \
}

typedef struct {

    uart_port_t uartPort;

} __tommRoC_hw_uart_handle_t__;

#define __EMPTY___tommRoC_hw_uart_handle_t____      \
{                                                   \
    /* .uartPort */     UART_NUM_MAX,               \
}

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

/*******************************************************************************
 * local functions
 ******************************************************************************/

/**
 * NOTE:
 * Starting from uart_read_bytes, define UART_GET_BYTES_FUNCTION_AVAILABLE and uart_get_bytes function into esp-idf framework - uart.h and uart.c files.
 *
int uart_read_bytes(uart_port_t uart_num, void* buf, uint32_t length, TickType_t ticks_to_wait);
#define UART_GET_BYTES_FUNCTION_AVAILABLE
int uart_get_bytes(uart_port_t uart_num, void* buf, uint32_t length, TickType_t ticks_to_wait);

int uart_get_bytes(uart_port_t uart_num, void *buf, uint32_t length, TickType_t ticks_to_wait)
{
    ESP_RETURN_ON_FALSE((uart_num < UART_NUM_MAX), (-1), UART_TAG, "uart_num error");
    ESP_RETURN_ON_FALSE((buf), (-1), UART_TAG, "uart data null");
    ESP_RETURN_ON_FALSE((p_uart_obj[uart_num]), (-1), UART_TAG, "uart driver error");
    uint8_t *data = NULL;
    size_t size;
    size_t copy_len = 0;
    int len_tmp;
    if (xSemaphoreTake(p_uart_obj[uart_num]->rx_mux, (portTickType)ticks_to_wait) != pdTRUE) {
        return -1;
    }
    while (length) {
        if (p_uart_obj[uart_num]->rx_cur_remain == 0) {
            data = (uint8_t *) xRingbufferReceive(p_uart_obj[uart_num]->rx_ring_buf, &size, (portTickType) ticks_to_wait);
            if (data) {
                p_uart_obj[uart_num]->rx_head_ptr = data;
                p_uart_obj[uart_num]->rx_ptr = data;
                p_uart_obj[uart_num]->rx_cur_remain = size;
            } else {
                //When using dual cores, `rx_buffer_full_flg` may read and write on different cores at same time,
                //which may lose synchronization. So we also need to call `uart_check_buf_full` once when ringbuffer is empty
                //to solve the possible asynchronous issues.
                if (uart_check_buf_full(uart_num)) {
                    //This condition will never be true if `uart_read_bytes`
                    //and `uart_rx_intr_handler_default` are scheduled on the same core.
                    continue;
                } else {
                    xSemaphoreGive(p_uart_obj[uart_num]->rx_mux);
                    return copy_len;
                }
            }
        }
        if (p_uart_obj[uart_num]->rx_cur_remain > length) {
            len_tmp = length;
        } else {
            len_tmp = p_uart_obj[uart_num]->rx_cur_remain;
        }
        memcpy((uint8_t *)buf + copy_len, p_uart_obj[uart_num]->rx_ptr, len_tmp);
        copy_len += len_tmp;
        length -= len_tmp;
    }

    xSemaphoreGive(p_uart_obj[uart_num]->rx_mux);
    return copy_len;
}
*/

static tommRoC_hw_err_enum_t _data_ready(
        const   uart_port_t                         uartPort,
                uint16_t*                   const   availableAmountPtr) {

    size_t size;

    if (ESP_OK != uart_get_buffered_data_len(uartPort, &size)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    *availableAmountPtr = (uint16_t) size;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _write_buffer(
        const   uart_port_t                         uartPort,
        const   uint8_t*                    const   writeBufferPtr,
        const   uint16_t                            writeBufferLen) {

    uint16_t toWriteAmount;
    uint8_t* ptr;
    int singleWriteAmount;

    ptr             = (uint8_t*) writeBufferPtr;
    toWriteAmount   = writeBufferLen;

    while (0 != toWriteAmount) {

        singleWriteAmount = uart_write_bytes(uartPort, (const char*) ptr, (size_t) toWriteAmount);

        if (singleWriteAmount < 0) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        toWriteAmount   -= (uint16_t) singleWriteAmount;
        ptr             += (uint16_t) singleWriteAmount;

        if (toWriteAmount > 0) {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1));
        }
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _write_buffers(
        const   uart_port_t                         uartPort,
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount) {

    const tommRoC_hw_bus_write_buf_t* writeBufferPtr;
    uint8_t index;

    for (index = 0, writeBufferPtr = writeBuffersPtr; index < writeBuffersAmount; ++index, ++writeBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _write_buffer(
                        uartPort,
                        writeBufferPtr->bufferPtr,
                        writeBufferPtr->toWriteAmount));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _read_buffer(
        const   uart_port_t                         uartPort,
                uint8_t*                    const   readBufferPtr,
        const   uint16_t                            toReadAmount,
                uint16_t*                   const   readedAmountPtr) {

    uint16_t availableAmount;
    uint16_t toRead;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_data_ready(uartPort, &availableAmount));

    toRead = tommRoCMathMin(toReadAmount, availableAmount);

    if (0 == toRead) {
        return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
    }

    // NOTE: wait for 2 msec
    if (uart_read_bytes(uartPort, readBufferPtr, toRead, 2 / portTICK_PERIOD_MS) < 0) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    *readedAmountPtr = toRead;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _read_buffers(
        const   uart_port_t                         uartPort,
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount) {

    tommRoC_hw_bus_read_buf_t* readBufferPtr;
    uint8_t index;

    for (index = 0, readBufferPtr = readBuffersPtr; index < readBuffersAmount; ++index, ++readBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _read_buffer(
                        uartPort,
                        readBufferPtr->bufferPtr,
                        readBufferPtr->toReadAmount,
                        readBufferPtr->readedAmountPtr));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

#if defined (UART_GET_BYTES_FUNCTION_AVAILABLE)
static tommRoC_hw_err_enum_t _get_buffer(
        const   uart_port_t                         uartPort,
                uint8_t*                    const   getBufferPtr,
        const   uint16_t                            toGetAmount,
                uint16_t*                   const   getAmountPtr) {

    uint16_t availableAmount;
    uint16_t toGet;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_data_ready(uartPort, &availableAmount));

    toGet = tommRoCMathMin(toGetAmount, availableAmount);

    if (0 == toGet) {
        return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
    }

    // NOTE: wait for 2 msec
    if (uart_get_bytes(uartPort, getBufferPtr, toGet, 2 / portTICK_PERIOD_MS) < 0) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    *getAmountPtr = toGet;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _get_buffers(
        const   uart_port_t                         uartPort,
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount) {

    tommRoC_hw_bus_read_buf_t* readBufferPtr;
    uint8_t index;

    for (index = 0, readBufferPtr = readBuffersPtr; index < readBuffersAmount; ++index, ++readBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _get_buffer(
                        uartPort,
                        readBufferPtr->bufferPtr,
                        readBufferPtr->toReadAmount,
                        readBufferPtr->readedAmountPtr));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

static tommRoC_hw_err_enum_t _clear_data(
        const   uart_port_t                         uartPort) {

    if (ESP_OK != uart_flush_input(uartPort)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    // NOTE: wait for 10 msec to complete
    if (ESP_OK != uart_wait_tx_done(uartPort, 10 / portTICK_PERIOD_MS)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

/******************* BUS implementation functs */

#if defined (UART_GET_BYTES_FUNCTION_AVAILABLE)
#define __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(                                 \
                uartPrefix,                                                                         \
                uart,                                                                               \
                uartConfig,                                                                         \
                uartHandle)                                                                         \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _data_ready_ESP32(                              \
                    uint16_t*   const   availableAmountPtr,                                         \
            const   void*       const   inputPtr,                                                   \
                    void*       const   resultPtr) {                                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _data_ready(                                                                         \
                uartHandle.uartPort,                                                                \
                availableAmountPtr);                                                                \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _write_buffers_ESP32(                           \
            const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,                            \
            const   uint8_t                             writeBuffersAmount,                         \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _write_buffers(                                                                      \
                uartHandle.uartPort,                                                                \
                writeBuffersPtr,                                                                    \
                writeBuffersAmount);                                                                \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _read_buffers_ESP32(                            \
                    tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,                             \
            const   uint8_t                             readBuffersAmount,                          \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _read_buffers(                                                                       \
                uartHandle.uartPort,                                                                \
                readBuffersPtr,                                                                     \
                readBuffersAmount);                                                                 \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _get_buffers_ESP32(                             \
                    tommRoC_hw_bus_read_buf_t*  const   getBuffersPtr,                              \
            const   uint8_t                             getBuffersAmount,                           \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _get_buffers(                                                                        \
                uartHandle.uartPort,                                                                \
                getBuffersPtr,                                                                      \
                getBuffersAmount);                                                                  \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _clear_data_ESP32(                              \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _clear_data(uartHandle.uartPort);                                                    \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _low_power_enter_ESP32(                         \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusUARTESP32HalSetForLowPowerEnter(                                 \
                uartHandle.uartPort,                                                                \
                uartConfig.txGPIONum,                                                               \
                uartConfig.rxGPIONum);                                                              \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _low_power_exit_ESP32(                          \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusUARTESP32HalSetForLowPowerExit(                                  \
                uartHandle.uartPort,                                                                \
                uartConfig.txGPIONum,                                                               \
                uartConfig.rxGPIONum);                                                              \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _set_prop_ESP32(                                \
            const   tommRoC_hw_bus_prop_enum_t          property,                                   \
            const   void*                       const   propValuePtr,                               \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusUARTESP32HalPropSet(                                             \
                uartHandle.uartPort,                                                                \
                property,                                                                           \
                propValuePtr);                                                                      \
    }                                                                                               \
                                                                                                    \
    static void _ ## uartPrefix ## _get_callback_ESP32(                                             \
                    tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {                               \
                                                                                                    \
        cbFunctPtr->dataReady       = _ ## uartPrefix ## _data_ready_ESP32;                         \
        cbFunctPtr->writeBuffers    = _ ## uartPrefix ## _write_buffers_ESP32;                      \
        cbFunctPtr->readBuffers     = _ ## uartPrefix ## _read_buffers_ESP32;                       \
        cbFunctPtr->getBuffers      = _ ## uartPrefix ## _get_buffers_ESP32;                        \
        cbFunctPtr->clearData       = _ ## uartPrefix ## _clear_data_ESP32;                         \
        cbFunctPtr->lowPowerEnter   = _ ## uartPrefix ## _low_power_enter_ESP32;                    \
        cbFunctPtr->lowPowerExit    = _ ## uartPrefix ## _low_power_exit_ESP32;                     \
        cbFunctPtr->setProp         = _ ## uartPrefix ## _set_prop_ESP32;                           \
    }

#else
#define __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(                                 \
                uartPrefix,                                                                         \
                uart,                                                                               \
                uartConfig,                                                                         \
                uartHandle)                                                                         \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _data_ready_ESP32(                              \
                    uint16_t*   const   availableAmountPtr,                                         \
            const   void*       const   inputPtr,                                                   \
                    void*       const   resultPtr) {                                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _data_ready(                                                                         \
                uartHandle.uartPort,                                                                \
                availableAmountPtr);                                                                \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _write_buffers_ESP32(                           \
            const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,                            \
            const   uint8_t                             writeBuffersAmount,                         \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _write_buffers(                                                                      \
                uartHandle.uartPort,                                                                \
                writeBuffersPtr,                                                                    \
                writeBuffersAmount);                                                                \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _read_buffers_ESP32(                            \
                    tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,                             \
            const   uint8_t                             readBuffersAmount,                          \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _read_buffers(                                                                       \
                uartHandle.uartPort,                                                                \
                readBuffersPtr,                                                                     \
                readBuffersAmount);                                                                 \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _clear_data_ESP32(                              \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _clear_data(uartHandle.uartPort);                                                    \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _low_power_enter_ESP32(                         \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusUARTESP32HalSetForLowPowerEnter(                                 \
                uartHandle.uartPort,                                                                \
                uartConfig.txGPIONum,                                                               \
                uartConfig.rxGPIONum);                                                              \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _low_power_exit_ESP32(                          \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusUARTESP32HalSetForLowPowerExit(                                  \
                uartHandle.uartPort,                                                                \
                uartConfig.txGPIONum,                                                               \
                uartConfig.rxGPIONum);                                                              \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _ ## uartPrefix ## _set_prop_ESP32(                                \
            const   tommRoC_hw_bus_prop_enum_t          property,                                   \
            const   void*                       const   propValuePtr,                               \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusUARTESP32HalPropSet(                                             \
                uartHandle.uartPort,                                                                \
                property,                                                                           \
                propValuePtr);                                                                      \
    }                                                                                               \
                                                                                                    \
    static void _ ## uartPrefix ## _get_callback_ESP32(                                             \
                    tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {                               \
                                                                                                    \
        cbFunctPtr->dataReady       = _ ## uartPrefix ## _data_ready_ESP32;                         \
        cbFunctPtr->writeBuffers    = _ ## uartPrefix ## _write_buffers_ESP32;                      \
        cbFunctPtr->readBuffers     = _ ## uartPrefix ## _read_buffers_ESP32;                       \
        cbFunctPtr->clearData       = _ ## uartPrefix ## _clear_data_ESP32;                         \
        cbFunctPtr->lowPowerEnter   = _ ## uartPrefix ## _low_power_enter_ESP32;                    \
        cbFunctPtr->lowPowerExit    = _ ## uartPrefix ## _low_power_exit_ESP32;                     \
        cbFunctPtr->setProp         = _ ## uartPrefix ## _set_prop_ESP32;                           \
    }
#endif


#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART0, TOMMROC_HW_TEMPLATE_BUS_UART_0, _uart_config_0, _uart_handle_0);
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART1, TOMMROC_HW_TEMPLATE_BUS_UART_1, _uart_config_1, _uart_handle_1);
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART2, TOMMROC_HW_TEMPLATE_BUS_UART_2, _uart_config_2, _uart_handle_2);
#endif


/******************* BUS set prop functs */

static tommRoC_hw_err_enum_t _set_tx_buffer_size(
        const   tommRoC_hw_template_bus_uart_enum_t             bus,
        const   uint16_t*                               const   propValuePtr) {

    /**
     * NOTE:
     * Tx_buffer_size should be multiple of uint32_t size AND should greater than SOC_UART_FIFO_LEN.
     */
    TOMMROC_ASSERT_ZERO(*propValuePtr % TOMMROC_UTIL_U32_SIZE);
    TOMMROC_ASSERT_MORE_OR_EQUALS_THAN(*propValuePtr, TOMMROC_HW_TEMPLATE_BUS_UART_ESP32_HAL_MINIMUM_BUFFER_SIZE);

    TOMMROC_HW_PARAM_CHECK_ON_NOT_ZERO_RETURN_ERR(*propValuePtr % TOMMROC_UTIL_U32_SIZE);
    TOMMROC_HW_PARAM_CHECK_ON_TEST_RETURN_ERR(*propValuePtr, <, TOMMROC_HW_TEMPLATE_BUS_UART_ESP32_HAL_MINIMUM_BUFFER_SIZE);

    switch (bus) {

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_0:
        _uart_config_0.txBufferSize = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_1:
        _uart_config_1.txBufferSize = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_2:
        _uart_config_2.txBufferSize = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_rx_buffer_size(
        const   tommRoC_hw_template_bus_uart_enum_t             bus,
        const   uint16_t*                               const   propValuePtr) {

    /**
     * NOTE:
     * Rx_buffer_size should be multiple of uint32_t size AND should greater than SOC_UART_FIFO_LEN.
     */
    TOMMROC_ASSERT_ZERO(*propValuePtr % TOMMROC_UTIL_U32_SIZE);
    TOMMROC_ASSERT_MORE_OR_EQUALS_THAN(*propValuePtr, TOMMROC_HW_TEMPLATE_BUS_UART_ESP32_HAL_MINIMUM_BUFFER_SIZE);

    TOMMROC_HW_PARAM_CHECK_ON_NOT_ZERO_RETURN_ERR(*propValuePtr % TOMMROC_UTIL_U32_SIZE);
    TOMMROC_HW_PARAM_CHECK_ON_TEST_RETURN_ERR(*propValuePtr, <, TOMMROC_HW_TEMPLATE_BUS_UART_ESP32_HAL_MINIMUM_BUFFER_SIZE);

    switch (bus) {

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_0:
        _uart_config_0.rxBufferSize = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_1:
        _uart_config_1.rxBufferSize = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_2:
        _uart_config_2.rxBufferSize = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
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

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_tx_pin(
        const   tommRoC_hw_template_bus_uart_enum_t             bus,
        const   gpio_num_t*                             const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_0:
        _uart_config_0.txGPIONum = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_1:
        _uart_config_1.txGPIONum = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_2:
        _uart_config_2.txGPIONum = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_rx_pin(
        const   tommRoC_hw_template_bus_uart_enum_t             bus,
        const   gpio_num_t*                             const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_0:
        _uart_config_0.rxGPIONum = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_1:
        _uart_config_1.rxGPIONum = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_2:
        _uart_config_2.rxGPIONum = *propValuePtr;
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

    case TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_TX_BUFFER_SIZE:
        return _set_tx_buffer_size(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_RX_BUFFER_SIZE:
        return _set_rx_buffer_size(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_BAUD_RATE:
        return _set_baudrate(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_TX_PIN:
        return _set_tx_pin(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_RX_PIN:
        return _set_rx_pin(bus, propValuePtr);

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

    tommRoC_hw_template_bus_uart_esp32_hal_config_t halConfig;

    halConfig.uartPort                          = UART_NUM_0;
    halConfig.uartConfig.baud_rate              = _uart_config_0.baudRate;
    halConfig.uartConfig.data_bits              = UART_DATA_8_BITS;
    halConfig.uartConfig.parity                 = UART_PARITY_DISABLE;
    halConfig.uartConfig.stop_bits              = UART_STOP_BITS_1;
    halConfig.uartConfig.flow_ctrl              = UART_HW_FLOWCTRL_DISABLE;
    halConfig.uartConfig.rx_flow_ctrl_thresh    = 0;
    halConfig.uartConfig.source_clk             = __SOURCE_CLK__;
    halConfig.txBufferSize                      = _uart_config_0.txBufferSize;
    halConfig.rxBufferSize                      = _uart_config_0.rxBufferSize;
    halConfig.txGPIONum                         = _uart_config_0.txGPIONum;
    halConfig.rxGPIONum                         = _uart_config_0.rxGPIONum;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusUARTESP32HalInit(&halConfig));

    _EUSART0_get_callback_ESP32(cbFunctPtr);

    _uart_handle_0.uartPort = halConfig.uartPort;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    tommRoC_hw_template_bus_uart_esp32_hal_config_t halConfig;

    halConfig.uartPort                          = UART_NUM_1;
    halConfig.uartConfig.baud_rate              = _uart_config_1.baudRate;
    halConfig.uartConfig.data_bits              = UART_DATA_8_BITS;
    halConfig.uartConfig.parity                 = UART_PARITY_DISABLE;
    halConfig.uartConfig.stop_bits              = UART_STOP_BITS_1;
    halConfig.uartConfig.flow_ctrl              = UART_HW_FLOWCTRL_DISABLE;
    halConfig.uartConfig.rx_flow_ctrl_thresh    = 0;
    halConfig.uartConfig.source_clk             = __SOURCE_CLK__;
    halConfig.txBufferSize                      = _uart_config_1.txBufferSize;
    halConfig.rxBufferSize                      = _uart_config_1.rxBufferSize;
    halConfig.txGPIONum                         = _uart_config_1.txGPIONum;
    halConfig.rxGPIONum                         = _uart_config_1.rxGPIONum;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusUARTESP32HalInit(&halConfig));

    _EUSART1_get_callback_ESP32(cbFunctPtr);

    _uart_handle_1.uartPort = halConfig.uartPort;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART2Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    tommRoC_hw_template_bus_uart_esp32_hal_config_t halConfig;

    halConfig.uartPort                          = UART_NUM_2;
    halConfig.uartConfig.baud_rate              = _uart_config_2.baudRate;
    halConfig.uartConfig.data_bits              = UART_DATA_8_BITS;
    halConfig.uartConfig.parity                 = UART_PARITY_DISABLE;
    halConfig.uartConfig.stop_bits              = UART_STOP_BITS_1;
    halConfig.uartConfig.flow_ctrl              = UART_HW_FLOWCTRL_DISABLE;
    halConfig.uartConfig.rx_flow_ctrl_thresh    = 0;
    halConfig.uartConfig.source_clk             = __SOURCE_CLK__;
    halConfig.txBufferSize                      = _uart_config_2.txBufferSize;
    halConfig.rxBufferSize                      = _uart_config_2.rxBufferSize;
    halConfig.txGPIONum                         = _uart_config_2.txGPIONum;
    halConfig.rxGPIONum                         = _uart_config_2.rxGPIONum;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusUARTESP32HalInit(&halConfig));

    _EUSART2_get_callback_ESP32(cbFunctPtr);

    _uart_handle_2.uartPort = halConfig.uartPort;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif
