
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentUART.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)

#include "TOMMROC.h"

#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_UART_IS_USED__)

#include "bus/common/uart/tommRoCHwTemplateBusCommonUARTFIFO.h"
#include "bus/common/uart/tommRoCHwTemplateBusCommonUARTFIFOCb.h"

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <sys/ioctl.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __AVAILABLE_RES_HARDWARE_AMOUNT__           (5)

#define __UART_0_INDEX__                            (0)
#define __UART_1_INDEX__                            (1)
#define __UART_2_INDEX__                            (2)
#define __UART_3_INDEX__                            (3)
#define __UART_4_INDEX__                            (4)

#define __NOT_VALID_HANDLE__                        (-1)

#define __UART_DEFAULT_BAUDRAUTE__                  (115200)

#define __SUCCESS_RESULT__                          (0)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    tommRoC_hw_template_bus_uart_buffer_t   buffer;
    uint32_t                                baudRate;
    char*                                   deviceNameStrPtr;

} __tommRoC_hw_uart_config_t__;

#define __EMPTY___tommRoC_hw_uart_config_t____                                  \
{                                                                               \
    /* .buffer */           __EMPTY_tommRoC_hw_template_bus_uart_buffer_t__,    \
    /* .baudRate */         __UART_DEFAULT_BAUDRAUTE__,                         \
    /* .deviceNameStrPtr */ NULL,                                               \
}

typedef struct {

    tommRoC_hw_template_bus_common_uart_fifo_t  txUARTFifo;
    tommRoC_hw_template_bus_common_uart_fifo_t  rxUARTFifo;

} __tommRoC_hw_uart_handle_t__;

#define __EMPTY___tommRoC_hw_uart_handle_t____                                  \
{                                                                               \
    /* .txUARTFifo */   __EMPTY_tommRoC_hw_template_bus_common_uart_fifo_t__,   \
    /* .rxUARTFifo */   __EMPTY_tommRoC_hw_template_bus_common_uart_fifo_t__,   \
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

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
static __tommRoC_hw_uart_config_t__ _uart_config_3 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_config_t__);
static __tommRoC_hw_uart_handle_t__ _uart_handle_3 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
static __tommRoC_hw_uart_config_t__ _uart_config_4 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_config_t__);
static __tommRoC_hw_uart_handle_t__ _uart_handle_4 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_uart_handle_t__);
#endif

static int _hw_handle[__AVAILABLE_RES_HARDWARE_AMOUNT__] = {
        __NOT_VALID_HANDLE__,
        __NOT_VALID_HANDLE__,
        __NOT_VALID_HANDLE__,
        __NOT_VALID_HANDLE__,
        __NOT_VALID_HANDLE__,
};

/*******************************************************************************
 * local functions
 ******************************************************************************/

/******************* Low level functions */

