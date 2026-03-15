
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateDES3.h"

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

tommRoC_sw_err_enum_t tommRoCSwTemplateDES3Start(void) {
    
#if defined (__TOMMROC_SW_USE_DES3_CBC_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwDES3_CBC_Start());
#endif

#if defined (__TOMMROC_SW_USE_DES3_ECB_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwDES3_ECB_Start());
#endif

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateDES3Stop(void) {

#if defined (__TOMMROC_SW_USE_DES3_CBC_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwDES3_CBC_Stop());
#endif

#if defined (__TOMMROC_SW_USE_DES3_ECB_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwDES3_ECB_Stop());
#endif

    return TOMMRO_C_SW_ERR_SUCCESS;
}
