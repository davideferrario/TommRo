
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateMMC.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)

#include "TOMMROC.h"

#if defined (__TOMMROC_HW_TEMPLATE_MMC_AT_LEAST_ONE_IS_USED__)
#if !defined (HAL_MMC_MODULE_ENABLED)
#error "HAL_MMC_MODULE_ENABLED must be defined"
#endif

#include "MMC/common/tommRoCHwTemplateMMCCommonCb.h"

#include "TOMMROCMw.h"
#include "TOMMROCMwTemplate.h"

#include "sdmmc.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    bool                    transferCompleteCbCalled;
    HAL_MMC_StateTypeDef    state;

    bool                    errorCbCalled;
    uint32_t                errorCode;

} __stm32_callback_data_t__;

#define __EMPTY___stm32_callback_data_t____                 \
{                                                           \
    /* .transferCompleteCbCalled */ false,                  \
    /* .state */                    HAL_MMC_STATE_RESET,    \
    /* .errorCbCalled */            false,                  \
    /* .errorCode */                HAL_MMC_ERROR_NONE,     \
}

typedef struct {

    void*                               mmcPtr;
    volatile __stm32_callback_data_t__  stm32CallbackData;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    tommRoC_mw_template_semaphore_t     syncSem;
#endif

} __tommRoC_hw_mmc_handle_t__;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
#define __EMPTY___tommRoC_hw_mmc_handle_t____                               \
{                                                                           \
    /* .mmcPtr */               NULL,                                       \
    /* .stm32CallbackData */    __EMPTY___stm32_callback_data_t____,        \
    /* .syncSem */              __EMPTY_tommRoC_mw_template_semaphore_t__,  \
}
#else
#define __EMPTY___tommRoC_hw_mmc_handle_t____                           \
{                                                                       \
    /* .mmcPtr */               NULL,                                   \
    /* .stm32CallbackData */    __EMPTY___stm32_callback_data_t____,    \
}
#endif

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_MMC_1_TEMPLATE__)
static __tommRoC_hw_mmc_handle_t__ _mmc_handle_1 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_mmc_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_MMC_2_TEMPLATE__)
static __tommRoC_hw_mmc_handle_t__ _mmc_handle_2 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_mmc_handle_t__);
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
static void _irq_mmc_tx_rx_handle(__tommRoC_hw_mmc_handle_t__* const mmcHandlePtr, MMC_HandleTypeDef *hmmc) {

    mmcHandlePtr->stm32CallbackData.state                       = hmmc->State;
    mmcHandlePtr->stm32CallbackData.transferCompleteCbCalled    = true;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwSemaphoreRelease(&mmcHandlePtr->syncSem));
#endif
}

static void _irq_mmc_error_handle(__tommRoC_hw_mmc_handle_t__* const mmcHandlePtr, MMC_HandleTypeDef *hmmc) {

    mmcHandlePtr->stm32CallbackData.errorCode       = hmmc->ErrorCode;
    mmcHandlePtr->stm32CallbackData.errorCbCalled   = true;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwSemaphoreRelease(&mmcHandlePtr->syncSem));
#endif
}

static void _irq_mmc_abort_handle(__tommRoC_hw_mmc_handle_t__* const mmcHandlePtr, MMC_HandleTypeDef *hmmc) {

}

static void _transfer_complete_cb(MMC_HandleTypeDef *hmmc) {

#if defined (__TOMMROC_HW_USE_MMC_1_TEMPLATE__)
    if (((MMC_HandleTypeDef*) _mmc_handle_1.mmcPtr)->Instance == hmmc->Instance) {
        _irq_mmc_tx_rx_handle(&_mmc_handle_1, hmmc);
        return;
    }
#endif

#if defined (__TOMMROC_HW_USE_MMC_2_TEMPLATE__)
    if (((MMC_HandleTypeDef*) _mmc_handle_2.mmcPtr)->Instance == hmmc->Instance) {
        _irq_mmc_tx_rx_handle(&_mmc_handle_2, hmmc);
        return;
    }
#endif
}

static void _error_cb(MMC_HandleTypeDef *hmmc) {

#if defined (__TOMMROC_HW_USE_MMC_1_TEMPLATE__)
    if (((MMC_HandleTypeDef*) _mmc_handle_1.mmcPtr)->Instance == hmmc->Instance) {
        _irq_mmc_error_handle(&_mmc_handle_1, hmmc);
        return;
    }
#endif

#if defined (__TOMMROC_HW_USE_MMC_2_TEMPLATE__)
    if (((MMC_HandleTypeDef*) _mmc_handle_1.mmcPtr)->Instance == hmmc->Instance) {
        _irq_mmc_error_handle(&_mmc_handle_2, hmmc);
        return;
    }
#endif
}

