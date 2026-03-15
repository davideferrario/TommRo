
#ifndef TOMMROC_HW_DEVICES_COMM_ESP32_AT_MQTT_H_
#define TOMMROC_HW_DEVICES_COMM_ESP32_AT_MQTT_H_

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
#include "tommRoCHwDevicesCommESP32ATMQTTDEF.h"

#include "net/MQTT/tommRoCHwNetMQTTDEF.h"

#include "comm/IP/IPv4/tommRoCHwCommIPv4.h"

#include "comm/tommRoCHwComm.h"

#include "tommRoCHwBus.h"
#include "tommRoCHwBusDevice.h"
#include "tommRoCHwErr.h"
#include "tommRoCHwNet.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Register callback used for MQTT incoming message reception.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        incomingDataCb          notification incoming data callback function (NULL to disable).
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32ATMQTTRegisterIncomingMsgCb(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   tommRoC_hw_devices_comm_esp32_at_mqtt_def_incoming_data_cb_t            incomingDataCb);

/**
 * Set MQTT user configuration.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        clientIDStrPtr          MQTT client ID string pointer.
 * param[in]        usernameStrPtr          username to login to MQTT broker string pointer.
 * param[in]        passwordStrPtr          password to login to MQTT broker string pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32ATMQTTUserConfig(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   char*                                                           const   clientIDStrPtr,
        const   char*                                                           const   usernameStrPtr,
        const   char*                                                           const   passwordStrPtr);

/**
 * Connect to the IPv4 address MQTT broker.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        ipV4AddPtr              IPv4 address MQTT broker to connect pointer.
 * param[in]        tcpPort                 MQTT broker TCP port.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32ATMQTTConnect(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   tommRoC_hw_comm_ip_v4_add_t*                                    const   ipV4AddPtr,
        const   uint16_t                                                                tcpPort);

/**
 * Connect to the string host address MQTT broker.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        hostStrPtr              host address MQTT broker as string to connect pointer.
 * param[in]        tcpPort                 MQTT broker TCP port.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32ATMQTTConnectHost(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   char*                                                           const   hostStrPtr,
        const   uint16_t                                                                tcpPort);

/**
 * Disconnect a MQTT client endpoint.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32ATMQTTClose(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Check if MQTT client endpoint is connected to a MQTT broker.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       isConnectedPtr          is connected boolean pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32ATMQTTIsConnected(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
                bool*                                                           const   isConnectedPtr);

/**
 * Publish data to an MQTT topic.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        topicStrPtr             MQTT topic string pointer.
 * param[in]        payloadBufferPtr        payload buffer pointer.
 * param[in]        payloadBufferLen        payload buffer length [byte].
 * param[in]        QoS                     Quality of Service.
 * param[in]        retain                  retain flag.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32ATMQTTPublish(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   char*                                                           const   topicStrPtr,
        const   void*                                                           const   payloadBufferPtr,
        const   uint32_t                                                                payloadBufferLen,
        const   tommRoC_hw_net_mqtt_client_def_qos_enum_t                               QoS,
        const   tommRoC_hw_net_mqtt_client_def_retain_enum_t                            retain);

/**
 * Subscribe to a MQTT topic.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        topicStrPtr             MQTT topic string pointer.
 * param[in]        QoS                     Quality of Service.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32ATMQTTSubscribe(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   char*                                                           const   topicStrPtr,
        const   tommRoC_hw_net_mqtt_client_def_qos_enum_t                               QoS);

/**
 * Unsubscribe from a MQTT topic.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        topicStrPtr             MQTT topic string pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32ATMQTTUnsubscribe(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   char*                                                           const   topicStrPtr);

/**
 * Yield MQTT - check for incoming data on subscribd topic.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        timeoutMsec             MQTT yield timeout [msec].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32ATMQTTYield(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   uint32_t                                                                timeoutMsec);

#endif
