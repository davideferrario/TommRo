
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "net/common/tommRoCHwTemplateNetCommon.h"

#include "tommRoCHwTemplateNet.h"

#if defined (__TOMMROC_HW_NET_TEMPLATE_IS_USED__)

#include "TOMMROC.h"
#include "TOMMROCHw.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <linux/if.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <ifaddrs.h>
#include <stdio.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __NI_MAXHOST__          (1025)
#define __NI_NUMERICHOST__      (1)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_hw_err_enum_t _check_itf_flag(const char* const itfNameStrPtr, const int flagMask, bool* const isUpPtr) {

    struct ifreq ifr;
    int dummySocket = -1;
    unsigned int flags;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&ifr, 0, sizeof(ifr)));
    strncpy(ifr.ifr_name, itfNameStrPtr, IFNAMSIZ - TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE);
    ifr.ifr_name[IFNAMSIZ - TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE] = TOMMROC_STRING_NULL_TERMINATOR_CHAR;

    if (ioctl(dummySocket, SIOCGIFFLAGS, &ifr) < 0) {
        *isUpPtr = false;
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    flags = ifr.ifr_flags;

    *isUpPtr = (bool) (flags & flagMask);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _is_up_funct(const int flagMask, bool* const isUpPtr) {

    bool isEth0Up   = false;
    bool isWlan0Up  = false;

    tommRoC_hw_err_enum_t hwEth0Res;
    tommRoC_hw_err_enum_t hwWlan0Res;

    hwEth0Res   = _check_itf_flag("eth0",   flagMask,   &isEth0Up);
    hwWlan0Res  = _check_itf_flag("wlan0",  flagMask,   &isWlan0Up);

    if ((TOMMRO_C_HW_ERR_SUCCESS != hwEth0Res) && (TOMMRO_C_HW_ERR_SUCCESS != hwWlan0Res)) {
        *isUpPtr = false;
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (isEth0Up || isWlan0Up) {
        *isUpPtr = true;
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    *isUpPtr = false;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _is_itf_up_funct(bool* const isItfUpPtr) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _is_up_funct(
                    IFF_UP,
                    isItfUpPtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _is_link_up_funct(bool* const isLinkUpPtr) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _is_up_funct(
                    IFF_RUNNING,
                    isLinkUpPtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _generic_get_itf_config(const char* const itfStrPtr, tommRoC_hw_comm_ip_v4_add_t* const ipV4AddPtr) {

    struct ifaddrs *ifaddr, *ifa;
    int s;
    char host[__NI_MAXHOST__];

    if (getifaddrs(&ifaddr) == -1) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL)
            continue;

        s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, __NI_MAXHOST__, NULL, 0, __NI_NUMERICHOST__);

        if ((tommRoCStringCompare(ifa->ifa_name, itfStrPtr) == TOMMRO_C_ERR_SUCCESS) && (ifa->ifa_addr->sa_family == AF_INET)) {

            if (s != 0) {
                printf("getnameinfo() failed: %s\n", gai_strerror(s));
                return TOMMRO_C_HW_LOW_LEVEL_ERR;
            }
            printf("\tInterface : <%s>\n",ifa->ifa_name );
            printf("\t  Address : <%s>\n", host);
        }
    }

    freeifaddrs(ifaddr);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _get_itf_config_funct(
                tommRoC_hw_comm_ip_v4_add_t*        const   ipV4AddPtr,
                tommRoC_hw_comm_ip_v4_mask_t*       const   ipV4MaskPtr,
                tommRoC_hw_comm_ip_v4_gateway_t*    const   ipV4GatewayPtr) {

    return _generic_get_itf_config("wlan0", ipV4AddPtr);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateNetCommonStart(void) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetInitIsItfUp(_is_itf_up_funct));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetInitIsLinkUp(_is_link_up_funct));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetInitGetItfConfig(_get_itf_config_funct));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNetCommonStop(void) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetCloseEnv(TOMMROC_HW_NET_IS_ITF_UP_FUNCT));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetCloseEnv(TOMMROC_HW_NET_IS_LINK_UP_FUNCT));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetCloseEnv(TOMMROC_HW_NET_GET_ITF_CFG_FUNCT));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

#endif

#endif
