
#if defined (__TOMMROC_MW_USE_MUTEX_THREADX_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_ThreadX_MutexCb.h"

#include "rtos/threadX/common/compatibility/tommRoCMwTemplateRTOS_ThreadX_Compatibility.h"

#include "TOMMROC.h"

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
static ULONG _get_timeout(const uint32_t waitTimeoutMs) {

    if (LOCK_MUTEX_NO_WAIT_TIMEOUT == waitTimeoutMs) {
        return TX_NO_WAIT;
    }

    if (LOCK_MUTEX_INFINITE_TIMEOUT == waitTimeoutMs) {
        return TX_WAIT_FOREVER;
    }

    return TOMMROC_MW_TEMPLATE_RTOS_THREADX_COMMON_COMPATIBILITY_MS_TO_TICKS(waitTimeoutMs);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_MutexCb_Create(
                void*       const   inputMutexPtr) {

    tommRoC_mw_template_mutex_t* mutexPtr;
    UINT res;

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_MUTEX, ((tommRoC_mw_template_mutex_t*)NULL)->threadXMutex);

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    res = tx_mutex_create(&mutexPtr->threadXMutex, TX_NULL, TX_NO_INHERIT);

    if (__THREADX_MUTEX_CREATE_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_MutexCb_CreateRecursive(
                void*       const   inputMutexPtr) {

    return tommRoCMwTemplateRTOS_ThreadX_MutexCb_Create(inputMutexPtr);
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_MutexCb_Lock(
                void*       const   inputMutexPtr,
        const   uint32_t            waitTimeoutMs) {

    ULONG wait_option;
    tommRoC_mw_template_mutex_t* mutexPtr;
    UINT res;

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_MUTEX, ((tommRoC_mw_template_mutex_t*)NULL)->threadXMutex);

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_WAIT_FOREVER, wait_option);

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    wait_option = _get_timeout(waitTimeoutMs);

    res = tx_mutex_get(&mutexPtr->threadXMutex, wait_option);

    if (__THREADX_MUTEX_GET_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_MutexCb_UnLock(
                void*       const   inputMutexPtr) {

    tommRoC_mw_template_mutex_t* mutexPtr;
    UINT res;

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_MUTEX, ((tommRoC_mw_template_mutex_t*)NULL)->threadXMutex);

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    res = tx_mutex_put(&mutexPtr->threadXMutex);

    if (__THREADX_MUTEX_PUT_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_MutexCb_Destroy(
                void*       const   inputMutexPtr) {

    tommRoC_mw_template_mutex_t* mutexPtr;
    UINT res;

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_MUTEX, ((tommRoC_mw_template_mutex_t*)NULL)->threadXMutex);

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    res = tx_mutex_delete(&mutexPtr->threadXMutex);

    if (__THREADX_MUTEX_DELETE_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
