
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOSEventU32.h"

#if defined (__TOMMROC_MW_EVENT_TEMPLATE_IS_USED__)
#include "tommRoCMwTemplateRTOSMutex.h"

#if !defined (__TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__)
#error "__TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__ is needed"
#endif

#include "rtos/eventU32/notGuarded/tommRoCMwTemplateRTOSEventU32NotGuarded.h"

#include "TOMMROC.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
TOMMROC_SCTA_EQUALS(TOMMROC_MW_TEMPLATE_RTOS_EVENT_U32_NOT_AVAILABLE_EVENT, TOMMROC_MW_TEMPLATE_RTOS_EVENT_U32_NOT_GUARDED_NOT_AVAILABLE_EVENT);

/*******************************************************************************
 * local vars
 ******************************************************************************/
static tommRoC_mw_template_mutex_t _mutex;
static tommRoC_guard_t _guard;

static bool _is_started = false;

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

static tommRoC_mw_err_enum_t _init(const uint8_t maxEventAmount) {

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
    /**
     * NOTE:
     * For ESP32, it is not possible to lock a mutex in case the osThreadSuspendAll has been called.
     * For now solved with this workaround.
     */
    return tommRoCMwTemplateRTOSEventU32NotGuardedStart(
            maxEventAmount);
#else
    TOMMROC_MW_UTIL_SYNCHRO_TOMMROC_MW_LIB_FUNCT(
            &_guard,
            tommRoCMwTemplateRTOSEventU32NotGuardedStart(
                    maxEventAmount));
#endif
}

static tommRoC_mw_err_enum_t _close(void) {

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
    /**
     * NOTE:
     * For ESP32, it is not possible to un-lock a mutex in case the osThreadSuspendAll has been called.
     * For now solved with this workaround.
     */
    return tommRoCMwTemplateRTOSEventU32NotGuardedStop();
#else
    TOMMROC_MW_UTIL_SYNCHRO_TOMMROC_MW_LIB_FUNCT(
            &_guard,
            tommRoCMwTemplateRTOSEventU32NotGuardedStop());
#endif
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSEventU32Start(const uint8_t maxEventAmount) {

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwMutexCreate(&_mutex));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCGuardInit(_lock, _un_lock, &_guard));

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_init(maxEventAmount));

    _is_started = true;

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSEventU32Stop(void) {

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_close());

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCGuardClear(&_guard));
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwMutexDestroy(&_mutex));

    _is_started = false;

    return TOMMRO_C_MW_ERR_SUCCESS;
}

bool tommRoCMwTemplateRTOSEventU32IsStarted(void) {
    return _is_started;
}

uint32_t tommRoCMwTemplateRTOSEventU32GetFirstAvailable(void) {

    TOMMROC_GUARD_SYNCHRO_WITH_RESULT_FUNCT(
            uint32_t,
            &_guard,
            TOMMROC_MW_TEMPLATE_RTOS_EVENT_U32_NOT_AVAILABLE_EVENT,
            tommRoCMwTemplateRTOSEventU32NotGuardedGetFirstAvailable());
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSEventU32Destroy(const uint32_t event) {

    TOMMROC_MW_UTIL_SYNCHRO_TOMMROC_MW_LIB_FUNCT(
            &_guard,
            tommRoCMwTemplateRTOSEventU32NotGuardedDestroy(
                    event));
}

#endif
