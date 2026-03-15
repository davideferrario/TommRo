
#if defined (__TOMMROC_USE_ARM_DEBUG_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "debug/print/arm/core/tommRoCTemplateDebugPrint_ARM.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_IS_USED__)

/*******************************************************************************
 * local defines
 ******************************************************************************/
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

    // Enable GPIO Clock.
#if defined (_CMU_HFPERCLKEN0_GPIO_MASK)
    CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_GPIO;
#elif defined (_CMU_HFBUSCLKEN0_GPIO_MASK)
    CMU->HFBUSCLKEN0 |= CMU_HFBUSCLKEN0_GPIO;
#endif

    // Enable Serial wire output pin
#if defined (_GPIO_ROUTE_SWOPEN_MASK)
    GPIO->ROUTE |= GPIO_ROUTE_SWOPEN;
#elif defined (_GPIO_ROUTEPEN_SWVPEN_MASK)
    GPIO->ROUTEPEN |= GPIO_ROUTEPEN_SWVPEN;
#endif

    // Set correct location
#if defined (_EFM32_GIANT_FAMILY) || defined (_EFM32_LEOPARD_FAMILY) || defined (_EFM32_WONDER_FAMILY)

    // Set location 0
#if defined (_GPIO_ROUTE_SWOPEN_MASK)
    GPIO->ROUTE = (GPIO->ROUTE & ~(_GPIO_ROUTE_SWLOCATION_MASK)) | GPIO_ROUTE_SWLOCATION_LOC0;
#elif defined (_GPIO_ROUTEPEN_SWVPEN_MASK)
    GPIO->ROUTELOC0 = (GPIO->ROUTELOC0 & ~(_GPIO_ROUTELOC0_SWVLOC_MASK)) | GPIO_ROUTE_SWLOCATION_LOC0;
#endif

    // Enable output on pin - GPIO Port F, Pin 2
    GPIO->P[5].MODEL &= ~(_GPIO_P_MODEL_MODE2_MASK);
    GPIO->P[5].MODEL |= GPIO_P_MODEL_MODE2_PUSHPULL;
#else

#if defined (_GPIO_ROUTE_SWOPEN_MASK)
    // Set location 1
    GPIO->ROUTE = (GPIO->ROUTE & ~(_GPIO_ROUTE_SWLOCATION_MASK)) | GPIO_ROUTE_SWLOCATION_LOC1;
#elif defined (_GPIO_ROUTEPEN_SWVPEN_MASK)
    GPIO->ROUTELOC1 = (GPIO->ROUTELOC1 & ~(_GPIO_ROUTELOC1_SWVLOC_MASK)) | GPIO_ROUTE_SWLOCATION_LOC1;
#endif

    // Enable output on pin
    GPIO->P[2].MODEH &= ~(_GPIO_P_MODEH_MODE15_MASK);
    GPIO->P[2].MODEH |= GPIO_P_MODEH_MODE15_PUSHPULL;
#endif

    // Enable debug clock AUXHFRCO
    CMU->OSCENCMD = CMU_OSCENCMD_AUXHFRCOEN;

    // Wait until clock is ready
    while (!(CMU->STATUS & CMU_STATUS_AUXHFRCORDY)) ;
}

uint32_t tommRoCTemplateDebugPrint_ARM_GetCpuDebugFreqHz(void) {

    return CMU_ClockFreqGet(cmuClock_DBG);
}

uint32_t tommRoCTemplateDebugPrint_ARM_GetSWOSpeedHz(void) {

    return (uint32_t) __SWO_SPEED_HZ__;
}

#endif

#endif
