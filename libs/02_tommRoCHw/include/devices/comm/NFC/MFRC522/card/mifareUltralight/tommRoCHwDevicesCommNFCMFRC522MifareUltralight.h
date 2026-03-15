
#ifndef TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_MIFARE_ULTRALIGHT_H_
#define TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_MIFARE_ULTRALIGHT_H_

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
#include "tommRoCHwBusDevice.h"
#include "tommRoCHwErr.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Mifare Ultralight card UUID size
#define TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_MIFARE_ULTRALIGHT_UUID_SIZE_BYTE    (7)

// Mifare Ultralight card memory page amount
#define TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_MIFARE_ULTRALIGHT_PAGE_AMOUNT       (16)
// Mifare Ultralight card memory page size
#define TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_MIFARE_ULTRALIGHT_PAGE_SIZE_BYTE    (4)
// Mifare Ultralight card memory size
#define TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_MIFARE_ULTRALIGHT_MEMORY_SIZE_BYTE  (TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_MIFARE_ULTRALIGHT_PAGE_AMOUNT * TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_MIFARE_ULTRALIGHT_PAGE_SIZE_BYTE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* NFC dedicated API. */

/**
 * Get card UUID.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        timeoutMsec             wait timeout [msec].
 * param[out]       UUIDPtr                 card UUID buffer pointer.
 * param[in]        UUIDSize                card UUID buffer size [byte].
 * param[out]       UUIDLenPtr              card UUID buffer length [byte] pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCMFRC522MifareUltralightGetCardUUID(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
        const   uint32_t                            timeoutMsec,
                uint8_t*                    const   UUIDPtr,
        const   uint8_t                             UUIDSize,
                uint8_t*                    const   UUIDLenPtr);


/******************* Reader/Writer dedicated API. */

/**
 * Read page memory of a card.
 * NOTE: the device responds to the READ command by sending 16 bytes starting from the page address defined in the command.
 * Example: if ADR is 3, pages 3,4,5,6 are returned. A roll back is implemented.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        timeoutMsec             wait timeout [msec].
 * param[in]        pageAddress             page address [0 - 15]
 * param[out]       readBufferPtr           output buffer pointer.
 * param[in]        readBufferSize          output buffer max size [byte].
 * param[out]       readBufferLenPtr        output buffer length pointer [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCMFRC522MifareUltralightReadMemory(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
        const   uint32_t                            timeoutMsec,
        const   uint8_t                             pageAddress,
                void*                       const   readBufferPtr,
        const   uint16_t                            readBufferSize,
                uint16_t*                   const   readBufferLenPtr);

#endif
