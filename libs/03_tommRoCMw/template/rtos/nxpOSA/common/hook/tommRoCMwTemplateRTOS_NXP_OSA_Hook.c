
#if defined (__TOMMROC_MW_USE_THREAD_NXP_OSA_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_NXP_OSA_Hook.h"

#include "TOMMROC.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_MW_TEMPLATE_RTOS_NXP_OSA_CHECK_FOR_STACK_OVERFLOW_IS_USED__) || defined (__TOMMROC_MW_TEMPLATE_RTOS_NXP_OSA_MALLOC_FAILED_HOOK_IS_USED__)
#if defined (__TOMMROC_DEBUG_ENABLE__)
static const char __DEBUG_OBJ_ID__[] = "NXPHook";
#endif
#endif

#if defined (__TOMMROC_MW_TEMPLATE_RTOS_NXP_OSA_CHECK_FOR_STACK_OVERFLOW_IS_USED__)
static char _stack_overflow_task_name[configMAX_TASK_NAME_LEN + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE];
static bool _stack_overflow_has_been_detected = false;
#endif

#if defined (__TOMMROC_MW_TEMPLATE_RTOS_NXP_OSA_MALLOC_FAILED_HOOK_IS_USED__)
static bool _malloc_failed_has_been_detected = false;
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if defined (__TOMMROC_MW_TEMPLATE_RTOS_NXP_OSA_CHECK_FOR_STACK_OVERFLOW_IS_USED__)
void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    char *pcTaskName ) {

    uint16_t pcTaskNameStrLen;

    TOMMROC_UTIL_UNUSED_PARAM(xTask);

    if (UNITY_IS_BEGIN()) {
        TEST_ASSERT_TRUE(false);
    }

    // If here, ERROR!!!
    TOMMROC_ASSERT_TRUE(false);

    pcTaskNameStrLen = tommRoCStringStrLen(pcTaskName);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(_stack_overflow_task_name, TOMMROC_STRING_NULL_TERMINATOR_CHAR, sizeof(_stack_overflow_task_name)));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(_stack_overflow_task_name, pcTaskName, pcTaskNameStrLen));

    _stack_overflow_has_been_detected = true;
}
#endif

#if defined (__TOMMROC_MW_TEMPLATE_RTOS_NXP_OSA_MALLOC_FAILED_HOOK_IS_USED__)
void vApplicationMallocFailedHook( void ) {

    if (UNITY_IS_BEGIN()) {
        TEST_ASSERT_TRUE(false);
    }

    // If here, ERROR!!!
    TOMMROC_ASSERT_TRUE(false);

    _malloc_failed_has_been_detected = true;
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_MW_TEMPLATE_RTOS_NXP_OSA_CHECK_FOR_STACK_OVERFLOW_IS_USED__)
bool tommRoCMwTemplateRTOS_NXP_OSA_HookStackOverflowHasBeenDetected(void) {
    return _stack_overflow_has_been_detected;
}
#endif

#if defined (__TOMMROC_MW_TEMPLATE_RTOS_NXP_OSA_MALLOC_FAILED_HOOK_IS_USED__)
bool tommRoCMwTemplateRTOS_NXP_OSA_HookMallocFailedHasBeenDetected(void) {
    return _malloc_failed_has_been_detected;
}
#endif

void tommRoCMwTemplateRTOS_NXP_OSA_HookDebug(void) {
#if defined (__TOMMROC_MW_TEMPLATE_RTOS_NXP_OSA_CHECK_FOR_STACK_OVERFLOW_IS_USED__)
    if (tommRoCMwTemplateRTOS_NXP_OSA_HookStackOverflowHasBeenDetected()) {
        TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_E_LEVEL, "TASK OVERFLOW!!!!!! ", _stack_overflow_task_name);
    }
#endif

#if defined (__TOMMROC_MW_TEMPLATE_RTOS_NXP_OSA_MALLOC_FAILED_HOOK_IS_USED__)
    if (tommRoCMwTemplateRTOS_NXP_OSA_HookMallocFailedHasBeenDetected()) {
        TOMMROC_DEBUG_E("MALLOC FAILED!!!!!!");
    }
#endif
}

#endif
