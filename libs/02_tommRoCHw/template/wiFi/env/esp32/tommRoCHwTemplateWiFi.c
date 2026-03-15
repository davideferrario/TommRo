
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateWiFi.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)

#include "env/tommRoCTemplateEnv.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"

#if (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
#include "lwip/ip4_addr.h"
#endif

#include "lwip/err.h"
#include "lwip/sys.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define WIFI_CONNECTED_BIT          (BIT0)
#define WIFI_FAIL_BIT               (BIT1)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_DEBUG_ENABLE__)
static const char __DEBUG_OBJ_ID__[] = "hwTempWiFi";
#endif

// Event group
static EventGroupHandle_t _wifi_event_group = NULL;

static uint32_t _connect_retry_amount   = TOMMROC_HW_TEMPLATE_WIFI_CONNECT_RETRY_AMOUNT_FOREVER;    // 0 -> retry forever; UINT32_MAX_VALUE (0xFFFFFFFF) -> never retry.
static uint32_t _connect_retry_num      = 0;

static bool _is_init = false;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_hw_err_enum_t _setup_wifi_config(
        const   char*           const   wiFiSSIDStrPtr,
        const   uint16_t                wiFiSSIDStrLen,
        const   char*           const   wiFiPASSStrPtr,
        const   uint16_t                wiFiPASSStrLen,
                wifi_config_t*  const   wifiConfigPtr) {

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(wifiConfigPtr, 0x00, sizeof(wifi_config_t)));

    // NOTE: check for buffer overflow
    TOMMROC_ASSERT_LESS_OR_EQUALS_THAN(wiFiSSIDStrLen, TOMMROC_UTIL_STRING_ARR_LENGTH(((wifi_config_t*) NULL)->sta.ssid));
    TOMMROC_ASSERT_LESS_OR_EQUALS_THAN(wiFiPASSStrLen, TOMMROC_UTIL_STRING_ARR_LENGTH(((wifi_config_t*) NULL)->sta.password));

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(wifiConfigPtr->sta.ssid, wiFiSSIDStrPtr, wiFiSSIDStrLen));
    wifiConfigPtr->sta.ssid[wiFiSSIDStrLen] = TOMMROC_STRING_NULL_TERMINATOR_CHAR;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(wifiConfigPtr->sta.password, wiFiPASSStrPtr, wiFiPASSStrLen));
    wifiConfigPtr->sta.password[wiFiPASSStrLen] = TOMMROC_STRING_NULL_TERMINATOR_CHAR;

    wifiConfigPtr->sta.pmf_cfg.capable  = true;
    wifiConfigPtr->sta.pmf_cfg.required = false;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

