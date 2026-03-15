
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValue.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)

#include "sdkconfig.h"

#include "env/tommRoCTemplateEnv.h"

#if !defined (__TOMMROC_HW_DISABLE_BLE_TEMPLATE__) && !defined (CONFIG_EXAMPLE_PROV_TRANSPORT_BLE) && defined (CONFIG_BT_ENABLED) && defined (CONFIG_BT_NIMBLE_ENABLED)
#if defined (CONFIG_BT_NIMBLE_MAX_CONNECTIONS) && (CONFIG_BT_NIMBLE_MAX_CONNECTIONS > 1)
#include "TOMMROCHw.h"

#include "TOMMROCMw.h"
#include "TOMMROCMwTemplate.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__)
static tommRoC_mw_template_mutex_t _mutex;
#endif
static tommRoC_guard_t _guard;

static const esp32_multi_nimble_conn_handle_mtu_value_t _conn_handle_mtu_value_empty = TOMMROC_UTIL_EMPTY_VARIABLE(esp32_multi_nimble_conn_handle_mtu_value_t);

static esp32_multi_nimble_conn_handle_mtu_value_t _conn_handle_mtu_value_array[CONFIG_BT_NIMBLE_MAX_CONNECTIONS];

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if defined (__TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__)
static tommRoC_err_enum_t _lock_mutex(void) {
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCMwMutexLock(&_mutex, LOCK_MUTEX_INFINITE_TIMEOUT), TOMMRO_C_LOW_LEVEL_ERR);
    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _unlock_mutex(void) {
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCMwMutexUnLock(&_mutex), TOMMRO_C_LOW_LEVEL_ERR);
    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _lock(void)   {   return _lock_mutex();   }
static tommRoC_err_enum_t _unlock(void) {   return _unlock_mutex(); }

static tommRoC_err_enum_t _init_guard(void) {

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCMwMutexCreate(&_mutex), TOMMRO_C_LOW_LEVEL_ERR);
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCGuardInit(_lock, _unlock, &_guard));
    return TOMMRO_C_ERR_SUCCESS;
}
#endif

static tommRoC_hw_err_enum_t _not_guarded_init(void) {

    uint8_t idx;

    for (idx = 0; idx < TOMMROC_UTIL_ARR_EAMOUNT(_conn_handle_mtu_value_array); ++idx) {
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&_conn_handle_mtu_value_array[idx], &_conn_handle_mtu_value_empty, sizeof(esp32_multi_nimble_conn_handle_mtu_value_t)));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _not_guarded_add(const esp32_multi_nimble_conn_handle_mtu_value_t* const connHandleMTUValuePtr) {

    uint8_t idx;

    for (idx = 0; idx < TOMMROC_UTIL_ARR_EAMOUNT(_conn_handle_mtu_value_array); ++idx) {
        if (_conn_handle_mtu_value_array[idx].isEmpty) {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&_conn_handle_mtu_value_array[idx], connHandleMTUValuePtr, sizeof(esp32_multi_nimble_conn_handle_mtu_value_t)));
            _conn_handle_mtu_value_array[idx].isEmpty = false;
            return TOMMRO_C_HW_ERR_SUCCESS;
        }
    }

    return TOMMRO_C_HW_LOW_LEVEL_ERR;
}

static tommRoC_hw_err_enum_t _not_guarded_remove(const esp32_multi_nimble_conn_handle_mtu_value_t* const connHandleMTUValuePtr) {

    uint8_t idx;

    for (idx = 0; idx < TOMMROC_UTIL_ARR_EAMOUNT(_conn_handle_mtu_value_array); ++idx) {
        if ((!_conn_handle_mtu_value_array[idx].isEmpty) && (connHandleMTUValuePtr->connHandle == _conn_handle_mtu_value_array[idx].connHandle)) {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&_conn_handle_mtu_value_array[idx], &_conn_handle_mtu_value_empty, sizeof(esp32_multi_nimble_conn_handle_mtu_value_t)));
            return TOMMRO_C_HW_ERR_SUCCESS;
        }
    }

    return TOMMRO_C_HW_LOW_LEVEL_ERR;
}

