
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateMMCCommon.h"

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

tommRoC_hw_err_enum_t tommRoCHwTemplateMMCCommonStart(
        tommRoC_hw_err_enum_t (*environmentStartFunctPtr)(tommRoC_hw_mmc_cb_funct_t* const),
                tommRoC_hw_mmc_cb_funct_t*  const   cbFunctPtr,
                tommRoC_hw_mmc_t*           const   MMCHandlePtr) {

    TOMMROC_ASSERT_NOT_NULL(environmentStartFunctPtr);
    TOMMROC_ASSERT_NOT_NULL(cbFunctPtr);
    TOMMROC_ASSERT_NOT_NULL(MMCHandlePtr);

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwMMCCbFunctReset(cbFunctPtr));
    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(environmentStartFunctPtr(cbFunctPtr));
    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwMMCInit(cbFunctPtr, MMCHandlePtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}
