
#ifndef TOMMROC_HW_TEMPLATE_BLE_H_
#define TOMMROC_HW_TEMPLATE_BLE_H_

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

/**
 *  - Disable BLE template
 *      - __TOMMROC_HW_DISABLE_BLE_TEMPLATE__           disable library BLE template implementation.
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "BLE/env/tommRoCHwTemplateBLEEnv.h"

#include "TOMMROC.h"
#include "TOMMROCHw.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/
TOMMRO_C_UTIL_PACKED_PRE typedef struct TOMMRO_C_UTIL_PACKED_POST {
    uint8_t     flags[3];
    uint8_t     length;
    uint8_t     type;
    uint16_t    company_id;
    uint16_t    beacon_type;
} tommRoC_hw_template_ble_ibeacon_head_t;

TOMMRO_C_UTIL_PACKED_PRE typedef struct TOMMRO_C_UTIL_PACKED_POST {
    uint8_t     proximity_uuid[16];
    uint16_t    major;
    uint16_t    minor;
    int8_t      measured_power;
} tommRoC_hw_template_ble_ibeacon_vendor_t;

TOMMRO_C_UTIL_PACKED_PRE typedef struct TOMMRO_C_UTIL_PACKED_POST {

    uint8_t BLEMACAddr[TOMMROC_HW_COMM_BLE_MAC_ADDRESS_SIZE_BYTE];  // BLE device MAC address
    int32_t rssi;                                                   // Device

    tommRoC_hw_template_ble_ibeacon_head_t      head;
    tommRoC_hw_template_ble_ibeacon_vendor_t    vendor;

} tommRoC_hw_template_ble_ibeacon_t;

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_template_ble_central_generic_scan_funct_t)(const void* const scanResultPtr);
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_template_ble_central_ibeacon_scan_funct_t)(const tommRoC_hw_template_ble_ibeacon_t* const ibeaconPtr);
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_template_ble_central_scan_completed_funct_t)(void);

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEPeripheralInit(const char* const deviceBLENameStrPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateBLEPeripheralDeInit(void);
tommRoC_hw_err_enum_t tommRoCHwTemplateBLECentralInit(void);
tommRoC_hw_err_enum_t tommRoCHwTemplateBLECentralDeInit(void);

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEPeripheralADVStart(const char* const deviceBLENameStrPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateBLEPeripheralADVStop(void);
tommRoC_hw_err_enum_t tommRoCHwTemplateBLEPeripheralADVResume(void);

tommRoC_hw_err_enum_t tommRoCHwTemplateBLECentralGenericScanStart(
        const   tommRoC_hw_template_ble_central_generic_scan_funct_t    scanFunctPtr,
        const   tommRoC_hw_template_ble_central_scan_completed_funct_t  scanCompletedFunctPtr,
        const   uint32_t                                                scanDurationSec);
tommRoC_hw_err_enum_t tommRoCHwTemplateBLECentralBeaconScanStart(
        const   tommRoC_hw_template_ble_central_ibeacon_scan_funct_t    scanFunctPtr,
        const   tommRoC_hw_template_ble_central_scan_completed_funct_t  scanCompletedFunctPtr,
        const   uint32_t                                                beaconScanDurationSec);
tommRoC_hw_err_enum_t tommRoCHwTemplateBLECentralConnect(
        const   uint8_t*                                        const   BLEMACAddrPtr,
        const   uint8_t                                                 BLEMACAddrSize,
        const   tommRoC_hw_comm_ble_uuid_len_type_enum_t                advServiceUUIDLenType,
        const   void*                                           const   advServiceUUIDPtr,
        const   uint8_t                                                 advServiceUUIDSize,
        const   tommRoC_hw_comm_ble_uuid_len_type_enum_t                toWriteCharUUIDLenType,
        const   void*                                           const   toWriteCharUUIDPtr,
        const   uint8_t                                                 toWriteCharUUIDSize,
        const   tommRoC_hw_comm_ble_uuid_len_type_enum_t                notifyCharUUIDLenType,
        const   void*                                           const   notifyCharUUIDPtr,
        const   uint8_t                                                 notifyCharUUIDSize);

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEDisconnect(void);
bool tommRoCHwTemplateBLEIsConnected(void);

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEWrite(
        const   void*                                           const   dataBufferPtr,
        const   uint32_t                                                dataBufferSize,
        const   bool                                                    writeWithRsp);

#endif
