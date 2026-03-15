
#ifndef TOMMROC_HW_DEVICES_COMM_ESP32_AT_MQTT_DEF_H_
#define TOMMROC_HW_DEVICES_COMM_ESP32_AT_MQTT_DEF_H_

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
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// MQTT subscribe message type.
typedef struct {

    void*       topicDataPtr;
    uint32_t    topicDataSize;

    void*       payloadPtr;
    uint32_t    payloadSize;

} tommRoC_hw_devices_comm_esp32_at_mqtt_def_incoming_message_data_t;

// MQTT subscribe incoming message data callback function type definition.
typedef void (*tommRoC_hw_devices_comm_esp32_at_mqtt_def_incoming_data_cb_t)(const tommRoC_hw_devices_comm_esp32_at_mqtt_def_incoming_message_data_t* const messageDataPtr);

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
