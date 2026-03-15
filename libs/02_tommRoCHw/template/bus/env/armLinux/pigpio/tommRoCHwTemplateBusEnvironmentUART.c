
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentUART.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_UART_IS_USED__)

#include <pigpio.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __RPI_AVAILABLE_RES_HARDWARE_AMOUNT__       (2)

#define __RPI_UART_0_INDEX__                        (0)
#define __RPI_UART_1_INDEX__                        (1)

#define __RPI_UART0_TXD_GPIO_PIN__                  (14)
#define __RPI_UART0_RXD_GPIO_PIN__                  (15)

#define __NOT_VALID_HANDLE__                        (-1)

#define __HARDWARE_RPI_UART_DEFAULT_BAUDRAUTE__     (115200)

#define __PIGPIO_GPIO_SUCCESS_RESULT__              (0)
#define __PIGPIO_HW_SUCCESS_RESULT__                (0)

#define __SER_OPEN_DEFAULT_FLAG_PARAM__             (0)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    uint32_t    baudRate;
    char*       deviceNameStrPtr;

} _uart_arm_linux_config_t_;

#define __EMPTY__uart_arm_linux_config_t___                             \
{                                                                       \
    /* .baudRate */         __HARDWARE_RPI_UART_DEFAULT_BAUDRAUTE__,    \
    /* .deviceNameStrPtr */ NULL,                                       \
}

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
static _uart_arm_linux_config_t_ _hw_0_config = TOMMROC_UTIL_EMPTY_VARIABLE(_uart_arm_linux_config_t_);
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
static _uart_arm_linux_config_t_ _hw_1_config = TOMMROC_UTIL_EMPTY_VARIABLE(_uart_arm_linux_config_t_);
#endif

static int _hw_handle[__RPI_AVAILABLE_RES_HARDWARE_AMOUNT__] = {
        __NOT_VALID_HANDLE__,
        __NOT_VALID_HANDLE__,
};

/*******************************************************************************
 * local functions
 ******************************************************************************/

/******************* Low level functions */

static tommRoC_hw_err_enum_t _open_hw(
        const   uint8_t                                     hwResIndex,
        const   _uart_arm_linux_config_t_*          const   configPtr) {

    int handle;

    TOMMROC_ASSERT_LESS_THAN(hwResIndex, __RPI_AVAILABLE_RES_HARDWARE_AMOUNT__);

    handle = serOpen(
            configPtr->deviceNameStrPtr,
            configPtr->baudRate,
            __SER_OPEN_DEFAULT_FLAG_PARAM__);

    TOMMROC_ASSERT_MORE_OR_EQUALS_THAN(handle, __PIGPIO_HW_SUCCESS_RESULT__);

    if (handle < __PIGPIO_HW_SUCCESS_RESULT__) {
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

    int handle;
    int result;

    TOMMROC_ASSERT_LESS_THAN(hwResIndex, __RPI_AVAILABLE_RES_HARDWARE_AMOUNT__);

    handle = _hw_handle[hwResIndex];

    TOMMROC_ASSERT_NOT_EQUALS(handle, __NOT_VALID_HANDLE__);

    if (__NOT_VALID_HANDLE__ == handle) {
        return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
    }

    result = serWrite(handle, (char*) writeBufferPtr, (unsigned) writeBufferLen);

    TOMMROC_ASSERT_MORE_OR_EQUALS_THAN(result, __PIGPIO_HW_SUCCESS_RESULT__);

    if (result < __PIGPIO_HW_SUCCESS_RESULT__) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _hw_read_buffer(
        const   uint8_t             hwResIndex,
                uint8_t*    const   readBufferPtr,
        const   uint16_t            toReadAmount,
                uint16_t*   const   readedAmountPtr) {

    int handle;
    int result;

    TOMMROC_ASSERT_LESS_THAN(hwResIndex, __RPI_AVAILABLE_RES_HARDWARE_AMOUNT__);

    handle = _hw_handle[hwResIndex];

    TOMMROC_ASSERT_NOT_EQUALS(handle, __NOT_VALID_HANDLE__);

    if (__NOT_VALID_HANDLE__ == handle) {
        return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
    }

    result = serRead(handle, (char*) readBufferPtr, (unsigned) toReadAmount);

    TOMMROC_ASSERT_MORE_OR_EQUALS_THAN(result, __PIGPIO_HW_SUCCESS_RESULT__);

    if (result < __PIGPIO_HW_SUCCESS_RESULT__) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    *readedAmountPtr = (uint16_t) result;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _common_data_ready(
        const   uint8_t             hwResIndex,
                uint16_t*   const   availableAmountPtr) {

    int handle;
    int availableBytes;

    TOMMROC_ASSERT_LESS_THAN(hwResIndex, __RPI_AVAILABLE_RES_HARDWARE_AMOUNT__);

    handle = _hw_handle[hwResIndex];

    TOMMROC_ASSERT_NOT_EQUALS(handle, __NOT_VALID_HANDLE__);

    if (__NOT_VALID_HANDLE__ == handle) {
        return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
    }

    availableBytes = serDataAvailable(handle);

    TOMMROC_ASSERT_MORE_OR_EQUALS_THAN(availableBytes, __PIGPIO_HW_SUCCESS_RESULT__);

    if (availableBytes < __PIGPIO_HW_SUCCESS_RESULT__) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    *availableAmountPtr = (uint16_t) availableBytes;

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

    uint16_t availableAmount;
    uint16_t readedAmount;
    uint16_t idx;
    uint8_t dataByte;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _common_data_ready(hwResIndex, &availableAmount));

    for (idx = 0; idx < availableAmount; ++idx) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _hw_read_buffer(
                        hwResIndex,
                        &dataByte,
                        sizeof(dataByte),
                        &readedAmount));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _common_clear_received_data(
        const   uint8_t hwResIndex) {

    uint16_t availableAmount;
    uint16_t readedAmount;
    uint16_t idx;
    uint8_t dataByte;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _common_data_ready(hwResIndex, &availableAmount));

    for (idx = 0; idx < availableAmount; ++idx) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _hw_read_buffer(
                        hwResIndex,
                        &dataByte,
                        sizeof(dataByte),
                        &readedAmount));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}


