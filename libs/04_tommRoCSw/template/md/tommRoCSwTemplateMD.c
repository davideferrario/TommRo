
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateMD.h"

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

tommRoC_sw_err_enum_t tommRoCSwTemplateMDStart(void) {

#if defined (__TOMMROC_SW_USE_MD2_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwMD2Start());
#endif

#if defined (__TOMMROC_SW_USE_MD4_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwMD4Start());
#endif

#if defined (__TOMMROC_SW_USE_MD5_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwMD5Start());
#endif

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateMDStop(void) {
    
#if defined (__TOMMROC_SW_USE_MD2_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwMD2Stop());
#endif

#if defined (__TOMMROC_SW_USE_MD4_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwMD4Stop());
#endif

#if defined (__TOMMROC_SW_USE_MD5_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwMD5Stop());
#endif

    return TOMMRO_C_SW_ERR_SUCCESS;
}
