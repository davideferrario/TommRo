
#if defined (__TOMMROC_USE_RESET_CAUSE_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/tommRoCTemplateOsResetCause.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)

#include "TOMMROC.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MK22_IS_USED__)
#elif defined (__TOMMROC_TEMPLATE_ARM_NXP_MKWx1Z_IS_USED__)
#elif defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__)
#include "fsl_reset.h"
#elif defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
#endif

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

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_os_reset_cause_enum_t tommRoCTemplateOsResetCause(void) {

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MK22_IS_USED__)
#elif defined (__TOMMROC_TEMPLATE_ARM_NXP_MKWx1Z_IS_USED__)
#elif defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__)
    do { // Added to avoid "warning: unreachable code"
        switch (RESET_GetResetSource()) {

        case kRESET_SrcPowerOn:     return TOMMRO_C_OS_RESET_CAUSE_POWER_ON;
        case kRESET_SrcBrownDown:   return TOMMRO_C_OS_RESET_CAUSE_BROWN_DOWN;
        case kRESET_SrcExternalPin: return TOMMRO_C_OS_RESET_CAUSE_EXTERNAL_PIN;
        case kRESET_SrcWatchDog:    return TOMMRO_C_OS_RESET_CAUSE_WATCHDOG;
        case kRESET_SrcLockUp:      return TOMMRO_C_OS_RESET_CAUSE_LOCK_UP;
        case kRESET_SrcReboot:      return TOMMRO_C_OS_RESET_CAUSE_REBOOT;
        case kRESET_SrcCpuSystem:   return TOMMRO_C_OS_RESET_CAUSE_CPU_SYSTEM;
        case kRESET_SrcWakeUp:      return TOMMRO_C_OS_RESET_CAUSE_WAKE_UP;
        case kRESET_SrcCpuSoftware: return TOMMRO_C_OS_RESET_CAUSE_CPU_SOFTWARE;

        default:
            // If here, error!!!
            TOMMROC_ASSERT_TRUE(false);
            break;
        }
    } while (0);
#elif defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
#endif

    return TOMMRO_C_OS_RESET_CAUSE_UNKNOWN;
}

tommRoC_err_enum_t tommRoCTemplateOsClearResetCause(void) {

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MK22_IS_USED__)
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#elif defined (__TOMMROC_TEMPLATE_ARM_NXP_MKWx1Z_IS_USED__)
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#elif defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__)
    RESET_ClearResetSource();
    return TOMMRO_C_ERR_SUCCESS;
#elif defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

#endif

#endif
