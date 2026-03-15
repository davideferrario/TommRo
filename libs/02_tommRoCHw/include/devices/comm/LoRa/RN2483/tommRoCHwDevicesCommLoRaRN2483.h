
#ifndef TOMMROC_HW_DEVICES_COMM_LORA_RN2483_H_
#define TOMMROC_HW_DEVICES_COMM_LORA_RN2483_H_

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

/*******************************************************************************
 * defines
 ******************************************************************************/

// Device data.
#define TOMMROC_HW_DEVICES_COMM_LORA_RN2483_DEVICE_DATA_SIZE    (   TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE     )

// __LORAWAN_DEVICE_APPEUI_SIZE_BYTE__ is the number of byte which form the AppEUI
#define __LORAWAN_DEVICE_APPEUI_SIZE_BYTE__     8

// __LORAWAN_DEVICE_DEVADDR_SIZE_BYTE__ is the number of byte which form the device address
#define __LORAWAN_DEVICE_DEVADDR_SIZE_BYTE__    4

// __LORAWAN_DEVICE_DEVEUI_SIZE_BYTE__ is the number of byte which form the devEUI
#define __LORAWAN_DEVICE_DEVEUI_SIZE_BYTE__     8

// __LORAWAN_DEVICE_APPKEY_SIZE_BYTE__ is the number of byte which form the appKey
#define __LORAWAN_DEVICE_APPKEY_SIZE_BYTE__     16

// number of availbale channels in RN2483 device
#define __RN2483_NUM_OF_CHANNLES__              16

// max payload size in the LoRaWAN payload admitted
#define __LORAWAN_PROTOCOL_MAX_PAYLOAD_SIZE__   51

// __LORAWAN_DEVICE_HWEUI_SIZE_BYTE__ is the number of byte which form the hweui
#define __LORAWAN_DEVICE_HWEUI_SIZE_BYTE__      8

/*******************************************************************************
 * typedefs
 ******************************************************************************/
