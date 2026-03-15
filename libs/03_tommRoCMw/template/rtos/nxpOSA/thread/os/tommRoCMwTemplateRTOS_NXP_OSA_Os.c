
#if defined (__TOMMROC_MW_USE_THREAD_NXP_OSA_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_NXP_OSA_Os.h"

#include "rtos/nxpOSA/common/critical/tommRoCMwTemplateRTOS_NXP_OSA_Critical.h"

#include "TOMMROC.h"

#include "fsl_os_abstraction.h"

#include "rtos/nxpOSA/thread/os/freeRTOS/tommRoCMwTemplateRTOS_NXP_OSA_OsFreeRTOS.h"

#include "FreeRTOSConfig.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#if !defined (configTICK_RATE_HZ_VALUE)
#error "Add configTICK_RATE_HZ_VALUE to your FreeRTOSConfig.h file"
#else
#define __OS_KERNEL_SYS_TICK_FREQ__     (configTICK_RATE_HZ_VALUE)
#endif

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static uint32_t _uptime_correct_factor_msec = 0;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_err_enum_t _delay_msec(const uint32_t msec) {

    /**
     * NOTE:
     * as described in "tommRoCOsDelayMsec" function interface, in case of multitasking environment, if delay param is zero, a task yield must be performed.
     */
    if (0 == msec) {
        OSA_TaskYield();
        return TOMMRO_C_ERR_SUCCESS;
    }

    OSA_TimeDelay(msec);

    return TOMMRO_C_ERR_SUCCESS;
}

static uint32_t _get_uptime_msec(void) {

    return (_uptime_correct_factor_msec + OSA_TimeGetMsec());
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_OsStart(void) {

    tommRoC_os_critical_funct_t criticalFunct;

    criticalFunct.enterCritical = tommRoCMwTemplateRTOS_NXP_OSA_CriticalEnter;
    criticalFunct.exitCritical  = tommRoCMwTemplateRTOS_NXP_OSA_CriticalExit;

#if (configUSE_TICKLESS_IDLE == 1)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCMwTemplateRTOS_NXP_OSA_Os_FreeRTOSTicklessConfigLPTMRClk());
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsInitDelayMsec(_delay_msec),
            TOMMRO_C_MW_LOW_LEVEL_ERR);

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsInitUptimeMsec(_get_uptime_msec),
            TOMMRO_C_MW_LOW_LEVEL_ERR);

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsInitCritical(&criticalFunct),
            TOMMRO_C_MW_LOW_LEVEL_ERR);

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_OsStop(void) {

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

void tommRoCMwTemplateRTOS_NXP_OSA_OsUptimeIncMSec(const uint32_t msec) {

    _uptime_correct_factor_msec += msec;
}

#endif
