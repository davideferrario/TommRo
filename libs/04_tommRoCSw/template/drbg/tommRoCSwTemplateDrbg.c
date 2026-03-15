
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateDrbg.h"

#include "TOMMROC.h"
#include "TOMMROCTemplate.h"

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

tommRoC_sw_err_enum_t tommRoCSwTemplateDrbgStart(void) {

#if defined (__TOMMROC_SW_USE_CTR_DRBG_TEMPLATE__) || defined (__TOMMROC_SW_USE_HMAC_DRBG_TEMPLATE__)
    // NOTE: personal data is compile timestamp + UUID + execution timestamp (if available)
    static const char compileTimestampChar[] = TOMMRO_C_UTIL_COMPILE_TIMESTAMP;
    uint8_t UUID[TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE];
    uint8_t UUIDLen;
    uint8_t envPersonalDataBuffer[TOMMROC_UTIL_STRING_ARR_LENGTH(compileTimestampChar) + TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE + TOMMROC_UTIL_U32_SIZE];

    bool isInit;
    bool isTimestampInit;
    bool isDateTimeInit;

    void* ptr;
    uint16_t bSize;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(envPersonalDataBuffer, 0x00, sizeof(envPersonalDataBuffer)));

    ptr     = envPersonalDataBuffer;
    bSize   = sizeof(envPersonalDataBuffer);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilBufferAppendString(ptr, bSize, compileTimestampChar, &ptr, &bSize));

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsIsInitEnv(TOMMRO_C_OS_GET_UUID_FUNCT, &isInit));
    if (isInit) {
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsGetUUID(UUID, sizeof(UUID), &UUIDLen));
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilBufferAppendArray(ptr, bSize, UUID, UUIDLen, &ptr, &bSize));
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsIsInitEnv(TOMMRO_C_OS_TIMESTAMP_FUNCT, &isTimestampInit));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsIsInitEnv(TOMMRO_C_OS_DATE_TIME_FUNCT, &isDateTimeInit));
    if (isTimestampInit || isDateTimeInit) {
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilBufferAppendU32MSB(ptr, bSize, tommRoCOsGetTimestamp(), &ptr, &bSize));
    }
#endif

#if defined (__TOMMROC_SW_USE_CTR_DRBG_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwCtrDrbgStart());
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwCtrDrbgSeed(envPersonalDataBuffer, sizeof(envPersonalDataBuffer)));
#endif

#if defined (__TOMMROC_SW_USE_HMAC_DRBG_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwHmacDrbgStart());
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwHmacDrbgSeed(envPersonalDataBuffer, sizeof(envPersonalDataBuffer)));
#endif

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateDrbgStop(void) {

#if defined (__TOMMROC_SW_USE_CTR_DRBG_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwCtrDrbgStop());
#endif

#if defined (__TOMMROC_SW_USE_HMAC_DRBG_TEMPLATE__)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwHmacDrbgStop());
#endif

    return TOMMRO_C_SW_ERR_SUCCESS;
}
