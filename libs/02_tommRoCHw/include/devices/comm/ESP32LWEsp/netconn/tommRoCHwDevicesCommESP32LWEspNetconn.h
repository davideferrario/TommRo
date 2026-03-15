
#ifndef TOMMROC_HW_DEVICES_COMM_ESP32_LWESP_NETCONN_H_
#define TOMMROC_HW_DEVICES_COMM_ESP32_LWESP_NETCONN_H_

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
#include "tommRoCHwDevicesCommESP32LWEspNetconnDEF.h"

#include "comm/tommRoCHwComm.h"

#include "tommRoCHwBusDevice.h"
#include "tommRoCHwErr.h"
#include "tommRoCHwNet.h"

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
 * Start TCP client session [remote address: IP address].
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        ipV4AddPtr              server IP address pointer.
 * param[in]        tcpPort                 server TCP port number.
 * param[out]       socketPtr               output socket endpoint pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32LWEspNetconnConnect(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr,
        const   tommRoC_hw_comm_ip_v4_add_t*    const   ipV4AddPtr,
        const   uint16_t                                tcpPort,
                tommRoC_hw_net_socket_def_t*    const   socketPtr);

/**
 * Start TCP client session [remote address: host name].
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        hostStrPtr              host remote address string pointer.
 * param[in]        tcpPort                 server TCP port number.
 * param[out]       socketPtr               output socket endpoint pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32LWEspNetconnConnectHost(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr,
        const   char*                           const   hostStrPtr,
        const   uint16_t                                tcpPort,
                tommRoC_hw_net_socket_def_t*    const   socketPtr);

/**
 * Stop current TCP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in/out]    socketPtr               socket endpoint pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32LWEspNetconnClose(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr,
                tommRoC_hw_net_socket_def_t*    const   socketPtr);

/**
 * Send data on TCP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        socketPtr               socket endpoint pointer.
 * param[in]        writeBufferPtr          data buffer pointer.
 * param[in]        writeBufferLen          data buffer to write size [byte].
 * param[out]       writtenLenPtr           amount of data written size [byte].
 * param[in]        writeTimeoutMsec        timeout [msec].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32LWEspNetconnSendBuffer(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr,
        const   tommRoC_hw_net_socket_def_t*    const   socketPtr,
        const   void*                           const   writeBufferPtr,
        const   uint32_t                                writeBufferLen,
                uint32_t*                       const   writtenLenPtr,
        const   uint32_t                                writeTimeoutMsec);

/**
 * Get available data ready on TCP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        socketPtr               socket endpoint pointer.
 * param[out]       availableAmountPtr      amount of available data ready to be read size [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32LWEspNetconnDataReady(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr,
        const   tommRoC_hw_net_socket_def_t*    const   socketPtr,
                uint32_t*                       const   availableAmountPtr);

/**
 * Read data from TCP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        socketPtr               socket endpoint pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        readBufferLen           data buffer to read size [byte].
 * param[out]       readLenPtr              amount of data readed size [byte].
 * param[in]        readTimeoutMsec         timeout [msec].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32LWEspNetconnReadBuffer(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr,
        const   tommRoC_hw_net_socket_def_t*    const   socketPtr,
                void*                           const   readBufferPtr,
        const   uint32_t                                readBufferLen,
                uint32_t*                       const   readLenPtr,
        const   uint32_t                                readTimeoutMsec);

#endif