/******************* BUS implementation functs */

#define __TOMMROC_HW_UART_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(hwResIndex)                        \
                                                                                                            \
    static tommRoC_hw_err_enum_t _uart ## hwResIndex ## _data_ready_ARMLinux(                               \
                    uint16_t*   const   availableAmountPtr,                                                 \
            const   void*       const   inputPtr,                                                           \
                    void*       const   resultPtr) {                                                        \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        return  _common_data_ready(hwResIndex, availableAmountPtr);                                         \
    }                                                                                                       \
                                                                                                            \
    static tommRoC_hw_err_enum_t _uart ## hwResIndex ## _write_buffers_ARMLinux(                            \
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
    static tommRoC_hw_err_enum_t _uart ## hwResIndex ## _read_buffers_ARMLinux(                             \
                    tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,                                     \
            const   uint8_t                             readBuffersAmount,                                  \
            const   void*                       const   inputPtr,                                           \
                    void*                       const   resultPtr) {                                        \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        return _common_read_buffers(hwResIndex, readBuffersPtr, readBuffersAmount);                         \
    }                                                                                                       \
                                                                                                            \
    static tommRoC_hw_err_enum_t _uart ## hwResIndex ## _clear_data_ARMLinux(                               \
            const   void*                       const   inputPtr,                                           \
                    void*                       const   resultPtr) {                                        \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        return _common_clear_data(hwResIndex);                                                              \
    }                                                                                                       \
                                                                                                            \
    static tommRoC_hw_err_enum_t _uart ## hwResIndex ## _clear_received_data_ARMLinux(                      \
            const   void*                       const   inputPtr,                                           \
                    void*                       const   resultPtr) {                                        \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        return _common_clear_received_data(hwResIndex);                                                     \
    }                                                                                                       \
                                                                                                            \
    static void _uart ## hwResIndex ## _get_callback_ARMLinux(                                              \
                    tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {                                       \
                                                                                                            \
        cbFunctPtr->dataReady           = _uart ## hwResIndex ## _data_ready_ARMLinux;                      \
        cbFunctPtr->writeBuffers        = _uart ## hwResIndex ## _write_buffers_ARMLinux;                   \
        cbFunctPtr->readBuffers         = _uart ## hwResIndex ## _read_buffers_ARMLinux;                    \
        cbFunctPtr->clearData           = _uart ## hwResIndex ## _clear_data_ARMLinux;                      \
        cbFunctPtr->clearReceivedData   = _uart ## hwResIndex ## _clear_received_data_ARMLinux;             \
    }

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    __TOMMROC_HW_UART_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(__RPI_UART_0_INDEX__);
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    __TOMMROC_HW_UART_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(__RPI_UART_1_INDEX__);
#endif


#define __TOMMROC_HW_TEMPLATE_BUS_UART_START_ARMLINUX__(hwResIndex, config, cbFunctPtr)                     \
                                                                                                            \
        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_open_hw(hwResIndex, &config));    \
                                                                                                            \
        _uart ## hwResIndex ## _get_callback_ARMLinux(cbFunctPtr);                                          \
                                                                                                            \
        return TOMMRO_C_HW_ERR_SUCCESS;


static tommRoC_hw_err_enum_t _check_device_name_string(
        const   char*   const   deviceNameStrPtr) {

    if (TOMMRO_C_ERR_SUCCESS == tommRoCStringStartWith(deviceNameStrPtr, "/dev/ttyS")) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
    
    if (TOMMRO_C_ERR_SUCCESS == tommRoCStringStartWith(deviceNameStrPtr, "/dev/ttyUSB")) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }    

    if (TOMMRO_C_ERR_SUCCESS == tommRoCStringStartWith(deviceNameStrPtr, "/dev/serial")) {
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

    __TOMMROC_HW_TEMPLATE_BUS_UART_START_ARMLINUX__(__RPI_UART_0_INDEX__, _hw_0_config, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_UART_START_ARMLINUX__(__RPI_UART_1_INDEX__, _hw_1_config, cbFunctPtr);
}
#endif

#endif

#endif
