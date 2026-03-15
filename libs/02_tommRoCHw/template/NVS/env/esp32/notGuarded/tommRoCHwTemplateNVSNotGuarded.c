
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateNVSNotGuarded.h"

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)
#include "TOMMROC.h"

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
#if defined (__TOMMROC_DEBUG_ENABLE__)
static const char __DEBUG_OBJ_ID__[] = "hwTempNVSNG";
#endif

static nvs_handle _handle;

/*******************************************************************************
 * local functions
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedStart(void) {

    esp_err_t err;

    err = nvs_open("storage", NVS_READWRITE, &_handle);

    if (ESP_OK == err) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_open: ", esp_err_to_name(err));

    if (ESP_FAIL == err) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (ESP_ERR_NVS_NOT_INITIALIZED == err) {
        return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
    }

    if ((ESP_ERR_NVS_PART_NOT_FOUND == err) || (ESP_ERR_NVS_NOT_FOUND == err) || (ESP_ERR_NVS_INVALID_NAME == err)) {
        return TOMMRO_C_HW_PARAM_ERR;
    }

    if (ESP_ERR_NO_MEM == err) {
        return TOMMRO_C_HW_GENERIC_ERR;
    }

    return TOMMRO_C_HW_LOW_LEVEL_ERR;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedStop(void) {

    nvs_close(_handle);

    return TOMMRO_C_HW_ERR_SUCCESS;
}


tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedSetU8(const char* const keyStrPtr, const uint8_t value) {

    esp_err_t err;

    err = nvs_set_u8(_handle, keyStrPtr, value);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_set_u8: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    err = nvs_commit(_handle);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_commit: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedSetI8(const char* const keyStrPtr, const int8_t value) {

    esp_err_t err;

    err = nvs_set_i8(_handle, keyStrPtr, value);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_set_i8: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    err = nvs_commit(_handle);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_commit: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedSetU16(const char* const keyStrPtr, const uint16_t value) {

    esp_err_t err;

    err = nvs_set_u16(_handle, keyStrPtr, value);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_set_u16: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    err = nvs_commit(_handle);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_commit: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedSetI16(const char* const keyStrPtr, const int16_t value) {

    esp_err_t err;

    err = nvs_set_i16(_handle, keyStrPtr, value);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_set_i16: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    err = nvs_commit(_handle);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_commit: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedSetU32(const char* const keyStrPtr, const uint32_t value) {

    esp_err_t err;

    err = nvs_set_u32(_handle, keyStrPtr, value);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_set_u32: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    err = nvs_commit(_handle);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_commit: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedSetI32(const char* const keyStrPtr, const int32_t value) {

    esp_err_t err;

    err = nvs_set_i32(_handle, keyStrPtr, value);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_set_i32: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    err = nvs_commit(_handle);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_commit: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedSetStr(const char* const keyStrPtr, const char* const valueStrPtr) {

    esp_err_t err;

    err = nvs_set_str(_handle, keyStrPtr, valueStrPtr);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_set_str: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    err = nvs_commit(_handle);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_commit: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedSetBlob(const char* const keyStrPtr, const void* const valueBufferPtr, const uint32_t valueBufferSize) {

    esp_err_t err;

    err = nvs_set_blob(_handle, keyStrPtr, valueBufferPtr, valueBufferSize);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_set_blob: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    err = nvs_commit(_handle);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_commit: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}


tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedGetU8(const char* const keyStrPtr, uint8_t* const valuePtr) {

    esp_err_t err;

    err = nvs_get_u8(_handle, keyStrPtr, valuePtr);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_get_u8: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedGetI8(const char* const keyStrPtr, int8_t* const valuePtr) {

    esp_err_t err;

    err = nvs_get_i8(_handle, keyStrPtr, valuePtr);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_get_i8: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedGetU16(const char* const keyStrPtr, uint16_t* const valuePtr) {

    esp_err_t err;

    err = nvs_get_u16(_handle, keyStrPtr, valuePtr);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_get_u16: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedGetI16(const char* const keyStrPtr, int16_t* const valuePtr) {

    esp_err_t err;

    err = nvs_get_i16(_handle, keyStrPtr, valuePtr);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_get_i16: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedGetU32(const char* const keyStrPtr, uint32_t* const valuePtr) {

    esp_err_t err;

    err = nvs_get_u32(_handle, keyStrPtr, valuePtr);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_get_u32: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedGetI32(const char* const keyStrPtr, int32_t* const valuePtr) {

    esp_err_t err;

    err = nvs_get_i32(_handle, keyStrPtr, valuePtr);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_get_i32: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedGetStr(const char* const keyStrPtr, char* const valueStrPtr, const uint32_t valueStrSize) {

    size_t length;
    esp_err_t err;

    length = (size_t) valueStrSize;
    err = nvs_get_str(_handle, keyStrPtr, valueStrPtr, &length);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_get_str: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_EQUALS(length, valueStrSize);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedGetBlob(const char* const keyStrPtr, void* const valueBufferPtr, const uint32_t valueBufferSize) {

    size_t length;
    esp_err_t err;

    length = (size_t) valueBufferSize;
    err = nvs_get_blob(_handle, keyStrPtr, valueBufferPtr, &length);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_get_blob: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_EQUALS(length, valueBufferSize);

    return TOMMRO_C_HW_ERR_SUCCESS;
}


tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedEraseKey(const char* const keyStrPtr) {

    esp_err_t err;

    err = nvs_erase_key(_handle, keyStrPtr);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_erase_key: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedEraseAll(void) {

    esp_err_t err;

    err = nvs_erase_all(_handle);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "nvs_erase_all: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

#endif
