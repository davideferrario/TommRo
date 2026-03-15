
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateLWEspMBox.h"

#include "TOMMROC.h"
#include "TOMMROCHw.h"
#include "TOMMROCMw.h"

#include "TOMMROCMwTemplate.h"

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

uint32_t tommRoCHwTemplateLWEspMBoxEnvGetSize(void) {
#if defined (__TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__)
    return sizeof(tommRoC_mw_template_queue_t);
#else
    return UINT32_MAX;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLWEspMBoxCreate(void* mboxPtr, uint32_t size) {
#if defined (__TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__)
    /**
     * NOTE: from lwesp library.
     * Create a new message queue with entry type of void*.
     * param[in]       size: Number of entries for message queue to hold
     */
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCMwQueueCreate(mboxPtr, TOMMROC_UTIL_PTR_SIZE, size * TOMMROC_UTIL_PTR_SIZE), TOMMRO_C_HW_LOW_LEVEL_ERR);
    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(mboxPtr);
    TOMMROC_UTIL_UNUSED_PARAM(size);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLWEspMBoxDestroy(void* mboxPtr) {
#if defined (__TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCMwQueueDestroy(mboxPtr), TOMMRO_C_HW_LOW_LEVEL_ERR);
    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(mboxPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLWEspMBoxPut(void* mboxPtr, void* dataPtr) {
#if defined (__TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCMwQueuePut(mboxPtr, &dataPtr, QUEUE_INFINITE_TIMEOUT), TOMMRO_C_HW_LOW_LEVEL_ERR);
    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(mboxPtr);
    TOMMROC_UTIL_UNUSED_PARAM(dataPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLWEspMBoxGet(void* mboxPtr, void** dataPtr, uint32_t timeout) {
#if defined (__TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCMwQueueGet(mboxPtr, dataPtr, ((0 == timeout) ? (QUEUE_INFINITE_TIMEOUT) : (timeout))), TOMMRO_C_HW_LOW_LEVEL_ERR);
    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(mboxPtr);
    TOMMROC_UTIL_UNUSED_PARAM(dataPtr);
    TOMMROC_UTIL_UNUSED_PARAM(timeout);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLWEspMBoxPutnow(void* mboxPtr, void* dataPtr) {
#if defined (__TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCMwQueuePut(mboxPtr, &dataPtr, 1), TOMMRO_C_HW_LOW_LEVEL_ERR);
    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(mboxPtr);
    TOMMROC_UTIL_UNUSED_PARAM(dataPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLWEspMBoxGetnow(void* mboxPtr, void** dataPtr) {
#if defined (__TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCMwQueueGet(mboxPtr, dataPtr, 1), TOMMRO_C_HW_LOW_LEVEL_ERR);
    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(mboxPtr);
    TOMMROC_UTIL_UNUSED_PARAM(dataPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}
