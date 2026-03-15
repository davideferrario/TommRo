
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "net/DNS/tommRoCHwTemplateNetDNS.h"

#if defined (__TOMMROC_HW_USE_DNS_NET_TEMPLATE__)

#include "TOMMROC.h"
#include "TOMMROCHw.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
#include "net/DNS/arm/callback/tommRoCHwTemplateNetDNS_ARM_Cb.h"

#include "lwip/dns.h"

#if !LWIP_DNS
#error "LWIP_DNS is needed"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __FOUND_CALLBACK_TIMEOUT_SEC__      (5)
#define __FOUND_CALLBACK_TIMEOUT_MSEC__     (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(__FOUND_CALLBACK_TIMEOUT_SEC__))

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_hw_err_enum_t _wait_for_callback(volatile bool* const hasBeenCalledPtr, const uint32_t timeoutMsec) {

    tommRoC_timer_t timer;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, timeoutMsec));

    do {

        if (*hasBeenCalledPtr) {
            return TOMMRO_C_HW_ERR_SUCCESS;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1));

    } while (TOMMRO_C_TIMER_NOT_EXPIRED_ERR == tommRoCTimerIsExpired(&timer));

    return TOMMRO_C_HW_TIMEOUT_ERR;
}

static tommRoC_hw_err_enum_t _wait_for_found_callback(tommRoC_hw_template_net_dns__arm__cb_found_cb_arg_t* const foundCbPtr) {

    return _wait_for_callback(
            &foundCbPtr->hasBeenCalled,
            __FOUND_CALLBACK_TIMEOUT_MSEC__);
}

static tommRoC_hw_err_enum_t _set_server(
        const   tommRoC_hw_comm_ip_v4_add_t*    const   dnsServerIPv4AddPtr) {

    uint8_t dnsServerIPv4AddU8Array[TOMMROC_HW_COMM_IP_IPv4_ITF_EAMOUNT];
    ip4_addr_t dnsServerIPv4Add;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwCommIPv4ItfToU8Array(
                    dnsServerIPv4AddPtr,
                    dnsServerIPv4AddU8Array));

    IP_ADDR4(&dnsServerIPv4Add, dnsServerIPv4AddU8Array[0], dnsServerIPv4AddU8Array[1], dnsServerIPv4AddU8Array[2], dnsServerIPv4AddU8Array[3]);

    dns_setserver(0, &dnsServerIPv4Add);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _get_host_by_name(
        const   char*                           const   hostNameStrPtr,
                tommRoC_hw_comm_ip_v4_add_t*    const   hostIPv4AddPtr) {

    ip4_addr_t hostIPv4Add;
    uint8_t a1, a2, a3, a4;
    tommRoC_hw_template_net_dns__arm__cb_found_cb_arg_t foundCbArg = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_hw_template_net_dns__arm__cb_found_cb_arg_t);

    err_t res;

    foundCbArg.hostIPv4AddPtr = &hostIPv4Add;

    res = dns_gethostbyname(
            hostNameStrPtr,
            &hostIPv4Add,
            tommRoCHwTemplateNetDNS_ARM_CbFoundCb,
            &foundCbArg);

    if (ERR_INPROGRESS == res) {
        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_wait_for_found_callback(&foundCbArg));
    }

    if ((ERR_OK == res) || ((ERR_INPROGRESS == res) && foundCbArg.validHostIPv4)) {

        a1 = ip4_addr1_val(hostIPv4Add);
        a2 = ip4_addr2_val(hostIPv4Add);
        a3 = ip4_addr3_val(hostIPv4Add);
        a4 = ip4_addr4_val(hostIPv4Add);
        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwCommIPv4ItfInit(a1, a2, a3, a4, hostIPv4AddPtr));

        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    return TOMMRO_C_HW_LOW_LEVEL_ERR;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateNetDNSStart(void) {

    const tommRoC_hw_net_dns_init_t init = {
            /* .setServerFunct */       _set_server,
            /* .getHostByNameFunct */   _get_host_by_name,
    };

    dns_init();

    return tommRoCHwNetDNSInitEnv(&init);
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNetDNSStop(void) {

    return tommRoCHwNetDNSCloseEnv();
}

#endif

#endif
