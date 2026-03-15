
#if defined (__TOMMROC_MW_USE_THREAD_THREADX_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_ThreadX_Hook.h"

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
#if defined (__TOMMROC_MW_TEMPLATE_RTOS_THREADX_CHECK_FOR_STACK_OVERFLOW_IS_USED__)
#if defined (__TOMMROC_DEBUG_ENABLE__)
static const char __DEBUG_OBJ_ID__[] = "ThreadXHook";
#endif
#endif

#if defined (__TOMMROC_MW_TEMPLATE_RTOS_THREADX_CHECK_FOR_STACK_OVERFLOW_IS_USED__)
static bool _stack_overflow_has_been_detected = false;
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_MW_TEMPLATE_RTOS_THREADX_CHECK_FOR_STACK_OVERFLOW_IS_USED__)
bool tommRoCMwTemplateRTOS_ThreadX_HookStackOverflowHasBeenDetected(void) {
    return _stack_overflow_has_been_detected;
}
VOID tommRoCMwTemplateRTOS_ThreadX_HookStackOverflowStackErrorHandler(TX_THREAD *thread_ptr) {

    TOMMROC_UTIL_UNUSED_PARAM(thread_ptr);

    if (UNITY_IS_BEGIN()) {
        TEST_ASSERT_TRUE(false);
    }

    // If here, ERROR!!!
    TOMMROC_ASSERT_TRUE(false);

    _stack_overflow_has_been_detected = true;
}
#endif

void tommRoCMwTemplateRTOS_ThreadX_HookDebug(void) {
#if defined (__TOMMROC_MW_TEMPLATE_RTOS_THREADX_CHECK_FOR_STACK_OVERFLOW_IS_USED__)
    if (tommRoCMwTemplateRTOS_ThreadX_HookStackOverflowHasBeenDetected()) {
        TOMMROC_DEBUG_E("TASK ERROR!!!!!!");
    }
#endif
}

#endif
