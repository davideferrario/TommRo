
#ifndef TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_H_
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_H_

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

#include "comm/tommRoCHwComm.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/
                                                                                //              Time     ,Latitude   ,Longitude   ,F,NS,HD ,Alt  ,
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_STR_MAX_SIZE             (sizeof("$GPGGA,000000.00,0000.0000,N,00000.0000,W,0,00,0.0,000.0,M,-00.0,M,,*00"))
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_STR_LEN_SIZE             (TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_STR_MAX_SIZE - TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)

#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_TIME_STR_MAX_SIZE        (sizeof("000000.00"))
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_TIME_STR_LEN_SIZE        (TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_TIME_STR_MAX_SIZE - TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_LATITUDE_STR_MAX_SIZE    (sizeof("0000.0000,N"))
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_LATITUDE_STR_LEN_SIZE    (TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_LATITUDE_STR_MAX_SIZE - TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_LONGITUDE_STR_MAX_SIZE   (sizeof("00000.0000,W"))
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_LONGITUDE_STR_LEN_SIZE   (TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_LONGITUDE_STR_MAX_SIZE - TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_FIX_QUALITY_STR_MAX_SIZE (sizeof("0"))
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_FIX_QUALITY_STR_LEN_SIZE (TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_FIX_QUALITY_STR_MAX_SIZE - TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_NUM_SAT_STR_MAX_SIZE     (sizeof("00"))
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_NUM_SAT_STR_LEN_SIZE     (TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_NUM_SAT_STR_MAX_SIZE - TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_ALTITUDE_STR_MAX_SIZE    (sizeof("00000.0"))
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_ALTITUDE_STR_LEN_SIZE    (TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_ALTITUDE_STR_MAX_SIZE - TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)


                                                                                //              Time     ,W,Latitude   ,Longitude   ,Speed,Cours,Date  ,
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPRMC_STR_MAX_SIZE             (sizeof("$GPRMC,000000.00,A,0000.0000,N,00000.0000,E,000.0,000.0,000000,000.0,000.0,W,-0.00e-00*0A"))
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPRMC_STR_LEN_SIZE             (TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPRMC_STR_MAX_SIZE - TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)

#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPRMC_TIME_STR_MAX_SIZE        (sizeof("000000.00"))
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPRMC_TIME_STR_LEN_SIZE        (TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPRMC_TIME_STR_MAX_SIZE - TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPRMC_STATUS_STR_MAX_SIZE      (sizeof("A"))
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPRMC_STATUS_STR_LEN_SIZE      (TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPRMC_STATUS_STR_MAX_SIZE - TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPRMC_LATITUDE_STR_MAX_SIZE    (sizeof("0000.0000,N"))
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPRMC_LATITUDE_STR_LEN_SIZE    (TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPRMC_LATITUDE_STR_MAX_SIZE - TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPRMC_LONGITUDE_STR_MAX_SIZE   (sizeof("00000.0000,E"))
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPRMC_LONGITUDE_STR_LEN_SIZE   (TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPRMC_LONGITUDE_STR_MAX_SIZE - TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPRMC_DATE_STR_MAX_SIZE        (sizeof("000000"))
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPRMC_DATE_STR_LEN_SIZE        (TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPRMC_DATE_STR_MAX_SIZE - TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)

#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_IMEI_DEVICE_SIZE                    (15 + 1)
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_IMEI_DEVICE_STRING_LENGTH           (TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_IMEI_DEVICE_SIZE - TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)

// Device data.
#define TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_DEVICE_DATA_SIZE                    (TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_IMEI_DEVICE_SIZE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// NMEA GPGGA string.
typedef struct {
    char data[TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPGGA_STR_MAX_SIZE];
} tommRoC_hw_devices_comm_lpwa_hl780x_nmea_gpgga_t;

// NMEA GPRMC string.
typedef struct {
    char data[TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_NMEA_GPRMC_STR_MAX_SIZE];
} tommRoC_hw_devices_comm_lpwa_hl780x_nmea_gprmc_t;


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_comm_lpwa_hl780x_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xInitUART(
        const   tommRoC_hw_bus_t*                                   const   busHandlerPtr,
        const   tommRoC_guard_t*                                    const   guardPtr,
                tommRoC_hw_bus_device_specific_uart_t*              const   specificPtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xAttachDeviceData(
        const   tommRoC_hw_devices_comm_lpwa_hl780x_device_data_t*  const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xStart(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);


/******************* General Configuration */

/**
 * Read IMEI.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       IMEIStrPtr              IMEI string pointer. Have to be an array of TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_IMEI_DEVICE_SIZE byte size.
 *                                          IMEI is a string of maximum TOMMROC_HW_DEVICES_COMM_LPWA_HL780x_IMEI_DEVICE_STRING_LENGTH length + '\0' character.
 * param[in]        IMEIStrSize             IMEI string array size.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xIMEIRead(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
                char*                                               const   IMEIStrPtr,
        const   uint16_t                                                    IMEIStrSize);


/******************* Connection Configuration */

/**
 * Start GNSS section of chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        apnStrPtr               Access Point Name string pointer.
 * param[in]        cnxLoginStrPtr          User name of the cnx string pointer (NULL if none).
 * param[in]        cnxPasswordStrPtr       Password name of the cnx string pointer (NULL if none).
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xGPRSConfig(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   char*                                               const   apnStrPtr,
        const   char*                                               const   cnxLoginStrPtr,
        const   char*                                               const   cnxPasswordStrPtr);


/******************* TCP client */

/**
 * Start TCP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        ipV4AddPtr              server IP address pointer.
 * param[in]        tcpPort                 server TCP port number.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xTCPClientStart(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   tommRoC_hw_comm_ip_v4_add_t*                        const   ipV4AddPtr,
        const   uint16_t                                                    tcpPort);

/**
 * Stop current TCP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xTCPClientStop(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Get IP address of TCP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        ipV4AddPtr              device IP address pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xTCPClientGetIPAddress(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
                tommRoC_hw_comm_ip_v4_add_t*                        const   ipV4AddPtr);

/**
 * Send data on TCP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        dataBufferPtr           data buffer pointer.
 * param[in]        dataBufferLen           data buffer length.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xTCPClientSendBuffer(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   uint8_t*                                            const   dataBufferPtr,
        const   uint16_t                                                    dataBufferLen);

/**
 * Get amount of available received data on TCP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       availableAmountPtr      amount of available received data pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xTCPClientDataReady(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
                uint16_t*                                           const   availableAmountPtr);

/**
 * Read data from TCP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xTCPClientReadBuffer(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
                uint8_t*                                            const   readBufferPtr,
        const   uint16_t                                                    toReadAmount,
                uint16_t*                                           const   readedAmountPtr);


/******************* HTTP client */

/**
 * Start HTTP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        httpServerStrPtr        http server string pointer.
 * param[in]        httpPort                http server port number.
 * param[in]        httpVersion             http version (supported HTTP 1.1 o rHTTPS).
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xHTTPClientStart(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   char*                                               const   httpServerStrPtr,
        const   uint16_t                                                    httpPort,
        const   tommRoC_hw_comm_http_version_enum_t                         httpVersion);

/**
 * Stop current HTTP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xHTTPClientStop(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Perform a HTTP GET request and retrieve answer from HTTP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        requestURIStrPtr        HTTP GET request URI string pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xHTTPClientPerformGET(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   char*                                               const   requestURIStrPtr,
                uint8_t*                                            const   readBufferPtr,
        const   uint16_t                                                    toReadAmount,
                uint16_t*                                           const   readedAmountPtr);

/**
 * Perform a HTTP POST request and retrieve answer from HTTP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        requestHeaderStrsPtr    request header (content-length excluded) string pointer array (can be NULL).
 * param[in]        requestHeaderStrsAmount request header string pointer array element amount (can be zero).
 * param[in]        localURIStrPtr          HTTP POST local URI string pointer (can be NULL).
 * param[in]        requestURIStrPtr        HTTP POST request URI string pointer.
 * param[in]        requestDataStrPtr       HTTP POST request payload data string pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xHTTPClientPerformPOST(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   char**                                              const   requestHeaderStrsPtr,
        const   uint8_t                                                     requestHeaderStrsAmount,
        const   char*                                               const   localURIStrPtr,
        const   char*                                               const   requestURIStrPtr,
        const   char*                                               const   requestDataStrPtr,
                uint8_t*                                            const   readBufferPtr,
        const   uint16_t                                                    toReadAmount,
                uint16_t*                                           const   readedAmountPtr);


/******************* FTP client */

/**
 * Start FTP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        ipV4AddPtr              server IP address pointer.
 * param[in]        tcpPort                 server TCP port number.
 * param[in]        loginStrPtr             FTP username (NULL if not used).
 * param[in]        passwordStrPtr          FTP password (NULL if not used).
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xFTPClientStart(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   tommRoC_hw_comm_ip_v4_add_t*                        const   ipV4AddPtr,
        const   uint16_t                                                    tcpPort,
        const   char*                                               const   loginStrPtr,
        const   char*                                               const   passwordStrPtr);

/**
 * Start FTP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        serverStrPtr            host server name string pointer.
 * param[in]        tcpPort                 server TCP port number.
 * param[in]        loginStrPtr             FTP username (NULL if not used).
 * param[in]        passwordStrPtr          FTP password (NULL if not used).
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xFTPClientStartHost(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   char*                                               const   serverStrPtr,
        const   uint16_t                                                    tcpPort,
        const   char*                                               const   loginStrPtr,
        const   char*                                               const   passwordStrPtr);

/**
 * Stop current FTP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xFTPClientStop(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Download a file from current FTP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        serverPathStrPtr        path of the file (NULL if path given by the FTP server used).
 * param[in]        fileNameStrPtr          name of the file to download.
 * param[in]        dataOffset              offset to "resume transfer" (used to packet FTP download).
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xFTPClientDownloadFile(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   char*                                               const   serverPathStrPtr,
        const   char*                                               const   fileNameStrPtr,
        const   uint32_t                                                    dataOffset,
                uint8_t*                                            const   readBufferPtr,
        const   uint16_t                                                    toReadAmount,
                uint16_t*                                           const   readedAmountPtr);

/**
 * Upload a file to current FTP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        serverPathStrPtr        path of the file (NULL if path given by the FTP server used).
 * param[in]        fileNameStrPtr          name of the file to delete.
 * param[in]        dataOffset              offset to "resume transfer" (used to packet FTP upload).
 * param[in]        dataBufferPtr           data buffer pointer.
 * param[in]        dataBufferLen           data buffer length.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xFTPClientUploadFile(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   char*                                               const   serverPathStrPtr,
        const   char*                                               const   fileNameStrPtr,
        const   uint32_t                                                    dataOffset,
        const   uint8_t*                                            const   dataBufferPtr,
        const   uint16_t                                                    dataBufferLen);

/**
 * Delete a file on current FTP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        serverPathStrPtr        path of the file (NULL if path given by the FTP server used).
 * param[in]        fileNameStrPtr          name of the file to delete.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xFTPClientDeleteFile(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   char*                                               const   serverPathStrPtr,
        const   char*                                               const   fileNameStrPtr);

/**
 * Check if a file exist and get file size on current FTP client session.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        serverPathStrPtr        path of the file (NULL if path given by the FTP server used).
 * param[in]        fileNameStrPtr          name of the file to delete.
 * param[out]       fileExistPtr            file exist boolean pointer.
 * param[out]       fileSizePtr             file size pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xFTPClientFileSize(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   char*                                               const   serverPathStrPtr,
        const   char*                                               const   fileNameStrPtr,
                bool*                                               const   fileExistPtr,
                uint32_t*                                           const   fileSizePtr);


/******************* NMEA */

/**
 * Get valid NMEA strings.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       GPGGAStringPtr          output GPGGA string pointer (NULL if not needed).
 * param[out]       GPRMCStringPtr          output GPRMC string pointer (NULL if not needed).
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLPWAHL780xNMEAGet(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
                tommRoC_hw_devices_comm_lpwa_hl780x_nmea_gpgga_t*   const   GPGGAStringPtr,
                tommRoC_hw_devices_comm_lpwa_hl780x_nmea_gprmc_t*   const   GPRMCStringPtr);

#endif
