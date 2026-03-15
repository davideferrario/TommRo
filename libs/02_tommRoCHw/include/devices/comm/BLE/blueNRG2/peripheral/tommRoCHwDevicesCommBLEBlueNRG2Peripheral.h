
#ifndef TOMMROC_HW_DEVICES_COMM_BLE_BLUENRG2_PERIPHERAL_H_
#define TOMMROC_HW_DEVICES_COMM_BLE_BLUENRG2_PERIPHERAL_H_

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
#include "tommRoCHwCommSpecificBLE.h"
#include "tommRoCHwErr.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

#define TOMMROC_HW_DEVICES_COMM_BLE_BLUENRG2_PERIPHERAL_ADV_INTERVAL_VALID_VALUE_MIN        (0x0020)
#define TOMMROC_HW_DEVICES_COMM_BLE_BLUENRG2_PERIPHERAL_ADV_INTERVAL_VALID_VALUE_MAX        (0x4000)

#define TOMMROC_HW_DEVICES_COMM_BLE_BLUENRG2_PERIPHERAL_SLAVE_CONN_INTERVAL_VALID_VALUE_MIN (0x0006)
#define TOMMROC_HW_DEVICES_COMM_BLE_BLUENRG2_PERIPHERAL_SLAVE_CONN_INTERVAL_VALID_VALUE_MAX (0x0C80)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Put chip in general discoverable mode.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        advIntervalMin          minimum advertising interval.
 *                                          NOTE: Time = advIntervalMin * 0.625msec. Valid values: 0x0020 (20.000 ms) ... 0x4000 (10240.000 ms)
 * param[in]        advIntervalMax          maximum advertising interval.
 *                                          NOTE: Time = advIntervalMax * 0.625msec. Valid values: 0x0020 (20.000 ms) ... 0x4000 (10240.000 ms)
 * param[in]        BLEName                 BLE name.
 * param[in]        slaveConnIntervalMin    slave connection interval minimum value suggested by peripheral.
 *                                          NOTE: connection interval is defined as following: connIntervalMin = slaveConnIntervalMin x 1.25ms. Valid values: 0x0006 (7.50ms) ... 0x0C80 (4000.00ms)
 * param[in]        slaveConnIntervalMax    slave connection interval maximum value suggested by peripheral.
 *                                          NOTE: connection interval is defined as following: connIntervalMax = slaveConnIntervalMax x 1.25ms. Valid values: 0x0006 (7.50ms) ... 0x0C80 (4000.00ms)
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommBlueNRG2PeripheralSetDiscoverable(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
        const   uint16_t                            advIntervalMin,
        const   uint16_t                            advIntervalMax,
        const   tommRoC_hw_comm_ble_name_t          BLEName,
        const   uint16_t                            slaveConnIntervalMin,
        const   uint16_t                            slaveConnIntervalMax);

#endif
