
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentI2CMaster.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)

#include "TOMMROC.h"

#if defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

#include "bus/common/i2c/master/tommRoCHwTemplateBusCommonI2CMasterCb.h"

#include "bus/env/arm/STM32/i2c/tommRoCHwTemplateBusI2CSTM32DEF.h"
#include "bus/env/arm/STM32/i2c/tommRoCHwTemplateBusI2CSTM32Hal.h"

#include "TOMMROCMw.h"
#include "TOMMROCMwTemplate.h"

#include "i2c.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __DEFAULT_MCU_PULL_UP_STATUS__  (TOMMRO_C_UTIL_DISABLED)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    tommRoC_util_enabled_status_enum_t      mcuPullUpStatus;

} __tommRoC_hw_i2c_master_config_t__;

#define __EMPTY___tommRoC_hw_i2c_master_config_t____        \
{                                                           \
    /* .mcuPullUpStatus */  __DEFAULT_MCU_PULL_UP_STATUS__, \
}

typedef struct {

    bool                    transferCompleteCbCalled;
    HAL_I2C_StateTypeDef    state;

    bool                    errorCbCalled;
    uint32_t                errorCode;

} __stm32_callback_data_t__;

#define __EMPTY___stm32_callback_data_t____                 \
{                                                           \
    /* .transferCompleteCbCalled */ false,                  \
    /* .state */                    HAL_I2C_STATE_ABORT,    \
    /* .errorCbCalled */            false,                  \
    /* .errorCode */                HAL_I2C_ERROR_NONE,     \
}

typedef struct {

    void*                               i2cPtr;
    volatile __stm32_callback_data_t__  stm32CallbackData;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    tommRoC_mw_template_semaphore_t     syncSem;
#endif

} __tommRoC_hw_i2c_master_handle_t__;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
#define __EMPTY___tommRoC_hw_i2c_master_handle_t____                        \
{                                                                           \
    /* .i2cPtr */               NULL,                                       \
    /* .stm32CallbackData */    __EMPTY___stm32_callback_data_t____,        \
    /* .syncSem */              __EMPTY_tommRoC_mw_template_semaphore_t__,  \
}
#else
#define __EMPTY___tommRoC_hw_i2c_master_handle_t____                    \
{                                                                       \
    /* .i2cPtr */               NULL,                                   \
    /* .stm32CallbackData */    __EMPTY___stm32_callback_data_t____,    \
}
#endif

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
static __tommRoC_hw_i2c_master_config_t__ _i2c_master_config_1 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_i2c_master_config_t__);
static __tommRoC_hw_i2c_master_handle_t__ _i2c_master_handle_1 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_i2c_master_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_2_TEMPLATE__)
static __tommRoC_hw_i2c_master_config_t__ _i2c_master_config_2 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_i2c_master_config_t__);
static __tommRoC_hw_i2c_master_handle_t__ _i2c_master_handle_2 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_i2c_master_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_3_TEMPLATE__)
static __tommRoC_hw_i2c_master_config_t__ _i2c_master_config_3 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_i2c_master_config_t__);
static __tommRoC_hw_i2c_master_handle_t__ _i2c_master_handle_3 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_i2c_master_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_4_TEMPLATE__)
static __tommRoC_hw_i2c_master_config_t__ _i2c_master_config_4 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_i2c_master_config_t__);
static __tommRoC_hw_i2c_master_handle_t__ _i2c_master_handle_4 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_i2c_master_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_5_TEMPLATE__)
static __tommRoC_hw_i2c_master_config_t__ _i2c_master_config_5 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_i2c_master_config_t__);
static __tommRoC_hw_i2c_master_handle_t__ _i2c_master_handle_5 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_i2c_master_handle_t__);
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
static void _irq_i2c_tx_rx_handle(__tommRoC_hw_i2c_master_handle_t__* const i2cHandlePtr, I2C_HandleTypeDef *hi2c) {

    i2cHandlePtr->stm32CallbackData.state                       = hi2c->State;
    i2cHandlePtr->stm32CallbackData.transferCompleteCbCalled    = true;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwSemaphoreRelease(&i2cHandlePtr->syncSem));
