
#if defined (__TOMMROC_MW_USE_THREAD_CMSIS_V2_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_CMSIS_RTOS_Critical.h"

#include "rtos/cmsisRTOS/V2/common/CMSIS_RTOS/tommRoCMwTemplateRTOS_cmsis_os.h"
#include "rtos/cmsisRTOS/V2/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"

#if defined (__TOMMROC_MW_ARM_ESP32_RTOS_INTERNAL_TEMPLATE_IS_USED__)
#include "freertos/FreeRTOS.h"
#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
#include <stdint.h>
#else
#error "Not supported RTOS environment"
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
#if defined (__TOMMROC_MW_ARM_ESP32_RTOS_INTERNAL_TEMPLATE_IS_USED__)
static portMUX_TYPE _mux = portMUX_INITIALIZER_UNLOCKED;
#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
static uint32_t _base_priority_array[16];
static uint32_t _base_priority_top = 0;
#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
static uint8_t _cpu_SR;
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if defined (__TOMMROC_MW_ARM_ESP32_RTOS_INTERNAL_TEMPLATE_IS_USED__)
#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
static bool _in_handler_mode(void) {
    return (0 != __get_IPSR());
}

static void _enter_critical(void) {

    if (_in_handler_mode()) {
        if (_base_priority_top < TOMMROC_UTIL_ARR_EAMOUNT(_base_priority_array)) {
            _base_priority_array[_base_priority_top] = portSET_INTERRUPT_MASK_FROM_ISR();
            ++_base_priority_top;
        }
    }
    else {
        portENTER_CRITICAL();
    }
}

static void _exit_critical(void) {

    if (_in_handler_mode()) {
        if (0 != _base_priority_top) {
            --_base_priority_top;
            portCLEAR_INTERRUPT_MASK_FROM_ISR(_base_priority_array[_base_priority_top]);
        }
    }
    else {
        portEXIT_CRITICAL();
    }
}
#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_CriticalEnter(uint32_t* const specificDataPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(specificDataPtr);

#if defined (__TOMMROC_MW_ARM_ESP32_RTOS_INTERNAL_TEMPLATE_IS_USED__)
    portENTER_CRITICAL_SAFE(&_mux);
#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
    _enter_critical();
#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
    asm (
            "MRS R0, PRIMASK\n\t"
            "CPSID I\n\t"
            "STRB R0, %[output]"
            : [output] "=m" (_cpu_SR) :: "r0");
#endif

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_CriticalExit(uint32_t* const specificDataPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(specificDataPtr);

#if defined (__TOMMROC_MW_ARM_ESP32_RTOS_INTERNAL_TEMPLATE_IS_USED__)
    portEXIT_CRITICAL_SAFE(&_mux);
#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
    _exit_critical();
#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
    asm (
            "ldrb r0, %[input]\n\t"
            "msr PRIMASK,r0;\n\t"
            ::[input] "m" (_cpu_SR) : "r0");
#endif

    return TOMMRO_C_ERR_SUCCESS;
}

#endif
