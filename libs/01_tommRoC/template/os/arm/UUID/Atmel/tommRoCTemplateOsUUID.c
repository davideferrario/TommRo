
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/tommRoCTemplateOsUUID.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_ATMEL_IS_USED__)

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

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateOsUUIDGet(
                void*       const   uuidBufferPtr,
        const   uint8_t             uuidBufferSize,
                uint8_t*    const   uuidBufferLenPtr) {

#if defined (__TOMMROC_TEMPLATE_ARM_ATMEL_SAML21_IS_USED__)

    /**
     * From datasheet:
     *
     * Each device has a unique 128-bit serial number which is a concatenation of four 32-bit words contained at the following addresses:
     * Word 0: 0x0080A00C
     * Word 1: 0x0080A040
     * Word 2: 0x0080A044
     * Word 3: 0x0080A048
     *
     * The uniqueness of the serial number is guaranteed only when using all 128 bits.
     */
    static const uint32_t* serialNPtr[] = { (uint32_t*) 0x0080A00C, (uint32_t*) 0x0080A040, (uint32_t*) 0x0080A044, (uint32_t*) 0x0080A048, };

    uint8_t idx;

    void* ptr;
    uint16_t bSize;

    TOMMROC_ASSERT_MORE_OR_EQUALS_THAN(uuidBufferSize, TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE);

    TOMMROC_PARAM_CHECK_ON_TEST_RETURN_ERR(uuidBufferSize, <, TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE);

    ptr     = uuidBufferPtr;
    bSize   = uuidBufferSize;
    for (idx = 0; idx < TOMMROC_UTIL_ARR_EAMOUNT(serialNPtr); ++ptr) {
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilBufferAppendU32MSB(ptr, bSize, *serialNPtr[idx], &ptr, &bSize));
    }

    *uuidBufferLenPtr = TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE;

    return TOMMRO_C_ERR_SUCCESS;
#endif
}

#endif

#endif
