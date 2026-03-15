
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateMemory.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include <stdlib.h>
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/

// Different version ECDH key size needed memory size (empiric values).
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
#define __TOMMROC_SW_TEMPLATE_ECDH_COMPLETE_MEMORY_SIZE__           (98 * 256)
#else
#define __TOMMROC_SW_TEMPLATE_ECDH_COMPLETE_MEMORY_SIZE__           (69 * 256)
#endif
#define __TOMMROC_SW_TEMPLATE_ECDH_MAX_KEY_256_BIT_MEMORY_SIZE__    (26 * 256)

// Different version RSA key size needed memory size (empiric values).
#define __TOMMROC_SW_TEMPLATE_RSA_MAX_KEY_512_BIT_MEMORY_SIZE__     (16 * 256)
#define __TOMMROC_SW_TEMPLATE_RSA_MAX_KEY_1024_BIT_MEMORY_SIZE__    (30 * 256)
#define __TOMMROC_SW_TEMPLATE_RSA_MAX_KEY_2048_BIT_MEMORY_SIZE__    (49 * 256)
#define __TOMMROC_SW_TEMPLATE_RSA_MAX_KEY_4096_BIT_MEMORY_SIZE__    (87 * 256)


// ARM/XC8/XC16/XC32 have ECDH ECP key size limited to 256 bit
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)   ||  \
    defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)   ||  \
    defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC16)  ||  \
    defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC32)
#define __TOMMROC_SW_TEMPLATE_ECDH_NEEDED_MEMORY_SIZE__     (__TOMMROC_SW_TEMPLATE_ECDH_MAX_KEY_256_BIT_MEMORY_SIZE__)
#else
#define __TOMMROC_SW_TEMPLATE_ECDH_NEEDED_MEMORY_SIZE__     (__TOMMROC_SW_TEMPLATE_ECDH_COMPLETE_MEMORY_SIZE__)
#endif

// Different RSA needed memory size
#if defined (__TOMMROC_SW_USE_RSA_512_BIT_TEMPLATE__)
#define __TOMMROC_SW_TEMPLATE_RSA_NEEDED_MEMORY_SIZE__      (__TOMMROC_SW_TEMPLATE_RSA_MAX_KEY_512_BIT_MEMORY_SIZE__)
#elif defined (__TOMMROC_SW_USE_RSA_1024_BIT_TEMPLATE__)
#define __TOMMROC_SW_TEMPLATE_RSA_NEEDED_MEMORY_SIZE__      (__TOMMROC_SW_TEMPLATE_RSA_MAX_KEY_1024_BIT_MEMORY_SIZE__)
#elif defined (__TOMMROC_SW_USE_RSA_2048_BIT_TEMPLATE__)
#define __TOMMROC_SW_TEMPLATE_RSA_NEEDED_MEMORY_SIZE__      (__TOMMROC_SW_TEMPLATE_RSA_MAX_KEY_2048_BIT_MEMORY_SIZE__)
#elif defined (__TOMMROC_SW_USE_RSA_4096_BIT_TEMPLATE__)
#define __TOMMROC_SW_TEMPLATE_RSA_NEEDED_MEMORY_SIZE__      (__TOMMROC_SW_TEMPLATE_RSA_MAX_KEY_4096_BIT_MEMORY_SIZE__)
#endif


