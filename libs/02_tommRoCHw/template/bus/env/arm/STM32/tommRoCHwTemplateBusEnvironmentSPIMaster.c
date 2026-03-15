
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentSPIMaster.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)

#include "TOMMROC.h"

#if defined (__TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

#include "bus/common/spi/master/tommRoCHwTemplateBusCommonSPIMasterCb.h"

#include "bus/env/arm/STM32/spi/tommRoCHwTemplateBusSPISTM32DEF.h"
#include "bus/env/arm/STM32/spi/tommRoCHwTemplateBusSPISTM32Hal.h"

#include "TOMMROCMw.h"
#include "TOMMROCMwTemplate.h"

#include "spi.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
// NOTE: STM32U5 has limited FIFO on SPI
#if defined (__TOMMROC_TEMPLATE_ARM_STM32U5_IS_USED__)
#define __SPI_SINGLE_TRANSFER_MAX_SIZE_BYTE__   (8)
#endif

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    bool                    transferCompleteCbCalled;
    HAL_SPI_StateTypeDef    state;

    bool                    errorCbCalled;
    uint32_t                errorCode;

} __stm32_callback_data_t__;

#define __EMPTY___stm32_callback_data_t____                 \
{                                                           \
    /* .transferCompleteCbCalled */ false,                  \
    /* .state */                    HAL_SPI_STATE_ERROR,    \
    /* .errorCbCalled */            false,                  \
    /* .errorCode */                HAL_SPI_ERROR_NONE,     \
}

typedef struct {

    void*                               spiPtr;
    volatile __stm32_callback_data_t__  stm32CallbackData;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    tommRoC_mw_template_semaphore_t     syncSem;
#endif

} __tommRoC_hw_spi_master_handle_t__;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
#define __EMPTY___tommRoC_hw_spi_master_handle_t____                        \
{                                                                           \
    /* .spiPtr */               NULL,                                       \
    /* .stm32CallbackData */    __EMPTY___stm32_callback_data_t____,        \
    /* .syncSem */              __EMPTY_tommRoC_mw_template_semaphore_t__,  \
}
#else
#define __EMPTY___tommRoC_hw_spi_master_handle_t____                    \
{                                                                       \
    /* .spiPtr */               NULL,                                   \
    /* .stm32CallbackData */    __EMPTY___stm32_callback_data_t____,    \
}
#endif

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
static __tommRoC_hw_spi_master_handle_t__ _spi_master_handle_1 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_spi_master_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_TEMPLATE__)
static __tommRoC_hw_spi_master_handle_t__ _spi_master_handle_2 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_spi_master_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_3_TEMPLATE__)
static __tommRoC_hw_spi_master_handle_t__ _spi_master_handle_3 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_spi_master_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_4_TEMPLATE__)
static __tommRoC_hw_spi_master_handle_t__ _spi_master_handle_4 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_spi_master_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_5_TEMPLATE__)
static __tommRoC_hw_spi_master_handle_t__ _spi_master_handle_5 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_spi_master_handle_t__);
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
static void _irq_spi_tx_rx_handle(__tommRoC_hw_spi_master_handle_t__* const spiHandlePtr, SPI_HandleTypeDef *hspi) {

    spiHandlePtr->stm32CallbackData.state                       = hspi->State;
    spiHandlePtr->stm32CallbackData.transferCompleteCbCalled    = true;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwSemaphoreRelease(&spiHandlePtr->syncSem));
#endif
}

static void _irq_spi_error_handle(__tommRoC_hw_spi_master_handle_t__* const spiHandlePtr, SPI_HandleTypeDef *hspi) {

    spiHandlePtr->stm32CallbackData.errorCode       = hspi->ErrorCode;
    spiHandlePtr->stm32CallbackData.errorCbCalled   = true;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwSemaphoreRelease(&spiHandlePtr->syncSem));
#endif
}

