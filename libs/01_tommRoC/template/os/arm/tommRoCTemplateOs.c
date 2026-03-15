
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateOs.h"

#include "os/tommRoCTemplateOsCritical.h"
#include "os/tommRoCTemplateOsIsFromISR.h"
#include "os/tommRoCTemplateOsResetCause.h"
#include "os/tommRoCTemplateOsUUID.h"

#include "env/tommRoCTemplateEnv.h"

#include "os/arm/DWT/tommRoCTemplateOs_ARM_DWT.h"
#include "os/arm/lowPower/tommRoCTemplateOs_ARM_LowPower.h"
#include "os/arm/RTC/tommRoCTemplateOs_ARM_RTC.h"
#include "os/arm/sysTick/tommRoCTemplateOs_ARM_SysTick.h"

#include "TOMMROC.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_err_enum_t _delay_msec(const uint32_t msec) {

    /**
     * NOTE:
     * as described in "tommRoCOsDelayMsec" function interface, in case of NOT multitasking environment, if delay param is zero, function should return SUCCESS result immediately.
     */
    if (0 == msec) {
        return TOMMRO_C_ERR_SUCCESS;
    }

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)
    HAL_Delay(msec);
#endif

#if defined (TOMMROC_TEMPLATE_OS__ARM__SYSTICK_IS_USED)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOs_ARM_SysTickDelayMsec(msec));
#endif

    return TOMMRO_C_ERR_SUCCESS;
}

static uint32_t _get_uptime_msec(void) {

    uint32_t result = 0;

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)
    result = HAL_GetTick();

#elif defined (TOMMROC_TEMPLATE_OS__ARM__SYSTICK_IS_USED)
    result = tommRoCTemplateOs_ARM_SysTickGetUptimeMsec();

#else
    // If here, ERROR!!!
    TOMMROC_ASSERT_TRUE(false);
#endif

    return result;
}

#if defined (DWT)
static tommRoC_err_enum_t _delay_usec(const uint32_t usec) {

    return tommRoCTemplateOs_ARM_DWTDelayUsec(usec);
}

static uint32_t _get_uptime_usec(void) {

    uint32_t criticalSpecificData;

    uint32_t result;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsEnterCritical(&criticalSpecificData));
    result = tommRoCTemplateOs_ARM_DWTGetUptimeUsec();
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsExitCritical(&criticalSpecificData));

    return result;
}

static uint32_t _get_hard_clock(void) {

    return tommRoCTemplateOs_ARM_DWTGetCYCCNT();
}
#endif

#if defined (__TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__)
static tommRoC_err_enum_t _sleep_for_msec(const uint32_t msec) {

    return tommRoCTemplateOs_ARM_LowPowerSleep(msec);
}
#endif

static tommRoC_err_enum_t _reboot(void) {

    uint32_t criticalSpecificData;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsEnterCritical(&criticalSpecificData));
    NVIC_SystemReset();

    // We should never get here
    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _start_up_delay_msec(void) {

#if defined (TOMMROC_TEMPLATE_OS__ARM__SYSTICK_IS_USED)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOs_ARM_SysTickInit());
#endif

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _stop_delay_msec(void) {

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)
    HAL_SuspendTick();
#endif

#if defined (TOMMROC_TEMPLATE_OS__ARM__SYSTICK_IS_USED)
    tommRoCTemplateOs_ARM_SysTickClose();
#endif

    return TOMMRO_C_ERR_SUCCESS;
}

