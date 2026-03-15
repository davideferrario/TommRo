
#ifndef TOMMROC_HW_DEVICES_COMM_RF868_wMBUS_METIS_H_
#define TOMMROC_HW_DEVICES_COMM_RF868_wMBUS_METIS_H_

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

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/**
 * Module Serial Number size [byte]
 *
 * NOTE: from datasheet:
 * The most significant byte is returned first (MSB first).
 * This byte identifies the product ("PID") and is followed by a 3 bytes serial number.
 */
#define TOMMROC_HW_DEVICES_COMM_RF868_wMBUS_METIS_SERIAL_NUMBER_SIZE    (4)


// Device data.
#define TOMMROC_HW_DEVICES_COMM_RF868_wMBUS_METIS_DEVICE_DATA_SIZE      (sizeof(tommRoC_fifo_ISR_t))

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of RF868 wM-BUS mode at 868 MHz.
typedef enum {

    TOMMROC_HW_DEVICES_COMM_RF868_wMBUS_METIS_MODE_S1 = 0,
    TOMMROC_HW_DEVICES_COMM_RF868_wMBUS_METIS_MODE_S1_M,        // TX only
    TOMMROC_HW_DEVICES_COMM_RF868_wMBUS_METIS_MODE_S2,          // TX and RX
    TOMMROC_HW_DEVICES_COMM_RF868_wMBUS_METIS_MODE_T1_METER,    // TX only
    TOMMROC_HW_DEVICES_COMM_RF868_wMBUS_METIS_MODE_T1_OTHER,
    TOMMROC_HW_DEVICES_COMM_RF868_wMBUS_METIS_MODE_T2_METER,    // RX and TX
    TOMMROC_HW_DEVICES_COMM_RF868_wMBUS_METIS_MODE_T2_OTHER,    // RX and TX
    TOMMROC_HW_DEVICES_COMM_RF868_wMBUS_METIS_MODE_C2_T2_OTHER, // RX only
    TOMMROC_HW_DEVICES_COMM_RF868_wMBUS_METIS_MODE_C1_METER,    // TX only
    TOMMROC_HW_DEVICES_COMM_RF868_wMBUS_METIS_MODE_C2_METER,    // RX and TX
    TOMMROC_HW_DEVICES_COMM_RF868_wMBUS_METIS_MODE_C2_OTHER,    // RX and TX

} tommRoC_hw_devices_comm_rf868_wmbus_metis_mode_enum_t;


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_COMM_RF868_wMBUS_METIS_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_comm_rf868_wmbus_metis_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRF868wMBusMetisInitUART(
        const   tommRoC_hw_bus_t*                                           const   busHandlerPtr,
        const   tommRoC_guard_t*                                            const   guardPtr,
                tommRoC_hw_bus_device_specific_uart_t*                      const   specificPtr,
                tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRF868wMBusMetisAttachDeviceData(
        const   tommRoC_hw_devices_comm_rf868_wmbus_metis_device_data_t*    const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        rxDataBufferPtr         received data buffer (internal driver used) pointer.
 * param[in]        rxDataBufferSize        received data buffer (internal driver used) size [byte].
 *                                          NOTE: one byte of buffer is not used.
 * param[in]        mode                    RF868 wM-BUS mode at 868 MHz.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRF868wMBusMetisStart(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
                void*                                                       const   rxDataBufferPtr,
        const   uint32_t                                                            rxDataBufferSize,
        const   tommRoC_hw_devices_comm_rf868_wmbus_metis_mode_enum_t               mode);

/**
 * Read module serial number.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       serialNumberPtr         serial number buffer pointer. Have to be an array of TOMMROC_HW_DEVICES_COMM_RF868_wMBUS_METIS_SERIAL_NUMBER_SIZE byte size.
 * param[in]        serialNumberSize        serial number buffer size [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRF868wMBusMetisSerialNumberRead(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
                uint8_t*                                                    const   serialNumberPtr,
        const   uint16_t                                                            serialNumberSize);

/**
 * Read module firmware version.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       majorPtr                firmware version major byte pointer.
 * param[out]       minorPtr                firmware version minor byte pointer.
 * param[out]       patchPtr                firmware version patch byte pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRF868wMBusMetisFirmwareVersionRead(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
                uint8_t*                                                    const   majorPtr,
                uint8_t*                                                    const   minorPtr,
                uint8_t*                                                    const   patchPtr);

/**
 * Transmit data.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 * param[in]        payloadPtr              application payload data buffer pointer.
 *                                          NOTE: application payload MUST be formatted in wMBUS frame (first byte MUST be Length Field).
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRF868wMBusMetisTransmit(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
        const   void*                                                       const   payloadPtr);

/**
 * Transmit data - length version.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 * param[in]        payloadPtr              application payload data buffer pointer.
 *                                          NOTE: application payload MUST be formatted in wMBUS frame but first byte MUST NOT be Length Field.
 * param[in]        payloadLen              application payload data buffer length.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRF868wMBusMetisTransmitLen(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
        const   void*                                                       const   payloadPtr,
        const   uint8_t                                                             payloadLen);

/**
 * Get amount of available received data.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 * param[out]       availableAmountPtr      amount of available received data pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRF868wMBusMetisDataReady(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
                uint16_t*                                                   const   availableAmountPtr);

/**
 * Read buffer.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRF868wMBusMetisReadBuffer(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
                void*                                                       const   readBufferPtr,
        const   uint16_t                                                            toReadAmount,
                uint16_t*                                                   const   readedAmountPtr);

#endif
