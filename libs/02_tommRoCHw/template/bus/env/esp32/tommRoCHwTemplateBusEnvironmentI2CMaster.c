
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentI2CMaster.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

#include "bus/common/i2c/master/tommRoCHwTemplateBusCommonI2CMasterCb.h"

#include "bus/env/esp32/i2c/tommRoCHwTemplateBusI2CESP32Hal.h"

#if (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
#include "soc/gpio_num.h"
#endif

#include "driver/gpio.h"
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __DEFAULT_BAUDRATE__            (100000)
#define __DEFAULT_SDA_IO_NUM__          (GPIO_NUM_NC)
#define __DEFAULT_SCL_IO_NUM__          (GPIO_NUM_NC)
#define __DEFAULT_MCU_PULL_UP_STATUS__  (TOMMRO_C_UTIL_DISABLED)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    uint32_t                                baudRate;
    gpio_num_t                              sdaGPIONum;
    gpio_num_t                              sclGPIONum;
    tommRoC_util_enabled_status_enum_t      mcuPullUpStatus;

} __tommRoC_hw_i2c_master_config_t__;

#define __EMPTY___tommRoC_hw_i2c_master_config_t____        \
{                                                           \
    /* .baudRate */         __DEFAULT_BAUDRATE__,           \
    /* .sdaGPIONum */       __DEFAULT_SDA_IO_NUM__,         \
    /* .sclGPIONum */       __DEFAULT_SCL_IO_NUM__,         \
    /* .mcuPullUpStatus */  __DEFAULT_MCU_PULL_UP_STATUS__, \
}

typedef struct {

    i2c_port_t  i2cPort;

} __tommRoC_hw_i2c_master_handle_t__;