#endif
}

static void _irq_i2c_error_handle(__tommRoC_hw_i2c_master_handle_t__* const i2cHandlePtr, I2C_HandleTypeDef *hi2c) {

    i2cHandlePtr->stm32CallbackData.errorCode       = hi2c->ErrorCode;
    i2cHandlePtr->stm32CallbackData.errorCbCalled   = true;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwSemaphoreRelease(&i2cHandlePtr->syncSem));
#endif
}

static void _transfer_complete_cb(I2C_HandleTypeDef *hi2c) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    if (((I2C_HandleTypeDef*) _i2c_master_handle_1.i2cPtr)->Instance == hi2c->Instance) {
        _irq_i2c_tx_rx_handle(&_i2c_master_handle_1, hi2c);
        return;
    }
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_2_TEMPLATE__)
    if (((I2C_HandleTypeDef*) _i2c_master_handle_2.i2cPtr)->Instance == hi2c->Instance) {
        _irq_i2c_tx_rx_handle(&_i2c_master_handle_2, hi2c);
        return;
    }
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_3_TEMPLATE__)
    if (((I2C_HandleTypeDef*) _i2c_master_handle_3.i2cPtr)->Instance == hi2c->Instance) {
        _irq_i2c_tx_rx_handle(&_i2c_master_handle_3, hi2c);
        return;
    }
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_4_TEMPLATE__)
    if (((I2C_HandleTypeDef*) _i2c_master_handle_4.i2cPtr)->Instance == hi2c->Instance) {
        _irq_i2c_tx_rx_handle(&_i2c_master_handle_4, hi2c);
        return;
    }
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_5_TEMPLATE__)
    if (((I2C_HandleTypeDef*) _i2c_master_handle_5.i2cPtr)->Instance == hi2c->Instance) {
        _irq_i2c_tx_rx_handle(&_i2c_master_handle_5, hi2c);
        return;
    }
#endif
}

static void _error_cb(I2C_HandleTypeDef *hi2c) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    if (((I2C_HandleTypeDef*) _i2c_master_handle_1.i2cPtr)->Instance == hi2c->Instance) {
        _irq_i2c_error_handle(&_i2c_master_handle_1, hi2c);
        return;
    }
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_2_TEMPLATE__)
    if (((I2C_HandleTypeDef*) _i2c_master_handle_2.i2cPtr)->Instance == hi2c->Instance) {
        _irq_i2c_error_handle(&_i2c_master_handle_2, hi2c);
        return;
    }
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_3_TEMPLATE__)
    if (((I2C_HandleTypeDef*) _i2c_master_handle_3.i2cPtr)->Instance == hi2c->Instance) {
        _irq_i2c_error_handle(&_i2c_master_handle_3, hi2c);
        return;
    }
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_4_TEMPLATE__)
    if (((I2C_HandleTypeDef*) _i2c_master_handle_4.i2cPtr)->Instance == hi2c->Instance) {
        _irq_i2c_error_handle(&_i2c_master_handle_4, hi2c);
        return;
    }
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_5_TEMPLATE__)
    if (((I2C_HandleTypeDef*) _i2c_master_handle_5.i2cPtr)->Instance == hi2c->Instance) {
        _irq_i2c_error_handle(&_i2c_master_handle_5, hi2c);
        return;
    }
#endif
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)  { _transfer_complete_cb(hi2c); }
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)  { _transfer_complete_cb(hi2c); }

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c) { _error_cb(hi2c); }

