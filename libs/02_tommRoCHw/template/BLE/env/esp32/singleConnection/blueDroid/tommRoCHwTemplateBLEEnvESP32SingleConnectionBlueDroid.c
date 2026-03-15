
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBLE.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)

#include "sdkconfig.h"

#if !defined (__TOMMROC_HW_DISABLE_BLE_TEMPLATE__) && !defined (CONFIG_EXAMPLE_PROV_TRANSPORT_BLE) && defined (CONFIG_BT_ENABLED) && defined (CONFIG_BT_BLUEDROID_ENABLED)

#if (1 == CONFIG_BT_MULTI_CONNECTION_ENBALE)
#error "only BlueDroid with multi connection disabled is supported."
#endif

#if (1 != CONFIG_BT_ACL_CONNECTIONS)
#error "only BlueDroid with ACL_CONNECTIONS==1 is supported."
#endif

#include "tommRoCHwTemplateBLEEnvESP32SingleConnectionBlueDroid.h"

#include "esp_bt.h"
#include "esp_gap_ble_api.h"
#include "esp_gattc_api.h"
#include "esp_gatt_defs.h"
#include "esp_bt_main.h"
#include "esp_bt_defs.h"
#include "esp_ibeacon_api.h"
#include "esp_gatt_common_api.h"
#include "esp_log.h"

#include <stdint.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __INVALID_HANDLE__                      (0)

#define __STOP_SCANNING_WAIT_TIMEOUT_MSEC__     (10)

#define __CONNECT_TIMEOUT_FOR_BYTE_MSEC__       (TOMMROC_TIMER_SEC_TO_mSEC_TIMEOUT(5))
#define __DISCONNECT_TIMEOUT_FOR_BYTE_MSEC__    (250)
#define __WRITE_TIMEOUT_FOR_BYTE_MSEC__         (75)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
TOMMROC_SCTA_EQUALS(TOMMROC_HW_COMM_BLE_MAC_ADDRESS_SIZE_BYTE, ESP_BD_ADDR_LEN);

TOMMROC_SCTA_SIZE_OF_SMEMBER_EQUALS(tommRoC_hw_template_ble_ibeacon_t, BLEMACAddr, esp_ble_gap_cb_param_t, scan_rst.bda);

TOMMROC_SCTA_SIZE_OF_EQUALS(tommRoC_hw_template_ble_ibeacon_head_t,     esp_ble_ibeacon_head_t);
TOMMROC_SCTA_SIZE_OF_EQUALS(tommRoC_hw_template_ble_ibeacon_vendor_t,   esp_ble_ibeacon_vendor_t);

TOMMROC_SCTA_SIZE_OF_SMEMBER_EQUALS(tommRoC_hw_template_ble_ibeacon_head_t, flags,          esp_ble_ibeacon_head_t, flags);
TOMMROC_SCTA_SIZE_OF_SMEMBER_EQUALS(tommRoC_hw_template_ble_ibeacon_head_t, length,         esp_ble_ibeacon_head_t, length);
TOMMROC_SCTA_SIZE_OF_SMEMBER_EQUALS(tommRoC_hw_template_ble_ibeacon_head_t, type,           esp_ble_ibeacon_head_t, type);
TOMMROC_SCTA_SIZE_OF_SMEMBER_EQUALS(tommRoC_hw_template_ble_ibeacon_head_t, company_id,     esp_ble_ibeacon_head_t, company_id);
TOMMROC_SCTA_SIZE_OF_SMEMBER_EQUALS(tommRoC_hw_template_ble_ibeacon_head_t, beacon_type,    esp_ble_ibeacon_head_t, beacon_type);

TOMMROC_SCTA_SIZE_OF_SMEMBER_EQUALS(tommRoC_hw_template_ble_ibeacon_vendor_t,   proximity_uuid, esp_ble_ibeacon_vendor_t,   proximity_uuid);
TOMMROC_SCTA_SIZE_OF_SMEMBER_EQUALS(tommRoC_hw_template_ble_ibeacon_vendor_t,   major,          esp_ble_ibeacon_vendor_t,   major);
TOMMROC_SCTA_SIZE_OF_SMEMBER_EQUALS(tommRoC_hw_template_ble_ibeacon_vendor_t,   minor,          esp_ble_ibeacon_vendor_t,   minor);
TOMMROC_SCTA_SIZE_OF_SMEMBER_EQUALS(tommRoC_hw_template_ble_ibeacon_vendor_t,   measured_power, esp_ble_ibeacon_vendor_t,   measured_power);

TOMMROC_SCTA_EQUALS(TOMMROC_HW_COMM_BLE_UUID_16_BIT_BYTE_SIZE,  ESP_UUID_LEN_16);
TOMMROC_SCTA_EQUALS(TOMMROC_HW_COMM_BLE_UUID_32_BIT_BYTE_SIZE,  ESP_UUID_LEN_32);
TOMMROC_SCTA_EQUALS(TOMMROC_HW_COMM_BLE_UUID_128_BIT_BYTE_SIZE, ESP_UUID_LEN_128);

typedef struct {

    esp_gattc_cb_t  gattc_cb;
    esp_gatt_if_t   gattc_if;
    uint16_t        app_id;
    uint16_t        conn_id;
    uint16_t        service_start_handle;
    uint16_t        service_end_handle;
    uint16_t        to_write_char_handle;
    uint16_t        notify_char_handle;
    esp_bd_addr_t   remote_bda;

} __gattc_profile_inst_t__;

#define __EMPTY___gattc_profile_inst_t____                      \
{                                                               \
    /* .gattc_cb */             _gattc_profile_event_handler,   \
    /* .gattc_if */             ESP_GATT_IF_NONE,               \
    /* .app_id */               0,                              \
    /* .conn_id */              0,                              \
    /* .service_start_handle */ 0,                              \
    /* .service_end_handle */   0,                              \
    /* .to_write_char_handle */ 0,                              \
    /* .notify_char_handle */   0,                              \
    /* .remote_bda */           { 0, 0, 0, 0, 0, 0, },          \
}

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_DEBUG_ENABLE__)
static const char __DEBUG_OBJ_ID__[] = "hwTempBLEBlueDroid";
#endif

