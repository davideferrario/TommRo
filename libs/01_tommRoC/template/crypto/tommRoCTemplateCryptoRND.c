
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateCryptoRND.h"

#include "crypto/env/tommRoCTemplateCryptoEnvironmentRND.h"

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
#if defined (__TOMMROC_USE_CRYPTO_PRNG_AS_RND_TEMPLATE__)
static tommRoC_err_enum_t _rnd_retrive(
                uint8_t*    const   bufferPtr,
        const   uint32_t            outputLen) {

    uint32_t value;
    uint32_t remaining;
    uint32_t toCopy;
    uint8_t* ptr;

    remaining   = outputLen;
    ptr         = bufferPtr;

    while (0 != remaining) {

        value = tommRoCUtilU32Prng();

        toCopy = tommRoCMathMin(sizeof(value), remaining);

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(ptr, &value, toCopy));

        remaining   -= toCopy;
        ptr         += toCopy;
    }

    return TOMMRO_C_ERR_SUCCESS;
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateCryptoRNDStart(void) {

#if defined (__TOMMROC_USE_CRYPTO_PRNG_AS_RND_TEMPLATE__)

    /**
     * NOTE: seed data is compile timestamp + execution timestamp (if available)
     * UUID is not used because it is added in tommRoCTemplateCryptoEnvironmentRNDPrngAddSeed function.
     */
    static const char compileTimestampChar[] = TOMMRO_C_UTIL_COMPILE_TIMESTAMP;
    uint8_t seedDataBuffer[TOMMROC_UTIL_STRING_ARR_LENGTH(compileTimestampChar) + TOMMROC_UTIL_U32_SIZE];

    bool isTimestampInit;
    bool isDateTimeInit;

    void* ptr;
    uint16_t bSize;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(seedDataBuffer, 0x00, sizeof(seedDataBuffer)));

    ptr     = seedDataBuffer;
    bSize   = sizeof(seedDataBuffer);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilBufferAppendString(ptr, bSize, compileTimestampChar, &ptr, &bSize));

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsIsInitEnv(TOMMRO_C_OS_TIMESTAMP_FUNCT, &isTimestampInit));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsIsInitEnv(TOMMRO_C_OS_DATE_TIME_FUNCT, &isDateTimeInit));
    if (isTimestampInit || isDateTimeInit) {
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilBufferAppendU32MSB(ptr, bSize, tommRoCOsGetTimestamp(), &ptr, &bSize));
    }

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCUtilPrngInit());

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilPrngAddSeed(seedDataBuffer, sizeof(seedDataBuffer)));
    tommRoCTemplateCryptoEnvironmentRNDPrngAddSeed();

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCCryptoRNDInitEnv(_rnd_retrive));

    return TOMMRO_C_ERR_SUCCESS;

#elif defined (__TOMMROC_USE_CRYPTO_RND_TEMPLATE__)
    return tommRoCTemplateCryptoEnvironmentRNDStart();
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateCryptoRNDStop(void) {
    
#if defined (__TOMMROC_USE_CRYPTO_PRNG_AS_RND_TEMPLATE__)

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCCryptoRNDCloseEnv());
            
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCUtilPrngClose());

    return TOMMRO_C_ERR_SUCCESS;

#elif defined (__TOMMROC_USE_CRYPTO_RND_TEMPLATE__)
    return tommRoCTemplateCryptoEnvironmentRNDStop();
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}
