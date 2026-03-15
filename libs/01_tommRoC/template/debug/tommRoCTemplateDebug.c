
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateDebug.h"

/******************** Print debug template */
#if defined (__TOMMROC_PRINT_DEBUG_TEMPLATE_IS_USED__)
#include "debug/print/tommRoCTemplateDebugPrint.h"
#endif

/******************** Save debug template */
#if defined (__TOMMROC_SAVE_DEBUG_TEMPLATE_IS_USED__)
#include "debug/save/tommRoCTemplateDebugSave.h"
#endif

#if defined (__TOMMROC_PRINT_DEBUG_TEMPLATE_IS_USED__) || defined (__TOMMROC_SAVE_DEBUG_TEMPLATE_IS_USED__)
#include "TOMMROC.h"
#include "TOMMROCHw.h"
#include "TOMMROCMw.h"
#include "TOMMROCPw.h"
#include "TOMMROCSw.h"
#include "TOMMROCTw.h"
#endif

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

#if defined (__TOMMROC_PRINT_DEBUG_TEMPLATE_IS_USED__)
static tommRoC_err_enum_t _start_print_debug(const tommRoC_template_debug_init_t* const templateInitPtr) {

    tommRoC_debug_print_env_init_t initPrintDebug = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_debug_print_env_init_t);

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateDebugPrintStart());

    initPrintDebug.debugPrintStr    = tommRoCTemplateDebugPrintStr;
    initPrintDebug.debugPrintStrLen = tommRoCTemplateDebugPrintStrLen;
    initPrintDebug.newLineStrPtr    = tommRoCTemplateDebugPrintNewLineStr();
    initPrintDebug.debugStatusPtr   = templateInitPtr->libDebugStatusPtr;
    initPrintDebug.guardPtr         = templateInitPtr->printGuardPtr;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCDebugInitEnv(&initPrintDebug));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCDebugSetProp(TOMMRO_C_DEBUG_IS_PRINT_PENDING_FUNCT_PTR_PROP, tommRoCTemplateDebugPrintIsPending));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwDebugInit(templateInitPtr->libDebugStatusPtr));
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwDebugInit(templateInitPtr->libDebugStatusPtr));
    TOMMROC_PW_ASSERT_TOMMROC_PW_LIB_FUNCT_SUCCESS(tommRoCPwDebugInit(templateInitPtr->libDebugStatusPtr));
    TOMMROC_SW_ASSERT_TOMMROC_SW_LIB_FUNCT_SUCCESS(tommRoCSwDebugInit(templateInitPtr->libDebugStatusPtr));
    TOMMROC_TW_ASSERT_TOMMROC_TW_LIB_FUNCT_SUCCESS(tommRoCTwDebugInit(templateInitPtr->libDebugStatusPtr));

    return TOMMRO_C_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_SAVE_DEBUG_TEMPLATE_IS_USED__)
static tommRoC_err_enum_t _start_save_debug(const tommRoC_template_debug_init_t* const templateInitPtr) {

    tommRoC_debug_save_env_init_t initSaveDebug = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_debug_save_env_init_t);

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateDebugSaveStart());

    initSaveDebug.debugSaveStr      = tommRoCTemplateDebugSaveStr;
    initSaveDebug.newLineStrPtr     = tommRoCTemplateDebugSaveNewLineStr();
    initSaveDebug.guardPtr          = templateInitPtr->saveGuardPtr;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCDebugExtendForSaveEnv(&initSaveDebug));

    return TOMMRO_C_ERR_SUCCESS;
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateDebugStart(
        const   tommRoC_template_debug_init_t*  const   templateInitPtr) {

    TOMMROC_ASSERT_NOT_NULL(templateInitPtr);

    TOMMROC_PARAM_CHECK_ON_NULL_RETURN_ERR(templateInitPtr);

#if defined (__TOMMROC_PRINT_DEBUG_TEMPLATE_IS_USED__)

    TOMMROC_ASSERT_NOT_NULL(templateInitPtr->libDebugStatusPtr);

    TOMMROC_PARAM_CHECK_ON_NULL_RETURN_ERR(templateInitPtr->libDebugStatusPtr);

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_start_print_debug(templateInitPtr));

#if defined (__TOMMROC_SAVE_DEBUG_TEMPLATE_IS_USED__)

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_start_save_debug(templateInitPtr));
#endif

    return TOMMRO_C_ERR_SUCCESS;

#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateDebugStop(void) {

#if defined (__TOMMROC_PRINT_DEBUG_TEMPLATE_IS_USED__) || defined (__TOMMROC_SAVE_DEBUG_TEMPLATE_IS_USED__)

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCDebugCloseEnv());

    return TOMMRO_C_ERR_SUCCESS;

#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}
