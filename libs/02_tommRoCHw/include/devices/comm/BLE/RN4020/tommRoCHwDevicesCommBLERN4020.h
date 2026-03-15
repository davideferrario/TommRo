
#ifndef TOMMROC_HW_DEVICES_COMM_BLE_RN4020_H_
#define TOMMROC_HW_DEVICES_COMM_BLE_RN4020_H_

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
#include "tommRoCHwCommSpecificBLE.h"
#include "tommRoCHwErr.h"
#include "tommRoCHwGPIO.h"

#include "TOMMROC.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// BLE device name max length.
#define RN4020_NAME_MAX_LENGTH                      (TOMMROC_HW_COMM_BLE_NAME_MAX_LENGTH)

#define RN4020_DEFAULT_ADV_INTERVAL_MSEC            (250)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/******************* Common RN4020 for <init/start struct> definition */

// tommRoC hardware RN4020 layer callback functions.
typedef struct {

    /**
     * Each function pointer is specific to particular RN4020 pin operation.
     */

    /**
     * Wake software.
     */
    tommRoC_hw_gpio_set_cb_t    wakeSoftware;

    /**
     * Sleep software.
     */
    tommRoC_hw_gpio_set_cb_t    sleepSoftware;

    /**
     * Set CMD mode.
     */
    tommRoC_hw_gpio_set_cb_t    setCMDMode;

    /**
     * Set MLDP mode.
     */
    tommRoC_hw_gpio_set_cb_t    setMLDPMode;

    /**
     * Get is connected status.
     */
    bool (*isConnected)(void);

    /**
     * Wake hardware.
     */
    tommRoC_hw_gpio_set_cb_t    wakeHardware;

    /**
     * Sleep hardware.
     */
    tommRoC_hw_gpio_set_cb_t    sleepHardware;

} tommRoC_hw_devices_comm_rn4020_cb_funct_t;

#define __EMPTY_tommRoC_hw_devices_comm_rn4020_cb_funct_t__     \
{                                                               \
    /* .wakeSoftware */     NULL,                               \
    /* .sleepSoftware */    NULL,                               \
    /* .setCMDMode */       NULL,                               \
    /* .setMLDPMode */      NULL,                               \
    /* .isConnected */      NULL,                               \
    /* .wakeHardware */     NULL,                               \
    /* .sleepHardware */    NULL,                               \
}

// tommRoC hardware RN4020.
typedef struct {

    /**
     * Callback funct struct.
     */
    tommRoC_hw_devices_comm_rn4020_cb_funct_t* cbFunctPtr;

    /**
     * Bus.
     */
    tommRoC_hw_bus_t*                           busHandlerPtr;

    /**
     * Guard (NULL if disabled).
     */
    tommRoC_guard_t*                            guardPtr;

    /**
     * BLE role.
     */
    tommRoC_hw_comm_ble_role_enum_t             role;

} tommRoC_hw_devices_comm_rn4020_t;

#define __EMPTY_tommRoC_hw_devices_comm_rn4020_t__                  \
{                                                                   \
    /* .cbFunctPtr */       NULL,                                   \
    /* .busHandlerPtr */    NULL,                                   \
    /* .guardPtr */         NULL,                                   \
    /* .role */             TOMMRO_C_HW_COMM_BLE_ROLE_NOT_INIT,     \
}

/******************* Peripheral specific RN4020 for <init/start struct> definition */

typedef enum {

    PERIPHERALA =0,

} tommRoC_hw_devices_comm_rn4020_peripheral_prop_enum_t;

typedef struct {

    /**
     * RN4020 device private service.
     */
    tommRoC_hw_comm_ble_private_service_t*          privateServicePtr;

    /**
     * RN4020 advertising interval [msec]
     */
    uint16_t                                        advIntervalMsec;

} tommRoC_hw_devices_comm_rn4020_peripheral_config_t;

#define __EMPTY_tommRoC_hw_devices_comm_rn4020_peripheral_config_t__    \
{                                                                       \
    /* .privateServicePtr */    NULL,                                   \
    /* .advIntervalMsec */      RN4020_DEFAULT_ADV_INTERVAL_MSEC,       \
}


/******************* Central specific RN4020 for <init/start struct> definition */

typedef enum {

    CENTRALA =0,

} tommRoC_hw_devices_comm_rn4020_central_prop_enum_t;

typedef struct {

} tommRoC_hw_devices_comm_rn4020_central_config_t;

