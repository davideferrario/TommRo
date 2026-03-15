
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/tommRoCTemplateOsUUID.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)

#include "TOMMROC.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MK22_IS_USED__) || defined (__TOMMROC_TEMPLATE_ARM_NXP_MKWx1Z_IS_USED__)
#include "fsl_sim.h"
#endif

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

    TOMMROC_ASSERT_MORE_OR_EQUALS_THAN(uuidBufferSize, TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE);

    TOMMROC_PARAM_CHECK_ON_TEST_RETURN_ERR(uuidBufferSize, <, TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE);

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MK22_IS_USED__) || defined (__TOMMROC_TEMPLATE_ARM_NXP_MKWx1Z_IS_USED__)
    sim_uid_t uid;
    const uint8_t* uidPtr = (uint8_t*) &uid;

    TOMMROC_CTA_EQUALS(sizeof(uid), TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE);

    SIM_GetUniqueId(&uid);
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__)
    const uint8_t* uidPtr = (uint8_t*) FSL_FEATURE_FLASH_ADDR_OF_VENDOR_BD_ADDR;

    TOMMROC_CTA_EQUALS(6, TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE);
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
    const uint32_t uid[] = { SIM->UUIDH, SIM->UUIDL };
    const uint8_t* uidPtr = (uint8_t*) uid;

    TOMMROC_CTA_EQUALS(sizeof(uid), TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE);
#endif

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(uuidBufferPtr, uidPtr, TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE));

    *uuidBufferLenPtr = TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE;

    return TOMMRO_C_ERR_SUCCESS;
}

#endif

#endif
