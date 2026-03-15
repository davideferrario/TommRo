
#if defined (__TOMMROC_MW_USE_THREAD_THREADX_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_ThreadX_Os.h"

#include "rtos/threadX/common/critical/tommRoCMwTemplateRTOS_ThreadX_Critical.h"

#include "TOMMROC.h"

#include "tx_api.h"
#include "tx_thread.h"

#include "tx_user.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#if !defined (TX_TIMER_TICKS_PER_SECOND)
#error "Add TX_TIMER_TICKS_PER_SECOND to your tx_user.h file"
#endif
#if (TX_TIMER_TICKS_PER_SECOND < 1000)
#warning "for a better resolution it is suggested to use TX_TIMER_TICKS_PER_SECOND MUST >= 1000"
#endif

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if (TX_TIMER_TICKS_PER_SECOND != 1000)
static uint32_t _uptime_factor;
#endif

#if (TX_TIMER_TICKS_PER_SECOND > 1000)
static uint32_t _u32_max_div_factor;
static uint32_t _u32_max_mod_factor;
#endif

static uint32_t _uptime_correct_factor_msec = 0;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static ULONG _msec_to_timer_ticks(const uint32_t msec) {

    ULONG res;

    res = TOMMROC_UNIT_MEASURE_TIME_APPROX_mSEC_TO_SEC((ULONG) msec * TX_TIMER_TICKS_PER_SECOND);

    return (0 == res) ? (1) : (res);
}

#if (1000 == TX_TIMER_TICKS_PER_SECOND)
static uint32_t _get_uptime_msec_no_factor(void) {
    return (_uptime_correct_factor_msec + (uint32_t) tx_time_get());
}
#elif (TX_TIMER_TICKS_PER_SECOND > 1000)
static uint32_t _get_uptime_msec_div_factor(void) {

    static uint32_t lastSysTick = 0;
    static uint32_t toAddToResult = 0;
    static uint32_t toAddSysTick = 0;

    uint32_t criticalSpecificData;

    uint32_t sysTick;

    uint32_t addToResult;
    uint32_t addSysTick;

    sysTick = (uint32_t) tx_time_get();

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
        return (_uptime_correct_factor_msec + (sysTick / _uptime_factor) + addToResult);
    }

    if (sysTick < (UINT32_MAX - addSysTick + 1)) {
        return (_uptime_correct_factor_msec + ((sysTick + addSysTick) / _uptime_factor) + addToResult);
    }

    return (_uptime_correct_factor_msec + ((sysTick + addSysTick) / _uptime_factor) + addToResult + _u32_max_div_factor);
}
#else
static uint32_t _get_uptime_msec_mul_factor(void) {
    return (_uptime_correct_factor_msec + ((uint32_t) tx_time_get() * _uptime_factor));
}
#endif

static tommRoC_err_enum_t _delay_msec(const uint32_t msec) {

    /**
     * NOTE:
     * as described in "tommRoCOsDelayMsec" function interface, in case of multitasking environment, if delay param is zero, a task yield must be performed.
     */
    if (0 == msec) {
        tx_thread_relinquish();
        return TOMMRO_C_ERR_SUCCESS;
    }

    if (TX_SUCCESS != tx_thread_sleep(_msec_to_timer_ticks(msec))) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_os_get_uptime_msec_funct_t _get_uptime_msec_funct_ptr_and_init_factor(void) {

#if (1000 == TX_TIMER_TICKS_PER_SECOND)
    return _get_uptime_msec_no_factor;
#elif (TX_TIMER_TICKS_PER_SECOND > 1000)
    _uptime_factor = (uint32_t) TOMMROC_MATH_UINT_DIVIDE_APPROX((uint32_t) TX_TIMER_TICKS_PER_SECOND, (uint32_t) 1000);

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
    _uptime_factor = (uint32_t) TOMMROC_MATH_UINT_DIVIDE_APPROX((uint32_t) TOMMROC_UNIT_MEASURE_TIME_mSEC_IN_A_SEC, (uint32_t) TX_TIMER_TICKS_PER_SECOND);

    return _get_uptime_msec_mul_factor;
#endif
}

static tommRoC_err_enum_t _is_from_isr(bool* const isFromISRPtr) {
    *isFromISRPtr = (((ULONG) 0) != TX_THREAD_GET_SYSTEM_STATE());
    return TOMMRO_C_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_OsStart(void) {

    tommRoC_os_get_uptime_msec_funct_t  upTimeFunctPtr;
    tommRoC_os_critical_funct_t         criticalFunct;

    upTimeFunctPtr = _get_uptime_msec_funct_ptr_and_init_factor();

    criticalFunct.enterCritical = tommRoCMwTemplateRTOS_ThreadX_CriticalEnter;
    criticalFunct.exitCritical  = tommRoCMwTemplateRTOS_ThreadX_CriticalExit;

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsInitDelayMsec(_delay_msec),
            TOMMRO_C_MW_LOW_LEVEL_ERR);

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsInitUptimeMsec(upTimeFunctPtr),
            TOMMRO_C_MW_LOW_LEVEL_ERR);

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsInitCritical(&criticalFunct),
            TOMMRO_C_MW_LOW_LEVEL_ERR);
            
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsInitIsFromISR(_is_from_isr),
            TOMMRO_C_MW_LOW_LEVEL_ERR);

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_OsStop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsCloseEnv(TOMMRO_C_OS_IS_FROM_ISR_FUNCT),
            TOMMRO_C_MW_LOW_LEVEL_ERR);
            
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

void tommRoCMwTemplateRTOS_ThreadX_OsUptimeIncMSec(const uint32_t msec) {

    _uptime_correct_factor_msec += msec;
}

#endif
