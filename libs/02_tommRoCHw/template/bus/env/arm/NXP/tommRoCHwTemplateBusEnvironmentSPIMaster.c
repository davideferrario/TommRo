
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentSPIMaster.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

#include "bus/common/spi/master/tommRoCHwTemplateBusCommonSPIMasterCb.h"

#include "bus/env/arm/NXP/spi/tommRoCHwTemplateBusSPINXPHal.h"
#include "bus/env/arm/NXP/spi/tommRoCHwTemplateBusSPINXPLocation.h"

#if defined (FSL_FEATURE_SOC_SPI_COUNT) && FSL_FEATURE_SOC_SPI_COUNT &&  \
    defined (FSL_FEATURE_SOC_DSPI_COUNT) && FSL_FEATURE_SOC_DSPI_COUNT
#error "Library not compatible with both SPI and DSPI"
#endif

#include "TOMMROCMw.h"
#include "TOMMROCMwTemplate.h"

#if defined (FSL_FEATURE_SOC_SPI_COUNT) && FSL_FEATURE_SOC_SPI_COUNT
#include "fsl_spi.h"
#endif

#if defined (FSL_FEATURE_SOC_DSPI_COUNT) && FSL_FEATURE_SOC_DSPI_COUNT
#include "fsl_dspi.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __DEFAULT_MODE__                (TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_0)
#define __DEFAULT_BAUDRATE__            (500000)
#define __DEFAULT_ROUTE_LOCATION__      (TOMMROC_HW_TEMPLATE_LOCATION_0)

#if defined (FSL_FEATURE_SOC_SPI_COUNT) && FSL_FEATURE_SOC_SPI_COUNT
#define __master_handle_t__             spi_master_handle_t
#define __transfer_t__                  spi_transfer_t
#define __master_config_t__             spi_master_config_t
#define __slave_config_t__              spi_slave_config_t
#define __MasterTransferCreateHandle__  SPI_MasterTransferCreateHandle
#define __MasterTransferNonBlocking__   SPI_MasterTransferNonBlocking
#define __MasterTransferAbort__         SPI_MasterTransferAbort
#define __MasterGetDefaultConfig__      SPI_MasterGetDefaultConfig
#endif

#if defined (FSL_FEATURE_SOC_DSPI_COUNT) && FSL_FEATURE_SOC_DSPI_COUNT
#define __master_handle_t__             dspi_master_handle_t
#define __transfer_t__                  dspi_transfer_t
#define __master_config_t__             dspi_master_config_t
#define __slave_config_t__              dspi_slave_config_t
#define __MasterTransferCreateHandle__  DSPI_MasterTransferCreateHandle
#define __MasterTransferNonBlocking__   DSPI_MasterTransferNonBlocking
#define __MasterTransferAbort__         DSPI_MasterTransferAbort
#define __MasterGetDefaultConfig__      DSPI_MasterGetDefaultConfig
#endif

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    tommRoC_hw_template_bus_spi_master_mode_t   mode;
    uint32_t                                    baudRate;
    tommRoC_hw_template_bus_location_enum_t     location;

} __tommRoC_hw_spi_master_config_t__;