static const esp_ble_scan_params_t _scan_params_duplicate_disable = {
        .scan_type          = BLE_SCAN_TYPE_ACTIVE,
        .own_addr_type      = BLE_ADDR_TYPE_PUBLIC,
        .scan_filter_policy = BLE_SCAN_FILTER_ALLOW_ALL,
        .scan_interval      = 0x06E1,
        .scan_window        = 0x06E0,
        .scan_duplicate     = BLE_SCAN_DUPLICATE_DISABLE,   // NOTE: BLE_SCAN_DUPLICATE_DISABLE means that Link Layer should generate advertising reports to the application for each packet received.
};

static const esp_ble_scan_params_t _scan_params_duplicate_enable = {
        .scan_type          = BLE_SCAN_TYPE_ACTIVE,
        .own_addr_type      = BLE_ADDR_TYPE_PUBLIC,
        .scan_filter_policy = BLE_SCAN_FILTER_ALLOW_ALL,
        .scan_interval      = 0x06E1,
        .scan_window        = 0x06E0,
        .scan_duplicate     = BLE_SCAN_DUPLICATE_ENABLE,    // NOTE: BLE_SCAN_DUPLICATE_ENABLE means that Link Layer filter out duplicate advertising reports to the application.
};

static const esp_bt_uuid_t _notify_descr_uuid = {
        .len = ESP_UUID_LEN_16,
        .uuid = {.uuid16 = ESP_GATT_UUID_CHAR_CLIENT_CONFIG,},
};

static bool _is_peripheral = false;

static tommRoC_hw_template_ble_central_generic_scan_funct_t     _generic_scan_funct_ptr     = NULL;
static tommRoC_hw_template_ble_central_ibeacon_scan_funct_t     _ibeacon_scan_funct_ptr     = NULL;
static tommRoC_hw_template_ble_central_scan_completed_funct_t   _scan_completed_funct_ptr   = NULL;

static tommRoC_hw_template_ble_env_esp32_blueDroid_notify_funct_t _notify_event_funct_ptr = NULL;

static uint32_t _scan_duration_sec = 0; // Scanning time [sec]. 0 means scan permanently

static bool _is_scan_in_progress    = false;
static bool _is_adv_in_progress     = false;

static __gattc_profile_inst_t__ _gl_profile;

static esp_bt_uuid_t _adv_service_filter_uuid;
static esp_bt_uuid_t _to_write_char_filter_uuid;
static esp_bt_uuid_t _notify_char_filter_uuid;

static bool _connecting = false;
static bool _connected  = false;
static bool _get_server = false;

