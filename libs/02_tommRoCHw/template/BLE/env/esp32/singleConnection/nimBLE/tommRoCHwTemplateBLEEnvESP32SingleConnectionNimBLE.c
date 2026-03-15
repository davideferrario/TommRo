
/**
 * NOTE:
 * - In case of BLE peripheral, application must implement "gatt_svr.c" and "gatt_svr.h" files into "nimBLE" folder.
 * - In case of BLE central, application must implement "gatt_cent.c" and "gatt_cent.h" files into "nimBLE" folder.
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBLE.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)

#include "sdkconfig.h"

#include "env/tommRoCTemplateEnv.h"

#if !defined (__TOMMROC_HW_DISABLE_BLE_TEMPLATE__) && !defined (CONFIG_EXAMPLE_PROV_TRANSPORT_BLE) && defined (CONFIG_BT_ENABLED) && defined (CONFIG_BT_NIMBLE_ENABLED)
#if defined (CONFIG_BT_NIMBLE_MAX_CONNECTIONS) && (1 == CONFIG_BT_NIMBLE_MAX_CONNECTIONS)

#include "tommRoCHwTemplateBLEEnvESP32SingleConnectionNimBLE.h"

#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
#include "esp_nimble_hci.h"
#endif

#include "host/ble_hs.h"
#include "host/ble_uuid.h"
#include "host/util/util.h"
#include "services/gap/ble_svc_gap.h"

#if defined (CONFIG_BT_NIMBLE_ROLE_PERIPHERAL)
#include "nimBLE/gatt_svr.h"
#endif

#if defined (CONFIG_BT_NIMBLE_ROLE_CENTRAL)
#include "nimBLE/gatt_cent.h"
#endif

#include "esp_bt.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __WRITE_DELAY_FOR_EVERY_BYTE_uSEC__ (250)

#define __CONN_HANDLE_NOT_CONNECTED_VALUE__ (-1)
#define __MTU_VALUE_DEFAULT__               (20)

// NOTE: copied by NXP BLE stack
#define __G_ATT_OPCODE_SIZE__               (1U)
#define __G_ATT_HANDLE_SIZE__               (2U)

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

static char _device_ble_name_str[MYNEWT_VAL(BLE_SVC_GAP_DEVICE_NAME_MAX_LENGTH) + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE];

static int bleprph_gap_event(struct ble_gap_event *event, void *arg);
static uint8_t _own_addr_type;

static int32_t _conn_handle = __CONN_HANDLE_NOT_CONNECTED_VALUE__;
static uint16_t _mtu_value  = __MTU_VALUE_DEFAULT__;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static bool _is_connected(void) {
    return (__CONN_HANDLE_NOT_CONNECTED_VALUE__ != _conn_handle);
}

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

/**
 * The nimble host executes this callback when a GAP event occurs.  The
 * application associates a GAP event callback with each connection that forms.
 * bleprph uses the same callback for all connections.
 *
 * @param event                 The type of event being signalled.
 * @param ctxt                  Various information pertaining to the event.
 * @param arg                   Application-specified argument; unused by
 *                                  bleprph.
 *
 * @return                      0 if the application successfully handled the
 *                                  event; nonzero on failure.  The semantics
 *                                  of the return code is specific to the
 *                                  particular GAP event being signalled.
 */
