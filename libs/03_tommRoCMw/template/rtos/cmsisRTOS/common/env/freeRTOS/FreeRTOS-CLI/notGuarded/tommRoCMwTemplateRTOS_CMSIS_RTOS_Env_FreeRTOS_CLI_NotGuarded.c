
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_CMSIS_RTOS_Env_FreeRTOS_CLI_NotGuarded.h"

#if defined (__TOMMROC_MW_USE_THREAD_CMSIS_V1_RTOS_TEMPLATE__)
#include "rtos/cmsisRTOS/V1/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"
#elif defined (__TOMMROC_MW_USE_THREAD_CMSIS_V2_RTOS_TEMPLATE__)
#include "rtos/cmsisRTOS/V2/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"
#endif

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)

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

/*******************************************************************************
 * local functions
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_Env_FreeRTOS_CLINotGuardedRegisterCommand(const CLI_Command_Definition_t* const commandToRegisterPtr) {

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)

    if (pdPASS != FreeRTOS_CLIRegisterCommand(commandToRegisterPtr)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(commandToRegisterPtr);
    return TOMMRO_C_MW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

bool tommRoCMwTemplateRTOS_CMSIS_RTOS_Env_FreeRTOS_CLINotGuardedProcessCommand(const char* const commandInputStrPtr, char* writeBufferStrPtr, uint32_t writeBufferStrSize) {

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)

    BaseType_t res;

    res = FreeRTOS_CLIProcessCommand(
            commandInputStrPtr,
            writeBufferStrPtr,
            (size_t) writeBufferStrSize);

    return ((pdFALSE == res) ? (false) : (true));
#else
    TOMMROC_UTIL_UNUSED_PARAM(commandInputStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(writeBufferStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(writeBufferStrSize);
    return false;
#endif
}

#endif