static bool _writing = false;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static void _gattc_profile_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param) {

    do { // Added to avoid "warning: unreachable code"
        switch (event) {

        case ESP_GATTC_REG_EVT: {
            if (ESP_GATT_OK != param->reg.status) {
                TOMMROC_DEBUG_PRINTLN_PLUS_U32(TOMMRO_C_DEBUG_E_LEVEL, "ESP_GATTC_REG_EVT failed; status=", param->reg.status, TOMMRO_C_UTIL_DECIMAL_FORMAT);
            }
            else {
                TOMMROC_DEBUG_D("ESP_GATTC_REG_EVT success");
            }
            break;
        }

        case ESP_GATTC_CONNECT_EVT: {
            TOMMROC_DEBUG_PRINTLN_PLUS_U32(TOMMRO_C_DEBUG_D_LEVEL, "ESP_GATTC_CONNECT_EVT conn_id=", param->connect.conn_id, TOMMRO_C_UTIL_DECIMAL_FORMAT);
            TOMMROC_DEBUG_PRINTLN_PLUS_U32(TOMMRO_C_DEBUG_D_LEVEL, "ESP_GATTC_CONNECT_EVT if=", gattc_if, TOMMRO_C_UTIL_DECIMAL_FORMAT);

            _gl_profile.conn_id = param->connect.conn_id;
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(_gl_profile.remote_bda, param->connect.remote_bda, sizeof(esp_bd_addr_t)));

            if (ESP_OK != esp_ble_gattc_send_mtu_req(gattc_if, param->connect.conn_id)) {
                TOMMROC_DEBUG_E("esp_ble_gattc_send_mtu_req error!!!");
            }
            break;
        }

        case ESP_GATTC_OPEN_EVT: {
            if (ESP_GATT_OK != param->open.status) {
                TOMMROC_DEBUG_PRINTLN_PLUS_U32(TOMMRO_C_DEBUG_E_LEVEL, "ESP_GATTC_OPEN_EVT failed; status=", param->open.status, TOMMRO_C_UTIL_DECIMAL_FORMAT);
            }
            else {
                TOMMROC_DEBUG_D("ESP_GATTC_OPEN_EVT success");
            }
            break;
        }

        case ESP_GATTC_DIS_SRVC_CMPL_EVT: {
            if (ESP_GATT_OK != param->dis_srvc_cmpl.status) {
                TOMMROC_DEBUG_PRINTLN_PLUS_U32(TOMMRO_C_DEBUG_E_LEVEL, "ESP_GATTC_DIS_SRVC_CMPL_EVT failed; status=", param->dis_srvc_cmpl.status, TOMMRO_C_UTIL_DECIMAL_FORMAT);
            }
            else {
                TOMMROC_DEBUG_D("ESP_GATTC_DIS_SRVC_CMPL_EVT success");
                esp_ble_gattc_search_service(gattc_if, param->cfg_mtu.conn_id, &_adv_service_filter_uuid);
            }
            break;
        }

        case ESP_GATTC_CFG_MTU_EVT: {
            if (ESP_GATT_OK != param->cfg_mtu.status) {
                TOMMROC_DEBUG_PRINTLN_PLUS_U32(TOMMRO_C_DEBUG_E_LEVEL, "ESP_GATTC_CFG_MTU_EVT failed; status=", param->cfg_mtu.status, TOMMRO_C_UTIL_DECIMAL_FORMAT);
            }
            break;
        }

        case ESP_GATTC_SEARCH_RES_EVT: {
            if (_adv_service_filter_uuid.len == param->search_res.srvc_id.uuid.len) {

                do { // Added to avoid "warning: unreachable code"
                    switch (_adv_service_filter_uuid.len) {

                    case ESP_UUID_LEN_16:
                        if (TOMMRO_C_ERR_SUCCESS == tommRoCUtilMemCompare(&param->search_res.srvc_id.uuid.uuid.uuid16, &_adv_service_filter_uuid.uuid.uuid16, ESP_UUID_LEN_16)) {
                            TOMMROC_DEBUG_D("ESP_GATTC_SEARCH_RES_EVT: 16 bit service found");
                            _get_server = true;
                            _gl_profile.service_start_handle    = param->search_res.start_handle;
                            _gl_profile.service_end_handle      = param->search_res.end_handle;
                        }
                        break;

                    case ESP_UUID_LEN_32:
                        if (TOMMRO_C_ERR_SUCCESS == tommRoCUtilMemCompare(&param->search_res.srvc_id.uuid.uuid.uuid32, &_adv_service_filter_uuid.uuid.uuid32, ESP_UUID_LEN_32)) {
                            TOMMROC_DEBUG_D("ESP_GATTC_SEARCH_RES_EVT: 32 bit service found");
                            _get_server = true;
                            _gl_profile.service_start_handle    = param->search_res.start_handle;
                            _gl_profile.service_end_handle      = param->search_res.end_handle;
                        }
                        break;

                    case ESP_UUID_LEN_128:
                        if (TOMMRO_C_ERR_SUCCESS == tommRoCUtilMemCompare(param->search_res.srvc_id.uuid.uuid.uuid128, _adv_service_filter_uuid.uuid.uuid128, ESP_UUID_LEN_128)) {
                            TOMMROC_DEBUG_D("ESP_GATTC_SEARCH_RES_EVT: 128 bit service found");
                            _get_server = true;
                            _gl_profile.service_start_handle    = param->search_res.start_handle;
                            _gl_profile.service_end_handle      = param->search_res.end_handle;
                        }
                        break;

                    default:
                        // If here, ERROR!!!
                        TOMMROC_ASSERT_TRUE(false);
                        break;

                    }
                } while (0);
            }
            break;
        }

        case ESP_GATTC_SEARCH_CMPL_EVT: {
            if (ESP_GATT_OK != param->search_cmpl.status) {
                TOMMROC_DEBUG_PRINTLN_PLUS_U32(TOMMRO_C_DEBUG_E_LEVEL, "ESP_GATTC_SEARCH_CMPL_EVT failed; status=", param->search_cmpl.status, TOMMRO_C_UTIL_DECIMAL_FORMAT);
            }
            else {
                if (ESP_GATT_SERVICE_FROM_REMOTE_DEVICE == param->search_cmpl.searched_service_source) {
                    TOMMROC_DEBUG_D("ESP_GATTC_SEARCH_CMPL_EVT: get srvc info from device");
                }
                else if (ESP_GATT_SERVICE_FROM_NVS_FLASH == param->search_cmpl.searched_service_source) {
                    TOMMROC_DEBUG_D("ESP_GATTC_SEARCH_CMPL_EVT: get srvc info from flash");
                }
                else {
                    TOMMROC_DEBUG_D("ESP_GATTC_SEARCH_CMPL_EVT: unknown service source");
                }

                if (_get_server) {

                    uint16_t count = 0;
                    esp_gatt_status_t status;
                    esp_gattc_char_elem_t* char_elem_result = NULL;

                    status = esp_ble_gattc_get_attr_count(
                            gattc_if,
                            param->search_cmpl.conn_id,
                            ESP_GATT_DB_CHARACTERISTIC,
                            _gl_profile.service_start_handle,
                            _gl_profile.service_end_handle,
                            __INVALID_HANDLE__,
                            &count);

                    if (ESP_GATT_OK != status) {
                        TOMMROC_DEBUG_E("esp_ble_gattc_get_attr_count error!!!");
                        return;
                    }

                    TOMMROC_DEBUG_PRINTLN_PLUS_U16(TOMMRO_C_DEBUG_D_LEVEL, "ESP_GATTC_SEARCH_CMPL_EVT; count=", count, TOMMRO_C_UTIL_DECIMAL_FORMAT);

                    if (count > 0) {

                        char_elem_result = (esp_gattc_char_elem_t*) malloc(sizeof(esp_gattc_char_elem_t) * count);
                        if (!char_elem_result){
                            TOMMROC_DEBUG_E("gattc no mem error!!!");
                            return;
                        }

                        status = esp_ble_gattc_get_char_by_uuid(
                                gattc_if,
                                param->search_cmpl.conn_id,
                                _gl_profile.service_start_handle,
                                _gl_profile.service_end_handle,
                                _to_write_char_filter_uuid,
                                char_elem_result,
                                &count);

                        if (ESP_GATT_OK != status) {
                            TOMMROC_DEBUG_E("esp_ble_gattc_get_char_by_uuid _to_write_char_filter_uuid error!!!");
                            free(char_elem_result);
                            char_elem_result = NULL;
                            return;
                        }

                        // NOTE: suppose that every service have only one char, so we used first 'char_elem_result'
                        if ((count > 0) && ((char_elem_result[0].properties & ESP_GATT_CHAR_PROP_BIT_WRITE) || (char_elem_result[0].properties & ESP_GATT_CHAR_PROP_BIT_WRITE_NR))) {
                            _gl_profile.to_write_char_handle = char_elem_result[0].char_handle;
                        }
                        else {
                            TOMMROC_DEBUG_E("ESP_GATTC_SEARCH_CMPL_EVT: to_write_char_handle not found");
                        }


                        status = esp_ble_gattc_get_char_by_uuid(
                                gattc_if,
                                param->search_cmpl.conn_id,
                                _gl_profile.service_start_handle,
                                _gl_profile.service_end_handle,
                                _notify_char_filter_uuid,
                                char_elem_result,
                                &count);

                        if (ESP_GATT_OK != status) {
                            TOMMROC_DEBUG_E("esp_ble_gattc_get_char_by_uuid _notify_char_filter_uuid error!!!");
                            free(char_elem_result);
                            char_elem_result = NULL;
                            return;
                        }

                        // NOTE: suppose that every service have only one char, so we used first 'char_elem_result'
                        if ((count > 0) && (char_elem_result[0].properties & ESP_GATT_CHAR_PROP_BIT_NOTIFY)) {
                            _gl_profile.notify_char_handle = char_elem_result[0].char_handle;
                            if (ESP_OK != esp_ble_gattc_register_for_notify(gattc_if, _gl_profile.remote_bda, char_elem_result[0].char_handle)) {
                                TOMMROC_DEBUG_E("esp_ble_gattc_register_for_notify error!!!");
                            }
                            else {
                                TOMMROC_DEBUG_D("esp_ble_gattc_register_for_notify success");
                            }
                        }
                        else {
                            TOMMROC_DEBUG_E("ESP_GATTC_SEARCH_CMPL_EVT: notify_char_handle not found");
                        }

                        free(char_elem_result);
                        char_elem_result = NULL;
                    }
                    else {
                        TOMMROC_DEBUG_E("no char found");
                    }
                }
            }
            break;
        }

        case ESP_GATTC_REG_FOR_NOTIFY_EVT: {
            if (ESP_GATT_OK != param->reg_for_notify.status) {
                TOMMROC_DEBUG_PRINTLN_PLUS_U32(TOMMRO_C_DEBUG_E_LEVEL, "ESP_GATTC_REG_FOR_NOTIFY_EVT failed; status=", param->reg_for_notify.status, TOMMRO_C_UTIL_DECIMAL_FORMAT);
            }
            else {

                uint16_t count = 0;
                uint16_t notify_en = 1;
                esp_gatt_status_t status;
                esp_gattc_descr_elem_t* descr_elem_result = NULL;

                status = esp_ble_gattc_get_attr_count(
                        gattc_if,
                        _gl_profile.conn_id,
                        ESP_GATT_DB_DESCRIPTOR,
                        _gl_profile.service_start_handle,
                        _gl_profile.service_end_handle,
                        _gl_profile.notify_char_handle,
                        &count);

                if (ESP_GATT_OK != status) {
                    TOMMROC_DEBUG_E("esp_ble_gattc_get_attr_count error!!!");
                    return;
                }

                TOMMROC_DEBUG_PRINTLN_PLUS_U16(TOMMRO_C_DEBUG_D_LEVEL, "ESP_GATTC_REG_FOR_NOTIFY_EVT; count=", count, TOMMRO_C_UTIL_DECIMAL_FORMAT);

                if (count > 0) {

                    descr_elem_result = (esp_gattc_descr_elem_t*) malloc(sizeof(esp_gattc_descr_elem_t) * count);
                    if (!descr_elem_result) {
                        TOMMROC_DEBUG_E("gattc no mem error!!!");
                        return;
                    }

                    status = esp_ble_gattc_get_descr_by_char_handle(
                            gattc_if,
                            _gl_profile.conn_id,
                            param->reg_for_notify.handle,
                            _notify_descr_uuid,
                            descr_elem_result,
                            &count);

                    if (ESP_GATT_OK != status) {
                        TOMMROC_DEBUG_E("esp_ble_gattc_get_descr_by_char_handle error!!!");
                        free(descr_elem_result);
                        descr_elem_result = NULL;
                        return;
                    }

                    // NOTE: suppose that every char has only one descriptor, so we used first 'descr_elem_result'
                    if ((count > 0) && (descr_elem_result[0].uuid.len == ESP_UUID_LEN_16) && (descr_elem_result[0].uuid.uuid.uuid16 == ESP_GATT_UUID_CHAR_CLIENT_CONFIG)) {
                        if (ESP_OK != esp_ble_gattc_write_char_descr(
                                gattc_if,
                                _gl_profile.conn_id,
                                descr_elem_result[0].handle,
                                sizeof(notify_en),
                                (uint8_t *)&notify_en,
                                ESP_GATT_WRITE_TYPE_RSP,
                                ESP_GATT_AUTH_REQ_NONE)) {
                            TOMMROC_DEBUG_E("esp_ble_gattc_write_char_descr error!!!");
                        }
                        else {
                            TOMMROC_DEBUG_D("esp_ble_gattc_write_char_descr success");

                            _connecting = false;
                            _connected  = true;
                        }
                    }

                    free(descr_elem_result);
                    descr_elem_result = NULL;
                }
                else {
                    TOMMROC_DEBUG_E("decsr not found");
                }
            }
            break;
        }

        case ESP_GATTC_NOTIFY_EVT: {
            if (param->notify.is_notify) {
                TOMMROC_DEBUG_D("ESP_GATTC_NOTIFY_EVT: received notify");
            }
            else{
                TOMMROC_DEBUG_D("ESP_GATTC_NOTIFY_EVT: received indicate");
            }

            if (NULL != _notify_event_funct_ptr) {
                TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
                        _notify_event_funct_ptr(
                                param->notify.conn_id,
                                param->notify.handle,
                                param->notify.value,
                                param->notify.value_len));
            }
            break;
        }

        case ESP_GATTC_WRITE_DESCR_EVT: {
            if (ESP_GATT_OK != param->write.status) {
                TOMMROC_DEBUG_PRINTLN_PLUS_U32(TOMMRO_C_DEBUG_E_LEVEL, "ESP_GATTC_WRITE_CHAR_EVT failed; status=", param->write.status, TOMMRO_C_UTIL_DECIMAL_FORMAT);
            }
            break;
        }

        case ESP_GATTC_SRVC_CHG_EVT: {
            TOMMROC_DEBUG_D("ESP_GATTC_SRVC_CHG_EVT");
            break;
        }

        case ESP_GATTC_WRITE_CHAR_EVT: {
            if (ESP_GATT_OK != param->write.status) {
                TOMMROC_DEBUG_PRINTLN_PLUS_U32(TOMMRO_C_DEBUG_E_LEVEL, "ESP_GATTC_WRITE_CHAR_EVT failed; status=", param->write.status, TOMMRO_C_UTIL_DECIMAL_FORMAT);
            }
            else {
                _writing = false;
            }
            break;
        }

        case ESP_GATTC_DISCONNECT_EVT: {
            TOMMROC_DEBUG_PRINTLN_PLUS_U32(TOMMRO_C_DEBUG_E_LEVEL, "ESP_GATTC_DISCONNECT_EVT; reason=", param->disconnect.reason, TOMMRO_C_UTIL_DECIMAL_FORMAT);
            _connected  = false;
            _connecting = false;
            _get_server = false;
            _writing    = false;
            break;
        }

        default:
            break;

        }
    } while (0);
}

