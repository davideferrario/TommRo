
#ifndef TOMMROC_HW_DEVICES_COMM_ETH_ADIN1110_H_
#define TOMMROC_HW_DEVICES_COMM_ETH_ADIN1110_H_

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
#include "comm/ETH/tommRoCHwCommETH.h"

#include "tommRoCHwBus.h"
#include "tommRoCHwBusDevice.h"
#include "tommRoCHwErr.h"
#include "tommRoCHwGPIO.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// ADIN1110 buffer size [byte]
#define TOMMROC_HW_DEVICES_COMM_ETH_ADIN1110_BUFFER_SIZE_BYTE   (1530)


// Device data.
#define TOMMROC_HW_DEVICES_COMM_ETH_ADIN1110_DEVICE_DATA_SIZE   (   TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE     )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_COMM_ETH_ADIN1110_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_comm_eth_adin1110_device_data_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init bus device as for SPI master bus.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        chipSelect              chip select function pointer.
 * param[in]        chipDeSelect            chip de-select function pointer.
 * param[in]        busHandlerPtr           bus pointer.
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[out]       specificSlavePtr        output specific SPI slave pointer [needed as static because linked by bus device].
 * param[out]       busDevicePtr            output bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommETHADIN1110InitSPI(
        const   tommRoC_hw_gpio_set_cb_t                                    chipSelect,
        const   tommRoC_hw_gpio_set_cb_t                                    chipDeSelect,
        const   tommRoC_hw_bus_t*                                   const   busHandlerPtr,
        const   tommRoC_guard_t*                                    const   guardPtr,
                tommRoC_hw_bus_device_specific_spi_slave_t*         const   specificSlavePtr,
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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommETHADIN1110AttachDeviceData(
        const   tommRoC_hw_devices_comm_eth_adin1110_device_data_t* const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        resetLow                set RESET pin low function pointer.
 * param[in]        resetHigh               set RESET pin high function pointer.
 * param[in]        MACAddBuffer            MAC address to assign to the device buffer pointer.
 * param[in]        MACAddBufferSize        MAC address to assign to the device buffer size [byte].
 *                                          NOTE: it MUST be TOMMROC_HW_COMM_ETH_MAC_ADDRESS_SIZE_BYTE.
 * param[in]        CRC8Enabled             CRC8 enabled status.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommETHADIN1110Start(
        const   tommRoC_hw_gpio_set_cb_t                                    resetLow,
        const   tommRoC_hw_gpio_set_cb_t                                    resetHigh,
        const   uint8_t*                                            const   MACAddBuffer,
        const   uint8_t                                                     MACAddBufferSize,
        const   tommRoC_util_enabled_status_enum_t                          CRC8Enabled,
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Stop chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommETHADIN1110Stop(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Set chip in promiscuous mode.
 * NOTE: all MAC filters are dropped.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommETHADIN1110SetPromisc(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Write a frame to the chip TX FIFO.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        destMACAddBuffer        destination MAC address buffer pointer.
 * param[in]        destMACAddBufferSize    destination MAC address buffer size [byte].
 *                                          NOTE: it MUST be TOMMROC_HW_COMM_ETH_MAC_ADDRESS_SIZE_BYTE.
 * param[in]        dataBufferPtr           data buffer pointer.
 * param[in]        dataBufferSize          data buffer size [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommETHADIN1110WriteTxFIFO(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   uint8_t*                                            const   destMACAddBuffer,
        const   uint8_t                                                     destMACAddBufferSize,
        const   void*                                               const   dataBufferPtr,
        const   uint32_t                                                    dataBufferSize);

/**
 * Read a frame from the chip RX FIFO.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       destMACAddBuffer        destination MAC address buffer pointer.
 * param[in]        destMACAddBufferSize    destination MAC address buffer size [byte].
 * param[out]       sourceMACAddBuffer      source MAC address buffer pointer.
 * param[in]        sourceMACAddBufferSize  source MAC address buffer size [byte].
 * param[out]       dataBufferPtr           data buffer pointer.
 * param[in]        dataBufferSize          data buffer maximum size [byte].
 *                                          NOTE: must be TOMMROC_HW_DEVICES_COMM_ETH_ADIN1110_BUFFER_SIZE_BYTE.
 * param[out]       dataBufferLenPtr        data buffer length [byte] pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommETHADIN1110ReadRxFIFO(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
                uint8_t*                                            const   destMACAddBuffer,
        const   uint8_t                                                     destMACAddBufferSize,
                uint8_t*                                            const   sourceMACAddBuffer,
        const   uint8_t                                                     sourceMACAddBufferSize,
                void*                                               const   dataBufferPtr,
        const   uint32_t                                                    dataBufferSize,
                uint32_t*                                           const   dataBufferLenPtr);

#endif