static void _transfer_complete_cb(SPI_HandleTypeDef *hspi) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    if (((SPI_HandleTypeDef*) _spi_master_handle_1.spiPtr)->Instance == hspi->Instance) {
        _irq_spi_tx_rx_handle(&_spi_master_handle_1, hspi);
        return;
    }
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_TEMPLATE__)
    if (((SPI_HandleTypeDef*) _spi_master_handle_2.spiPtr)->Instance == hspi->Instance) {
        _irq_spi_tx_rx_handle(&_spi_master_handle_2, hspi);
        return;
    }
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_3_TEMPLATE__)
    if (((SPI_HandleTypeDef*) _spi_master_handle_3.spiPtr)->Instance == hspi->Instance) {
        _irq_spi_tx_rx_handle(&_spi_master_handle_3, hspi);
        return;
    }
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_4_TEMPLATE__)
    if (((SPI_HandleTypeDef*) _spi_master_handle_4.spiPtr)->Instance == hspi->Instance) {
        _irq_spi_tx_rx_handle(&_spi_master_handle_4, hspi);
        return;
    }
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_5_TEMPLATE__)
    if (((SPI_HandleTypeDef*) _spi_master_handle_5.spiPtr)->Instance == hspi->Instance) {
        _irq_spi_tx_rx_handle(&_spi_master_handle_5, hspi);
        return;
    }
#endif
}

static void _error_cb(SPI_HandleTypeDef *hspi) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    if (((SPI_HandleTypeDef*) _spi_master_handle_1.spiPtr)->Instance == hspi->Instance) {
        _irq_spi_error_handle(&_spi_master_handle_1, hspi);
        return;
    }
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_TEMPLATE__)
    if (((SPI_HandleTypeDef*) _spi_master_handle_2.spiPtr)->Instance == hspi->Instance) {
        _irq_spi_error_handle(&_spi_master_handle_2, hspi);
        return;
    }
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_3_TEMPLATE__)
    if (((SPI_HandleTypeDef*) _spi_master_handle_3.spiPtr)->Instance == hspi->Instance) {
        _irq_spi_error_handle(&_spi_master_handle_3, hspi);
        return;
    }
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_4_TEMPLATE__)
    if (((SPI_HandleTypeDef*) _spi_master_handle_4.spiPtr)->Instance == hspi->Instance) {
        _irq_spi_error_handle(&_spi_master_handle_4, hspi);
        return;
    }
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_5_TEMPLATE__)
    if (((SPI_HandleTypeDef*) _spi_master_handle_5.spiPtr)->Instance == hspi->Instance) {
        _irq_spi_error_handle(&_spi_master_handle_5, hspi);
        return;
    }
#endif
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)    { _transfer_complete_cb(hspi); }
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)    { _transfer_complete_cb(hspi); }
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)  { _transfer_complete_cb(hspi); }

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi) { _error_cb(hspi); }

