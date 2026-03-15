
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentI2CMaster.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

#include "bus/common/i2c/master/tommRoCHwTemplateBusCommonI2CMasterCb.h"

#include "bus/env/arm/SiLabs/i2c/tommRoCHwTemplateBusI2CSiLabsHal.h"
#include "bus/env/arm/SiLabs/i2c/tommRoCHwTemplateBusI2CSiLabsLocation.h"

#include "TOMMROCMwTemplate.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __DEFAULT_BAUDRATE__            (100000)
#define __DEFAULT_MCU_PULL_UP_STATUS__  (TOMMRO_C_UTIL_DISABLED)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    uint32_t                                        baudRate;
    tommRoC_hw_template_bus_i2c_silabs_location_t   siLabsLocation;
    tommRoC_util_enabled_status_enum_t              mcuPullUpStatus;

} __tommRoC_hw_i2c_master_config_t__;

#define __EMPTY___tommRoC_hw_i2c_master_config_t____                                    \
{                                                                                       \
    /* .baudRate */         __DEFAULT_BAUDRATE__,                                       \
    /* .siLabsLocation */   __EMPTY_tommRoC_hw_template_bus_i2c_silabs_location_t__,    \
    /* .mcuPullUpStatus */  __DEFAULT_MCU_PULL_UP_STATUS__,                             \
}

typedef struct {

    void*                       i2cPtr;
    I2C_TransferReturn_TypeDef  i2cStatus;

} __tommRoC_hw_i2c_master_handle_t__;

#define __EMPTY___tommRoC_hw_i2c_master_handle_t____    \
{                                                       \
    /* .i2cPtr */           NULL,                       \
    /* .i2cStatus */        i2cTransferSwFault,         \
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
#if defined (I2C_PRESENT) && I2C_COUNT
static tommRoC_hw_err_enum_t _i2c_master_transfer(
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
                I2C_TransferSeq_TypeDef*            const   transferSeqPtr,
        const   uint32_t                                    timeoutMsec) {

    I2C_TypeDef* i2cTypePtr = (I2C_TypeDef*) i2cHandlePtr->i2cPtr;
    volatile I2C_TransferReturn_TypeDef* i2cStatusPtr = &i2cHandlePtr->i2cStatus;

    tommRoC_timer_t timer;
    uint32_t elapsedMsec;

    // Do a polled transfer
    *i2cStatusPtr = I2C_TransferInit(i2cTypePtr, transferSeqPtr);
    if (i2cTransferInProgress != *i2cStatusPtr) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, timeoutMsec));

    do {

        if (i2cTransferDone == *i2cStatusPtr) {
            return TOMMRO_C_HW_ERR_SUCCESS;
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
    if (i2cTransferDone == *i2cStatusPtr) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
    
    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
}

static tommRoC_hw_err_enum_t _i2c_master_write_transfer(
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
        const   uint8_t                                     slaveAddress7Bit,
        const   uint8_t*                            const   writeBufferPtr,
        const   uint16_t                                    writeBufferLen,
        const   uint32_t                                    timeoutMsec) {
            
    I2C_TransferSeq_TypeDef transferSeq;

    transferSeq.addr        = (uint16_t) slaveAddress7Bit << 1;
    transferSeq.flags       = I2C_FLAG_WRITE;
    transferSeq.buf[0].data = (uint8_t*) writeBufferPtr;
    transferSeq.buf[0].len  = writeBufferLen;
    transferSeq.buf[1].data = NULL;
    transferSeq.buf[1].len  = 0;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_i2c_master_transfer(i2cHandlePtr, &transferSeq, timeoutMsec));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _i2c_master_write_write_transfer(
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
        const   uint8_t                                     slaveAddress7Bit,
        const   uint8_t*                            const   writeBuffer1Ptr,
        const   uint16_t                                    writeBuffer1Len,
        const   uint8_t*                            const   writeBuffer2Ptr,
        const   uint16_t                                    writeBuffer2Len,
        const   uint32_t                                    timeoutMsec) {

    I2C_TransferSeq_TypeDef transferSeq;

    transferSeq.addr        = (uint16_t) slaveAddress7Bit << 1;
    transferSeq.flags       = I2C_FLAG_WRITE_WRITE;
    transferSeq.buf[0].data = (uint8_t*) writeBuffer1Ptr;
    transferSeq.buf[0].len  = writeBuffer1Len;
    transferSeq.buf[1].data = (uint8_t*) writeBuffer2Ptr;
    transferSeq.buf[1].len  = writeBuffer2Len;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_i2c_master_transfer(i2cHandlePtr, &transferSeq, timeoutMsec));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _i2c_master_read_transfer(
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
        const   uint8_t                                     slaveAddress7Bit,
                uint8_t*                            const   readBufferPtr,
        const   uint16_t                                    toReadAmount,
        const   uint32_t                                    timeoutMsec) {
            
    I2C_TransferSeq_TypeDef transferSeq;

    transferSeq.addr        = (uint16_t) slaveAddress7Bit << 1;
    transferSeq.flags       = I2C_FLAG_READ;
    transferSeq.buf[0].data = readBufferPtr;
    transferSeq.buf[0].len  = toReadAmount;
    transferSeq.buf[1].data = NULL;
    transferSeq.buf[1].len  = 0;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_i2c_master_transfer(i2cHandlePtr, &transferSeq, timeoutMsec));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _i2c_master_write_read_transfer(
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
        const   uint8_t                                     slaveAddress7Bit,
        const   uint8_t*                            const   writeBufferPtr,
        const   uint16_t                                    writeBufferLen,
                uint8_t*                            const   readBufferPtr,
        const   uint16_t                                    toReadAmount,
        const   uint32_t                                    timeoutMsec) {

    I2C_TransferSeq_TypeDef transferSeq;

    transferSeq.addr        = (uint16_t) slaveAddress7Bit << 1;
    transferSeq.flags       = I2C_FLAG_WRITE_READ;
    transferSeq.buf[0].data = (uint8_t*) writeBufferPtr;
    transferSeq.buf[0].len  = writeBufferLen;
    transferSeq.buf[1].data = readBufferPtr;
    transferSeq.buf[1].len  = toReadAmount;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_i2c_master_transfer(i2cHandlePtr, &transferSeq, timeoutMsec));

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
    uint8_t toSendBuffAmount;
    uint8_t index;

    TOMMROC_UTIL_UNUSED_PARAM(i2cConfigPtr);

    for (index = 0, writeBufferPtr = writeBuffersPtr; index < writeBuffersAmount; index += toSendBuffAmount, writeBufferPtr += toSendBuffAmount) {

        toSendBuffAmount = tommRoCMathMin(2, writeBuffersAmount - index);

        if (toSendBuffAmount < 2) {

            TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                    _i2c_master_write_transfer(
                            i2cHandlePtr,
                            slaveAddress7Bit,
                            writeBufferPtr->bufferPtr,
                            writeBufferPtr->toWriteAmount,
                            timeoutPerByteMsec * tommRoCMathMax(1, writeBufferPtr->toWriteAmount)));
        }
        else {

            TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                    _i2c_master_write_write_transfer(
                            i2cHandlePtr,
                            slaveAddress7Bit,
                            writeBufferPtr->bufferPtr,
                            writeBufferPtr->toWriteAmount,
                            (writeBufferPtr + 1)->bufferPtr,
                            (writeBufferPtr + 1)->toWriteAmount,
                            timeoutPerByteMsec * tommRoCMathMax(1, writeBufferPtr->toWriteAmount + (writeBufferPtr + 1)->toWriteAmount)));
        }
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
                    timeoutPerByteMsec * tommRoCMathMax(1, writeBufferLen + toReadAmount)));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
void I2C0_IRQHandler(void) {
    // Get appropriate status
    _i2c_master_handle_0.i2cStatus = I2C_Transfer(I2C0);

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
void I2C1_IRQHandler(void) {
    // Get appropriate status
    _i2c_master_handle_1.i2cStatus = I2C_Transfer(I2C1);

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}
#endif
#endif

/******************* BUS implementation functs */

#define __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(                            \
                i2cMasterPrefix,                                                                    \
                i2cMaster,                                                                          \
                i2cConfig,                                                                          \
                i2cHandle,                                                                          \
                i2cClock)                                                                           \
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
        return tommRoCHwTemplateBusI2CSiLabsHalSetForLowPowerEnter(                                 \
                i2cClock,                                                                           \
                &i2cConfig.siLabsLocation,                                                          \
                i2cConfig.mcuPullUpStatus);                                                         \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _i2c_master_ ## i2cMasterPrefix ## _low_power_exit_ARM(            \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusI2CSiLabsHalSetForLowPowerExit(                                  \
                i2cClock,                                                                           \
                &i2cConfig.siLabsLocation,                                                          \
                i2cConfig.mcuPullUpStatus);                                                         \
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
    __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(I2C0, TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_0, _i2c_master_config_0, _i2c_master_handle_0, cmuClock_I2C0);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(I2C1, TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_1, _i2c_master_config_1, _i2c_master_handle_1, cmuClock_I2C1);
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

