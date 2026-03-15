
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateLwIPSem.h"

// NOTE: include lwesp template to reuse same code.
#include "lwesp/sem/tommRoCHwTemplateLWEspSem.h"

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

uint32_t tommRoCHwTemplateLwIPSemEnvGetSize(void) {
    return tommRoCHwTemplateLWEspSemEnvGetSize();
}


tommRoC_hw_err_enum_t tommRoCHwTemplateLwIPSemCreate(void* semPtr, uint8_t cnt) {
    return tommRoCHwTemplateLWEspSemCreate(semPtr, cnt);
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLwIPSemDestroy(void* semPtr) {
    return tommRoCHwTemplateLWEspSemDestroy(semPtr);
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLwIPSemWait(void* semPtr, uint32_t timeout) {
    return tommRoCHwTemplateLWEspSemWait(semPtr, timeout);
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLwIPSemRelease(void* semPtr) {
    return tommRoCHwTemplateLWEspSemRelease(semPtr);
}
