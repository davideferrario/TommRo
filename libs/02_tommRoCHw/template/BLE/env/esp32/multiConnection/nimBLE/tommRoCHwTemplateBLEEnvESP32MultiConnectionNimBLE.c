
/**
 * NOTE:
 * - In case of BLE peripheral, application must implement "gatt_svr.c" and "gatt_svr.h" files into "nimBLE" folder.
 * - In case of BLE central, application must implement "gatt_cent.c" and "gatt_cent.h" files into "nimBLE" folder.
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBLEMulti.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)

#include "sdkconfig.h"

#include "env/tommRoCTemplateEnv.h"

#if !defined (__TOMMROC_HW_DISABLE_BLE_TEMPLATE__) && !defined (CONFIG_EXAMPLE_PROV_TRANSPORT_BLE) && defined (CONFIG_BT_ENABLED) && defined (CONFIG_BT_NIMBLE_ENABLED)
#if defined (CONFIG_BT_NIMBLE_MAX_CONNECTIONS) && (CONFIG_BT_NIMBLE_MAX_CONNECTIONS > 1)
#include "BLE/env/esp32/multiConnection/nimBLE/connHandleMTUValue/tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValue.h"

#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
#include "esp_nimble_hci.h"
#endif

#include "host/ble_hs.h"
#include "host/ble_uuid.h"
#include "host/util/util.h"
#include "services/gap/ble_svc_gap.h"

#if defined (CONFIG_BT_NIMBLE_ROLE_CENTRAL)
#include "blecent.h"
#endif

#if MYNEWT_VAL(BLE_GATT_CACHING)
#include "host/ble_esp_gattc_cache.h"
#endif

#if defined (CONFIG_BT_NIMBLE_ROLE_PERIPHERAL)
#include "nimBLE/gatt_svr.h"
#endif

#if defined (CONFIG_BT_NIMBLE_ROLE_CENTRAL)
#include "nimBLE/gatt_cent.h"
//https://github.com/espressif/esp-idf/blob/master/examples/bluetooth/nimble/blecent/main/main.c
#endif

#include "esp_bt.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __WRITE_DELAY_FOR_EVERY_BYTE_uSEC__ (250)

// NOTE: copied by NXP BLE stack
#define __G_ATT_OPCODE_SIZE__               (1U)
#define __G_ATT_HANDLE_SIZE__               (2U)

#if defined (CONFIG_BT_NIMBLE_ROLE_PERIPHERAL)
#define __WAIT_FOR_NIMBLE_STARTED_mSEC__    (500)
#endif

#if defined (CONFIG_BT_NIMBLE_ROLE_CENTRAL)
#define __WAIT_FOR_NIMBLE_STARTED_mSEC__    (500)
#endif

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
TOMMROC_SCTA_EQUALS(TOMMROC_HW_COMM_BLE_MAC_ADDRESS_SIZE_BYTE, sizeof(((ble_addr_t*)NULL)->val));

#if defined (CONFIG_BT_NIMBLE_ROLE_PERIPHERAL)
#if defined (NIM_BLE_GATT_SVR_ADV_ADD_UUIDS_16_TO_ADV)
extern ble_uuid16_t* _nimble_adv_uuids16_ptr;
extern uint8_t _nimble_adv_uuids16_num;
#endif

#if defined (NIM_BLE_GATT_SVR_ADV_ADD_UUIDS_32_TO_ADV)
extern ble_uuid32_t* _nimble_adv_uuids32_ptr;
extern uint8_t _nimble_adv_uuids32_num;
#endif

#if defined (NIM_BLE_GATT_SVR_ADV_ADD_UUIDS_128_TO_ADV)
extern ble_uuid128_t* _nimble_adv_uuids128_ptr;
extern uint8_t _nimble_adv_uuids128_num;
#endif

#if defined (NIM_BLE_GATT_SVR_ADV_ADD_MANUF_SPECIFIC_DATA_TO_ADV)
extern uint8_t* _nimble_adv_manuf_spefific_data_ptr;
extern uint8_t _nimble_adv_manuf_spefific_data_len;
#endif


#if defined (NIM_BLE_GATT_SVR_ADV_ADD_UUIDS_16_TO_ADV_RSP)
extern ble_uuid16_t* _nimble_adv_rsp_uuids16_ptr;
extern uint8_t _nimble_adv_rsp_uuids16_num;
#endif

#if defined (NIM_BLE_GATT_SVR_ADV_ADD_UUIDS_32_TO_ADV_RSP)
extern ble_uuid32_t* _nimble_adv_rsp_uuids32_ptr;
extern uint8_t _nimble_adv_rsp_uuids32_num;
#endif

#if defined (NIM_BLE_GATT_SVR_ADV_ADD_UUIDS_128_TO_ADV_RSP)
extern ble_uuid128_t* _nimble_adv_rsp_uuids128_ptr;
extern uint8_t _nimble_adv_rsp_uuids128_num;
#endif

#if defined (NIM_BLE_GATT_SVR_ADV_ADD_MANUF_SPECIFIC_DATA_TO_ADV_RSP)
extern uint8_t* _nimble_adv_rsp_manuf_spefific_data_ptr;
extern uint8_t _nimble_adv_rsp_manuf_spefific_data_len;
#endif

#if defined (NIM_BLE_GATT_SVR_ADV_ITVL_MIN)
extern uint16_t _nimble_adv_itvl_min;
#endif
#if defined (NIM_BLE_GATT_SVR_ADV_ITVL_MAX)
extern uint16_t _nimble_adv_itvl_max;
#endif
#endif

// NOTE: this is defined externally
void ble_store_config_init(void);

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_DEBUG_ENABLE__)
static const char __DEBUG_OBJ_ID__[] = "hwTempBLENimBLE";
#endif

static const tommRoC_hw_template_ble_multi_def_conn_handler_t _template_ble_multi_conn_handler_empty = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_hw_template_ble_multi_def_conn_handler_t);

#if defined (CONFIG_BT_NIMBLE_ROLE_PERIPHERAL)
static tommRoC_hw_template_ble_multi_def_on_connect_funct_t _on_connect_cb = NULL;
#endif
static tommRoC_hw_template_ble_multi_def_on_disconnect_funct_t _on_disconnect_cb = NULL;
static tommRoC_hw_template_ble_multi_def_on_receive_funct_t _on_receive_cb = NULL;

#if defined (CONFIG_BT_NIMBLE_ROLE_PERIPHERAL)
static char _device_ble_name_str[MYNEWT_VAL(BLE_SVC_GAP_DEVICE_NAME_MAX_LENGTH) + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE];

static int bleprph_gap_event(struct ble_gap_event *event, void *arg);
#endif

#if defined (CONFIG_BT_NIMBLE_ROLE_CENTRAL)
static tommRoC_hw_template_ble_central_generic_scan_funct_t     _generic_scan_funct_ptr     = NULL;
static tommRoC_hw_template_ble_central_ibeacon_scan_funct_t     _ibeacon_scan_funct_ptr     = NULL;
static tommRoC_hw_template_ble_central_scan_completed_funct_t   _scan_completed_funct_ptr   = NULL;

static bool _connecting = false;
static bool _connected  = false;
static bool _writing = false;

static int blecent_gap_event(struct ble_gap_event *event, void *arg);
#endif

static bool _nimble_started = false;

static uint8_t _own_addr_type;

/*******************************************************************************
 * local functions
 ******************************************************************************/