static tommRoC_hw_err_enum_t _wait_for_transfer_complete(
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
        const   uint8_t                                     slaveAddress7Bit,
        const   uint32_t                                    timeoutMsec) {

    I2C_HandleTypeDef* i2cPtr = (I2C_HandleTypeDef*) i2cHandlePtr->i2cPtr;
    
#if !defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    tommRoC_timer_t timer;
    uint32_t elapsedMsec;
#endif

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)

    if (TOMMRO_C_MW_ERR_SUCCESS == tommRoCMwSemaphoreWait(&i2cHandlePtr->syncSem, timeoutMsec)) {
        if (i2cHandlePtr->stm32CallbackData.transferCompleteCbCalled) {
            if (HAL_I2C_STATE_READY == i2cHandlePtr->stm32CallbackData.state) {
                return TOMMRO_C_HW_ERR_SUCCESS;
            }
        }

        if (i2cHandlePtr->stm32CallbackData.errorCbCalled) {
            return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
        }
    }

    // NOTE: in case of timeout expired, check again if SUCCESS because it could be the case in multitask environment
    if ((i2cHandlePtr->stm32CallbackData.transferCompleteCbCalled) && (HAL_I2C_STATE_READY == i2cHandlePtr->stm32CallbackData.state)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    if (!i2cHandlePtr->stm32CallbackData.transferCompleteCbCalled && !i2cHandlePtr->stm32CallbackData.errorCbCalled) {
        HAL_I2C_Master_Abort_IT(i2cPtr, slaveAddress7Bit << 1);
    }

    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
#else

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, timeoutMsec));

    do {

        if (i2cHandlePtr->stm32CallbackData.transferCompleteCbCalled) {
            if (HAL_I2C_STATE_READY == i2cHandlePtr->stm32CallbackData.state) {
                return TOMMRO_C_HW_ERR_SUCCESS;
            }
            else {
                break;
            }
        }

        if (i2cHandlePtr->stm32CallbackData.errorCbCalled) {
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
    if ((i2cHandlePtr->stm32CallbackData.transferCompleteCbCalled) && (HAL_I2C_STATE_READY == i2cHandlePtr->stm32CallbackData.state)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    if (!i2cHandlePtr->stm32CallbackData.transferCompleteCbCalled && !i2cHandlePtr->stm32CallbackData.errorCbCalled) {
        HAL_I2C_Master_Abort_IT(i2cPtr, slaveAddress7Bit << 1);
    }

    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
#endif
}

static tommRoC_hw_err_enum_t _i2c_master_write_transfer(
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
        const   uint8_t                                     slaveAddress7Bit,
        const   uint8_t*                            const   writeBufferPtr,
        const   uint16_t                                    writeBufferLen,
        const   uint32_t                                    XferOptions,
        const   uint32_t                                    timeoutMsec) {

    static const __stm32_callback_data_t__ stm32CallbackDataEmpty = TOMMROC_UTIL_EMPTY_VARIABLE(__stm32_callback_data_t__);

    I2C_HandleTypeDef* i2cPtr = (I2C_HandleTypeDef*) i2cHandlePtr->i2cPtr;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy((void*) &i2cHandlePtr->stm32CallbackData, &stm32CallbackDataEmpty, sizeof(stm32CallbackDataEmpty)));

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    // NOTE: call semaphore wait in order to "clean" possible old released semaphore
    while (TOMMRO_C_MW_ERR_SUCCESS == tommRoCMwSemaphoreWait(&i2cHandlePtr->syncSem, WAIT_SEMAPHORE_NO_WAIT_TIMEOUT)) ;
#endif

    if (HAL_OK != HAL_I2C_Master_Seq_Transmit_IT(i2cPtr, slaveAddress7Bit << 1, (uint8_t*) writeBufferPtr, writeBufferLen, XferOptions)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_wait_for_transfer_complete(i2cHandlePtr, slaveAddress7Bit, timeoutMsec));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _i2c_master_read_transfer(
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr,
        const   uint8_t                                     slaveAddress7Bit,
                uint8_t*                            const   readBufferPtr,
        const   uint16_t                                    toReadAmount,
        const   uint32_t                                    XferOptions,
        const   uint32_t                                    timeoutMsec) {

    static const __stm32_callback_data_t__ stm32CallbackDataEmpty = TOMMROC_UTIL_EMPTY_VARIABLE(__stm32_callback_data_t__);

    I2C_HandleTypeDef* i2cPtr = (I2C_HandleTypeDef*) i2cHandlePtr->i2cPtr;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy((void*) &i2cHandlePtr->stm32CallbackData, &stm32CallbackDataEmpty, sizeof(stm32CallbackDataEmpty)));

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    // NOTE: call semaphore wait in order to "clean" possible old released semaphore
    while (TOMMRO_C_MW_ERR_SUCCESS == tommRoCMwSemaphoreWait(&i2cHandlePtr->syncSem, WAIT_SEMAPHORE_NO_WAIT_TIMEOUT)) ;
#endif

    if (HAL_OK != HAL_I2C_Master_Seq_Receive_IT(i2cPtr, slaveAddress7Bit << 1, readBufferPtr, toReadAmount, XferOptions)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_wait_for_transfer_complete(i2cHandlePtr, slaveAddress7Bit, timeoutMsec));

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
    uint32_t XferOptions;
    uint8_t index;

    TOMMROC_UTIL_UNUSED_PARAM(i2cConfigPtr);

    for (index = 0, writeBufferPtr = writeBuffersPtr; index < writeBuffersAmount; ++index, ++writeBufferPtr) {

        if (1 == writeBuffersAmount) {              // If single transfer -> default (FIRST and LAST frame)
            XferOptions = I2C_FIRST_AND_LAST_FRAME; // No sequential
        }
        else if (0 == index) {                      // If first transfer -> FIRST
            XferOptions = I2C_FIRST_AND_NEXT_FRAME; // Sequential (Master only) -> start condition/address/data without stop condition then permit call same master sequential interface several times
        }
        else if (writeBuffersAmount - 1 == index) { // If last transfer -> LAST
            XferOptions = I2C_LAST_FRAME;           // Sequential -> only new data to transfer/stop condition
        }
        else {                                      // If other transfer -> NEXT
            XferOptions = I2C_NEXT_FRAME;           // Sequential -> only new data to transfer/without stop
        }

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _i2c_master_write_transfer(
                        i2cHandlePtr,
                        slaveAddress7Bit,
                        writeBufferPtr->bufferPtr,
                        writeBufferPtr->toWriteAmount,
                        XferOptions,
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
    uint32_t XferOptions;
    uint8_t index;

    TOMMROC_UTIL_UNUSED_PARAM(i2cConfigPtr);

    for (index = 0, readBufferPtr = readBuffersPtr; index < readBuffersAmount; ++index, ++readBufferPtr) {

        if (1 == readBuffersAmount) {               // If single transfer -> default (FIRST and LAST frame)
            XferOptions = I2C_FIRST_AND_LAST_FRAME; // No sequential
        }
        else if (0 == index) {                      // If first transfer -> FIRST
            XferOptions = I2C_FIRST_FRAME;          // Sequential -> start condition/address/data without stop condition
        }
        else if (readBuffersAmount - 1 == index) {  // If last transfer -> LAST
            XferOptions = I2C_LAST_FRAME;           // Sequential -> only new data to transfer/stop condition
        }
        else {                                      // If other transfer -> NEXT
            XferOptions = I2C_NEXT_FRAME;           // Sequential -> only new data to transfer/without stop
        }

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _i2c_master_read_transfer(
                        i2cHandlePtr,
                        slaveAddress7Bit,
                        readBufferPtr->bufferPtr,
                        readBufferPtr->toReadAmount,
                        XferOptions,
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
                    I2C_FIRST_FRAME,
                    timeoutPerByteMsec * tommRoCMathMax(1, writeBufferLen)));

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(delayWriteToReadMsec));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _i2c_master_read_transfer(
                    i2cHandlePtr,
                    slaveAddress7Bit,
                    readBufferPtr,
                    toReadAmount,
                    I2C_LAST_FRAME,
                    timeoutPerByteMsec * tommRoCMathMax(1, toReadAmount)));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_low_power_enter(
        const   __tommRoC_hw_i2c_master_config_t__* const   i2cConfigPtr,
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr) {

    I2C_HandleTypeDef* i2cHandleTypePtr = (I2C_HandleTypeDef*) i2cHandlePtr->i2cPtr;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusI2CSTM32HalSetForLowPowerEnter(
                    i2cHandleTypePtr,
                    i2cConfigPtr->mcuPullUpStatus));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_low_power_exit(
        const   __tommRoC_hw_i2c_master_config_t__* const   i2cConfigPtr,
                __tommRoC_hw_i2c_master_handle_t__* const   i2cHandlePtr) {

    I2C_HandleTypeDef* i2cHandleTypePtr = (I2C_HandleTypeDef*) i2cHandlePtr->i2cPtr;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateBusI2CSTM32HalSetForLowPowerExit(
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

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(I2C1, _i2c_master_config_1, _i2c_master_handle_1);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_2_TEMPLATE__)
    __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(I2C2, _i2c_master_config_2, _i2c_master_handle_2);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_3_TEMPLATE__)
    __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(I2C3, _i2c_master_config_3, _i2c_master_handle_3);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_4_TEMPLATE__)
    __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(I2C4, _i2c_master_config_4, _i2c_master_handle_4);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_5_TEMPLATE__)
    __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(I2C5, _i2c_master_config_5, _i2c_master_handle_5);
