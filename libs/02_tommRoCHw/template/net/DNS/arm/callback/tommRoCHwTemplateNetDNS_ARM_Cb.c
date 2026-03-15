
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateNetDNS_ARM_Cb.h"

#if defined (__TOMMROC_HW_USE_DNS_NET_TEMPLATE__)

#include "TOMMROC.h"
#include "TOMMROCHw.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

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
static void _set_address(const ip_addr_t *ipaddr, tommRoC_hw_template_net_dns__arm__cb_found_cb_arg_t* const foundCbArgPtr) {

    if (NULL == ipaddr) {
        foundCbArgPtr->validHostIPv4 = false;
        return;
    }

    if (0 == ipaddr->addr) {
        foundCbArgPtr->validHostIPv4 = false;
        return;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(foundCbArgPtr->hostIPv4AddPtr, ipaddr, sizeof(ip_addr_t)));

    foundCbArgPtr->validHostIPv4 = true;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

void tommRoCHwTemplateNetDNS_ARM_CbFoundCb(const char *name, const ip_addr_t *ipaddr, void *callback_arg) {

    tommRoC_hw_template_net_dns__arm__cb_found_cb_arg_t* foundCbArgPtr = (tommRoC_hw_template_net_dns__arm__cb_found_cb_arg_t*) callback_arg;

    TOMMROC_UTIL_UNUSED_PARAM(name);

    _set_address(ipaddr, foundCbArgPtr);

    foundCbArgPtr->hasBeenCalled = true;
}

#endif

#endif