static int bleprph_gap_event(struct ble_gap_event *event, void *arg) {

    struct ble_gap_conn_desc desc;

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
                if (0 != rc) {
                    TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Failed to ble_gap_conn_find; rc=", (int32_t) rc);
                }

                rc = ble_att_set_preferred_mtu(CONFIG_BT_NIMBLE_ATT_PREFERRED_MTU);
                if (0 != rc) {
                    TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Failed to set preferred MTU; rc=", (int32_t) rc);
                }
            }

            if (0 != event->connect.status) {
                // Connection failed; resume advertising.
                bleprph_advertise();
            }

            // NOTE: values copied by bleprph_throughput example
            rc = ble_hs_hci_util_set_data_len(event->connect.conn_handle, 251, 2120);
            if (0 != rc) {
                TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Set packet length failed; rc=", (int32_t) rc);
            }

            _conn_handle    = (int32_t) event->connect.conn_handle;
            _mtu_value      = __MTU_VALUE_DEFAULT__;
            return 0;

        case BLE_GAP_EVENT_DISCONNECT:
            TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_D_LEVEL, "Disconnect; reason=", (int32_t) event->disconnect.reason);

            // Connection terminated; resume advertising.
            bleprph_advertise();

            _conn_handle    = __CONN_HANDLE_NOT_CONNECTED_VALUE__;
            _mtu_value      = __MTU_VALUE_DEFAULT__;
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
            _mtu_value = event->mtu.value;
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

    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(ble_hs_util_ensure_addr(0), 0);

    // Figure out address to use while advertising (no privacy for now)
    rc = ble_hs_id_infer_auto(0, &_own_addr_type);
    if (0 != rc) {
        TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "ble_hs_id_infer_auto error=", (int32_t) rc);
        return;
    }

    // Printing ADDR
    rc = ble_hs_id_copy_addr(_own_addr_type, addrVal, NULL);
    if (0 != rc) {
        TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "ble_hs_id_copy_addr error=", (int32_t) rc);
        return;
    }
    TOMMROC_DEBUG_PRINTLN_PLUS_BUFFER(TOMMRO_C_DEBUG_D_LEVEL, "Device Address: ", addrVal, sizeof(addrVal));

    // Begin advertising.
    bleprph_advertise();
}

