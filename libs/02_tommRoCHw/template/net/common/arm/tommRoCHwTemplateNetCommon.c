
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "net/common/tommRoCHwTemplateNetCommon.h"

#include "tommRoCHwTemplateNet.h"

#if defined (__TOMMROC_HW_NET_TEMPLATE_IS_USED__)

#include "TOMMROC.h"
#include "TOMMROCHw.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
#include "ethernetif.h"
#include "lwip.h"

#include "lwip/netif.h"
#include "lwip/opt.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_STM32F4_IS_USED__)
#include "stm32f4xx.h"
#endif

#if !defined(LWIP_NETIF_LINK_CALLBACK) || !(LWIP_NETIF_LINK_CALLBACK)
#error "LWIP_NETIF_LINK_CALLBACK MUST be 1"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
extern struct netif gnetif;

/*******************************************************************************
 * local functions
 ******************************************************************************/
void ethernetif_notify_conn_changed(struct netif *netif) {

    /**
     * NOTE:
     * https://community.st.com/s/question/0D50X00009XkhxBSAR/initialize-lwip-with-ethernet-disconnected
     *
     * Fix for unplugged cable on startup
     * If the link is down at start-up, netif_set_up() never gets called by MX_LWIP_Init()
     */

    if (netif_is_link_up(netif) && !netif_is_up(netif)) {
        netif_set_up(netif);
    }
}

static tommRoC_hw_err_enum_t _is_itf_up_funct(bool* const isItfUpPtr) {

    *isItfUpPtr = (bool) netif_is_up(&gnetif);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _is_link_up_funct(bool* const isLinkUpPtr) {

    *isLinkUpPtr = (bool) netif_is_link_up(&gnetif);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _get_itf_config_funct(
                tommRoC_hw_comm_ip_v4_add_t*        const   ipV4AddPtr,
                tommRoC_hw_comm_ip_v4_mask_t*       const   ipV4MaskPtr,
                tommRoC_hw_comm_ip_v4_gateway_t*    const   ipV4GatewayPtr) {

    uint8_t a1, a2, a3, a4;

    a1 = ip4_addr1(netif_ip4_addr(&gnetif));
    a2 = ip4_addr2(netif_ip4_addr(&gnetif));
    a3 = ip4_addr3(netif_ip4_addr(&gnetif));
    a4 = ip4_addr4(netif_ip4_addr(&gnetif));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwCommIPv4ItfInit(a1, a2, a3, a4, ipV4AddPtr));

    a1 = ip4_addr1(netif_ip4_netmask(&gnetif));
    a2 = ip4_addr2(netif_ip4_netmask(&gnetif));
    a3 = ip4_addr3(netif_ip4_netmask(&gnetif));
    a4 = ip4_addr4(netif_ip4_netmask(&gnetif));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwCommIPv4ItfInit(a1, a2, a3, a4, ipV4MaskPtr));

    a1 = ip4_addr1(netif_ip4_gw(&gnetif));
    a2 = ip4_addr2(netif_ip4_gw(&gnetif));
    a3 = ip4_addr3(netif_ip4_gw(&gnetif));
    a4 = ip4_addr4(netif_ip4_gw(&gnetif));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwCommIPv4ItfInit(a1, a2, a3, a4, ipV4GatewayPtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _set_itf_config_funct(
        const   tommRoC_hw_comm_ip_v4_add_t*        const   ipV4AddPtr,
        const   tommRoC_hw_comm_ip_v4_mask_t*       const   ipV4MaskPtr,
        const   tommRoC_hw_comm_ip_v4_gateway_t*    const   ipV4GatewayPtr) {

    uint8_t ipV4ItfU8Array[TOMMROC_HW_COMM_IP_IPv4_ITF_EAMOUNT];

    ip_addr_t ipAddr;
    ip_addr_t netMask;
    ip_addr_t gw;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwCommIPv4ItfToU8Array(ipV4AddPtr, ipV4ItfU8Array));
    IP_ADDR4(&ipAddr, ipV4ItfU8Array[0], ipV4ItfU8Array[1], ipV4ItfU8Array[2], ipV4ItfU8Array[3]);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwCommIPv4ItfToU8Array(ipV4MaskPtr, ipV4ItfU8Array));
    IP_ADDR4(&netMask, ipV4ItfU8Array[0], ipV4ItfU8Array[1], ipV4ItfU8Array[2], ipV4ItfU8Array[3]);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwCommIPv4ItfToU8Array(ipV4GatewayPtr, ipV4ItfU8Array));
    IP_ADDR4(&gw, ipV4ItfU8Array[0], ipV4ItfU8Array[1], ipV4ItfU8Array[2], ipV4ItfU8Array[3]);

    netif_set_addr(
            &gnetif,
            ip_2_ip4(&ipAddr),
            ip_2_ip4(&netMask),
            ip_2_ip4(&gw));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateNetCommonStart(void) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetInitIsItfUp(_is_itf_up_funct));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetInitIsLinkUp(_is_link_up_funct));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetInitGetItfConfig(_get_itf_config_funct));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetInitSetItfConfig(_set_itf_config_funct));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNetCommonStop(void) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetCloseEnv(TOMMROC_HW_NET_IS_ITF_UP_FUNCT));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetCloseEnv(TOMMROC_HW_NET_IS_LINK_UP_FUNCT));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetCloseEnv(TOMMROC_HW_NET_GET_ITF_CFG_FUNCT));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetCloseEnv(TOMMROC_HW_NET_SET_ITF_CFG_FUNCT));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

#endif

#endif