static void _abort_cb(MMC_HandleTypeDef *hmmc) {

#if defined (__TOMMROC_HW_USE_MMC_1_TEMPLATE__)
    if (((MMC_HandleTypeDef*) _mmc_handle_1.mmcPtr)->Instance == hmmc->Instance) {
        _irq_mmc_abort_handle(&_mmc_handle_1, hmmc);
        return;
    }
#endif

#if defined (__TOMMROC_HW_USE_MMC_2_TEMPLATE__)
    if (((MMC_HandleTypeDef*) _mmc_handle_1.mmcPtr)->Instance == hmmc->Instance) {
        _irq_mmc_abort_handle(&_mmc_handle_2, hmmc);
        return;
    }
#endif
}

void HAL_MMC_TxCpltCallback(MMC_HandleTypeDef *hmmc) { _transfer_complete_cb(hmmc); }
void HAL_MMC_RxCpltCallback(MMC_HandleTypeDef *hmmc) { _transfer_complete_cb(hmmc); }

void HAL_MMC_ErrorCallback(MMC_HandleTypeDef *hmmc) { _error_cb(hmmc); }
void HAL_MMC_AbortCallback(MMC_HandleTypeDef *hmmc) { _abort_cb(hmmc); }

static bool _mmc_is_ready(__tommRoC_hw_mmc_handle_t__* const mmcHandlePtr) {
    MMC_HandleTypeDef* mmcPtr = (MMC_HandleTypeDef*) mmcHandlePtr->mmcPtr;
    return (HAL_MMC_CARD_TRANSFER == HAL_MMC_GetCardState(mmcPtr));
}

static tommRoC_hw_err_enum_t _mmc_wait_for_ready(__tommRoC_hw_mmc_handle_t__* const mmcHandlePtr) {

    while (!_mmc_is_ready(mmcHandlePtr)) {
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(0));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _wait_for_transfer_complete(
                __tommRoC_hw_mmc_handle_t__*    const   mmcHandlePtr,
        const   uint32_t                                timeoutMsec) {

    MMC_HandleTypeDef* mmcPtr = (MMC_HandleTypeDef*) mmcHandlePtr->mmcPtr;

#if !defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    tommRoC_timer_t timer;
    uint32_t elapsedMsec;
#endif

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)

    if (TOMMRO_C_MW_ERR_SUCCESS == tommRoCMwSemaphoreWait(&mmcHandlePtr->syncSem, timeoutMsec)) {
        if (mmcHandlePtr->stm32CallbackData.transferCompleteCbCalled) {
            if (HAL_MMC_STATE_READY == mmcHandlePtr->stm32CallbackData.state) {
                return TOMMRO_C_HW_ERR_SUCCESS;
            }
        }

        if (mmcHandlePtr->stm32CallbackData.errorCbCalled) {
            return TOMMRO_C_HW_MMC_OPERATION_FAIL_ERR;
        }
    }

    // NOTE: in case of timeout expired, check again if SUCCESS because it could be the case in multitask environment
    if ((mmcHandlePtr->stm32CallbackData.transferCompleteCbCalled) && (HAL_MMC_STATE_READY == mmcHandlePtr->stm32CallbackData.state)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    if (!mmcHandlePtr->stm32CallbackData.transferCompleteCbCalled && !mmcHandlePtr->stm32CallbackData.errorCbCalled) {
        HAL_MMC_Abort_IT(mmcPtr);
    }

    return TOMMRO_C_HW_MMC_OPERATION_FAIL_ERR;
#else

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, timeoutMsec));

    do {

        if (mmcHandlePtr->stm32CallbackData.transferCompleteCbCalled) {
            if (HAL_MMC_STATE_READY == mmcHandlePtr->stm32CallbackData.state) {
                return TOMMRO_C_HW_ERR_SUCCESS;
            }
            else {
                break;
            }
        }

        if (mmcHandlePtr->stm32CallbackData.errorCbCalled) {
            return TOMMRO_C_HW_MMC_OPERATION_FAIL_ERR;
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
    if ((mmcHandlePtr->stm32CallbackData.transferCompleteCbCalled) && (HAL_MMC_STATE_READY == mmcHandlePtr->stm32CallbackData.state)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    if (!mmcHandlePtr->stm32CallbackData.transferCompleteCbCalled && !mmcHandlePtr->stm32CallbackData.errorCbCalled) {
        HAL_MMC_Abort_IT(mmcPtr);
    }

    return TOMMRO_C_HW_MMC_OPERATION_FAIL_ERR;
#endif
}

static tommRoC_hw_err_enum_t _mmc_write_transfer(
                __tommRoC_hw_mmc_handle_t__*    const   mmcHandlePtr,
        const   uint8_t*                        const   writeBufferPtr,
        const   uint32_t                                startBlockAdd,
        const   uint32_t                                blocksAmount,
        const   uint32_t                                timeoutMsec) {

    static const __stm32_callback_data_t__ stm32CallbackDataEmpty = TOMMROC_UTIL_EMPTY_VARIABLE(__stm32_callback_data_t__);

    MMC_HandleTypeDef* mmcPtr = (MMC_HandleTypeDef*) mmcHandlePtr->mmcPtr;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy((void*) &mmcHandlePtr->stm32CallbackData, &stm32CallbackDataEmpty, sizeof(stm32CallbackDataEmpty)));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_mmc_wait_for_ready(mmcHandlePtr));

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    // NOTE: call semaphore wait in order to "clean" possible old released semaphore
    while (TOMMRO_C_MW_ERR_SUCCESS == tommRoCMwSemaphoreWait(&mmcHandlePtr->syncSem, WAIT_SEMAPHORE_NO_WAIT_TIMEOUT)) ;
#endif

    if (HAL_OK != HAL_MMC_WriteBlocks_IT(mmcPtr, writeBufferPtr, startBlockAdd, blocksAmount)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_wait_for_transfer_complete(mmcHandlePtr, timeoutMsec));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _mmc_read_transfer(
                __tommRoC_hw_mmc_handle_t__*    const   mmcHandlePtr,
                uint8_t*                        const   readBufferPtr,
        const   uint32_t                                startBlockAdd,
        const   uint32_t                                blocksAmount,
        const   uint32_t                                timeoutMsec) {

    static const __stm32_callback_data_t__ stm32CallbackDataEmpty = TOMMROC_UTIL_EMPTY_VARIABLE(__stm32_callback_data_t__);

    MMC_HandleTypeDef* mmcPtr = (MMC_HandleTypeDef*) mmcHandlePtr->mmcPtr;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy((void*) &mmcHandlePtr->stm32CallbackData, &stm32CallbackDataEmpty, sizeof(stm32CallbackDataEmpty)));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_mmc_wait_for_ready(mmcHandlePtr));

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    // NOTE: call semaphore wait in order to "clean" possible old released semaphore
    while (TOMMRO_C_MW_ERR_SUCCESS == tommRoCMwSemaphoreWait(&mmcHandlePtr->syncSem, WAIT_SEMAPHORE_NO_WAIT_TIMEOUT)) ;