static bool _is_connected(const int32_t connHandle) {
    return (TOMMROC_HW_TEMPLATE_BLE_ENV_ESP32_MULTI_CONNECTION_NIM_BLE_CONN_HANDLE_MTU_VALUE_CONN_HANDLE_NOT_CONNECTED_VALUE != connHandle);
}

#if defined (CONFIG_BT_NIMBLE_ROLE_PERIPHERAL)
int scli_receive_key(int *console_key) {
    TOMMROC_UTIL_UNUSED_PARAM(console_key);
    return 0;
}

static void bleprph_advertise(void) {

    struct ble_gap_adv_params adv_params;
    struct ble_hs_adv_fields fields;
    const char *name;
    int rc;

    /**
     *  Set the advertisement data included in our advertisements:
     *     o Flags (indicates advertisement type and other general info).
     *     o Advertising tx power.
     *     o Device name.
     *     o 16-bit service UUIDs (alert notifications).
     */

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&fields, 0, sizeof(fields)));

    /* Advertise two flags:
     *     o Discoverability in forthcoming advertisement (general)
     *     o BLE-only (BR/EDR unsupported).
     */
    fields.flags = BLE_HS_ADV_F_DISC_GEN |
                   BLE_HS_ADV_F_BREDR_UNSUP;

    /* Indicate that the TX power level field should be included; have the
     * stack fill this value automatically.  This is done by assigning the
     * special value BLE_HS_ADV_TX_PWR_LVL_AUTO.
     */
    fields.tx_pwr_lvl_is_present = 1;
#if defined (NIM_BLE_GATT_ESP_BLE_PWR_TYPE_ADV_POWER_LEVEL)
    switch(esp_ble_tx_power_get(ESP_BLE_PWR_TYPE_ADV)) {
    case ESP_PWR_LVL_N12:   fields.tx_pwr_lvl = -12;    break;
    case ESP_PWR_LVL_N9:    fields.tx_pwr_lvl = -9;     break;
    case ESP_PWR_LVL_N6:    fields.tx_pwr_lvl = -6;     break;
    case ESP_PWR_LVL_N3:    fields.tx_pwr_lvl = -3;     break;
    case ESP_PWR_LVL_N0:    fields.tx_pwr_lvl = 0;      break;
    case ESP_PWR_LVL_P3:    fields.tx_pwr_lvl = 3;      break;
    case ESP_PWR_LVL_P6:    fields.tx_pwr_lvl = 6;      break;
    case ESP_PWR_LVL_P9:    fields.tx_pwr_lvl = 9;      break;
    default:
        fields.tx_pwr_lvl = BLE_HS_ADV_TX_PWR_LVL_AUTO;
        break;
    }
#else
    fields.tx_pwr_lvl = BLE_HS_ADV_TX_PWR_LVL_AUTO;
#endif

    name = ble_svc_gap_device_name();
    fields.name = (uint8_t*) name;
    fields.name_len = tommRoCStringStrLen(name);
    fields.name_is_complete = 1;

#if defined (NIM_BLE_GATT_SVR_ADV_ADD_UUIDS_16_TO_ADV)
    if (0 != _nimble_adv_uuids16_num) {
        fields.uuids16              = _nimble_adv_uuids16_ptr;
        fields.num_uuids16          = _nimble_adv_uuids16_num;
        fields.uuids16_is_complete  = 1;
    }
#endif

#if defined (NIM_BLE_GATT_SVR_ADV_ADD_UUIDS_32_TO_ADV)
    if (0 != _nimble_adv_uuids32_num) {
        fields.uuids32              = _nimble_adv_uuids32_ptr
        fields.num_uuids32          = _nimble_adv_uuids32_num;
        fields.uuids32_is_complete  = 1;
    }
#endif

#if defined (NIM_BLE_GATT_SVR_ADV_ADD_UUIDS_128_TO_ADV)
    if (0 != _nimble_adv_uuids128_num) {
        fields.uuids128             = _nimble_adv_uuids128_ptr;
        fields.num_uuids128         = _nimble_adv_uuids128_num;
        fields.uuids128_is_complete = 1;
    }
#endif

#if defined (NIM_BLE_GATT_SVR_ADV_ADD_MANUF_SPECIFIC_DATA_TO_ADV)
    if (0 != _nimble_adv_manuf_spefific_data_len) {
        fields.mfg_data     = _nimble_adv_manuf_spefific_data_ptr;
        fields.mfg_data_len = _nimble_adv_manuf_spefific_data_len;
    }
#endif

    rc = ble_gap_adv_set_fields(&fields);
    if (rc != 0) {
        TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Error ble_gap_adv_set_fields=", (int32_t) rc);
        return;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&fields, 0, sizeof(fields)));

#if defined (NIM_BLE_GATT_SVR_ADV_ADD_UUIDS_16_TO_ADV_RSP)
    if (0 != _nimble_adv_rsp_uuids16_num) {
        fields.uuids16              = _nimble_adv_rsp_uuids16_ptr;
        fields.num_uuids16          = _nimble_adv_rsp_uuids16_num;
        fields.uuids16_is_complete  = 1;
    }
#endif

#if defined (NIM_BLE_GATT_SVR_ADV_ADD_UUIDS_32_TO_ADV_RSP)
    if (0 != _nimble_adv_rsp_uuids32_num) {
        fields.uuids32              = _nimble_adv_rsp_uuids32_ptr;
        fields.num_uuids32          = _nimble_adv_rsp_uuids32_num;
        fields.uuids32_is_complete  = 1;
    }
#endif

#if defined (NIM_BLE_GATT_SVR_ADV_ADD_UUIDS_128_TO_ADV_RSP)
    if (0 != _nimble_adv_rsp_uuids128_num) {
        fields.uuids128             = _nimble_adv_rsp_uuids128_ptr;
        fields.num_uuids128         = _nimble_adv_rsp_uuids128_num;
        fields.uuids128_is_complete = 1;
    }
#endif

#if defined (NIM_BLE_GATT_SVR_ADV_ADD_MANUF_SPECIFIC_DATA_TO_ADV_RSP)
    if (0 != _nimble_adv_rsp_manuf_spefific_data_len) {
        fields.mfg_data     = _nimble_adv_rsp_manuf_spefific_data_ptr;
        fields.mfg_data_len = _nimble_adv_rsp_manuf_spefific_data_len;
    }
#endif

#if defined (NIM_BLE_GATT_SVR_ADV_ADD_UUIDS_16_TO_ADV_RSP)  ||  \
    defined (NIM_BLE_GATT_SVR_ADV_ADD_UUIDS_32_TO_ADV_RSP)  ||  \
    defined (NIM_BLE_GATT_SVR_ADV_ADD_UUIDS_128_TO_ADV_RSP) ||  \
    defined (NIM_BLE_GATT_SVR_ADV_ADD_MANUF_SPECIFIC_DATA_TO_ADV_RSP)
    rc = ble_gap_adv_rsp_set_fields(&fields);
    if (rc != 0) {
        TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Error ble_gap_adv_rsp_set_fields=", (int32_t) rc);
        return;
    }
#endif

    // Begin advertising.
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&adv_params, 0, sizeof(adv_params)));
    adv_params.conn_mode = BLE_GAP_CONN_MODE_UND;
    adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;
