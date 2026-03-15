
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "crypto/tommRoCTemplateCryptoAES.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)

#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__) || defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)

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

#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateCryptoAESStart(void) {

#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__) || defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateCryptoAESStop(void) {

#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__) || defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

#endif
