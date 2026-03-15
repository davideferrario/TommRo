
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateMDHmac.h"

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

tommRoC_sw_err_enum_t tommRoCSwTemplateMDHmacStart(void) {

#if defined (__TOMMROC_SW_USE_MD_HMAC_SHA1_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwMDHmacSHA1Start());
#endif

#if defined (__TOMMROC_SW_USE_MD_HMAC_SHA256_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwMDHmacSHA256Start());
#endif

#if defined (__TOMMROC_SW_USE_MD_HMAC_SHA512_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwMDHmacSHA512Start());
#endif

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateMDHmacStop(void) {

#if defined (__TOMMROC_SW_USE_MD_HMAC_SHA1_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwMDHmacSHA1Stop());
#endif

#if defined (__TOMMROC_SW_USE_MD_HMAC_SHA256_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwMDHmacSHA256Stop());
#endif

#if defined (__TOMMROC_SW_USE_MD_HMAC_SHA512_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwMDHmacSHA512Stop());
#endif

    return TOMMRO_C_SW_ERR_SUCCESS;
}