#if defined (NIM_BLE_GATT_SVR_ADV_ITVL_MIN)
    adv_params.itvl_min = _nimble_adv_itvl_min;
#endif
#if defined (NIM_BLE_GATT_SVR_ADV_ITVL_MAX)
    adv_params.itvl_max = _nimble_adv_itvl_max;
#endif
    rc = ble_gap_adv_start(_own_addr_type, NULL, BLE_HS_FOREVER, &adv_params, bleprph_gap_event, NULL);
    if (rc != 0) {
        TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Error enabling advertisement: ", (int32_t) rc);
        return;
    }

    TOMMROC_DEBUG_D("adv started");
}

static int bleprph_gap_event(struct ble_gap_event *event, void *arg) {

    struct ble_gap_conn_desc desc;

    esp32_multi_nimble_conn_handle_mtu_value_t connHandleMTUValue;
    tommRoC_hw_template_ble_multi_def_conn_handler_t connHandler;

    bool isFull;

    int rc;

    do { // Added to avoid "warning: unreachable code"
        switch (event->type) {

        case BLE_GAP_EVENT_CONNECT:
            // A new connection was established or a connection attempt failed.
            TOMMROC_DEBUG_D(((0 == event->connect.status) ? ("connection established") : ("connection failed")));

            if (0 == event->connect.status) {

#if defined (NIM_BLE_GATT_ESP_BLE_PWR_TYPE_DEFAULT_POWER_LEVEL)
                esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_DEFAULT, NIM_BLE_GATT_ESP_BLE_PWR_TYPE_DEFAULT_POWER_LEVEL);
#endif
#if defined (NIM_BLE_GATT_ESP_BLE_PWR_TYPE_ADV_POWER_LEVEL)
                esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, NIM_BLE_GATT_ESP_BLE_PWR_TYPE_ADV_POWER_LEVEL);
#endif
#if defined (NIM_BLE_GATT_ESP_BLE_PWR_TYPE_SCAN_POWER_LEVEL)
                esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_SCAN ,NIM_BLE_GATT_ESP_BLE_PWR_TYPE_SCAN_POWER_LEVEL);
#endif

                rc = ble_gap_conn_find(event->connect.conn_handle, &desc);
                TOMMROC_ASSERT_ZERO(rc);
                if (0 != rc) {
                    TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Failed to ble_gap_conn_find; rc=", (int32_t) rc);
                }

                rc = ble_att_set_preferred_mtu(CONFIG_BT_NIMBLE_ATT_PREFERRED_MTU);
                TOMMROC_ASSERT_ZERO(rc);
                if (0 != rc) {
                    TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Failed to set preferred MTU; rc=", (int32_t) rc);
                }

                // NOTE: values copied by bleprph_throughput example
                rc = ble_hs_hci_util_set_data_len(event->connect.conn_handle, 251, 2120);
                TOMMROC_ASSERT_ZERO(rc);
                if (0 != rc) {
                    TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Set packet length failed; rc=", (int32_t) rc);
                }

                connHandleMTUValue.connHandle   = (int32_t) event->connect.conn_handle;
                connHandleMTUValue.mtuValue     = TOMMROC_HW_TEMPLATE_BLE_ENV_ESP32_MULTI_CONNECTION_NIM_BLE_CONN_HANDLE_MTU_VALUE_MTU_VALUE_DEFAULT;
                connHandleMTUValue.isEmpty      = false;

                if (TOMMRO_C_HW_ERR_SUCCESS == tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueAdd(&connHandleMTUValue)) {
                    if (NULL != _on_connect_cb) {
                        connHandler.connHandle = connHandleMTUValue.connHandle;
                        _on_connect_cb(&connHandler);
                    }
                }

                TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueIsFull(&isFull));

                if (!isFull) {
                    bleprph_advertise();
                }

                TOMMROC_DEBUG_PRINTLN_PLUS_U16(TOMMRO_C_DEBUG_D_LEVEL, "connection. conn handle=", event->connect.conn_handle, TOMMRO_C_UTIL_DECIMAL_FORMAT);
            }
            return 0;

        case BLE_GAP_EVENT_DISCONNECT:
            TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueIsFull(&isFull));

            TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_D_LEVEL, "Disconnect; reason=", (int32_t) event->disconnect.reason);

            connHandleMTUValue.connHandle   = (int32_t) event->disconnect.conn.conn_handle;
            connHandleMTUValue.isEmpty      = true;

            if (TOMMRO_C_HW_ERR_SUCCESS == tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueRemove(&connHandleMTUValue)) {
                if (NULL != _on_disconnect_cb) {
                    connHandler.connHandle = connHandleMTUValue.connHandle;
                    _on_disconnect_cb(&connHandler);
                }
            }

            // If before was full, re-start ADV
            if (isFull) {
                bleprph_advertise();
            }

            TOMMROC_DEBUG_PRINTLN_PLUS_U16(TOMMRO_C_DEBUG_D_LEVEL, "disconnection. conn handle=", event->disconnect.conn.conn_handle, TOMMRO_C_UTIL_DECIMAL_FORMAT);
            return 0;

        case BLE_GAP_EVENT_CONN_UPDATE:
            // The central has updated the connection parameters.
            TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_D_LEVEL, "Connection updated; status=", (int32_t) event->conn_update.status);
            TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(ble_gap_conn_find(event->conn_update.conn_handle, &desc), 0);
            return 0;

        case BLE_GAP_EVENT_ADV_COMPLETE:
            bleprph_advertise();
            return 0;

        case BLE_GAP_EVENT_ENC_CHANGE:
            // Encryption has been enabled or disabled for this connection.
            TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_D_LEVEL, "Encryption change event; status=", (int32_t) event->enc_change.status);
            TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(ble_gap_conn_find(event->enc_change.conn_handle, &desc), 0);
            return 0;

        case BLE_GAP_EVENT_SUBSCRIBE:
            TOMMROC_DEBUG_D("Subscribe event");
            return 0;

        case BLE_GAP_EVENT_MTU:
            TOMMROC_DEBUG_PRINTLN_PLUS_U16(TOMMRO_C_DEBUG_D_LEVEL, "MTU update event; mtu=", event->mtu.value, TOMMRO_C_UTIL_DECIMAL_FORMAT);

            connHandleMTUValue.connHandle   = (int32_t) event->mtu.conn_handle;
            connHandleMTUValue.mtuValue     = event->mtu.value;
            connHandleMTUValue.isEmpty      = false;

            tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueUpdate(&connHandleMTUValue);

            TOMMROC_DEBUG_PRINTLN_PLUS_U16(TOMMRO_C_DEBUG_D_LEVEL, "MTU update. conn handle=", event->mtu.conn_handle, TOMMRO_C_UTIL_DECIMAL_FORMAT);
            return 0;

        case BLE_GAP_EVENT_REPEAT_PAIRING:
            /* We already have a bond with the peer, but it is attempting to
             * establish a new secure link.  This app sacrifices security for
             * convenience: just throw away the old bond and accept the new link.
             */

            // Delete the old bond.
            TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(ble_gap_conn_find(event->repeat_pairing.conn_handle, &desc), 0);
            ble_store_util_delete_peer(&desc.peer_id_addr);

            // Return BLE_GAP_REPEAT_PAIRING_RETRY to indicate that the host should continue with the pairing operation.
            return BLE_GAP_REPEAT_PAIRING_RETRY;

        case BLE_GAP_EVENT_PASSKEY_ACTION:
            TOMMROC_DEBUG_D("PASSKEY_ACTION_EVENT started");
            struct ble_sm_io pkey = {0};
            int key = 0;

            if (event->passkey.params.action == BLE_SM_IOACT_DISP) {
                pkey.action = event->passkey.params.action;
                pkey.passkey = 123456; // This is the passkey to be entered on peer
                ble_sm_inject_io(event->passkey.conn_handle, &pkey);
            } else if (event->passkey.params.action == BLE_SM_IOACT_NUMCMP) {
                pkey.action = event->passkey.params.action;
                if (scli_receive_key(&key)) {
                    pkey.numcmp_accept = key;
                } else {
                    pkey.numcmp_accept = 0;
                }
                ble_sm_inject_io(event->passkey.conn_handle, &pkey);
            } else if (event->passkey.params.action == BLE_SM_IOACT_OOB) {
                static uint8_t tem_oob[16] = {0};
                pkey.action = event->passkey.params.action;
                for (int i = 0; i < 16; i++) {
                    pkey.oob[i] = tem_oob[i];
                }
                ble_sm_inject_io(event->passkey.conn_handle, &pkey);
            } else if (event->passkey.params.action == BLE_SM_IOACT_INPUT) {
                pkey.action = event->passkey.params.action;
                if (scli_receive_key(&key)) {
                    pkey.passkey = key;
                } else {
                    pkey.passkey = 0;
                }
                ble_sm_inject_io(event->passkey.conn_handle, &pkey);
            }
            return 0;

        }
    } while (0);

    return 0;
}

