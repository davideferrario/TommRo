
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusUARTSw.h"

#include "bus/uart/sw/base/gpio/tommRoCHwTemplateBusUARTSwBaseGPIO.h"

#include "TOMMROC.h"
#include "TOMMROCHw.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "driver/timer.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __WAIT_FOR_RX_START_BIT_TIMEOUT_MSEC__          (2)
#define __WAIT_FOR_RX_STOP_BIT_TIMEOUT_MSEC__           (2)

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#define __TIMER_DIVIDER__   (2)                                     // Hardware timer clock divider
#define __TIMER_SCALE__     (TIMER_BASE_CLK / __TIMER_DIVIDER__)    // Convert counter value to seconds
#endif

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    tommRoC_hw_template_bus_uart_sw_base_gpio_t     baseGpio;

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
    bool                                            bitBangWithHwTimer;
    timer_idx_t                                     timerIdx;
    uint32_t                                        wrData;
    uint8_t                                         wrDataBitAmount;
    uint8_t                                         status; // 0 -> Start bit
    bool                                            txEnded;
#endif

} _tommRoC_hw_template_bus_uart_sw_t_;

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#define __EMPTY__tommRoC_hw_template_bus_uart_sw_t___                                   \
{                                                                                       \
    /* .baseGpio */             __EMPTY_tommRoC_hw_template_bus_uart_sw_base_gpio_t__,  \
    /* .bitBangWithHwTimer */   false,                                                  \
    /* .timerIdx */             TIMER_0,                                                \
    /* .wrData */               0,                                                      \
    /* .wrDataBitAmount */      0,                                                      \
    /* .status */               0,                                                      \
    /* .txEnded */              true,                                                   \
    }
#else
#define __EMPTY__tommRoC_hw_template_bus_uart_sw_t___                       \
{                                                                           \
    /* .baseGpio */ __EMPTY_tommRoC_hw_template_bus_uart_sw_base_gpio_t__,  \
}
#endif

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_UART_0_SW_TEMPLATE__)
static _tommRoC_hw_template_bus_uart_sw_t_ _uart_0_sw = TOMMROC_UTIL_EMPTY_VARIABLE(_tommRoC_hw_template_bus_uart_sw_t_);
#endif

#if defined (__TOMMROC_HW_USE_UART_1_SW_TEMPLATE__)
static _tommRoC_hw_template_bus_uart_sw_t_ _uart_1_sw = TOMMROC_UTIL_EMPTY_VARIABLE(_tommRoC_hw_template_bus_uart_sw_t_);
#endif

#if defined (__TOMMROC_HW_USE_UART_2_SW_TEMPLATE__)
static _tommRoC_hw_template_bus_uart_sw_t_ _uart_2_sw = TOMMROC_UTIL_EMPTY_VARIABLE(_tommRoC_hw_template_bus_uart_sw_t_);
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_SW_DEF_AT_LEAST_ONE_UART_SW_IS_USED__)
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
static void _isr_handler(_tommRoC_hw_template_bus_uart_sw_t_* const uartSwPtr) {

    if (0 == uartSwPtr->status) {
        // Start bit
        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(uartSwPtr->baseGpio.txLow());
    }
    // Begin with LSB
    else if (uartSwPtr->status - 1 < uartSwPtr->wrDataBitAmount) {
        if (TOMMRO_C_MATH_LOW_LEVEL == tommRoCMathBitTest(uartSwPtr->wrData, uartSwPtr->status - 1)) {
            TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(uartSwPtr->baseGpio.txLow());
        }
        else {
            TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(uartSwPtr->baseGpio.txHigh());
        }
    }
    else if (uartSwPtr->status - 1 == uartSwPtr->wrDataBitAmount) {
        // Stop bit
        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(uartSwPtr->baseGpio.txHigh());
    }
    else {
        timer_pause(TIMER_GROUP_1, uartSwPtr->timerIdx);
        uartSwPtr->txEnded = true;
    }

    ++uartSwPtr->status;
}

