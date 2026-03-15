
#if defined (__TOMMROC_MW_USE_THREAD_CMSIS_V1_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "rtos/cmsisRTOS/V1/thread/os/freeRTOS/tickless/tommRoCMwTemplateRTOS_CMSIS_RTOS_OsFreeRTOSTickless.h"

#include "rtos/cmsisRTOS/V1/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)

#include "fsl_common.h"

#if (0 != FSL_FEATURE_SOC_LPTMR_COUNT)
#include "fsl_lptmr.h"
#endif

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
#include "rtos/cmsisRTOS/V1/common/CMSIS_RTOS/tommRoCMwTemplateRTOS_cmsis_os.h"
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

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
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

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_Os_FreeRTOSTicklessConfigLPTMRClk(void) {

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

#endif