static void _bleprph_on_reset(int reason) {

    TOMMROC_UTIL_UNUSED_PARAM(reason);

    TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Resetting state; reason: ", (int32_t) reason);
}

static void _bleprph_on_sync(void) {

    uint8_t addrVal[6];

    int rc;

    // Make sure we have proper identity address set (public preferred)
    rc = ble_hs_util_ensure_addr(0);
    TOMMROC_ASSERT_ZERO(rc);
    if (0 != rc) {
        TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "ble_hs_util_ensure_addr error=", (int32_t) rc);
        return;
    }

    // Figure out address to use while advertising (no privacy for now)
    rc = ble_hs_id_infer_auto(0, &_own_addr_type);
    TOMMROC_ASSERT_ZERO(rc);
    if (0 != rc) {
        TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "ble_hs_id_infer_auto error=", (int32_t) rc);
        return;
    }

    // Printing ADDR
    rc = ble_hs_id_copy_addr(_own_addr_type, addrVal, NULL);
    TOMMROC_ASSERT_ZERO(rc);
    if (0 != rc) {
        TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "ble_hs_id_copy_addr error=", (int32_t) rc);
        return;
    }
    TOMMROC_DEBUG_PRINTLN_PLUS_BUFFER(TOMMRO_C_DEBUG_D_LEVEL, "Device Address: ", addrVal, sizeof(addrVal));

    // Begin advertising.
    bleprph_advertise();

    _nimble_started = true;
}

static void _bleprph_host_task(void *param) {

    TOMMROC_DEBUG_D("BLE PRPH Host Task Started");

    // This function will return only when nimble_port_stop() is executed
    nimble_port_run();

    nimble_port_freertos_deinit();
}
#endif

#if defined (CONFIG_BT_NIMBLE_ROLE_CENTRAL)
static int blecent_gap_event(struct ble_gap_event *event, void *arg) {

#if NIMBLE_BLE_CONNECT
    struct ble_gap_conn_desc desc;
#endif
    struct ble_hs_adv_fields fields;
#if MYNEWT_VAL(BLE_HCI_VS)
#if MYNEWT_VAL(BLE_POWER_CONTROL)
    struct ble_gap_set_auto_pcl_params params;
#endif
#endif
    int rc;

    switch (event->type) {
    case BLE_GAP_EVENT_DISC:
        TOMMROC_DEBUG_D("BLE_GAP_EVENT_DISC");

        // if generic scan selected
        if (NULL != _generic_scan_funct_ptr) {
            TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(_generic_scan_funct_ptr((void*) &event->disc));
        }

        // if iBeacon scan selected
        if (NULL != _ibeacon_scan_funct_ptr) {
            // Search for BLE iBeacon Packet
            if (esp_ble_is_ibeacon_packet(event->disc.data, event->disc.length_data)) {

                esp_ble_ibeacon_t* ibeacon_data = (esp_ble_ibeacon_t*) (event->disc.data);

                TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(ibeacon.BLEMACAddr, scan_result->scan_rst.bda, sizeof(ibeacon.BLEMACAddr)));
                ibeacon.rssi = (int32_t) scan_result->scan_rst.rssi;

                TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(ibeacon.head.flags, ibeacon_data->ibeacon_head.flags, sizeof(ibeacon.head.flags)));
                ibeacon.head.length         = ibeacon_data->ibeacon_head.length;
                ibeacon.head.type           = ibeacon_data->ibeacon_head.type;
                ibeacon.head.company_id     = ibeacon_data->ibeacon_head.company_id;
                ibeacon.head.beacon_type    = ibeacon_data->ibeacon_head.beacon_type;

                TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(ibeacon.vendor.proximity_uuid, ibeacon_data->ibeacon_vendor.proximity_uuid, sizeof(ibeacon.vendor.proximity_uuid)));
                ibeacon.vendor.major            = ENDIAN_CHANGE_U16(ibeacon_data->ibeacon_vendor.major);
                ibeacon.vendor.minor            = ENDIAN_CHANGE_U16(ibeacon_data->ibeacon_vendor.minor);
                ibeacon.vendor.measured_power   = ibeacon_data->ibeacon_vendor.measured_power;

                TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(_ibeacon_scan_funct_ptr(&ibeacon));
            }
        }











        rc = ble_hs_adv_parse_fields(&fields, event->disc.data, event->disc.length_data);
        if (rc != 0) {
            return 0;
        }

        /* An advertisement report was received during GAP discovery. */
        print_adv_fields(&fields);

        /* Try to connect to the advertiser if it looks interesting. */
//todo        blecent_connect_if_interesting(&event->disc);
        return 0;
#if NIMBLE_BLE_CONNECT
    case BLE_GAP_EVENT_CONNECT:
        TOMMROC_DEBUG_D("BLE_GAP_EVENT_CONNECT");
        /* A new connection was established or a connection attempt failed. */
        if (event->connect.status == 0) {
            /* Connection successfully established. */
            TOMMROC_DEBUG_D("Connection established");

            rc = ble_gap_conn_find(event->connect.conn_handle, &desc);
            assert(rc == 0);
            print_conn_desc(&desc);

            /* Remember peer. */
            rc = peer_add(event->connect.conn_handle);
            if (rc != 0) {
                TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Failed to add peer; error=", (int32_t) rc);
                return 0;
            }

#if MYNEWT_VAL(BLE_POWER_CONTROL)
            blecent_power_control(event->connect.conn_handle);
#endif

#if MYNEWT_VAL(BLE_HCI_VS)
#if MYNEWT_VAL(BLE_POWER_CONTROL)
            memset(&params, 0x0, sizeof(struct ble_gap_set_auto_pcl_params));
            params.conn_handle = event->connect.conn_handle;
            rc = ble_gap_set_auto_pcl_param(&params);
            if (rc != 0) {
                TOMMROC_DEBUG_D("Failed to send VSC");
                return 0;
            }
            else {
                TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_D_LEVEL, "Successfully issued VSC; res=", (int32_t) rc);
            }
