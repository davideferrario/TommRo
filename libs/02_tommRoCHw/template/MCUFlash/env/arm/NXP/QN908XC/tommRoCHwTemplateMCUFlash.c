
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateMCUFlash.h"

#include "TOMMROC.h"
#include "TOMMROCTemplate.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__)

#include "fsl_common.h"
#include "fsl_device_registers.h"
#include "fsl_flash.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static flash_config_t _flash_config;
static bool _is_init = false;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static status_t __attribute__((optimize("O3"))) _wrapper_init(flash_config_t *config) {

    status_t errStatus;

    __disable_irq();
    // Configure Flash
    FLASH_GetDefaultConfig(config);
    // Flash module init
    errStatus = FLASH_Init(config);
    __enable_irq();

    return errStatus;
}

static status_t __attribute__((optimize("O3"))) _wrapper_de_init(flash_config_t *config) {

    TOMMROC_UTIL_UNUSED_PARAM(config);

    return kStatus_FLASH_Success;
}

static status_t __attribute__((optimize("O3"))) _wrapper_erase(flash_config_t *config, uint32_t addStart, uint32_t lenBytes) {

    status_t errStatus;

    __disable_irq();
    errStatus = FLASH_Erase(config, addStart, lenBytes);
    __enable_irq();

    return errStatus;
}

static status_t __attribute__((optimize("O3"))) _wrapper_program(flash_config_t *config, uint32_t addStart, uint32_t *dataBuffer, uint32_t dataBufferSizeBytes) {

    status_t errStatus;

    __disable_irq();
    errStatus = FLASH_Program(config, addStart, dataBuffer, dataBufferSizeBytes);
    __enable_irq();

    return errStatus;
}

static void __attribute__((optimize("O3"))) _wrapper_get(uint32_t addStart, uint32_t *dataBuffer, uint32_t dataBufferSizeBytes) {

    uint32_t* flashAddrPtr;

    flashAddrPtr = (uint32_t*) addStart;

    __disable_irq();
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(dataBuffer, flashAddrPtr, dataBufferSizeBytes));
    __enable_irq();
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateMCUFlashInit(void) {

    if (!_is_init) {

        // Clean up Flash driver Structure
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&_flash_config, 0x00, sizeof(_flash_config)));

        if (kStatus_FLASH_Success != _wrapper_init(&_flash_config)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        _is_init = true;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateMCUFlashDeInit(void) {

    if (kStatus_FLASH_Success != _wrapper_de_init(&_flash_config)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateMCUFlashErase(const uint32_t addStart, const uint32_t lenBytes) {

    TOMMROC_ASSERT_ZERO(addStart % FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE);
    TOMMROC_ASSERT_ZERO(lenBytes % FSL_FEATURE_FLASH_PAGE_SIZE_BYTES);

    if (!_is_init) {
        return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
    }

    if (kStatus_FLASH_Success != _wrapper_erase(&_flash_config, FSL_FEATURE_FLASH_BASE_ADDR + addStart, lenBytes)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateMCUFlashWrite(const uint32_t addStart, const void* const dataBuffer, const uint32_t dataBufferSizeBytes) {

    TOMMROC_ASSERT_ZERO(addStart % FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE);
    TOMMROC_ASSERT_ZERO(dataBufferSizeBytes % FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE);

    if (!_is_init) {
        return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
    }

    if (kStatus_FLASH_Success != _wrapper_program(&_flash_config, FSL_FEATURE_FLASH_BASE_ADDR + addStart, (uint32_t*) dataBuffer, dataBufferSizeBytes)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateMCUFlashRead(const uint32_t addStart, void* const dataBuffer, const uint32_t dataBufferSizeBytes) {

    _wrapper_get(FSL_FEATURE_FLASH_BASE_ADDR + addStart, (uint32_t*) dataBuffer, dataBufferSizeBytes);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

#endif
