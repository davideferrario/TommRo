
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateLwIPThread.h"

// NOTE: include lwesp template to reuse same code.
#include "lwesp/thread/tommRoCHwTemplateLWEspThread.h"

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

uint32_t tommRoCHwTemplateLwIPThreadEnvGetSize(void) {
    return tommRoCHwTemplateLWEspThreadEnvGetSize();
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLwIPThreadCreate(void* threadPtr, const char* threadNamePtr, void(*threadMain)(void*), void* const threadArgPtr, uint32_t threadStackSize, uint32_t threadPriority) {
    return tommRoCHwTemplateLWEspThreadCreate(threadPtr, threadNamePtr, threadMain, threadArgPtr, threadStackSize, threadPriority);
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLwIPThreadTerminate(void* threadPtr) {
    return tommRoCHwTemplateLWEspThreadTerminate(threadPtr);
}