#endif
#endif

#if CONFIG_EXAMPLE_ENCRYPTION
            /** Initiate security - It will perform
             * Pairing (Exchange keys)
             * Bonding (Store keys)
             * Encryption (Enable encryption)
             * Will invoke event BLE_GAP_EVENT_ENC_CHANGE
             **/
            rc = ble_gap_security_initiate(event->connect.conn_handle);
            if (rc != 0) {
                TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_D_LEVEL, "Security could not be initiated; res=", (int32_t) rc);
                return ble_gap_terminate(event->connect.conn_handle, BLE_ERR_REM_USER_CONN_TERM);
            } else {
                TOMMROC_DEBUG_D("Connection secured");
            }
#else
#if MYNEWT_VAL(BLE_GATTC)
// TODO           /* Perform service discovery */
//            rc = peer_disc_all(event->connect.conn_handle,
//                    blecent_on_disc_complete, NULL);
//            if(rc != 0) {
//                tommroc_debug_println_plus_i32(tommro_c_debug_e_level, "failed to discover services; error=", (int32_t) rc);
//                return 0;
//            }
#endif
#endif
        } else {
            /* Connection attempt failed; resume scanning. */
            MODLOG_DFLT(ERROR, "Error: Connection failed; status=%d\n",
                    event->connect.status);
            //TODO        blecent_scan();
        }

        return 0;

    case BLE_GAP_EVENT_DISCONNECT:
        TOMMROC_DEBUG_D("BLE_GAP_EVENT_DISCONNECT");
        /* Connection terminated. */
        MODLOG_DFLT(INFO, "disconnect; reason=%d ", event->disconnect.reason);
        print_conn_desc(&event->disconnect.conn);
        MODLOG_DFLT(INFO, "\n");

        /* Forget about peer. */
        peer_delete(event->disconnect.conn.conn_handle);

#if MYNEWT_VAL(BLE_EATT_CHAN_NUM) > 0
        /* Reset EATT config */
        bearers = 0;
        for (int i = 0; i < MYNEWT_VAL(BLE_EATT_CHAN_NUM); i++) {
            cids[i] = 0;
        }
#endif

        /* Resume scanning. */
//TODO        blecent_scan();
        return 0;

    case BLE_GAP_EVENT_DISC_COMPLETE:
        TOMMROC_DEBUG_D("BLE_GAP_EVENT_DISC_COMPLETE");
        MODLOG_DFLT(INFO, "discovery complete; reason=%d\n",
                event->disc_complete.reason);
        return 0;

    case BLE_GAP_EVENT_ENC_CHANGE:
        TOMMROC_DEBUG_D("BLE_GAP_EVENT_ENC_CHANGE");
        /* Encryption has been enabled or disabled for this connection. */
        MODLOG_DFLT(INFO, "encryption change event; status=%d ",
                event->enc_change.status);
        rc = ble_gap_conn_find(event->enc_change.conn_handle, &desc);
        assert(rc == 0);
        print_conn_desc(&desc);
#if !MYNEWT_VAL(BLE_EATT_CHAN_NUM)
#if CONFIG_EXAMPLE_ENCRYPTION && MYNEWT_VAL(BLE_GATTC)
        /*** Go for service discovery after encryption has been successfully enabled ***/
        rc = peer_disc_all(event->enc_change.conn_handle,
                blecent_on_disc_complete, NULL);
        if (rc != 0) {
            MODLOG_DFLT(ERROR, "Failed to discover services; rc=%d\n", rc);
            return 0;
        }
#endif
#endif
        return 0;

    case BLE_GAP_EVENT_NOTIFY_RX:
        TOMMROC_DEBUG_D("BLE_GAP_EVENT_NOTIFY_RX");
        /* Peer sent us a notification or indication. */
        MODLOG_DFLT(INFO, "received %s; conn_handle=%d attr_handle=%d "
                "attr_len=%d\n",
                event->notify_rx.indication ?
                        "indication" :
                        "notification",
                        event->notify_rx.conn_handle,
                        event->notify_rx.attr_handle,
                        OS_MBUF_PKTLEN(event->notify_rx.om));

        /* Attribute data is contained in event->notify_rx.om. Use
         * `os_mbuf_copydata` to copy the data received in notification mbuf */
        return 0;

    case BLE_GAP_EVENT_MTU:
        TOMMROC_DEBUG_D("BLE_GAP_EVENT_MTU");
        MODLOG_DFLT(INFO, "mtu update event; conn_handle=%d cid=%d mtu=%d\n",
                event->mtu.conn_handle,
                event->mtu.channel_id,
                event->mtu.value);
        return 0;

    case BLE_GAP_EVENT_REPEAT_PAIRING:
        TOMMROC_DEBUG_D("BLE_GAP_EVENT_REPEAT_PAIRING");
        /* We already have a bond with the peer, but it is attempting to
         * establish a new secure link.  This app sacrifices security for
         * convenience: just throw away the old bond and accept the new link.
         */

        /* Delete the old bond. */
        rc = ble_gap_conn_find(event->repeat_pairing.conn_handle, &desc);
        assert(rc == 0);
        ble_store_util_delete_peer(&desc.peer_id_addr);

        /* Return BLE_GAP_REPEAT_PAIRING_RETRY to indicate that the host should
         * continue with the pairing operation.
         */
        return BLE_GAP_REPEAT_PAIRING_RETRY;

#if CONFIG_EXAMPLE_EXTENDED_ADV
    case BLE_GAP_EVENT_EXT_DISC:
        /* An advertisement report was received during GAP discovery. */
        ext_print_adv_report(&event->ext_disc);

        blecent_connect_if_interesting(&event->ext_disc);
        return 0;
#endif

#if MYNEWT_VAL(BLE_POWER_CONTROL)
    case BLE_GAP_EVENT_TRANSMIT_POWER:
        MODLOG_DFLT(INFO, "Transmit power event : status=%d conn_handle=%d reason=%d "
                "phy=%d power_level=%d power_level_flag=%d delta=%d",
                event->transmit_power.status,
                event->transmit_power.conn_handle,
                event->transmit_power.reason,
                event->transmit_power.phy,
                event->transmit_power.transmit_power_level,
                event->transmit_power.transmit_power_level_flag,
                event->transmit_power.delta);
        return 0;

    case BLE_GAP_EVENT_PATHLOSS_THRESHOLD:
        MODLOG_DFLT(INFO, "Pathloss threshold event : conn_handle=%d current path loss=%d "
                "zone_entered =%d",
                event->pathloss_threshold.conn_handle,
                event->pathloss_threshold.current_path_loss,
                event->pathloss_threshold.zone_entered);
        return 0;
#endif

