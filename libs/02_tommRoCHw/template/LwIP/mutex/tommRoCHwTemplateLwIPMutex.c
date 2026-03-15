
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateLwIPMutex.h"

// NOTE: include lwesp template to reuse same code.
#include "lwesp/mutex/tommRoCHwTemplateLWEspMutex.h"

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

uint32_t tommRoCHwTemplateLwIPMutexEnvGetSize(void) {
    return tommRoCHwTemplateLWEspMutexEnvGetSize();
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLwIPMutexCreateRecursive(void* mutexPtr) {
    return tommRoCHwTemplateLWEspMutexCreateRecursive(mutexPtr);
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLwIPMutexDestroy(void* mutexPtr) {
    return tommRoCHwTemplateLWEspMutexDestroy(mutexPtr);
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLwIPMutexLock(void* mutexPtr) {
    return tommRoCHwTemplateLWEspMutexLock(mutexPtr);
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLwIPMutexUnlock(void* mutexPtr) {
    return tommRoCHwTemplateLWEspMutexUnlock(mutexPtr);
}
