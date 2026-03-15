
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentI2CMaster.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

#include "bus/common/i2c/master/tommRoCHwTemplateBusCommonI2CMasterCb.h"

#include "bus/env/arm/NXP/i2c/tommRoCHwTemplateBusI2CNXPHal.h"
#include "bus/env/arm/NXP/i2c/tommRoCHwTemplateBusI2CNXPLocation.h"

#include "TOMMROCMw.h"
#include "TOMMROCMwTemplate.h"

#if defined (FSL_FEATURE_SOC_I2C_COUNT) && FSL_FEATURE_SOC_I2C_COUNT
#include "fsl_i2c.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __DEFAULT_BAUDRATE__            (100000)
#define __DEFAULT_ROUTE_LOCATION__      (TOMMROC_HW_TEMPLATE_LOCATION_0)
#define __DEFAULT_MCU_PULL_UP_STATUS__  (TOMMRO_C_UTIL_DISABLED)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    uint32_t                                baudRate;
    tommRoC_hw_template_bus_location_enum_t location;
    tommRoC_util_enabled_status_enum_t      mcuPullUpStatus;

} __tommRoC_hw_i2c_master_config_t__;

#define __EMPTY___tommRoC_hw_i2c_master_config_t____        \
{                                                           \
    /* .baudRate */         __DEFAULT_BAUDRATE__,           \
    /* .location */         __DEFAULT_ROUTE_LOCATION__,     \
    /* .mcuPullUpStatus */  __DEFAULT_MCU_PULL_UP_STATUS__, \
}

typedef struct {

    bool        cbCalled;
    status_t    transferStatus;

} __nxp_callback_data_t__;

#define __EMPTY___nxp_callback_data_t____                   \
{                                                           \
    /* .cbCalled */         false,                          \
    /* .transferStatus */   kStatus_NoTransferInProgress,   \
}

typedef struct {

    void*                               i2cPtr;
    i2c_master_handle_t*                nxpI2CMasterHandlePtr;
    volatile __nxp_callback_data_t__    nxpCallbackData;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    tommRoC_mw_template_semaphore_t     syncSem;
#endif

} __tommRoC_hw_i2c_master_handle_t__;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
#define __EMPTY___tommRoC_hw_i2c_master_handle_t____                                \
{                                                                                   \
    /* .i2cPtr */                   NULL,                                           \
    /* .nxpI2CMasterHandlePtr */    NULL,                                           \
    /* .nxpCallbackData */          __EMPTY___nxp_callback_data_t____,              \
    /* .syncSem */                  __EMPTY___tommRoC_mw_template_semaphore_t____,  \
}
#else
#define __EMPTY___tommRoC_hw_i2c_master_handle_t____                    \
{                                                                       \
    /* .i2cPtr */                   NULL,                               \
    /* .nxpI2CMasterHandlePtr */    NULL,                               \
    /* .nxpCallbackData */          __EMPTY___nxp_callback_data_t____,  \
}
#endif

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
static i2c_master_handle_t _nxp_i2c_master_handle_0;
static __tommRoC_hw_i2c_master_config_t__ _i2c_master_config_0 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_i2c_master_config_t__);
static __tommRoC_hw_i2c_master_handle_t__ _i2c_master_handle_0 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_i2c_master_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
static i2c_master_handle_t _nxp_i2c_master_handle_1;
static __tommRoC_hw_i2c_master_config_t__ _i2c_master_config_1 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_i2c_master_config_t__);
static __tommRoC_hw_i2c_master_handle_t__ _i2c_master_handle_1 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_i2c_master_handle_t__);
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if defined (FSL_FEATURE_SOC_I2C_COUNT) && FSL_FEATURE_SOC_I2C_COUNT
static void _i2c_master_transfer_callback(I2C_Type *base, i2c_master_handle_t *handle, status_t status, void *userData) {

    __tommRoC_hw_i2c_master_handle_t__* i2cHandlePtr = (__tommRoC_hw_i2c_master_handle_t__*) userData;

    TOMMROC_UTIL_UNUSED_PARAM(base);
    TOMMROC_UTIL_UNUSED_PARAM(handle);

    i2cHandlePtr->nxpCallbackData.transferStatus    = status;
    i2cHandlePtr->nxpCallbackData.cbCalled          = true;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwSemaphoreRelease(&i2cHandlePtr->syncSem));
#endif
}

