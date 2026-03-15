
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "net/common/tommRoCHwTemplateNetCommon.h"

#include "tommRoCHwTemplateNet.h"

#if defined (__TOMMROC_HW_NET_TEMPLATE_IS_USED__)

#include "TOMMROC.h"
#include "TOMMROCHw.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)

#include "env/tommRoCTemplateEnv.h"

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
#include "tcpip_adapter.h"
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
#include "esp_netif.h"
#endif

#include "lwip/netif.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_hw_err_enum_t _is_itf_up_funct(bool* const isItfUpPtr) {

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    struct netif* netifSTA;
    struct netif* netifETH;
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    esp_netif_t* espNetifSTA;
    esp_netif_t* espNetifETH;
#endif

    esp_err_t errSTA;
    esp_err_t errETH;

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    errSTA = tcpip_adapter_get_netif(TCPIP_ADAPTER_IF_STA, (void**) &netifSTA);
    errETH = tcpip_adapter_get_netif(TCPIP_ADAPTER_IF_ETH, (void**) &netifETH);
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    espNetifSTA = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
    espNetifETH = esp_netif_get_handle_from_ifkey("ETH_DEF");
    errSTA = (NULL != espNetifSTA) ? (ESP_OK) : (ESP_ERR_INVALID_ARG);
    errETH = (NULL != espNetifETH) ? (ESP_OK) : (ESP_ERR_INVALID_ARG);
#endif

    if (ESP_OK == errSTA) {
#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
        *isItfUpPtr = (bool) netif_is_up(netifSTA);
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
        *isItfUpPtr = esp_netif_is_netif_up(espNetifSTA);
#endif
    }
    else if (ESP_OK == errETH) {
#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
        *isItfUpPtr = (bool) netif_is_up(netifETH);
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
        *isItfUpPtr = esp_netif_is_netif_up(espNetifETH);
#endif
    }
    else {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _is_link_up_funct(bool* const isLinkUpPtr) {

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    struct netif* netifSTA;
    struct netif* netifETH;
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    esp_netif_t* espNetifSTA;
    esp_netif_t* espNetifETH;
#endif

    esp_err_t errSTA;
    esp_err_t errETH;

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    errSTA = tcpip_adapter_get_netif(TCPIP_ADAPTER_IF_STA, (void**) &netifSTA);
    errETH = tcpip_adapter_get_netif(TCPIP_ADAPTER_IF_ETH, (void**) &netifETH);
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    espNetifSTA = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
    espNetifETH = esp_netif_get_handle_from_ifkey("ETH_DEF");
    errSTA = (NULL != espNetifSTA) ? (ESP_OK) : (ESP_ERR_INVALID_ARG);
    errETH = (NULL != espNetifETH) ? (ESP_OK) : (ESP_ERR_INVALID_ARG);
#endif

    if (ESP_OK == errSTA) {
#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
        *isLinkUpPtr = (bool) netif_is_link_up(netifSTA);
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
        *isLinkUpPtr = esp_netif_is_netif_up(espNetifSTA);
#endif
    }
    else if (ESP_OK == errETH) {
#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
        *isLinkUpPtr = (bool) netif_is_link_up(netifETH);
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
        *isLinkUpPtr = esp_netif_is_netif_up(espNetifETH);
#endif
    }
    else {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateNetCommonStart(void) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetInitIsItfUp(_is_itf_up_funct));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetInitIsLinkUp(_is_link_up_funct));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNetCommonStop(void) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetCloseEnv(TOMMROC_HW_NET_IS_ITF_UP_FUNCT));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetCloseEnv(TOMMROC_HW_NET_IS_LINK_UP_FUNCT));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

#endif

#endif
