
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "net/DHCP/tommRoCHwTemplateNetDHCP.h"

#if defined (__TOMMROC_HW_USE_DHCP_NET_TEMPLATE__)

#include "TOMMROC.h"
#include "TOMMROCHw.h"
#include "TOMMROCMw.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "TOMMROCMwTemplate.h"

#if !defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
#error "Multi thread environment is needed for DHCP"
#endif

#include "lwip/api.h"
#include "lwip/dhcp.h"
#include "lwip/netif.h"

#include <stdbool.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __DHCP_TASK_RATE_MSEC__     (50)

#define __MAX_DHCP_TRIES__          (4)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef enum {

    __DHCP_INIT__ = 0,
    __DHCP_START__,
    __DHCP_WAIT_ADDRESS__,
    __DHCP_ADDRESS_ASSIGNED__,

} __status_enum_t__;

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_DEBUG_ENABLE__)
static const char __DEBUG_OBJ_ID__[] = "hwTempDHCP";
#endif

static tommRoC_mw_template_thread_t _DHCP_thread;
static bool _is_paused = false;

extern struct netif gnetif;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static void _debug_itf_config(void) {

#if defined (__TOMMROC_DEBUG_ENABLE__)
    tommRoC_hw_comm_ip_v4_add_t ipV4Add;
    tommRoC_hw_comm_ip_v4_mask_t ipV4Mask;
    tommRoC_hw_comm_ip_v4_gateway_t ipV4GW;

    tommRoC_hw_comm_ip_v4_itf_as_string_t ipV4AsStr;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwNetGetItfConfig(&ipV4Add, &ipV4Mask, &ipV4GW));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwCommIPv4ItfToAsString(&ipV4Add, &ipV4AsStr, TOMMROC_HW_COMM_IP_IPV4_AS_STRING_DECIMAL_FORMAT));
    TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_D_LEVEL, "IP: ", ipV4AsStr.data);

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwCommIPv4ItfToAsString(&ipV4GW, &ipV4AsStr, TOMMROC_HW_COMM_IP_IPV4_AS_STRING_DECIMAL_FORMAT));
    TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_D_LEVEL, "GW: ", ipV4AsStr.data);

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwCommIPv4ItfToAsString(&ipV4Mask, &ipV4AsStr, TOMMROC_HW_COMM_IP_IPV4_AS_STRING_DECIMAL_FORMAT));
    TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_D_LEVEL, "Mask: ", ipV4AsStr.data);
#endif
}

static void _DHCP_thread_main(void* const argument) {

    static bool lastIsPaused = false;
    static bool isPaused;

    struct netif* netif = (struct netif*) argument;
    struct dhcp* dhcp;

    __status_enum_t__ DHCPStatus;

    while (!netif_is_up(netif)) {
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1000));
    }

    TOMMROC_DEBUG_D("DHCPStatus = __DHCP_INIT__");
    DHCPStatus = __DHCP_INIT__;

    for (;;) {

        isPaused = _is_paused;

        if (isPaused && !lastIsPaused) {
            TOMMROC_DEBUG_D("DHCP Pause");
            dhcp_stop(netif);
        }
        else if (!isPaused && lastIsPaused) {
            TOMMROC_DEBUG_D("DHCP Resume");
            TOMMROC_DEBUG_D("DHCPStatus = __DHCP_INIT__");
            DHCPStatus = __DHCP_INIT__;
        }

        if (!isPaused) {

            switch (DHCPStatus) {

            case __DHCP_INIT__:
                ip_addr_set_zero_ip4(&netif->ip_addr);
                ip_addr_set_zero_ip4(&netif->netmask);
                ip_addr_set_zero_ip4(&netif->gw);

                TOMMROC_DEBUG_D("DHCPStatus = __DHCP_INIT__ -> __DHCP_START__");
                DHCPStatus = __DHCP_START__;
                break;

            case __DHCP_START__:
                dhcp_start(netif);
                TOMMROC_DEBUG_D("DHCPStatus = __DHCP_START__ -> __DHCP_WAIT_ADDRESS__");
                DHCPStatus = __DHCP_WAIT_ADDRESS__;
                break;

            case __DHCP_WAIT_ADDRESS__:
                if (dhcp_supplied_address(netif)) {
                    TOMMROC_DEBUG_D("DHCPStatus = __DHCP_WAIT_ADDRESS__ -> __DHCP_ADDRESS_ASSIGNED__");
                    DHCPStatus = __DHCP_ADDRESS_ASSIGNED__;

                    _debug_itf_config();
                }
                else {
                    dhcp = (struct dhcp*) netif_get_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP);

                    // DHCP timeout
                    if (dhcp->tries > __MAX_DHCP_TRIES__) {

                        dhcp_stop(netif);
                        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1000));
                        TOMMROC_DEBUG_D("DHCPStatus = __DHCP_WAIT_ADDRESS__ -> __DHCP_INIT__");
                        DHCPStatus = __DHCP_INIT__;
                    }
                }
                break;

            case __DHCP_ADDRESS_ASSIGNED__:
                if (!netif_is_up(netif)) {
                    dhcp_stop(netif);
                    TOMMROC_DEBUG_D("DHCPStatus = __DHCP_ADDRESS_ASSIGNED__ -> __DHCP_INIT__");
                    DHCPStatus = __DHCP_INIT__;
                }
                break;

            default:
                // If here, ERROR!!!
                TOMMROC_ASSERT_TRUE(false);
                break;

            }
        }

        lastIsPaused = isPaused;

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__DHCP_TASK_RATE_MSEC__));
    }
}

static tommRoC_hw_err_enum_t _dhcp_start_funct(void) {

    static const char threadNameStr[] = "HwTDHCP";

    tommRoC_mw_thread_config_t config = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_mw_thread_config_t);

    config.stackSize = 256;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCMwThreadCreate(_DHCP_thread_main, &gnetif, threadNameStr, &config, &_DHCP_thread),
            TOMMRO_C_HW_LOW_LEVEL_ERR);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _dhcp_stop_funct(void) {

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCMwThreadDestroy(&_DHCP_thread),
            TOMMRO_C_HW_LOW_LEVEL_ERR);

    dhcp_stop(&gnetif);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _dhcp_pause_funct(void) {
    _is_paused = true;
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__DHCP_TASK_RATE_MSEC__ * 2));
    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _dhcp_resume_funct(void) {
    _is_paused = false;
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__DHCP_TASK_RATE_MSEC__ * 2));
    return TOMMRO_C_HW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateNetDHCPStart(void) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetDHCPInitStart(_dhcp_start_funct));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetDHCPInitStop(_dhcp_stop_funct));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetDHCPInitPause(_dhcp_pause_funct));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetDHCPInitResume(_dhcp_resume_funct));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNetDHCPStop(void) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetDHCPCloseEnv(TOMMROC_HW_NET_DHCP_START_FUNCT));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetDHCPCloseEnv(TOMMROC_HW_NET_DHCP_STOP_FUNCT));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetDHCPCloseEnv(TOMMROC_HW_NET_DHCP_PAUSE_FUNCT));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetDHCPCloseEnv(TOMMROC_HW_NET_DHCP_RESUME_FUNCT));

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif
