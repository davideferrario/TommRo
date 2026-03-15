
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentUART.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_UART_IS_USED__)

#include <windows.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __AVAILABLE_RES_HARDWARE_AMOUNT__           (5)

#define __UART_0_INDEX__                            (0)
#define __UART_1_INDEX__                            (1)
#define __UART_2_INDEX__                            (2)
#define __UART_3_INDEX__                            (3)
#define __UART_4_INDEX__                            (4)

#define __NOT_VALID_HANDLE__                        (INVALID_HANDLE_VALUE)

#define __UART_DEFAULT_BAUDRAUTE__                  (115200)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    uint32_t    baudRate;
    char*       deviceNameStrPtr;

} _uart_win_config_t_;

#define __EMPTY__uart_win_config_t___                       \
{                                                           \
    /* .baudRate */         __UART_DEFAULT_BAUDRAUTE__,     \
    /* .deviceNameStrPtr */ NULL,                           \
}

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
static _uart_win_config_t_ _hw_0_config = TOMMROC_UTIL_EMPTY_VARIABLE(_uart_win_config_t_);
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
static _uart_win_config_t_ _hw_1_config = TOMMROC_UTIL_EMPTY_VARIABLE(_uart_win_config_t_);
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
static _uart_win_config_t_ _hw_2_config = TOMMROC_UTIL_EMPTY_VARIABLE(_uart_win_config_t_);
#endif

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
static _uart_win_config_t_ _hw_3_config = TOMMROC_UTIL_EMPTY_VARIABLE(_uart_win_config_t_);
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
static _uart_win_config_t_ _hw_4_config = TOMMROC_UTIL_EMPTY_VARIABLE(_uart_win_config_t_);
#endif