#define __EMPTY___tommRoC_hw_spi_master_config_t____    \
{                                                       \
    /* .mode */         __DEFAULT_MODE__,               \
    /* .baudRate */     __DEFAULT_BAUDRATE__,           \
    /* .location */     __DEFAULT_ROUTE_LOCATION__,     \
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

    void*                               spiPtr;
    __master_handle_t__*                nxpSPIMasterHandlePtr;
    volatile __nxp_callback_data_t__    nxpCallbackData;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    tommRoC_mw_template_semaphore_t     syncSem;
#endif

} __tommRoC_hw_spi_master_handle_t__;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
#define __EMPTY___tommRoC_hw_spi_master_handle_t____                                \
{                                                                                   \
    /* .spiPtr */                   NULL,                                           \
    /* .nxpSPIMasterHandlePtr */    NULL,                                           \
    /* .nxpCallbackData */          __EMPTY___nxp_callback_data_t____,              \
    /* .syncSem */                  __EMPTY___tommRoC_mw_template_semaphore_t____,  \
}
#else
#define __EMPTY___tommRoC_hw_spi_master_handle_t____                    \
{                                                                       \
    /* .spiPtr */                   NULL,                               \
    /* .nxpSPIMasterHandlePtr */    NULL,                               \
    /* .nxpCallbackData */          __EMPTY___nxp_callback_data_t____,  \
}
#endif

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
static __master_handle_t__ _nxp_spi_master_handle_0;
static __tommRoC_hw_spi_master_config_t__ _spi_master_config_0 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_spi_master_config_t__);
static __tommRoC_hw_spi_master_handle_t__ _spi_master_handle_0 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_spi_master_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
static __master_handle_t__ _nxp_spi_master_handle_1;
static __tommRoC_hw_spi_master_config_t__ _spi_master_config_1 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_spi_master_config_t__);
static __tommRoC_hw_spi_master_handle_t__ _spi_master_handle_1 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_spi_master_handle_t__);
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if (defined (FSL_FEATURE_SOC_SPI_COUNT) && FSL_FEATURE_SOC_SPI_COUNT) || (defined (FSL_FEATURE_SOC_DSPI_COUNT) && FSL_FEATURE_SOC_DSPI_COUNT)
static void _spi_master_transfer_callback(SPI_Type *base, __master_handle_t__ *handle, status_t status, void *userData) {

    __tommRoC_hw_spi_master_handle_t__* spiHandlePtr = (__tommRoC_hw_spi_master_handle_t__*) userData;

    TOMMROC_UTIL_UNUSED_PARAM(base);
    TOMMROC_UTIL_UNUSED_PARAM(handle);

    spiHandlePtr->nxpCallbackData.transferStatus    = status;
    spiHandlePtr->nxpCallbackData.cbCalled          = true;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwSemaphoreRelease(&spiHandlePtr->syncSem));
#endif
}

