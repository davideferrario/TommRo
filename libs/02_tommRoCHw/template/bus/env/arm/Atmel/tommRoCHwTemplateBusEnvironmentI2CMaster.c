
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentI2CMaster.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_ATMEL_IS_USED__)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

#include "bus/common/i2c/master/tommRoCHwTemplateBusCommonI2CMasterCb.h"

#include "bus/env/arm/Atmel/i2c/tommRoCHwTemplateBusI2CAtmelHal.h"

#include "TOMMROCMwTemplate.h"

#include "driver_init.h"

#include <stdbool.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __DEFAULT_MCU_PULL_UP_STATUS__  (TOMMRO_C_UTIL_DISABLED)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    tommRoC_util_enabled_status_enum_t mcuPullUpStatus;

} __tommRoC_hw_i2c_master_config_t__;

#define __EMPTY___tommRoC_hw_i2c_master_config_t____        \
{                                                           \
    /* .mcuPullUpStatus */  __DEFAULT_MCU_PULL_UP_STATUS__, \
}

typedef struct {

    bool    cbCalled;
    bool    isError;

} __atmel_callback_data_t__;

#define __EMPTY___atmel_callback_data_t____ \
{                                           \
    /* .cbCalled */ false,                  \
    /* .isError */  false,                  \
}

typedef struct {

    void*                               i2cPtr;
    volatile __atmel_callback_data_t__  atmelCallbackData;

} __tommRoC_hw_i2c_master_handle_t__;

#define __EMPTY___tommRoC_hw_i2c_master_handle_t____                    \
{                                                                       \
    /* .i2cPtr */               NULL,                                   \
    /* .atmelCallbackData */    __EMPTY___atmel_callback_data_t____,    \
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
static void _I2C_error(__tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr) {
    i2cHandlePtr->atmelCallbackData.isError     = true;
    i2cHandlePtr->atmelCallbackData.cbCalled    = true;
}
static void _I2C_tx_complete(__tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr) {
    i2cHandlePtr->atmelCallbackData.isError     = false;
    i2cHandlePtr->atmelCallbackData.cbCalled    = true;
}
static void _I2C_rx_complete(__tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr) {
    i2cHandlePtr->atmelCallbackData.isError     = false;
    i2cHandlePtr->atmelCallbackData.cbCalled    = true;
}

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
static void _I2C0_error(void)       { _I2C_error(&_i2c_master_handle_0); }
static void _I2C0_tx_complete(void) { _I2C_tx_complete(&_i2c_master_handle_0); }
static void _I2C0_rx_complete(void) { _I2C_rx_complete(&_i2c_master_handle_0); }
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
static void _I2C1_error(void)       { _I2C_error(&_i2c_master_handle_1); }
static void _I2C1_tx_complete(void) { _I2C_tx_complete(&_i2c_master_handle_1); }
static void _I2C1_rx_complete(void) { _I2C_rx_complete(&_i2c_master_handle_1); }
#endif

static tommRoC_hw_err_enum_t _i2c_master_transfer(
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
        const   uint8_t                                     slaveAddress7Bit,
                uint8_t*                            const   buffer,
        const   int32_t                                     len,
        const   uint16_t                                    flags,
        const   uint32_t                                    timeoutMsec) {

    struct i2c_m_async_desc * i2cAsyncDescPtr = (struct i2c_m_async_desc *) i2cHandlePtr->i2cPtr;

    struct _i2c_m_msg msg;

    tommRoC_timer_t timer;
    uint32_t elapsedMsec;

    msg.addr    = slaveAddress7Bit;
    msg.flags   = flags;
    msg.len     = len;
    msg.buffer  = buffer;

    i2cHandlePtr->atmelCallbackData.cbCalled = false;

    if (ERR_NONE != i2c_m_async_transfer(i2cAsyncDescPtr, &msg)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, timeoutMsec));

    do {

        if (i2cHandlePtr->atmelCallbackData.cbCalled) {
            if (!i2cHandlePtr->atmelCallbackData.isError) {
                return TOMMRO_C_HW_ERR_SUCCESS;
            }
            else {
                break;
            }
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerElapsed(&timer, &elapsedMsec));

        if (elapsedMsec > 1) {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1));
        }
        else {
#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
            // NOTE: don't replace with tommRoCOsDelayMsec(0) because as fast as possible is needed in case of single task project.
            tommRoCMwThreadYield();
#endif
        }

    } while (TOMMRO_C_TIMER_NOT_EXPIRED_ERR == tommRoCTimerIsExpired(&timer));

    // NOTE: in case of timeout expired, check again if SUCCESS because it could be the case in multitask environment
    if ((i2cHandlePtr->atmelCallbackData.cbCalled) && (!i2cHandlePtr->atmelCallbackData.isError)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    if (!i2cHandlePtr->atmelCallbackData.cbCalled || i2cHandlePtr->atmelCallbackData.isError) {
        TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(i2c_m_async_send_stop(i2cAsyncDescPtr), I2C_OK);
    }

    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
}

