
#ifndef ESP_IBEACON_API_ENV_ESP32_BLUE_DROID_H_
#define ESP_IBEACON_API_ENV_ESP32_BLUE_DROID_H_

/*
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/



/****************************************************************************
*
* This file is for iBeacon definitions. It supports both iBeacon sender and receiver
* which is distinguished by macros IBEACON_SENDER and IBEACON_RECEIVER,
*
* iBeacon is a trademark of Apple Inc. Before building devices which use iBeacon technology,
* visit https://developer.apple.com/ibeacon/ to obtain a license.
*
****************************************************************************/

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)

#include "sdkconfig.h"

#if !defined (__TOMMROC_HW_DISABLE_BLE_TEMPLATE__) && !defined (CONFIG_EXAMPLE_PROV_TRANSPORT_BLE) && defined (CONFIG_BT_ENABLED) && defined (CONFIG_BT_BLUEDROID_ENABLED)

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "esp_gap_ble_api.h"
#include "esp_gattc_api.h"


/* Because current ESP IDF version doesn't support scan and adv simultaneously,
 * so iBeacon sender and receiver should not run simultaneously */
#define IBEACON_SENDER      0
#define IBEACON_RECEIVER    1
#define IBEACON_MODE CONFIG_IBEACON_MODE

/* Major and Minor part are stored in big endian mode in iBeacon packet,
 * need to use this macro to transfer while creating or processing
 * iBeacon data */
#define ENDIAN_CHANGE_U16(x) ((((x)&0xFF00)>>8) + (((x)&0xFF)<<8))

/* Espressif WeChat official account can be found using WeChat "Yao Yi Yao Zhou Bian",
 * if device advertises using ESP defined UUID.
 * Please refer to http://zb.weixin.qq.com for further information. */
#define ESP_UUID    {0xFD, 0xA5, 0x06, 0x93, 0xA4, 0xE2, 0x4F, 0xB1, 0xAF, 0xCF, 0xC6, 0xEB, 0x07, 0x64, 0x78, 0x25}
#define ESP_MAJOR   10167
#define ESP_MINOR   61958


TOMMRO_C_UTIL_PACKED_PRE typedef struct TOMMRO_C_UTIL_PACKED_POST {
    uint8_t flags[3];
    uint8_t length;
    uint8_t type;
    uint16_t company_id;
    uint16_t beacon_type;
} esp_ble_ibeacon_head_t;

TOMMRO_C_UTIL_PACKED_PRE typedef struct TOMMRO_C_UTIL_PACKED_POST {
    uint8_t proximity_uuid[16];
    uint16_t major;
    uint16_t minor;
    int8_t measured_power;
} esp_ble_ibeacon_vendor_t;


TOMMRO_C_UTIL_PACKED_PRE typedef struct TOMMRO_C_UTIL_PACKED_POST {
    esp_ble_ibeacon_head_t ibeacon_head;
    esp_ble_ibeacon_vendor_t ibeacon_vendor;
} esp_ble_ibeacon_t;


/* For iBeacon packet format, please refer to Apple "Proximity Beacon Specification" doc */
/* Constant part of iBeacon data */
extern esp_ble_ibeacon_head_t ibeacon_common_head;

bool esp_ble_is_ibeacon_packet(uint8_t *adv_data, uint8_t adv_data_len);

#endif

#endif

#endif
