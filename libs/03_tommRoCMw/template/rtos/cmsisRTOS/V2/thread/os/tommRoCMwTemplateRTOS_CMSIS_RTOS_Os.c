
#if defined (__TOMMROC_MW_USE_THREAD_CMSIS_V2_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_CMSIS_RTOS_Os.h"

#include "rtos/cmsisRTOS/V2/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"
#include "rtos/cmsisRTOS/V2/common/critical/tommRoCMwTemplateRTOS_CMSIS_RTOS_Critical.h"

#include "TOMMROC.h"

#include "rtos/cmsisRTOS/V2/common/CMSIS_RTOS/tommRoCMwTemplateRTOS_cmsis_os.h"

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
#include "rtos/cmsisRTOS/V2/thread/os/freeRTOS/tommRoCMwTemplateRTOS_CMSIS_RTOS_OsFreeRTOS.h"

#if defined (__TOMMROC_MW_ARM_ESP32_RTOS_INTERNAL_TEMPLATE_IS_USED__)
#include "freertos/FreeRTOSConfig.h"
#else
#include "FreeRTOSConfig.h"
#endif
#endif

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
#include "rtos/cmsisRTOS/V2/thread/os/keilRTX/tommRoCMwTemplateRTOS_CMSIS_RTOS_OsKeilRTX.h"

#include "RTX_Conf_CM.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/
#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
#if defined (__TOMMROC_MW_ARM_ESP32_RTOS_INTERNAL_TEMPLATE_IS_USED__)
#if !defined (configTICK_RATE_HZ)
#error "Add configTICK_RATE_HZ to your FreeRTOSConfig.h file"
#endif
#if (1000 != configTICK_RATE_HZ)
#error "configTICK_RATE_HZ MUST be 1000. Config with \"make menuconfig\" command"
#endif
#endif

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_INTERNAL_TEMPLATE_IS_USED__) && (!defined (configTICK_RATE_HZ_VALUE))
#error "Add configTICK_RATE_HZ_VALUE to your FreeRTOSConfig.h file"
#endif

#if defined (__TOMMROC_MW_ARM_ESP32_RTOS_INTERNAL_TEMPLATE_IS_USED__)
#define __OS_KERNEL_SYS_TICK_FREQ__     (configTICK_RATE_HZ)
#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_INTERNAL_TEMPLATE_IS_USED__)
#define __OS_KERNEL_SYS_TICK_FREQ__     (configTICK_RATE_HZ_VALUE)
#endif
#endif

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
#if !defined (OS_CLOCK)
#error "Add OS_CLOCK to your RTX_Conf_CM.h file"
#else
#define __OS_KERNEL_SYS_TICK_FREQ__     (OS_CLOCK)
#endif
#endif

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if (__OS_KERNEL_SYS_TICK_FREQ__ != 1000)
static uint32_t _uptime_factor;
#endif