static void _bleprph_host_task(void *param) {

    TOMMROC_DEBUG_D("BLE Host Task Started");

    // This function will return only when nimble_port_stop() is executed
    nimble_port_run();

    nimble_port_freertos_deinit();
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* Standard BLE functions */

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEPeripheralInit(const char* const deviceBLENameStrPtr) {

    esp_err_t espErr;

    TOMMROC_ASSERT_NOT_NULL(deviceBLENameStrPtr);

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

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEPeripheralDeInit(void) {
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLECentralInit(void) {
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLECentralDeInit(void) {
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEPeripheralADVStart(const char* const deviceBLENameStrPtr) {

    if (0 != ble_svc_gap_device_name_set(deviceBLENameStrPtr)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(_device_ble_name_str, TOMMROC_STRING_NULL_TERMINATOR_CHAR, sizeof(_device_ble_name_str)));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(_device_ble_name_str, deviceBLENameStrPtr, tommRoCStringStrLen(deviceBLENameStrPtr)));

    // Begin advertising.
    bleprph_advertise();

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEPeripheralADVStop(void) {

    if (0 == ble_gap_adv_active()) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    if (0 != ble_gap_adv_stop()) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEPeripheralADVResume(void) {

    if (0 != ble_svc_gap_device_name_set(_device_ble_name_str)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    // Begin advertising.
    bleprph_advertise();

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLECentralGenericScanStart(
        const   tommRoC_hw_template_ble_central_generic_scan_funct_t    scanFunctPtr,
        const   tommRoC_hw_template_ble_central_scan_completed_funct_t  scanCompletedFunctPtr,
        const   uint32_t                                                scanDurationSec) {
    TOMMROC_UTIL_UNUSED_PARAM(scanFunctPtr);
    TOMMROC_UTIL_UNUSED_PARAM(scanCompletedFunctPtr);
    TOMMROC_UTIL_UNUSED_PARAM(scanDurationSec);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLECentralBeaconScanStart(
        const   tommRoC_hw_template_ble_central_ibeacon_scan_funct_t    scanFunctPtr,
        const   tommRoC_hw_template_ble_central_scan_completed_funct_t  scanCompletedFunctPtr,
        const   uint32_t                                                beaconScanDurationSec) {
    TOMMROC_UTIL_UNUSED_PARAM(scanFunctPtr);
    TOMMROC_UTIL_UNUSED_PARAM(scanCompletedFunctPtr);
    TOMMROC_UTIL_UNUSED_PARAM(beaconScanDurationSec);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
}

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
        const   uint8_t                                                 notifyCharUUIDSize) {
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
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEDisconnect(void) {

    int rc;

    if (!_is_connected()) {
        return TOMMRO_C_HW_BLE_NOT_CONNECTED_ERR;
    }

    rc = ble_gap_terminate(_conn_handle, BLE_ERR_REM_USER_CONN_TERM);
    if (0 != rc) {
        TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Error ble_gap_terminate: ", (int32_t) rc);
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

bool tommRoCHwTemplateBLEIsConnected(void) {
    return _is_connected();
}


tommRoC_hw_err_enum_t tommRoCHwTemplateBLEWrite(
        const   void*                                           const   dataBufferPtr,
        const   uint32_t                                                dataBufferSize,
        const   bool                                                    writeWithRsp) {
    TOMMROC_UTIL_UNUSED_PARAM(dataBufferPtr);
    TOMMROC_UTIL_UNUSED_PARAM(dataBufferSize);
    TOMMROC_UTIL_UNUSED_PARAM(writeWithRsp);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
}


/******************* Specific NimBLE functions */

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEEnvESP32NimBLENotify(const uint16_t chrValHandle, const void* const dataPtr, const uint16_t dataSize) {

    struct os_mbuf* om;
    int rc;

    void* ptr;
    uint16_t remaining;
    uint16_t toSendAmount;

    ptr         = (void*) dataPtr;
    remaining   = dataSize;

    while (remaining > 0) {

        if (!_is_connected()) {
            return TOMMRO_C_HW_DISCONNECTED_ERR;
        }

        toSendAmount = tommRoCMathMin(remaining, _mtu_value - __G_ATT_OPCODE_SIZE__ - __G_ATT_HANDLE_SIZE__);

        om = ble_hs_mbuf_from_flat(ptr, toSendAmount);
        if (NULL == om) {
            TOMMROC_DEBUG_E("Error ble_hs_mbuf_from_flat");
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        rc = ble_gattc_notify_custom((uint16_t) _conn_handle, chrValHandle, om);
        if (0 != rc) {
            TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Error ble_gattc_notify_custom: ", (int32_t) rc);
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(tommRoCMathMax(1, TOMMROC_UNIT_MEASURE_TIME_APPROX_uSEC_TO_mSEC(__WRITE_DELAY_FOR_EVERY_BYTE_uSEC__ * toSendAmount))));

        ptr         += toSendAmount;
        remaining   -= toSendAmount;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEEnvESP32NimBLEIndicate(const uint16_t chrValHandle, const void* const dataPtr, const uint16_t dataSize) {

    struct os_mbuf* om;
    int rc;

    void* ptr;
    uint16_t remaining;
    uint16_t toSendAmount;

    ptr         = (void*) dataPtr;
    remaining   = dataSize;

    while (remaining > 0) {

        if (!_is_connected()) {
            return TOMMRO_C_HW_DISCONNECTED_ERR;
        }

        toSendAmount = tommRoCMathMin(remaining, _mtu_value - __G_ATT_OPCODE_SIZE__ - __G_ATT_HANDLE_SIZE__);

        om = ble_hs_mbuf_from_flat(ptr, toSendAmount);
        if (NULL == om) {
            TOMMROC_DEBUG_E("Error ble_hs_mbuf_from_flat");
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        rc = ble_gattc_indicate_custom((uint16_t) _conn_handle, chrValHandle, om);
        if (0 != rc) {
            TOMMROC_DEBUG_PRINTLN_PLUS_I32(TOMMRO_C_DEBUG_E_LEVEL, "Error ble_gattc_indicate_custom: ", (int32_t) rc);
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(tommRoCMathMax(1, TOMMROC_UNIT_MEASURE_TIME_APPROX_uSEC_TO_mSEC(__WRITE_DELAY_FOR_EVERY_BYTE_uSEC__ * toSendAmount))));

        ptr         += toSendAmount;
        remaining   -= toSendAmount;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

#endif

#endif

#endif
