
#ifndef TOMMROC_HW_DEVICES_COMM_GSM_GPRS_SARA_R4_H_
#define TOMMROC_HW_DEVICES_COMM_GSM_GPRS_SARA_R4_H_

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

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/**
 * NOTE:
 * from AT commands manual - 19.3.1 section: Up to 7 sockets can be created.
 */
#define TOMMROC_HW_DEVICES_COMM_GSM_GPRS_SARA_R4_ACTIVE_SOCKET_AMOUNT       (7)


// Device data.
#define TOMMROC_HW_DEVICES_COMM_GSM_GPRS_SARA_R4_DEVICE_DATA_SIZE   (   TOMMROC_UTIL_FUNCT_PTR_SIZE                         +   \
                                                                        TOMMROC_UTIL_FUNCT_PTR_SIZE                         +   \
                                                                        TOMMROC_UTIL_FUNCT_PTR_SIZE                         +   \
                                                                        TOMMROC_UTIL_FUNCT_PTR_SIZE                         +   \
                                                                        TOMMROC_HW_COMM_GSM_GPRS_IMEI_STRING_DEVICE_SIZE        )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef enum {

    TOMMROC_HW_DEVICES_COMM_GSM_GPRS_SARA_R4_SMS_STAT_REC_UNREAD = 0,
    TOMMROC_HW_DEVICES_COMM_GSM_GPRS_SARA_R4_SMS_STAT_REC_READ,
    TOMMROC_HW_DEVICES_COMM_GSM_GPRS_SARA_R4_SMS_STAT_STO_UNSENT,
    TOMMROC_HW_DEVICES_COMM_GSM_GPRS_SARA_R4_SMS_STAT_STO_SENT,

} tommRoC_hw_devices_comm_gsm_gprs_sara_r4_sms_stat_enum_t;

// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_COMM_GSM_GPRS_SARA_R4_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_comm_gsm_gprs_sara_r4_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommGSMGPRSSaraR4InitUART(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommGSMGPRSSaraR4AttachDeviceData(
        const   tommRoC_hw_devices_comm_gsm_gprs_sara_r4_device_data_t*         const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        pwrOnLow                set PWR_ON pin low function pointer (NULL if none).
 * param[in]        pwrOnHigh               set PWR_ON pin high function pointer (NULL if none).
 * param[in]        resetNLow               set RESET_N pin low function pointer (NULL if none).
 * param[in]        resetNHigh              set RESET_N pin high function pointer (NULL if none).
 * param[in]        apnStrPtr               Access Point Name string pointer (NULL if none).
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommGSMGPRSSaraR4Start(
        const   tommRoC_hw_gpio_set_cb_t                                                pwrOnLow,
        const   tommRoC_hw_gpio_set_cb_t                                                pwrOnHigh,
        const   tommRoC_hw_gpio_set_cb_t                                                resetNLow,
        const   tommRoC_hw_gpio_set_cb_t                                                resetNHigh,
        const   char*                                                           const   apnStrPtr,
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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommGSMGPRSSaraR4IMEIRead(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
                char*                                                           const   IMEIStrPtr,
        const   uint16_t                                                                IMEIStrSize);


/******************* SMS */

tommRoC_hw_err_enum_t tommRoCHwDevicesCommGSMGPRSSaraR4SMSReadMessage(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   uint32_t                                                                index,
                tommRoC_hw_devices_comm_gsm_gprs_sara_r4_sms_stat_enum_t*       const   statPtr,
                char*                                                           const   SMSSourceAddStrPtr,
        const   uint32_t                                                                SMSSourceAddStrSize,
                uint16_t*                                                       const   SMSSourceAddStrLenPtr,
                char*                                                           const   SMSTextStrPtr,
        const   uint32_t                                                                SMSTextStrSize,
                uint16_t*                                                       const   SMSTextStrLenPtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommGSMGPRSSaraR4SMSSendMessage(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   char*                                                           const   SMSDestAddStrPtr,
        const   char*                                                           const   SMSTextStrPtr);


/******************* Connection Configuration */

/**
 * Activates PDP context.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        apnStrPtr               Access Point Name string pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommGSMGPRSSaraR4PDPContextActive(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Deactivates PDP context.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        apnStrPtr               Access Point Name string pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommGSMGPRSSaraR4PDPContextDeactive(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommGSMGPRSSaraR4GetNetworkStatus(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommGSMGPRSSaraR4PDPGetIPAddress(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
                tommRoC_hw_comm_ip_v4_add_t*                                    const   ipV4AddPtr);


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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommGSMGPRSSaraR4SocketTCPClientStart(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommGSMGPRSSaraR4SocketTCPClientStartHost(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommGSMGPRSSaraR4SocketTCPClientStop(
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
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommGSMGPRSSaraR4SocketTCPClientSendBuffer(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   tommRoC_hw_net_socket_def_t*                                    const   socketPtr,
        const   void*                                                           const   writeBufferPtr,
        const   uint32_t                                                                writeBufferLen,
                uint32_t*                                                       const   writtenLenPtr);

/**
 * Get available data ready on TCP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        socketPtr               socket endpoint pointer.
 * param[out]       availableAmountPtr      amount of available data ready to be read size [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommGSMGPRSSaraR4SocketTCPClientDataReady(
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
 * param[in]        readTimeoutMsec         timeout of read operation [msec].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommGSMGPRSSaraR4SocketTCPClientReadBuffer(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommGSMGPRSSaraR4NetSocketOnlyClient(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   tommRoC_guard_t*                                                const   guardPtr);

/**
 * Close library Hw Net Socket for only client using this device.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommGSMGPRSSaraR4NetSocketClose(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

#endif