static tommRoC_hw_err_enum_t _wait_for_transfer_complete(
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
        const   uint32_t                                    timeoutMsec) {

    I2C_Type* i2cTypePtr = (I2C_Type*) i2cHandlePtr->i2cPtr;

#if !defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    tommRoC_timer_t timer;
    uint32_t elapsedMsec;
#endif

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)

    if (TOMMRO_C_MW_ERR_SUCCESS == tommRoCMwSemaphoreWait(&i2cHandlePtr->syncSem, timeoutMsec)) {
        if (i2cHandlePtr->nxpCallbackData.cbCalled) {
            if ((status_t) kStatus_Success == i2cHandlePtr->nxpCallbackData.transferStatus) {
                return TOMMRO_C_HW_ERR_SUCCESS;
            }
        }
    }

    // NOTE: in case of timeout expired, check again if SUCCESS because it could be the case in multitask environment
    if ((i2cHandlePtr->nxpCallbackData.cbCalled) && ((status_t) kStatus_Success == i2cHandlePtr->nxpCallbackData.transferStatus)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    if (!i2cHandlePtr->nxpCallbackData.cbCalled || (kStatus_I2C_Nak == i2cHandlePtr->nxpCallbackData.transferStatus)) {
        I2C_MasterTransferAbort(i2cTypePtr, i2cHandlePtr->nxpI2CMasterHandlePtr);
    }

    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
#else

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, timeoutMsec));

    do {

        if (i2cHandlePtr->nxpCallbackData.cbCalled) {
            if ((status_t) kStatus_Success == i2cHandlePtr->nxpCallbackData.transferStatus) {
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
    if ((i2cHandlePtr->nxpCallbackData.cbCalled) && ((status_t) kStatus_Success == i2cHandlePtr->nxpCallbackData.transferStatus)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    if (!i2cHandlePtr->nxpCallbackData.cbCalled || (kStatus_I2C_Nak == i2cHandlePtr->nxpCallbackData.transferStatus)) {
        I2C_MasterTransferAbort(i2cTypePtr, i2cHandlePtr->nxpI2CMasterHandlePtr);
    }

    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
#endif
}

static tommRoC_hw_err_enum_t _i2c_master_transfer(
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
                i2c_master_transfer_t*              const   masterXferPtr,
        const   uint32_t                                    timeoutMsec) {

    static const __nxp_callback_data_t__ nxpCallbackDataEmpty = TOMMROC_UTIL_EMPTY_VARIABLE(__nxp_callback_data_t__);

    I2C_Type* i2cTypePtr = (I2C_Type*) i2cHandlePtr->i2cPtr;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy((void*) &i2cHandlePtr->nxpCallbackData, &nxpCallbackDataEmpty, sizeof(nxpCallbackDataEmpty)));

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    // NOTE: call semaphore wait in order to "clean" possible old released semaphore
    while (TOMMRO_C_MW_ERR_SUCCESS == tommRoCMwSemaphoreWait(&i2cHandlePtr->syncSem, WAIT_SEMAPHORE_NO_WAIT_TIMEOUT)) ;
#endif

    if (kStatus_Success != I2C_MasterTransferNonBlocking(i2cTypePtr, i2cHandlePtr->nxpI2CMasterHandlePtr, masterXferPtr)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_wait_for_transfer_complete(i2cHandlePtr, timeoutMsec));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _i2c_master_write_transfer(
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
        const   uint8_t                                     slaveAddress7Bit,
        const   uint8_t*                            const   writeBufferPtr,
        const   uint16_t                                    writeBufferLen,
        const   uint32_t                                    flags,
        const   uint32_t                                    timeoutMsec) {

    i2c_master_transfer_t masterXfer;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&masterXfer, 0, sizeof(masterXfer)));

    masterXfer.slaveAddress     = slaveAddress7Bit;
    masterXfer.direction        = kI2C_Write;
    masterXfer.subaddress       = 0;
    masterXfer.subaddressSize   = 0;
    masterXfer.data             = (uint8_t*) writeBufferPtr;
    masterXfer.dataSize         = (size_t) writeBufferLen;
    masterXfer.flags            = flags;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_i2c_master_transfer(i2cHandlePtr, &masterXfer, timeoutMsec));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _i2c_master_read_transfer(
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
        const   uint8_t                                     slaveAddress7Bit,
                uint8_t*                            const   readBufferPtr,
        const   uint16_t                                    toReadAmount,
        const   uint32_t                                    flags,
        const   uint32_t                                    timeoutMsec) {

    i2c_master_transfer_t masterXfer;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&masterXfer, 0, sizeof(masterXfer)));

    masterXfer.slaveAddress     = slaveAddress7Bit;
    masterXfer.direction        = kI2C_Read;
    masterXfer.subaddress       = 0;
    masterXfer.subaddressSize   = 0;
    masterXfer.data             = readBufferPtr;
    masterXfer.dataSize         = (size_t) toReadAmount;
    masterXfer.flags            = flags;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_i2c_master_transfer(i2cHandlePtr, &masterXfer, timeoutMsec));

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
    uint32_t flags;
    uint8_t idx;

    TOMMROC_UTIL_UNUSED_PARAM(i2cConfigPtr);

    for (idx = 0, writeBufferPtr = writeBuffersPtr; idx < writeBuffersAmount; ++idx, ++writeBufferPtr) {

        // NOTE: set to default as temporary fix. NXP SDK support only kI2C_TransferRepeatedStartFlag
        // TODO: to check if MK22 SDK support.
        flags = kI2C_TransferDefaultFlag;

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__)
        if (1 == writeBuffersAmount) {              // If single transfer -> default (START/STOP)
            flags = kI2C_TransferDefaultFlag;
        }
        else if (0 == idx) {                        // If first transfer -> START/NO STOP
            flags = kI2C_TransferNoStopFlag;
        }
        else if (writeBuffersAmount - 1 == idx) {   // If last transfer -> NO START/STOP
            flags = kI2C_TransferNoStartFlag ;
        }        
        else {                                      // NO START; NO STOP
            flags = kI2C_TransferNoStartFlag | kI2C_TransferNoStopFlag;
        }
#endif

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _i2c_master_write_transfer(
                        i2cHandlePtr,
                        slaveAddress7Bit,
                        writeBufferPtr->bufferPtr,
                        writeBufferPtr->toWriteAmount,
                        flags,
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
    uint32_t flags;
    uint8_t idx;

    uint8_t rdBuffer[32];
    uint16_t rdBufferLen;

    void* ptr;
    uint16_t bSize;

    TOMMROC_UTIL_UNUSED_PARAM(i2cConfigPtr);

    rdBufferLen = tommRoCHwBusReadBuffersTotalToReadData(readBuffersPtr, readBuffersAmount);

    if (rdBufferLen <= sizeof(rdBuffer)) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _i2c_master_read_transfer(
                        i2cHandlePtr,
                        slaveAddress7Bit,
                        rdBuffer,
                        rdBufferLen,
                        kI2C_TransferDefaultFlag,
                        timeoutPerByteMsec * tommRoCMathMax(1, rdBufferLen)));

        ptr     = rdBuffer;
        bSize   = rdBufferLen;
        for (idx = 0, readBufferPtr = readBuffersPtr; idx < readBuffersAmount; ++idx, ++readBufferPtr) {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilBufferExtractArray(ptr, bSize, readBufferPtr->bufferPtr, readBufferPtr->toReadAmount, &ptr, &bSize));
            *(readBufferPtr->readedAmountPtr) = readBufferPtr->toReadAmount;
        }

        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    for (idx = 0, readBufferPtr = readBuffersPtr; idx < readBuffersAmount; ++idx, ++readBufferPtr) {

        // TODO: as before.
        flags = kI2C_TransferDefaultFlag;

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _i2c_master_read_transfer(
                        i2cHandlePtr,
                        slaveAddress7Bit,
                        readBufferPtr->bufferPtr,
                        readBufferPtr->toReadAmount,
                        flags,
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

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _i2c_master_write_transfer(
                    i2cHandlePtr,
                    slaveAddress7Bit,
                    writeBufferPtr,
                    writeBufferLen,
                    kI2C_TransferNoStopFlag,
                    timeoutPerByteMsec * tommRoCMathMax(1, writeBufferLen)));

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(delayWriteToReadMsec));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _i2c_master_read_transfer(
                    i2cHandlePtr,
                    slaveAddress7Bit,
                    readBufferPtr,
                    toReadAmount,
                    kI2C_TransferRepeatedStartFlag,
                    timeoutPerByteMsec * tommRoCMathMax(1, toReadAmount)));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_low_power_enter(
        const   tommRoC_hw_template_bus_i2c_master_enum_t           i2cMaster,
        const   __tommRoC_hw_i2c_master_config_t__*         const   i2cConfigPtr) {

    tommRoC_hw_template_bus_i2c_nxp_location_t locationConfig;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwTemplateBusI2CNXPLocationGetMaster(
                    i2cMaster,
                    i2cConfigPtr->location,
                    &locationConfig));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusI2CNXPHalSetForLowPowerEnter(
                    &locationConfig,
                    i2cConfigPtr->mcuPullUpStatus));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_low_power_exit(
        const   tommRoC_hw_template_bus_i2c_master_enum_t           i2cMaster,
        const   __tommRoC_hw_i2c_master_config_t__*         const   i2cConfigPtr) {

    tommRoC_hw_template_bus_i2c_nxp_location_t locationConfig;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwTemplateBusI2CNXPLocationGetMaster(
                    i2cMaster,
                    i2cConfigPtr->location,
                    &locationConfig));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusI2CNXPHalSetForLowPowerExit(
                    &locationConfig,
                    i2cConfigPtr->mcuPullUpStatus));

    return TOMMRO_C_HW_ERR_SUCCESS;
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
        return _phy_low_power_enter(i2cMaster, &i2cConfig);                                         \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _i2c_master_ ## i2cMasterPrefix ## _low_power_exit_ARM(            \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return _phy_low_power_exit(i2cMaster, &i2cConfig);                                          \
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

