
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/arm/lowPower/tommRoCTemplateOs_ARM_TMR.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)

#include "os/arm/lowPower/common/tommRoCTemplateOs_ARM_LowPowerCommon.h"

#include "TOMMROC.h"

#include "nrf_drv_rtc.h"
#include "nrf_drv_clock.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __COUNTER_FREQUENCY_HZ__    ((uint32_t) 512)

#define __CHANNEL_ID__              (0)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if (defined (RTC_PRESENT) && RTC_COUNT)
static const nrf_drv_rtc_t _rtc = NRF_DRV_RTC_INSTANCE(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_NRF_DRV_RTC_INSTANCE);
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if (defined (RTC_PRESENT) && RTC_COUNT)
static void _nrf_drv_rtc_handler(nrf_drv_rtc_int_type_t int_type) {

    if (NRF_DRV_RTC_INT_COMPARE0 == int_type) {

        nrf_rtc_task_trigger(_rtc.p_reg, NRF_RTC_TASK_CLEAR);

        tommRoCTemplateOs_ARM_LowPowerCommonSleepStatusSet();
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

tommRoC_err_enum_t tommRoCTemplateOs_ARM_TMRInit(const uint32_t msec) {

#if (defined (RTC_PRESENT) && RTC_COUNT)

    nrf_drv_rtc_config_t config = NRF_DRV_RTC_DEFAULT_CONFIG;
    uint32_t counterVal;

    counterVal = ((msec * __COUNTER_FREQUENCY_HZ__) / (uint32_t) 1000);

    // Start the internal LFCLK XTAL oscillator.
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_clock_lfclk_init_check());

    // Uninit to be sure to reset
    nrf_drv_rtc_uninit(&_rtc);

    NVIC_DisableIRQ(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_IRQn_TYPE);
    NVIC_ClearPendingIRQ(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_IRQn_TYPE);

    // Initialize RTC instance
    config.prescaler = RTC_FREQ_TO_PRESCALER(__COUNTER_FREQUENCY_HZ__);
    if (NRFX_SUCCESS != nrf_drv_rtc_init(&_rtc, &config, _nrf_drv_rtc_handler)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    // Enable compare interrupt
    nrf_drv_rtc_int_enable(&_rtc, NRF_RTC_INT_COMPARE0_MASK);

    // Set compare channel to trigger interrupt after COMPARE_COUNTERTIME seconds
    if (NRFX_SUCCESS != nrf_drv_rtc_cc_set(&_rtc, __CHANNEL_ID__, counterVal, true)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    // Power on RTC instance
    nrf_drv_rtc_enable(&_rtc);

    return TOMMRO_C_ERR_SUCCESS;

#else

    TOMMROC_UTIL_UNUSED_PARAM(msec);

    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_TMRClose(void) {

#if (defined (RTC_PRESENT) && RTC_COUNT)

    uint32_t mask;

    nrf_drv_rtc_disable(&_rtc);

    nrf_drv_rtc_int_disable(&_rtc, &mask);

    NVIC_DisableIRQ(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_IRQn_TYPE);
    NVIC_ClearPendingIRQ(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_IRQn_TYPE);

    nrf_drv_rtc_uninit(&_rtc);

    return TOMMRO_C_ERR_SUCCESS;

#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

#endif

#endif
