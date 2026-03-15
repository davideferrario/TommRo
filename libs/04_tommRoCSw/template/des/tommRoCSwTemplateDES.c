
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateDES.h"

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

tommRoC_sw_err_enum_t tommRoCSwTemplateDESStart(void) {
    
#if defined (__TOMMROC_SW_USE_DES_CBC_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwDES_CBC_Start());
#endif

#if defined (__TOMMROC_SW_USE_DES_ECB_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwDES_ECB_Start());
#endif

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateDESStop(void) {

#if defined (__TOMMROC_SW_USE_DES_CBC_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwDES_CBC_Stop());
#endif

#if defined (__TOMMROC_SW_USE_DES_ECB_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwDES_ECB_Stop());
#endif

    return TOMMRO_C_SW_ERR_SUCCESS;
}
