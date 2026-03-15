
#if defined (__TOMMROC_USE_TIME_ESP32_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateOs.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)

#include "sdkconfig.h"

#include "env/tommRoCTemplateEnv.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/timer.h"

#if (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
#include "soc/timer_periph.h"
#endif

#include "soc/timer_group_struct.h"

#include "esp_mac.h"

#include "esp_timer.h"

#include "esp_system.h"
#include <esp_wifi.h>

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
#include "esp32/rom/ets_sys.h"
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
#include "rom/ets_sys.h"
#if (3 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MINOR)
#include "soc/timer_periph.h"
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MINOR)
#include "soc/wdt_periph.h"
#endif
#endif

#include "nvs_flash.h"

#include "time.h"
#include <sys/time.h>

#include <stdint.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#if !defined (CONFIG_IDF_TARGET_ESP32C5) && !defined (CONFIG_IDF_TARGET_ESP32C6)
#define __HARD_CLOCK_AVAILABLE__
#endif

#define __RTC_CALENDAR_MIN_VALID_YEAR__             ((uint16_t) 1970)
#define __RTC_CALENDAR_MAX_VALID_YEAR__             ((uint16_t) 2038)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static portMUX_TYPE _wdt_mux = portMUX_INITIALIZER_UNLOCKED;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_err_enum_t _delay_usec(const uint32_t usec) {
    ets_delay_us(usec);
    return TOMMRO_C_ERR_SUCCESS;
}

static uint32_t _get_uptime_usec(void) {
    return (uint32_t) esp_timer_get_time();
}

#if defined (__HARD_CLOCK_AVAILABLE__)
static uint32_t _get_hard_clock(void) {
    return xthal_get_ccount();
}
#endif

#if defined (__TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__)
static tommRoC_err_enum_t _sleep_for_msec(const uint32_t msec) {
}
#endif

static tommRoC_err_enum_t _reboot(void) {

    esp_restart();

    // We should never get here
    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _UUID_get(
                void*       const   uuidBufferPtr,
        const   uint8_t             uuidBufferSize,
                uint8_t*    const   uuidBufferLenPtr) {

    uint8_t eth_mac[6];

    TOMMROC_CTA_EQUALS(sizeof(eth_mac), TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE);

    TOMMROC_ASSERT_MORE_OR_EQUALS_THAN(uuidBufferSize, TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE);

    TOMMROC_PARAM_CHECK_ON_TEST_RETURN_ERR(uuidBufferSize, <, TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE);

    if (ESP_OK != esp_read_mac(eth_mac, ESP_MAC_ETH)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(uuidBufferPtr, eth_mac, TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE));

    *uuidBufferLenPtr = TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE;

    return TOMMRO_C_ERR_SUCCESS;
}

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)
static tommRoC_err_enum_t _set_timestamp(const uint32_t timestamp) {

    struct timeval tv;

    tv.tv_sec   = (time_t) timestamp;
    tv.tv_usec  = (suseconds_t) 0;

    if (0 != settimeofday(&tv, NULL)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

static uint32_t _get_timestamp(void) {

    struct timeval tv;

    if (0 != gettimeofday(&tv, NULL)) {
        return 0;
    }

    return (uint32_t) tv.tv_sec;
}
#endif

static void _disable_wdt(void) {

    portENTER_CRITICAL(&_wdt_mux);

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    TIMERG0.wdt_wprotect    = TIMG_WDT_WKEY_VALUE;  // Disable write protection
    TIMERG0.wdt_config0.en  = 0;                    // Disable WDT
    TIMERG0.wdt_wprotect    = 0;                    // Enable write protection
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    TIMERG0.wdtwprotect.wdt_wkey    = TIMG_WDT_WKEY_VALUE;  // Disable write protection
    TIMERG0.wdtconfig0.wdt_en       = 0;                    // Disable WDT
    TIMERG0.wdtwprotect.wdt_wkey    = 0;                    // Enable write protection
#endif

    portEXIT_CRITICAL(&_wdt_mux);
}

static void _enable_wdt(void) {

    portENTER_CRITICAL(&_wdt_mux);

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    TIMERG0.wdt_wprotect    = TIMG_WDT_WKEY_VALUE;  // Disable write protection
    TIMERG0.wdt_config0.en  = 1;                    // Enable timer
    TIMERG0.wdt_feed        = 1;                    // Reset timer
    TIMERG0.wdt_wprotect    = 0;                    // Enable write protection
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
    TIMERG0.wdtwprotect.wdt_wkey    = TIMG_WDT_WKEY_VALUE;  // Disable write protection
    TIMERG0.wdtconfig0.wdt_en       = 1;                    // Enable timer
    TIMERG0.wdtfeed.wdt_feed        = 1;                    // Reset timer
    TIMERG0.wdtwprotect.wdt_wkey    = 0;                    // Enable write protection
#endif

    portEXIT_CRITICAL(&_wdt_mux);
}

static tommRoC_err_enum_t _nvs_flash_start(void) {

    esp_err_t ret;

    // Initialize NVS.
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NOTE: used "vTaskDelay" because tommRo delay libraries are still not started.
        vTaskDelay(10 / portTICK_PERIOD_MS);
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    return ((ESP_OK == ret) ? (TOMMRO_C_ERR_SUCCESS) : (TOMMRO_C_LOW_LEVEL_ERR));
}

static tommRoC_err_enum_t _nvs_flash_stop(void) {
    ESP_ERROR_CHECK(nvs_flash_deinit());
    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _os_wdt_start(void) {

    tommRoC_os_wdt_funct_t wdtFunct;

    wdtFunct.disableWDT = _disable_wdt;
    wdtFunct.enableWDT  = _enable_wdt;

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsInitWDT(&wdtFunct));

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _os_wdt_stop(void) {

    return tommRoCOsCloseEnv(TOMMRO_C_OS_WDT_FUNCT);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateOsStart(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_nvs_flash_start());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_os_wdt_start());

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsDelayUsecStart());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsUptimeUsecStart());
#if defined (__HARD_CLOCK_AVAILABLE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsHardClockStart());
#endif

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCalendarStart());
#endif

