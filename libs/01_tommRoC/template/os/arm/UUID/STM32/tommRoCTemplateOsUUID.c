
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/tommRoCTemplateOsUUID.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_STM32_IS_USED__)

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

    const uint32_t* uidPtr = (uint32_t*) UID_BASE;

    TOMMROC_ASSERT_MORE_OR_EQUALS_THAN(uuidBufferSize, TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE);

    TOMMROC_PARAM_CHECK_ON_TEST_RETURN_ERR(uuidBufferSize, <, TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(uuidBufferPtr, uidPtr, TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE));

    *uuidBufferLenPtr = TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE;

    return TOMMRO_C_ERR_SUCCESS;
}

#endif

#endif
