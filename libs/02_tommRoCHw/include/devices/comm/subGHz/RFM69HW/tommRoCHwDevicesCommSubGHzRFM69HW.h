
#ifndef TOMMROC_HW_DEVICES_COMM_SUB_GHZ_RFM69HW_H_
#define TOMMROC_HW_DEVICES_COMM_SUB_GHZ_RFM69HW_H_

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

#include "TOMMROC.h"

#include <stdbool.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// RFM69HW broadcast node ID
#define TOMMROC_HW_DEVICES_COMM_SUB_GHZ_RFM69HW_BROADCAST_NODE_ID   (0xFF)

// RFM69HW max data length
// NOTE: to take advantage of the built in AES/CRC we limit the frame size to the
//       internal FIFO size (66 bytes - 3 bytes overhead - 2 bytes crc)
#define TOMMROC_HW_DEVICES_COMM_SUB_GHZ_RFM69HW_MAX_DATA_LEN        (61)

// Device data.
#define TOMMROC_HW_DEVICES_COMM_SUB_GHZ_RFM69HW_DEVICE_DATA_SIZE    (   TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                        TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                        TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                        TOMMROC_UTIL_U8_SIZE        +   \
                                                                        TOMMROC_UTIL_U8_SIZE        +   \
                                                                        TOMMROC_UTIL_U8_SIZE            )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Available frequency bands
typedef enum {

    TOMMROC_HW_DEVICES_COMM_SUB_GHZ_RFM69HW_FREQ_BAND_315MHZ = 0,
    TOMMROC_HW_DEVICES_COMM_SUB_GHZ_RFM69HW_FREQ_BAND_433MHZ,
    TOMMROC_HW_DEVICES_COMM_SUB_GHZ_RFM69HW_FREQ_BAND_868MHZ,
    TOMMROC_HW_DEVICES_COMM_SUB_GHZ_RFM69HW_FREQ_BAND_915MHZ,

} tommRoC_hw_devices_comm_sub_ghz_rfm69hw_freq_band_enum_t;


// RFM69HW node address structure.
typedef struct {

    uint8_t nodeID;
    uint8_t networkID;

} tommRoC_hw_devices_comm_sub_ghz_rfm69hw_node_address_t;

#define __EMPTY_tommRoC_hw_devices_comm_sub_ghz_rfm69hw_node_address_t__    \
{                                                                           \
    /* .nodeID */       0,                                                  \
    /* .networkID */    0,                                                  \
}


// Configuration structure.
typedef struct {

    tommRoC_hw_devices_comm_sub_ghz_rfm69hw_freq_band_enum_t    freqBand;
    tommRoC_hw_devices_comm_sub_ghz_rfm69hw_node_address_t      nodeAddress;
    uint8_t*                                                    aes128BitKeyPtr;    // NOTE: NULL to disable AES encryption

} tommRoC_hw_devices_comm_sub_ghz_rfm69hw_config_t;

#define __EMPTY_tommRoC_hw_devices_comm_sub_ghz_rfm69hw_config_t__                              \
{                                                                                               \
    /* .freqBand */         TOMMROC_HW_DEVICES_COMM_SUB_GHZ_RFM69HW_FREQ_BAND_315MHZ,           \
    /* .nodeAddress */      __EMPTY_tommRoC_hw_devices_comm_sub_ghz_rfm69hw_node_address_t__,   \
    /* .aes128BitKeyPtr */  NULL,                                                               \
}


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_COMM_SUB_GHZ_RFM69HW_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_comm_sub_ghz_rfm69hw_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommSubGHzRFM69HWInitSPI(
        const   tommRoC_hw_gpio_set_cb_t                            chipSelect,
        const   tommRoC_hw_gpio_set_cb_t                            chipDeSelect,
        const   tommRoC_hw_bus_t*                           const   busHandlerPtr,
        const   tommRoC_guard_t*                            const   guardPtr,
                tommRoC_hw_bus_device_specific_spi_slave_t* const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                    const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommSubGHzRFM69HWAttachDeviceData(
        const   tommRoC_hw_devices_comm_sub_ghz_rfm69hw_device_data_t*  const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        resetLow                set RESET pin low function pointer.
 * param[in]        resetHigh               set RESET pin high function pointer.
 * param[in]        DIO0Status              get DIO0 pin status function pointer (DIO0 pin is used to signal special conditions).
 * param[in]        configPtr               device configuration pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommSubGHzRFM69HWStart(
        const   tommRoC_hw_gpio_set_cb_t                                    resetLow,
        const   tommRoC_hw_gpio_set_cb_t                                    resetHigh,
        const   tommRoC_hw_gpio_get_cb_t                                    DIO0Status,
        const   tommRoC_hw_devices_comm_sub_ghz_rfm69hw_config_t*   const   configPtr,
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);






tommRoC_hw_err_enum_t tommRoCHwDevicesCommSubGHzRFM69HWSend(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
        const   uint8_t                             destNodeID,
        const   uint8_t*                    const   writeBufferPtr,
        const   uint8_t                             writeBufferLen,
        const   bool                                requestACK,
        const   bool                                sendACK);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommSubGHzRFM69HWReceive(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
                uint8_t*                    const   destNodeIDPtr,
                uint8_t*                    const   sourceNodeIDPtr,
                bool*                       const   requestACKPtr,
                bool*                       const   ACKPtr,
                uint8_t*                    const   readBufferPtr,
        const   uint8_t                             readBufferSize,
                uint8_t*                    const   readedAmountPtr);





/**
 * Stand by chip mode.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommSubGHzRFM69HWStandBy(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr);

/**
 * Sleep/wake chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommSubGHzRFM69HWSleep(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommSubGHzRFM69HWWake(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr);

#endif
