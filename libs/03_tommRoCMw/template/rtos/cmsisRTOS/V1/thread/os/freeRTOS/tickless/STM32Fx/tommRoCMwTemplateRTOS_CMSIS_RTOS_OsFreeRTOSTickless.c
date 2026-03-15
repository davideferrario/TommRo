
#if defined (__TOMMROC_MW_USE_THREAD_CMSIS_V1_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "rtos/cmsisRTOS/V1/thread/os/freeRTOS/tickless/tommRoCMwTemplateRTOS_CMSIS_RTOS_OsFreeRTOSTickless.h"

#include "rtos/cmsisRTOS/V1/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)

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
#if (configUSE_TICKLESS_IDLE == 1)
extern void vPortLptmrIsr(void);
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
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

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_Os_FreeRTOSTicklessConfigLPTMRClk(void) {

    return TOMMRO_C_MW_NOT_AVAILABLE_ERR;
}

#endif

#endif
