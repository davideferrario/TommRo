
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateUartDebug.h"

#include "TOMMROC.h"
#include "TOMMROCHw.h"
#if defined (__TOMMROC_DEBUG_ENABLE__)
#include "TOMMROCMw.h"
#include "TOMMROCPw.h"
#include "TOMMROCSw.h"
#include "TOMMROCTw.h"

#include "TOMMROCMwTemplate.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_DEBUG_ENABLE__)
static bool _is_only_tx = true;

static tommRoC_hw_bus_t* _bus_uart_ptr = NULL;
static tommRoC_guard_t* _guard_ptr = NULL;

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
static tommRoC_mw_template_mutex_t _mutex;
#endif
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if defined (__TOMMROC_DEBUG_ENABLE__)
#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
static tommRoC_err_enum_t _lock(void) {
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwMutexLock(&_mutex, LOCK_MUTEX_INFINITE_TIMEOUT));
    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _un_lock(void) {
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwMutexUnLock(&_mutex));
    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _init_guard(void) {

    static tommRoC_guard_t guard;

    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwMutexCreate(&_mutex));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCGuardInit(_lock, _un_lock, &guard));

    _guard_ptr = &guard;

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _close_guard(void) {

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCGuardClear(_guard_ptr));
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwMutexDestroy(&_mutex));

    _guard_ptr = NULL;

    return TOMMRO_C_ERR_SUCCESS;
}
#endif

static tommRoC_err_enum_t _print_string_len(const tommRoC_debug_level_enum_t debugLevel, const char* const stringPtr, const uint16_t stringLen) {

    tommRoC_hw_err_enum_t res;

    TOMMROC_UTIL_UNUSED_PARAM(debugLevel);

    res = tommRoCHwBusWriteBuffer(_bus_uart_ptr, (uint8_t*) stringPtr, stringLen, NULL, NULL);

    if (TOMMRO_C_HW_ERR_SUCCESS != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _debug_print_string(const tommRoC_debug_level_enum_t debugLevel, const char* const stringPtr) {

    uint16_t strLen;

    strLen = tommRoCStringStrLen(stringPtr);

    return _print_string_len(
            debugLevel,
            stringPtr,
            strLen);
}

static tommRoC_err_enum_t _debug_print_string_len(const tommRoC_debug_level_enum_t debugLevel, const char* const stringPtr, const uint16_t stringLen) {

    return _print_string_len(
            debugLevel,
            stringPtr,
            stringLen);
}

static tommRoC_err_enum_t _debug_print_str_tx_rx(const tommRoC_debug_level_enum_t debugLevel, const char* const stringPtr) {
    return _debug_print_string(debugLevel, stringPtr);
}
static tommRoC_err_enum_t _debug_print_str_only_tx_clear_rx(const tommRoC_debug_level_enum_t debugLevel, const char* const stringPtr) {
    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwBusClearReceivedData(_bus_uart_ptr, NULL, NULL));
    return _debug_print_string(debugLevel, stringPtr);
}
static tommRoC_err_enum_t _debug_print_str_only_tx_no_clear_rx(const tommRoC_debug_level_enum_t debugLevel, const char* const stringPtr) {
    return _debug_print_string(debugLevel, stringPtr);
}

static tommRoC_err_enum_t _debug_print_str_len_tx_rx(const tommRoC_debug_level_enum_t debugLevel, const char* const stringPtr, const uint16_t stringLen) {
    return _debug_print_string_len(debugLevel, stringPtr, stringLen);
}
static tommRoC_err_enum_t _debug_print_str_len_only_tx_clear_rx(const tommRoC_debug_level_enum_t debugLevel, const char* const stringPtr, const uint16_t stringLen) {
    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwBusClearReceivedData(_bus_uart_ptr, NULL, NULL));
    return _debug_print_string_len(debugLevel, stringPtr, stringLen);
}
static tommRoC_err_enum_t _debug_print_str_len_only_tx_no_clear_rx(const tommRoC_debug_level_enum_t debugLevel, const char* const stringPtr, const uint16_t stringLen) {
    return _debug_print_string_len(debugLevel, stringPtr, stringLen);
}

static tommRoC_err_enum_t _is_print_pending(bool* const isPendingPtr) {

    switch (tommRoCHwBusIsDataToTxPending(_bus_uart_ptr, NULL, NULL)) {

    case TOMMRO_C_HW_ERR_SUCCESS:
        *isPendingPtr = true;
        return TOMMRO_C_ERR_SUCCESS;

    case TOMMRO_C_HW_BUS_DATA_NOT_AVAILABLE_ERR:
        *isPendingPtr = false;
        return TOMMRO_C_ERR_SUCCESS;

    case TOMMRO_C_HW_NOT_AVAILABLE_ERR:
        *isPendingPtr = false;
        return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;

    }

    *isPendingPtr = false;
    return TOMMRO_C_LOW_LEVEL_ERR;
}

static tommRoC_hw_err_enum_t _init(const tommRoC_hw_bus_t* const busPtr, const tommRoC_debug_print_str_funct_t debugPrintStr, const tommRoC_debug_print_str_len_funct_t debugPrintStrLen) {

    static const char newLineStr[] = "\n\r";

    static tommRoC_debug_funct_enabled_status_t enabledStatus = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_debug_funct_enabled_status_t);

    static tommRoC_debug_print_env_init_t initEnvironment = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_debug_print_env_init_t);

    TOMMROC_ASSERT_NOT_NULL(busPtr);

    _bus_uart_ptr = (tommRoC_hw_bus_t*) busPtr;

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(_init_guard());
#endif

    enabledStatus.debugDStatus = TOMMRO_C_UTIL_ENABLED;
    enabledStatus.debugEStatus = TOMMRO_C_UTIL_ENABLED;
    enabledStatus.debugIStatus = TOMMRO_C_UTIL_ENABLED;
    enabledStatus.debugVStatus = TOMMRO_C_UTIL_ENABLED;
    enabledStatus.debugWStatus = TOMMRO_C_UTIL_ENABLED;

    initEnvironment.debugPrintStr       = debugPrintStr;
    initEnvironment.debugPrintStrLen    = debugPrintStrLen;
    initEnvironment.newLineStrPtr       = newLineStr;
    initEnvironment.debugStatusPtr      = &enabledStatus;
    initEnvironment.guardPtr            = _guard_ptr;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCDebugInitEnv(&initEnvironment));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCDebugSetProp(TOMMRO_C_DEBUG_IS_PRINT_PENDING_FUNCT_PTR_PROP, _is_print_pending));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwDebugInit(&enabledStatus));
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwDebugInit(&enabledStatus));
    TOMMROC_PW_ASSERT_TOMMROC_PW_LIB_FUNCT_SUCCESS(tommRoCPwDebugInit(&enabledStatus));
    TOMMROC_SW_ASSERT_TOMMROC_SW_LIB_FUNCT_SUCCESS(tommRoCSwDebugInit(&enabledStatus));
    TOMMROC_TW_ASSERT_TOMMROC_TW_LIB_FUNCT_SUCCESS(tommRoCTwDebugInit(&enabledStatus));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _close(void) {

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCDebugCloseEnv());

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(_close_guard());
#endif

    _bus_uart_ptr = NULL;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugInit(const tommRoC_hw_bus_t* const busPtr) {

#if defined (__TOMMROC_DEBUG_ENABLE__)
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_init(busPtr, _debug_print_str_tx_rx, _debug_print_str_len_tx_rx));

    _is_only_tx = false;

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(busPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugOnlyTxInit(const tommRoC_hw_bus_t* const busPtr) {

#if defined (__TOMMROC_DEBUG_ENABLE__)
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_init(busPtr, _debug_print_str_only_tx_clear_rx, _debug_print_str_len_only_tx_clear_rx));

    _is_only_tx = true;

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(busPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugOnlyTxNoClearRxInit(const tommRoC_hw_bus_t* const busPtr) {

#if defined (__TOMMROC_DEBUG_ENABLE__)
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_init(busPtr, _debug_print_str_only_tx_no_clear_rx, _debug_print_str_len_only_tx_no_clear_rx));

    _is_only_tx = true;

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(busPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugClose(void) {

#if defined (__TOMMROC_DEBUG_ENABLE__)
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_close());

    _is_only_tx = true;

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugSetRawType(const bool rawType) {
#if defined (__TOMMROC_DEBUG_ENABLE__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCDebugSetProp(TOMMRO_C_DEBUG_RAW_TYPE_PROP, &rawType));
    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(rawType);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugIsDataAvailable(void) {
#if defined (__TOMMROC_DEBUG_ENABLE__)
    if (_is_only_tx) {
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
    }
    return tommRoCHwBusIsDataAvailable(_bus_uart_ptr, NULL, NULL);
#else
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugDataReady(uint16_t* const availableAmountPtr) {
#if defined (__TOMMROC_DEBUG_ENABLE__)
    if (_is_only_tx) {
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
    }
    return tommRoCHwBusDataReady(_bus_uart_ptr, availableAmountPtr, NULL, NULL);
#else
    TOMMROC_UTIL_UNUSED_PARAM(availableAmountPtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugIsDataToTxPending(void) {
#if defined (__TOMMROC_DEBUG_ENABLE__)
    return tommRoCHwBusIsDataToTxPending(_bus_uart_ptr, NULL, NULL);
#else
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugDataToTxPendingAmount(uint16_t* const availableAmountPtr) {
#if defined (__TOMMROC_DEBUG_ENABLE__)
    return tommRoCHwBusDataToTxPendingAmount(_bus_uart_ptr, availableAmountPtr, NULL, NULL);
#else
    TOMMROC_UTIL_UNUSED_PARAM(availableAmountPtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugReadByte(uint8_t* const readDataPtr) {
#if defined (__TOMMROC_DEBUG_ENABLE__)
    if (_is_only_tx) {
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
    }
    return tommRoCHwBusReadByte(_bus_uart_ptr, readDataPtr, NULL, NULL);
#else
    TOMMROC_UTIL_UNUSED_PARAM(readDataPtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugReadBuffer(uint8_t* const readBufferPtr, const uint16_t toReadAmount, uint16_t* const readedAmountPtr) {
#if defined (__TOMMROC_DEBUG_ENABLE__)
    if (_is_only_tx) {
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
    }
    return tommRoCHwBusReadBuffer(_bus_uart_ptr, readBufferPtr, toReadAmount, readedAmountPtr, NULL, NULL);
#else
    TOMMROC_UTIL_UNUSED_PARAM(readBufferPtr);
    TOMMROC_UTIL_UNUSED_PARAM(toReadAmount);
    TOMMROC_UTIL_UNUSED_PARAM(readedAmountPtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateUartDebugReadBuffers(tommRoC_hw_bus_read_buf_t* const readBuffersPtr, const uint8_t readBuffersAmount) {
#if defined (__TOMMROC_DEBUG_ENABLE__)
    if (_is_only_tx) {
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
    }
    return tommRoCHwBusReadBuffers(_bus_uart_ptr, readBuffersPtr, readBuffersAmount, NULL, NULL);
#else
    TOMMROC_UTIL_UNUSED_PARAM(readBuffersPtr);
    TOMMROC_UTIL_UNUSED_PARAM(readBuffersAmount);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}