static tommRoC_hw_err_enum_t _not_guarded_update(const esp32_multi_nimble_conn_handle_mtu_value_t* const connHandleMTUValuePtr) {

    uint8_t idx;

    for (idx = 0; idx < TOMMROC_UTIL_ARR_EAMOUNT(_conn_handle_mtu_value_array); ++idx) {
        if ((!_conn_handle_mtu_value_array[idx].isEmpty) && (connHandleMTUValuePtr->connHandle == _conn_handle_mtu_value_array[idx].connHandle)) {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&_conn_handle_mtu_value_array[idx], connHandleMTUValuePtr, sizeof(esp32_multi_nimble_conn_handle_mtu_value_t)));
            return TOMMRO_C_HW_ERR_SUCCESS;
        }
    }

    return TOMMRO_C_HW_LOW_LEVEL_ERR;
}

static tommRoC_hw_err_enum_t _not_guarded_get_from_conn_handle(const uint16_t connHandle, esp32_multi_nimble_conn_handle_mtu_value_t* const connHandleMTUValuePtr) {

    uint8_t idx;

    for (idx = 0; idx < TOMMROC_UTIL_ARR_EAMOUNT(_conn_handle_mtu_value_array); ++idx) {
        if ((!_conn_handle_mtu_value_array[idx].isEmpty) && ((int32_t) connHandle == _conn_handle_mtu_value_array[idx].connHandle)) {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(connHandleMTUValuePtr, &_conn_handle_mtu_value_array[idx], sizeof(esp32_multi_nimble_conn_handle_mtu_value_t)));
            return TOMMRO_C_HW_ERR_SUCCESS;
        }
    }

    return TOMMRO_C_HW_LOW_LEVEL_ERR;
}

static tommRoC_hw_err_enum_t _not_guarded_is_empty(bool* const isEmptyPtr) {

    uint8_t idx;

    for (idx = 0; idx < TOMMROC_UTIL_ARR_EAMOUNT(_conn_handle_mtu_value_array); ++idx) {
        if (!_conn_handle_mtu_value_array[idx].isEmpty) {
            *isEmptyPtr = false;
            return TOMMRO_C_HW_ERR_SUCCESS;
        }
    }

    *isEmptyPtr = true;
    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _not_guarded_is_full(bool* const isFullPtr) {

    uint8_t idx;

    for (idx = 0; idx < TOMMROC_UTIL_ARR_EAMOUNT(_conn_handle_mtu_value_array); ++idx) {
        if (_conn_handle_mtu_value_array[idx].isEmpty) {
            *isFullPtr = false;
            return TOMMRO_C_HW_ERR_SUCCESS;
        }
    }

    *isFullPtr = true;
    return TOMMRO_C_HW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueInit(void) {

#if defined (__TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(_init_guard());
#else
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCGuardClear(&_guard));
#endif

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            &_guard,
            _not_guarded_init())
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueAdd(const esp32_multi_nimble_conn_handle_mtu_value_t* const connHandleMTUValuePtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            &_guard,
            _not_guarded_add(
                    connHandleMTUValuePtr))
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueRemove(const esp32_multi_nimble_conn_handle_mtu_value_t* const connHandleMTUValuePtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            &_guard,
            _not_guarded_remove(
                    connHandleMTUValuePtr))
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueUpdate(const esp32_multi_nimble_conn_handle_mtu_value_t* const connHandleMTUValuePtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            &_guard,
            _not_guarded_update(
                    connHandleMTUValuePtr))
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueGetFromConnHandle(const uint16_t connHandle, esp32_multi_nimble_conn_handle_mtu_value_t* const connHandleMTUValuePtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            &_guard,
            _not_guarded_get_from_conn_handle(
                    connHandle,
                    connHandleMTUValuePtr))
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueIsEmpty(bool* const isEmptyPtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            &_guard,
            _not_guarded_is_empty(
                    isEmptyPtr))
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueIsFull(bool* const isFullPtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            &_guard,
            _not_guarded_is_full(
                    isFullPtr))
}

#endif

#endif

#endif
