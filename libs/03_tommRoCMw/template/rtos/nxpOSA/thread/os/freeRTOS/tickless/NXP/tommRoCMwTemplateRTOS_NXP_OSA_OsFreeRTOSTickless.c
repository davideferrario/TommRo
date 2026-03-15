
#if defined (__TOMMROC_MW_USE_THREAD_NXP_OSA_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "rtos/nxpOSA/thread/os/freeRTOS/tickless/tommRoCMwTemplateRTOS_NXP_OSA_OsFreeRTOSTickless.h"

#include "rtos/nxpOSA/common/compatibility/tommRoCMwTemplateRTOS_NXP_OSA_Compatibility.h"

#include "env/tommRoCTemplateEnv.h"

#include "fsl_common.h"

#if (0 != FSL_FEATURE_SOC_LPTMR_COUNT)
#include "fsl_lptmr.h"
#endif

#include "fsl_os_abstraction.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if (0 != FSL_FEATURE_SOC_LPTMR_COUNT) && (configUSE_TICKLESS_IDLE == 1)
extern void vPortLptmrIsr(void);
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if (0 != FSL_FEATURE_SOC_LPTMR_COUNT)
// LPTMR0 IRQ handler
__attribute__((weak))
void LPTMR0_IRQHandler(void) {

#if (configUSE_TICKLESS_IDLE == 1)
    vPortLptmrIsr();
#endif
}

#if (configUSE_TICKLESS_IDLE == 1)
LPTMR_Type *vPortGetLptrmBase(void) {
    return LPTMR0;
}

IRQn_Type vPortGetLptmrIrqn(void) {
    return LPTMR0_IRQn;
}
#endif
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_Os_FreeRTOSTicklessConfigLPTMRClk(void) {

#if (0 != FSL_FEATURE_SOC_LPTMR_COUNT)

    lptmr_config_t lptmrConfig;

    CLOCK_EnableClock(kCLOCK_Lptmr0);
    // Configuration LPTMR
    LPTMR_GetDefaultConfig(&lptmrConfig);
    LPTMR_Init(LPTMR0, &lptmrConfig);

    NVIC_ClearPendingIRQ(LPTMR0_IRQn);

    EnableIRQ(LPTMR0_IRQn);
    LPTMR_EnableInterrupts(LPTMR0, kLPTMR_TimerInterruptEnable);

    return TOMMRO_C_MW_ERR_SUCCESS;
#else

    return TOMMRO_C_MW_NOT_AVAILABLE_ERR;
#endif
}

#endif
