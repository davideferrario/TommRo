
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateMCUFlash.h"

#include "TOMMROC.h"
#include "TOMMROCTemplate.h"

#if defined (__TOMMROC_TEMPLATE_ARM_STM32L4_IS_USED__)

#include "stm32l4xx_hal.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __FLASH_PROGRAM_BASE_SIZE_BIT__     (64)
#define __FLASH_PROGRAM_BASE_SIZE_BYTE__    (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(__FLASH_PROGRAM_BASE_SIZE_BIT__))
TOMMROC_SCTA_ZERO(__FLASH_PROGRAM_BASE_SIZE_BIT__   % TOMMROC_UNIT_MEASURE_BIT_IN_ONE_BYTE);
TOMMROC_SCTA_ZERO(__FLASH_PROGRAM_BASE_SIZE_BYTE__  % TOMMROC_UTIL_U32_SIZE);

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static bool _is_init = false;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static uint32_t _get_page_num(const uint32_t flashAddress) {

    if (flashAddress < (FLASH_BASE + FLASH_BANK_SIZE)) {
        // Bank 1
        return (flashAddress - FLASH_BASE) / FLASH_PAGE_SIZE;
    }

    // Bank 2
    return (flashAddress - (FLASH_BASE + FLASH_BANK_SIZE)) / FLASH_PAGE_SIZE;
}

static uint32_t _get_bank_num(const uint32_t flashAddress) {

    bool isBankSwap;

    isBankSwap = (!(0 == READ_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_FB_MODE)));

    if (flashAddress < (FLASH_BASE + FLASH_BANK_SIZE)) {
        return ((isBankSwap) ? (FLASH_BANK_2) : (FLASH_BANK_1));
    }

    return ((isBankSwap) ? (FLASH_BANK_1) : (FLASH_BANK_2));
}

static HAL_StatusTypeDef _wrapper_init(void) {

    HAL_StatusTypeDef errStatus;

    __disable_irq();
    errStatus = HAL_FLASH_Unlock();
    // Clear OPTVERR bit set on virgin samples
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
    __enable_irq();

    return errStatus;
}

static HAL_StatusTypeDef _wrapper_de_init(void) {

    HAL_StatusTypeDef errStatus;

    __disable_irq();
    errStatus = HAL_FLASH_Lock();
    __enable_irq();

    return errStatus;
}

static HAL_StatusTypeDef _wrapper_erase(const uint32_t addStart, const uint32_t lenBytes) {

    HAL_StatusTypeDef errStatus;

    uint32_t error = 0;

    uint32_t firstPage;
    uint32_t pageAmount;
    uint32_t bank;

    FLASH_EraseInitTypeDef FLASH_EraseInitStruct;

    // 1st page to erase
    firstPage = _get_page_num(addStart);
    // Number of pages to erase from 1st page
    pageAmount = _get_page_num(addStart + lenBytes - 1) - firstPage + 1;
    // Bank
    bank = _get_bank_num(addStart);

    FLASH_EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    FLASH_EraseInitStruct.Banks     = bank;
    FLASH_EraseInitStruct.Page      = firstPage;
    FLASH_EraseInitStruct.NbPages   = pageAmount;

    __disable_irq();
    errStatus = HAL_FLASHEx_Erase(&FLASH_EraseInitStruct, &error);
    __enable_irq();

    if (0xFFFFFFFFU != error) {
        return HAL_ERROR;
    }

    if (HAL_OK != errStatus) {
        return errStatus;
    }

    return HAL_OK;
}

static HAL_StatusTypeDef _wrapper_program(const uint32_t addStart, const uint32_t* const dataBuffer, const uint32_t dataBufferSizeBytes) {

    static const uint32_t addInc        = __FLASH_PROGRAM_BASE_SIZE_BYTE__;
    static const uint32_t dataIdxInc    = __FLASH_PROGRAM_BASE_SIZE_BYTE__ / TOMMROC_UTIL_U32_SIZE;

    HAL_StatusTypeDef errStatus;

    uint32_t relativeAdd;
    uint32_t dataIdx;
    uint64_t dataU64;

    for (relativeAdd = 0, dataIdx = 0; relativeAdd < dataBufferSizeBytes; relativeAdd += addInc, dataIdx += dataIdxInc) {

        dataU64 = tommRoCMathMake64From32(dataBuffer[dataIdx + 1], dataBuffer[dataIdx]);

        __disable_irq();
        errStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, addStart + relativeAdd, dataU64);
        __enable_irq();

        if (HAL_OK != errStatus) {
            return errStatus;
        }
    }

    return HAL_OK;
}

static void _wrapper_get(const uint32_t addStart, void* const dataBuffer, const uint32_t dataBufferSizeBytes) {

    void* flashAddrPtr;

    flashAddrPtr = (void*) addStart;

    __disable_irq();
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(dataBuffer, flashAddrPtr, dataBufferSizeBytes));
    __enable_irq();
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateMCUFlashInit(void) {

#if defined (HAL_FLASH_MODULE_ENABLED)
    if (!_is_init) {

        if (HAL_OK != _wrapper_init()) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        _is_init = true;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateMCUFlashDeInit(void) {

#if defined (HAL_FLASH_MODULE_ENABLED)
    if (HAL_OK != _wrapper_de_init()) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateMCUFlashErase(const uint32_t addStart, const uint32_t lenBytes) {

#if defined (HAL_FLASH_MODULE_ENABLED)
    if (!_is_init) {
        return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
    }

    if (HAL_OK != _wrapper_erase(addStart, lenBytes)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateMCUFlashWrite(const uint32_t addStart, const void* const dataBuffer, const uint32_t dataBufferSizeBytes) {

#if defined (HAL_FLASH_MODULE_ENABLED)

    TOMMROC_ASSERT_ZERO(addStart % __FLASH_PROGRAM_BASE_SIZE_BYTE__);
    TOMMROC_ASSERT_NOT_NULL(dataBuffer);

    TOMMROC_HW_PARAM_CHECK_ON_NOT_ZERO_RETURN_ERR(addStart % __FLASH_PROGRAM_BASE_SIZE_BYTE__);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(dataBuffer);

    if (!_is_init) {
        return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
    }

    if (HAL_OK != _wrapper_program(addStart, (uint32_t*) dataBuffer, dataBufferSizeBytes)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateMCUFlashRead(const uint32_t addStart, void* const dataBuffer, const uint32_t dataBufferSizeBytes) {

#if defined (HAL_FLASH_MODULE_ENABLED)

    TOMMROC_ASSERT_NOT_NULL(dataBuffer);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(dataBuffer);

    _wrapper_get(addStart, dataBuffer, dataBufferSizeBytes);

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

#endif