static HANDLE _hw_handle[__AVAILABLE_RES_HARDWARE_AMOUNT__] = {
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

static tommRoC_hw_err_enum_t _open_hw(
        const   uint8_t                         hwResIndex,
        const   _uart_win_config_t_*    const   configPtr) {

    DCB dcbSerialParams     = {0};
    COMMTIMEOUTS timeouts   = {0};
    HANDLE handle;

    TOMMROC_ASSERT_LESS_THAN(hwResIndex, __AVAILABLE_RES_HARDWARE_AMOUNT__);

    handle = CreateFile(
            configPtr->deviceNameStrPtr,    // Address of name of the communications device
            GENERIC_READ | GENERIC_WRITE,   // Access (read-write) mode
            0,                              // Must be opened with exclusive-access
            NULL,                           // Default security attributes
            OPEN_EXISTING,                  // Must use OPEN_EXISTING
            0,                              // Not overlapped I/O
            NULL);                          // hTemplate must be NULL for comm devices

    TOMMROC_ASSERT_NOT_EQUALS(handle, __NOT_VALID_HANDLE__);

    if (__NOT_VALID_HANDLE__ == handle) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    // Initialize the DCB structure.
    dcbSerialParams.DCBlength = sizeof(DCB);

    //  Build on the current configuration by first retrieving all current settings.
    if (!GetCommState(handle, &dcbSerialParams)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    // Fill in some DCB values and set the com state:
    dcbSerialParams.BaudRate    = (DWORD) configPtr->baudRate;  // Baud rate
    dcbSerialParams.ByteSize    = 8;                            // Data size, xmit and rcv
    dcbSerialParams.Parity      = NOPARITY;                     // Parity bit
    dcbSerialParams.StopBits    = ONESTOPBIT;                   // Stop bit

    if (!SetCommState(handle, &dcbSerialParams)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    timeouts.ReadIntervalTimeout            = 50;
    timeouts.ReadTotalTimeoutConstant       = 50;
    timeouts.ReadTotalTimeoutMultiplier     = 10;
    timeouts.WriteTotalTimeoutConstant      = 50;
    timeouts.WriteTotalTimeoutMultiplier    = 10;

    if (!SetCommTimeouts(handle, &timeouts)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    _hw_handle[hwResIndex] = handle;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

/******************* Common BUS functions */

static tommRoC_hw_err_enum_t _hw_write_buffer(
        const   uint8_t             hwResIndex,
        const   uint8_t*    const   writeBufferPtr,
        const   uint16_t            writeBufferLen) {

    HANDLE handle;
    DWORD writtenBytes;

    TOMMROC_ASSERT_LESS_THAN(hwResIndex, __AVAILABLE_RES_HARDWARE_AMOUNT__);

    handle = _hw_handle[hwResIndex];

    TOMMROC_ASSERT_NOT_EQUALS(handle, __NOT_VALID_HANDLE__);

    if (__NOT_VALID_HANDLE__ == handle) {
        return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
    }

    if (!WriteFile(handle, writeBufferPtr, writeBufferLen, &writtenBytes, NULL)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_EQUALS(writeBufferLen, writtenBytes);

    if (writeBufferLen != writtenBytes) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _hw_read_buffer(
        const   uint8_t             hwResIndex,
                uint8_t*    const   readBufferPtr,
        const   uint16_t            toReadAmount,
                uint16_t*   const   readedAmountPtr) {

    HANDLE handle;
    DWORD bytesRead = 0;

    TOMMROC_ASSERT_LESS_THAN(hwResIndex, __AVAILABLE_RES_HARDWARE_AMOUNT__);

    handle = _hw_handle[hwResIndex];

    TOMMROC_ASSERT_NOT_EQUALS(handle, __NOT_VALID_HANDLE__);

    if (__NOT_VALID_HANDLE__ == handle) {
        return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
    }

    if (!ReadFile(handle, readBufferPtr, toReadAmount, &bytesRead, NULL)){
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_EQUALS(bytesRead, toReadAmount);

    *readedAmountPtr = (uint16_t) bytesRead;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _common_data_ready(
        const   uint8_t             hwResIndex,
                uint16_t*   const   availableAmountPtr) {

    HANDLE handle;
    COMSTAT comStat;
    DWORD dwErrors;

    TOMMROC_ASSERT_LESS_THAN(hwResIndex, __AVAILABLE_RES_HARDWARE_AMOUNT__);

    handle = _hw_handle[hwResIndex];

    TOMMROC_ASSERT_NOT_EQUALS(handle, __NOT_VALID_HANDLE__);

    if (__NOT_VALID_HANDLE__ == handle) {
        return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
    }

    if (!ClearCommError(handle, &dwErrors, &comStat)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    *availableAmountPtr = comStat.cbInQue;

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
        const   uint8_t                             hwResIndex,
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount) {

    tommRoC_hw_bus_read_buf_t* readBufferPtr;
    uint8_t index;

    for (index = 0, readBufferPtr = readBuffersPtr; index < readBuffersAmount; ++index, ++readBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _hw_read_buffer(
                        hwResIndex,
                        readBufferPtr->bufferPtr,
                        readBufferPtr->toReadAmount,
                        readBufferPtr->readedAmountPtr));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _common_clear_data(
        const   uint8_t hwResIndex) {
}

static tommRoC_hw_err_enum_t _common_clear_received_data(
        const   uint8_t hwResIndex) {
}


/******************* BUS implementation functs */

#define __TOMMROC_HW_UART_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(                           \
                hwResIndex)                                                                         \
                                                                                                    \
    static tommRoC_hw_err_enum_t _uart ## hwResIndex ## _data_ready_Win(                            \
                    uint16_t*   const   availableAmountPtr,                                         \
            const   void*       const   inputPtr,                                                   \
                    void*       const   resultPtr) {                                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return  _common_data_ready(hwResIndex, availableAmountPtr);                                 \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _uart ## hwResIndex ## _write_buffers_Win(                         \
            const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,                            \
            const   uint8_t                             writeBuffersAmount,                         \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _common_write_buffers(hwResIndex, writeBuffersPtr, writeBuffersAmount);              \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _uart ## hwResIndex ## _read_buffers_Win(                          \
                    tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,                             \
            const   uint8_t                             readBuffersAmount,                          \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _common_read_buffers(hwResIndex, readBuffersPtr, readBuffersAmount);                 \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _uart ## hwResIndex ## _clear_data_Win(                            \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _common_clear_data(hwResIndex);                                                      \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _uart ## hwResIndex ## _clear_received_data_Win(                   \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _common_clear_received_data(hwResIndex);                                             \
    }                                                                                               \
                                                                                                    \
    static void _uart ## hwResIndex ## _get_callback_Win(                                           \
                    tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {                               \
                                                                                                    \
        cbFunctPtr->dataReady           = _uart ## hwResIndex ## _data_ready_Win;                   \
        cbFunctPtr->writeBuffers        = _uart ## hwResIndex ## _write_buffers_Win;                \
        cbFunctPtr->readBuffers         = _uart ## hwResIndex ## _read_buffers_Win;                 \
        cbFunctPtr->clearData           = _uart ## hwResIndex ## _clear_data_Win;                   \
        cbFunctPtr->clearReceivedData   = _uart ## hwResIndex ## _clear_received_data_Win;          \
    }

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    __TOMMROC_HW_UART_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(__UART_0_INDEX__);
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    __TOMMROC_HW_UART_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(__UART_1_INDEX__);
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    __TOMMROC_HW_UART_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(__UART_2_INDEX__);
#endif

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
    __TOMMROC_HW_UART_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(__UART_3_INDEX__);
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
    __TOMMROC_HW_UART_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(__UART_4_INDEX__);
#endif


#define __TOMMROC_HW_TEMPLATE_BUS_UART_START_WIN__(hwResIndex, config, cbFunctPtr)                          \
                                                                                                            \
        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_open_hw(hwResIndex, &config));    \
                                                                                                            \
        _uart ## hwResIndex ## _get_callback_Win(cbFunctPtr);                                               \
                                                                                                            \
        return TOMMRO_C_HW_ERR_SUCCESS;


static tommRoC_hw_err_enum_t _check_device_name_string(
        const   char*   const   deviceNameStrPtr) {

    if (TOMMRO_C_ERR_SUCCESS == tommRoCStringStartWith(deviceNameStrPtr, "\\\\.\\COM")) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    return TOMMRO_C_HW_PARAM_ERR;
}

static tommRoC_hw_err_enum_t _set_bus_uart_baud_rate(
        const   tommRoC_hw_template_bus_uart_enum_t         bus,
        const   uint32_t*                           const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_0:
        _hw_0_config.baudRate = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_1:
        _hw_1_config.baudRate = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_2:
        _hw_2_config.baudRate = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_3:
        _hw_3_config.baudRate = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_4:
        _hw_4_config.baudRate = *propValuePtr;
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
        _hw_0_config.deviceNameStrPtr = (char*) propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_1:
        _hw_1_config.deviceNameStrPtr = (char*) propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_2:
        _hw_2_config.deviceNameStrPtr = (char*) propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_3:
        _hw_3_config.deviceNameStrPtr = (char*) propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_UART_4:
        _hw_4_config.deviceNameStrPtr = (char*) propValuePtr;
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

    __TOMMROC_HW_TEMPLATE_BUS_UART_START_WIN__(__UART_0_INDEX__, _hw_0_config, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_UART_START_WIN__(__UART_1_INDEX__, _hw_1_config, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART2Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_UART_START_WIN__(__UART_2_INDEX__, _hw_2_config, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART3Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_UART_START_WIN__(__UART_3_INDEX__, _hw_3_config, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART4Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_UART_START_WIN__(__UART_4_INDEX__, _hw_4_config, cbFunctPtr);
}
#endif

#endif

#endif
