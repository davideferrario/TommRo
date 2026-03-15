
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateOs_ARM_DWT.h"

#include "env/tommRoCTemplateEnv.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static uint32_t _sys_clock_freq_div;
static uint32_t _factor_ratio;
static uint32_t _uptime_usec_result_to_add_calc;

/*******************************************************************************
 * local functions
 ******************************************************************************/
TOMMRO_C_UTIL_STATIC_INLINE_FUNCT uint32_t _get_CYCCNT(void) {

#if defined (DWT)
    return DWT->CYCCNT;
#else
    return 0;
#endif
}

#if defined (DWT)
static void _init_status(void) {

    static uint32_t sysClockFreq;

#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)
    sysClockFreq = SystemCoreClock;
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)
    sysClockFreq = CLOCK_GetFreq(kCLOCK_CoreSysClk);
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)
    sysClockFreq = CMU_ClockFreqGet(cmuClock_CORE);
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)
    sysClockFreq = HAL_RCC_GetSysClockFreq();
#endif

    if (0 == (sysClockFreq % (uint32_t) 1000000)) {
        _sys_clock_freq_div = sysClockFreq / (uint32_t) 1000000;
        _factor_ratio = (uint32_t) 1;
    }
    else if (0 == (sysClockFreq % (uint32_t) 1000)) {
        _sys_clock_freq_div = sysClockFreq / (uint32_t) 1000;
        _factor_ratio = (uint32_t) 1000;
    }
    else {
        _sys_clock_freq_div = TOMMROC_MATH_UINT_DIVIDE_APPROX(sysClockFreq, (uint32_t) 100);
        _factor_ratio = (uint32_t) 10000;
    }

    _uptime_usec_result_to_add_calc = (UINT32_MAX / _sys_clock_freq_div) * _factor_ratio;
    _uptime_usec_result_to_add_calc += TOMMROC_MATH_UINT_DIVIDE_APPROX((UINT32_MAX % _sys_clock_freq_div) * _factor_ratio, _sys_clock_freq_div);
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

bool tommRoCTemplateOs_ARM_DWTIsAvailable(void) {

#if defined (DWT)
    return true;
#else
    return false;
#endif
}

bool tommRoCTemplateOs_ARM_DWTInit(void) {

#if defined (DWT)

    // Disable TRC
    CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk; // ~0x01000000;
    // Enable TRC
    CoreDebug->DEMCR |=  CoreDebug_DEMCR_TRCENA_Msk; // 0x01000000;

    // Disable clock cycle counter
    DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001;
    // Enable  clock cycle counter
    DWT->CTRL |=  DWT_CTRL_CYCCNTENA_Msk; //0x00000001;

    // Reset the clock cycle counter value
    DWT->CYCCNT = 0;

    // 3 NO OPERATION instructions
    __asm("NOP");
    __asm("NOP");
    __asm("NOP");

    // If clock cycle counter not started
    if (0 == DWT->CYCCNT) {
        return false;
    }

    _init_status();

    // Clock cycle counter started
    return true;

#else
    return false;
#endif
}

bool tommRoCTemplateOs_ARM_DWTClose(void) {

#if defined (DWT)

    // Disable clock cycle counter
    DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001;

    // Disable TRC
    CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk; // ~0x01000000;

    // Clock cycle counter started
    return true;
#else
    return false;
#endif
}

uint32_t tommRoCTemplateOs_ARM_DWTGetCYCCNT(void) {
    return _get_CYCCNT();
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_DWTDelayUsec(const uint32_t usec) {

    uint32_t cycles;
    uint32_t start;

    start = _get_CYCCNT();

    if ((uint32_t) 1 == _factor_ratio) {
        cycles = _sys_clock_freq_div * usec;
    }
    else {
        cycles = TOMMROC_MATH_UINT_DIVIDE_APPROX(_sys_clock_freq_div * usec, _factor_ratio);
    }

    if (0 == cycles) {
        return TOMMRO_C_ERR_SUCCESS;
    }

    if  (start <= (UINT32_MAX - 128) - cycles) {
        while ((_get_CYCCNT() - start) < cycles) ;
    }
    else {
        while (tommRoCMathRoundDiffU32(_get_CYCCNT(), start) < cycles) ;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

uint32_t tommRoCTemplateOs_ARM_DWTGetUptimeUsec(void) {

    static uint32_t lastCYCCNT = 0;
    static uint32_t resultToAdd = 0;

    uint32_t now;
    uint32_t result;

    now = _get_CYCCNT();

    if (now < lastCYCCNT) {
        resultToAdd += _uptime_usec_result_to_add_calc;
    }

    lastCYCCNT = now;

    if (now > (UINT32_MAX - _sys_clock_freq_div / 2) / _factor_ratio) {
        result = (now / _sys_clock_freq_div) * _factor_ratio;
        if (((uint32_t) 1 != _factor_ratio) && ((now % _sys_clock_freq_div) > (UINT32_MAX - _sys_clock_freq_div / 2) / _factor_ratio)) {
            result += TOMMROC_MATH_UINT_DIVIDE_APPROX((now % _sys_clock_freq_div) * (_factor_ratio / (uint32_t) 5), _sys_clock_freq_div) * (uint32_t) 5;
        }
        else {
            result += TOMMROC_MATH_UINT_DIVIDE_APPROX((now % _sys_clock_freq_div) * _factor_ratio, _sys_clock_freq_div);
        }
    }
    else {
        result = TOMMROC_MATH_UINT_DIVIDE_APPROX(now * _factor_ratio, _sys_clock_freq_div);
    }

    return result + resultToAdd;
}
#endif
