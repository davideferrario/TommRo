
#if defined (__TOMMROC_USE_ARM_DEBUG_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "debug/print/arm/core/tommRoCTemplateDebugPrint_ARM.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MK22_IS_USED__)

#include "fsl_clock.h"
#if defined (FSL_FEATURE_SOC_PORT_COUNT) && FSL_FEATURE_SOC_PORT_COUNT
#include "fsl_port.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __SWO_CLOCK_NAME__          (kCLOCK_PortA)
#define __SWO_GPIO_PORT__           (PORTA)
#define __SWO_GPIO_PIN__            (2U)
#define __SWO_GPIO_PORT_MUX__       (kPORT_MuxAlt7)

#define __SWO_SPEED_HZ__            (1000000)

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

void tommRoCTemplateDebugPrint_ARM_OnEnterSetupITM(void) {

    // Configure GPIO port/pin as TRACE_SWO
    CLOCK_EnableClock(__SWO_CLOCK_NAME__);

    PORT_SetPinMux(__SWO_GPIO_PORT__, __SWO_GPIO_PIN__, __SWO_GPIO_PORT_MUX__);
}

uint32_t tommRoCTemplateDebugPrint_ARM_GetCpuDebugFreqHz(void) {

    return CLOCK_GetFreq(SYS_CLK);
}

uint32_t tommRoCTemplateDebugPrint_ARM_GetSWOSpeedHz(void) {

    return (uint32_t) __SWO_SPEED_HZ__;
}

#endif

#endif
