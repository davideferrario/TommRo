
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_CMSIS_RTOS_Env_FreeRTOS_CLI.h"

#if defined (__TOMMROC_MW_USE_THREAD_CMSIS_V1_RTOS_TEMPLATE__)
#include "rtos/cmsisRTOS/V1/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"
#elif defined (__TOMMROC_MW_USE_THREAD_CMSIS_V2_RTOS_TEMPLATE__)
#include "rtos/cmsisRTOS/V2/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"
#endif

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)

#include "rtos/cmsisRTOS/common/env/freeRTOS/FreeRTOS-CLI/notGuarded/tommRoCMwTemplateRTOS_CMSIS_RTOS_Env_FreeRTOS_CLI_NotGuarded.h"

#include "rtos/cmsisRTOS/common/env/freeRTOS/FreeRTOS-CLI/lib/FreeRTOS_CLI.h"

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
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_Env_FreeRTOS_CLIInit(void) {

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwMutexCreate(&_mutex));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCGuardInit(_lock, _un_lock, &_guard));

    return TOMMRO_C_MW_ERR_SUCCESS;
#else
    return TOMMRO_C_MW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_Env_FreeRTOS_CLIClose(void) {

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCGuardClear(&_guard));
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwMutexDestroy(&_mutex));

    return TOMMRO_C_MW_ERR_SUCCESS;
#else
    return TOMMRO_C_MW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_Env_FreeRTOS_CLIRegisterCommand(const CLI_Command_Definition_t* const commandToRegisterPtr) {

    TOMMROC_MW_UTIL_SYNCHRO_TOMMROC_MW_LIB_FUNCT(
            &_guard,
            tommRoCMwTemplateRTOS_CMSIS_RTOS_Env_FreeRTOS_CLINotGuardedRegisterCommand(
                    commandToRegisterPtr));
}

bool tommRoCMwTemplateRTOS_CMSIS_RTOS_Env_FreeRTOS_CLIProcessCommand(const char* const commandInputStrPtr, char* writeBufferStrPtr, uint32_t writeBufferStrSize) {

    TOMMROC_GUARD_SYNCHRO_WITH_RESULT_FUNCT(
            bool,
            &_guard,
            false,
            tommRoCMwTemplateRTOS_CMSIS_RTOS_Env_FreeRTOS_CLINotGuardedProcessCommand(
                    commandInputStrPtr,
                    writeBufferStrPtr,
                    writeBufferStrSize));
}

const char* tommRoCMwTemplateRTOS_CMSIS_RTOS_Env_FreeRTOS_CLIGetParameter(const char* const commandInputStrPtr, const uint32_t paramIdx, uint32_t* const paramStrLenPtr) {

    // NOTE: CLIGetParameter MUST not be in guarded because it is called by a command implementation - already guarded.
#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)

    BaseType_t parameterStringLength;
    const char* res;

    res = FreeRTOS_CLIGetParameter(
            commandInputStrPtr,
            (UBaseType_t) paramIdx,
            &parameterStringLength);

    *paramStrLenPtr = (uint32_t) parameterStringLength;

    return res;
#else
    TOMMROC_UTIL_UNUSED_PARAM(commandInputStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(paramIdx);
    TOMMROC_UTIL_UNUSED_PARAM(paramStrLenPtr);
    return NULL;
#endif
}

#endif