static tommRoC_hw_err_enum_t _wait_for_transfer_complete(
                __tommRoC_hw_spi_master_handle_t__* const   spiHandlePtr,
        const   uint32_t                                    timeoutMsec) {

    SPI_HandleTypeDef* spiPtr = (SPI_HandleTypeDef*) spiHandlePtr->spiPtr;

#if !defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    tommRoC_timer_t timer;
    uint32_t elapsedMsec;
#endif

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)

    if (TOMMRO_C_MW_ERR_SUCCESS == tommRoCMwSemaphoreWait(&spiHandlePtr->syncSem, timeoutMsec)) {
        if (spiHandlePtr->stm32CallbackData.transferCompleteCbCalled) {
            if (HAL_SPI_STATE_READY == spiHandlePtr->stm32CallbackData.state) {
                return TOMMRO_C_HW_ERR_SUCCESS;
            }
        }

        if (spiHandlePtr->stm32CallbackData.errorCbCalled) {
            return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
        }
    }

    // NOTE: in case of timeout expired, check again if SUCCESS because it could be the case in multitask environment
    if ((spiHandlePtr->stm32CallbackData.transferCompleteCbCalled) && (HAL_SPI_STATE_READY == spiHandlePtr->stm32CallbackData.state)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    if (!spiHandlePtr->stm32CallbackData.transferCompleteCbCalled && !spiHandlePtr->stm32CallbackData.errorCbCalled) {
        HAL_SPI_Abort_IT(spiPtr);
    }

    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
#else

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, timeoutMsec));

    do {

        if (spiHandlePtr->stm32CallbackData.transferCompleteCbCalled) {
            if (HAL_SPI_STATE_READY == spiHandlePtr->stm32CallbackData.state) {
                return TOMMRO_C_HW_ERR_SUCCESS;
            }
            else {
                break;
            }
        }

        if (spiHandlePtr->stm32CallbackData.errorCbCalled) {
            return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerElapsed(&timer, &elapsedMsec));

        if (elapsedMsec > 1) {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1));
        }
        else {
            // NOTE: don't replace with tommRoCOsDelayMsec(0) because as fast as possible is needed in case of single task project.
#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
            tommRoCMwThreadYield();
#endif
        }

    } while (TOMMRO_C_TIMER_NOT_EXPIRED_ERR == tommRoCTimerIsExpired(&timer));
    
    // NOTE: in case of timeout expired, check again if SUCCESS because it could be the case in multitask environment
    if ((spiHandlePtr->stm32CallbackData.transferCompleteCbCalled) && (HAL_SPI_STATE_READY == spiHandlePtr->stm32CallbackData.state)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    if (!spiHandlePtr->stm32CallbackData.transferCompleteCbCalled && !spiHandlePtr->stm32CallbackData.errorCbCalled) {
        HAL_SPI_Abort_IT(spiPtr);
    }

    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
#endif
}

static tommRoC_hw_err_enum_t _spi_master_write_transfer_low_level(
                __tommRoC_hw_spi_master_handle_t__* const   spiHandlePtr,
        const   uint8_t*                            const   writeBufferPtr,
        const   uint16_t                                    writeBufferLen,
        const   uint32_t                                    timeoutMsec) {

    static const __stm32_callback_data_t__ stm32CallbackDataEmpty = TOMMROC_UTIL_EMPTY_VARIABLE(__stm32_callback_data_t__);

    SPI_HandleTypeDef* spiPtr = (SPI_HandleTypeDef*) spiHandlePtr->spiPtr;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy((void*) &spiHandlePtr->stm32CallbackData, &stm32CallbackDataEmpty, sizeof(stm32CallbackDataEmpty)));

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    // NOTE: call semaphore wait in order to "clean" possible old released semaphore
    while (TOMMRO_C_MW_ERR_SUCCESS == tommRoCMwSemaphoreWait(&spiHandlePtr->syncSem, WAIT_SEMAPHORE_NO_WAIT_TIMEOUT)) ;
#endif

    if (HAL_OK != HAL_SPI_Transmit_IT(spiPtr, (uint8_t*) writeBufferPtr, writeBufferLen)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_wait_for_transfer_complete(spiHandlePtr, timeoutMsec));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _spi_master_read_transfer_low_level(
                __tommRoC_hw_spi_master_handle_t__* const   spiHandlePtr,
                uint8_t*                            const   readBufferPtr,
        const   uint16_t                                    toReadAmount,
        const   uint32_t                                    timeoutMsec) {

    static const __stm32_callback_data_t__ stm32CallbackDataEmpty = TOMMROC_UTIL_EMPTY_VARIABLE(__stm32_callback_data_t__);

    SPI_HandleTypeDef* spiPtr = (SPI_HandleTypeDef*) spiHandlePtr->spiPtr;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy((void*) &spiHandlePtr->stm32CallbackData, &stm32CallbackDataEmpty, sizeof(stm32CallbackDataEmpty)));

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    // NOTE: call semaphore wait in order to "clean" possible old released semaphore
    while (TOMMRO_C_MW_ERR_SUCCESS == tommRoCMwSemaphoreWait(&spiHandlePtr->syncSem, WAIT_SEMAPHORE_NO_WAIT_TIMEOUT)) ;
