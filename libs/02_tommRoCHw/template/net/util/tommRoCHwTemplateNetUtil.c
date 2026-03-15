
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateNetUtil.h"

#include "env/tommRoCTemplateEnv.h"

#include "TOMMROC.h"
#include "TOMMROCHw.h"

#include <stdbool.h>

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

tommRoC_hw_err_enum_t tommRoCHwTemplateNetUtilMACAddGenerate(uint8_t* const MACAddBufferPtr, const uint8_t MACAddBufferSize, uint8_t* const MACAddLenPtr) {

    static const tommRoC_crc_polynomial_crc16_config_t CRC16Config = TOMMRO_C_CRC_CRC16_CCITT;
    static const tommRoC_crc_polynomial_crc32_config_t CRC32Config = TOMMRO_C_CRC_CRC32_POSIX_CONFIG;

    uint8_t UUID[TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE];

    uint8_t UUIDLen;

    uint32_t CRC32;
    uint16_t CRC16;

    bool isInit;

    void* ptr;
    uint16_t bSize;

    TOMMROC_ASSERT_NOT_NULL(MACAddBufferPtr);
    TOMMROC_ASSERT_MORE_OR_EQUALS_THAN(MACAddBufferSize, TOMMROC_HW_TEMPLATE_NET_UTIL_MAC_ADDRESS_SIZE_BYTE);
    TOMMROC_ASSERT_NOT_NULL(MACAddLenPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(MACAddBufferPtr);
    TOMMROC_HW_PARAM_CHECK_ON_TEST_RETURN_ERR(MACAddBufferSize, <, TOMMROC_HW_TEMPLATE_NET_UTIL_MAC_ADDRESS_SIZE_BYTE);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(MACAddLenPtr);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsIsInitEnv(TOMMRO_C_OS_GET_UUID_FUNCT, &isInit));
    TOMMROC_ASSERT_TRUE(isInit);

    if (isInit) {
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsGetUUID(UUID, sizeof(UUID), &UUIDLen));
        TOMMROC_ASSERT_EQUALS(UUIDLen, sizeof(UUID));
    }
    else {
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(UUID, 0x00, sizeof(UUID)));
    }

    CRC16 = tommRoCCRCPolynomialCRC16(&CRC16Config, UUID, sizeof(UUID));
    CRC32 = tommRoCCRCPolynomialCRC32(&CRC32Config, UUID, sizeof(UUID));

    ptr     = MACAddBufferPtr;
    bSize   = MACAddBufferSize;
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilBufferAppendU16MSB(ptr, bSize, CRC16, &ptr, &bSize));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilBufferAppendU32MSB(ptr, bSize, CRC32, &ptr, &bSize));

    // NOTE: clear bit 0 of byte 0 (0: unicast, 1: multicast) and set bit 1 of byte 0 (0: globally unicque, 1: locally administered)
    *MACAddBufferPtr = tommRoCMathBitClear(*MACAddBufferPtr, 0);
    *MACAddBufferPtr = tommRoCMathBitSet(*MACAddBufferPtr, 1);

    *MACAddLenPtr = TOMMROC_HW_TEMPLATE_NET_UTIL_MAC_ADDRESS_SIZE_BYTE;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
