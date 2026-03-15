
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/arm/lowPower/tommRoCTemplateOs_ARM_LowPower.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)
#include "os/arm/lowPower/NXP/LLWU/tommRoCTemplateOs_ARM_LowPowerLLWU.h"
#include "os/arm/lowPower/NXP/waitMode/tommRoCTemplateOs_ARM_LowPowerWaitMode.h"
#include "os/arm/lowPower/NXP/stopMode/tommRoCTemplateOs_ARM_LowPowerStopMode.h"

#include "os/arm/lowPower/common/tommRoCTemplateOs_ARM_LowPowerCommon.h"

#include "os/arm/lowPower/tommRoCTemplateOs_ARM_TMR.h"
#include "os/arm/RTC/tommRoCTemplateOs_ARM_RTC.h"
#include "os/arm/sysTick/tommRoCTemplateOs_ARM_SysTick.h"

#include "tommRoCTemplateOs.h"

#include "fsl_common.h"

#if defined (FSL_FEATURE_SOC_RTC_COUNT) && (0 != FSL_FEATURE_SOC_RTC_COUNT)
#include "fsl_rtc.h"
#endif

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
#if defined (FSL_FEATURE_SOC_LLWU_COUNT) && FSL_FEATURE_SOC_LLWU_COUNT
static void _llwu_internal_wakeup_callback(void) {
    tommRoCTemplateOs_ARM_LowPowerCommonSleepStatusSet();
}

static tommRoC_err_enum_t _llwu_init(void) {
    tommRoCTemplateOs_ARM_LowPowerLLWUSetInternalWakeupCallback(_llwu_internal_wakeup_callback);

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateOs_ARM_LowPowerLLWUInit());

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _llwu_close(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateOs_ARM_LowPowerLLWUClose());

    tommRoCTemplateOs_ARM_LowPowerLLWUSetInternalWakeupCallback(NULL);

    return TOMMRO_C_ERR_SUCCESS;

}
#endif

#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_INTERRUPT_BASED_IS_USED)
static void _rtc_alarm_callback(void) {
    tommRoCTemplateOs_ARM_LowPowerCommonSleepStatusSet();
}
#endif
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

#if defined (FSL_FEATURE_SOC_LLWU_COUNT) && FSL_FEATURE_SOC_LLWU_COUNT
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_llwu_init());
#endif

#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsEnterCritical(&criticalSpecificData));

#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_INTERRUPT_BASED_IS_USED)
    RTC_SetAlarmCallback(_rtc_alarm_callback);
#endif

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

#if defined (FSL_FEATURE_SOC_LLWU_COUNT) && FSL_FEATURE_SOC_LLWU_COUNT
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_llwu_close());
#endif

#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsEnterCritical(&criticalSpecificData));

    tommRoCTemplateOs_ARM_RTCAlarmClose();

#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_INTERRUPT_BASED_IS_USED)
    RTC_SetAlarmCallback(NULL);
#endif

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