#if defined (DWT)
static tommRoC_err_enum_t _start_up_delay_usec(void) {

    if (!tommRoCTemplateOs_ARM_DWTInit()) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _stop_delay_usec(void) {

    if (!tommRoCTemplateOs_ARM_DWTClose()) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)
#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_TIMESTAMP_BASED_IS_USED)
static tommRoC_err_enum_t _hw_calendar_timestamp_based_start(void) {

    tommRoC_os_timestamp_funct_init_t timestampFunctInit;

    timestampFunctInit.setTimestamp = tommRoCTemplateOs_ARM_RTCSetTimestamp;
    timestampFunctInit.getTimestamp = tommRoCTemplateOs_ARM_RTCGetTimestamp;
    timestampFunctInit.minValidYear = TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_MIN_VALID_YEAR;
    timestampFunctInit.maxValidYear = TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_MAX_VALID_YEAR;

    return tommRoCOsInitTimestamp(&timestampFunctInit);
}
#endif

#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_DATE_TIME_BASED_IS_USED)
static tommRoC_err_enum_t _hw_calendar_date_time_based_start(void) {

    tommRoC_os_date_time_funct_init_t dateTimeFunctInit;

    dateTimeFunctInit.setDateTime   = tommRoCTemplateOs_ARM_RTCSetDateTime;
    dateTimeFunctInit.getDateTime   = tommRoCTemplateOs_ARM_RTCGetDateTime;
    dateTimeFunctInit.minValidYear  = TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_MIN_VALID_YEAR;
    dateTimeFunctInit.maxValidYear  = TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_MAX_VALID_YEAR;

    return tommRoCOsInitDateTime(&dateTimeFunctInit);
}
#endif

static tommRoC_err_enum_t _hw_calendar_start(void) {

#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_NOT_AVAILABLE)
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#else

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOs_ARM_RTCInit());

#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_TIMESTAMP_BASED_IS_USED)
    return _hw_calendar_timestamp_based_start();
#endif

#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_DATE_TIME_BASED_IS_USED)
    return _hw_calendar_date_time_based_start();
#endif

    // If here, ERROR!!!
    TOMMROC_ASSERT_TRUE(false);

    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

static tommRoC_err_enum_t _hw_calendar_stop(void) {

#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_NOT_AVAILABLE)
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#else

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOs_ARM_RTCClose());

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsCloseEnv(TOMMRO_C_OS_TIMESTAMP_FUNCT));
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsCloseEnv(TOMMRO_C_OS_DATE_TIME_FUNCT));

    return TOMMRO_C_ERR_SUCCESS;
#endif
}
#endif

#if defined (__TOMMROC_USE_SOFT_CALENDAR_OS_TEMPLATE__)
static tommRoC_err_enum_t _sw_calendar_start(void) {

    tommRoC_os_timestamp_funct_init_t timestampFunctInit;

    timestampFunctInit.setTimestamp = tommRoCSoftCalendarSetTimestamp;
    timestampFunctInit.getTimestamp = tommRoCSoftCalendarGetTimestamp;
    timestampFunctInit.minValidYear = TOMMROC_SOFT_CALENDAR_MIN_VALID_YEAR;
    timestampFunctInit.maxValidYear = TOMMROC_SOFT_CALENDAR_MAX_VALID_YEAR;

    return tommRoCOsInitTimestamp(&timestampFunctInit);
}

static tommRoC_err_enum_t _sw_calendar_stop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsCloseEnv(TOMMRO_C_OS_TIMESTAMP_FUNCT));

    return TOMMRO_C_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)
static tommRoC_err_enum_t _clock_init(void) {

    if (!nrf_drv_clock_init_check()) {

        if (NRF_SUCCESS != nrf_drv_clock_init()) {
            return TOMMRO_C_LOW_LEVEL_ERR;
        }
    }

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _clock_uninit(void) {

    if (nrf_drv_clock_init_check()) {
        nrf_drv_clock_uninit();
    }

    return TOMMRO_C_ERR_SUCCESS;
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateOsStart(void) {

#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_clock_init());
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsDelayMsecStart());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsDelayUsecStart());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsUptimeMsecStart());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsUptimeUsecStart());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsHardClockStart());

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__) || defined (__TOMMROC_USE_SOFT_CALENDAR_OS_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCalendarStart());
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCriticalStart());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsIsFromISRStart());

#if defined (__TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsSleepForMsecStart());
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsRebootStart());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsGetUUIDStart());

#if defined (__TOMMROC_USE_RESET_CAUSE_OS_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsResetCauseStart());
#endif

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsStop(void) {

#if defined (__TOMMROC_USE_RESET_CAUSE_OS_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsResetCauseStop());
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsGetUUIDStop());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsRebootStop());

#if defined (__TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsSleepForMsecStop());
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCriticalStop());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsIsFromISRStop());

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__) || defined (__TOMMROC_USE_SOFT_CALENDAR_OS_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCalendarStop());
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsHardClockStop());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsUptimeUsecStop());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsUptimeMsecStop());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsDelayUsecStop());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsDelayMsecStop());

#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_clock_uninit());
#endif

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsDelayMsecStart(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_start_up_delay_msec());

    return tommRoCOsInitDelayMsec(_delay_msec);
}