static void IRAM_ATTR timer_group_1_isr(void *para) {

    int timer_idx = (int) para;

    // Retrieve the interrupt status from the timer that reported the interrupt
    uint32_t intr_status = TIMERG1.int_st_timers.val;

    TIMERG1.hw_timer[timer_idx].update = 1;

    // Clear the interrupt
    if ((intr_status & BIT(timer_idx)) && timer_idx == TIMER_0) {
        TIMERG1.int_clr_timers.t0 = 1;
    }
    else if ((intr_status & BIT(timer_idx)) && timer_idx == TIMER_1) {
        TIMERG1.int_clr_timers.t1 = 1;
    }
    else {
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
    }

    // After the alarm has been triggered we need enable it again, so it is triggered the next time
    TIMERG1.hw_timer[timer_idx].config.alarm_en = TIMER_ALARM_EN;

    if (TIMER_0 == timer_idx) {
#if defined (__TOMMROC_HW_USE_UART_0_SW_TEMPLATE__)
        _isr_handler(&_uart_0_sw);
#endif
    }
    else if (TIMER_1 == timer_idx) {
#if defined (__TOMMROC_HW_USE_UART_1_SW_TEMPLATE__)
        _isr_handler(&_uart_1_sw);
#endif
    }
}
#endif

static tommRoC_hw_err_enum_t _wait_for_bit_status(
        const   tommRoC_hw_template_bus_uart_sw_base_gpio_t*    const   uartSwBaseGpioPtr,
        const   uint32_t                                                timeoutMs,
        const   tommRoC_util_bit_status_enum_t                          expectedBitStatus) {

    tommRoC_timer_t timer;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, timeoutMs));

    do {

        if (expectedBitStatus == uartSwBaseGpioPtr->rxStatus()) {
            return TOMMRO_C_HW_ERR_SUCCESS;
        }

    } while (TOMMRO_C_TIMER_NOT_EXPIRED_ERR == tommRoCTimerIsExpired(&timer));

    return TOMMRO_C_HW_LOW_LEVEL_ERR;
}

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
static void _uart_write_byte_bit_bang_with_hw_timer(
        const   uint32_t                                        data,
        const   uint8_t                                         dataBitAmount,
                _tommRoC_hw_template_bus_uart_sw_t_*    const   uartSwPtr) {

    uartSwPtr->wrData           = data;
    uartSwPtr->wrDataBitAmount  = dataBitAmount;
    uartSwPtr->status           = 0;
    uartSwPtr->txEnded          = false;

    // Start HW timer. Everything is handle by interrupt
    if (ESP_OK != timer_set_counter_value(TIMER_GROUP_1, uartSwPtr->timerIdx, 0)) {
        return;
    }

    if (ESP_OK != timer_start(TIMER_GROUP_1, uartSwPtr->timerIdx)) {
        return;
    }

    while (!uartSwPtr->txEnded) {
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(0));
    }
}
#endif

static void _uart_write_byte_bit_bang_with_delay(
        const   uint32_t                                        data,
        const   uint8_t                                         dataBitAmount,
                _tommRoC_hw_template_bus_uart_sw_t_*    const   uartSwPtr) {

    uint32_t criticalSpecificData;

    uint8_t idx;

    // Enter critical in order to get a clean transmit
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsEnterCritical(&criticalSpecificData));

    // Start bit
    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(uartSwPtr->baseGpio.txLow());
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayUsec(uartSwPtr->baseGpio.baseDelayUsec));

    // Begin with LSB
    for (idx = 0; idx < dataBitAmount; ++idx) {

        if (TOMMRO_C_MATH_LOW_LEVEL == tommRoCMathBitTest(data, idx)) {
            TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(uartSwPtr->baseGpio.txLow());
        }
        else {
            TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(uartSwPtr->baseGpio.txHigh());
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayUsec(uartSwPtr->baseGpio.baseDelayUsec));
    }

    // Stop bit
    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(uartSwPtr->baseGpio.txHigh());
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayUsec(uartSwPtr->baseGpio.baseDelayUsec));

    // Restore critical
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsExitCritical(&criticalSpecificData));
}

