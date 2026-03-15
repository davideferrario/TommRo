
#ifndef TOMMROC_HW_DEVICES_COMM_CELLULAR_SARA_R5_H_
#define TOMMROC_HW_DEVICES_COMM_CELLULAR_SARA_R5_H_

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
#include "tommRoCHwBus.h"
#include "tommRoCHwBusDevice.h"
#include "tommRoCHwErr.h"
#include "tommRoCHwGPIO.h"
#include "tommRoCHwNet.h"

#include "comm/tommRoCHwComm.h"

#include "devices/comm/cellular/tommRoCHwDevicesCommCellularDEF.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Default timeout for network registration
#define TOMMROC_HW_DEVICES_COMM_CELLULAR_SARA_R5_WAIT_FOR_NETWORK_DEFAULT_TIMEOUT_mSEC  (TOMMROC_UNIT_MEASURE_TIME_MIN_TO_mSEC(2))

/**
 * NOTE:
 * from AT commands manual - 19.3.1 section: Up to 7 sockets can be created.
 */
#define TOMMROC_HW_DEVICES_COMM_CELLULAR_SARA_R5_ACTIVE_SOCKET_AMOUNT   (7)

// Default LwIP PPP AUTH parameters.
#define TOMMROC_HW_DEVICES_COMM_CELLULAR_SARA_R5_LWIP_PPP_AUTH_TYPE_DEFAULT         (TOMMROC_HW_NET_LWIP_PPP_DEF_AUTH_TYPE_PAP)
#define TOMMROC_HW_DEVICES_COMM_CELLULAR_SARA_R5_LWIP_PPP_AUTH_USER_STR_DEFAULT     ("")
#define TOMMROC_HW_DEVICES_COMM_CELLULAR_SARA_R5_LWIP_PPP_AUTH_PASSWD_STR_DEFAULT   ("")


