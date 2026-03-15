/****************************************************************************
*
* This file is for iBeacon APIs. It supports both iBeacon encode and decode.
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
#include "esp_ibeacon_api.h"


/* For iBeacon packet format, please refer to Apple "Proximity Beacon Specification" doc */
/* Constant part of iBeacon data */
esp_ble_ibeacon_head_t ibeacon_common_head_1 = {
    .flags = {0x02, 0x01, 0x06},
    .length = 0x1A,
    .type = 0xFF,
    .company_id = 0x004C,
    .beacon_type = 0x1502
};

esp_ble_ibeacon_head_t ibeacon_common_head_2 = {
    .flags = {0x02, 0x01, 0x1A},
    .length = 0x1A,
    .type = 0xFF,
    .company_id = 0x004C,
    .beacon_type = 0x1502
};

/* Vendor part of iBeacon data*/
esp_ble_ibeacon_vendor_t vendor_config = {
    .proximity_uuid = ESP_UUID,
    .major = ENDIAN_CHANGE_U16(ESP_MAJOR), //Major=ESP_MAJOR
    .minor = ENDIAN_CHANGE_U16(ESP_MINOR), //Minor=ESP_MINOR
    .measured_power = 0xC5
};

bool esp_ble_is_ibeacon_packet(uint8_t *adv_data, uint8_t adv_data_len) {
    bool result = false;

    if ((adv_data != NULL) && (adv_data_len == 0x1E)){
        if (TOMMRO_C_ERR_SUCCESS == tommRoCUtilMemCompare(adv_data, (uint8_t*)&ibeacon_common_head_1, sizeof(ibeacon_common_head_1))){
            result = true;
        }
        else if (TOMMRO_C_ERR_SUCCESS == tommRoCUtilMemCompare(adv_data, (uint8_t*)&ibeacon_common_head_2, sizeof(ibeacon_common_head_2))){
            result = true;
        }
    }

    return result;
}

#endif

#endif
