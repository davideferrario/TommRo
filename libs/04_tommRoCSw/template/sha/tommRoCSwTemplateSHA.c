
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateSHA.h"

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

tommRoC_sw_err_enum_t tommRoCSwTemplateSHAStart(void) {

#if defined (__TOMMROC_SW_USE_SHA1_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwSHA1Start());
#endif

#if defined (__TOMMROC_SW_USE_SHA224_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwSHA224Start());
#endif

#if defined (__TOMMROC_SW_USE_SHA256_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwSHA256Start());
#endif

#if defined (__TOMMROC_SW_USE_SHA384_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwSHA384Start());
#endif

#if defined (__TOMMROC_SW_USE_SHA512_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwSHA512Start());
#endif

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateSHAStop(void) {
    
#if defined (__TOMMROC_SW_USE_SHA1_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwSHA1Stop());
#endif

#if defined (__TOMMROC_SW_USE_SHA224_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwSHA224Stop());
#endif

#if defined (__TOMMROC_SW_USE_SHA256_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwSHA256Stop());
#endif

#if defined (__TOMMROC_SW_USE_SHA384_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwSHA384Stop());
#endif

#if defined (__TOMMROC_SW_USE_SHA512_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwSHA512Stop());
#endif

    return TOMMRO_C_SW_ERR_SUCCESS;
}