// Wifi event handler
static void _event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {

    esp_err_t err;

    if ((event_base == WIFI_EVENT) && (event_id == WIFI_EVENT_STA_START)) {
        err = esp_wifi_connect();
        if (ESP_OK != err) {
            TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "esp_wifi_connect error: ", esp_err_to_name(err));
        }
    }
    else if ((event_base == WIFI_EVENT) && (event_id == WIFI_EVENT_STA_CONNECTED)) {
        TOMMROC_DEBUG_D("WIFI_EVENT_STA_CONNECTED");
    }
    else if ((event_base == WIFI_EVENT) && (event_id == WIFI_EVENT_STA_DISCONNECTED)) {

        TOMMROC_DEBUG_D("WIFI_EVENT_STA_DISCONNECTED");

        if (0 != (WIFI_CONNECTED_BIT & xEventGroupGetBits(_wifi_event_group))) {
            xEventGroupClearBits(_wifi_event_group, WIFI_CONNECTED_BIT);
        }

        if (TOMMROC_HW_TEMPLATE_WIFI_CONNECT_RETRY_AMOUNT_NEVER != _connect_retry_amount) {
            if ((TOMMROC_HW_TEMPLATE_WIFI_CONNECT_RETRY_AMOUNT_FOREVER == _connect_retry_amount) || (_connect_retry_num < _connect_retry_amount)) {
                err = esp_wifi_connect();
                if (ESP_OK != err) {
                    TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "esp_wifi_connect error: ", esp_err_to_name(err));
                }
                ++_connect_retry_num;
                TOMMROC_DEBUG_D("Retry to Wi-Fi connect");
            } else {
                xEventGroupSetBits(_wifi_event_group, WIFI_FAIL_BIT);
            }
        }
    }
    else if ((event_base == IP_EVENT) && (event_id == IP_EVENT_STA_GOT_IP)) {
        TOMMROC_DEBUG_D("IP_EVENT_STA_GOT_IP");
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        // NOTE: remove unused warning
        (void) event;
        _connect_retry_num = 0;
        xEventGroupSetBits(_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

static tommRoC_hw_err_enum_t _start_wifi(
        const   char*       const   wiFiSSIDStrPtr,
        const   uint16_t            wiFiSSIDStrLen,
        const   char*       const   wiFiPASSStrPtr,
        const   uint16_t            wiFiPASSStrLen,
        const   uint32_t            connectRetryAmount) {

    wifi_config_t wifiConfig;

    esp_err_t err;

    TOMMROC_DEBUG_PRINTLN_PLUS_STRING_LEN(TOMMRO_C_DEBUG_D_LEVEL, "WiFi SSID: ", wiFiSSIDStrPtr, wiFiSSIDStrLen);
    TOMMROC_DEBUG_PRINTLN_PLUS_STRING_LEN(TOMMRO_C_DEBUG_D_LEVEL, "WiFi PASS: ", wiFiPASSStrPtr, wiFiPASSStrLen);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _setup_wifi_config(
                    wiFiSSIDStrPtr,
                    wiFiSSIDStrLen,
                    wiFiPASSStrPtr,
                    wiFiPASSStrLen,
                    &wifiConfig));

    // Disable the default wifi logging
    esp_log_level_set("wifi", ESP_LOG_NONE);

    _wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &_event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &_event_handler, NULL));

    err = esp_wifi_set_storage(WIFI_STORAGE_RAM);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "esp_wifi_set_storage error: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    err = esp_wifi_set_mode(WIFI_MODE_STA);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "esp_wifi_set_mode error: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    err = esp_wifi_set_config(ESP_IF_WIFI_STA, &wifiConfig);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "esp_wifi_set_config error: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    err = esp_wifi_start();
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "esp_wifi_start error: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_DEBUG_D("wifi_init_sta finished");

    _connect_retry_amount = connectRetryAmount;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _stop_wifi(void) {

    esp_err_t err;

    err = esp_wifi_stop();
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "esp_wifi_stop error: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    ESP_ERROR_CHECK(esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, &_event_handler));
    ESP_ERROR_CHECK(esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, &_event_handler));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _is_itf_up_funct(bool* const isUpPtr) {

    *isUpPtr = true;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _is_link_up_funct(bool* const isUpPtr) {

    *isUpPtr = tommRoCHwTemplateWiFiIsConnected();

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _get_itf_config_funct(
                tommRoC_hw_comm_ip_v4_add_t*        const   ipV4AddPtr,
                tommRoC_hw_comm_ip_v4_mask_t*       const   ipV4MaskPtr,
                tommRoC_hw_comm_ip_v4_gateway_t*    const   ipV4GatewayPtr) {

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    tcpip_adapter_ip_info_t ipInfo;
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    esp_netif_ip_info_t ipInfo;
#endif

    uint8_t a1, a2, a3, a4;

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    if (ESP_OK != tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ipInfo)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    if (ESP_OK != esp_netif_get_ip_info(esp_netif_get_handle_from_ifkey("WIFI_STA_DEF"), &ipInfo)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
#endif

    a1 = ip4_addr1_val(ipInfo.ip);
    a2 = ip4_addr2_val(ipInfo.ip);
    a3 = ip4_addr3_val(ipInfo.ip);
    a4 = ip4_addr4_val(ipInfo.ip);
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwCommIPv4ItfInit(a1, a2, a3, a4, ipV4AddPtr));

    a1 = ip4_addr1_val(ipInfo.netmask);
    a2 = ip4_addr2_val(ipInfo.netmask);
    a3 = ip4_addr3_val(ipInfo.netmask);
    a4 = ip4_addr4_val(ipInfo.netmask);
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwCommIPv4ItfInit(a1, a2, a3, a4, ipV4MaskPtr));

    a1 = ip4_addr1_val(ipInfo.gw);
    a2 = ip4_addr2_val(ipInfo.gw);
    a3 = ip4_addr3_val(ipInfo.gw);
    a4 = ip4_addr4_val(ipInfo.gw);
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwCommIPv4ItfInit(a1, a2, a3, a4, ipV4GatewayPtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _set_itf_config_funct(
        const   tommRoC_hw_comm_ip_v4_add_t*        const   ipV4AddPtr,
        const   tommRoC_hw_comm_ip_v4_mask_t*       const   ipV4MaskPtr,
        const   tommRoC_hw_comm_ip_v4_gateway_t*    const   ipV4GatewayPtr) {

    uint8_t ipV4ItfU8Array[TOMMROC_HW_COMM_IP_IPv4_ITF_EAMOUNT];

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    tcpip_adapter_ip_info_t ipInfo;
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    esp_netif_ip_info_t ipInfo;
#endif

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwCommIPv4ItfToU8Array(ipV4AddPtr, ipV4ItfU8Array));
    IP4_ADDR(&ipInfo.ip, ipV4ItfU8Array[0], ipV4ItfU8Array[1], ipV4ItfU8Array[2], ipV4ItfU8Array[3]);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwCommIPv4ItfToU8Array(ipV4MaskPtr, ipV4ItfU8Array));
    IP4_ADDR(&ipInfo.netmask, ipV4ItfU8Array[0], ipV4ItfU8Array[1], ipV4ItfU8Array[2], ipV4ItfU8Array[3]);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwCommIPv4ItfToU8Array(ipV4GatewayPtr, ipV4ItfU8Array));
    IP4_ADDR(&ipInfo.gw, ipV4ItfU8Array[0], ipV4ItfU8Array[1], ipV4ItfU8Array[2], ipV4ItfU8Array[3]);

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    if (ESP_OK != tcpip_adapter_set_ip_info(TCPIP_ADAPTER_IF_STA, &ipInfo)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    if (ESP_OK != esp_netif_set_ip_info(esp_netif_get_handle_from_ifkey("WIFI_STA_DEF"), &ipInfo)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _init_net_frmwrk(void) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetInitIsItfUp(_is_itf_up_funct));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetInitIsLinkUp(_is_link_up_funct));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetInitGetItfConfig(_get_itf_config_funct));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetInitSetItfConfig(_set_itf_config_funct));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _stop_net_frmwrk(void) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetCloseEnv(TOMMROC_HW_NET_IS_ITF_UP_FUNCT));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetCloseEnv(TOMMROC_HW_NET_IS_LINK_UP_FUNCT));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetCloseEnv(TOMMROC_HW_NET_GET_ITF_CFG_FUNCT));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetCloseEnv(TOMMROC_HW_NET_SET_ITF_CFG_FUNCT));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateWiFiInit(
        const   char*       const   wiFiSSIDStrPtr,
        const   char*       const   wiFiPASSStrPtr,
        const   uint32_t            connectRetryAmount) {

    uint16_t wiFiSSIDStrLen;
    uint16_t wiFiPASSStrLen;

    TOMMROC_ASSERT_NOT_NULL(wiFiSSIDStrPtr);
    TOMMROC_ASSERT_NOT_NULL(wiFiPASSStrPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(wiFiSSIDStrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(wiFiPASSStrPtr);

    wiFiSSIDStrLen = tommRoCStringStrLen(wiFiSSIDStrPtr);
    wiFiPASSStrLen = tommRoCStringStrLen(wiFiPASSStrPtr);

    TOMMROC_ASSERT_NOT_ZERO(wiFiSSIDStrLen);
    TOMMROC_ASSERT_NOT_ZERO(wiFiPASSStrLen);

    TOMMROC_HW_PARAM_CHECK_ON_ZERO_RETURN_ERR(wiFiSSIDStrLen);
    TOMMROC_HW_PARAM_CHECK_ON_ZERO_RETURN_ERR(wiFiPASSStrLen);

    if (_is_init) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _start_wifi(
                    wiFiSSIDStrPtr,
                    wiFiSSIDStrLen,
                    wiFiPASSStrPtr,
                    wiFiPASSStrLen,
                    connectRetryAmount));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _init_net_frmwrk());

    _is_init = true;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateWiFiStop(void) {

    if (!_is_init) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _stop_net_frmwrk());

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _stop_wifi());

    _is_init = false;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

