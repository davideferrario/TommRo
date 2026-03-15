
#ifndef TOMMROC_HW_COMM_H_
#define TOMMROC_HW_COMM_H_

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
#include "comm/BLE/tommRoCHwCommBLE.h"
#include "comm/ETH/tommRoCHwCommETH.h"
#include "comm/GSMGPRS/tommRoCHwCommGSMGPRS.h"
#include "comm/HTTP/tommRoCHwCommHTTP.h"
#include "comm/IP/tommRoCHwCommIP.h"
#include "comm/location/tommRoCHwCommLocation.h"
#include "comm/NFC/tommRoCHwCommNFC.h"
#include "comm/NMEA/tommRoCHwCommNMEA.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC hardware comm hardware flow control type.
typedef enum {

    /**
     * Hardware flow control disabled.
     */
    TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_DISABLED = 0,

    /**
     * Hardware flow control only CTS.
     */
    TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_ONLY_CTS,

    /**
     * Hardware flow control only RTS.
     */
    TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_ONLY_RTS,

    /**
     * Hardware flow control completed (both CTS and RTS).
     */
    TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_CTS_RTS,

} tommRoC_hw_comm_hw_flow_control_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
