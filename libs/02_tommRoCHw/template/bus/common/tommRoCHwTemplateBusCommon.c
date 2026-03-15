
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusCommon.h"

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

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonStart(
        const   tommRoC_hw_bus_type_enum_t                          type,
        tommRoC_hw_err_enum_t (*environmentStartFunctPtr)(tommRoC_hw_bus_cb_funct_t* const),
                tommRoC_hw_bus_cb_funct_t*                  const   cbFunctPtr,
                tommRoC_hw_bus_t*                           const   busHandlePtr) {

    TOMMROC_ASSERT_NOT_NULL(environmentStartFunctPtr);
    TOMMROC_ASSERT_NOT_NULL(cbFunctPtr);
    TOMMROC_ASSERT_NOT_NULL(busHandlePtr);

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwBusCbFunctReset(cbFunctPtr));
    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(environmentStartFunctPtr(cbFunctPtr));
    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwBusInit(type, cbFunctPtr, busHandlePtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}