static void _esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param) {

    tommRoC_hw_template_ble_ibeacon_t ibeacon;

    esp_err_t err;

    do { // Added to avoid "warning: unreachable code"
        switch (event) {

        case ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT: {
            if (ESP_OK != esp_ble_gap_start_scanning(_scan_duration_sec)) {
                TOMMROC_DEBUG_E("esp_ble_gap_start_scanning error!!!");
            }
            break;
        }

        case ESP_GAP_BLE_SCAN_START_COMPLETE_EVT: {
            // Scan start complete event to indicate scan start successfully or failed
            if ((err = param->scan_start_cmpl.status) != ESP_BT_STATUS_SUCCESS) {
                TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "Scan start failed: ", esp_err_to_name(err));
            }
            else {
                _is_scan_in_progress = true;
            }
            break;
        }

        case ESP_GAP_BLE_ADV_START_COMPLETE_EVT: {
            // Adv start complete event to indicate adv start successfully or failed
            if ((err = param->adv_start_cmpl.status) != ESP_BT_STATUS_SUCCESS) {
                TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "Adv start failed: ", esp_err_to_name(err));
            }
            else {
                _is_adv_in_progress = true;
            }
            break;
        }

        case ESP_GAP_BLE_SCAN_RESULT_EVT: {
            esp_ble_gap_cb_param_t* scan_result = (esp_ble_gap_cb_param_t*) param;

            do { // Added to avoid "warning: unreachable code"
                switch (scan_result->scan_rst.search_evt) {

                case ESP_GAP_SEARCH_INQ_CMPL_EVT: {
                    // Scan is done. Scan timeout has expired
                    _is_scan_in_progress = false;
                    if (NULL != _scan_completed_funct_ptr) {
                        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(_scan_completed_funct_ptr());
                    }
                }
                break;

                case ESP_GAP_SEARCH_INQ_RES_EVT: {
                    // if generic scan selected
                    if (NULL != _generic_scan_funct_ptr) {
                        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(_generic_scan_funct_ptr((void*) &scan_result->scan_rst));
                    }

                    // if iBeacon scan selected
                    if (NULL != _ibeacon_scan_funct_ptr) {
                        // Search for BLE iBeacon Packet
                        if (esp_ble_is_ibeacon_packet(scan_result->scan_rst.ble_adv, scan_result->scan_rst.adv_data_len)) {

                            esp_ble_ibeacon_t* ibeacon_data = (esp_ble_ibeacon_t*) (scan_result->scan_rst.ble_adv);

                            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(ibeacon.BLEMACAddr, scan_result->scan_rst.bda, sizeof(ibeacon.BLEMACAddr)));
                            ibeacon.rssi = (int32_t) scan_result->scan_rst.rssi;

                            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(ibeacon.head.flags, ibeacon_data->ibeacon_head.flags, sizeof(ibeacon.head.flags)));
                            ibeacon.head.length         = ibeacon_data->ibeacon_head.length;
                            ibeacon.head.type           = ibeacon_data->ibeacon_head.type;
                            ibeacon.head.company_id     = ibeacon_data->ibeacon_head.company_id;
                            ibeacon.head.beacon_type    = ibeacon_data->ibeacon_head.beacon_type;

                            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(ibeacon.vendor.proximity_uuid, ibeacon_data->ibeacon_vendor.proximity_uuid, sizeof(ibeacon.vendor.proximity_uuid)));
                            ibeacon.vendor.major            = ENDIAN_CHANGE_U16(ibeacon_data->ibeacon_vendor.major);
                            ibeacon.vendor.minor            = ENDIAN_CHANGE_U16(ibeacon_data->ibeacon_vendor.minor);
                            ibeacon.vendor.measured_power   = ibeacon_data->ibeacon_vendor.measured_power;

                            TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(_ibeacon_scan_funct_ptr(&ibeacon));
                        }
                    }
                    break;
                }

                default:
                    break;

                }
            } while (0);

            break;
        }

        case ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT:  {
            if ((err = param->scan_stop_cmpl.status) != ESP_BT_STATUS_SUCCESS) {
                TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "Scan stop failed: ", esp_err_to_name(err));
            }
            else {
                _is_scan_in_progress = false;
            }
            break;
        }

        case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT: {
            if ((err = param->adv_stop_cmpl.status) != ESP_BT_STATUS_SUCCESS) {
                TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "Adv stop failed: ", esp_err_to_name(err));
            }
            else {
                _is_adv_in_progress = false;
            }
            break;
        }

        default:
            break;

        }
    } while (0);
}

