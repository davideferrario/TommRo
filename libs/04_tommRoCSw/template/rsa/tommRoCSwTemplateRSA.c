
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateRSA.h"

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

tommRoC_sw_err_enum_t tommRoCSwTemplateRSAStart(void) {

#if defined (__TOMMROC_SW_USE_RSA_512_BIT_TEMPLATE__)   ||  \
    defined (__TOMMROC_SW_USE_RSA_1024_BIT_TEMPLATE__)  ||  \
    defined (__TOMMROC_SW_USE_RSA_2048_BIT_TEMPLATE__)  ||  \
    defined (__TOMMROC_SW_USE_RSA_4096_BIT_TEMPLATE__)

#if defined (__TOMMROC_SW_USE_RSA_COMPLETE_TEMPLATE__)

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwRSAStart());
#elif defined (__TOMMROC_SW_USE_RSA_MINIMUM_PLUS_SIGN_TEMPLATE__)

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwRSAStartMinimumPlusSign());
#elif defined (__TOMMROC_SW_USE_RSA_MINIMUM_PLUS_VERIFY_TEMPLATE__)

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwRSAStartMinimumPlusVerify());            
#else

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwRSAStartMinimum());
#endif
#endif

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateRSAStop(void) {

#if defined (__TOMMROC_SW_USE_RSA_512_BIT_TEMPLATE__)   ||  \
    defined (__TOMMROC_SW_USE_RSA_1024_BIT_TEMPLATE__)  ||  \
    defined (__TOMMROC_SW_USE_RSA_2048_BIT_TEMPLATE__)  ||  \
    defined (__TOMMROC_SW_USE_RSA_4096_BIT_TEMPLATE__)

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwRSAStop());
#endif

    return TOMMRO_C_SW_ERR_SUCCESS;
}