tommRoC_err_enum_t tommRoCTemplateOsDelayUsecStart(void) {

#if defined (DWT)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_start_up_delay_usec());

    return tommRoCOsInitDelayUsec(_delay_usec);
#else
    return TOMMRO_C_ERR_SUCCESS;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsUptimeMsecStart(void) {
    return tommRoCOsInitUptimeMsec(_get_uptime_msec);
}

tommRoC_err_enum_t tommRoCTemplateOsUptimeUsecStart(void) {

#if defined (DWT)
    return tommRoCOsInitUptimeUsec(_get_uptime_usec);
#else
    return TOMMRO_C_ERR_SUCCESS;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsHardClockStart(void) {

#if defined (DWT)
    return tommRoCOsInitHardClock(_get_hard_clock);
#else
    return TOMMRO_C_ERR_SUCCESS;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsCalendarStart(void) {

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)
    return _hw_calendar_start();
#elif defined (__TOMMROC_USE_SOFT_CALENDAR_OS_TEMPLATE__)
    return _sw_calendar_start();
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsCriticalStart(void) {

    tommRoC_os_critical_funct_t criticalFunct;

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCriticalInit());

    criticalFunct.enterCritical = tommRoCTemplateOsCriticalEnter;
    criticalFunct.exitCritical  = tommRoCTemplateOsCriticalExit;

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsInitCritical(&criticalFunct));

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsIsFromISRStart(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsIsFromISRInit());

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsInitIsFromISR(tommRoCTemplateOsIsFromISR));

    return TOMMRO_C_ERR_SUCCESS;
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
    return tommRoCOsInitGetUUID(tommRoCTemplateOsUUIDGet);
}

tommRoC_err_enum_t tommRoCTemplateOsResetCauseStart(void) {

#if defined (__TOMMROC_USE_RESET_CAUSE_OS_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsInitResetCause(tommRoCTemplateOsResetCause));
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsInitClearResetCause(tommRoCTemplateOsClearResetCause));
    return TOMMRO_C_ERR_SUCCESS;
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}


tommRoC_err_enum_t tommRoCTemplateOsDelayMsecStop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsCloseEnv(TOMMRO_C_OS_DELAY_MSEC_FUNCT));

    return _stop_delay_msec();
}

tommRoC_err_enum_t tommRoCTemplateOsDelayUsecStop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsCloseEnv(TOMMRO_C_OS_DELAY_USEC_FUNCT));

#if defined (DWT)
    return _stop_delay_usec();
#else
    return TOMMRO_C_ERR_SUCCESS;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsUptimeMsecStop(void) {
    return tommRoCOsCloseEnv(TOMMRO_C_OS_UPTIME_MSEC_FUNCT);
}

tommRoC_err_enum_t tommRoCTemplateOsUptimeUsecStop(void) {
    return tommRoCOsCloseEnv(TOMMRO_C_OS_UPTIME_USEC_FUNCT);
}

tommRoC_err_enum_t tommRoCTemplateOsHardClockStop(void) {
    return tommRoCOsCloseEnv(TOMMRO_C_OS_HARD_CLOCK_FUNCT);
}

tommRoC_err_enum_t tommRoCTemplateOsCalendarStop(void) {

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)
    return _hw_calendar_stop();
#elif defined (__TOMMROC_USE_SOFT_CALENDAR_OS_TEMPLATE__)
    return _sw_calendar_stop();
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsCriticalStop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsCloseEnv(TOMMRO_C_OS_CRITICAL_FUNCT));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCriticalClose());

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsIsFromISRStop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsCloseEnv(TOMMRO_C_OS_IS_FROM_ISR_FUNCT));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsIsFromISRClose());

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsSleepForMsecStop(void) {
    return tommRoCOsCloseEnv(TOMMRO_C_OS_SLEEP_FOR_MSEC_FUNCT);
}

tommRoC_err_enum_t tommRoCTemplateOsRebootStop(void) {
    return tommRoCOsCloseEnv(TOMMRO_C_OS_REBOOT_FUNCT);
}

tommRoC_err_enum_t tommRoCTemplateOsGetUUIDStop(void) {
    return tommRoCOsCloseEnv(TOMMRO_C_OS_GET_UUID_FUNCT);
}

tommRoC_err_enum_t tommRoCTemplateOsResetCauseStop(void) {
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsCloseEnv(TOMMRO_C_OS_RESET_CAUSE_FUNCT));
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsCloseEnv(TOMMRO_C_OS_CLEAR_RESET_CAUSE_FUNCT));
    return TOMMRO_C_ERR_SUCCESS;
}

#endif
