
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/arm/lowPower/tommRoCTemplateOs_ARM_LowPower.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)
#include "os/arm/lowPower/SiLabs/waitMode/tommRoCTemplateOs_ARM_LowPowerWaitMode.h"
#include "os/arm/lowPower/SiLabs/stopMode/tommRoCTemplateOs_ARM_LowPowerStopMode.h"

#include "os/arm/lowPower/common/tommRoCTemplateOs_ARM_LowPowerCommon.h"

#include "os/arm/lowPower/tommRoCTemplateOs_ARM_TMR.h"
#include "os/arm/RTC/tommRoCTemplateOs_ARM_RTC.h"
#include "os/arm/sysTick/tommRoCTemplateOs_ARM_SysTick.h"

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
#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
static void _rtc_alarm_callback(void) {

    tommRoCTemplateOs_ARM_LowPowerCommonSleepStatusSet();
}
#endif

static tommRoC_err_enum_t _prepare_for_stop(const uint32_t msec) {

#if !defined (__TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__)
    TOMMROC_UTIL_UNUSED_PARAM(msec);
#endif

#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
    const uint32_t toSecond = TOMMROC_UNIT_MEASURE_TIME_APPROX_mSEC_TO_SEC(msec);
    uint32_t criticalSpecificData;
#endif

    tommRoCTemplateOs_ARM_LowPowerCommonSleepStatusReset();

#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsEnterCritical(&criticalSpecificData));

    tommRoCTemplateOs_ARM_RTC_SetAlarmCallback(_rtc_alarm_callback);
    tommRoCTemplateOs_ARM_RTCAlarmInit(toSecond);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsExitCritical(&criticalSpecificData));
#endif

#if defined (__TOMMROC_USE_HW_TIMER_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOs_ARM_TMRInit(msec));
#endif

#if defined (TOMMROC_TEMPLATE_OS__ARM__SYSTICK_IS_USED)
    tommRoCTemplateOs_ARM_SysTickDisable();
#endif

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _restore_from_stop(const uint32_t msec) {

#if !defined (__TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__)
    TOMMROC_UTIL_UNUSED_PARAM(msec);
#endif

#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
    const uint32_t toSecond = TOMMROC_UNIT_MEASURE_TIME_APPROX_mSEC_TO_SEC(msec);
    uint32_t criticalSpecificData;
#endif

#if defined (TOMMROC_TEMPLATE_OS__ARM__SYSTICK_IS_USED)
#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
    tommRoCTemplateOs_ARM_SysTickIncMSec(TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(toSecond));
#endif
#if defined (__TOMMROC_USE_HW_TIMER_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
    tommRoCTemplateOs_ARM_SysTickIncMSec(msec);
#endif
    tommRoCTemplateOs_ARM_SysTickEnable();
#endif

#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsEnterCritical(&criticalSpecificData));

    tommRoCTemplateOs_ARM_RTCAlarmClose();
    tommRoCTemplateOs_ARM_RTC_SetAlarmCallback(NULL);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsExitCritical(&criticalSpecificData));
#endif

#if defined (__TOMMROC_USE_HW_TIMER_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOs_ARM_TMRClose());
#endif

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _stop(void) {

    while (!tommRoCTemplateOs_ARM_LowPowerCommonSleepStatusGet()) {
        TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOs_ARM_LowPowerStopModeEnter());
    }

    return TOMMRO_C_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateOs_ARM_LowPowerWait(void) {

    tommRoC_err_enum_t result;

    tommRoCTemplateOs_ARM_LowPowerWaitModePreEnter();
    result = tommRoCTemplateOs_ARM_LowPowerWaitModeEnter();
    tommRoCTemplateOs_ARM_LowPowerWaitModePostExit();

    return result;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_LowPowerSleep(const uint32_t msec) {

#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
    // Check param input for HW calendar
    const uint32_t toSecond = TOMMROC_UNIT_MEASURE_TIME_APPROX_mSEC_TO_SEC(msec);
#endif

    tommRoC_err_enum_t result;

    if (0 == msec) {
        return TOMMRO_C_ERR_SUCCESS;
    }

#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
    if (0 == toSecond) {
        return TOMMRO_C_ERR_SUCCESS;
    }
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_prepare_for_stop(msec));

    tommRoCTemplateOs_ARM_LowPowerStopModePreEnter();
    result = _stop();
    tommRoCTemplateOs_ARM_LowPowerStopModePostExit();

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_restore_from_stop(msec));

    return result;
}

#endif

#endif