#if (__OS_KERNEL_SYS_TICK_FREQ__ > 1000)
static uint32_t _u32_max_div_factor;
static uint32_t _u32_max_mod_factor;
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_err_enum_t _delay_msec(const uint32_t msec) {

    uint32_t ticks;

    /**
     * NOTE:
     * as described in "tommRoCOsDelayMsec" function interface, in case of multitasking environment, if delay param is zero, a task yield must be performed.
     */
    if (0 == msec) {
        osThreadYield();
        return TOMMRO_C_ERR_SUCCESS;
    }

    ticks = msec / portTICK_PERIOD_MS;

    if (__CMSIS_RTOS_OS_DELAY_SUCCESS_RESULT__ != osDelay((ticks) ? (ticks) : (1))) {   // Minimum delay = 1 tick
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

#if (1000 == __OS_KERNEL_SYS_TICK_FREQ__)
static uint32_t _get_uptime_msec_no_factor(void) {
    return osKernelGetTickCount();
}
#elif (__OS_KERNEL_SYS_TICK_FREQ__ > 1000)
static uint32_t _get_uptime_msec_div_factor(void) {

    static uint32_t lastSysTick = 0;
    static uint32_t toAddToResult = 0;
    static uint32_t toAddSysTick = 0;

    uint32_t criticalSpecificData;

    uint32_t sysTick;

    uint32_t addToResult;
    uint32_t addSysTick;

    sysTick = osKernelGetTickCount();

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsEnterCritical(&criticalSpecificData));

    if (sysTick < lastSysTick) {

        toAddToResult   += _u32_max_div_factor;
        toAddSysTick    += _u32_max_mod_factor;

        toAddToResult   += (toAddSysTick / _uptime_factor);
        toAddSysTick    = (toAddSysTick % _uptime_factor);
    }

    addToResult = toAddToResult;
    addSysTick  = toAddSysTick;

    lastSysTick = sysTick;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsExitCritical(&criticalSpecificData));

    if (0 == addSysTick) {
        return (sysTick / _uptime_factor) + addToResult;
    }

    if (sysTick < (UINT32_MAX - addSysTick + 1)) {
        return ((sysTick + addSysTick) / _uptime_factor) + addToResult;
    }

    return ((sysTick + addSysTick) / _uptime_factor) + addToResult + _u32_max_div_factor;
}
#else
static uint32_t _get_uptime_msec_mul_factor(void) {
    return osKernelGetTickCount() * _uptime_factor;
}
#endif

static tommRoC_os_get_uptime_msec_funct_t _get_uptime_msec_funct_ptr_and_init_factor(void) {

#if (1000 == __OS_KERNEL_SYS_TICK_FREQ__)
    return _get_uptime_msec_no_factor;
#elif (__OS_KERNEL_SYS_TICK_FREQ__ > 1000)
    _uptime_factor = (uint32_t) osKernelSysTickFrequency / (uint32_t) 1000;

    if ((UINT32_MAX % _uptime_factor) == (_uptime_factor - 1)) {
        _u32_max_div_factor = (UINT32_MAX / _uptime_factor) + 1;
        _u32_max_mod_factor = 0;
    }
    else {
        _u32_max_div_factor = (UINT32_MAX / _uptime_factor);
        _u32_max_mod_factor = (UINT32_MAX % _uptime_factor) + 1;
    }

    return _get_uptime_msec_div_factor;
#else
    _uptime_factor = (uint32_t) 1000 / (uint32_t) osKernelSysTickFrequency;

    return _get_uptime_msec_mul_factor;
#endif
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_OsStart(void) {

    tommRoC_os_get_uptime_msec_funct_t  upTimeFunctPtr;
    tommRoC_os_critical_funct_t         criticalFunct;

    upTimeFunctPtr = _get_uptime_msec_funct_ptr_and_init_factor();

    criticalFunct.enterCritical = tommRoCMwTemplateRTOS_CMSIS_RTOS_CriticalEnter;
    criticalFunct.exitCritical  = tommRoCMwTemplateRTOS_CMSIS_RTOS_CriticalExit;

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__) && (configUSE_TICKLESS_IDLE == 1)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCMwTemplateRTOS_CMSIS_RTOS_Os_FreeRTOSTicklessConfigLPTMRClk());
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsInitDelayMsec(_delay_msec),
            TOMMRO_C_MW_LOW_LEVEL_ERR);

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsInitUptimeMsec(upTimeFunctPtr),
            TOMMRO_C_MW_LOW_LEVEL_ERR);

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsInitCritical(&criticalFunct),
            TOMMRO_C_MW_LOW_LEVEL_ERR);

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_OsStop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsCloseEnv(TOMMRO_C_OS_CRITICAL_FUNCT),
            TOMMRO_C_MW_LOW_LEVEL_ERR);

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsCloseEnv(TOMMRO_C_OS_UPTIME_MSEC_FUNCT),
            TOMMRO_C_MW_LOW_LEVEL_ERR);

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsCloseEnv(TOMMRO_C_OS_DELAY_MSEC_FUNCT),
            TOMMRO_C_MW_LOW_LEVEL_ERR);

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
