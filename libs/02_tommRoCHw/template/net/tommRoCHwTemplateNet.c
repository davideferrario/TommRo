
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateNet.h"

#include "net/BSDSocket/tommRoCHwTemplateNetBSDSocket.h"
#include "net/common/tommRoCHwTemplateNetCommon.h"
#include "net/DHCP/tommRoCHwTemplateNetDHCP.h"
#include "net/DNS/tommRoCHwTemplateNetDNS.h"
#include "net/SNTP/tommRoCHwTemplateNetSNTP.h"

#include "TOMMROCHw.h"

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

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateNetStart(void) {

#if defined (__TOMMROC_HW_NET_TEMPLATE_IS_USED__)
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwTemplateNetCommonStart());
#endif

#if defined (__TOMMROC_HW_USE_BSD_SOCKET_COMPLETE_NET_TEMPLATE__)
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwTemplateNetBSDSocketCompleteStart());
#elif defined (__TOMMROC_HW_USE_BSD_SOCKET_ONLY_CLIENT_NET_TEMPLATE__)
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwTemplateNetBSDSocketOnlyClientStart());
#elif defined (__TOMMROC_HW_USE_BSD_SOCKET_ONLY_SERVER_NET_TEMPLATE__)
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwTemplateNetBSDSocketOnlyServerStart());
#endif

#if defined (__TOMMROC_HW_USE_DHCP_NET_TEMPLATE__)
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwTemplateNetDHCPStart());
#endif

#if defined (__TOMMROC_HW_USE_DNS_NET_TEMPLATE__)
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwTemplateNetDNSStart());
#endif

#if defined (__TOMMROC_HW_USE_SNTP_NET_TEMPLATE__)
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwTemplateNetSNTPStart());
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNetStop(void) {

#if defined (__TOMMROC_HW_USE_SNTP_NET_TEMPLATE__)
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwTemplateNetSNTPStop());
#endif

#if defined (__TOMMROC_HW_USE_DNS_NET_TEMPLATE__)
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwTemplateNetDNSStop());
#endif

#if defined (__TOMMROC_HW_USE_DHCP_NET_TEMPLATE__)
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwTemplateNetDHCPStop());
#endif

#if defined (__TOMMROC_HW_NET_BSD_SOCKET_TEMPLATE_IS_USED__)
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwTemplateNetBSDSocketStop());
#endif

#if defined (__TOMMROC_HW_NET_TEMPLATE_IS_USED__)
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwTemplateNetCommonStop());
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
