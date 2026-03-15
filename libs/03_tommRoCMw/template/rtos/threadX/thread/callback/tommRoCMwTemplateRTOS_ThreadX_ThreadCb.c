
#if defined (__TOMMROC_MW_USE_THREAD_THREADX_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_ThreadX_ThreadCb.h"

#include "rtos/threadX/common/compatibility/tommRoCMwTemplateRTOS_ThreadX_Compatibility.h"
#include "rtos/threadX/common/critical/tommRoCMwTemplateRTOS_ThreadX_Critical.h"
#include "rtos/threadX/common/util/tommRoCMwTemplateRTOS_ThreadX_Util.h"

#include "TOMMROC.h"

#include "TOMMROCMwTemplate.h"

#include "tx_thread.h"
#include "tx_user.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __PRIORITY_MIN__            (0)
#define __PRIORITY_MAX__            (TX_MAX_PRIORITIES - 1)

#define __PRIORITY_STEP__           ((__PRIORITY_MAX__ - (__PRIORITY_MIN__ + 1)) / 6)

#define __PRIORITY_REALTIME__       (__PRIORITY_MIN__           + 1)
#define __PRIORITY_HIGH__           (__PRIORITY_REALTIME__      + __PRIORITY_STEP__)
#define __PRIORITY_ABOVE_NORMAL__   (__PRIORITY_HIGH__          + __PRIORITY_STEP__)
#define __PRIORITY_NORMAL__         (__PRIORITY_ABOVE_NORMAL__  + __PRIORITY_STEP__)
#define __PRIORITY_BELOW_NORMAL__   (__PRIORITY_NORMAL__        + __PRIORITY_STEP__)
#define __PRIORITY_LOW__            (__PRIORITY_BELOW_NORMAL__  + __PRIORITY_STEP__)
#define __PRIORITY_IDLE__           (__PRIORITY_LOW__           + __PRIORITY_STEP__)

#define __PRIORITY_DEFAULT__        (__PRIORITY_NORMAL__)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static UINT _suspend_resume_old_priority    = __PRIORITY_MIN__;
static UINT _suspend_resume_old_threshold   = __PRIORITY_MIN__;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static UINT _convert_priority(const tommRoC_mw_thread_priority_enum_t priority) {

    switch (priority) {

    case TOMMRO_C_MW_THREAD_PRIORITY_IDLE:          return (UINT) __PRIORITY_IDLE__;
    case TOMMRO_C_MW_THREAD_PRIORITY_LOW:           return (UINT) __PRIORITY_LOW__;
    case TOMMRO_C_MW_THREAD_PRIORITY_BELOW_NORMAL:  return (UINT) __PRIORITY_BELOW_NORMAL__;
    case TOMMRO_C_MW_THREAD_PRIORITY_NORMAL:        return (UINT) __PRIORITY_NORMAL__;
    case TOMMRO_C_MW_THREAD_PRIORITY_ABOVE_NORMAL:  return (UINT) __PRIORITY_ABOVE_NORMAL__;
    case TOMMRO_C_MW_THREAD_PRIORITY_HIGH:          return (UINT) __PRIORITY_HIGH__;
    case TOMMRO_C_MW_THREAD_PRIORITY_REALTIME:      return (UINT) __PRIORITY_REALTIME__;
    case TOMMRO_C_MW_THREAD_PRIORITY_DEFAULT:       return (UINT) __PRIORITY_DEFAULT__;

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;

    }

    return (UINT) __PRIORITY_MIN__;
}

static uint32_t _convert_stack_size(const uint32_t stackSize) {

    if (TOMMRO_C_MW_THREAD_STACK_SIZE_DEFAULT == stackSize) {
        return (uint32_t) __THREADX_THREAD_STACK_SIZE_DEFAULT__;
    }

    return (uint32_t) stackSize;
}

static VOID _entry_function(ULONG id) {

    tommRoC_mw_template_thread_t* threadPtr = (tommRoC_mw_template_thread_t*) id;

    threadPtr->entryFunctionParam.mainThread(threadPtr->entryFunctionParam.mainThreadArgPtr);
}

static void _suspend_all(void) {

    TX_THREAD* currentThreadPtr;

    TOMMROC_ASSERT_EQUALS(_suspend_resume_old_priority, __PRIORITY_MIN__);

    if (__PRIORITY_MIN__ != _suspend_resume_old_priority) {
        return;
    }

    TX_THREAD_GET_CURRENT(currentThreadPtr)

    tx_thread_priority_change(currentThreadPtr, __PRIORITY_MIN__, &_suspend_resume_old_priority);
    tx_thread_preemption_change(currentThreadPtr, __PRIORITY_MIN__, &_suspend_resume_old_threshold);
}