static void _esp_gattc_cb(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param) {

    // If event is register event, store the gattc_if for each profile
    if (ESP_GATTC_REG_EVT == event) {
        if (ESP_GATT_OK == param->reg.status) {
            _gl_profile.gattc_if = gattc_if;
        }
        else {
            return;
        }
    }

    // If the gattc_if equal to profile, call profile cb handler, so here call each profile's callback
    if ((ESP_GATT_IF_NONE == gattc_if) || (gattc_if == _gl_profile.gattc_if)) {
        if (NULL != _gl_profile.gattc_cb) {
            _gl_profile.gattc_cb(event, gattc_if, param);
        }
    }
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* Standard BLE functions */

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEPeripheralInit(const char* const deviceBLENameStrPtr) {
    TOMMROC_ASSERT_NOT_NULL(deviceBLENameStrPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEPeripheralDeInit(void) {
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLECentralInit(void) {

    static const __gattc_profile_inst_t__ glProfileEmpty = TOMMROC_UTIL_EMPTY_VARIABLE(__gattc_profile_inst_t__);

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&_gl_profile, &glProfileEmpty, sizeof(__gattc_profile_inst_t__)));

    if (ESP_OK != esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT)) {
        TOMMROC_DEBUG_E("esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT) error!!!");
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (ESP_OK != esp_bt_controller_init(&bt_cfg)) {
        TOMMROC_DEBUG_E("esp_bt_controller_init error!!!");
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (ESP_OK != esp_bt_controller_enable(ESP_BT_MODE_BLE)) {
        TOMMROC_DEBUG_E("esp_bt_controller_enable(ESP_BT_MODE_BLE) error!!!");
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (ESP_OK != esp_bluedroid_init()) {
        TOMMROC_DEBUG_E("esp_bluedroid_init error!!!");
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (ESP_OK != esp_bluedroid_enable()) {
        TOMMROC_DEBUG_E("esp_bluedroid_enable error!!!");
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    // Register the scan callback function to the gap module
    if (ESP_OK != esp_ble_gap_register_callback(_esp_gap_cb)) {
        TOMMROC_DEBUG_E("esp_ble_gap_register_callback error!!!");
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    // Register the callback function to the gattc module
    if (ESP_OK != esp_ble_gattc_register_callback(_esp_gattc_cb)) {
        TOMMROC_DEBUG_E("esp_ble_gattc_register_callback error!!!");
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (ESP_OK != esp_ble_gattc_app_register(0)) {
        TOMMROC_DEBUG_E("esp_ble_gattc_app_register error!!!");
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (ESP_OK != esp_ble_gatt_set_local_mtu(500)) {
        TOMMROC_DEBUG_E("esp_ble_gatt_set_local_mtu error!!!");
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    _is_peripheral = false;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLECentralDeInit(void) {

    if (ESP_OK != esp_bluedroid_disable()) {
        TOMMROC_DEBUG_E("esp_bluedroid_disable error!!!");
    }
    if (ESP_OK != esp_bluedroid_deinit()) {
        TOMMROC_DEBUG_E("esp_bluedroid_deinit error!!!");
    }

    if (ESP_OK != esp_bt_controller_disable()) {
        TOMMROC_DEBUG_E("esp_bt_controller_disable error!!!");
    }
    if (ESP_OK != esp_bt_controller_deinit()) {
        TOMMROC_DEBUG_E("esp_bt_controller_deinit error!!!");
    }

    _is_peripheral = false;

    return TOMMRO_C_HW_ERR_SUCCESS;
}


tommRoC_hw_err_enum_t tommRoCHwTemplateBLEPeripheralADVStart(const char* const deviceBLENameStrPtr) {
    TOMMROC_ASSERT_NOT_NULL(deviceBLENameStrPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEPeripheralADVStop(void) {
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEPeripheralADVResume(void) {
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
}


tommRoC_hw_err_enum_t tommRoCHwTemplateBLECentralGenericScanStart(
        const   tommRoC_hw_template_ble_central_generic_scan_funct_t    scanFunctPtr,
        const   tommRoC_hw_template_ble_central_scan_completed_funct_t  scanCompletedFunctPtr,
        const   uint32_t                                                scanDurationSec) {

    if (_is_peripheral) {
        return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
    }

    if (_connecting) {
        return TOMMRO_C_HW_BLE_CONNECTED_ERR;
    }
    if (_connected) {
        return TOMMRO_C_HW_BLE_CONNECTED_ERR;
    }
    if (_writing) {
        return TOMMRO_C_HW_BLE_CONNECTED_ERR;
    }

    _generic_scan_funct_ptr     = scanFunctPtr;
    _ibeacon_scan_funct_ptr     = NULL;
    _scan_completed_funct_ptr   = scanCompletedFunctPtr;
    _scan_duration_sec          = scanDurationSec;

    // Scan only once
    if (ESP_OK != esp_ble_gap_set_scan_params((esp_ble_scan_params_t*) &_scan_params)) {
        TOMMROC_DEBUG_E("esp_ble_gap_set_scan_params error!!!");
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLECentralBeaconScanStart(
        const   tommRoC_hw_template_ble_central_ibeacon_scan_funct_t    scanFunctPtr,
        const   tommRoC_hw_template_ble_central_scan_completed_funct_t  scanCompletedFunctPtr,
        const   uint32_t                                                beaconScanDurationSec) {

    if (_is_peripheral) {
        return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
    }

    if (_connecting) {
        return TOMMRO_C_HW_BLE_CONNECTED_ERR;
    }
    if (_connected) {
        return TOMMRO_C_HW_BLE_CONNECTED_ERR;
    }
    if (_writing) {
        return TOMMRO_C_HW_BLE_CONNECTED_ERR;
    }

    _generic_scan_funct_ptr     = NULL;
    _ibeacon_scan_funct_ptr     = scanFunctPtr;
    _scan_completed_funct_ptr   = scanCompletedFunctPtr;
    _scan_duration_sec          = beaconScanDurationSec;

    // Scan only once
    if (ESP_OK != esp_ble_gap_set_scan_params((esp_ble_scan_params_t*) &_scan_params)) {
        TOMMROC_DEBUG_E("esp_ble_gap_set_scan_params error!!!");
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLECentralConnect(
        const   uint8_t*                                        const   BLEMACAddrPtr,
        const   uint8_t                                                 BLEMACAddrSize,
        const   tommRoC_hw_comm_ble_uuid_len_type_enum_t                advServiceUUIDLenType,
        const   void*                                           const   advServiceUUIDPtr,
        const   uint8_t                                                 advServiceUUIDSize,
        const   tommRoC_hw_comm_ble_uuid_len_type_enum_t                toWriteCharUUIDLenType,
        const   void*                                           const   toWriteCharUUIDPtr,
        const   uint8_t                                                 toWriteCharUUIDSize,
        const   tommRoC_hw_comm_ble_uuid_len_type_enum_t                notifyCharUUIDLenType,
        const   void*                                           const   notifyCharUUIDPtr,
        const   uint8_t                                                 notifyCharUUIDSize) {

    tommRoC_timer_t timer;

    TOMMROC_ASSERT_NOT_NULL(BLEMACAddrPtr);
    TOMMROC_ASSERT_EQUALS(BLEMACAddrSize, TOMMROC_HW_COMM_BLE_MAC_ADDRESS_SIZE_BYTE);
    TOMMROC_ASSERT_NOT_NULL(advServiceUUIDPtr);
    TOMMROC_ASSERT_NOT_ZERO(advServiceUUIDSize);
    TOMMROC_ASSERT_NOT_NULL(toWriteCharUUIDPtr);
    TOMMROC_ASSERT_NOT_ZERO(toWriteCharUUIDSize);
    TOMMROC_ASSERT_NOT_NULL(notifyCharUUIDPtr);
    TOMMROC_ASSERT_NOT_ZERO(notifyCharUUIDSize);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(BLEMACAddrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_TEST_RETURN_ERR(BLEMACAddrSize, !=, TOMMROC_HW_COMM_BLE_MAC_ADDRESS_SIZE_BYTE);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(advServiceUUIDPtr);
    TOMMROC_HW_PARAM_CHECK_ON_ZERO_RETURN_ERR(advServiceUUIDSize);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(toWriteCharUUIDPtr);
    TOMMROC_HW_PARAM_CHECK_ON_ZERO_RETURN_ERR(toWriteCharUUIDSize);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(notifyCharUUIDPtr);
    TOMMROC_HW_PARAM_CHECK_ON_ZERO_RETURN_ERR(notifyCharUUIDSize);

    if (_is_peripheral) {
        return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
    }

    if (_connecting) {
        return TOMMRO_C_HW_BLE_CONNECTED_ERR;
    }
    if (_connected) {
        return TOMMRO_C_HW_BLE_CONNECTED_ERR;
    }
    if (_writing) {
        return TOMMRO_C_HW_BLE_CONNECTED_ERR;
    }

    do { // Added to avoid "warning: unreachable code"
        switch (advServiceUUIDLenType) {
        case TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_16_BIT:
            if (advServiceUUIDSize != TOMMROC_HW_COMM_BLE_UUID_16_BIT_BYTE_SIZE) { return TOMMRO_C_HW_PARAM_ERR; }
            break;
        case TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_32_BIT:
            if (advServiceUUIDSize != TOMMROC_HW_COMM_BLE_UUID_32_BIT_BYTE_SIZE) { return TOMMRO_C_HW_PARAM_ERR; }
            break;
        case TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_128_BIT:
            if (advServiceUUIDSize != TOMMROC_HW_COMM_BLE_UUID_128_BIT_BYTE_SIZE) { return TOMMRO_C_HW_PARAM_ERR; }
            break;

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            return TOMMRO_C_HW_PARAM_ERR;
        }
    } while (0);

    do { // Added to avoid "warning: unreachable code"
        switch (toWriteCharUUIDLenType) {
        case TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_16_BIT:
            if (toWriteCharUUIDSize != TOMMROC_HW_COMM_BLE_UUID_16_BIT_BYTE_SIZE) { return TOMMRO_C_HW_PARAM_ERR; }
            break;
        case TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_32_BIT:
            if (toWriteCharUUIDSize != TOMMROC_HW_COMM_BLE_UUID_32_BIT_BYTE_SIZE) { return TOMMRO_C_HW_PARAM_ERR; }
            break;
        case TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_128_BIT:
            if (toWriteCharUUIDSize != TOMMROC_HW_COMM_BLE_UUID_128_BIT_BYTE_SIZE) { return TOMMRO_C_HW_PARAM_ERR; }
            break;

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            return TOMMRO_C_HW_PARAM_ERR;
        }
    } while (0);

    do { // Added to avoid "warning: unreachable code"
        switch (notifyCharUUIDLenType) {
        case TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_16_BIT:
            if (notifyCharUUIDSize != TOMMROC_HW_COMM_BLE_UUID_16_BIT_BYTE_SIZE) { return TOMMRO_C_HW_PARAM_ERR; }
            break;
        case TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_32_BIT:
            if (notifyCharUUIDSize != TOMMROC_HW_COMM_BLE_UUID_32_BIT_BYTE_SIZE) { return TOMMRO_C_HW_PARAM_ERR; }
            break;
        case TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_128_BIT:
            if (notifyCharUUIDSize != TOMMROC_HW_COMM_BLE_UUID_128_BIT_BYTE_SIZE) { return TOMMRO_C_HW_PARAM_ERR; }
            break;

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            return TOMMRO_C_HW_PARAM_ERR;
        }
    } while (0);

    if (_is_scan_in_progress) {

        if (ESP_OK != esp_ble_gap_stop_scanning()) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, __STOP_SCANNING_WAIT_TIMEOUT_MSEC__));

        while (_is_scan_in_progress) {

            if (TOMMRO_C_TIMER_EXPIRED_ERR == tommRoCTimerIsExpired(&timer)) {
                return TOMMRO_C_HW_TIMEOUT_ERR;
            }

            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(0));
        }
    }

    do { // Added to avoid "warning: unreachable code"
        switch (advServiceUUIDLenType) {
        case TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_16_BIT:
            _adv_service_filter_uuid.len = ESP_UUID_LEN_16;
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&_adv_service_filter_uuid.uuid.uuid16, advServiceUUIDPtr, advServiceUUIDSize));
            break;

        case TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_32_BIT:
            _adv_service_filter_uuid.len = ESP_UUID_LEN_32;
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&_adv_service_filter_uuid.uuid.uuid32, advServiceUUIDPtr, advServiceUUIDSize));
            break;

        case TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_128_BIT:
            _adv_service_filter_uuid.len = ESP_UUID_LEN_128;
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(_adv_service_filter_uuid.uuid.uuid128, advServiceUUIDPtr, advServiceUUIDSize));
            break;

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }
    } while (0);

    do { // Added to avoid "warning: unreachable code"
        switch (toWriteCharUUIDLenType) {
        case TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_16_BIT:
            _to_write_char_filter_uuid.len = ESP_UUID_LEN_16;
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&_to_write_char_filter_uuid.uuid.uuid16, toWriteCharUUIDPtr, toWriteCharUUIDSize));
            break;

        case TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_32_BIT:
            _to_write_char_filter_uuid.len = ESP_UUID_LEN_32;
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&_to_write_char_filter_uuid.uuid.uuid32, toWriteCharUUIDPtr, toWriteCharUUIDSize));
            break;

        case TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_128_BIT:
            _to_write_char_filter_uuid.len = ESP_UUID_LEN_128;
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(_to_write_char_filter_uuid.uuid.uuid128, toWriteCharUUIDPtr, toWriteCharUUIDSize));
            break;

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }
    } while (0);

    do { // Added to avoid "warning: unreachable code"
        switch (notifyCharUUIDLenType) {
        case TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_16_BIT:
            _notify_char_filter_uuid.len = ESP_UUID_LEN_16;
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&_notify_char_filter_uuid.uuid.uuid16, notifyCharUUIDPtr, notifyCharUUIDSize));
            break;

        case TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_32_BIT:
            _notify_char_filter_uuid.len = ESP_UUID_LEN_32;
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&_notify_char_filter_uuid.uuid.uuid32, notifyCharUUIDPtr, notifyCharUUIDSize));
            break;

        case TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_128_BIT:
            _notify_char_filter_uuid.len = ESP_UUID_LEN_128;
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(_notify_char_filter_uuid.uuid.uuid128, notifyCharUUIDPtr, notifyCharUUIDSize));
            break;

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }
    } while (0);

    _connecting = false;
    _connected  = false;
    _get_server = false;
    _writing    = false;

    _connecting = true;

    TOMMROC_DEBUG_D("connecting...");

    if (ESP_OK != esp_ble_gattc_open(_gl_profile.gattc_if, (uint8_t*) BLEMACAddrPtr, BLE_ADDR_TYPE_PUBLIC, true)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, __CONNECT_TIMEOUT_FOR_BYTE_MSEC__));

    while (!_connected) {

        if (TOMMRO_C_TIMER_EXPIRED_ERR == tommRoCTimerIsExpired(&timer)) {
            TOMMROC_DEBUG_D("connect timeout expired");
            return TOMMRO_C_HW_TIMEOUT_ERR;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1));
    }

    TOMMROC_DEBUG_D("connected");

    return TOMMRO_C_HW_ERR_SUCCESS;
}


