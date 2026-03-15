
#ifndef TOMMROC_HW_NET_CORE_MQTT_CLIENT_DEF_H_
#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_DEF_H_

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
#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/**
 * Enumeration of tommRoC Hw Core MQTT Client QoS type.
 *
 * The Quality of Service (QoS) level is an agreement between the sender and the receiver of a message
 * that defines the guarantee of delivery for a specific message.
 * There are 3 QoS levels in MQTT:
 *  - At most once  (0)
 *  - At least once (1)
 *  - Exactly once  (2)
 */
typedef enum {

    TOMMROC_HW_NET_CORE_MQTT_CLIENT_DEF_QOS_0__AT_MOST_ONCE = 0,    // At most once.
    TOMMROC_HW_NET_CORE_MQTT_CLIENT_DEF_QOS_1__AT_LEAST_ONCE,       // At least once.
    TOMMROC_HW_NET_CORE_MQTT_CLIENT_DEF_QOS_2__EXACTLY_ONCE,        // Exactly once.

} tommRoC_hw_net_core_mqtt_client_def_qos_enum_t;


/**
 * Enumeration of tommRoC Hw Core MQTT Client retain flag type.
 *
 * A retained message is a normal MQTT message with the retained flag set to true.
 * The broker stores the last retained message and the corresponding QoS for that topic.
 * Each client that subscribes to a topic pattern that matches the topic of the retained message receives the retained message
 * immediately after they subscribe.
 * The broker stores only one retained message per topic.
 */
typedef enum {

    TOMMROC_HW_NET_CORE_MQTT_CLIENT_DEF_RETAIN_FALSE = 0,
    TOMMROC_HW_NET_CORE_MQTT_CLIENT_DEF_RETAIN_TRUE,

} tommRoC_hw_net_core_mqtt_client_def_retain_enum_t;


/**
 * Enumeration of tommRoC Hw Core MQTT Client clean session flag type.
 *
 * When a client connects to a broker it can connect using:
 * - non persistent connection (clean session)
 * - persistent connection (not clean session)
 *
 * With non persistent connection (clean session) the broker doesn’t store any subscription information/undelivered messages for the client.
 * This mode is ideal when the client only publishes messages.
 *
 * It can also connect as a durable client using a persistent connection.
 */
typedef enum {

    TOMMROC_HW_NET_CORE_MQTT_CLIENT_DEF_CLEAN_SESSION_FALSE = 0,
    TOMMROC_HW_NET_CORE_MQTT_CLIENT_DEF_CLEAN_SESSION_TRUE,

} tommRoC_hw_net_core_mqtt_client_def_clean_session_enum_t;


// tommRoC Hw Core MQTT Client notify data callback function type
typedef void (*tommRoC_hw_net_core_mqtt_client_def_notify_data_cb_funct_t)(
        const   tommRoC_hw_net_core_mqtt_client_def_qos_enum_t          QoS,
        const   char*                                           const   topicNameStrPtr,    // Topic name string pointer
        const   uint16_t                                                topicNameStrLen,    // Topic name string length ('\0' char excluded)
        const   void*                                           const   payloadPtr,
        const   uint32_t                                                payloadSize);

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