static tommRoC_hw_err_enum_t _i2c_master_write_transfer(
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
        const   uint8_t                                     slaveAddress7Bit,
        const   uint8_t*                            const   writeBufferPtr,
        const   uint16_t                                    writeBufferLen,
        const   uint16_t                                    flags,
        const   uint32_t                                    timeoutMsec) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _i2c_master_transfer(
                    i2cHandlePtr,
                    slaveAddress7Bit,
                    (uint8_t*) writeBufferPtr,
                    writeBufferLen,
                    flags,
                    timeoutMsec));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _i2c_master_read_transfer(
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
        const   uint8_t                                     slaveAddress7Bit,
                uint8_t*                            const   readBufferPtr,
        const   uint16_t                                    toReadAmount,
        const   uint16_t                                    flags,
        const   uint32_t                                    timeoutMsec) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _i2c_master_transfer(
                    i2cHandlePtr,
                    slaveAddress7Bit,
                    readBufferPtr,
                    toReadAmount,
                    flags,
                    timeoutMsec));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_write_buffers(
                void*                       const   i2cConfigPtr,
                void*                       const   i2cHandlePtr,
        const   uint8_t                             slaveAddress7Bit,
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount,
        const   uint32_t                            timeoutPerByteMsec) {

    const tommRoC_hw_bus_write_buf_t* writeBufferPtr;
    uint8_t idx;

    uint8_t wrBuffer[256];
    uint16_t wrBufferLen;

    void* ptr;
    uint16_t bSize;

    TOMMROC_UTIL_UNUSED_PARAM(i2cConfigPtr);

    wrBufferLen = tommRoCHwBusWriteBuffersTotalToWriteData(writeBuffersPtr, writeBuffersAmount);

    if (wrBufferLen > sizeof(wrBuffer)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    ptr     = wrBuffer;
    bSize   = wrBufferLen;
    for (idx = 0, writeBufferPtr = writeBuffersPtr; idx < writeBuffersAmount; ++idx, ++writeBufferPtr) {
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilBufferAppendArray(ptr, bSize, writeBufferPtr->bufferPtr, writeBufferPtr->toWriteAmount, &ptr, &bSize));
    }

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _i2c_master_write_transfer(
                    i2cHandlePtr,
                    slaveAddress7Bit,
                    wrBuffer,
                    wrBufferLen,
                    I2C_M_STOP,
                    timeoutPerByteMsec * tommRoCMathMax(1, wrBufferLen)));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_read_buffers(
                void*                       const   i2cConfigPtr,
                void*                       const   i2cHandlePtr,
        const   uint8_t                             slaveAddress7Bit,
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   uint32_t                            timeoutPerByteMsec) {

    tommRoC_hw_bus_read_buf_t* readBufferPtr;
    uint8_t idx;

    uint8_t rdBuffer[256];
    uint16_t rdBufferLen;

    void* ptr;
    uint16_t bSize;

    TOMMROC_UTIL_UNUSED_PARAM(i2cConfigPtr);

    rdBufferLen = tommRoCHwBusReadBuffersTotalToReadData(readBuffersPtr, readBuffersAmount);

    if (rdBufferLen > sizeof(rdBuffer)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _i2c_master_read_transfer(
                    i2cHandlePtr,
                    slaveAddress7Bit,
                    rdBuffer,
                    rdBufferLen,
                    I2C_M_STOP | I2C_M_RD,
                    timeoutPerByteMsec * tommRoCMathMax(1, rdBufferLen)));

    ptr     = rdBuffer;
    bSize   = rdBufferLen;
    for (idx = 0, readBufferPtr = readBuffersPtr; idx < readBuffersAmount; ++idx, ++readBufferPtr) {
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilBufferExtractArray(ptr, bSize, readBufferPtr->bufferPtr, readBufferPtr->toReadAmount, &ptr, &bSize));
        *(readBufferPtr->readedAmountPtr) = readBufferPtr->toReadAmount;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
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

    TOMMROC_UTIL_UNUSED_PARAM(i2cConfigPtr);
    TOMMROC_UTIL_UNUSED_PARAM(timeoutPerByteMsec);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _i2c_master_write_transfer(
                    i2cHandlePtr,
                    slaveAddress7Bit,
                    writeBufferPtr,
                    writeBufferLen,
                    I2C_M_STOP,
                    timeoutPerByteMsec * tommRoCMathMax(1, writeBufferLen)));

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(delayWriteToReadMsec));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _i2c_master_read_transfer(
                    i2cHandlePtr,
                    slaveAddress7Bit,
                    readBufferPtr,
                    toReadAmount,
                    I2C_M_STOP | I2C_M_RD,
                    timeoutPerByteMsec * tommRoCMathMax(1, toReadAmount)));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_low_power_enter(
        const   __tommRoC_hw_i2c_master_config_t__* const   i2cConfigPtr,
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr) {

    struct i2c_m_async_desc* i2cHandleTypePtr = (struct i2c_m_async_desc*) i2cHandlePtr->i2cPtr;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusI2CAtmelHalSetForLowPowerEnter(
                    i2cHandleTypePtr,
                    i2cConfigPtr->mcuPullUpStatus));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_low_power_exit(
        const   __tommRoC_hw_i2c_master_config_t__* const   i2cConfigPtr,
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr) {

    struct i2c_m_async_desc* i2cHandleTypePtr = (struct i2c_m_async_desc*) i2cHandlePtr->i2cPtr;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusI2CAtmelHalSetForLowPowerExit(
                    i2cHandleTypePtr,
                    i2cConfigPtr->mcuPullUpStatus));

    return TOMMRO_C_HW_ERR_SUCCESS;
}


