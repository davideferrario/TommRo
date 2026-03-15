
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "net/DNS/tommRoCHwTemplateNetDNS.h"

#if defined (__TOMMROC_HW_USE_DNS_NET_TEMPLATE__)

#include "TOMMROC.h"
#include "TOMMROCHw.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "net/DNS/esp32/callback/tommRoCHwTemplateNetDNS_ESP32_Cb.h"

#include "lwip/dns.h"

#if !LWIP_DNS
#error "LWIP_DNS is needed"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __FOUND_CALLBACK_TIMEOUT_SEC__      (15)
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

    TEST_ASSERT_EQUAL(TOMMRO_C_ERR_SUCCESS, tommRoCTimerStart(&timer, timeoutMsec));

    do {

        if (*hasBeenCalledPtr) {
            return TOMMRO_C_HW_ERR_SUCCESS;
        }

        TEST_ASSERT_EQUAL(TOMMRO_C_ERR_SUCCESS, tommRoCOsDelayMsec(1));

    } while (TOMMRO_C_TIMER_NOT_EXPIRED_ERR == tommRoCTimerIsExpired(&timer));

    return TOMMRO_C_HW_TIMEOUT_ERR;
}

static tommRoC_hw_err_enum_t _wait_for_found_callback(tommRoC_hw_template_net_dns__esp32__cb_found_cb_arg_t* const foundCbPtr) {

    return _wait_for_callback(
            &foundCbPtr->hasBeenCalled,
            __FOUND_CALLBACK_TIMEOUT_MSEC__);
}

static tommRoC_hw_err_enum_t _set_server(
        const   tommRoC_hw_comm_ip_v4_add_t*    const   dnsServerIPv4AddPtr) {

    uint8_t dnsServerIPv4AddU8Array[TOMMROC_HW_COMM_IP_IPv4_ITF_EAMOUNT];
    ip_addr_t dnsServerIpAdd;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwCommIPv4ItfToU8Array(
                    dnsServerIPv4AddPtr,
                    dnsServerIPv4AddU8Array));

    IP_ADDR4(&dnsServerIpAdd, dnsServerIPv4AddU8Array[0], dnsServerIPv4AddU8Array[1], dnsServerIPv4AddU8Array[2], dnsServerIPv4AddU8Array[3]);

    dns_setserver(0, &dnsServerIpAdd);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _get_host_by_name(
        const   char*                           const   hostNameStrPtr,
                tommRoC_hw_comm_ip_v4_add_t*    const   hostIPv4AddPtr) {

    ip_addr_t hostIPAdd;
    uint8_t a1, a2, a3, a4;
    tommRoC_hw_template_net_dns__esp32__cb_found_cb_arg_t foundCbArg = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_hw_template_net_dns__esp32__cb_found_cb_arg_t);

    err_t res;

    foundCbArg.hostIPAddPtr = &hostIPAdd;

    res = dns_gethostbyname(
            hostNameStrPtr,
            &hostIPAdd,
            tommRoCHwTemplateNetDNS_ESP32_CbFoundCb,
            &foundCbArg);

    if (ERR_INPROGRESS == res) {
        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_wait_for_found_callback(&foundCbArg));
    }

    if ((ERR_OK == res) || ((ERR_INPROGRESS == res) && foundCbArg.validHostIP)) {

        a1 = ip4_addr1_val(hostIPAdd.u_addr.ip4);
        a2 = ip4_addr2_val(hostIPAdd.u_addr.ip4);
        a3 = ip4_addr3_val(hostIPAdd.u_addr.ip4);
        a4 = ip4_addr4_val(hostIPAdd.u_addr.ip4);
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