#define __EMPTY_tommRoC_hw_devices_comm_rn4020_central_config_t__       \
{                                                                       \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* Common RN4020 functions */

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020InitCbFunct(
        const   tommRoC_hw_gpio_set_cb_t                            wakeSoftware,
        const   tommRoC_hw_gpio_set_cb_t                            sleepSoftware,
        const   tommRoC_hw_gpio_set_cb_t                            setCMDMode,
        const   tommRoC_hw_gpio_set_cb_t                            setMLDPMode,
        bool (*isConnected)(void),
        const   tommRoC_hw_gpio_set_cb_t                            wakeHardware,
        const   tommRoC_hw_gpio_set_cb_t                            sleepHardware,
                tommRoC_hw_devices_comm_rn4020_cb_funct_t*  const   cbFunctPtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020GetProp(
        const   tommRoC_hw_devices_comm_rn4020_t*           const   commPtr,
        const   tommRoC_hw_comm_ble_prop_enum_t                     property,
                void*                                       const   propValuePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020SetProp(
        const   tommRoC_hw_devices_comm_rn4020_t*           const   commPtr,
        const   tommRoC_hw_comm_ble_prop_enum_t                     property,
        const   void*                                       const   propValuePtr);


/******************* Peripheral specific RN4020 functions */

/**
 * Start an RN4020 device as peripheral
 *
 * NOTE: RN4020 is HW reset, factory reset, config and on exit it is set in HW/SW sleep.
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020StartAsPeripheral(
        const   tommRoC_hw_devices_comm_rn4020_cb_funct_t*              const   cbFunctPtr,
        const   tommRoC_hw_bus_t*                                       const   busHandlerPtr,
        const   tommRoC_guard_t*                                        const   guardPtr,
        const   tommRoC_hw_devices_comm_rn4020_peripheral_config_t*     const   configPtr,
                tommRoC_hw_devices_comm_rn4020_t*                       const   commPtr);

/**
 * Start an RN4020 device as MLDP profile peripheral
 *
 * NOTE: RN4020 is HW reset, factory reset, config and on exit it is set in HW/SW sleep.
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020StartAsMLDPPeripheral(
        const   tommRoC_hw_devices_comm_rn4020_cb_funct_t*              const   cbFunctPtr,
        const   tommRoC_hw_bus_t*                                       const   busHandlerPtr,
        const   tommRoC_guard_t*                                        const   guardPtr,
        const   uint16_t                                                        advIntervalMsec,
                tommRoC_hw_devices_comm_rn4020_t*                       const   commPtr);

/**
 * Start an RN4020 device as MLDP profile peripheral (specific for FOTA support)
 *
 * NOTE: RN4020 is HW reset, factory reset, config and on exit it is set in HW/SW sleep.
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020StartAsMLDPForFotaPeripheral(
        const   tommRoC_hw_devices_comm_rn4020_cb_funct_t*              const   cbFunctPtr,
        const   tommRoC_hw_bus_t*                                       const   busHandlerPtr,
        const   tommRoC_guard_t*                                        const   guardPtr,
        const   uint16_t                                                        advIntervalMsec,
                tommRoC_hw_devices_comm_rn4020_t*                       const   commPtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020PeripheralCheck(
        const   tommRoC_hw_devices_comm_rn4020_t*                       const   commPtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020PeripheralConfigInit(
        const   tommRoC_hw_comm_ble_private_service_t*                  const   privateServicePtr,
        const   uint16_t                                                        advIntervalMsec,
                tommRoC_hw_devices_comm_rn4020_peripheral_config_t*     const   configPtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020GetPeripheralProp(
        const   tommRoC_hw_devices_comm_rn4020_t*                       const   commPtr,
        const   tommRoC_hw_devices_comm_rn4020_peripheral_prop_enum_t           property,
                void*                                                   const   propValuePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020SetPeripheralProp(
        const   tommRoC_hw_devices_comm_rn4020_t*                       const   commPtr,
        const   tommRoC_hw_devices_comm_rn4020_peripheral_prop_enum_t           property,
        const   void*                                                   const   propValuePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020SendBufferPeripheral(
        const   tommRoC_hw_devices_comm_rn4020_t*   const   commPtr,
        const   uint8_t*                            const   characteristicUUIDPtr,
        const   uint8_t                                     characteristicUUIDLen,
        const   uint8_t                                     characteristicBufferSize,
        const   uint8_t*                            const   bufferPtr,
        const   uint16_t                                    bufferLen);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020ReceiveBufferPeripheral(
        const   tommRoC_hw_devices_comm_rn4020_t*   const   commPtr,
        const   uint32_t                                    waitTimeoutMsec,
                uint8_t*                            const   bufferPtr,
        const   uint16_t                                    bufferSize,
                uint16_t*                           const   receivedAmountPtr);


/******************* Central specific RN4020 functions */

/**
 * Start an RN4020 device as central
 *
 * NOTE: RN4020 is HW reset, factory reset, config and on exit it is set in HW/SW sleep.
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020StartAsCentral(
        const   tommRoC_hw_devices_comm_rn4020_cb_funct_t*              const   cbFunctPtr,
        const   tommRoC_hw_bus_t*                                       const   busHandlerPtr,
        const   tommRoC_guard_t*                                        const   guardPtr,
        const   tommRoC_hw_devices_comm_rn4020_central_config_t*        const   configPtr,
                tommRoC_hw_devices_comm_rn4020_t*                       const   commPtr);

/**
 * Start an RN4020 device as MLDP profile central
 *
 * NOTE: RN4020 is HW reset, factory reset, config and on exit it is set in HW/SW sleep.
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020StartAsMLDPCentral(
        const   tommRoC_hw_devices_comm_rn4020_cb_funct_t*              const   cbFunctPtr,
        const   tommRoC_hw_bus_t*                                       const   busHandlerPtr,
        const   tommRoC_guard_t*                                        const   guardPtr,
                tommRoC_hw_devices_comm_rn4020_t*                       const   commPtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020CentralCheck(
        const   tommRoC_hw_devices_comm_rn4020_t*                       const   commPtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020CentralConfigInit(
                tommRoC_hw_devices_comm_rn4020_central_config_t*        const   configPtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020GetCentralProp(
        const   tommRoC_hw_devices_comm_rn4020_t*                       const   commPtr,
        const   tommRoC_hw_devices_comm_rn4020_central_prop_enum_t              property,
                void*                                                   const   propValuePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020SetCentralProp(
        const   tommRoC_hw_devices_comm_rn4020_t*                       const   commPtr,
        const   tommRoC_hw_devices_comm_rn4020_central_prop_enum_t              property,
        const   void*                                                   const   propValuePtr);

//TODO: Recheck
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020SendBufferCentral(
        const   tommRoC_hw_devices_comm_rn4020_t*   const   commPtr,
        const   uint8_t*                            const   characteristicUUIDPtr,
        const   uint8_t                                     characteristicUUIDLen,
        const   uint8_t                                     characteristicBufferSize,
        const   uint8_t*                            const   bufferPtr,
        const   uint16_t                                    bufferLen);

//TODO: Recheck
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020ReceiveBufferCentral(
        const   tommRoC_hw_devices_comm_rn4020_t*   const   commPtr,
        const   uint8_t*                            const   characteristicUUIDPtr,
        const   uint8_t                                     characteristicUUIDLen,
        const   uint32_t                                    waitTimeoutMsec,
                uint8_t*                            const   bufferPtr,
        const   uint16_t                                    bufferSize,
                uint16_t*                           const   receivedAmountPtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020StartScanCentral(
        const   tommRoC_hw_devices_comm_rn4020_t*   const   commPtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020StopScanCentral(
        const   tommRoC_hw_devices_comm_rn4020_t*   const   commPtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020GetScanResultCentral(
        const   tommRoC_hw_devices_comm_rn4020_t*   const   commPtr,
                tommRoC_hw_comm_ble_scan_result_t*  const   scanResultPtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020ConnectToCentral(
        const   tommRoC_hw_devices_comm_rn4020_t*   const   commPtr,
        const   tommRoC_hw_comm_ble_mac_address_t*  const   macAddressPtr);

/******************* RN4020 low level common functions */

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020Sleep(
        const   tommRoC_hw_devices_comm_rn4020_t*   const   commPtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020Wake(
        const   tommRoC_hw_devices_comm_rn4020_t*   const   commPtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020IsConnected(
        const   tommRoC_hw_devices_comm_rn4020_t*   const   commPtr,
                bool*                                       isConnectedPtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommRN4020Disconnect(
        const   tommRoC_hw_devices_comm_rn4020_t*   const   commPtr);

#endif