/******************* BUS implementation functs */

#define __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(                            \
                i2cMasterPrefix,                                                                    \
                i2cConfig,                                                                          \
                i2cHandle)                                                                          \
                                                                                                    \
    static tommRoC_hw_err_enum_t _i2c_master_ ## i2cMasterPrefix ## _write_buffers_ARM(             \
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
                NULL,                                                                               \
                &i2cHandle,                                                                         \
                _phy_write_buffers);                                                                \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _i2c_master_ ## i2cMasterPrefix ## _read_buffers_ARM(              \
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
                NULL,                                                                               \
                &i2cHandle,                                                                         \
                _phy_read_buffers);                                                                 \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _i2c_master_ ## i2cMasterPrefix ## _write_read_buffer_ARM(         \
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
                NULL,                                                                               \
                &i2cHandle,                                                                         \
                _phy_write_read_buffer);                                                            \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _i2c_master_ ## i2cMasterPrefix ## _clear_data_ARM(                \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return TOMMRO_C_HW_ERR_SUCCESS;                                                             \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _i2c_master_ ## i2cMasterPrefix ## _low_power_enter_ARM(           \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _phy_low_power_enter(&i2cConfig, &i2cHandle);                                        \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _i2c_master_ ## i2cMasterPrefix ## _low_power_exit_ARM(            \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _phy_low_power_exit(&i2cConfig, &i2cHandle);                                         \
    }                                                                                               \
                                                                                                    \
    static void _i2c_master_ ## i2cMasterPrefix ## _get_callback_ARM(                               \
                    tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {                               \
                                                                                                    \
        cbFunctPtr->writeBuffers    = _i2c_master_ ## i2cMasterPrefix ## _write_buffers_ARM;        \
        cbFunctPtr->readBuffers     = _i2c_master_ ## i2cMasterPrefix ## _read_buffers_ARM;         \
        cbFunctPtr->writeReadBuffer = _i2c_master_ ## i2cMasterPrefix ## _write_read_buffer_ARM;    \
        cbFunctPtr->clearData       = _i2c_master_ ## i2cMasterPrefix ## _clear_data_ARM;           \
        cbFunctPtr->lowPowerEnter   = _i2c_master_ ## i2cMasterPrefix ## _low_power_enter_ARM;      \
        cbFunctPtr->lowPowerExit    = _i2c_master_ ## i2cMasterPrefix ## _low_power_exit_ARM;       \
    }

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
    __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(I2C_0, _i2c_master_config_0, _i2c_master_handle_0);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(I2C_1, _i2c_master_config_1, _i2c_master_handle_1);
#endif


/******************* BUS set prop functs */

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


/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_DEF_AT_LEAST_ONE_IS_USED__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMasterSetProp(
        const   tommRoC_hw_template_bus_i2c_master_prop_enum_t          property,
        const   tommRoC_hw_template_bus_i2c_master_enum_t               bus,
        const   void*                                           const   propValuePtr) {

    switch (property) {

    case TOMMRO_C_HW_TEMPLATE_BUS_I2C_MASTER_PROP_MCU_PULL_UP_STATUS:
        return _set_mcu_pull_up_status(bus, propValuePtr);

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

    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(i2c_m_async_register_callback(&I2C_0, I2C_M_ASYNC_ERROR, (FUNC_PTR)_I2C0_error), I2C_OK);
    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(i2c_m_async_register_callback(&I2C_0, I2C_M_ASYNC_TX_COMPLETE, (FUNC_PTR)_I2C0_tx_complete), I2C_OK);
    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(i2c_m_async_register_callback(&I2C_0, I2C_M_ASYNC_RX_COMPLETE, (FUNC_PTR)_I2C0_rx_complete), I2C_OK);

    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(i2c_m_async_enable(&I2C_0), ERR_NONE);

    _i2c_master_I2C_0_get_callback_ARM(cbFunctPtr);

    _i2c_master_handle_0.i2cPtr = (void*) &I2C_0;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(i2c_m_async_register_callback(&I2C_1, I2C_M_ASYNC_ERROR, (FUNC_PTR)_I2C1_error), I2C_OK);
    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(i2c_m_async_register_callback(&I2C_1, I2C_M_ASYNC_TX_COMPLETE, (FUNC_PTR)_I2C1_tx_complete), I2C_OK);
    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(i2c_m_async_register_callback(&I2C_1, I2C_M_ASYNC_RX_COMPLETE, (FUNC_PTR)_I2C1_rx_complete), I2C_OK);

    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(i2c_m_async_enable(&I2C_1), ERR_NONE);

    _i2c_master_I2C_1_get_callback_ARM(cbFunctPtr);

    _i2c_master_handle_1.i2cPtr = (void*) &I2C_1;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif

#endif

