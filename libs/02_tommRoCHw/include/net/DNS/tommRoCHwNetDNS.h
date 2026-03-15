
#ifndef TOMMROC_HW_NET_DNS_H_
#define TOMMROC_HW_NET_DNS_H_

/*
 *******************************************************************************
 * License
 * (C) Copyright 2017
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications according to the supply agreement.
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: this software is provided
 * "AS IS", with no express or implied warranties of any kind, including,
 * but not limited to, any implied warranties of merchantability or
 * fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Supplier will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 */

/**
 * Author
 * TommRo Software Department
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "comm/IP/IPv4/tommRoCHwCommIPv4.h"

#include "tommRoCHwErr.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC Hw Net DNS callback functions type definition.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_dns_set_server_funct_t)(
        const   tommRoC_hw_comm_ip_v4_add_t*    const   dnsServerIPv4AddPtr);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_dns_get_host_by_name_funct_t)(
        const   char*                           const   hostNameStrPtr,
                tommRoC_hw_comm_ip_v4_add_t*    const   hostIPv4AddPtr);


// tommRoC Hw Net DNS init config structure.
typedef struct {

    /**
     * Set DNS server callback.
     * NOTE: NULL if not used.
     */
    tommRoC_hw_net_dns_set_server_funct_t       setServerFunct;

    /**
     * DNS functionality callback.
     * NOTE: can not be NULL.
     */
    tommRoC_hw_net_dns_get_host_by_name_funct_t getHostByNameFunct;

} tommRoC_hw_net_dns_init_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Prepare library Hw Net DNS environment.
 *
 * param[in]        initConfigPtr           pointer to init structure.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetDNSInitEnv(const tommRoC_hw_net_dns_init_t* const initConfigPtr);

/**
 * Close library Hw Net DNS environment.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetDNSCloseEnv(void);

/**
 * Check if library Hw Net DNS set server/get host by name environment is init.
 *
 * param[in]        isInitPtr               Is init boolean status.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetDNSIsInitSetServerEnv(bool* const isInitPtr);
tommRoC_hw_err_enum_t tommRoCHwNetDNSIsInitGetHostByNameEnv(bool* const isInitPtr);


/**
 * Set DNS server IPv4 address.
 *
 * param[in]        dnsServerIPv4AddPtr     DNS server IPv4 address pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetDNSSetServer(
        const   tommRoC_hw_comm_ip_v4_add_t*    const   dnsServerIPv4AddPtr);

/**
 * Resolve a hostname (string) into an IPv4 address..
 *
 * param[in]        hostNameStrPtr          hostname string pointer.
 * param[out]       hostIPv4AddPtr          output DNS server IPv4 address pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetDNSGetHostByName(
        const   char*                           const   hostNameStrPtr,
                tommRoC_hw_comm_ip_v4_add_t*    const   hostIPv4AddPtr);

#endif