static tommRoC_hw_err_enum_t _wait_for_transfer_complete(
                __tommRoC_hw_spi_master_handle_t__* const   spiHandlePtr,
        const   uint32_t                                    timeoutMsec) {

    SPI_Type* spiTypePtr = (SPI_Type*) spiHandlePtr->spiPtr;

#if !defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    tommRoC_timer_t timer;
    uint32_t elapsedMsec;
#endif

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)

    if (TOMMRO_C_MW_ERR_SUCCESS == tommRoCMwSemaphoreWait(&spiHandlePtr->syncSem, timeoutMsec)) {
        if (spiHandlePtr->nxpCallbackData.cbCalled) {
            if ((status_t) kStatus_Success == spiHandlePtr->nxpCallbackData.transferStatus) {
                return TOMMRO_C_HW_ERR_SUCCESS;
            }
#if defined (FSL_FEATURE_SOC_SPI_COUNT) && FSL_FEATURE_SOC_SPI_COUNT
            else if ((status_t) kStatus_SPI_Idle == spiHandlePtr->nxpCallbackData.transferStatus) {
                return TOMMRO_C_HW_ERR_SUCCESS;
            }
#endif
        }
    }

    // NOTE: in case of timeout expired, check again if SUCCESS because it could be the case in multitask environment
    if ((spiHandlePtr->nxpCallbackData.cbCalled) && ((status_t) kStatus_Success == spiHandlePtr->nxpCallbackData.transferStatus)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

#if defined (FSL_FEATURE_SOC_SPI_COUNT) && FSL_FEATURE_SOC_SPI_COUNT
    if ((spiHandlePtr->nxpCallbackData.cbCalled) && ((status_t) kStatus_SPI_Idle == spiHandlePtr->nxpCallbackData.transferStatus)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

    if (!spiHandlePtr->nxpCallbackData.cbCalled) {
        __MasterTransferAbort__(spiTypePtr, spiHandlePtr->nxpSPIMasterHandlePtr);
    }

    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
#else

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, timeoutMsec));

    do {

        if (spiHandlePtr->nxpCallbackData.cbCalled) {
            if ((status_t) kStatus_Success == spiHandlePtr->nxpCallbackData.transferStatus) {
                return TOMMRO_C_HW_ERR_SUCCESS;
            }

#if defined (FSL_FEATURE_SOC_SPI_COUNT) && FSL_FEATURE_SOC_SPI_COUNT
            else if ((status_t) kStatus_SPI_Idle == spiHandlePtr->nxpCallbackData.transferStatus) {
                return TOMMRO_C_HW_ERR_SUCCESS;
            }
#endif
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
    if ((spiHandlePtr->nxpCallbackData.cbCalled) && ((status_t) kStatus_Success == spiHandlePtr->nxpCallbackData.transferStatus)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

#if defined (FSL_FEATURE_SOC_SPI_COUNT) && FSL_FEATURE_SOC_SPI_COUNT
    if ((spiHandlePtr->nxpCallbackData.cbCalled) && ((status_t) kStatus_SPI_Idle == spiHandlePtr->nxpCallbackData.transferStatus)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

    if (!spiHandlePtr->nxpCallbackData.cbCalled) {
        __MasterTransferAbort__(spiTypePtr, spiHandlePtr->nxpSPIMasterHandlePtr);
    }

    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
#endif
}

static tommRoC_hw_err_enum_t _spi_master_transfer(
                __tommRoC_hw_spi_master_handle_t__* const   spiHandlePtr,
                __transfer_t__*                     const   masterXferPtr,
        const   uint32_t                                    timeoutMsec) {

    static const __nxp_callback_data_t__ nxpCallbackDataEmpty = TOMMROC_UTIL_EMPTY_VARIABLE(__nxp_callback_data_t__);

    SPI_Type* spiTypePtr = (SPI_Type*) spiHandlePtr->spiPtr;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy((void*) &spiHandlePtr->nxpCallbackData, &nxpCallbackDataEmpty, sizeof(nxpCallbackDataEmpty)));

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    // NOTE: call semaphore wait in order to "clean" possible old released semaphore
    while (TOMMRO_C_MW_ERR_SUCCESS == tommRoCMwSemaphoreWait(&spiHandlePtr->syncSem, WAIT_SEMAPHORE_NO_WAIT_TIMEOUT)) ;
#endif

    if (kStatus_Success != __MasterTransferNonBlocking__(spiTypePtr, spiHandlePtr->nxpSPIMasterHandlePtr, masterXferPtr)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_wait_for_transfer_complete(spiHandlePtr, timeoutMsec));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _spi_master_write_transfer(
                __tommRoC_hw_spi_master_handle_t__* const   spiHandlePtr,
        const   uint8_t*                            const   writeBufferPtr,
        const   uint16_t                                    writeBufferLen,
        const   uint32_t                                    timeoutMsec) {

    __transfer_t__ masterXfer;

    tommRoCUtilMemSet(&masterXfer, 0, sizeof(masterXfer));

    masterXfer.txData       = (uint8_t*) writeBufferPtr;
    masterXfer.rxData       = NULL;
    masterXfer.dataSize     = (size_t) writeBufferLen;
    // NOTE: for SPI, control flag is useless to.
#if defined (FSL_FEATURE_SOC_DSPI_COUNT) && FSL_FEATURE_SOC_DSPI_COUNT
    masterXfer.configFlags  = kDSPI_MasterCtar0 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;
#endif

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_spi_master_transfer(spiHandlePtr, &masterXfer, timeoutMsec));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _spi_master_read_transfer(
                __tommRoC_hw_spi_master_handle_t__* const   spiHandlePtr,
                uint8_t*                            const   readBufferPtr,
        const   uint16_t                                    toReadAmount,
        const   uint32_t                                    timeoutMsec) {

    __transfer_t__ masterXfer;

    tommRoCUtilMemSet(&masterXfer, 0, sizeof(masterXfer));

    masterXfer.txData       = NULL;
    masterXfer.rxData       = readBufferPtr;
    masterXfer.dataSize     = (size_t) toReadAmount;
    // NOTE: for SPI, control flag is useless to.
#if defined (FSL_FEATURE_SOC_DSPI_COUNT) && FSL_FEATURE_SOC_DSPI_COUNT
    masterXfer.configFlags  = kDSPI_MasterCtar0 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;
#endif

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_spi_master_transfer(spiHandlePtr, &masterXfer, timeoutMsec));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _spi_master_transceive_transfer(
                __tommRoC_hw_spi_master_handle_t__* const   spiHandlePtr,
        const   uint8_t*                            const   writeBufferPtr,
                uint8_t*                            const   readBufferPtr,
        const   uint16_t                                    bufferLength,
        const   uint32_t                                    timeoutMsec) {

    __transfer_t__ masterXfer;

    tommRoCUtilMemSet(&masterXfer, 0, sizeof(masterXfer));

    masterXfer.txData       = (uint8_t*) writeBufferPtr;
    masterXfer.rxData       = readBufferPtr;
    masterXfer.dataSize     = (size_t) bufferLength;
    // NOTE: for SPI, control flag is useless to.
#if defined (FSL_FEATURE_SOC_DSPI_COUNT) && FSL_FEATURE_SOC_DSPI_COUNT
    masterXfer.configFlags  = kDSPI_MasterCtar0 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;
#endif

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_spi_master_transfer(spiHandlePtr, &masterXfer, timeoutMsec));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_write_buffers(
                void*                       const   spiConfigPtr,
                void*                       const   spiHandlePtr,
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount,
        const   uint32_t                            timeoutPerByteMsec) {

    const tommRoC_hw_bus_write_buf_t* writeBufferPtr;
    uint8_t index;

    TOMMROC_UTIL_UNUSED_PARAM(spiConfigPtr);

    for (index = 0, writeBufferPtr = writeBuffersPtr; index < writeBuffersAmount; ++index, ++writeBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _spi_master_write_transfer(
                        spiHandlePtr,
                        writeBufferPtr->bufferPtr,
                        writeBufferPtr->toWriteAmount,
                        timeoutPerByteMsec * writeBufferPtr->toWriteAmount));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_read_buffers(
                void*                       const   spiConfigPtr,
                void*                       const   spiHandlePtr,
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   uint32_t                            timeoutPerByteMsec) {

    tommRoC_hw_bus_read_buf_t* readBufferPtr;
    uint8_t index;

    TOMMROC_UTIL_UNUSED_PARAM(spiConfigPtr);

    for (index = 0, readBufferPtr = readBuffersPtr; index < readBuffersAmount; ++index, ++readBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _spi_master_read_transfer(
                        spiHandlePtr,
                        readBufferPtr->bufferPtr,
                        readBufferPtr->toReadAmount,
                        timeoutPerByteMsec * readBufferPtr->toReadAmount));

        *(readBufferPtr->readedAmountPtr) = readBufferPtr->toReadAmount;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_transceive_buffer(
                void*                       const   spiConfigPtr,
                void*                       const   spiHandlePtr,
        const   uint8_t*                    const   writeBufferPtr,
                uint8_t*                    const   readBufferPtr,
        const   uint16_t                            bufferLength,
        const   uint32_t                            timeoutPerByteMsec) {

    TOMMROC_UTIL_UNUSED_PARAM(spiConfigPtr);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _spi_master_transceive_transfer(
                    spiHandlePtr,
                    writeBufferPtr,
                    readBufferPtr,
                    bufferLength,
                    timeoutPerByteMsec * bufferLength));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_low_power_enter(
        const   tommRoC_hw_template_bus_spi_master_enum_t   spiMaster,
        const   tommRoC_hw_template_bus_location_enum_t     location) {

    tommRoC_hw_template_bus_spi_nxp_location_t locationConfig;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwTemplateBusSPINXPLocationGetMaster(
                    spiMaster,
                    location,
                    &locationConfig));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusSPINXPHalSetForLowPowerEnter(
                    &locationConfig));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_low_power_exit(
        const   tommRoC_hw_template_bus_spi_master_enum_t   spiMaster,
        const   tommRoC_hw_template_bus_location_enum_t     location) {

    tommRoC_hw_template_bus_spi_nxp_location_t locationConfig;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwTemplateBusSPINXPLocationGetMaster(
                    spiMaster,
                    location,
                    &locationConfig));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusSPINXPHalSetForLowPowerExit(
                    &locationConfig));

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif


/******************* BUS implementation functs */

#define __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(                                \
                spiMasterPrefix,                                                                        \
                spiMaster,                                                                              \
                spiConfig,                                                                              \
                spiHandle)                                                                              \
                                                                                                        \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _write_buffers_ARM(                 \
            const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,                                \
            const   uint8_t                             writeBuffersAmount,                             \
            const   void*                       const   inputPtr,                                       \
                    void*                       const   resultPtr) {                                    \
                                                                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                           \
                                                                                                        \
        return tommRoCHwTemplateBusCommonSPIMasterCbWriteBuffers(                                       \
                writeBuffersPtr,                                                                        \
                writeBuffersAmount,                                                                     \
                &spiConfig,                                                                             \
                &spiHandle,                                                                             \
                _phy_write_buffers);                                                                    \
    }                                                                                                   \
                                                                                                        \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _read_buffers_ARM(                  \
                    tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,                                 \
            const   uint8_t                             readBuffersAmount,                              \
            const   void*                       const   inputPtr,                                       \
                    void*                       const   resultPtr) {                                    \
                                                                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                           \
                                                                                                        \
        return tommRoCHwTemplateBusCommonSPIMasterCbReadBuffers(                                        \
                readBuffersPtr,                                                                         \
                readBuffersAmount,                                                                      \
                &spiConfig,                                                                             \
                &spiHandle,                                                                             \
                _phy_read_buffers);                                                                     \
    }                                                                                                   \
                                                                                                        \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _transceive_buffer_ARM(             \
            const   uint8_t*                    const   writeBufferPtr,                                 \
                    uint8_t*                    const   readBufferPtr,                                  \
            const   uint16_t                            bufferLength,                                   \
            const   void*                       const   inputPtr,                                       \
                    void*                       const   resultPtr) {                                    \
                                                                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                           \
                                                                                                        \
        return tommRoCHwTemplateBusCommonSPIMasterCbTransceiveBuffer(                                   \
                writeBufferPtr,                                                                         \
                readBufferPtr,                                                                          \
                bufferLength,                                                                           \
                NULL,                                                                                   \
                &spiHandle,                                                                             \
                _phy_transceive_buffer);                                                                \
    }                                                                                                   \
                                                                                                        \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _clear_data_ARM(                    \
            const   void*                       const   inputPtr,                                       \
                    void*                       const   resultPtr) {                                    \
                                                                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                           \
                                                                                                        \
        return TOMMRO_C_HW_ERR_SUCCESS;                                                                 \
    }                                                                                                   \
                                                                                                        \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _low_power_enter_ARM(               \
            const   void*                       const   inputPtr,                                       \
                    void*                       const   resultPtr) {                                    \
                                                                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                           \
                                                                                                        \
        return _phy_low_power_enter(spiMaster, spiConfig.location);                                     \
    }                                                                                                   \
                                                                                                        \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _low_power_exit_ARM(                \
            const   void*                       const   inputPtr,                                       \
                    void*                       const   resultPtr) {                                    \
                                                                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                           \
                                                                                                        \
        return _phy_low_power_exit(spiMaster, spiConfig.location);                                      \
    }                                                                                                   \
                                                                                                        \
    static void _spi_master_ ## spiMasterPrefix ## _get_callback_ARM(                                   \
                    tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {                                   \
                                                                                                        \
        cbFunctPtr->writeBuffers        = _spi_master_ ## spiMasterPrefix ## _write_buffers_ARM;        \
        cbFunctPtr->readBuffers         = _spi_master_ ## spiMasterPrefix ## _read_buffers_ARM;         \
        cbFunctPtr->transceiveBuffer    = _spi_master_ ## spiMasterPrefix ## _transceive_buffer_ARM;    \
        cbFunctPtr->clearData           = _spi_master_ ## spiMasterPrefix ## _clear_data_ARM;           \
        cbFunctPtr->lowPowerEnter       = _spi_master_ ## spiMasterPrefix ## _low_power_enter_ARM;      \
        cbFunctPtr->lowPowerExit        = _spi_master_ ## spiMasterPrefix ## _low_power_exit_ARM;       \
    }

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(SPI0, TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0, _spi_master_config_0, _spi_master_handle_0);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(SPI1, TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1, _spi_master_config_1, _spi_master_handle_1);
#endif


/******************* BUS set prop functs */

static tommRoC_hw_err_enum_t _set_mode(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   tommRoC_hw_template_bus_spi_master_mode_t*  const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        _spi_master_config_0.mode = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _spi_master_config_1.mode = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_baudrate(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   uint32_t*                                   const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        _spi_master_config_0.baudRate = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _spi_master_config_1.baudRate = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_location(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   tommRoC_hw_template_bus_location_enum_t*    const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        _spi_master_config_0.location = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _spi_master_config_1.location = *propValuePtr;
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

#if defined (__TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_DEF_AT_LEAST_ONE_IS_USED__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMasterSetProp(
        const   tommRoC_hw_template_bus_spi_master_prop_enum_t          property,
        const   tommRoC_hw_template_bus_spi_master_enum_t               bus,
        const   void*                                           const   propValuePtr) {

    switch (property) {

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_MODE:
        return _set_mode(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_BAUD_RATE:
        return _set_baudrate(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_LOCATION:
        return _set_location(bus, propValuePtr);

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;
    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMaster0Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    SPI_Type* const spiBase[] = SPI_BASE_PTRS;

    __master_config_t__ config;
    tommRoC_hw_template_bus_spi_nxp_hal_config_t halConfig;

    __MasterGetDefaultConfig__(&config);

#if defined (FSL_FEATURE_SOC_DSPI_COUNT) && FSL_FEATURE_SOC_DSPI_COUNT

    config.ctarConfig.baudRate                      = _spi_master_config_0.baudRate;
    config.ctarConfig.pcsToSckDelayInNanoSec        = 1000000000U / _spi_master_config_0.baudRate;
    config.ctarConfig.lastSckToPcsDelayInNanoSec    = 1000000000U / _spi_master_config_0.baudRate;
    config.ctarConfig.betweenTransferDelayInNanoSec = 1000000000U / _spi_master_config_0.baudRate;

    switch (_spi_master_config_0.mode) {

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_0:
        config.ctarConfig.cpol = kDSPI_ClockPolarityActiveHigh;
        config.ctarConfig.cpha = kDSPI_ClockPhaseFirstEdge;
        break;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_1:
        config.ctarConfig.cpol = kDSPI_ClockPolarityActiveHigh;
        config.ctarConfig.cpha = kDSPI_ClockPhaseSecondEdge;
        break;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_2:
        config.ctarConfig.cpol = kDSPI_ClockPolarityActiveLow;
        config.ctarConfig.cpha = kDSPI_ClockPhaseFirstEdge;
        break;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_3:
        config.ctarConfig.cpol = kDSPI_ClockPolarityActiveLow;
        config.ctarConfig.cpha = kDSPI_ClockPhaseSecondEdge;
        break;

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);

        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
#endif

#if defined (FSL_FEATURE_SOC_SPI_COUNT) && FSL_FEATURE_SOC_SPI_COUNT

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
    config.outputMode = kSPI_SlaveSelectAsGpio;
#endif
    config.baudRate_Bps = _spi_master_config_0.baudRate;

    switch (_spi_master_config_0.mode) {

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_0:
        config.polarity = kSPI_ClockPolarityActiveHigh;
        config.phase    = kSPI_ClockPhaseFirstEdge;
        break;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_1:
        config.polarity = kSPI_ClockPolarityActiveHigh;
        config.phase    = kSPI_ClockPhaseSecondEdge;
        break;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_2:
        config.polarity = kSPI_ClockPolarityActiveLow;
        config.phase    = kSPI_ClockPhaseFirstEdge;
        break;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_3:
        config.polarity = kSPI_ClockPolarityActiveLow;
        config.phase    = kSPI_ClockPhaseSecondEdge;
        break;

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);

        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
#endif

    halConfig.spiPtr    = (void*) spiBase[0];
    halConfig.configPtr = (void*) &config;
#if defined (DSPI0_CLK_SRC)
    halConfig.clockName = DSPI0_CLK_SRC;
#elif defined (SPI0_CLK_SRC)
    halConfig.clockName = SPI0_CLK_SRC;
#else
    halConfig.clockName = kCLOCK_BusClk;
#endif

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwTemplateBusSPINXPLocationGetMaster(
                    TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0,
                    _spi_master_config_0.location,
                    &halConfig.location));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusSPINXPHalMasterInit(&halConfig));

    _spi_master_SPI0_get_callback_ARM(cbFunctPtr);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&_nxp_spi_master_handle_0, 0x00, sizeof(__master_handle_t__)));

    _spi_master_handle_0.spiPtr                 = halConfig.spiPtr;
    _spi_master_handle_0.nxpSPIMasterHandlePtr  = &_nxp_spi_master_handle_0;

    __MasterTransferCreateHandle__(spiBase[0], &_nxp_spi_master_handle_0, _spi_master_transfer_callback, (void*) &_spi_master_handle_0.nxpCallbackData);

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
    tommRoCMwSemaphoreCreate(&_spi_master_handle_0.syncSem, 0),
    TOMMRO_C_HW_LOW_LEVEL_ERR);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMaster1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    SPI_Type* const spiBase[] = SPI_BASE_PTRS;

    __master_config_t__ config;
    tommRoC_hw_template_bus_spi_nxp_hal_config_t halConfig;

    __MasterGetDefaultConfig__(&config);

#if defined (FSL_FEATURE_SOC_DSPI_COUNT) && FSL_FEATURE_SOC_DSPI_COUNT

    config.ctarConfig.baudRate                      = _spi_master_config_1.baudRate;
    config.ctarConfig.pcsToSckDelayInNanoSec        = 1000000000U / _spi_master_config_1.baudRate;
    config.ctarConfig.lastSckToPcsDelayInNanoSec    = 1000000000U / _spi_master_config_1.baudRate;
    config.ctarConfig.betweenTransferDelayInNanoSec = 1000000000U / _spi_master_config_1.baudRate;

    switch (_spi_master_config_1.mode) {

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_0:
        config.ctarConfig.cpol = kDSPI_ClockPolarityActiveHigh;
        config.ctarConfig.cpha = kDSPI_ClockPhaseFirstEdge;
        break;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_1:
        config.ctarConfig.cpol = kDSPI_ClockPolarityActiveHigh;
        config.ctarConfig.cpha = kDSPI_ClockPhaseSecondEdge;
        break;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_2:
        config.ctarConfig.cpol = kDSPI_ClockPolarityActiveLow;
        config.ctarConfig.cpha = kDSPI_ClockPhaseFirstEdge;
        break;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_3:
        config.ctarConfig.cpol = kDSPI_ClockPolarityActiveLow;
        config.ctarConfig.cpha = kDSPI_ClockPhaseSecondEdge;
        break;

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);

        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
#endif

#if defined (FSL_FEATURE_SOC_SPI_COUNT) && FSL_FEATURE_SOC_SPI_COUNT

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
    config.outputMode = kSPI_SlaveSelectAsGpio;
#endif
    config.baudRate_Bps = _spi_master_config_1.baudRate;

    switch (_spi_master_config_1.mode) {

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_0:
        config.polarity = kSPI_ClockPolarityActiveHigh;
        config.phase    = kSPI_ClockPhaseFirstEdge;
        break;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_1:
        config.polarity = kSPI_ClockPolarityActiveHigh;
        config.phase    = kSPI_ClockPhaseSecondEdge;
        break;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_2:
        config.polarity = kSPI_ClockPolarityActiveLow;
        config.phase    = kSPI_ClockPhaseFirstEdge;
        break;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_3:
        config.polarity = kSPI_ClockPolarityActiveLow;
        config.phase    = kSPI_ClockPhaseSecondEdge;
        break;

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);

        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
#endif

    halConfig.spiPtr    = (void*) spiBase[1];
    halConfig.configPtr = (void*) &config;
#if defined (DSPI1_CLK_SRC)
    halConfig.clockName = DSPI1_CLK_SRC;
#elif defined (SPI1_CLK_SRC)
    halConfig.clockName = SPI1_CLK_SRC;
#else
    halConfig.clockName = kCLOCK_BusClk;
#endif

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwTemplateBusSPINXPLocationGetMaster(
                    TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1,
                    _spi_master_config_1.location,
                    &halConfig.location));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusSPINXPHalMasterInit(&halConfig));

    _spi_master_SPI1_get_callback_ARM(cbFunctPtr);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&_nxp_spi_master_handle_1, 0x00, sizeof(__master_handle_t__)));

    _spi_master_handle_1.spiPtr                 = halConfig.spiPtr;
    _spi_master_handle_1.nxpSPIMasterHandlePtr  = &_nxp_spi_master_handle_1;

    __MasterTransferCreateHandle__(spiBase[1], &_nxp_spi_master_handle_1, _spi_master_transfer_callback, (void*) &_spi_master_handle_1.nxpCallbackData);

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
    tommRoCMwSemaphoreCreate(&_spi_master_handle_1.syncSem, 0),
    TOMMRO_C_HW_LOW_LEVEL_ERR);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif

#endif
