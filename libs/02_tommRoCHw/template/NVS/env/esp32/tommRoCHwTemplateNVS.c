
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateNVS.h"

#include "TOMMROC.h"

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)
#include "NVS/env/esp32/notGuarded/tommRoCHwTemplateNVSNotGuarded.h"

#include "nvs_flash.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static tommRoC_guard_t* _guard_ptr = NULL;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_hw_err_enum_t _nvs_start(void) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateNVSNotGuardedStart());
}

static tommRoC_hw_err_enum_t _nvs_stop(void) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateNVSNotGuardedStop());
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSStart(void) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_nvs_start());
    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSStop(void) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_nvs_stop());
    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSSetGuard(const tommRoC_guard_t* const guardPtr) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)

    if (NULL != guardPtr) {
        TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCGuardCheck(guardPtr), TOMMRO_C_HW_PARAM_ERR);
    }

    _guard_ptr = (tommRoC_guard_t*) guardPtr;

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(guardPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}


tommRoC_hw_err_enum_t tommRoCHwTemplateNVSSetU8(const char* const keyStrPtr, const uint8_t value) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(keyStrPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(keyStrPtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateNVSNotGuardedSetU8(
                    keyStrPtr,
                    value));
#else
    TOMMROC_UTIL_UNUSED_PARAM(keyStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(value);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSSetI8(const char* const keyStrPtr, const int8_t value) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(keyStrPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(keyStrPtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateNVSNotGuardedSetI8(
                    keyStrPtr,
                    value));
#else
    TOMMROC_UTIL_UNUSED_PARAM(keyStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(value);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSSetU16(const char* const keyStrPtr, const uint16_t value) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(keyStrPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(keyStrPtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateNVSNotGuardedSetU16(
                    keyStrPtr,
                    value));
#else
    TOMMROC_UTIL_UNUSED_PARAM(keyStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(value);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSSetI16(const char* const keyStrPtr, const int16_t value) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(keyStrPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(keyStrPtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateNVSNotGuardedSetI16(
                    keyStrPtr,
                    value));
#else
    TOMMROC_UTIL_UNUSED_PARAM(keyStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(value);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSSetU32(const char* const keyStrPtr, const uint32_t value) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(keyStrPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(keyStrPtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateNVSNotGuardedSetU32(
                    keyStrPtr,
                    value));
#else
    TOMMROC_UTIL_UNUSED_PARAM(keyStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(value);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSSetI32(const char* const keyStrPtr, const int32_t value) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(keyStrPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(keyStrPtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateNVSNotGuardedSetI32(
                    keyStrPtr,
                    value));
#else
    TOMMROC_UTIL_UNUSED_PARAM(keyStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(value);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSSetStr(const char* const keyStrPtr, const char* const valueStrPtr) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(keyStrPtr);
    TOMMROC_ASSERT_NOT_NULL(valueStrPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(keyStrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(valueStrPtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateNVSNotGuardedSetStr(
                    keyStrPtr,
                    valueStrPtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(keyStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(valueStrPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSSetBlob(const char* const keyStrPtr, const void* const valueBufferPtr, const uint32_t valueBufferSize) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(keyStrPtr);
    TOMMROC_ASSERT_NOT_NULL(valueBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(valueBufferSize);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(keyStrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(valueBufferPtr);
    TOMMROC_HW_PARAM_CHECK_ON_ZERO_RETURN_ERR(valueBufferSize);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateNVSNotGuardedSetBlob(
                    keyStrPtr,
                    valueBufferPtr,
                    valueBufferSize));
#else
    TOMMROC_UTIL_UNUSED_PARAM(keyStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(valueBufferPtr);
    TOMMROC_UTIL_UNUSED_PARAM(valueBufferSize);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}


tommRoC_hw_err_enum_t tommRoCHwTemplateNVSGetU8(const char* const keyStrPtr, uint8_t* const valuePtr) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(keyStrPtr);
    TOMMROC_ASSERT_NOT_NULL(valuePtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(keyStrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(valuePtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateNVSNotGuardedGetU8(
                    keyStrPtr,
                    valuePtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(keyStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(valuePtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSGetI8(const char* const keyStrPtr, int8_t* const valuePtr) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(keyStrPtr);
    TOMMROC_ASSERT_NOT_NULL(valuePtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(keyStrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(valuePtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateNVSNotGuardedGetI8(
                    keyStrPtr,
                    valuePtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(keyStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(valuePtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSGetU16(const char* const keyStrPtr, uint16_t* const valuePtr) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(keyStrPtr);
    TOMMROC_ASSERT_NOT_NULL(valuePtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(keyStrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(valuePtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateNVSNotGuardedGetU16(
                    keyStrPtr,
                    valuePtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(keyStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(valuePtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSGetI16(const char* const keyStrPtr, int16_t* const valuePtr) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(keyStrPtr);
    TOMMROC_ASSERT_NOT_NULL(valuePtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(keyStrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(valuePtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateNVSNotGuardedGetI16(
                    keyStrPtr,
                    valuePtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(keyStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(valuePtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSGetU32(const char* const keyStrPtr, uint32_t* const valuePtr) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(keyStrPtr);
    TOMMROC_ASSERT_NOT_NULL(valuePtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(keyStrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(valuePtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateNVSNotGuardedGetU32(
                    keyStrPtr,
                    valuePtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(keyStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(valuePtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSGetI32(const char* const keyStrPtr, int32_t* const valuePtr) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(keyStrPtr);
    TOMMROC_ASSERT_NOT_NULL(valuePtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(keyStrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(valuePtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateNVSNotGuardedGetI32(
                    keyStrPtr,
                    valuePtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(keyStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(valuePtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSGetStr(const char* const keyStrPtr, char* const valueStrPtr, const uint32_t valueStrSize) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(keyStrPtr);
    TOMMROC_ASSERT_NOT_NULL(valueStrPtr);
    TOMMROC_ASSERT_NOT_ZERO(valueStrSize);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(keyStrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(valueStrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_ZERO_RETURN_ERR(valueStrSize);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateNVSNotGuardedGetStr(
                    keyStrPtr,
                    valueStrPtr,
                    valueStrSize));
#else
    TOMMROC_UTIL_UNUSED_PARAM(keyStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(valueStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(valueStrSize);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSGetBlob(const char* const keyStrPtr, void* const valueBufferPtr, const uint32_t valueBufferSize) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(keyStrPtr);
    TOMMROC_ASSERT_NOT_NULL(valueBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(valueBufferSize);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(keyStrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(valueBufferPtr);
    TOMMROC_HW_PARAM_CHECK_ON_ZERO_RETURN_ERR(valueBufferSize);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateNVSNotGuardedGetBlob(
                    keyStrPtr,
                    valueBufferPtr,
                    valueBufferSize));
#else
    TOMMROC_UTIL_UNUSED_PARAM(keyStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(valueBufferPtr);
    TOMMROC_UTIL_UNUSED_PARAM(valueBufferSize);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}


tommRoC_hw_err_enum_t tommRoCHwTemplateNVSEraseKey(const char* const keyStrPtr) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateNVSNotGuardedEraseKey(
                    keyStrPtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(keyStrPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSEraseAll(void) {

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateNVSNotGuardedEraseAll());
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}
