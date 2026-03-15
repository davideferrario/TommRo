
#if defined (__TOMMROC_USE_TIME_XC_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateOs.h"

#include "os/tommRoCTemplateOsCritical.h"
#include "os/tommRoCTemplateOsResetCause.h"
#include "os/tommRoCTemplateOsUUID.h"

#include "TOMMROC.h"

#include "mcc.h"
#include <xc.h>
#include <stdint.h>

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
static tommRoC_err_enum_t __delay_msec(const uint32_t msec) {

    uint32_t count;

    for (count = 0; count < msec; ++count) {
        __delay_ms(1);
    }

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _delay_msec(const uint32_t msec) {

    tommRoC_timer_t timer;

    /**
     * NOTE:
     * as described in "tommRoCOsDelayMsec" function interface, in case of NOT multitasking environment, if delay param is zero, function should return SUCCESS result immediately.
     */
    if (0 == msec) {
        return TOMMRO_C_ERR_SUCCESS;
    }

    if (TOMMRO_C_ERR_SUCCESS != tommRoCTimerStart(&timer, msec)) {
        return __delay_msec(msec);        
    }

    while (TOMMRO_C_TIMER_NOT_EXPIRED_ERR == tommRoCTimerIsExpired(&timer)) {

        // Go in sleep with IDLEN = 1 (CPU off; peripheral ON).
        // It's assumed that timer is running with an interrupt PIC peripheral.
        // Check "Doze Idle Features of 8-Bit PIC.pdf" document.
        IDLEN = 1;
        SLEEP();
        Nop();
    }

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _delay_usec(const uint32_t usec) {

    // At 8MHZ                          ->      1MHz
    // Time to enter:   36      usec            288
    // Time to exit:    9       usec            72
    // Time to cycle:   20.45   usec            163,6

    static const uint32_t usecToEnterExit =  (uint32_t)(288000)    / ((uint32_t)_XTAL_FREQ / (uint32_t)1000);
    static const uint32_t usecSingleCycle =  (uint32_t)(72000)     / ((uint32_t)_XTAL_FREQ / (uint32_t)1000);
    static const uint32_t usecToTest =       (uint32_t)(163600)    / ((uint32_t)_XTAL_FREQ / (uint32_t)1000);

    uint32_t count;

    if (usec <= usecToTest) {
        return TOMMRO_C_ERR_SUCCESS;
    }

    for (count = 0; count < usec - usecToTest; count += usecSingleCycle) {
        __delay_us(1);
    }

    return TOMMRO_C_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateOsStart(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsDelayMsecStart());
        
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsDelayUsecStart());
    
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsUptimeMsecStart());

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCriticalStart());

#if defined (__TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsSleepForMsecStart());
#endif

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsStop(void) {

#if defined (__TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsSleepForMsecStop());
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCriticalStop());

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsUptimeMsecStop());

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsDelayUsecStop());
    
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsDelayMsecStop());

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsDelayMsecStart(void) {

    // NOTE: this is needed cause Microchip XC compiler optimization about not used functions.
    tommRoC_os_delay_msec_funct_t functPtr = _delay_msec;

    // If function not used in code, return success.
    if (NULL == functPtr) {
        return TOMMRO_C_ERR_SUCCESS;
    }

    return tommRoCOsInitDelayMsec(_delay_msec);
}

tommRoC_err_enum_t tommRoCTemplateOsDelayUsecStart(void) {

    // NOTE: this is needed cause Microchip XC compiler optimization about not used functions.
    tommRoC_os_delay_usec_funct_t functPtr = _delay_usec;

    // If function not used in code, return success.
    if (NULL == functPtr) {
        return TOMMRO_C_ERR_SUCCESS;
    }

    return tommRoCOsInitDelayUsec(_delay_usec);
}

tommRoC_err_enum_t tommRoCTemplateOsUptimeMsecStart(void) {

    // NOTE: this is needed cause Microchip XC compiler optimization about not used functions.
    tommRoC_os_get_uptime_msec_funct_t functPtr = tommRoCSoftUptimeGetMSec;

    // If function not used in code, return success.
    if (NULL == functPtr) {
        return TOMMRO_C_ERR_SUCCESS;
    }

    return tommRoCOsInitUptimeMsec(tommRoCSoftUptimeGetMSec);
}

tommRoC_err_enum_t tommRoCTemplateOsUptimeUsecStart(void) {
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOsCalendarStart(void) {

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)
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

tommRoC_err_enum_t tommRoCTemplateOsSleepForMsecStart(void) {

#if defined (__TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__)
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsRebootStart(void) {
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}


tommRoC_err_enum_t tommRoCTemplateOsDelayMsecStop(void) {

    // NOTE: this is needed cause Microchip XC compiler optimization about not used functions.
    tommRoC_os_delay_msec_funct_t functPtr = _delay_msec;

    // If function not used in code, return success.
    if (NULL == functPtr) {
        return TOMMRO_C_ERR_SUCCESS;
    }

    return tommRoCOsCloseEnv(TOMMRO_C_OS_DELAY_MSEC_FUNCT);
}

tommRoC_err_enum_t tommRoCTemplateOsDelayUsecStop(void) {

    // NOTE: this is needed cause Microchip XC compiler optimization about not used functions.
    tommRoC_os_delay_usec_funct_t functPtr = _delay_usec;

    // If function not used in code, return success.
    if (NULL == functPtr) {
        return TOMMRO_C_ERR_SUCCESS;
    }

    return tommRoCOsCloseEnv(TOMMRO_C_OS_DELAY_USEC_FUNCT);
}

tommRoC_err_enum_t tommRoCTemplateOsUptimeMsecStop(void) {

    // NOTE: this is needed cause Microchip XC compiler optimization about not used functions.
    tommRoC_os_get_uptime_msec_funct_t functPtr = tommRoCSoftUptimeGetMSec;

    // If function not used in code, return success.
    if (NULL == functPtr) {
        return TOMMRO_C_ERR_SUCCESS;
    }

    return tommRoCOsCloseEnv(TOMMRO_C_OS_UPTIME_MSEC_FUNCT);
}

tommRoC_err_enum_t tommRoCTemplateOsUptimeUsecStop(void) {
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOsCalendarStop(void) {

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsCriticalStop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsCloseEnv(TOMMRO_C_OS_CRITICAL_FUNCT));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCriticalClose());

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsSleepForMsecStop(void) {

#if defined (__TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__)
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsRebootStop(void) {
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

#endif
