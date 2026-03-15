
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateNetSNTP.h"

#include "net/SNTP/handler/tommRoCHwTemplateNetSNTPHandler.h"

#if defined (__TOMMROC_HW_USE_SNTP_NET_TEMPLATE__)

#include "TOMMROC.h"
#include "TOMMROCHw.h"
#include "TOMMROCMw.h"

#include "TOMMROCMwTemplate.h"

#if !defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
#error "Multi thread environment is needed for SNTP"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __SNTP_TASK_STACK_SIZE_BYTE__   (320)

#define __TASK_EXECUTE_RATE_MSEC__  (250)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static tommRoC_mw_template_thread_t _SNTP_thread;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static void _SNTP_thread_main(void* const argument) {

    TOMMROC_UTIL_UNUSED_PARAM(argument);

    for (;;) {

        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateNetSNTPHandlerRun());

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__TASK_EXECUTE_RATE_MSEC__));
    }
}

static tommRoC_hw_err_enum_t _sntp_start_funct(void) {

    static const char threadNameStr[] = "HwTSNTP";

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCMwThreadCreateConfig(_SNTP_thread_main, NULL, threadNameStr, TOMMRO_C_MW_THREAD_PRIORITY_NORMAL, __SNTP_TASK_STACK_SIZE_BYTE__, &_SNTP_thread),
            TOMMRO_C_HW_LOW_LEVEL_ERR);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _sntp_stop_funct(void) {

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCMwThreadDestroy(&_SNTP_thread),
            TOMMRO_C_HW_LOW_LEVEL_ERR);

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateNetSNTPStart(void) {

#if defined (__TOMMROC_HW_USE_SNTP_NET_TEMPLATE__)

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetSNTPInitStart(_sntp_start_funct));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetSNTPInitStop(_sntp_stop_funct));

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNetSNTPStop(void) {

#if defined (__TOMMROC_HW_USE_SNTP_NET_TEMPLATE__)

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetSNTPCloseEnv(TOMMROC_HW_NET_SNTP_START_FUNCT));
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetSNTPCloseEnv(TOMMROC_HW_NET_SNTP_STOP_FUNCT));

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNetSNTPHandle(void) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwTemplateNetSNTPHandlerRun());

    return TOMMRO_C_HW_ERR_SUCCESS;
}