#define __EMPTY___tommRoC_hw_i2c_master_handle_t____    \
{                                                       \
    /* .i2cPort */      I2C_NUM_MAX,                    \
}

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
static __tommRoC_hw_i2c_master_config_t__ _i2c_master_config_0 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_i2c_master_config_t__);
static __tommRoC_hw_i2c_master_handle_t__ _i2c_master_handle_0 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_i2c_master_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
static __tommRoC_hw_i2c_master_config_t__ _i2c_master_config_1 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_i2c_master_config_t__);
static __tommRoC_hw_i2c_master_handle_t__ _i2c_master_handle_1 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_i2c_master_handle_t__);
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_hw_err_enum_t _write_buffers(
                i2c_cmd_handle_t                            cmd,
        const   __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
        const   uint8_t                                     slaveAddress7Bit,
        const   tommRoC_hw_bus_write_buf_t*         const   writeBuffersPtr,
        const   uint8_t                                     writeBuffersAmount,
        const   uint32_t                                    timeoutPerByteMsec) {

    const tommRoC_hw_bus_write_buf_t* writeBufferPtr;
    uint8_t index;
    uint16_t toWriteAmount;

    if (ESP_OK != i2c_master_start(cmd)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (ESP_OK != i2c_master_write_byte(cmd, (slaveAddress7Bit << 1) | I2C_MASTER_WRITE, true)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    for (index = 0, writeBufferPtr = writeBuffersPtr, toWriteAmount = 0; index < writeBuffersAmount; ++index, ++writeBufferPtr, toWriteAmount += writeBufferPtr->toWriteAmount) {

        if (ESP_OK != i2c_master_write(cmd, writeBufferPtr->bufferPtr, (size_t) writeBufferPtr->toWriteAmount, true)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }
    }

    if (ESP_OK != i2c_master_stop(cmd)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (ESP_OK != i2c_master_cmd_begin(i2cHandlePtr->i2cPort, cmd, ((uint32_t) toWriteAmount * timeoutPerByteMsec) / portTICK_RATE_MS)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _read_buffers(
                i2c_cmd_handle_t                            cmd,
        const   __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
        const   uint8_t                                     slaveAddress7Bit,
                tommRoC_hw_bus_read_buf_t*          const   readBuffersPtr,
        const   uint8_t                                     readBuffersAmount,
        const   uint32_t                                    timeoutPerByteMsec) {

    tommRoC_hw_bus_read_buf_t* readBufferPtr;
    uint8_t index;
    uint16_t toReadAmount;
    i2c_ack_type_t ackType;

    if (ESP_OK != i2c_master_start(cmd)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (ESP_OK != i2c_master_write_byte(cmd, (slaveAddress7Bit << 1) | I2C_MASTER_READ, true)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    for (index = 0, readBufferPtr = readBuffersPtr, toReadAmount = 0; index < readBuffersAmount; ++index, ++readBufferPtr, toReadAmount += readBufferPtr->toReadAmount) {

        ackType = (readBuffersAmount - 1 != index) ? I2C_MASTER_ACK : I2C_MASTER_LAST_NACK;

        if (ESP_OK != i2c_master_read(cmd, readBufferPtr->bufferPtr, (size_t) readBufferPtr->toReadAmount, ackType)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        *(readBufferPtr->readedAmountPtr) = readBufferPtr->toReadAmount;
    }

    if (ESP_OK != i2c_master_stop(cmd)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (ESP_OK != i2c_master_cmd_begin(i2cHandlePtr->i2cPort, cmd, ((uint32_t) toReadAmount * timeoutPerByteMsec) / portTICK_RATE_MS)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _write_read_buffer(
                i2c_cmd_handle_t                            cmd,
        const   __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
        const   uint8_t                                     slaveAddress7Bit,
        const   uint8_t*                            const   writeBufferPtr,
        const   uint16_t                                    writeBufferLen,
                uint8_t*                            const   readBufferPtr,
        const   uint16_t                                    toReadAmount,
        const   uint32_t                                    delayWriteToReadMsec,
        const   uint32_t                                    timeoutPerByteMsec) {

    TOMMROC_UTIL_UNUSED_PARAM(delayWriteToReadMsec);

    if (ESP_OK != i2c_master_start(cmd)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (ESP_OK != i2c_master_write_byte(cmd, (slaveAddress7Bit << 1) | I2C_MASTER_WRITE, true)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (ESP_OK != i2c_master_write(cmd, writeBufferPtr, (size_t) writeBufferLen, true)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (ESP_OK != i2c_master_start(cmd)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (ESP_OK != i2c_master_write_byte(cmd, (slaveAddress7Bit << 1) | I2C_MASTER_READ, true)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (ESP_OK != i2c_master_read(cmd, readBufferPtr, (size_t) toReadAmount, I2C_MASTER_LAST_NACK)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (ESP_OK != i2c_master_stop(cmd)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (ESP_OK != i2c_master_cmd_begin(i2cHandlePtr->i2cPort, cmd, ((uint32_t) (writeBufferLen + toReadAmount) * timeoutPerByteMsec) / portTICK_RATE_MS)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_write_buffers(
                void*                       const   i2cConfigPtr,
                void*                       const   i2cHandlePtr,
        const   uint8_t                             slaveAddress7Bit,
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount,
        const   uint32_t                            timeoutPerByteMsec) {

    tommRoC_hw_err_enum_t res;

    TOMMROC_UTIL_UNUSED_PARAM(i2cConfigPtr);

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    if (NULL == cmd) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    res = _write_buffers(
            cmd,
            i2cHandlePtr,
            slaveAddress7Bit,
            writeBuffersPtr,
            writeBuffersAmount,
            timeoutPerByteMsec);

    i2c_cmd_link_delete(cmd);

    return res;
}

static tommRoC_hw_err_enum_t _phy_read_buffers(
                void*                       const   i2cConfigPtr,
                void*                       const   i2cHandlePtr,
        const   uint8_t                             slaveAddress7Bit,
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   uint32_t                            timeoutPerByteMsec) {

    tommRoC_hw_err_enum_t res;

    TOMMROC_UTIL_UNUSED_PARAM(i2cConfigPtr);

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    if (NULL == cmd) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    res = _read_buffers(
            cmd,
            i2cHandlePtr,
            slaveAddress7Bit,
            readBuffersPtr,
            readBuffersAmount,
            timeoutPerByteMsec);

    i2c_cmd_link_delete(cmd);

    return res;
}

static tommRoC_hw_err_enum_t _phy_write_read_buffer(
                void*                       const   i2cConfigPtr,
                void*                       const   i2cHandlePtr,
        const   uint8_t                             slaveAddress7Bit,
        const   uint8_t*                    const   writeBufferPtr,
        const   uint16_t                            writeBufferLen,
                uint8_t*                    const   readBufferPtr,
        const   uint16_t                            toReadAmount,
        const   uint32_t                            delayWriteToReadMsec,
        const   uint32_t                            timeoutPerByteMsec) {

    tommRoC_hw_err_enum_t res;

    TOMMROC_UTIL_UNUSED_PARAM(i2cConfigPtr);

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    if (NULL == cmd) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    res = _write_read_buffer(
            cmd,
            i2cHandlePtr,
            slaveAddress7Bit,
            writeBufferPtr,
            writeBufferLen,
            readBufferPtr,
            toReadAmount,
            delayWriteToReadMsec,
            timeoutPerByteMsec);

    i2c_cmd_link_delete(cmd);

    return res;
}


/******************* BUS implementation functs */

#define __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(                            \
                i2cMasterPrefix,                                                                    \
                i2cMaster,                                                                          \
                i2cConfig,                                                                          \
                i2cHandle)                                                                          \
                                                                                                    \
    static tommRoC_hw_err_enum_t _i2c_master_ ## i2cMasterPrefix ## _write_buffers_ESP32(           \
            const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,                            \
            const   uint8_t                             writeBuffersAmount,                         \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonI2CMasterCbWriteBuffers(                                   \
                writeBuffersPtr,                                                                    \
                writeBuffersAmount,                                                                 \
                (tommRoC_hw_bus_device_specific_i2c_slave_t*) inputPtr,                             \
                &i2cConfig,                                                                         \
                &i2cHandle,                                                                         \
                _phy_write_buffers);                                                                \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _i2c_master_ ## i2cMasterPrefix ## _read_buffers_ESP32(            \
                    tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,                             \
            const   uint8_t                             readBuffersAmount,                          \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonI2CMasterCbReadBuffers(                                    \
                readBuffersPtr,                                                                     \
                readBuffersAmount,                                                                  \
                (tommRoC_hw_bus_device_specific_i2c_slave_t*) inputPtr,                             \
                &i2cConfig,                                                                         \
                &i2cHandle,                                                                         \
                _phy_read_buffers);                                                                 \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _i2c_master_ ## i2cMasterPrefix ## _write_read_buffer_ESP32(       \
            const   uint8_t*                    const   writeBufferPtr,                             \
            const   uint16_t                            writeBufferLen,                             \
                    uint8_t*                    const   readBufferPtr,                              \
            const   uint16_t                            toReadAmount,                               \
                    uint16_t*                   const   readedAmountPtr,                            \
            const   uint32_t                            delayWriteToReadMsec,                       \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonI2CMasterCbWriteReadBuffer(                                \
                writeBufferPtr,                                                                     \
                writeBufferLen,                                                                     \
                readBufferPtr,                                                                      \
                toReadAmount,                                                                       \
                readedAmountPtr,                                                                    \
                delayWriteToReadMsec,                                                               \
                (tommRoC_hw_bus_device_specific_i2c_slave_t*) inputPtr,                             \
                &i2cConfig,                                                                         \
                &i2cHandle,                                                                         \
                _phy_write_read_buffer);                                                            \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _i2c_master_ ## i2cMasterPrefix ## _clear_data_ESP32(              \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return TOMMRO_C_HW_ERR_SUCCESS;                                                             \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _i2c_master_ ## i2cMasterPrefix ## _low_power_enter_ESP32(         \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusI2CESP32HalSetForLowPowerEnter(                                  \
                i2cHandle.i2cPort,                                                                  \
                i2cConfig.sdaGPIONum,                                                               \
                i2cConfig.sclGPIONum);                                                              \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _i2c_master_ ## i2cMasterPrefix ## _low_power_exit_ESP32(          \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusI2CESP32HalSetForLowPowerExit(                                   \
                i2cHandle.i2cPort,                                                                  \
                i2cConfig.sdaGPIONum,                                                               \
                i2cConfig.sclGPIONum);                                                              \
    }                                                                                               \
                                                                                                    \
    static void _i2c_master_ ## i2cMasterPrefix ## _get_callback_ESP32(                             \
                    tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {                               \
                                                                                                    \
        cbFunctPtr->writeBuffers    = _i2c_master_ ## i2cMasterPrefix ## _write_buffers_ESP32;      \
        cbFunctPtr->readBuffers     = _i2c_master_ ## i2cMasterPrefix ## _read_buffers_ESP32;       \
        cbFunctPtr->writeReadBuffer = _i2c_master_ ## i2cMasterPrefix ## _write_read_buffer_ESP32;  \
        cbFunctPtr->clearData       = _i2c_master_ ## i2cMasterPrefix ## _clear_data_ESP32;         \
        cbFunctPtr->lowPowerEnter   = _i2c_master_ ## i2cMasterPrefix ## _low_power_enter_ESP32;    \
        cbFunctPtr->lowPowerExit    = _i2c_master_ ## i2cMasterPrefix ## _low_power_exit_ESP32;     \
    }

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
    __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(I2C0, TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_0, _i2c_master_config_0, _i2c_master_handle_0);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(I2C1, TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_1, _i2c_master_config_1, _i2c_master_handle_1);
#endif


/******************* BUS set prop functs */


static tommRoC_hw_err_enum_t _set_baudrate(
        const   tommRoC_hw_template_bus_i2c_master_enum_t           bus,
        const   uint32_t*                                   const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_0:
        _i2c_master_config_0.baudRate = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_1:
        _i2c_master_config_1.baudRate = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_mcu_pull_up_status(
        const   tommRoC_hw_template_bus_i2c_master_enum_t           bus,
        const   tommRoC_util_enabled_status_enum_t*         const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_0:
        _i2c_master_config_0.mcuPullUpStatus = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_1:
        _i2c_master_config_1.mcuPullUpStatus = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_sda_pin(
        const   tommRoC_hw_template_bus_i2c_master_enum_t           bus,
        const   gpio_num_t*                                 const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_0:
        _i2c_master_config_0.sdaGPIONum = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_1:
        _i2c_master_config_1.sdaGPIONum = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_scl_pin(
        const   tommRoC_hw_template_bus_i2c_master_enum_t           bus,
        const   gpio_num_t*                                 const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_0:
        _i2c_master_config_0.sclGPIONum = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_1:
        _i2c_master_config_1.sclGPIONum = *propValuePtr;
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

#if defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_DEF_AT_LEAST_ONE_IS_USED__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMasterSetProp(
        const   tommRoC_hw_template_bus_i2c_master_prop_enum_t          property,
        const   tommRoC_hw_template_bus_i2c_master_enum_t               bus,
        const   void*                                           const   propValuePtr) {

    switch (property) {

    case TOMMRO_C_HW_TEMPLATE_BUS_I2C_MASTER_PROP_BAUD_RATE:
        return _set_baudrate(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_I2C_MASTER_PROP_MCU_PULL_UP_STATUS:
        return _set_mcu_pull_up_status(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_I2C_MASTER_PROP_SDA_PIN:
        return _set_sda_pin(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_I2C_MASTER_PROP_SCL_PIN:
        return _set_scl_pin(bus, propValuePtr);

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;
    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster0Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    tommRoC_hw_template_bus_i2c_esp32_hal_config_t halConfig;

    halConfig.i2cPort                       = I2C_NUM_0;
    halConfig.i2cConfig.master.clk_speed    = _i2c_master_config_0.baudRate;
    halConfig.i2cConfig.mode                = I2C_MODE_MASTER;
    halConfig.i2cConfig.sda_io_num          = _i2c_master_config_0.sdaGPIONum;
    halConfig.i2cConfig.sda_pullup_en       = (TOMMRO_C_UTIL_DISABLED == _i2c_master_config_0.mcuPullUpStatus) ? (GPIO_PULLUP_DISABLE) : (GPIO_PULLUP_ENABLE);
    halConfig.i2cConfig.scl_io_num          = _i2c_master_config_0.sclGPIONum;
    halConfig.i2cConfig.scl_pullup_en       = (TOMMRO_C_UTIL_DISABLED == _i2c_master_config_0.mcuPullUpStatus) ? (GPIO_PULLUP_DISABLE) : (GPIO_PULLUP_ENABLE);
    halConfig.i2cConfig.clk_flags           = I2C_SCLK_SRC_FLAG_FOR_NOMAL;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusI2CESP32HalMasterInit(&halConfig));

    _i2c_master_I2C0_get_callback_ESP32(cbFunctPtr);

    _i2c_master_handle_0.i2cPort = halConfig.i2cPort;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    tommRoC_hw_template_bus_i2c_esp32_hal_config_t halConfig;

    halConfig.i2cPort                       = I2C_NUM_1;
    halConfig.i2cConfig.master.clk_speed    = _i2c_master_config_1.baudRate;
    halConfig.i2cConfig.mode                = I2C_MODE_MASTER;
    halConfig.i2cConfig.sda_io_num          = _i2c_master_config_1.sdaGPIONum;
    halConfig.i2cConfig.sda_pullup_en       = (TOMMRO_C_UTIL_DISABLED == _i2c_master_config_1.mcuPullUpStatus) ? (GPIO_PULLUP_DISABLE) : (GPIO_PULLUP_ENABLE);
    halConfig.i2cConfig.scl_io_num          = _i2c_master_config_1.sclGPIONum;
    halConfig.i2cConfig.scl_pullup_en       = (TOMMRO_C_UTIL_DISABLED == _i2c_master_config_1.mcuPullUpStatus) ? (GPIO_PULLUP_DISABLE) : (GPIO_PULLUP_ENABLE);
    halConfig.i2cConfig.clk_flags           = I2C_SCLK_SRC_FLAG_FOR_NOMAL;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusI2CESP32HalMasterInit(&halConfig));

    _i2c_master_I2C1_get_callback_ESP32(cbFunctPtr);

    _i2c_master_handle_1.i2cPort = halConfig.i2cPort;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif
