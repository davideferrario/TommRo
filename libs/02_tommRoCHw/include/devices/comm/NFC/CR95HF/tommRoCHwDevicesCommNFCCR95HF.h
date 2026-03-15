
#ifndef TOMMROC_HW_DEVICES_COMM_NFC_CR95HF_H_
#define TOMMROC_HW_DEVICES_COMM_NFC_CR95HF_H_

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

#include "comm/NFC/tommRoCHwCommNFC.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/**
 * Protect/Unprotect from concurrent execution on multi-thread platforms type.
 */
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_comm_nfc_cr95hf_worker_cb_t)(void);

// On discovery callback functions type definition.
typedef void (*tommRoC_hw_devices_comm_nfc_cr95hf_on_discovery_cb_funct_t)(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr,
        const   tommRoC_hw_comm_nfc_device_t*   const   nfcDevicePtr);

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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCCR95HFInitSPI(
        const   tommRoC_hw_gpio_set_cb_t                                    chipSelect,
        const   tommRoC_hw_gpio_set_cb_t                                    chipDeSelect,
        const   tommRoC_hw_bus_t*                                   const   busHandlerPtr,
        const   tommRoC_guard_t*                                    const   guardPtr,
                tommRoC_hw_bus_device_specific_spi_slave_t*         const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        protectWorker           protect from concurrent execution on multi-thread platforms function pointer.
 * param[in]        unprotectWorker         unprotect from concurrent execution on multi-thread platforms function pointer.
 * param[in]        irqInSetLow             set IRQ IN pin low function pointer.
 * param[in]        irqInSetHigh            set IRQ IN pin high function pointer.
 * param[in]        irqOutGetStatus         get IRQ OUT pin status function pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCCR95HFStart(
        const   tommRoC_hw_devices_comm_nfc_cr95hf_worker_cb_t              protectWorker,
        const   tommRoC_hw_devices_comm_nfc_cr95hf_worker_cb_t              unprotectWorker,
        const   tommRoC_hw_gpio_set_cb_t                                    irqInSetLow,
        const   tommRoC_hw_gpio_set_cb_t                                    irqInSetHigh,
        const   tommRoC_hw_gpio_get_cb_t                                    irqOutGetStatus,
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);


/******************* NFC dedicated API. */

/**
 * Start NFC discovery loop for remote NFC device detection.
 *
 * param[in]        modeTechPtr             NFC technologies to look for array pointer.
 * param[in]        modeTechAmount          NFC technologies to look for array elements amount.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCCR95HFStartDiscovery(
        const   tommRoC_hw_comm_nfc_mode_tech_t*                    const   modeTechPtr,
        const   uint8_t                                                     modeTechAmount,
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Stop NFC discovery loop for remote NFC device detection.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCCR95HFStopDiscovery(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Wait until remote NFC device is discovered (with callback version).
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        timeoutMsec             wait timeout [msec].
 * param[in]        p2pFunctCb              on NFC P2P discovery callback pointer.
 * param[in]        rwFunctCb               on NFC RW discovery callback pointer.
 * param[in]        wrongFunctCb            on wrong discovery callback pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCCR95HFWaitForDiscovery(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   uint32_t                                                    timeoutMsec,
        const   tommRoC_hw_devices_comm_nfc_cr95hf_on_discovery_cb_funct_t  p2pFunctCb,
        const   tommRoC_hw_devices_comm_nfc_cr95hf_on_discovery_cb_funct_t  rwFunctCb,
        const   tommRoC_hw_devices_comm_nfc_cr95hf_on_discovery_cb_funct_t  wrongFunctCb);


/******************* Reader/Writer dedicated API. */

/**
 * Read NFC-V single block.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        nfcDevicePtr            NFC remote device properties pointer.
 * param[in]        blockNumber             number of the block.
 * param[out]       readBufferPtr           output buffer pointer.
 * param[in]        readBufferSize          output buffer max size [byte].
 * param[out]       readBufferLenPtr        output buffer length pointer [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCCR95HFRWReadSingleBlock(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   tommRoC_hw_comm_nfc_device_t*                       const   nfcDevicePtr,
        const   uint8_t                                                     blockNumber,
                uint8_t*                                            const   readBufferPtr,
        const   uint16_t                                                    readBufferSize,
                uint16_t*                                           const   readBufferLenPtr);

/**
 * Write NFC-V single block.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        nfcDevicePtr            NFC remote device properties pointer.
 * param[in]        blockNumber             number of the block.
 * param[in]        writeBufferPtr          input buffer pointer.
 * param[in]        writeBufferLen          input buffer length [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCCR95HFRWWriteSingleBlock(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   tommRoC_hw_comm_nfc_device_t*                       const   nfcDevicePtr,
        const   uint8_t                                                     blockNumber,
        const   uint8_t*                                            const   writeBufferPtr,
        const   uint16_t                                                    writeBufferLen);

/**
 * Read NFC-V multiple blocks.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        nfcDevicePtr            NFC remote device properties pointer.
 * param[in]        firstBlockNumber        number of the first block.
 * param[in]        blocksAmount            amount of blocks.
 * param[out]       readBufferPtr           output buffer pointer.
 * param[in]        readBufferSize          output buffer max size [byte].
 * param[out]       readBufferLenPtr        output buffer length pointer [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCCR95HFRWReadBlocks(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   tommRoC_hw_comm_nfc_device_t*                       const   nfcDevicePtr,
        const   uint8_t                                                     firstBlockNumber,
        const   uint8_t                                                     blocksAmount,
                uint8_t*                                            const   readBufferPtr,
        const   uint16_t                                                    readBufferSize,
                uint16_t*                                           const   readBufferLenPtr);

/**
 * Write NFC-V multiple blocks.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        nfcDevicePtr            NFC remote device properties pointer.
 * param[in]        firstBlockNumber        number of the first block.
 * param[in]        blocksAmount            amount of blocks to write.
 * param[in]        blockSize               size of single block [byte].
 * param[in]        writeBufferPtr          input buffer pointer.
 * param[in]        writeBufferLen          input buffer length [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCCR95HFRWWriteBlocks(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   tommRoC_hw_comm_nfc_device_t*                       const   nfcDevicePtr,
        const   uint8_t                                                     firstBlockNumber,
        const   uint8_t                                                     blocksAmount,
        const   uint8_t                                                     blockSize,
        const   uint8_t*                                            const   writeBufferPtr,
        const   uint16_t                                                    writeBufferLen);

#endif