static void _uart_write_byte_bit_bang(
        const   uint32_t                                        data,
        const   uint8_t                                         dataBitAmount,
                _tommRoC_hw_template_bus_uart_sw_t_*    const   uartSwPtr) {

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
    if (uartSwPtr->bitBangWithHwTimer) {

        _uart_write_byte_bit_bang_with_hw_timer(
                data,
                dataBitAmount,
                uartSwPtr);

        return;
    }
#endif

    _uart_write_byte_bit_bang_with_delay(
            data,
            dataBitAmount,
            uartSwPtr);
}

static uint32_t _uart_read_byte_bit_bang(
        const   uint8_t                                                 dataBitAmount,
        const   tommRoC_hw_template_bus_uart_sw_base_gpio_t*    const   uartSwBaseGpioPtr) {

    tommRoC_util_bit_status_enum_t pinStatus[TOMMROC_UNIT_MEASURE_BYTE_TO_BIT(TOMMROC_UTIL_U32_SIZE)];
    uint32_t receivedData;
    uint8_t idx;

    // Wait for enter in start bit
    if (TOMMRO_C_HW_ERR_SUCCESS != _wait_for_bit_status(uartSwBaseGpioPtr, __WAIT_FOR_RX_START_BIT_TIMEOUT_MSEC__, TOMMRO_C_UTIL_LOW_LEVEL)) {
        return UINT32_MAX;
    }

    // NOTE: wait for (delay/2) to put in the middle of start bit. The delay into loop, put in the middle of first data bit
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayUsec(uartSwBaseGpioPtr->baseDelayUsec / 2));

    // Begin with LSB
    for (idx = 0; idx < dataBitAmount; ++idx) {

        // NOTE: in for loop just delay/read pin status (to have less computation -> maximum precision)
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayUsec(uartSwBaseGpioPtr->baseDelayUsec));

        pinStatus[idx] = uartSwBaseGpioPtr->rxStatus();
    }

    // NOTE: wait for (delay/2) to put in the end of last data bit/start of stop bit
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayUsec(uartSwBaseGpioPtr->baseDelayUsec / 2));

    // Wait for enter in stop bit
    if (TOMMRO_C_HW_ERR_SUCCESS != _wait_for_bit_status(uartSwBaseGpioPtr, __WAIT_FOR_RX_STOP_BIT_TIMEOUT_MSEC__, TOMMRO_C_UTIL_HIGH_LEVEL)) {
        return UINT32_MAX;
    }

    // NOTE: wait for (delay/2) to put in the end middle of stop bit
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayUsec(uartSwBaseGpioPtr->baseDelayUsec / 2));

    // NOTE: double check. In the middle of stop bit, check again pin status.
    if (TOMMRO_C_UTIL_LOW_LEVEL == uartSwBaseGpioPtr->rxStatus()) {
        return UINT32_MAX;
    }

    // Extract received data.
    for (receivedData = 0, idx = 0; idx < dataBitAmount; ++idx) {
        if (TOMMRO_C_UTIL_HIGH_LEVEL == pinStatus[idx]) {
            receivedData = tommRoCMathBitSet(receivedData, idx);
        }
    }

    return receivedData;
}

static tommRoC_hw_err_enum_t _uart_write_buffer_U32_bit_bang(
                _tommRoC_hw_template_bus_uart_sw_t_*    const   uartSwPtr,
        const   uint8_t*                                const   writeBufferPtr,
        const   uint16_t                                        writeBufferLen) {

    void* dataPtr;
    uint16_t counter;

    if (0 != (writeBufferLen % TOMMROC_UTIL_U32_SIZE)) {
        return TOMMRO_C_HW_PARAM_ERR;
    }

    for (dataPtr = (void*) writeBufferPtr, counter = 0; counter < writeBufferLen; dataPtr += TOMMROC_UTIL_U32_SIZE, counter += TOMMROC_UTIL_U32_SIZE) {

        _uart_write_byte_bit_bang(
                *(uint32_t*)dataPtr,
                uartSwPtr->baseGpio.dataBitAmount,
                uartSwPtr);
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _uart_write_buffer_U16_bit_bang(
                _tommRoC_hw_template_bus_uart_sw_t_*    const   uartSwPtr,
        const   uint8_t*                                const   writeBufferPtr,
        const   uint16_t                                        writeBufferLen) {

    void* dataPtr;
    uint16_t counter;

    if (0 != (writeBufferLen % TOMMROC_UTIL_U16_SIZE)) {
        return TOMMRO_C_HW_PARAM_ERR;
    }

    for (dataPtr = (void*) writeBufferPtr, counter = 0; counter < writeBufferLen; dataPtr += TOMMROC_UTIL_U16_SIZE, counter += TOMMROC_UTIL_U16_SIZE) {

        _uart_write_byte_bit_bang(
                *(uint16_t*)dataPtr,
                uartSwPtr->baseGpio.dataBitAmount,
                uartSwPtr);
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _uart_write_buffer_U8_bit_bang(
                _tommRoC_hw_template_bus_uart_sw_t_*    const   uartSwPtr,
        const   uint8_t*                                const   writeBufferPtr,
        const   uint16_t                                        writeBufferLen) {

    void* dataPtr;
    uint16_t counter;

    for (dataPtr = (void*) writeBufferPtr, counter = 0; counter < writeBufferLen; dataPtr += TOMMROC_UTIL_U8_SIZE, counter += TOMMROC_UTIL_U8_SIZE) {

        _uart_write_byte_bit_bang(
                *(uint8_t*)dataPtr,
                uartSwPtr->baseGpio.dataBitAmount,
                uartSwPtr);
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _uart_write_buffer_bit_bang(
                _tommRoC_hw_template_bus_uart_sw_t_*    const   uartSwPtr,
        const   uint8_t*                                const   writeBufferPtr,
        const   uint16_t                                        writeBufferLen) {

    if (uartSwPtr->baseGpio.dataBitAmount > TOMMROC_UNIT_MEASURE_BYTE_TO_BIT(TOMMROC_UTIL_U16_SIZE)) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _uart_write_buffer_U32_bit_bang(
                        uartSwPtr,
                        writeBufferPtr,
                        writeBufferLen));
    }
    else if (uartSwPtr->baseGpio.dataBitAmount > TOMMROC_UNIT_MEASURE_BYTE_TO_BIT(TOMMROC_UTIL_U8_SIZE)) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _uart_write_buffer_U16_bit_bang(
                        uartSwPtr,
                        writeBufferPtr,
                        writeBufferLen));
    }
    else {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _uart_write_buffer_U8_bit_bang(
                        uartSwPtr,
                        writeBufferPtr,
                        writeBufferLen));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _uart_read_buffer_U32_bit_bang(
        const   _tommRoC_hw_template_bus_uart_sw_t_*    const   uartSwPtr,
                uint8_t*                                const   readBufferPtr,
        const   uint16_t                                        toReadAmount,
                uint16_t*                               const   readedAmountPtr) {

    uint32_t* dataPtr;
    uint16_t counter;

    if (0 != (toReadAmount % TOMMROC_UTIL_U32_SIZE)) {
        return TOMMRO_C_HW_PARAM_ERR;
    }

    for (dataPtr = (uint32_t*) readBufferPtr, counter = 0; counter < toReadAmount; dataPtr += TOMMROC_UTIL_U32_SIZE, counter += TOMMROC_UTIL_U32_SIZE) {

        *dataPtr = _uart_read_byte_bit_bang(
                uartSwPtr->baseGpio.dataBitAmount,
                &uartSwPtr->baseGpio);
    }

    *readedAmountPtr = toReadAmount;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _uart_read_buffer_U16_bit_bang(
        const   _tommRoC_hw_template_bus_uart_sw_t_*    const   uartSwPtr,
                uint8_t*                                const   readBufferPtr,
        const   uint16_t                                        toReadAmount,
                uint16_t*                               const   readedAmountPtr) {

    uint16_t* dataPtr;
    uint16_t counter;

    if (0 != (toReadAmount % TOMMROC_UTIL_U16_SIZE)) {
        return TOMMRO_C_HW_PARAM_ERR;
    }

    for (dataPtr = (uint16_t*) readBufferPtr, counter = 0; counter < toReadAmount; dataPtr += TOMMROC_UTIL_U16_SIZE, counter += TOMMROC_UTIL_U16_SIZE) {

        *dataPtr = _uart_read_byte_bit_bang(
                uartSwPtr->baseGpio.dataBitAmount,
                &uartSwPtr->baseGpio);
    }

    *readedAmountPtr = toReadAmount;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _uart_read_buffer_U8_bit_bang(
        const   _tommRoC_hw_template_bus_uart_sw_t_*    const   uartSwPtr,
                uint8_t*                                const   readBufferPtr,
        const   uint16_t                                        toReadAmount,
                uint16_t*                               const   readedAmountPtr) {

    uint8_t* dataPtr;
    uint16_t counter;

    for (dataPtr = (uint8_t*) readBufferPtr, counter = 0; counter < toReadAmount; dataPtr += TOMMROC_UTIL_U8_SIZE, counter += TOMMROC_UTIL_U8_SIZE) {

        *dataPtr = _uart_read_byte_bit_bang(
                uartSwPtr->baseGpio.dataBitAmount,
                &uartSwPtr->baseGpio);
    }

    *readedAmountPtr = toReadAmount;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _uart_read_buffer_bit_bang(
        const   _tommRoC_hw_template_bus_uart_sw_t_*    const   uartSwPtr,
                uint8_t*                                const   readBufferPtr,
        const   uint16_t                                        toReadAmount,
                uint16_t*                               const   readedAmountPtr) {

    if (uartSwPtr->baseGpio.dataBitAmount > TOMMROC_UNIT_MEASURE_BYTE_TO_BIT(TOMMROC_UTIL_U16_SIZE)) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _uart_read_buffer_U32_bit_bang(
                        uartSwPtr,
                        readBufferPtr,
                        toReadAmount,
                        readedAmountPtr));
    }
    else if (uartSwPtr->baseGpio.dataBitAmount > TOMMROC_UNIT_MEASURE_BYTE_TO_BIT(TOMMROC_UTIL_U8_SIZE)) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _uart_read_buffer_U16_bit_bang(
                        uartSwPtr,
                        readBufferPtr,
                        toReadAmount,
                        readedAmountPtr));
    }
    else {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _uart_read_buffer_U8_bit_bang(
                        uartSwPtr,
                        readBufferPtr,
                        toReadAmount,
                        readedAmountPtr));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _uart_sw_write_buffers(
                _tommRoC_hw_template_bus_uart_sw_t_*    const   uartSwPtr,
        const   tommRoC_hw_bus_write_buf_t*             const   writeBuffersPtr,
        const   uint8_t                                         writeBuffersAmount,
        const   uint8_t*                                const   inputPtr,
                void*                                   const   resultPtr) {

    const tommRoC_hw_bus_write_buf_t* writeBufferPtr;
    uint8_t index;

    TOMMROC_UTIL_UNUSED_PARAM(inputPtr);
    TOMMROC_UTIL_UNUSED_PARAM(resultPtr);

    for (index = 0, writeBufferPtr = writeBuffersPtr; index < writeBuffersAmount; ++index, ++writeBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _uart_write_buffer_bit_bang(
                        uartSwPtr,
                        writeBufferPtr->bufferPtr,
                        writeBufferPtr->toWriteAmount));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _uart_sw_read_buffers(
        const   _tommRoC_hw_template_bus_uart_sw_t_*    const   uartSwPtr,
                tommRoC_hw_bus_read_buf_t*              const   readBuffersPtr,
        const   uint8_t                                         readBuffersAmount,
        const   uint8_t*                                const   inputPtr,
                void*                                   const   resultPtr) {

    tommRoC_hw_bus_read_buf_t* readBufferPtr;
    uint8_t index;

    TOMMROC_UTIL_UNUSED_PARAM(inputPtr);
    TOMMROC_UTIL_UNUSED_PARAM(resultPtr);

    for (index = 0, readBufferPtr = readBuffersPtr; index < readBuffersAmount; ++index, ++readBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _uart_read_buffer_bit_bang(
                        uartSwPtr,
                        readBufferPtr->bufferPtr,
                        readBufferPtr->toReadAmount,
                        readBufferPtr->readedAmountPtr));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static void _init_pins(
        const   tommRoC_hw_template_bus_uart_sw_init_t* const   swInitPtr) {

    swInitPtr->txHigh();
}

#if defined (__TOMMROC_HW_USE_UART_0_SW_TEMPLATE__)
static tommRoC_hw_err_enum_t _uart_0_sw_write_buffers(
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr) {

    return _uart_sw_write_buffers(
            &_uart_0_sw,
            writeBuffersPtr,
            writeBuffersAmount,
            inputPtr,
            resultPtr);
}
static tommRoC_hw_err_enum_t _uart_0_sw_read_buffers(
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr) {

    return _uart_sw_read_buffers(
            &_uart_0_sw,
            readBuffersPtr,
            readBuffersAmount,
            inputPtr,
            resultPtr);
}
static void _uart_0_sw_get_callback(
        const   tommRoC_hw_gpio_get_cb_t            rxStatus,
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwBusCbFunctReset(cbFunctPtr));

    cbFunctPtr->writeBuffers    = _uart_0_sw_write_buffers;

    if (NULL != rxStatus) {
        cbFunctPtr->readBuffers = _uart_0_sw_read_buffers;
    }
}
#endif

#if defined (__TOMMROC_HW_USE_UART_1_SW_TEMPLATE__)
static tommRoC_hw_err_enum_t _uart_1_sw_write_buffers(
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr) {

    return _uart_sw_write_buffers(
            &_uart_1_sw,
            writeBuffersPtr,
            writeBuffersAmount,
            inputPtr,
            resultPtr);
}
static tommRoC_hw_err_enum_t _uart_1_sw_read_buffers(
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr) {

    return _uart_sw_read_buffers(
            &_uart_1_sw,
            readBuffersPtr,
            readBuffersAmount,
            inputPtr,
            resultPtr);
}
static void _uart_1_sw_get_callback(
        const   tommRoC_hw_gpio_get_cb_t            rxStatus,
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwBusCbFunctReset(cbFunctPtr));

    cbFunctPtr->writeBuffers    = _uart_1_sw_write_buffers;

    if (NULL != rxStatus) {
        cbFunctPtr->readBuffers = _uart_1_sw_read_buffers;
    }
}
#endif

#if defined (__TOMMROC_HW_USE_UART_2_SW_TEMPLATE__)
static tommRoC_hw_err_enum_t _uart_2_sw_write_buffers(
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr) {

    return _uart_sw_write_buffers(
            &_uart_2_sw,
            writeBuffersPtr,
            writeBuffersAmount,
            inputPtr,
            resultPtr);
}
static tommRoC_hw_err_enum_t _uart_2_sw_read_buffers(
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr) {

    return _uart_sw_read_buffers(
            &_uart_2_sw,
            readBuffersPtr,
            readBuffersAmount,
            inputPtr,
            resultPtr);
}
static void _uart_2_sw_get_callback(
        const   tommRoC_hw_gpio_get_cb_t            rxStatus,
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwBusCbFunctReset(cbFunctPtr));

    cbFunctPtr->writeBuffers    = _uart_2_sw_write_buffers;

    if (NULL != rxStatus) {
        cbFunctPtr->readBuffers = _uart_2_sw_read_buffers;
    }
}
#endif

static tommRoC_hw_err_enum_t _ckeck_init_param(
        const   tommRoC_hw_template_bus_uart_sw_init_t* const   swInitPtr) {

    TOMMROC_ASSERT_NOT_NULL(swInitPtr);
    TOMMROC_ASSERT_NOT_NULL(swInitPtr->txHigh);
    TOMMROC_ASSERT_NOT_NULL(swInitPtr->txLow);
    TOMMROC_ASSERT_NOT_ZERO(swInitPtr->dataBitAmount);
    TOMMROC_ASSERT_LESS_OR_EQUALS_THAN(swInitPtr->dataBitAmount, TOMMROC_UNIT_MEASURE_BYTE_TO_BIT(TOMMROC_UTIL_U32_SIZE));
    TOMMROC_ASSERT_NOT_ZERO(swInitPtr->baudRateBPS);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(swInitPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(swInitPtr->txHigh);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(swInitPtr->txLow);
    TOMMROC_HW_PARAM_CHECK_ON_ZERO_RETURN_ERR(swInitPtr->dataBitAmount);
    TOMMROC_HW_PARAM_CHECK_ON_TEST_RETURN_ERR(swInitPtr->dataBitAmount, >, TOMMROC_UNIT_MEASURE_BYTE_TO_BIT(TOMMROC_UTIL_U32_SIZE));
    TOMMROC_HW_PARAM_CHECK_ON_ZERO_RETURN_ERR(swInitPtr->baudRateBPS);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static void _init_uart_sw_struct(
        const   tommRoC_hw_template_bus_uart_sw_init_t* const   swInitPtr,
                _tommRoC_hw_template_bus_uart_sw_t_*    const   uartSwPtr) {

    uartSwPtr->baseGpio.txHigh          = swInitPtr->txHigh;
    uartSwPtr->baseGpio.txLow           = swInitPtr->txLow;
    uartSwPtr->baseGpio.rxStatus        = swInitPtr->rxStatus;
    uartSwPtr->baseGpio.dataBitAmount   = swInitPtr->dataBitAmount;

    uartSwPtr->baseGpio.baseDelayUsec = TOMMROC_MATH_UINT_DIVIDE_APPROX((uint32_t) 1000000, swInitPtr->baudRateBPS);
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUART0SwStart(
        const   tommRoC_hw_template_bus_uart_sw_init_t* const   swInitPtr,
                tommRoC_hw_bus_t*                       const   busHandlePtr) {

#if defined (__TOMMROC_HW_USE_UART_0_SW_TEMPLATE__)

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
    static const timer_config_t timerConfig = {
            .alarm_en       = TIMER_ALARM_EN,
            .counter_en     = TIMER_PAUSE,
            .intr_type      = TIMER_INTR_LEVEL,
            .counter_dir    = TIMER_COUNT_UP,
            .auto_reload    = TIMER_AUTORELOAD_EN,
            .divider        = __TIMER_DIVIDER__,
    };
#endif

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_ckeck_init_param(swInitPtr));

    _init_pins(swInitPtr);

    _init_uart_sw_struct(swInitPtr, &_uart_0_sw);

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
    if (swInitPtr->useHwTimer) {

        if (ESP_OK != timer_init(TIMER_GROUP_1, TIMER_0, &timerConfig)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        // Timer's counter will initially start from value below.
        // Also, if auto_reload is set, this value will be automatically reload on alarm
        if (ESP_OK != timer_set_counter_value(TIMER_GROUP_1, TIMER_0, 0)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        // Configure the alarm value and the interrupt on alarm.
        if (ESP_OK != timer_set_alarm_value(TIMER_GROUP_1, TIMER_0, (uint64_t) __TIMER_SCALE__ * (uint64_t) _uart_0_sw.baseGpio.baseDelayUsec / (uint64_t) 1000000)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }
        if (ESP_OK != timer_enable_intr(TIMER_GROUP_1, TIMER_0)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }
        if (ESP_OK != timer_isr_register(TIMER_GROUP_1, TIMER_0, timer_group_1_isr, (void*) TIMER_0, ESP_INTR_FLAG_IRAM, NULL)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }
    }

    _uart_0_sw.bitBangWithHwTimer   = swInitPtr->useHwTimer;
    _uart_0_sw.timerIdx             = TIMER_0;
#endif

    _uart_0_sw_get_callback(swInitPtr->rxStatus, &cbFunct);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwBusInit(
                    TOMMRO_C_HW_BUS_UART_BUS_TYPE,
                    &cbFunct,
                    busHandlePtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(swInitPtr);
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUART1SwStart(
        const   tommRoC_hw_template_bus_uart_sw_init_t* const   swInitPtr,
                tommRoC_hw_bus_t*                       const   busHandlePtr) {

#if defined (__TOMMROC_HW_USE_UART_1_SW_TEMPLATE__)

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
    static const timer_config_t timerConfig = {
            .alarm_en       = TIMER_ALARM_EN,
            .counter_en     = TIMER_PAUSE,
            .intr_type      = TIMER_INTR_LEVEL,
            .counter_dir    = TIMER_COUNT_UP,
            .auto_reload    = TIMER_AUTORELOAD_EN,
            .divider        = __TIMER_DIVIDER__,
    };
#endif

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_ckeck_init_param(swInitPtr));

    _init_pins(swInitPtr);

    _init_uart_sw_struct(swInitPtr, &_uart_1_sw);

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
    if (swInitPtr->useHwTimer) {

        if (ESP_OK != timer_init(TIMER_GROUP_1, TIMER_1, &timerConfig)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        // Timer's counter will initially start from value below.
        // Also, if auto_reload is set, this value will be automatically reload on alarm
        if (ESP_OK != timer_set_counter_value(TIMER_GROUP_1, TIMER_1, 0)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        // Configure the alarm value and the interrupt on alarm.
        if (ESP_OK != timer_set_alarm_value(TIMER_GROUP_1, TIMER_1, (uint64_t) __TIMER_SCALE__ * (uint64_t) _uart_1_sw.baseGpio.baseDelayUsec / (uint64_t) 1000000)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }
        if (ESP_OK != timer_enable_intr(TIMER_GROUP_1, TIMER_1)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }
        if (ESP_OK != timer_isr_register(TIMER_GROUP_1, TIMER_1, timer_group_1_isr, (void*) TIMER_1, ESP_INTR_FLAG_IRAM, NULL)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }
    }

    _uart_1_sw.bitBangWithHwTimer   = swInitPtr->useHwTimer;
    _uart_1_sw.timerIdx             = TIMER_1;
#endif

    _uart_1_sw_get_callback(swInitPtr->rxStatus, &cbFunct);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwBusInit(
                    TOMMRO_C_HW_BUS_UART_BUS_TYPE,
                    &cbFunct,
                    busHandlePtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(swInitPtr);
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUART2SwStart(
        const   tommRoC_hw_template_bus_uart_sw_init_t* const   swInitPtr,
                tommRoC_hw_bus_t*                       const   busHandlePtr) {

#if defined (__TOMMROC_HW_USE_UART_2_SW_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_ckeck_init_param(swInitPtr));

    _init_pins(swInitPtr);

    _init_uart_sw_struct(swInitPtr, &_uart_2_sw);

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
    if (swInitPtr->useHwTimer) {
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
    }

    _uart_2_sw.bitBangWithHwTimer = false;
#endif

    _uart_2_sw_get_callback(swInitPtr->rxStatus, &cbFunct);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwBusInit(
                    TOMMRO_C_HW_BUS_UART_BUS_TYPE,
                    &cbFunct,
                    busHandlePtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(swInitPtr);
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}
