
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateMMC.h"

#include "MMC/common/tommRoCHwTemplateMMCCommon.h"
#include "MMC/env/tommRoCHwTemplateMMCEnvironment.h"

#include "TOMMROC.h"

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

tommRoC_hw_err_enum_t tommRoCHwTemplateMMC0Start(tommRoC_hw_mmc_t* const MMCHandlePtr) {

#if defined (__TOMMROC_HW_USE_MMC_0_TEMPLATE__)

    static tommRoC_hw_mmc_cb_funct_t cbFunct;

    return tommRoCHwTemplateMMCCommonStart(
            tommRoCHwTemplateMMCEnvironment0Start,
            &cbFunct,
            MMCHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(MMCHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateMMC1Start(tommRoC_hw_mmc_t* const MMCHandlePtr) {

#if defined (__TOMMROC_HW_USE_MMC_1_TEMPLATE__)

    static tommRoC_hw_mmc_cb_funct_t cbFunct;

    return tommRoCHwTemplateMMCCommonStart(
            tommRoCHwTemplateMMCEnvironment1Start,
            &cbFunct,
            MMCHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(MMCHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateMMC2Start(tommRoC_hw_mmc_t* const MMCHandlePtr) {

#if defined (__TOMMROC_HW_USE_MMC_2_TEMPLATE__)

    static tommRoC_hw_mmc_cb_funct_t cbFunct;

    return tommRoCHwTemplateMMCCommonStart(
            tommRoCHwTemplateMMCEnvironment2Start,
            &cbFunct,
            MMCHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(MMCHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateMMC3Start(tommRoC_hw_mmc_t* const MMCHandlePtr) {

#if defined (__TOMMROC_HW_USE_MMC_3_TEMPLATE__)

    static tommRoC_hw_mmc_cb_funct_t cbFunct;

    return tommRoCHwTemplateMMCCommonStart(
            tommRoCHwTemplateMMCEnvironment3Start,
            &cbFunct,
            MMCHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(MMCHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateMMC4Start(tommRoC_hw_mmc_t* const MMCHandlePtr) {

#if defined (__TOMMROC_HW_USE_MMC_4_TEMPLATE__)

    static tommRoC_hw_mmc_cb_funct_t cbFunct;

    return tommRoCHwTemplateMMCCommonStart(
            tommRoCHwTemplateMMCEnvironment4Start,
            &cbFunct,
            MMCHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(MMCHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateMMC5Start(tommRoC_hw_mmc_t* const MMCHandlePtr) {

#if defined (__TOMMROC_HW_USE_MMC_5_TEMPLATE__)

    static tommRoC_hw_mmc_cb_funct_t cbFunct;

    return tommRoCHwTemplateMMCCommonStart(
            tommRoCHwTemplateMMCEnvironment5Start,
            &cbFunct,
            MMCHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(MMCHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}
