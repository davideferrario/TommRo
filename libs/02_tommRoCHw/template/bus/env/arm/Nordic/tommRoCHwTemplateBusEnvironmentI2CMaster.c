
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentI2CMaster.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

#include "bus/common/i2c/master/tommRoCHwTemplateBusCommonI2CMasterCb.h"

#include "bus/env/arm/Nordic/i2c/tommRoCHwTemplateBusI2CNordicHal.h"

#include "TOMMROCMwTemplate.h"

#if (defined (TWI_PRESENT) && TWI_COUNT)
#include "nrfx_twi.h"
#endif

#include <stdbool.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __DEFAULT_FREQUENCY__           (NRF_TWI_FREQ_100K)
#define __DEFAULT_SCL_PIN_NUM__         (31)
#define __DEFAULT_SDA_PIN_NUM__         (31)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    nrf_twi_frequency_t frequency;
    uint32_t            sclPin;
    uint32_t            sdaPin;

} __tommRoC_hw_i2c_master_config_t__;

#define __EMPTY___tommRoC_hw_i2c_master_config_t____    \
{                                                       \
    /* .frequency */    __DEFAULT_FREQUENCY__,          \
    /* .sclPin */       __DEFAULT_SCL_PIN_NUM__,        \
    /* .sdaPin */       __DEFAULT_SDA_PIN_NUM__,        \
}

typedef struct {

    bool        cbCalled;
    nrfx_err_t  transferResult;

} __nordic_callback_data_t__;

#define __EMPTY___nordic_callback_data_t____            \
{                                                       \
    /* .cbCalled */         false,                      \
    /* .transferResult */   NRFX_ERROR_INTERNAL,        \
}

typedef struct {

    nrfx_twi_t                  nrfxTwi;
    __nordic_callback_data_t__  nordicCallbackData;

} __tommRoC_hw_i2c_master_handle_t__;

