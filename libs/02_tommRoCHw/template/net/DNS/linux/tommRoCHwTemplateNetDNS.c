
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "net/DNS/tommRoCHwTemplateNetDNS.h"

#if defined (__TOMMROC_HW_USE_DNS_NET_TEMPLATE__)

#include "TOMMROC.h"
#include "TOMMROCHw.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)

#if !defined (_POSIX_C_SOURCE)
#error "define _POSIX_C_SOURCE=200112L for DNS on Linux"
#elif (_POSIX_C_SOURCE < 200112L)
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE     (200112L)
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

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
static void _in_addr_t_to_ipV4_add(const in_addr_t sAddr, tommRoC_hw_comm_ip_v4_add_t* const ipV4AddPtr) {

    uint32_t iPv4AddAsU32;
    uint8_t iPv4AddA1;
    uint8_t iPv4AddA2;
    uint8_t iPv4AddA3;
    uint8_t iPv4AddA4;

    iPv4AddAsU32 = ntohl(sAddr);
    iPv4AddA1 = tommRoCMathMake8(iPv4AddAsU32, 3);
    iPv4AddA2 = tommRoCMathMake8(iPv4AddAsU32, 2);
    iPv4AddA3 = tommRoCMathMake8(iPv4AddAsU32, 1);
    iPv4AddA4 = tommRoCMathMake8(iPv4AddAsU32, 0);

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwCommIPv4ItfInit(iPv4AddA1, iPv4AddA2, iPv4AddA3, iPv4AddA4, ipV4AddPtr));
}

static tommRoC_hw_err_enum_t _get_host_by_name(
        const   char*                           const   hostNameStrPtr,
                tommRoC_hw_comm_ip_v4_add_t*    const   hostIPv4AddPtr) {

    struct addrinfo* result = NULL;
    struct addrinfo* res;
    struct addrinfo hints;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&hints, 0x00, sizeof (hints)));
    hints.ai_family     = AF_INET;
    hints.ai_socktype   = SOCK_STREAM;
    hints.ai_flags      |= AI_CANONNAME;

    if (0 != getaddrinfo(hostNameStrPtr, NULL, &hints, &result)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    res = result;

    // Prefer ip4 addresses
    while (res) {

        if (res->ai_family == AF_INET) {

            _in_addr_t_to_ipV4_add(
                    ((struct sockaddr_in*)(res->ai_addr))->sin_addr.s_addr,
                    hostIPv4AddPtr);

            freeaddrinfo(result);

            return TOMMRO_C_HW_ERR_SUCCESS;
        }

        res = res->ai_next;
    }

    freeaddrinfo(result);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateNetDNSStart(void) {

    const tommRoC_hw_net_dns_init_t init = {
            /* .setServerFunct */       NULL,
            /* .getHostByNameFunct */   _get_host_by_name,
    };

    return tommRoCHwNetDNSInitEnv(&init);
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNetDNSStop(void) {

    return tommRoCHwNetDNSCloseEnv();
}

#endif

#endif