#endif


/******************* BUS set prop functs */

static tommRoC_hw_err_enum_t _set_mcu_pull_up_status(
        const   tommRoC_hw_template_bus_i2c_master_enum_t           bus,
        const   tommRoC_util_enabled_status_enum_t*         const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_1:
        _i2c_master_config_1.mcuPullUpStatus = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_2:
        _i2c_master_config_2.mcuPullUpStatus = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_3_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_3:
        _i2c_master_config_3.mcuPullUpStatus = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_4_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_4:
        _i2c_master_config_4.mcuPullUpStatus = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_5_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_5:
        _i2c_master_config_5.mcuPullUpStatus = *propValuePtr;
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

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    _i2c_master_I2C1_get_callback_ARM(cbFunctPtr);

    _i2c_master_handle_1.i2cPtr = (void*) &hi2c1;
    
#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
    tommRoCMwSemaphoreCreate(&_i2c_master_handle_1.syncSem, 0),
    TOMMRO_C_HW_LOW_LEVEL_ERR);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_2_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster2Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    _i2c_master_I2C2_get_callback_ARM(cbFunctPtr);

    _i2c_master_handle_2.i2cPtr = (void*) &hi2c2;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
    tommRoCMwSemaphoreCreate(&_i2c_master_handle_2.syncSem, 0),
    TOMMRO_C_HW_LOW_LEVEL_ERR);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_3_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster3Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    _i2c_master_I2C3_get_callback_ARM(cbFunctPtr);

    _i2c_master_handle_3.i2cPtr = (void*) &hi2c3;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
    tommRoCMwSemaphoreCreate(&_i2c_master_handle_3.syncSem, 0),
    TOMMRO_C_HW_LOW_LEVEL_ERR);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_4_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster4Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    _i2c_master_I2C4_get_callback_ARM(cbFunctPtr);

    _i2c_master_handle_4.i2cPtr = (void*) &hi2c4;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
    tommRoCMwSemaphoreCreate(&_i2c_master_handle_4.syncSem, 0),
    TOMMRO_C_HW_LOW_LEVEL_ERR);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_5_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster5Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    _i2c_master_I2C5_get_callback_ARM(cbFunctPtr);

    _i2c_master_handle_5.i2cPtr = (void*) &hi2c5;

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
    tommRoCMwSemaphoreCreate(&_i2c_master_handle_5.syncSem, 0),
    TOMMRO_C_HW_LOW_LEVEL_ERR);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif
