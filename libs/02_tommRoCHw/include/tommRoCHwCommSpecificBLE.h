
#ifndef TOMMROC_HW_COMM_SPECIFIC_BLE_H_
#define TOMMROC_HW_COMM_SPECIFIC_BLE_H_

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
#include "tommRoCHwErr.h"

#include "TOMMROC.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// BLE MAC address size [byte].
#define TOMMROC_HW_COMM_BLE_MAC_ADDRESS_SIZE_BYTE                       (6)

// BLE charateristic max size [byte].
#define TOMMROC_HW_COMM_BLE_CHARACTERISTIC_MAX_SIZE_BYTE                (20)

// BLE device name max length [byte].
#define TOMMROC_HW_COMM_BLE_NAME_MAX_LENGTH                             (20)

// BLE custom ADV payload max length [byte].
// TODO: check length (why not 10???)
#define TOMMROC_HW_COMM_BLE_CUSTOM_ADV_ELEM_MAX_LENGTH                  (20)
//#define TOMMROC_HW_COMM_BLE_CUSTOM_ADV_PAYLOAD_MAX_LENGTH                  (20)

#define TOMMROC_HW_COMM_BLE_UUID_16_BIT_BIT_SIZE                        (16)
#define TOMMROC_HW_COMM_BLE_UUID_16_BIT_BYTE_SIZE                       (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(TOMMROC_HW_COMM_BLE_UUID_16_BIT_BIT_SIZE))

#define TOMMROC_HW_COMM_BLE_UUID_32_BIT_BIT_SIZE                        (32)
#define TOMMROC_HW_COMM_BLE_UUID_32_BIT_BYTE_SIZE                       (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(TOMMROC_HW_COMM_BLE_UUID_32_BIT_BIT_SIZE))

#define TOMMROC_HW_COMM_BLE_UUID_128_BIT_BIT_SIZE                       (128)
#define TOMMROC_HW_COMM_BLE_UUID_128_BIT_BYTE_SIZE                      (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(TOMMROC_HW_COMM_BLE_UUID_128_BIT_BIT_SIZE))

#define TOMMROC_HW_COMM_BLE_PUBLIC_SERVICE_UUID_BIT_LENGTH              (TOMMROC_HW_COMM_BLE_UUID_16_BIT_BIT_SIZE)
#define TOMMROC_HW_COMM_BLE_PUBLIC_SERVICE_UUID_BYTE_LENGTH             (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(TOMMROC_HW_COMM_BLE_PUBLIC_SERVICE_UUID_BIT_LENGTH))

#define TOMMROC_HW_COMM_BLE_PRIVATE_SERVICE_UUID_BIT_LENGTH             (TOMMROC_HW_COMM_BLE_UUID_128_BIT_BIT_SIZE)
#define TOMMROC_HW_COMM_BLE_PRIVATE_SERVICE_UUID_BYTE_LENGTH            (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(TOMMROC_HW_COMM_BLE_PRIVATE_SERVICE_UUID_BIT_LENGTH))

#define TOMMROC_HW_COMM_BLE_PRIVATE_CHARACTERISTIC_UUID_BIT_LENGTH      (TOMMROC_HW_COMM_BLE_UUID_128_BIT_BIT_SIZE)
#define TOMMROC_HW_COMM_BLE_PRIVATE_CHARACTERISTIC_UUID_BYTE_LENGTH     (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(TOMMROC_HW_COMM_BLE_PRIVATE_CHARACTERISTIC_UUID_BIT_LENGTH))

// The accessibility of each BLE characteristic is defined by the 8-bit characteristic property in bitmap format
#define TOMMROC_HW_COMM_BLE_CHARACTERISTC_EXTENDED_PROPERTY             (0b10000000)    // Additional property available.
#define TOMMROC_HW_COMM_BLE_CHARACTERISTC_AUTH_WRITE                    (0b01000000)    // Write characteristic with authentication from client to server.
#define TOMMROC_HW_COMM_BLE_CHARACTERISTC_INDICATE                      (0b00100000)    // Indicate value of characteristic with acknowledgment from server to client.
#define TOMMROC_HW_COMM_BLE_CHARACTERISTC_NOTIFY                        (0b00010000)    // Notify value of characteristic without acknowledgment from server to client.
#define TOMMROC_HW_COMM_BLE_CHARACTERISTC_WRITE                         (0b00001000)    // Write value of characteristic with acknowledgment from client to server.
#define TOMMROC_HW_COMM_BLE_CHARACTERISTC_WRITE_WITHOUT_RESPONSE        (0b00000100)    // Write value of characteristic without acknowledgment from client to server.
#define TOMMROC_HW_COMM_BLE_CHARACTERISTC_READ                          (0b00000010)    // Read value of characteristic. Value is sent from server to client.
#define TOMMROC_HW_COMM_BLE_CHARACTERISTC_BROADCAST                     (0b00000001)    // Broadcast value of characteristic.

// BLE device connection parameters limits.
#define TOMMROC_HW_COMM_BLE_CONNECTION_PARAMETERS_INTERVAL_MIN          (0x0006)
#define TOMMROC_HW_COMM_BLE_CONNECTION_PARAMETERS_INTERVAL_MAX          (0x0C80)

#define TOMMROC_HW_COMM_BLE_CONNECTION_PARAMETERS_LATENCY_MIN           (0x0000)
#define TOMMROC_HW_COMM_BLE_CONNECTION_PARAMETERS_LATENCY_MAX           (0x01F3)

#define TOMMROC_HW_COMM_BLE_CONNECTION_PARAMETERS_TIMEOUT_MIN           (0x000A)
#define TOMMROC_HW_COMM_BLE_CONNECTION_PARAMETERS_TIMEOUT_MAX           (0x0C80)

// BLE stop advertising (to use in "set adv" interval param)
#define TOMMROC_HW_COMM_BLE_STOP_ADVERTISING                            (0)


/**
 * BLE ADV payload elements types.
 */
#define BLE_ADV_FLAGS_TYPE_ID                                           (0x01)
#define BLE_ADV_INCOMPLETE_LIST_16_BIT_UUID_TYPE_ID                     (0x02)
#define BLE_ADV_COMPLETE_LIST_16_BIT_UUID_TYPE_ID                       (0x03)
#define BLE_ADV_INCOMPLETE_LIST_32_BIT_UUID_TYPE_ID                     (0x04)
#define BLE_ADV_COMPLETE_LIST_32_BIT_UUID_TYPE_ID                       (0x05)
#define BLE_ADV_INCOMPLETE_LIST_128_BIT_UUID_TYPE_ID                    (0x06)
#define BLE_ADV_COMPLETE_LIST_128_BIT_UUID_TYPE_ID                      (0x07)
#define BLE_ADV_SHORT_LOCAL_NAME_TYPE_ID                                (0x08)
#define BLE_ADV_COMPLETE_LOCAL_NAME_TYPE_ID                             (0x09)
#define BLE_ADV_TX_POWER_LEVEL_TYPE_ID                                  (0x0A)
#define BLE_ADV_CLASS_OF_DEVICE_TYPE_ID                                 (0x0D)
#define BLE_ADV_SIMPLE_PAIRING_HASH_TYPE_ID                             (0x0E)
#define BLE_ADV_SIMPLE_PAIRING_RANDOMIZER_TYPE_ID                       (0x0F)
#define BLE_ADV_TK_VALUE_TYPE_ID                                        (0x10)
#define BLE_ADV_SECURITY_OOB_FLAG_TYPE_ID                               (0x11)
#define BLE_ADV_SLAVE_CONNECTION_INTERVAL_RANGE_TYPE_ID                 (0x12)
#define BLE_ADV_LIST_16_BIT_SERVICE_TYPE_ID                             (0x14)
#define BLE_ADV_LIST_128_BIT_SERVICE_TYPE_ID                            (0x15)
#define BLE_ADV_SERVICE_DATA_TYPE_ID                                    (0x16)
#define BLE_ADV_MANUFACTURE_SPECIFIC_DATA_TYPE_ID                       (0xFF)

/*******************************************************************************
 * typedefs
 ******************************************************************************/