#endif

    if (HAL_OK != HAL_MMC_ReadBlocks_IT(mmcPtr, readBufferPtr, startBlockAdd, blocksAmount)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_wait_for_transfer_complete(mmcHandlePtr, timeoutMsec));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_write_buffer(
                void*       const   MMCConfigPtr,
                void*       const   MMCHandlePtr,
        const   uint32_t            logicalAddStart,
        const   void*       const   writeBufferPtr,
        const   uint32_t            writeBufferLen,
                uint32_t*   const   writtenLenPtr,
        const   uint32_t            timeoutPerByteMsec) {

    __tommRoC_hw_mmc_handle_t__* mmcHandlePtr   = (__tommRoC_hw_mmc_handle_t__*) MMCHandlePtr;
    MMC_HandleTypeDef* mmcPtr                   = (MMC_HandleTypeDef*) mmcHandlePtr->mmcPtr;

    HAL_MMC_CardInfoTypeDef cardInfo;

    uint32_t startBlockAdd;
    uint32_t blocksAmount;

    TOMMROC_UTIL_UNUSED_PARAM(MMCConfigPtr);

    if (HAL_OK != HAL_MMC_GetCardInfo(mmcPtr, &cardInfo)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (0 == cardInfo.BlockSize) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (0 == cardInfo.BlockNbr) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (0 != (logicalAddStart % cardInfo.BlockSize)) {
        return TOMMRO_C_HW_PARAM_ERR;
    }

    if (0 != (writeBufferLen % cardInfo.BlockSize)) {
        return TOMMRO_C_HW_PARAM_ERR;
    }

    startBlockAdd   = logicalAddStart / cardInfo.BlockSize;
    blocksAmount    = writeBufferLen / cardInfo.BlockSize;

    if (startBlockAdd >= cardInfo.BlockNbr) {
        return TOMMRO_C_HW_PARAM_ERR;
    }
    if (startBlockAdd + blocksAmount > cardInfo.BlockNbr) {
        return TOMMRO_C_HW_PARAM_ERR;
    }

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _mmc_write_transfer(
                    mmcHandlePtr,
                    writeBufferPtr,
                    startBlockAdd,
                    blocksAmount,
                    timeoutPerByteMsec * tommRoCMathMax(1, writeBufferLen)));

    *writtenLenPtr = writeBufferLen;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_read_buffer(
                void*       const   MMCConfigPtr,
                void*       const   MMCHandlePtr,
        const   uint32_t            logicalAddStart,
                void*       const   readBufferPtr,
        const   uint32_t            readBufferLen,
                uint32_t*   const   readedLenPtr,
        const   uint32_t            timeoutPerByteMsec) {

    __tommRoC_hw_mmc_handle_t__* mmcHandlePtr   = (__tommRoC_hw_mmc_handle_t__*) MMCHandlePtr;
    MMC_HandleTypeDef* mmcPtr                   = (MMC_HandleTypeDef*) mmcHandlePtr->mmcPtr;

    HAL_MMC_CardInfoTypeDef cardInfo;

    uint32_t startBlockAdd;
    uint32_t blocksAmount;

    TOMMROC_UTIL_UNUSED_PARAM(MMCConfigPtr);

    if (HAL_OK != HAL_MMC_GetCardInfo(mmcPtr, &cardInfo)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (0 == cardInfo.BlockSize) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (0 == cardInfo.BlockNbr) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (0 != (logicalAddStart % cardInfo.BlockSize)) {
        return TOMMRO_C_HW_PARAM_ERR;
    }

    if (0 != (readBufferLen % cardInfo.BlockSize)) {
        return TOMMRO_C_HW_PARAM_ERR;
    }

    startBlockAdd   = logicalAddStart / cardInfo.BlockSize;
    blocksAmount    = readBufferLen / cardInfo.BlockSize;

    if (startBlockAdd >= cardInfo.BlockNbr) {
        return TOMMRO_C_HW_PARAM_ERR;
    }
    if (startBlockAdd + blocksAmount > cardInfo.BlockNbr) {
        return TOMMRO_C_HW_PARAM_ERR;
    }

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _mmc_read_transfer(
                    mmcHandlePtr,
                    readBufferPtr,
                    startBlockAdd,
                    blocksAmount,
                    timeoutPerByteMsec * tommRoCMathMax(1, readBufferLen)));

    *readedLenPtr = readBufferLen;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_low_power_enter(__tommRoC_hw_mmc_handle_t__* const mmcHandlePtr) {
    MMC_HandleTypeDef* mmcHandleTypePtr = (MMC_HandleTypeDef*) mmcHandlePtr->mmcPtr;
    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_low_power_exit(__tommRoC_hw_mmc_handle_t__* const mmcHandlePtr) {
    MMC_HandleTypeDef* mmcHandleTypePtr = (MMC_HandleTypeDef*) mmcHandlePtr->mmcPtr;
    return TOMMRO_C_HW_ERR_SUCCESS;
}


/******************* MMC implementation functs */

#define __TOMMROC_HW_MMC_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(mmcMasterPrefix, mmcHandle)            \
                                                                                                        \
    static tommRoC_hw_err_enum_t _mmc_ ## mmcMasterPrefix ## _write_buffer_ARM(                         \
            const   uint32_t            logicalAddStart,                                                \
            const   void*       const   writeBufferPtr,                                                 \
            const   uint32_t            writeBufferLen,                                                 \
                    uint32_t*   const   writtenLenPtr) {                                                \
                                                                                                        \
        return tommRoCHwTemplateMMCCommonCbWriteBuffer(                                                 \
                logicalAddStart,                                                                        \
                writeBufferPtr,                                                                         \
                writeBufferLen,                                                                         \
                writtenLenPtr,                                                                          \
                NULL,                                                                                   \
                &mmcHandle,                                                                             \
                _phy_write_buffer);                                                                     \
    }                                                                                                   \
                                                                                                        \
    static tommRoC_hw_err_enum_t _mmc_ ## mmcMasterPrefix ## _read_buffer_ARM(                          \
            const   uint32_t            logicalAddStart,                                                \
                    void*       const   readBufferPtr,                                                  \
            const   uint32_t            readBufferLen,                                                  \
                    uint32_t*   const   readedLenPtr) {                                                 \
                                                                                                        \
        return tommRoCHwTemplateMMCCommonCbReadBuffer(                                                  \
                logicalAddStart,                                                                        \
                readBufferPtr,                                                                          \
                readBufferLen,                                                                          \
                readedLenPtr,                                                                           \
                NULL,                                                                                   \
                &mmcHandle,                                                                             \
                _phy_read_buffer);                                                                      \
    }                                                                                                   \
                                                                                                        \
    static tommRoC_hw_err_enum_t _mmc_ ## mmcMasterPrefix ## _low_power_enter_ARM(void) {               \
        return _phy_low_power_enter(&mmcHandle);                                                        \
    }                                                                                                   \
                                                                                                        \
    static tommRoC_hw_err_enum_t _mmc_ ## mmcMasterPrefix ## _low_power_exit_ARM(void) {                \
        return _phy_low_power_exit(&mmcHandle);                                                         \
    }                                                                                                   \
                                                                                                        \
    static void _mmc_ ## mmcMasterPrefix ## _get_callback_ARM(                                          \
                    tommRoC_hw_mmc_cb_funct_t*  const   cbFunctPtr) {                                   \
                                                                                                        \
        cbFunctPtr->writeBuffer     = _mmc_ ## mmcMasterPrefix ## _write_buffer_ARM;                    \
        cbFunctPtr->readBuffer      = _mmc_ ## mmcMasterPrefix ## _read_buffer_ARM;                     \
        cbFunctPtr->lowPowerEnter   = _mmc_ ## mmcMasterPrefix ## _low_power_enter_ARM;                 \
        cbFunctPtr->lowPowerExit    = _mmc_ ## mmcMasterPrefix ## _low_power_exit_ARM;                  \
    }

#if defined (__TOMMROC_HW_USE_MMC_1_TEMPLATE__)
    __TOMMROC_HW_MMC_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(MMC1, _mmc_handle_1);
#endif

#if defined (__TOMMROC_HW_USE_MMC_2_TEMPLATE__)
    __TOMMROC_HW_MMC_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(MMC2, _mmc_handle_2);
#endif

#if defined (__TOMMROC_HW_USE_MMC_3_TEMPLATE__)
    __TOMMROC_HW_MMC_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(MMC3, _mmc_handle_3);
#endif

#if defined (__TOMMROC_HW_USE_MMC_4_TEMPLATE__)
    __TOMMROC_HW_MMC_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(MMC4, _mmc_handle_4);
#endif

#if defined (__TOMMROC_HW_USE_MMC_5_TEMPLATE__)
_   _TOMMROC_HW_MMC_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(MMC5, _mmc_handle_5);
#endif


/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_HW_USE_MMC_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateMMCEnvironment1Start(
                tommRoC_hw_mmc_cb_funct_t*  const   cbFunctPtr) {

    _mmc_MMC1_get_callback_ARM(cbFunctPtr);

    _mmc_handle_1.mmcPtr = (void*) &hmmc1;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
    tommRoCMwSemaphoreCreate(&_mmc_handle_1.syncSem, 0),
    TOMMRO_C_HW_LOW_LEVEL_ERR);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_MMC_2_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateMMCEnvironment2Start(
                tommRoC_hw_mmc_cb_funct_t*  const   cbFunctPtr) {

    _mmc_MMC2_get_callback_ARM(cbFunctPtr);

    _mmc_handle_2.mmcPtr = (void*) &hmmc2;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
    tommRoCMwSemaphoreCreate(&_mmc_handle_2.syncSem, 0),
    TOMMRO_C_HW_LOW_LEVEL_ERR);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_MMC_3_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateMMCEnvironment3Start(
                tommRoC_hw_mmc_cb_funct_t*  const   cbFunctPtr) {

    _mmc_MMC3_get_callback_ARM(cbFunctPtr);

    _mmc_handle_3.mmcPtr = (void*) &hmmc3;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
    tommRoCMwSemaphoreCreate(&_mmc_handle_3.syncSem, 0),
    TOMMRO_C_HW_LOW_LEVEL_ERR);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_MMC_4_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateMMCEnvironment4Start(
                tommRoC_hw_mmc_cb_funct_t*  const   cbFunctPtr) {

    _mmc_MMC4_get_callback_ARM(cbFunctPtr);

    _mmc_handle_4.mmcPtr = (void*) &hmmc4;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
    tommRoCMwSemaphoreCreate(&_mmc_handle_4.syncSem, 0),
    TOMMRO_C_HW_LOW_LEVEL_ERR);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_MMC_5_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateMMCEnvironment5Start(
                tommRoC_hw_mmc_cb_funct_t*  const   cbFunctPtr) {

    _mmc_MMC5_get_callback_ARM(cbFunctPtr);

    _mmc_handle_5.mmcPtr = (void*) &hmmc5;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
    tommRoCMwSemaphoreCreate(&_mmc_handle_5.syncSem, 0),
    TOMMRO_C_HW_LOW_LEVEL_ERR);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif
