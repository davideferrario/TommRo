
#ifndef TOMMROC_HW_NET_AZURE_CLIENT_DEF_H_
#define TOMMROC_HW_NET_AZURE_CLIENT_DEF_H_

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
#include "net/MQTT/client/tommRoCHwNetMQTTClientDEF.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC Hw Net Azure Client incoming message data callback function type.
typedef tommRoC_hw_net_mqtt_client_def_incoming_message_data_t tommRoC_hw_net_azure_client_def_incoming_message_data_t;

// tommRoC Hw Net Azure Client incoming message data callback function type definition.
typedef tommRoC_hw_net_mqtt_client_def_incoming_data_cb_t tommRoC_hw_net_azure_client_def_incoming_data_cb_t;

// tommRoC Hw Net MQTT Client message type.
typedef struct {

    void*                                           payloadPtr;
    uint32_t                                        payloadSize;

} tommRoC_hw_net_azure_client_def_message_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