static tommRoC_hw_err_enum_t _convert_baudrate_format(
        const   uint32_t            baudRate,
                int*        const   convertedSpeedPtr) {

    TOMMROC_ASSERT_NOT_NULL(convertedSpeedPtr);

    switch (baudRate) {

    case     50: *convertedSpeedPtr =     B50; break;
    case     75: *convertedSpeedPtr =     B75; break;
    case    110: *convertedSpeedPtr =    B110; break;
    case    134: *convertedSpeedPtr =    B134; break;
    case    150: *convertedSpeedPtr =    B150; break;
    case    200: *convertedSpeedPtr =    B200; break;
    case    300: *convertedSpeedPtr =    B300; break;
    case    600: *convertedSpeedPtr =    B600; break;
    case   1200: *convertedSpeedPtr =   B1200; break;
    case   1800: *convertedSpeedPtr =   B1800; break;
    case   2400: *convertedSpeedPtr =   B2400; break;
    case   4800: *convertedSpeedPtr =   B4800; break;
    case   9600: *convertedSpeedPtr =   B9600; break;
    case  19200: *convertedSpeedPtr =  B19200; break;
    case  38400: *convertedSpeedPtr =  B38400; break;
    case  57600: *convertedSpeedPtr =  B57600; break;
    case 115200: *convertedSpeedPtr = B115200; break;
    case 230400: *convertedSpeedPtr = B230400; break;
    case 460800: *convertedSpeedPtr = B460800; break;

    default:
        return TOMMRO_C_HW_LOW_LEVEL_ERR;

    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _open_hw(
        const   uint8_t                                 hwResIndex,
        const   __tommRoC_hw_uart_config_t__*   const   configPtr) {

    int handle;
    struct termios serialPortSettings;
    int convertedSpeed;

    TOMMROC_ASSERT_LESS_THAN(hwResIndex, __AVAILABLE_RES_HARDWARE_AMOUNT__);

    // Convert baudrate
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_convert_baudrate_format(configPtr->baudRate, &convertedSpeed));

    // Open in blocking mode; read will wait
    handle = open(configPtr->deviceNameStrPtr, O_RDWR | O_NOCTTY);  // O_RDWR - Read/Write access to serial port
                                                                    // O_NOCTTY - No terminal will control the process

    TOMMROC_ASSERT_NOT_EQUALS(handle, __NOT_VALID_HANDLE__);

    if (__NOT_VALID_HANDLE__ == handle) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    // Get the current settings of the serial port
    if (__SUCCESS_RESULT__ != tcgetattr(handle, &serialPortSettings)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    cfmakeraw(&serialPortSettings);

    if (__SUCCESS_RESULT__ != cfsetispeed(&serialPortSettings, convertedSpeed)) {   // Baudrate
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (__SUCCESS_RESULT__ != cfsetospeed(&serialPortSettings, convertedSpeed)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    serialPortSettings.c_cflag &= ~PARENB;                                          // No Parity
    serialPortSettings.c_cflag &= ~CSTOPB;                                          // Stop bits = 1
    serialPortSettings.c_cflag &= ~CSIZE;                                           // Clears the Mask
    serialPortSettings.c_cflag |= CS8;                                              // Set the data bits = 8
    serialPortSettings.c_cflag |= CREAD | CLOCAL;                                   // Enable receiver
    serialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);                          // Disable XON/XOFF flow control both i/p and o/p
    serialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);                  // Non Cannonical mode
    serialPortSettings.c_oflag &= ~OPOST;                                           // No Output Processing
                                                              
    // Setting timeouts - fetch bytes as they become available
    serialPortSettings.c_cc[VMIN]  = 0;     // Read at least 0 characters before returning
    serialPortSettings.c_cc[VTIME] = 1;     // Wait (1 * 100) msec for reading
    
    // Discards old data in the rx buffer
    if (__SUCCESS_RESULT__ != tcflush(handle, TCIFLUSH)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    // Set current setting
    if (__SUCCESS_RESULT__ != tcsetattr(handle, TCSANOW, &serialPortSettings)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    _hw_handle[hwResIndex] = handle;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

/******************* Common BUS functions */

static tommRoC_hw_err_enum_t _update_rx_fifo(
        const   uint8_t                                             hwResIndex,
                tommRoC_hw_template_bus_common_uart_fifo_t* const   rxUARTFifoPtr) {

    int handle;
    int availableBytes;
    int idx;

    uint8_t dataByte;

    TOMMROC_ASSERT_LESS_THAN(hwResIndex, __AVAILABLE_RES_HARDWARE_AMOUNT__);

    handle = _hw_handle[hwResIndex];

    TOMMROC_ASSERT_NOT_EQUALS(handle, __NOT_VALID_HANDLE__);

    if (__NOT_VALID_HANDLE__ == handle) {
        return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
    }

    if (ioctl(handle, FIONREAD, &availableBytes) < __SUCCESS_RESULT__) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    for (idx = 0; idx < availableBytes; ++idx) {

        if (TOMMROC_UTIL_U8_SIZE != read(handle, &dataByte, TOMMROC_UTIL_U8_SIZE)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        // NOTE: don't use ASSERT_SUCCESS because can be possible that it return NOT_ENOUGH_RESOURCE
        tommRoCFIFOISRPush(&rxUARTFifoPtr->fifo, dataByte);
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _hw_write_buffer(
        const   uint8_t             hwResIndex,
        const   uint8_t*    const   writeBufferPtr,
        const   uint16_t            writeBufferLen) {

    int handle;
    int written;
    int writtenBytes;

    TOMMROC_ASSERT_LESS_THAN(hwResIndex, __AVAILABLE_RES_HARDWARE_AMOUNT__);

    handle = _hw_handle[hwResIndex];

    TOMMROC_ASSERT_NOT_EQUALS(handle, __NOT_VALID_HANDLE__);

    if (__NOT_VALID_HANDLE__ == handle) {
        return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
    }
    
    written = 0;
    writtenBytes = 0;

    while ((written != (int) writeBufferLen) && (writtenBytes >= 0)) {

        writtenBytes = write(handle, writeBufferPtr + written, writeBufferLen - written);

        if (writtenBytes < __SUCCESS_RESULT__) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        written += writtenBytes;

        if (written != writeBufferLen) {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(10));
        }
    }
    
    TOMMROC_ASSERT_EQUALS(writeBufferLen, writtenBytes);

    if (writeBufferLen != (uint16_t) writtenBytes) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _common_data_ready(
        const   uint8_t                                             hwResIndex,
                tommRoC_hw_template_bus_common_uart_fifo_t* const   rxUARTFifoPtr,
                uint16_t*                                   const   availableAmountPtr) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _update_rx_fifo(
                    hwResIndex,
                    rxUARTFifoPtr));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusCommonUARTFIFOCbDataAmount(
                    rxUARTFifoPtr,
                    availableAmountPtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _common_write_buffers(
        const   uint8_t                             hwResIndex,
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount) {

    const tommRoC_hw_bus_write_buf_t* writeBufferPtr;
    uint8_t index;

    for (index = 0, writeBufferPtr = writeBuffersPtr; index < writeBuffersAmount; ++index, ++writeBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _hw_write_buffer(
                        hwResIndex,
                        writeBufferPtr->bufferPtr,
                        writeBufferPtr->toWriteAmount));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _common_read_buffers(
        const   uint8_t                                             hwResIndex,
                tommRoC_hw_template_bus_common_uart_fifo_t* const   rxUARTFifoPtr,
                tommRoC_hw_bus_read_buf_t*                  const   readBuffersPtr,
        const   uint8_t                                             readBuffersAmount) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _update_rx_fifo(
                    hwResIndex,
                    rxUARTFifoPtr));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusCommonUARTFIFOCbReadBuffers(
                    rxUARTFifoPtr,
                    readBuffersPtr,
                    readBuffersAmount));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _common_get_buffers(
        const   uint8_t                                             hwResIndex,
                tommRoC_hw_template_bus_common_uart_fifo_t* const   rxUARTFifoPtr,
                tommRoC_hw_bus_read_buf_t*                  const   getBuffersPtr,
        const   uint8_t                                             getBuffersAmount) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _update_rx_fifo(
                    hwResIndex,
                    rxUARTFifoPtr));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusCommonUARTFIFOCbGetBuffers(
                    rxUARTFifoPtr,
                    getBuffersPtr,
                    getBuffersAmount));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _common_clear_received_data(
        const   uint8_t                                             hwResIndex,
                tommRoC_hw_template_bus_common_uart_fifo_t* const   rxUARTFifoPtr) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _update_rx_fifo(
                    hwResIndex,
                    rxUARTFifoPtr));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusCommonUARTFIFOCbClearSingleData(
                    rxUARTFifoPtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _common_clear_data(
        const   uint8_t                                             hwResIndex,
                tommRoC_hw_template_bus_common_uart_fifo_t* const   rxUARTFifoPtr) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_common_clear_received_data(hwResIndex, rxUARTFifoPtr));
    return TOMMRO_C_HW_ERR_SUCCESS;
}


/******************* BUS implementation functs */

#define __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(hwResIndex, uartHandle)                  \
                                                                                                            \
    static tommRoC_hw_err_enum_t _uart ## hwResIndex ## _data_ready_Linux(                                  \
                    uint16_t*   const   availableAmountPtr,                                                 \
            const   void*       const   inputPtr,                                                           \
                    void*       const   resultPtr) {                                                        \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        return  _common_data_ready(hwResIndex, &uartHandle.rxUARTFifo, availableAmountPtr);                 \
    }                                                                                                       \
                                                                                                            \
    static tommRoC_hw_err_enum_t _uart ## hwResIndex ## _write_buffers_Linux(                               \
            const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,                                    \
            const   uint8_t                             writeBuffersAmount,                                 \
            const   void*                       const   inputPtr,                                           \
                    void*                       const   resultPtr) {                                        \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        return _common_write_buffers(hwResIndex, writeBuffersPtr, writeBuffersAmount);                      \
    }                                                                                                       \
                                                                                                            \
    static tommRoC_hw_err_enum_t _uart ## hwResIndex ## _read_buffers_Linux(                                \
                    tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,                                     \
            const   uint8_t                             readBuffersAmount,                                  \
            const   void*                       const   inputPtr,                                           \
                    void*                       const   resultPtr) {                                        \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        return _common_read_buffers(hwResIndex, &uartHandle.rxUARTFifo, readBuffersPtr, readBuffersAmount); \
    }                                                                                                       \
                                                                                                            \
    static tommRoC_hw_err_enum_t _uart ## hwResIndex ## _get_buffers_Linux(                                 \
                    tommRoC_hw_bus_read_buf_t*  const   getBuffersPtr,                                      \
            const   uint8_t                             getBuffersAmount,                                   \
            const   void*                       const   inputPtr,                                           \
                    void*                       const   resultPtr) {                                        \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        return _common_get_buffers(hwResIndex, &uartHandle.rxUARTFifo, getBuffersPtr, getBuffersAmount);    \
    }                                                                                                       \
                                                                                                            \
    static tommRoC_hw_err_enum_t _uart ## hwResIndex ## _clear_data_Linux(                                  \
            const   void*                       const   inputPtr,                                           \
                    void*                       const   resultPtr) {                                        \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        return _common_clear_data(hwResIndex, &uartHandle.rxUARTFifo);                                      \
    }                                                                                                       \
                                                                                                            \
    static tommRoC_hw_err_enum_t _uart ## hwResIndex ## _clear_to_send_data_Linux(                          \
            const   void*                       const   inputPtr,                                           \
                    void*                       const   resultPtr) {                                        \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        return TOMMRO_C_HW_ERR_SUCCESS;                                                                     \
    }                                                                                                       \
                                                                                                            \
    static tommRoC_hw_err_enum_t _uart ## hwResIndex ## _clear_received_data_Linux(                         \
            const   void*                       const   inputPtr,                                           \
                    void*                       const   resultPtr) {                                        \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        return _common_clear_received_data(hwResIndex, &uartHandle.rxUARTFifo);                             \
    }                                                                                                       \
                                                                                                            \
    static tommRoC_hw_err_enum_t _uart ## hwResIndex ## _low_power_enter_Linux(                             \
            const   void*                       const   inputPtr,                                           \
                    void*                       const   resultPtr) {                                        \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        return TOMMRO_C_HW_ERR_SUCCESS;                                                                     \
    }                                                                                                       \
                                                                                                            \
    static tommRoC_hw_err_enum_t _uart ## hwResIndex ## _low_power_exit_Linux(                              \
            const   void*                       const   inputPtr,                                           \
                    void*                       const   resultPtr) {                                        \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        return TOMMRO_C_HW_ERR_SUCCESS;                                                                     \
    }                                                                                                       \
                                                                                                            \
    static void _uart ## hwResIndex ## _get_callback_Linux(                                                 \
                    tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {                                       \
                                                                                                            \
        cbFunctPtr->dataReady           = _uart ## hwResIndex ## _data_ready_Linux;                         \
        cbFunctPtr->writeBuffers        = _uart ## hwResIndex ## _write_buffers_Linux;                      \
        cbFunctPtr->readBuffers         = _uart ## hwResIndex ## _read_buffers_Linux;                       \
        cbFunctPtr->getBuffers          = _uart ## hwResIndex ## _get_buffers_Linux;                        \
        cbFunctPtr->clearData           = _uart ## hwResIndex ## _clear_data_Linux;                         \
        cbFunctPtr->clearToSendData     = _uart ## hwResIndex ## _clear_to_send_data_Linux;                 \
        cbFunctPtr->clearReceivedData   = _uart ## hwResIndex ## _clear_received_data_Linux;                \
        cbFunctPtr->lowPowerEnter       = _uart ## hwResIndex ## _low_power_enter_Linux;                    \
        cbFunctPtr->lowPowerExit        = _uart ## hwResIndex ## _low_power_exit_Linux;                     \
    }

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(__UART_0_INDEX__, _uart_handle_0);
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(__UART_1_INDEX__, _uart_handle_1);
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(__UART_2_INDEX__, _uart_handle_2);
#endif

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(__UART_3_INDEX__, _uart_handle_3);
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
    __TOMMROC_HW_USART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(__UART_4_INDEX__, _uart_handle_4);
#endif


#define __TOMMROC_HW_TEMPLATE_BUS_UART_START_LINUX__(hwResIndex, uartHandle, cbFunctPtr, uartConfig)            \
                                                                                                                \
        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(                                       \
                tommRoCHwTemplateBusCommonUARTFIFOInit(                                                         \
                        &uartConfig.buffer,                                                                     \
                        &uartHandle.txUARTFifo,                                                                 \
                        &uartHandle.rxUARTFifo));                                                               \
                                                                                                                \
        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_open_hw(hwResIndex, &uartConfig));    \
                                                                                                                \
        _uart ## hwResIndex ## _get_callback_Linux(cbFunctPtr);                                                 \
                                                                                                                \
        return TOMMRO_C_HW_ERR_SUCCESS;


static tommRoC_hw_err_enum_t _check_device_name_string(
        const   char*   const   deviceNameStrPtr) {

    if (TOMMRO_C_ERR_SUCCESS == tommRoCStringStartWith(deviceNameStrPtr, "/dev/tty")) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    if (TOMMRO_C_ERR_SUCCESS == tommRoCStringStartWith(deviceNameStrPtr, "/dev/serial")) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    return TOMMRO_C_HW_PARAM_ERR;
}


/******************* BUS set prop functs */

static tommRoC_hw_err_enum_t _set_buffer_specific(
        const   tommRoC_hw_template_bus_uart_buffer_t*  const   propValuePtr,
                tommRoC_hw_template_bus_uart_buffer_t*  const   uartBufferPtr) {

    const tommRoC_hw_template_bus_uart_buffer_t empty = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_hw_template_bus_uart_buffer_t);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopySafe(uartBufferPtr, sizeof(tommRoC_hw_template_bus_uart_buffer_t), &empty, sizeof(tommRoC_hw_template_bus_uart_buffer_t), sizeof(empty)));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopySafe(uartBufferPtr, sizeof(tommRoC_hw_template_bus_uart_buffer_t), propValuePtr, sizeof(tommRoC_hw_template_bus_uart_buffer_t), sizeof(tommRoC_hw_template_bus_uart_buffer_t)));

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

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_3:
        return _set_buffer_specific(propValuePtr, &_uart_config_3.buffer);
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_4:
        return _set_buffer_specific(propValuePtr, &_uart_config_4.buffer);
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_bus_uart_baud_rate(
        const   tommRoC_hw_template_bus_uart_enum_t         bus,
        const   uint32_t*                           const   propValuePtr) {

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

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_3:
        _uart_config_3.baudRate = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_4:
        _uart_config_4.baudRate = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_bus_uart_device_name_string(
        const   tommRoC_hw_template_bus_uart_enum_t         bus,
        const   char*                               const   propValuePtr) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _check_device_name_string(propValuePtr));

    switch (bus) {

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_0:
        _uart_config_0.deviceNameStrPtr = (char*) propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_1:
        _uart_config_1.deviceNameStrPtr = (char*) propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_2:
        _uart_config_2.deviceNameStrPtr = (char*) propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_3:
        _uart_config_3.deviceNameStrPtr = (char*) propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_4:
        _uart_config_4.deviceNameStrPtr = (char*) propValuePtr;
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
        return _set_bus_uart_baud_rate(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_DEVICE_NAME_STRING:
        return _set_bus_uart_device_name_string(bus, propValuePtr);

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

    __TOMMROC_HW_TEMPLATE_BUS_UART_START_LINUX__(__UART_0_INDEX__, _uart_handle_0, cbFunctPtr, _uart_config_0);
}
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_UART_START_LINUX__(__UART_1_INDEX__, _uart_handle_1, cbFunctPtr, _uart_config_1);
}
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART2Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_UART_START_LINUX__(__UART_2_INDEX__, _uart_handle_2, cbFunctPtr, _uart_config_2);
}
#endif

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART3Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_UART_START_LINUX__(__UART_3_INDEX__, _uart_handle_3, cbFunctPtr, _uart_config_3);
}
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART4Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_UART_START_LINUX__(__UART_4_INDEX__, _uart_handle_4, cbFunctPtr, _uart_config_4);
}
#endif

#endif

#endif