#endif

    if (HAL_OK != HAL_SPI_Receive_IT(spiPtr, readBufferPtr, toReadAmount)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_wait_for_transfer_complete(spiHandlePtr, timeoutMsec));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _spi_master_transceive_transfer_low_level(
                __tommRoC_hw_spi_master_handle_t__* const   spiHandlePtr,
        const   uint8_t*                            const   writeBufferPtr,
                uint8_t*                            const   readBufferPtr,
        const   uint16_t                                    bufferLength,
        const   uint32_t                                    timeoutMsec) {

    static const __stm32_callback_data_t__ stm32CallbackDataEmpty = TOMMROC_UTIL_EMPTY_VARIABLE(__stm32_callback_data_t__);

    SPI_HandleTypeDef* spiPtr = (SPI_HandleTypeDef*) spiHandlePtr->spiPtr;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy((void*) &spiHandlePtr->stm32CallbackData, &stm32CallbackDataEmpty, sizeof(stm32CallbackDataEmpty)));

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    // NOTE: call semaphore wait in order to "clean" possible old released semaphore
    while (TOMMRO_C_MW_ERR_SUCCESS == tommRoCMwSemaphoreWait(&spiHandlePtr->syncSem, WAIT_SEMAPHORE_NO_WAIT_TIMEOUT)) ;