#define __EMPTY___tommRoC_hw_i2c_master_handle_t____                    \
{                                                                       \
    /* .nrfxTwi */              NRFX_TWI_INSTANCE(0),                   \
    /* .nordicCallbackData */   __EMPTY___nordic_callback_data_t____,   \
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
#if (defined (TWI_PRESENT) && TWI_COUNT)
static void _nrfx_twi_evt_handler(
                __nordic_callback_data_t__* const   nordicCallbackDataPtr,
                nrfx_twi_evt_t              const*  p_event,
                void*                               p_context) {

    TOMMROC_UTIL_UNUSED_PARAM(p_context);

    switch (p_event->type) {

    case NRFX_TWI_EVT_DONE:
        nordicCallbackDataPtr->transferResult = NRFX_SUCCESS;
        break;

    case NRFX_TWI_EVT_ADDRESS_NACK:
        nordicCallbackDataPtr->transferResult = NRFX_ERROR_DRV_TWI_ERR_ANACK;
        break;

    case NRFX_TWI_EVT_DATA_NACK:
        nordicCallbackDataPtr->transferResult = NRFX_ERROR_DRV_TWI_ERR_DNACK;
        break;

    default:
        nordicCallbackDataPtr->transferResult = NRFX_ERROR_INTERNAL;
        break;

    }

    nordicCallbackDataPtr->cbCalled = true;
}

static tommRoC_hw_err_enum_t _i2c_master_transfer(
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
                nrfx_twi_xfer_desc_t*               const   nrfxTwiXferDescPtr,
        const   uint32_t                                    flags,
        const   uint32_t                                    timeoutMsec) {

    nrfx_twi_t* nrfxI2cPtr = &i2cHandlePtr->nrfxTwi;

    tommRoC_timer_t timer;
    uint32_t elapsedMsec;

    i2cHandlePtr->nordicCallbackData.cbCalled = false;

    if (NRFX_SUCCESS != nrfx_twi_xfer(nrfxI2cPtr, nrfxTwiXferDescPtr, flags)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, timeoutMsec));

    do {

        if (i2cHandlePtr->nordicCallbackData.cbCalled) {
            if (NRFX_SUCCESS == i2cHandlePtr->nordicCallbackData.transferResult) {
                return TOMMRO_C_HW_ERR_SUCCESS;
            }
            else {
                return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
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
    if ((i2cHandlePtr->nordicCallbackData.cbCalled) && (NRFX_SUCCESS == i2cHandlePtr->nordicCallbackData.transferResult)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
}

static tommRoC_hw_err_enum_t _i2c_master_write_transfer(
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
        const   uint8_t                                     slaveAddress7Bit,
        const   uint8_t*                            const   writeBufferPtr,
        const   uint16_t                                    writeBufferLen,
        const   uint32_t                                    flags,
        const   uint32_t                                    timeoutMsec) {

    nrfx_twi_xfer_desc_t nrfxTwiXferDesc = NRFX_TWI_XFER_DESC_TX(slaveAddress7Bit, (uint8_t*) writeBufferPtr, writeBufferLen);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_i2c_master_transfer(i2cHandlePtr, &nrfxTwiXferDesc, flags, timeoutMsec));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _i2c_master_read_transfer(
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
        const   uint8_t                                     slaveAddress7Bit,
                uint8_t*                            const   readBufferPtr,
        const   uint16_t                                    toReadAmount,
        const   uint32_t                                    flags,
        const   uint32_t                                    timeoutMsec) {

    nrfx_twi_xfer_desc_t nrfxTwiXferDesc = NRFX_TWI_XFER_DESC_RX(slaveAddress7Bit, readBufferPtr, toReadAmount);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_i2c_master_transfer(i2cHandlePtr, &nrfxTwiXferDesc, flags, timeoutMsec));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _i2c_master_write_read_transfer(
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
        const   uint8_t                                     slaveAddress7Bit,
        const   uint8_t*                            const   writeBufferPtr,
        const   uint16_t                                    writeBufferLen,
                uint8_t*                            const   readBufferPtr,
        const   uint16_t                                    toReadAmount,
        const   uint32_t                                    flags,
        const   uint32_t                                    timeoutMsec) {

    nrfx_twi_xfer_desc_t nrfxTwiXferDesc = NRFX_TWI_XFER_DESC_TXRX(slaveAddress7Bit, (uint8_t*) writeBufferPtr, writeBufferLen, readBufferPtr, toReadAmount);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_i2c_master_transfer(i2cHandlePtr, &nrfxTwiXferDesc, flags, timeoutMsec));

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
    uint8_t index;

    TOMMROC_UTIL_UNUSED_PARAM(i2cConfigPtr);

    for (index = 0, writeBufferPtr = writeBuffersPtr; index < writeBuffersAmount; ++index, ++writeBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _i2c_master_write_transfer(
                        i2cHandlePtr,
                        slaveAddress7Bit,
                        writeBufferPtr->bufferPtr,
                        writeBufferPtr->toWriteAmount,
                        0,
                        timeoutPerByteMsec * tommRoCMathMax(1, writeBufferPtr->toWriteAmount)));
    }

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
    uint8_t index;

    TOMMROC_UTIL_UNUSED_PARAM(i2cConfigPtr);

    for (index = 0, readBufferPtr = readBuffersPtr; index < readBuffersAmount; ++index, ++readBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _i2c_master_read_transfer(
                        i2cHandlePtr,
                        slaveAddress7Bit,
                        readBufferPtr->bufferPtr,
                        readBufferPtr->toReadAmount,
                        0,
                        timeoutPerByteMsec * tommRoCMathMax(1, readBufferPtr->toReadAmount)));

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
    TOMMROC_UTIL_UNUSED_PARAM(delayWriteToReadMsec);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _i2c_master_write_read_transfer(
                    i2cHandlePtr,
                    slaveAddress7Bit,
                    writeBufferPtr,
                    writeBufferLen,
                    readBufferPtr,
                    toReadAmount,
                    0,
                    timeoutPerByteMsec * tommRoCMathMax(1, writeBufferLen + toReadAmount)));

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif


/******************* Driver IRQ event Handler */

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
static void _nrfx_twi0_evt_handler(
                nrfx_twi_evt_t  const*  p_event,
                void*                   p_context) {

    _nrfx_twi_evt_handler(&_i2c_master_handle_0.nordicCallbackData, p_event, p_context);
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
static void _nrfx_twi1_evt_handler(
                nrfx_twi_evt_t  const*  p_event,
                void*                   p_context) {

    _nrfx_twi_evt_handler(&_i2c_master_handle_1.nordicCallbackData, p_event, p_context);
}
#endif


/******************* BUS implementation functs */

#define __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(                            \
                i2cMasterPrefix,                                                                    \
                i2cMaster,                                                                          \
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
                &i2cConfig,                                                                         \
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
                &i2cConfig,                                                                         \
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
                &i2cConfig,                                                                         \
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
        return tommRoCHwTemplateBusI2CNordicHalSetForLowPowerEnter(                                 \
                i2cConfig.sclPin,                                                                   \
                i2cConfig.sdaPin);                                                                  \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _i2c_master_ ## i2cMasterPrefix ## _low_power_exit_ARM(            \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusI2CNordicHalSetForLowPowerExit(                                  \
                i2cConfig.sclPin,                                                                   \
                i2cConfig.sdaPin);                                                                  \
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
    __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(I2C0, TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_0, _i2c_master_config_0, _i2c_master_handle_0);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(I2C1, TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_1, _i2c_master_config_1, _i2c_master_handle_1);
#endif


/******************* BUS set prop functs */

static nrf_twi_frequency_t _frequency_convert(const uint32_t frequencyU32) {

    switch (frequencyU32) {

    case 100000UL:  return NRF_TWI_FREQ_100K;
    case 250000UL:  return NRF_TWI_FREQ_250K;
    case 400000UL:  return NRF_TWI_FREQ_400K;

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;

    }

    return __DEFAULT_FREQUENCY__;
}

static tommRoC_hw_err_enum_t _set_baudrate(
        const   tommRoC_hw_template_bus_i2c_master_enum_t           bus,
        const   uint32_t*                                   const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_0:
        _i2c_master_config_0.frequency = _frequency_convert(*propValuePtr);
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_1:
        _i2c_master_config_1.frequency = _frequency_convert(*propValuePtr);
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_sda_pin(
        const   tommRoC_hw_template_bus_i2c_master_enum_t           bus,
        const   uint32_t*                                   const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_0:
        _i2c_master_config_0.sdaPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_1:
        _i2c_master_config_1.sdaPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_scl_pin(
        const   tommRoC_hw_template_bus_i2c_master_enum_t           bus,
        const   uint32_t*                                   const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_0:
        _i2c_master_config_0.sclPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_1:
        _i2c_master_config_1.sclPin = *propValuePtr;
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

    tommRoC_hw_template_bus_i2c_nordic_hal_config_t halConfig;

    halConfig.nrfxTwi.p_twi         = NRF_TWI0;
    halConfig.nrfxTwi.drv_inst_idx  = NRFX_TWI0_INST_IDX;
    halConfig.frequency             = _i2c_master_config_0.frequency;
    halConfig.sclPin                = _i2c_master_config_0.sclPin;
    halConfig.sdaPin                = _i2c_master_config_0.sdaPin;
    halConfig.nrfxTwiEvtHandler     = _nrfx_twi0_evt_handler;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusI2CNordicHalMasterInit(&halConfig));

    _i2c_master_I2C0_get_callback_ARM(cbFunctPtr);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&_i2c_master_handle_0.nrfxTwi, &halConfig.nrfxTwi, sizeof(nrfx_twi_t)));

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {
}
#endif

#endif

#endif

#endif

