
#if defined (__TOMMROC_USE_TIME_WINDOWS_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/tommRoCTemplateOsCritical.h"

#include <windows.h>

#include <stdbool.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __SPIN_COUNT_VALUE__        (0x00000400)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static CRITICAL_SECTION _critical_section;
static bool _is_init = false;

/*******************************************************************************
 * local functions
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateOsCriticalInit(void) {

    /**
     * Initializes critical section object and sets spin count for the critical section.
     * When a thread tries to acquire critical section that is locked, the thread spins:
     * it enters a loop which iterates spin count times, checking to see if the lock is released.
     * If the lock is not released before the loop finishes, the thread goes to sleep to wait for
     * the lock to be released.
     */
    if (!InitializeCriticalSectionAndSpinCount(&_critical_section, __SPIN_COUNT_VALUE__)) {
        _is_init = false;
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    _is_init = true;

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsCriticalClose(void) {

    if (!_is_init) {
        return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
    }

    DeleteCriticalSection(&_critical_section);

    _is_init = false;

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsCriticalEnter(uint32_t* const specificDataPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(specificDataPtr);

    if (!_is_init) {
        return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
    }

    EnterCriticalSection(&_critical_section);

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsCriticalExit(uint32_t* const specificDataPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(specificDataPtr);

    if (!_is_init) {
        return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
    }

    LeaveCriticalSection(&_critical_section);

    return TOMMRO_C_ERR_SUCCESS;
}

#endif