#if MYNEWT_VAL(BLE_EATT_CHAN_NUM) > 0
    case BLE_GAP_EVENT_EATT:
        int i;
        MODLOG_DFLT(INFO, "EATT %s : conn_handle=%d cid=%d",
                event->eatt.status ? "disconnected" : "connected",
                        event->eatt.conn_handle,
                        event->eatt.cid);
        if (event->eatt.status) {
            /* Remove CID from the list of saved CIDs */
            for (i = 0; i < bearers; i++) {
                if (cids[i] == event->eatt.cid) {
                    break;
                }
            }
            while (i < (bearers - 1)) {
                cids[i] = cids[i + 1];
                i += 1;
            }
            cids[i] = 0;

            /* Now Abort */
            return 0;
        }
        cids[bearers] = event->eatt.cid;
        bearers += 1;
        if (bearers != MYNEWT_VAL(BLE_EATT_CHAN_NUM)) {
            /* Wait until all EATT bearers are connected before proceeding */
            return 0;
        }
        /* Set the default bearer to use for further procedures */
        rc = ble_att_set_default_bearer_using_cid(event->eatt.conn_handle, cids[0]);
        if (rc != 0) {
            MODLOG_DFLT(INFO, "Cannot set default EATT bearer, rc = %d\n", rc);
            return rc;
        }
#if MYNEWT_VAL(BLE_GATTC)
        /* Perform service discovery */
        rc = peer_disc_all(event->eatt.conn_handle,
                blecent_on_disc_complete, NULL);
        if(rc != 0) {
            MODLOG_DFLT(ERROR, "Failed to discover services; rc=%d\n", rc);
            return 0;
        }
#endif
#endif
        return 0;

#endif
    default:
        TOMMROC_DEBUG_D("default");
        return 0;
    }
}

static void _blecent_on_reset(int reason) {

    TOMMROC_UTIL_UNUSED_PARAM(reason);

    TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Resetting state; reason: ", (int32_t) reason);
}

static void _blecent_on_sync(void) {

    uint8_t addrVal[6];

    int rc;

    // Make sure we have proper identity address set (public preferred)
    rc = ble_hs_util_ensure_addr(0);
    TOMMROC_ASSERT_ZERO(rc);
    if (0 != rc) {
        TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "ble_hs_util_ensure_addr error=", (int32_t) rc);
        return;
    }

    // Figure out address to use while advertising (no privacy for now)
    rc = ble_hs_id_infer_auto(0, &_own_addr_type);
    TOMMROC_ASSERT_ZERO(rc);
    if (0 != rc) {
        TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "ble_hs_id_infer_auto error=", (int32_t) rc);
        return;
    }

    // Printing ADDR
    rc = ble_hs_id_copy_addr(_own_addr_type, addrVal, NULL);
    TOMMROC_ASSERT_ZERO(rc);
    if (0 != rc) {
        TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "ble_hs_id_copy_addr error=", (int32_t) rc);
        return;
    }
    TOMMROC_DEBUG_PRINTLN_PLUS_BUFFER(TOMMRO_C_DEBUG_D_LEVEL, "Device Address: ", addrVal, sizeof(addrVal));

    _nimble_started = true;
}

static void _blecent_host_task(void *param) {

    TOMMROC_DEBUG_D("BLE Cent Host Task Started");

    // This function will return only when nimble_port_stop() is executed
    nimble_port_run();

    nimble_port_freertos_deinit();
}
#endif

static tommRoC_hw_err_enum_t _wait_for_nimble_started(void) {

    tommRoC_timer_t timer;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, __WAIT_FOR_NIMBLE_STARTED_mSEC__));

    do {

        if (_nimble_started) {
            return TOMMRO_C_HW_ERR_SUCCESS;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(0));

    } while (TOMMRO_C_TIMER_NOT_EXPIRED_ERR == tommRoCTimerIsExpired(&timer));

    return TOMMRO_C_HW_TIMEOUT_ERR;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* Standard BLE functions */

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiPeripheralInit(
        const   tommRoC_hw_template_ble_multi_def_on_connect_funct_t        onConnectFunctPtr,
        const   tommRoC_hw_template_ble_multi_def_on_disconnect_funct_t     onDisconnectFunctPtr,
        const   tommRoC_hw_template_ble_multi_def_on_receive_funct_t        onReceiveFunctPtr,
        const   char*                                               const   deviceBLENameStrPtr) {

#if defined (CONFIG_BT_NIMBLE_ROLE_PERIPHERAL)

    esp_err_t espErr;

    TOMMROC_ASSERT_NOT_NULL(deviceBLENameStrPtr);

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueInit());

    _on_connect_cb      = onConnectFunctPtr;
    _on_disconnect_cb   = onDisconnectFunctPtr;
    _on_receive_cb      = onReceiveFunctPtr;

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    espErr = esp_nimble_hci_and_controller_init();
    ESP_ERROR_CHECK(espErr);

    if (ESP_OK != espErr) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
#endif

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    nimble_port_init();
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    espErr = nimble_port_init();
    if (ESP_OK != espErr) {
        TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Error nimble_port_init=", (int32_t) espErr);
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
#endif

    // Initialize the NimBLE host configuration.
    ble_hs_cfg.reset_cb             = _bleprph_on_reset;
    ble_hs_cfg.sync_cb              = _bleprph_on_sync;
    ble_hs_cfg.gatts_register_cb    = gatt_svr_register_cb;
    ble_hs_cfg.store_status_cb      = ble_store_util_status_rr;
    ble_hs_cfg.sm_io_cap            = BLE_SM_IO_CAP_NO_IO;
    ble_hs_cfg.sm_sc                = 0;

    if (0 != gatt_svr_init()) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (0 != ble_svc_gap_device_name_set(deviceBLENameStrPtr)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(_device_ble_name_str, TOMMROC_STRING_NULL_TERMINATOR_CHAR, sizeof(_device_ble_name_str)));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(_device_ble_name_str, deviceBLENameStrPtr, tommRoCStringStrLen(deviceBLENameStrPtr)));

#if defined (NIM_BLE_GATT_ESP_BLE_PWR_TYPE_DEFAULT_POWER_LEVEL)
    esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_DEFAULT, NIM_BLE_GATT_ESP_BLE_PWR_TYPE_DEFAULT_POWER_LEVEL);
#endif
#if defined (NIM_BLE_GATT_ESP_BLE_PWR_TYPE_ADV_POWER_LEVEL)
    esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, NIM_BLE_GATT_ESP_BLE_PWR_TYPE_ADV_POWER_LEVEL);
#endif
#if defined (NIM_BLE_GATT_ESP_BLE_PWR_TYPE_SCAN_POWER_LEVEL)
    esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_SCAN ,NIM_BLE_GATT_ESP_BLE_PWR_TYPE_SCAN_POWER_LEVEL);