static tommRoC_hw_err_enum_t _set_location(
        const   tommRoC_hw_template_bus_i2c_master_enum_t           bus,
        const   tommRoC_hw_template_bus_location_enum_t*    const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_0:
        _i2c_master_config_0.location = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_1:
        _i2c_master_config_1.location = *propValuePtr;
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

    case TOMMRO_C_HW_TEMPLATE_BUS_I2C_MASTER_PROP_LOCATION:
        return _set_location(bus, propValuePtr);

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

    I2C_Type* const i2cBase[] = I2C_BASE_PTRS;

    i2c_master_config_t config;
    tommRoC_hw_template_bus_i2c_nxp_hal_config_t halConfig;

    I2C_MasterGetDefaultConfig(&config);

    config.baudRate_Bps = _i2c_master_config_0.baudRate;

    halConfig.i2cPtr            = (void*) i2cBase[0];
    halConfig.configPtr         = (void*) &config;
#if defined (I2C0_CLK_SRC)
    halConfig.clockName         = I2C0_CLK_SRC;
#else
    halConfig.clockName         = kCLOCK_BusClk;
#endif
    halConfig.mcuPullUpStatus   = _i2c_master_config_0.mcuPullUpStatus;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwTemplateBusI2CNXPLocationGetMaster(
                    TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_0,
                    _i2c_master_config_0.location,
                    &halConfig.location));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusI2CNXPHalMasterInit(&halConfig));

    _i2c_master_I2C0_get_callback_ARM(cbFunctPtr);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&_nxp_i2c_master_handle_0, 0, sizeof(i2c_master_handle_t)));

    _i2c_master_handle_0.i2cPtr                 = halConfig.i2cPtr;
    _i2c_master_handle_0.nxpI2CMasterHandlePtr  = &_nxp_i2c_master_handle_0;

    I2C_MasterTransferCreateHandle(i2cBase[0], &_nxp_i2c_master_handle_0, _i2c_master_transfer_callback, (void*) &_i2c_master_handle_0);

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
    tommRoCMwSemaphoreCreate(&_i2c_master_handle_0.syncSem, 0),
    TOMMRO_C_HW_LOW_LEVEL_ERR);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    I2C_Type* const i2cBase[] = I2C_BASE_PTRS;

    i2c_master_config_t config;
    tommRoC_hw_template_bus_i2c_nxp_hal_config_t halConfig;

    I2C_MasterGetDefaultConfig(&config);

    config.baudRate_Bps = _i2c_master_config_1.baudRate;

    halConfig.i2cPtr            = (void*) i2cBase[1];
    halConfig.configPtr         = (void*) &config;
#if defined (I2C1_CLK_SRC)
    halConfig.clockName         = I2C1_CLK_SRC;
#else
    halConfig.clockName         = kCLOCK_BusClk;
#endif
    halConfig.mcuPullUpStatus   = _i2c_master_config_1.mcuPullUpStatus;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwTemplateBusI2CNXPLocationGetMaster(
                    TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_1,
                    _i2c_master_config_1.location,
                    &halConfig.location));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusI2CNXPHalMasterInit(&halConfig));

    _i2c_master_I2C1_get_callback_ARM(cbFunctPtr);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&_nxp_i2c_master_handle_1, 0, sizeof(i2c_master_handle_t)));

    _i2c_master_handle_1.i2cPtr                 = halConfig.i2cPtr;
    _i2c_master_handle_1.nxpI2CMasterHandlePtr  = &_nxp_i2c_master_handle_1;

    I2C_MasterTransferCreateHandle(i2cBase[1], &_nxp_i2c_master_handle_1, _i2c_master_transfer_callback, (void*) &_i2c_master_handle_1);

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
    tommRoCMwSemaphoreCreate(&_i2c_master_handle_1.syncSem, 0),
    TOMMRO_C_HW_LOW_LEVEL_ERR);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif

#endif