#if defined (_I2C_ROUTE_LOCATION_MASK)
static tommRoC_hw_err_enum_t _set_location(
        const   tommRoC_hw_template_bus_i2c_master_enum_t           bus,
        const   tommRoC_hw_template_bus_location_enum_t*    const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_0:
        return tommRoCHwTemplateBusI2CSiLabsLocationGetMaster(bus, *propValuePtr, &_i2c_master_config_0.siLabsLocation);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_1:
        return tommRoCHwTemplateBusI2CSiLabsLocationGetMaster(bus, *propValuePtr, &_i2c_master_config_1.siLabsLocation);
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

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

#if defined (_GPIO_I2C_ROUTEEN_RESETVALUE)
static tommRoC_hw_err_enum_t _set_sda_port(
        const   tommRoC_hw_template_bus_i2c_master_enum_t           bus,
        const   GPIO_Port_TypeDef*                          const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_0:
        _i2c_master_config_0.siLabsLocation.gpioSDAPort = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_1:
        _i2c_master_config_1.siLabsLocation.gpioSDAPort = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_scl_port(
        const   tommRoC_hw_template_bus_i2c_master_enum_t           bus,
        const   GPIO_Port_TypeDef*                          const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_0:
        _i2c_master_config_0.siLabsLocation.gpioSCLPort = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_1:
        _i2c_master_config_1.siLabsLocation.gpioSCLPort = *propValuePtr;
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
        _i2c_master_config_0.siLabsLocation.gpioSDAPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_1:
        _i2c_master_config_1.siLabsLocation.gpioSDAPin = *propValuePtr;
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
        _i2c_master_config_0.siLabsLocation.gpioSCLPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_1:
        _i2c_master_config_1.siLabsLocation.gpioSCLPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif


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

#if defined (_I2C_ROUTE_LOCATION_MASK)
    case TOMMRO_C_HW_TEMPLATE_BUS_I2C_MASTER_PROP_LOCATION:
        return _set_location(bus, propValuePtr);
#endif

    case TOMMRO_C_HW_TEMPLATE_BUS_I2C_MASTER_PROP_MCU_PULL_UP_STATUS:
        return _set_mcu_pull_up_status(bus, propValuePtr);

#if defined (_GPIO_I2C_ROUTEEN_RESETVALUE)
    case TOMMRO_C_HW_TEMPLATE_BUS_I2C_MASTER_PROP_SDA_PORT:
        return _set_sda_port(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_I2C_MASTER_PROP_SCL_PORT:
        return _set_scl_port(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_I2C_MASTER_PROP_SDA_PIN:
        return _set_sda_pin(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_I2C_MASTER_PROP_SCL_PIN:
        return _set_scl_pin(bus, propValuePtr);
#endif

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

    tommRoC_hw_template_bus_i2c_silabs_hal_config_t halConfig;

    halConfig.clock             = cmuClock_I2C0;
    halConfig.i2cPtr            = (void*) I2C0;
    halConfig.baudRate          = _i2c_master_config_0.baudRate;
    halConfig.IRQn              = I2C0_IRQn;
    halConfig.mcuPullUpStatus   = _i2c_master_config_0.mcuPullUpStatus;
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&halConfig.location, &_i2c_master_config_0.siLabsLocation, sizeof(tommRoC_hw_template_bus_i2c_silabs_location_t)));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusI2CSiLabsHalMasterInit(&halConfig));

    _i2c_master_I2C0_get_callback_ARM(cbFunctPtr);

    _i2c_master_handle_0.i2cPtr = halConfig.i2cPtr;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster1Start(
        tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    tommRoC_hw_template_bus_i2c_silabs_hal_config_t halConfig;

    halConfig.clock             = cmuClock_I2C1;
    halConfig.i2cPtr            = (void*) I2C1;
    halConfig.baudRate          = _i2c_master_config_1.baudRate;
    halConfig.IRQn              = I2C1_IRQn;
    halConfig.mcuPullUpStatus   = _i2c_master_config_1.mcuPullUpStatus;
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&halConfig.location, &_i2c_master_config_1.siLabsLocation, sizeof(tommRoC_hw_template_bus_i2c_silabs_location_t)));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusI2CSiLabsHalMasterInit(&halConfig));

    _i2c_master_I2C1_get_callback_ARM(cbFunctPtr);

    _i2c_master_handle_1.i2cPtr = halConfig.i2cPtr;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif

#endif