typedef enum {

    /**
     *
     *
     * Available:
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_RESP_OFF = 0,

    /**
     *
     *
     * Available:
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_RESP_ON

} tommRoC_hw_devices_comm_lora_rn2483_resp_on_off_enum_t;

typedef enum {

    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_RESP_OK = 0,

    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_RESP_INVALID_PARAM

} tommRoC_hw_devices_comm_lora_rn2483_resp_result_enum_t;

typedef enum {

    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_JOIN_OTAA = 0,

    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_JOIN_ABP

} tommRoC_hw_devices_comm_lora_rn2483_join_mode_t;

typedef enum {

    // Response: this command may reply with two responses. The first response will be
    // received immediately after entering the command. In case the command is
    // valid (ok reply received) a second reply will be received after the end of the
    // join procedure

    // Response after entering the command:
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_JOIN_RESULT_OK = 0,
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_JOIN_RESULT_INVALID_PARAM,
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_JOIN_RESULT_KEYS_NOT_INIT,
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_JOIN_RESULT_NO_FREE_CH,
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_JOIN_RESULT_SILENT,
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_JOIN_RESULT_BUSY,
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_JOIN_RESULT_MAC_PAUSED,
    // TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_JOIN_RESULT_RESP_AFTER_ENTER_CMD_NUM is used to indicate
    // the max number of possible response received from RN2483 device after the entering command phase
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_JOIN_RESULT_RESP_AFTER_ENTER_CMD_NUM,

    // Response after the join procedure:
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_JOIN_RESULT_ACCEPTED,
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_JOIN_RESULT_DENIED

} tommRoC_hw_devices_comm_lora_rn2483_join_result_t;

typedef enum {

    // Response: this command may reply with two responses. The first response will be
    // received immediately after entering the command. In case the command is
    // valid (ok reply received), a second reply will be received after the end of the
    // uplink transmission

    // Response after entering the command:
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_TX_DATA_RESULT_OK = 0,
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_TX_DATA_RESULT_INVALID_PARAM,
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_TX_DATA_RESULT_NOT_JOINED,
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_TX_DATA_RESULT_NO_FREE_CH,
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_TX_DATA_RESULT_SILENT,
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_TX_DATA_RESULT_FRAME_COUNTER_ERR,
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_TX_DATA_RESULT_BUSY,
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_TX_DATA_RESULT_MAC_PAUSED,
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_TX_DATA_RESULT_INVALID_DATA_LEN_1,
    // TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_TX_DATA_RESULT_RESP_AFTER_ENTER_CMD_NUM is used to indicate
    // the max number of possible response received from RN2483 device after the entering command phase
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_TX_DATA_RESULT_RESP_AFTER_ENTER_CMD_NUM,

    // Response after the first uplink transmission attempt:
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_TX_DATA_RESULT_TX_DATA_OK,
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_TX_DATA_RESULT_MAC_RX,
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_TX_DATA_RESULT_INVALID_RESP_PAYLOAD_SIZE,
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_TX_DATA_RESULT_MAC_ERR,
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_TX_DATA_RESULT_INVALID_DATA_LEN_2

} tommRoC_hw_devices_comm_lora_rn2483_tx_data_result_t;

typedef enum {

    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_TX_CNF = 0,

    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_TX_UNCNF

} tommRoC_hw_devices_comm_lora_rn2483_tx_type_t;

typedef struct {

    uint32_t                                                frequencyValue;
    uint16_t                                                dutyCycleValue;
    uint8_t                                                 minDataRangeValue;
    uint8_t                                                 maxDataRangeValue;
    tommRoC_hw_devices_comm_lora_rn2483_resp_on_off_enum_t  status;
} _st_rn2483_mac_channel_param_t;

typedef struct {
    uint8_t     dataRateValue;
    uint32_t    frequencyValue;
} _st_rn2483_2nd_rx_window_param_t;

typedef struct {

    tommRoC_hw_devices_comm_lora_rn2483_tx_type_t           type;
    uint8_t                                                 portNo;
    uint8_t                                                 dataBuff[__LORAWAN_PROTOCOL_MAX_PAYLOAD_SIZE__];
    uint16_t                                                dataBuffSize;
} _st_rn2483_mac_tx_data_cmd_param_t;

typedef struct {

    tommRoC_hw_devices_comm_lora_rn2483_tx_data_result_t    result;
    uint8_t                                                 portNumber;
    uint8_t                                                 rxNumOfByte;
    uint8_t                                                 rxDataValueBuff[__LORAWAN_PROTOCOL_MAX_PAYLOAD_SIZE__];
} _st_rn2483_mac_tx_data_resp_param_t;

// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_COMM_LORA_RN2483_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_comm_lora_rn2483_device_data_t;

// Enumeration of RN2483 commands (sys, mac, radio)
typedef enum {

    /**
     *
     *  System commands
     *
     */

    /**
     * System command - sys sleep <length>
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_SYS_SLEEP_CMD,

    /**
     * System command - sys reset
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_SYS_RESET_CMD,

    /**
     * System command - sys eraseFW
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_SYS_ERASEFW_CMD,

    /**
     * System command - sys factoryRESET
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_SYS_FACTORYRESET_CMD,

    /**
     *
     *  LoRaWAN Protocol commands
     *
     */

    /**
     * LoRaWAN protocol command - mac reset <band>
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_LWAN_RESET_CMD,

    /**
     * LoRaWAN protocol command - mac tx <type> <portno> <data>
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_LWAN_TX_CMD,

    /**
     * LoRaWAN protocol command - mac join <mode>
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_LWAN_JOIN_CMD,

    /**
     * LoRaWAN protocol command - mac save
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_LWAN_SAVE_CMD,

    /**
     * LoRaWAN protocol command - mac forceENABLE
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_LWAN_FORCEENABLE_CMD,

    /**
     * LoRaWAN protocol command - mac pause
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_LWAN_PAUSE_CMD,

    /**
     * LoRaWAN protocol command - mac resume
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_LWAN_RESUME_CMD,

    /**
     *
     *  Radio commands
     *
     */

    /**
     * Radio command - radio rx <rxWindowSize>
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_RADIO_RX_CMD,

    /**
     * Radio command - radio tx <data>
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_RADIO_TX_CMD,

    /**
     * Radio command - radio cw <state>
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_RADIO_CW_CMD,

    /**
     * Radio command - rxstop
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_RXSTOP_CMD

} tommRoC_hw_devices_comm_lora_rn2483_command_enum_t;

// Enumeration of RN2483 get properties (mac get paramId <paramValue>)
typedef enum {


    /**
     *
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_ADR_GET_PROP,

    /**
     * Returns  the application identifier for the module. The application
     * identifier is a value given to the device by the network.
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_APPEUI_GET_PROP,

    /**
     *
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_AR_GET_PROP,

    /**
     *
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_CH_PARAM_GET_PROP,

    /**
     *
     *
     * Available:
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_CLASS_GET_PROP,

    /**
     *
     *
     * Available:
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_DCYCLEPS_GET_PROP,

    /**
     *
     *
     * Available:
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_DEVADDR_GET_PROP,

    /**
     * Returns the globally unique end-device identifier, as set in the module
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_DEVEUI_GET_PROP,

    /**
     *
     *
     * Available:
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_DNCTR_GET_PROP,

    /**
     *
     *
     * Available:
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_DR_GET_PROP,

    /**
     *
     *
     * Available:
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_GWNB_GET_PROP,

    /**
     *
     *
     * Available:
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_MCAST_GET_PROP,

    /**
     *
     *
     * Available:
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_MCASTDEVADDR_GET_PROP,

    /**
     *
     *
     * Available:
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_MCASTDNCTR_GET_PROP,

    /**
     *
     *
     * Available:
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_MRGN_GET_PROP,

    /**
     *
     *
     * Available:
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_PWRIDX_GET_PROP,

    /**
     *
     *
     * Available:
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_RETX_GET_PROP,

    /**
     *
     *
     * Available:
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_RX2_GET_PROP,

    /**
     *
     *
     * Available:
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_RXDELAY1_GET_PROP,

    /**
     *
     *
     * Available:
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_RXDELAY2_GET_PROP,

    /**
     *
     *
     * Available:
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_STATUS_GET_PROP,

    /**
     *
     *
     * Available:
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_SYNC_GET_PROP,

    /**
     *
     *
     * Available:
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_UPCTR_GET_PROP

} tommRoC_hw_devices_comm_lora_rn2483_get_prop_enum_t;

// Enumeration of RN2483 set properties (mac set paramId <paramValue>)
typedef enum {


    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_APPKEY_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_AR_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_APPSKEY_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_BAT_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_CLASS_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_DEVADDR_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_DEVEUI_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_DNCTR_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_DR_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_LINKCHK_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_MCAST_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_MCASTAPPSKEY_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_MCASTDEVADDR_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_MCASTDNCTR_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_MCASTNWKSKEY_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_NWKSKEY_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_PWRIDX_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_RETX_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_RX2_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_RXDELAY1_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_SYNC_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_UPCTR_SET_PROP,

    /**
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_APPEUI_SET_PROP

} tommRoC_hw_devices_comm_lora_rn2483_set_prop_enum_t;

// Enumeration of RN2483 get properties (sys get paramId <paramValue>)
typedef enum {

    /**
     *
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_SYS_VER_GET_PROP,

    /**
     *
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_SYS_HWEUI_GET_PROP

} tommRoC_hw_devices_comm_lora_rn2483_sys_get_prop_enum_t;

// Enumeration of RN2483 get properties (radio get paramId <paramValue>)
typedef enum {

    /**
     *
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_RADIO_PWR_GET_PROP,

    /**
     *
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_RADIO_RSSI_GET_PROP,

    /**
     *
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_COMM_LORA_RN2483_RADIO_SNR_GET_PROP

} tommRoC_hw_devices_comm_lora_rn2483_radio_get_prop_enum_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLoRaRN2483InitUART(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLoRaRN2483AttachDeviceData(
        const   tommRoC_hw_devices_comm_lora_rn2483_device_data_t*  const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        enterReset              enter in reset function pointer.
 * param[in]        exitReset               exit from reset function pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLoRaRN2483Start(
        const   tommRoC_hw_gpio_set_cb_t                                    enterReset,
        const   tommRoC_hw_gpio_set_cb_t                                    exitReset,
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 *
 *
 * param[in]
 * param[in]
 * param[in]
 *
 * return tommRoC_hw_err_enum_t
 */

tommRoC_hw_err_enum_t tommRoCHwDevicesCommLoRaRN2483Commands(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   tommRoC_hw_devices_comm_lora_rn2483_command_enum_t              commandProperty,
        const   void*                                                   const   commandParamInPtr,
                void*                                                   const   commandResponsePtr);

/* tommRoCHwDevicesCommLoRaRN2483LoraWanPropGet */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommLoRaRN2483LoraWanPropGet(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   tommRoC_hw_devices_comm_lora_rn2483_get_prop_enum_t             loraWanGetProperty,
        const   void*                                                   const   loraWanGetParamInPtr,
                void*                                                   const   loraWanGetResponsePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommLoRaRN2483LoraWanPropSet(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   tommRoC_hw_devices_comm_lora_rn2483_set_prop_enum_t             loraWanGetProperty,
        const   void*                                                   const   loraWanSetParamInPtr,
                void*                                                   const   loraWanSetResponsePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommLoRaRN2483SystemPropGet(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   tommRoC_hw_devices_comm_lora_rn2483_sys_get_prop_enum_t         systemGetProperty,
        const   void*                                                   const   systemGetParamInPtr,
                void*                                                   const   systemGetResponsePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommLoRaRN2483RadioPropGet(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
        const   tommRoC_hw_devices_comm_lora_rn2483_radio_get_prop_enum_t           radioGetProperty,
        const   void*                                                       const   radioGetParamInPtr,
                void*                                                       const   radioGetResponsePtr);

#endif
