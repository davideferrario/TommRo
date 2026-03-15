
#ifndef TOMMROC_HW_NET_DHCP_H_
#define TOMMROC_HW_NET_DHCP_H_

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
#include "tommRoCHwErr.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC Hw Net DHCP functionality function type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_dhcp_funct_t)(void);


// Enumeration of tommRoC Hw Net DHCP init resources.
typedef enum {

    /**
     * Hw Net DHCP start funct resource.
     *
     * initResourcePtr have to be tommRoC_hw_net_dhcp_funct_t.
     */
    TOMMROC_HW_NET_DHCP_START_FUNCT = 0,

    /**
     * Hw Net DHCP stop funct resource.
     *
     * initResourcePtr have to be tommRoC_hw_net_dhcp_funct_t.
     */
    TOMMROC_HW_NET_DHCP_STOP_FUNCT,

    /**
     * Hw Net DHCP pause funct resource.
     *
     * initResourcePtr have to be tommRoC_hw_net_dhcp_funct_t.
     */
    TOMMROC_HW_NET_DHCP_PAUSE_FUNCT,

    /**
     * Hw Net DHCP resume funct resource.
     *
     * initResourcePtr have to be tommRoC_hw_net_dhcp_funct_t.
     */
    TOMMROC_HW_NET_DHCP_RESUME_FUNCT,

} tommRoC_hw_net_dhcp_environment_resource_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Prepare single library Hw Net DHCP environment.
 * NOTE: to be used for compiler (e.g.: XC8) that are not able to distinguish
 *       internal switch and generate recursive function error message.
 *
 * param[in]        initResourcePtr         pointer to environment resource init data.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetDHCPInitStart(const tommRoC_hw_net_dhcp_funct_t initResourcePtr);
tommRoC_hw_err_enum_t tommRoCHwNetDHCPInitStop(const tommRoC_hw_net_dhcp_funct_t initResourcePtr);
tommRoC_hw_err_enum_t tommRoCHwNetDHCPInitPause(const tommRoC_hw_net_dhcp_funct_t initResourcePtr);
tommRoC_hw_err_enum_t tommRoCHwNetDHCPInitResume(const tommRoC_hw_net_dhcp_funct_t initResourcePtr);


/**
 * Prepare library Hw Net DHCP environment.
 *
 * param[in]        resource                Hw Net DHCP init environment resource to set
 * param[in]        initResourcePtr         pointer to environment resource init data.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetDHCPInitEnv(
        const   tommRoC_hw_net_dhcp_environment_resource_enum_t         resource,
        const   void*                                           const   initResourcePtr);

/**
 * Close library Hw Net DHCP environment.
 *
 * param[in]        resource                Hw Net DHCP init environment resource to set
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetDHCPCloseEnv(
        const   tommRoC_hw_net_dhcp_environment_resource_enum_t         resource);

/**
 * Check if library Hw Net DHCP environment is init.
 *
 * param[in]        resource                Hw Net DHCP init environment resource to check
 * param[in]        isInitPtr               Is init boolean status.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetDHCPIsInitEnv(
        const   tommRoC_hw_net_dhcp_environment_resource_enum_t         resource,
                bool*                                           const   isInitPtr);

/**
 * DHCP Start.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetDHCPStart(void);

/**
 * DHCP Stop.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetDHCPStop(void);

/**
 * DHCP Pause.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetDHCPPause(void);

/**
 * DHCP Resume.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetDHCPResume(void);


/**
 * Get DHCP paused status.
 *
 * return bool
 */
bool tommRoCHwNetDHCPIsPaused(void);

#endif