// BLE device module role enumeration.
typedef enum {

    /**
     * In Peripheral mode, the BLE module is permitted to broadcast advertising packets and be connectable.
     */
    TOMMRO_C_HW_COMM_BLE_ROLE_PERIPHERAL = 0,

    /**
     * In Central mode, the BLE module can scan for advertisements and connect to a peripheral.
     */
    TOMMRO_C_HW_COMM_BLE_ROLE_CENTRAL,

    /**
     * BLE device not init.
     */
    TOMMRO_C_HW_COMM_BLE_ROLE_NOT_INIT,

} tommRoC_hw_comm_ble_role_enum_t;


// BLE MAC address code.
typedef uint8_t tommRoC_hw_comm_ble_mac_address_code_t[TOMMROC_HW_COMM_BLE_MAC_ADDRESS_SIZE_BYTE];
#define __EMPTY_tommRoC_hw_comm_ble_mac_address_code_t__    { 0 }

// BLE MAC address type.
typedef enum {

    /**
     * Public (static) MAC address.
     */
    TOMMRO_C_HW_COMM_BLE_MAC_ADDRESS_PUBLIC = 0,

    /**
     * Random MAC address.
     */
    TOMMRO_C_HW_COMM_BLE_MAC_ADDRESS_RANDOM,

} tommRoC_hw_comm_ble_mac_address_type_enum_t;


// BLE name.
typedef char tommRoC_hw_comm_ble_name_t[TOMMROC_HW_COMM_BLE_NAME_MAX_LENGTH + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE];
#define __EMPTY_tommRoC_hw_comm_ble_name_t__                { TOMMROC_STRING_NULL_TERMINATOR_CHAR }


// BLE device TX power enumeration.
typedef enum {

    TOMMRO_C_HW_COMM_BLE_TX_POWER_0 = 0,
    TOMMRO_C_HW_COMM_BLE_TX_POWER_1,
    TOMMRO_C_HW_COMM_BLE_TX_POWER_2,
    TOMMRO_C_HW_COMM_BLE_TX_POWER_3,
    TOMMRO_C_HW_COMM_BLE_TX_POWER_4,
    TOMMRO_C_HW_COMM_BLE_TX_POWER_5,
    TOMMRO_C_HW_COMM_BLE_TX_POWER_6,
    TOMMRO_C_HW_COMM_BLE_TX_POWER_7,

    TOMMRO_C_HW_COMM_BLE_TX_POWER_DEFAULT   = TOMMRO_C_HW_COMM_BLE_TX_POWER_4,
    TOMMRO_C_HW_COMM_BLE_TX_POWER_MINIMUM   = TOMMRO_C_HW_COMM_BLE_TX_POWER_0,
    TOMMRO_C_HW_COMM_BLE_TX_POWER_MAXIMUM   = TOMMRO_C_HW_COMM_BLE_TX_POWER_7,

} tommRoC_hw_comm_ble_tx_power_level_enum_t;


// BLE UUID length enumeration.
typedef enum {

    TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_16_BIT = 0,
    TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_32_BIT,
    TOMMRO_C_HW_COMM_BLE_UUID_LEN_TYPE_128_BIT,

} tommRoC_hw_comm_ble_uuid_len_type_enum_t;


// BLE custom advertisement element.
typedef struct {

    /**
     * BLE custom advertisement type.
     */
    uint8_t     advType;

    /**
     * BLE custom advertisement data.
     */
    uint8_t*    advData;

    /**
     * BLE custom advertisement data length [max TOMMROC_HW_COMM_BLE_CUSTOM_ADV_ELEM_MAX_LENGTH byte].
     */
    uint8_t     advDataLength;

} tommRoC_hw_comm_ble_custom_adv_t;

#define __EMPTY_tommRoC_hw_comm_ble_custom_adv_t__          \
{                                                           \
    /* .advType */          0,                              \
    /* .advData */          NULL,                           \
    /* .advDataLength */    0,                              \
}

// BLE custom advertisement payload.
typedef struct {

    /**
     * BLE custom advertisement elements pointer.
     */
    tommRoC_hw_comm_ble_custom_adv_t*   advElementsPtr;

    /**
     * BLE custom advertisement elements amount.
     */
    uint8_t                             advElementsAmount;

} tommRoC_hw_comm_ble_custom_adv_payload_t;