bool tommRoCHwTemplateWiFiIsConnected(void) {

    if (NULL == _wifi_event_group) {
        return false;
    }

    return (0 != (WIFI_CONNECTED_BIT & xEventGroupGetBits(_wifi_event_group)));
}

tommRoC_hw_err_enum_t tommRoCHwTemplateWiFiDisconnect(void) {

    esp_err_t err;

    if (!tommRoCHwTemplateWiFiIsConnected()) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    // NOTE: never retry to connect.
    _connect_retry_amount = TOMMROC_HW_TEMPLATE_WIFI_CONNECT_RETRY_AMOUNT_NEVER;

    err = esp_wifi_disconnect();
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "esp_wifi_disconnect error: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateWiFiConnect(
        const   char*       const   wiFiSSIDStrPtr,
        const   char*       const   wiFiPASSStrPtr,
        const   uint32_t            connectRetryAmount) {

    uint16_t wiFiSSIDStrLen;
    uint16_t wiFiPASSStrLen;
    wifi_config_t wifiConfig;

    esp_err_t err;

    TOMMROC_ASSERT_NOT_NULL(wiFiSSIDStrPtr);
    TOMMROC_ASSERT_NOT_NULL(wiFiPASSStrPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(wiFiSSIDStrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(wiFiPASSStrPtr);

    wiFiSSIDStrLen = tommRoCStringStrLen(wiFiSSIDStrPtr);
    wiFiPASSStrLen = tommRoCStringStrLen(wiFiPASSStrPtr);

    TOMMROC_ASSERT_NOT_ZERO(wiFiSSIDStrLen);
    TOMMROC_ASSERT_NOT_ZERO(wiFiPASSStrLen);

    TOMMROC_HW_PARAM_CHECK_ON_ZERO_RETURN_ERR(wiFiSSIDStrLen);
    TOMMROC_HW_PARAM_CHECK_ON_ZERO_RETURN_ERR(wiFiPASSStrLen);

    if (tommRoCHwTemplateWiFiIsConnected()) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_DEBUG_PRINTLN_PLUS_STRING_LEN(TOMMRO_C_DEBUG_D_LEVEL, "WiFi SSID: ", wiFiSSIDStrPtr, wiFiSSIDStrLen);
    TOMMROC_DEBUG_PRINTLN_PLUS_STRING_LEN(TOMMRO_C_DEBUG_D_LEVEL, "WiFi PASS: ", wiFiPASSStrPtr, wiFiPASSStrLen);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _setup_wifi_config(
                    wiFiSSIDStrPtr,
                    wiFiSSIDStrLen,
                    wiFiPASSStrPtr,
                    wiFiPASSStrLen,
                    &wifiConfig));

    err = esp_wifi_set_config(ESP_IF_WIFI_STA, &wifiConfig);
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "esp_wifi_set_config error: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    _connect_retry_amount = connectRetryAmount;

    err = esp_wifi_connect();
    if (ESP_OK != err) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "esp_wifi_connect error: ", esp_err_to_name(err));
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

#endif