#if defined (__TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsSleepForMsecStart());
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsRebootStart());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsGetUUIDStart());

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsStop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsGetUUIDStop());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsRebootStop());

#if defined (__TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsSleepForMsecStop());
#endif

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCalendarStop());
#endif

#if defined (__HARD_CLOCK_AVAILABLE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsHardClockStop());
#endif
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsUptimeUsecStop());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsDelayUsecStop());

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_os_wdt_stop());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_nvs_flash_stop());

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsDelayMsecStart(void) {
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOsDelayUsecStart(void) {
    return tommRoCOsInitDelayUsec(_delay_usec);
}

tommRoC_err_enum_t tommRoCTemplateOsUptimeMsecStart(void) {
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOsUptimeUsecStart(void) {
    return tommRoCOsInitUptimeUsec(_get_uptime_usec);
}

tommRoC_err_enum_t tommRoCTemplateOsHardClockStart(void) {
#if defined (__HARD_CLOCK_AVAILABLE__)
    return tommRoCOsInitHardClock(_get_hard_clock);
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsCalendarStart(void) {

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)

    tommRoC_os_timestamp_funct_init_t timeStampFunctInit;

    timeStampFunctInit.setTimestamp = _set_timestamp;
    timeStampFunctInit.getTimestamp = _get_timestamp;
    timeStampFunctInit.minValidYear = __RTC_CALENDAR_MIN_VALID_YEAR__;
    timeStampFunctInit.maxValidYear = __RTC_CALENDAR_MAX_VALID_YEAR__;

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsInitTimestamp(&timeStampFunctInit));

    return TOMMRO_C_ERR_SUCCESS;
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsCriticalStart(void) {
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOsIsFromISRStart(void) {
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOsSleepForMsecStart(void) {

#if defined (__TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__)
    return tommRoCOsInitSleepForMsec(_sleep_for_msec);
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsRebootStart(void) {
    return tommRoCOsInitReboot(_reboot);
}

tommRoC_err_enum_t tommRoCTemplateOsGetUUIDStart(void) {
    return tommRoCOsInitGetUUID(_UUID_get);
}


tommRoC_err_enum_t tommRoCTemplateOsDelayMsecStop(void) {
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOsDelayUsecStop(void) {
    return tommRoCOsCloseEnv(TOMMRO_C_OS_DELAY_USEC_FUNCT);
}

tommRoC_err_enum_t tommRoCTemplateOsUptimeMsecStop(void) {
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOsUptimeUsecStop(void) {
    return tommRoCOsCloseEnv(TOMMRO_C_OS_UPTIME_USEC_FUNCT);
}

tommRoC_err_enum_t tommRoCTemplateOsHardClockStop(void) {
#if defined (__HARD_CLOCK_AVAILABLE__)
    return tommRoCOsCloseEnv(TOMMRO_C_OS_HARD_CLOCK_FUNCT);
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsCalendarStop(void) {

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsCloseEnv(TOMMRO_C_OS_TIMESTAMP_FUNCT));

    return TOMMRO_C_ERR_SUCCESS;
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsCriticalStop(void) {
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOsIsFromISRStop(void) {
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOsSleepForMsecStop(void) {

#if defined (__TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__)
    return tommRoCOsCloseEnv(TOMMRO_C_OS_SLEEP_FOR_MSEC_FUNCT);
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsRebootStop(void) {
    return tommRoCOsCloseEnv(TOMMRO_C_OS_REBOOT_FUNCT);
}

tommRoC_err_enum_t tommRoCTemplateOsGetUUIDStop(void) {
    return tommRoCOsCloseEnv(TOMMRO_C_OS_GET_UUID_FUNCT);
}

#endif

#endif