#define __EMPTY_tommRoC_hw_comm_ble_custom_adv_payload_t__  \
{                                                           \
    /* .advElementsPtr */       NULL,                       \
    /* .advElementsAmount */    0,                          \
}


// BLE device module common properties enumeration.
typedef enum {

    /**
     * BLE device name property.
     *
     * Available:   set for peripheral devices.
     * Notes:       propValuePtr has to be char* of max size [TOMMROC_HW_COMM_BLE_NAME_MAX_LENGTH + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE].
     */
    TOMMRO_C_HW_COMM_BLE_NAME_PROP = 0,

    /**
     * BLE MAC address property.
     *
     * Available:   get/set.
     * Notes:       propValuePtr has to be tommRoC_hw_comm_ble_mac_address_t*.
     */
    TOMMRO_C_HW_COMM_BLE_MAC_ADDRESS_PROP,

    /**
     * BLE advertising interval [msec].
     *
     * Available:   set for peripheral devices.
     * Notes:       propValuePtr has to be uint16_t*.
     */
    TOMMRO_C_HW_COMM_BLE_ADV_INTERVAL_PROP,

    /**
     * BLE custom advertisement payload.
     *
     * Available:   set for peripheral devices.
     * Notes:       propValuePtr has to be tommRoC_hw_comm_ble_custom_adv_payload_t*.
     */
    TOMMRO_C_HW_COMM_BLE_CUSTOM_ADV_PAYLOAD_PROP,

} tommRoC_hw_comm_ble_prop_enum_t;


// BLE device characteristic.
typedef struct {

    /**
     * Private characteristic UUID [128 bit].
     */
    uint8_t     privateCharacteristicUUID[TOMMROC_HW_COMM_BLE_PRIVATE_CHARACTERISTIC_UUID_BYTE_LENGTH];

    /**
     * Property bitmap of the characteristic (has to be a bitmap of TOMMROC_HW_COMM_BLE_CHARACTERISTC bitmask).
     */
    uint8_t     property;

    /**
     * Maximum data size in bytes that the characteristic holds.
     */
    uint8_t     maxDataSize;

} tommRoC_hw_comm_ble_characteristic_t;

#define __EMPTY_tommRoC_hw_comm_ble_characteristic_t__      \
{                                                           \
    /* .privateCharacteristicUUID */    { 0 },              \
    /* .property */                     0,                  \
    /* .maxDataSize */                  0,                  \
}

// BLE device private service.
typedef struct {

    /**
     * Private service UUID [128 bit].
     */
    uint8_t                                 privateServiceUUID[TOMMROC_HW_COMM_BLE_PRIVATE_SERVICE_UUID_BYTE_LENGTH];

    /**
     * Characteristics array pointer.
     */
    tommRoC_hw_comm_ble_characteristic_t*   characteristicArrayPtr;

    /**
     * Characteristics array element amount.
     */
    uint8_t                                 characteristicAmount;

} tommRoC_hw_comm_ble_private_service_t;

#define __EMPTY_tommRoC_hw_comm_ble_private_service_t__     \
{                                                           \
    /* .privateServiceUUID */       { 0 },                  \
    /* .characteristicArrayPtr */   NULL,                   \
    /* .characteristicAmount */     0,                      \
}


// BLE MAC address.
typedef struct {

    /**
     * BLE MAC address code.
     */
    tommRoC_hw_comm_ble_mac_address_code_t      addressCode;

    /**
     * BLE MAC address type.
     */
    tommRoC_hw_comm_ble_mac_address_type_enum_t addressType;

} tommRoC_hw_comm_ble_mac_address_t;

#define __EMPTY_tommRoC_hw_comm_ble_mac_address_t__                         \
{                                                                           \
    /* .addressCode */  __EMPTY_tommRoC_hw_comm_ble_mac_address_code_t__,   \
    /* .addressType */  TOMMRO_C_HW_COMM_BLE_MAC_ADDRESS_PUBLIC,            \
}


