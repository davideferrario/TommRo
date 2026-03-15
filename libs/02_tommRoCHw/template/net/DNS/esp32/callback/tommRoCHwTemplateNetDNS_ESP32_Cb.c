
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateNetDNS_ESP32_Cb.h"

#if defined (__TOMMROC_HW_USE_DNS_NET_TEMPLATE__)

#include "TOMMROC.h"
#include "TOMMROCHw.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)

#include "env/tommRoCTemplateEnv.h"

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
static void _set_address(const ip_addr_t *ipaddr, tommRoC_hw_template_net_dns__esp32__cb_found_cb_arg_t* const foundCbArgPtr) {

    if (NULL == ipaddr) {
        foundCbArgPtr->validHostIP = false;
        return;
    }

    if ((IPADDR_TYPE_V4 == ipaddr->type) && (0 == ipaddr->u_addr.ip4.addr)) {
        foundCbArgPtr->validHostIP = false;
        return;
    }

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    if ((IPADDR_TYPE_V6 == ipaddr->type) && (0 == ipaddr->u_addr.ip6.addr)) {
        foundCbArgPtr->validHostIP = false;
        return;
    }
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    if ((IPADDR_TYPE_V6 == ipaddr->type) && (0 == ipaddr->u_addr.ip6.addr[0]) && (0 == ipaddr->u_addr.ip6.addr[1]) && (0 == ipaddr->u_addr.ip6.addr[2]) && (0 == ipaddr->u_addr.ip6.addr[3])) {
        foundCbArgPtr->validHostIP = false;
        return;
    }
#endif

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(foundCbArgPtr->hostIPAddPtr, ipaddr, sizeof(ip_addr_t)));

    foundCbArgPtr->validHostIP = true;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

void tommRoCHwTemplateNetDNS_ESP32_CbFoundCb(const char *name, const ip_addr_t *ipaddr, void *callback_arg) {

    tommRoC_hw_template_net_dns__esp32__cb_found_cb_arg_t* foundCbArgPtr = (tommRoC_hw_template_net_dns__esp32__cb_found_cb_arg_t*) callback_arg;

    TOMMROC_UTIL_UNUSED_PARAM(name);

    _set_address(ipaddr, foundCbArgPtr);

    foundCbArgPtr->hasBeenCalled = true;
}

#endif

#endif
