
#if defined (__TOMMROC_USE_RESET_CAUSE_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/tommRoCTemplateOsResetCause.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)

#include "TOMMROC.h"

#include "em_rmu.h"

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

#if (defined(RMU_COUNT) && (RMU_COUNT > 0))

    uint32_t resetCauseMask;

    // NOTE: reset cause is a mask of reset cause
    resetCauseMask = RMU_ResetCauseGet();

#if defined (RMU_RSTCAUSE_PORST)
    if (resetCauseMask & RMU_RSTCAUSE_PORST) {
        return TOMMRO_C_OS_RESET_CAUSE_POWER_ON;
    }
#endif

#if defined (RMU_RSTCAUSE_BODUNREGRST)
    if (resetCauseMask & RMU_RSTCAUSE_BODUNREGRST) {
        return TOMMRO_C_OS_RESET_CAUSE_BROWN_DOWN;
    }
#endif

#if defined (RMU_RSTCAUSE_BODREGRST)
    if (resetCauseMask & RMU_RSTCAUSE_BODREGRST) {
        return TOMMRO_C_OS_RESET_CAUSE_BROWN_DOWN;
    }
#endif

#if defined (RMU_RSTCAUSE_AVDDBOD)
    if (resetCauseMask & RMU_RSTCAUSE_AVDDBOD) {
        return TOMMRO_C_OS_RESET_CAUSE_BROWN_DOWN;
    }
#endif

#if defined (RMU_RSTCAUSE_DVDDBOD)
    if (resetCauseMask & RMU_RSTCAUSE_DVDDBOD) {
        return TOMMRO_C_OS_RESET_CAUSE_BROWN_DOWN;
    }
#endif

#if defined (RMU_RSTCAUSE_DECBOD)
    if (resetCauseMask & RMU_RSTCAUSE_DECBOD) {
        return TOMMRO_C_OS_RESET_CAUSE_BROWN_DOWN;
    }
#endif

#if defined (RMU_RSTCAUSE_EXTRST)
    if (resetCauseMask & RMU_RSTCAUSE_EXTRST) {
        return TOMMRO_C_OS_RESET_CAUSE_EXTERNAL_PIN;
    }
#endif

#if defined (RMU_RSTCAUSE_WDOGRST)
    if (resetCauseMask & RMU_RSTCAUSE_WDOGRST) {
        return TOMMRO_C_OS_RESET_CAUSE_WATCHDOG;
    }
#endif

#if defined (RMU_RSTCAUSE_LOCKUPRST)
    if (resetCauseMask & RMU_RSTCAUSE_LOCKUPRST) {
        return TOMMRO_C_OS_RESET_CAUSE_LOCK_UP;
    }
#endif

#if defined (RMU_RSTCAUSE_SYSREQRST)
    if (resetCauseMask & RMU_RSTCAUSE_SYSREQRST) {
        return TOMMRO_C_OS_RESET_CAUSE_CPU_SYSTEM;
    }
#endif

#if defined (RMU_RSTCAUSE_EM4RST)
    if (resetCauseMask & RMU_RSTCAUSE_EM4RST) {
        return TOMMRO_C_OS_RESET_CAUSE_WAKE_UP;
    }
#endif

#if defined (RMU_RSTCAUSE_EM4WURST)
    if (resetCauseMask & RMU_RSTCAUSE_EM4WURST) {
        return TOMMRO_C_OS_RESET_CAUSE_WAKE_UP;
    }
#endif

#if defined (RMU_RSTCAUSE_BODAVDD0)
    if (resetCauseMask & RMU_RSTCAUSE_BODAVDD0) {
        return TOMMRO_C_OS_RESET_CAUSE_BROWN_DOWN;
    }
#endif

#if defined (RMU_RSTCAUSE_BODAVDD1)
    if (resetCauseMask & RMU_RSTCAUSE_BODAVDD1) {
        return TOMMRO_C_OS_RESET_CAUSE_BROWN_DOWN;
    }
#endif

#if defined (RMU_RSTCAUSE_BUBODVDDDREG)
    if (resetCauseMask & RMU_RSTCAUSE_BUBODVDDDREG) {
        return TOMMRO_C_OS_RESET_CAUSE_BROWN_DOWN;
    }
#endif

#if defined (RMU_RSTCAUSE_BUBODBUVIN)
    if (resetCauseMask & RMU_RSTCAUSE_BUBODBUVIN) {
        return TOMMRO_C_OS_RESET_CAUSE_BROWN_DOWN;
    }
#endif

#if defined (RMU_RSTCAUSE_BUBODUNREG)
    if (resetCauseMask & RMU_RSTCAUSE_BUBODUNREG) {
        return TOMMRO_C_OS_RESET_CAUSE_BROWN_DOWN;
    }
#endif

#if defined (RMU_RSTCAUSE_BUBODREG)
    if (resetCauseMask & RMU_RSTCAUSE_BUBODREG) {
        return TOMMRO_C_OS_RESET_CAUSE_BROWN_DOWN;
    }
#endif

#if defined (RMU_RSTCAUSE_BUMODERST)
    if (resetCauseMask & RMU_RSTCAUSE_BUMODERST) {
        return TOMMRO_C_OS_RESET_CAUSE_BROWN_DOWN;
    }
#endif
#endif

    return TOMMRO_C_OS_RESET_CAUSE_UNKNOWN;
}

tommRoC_err_enum_t tommRoCTemplateOsClearResetCause(void) {

#if (defined(RMU_COUNT) && (RMU_COUNT > 0))
    RMU_ResetCauseClear();
    return TOMMRO_C_ERR_SUCCESS;
#else
    return 
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;;
#endif
}

#endif

#endif
