
#ifndef TOMMROC_HW_NET_H_
#define TOMMROC_HW_NET_H_

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
#include "net/azure/tommRoCHwNetAzure.h"
#include "net/coreHTTP/tommRoCHwNetCoreHTTP.h"
#include "net/coreMQTT/tommRoCHwNetCoreMQTT.h"
#include "net/DHCP/tommRoCHwNetDHCP.h"
#include "net/DNS/tommRoCHwNetDNS.h"
#include "net/HTTP/tommRoCHwNetHTTP.h"
#include "net/LwIP/tommRoCHwNetLwIP.h"
#include "net/MQTT/tommRoCHwNetMQTT.h"
#include "net/SNTP/tommRoCHwNetSNTP.h"
#include "net/socket/tommRoCHwNetSocket.h"

#include "comm/IP/tommRoCHwCommIP.h"

#include "tommRoCHwErr.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC Hw Net is interface up function type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_is_itf_up_funct_t)(bool* const isItfUpPtr);
// tommRoC Hw Net is link up function type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_is_link_up_funct_t)(bool* const isLinkUpPtr);
// tommRoC Hw Net get interface config function type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_get_itf_cfg_funct_t)(tommRoC_hw_comm_ip_v4_add_t* const ipV4AddPtr, tommRoC_hw_comm_ip_v4_mask_t* const ipV4MaskPtr, tommRoC_hw_comm_ip_v4_gateway_t* const ipV4GatewayPtr);
// tommRoC Hw Net set interface config function type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_set_itf_cfg_funct_t)(const tommRoC_hw_comm_ip_v4_add_t* const ipV4AddPtr, const tommRoC_hw_comm_ip_v4_mask_t* const ipV4MaskPtr, const tommRoC_hw_comm_ip_v4_gateway_t* const ipV4GatewayPtr);

// Enumeration of tommRoC Hw Net init resources.
typedef enum {

    /**
     * Hw Net is interface up funct resource.
     *
     * initResourcePtr have to be tommRoC_hw_net_is_itf_up_funct_t.
     */
    TOMMROC_HW_NET_IS_ITF_UP_FUNCT = 0,

    /**
     * Hw Net is link up funct resource.
     *
     * initResourcePtr have to be tommRoC_hw_net_is_link_up_funct_t.
     */
    TOMMROC_HW_NET_IS_LINK_UP_FUNCT,

    /**
     * Hw Net get interface config funct resource.
     *
     * initResourcePtr have to be tommRoC_hw_net_get_itf_cfg_funct_t.
     */
    TOMMROC_HW_NET_GET_ITF_CFG_FUNCT,

    /**
     * Hw Net set interface config funct resource.
     *
     * initResourcePtr have to be tommRoC_hw_net_set_itf_cfg_funct_t.
     */
    TOMMROC_HW_NET_SET_ITF_CFG_FUNCT,

} tommRoC_hw_net_environment_resource_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Prepare single library Hw Net environment.
 * NOTE: to be used for compiler (e.g.: XC8) that are not able to distinguish
 *       internal switch and generate recursive function error message.
 *
 * param[in]        initResourcePtr         pointer to environment resource init data.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetInitIsItfUp(const tommRoC_hw_net_is_itf_up_funct_t initResourcePtr);
tommRoC_hw_err_enum_t tommRoCHwNetInitIsLinkUp(const tommRoC_hw_net_is_link_up_funct_t initResourcePtr);
tommRoC_hw_err_enum_t tommRoCHwNetInitGetItfConfig(const tommRoC_hw_net_get_itf_cfg_funct_t initResourcePtr);
tommRoC_hw_err_enum_t tommRoCHwNetInitSetItfConfig(const tommRoC_hw_net_set_itf_cfg_funct_t initResourcePtr);


/**
 * Prepare library Hw Net environment.
 *
 * param[in]        resource                Hw Net init environment resource to set
 * param[in]        initResourcePtr         pointer to environment resource init data.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetInitEnv(
        const   tommRoC_hw_net_environment_resource_enum_t          resource,
        const   void*                                       const   initResourcePtr);

/**
 * Close library Hw Net environment.
 *
 * param[in]        resource                Hw Net init environment resource to set
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCloseEnv(
        const   tommRoC_hw_net_environment_resource_enum_t          resource);

/**
 * Check if library Hw Net environment is init.
 *
 * param[in]        resource                Hw Net init environment resource to check
 * param[out]       isInitPtr               Is init boolean status pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetIsInitEnv(
        const   tommRoC_hw_net_environment_resource_enum_t          resource,
                bool*                                       const   isInitPtr);


/**
 * Check if Hw Net interface is up.
 * If set, network interface is enabled and processes traffic.
 *
 * param[out]       isItfUpPtr              Is net interface up boolean pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetIsItfUp(bool* const isItfUpPtr);

/**
 * Check if Hw Net link is up.
 * If set, the interface has an active link (set by the network interface driver).
 *
 * param[out]       isLinkUpPtr             Is net link up boolean pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetIsLinkUp(bool* const isLinkUpPtr);

/**
 * Get/Set Hw Net interface configuration (IP, subnet mask, gateway).
 *
 * param[in/out]    ipV4AddPtr              input/output IPv4 address structure pointer.
 * param[in/out]    ipV4MaskPtr             input/output IPv4 subnet mask structure pointer.
 * param[in/out]    ipV4GatewayPtr          input/output IPv4 gateway structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetGetItfConfig(
                tommRoC_hw_comm_ip_v4_add_t*        const   ipV4AddPtr,
                tommRoC_hw_comm_ip_v4_mask_t*       const   ipV4MaskPtr,
                tommRoC_hw_comm_ip_v4_gateway_t*    const   ipV4GatewayPtr);

tommRoC_hw_err_enum_t tommRoCHwNetSetItfConfig(
        const   tommRoC_hw_comm_ip_v4_add_t*        const   ipV4AddPtr,
        const   tommRoC_hw_comm_ip_v4_mask_t*       const   ipV4MaskPtr,
        const   tommRoC_hw_comm_ip_v4_gateway_t*    const   ipV4GatewayPtr);


/**
 * Functions to convert between host and network byte order.
 * NOTE: Network byte order is always Big-Endian and host byte order can be either Little-Endian or Big-Endian.
 *
 * param[in]        value                   input value.
 *
 * return uint16_t/uint32_t
 */
uint32_t tommRoCHwNetNToHL(const uint32_t value);
uint16_t tommRoCHwNetNToHS(const uint16_t value);
uint32_t tommRoCHwNetHToNL(const uint32_t value);
uint16_t tommRoCHwNetHToNS(const uint16_t value);

#endif
