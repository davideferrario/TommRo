
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateWDT.h"

#include "TOMMROC.h"
#include "TOMMROCMw.h"

#include "TOMMROCTemplate.h"
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
#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
static tommRoC_mw_template_mutex_t _mutex;
static tommRoC_guard_t _guard;

static tommRoC_mw_template_thread_id_t* _app_thread_ID_table_ptr = NULL;
static uint8_t _app_thread_ID_table_eamount = 0;

static uint32_t _wdt_timeout_msec = UINT32_MAX;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_err_enum_t _lock(void) {
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwMutexLock(&_mutex, LOCK_MUTEX_INFINITE_TIMEOUT));
    return TOMMRO_C_ERR_SUCCESS;
}
static tommRoC_err_enum_t _un_lock(void) {
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwMutexUnLock(&_mutex));
    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_mw_err_enum_t _get_task_ID(uint8_t* const taskIDPtr) {

    tommRoC_mw_template_thread_id_t threadID;

    uint8_t idx;

    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwThreadGetID(&threadID));

    for (idx = 0; idx < _app_thread_ID_table_eamount; ++idx) {

        if (TOMMRO_C_MW_ERR_SUCCESS == tommRoCMwThreadCompareID(&threadID, _app_thread_ID_table_ptr + idx, sizeof(tommRoC_mw_template_thread_id_t))) {
            *taskIDPtr = idx;
            return TOMMRO_C_MW_ERR_SUCCESS;
        }

        /**
         * NOTE:
         * TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(0)) not used because this function is called by tommRoCOsDelayMsec.
         * It will create recursive function call
         */
    }

    return TOMMRO_C_MW_NOT_AVAILABLE_ERR;
}

static uint32_t _os_extend_delay_msec(void) {

    uint8_t taskID;

    // NOTE: if it is not possible to get taskID, it means that it is a "not handled" task
    if (TOMMRO_C_MW_ERR_SUCCESS != _get_task_ID(&taskID)) {
        return UINT32_MAX;
    }

    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwWDTTaskRefresh(taskID));

    return _wdt_timeout_msec;
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateWDTInit(
        const   void*                           const   appThreadIDTablePtr,
        const   uint8_t                                 appThreadIDTableAmount,
        const   tommRoC_mw_wdt_refresh_funct_t          refreshFunctPtr,
                void*                           const   refreshFunctInOutPtr,
                tommRoC_mw_wdt_t*               const   WDTArrayPtr,
        const   uint8_t                                 WDTArrayAmount,
        const   uint32_t                                WDTTimeoutMsec) {

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)

    TOMMROC_ASSERT_NOT_NULL(appThreadIDTablePtr);
    TOMMROC_ASSERT_NOT_ZERO(appThreadIDTableAmount);

    TOMMROC_MW_PARAM_CHECK_ON_NULL_RETURN_ERR(appThreadIDTablePtr);
    TOMMROC_MW_PARAM_CHECK_ON_ZERO_RETURN_ERR(appThreadIDTableAmount);

    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwMutexCreate(&_mutex));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCGuardInit(_lock, _un_lock, &_guard));

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCMwWDTInit(
                    &_guard,
                    refreshFunctPtr,
                    refreshFunctInOutPtr,
                    WDTArrayPtr,
                    WDTArrayAmount,
                    WDTTimeoutMsec));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsInitExtendDelayMsec(_os_extend_delay_msec),
            TOMMRO_C_MW_LOW_LEVEL_ERR);

    _app_thread_ID_table_ptr        = (tommRoC_mw_template_thread_id_t*) appThreadIDTablePtr;
    _app_thread_ID_table_eamount    = appThreadIDTableAmount;
    _wdt_timeout_msec               = (2 * WDTTimeoutMsec) / 3; // NOTE: 2/3 to give a little bit of tollerance.

    return TOMMRO_C_MW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(appThreadIDTablePtr);
    TOMMROC_UTIL_UNUSED_PARAM(appThreadIDTableAmount);
    TOMMROC_UTIL_UNUSED_PARAM(refreshFunctPtr);
    TOMMROC_UTIL_UNUSED_PARAM(refreshFunctInOutPtr);
    TOMMROC_UTIL_UNUSED_PARAM(WDTArrayPtr);
    TOMMROC_UTIL_UNUSED_PARAM(WDTArrayAmount);
    TOMMROC_UTIL_UNUSED_PARAM(WDTTimeoutMsec);
    return TOMMRO_C_MW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_mw_err_enum_t tommRoCMwTemplateWDTClose(void) {

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)

    _app_thread_ID_table_ptr        = (tommRoC_mw_template_thread_id_t*) NULL;
    _app_thread_ID_table_eamount    = 0;

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsCloseEnv(TOMMRO_C_OS_EXTEND_DELAY_MSEC_FUNCT),
            TOMMRO_C_MW_LOW_LEVEL_ERR);

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwWDTClose());

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCGuardClear(&_guard));
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwMutexDestroy(&_mutex));

    return TOMMRO_C_MW_ERR_SUCCESS;
#else
    return TOMMRO_C_MW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_mw_err_enum_t tommRoCMwTemplateWDTCheck(
                uint8_t*                        const   wdtExpiredAmountPtr,
                uint8_t*                        const   expiredTaskIDArrayPtr,
        const   uint8_t                                 expiredTaskIDArraySize) {

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwWDTCheck(wdtExpiredAmountPtr, expiredTaskIDArrayPtr, expiredTaskIDArraySize));
    return TOMMRO_C_MW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(wdtExpiredAmountPtr);
    TOMMROC_UTIL_UNUSED_PARAM(expiredTaskIDArrayPtr);
    TOMMROC_UTIL_UNUSED_PARAM(expiredTaskIDArraySize);
    return TOMMRO_C_MW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_mw_err_enum_t tommRoCMwTemplateWDTDisable(void) {

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwWDTDisable());
    return TOMMRO_C_MW_ERR_SUCCESS;
#else
    return TOMMRO_C_MW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_mw_err_enum_t tommRoCMwTemplateWDTEnable(void) {

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwWDTEnable());
    return TOMMRO_C_MW_ERR_SUCCESS;
#else
    return TOMMRO_C_MW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_mw_err_enum_t tommRoCMwTemplateWDTTaskDisable(void) {

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)

    uint8_t taskID;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_get_task_ID(&taskID));
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwWDTTaskDisable(taskID));
    return TOMMRO_C_MW_ERR_SUCCESS;
#else
    return TOMMRO_C_MW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_mw_err_enum_t tommRoCMwTemplateWDTTaskEnable(void) {

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)

    uint8_t taskID;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_get_task_ID(&taskID));
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwWDTTaskEnable(taskID));
    return TOMMRO_C_MW_ERR_SUCCESS;
#else
    return TOMMRO_C_MW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}
