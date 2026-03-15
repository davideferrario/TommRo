
#ifndef TOMMROC_HW_TEMPLATE_BLE_MULTI_H_
#define TOMMROC_HW_TEMPLATE_BLE_MULTI_H_

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

#include "tommRoCHwTemplateBLE.h"
#include "tommRoCHwTemplateBLEMultiDEF.h"

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

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiPeripheralInit(
        const   tommRoC_hw_template_ble_multi_def_on_connect_funct_t        onConnectFunctPtr,
        const   tommRoC_hw_template_ble_multi_def_on_disconnect_funct_t     onDisconnectFunctPtr,
        const   tommRoC_hw_template_ble_multi_def_on_receive_funct_t        onReceiveFunctPtr,
        const   char*                                               const   deviceBLENameStrPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiPeripheralDeInit(void);
tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiCentralInit(void);
tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiCentralDeInit(void);

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiPeripheralADVStart(const char* const deviceBLENameStrPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiPeripheralADVStop(void);
tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiPeripheralADVResume(void);

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiCentralGenericScanStart(
        const   tommRoC_hw_template_ble_central_generic_scan_funct_t    scanFunctPtr,
        const   tommRoC_hw_template_ble_central_scan_completed_funct_t  scanCompletedFunctPtr,
        const   uint32_t                                                scanDurationSec);
tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiCentralBeaconScanStart(
        const   tommRoC_hw_template_ble_central_ibeacon_scan_funct_t    scanFunctPtr,
        const   tommRoC_hw_template_ble_central_scan_completed_funct_t  scanCompletedFunctPtr,
        const   uint32_t                                                beaconScanDurationSec);
tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiCentralConnect(
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

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiDisconnect(tommRoC_hw_template_ble_multi_def_conn_handler_t* const connHandlerPtr);
bool tommRoCHwTemplateBLEMultiIsConnected(const tommRoC_hw_template_ble_multi_def_conn_handler_t* const connHandlerPtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiWrite(
        const   void*                                           const   dataBufferPtr,
        const   uint32_t                                                dataBufferSize,
        const   bool                                                    writeWithRsp);

#endif