// Device data.
#define TOMMROC_HW_DEVICES_COMM_CELLULAR_SARA_R5_DEVICE_DATA_SIZE   (   TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                        TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                        TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                        TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                        TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                        TOMMROC_UTIL_ENUM_SIZE          )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_COMM_CELLULAR_SARA_R5_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_comm_cellular_sara_r5_device_data_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init bus device as for UART bus.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        busHandlerPtr           bus pointer.
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[out]       specificPtr             output specific UART pointer [needed as static because linked by bus device].
 * param[out]       busDevicePtr            output bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommCellularSaraR5InitUART(
        const   tommRoC_hw_bus_t*                                               const   busHandlerPtr,
        const   tommRoC_guard_t*                                                const   guardPtr,
                tommRoC_hw_bus_device_specific_uart_t*                          const   specificPtr,
                tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommCellularSaraR5AttachDeviceData(
        const   tommRoC_hw_devices_comm_cellular_sara_r5_device_data_t*         const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        pwrOnLow                set PWR_ON pin low function pointer (NULL if none).
 * param[in]        pwrOnHigh               set PWR_ON pin high function pointer (NULL if none).
 * param[in]        resetNLow               set RESET_N pin low function pointer (NULL if none).
 * param[in]        resetNHigh              set RESET_N pin high function pointer (NULL if none).
 * param[in]        VIntStatus              get V_INT pin status function pointer (NULL if none).
 * param[in]        baudRate                baud rate to be used [bit/sec]. If used 115200, nothing is changed.
 *                                          NOTE: on start, ESP32 has baud rate=115200. Then the used UART MUST start with baud rate=115200 and it will be configured using the bus set prop function.
 * param[in]        hwFlowControl           hardware flow control.
 * param[in]        factoryReset            select if send factory reset AT command at modem startup.
 * param[in]        apnStrPtr               Access Point Name string pointer (NULL if none).
 * param[in]        waitForRegMsec          wait for modem network registration timeout [msec].
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommCellularSaraR5Start(
        const   tommRoC_hw_gpio_set_cb_t                                                pwrOnLow,
        const   tommRoC_hw_gpio_set_cb_t                                                pwrOnHigh,
        const   tommRoC_hw_gpio_set_cb_t                                                resetNLow,
        const   tommRoC_hw_gpio_set_cb_t                                                resetNHigh,
        const   tommRoC_hw_gpio_get_cb_t                                                VIntStatus,
        const   uint32_t                                                                baudRate,
        const   tommRoC_hw_comm_hw_flow_control_enum_t                                  hwFlowControl,
        const   bool                                                                    factoryReset,
        const   char*                                                           const   apnStrPtr,
        const   uint32_t                                                                waitForRegMsec,
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Start chip for LwIP stack.
 *
 * param[in]        pwrOnLow                set PWR_ON pin low function pointer (NULL if none).
 * param[in]        pwrOnHigh               set PWR_ON pin high function pointer (NULL if none).
 * param[in]        resetNLow               set RESET_N pin low function pointer (NULL if none).
 * param[in]        resetNHigh              set RESET_N pin high function pointer (NULL if none).
 * param[in]        VIntStatus              get V_INT pin status function pointer (NULL if none).
 * param[in]        baudRate                baud rate to be used [bit/sec]. If used 115200, nothing is changed.
 *                                          NOTE: on start, ESP32 has baud rate=115200. Then the used UART MUST start with baud rate=115200 and it will be configured using the bus set prop function.
 * param[in]        hwFlowControl           hardware flow control.
 * param[in]        factoryReset            select if send factory reset AT command at modem startup.
 * param[in]        apnStrPtr               Access Point Name string pointer (NULL if none).
 * param[in]        waitForRegMsec          wait for modem network registration timeout [msec].
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommCellularSaraR5StartForLwIP(
        const   tommRoC_hw_gpio_set_cb_t                                                pwrOnLow,
        const   tommRoC_hw_gpio_set_cb_t                                                pwrOnHigh,
        const   tommRoC_hw_gpio_set_cb_t                                                resetNLow,
        const   tommRoC_hw_gpio_set_cb_t                                                resetNHigh,
        const   tommRoC_hw_gpio_get_cb_t                                                VIntStatus,
        const   uint32_t                                                                baudRate,
        const   tommRoC_hw_comm_hw_flow_control_enum_t                                  hwFlowControl,
        const   bool                                                                    factoryReset,
        const   char*                                                           const   apnStrPtr,
        const   uint32_t                                                                waitForRegMsec,
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);


/******************* General Configuration */

/**
 * Read IMEI.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       IMEIStrPtr              IMEI string pointer. Have to be an array of TOMMROC_HW_COMM_GSM_GPRS_IMEI_STRING_DEVICE_SIZE byte size.
 *                                          IMEI is a string of maximum TOMMROC_HW_COMM_GSM_GPRS_IMEI_STRING_DEVICE_LENGTH length + '\0' character.
 * param[in]        IMEIStrSize             IMEI string array size.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommCellularSaraR5IMEIRead(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
                char*                                                           const   IMEIStrPtr,
        const   uint16_t                                                                IMEIStrSize);

/**
 * Read IMSI.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       IMSIStrPtr              IMSI string pointer. Have to be an array of TOMMROC_HW_COMM_GSM_GPRS_IMSI_STRING_DEVICE_SIZE byte size.
 *                                          IMSI is a string of maximum TOMMROC_HW_COMM_GSM_GPRS_IMSI_STRING_DEVICE_LENGTH length + '\0' character.
 * param[in]        IMSIStrSize             IMSI string array size.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommCellularSaraR5IMSIRead(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
                char*                                                           const   IMSIStrPtr,
        const   uint16_t                                                                IMSIStrSize);


/******************* Connection Configuration */

/**
 * Get network registration status.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       GSMStatusPtr            GSM network registration status pointer.
 * param[out]       GPRSStatusPtr           GPRS network registration status pointer.
 * param[out]       ESPStatusPtr            ESP network registration status pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommCellularSaraR5GetNetworkStatus(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
                tommRoC_hw_comm_gsm_gprs_network_registration_status_enum_t*    const   GSMStatusPtr,
                tommRoC_hw_comm_gsm_gprs_network_registration_status_enum_t*    const   GPRSStatusPtr,
                tommRoC_hw_comm_gsm_gprs_network_registration_status_enum_t*    const   ESPStatusPtr);

/**
 * Get IP address of PDP context.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        ipV4AddPtr              device IP address pointer.
 *
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommCellularSaraR5GetIPAddress(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
                tommRoC_hw_comm_ip_v4_add_t*                                    const   ipV4AddPtr);

/**
 * Get signal information.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        signalInfoPtr           signal info structure pointer.
 *
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommCellularSaraR5GetSignalInfo(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
                tommRoC_hw_devices_comm_cellular_def_signal_info_t*             const   signalInfoPtr);


/******************* Socket TCP client */

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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommCellularSaraR5SocketTCPClientConnect(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   tommRoC_hw_comm_ip_v4_add_t*                                    const   ipV4AddPtr,
        const   uint16_t                                                                tcpPort,
                tommRoC_hw_net_socket_def_t*                                    const   socketPtr);

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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommCellularSaraR5SocketTCPClientConnectHost(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   char*                                                           const   hostStrPtr,
        const   uint16_t                                                                tcpPort,
                tommRoC_hw_net_socket_def_t*                                    const   socketPtr);

/**
 * Stop current TCP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in/out]    socketPtr               socket endpoint pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommCellularSaraR5SocketTCPClientClose(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
                tommRoC_hw_net_socket_def_t*                                    const   socketPtr);

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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommCellularSaraR5SocketTCPClientSendBuffer(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   tommRoC_hw_net_socket_def_t*                                    const   socketPtr,
        const   void*                                                           const   writeBufferPtr,
        const   uint32_t                                                                writeBufferLen,
                uint32_t*                                                       const   writtenLenPtr,
        const   uint32_t                                                                writeTimeoutMsec);

/**
 * Get available data ready on TCP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        socketPtr               socket endpoint pointer.
 * param[out]       availableAmountPtr      amount of available data ready to be read size [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommCellularSaraR5SocketTCPClientDataReady(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   tommRoC_hw_net_socket_def_t*                                    const   socketPtr,
                uint32_t*                                                       const   availableAmountPtr);

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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommCellularSaraR5SocketTCPClientReadBuffer(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   tommRoC_hw_net_socket_def_t*                                    const   socketPtr,
                void*                                                           const   readBufferPtr,
        const   uint32_t                                                                readBufferLen,
                uint32_t*                                                       const   readLenPtr,
        const   uint32_t                                                                readTimeoutMsec);


/******************* TommRoC Hw Net Socket Interface */

/**
 * Init library Hw Net Socket for only client using this device.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        guardPtr                bus device Net Socket guard (NULL if none).
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommCellularSaraR5NetSocketOnlyClient(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   tommRoC_guard_t*                                                const   guardPtr);

/**
 * Close library Hw Net Socket for only client using this device.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommCellularSaraR5NetSocketClose(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);


/******************* TommRoC Hw Net LwIP Interface */

/**
 * Init library Hw Net Socket for LwIP only client using this device.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        authType                PPP authentication type.
 * param[in]        authUserStrPtr          PPP authentication user string pointer (NULL if none).
 * param[in]        authPasswdStrPtr        PPP authentication password string pointer (NULL if none).
 * param[in]        notifyPhaseCb           PPP notify phase callback function (NULL if none).
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommCellularSaraR5LwIPOnlyClient(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   tommRoC_hw_net_lwip_ppp_def_auth_type_enum_t                            authType,
        const   char*                                                           const   authUserStrPtr,
        const   char*                                                           const   authPasswdStrPtr,
        const   tommRoC_hw_net_lwip_ppp_def_notify_phase_funct_t                        notifyPhaseCb);

/**
 * Close library Hw Net Socket for only client using this device.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommCellularSaraR5LwIPClose(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

#endif
