
#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/arm/RTC/tommRoCTemplateOs_ARM_RTC.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)

#include "TOMMROC.h"

#include "nrf_drv_rtc.h"
#include "nrf_drv_clock.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_INTERRUPT_BASED_IS_USED)
#define __WAKEUP_INTERVAL_SEC__         (1)
#define __WAKEUP_INTERVAL_MSEC__        (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(__WAKEUP_INTERVAL_SEC__))

#define __CHANNEL_ID_CALENDAR__         (0)
#endif

#define __COMPARE_COUNTERTIME__         (__WAKEUP_INTERVAL_SEC__)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if (defined (RTC_PRESENT) && RTC_COUNT)
static const nrf_drv_rtc_t _rtc = NRF_DRV_RTC_INSTANCE(TOMMROC_TEMPLATE_OS__ARM__RTC_USED_NRF_DRV_RTC_INSTANCE);
#endif

static tommRoC_template_os_arm_rtc_alarm_callback_t _alarm_cb = NULL;
static uint32_t _alarm_interrupt_counter = 0;
static uint32_t _to_reach_alarm_interrupt_counter = 0;

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if (defined (RTC_PRESENT) && RTC_COUNT)
static void _rtc_handler(void) {

    tommRoCSoftCalendarIncSec(__WAKEUP_INTERVAL_SEC__);

    if (NULL == _alarm_cb) {
        return;
    }

    ++_alarm_interrupt_counter;

    if (_to_reach_alarm_interrupt_counter == _alarm_interrupt_counter) {
        _alarm_cb();
    }
}

static void _nrf_drv_rtc_handler(nrf_drv_rtc_int_type_t int_type) {

    if (NRF_DRV_RTC_INT_COMPARE0 == int_type) {

        nrf_rtc_task_trigger(_rtc.p_reg, NRF_RTC_TASK_CLEAR);

        nrf_drv_rtc_cc_set(&_rtc, __CHANNEL_ID_CALENDAR__, __COMPARE_COUNTERTIME__ * 8, true);

        _rtc_handler();
    }
}

static tommRoC_err_enum_t _clock_lfclk_init_check(void) {

    if (!nrf_drv_clock_init_check()) {

        if (NRF_SUCCESS != nrf_drv_clock_init()) {
            return TOMMRO_C_LOW_LEVEL_ERR;
        }
    }

    if (!nrf_drv_clock_lfclk_is_running()) {
        nrf_drv_clock_lfclk_request(NULL);
    }

    return TOMMRO_C_ERR_SUCCESS;
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCInit(void) {

#if (defined (RTC_PRESENT) && RTC_COUNT)

    nrf_drv_rtc_config_t config = NRF_DRV_RTC_DEFAULT_CONFIG;

    // Start the internal LFCLK XTAL oscillator.
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_clock_lfclk_init_check());

    // Uninit to be sure to reset
    nrf_drv_rtc_uninit(&_rtc);

    NVIC_DisableIRQ(TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE);
    NVIC_ClearPendingIRQ(TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE);

    // Initialize RTC instance
    config.prescaler = RTC_FREQ_TO_PRESCALER(8);        // 8 Hz counter frequency
    if (NRFX_SUCCESS != nrf_drv_rtc_init(&_rtc, &config, _nrf_drv_rtc_handler)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    // Enable compare interrupt
    nrf_drv_rtc_int_enable(&_rtc, NRF_RTC_INT_COMPARE0_MASK);

    // Set compare channel to trigger interrupt after COMPARE_COUNTERTIME seconds
    if (NRFX_SUCCESS != nrf_drv_rtc_cc_set(&_rtc, __CHANNEL_ID_CALENDAR__, __COMPARE_COUNTERTIME__ * 8, true)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    // Power on RTC instance
    nrf_drv_rtc_enable(&_rtc);

    return TOMMRO_C_ERR_SUCCESS;

#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCClose(void) {

#if (defined (RTC_PRESENT) && RTC_COUNT)

    uint32_t mask;

    nrf_drv_rtc_disable(&_rtc);

    nrf_drv_rtc_int_disable(&_rtc, &mask);

    NVIC_DisableIRQ(TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE);
    NVIC_ClearPendingIRQ(TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE);

    nrf_drv_rtc_uninit(&_rtc);

    return TOMMRO_C_ERR_SUCCESS;

#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCSetTimestamp(const uint32_t timestamp) {

#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_TIMESTAMP_BASED_IS_USED)
    return tommRoCSoftCalendarSetTimestamp(timestamp);

#elif defined (TOMMROC_TEMPLATE_OS__ARM__RTC_DATE_TIME_BASED_IS_USED)

#else
    TOMMROC_UTIL_UNUSED_PARAM(timestamp);
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

uint32_t tommRoCTemplateOs_ARM_RTCGetTimestamp(void) {

#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_TIMESTAMP_BASED_IS_USED)
    return tommRoCSoftCalendarGetTimestamp();

#elif defined (TOMMROC_TEMPLATE_OS__ARM__RTC_DATE_TIME_BASED_IS_USED)

#else
    return 0;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCSetDateTime(const tommRoC_date_time_t* const dateTimePtr) {

#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_TIMESTAMP_BASED_IS_USED)

    uint32_t timestamp;

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCDateTimeDateTimeToTimestamp(dateTimePtr, &timestamp));

    return tommRoCSoftCalendarSetTimestamp(timestamp);

#elif defined (TOMMROC_TEMPLATE_OS__ARM__RTC_DATE_TIME_BASED_IS_USED)

#else
    TOMMROC_UTIL_UNUSED_PARAM(dateTimePtr);
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCGetDateTime(tommRoC_date_time_t* const dateTimePtr) {

#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_TIMESTAMP_BASED_IS_USED)

    uint32_t timestamp;

    timestamp = tommRoCSoftCalendarGetTimestamp();

    return tommRoCDateTimeTimestampToDateTime(timestamp, dateTimePtr);

#elif defined (TOMMROC_TEMPLATE_OS__ARM__RTC_DATE_TIME_BASED_IS_USED)

#else
    TOMMROC_UTIL_UNUSED_PARAM(dateTimePtr);
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTC_SetAlarmCallback(const tommRoC_template_os_arm_rtc_alarm_callback_t alarmCb) {

    _alarm_cb = alarmCb;

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCAlarmInit(const uint32_t toSecond) {

    TOMMROC_ASSERT_NOT_ZERO(toSecond);

    _alarm_interrupt_counter            = 0;
    _to_reach_alarm_interrupt_counter   = toSecond;

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCAlarmClose(void) {

    _alarm_interrupt_counter            = 0;
    _to_reach_alarm_interrupt_counter   = 0;

    return TOMMRO_C_ERR_SUCCESS;
}

#endif

#endif