tommRoC_hw_err_enum_t tommRoCHwTemplateBLEDisconnect(void) {

    tommRoC_timer_t timer;

    if (_connecting) {
        return TOMMRO_C_HW_BLE_CONNECTED_ERR;
    }
    if (!_connected) {
        return TOMMRO_C_HW_BLE_CONNECTED_ERR;
    }
    if (_writing) {
        return TOMMRO_C_HW_BLE_CONNECTED_ERR;
    }

    TOMMROC_DEBUG_D("disconnecting...");

    if (ESP_OK != esp_ble_gattc_close(_gl_profile.gattc_if, _gl_profile.conn_id)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, __DISCONNECT_TIMEOUT_FOR_BYTE_MSEC__));

    while (_connected) {

        if (TOMMRO_C_TIMER_EXPIRED_ERR == tommRoCTimerIsExpired(&timer)) {
            TOMMROC_DEBUG_D("disconnect timeout expired");
            return TOMMRO_C_HW_TIMEOUT_ERR;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1));
    }

    TOMMROC_DEBUG_D("disconnected");

    _connecting = false;
    _connected  = false;
    _get_server = false;
    _writing    = false;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

bool tommRoCHwTemplateBLEIsConnected(void) {
    return _connected;
}


tommRoC_hw_err_enum_t tommRoCHwTemplateBLEWrite(
        const   void*                                           const   dataBufferPtr,
        const   uint32_t                                                dataBufferSize,
        const   bool                                                    writeWithRsp) {

    tommRoC_timer_t timer;

    TOMMROC_ASSERT_NOT_NULL(dataBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(dataBufferSize);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(dataBufferPtr);
    TOMMROC_HW_PARAM_CHECK_ON_ZERO_RETURN_ERR(dataBufferSize);

    if (_connecting) {
        return TOMMRO_C_HW_BLE_CONNECTED_ERR;
    }
    if (!_connected) {
        return TOMMRO_C_HW_BLE_CONNECTED_ERR;
    }
    if (_writing) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (ESP_OK != esp_ble_gattc_write_char(_gl_profile.gattc_if, _gl_profile.conn_id, _gl_profile.to_write_char_handle, dataBufferSize, (uint8_t*) dataBufferPtr, (writeWithRsp) ? (ESP_GATT_WRITE_TYPE_RSP) : (ESP_GATT_WRITE_TYPE_NO_RSP), ESP_GATT_AUTH_REQ_NONE)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    _writing = true;

    TOMMROC_DEBUG_D("writing...");

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, __WRITE_TIMEOUT_FOR_BYTE_MSEC__ * dataBufferSize));

    while (_writing) {

        if (TOMMRO_C_TIMER_EXPIRED_ERR == tommRoCTimerIsExpired(&timer)) {
            TOMMROC_DEBUG_D("write timeout expired");
            return TOMMRO_C_HW_TIMEOUT_ERR;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1));
    }

    TOMMROC_DEBUG_D("written");

    return TOMMRO_C_HW_ERR_SUCCESS;
}


/******************* Specific BlueDroid functions */

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEEnvESP32BlueDroidGetProp(
        const   tommRoC_hw_template_ble_env_esp32_bluedroid_prop_enum_t         property,
                void*                                                   const   propValuePtr) {

    TOMMROC_ASSERT_NOT_NULL(propValuePtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(propValuePtr);

    do { // Added to avoid "warning: unreachable code"
        switch (property) {

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            return TOMMRO_C_HW_PARAM_ERR;

        }
    } while (0);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEEnvESP32BlueDroidSetProp(
        const   tommRoC_hw_template_ble_env_esp32_bluedroid_prop_enum_t         property,
        const   void*                                                   const   propValuePtr) {

    TOMMROC_ASSERT_NOT_NULL(propValuePtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(propValuePtr);

    do { // Added to avoid "warning: unreachable code"
        switch (property) {

        case TOMMROC_HW_TEMPLATE_BLE_ENV_ESP32_BLUE_DROID_NOTIFY_FUNCT:
            _notify_event_funct_ptr = (tommRoC_hw_template_ble_env_esp32_blueDroid_notify_funct_t) propValuePtr;
            break;

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            return TOMMRO_C_HW_PARAM_ERR;

        }
    } while (0);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

#endif

#endif