// Define of needed memory size.
#if defined (__TOMMROC_SW_USE_AES_CBC_TEMPLATE__)           // AES_CBC
#define __TOMMROC_SW_TEMPLATE_AES_CBC_MEMORY_SIZE__         (8)
#endif
#if defined (__TOMMROC_SW_USE_AES_ECB_TEMPLATE__)           // AES_ECB
#define __TOMMROC_SW_TEMPLATE_AES_ECB_MEMORY_SIZE__         (8)
#endif
#if defined (__TOMMROC_SW_USE_CTR_DRBG_TEMPLATE__)          // CTR_DRBG
#define __TOMMROC_SW_TEMPLATE_CTR_DRBG_MEMORY_SIZE__        (8)
#endif
#if defined (__TOMMROC_SW_USE_DES_CBC_TEMPLATE__)           // DES_CBC
#define __TOMMROC_SW_TEMPLATE_DES_CBC_MEMORY_SIZE__         (8)
#endif
#if defined (__TOMMROC_SW_USE_DES_ECB_TEMPLATE__)           // DES_ECB
#define __TOMMROC_SW_TEMPLATE_DES_ECB_MEMORY_SIZE__         (8)
#endif
#if defined (__TOMMROC_SW_USE_DES3_CBC_TEMPLATE__)          // DES3_CBC
#define __TOMMROC_SW_TEMPLATE_DES3_CBC_MEMORY_SIZE__        (8)
#endif
#if defined (__TOMMROC_SW_USE_DES3_ECB_TEMPLATE__)          // DES3_ECB
#define __TOMMROC_SW_TEMPLATE_DES3_ECB_MEMORY_SIZE__        (8)
#endif
#if defined (__TOMMROC_SW_USE_ECDH_TEMPLATE__)              // ECDH
#define __TOMMROC_SW_TEMPLATE_ECDH_MEMORY_SIZE__            (__TOMMROC_SW_TEMPLATE_ECDH_NEEDED_MEMORY_SIZE__)
#endif
#if defined (__TOMMROC_SW_USE_ENTROPY_TEMPLATE__)           // ENTROPY
#define __TOMMROC_SW_TEMPLATE_ENTROPY_MEMORY_SIZE__         (8)
#endif
#if defined (__TOMMROC_SW_USE_HMAC_DRBG_TEMPLATE__)         // HMAC_DRB
#define __TOMMROC_SW_TEMPLATE_HMAC_DRBG_MEMORY_SIZE__       (8)
#endif
#if defined (__TOMMROC_SW_USE_MD2_TEMPLATE__)               // MD2
#define __TOMMROC_SW_TEMPLATE_MD2_MEMORY_SIZE__             (8)
#endif
#if defined (__TOMMROC_SW_USE_MD4_TEMPLATE__)               // MD4
#define __TOMMROC_SW_TEMPLATE_MD4_MEMORY_SIZE__             (8)
#endif
#if defined (__TOMMROC_SW_USE_MD5_TEMPLATE__)               // MD5
#define __TOMMROC_SW_TEMPLATE_MD5_MEMORY_SIZE__             (8)
#endif
#if defined (__TOMMROC_SW_USE_MD_HMAC_SHA1_TEMPLATE__)      // MD HMAC SHA1
#define __TOMMROC_SW_TEMPLATE_MD_HMAC_SHA1_MEMORY_SIZE__    (8)
#endif
#if defined (__TOMMROC_SW_USE_MD_HMAC_SHA256_TEMPLATE__)    // MD HMAC SHA256
#define __TOMMROC_SW_TEMPLATE_MD_HMAC_SHA256_MEMORY_SIZE__  (8)
#endif
#if defined (__TOMMROC_SW_USE_MD_HMAC_SHA512_TEMPLATE__)    // MD HMAC SHA512
#define __TOMMROC_SW_TEMPLATE_MD_HMAC_SHA512_MEMORY_SIZE__  (8)
#endif
#if defined (__TOMMROC_SW_TEMPLATE_RSA_NEEDED_MEMORY_SIZE__)// RSA
#define __TOMMROC_SW_TEMPLATE_RSA_MEMORY_SIZE__             (__TOMMROC_SW_TEMPLATE_RSA_NEEDED_MEMORY_SIZE__)
#endif
#if defined (__TOMMROC_SW_USE_SHA1_TEMPLATE__)              // SHA1
#define __TOMMROC_SW_TEMPLATE_SHA1_MEMORY_SIZE__            (8)
#endif
#if defined (__TOMMROC_SW_USE_SHA224_TEMPLATE__)            // SHA224
#define __TOMMROC_SW_TEMPLATE_SHA224_MEMORY_SIZE__          (8)
#endif
#if defined (__TOMMROC_SW_USE_SHA256_TEMPLATE__)            // SHA256
#define __TOMMROC_SW_TEMPLATE_SHA256_MEMORY_SIZE__          (8)
#endif
#if defined (__TOMMROC_SW_USE_SHA384_TEMPLATE__)            // SHA384
#define __TOMMROC_SW_TEMPLATE_SHA384_MEMORY_SIZE__          (8)
#endif
#if defined (__TOMMROC_SW_USE_SHA512_TEMPLATE__)            // SHA512
#define __TOMMROC_SW_TEMPLATE_SHA512_MEMORY_SIZE__          (8)
#endif
#if defined (__TOMMROC_SW_USE_SSL_TEMPLATE__)               // SSL
#if defined (__TOMMROC_SW_USE_SSL_PARALLEL_CONNECTION_AMOUNT__)
#define __TOMMROC_SW_TEMPLATE_SSL_MEMORY_SIZE__             (__TOMMROC_SW_USE_SSL_PARALLEL_CONNECTION_AMOUNT__ * (24 * 256))
#else
#define __TOMMROC_SW_TEMPLATE_SSL_MEMORY_SIZE__             (276 * 256)
#endif
#endif