#endif

    ble_store_config_init();

    nimble_port_freertos_init(_bleprph_host_task);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_wait_for_nimble_started());

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(onConnectFunctPtr);
    TOMMROC_UTIL_UNUSED_PARAM(onDisconnectFunctPtr);
    TOMMROC_UTIL_UNUSED_PARAM(onReceiveFunctPtr);
    TOMMROC_UTIL_UNUSED_PARAM(deviceBLENameStrPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiPeripheralDeInit(void) {
#if defined (CONFIG_BT_NIMBLE_ROLE_PERIPHERAL)
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiCentralInit(void) {

#if defined (CONFIG_BT_NIMBLE_ROLE_CENTRAL)

    esp_err_t espErr;

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    espErr = esp_nimble_hci_and_controller_init();
    ESP_ERROR_CHECK(espErr);

    if (ESP_OK != espErr) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
#endif

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    nimble_port_init();
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    espErr = nimble_port_init();
    if (ESP_OK != espErr) {
        TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Error nimble_port_init=", (int32_t) espErr);
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
#endif

    // Initialize the NimBLE host configuration.
    ble_hs_cfg.reset_cb         = _blecent_on_reset;
    ble_hs_cfg.sync_cb          = _blecent_on_sync;
    ble_hs_cfg.store_status_cb  = ble_store_util_status_rr;

#if NIMBLE_BLE_CONNECT

    int rc;

    // Initialize data structures to track connected peers.
#if MYNEWT_VAL(BLE_INCL_SVC_DISCOVERY) || MYNEWT_VAL(BLE_GATT_CACHING_INCLUDE_SERVICES)
    rc = peer_init(MYNEWT_VAL(BLE_MAX_CONNECTIONS), 64, 64, 64, 64);
    TOMMROC_ASSERT_ZERO(rc);
    if (0 != rc) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
#else
    rc = peer_init(MYNEWT_VAL(BLE_MAX_CONNECTIONS), 64, 64, 64);
    TOMMROC_ASSERT_ZERO(rc);
    if (0 != rc) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
#endif
#endif

#if CONFIG_BT_NIMBLE_GAP_SERVICE
    int m;
    /* Set the default device name. */
    m = ble_svc_gap_device_name_set("nimble-blecent");
    TOMMROC_ASSERT_ZERO(m);
    if (0 != m) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
#endif

    ble_store_config_init();

    nimble_port_freertos_init(_blecent_host_task);

#if MYNEWT_VAL(BLE_EATT_CHAN_NUM) > 0
    bearers = 0;
    for (int i = 0; i < MYNEWT_VAL(BLE_EATT_CHAN_NUM); i++) {
        cids[i] = 0;
    }
#endif

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_wait_for_nimble_started());

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiCentralDeInit(void) {
#if defined (CONFIG_BT_NIMBLE_ROLE_CENTRAL)
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiPeripheralADVStart(const char* const deviceBLENameStrPtr) {

#if defined (CONFIG_BT_NIMBLE_ROLE_PERIPHERAL)

    if (0 != ble_svc_gap_device_name_set(deviceBLENameStrPtr)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(_device_ble_name_str, TOMMROC_STRING_NULL_TERMINATOR_CHAR, sizeof(_device_ble_name_str)));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(_device_ble_name_str, deviceBLENameStrPtr, tommRoCStringStrLen(deviceBLENameStrPtr)));

    // Begin advertising.
    bleprph_advertise();

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(deviceBLENameStrPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiPeripheralADVStop(void) {

#if defined (CONFIG_BT_NIMBLE_ROLE_PERIPHERAL)

    if (0 == ble_gap_adv_active()) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    if (0 != ble_gap_adv_stop()) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiPeripheralADVResume(void) {

#if defined (CONFIG_BT_NIMBLE_ROLE_PERIPHERAL)

    if (0 != ble_svc_gap_device_name_set(_device_ble_name_str)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    // Begin advertising.
    bleprph_advertise();

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiCentralGenericScanStart(
        const   tommRoC_hw_template_ble_central_generic_scan_funct_t    scanFunctPtr,
        const   tommRoC_hw_template_ble_central_scan_completed_funct_t  scanCompletedFunctPtr,
        const   uint32_t                                                scanDurationSec) {

#if defined (CONFIG_BT_NIMBLE_ROLE_CENTRAL)

    struct ble_gap_disc_params disc_params = {0};
    int rc;

    if (_connecting) {
        return TOMMRO_C_HW_BLE_CONNECTED_ERR;
    }
    if (_connected) {
        return TOMMRO_C_HW_BLE_CONNECTED_ERR;
    }
    if (_writing) {
        return TOMMRO_C_HW_BLE_CONNECTED_ERR;
    }

    _generic_scan_funct_ptr     = scanFunctPtr;
    _ibeacon_scan_funct_ptr     = NULL;
    _scan_completed_funct_ptr   = scanCompletedFunctPtr;

    /**
     * NOTE:
     * Tell the controller to DON'T filter duplicates.
     * We want to process repeated advertisements from the same device.
     */
    disc_params.filter_duplicates = 0;

    /**
     * NOTE:
     * Perform a passive scan.
     * I.e., don't send follow-up scan requests to each advertiser.
     */
    disc_params.passive = 1;

    /**
     * NOTE:
     * Use defaults for the rest of the parameters.
     */
    // Use defaults for the rest of the parameters.
    disc_params.itvl            = 0;
    disc_params.window          = 0;
    disc_params.filter_policy   = 0;
    disc_params.limited         = 0;

    // Scanning time [sec]. 0 means scan permanently
    rc = ble_gap_disc(_own_addr_type, (0 == scanDurationSec) ? (BLE_HS_FOREVER) : (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(scanDurationSec)), &disc_params, blecent_gap_event, NULL);
    if (rc != 0) {
        TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Error ble_gap_disc=", (int32_t) rc);
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(scanFunctPtr);
    TOMMROC_UTIL_UNUSED_PARAM(scanCompletedFunctPtr);
    TOMMROC_UTIL_UNUSED_PARAM(scanDurationSec);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiCentralBeaconScanStart(
        const   tommRoC_hw_template_ble_central_ibeacon_scan_funct_t    scanFunctPtr,
        const   tommRoC_hw_template_ble_central_scan_completed_funct_t  scanCompletedFunctPtr,
        const   uint32_t                                                beaconScanDurationSec) {

#if defined (CONFIG_BT_NIMBLE_ROLE_CENTRAL)

    TOMMROC_UTIL_UNUSED_PARAM(scanFunctPtr);
    TOMMROC_UTIL_UNUSED_PARAM(scanCompletedFunctPtr);
    TOMMROC_UTIL_UNUSED_PARAM(beaconScanDurationSec);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#else
    TOMMROC_UTIL_UNUSED_PARAM(scanFunctPtr);
    TOMMROC_UTIL_UNUSED_PARAM(scanCompletedFunctPtr);
    TOMMROC_UTIL_UNUSED_PARAM(beaconScanDurationSec);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

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
        const   uint8_t                                                 notifyCharUUIDSize) {

#if defined (CONFIG_BT_NIMBLE_ROLE_CENTRAL)

    TOMMROC_UTIL_UNUSED_PARAM(BLEMACAddrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(BLEMACAddrSize);
    TOMMROC_UTIL_UNUSED_PARAM(advServiceUUIDLenType);
    TOMMROC_UTIL_UNUSED_PARAM(advServiceUUIDPtr);
    TOMMROC_UTIL_UNUSED_PARAM(advServiceUUIDSize);
    TOMMROC_UTIL_UNUSED_PARAM(toWriteCharUUIDLenType);
    TOMMROC_UTIL_UNUSED_PARAM(toWriteCharUUIDPtr);
    TOMMROC_UTIL_UNUSED_PARAM(toWriteCharUUIDSize);
    TOMMROC_UTIL_UNUSED_PARAM(notifyCharUUIDLenType);
    TOMMROC_UTIL_UNUSED_PARAM(notifyCharUUIDPtr);
    TOMMROC_UTIL_UNUSED_PARAM(notifyCharUUIDSize);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#else
    TOMMROC_UTIL_UNUSED_PARAM(BLEMACAddrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(BLEMACAddrSize);
    TOMMROC_UTIL_UNUSED_PARAM(advServiceUUIDLenType);
    TOMMROC_UTIL_UNUSED_PARAM(advServiceUUIDPtr);
    TOMMROC_UTIL_UNUSED_PARAM(advServiceUUIDSize);
    TOMMROC_UTIL_UNUSED_PARAM(toWriteCharUUIDLenType);
    TOMMROC_UTIL_UNUSED_PARAM(toWriteCharUUIDPtr);
    TOMMROC_UTIL_UNUSED_PARAM(toWriteCharUUIDSize);
    TOMMROC_UTIL_UNUSED_PARAM(notifyCharUUIDLenType);
    TOMMROC_UTIL_UNUSED_PARAM(notifyCharUUIDPtr);
    TOMMROC_UTIL_UNUSED_PARAM(notifyCharUUIDSize);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiDisconnect(tommRoC_hw_template_ble_multi_def_conn_handler_t* const connHandlerPtr) {

    esp32_multi_nimble_conn_handle_mtu_value_t connHandleMTUValue;
    tommRoC_hw_template_ble_multi_def_conn_handler_t connHandler;

    int rc;

    if (!_is_connected(connHandlerPtr->connHandle)) {
        return TOMMRO_C_HW_BLE_NOT_CONNECTED_ERR;
    }

    connHandleMTUValue.connHandle   = connHandlerPtr->connHandle;
    connHandleMTUValue.isEmpty      = true;

    rc = ble_gap_terminate((uint16_t) connHandlerPtr->connHandle, BLE_ERR_REM_USER_CONN_TERM);
    TOMMROC_ASSERT_ZERO(rc);
    if (0 != rc) {
        TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Error ble_gap_terminate: ", (int32_t) rc);
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (TOMMRO_C_HW_ERR_SUCCESS != tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueRemove(&connHandleMTUValue)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(connHandlerPtr, &_template_ble_multi_conn_handler_empty, sizeof(tommRoC_hw_template_ble_multi_def_conn_handler_t)));

    if (NULL != _on_disconnect_cb) {
        connHandler.connHandle = (uint16_t) connHandleMTUValue.connHandle;
        _on_disconnect_cb(&connHandler);
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

bool tommRoCHwTemplateBLEMultiIsConnected(const tommRoC_hw_template_ble_multi_def_conn_handler_t* const connHandlerPtr) {
    return (_is_connected(connHandlerPtr->connHandle));
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiWrite(
        const   void*                                           const   dataBufferPtr,
        const   uint32_t                                                dataBufferSize,
        const   bool                                                    writeWithRsp) {
    TOMMROC_UTIL_UNUSED_PARAM(dataBufferPtr);
    TOMMROC_UTIL_UNUSED_PARAM(dataBufferSize);
    TOMMROC_UTIL_UNUSED_PARAM(writeWithRsp);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
}


/******************* Specific NimBLE functions */

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiEnvESP32NimBLENotify(
        const   tommRoC_hw_template_ble_multi_def_conn_handler_t*   const   connHandlerPtr,
        const   uint16_t                                                    chrValHandle,
        const   void*                                               const   dataPtr,
        const   uint16_t                                                    dataSize) {

    esp32_multi_nimble_conn_handle_mtu_value_t connHandleMTUValue;

    struct os_mbuf* om;
    int rc;

    void* ptr;
    uint16_t remaining;
    uint16_t toSendAmount;

    ptr         = (void*) dataPtr;
    remaining   = dataSize;

    while (remaining > 0) {

        if (TOMMRO_C_HW_ERR_SUCCESS != tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueGetFromConnHandle(connHandlerPtr->connHandle,  &connHandleMTUValue)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        if (!_is_connected(connHandleMTUValue.connHandle)) {
            return TOMMRO_C_HW_DISCONNECTED_ERR;
        }

        toSendAmount = tommRoCMathMin(remaining, connHandleMTUValue.mtuValue - __G_ATT_OPCODE_SIZE__ - __G_ATT_HANDLE_SIZE__);

        om = ble_hs_mbuf_from_flat(ptr, toSendAmount);
        if (NULL == om) {
            TOMMROC_DEBUG_E("Error ble_hs_mbuf_from_flat");
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        rc = ble_gatts_notify_custom((uint16_t) connHandleMTUValue.connHandle, chrValHandle, om);
        TOMMROC_ASSERT_ZERO(rc);
        if (0 != rc) {
            TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Error ble_gattc_notify_custom: ", (int32_t) rc);
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        ptr         += toSendAmount;
        remaining   -= toSendAmount;

        if (remaining > 0) {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(tommRoCMathMax(1, TOMMROC_UNIT_MEASURE_TIME_APPROX_uSEC_TO_mSEC(__WRITE_DELAY_FOR_EVERY_BYTE_uSEC__ * toSendAmount))));
        }
        else {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(0));
        }
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiEnvESP32NimBLEIndicate(
        const   tommRoC_hw_template_ble_multi_def_conn_handler_t*   const   connHandlerPtr,
        const   uint16_t                                                    chrValHandle,
        const   void*                                               const   dataPtr,
        const   uint16_t                                                    dataSize) {

    esp32_multi_nimble_conn_handle_mtu_value_t connHandleMTUValue;

    struct os_mbuf* om;
    int rc;

    void* ptr;
    uint16_t remaining;
    uint16_t toSendAmount;

    ptr         = (void*) dataPtr;
    remaining   = dataSize;

    while (remaining > 0) {

        if (TOMMRO_C_HW_ERR_SUCCESS != tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueGetFromConnHandle(connHandlerPtr->connHandle,  &connHandleMTUValue)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        if (!_is_connected(connHandleMTUValue.connHandle)) {
            return TOMMRO_C_HW_DISCONNECTED_ERR;
        }

        toSendAmount = tommRoCMathMin(remaining, connHandleMTUValue.mtuValue - __G_ATT_OPCODE_SIZE__ - __G_ATT_HANDLE_SIZE__);

        om = ble_hs_mbuf_from_flat(ptr, toSendAmount);
        if (NULL == om) {
            TOMMROC_DEBUG_E("Error ble_hs_mbuf_from_flat");
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        rc = ble_gatts_indicate_custom((uint16_t) connHandleMTUValue.connHandle, chrValHandle, om);
        TOMMROC_ASSERT_ZERO(rc);
        if (0 != rc) {
            TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Error ble_gattc_indicate_custom: ", (int32_t) rc);
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        ptr         += toSendAmount;
        remaining   -= toSendAmount;

        if (remaining > 0) {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(tommRoCMathMax(1, TOMMROC_UNIT_MEASURE_TIME_APPROX_uSEC_TO_mSEC(__WRITE_DELAY_FOR_EVERY_BYTE_uSEC__ * toSendAmount))));
        }
        else {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(0));
        }
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiEnvESP32NimBLEOnReceive(
        const   tommRoC_hw_template_ble_multi_def_conn_handler_t*   const   connHandlerPtr,
        const   uint16_t                                                    chrValHandle,
        const   void*                                               const   dataPtr,
        const   uint16_t                                                    dataSize) {

    if (NULL == _on_receive_cb) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    return _on_receive_cb(
            connHandlerPtr,
            chrValHandle,
            dataPtr,
            dataSize);
}

#endif

#endif

#endif