// BLE scan result.
typedef struct {

    /**
     * BLE MAC address.
     */
    tommRoC_hw_comm_ble_mac_address_t           macAddress;

    /**
     * BLE name.
     */
    tommRoC_hw_comm_ble_name_t                  name;

    /**
     * BLE rssi level.
     */
    int8_t                                      rssi;

} tommRoC_hw_comm_ble_scan_result_t;

#define __EMPTY_tommRoC_hw_comm_ble_scan_result_t__                         \
{                                                                           \
    /* .macAddress */       __EMPTY_tommRoC_hw_comm_ble_mac_address_t__,    \
    /* .name */             __EMPTY_tommRoC_hw_comm_ble_name_t__,           \
    /* .rssi */             -1,                                             \
}


/*******************************************************************************
 * functions
 ******************************************************************************/


/******************* BLE custom ADV payload functs */

/**
 * BLE custom advertisement element init.
 */
tommRoC_hw_err_enum_t tommRoCHwCommBLECustomADVElemInit(
        const   uint8_t                                     advType,
        const   uint8_t*                            const   advData,
        const   uint8_t                                     advDataLength,
                tommRoC_hw_comm_ble_custom_adv_t*   const   advElemPtr);

/**
 * BLE custom advertisement element check.
 */
tommRoC_hw_err_enum_t tommRoCHwCommBLECustomADVElemCheck(
        const   tommRoC_hw_comm_ble_custom_adv_t*   const   advElemPtr);

/**
 * BLE custom advertisement payload init.
 */
tommRoC_hw_err_enum_t tommRoCHwCommBLECustomADVPAyloadInit(
        const   tommRoC_hw_comm_ble_custom_adv_t*           const   advElementsPtr,
        const   uint8_t                                             advElementsAmount,
                tommRoC_hw_comm_ble_custom_adv_payload_t*   const   advPayloadPtr);

/**
 * BLE custom advertisement payload check.
 */
tommRoC_hw_err_enum_t tommRoCHwCommBLECustomADVPayloadCheck(
        const   tommRoC_hw_comm_ble_custom_adv_payload_t*   const   advPayloadPtr);


/******************* BLE characteristic functs */

/**
 * BLE characteristic struct init.
 */
tommRoC_hw_err_enum_t tommRoCHwCommBLECharacteristicInit(
        const   uint8_t*                                const   uuidPtr,
        const   uint8_t                                         property,
        const   uint8_t                                         maxDataSize,
                tommRoC_hw_comm_ble_characteristic_t*   const   characteristicPtr);

/**
 * BLE generic UUID characteristic check.
 */
tommRoC_hw_err_enum_t tommRoCHwCommBLECharacteristicUUIDCheck(
        const   uint8_t*                                const   characteristicUUIDPtr,
        const   uint8_t                                         characteristicUUIDLen);

/**
 * BLE public UUID characteristic check.
 */
tommRoC_hw_err_enum_t tommRoCHwCommBLEPublicCharacteristicUUIDCheck(
        const   uint8_t*                                const   characteristicUUIDPtr,
        const   uint8_t                                         characteristicUUIDLen);

/**
 * BLE private UUID characteristic check.
 */
tommRoC_hw_err_enum_t tommRoCHwCommBLEPrivateCharacteristicUUIDCheck(
        const   uint8_t*                                const   characteristicUUIDPtr,
        const   uint8_t                                         characteristicUUIDLen);

/**
 * BLE characteristic check.
 */
tommRoC_hw_err_enum_t tommRoCHwCommBLECharacteristicCheck(
        const   tommRoC_hw_comm_ble_characteristic_t*   const   characteristicPtr);


/******************* BLE private service functs */

/**
 * BLE private service struct init.
 */
tommRoC_hw_err_enum_t tommRoCHwCommBLEPrivateServiceInit(
        const   uint8_t*                                const   uuidPtr,
        const   tommRoC_hw_comm_ble_characteristic_t*   const   characteristicArrayPtr,
        const   uint8_t                                         characteristicAmount,
                tommRoC_hw_comm_ble_private_service_t*  const   servicePtr);

/**
 * BLE private servic check.
 */
tommRoC_hw_err_enum_t tommRoCHwCommBLEPrivateServiceCheck(
        const   tommRoC_hw_comm_ble_private_service_t*  const   servicePtr);

#endif