// If not enabled, needed memory size is null.
#if !defined  (__TOMMROC_SW_TEMPLATE_AES_CBC_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_AES_CBC_MEMORY_SIZE__         (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_AES_ECB_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_AES_ECB_MEMORY_SIZE__         (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_CTR_DRBG_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_CTR_DRBG_MEMORY_SIZE__        (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_DES_CBC_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_DES_CBC_MEMORY_SIZE__         (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_DES_ECB_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_DES_ECB_MEMORY_SIZE__         (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_DES3_CBC_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_DES3_CBC_MEMORY_SIZE__        (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_DES3_ECB_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_DES3_ECB_MEMORY_SIZE__        (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_ECDH_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_ECDH_MEMORY_SIZE__            (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_ENTROPY_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_ENTROPY_MEMORY_SIZE__         (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_HMAC_DRBG_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_HMAC_DRBG_MEMORY_SIZE__       (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_MD2_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_MD2_MEMORY_SIZE__             (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_MD4_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_MD4_MEMORY_SIZE__             (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_MD5_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_MD5_MEMORY_SIZE__             (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_MD_HMAC_SHA1_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_MD_HMAC_SHA1_MEMORY_SIZE__    (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_MD_HMAC_SHA256_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_MD_HMAC_SHA256_MEMORY_SIZE__  (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_MD_HMAC_SHA512_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_MD_HMAC_SHA512_MEMORY_SIZE__  (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_RSA_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_RSA_MEMORY_SIZE__             (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_SHA1_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_SHA1_MEMORY_SIZE__            (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_SHA224_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_SHA224_MEMORY_SIZE__          (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_SHA256_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_SHA256_MEMORY_SIZE__          (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_SHA384_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_SHA384_MEMORY_SIZE__          (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_SHA512_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_SHA512_MEMORY_SIZE__          (0)
#endif
#if !defined  (__TOMMROC_SW_TEMPLATE_SSL_MEMORY_SIZE__)
#define __TOMMROC_SW_TEMPLATE_SSL_MEMORY_SIZE__             (0)
#endif


// Define needed memory size as sum.
#define __TOMMROC_SW_TEMPLATE_MEMORY_STACK_SIZE__                   \
        (   __TOMMROC_SW_TEMPLATE_AES_CBC_MEMORY_SIZE__         +   \
            __TOMMROC_SW_TEMPLATE_AES_ECB_MEMORY_SIZE__         +   \
            __TOMMROC_SW_TEMPLATE_CTR_DRBG_MEMORY_SIZE__        +   \
            __TOMMROC_SW_TEMPLATE_DES_CBC_MEMORY_SIZE__         +   \
            __TOMMROC_SW_TEMPLATE_DES_ECB_MEMORY_SIZE__         +   \
            __TOMMROC_SW_TEMPLATE_DES3_CBC_MEMORY_SIZE__        +   \
            __TOMMROC_SW_TEMPLATE_DES3_ECB_MEMORY_SIZE__        +   \
            __TOMMROC_SW_TEMPLATE_ECDH_MEMORY_SIZE__            +   \
            __TOMMROC_SW_TEMPLATE_ENTROPY_MEMORY_SIZE__         +   \
            __TOMMROC_SW_TEMPLATE_HMAC_DRBG_MEMORY_SIZE__       +   \
            __TOMMROC_SW_TEMPLATE_MD2_MEMORY_SIZE__             +   \
            __TOMMROC_SW_TEMPLATE_MD4_MEMORY_SIZE__             +   \
            __TOMMROC_SW_TEMPLATE_MD5_MEMORY_SIZE__             +   \
            __TOMMROC_SW_TEMPLATE_MD_HMAC_SHA1_MEMORY_SIZE__    +   \
            __TOMMROC_SW_TEMPLATE_MD_HMAC_SHA256_MEMORY_SIZE__  +   \
            __TOMMROC_SW_TEMPLATE_MD_HMAC_SHA512_MEMORY_SIZE__  +   \
            __TOMMROC_SW_TEMPLATE_RSA_MEMORY_SIZE__             +   \
            __TOMMROC_SW_TEMPLATE_SHA1_MEMORY_SIZE__            +   \
            __TOMMROC_SW_TEMPLATE_SHA224_MEMORY_SIZE__          +   \
            __TOMMROC_SW_TEMPLATE_SHA256_MEMORY_SIZE__          +   \
            __TOMMROC_SW_TEMPLATE_SHA384_MEMORY_SIZE__          +   \
            __TOMMROC_SW_TEMPLATE_SHA512_MEMORY_SIZE__          +   \
            __TOMMROC_SW_TEMPLATE_SSL_MEMORY_SIZE__                 )

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

tommRoC_sw_err_enum_t tommRoCSwTemplateMemoryStart(void) {
    
#if (__TOMMROC_SW_TEMPLATE_MEMORY_STACK_SIZE__ > 0)

#if !defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
    static uint8_t stackMemory[__TOMMROC_SW_TEMPLATE_MEMORY_STACK_SIZE__];
    return tommRoCSwMemoryInit(stackMemory, sizeof(stackMemory));
#else
    // NOTE: for ESP32 use malloc to avoid not enough static ram available issue
    static uint8_t* stackMemoryPtr;
    stackMemoryPtr = malloc(__TOMMROC_SW_TEMPLATE_MEMORY_STACK_SIZE__);
    return tommRoCSwMemoryInit(stackMemoryPtr, __TOMMROC_SW_TEMPLATE_MEMORY_STACK_SIZE__);
#endif

#else

    return TOMMRO_C_SW_ERR_SUCCESS;
#endif
}
