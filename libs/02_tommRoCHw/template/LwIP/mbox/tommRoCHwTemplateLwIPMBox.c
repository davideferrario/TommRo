
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateLwIPMBox.h"

// NOTE: include lwesp template to reuse same code.
#include "lwesp/mbox/tommRoCHwTemplateLWEspMBox.h"

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

uint32_t tommRoCHwTemplateLwIPMBoxEnvGetSize(void) {
    return tommRoCHwTemplateLWEspMBoxEnvGetSize();
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLwIPMBoxCreate(void* mboxPtr, uint32_t size) {
    return tommRoCHwTemplateLWEspMBoxCreate(mboxPtr, size);
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLwIPMBoxDestroy(void* mboxPtr) {
    return tommRoCHwTemplateLWEspMBoxDestroy(mboxPtr);
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLwIPMBoxPut(void* mboxPtr, void* dataPtr) {
    return tommRoCHwTemplateLWEspMBoxPut(mboxPtr, dataPtr);
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLwIPMBoxGet(void* mboxPtr, void** dataPtr, uint32_t timeout) {
    return tommRoCHwTemplateLWEspMBoxGet(mboxPtr, dataPtr, timeout);
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLwIPMBoxPutnow(void* mboxPtr, void* dataPtr) {
    return tommRoCHwTemplateLWEspMBoxPutnow(mboxPtr, dataPtr);
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLwIPMBoxGetnow(void* mboxPtr, void** dataPtr) {
    return tommRoCHwTemplateLWEspMBoxGetnow(mboxPtr, dataPtr);
}