static void _resume_all(void) {

    TX_THREAD* currentThreadPtr;

    UINT tmpPriority;
    UINT tmpThreshold;

    TOMMROC_ASSERT_NOT_EQUALS(_suspend_resume_old_priority, __PRIORITY_MIN__);

    if (__PRIORITY_MIN__ == _suspend_resume_old_priority) {
        return;
    }

    TX_THREAD_GET_CURRENT(currentThreadPtr)

    tx_thread_priority_change(currentThreadPtr, _suspend_resume_old_priority, &tmpPriority);
    tx_thread_preemption_change(currentThreadPtr, _suspend_resume_old_threshold, &tmpThreshold);

    _suspend_resume_old_priority    = __PRIORITY_MIN__;
    _suspend_resume_old_threshold   = __PRIORITY_MIN__;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_ThreadCb_Create(
        const   tommRoC_mw_thread_main_funct_t          mainThread,
                void*                           const   mainThreadArgPtr,
        const   char*                           const   threadNameStrPtr,
        const   tommRoC_mw_thread_config_t*     const   configPtr,
                void*                           const   inputThreadPtr) {

    tommRoC_mw_template_thread_t* threadPtr;
    UINT priority;
    uint32_t stackSize;
    TX_BYTE_POOL* appStackBytePoolPtr;
    VOID* pointer;
    UINT res;

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_THREAD, ((tommRoC_mw_template_thread_t*)NULL)->threadXThread);

    threadPtr = (tommRoC_mw_template_thread_t*) inputThreadPtr;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(threadPtr, 0x00, sizeof(tommRoC_mw_template_thread_t)));

    priority    = _convert_priority(configPtr->priority);
    stackSize   = tommRoCMathMax(_convert_stack_size(configPtr->stackSize), TX_MINIMUM_STACK);

    appStackBytePoolPtr = tommRoCMwTemplateRTOS_ThreadX_Util_GetAppStackBytePoolPtr();

    // Allocate stack for Thread
    pointer = TX_NULL;
    res = tx_byte_allocate(appStackBytePoolPtr, &pointer, stackSize, TX_NO_WAIT);

    if (TX_SUCCESS != res) {
        if (TX_NULL != pointer) {
            tx_byte_release(pointer);
        }
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    threadPtr->threadStackPtr = pointer;

    threadPtr->entryFunctionParam.mainThread        = mainThread;
    threadPtr->entryFunctionParam.mainThreadArgPtr  = mainThreadArgPtr;

    res = tx_thread_create(&threadPtr->threadXThread, (NULL != threadNameStrPtr) ? ((CHAR*) threadNameStrPtr) : (TX_NULL), _entry_function, (ULONG) threadPtr, pointer, (ULONG) stackSize, priority, priority, TX_NO_TIME_SLICE, TX_AUTO_START);

    if (__THREADX_THREAD_CREATE_SUCCESS_RESULT__ != res) {
        if (TX_NULL != pointer) {
            tx_byte_release(pointer);
        }
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_ThreadCb_GetID(
                void*   const   inputThreadIDPtr) {

    tommRoC_mw_template_thread_id_t* threadIDPtr;
    TX_THREAD* res;

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_THREAD*, tommRoC_mw_template_thread_id_t);

    threadIDPtr = (tommRoC_mw_template_thread_id_t*) inputThreadIDPtr;

    res = tx_thread_identify();

    if (__THREADX_THREAD_IDENTIFY_ON_ERROR_RESULT__ == res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopySafe(threadIDPtr, sizeof(tommRoC_mw_template_thread_id_t), &res, sizeof(TX_THREAD*), sizeof(res)));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_ThreadCb_Destroy(
                void*   const   inputThreadPtr) {

    tommRoC_mw_template_thread_t* threadPtr;
    UINT res;

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_THREAD, ((tommRoC_mw_template_thread_t*)NULL)->threadXThread);

    threadPtr = (tommRoC_mw_template_thread_t*) inputThreadPtr;

    res = tx_thread_terminate(&threadPtr->threadXThread);

    if (__THREADX_THREAD_TERMINATE_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    res = tx_thread_delete(&threadPtr->threadXThread);

    if (__THREADX_THREAD_DESTROY_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    // Release stack for Thread
    if (TX_NULL != threadPtr->threadStackPtr) {
        res = tx_byte_release(threadPtr->threadStackPtr);

        if (TX_SUCCESS != res) {
            return TOMMRO_C_MW_LOW_LEVEL_ERR;
        }
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_ThreadCb_Exit(void) {

    TX_THREAD* txThreadPtr;
    
    UINT res;

    txThreadPtr = tx_thread_identify();

    if (__THREADX_THREAD_IDENTIFY_ON_ERROR_RESULT__ == txThreadPtr) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    res = tx_thread_terminate(txThreadPtr);

    if (__THREADX_THREAD_TERMINATE_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    res = tx_thread_delete(txThreadPtr);

    if (__THREADX_THREAD_DESTROY_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

void tommRoCMwTemplateRTOS_ThreadX_ThreadCb_Yield(void) {
    tx_thread_relinquish();
}

void tommRoCMwTemplateRTOS_ThreadX_ThreadCb_SuspendAll(void) {

    uint32_t criticalSpecificData;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsEnterCritical(&criticalSpecificData));

    _suspend_all();

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsExitCritical(&criticalSpecificData));
}

void tommRoCMwTemplateRTOS_ThreadX_ThreadCb_ResumeAll(void) {

    uint32_t criticalSpecificData;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsEnterCritical(&criticalSpecificData));

    _resume_all();

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsExitCritical(&criticalSpecificData));
}

#endif