#endif

    if (HAL_OK != HAL_SPI_TransmitReceive_IT(spiPtr, (uint8_t*) writeBufferPtr, readBufferPtr, bufferLength)) {
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

    uint8_t* ptr;
    uint16_t remaining;
    uint16_t wrAmount;

    ptr         = (uint8_t*) writeBufferPtr;
    remaining   = writeBufferLen;

    while (remaining > 0) {

#if !defined (__TOMMROC_TEMPLATE_ARM_STM32U5_IS_USED__)
        wrAmount = remaining;
#else
        wrAmount = tommRoCMathMin(__SPI_SINGLE_TRANSFER_MAX_SIZE_BYTE__, remaining);
#endif

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _spi_master_write_transfer_low_level(
                        spiHandlePtr,
                        ptr,
                        wrAmount,
                        timeoutMsec));

        ptr         += wrAmount;
        remaining   -= wrAmount;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _spi_master_read_transfer(
                __tommRoC_hw_spi_master_handle_t__* const   spiHandlePtr,
                uint8_t*                            const   readBufferPtr,
        const   uint16_t                                    toReadAmount,
        const   uint32_t                                    timeoutMsec) {

    uint8_t* ptr;
    uint16_t remaining;
    uint16_t rdAmount;

    ptr         = readBufferPtr;
    remaining   = toReadAmount;

    while (remaining > 0) {

#if !defined (__TOMMROC_TEMPLATE_ARM_STM32U5_IS_USED__)
        rdAmount = remaining;
#else
        rdAmount = tommRoCMathMin(__SPI_SINGLE_TRANSFER_MAX_SIZE_BYTE__, remaining);
#endif

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _spi_master_read_transfer_low_level(
                        spiHandlePtr,
                        ptr,
                        rdAmount,
                        timeoutMsec));

        ptr         += rdAmount;
        remaining   -= rdAmount;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _spi_master_transceive_transfer(
                __tommRoC_hw_spi_master_handle_t__* const   spiHandlePtr,
        const   uint8_t*                            const   writeBufferPtr,
                uint8_t*                            const   readBufferPtr,
        const   uint16_t                                    bufferLength,
        const   uint32_t                                    timeoutMsec) {

    uint8_t* ptrWr;
    uint8_t* ptrRd;
    uint16_t remaining;
    uint16_t wrRdAmount;

    ptrWr       = (uint8_t*) writeBufferPtr;
    ptrRd       = readBufferPtr;
    remaining   = bufferLength;

    while (remaining > 0) {

#if !defined (__TOMMROC_TEMPLATE_ARM_STM32U5_IS_USED__)
        wrRdAmount = remaining;
#else
        wrRdAmount = tommRoCMathMin(__SPI_SINGLE_TRANSFER_MAX_SIZE_BYTE__, remaining);
#endif

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _spi_master_transceive_transfer_low_level(
                        spiHandlePtr,
                        ptrWr,
                        ptrRd,
                        wrRdAmount,
                        timeoutMsec));

        ptrWr       += wrRdAmount;
        ptrRd       += wrRdAmount;
        remaining   -= wrRdAmount;
    }

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

static tommRoC_hw_err_enum_t _phy_low_power_enter(__tommRoC_hw_spi_master_handle_t__* const spiHandlePtr) {

    SPI_HandleTypeDef* spiHandleTypePtr = (SPI_HandleTypeDef*) spiHandlePtr->spiPtr;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusSPISTM32HalSetForLowPowerEnter(
                    spiHandleTypePtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_low_power_exit(__tommRoC_hw_spi_master_handle_t__* const spiHandlePtr) {

    SPI_HandleTypeDef* spiHandleTypePtr = (SPI_HandleTypeDef*) spiHandlePtr->spiPtr;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusSPISTM32HalSetForLowPowerExit(
                    spiHandleTypePtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}


/******************* BUS implementation functs */

#define __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(spiMasterPrefix, spiHandle)     \
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
                NULL,                                                                                   \
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
                NULL,                                                                                   \
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
        return _phy_low_power_enter(&spiHandle);                                                        \
    }                                                                                                   \
                                                                                                        \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _low_power_exit_ARM(                \
            const   void*                       const   inputPtr,                                       \
                    void*                       const   resultPtr) {                                    \
                                                                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                           \
                                                                                                        \
        return _phy_low_power_exit(&spiHandle);                                                         \
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

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(SPI1, _spi_master_handle_1);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(SPI2, _spi_master_handle_2);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_3_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(SPI3, _spi_master_handle_3);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_4_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(SPI4, _spi_master_handle_4);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_5_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(SPI5, _spi_master_handle_5);
#endif


/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_DEF_AT_LEAST_ONE_IS_USED__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMasterSetProp(
        const   tommRoC_hw_template_bus_spi_master_prop_enum_t          property,
        const   tommRoC_hw_template_bus_spi_master_enum_t               bus,
        const   void*                                           const   propValuePtr) {

    TOMMROC_UTIL_UNUSED_PARAM(property);
    TOMMROC_UTIL_UNUSED_PARAM(bus);
    TOMMROC_UTIL_UNUSED_PARAM(propValuePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMaster1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    _spi_master_SPI1_get_callback_ARM(cbFunctPtr);

    _spi_master_handle_1.spiPtr = (void*) &hspi1;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
    tommRoCMwSemaphoreCreate(&_spi_master_handle_1.syncSem, 0),
    TOMMRO_C_HW_LOW_LEVEL_ERR);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMaster2Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    _spi_master_SPI2_get_callback_ARM(cbFunctPtr);

    _spi_master_handle_2.spiPtr = (void*) &hspi2;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
    tommRoCMwSemaphoreCreate(&_spi_master_handle_2.syncSem, 0),
    TOMMRO_C_HW_LOW_LEVEL_ERR);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_3_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMaster3Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    _spi_master_SPI3_get_callback_ARM(cbFunctPtr);

    _spi_master_handle_3.spiPtr = (void*) &hspi3;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
    tommRoCMwSemaphoreCreate(&_spi_master_handle_3.syncSem, 0),
    TOMMRO_C_HW_LOW_LEVEL_ERR);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_4_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMaster4Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    _spi_master_SPI4_get_callback_ARM(cbFunctPtr);

    _spi_master_handle_4.spiPtr = (void*) &hspi4;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
    tommRoCMwSemaphoreCreate(&_spi_master_handle_4.syncSem, 0),
    TOMMRO_C_HW_LOW_LEVEL_ERR);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_5_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMaster5Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    _spi_master_SPI5_get_callback_ARM(cbFunctPtr);

    _spi_master_handle_5.spiPtr = (void*) &hspi5;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
    tommRoCMwSemaphoreCreate(&_spi_master_handle_5.syncSem, 0),
    TOMMRO_C_HW_LOW_LEVEL_ERR);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif
