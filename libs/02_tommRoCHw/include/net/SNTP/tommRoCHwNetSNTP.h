
#ifndef TOMMROC_HW_NET_SNTP_H_
#define TOMMROC_HW_NET_SNTP_H_

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

// tommRoC Hw Net SNTP start/stop functionality function type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_sntp_funct_t)(void);


// Enumeration of tommRoC Hw Net SNTP init resources.
typedef enum {

    /**
     * Hw Net SNTP start funct resource.
     *
     * initResourcePtr have to be tommRoC_hw_net_sntp_funct_t.
     */
    TOMMROC_HW_NET_SNTP_START_FUNCT = 0,

    /**
     * Hw Net SNTP stop funct resource.
     *
     * initResourcePtr have to be tommRoC_hw_net_sntp_funct_t.
     */
    TOMMROC_HW_NET_SNTP_STOP_FUNCT,

} tommRoC_hw_net_sntp_environment_resource_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Prepare single library Hw Net SNTP environment.
 * NOTE: to be used for compiler (e.g.: XC8) that are not able to distinguish
 *       internal switch and generate recursive function error message.
 *
 * param[in]        initResourcePtr         pointer to environment resource init data.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSNTPInitStart(const tommRoC_hw_net_sntp_funct_t initResourcePtr);
tommRoC_hw_err_enum_t tommRoCHwNetSNTPInitStop(const tommRoC_hw_net_sntp_funct_t initResourcePtr);


/**
 * Prepare library Hw Net SNTP environment.
 *
 * param[in]        resource                Hw Net SNTP init environment resource to set
 * param[in]        initResourcePtr         pointer to environment resource init data.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSNTPInitEnv(
        const   tommRoC_hw_net_sntp_environment_resource_enum_t         resource,
        const   void*                                           const   initResourcePtr);

/**
 * Close library Hw Net SNTP environment.
 *
 * param[in]        resource                Hw Net SNTP init environment resource to set
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSNTPCloseEnv(
        const   tommRoC_hw_net_sntp_environment_resource_enum_t         resource);

/**
 * Check if library Hw Net SNTP environment is init.
 *
 * param[in]        resource                Hw Net SNTP init environment resource to check
 * param[in]        isInitPtr               Is init boolean status.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSNTPIsInitEnv(
        const   tommRoC_hw_net_sntp_environment_resource_enum_t         resource,
                bool*                                           const   isInitPtr);

/**
 * SNTP Start.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSNTPStart(void);

/**
 * SNTP Stop.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSNTPStop(void);


/**
 * Synchronize clock with SNTP server.
 * NOTE: SNTP server selected by IPv4 address.
 *
 * param[in]        IPv4AddPtr              SNTP server IPv4 address pointer.
 * param[out]       timestampPtr            synchronized with SNTP server timerstamp pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSNTPSync(
        const   tommRoC_hw_comm_ip_v4_add_t*    const   iPv4AddPtr,
                uint32_t*                       const   timestampPtr);

/**
 * Synchronize clock with SNTP server.
 * NOTE: SNTP server selected by host name.
 *
 * param[in]        hostNameStrPtr          SNTP server host name string pointer.
 * param[out]       timestampPtr            synchronized with SNTP server timerstamp pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSNTPSyncHost(
        const   char*                           const   hostNameStrPtr,
                uint32_t*                       const   timestampPtr);

#endif
