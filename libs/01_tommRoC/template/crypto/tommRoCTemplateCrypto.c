
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateCrypto.h"

#include "crypto/tommRoCTemplateCryptoAES.h"
#include "crypto/tommRoCTemplateCryptoRND.h"
#include "crypto/tommRoCTemplateCryptoSHA1.h"
#include "crypto/tommRoCTemplateCryptoSHA224.h"
#include "crypto/tommRoCTemplateCryptoSHA256.h"
#include "crypto/tommRoCTemplateCryptoSHA384.h"
#include "crypto/tommRoCTemplateCryptoSHA512.h"

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
#if defined (__TOMMROC_CRYPTO_TEMPLATE_IS_USED__)

static tommRoC_err_enum_t _crypto_start(void) {

#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__) || defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateCryptoAESStart());
#endif

#if defined (__TOMMROC_USE_CRYPTO_RND_TEMPLATE__) || defined (__TOMMROC_USE_CRYPTO_PRNG_AS_RND_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateCryptoRNDStart());
#endif

#if defined (__TOMMROC_USE_CRYPTO_SHA1_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateCryptoSHA1Start());
#endif

#if defined (__TOMMROC_USE_CRYPTO_SHA224_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateCryptoSHA224Start());
#endif

#if defined (__TOMMROC_USE_CRYPTO_SHA256_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateCryptoSHA256Start());
#endif

#if defined (__TOMMROC_USE_CRYPTO_SHA384_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateCryptoSHA384Start());
#endif

#if defined (__TOMMROC_USE_CRYPTO_SHA512_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateCryptoSHA512Start());
#endif

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _crypto_stop(void) {

#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__) || defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateCryptoAESStop());
#endif

#if defined (__TOMMROC_USE_CRYPTO_RND_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateCryptoRNDStop());
#endif

#if defined (__TOMMROC_USE_CRYPTO_SHA1_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateCryptoSHA1Stop());
#endif

#if defined (__TOMMROC_USE_CRYPTO_SHA224_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateCryptoSHA224Stop());
#endif

#if defined (__TOMMROC_USE_CRYPTO_SHA256_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateCryptoSHA256Stop());
#endif

#if defined (__TOMMROC_USE_CRYPTO_SHA384_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateCryptoSHA384Stop());
#endif

#if defined (__TOMMROC_USE_CRYPTO_SHA512_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateCryptoSHA512Stop());
#endif

    return TOMMRO_C_ERR_SUCCESS;
}

#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateCryptoStart(void) {

#if defined (__TOMMROC_CRYPTO_TEMPLATE_IS_USED__)
    return _crypto_start();
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateCryptoStop(void) {
    
#if defined (__TOMMROC_CRYPTO_TEMPLATE_IS_USED__)
    return _crypto_stop();
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}
