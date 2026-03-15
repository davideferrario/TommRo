
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateMCUFlash.h"

#include "TOMMROC.h"
#include "TOMMROCTemplate.h"

#if defined (__TOMMROC_TEMPLATE_ARM_STM32F4_IS_USED__)

#include "stm32f4xx_hal.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __FLASH_PROGRAM_BASE_SIZE_BIT__     (32)
#define __FLASH_PROGRAM_BASE_SIZE_BYTE__    (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(__FLASH_PROGRAM_BASE_SIZE_BIT__))
TOMMROC_SCTA_ZERO(__FLASH_PROGRAM_BASE_SIZE_BIT__   % TOMMROC_UNIT_MEASURE_BIT_IN_ONE_BYTE);
TOMMROC_SCTA_ZERO(__FLASH_PROGRAM_BASE_SIZE_BYTE__  % TOMMROC_UTIL_U32_SIZE);

// Base address of the Flash sectors Bank 1
#define __ADDR_FLASH_SECTOR_0__     ((uint32_t)0x08000000)  // Base @ of Sector 0, 16 Kbytes
#define __ADDR_FLASH_SECTOR_1__     ((uint32_t)0x08004000)  // Base @ of Sector 1, 16 Kbytes
#define __ADDR_FLASH_SECTOR_2__     ((uint32_t)0x08008000)  // Base @ of Sector 2, 16 Kbytes
#define __ADDR_FLASH_SECTOR_3__     ((uint32_t)0x0800C000)  // Base @ of Sector 3, 16 Kbytes
#define __ADDR_FLASH_SECTOR_4__     ((uint32_t)0x08010000)  // Base @ of Sector 4, 64 Kbytes
#define __ADDR_FLASH_SECTOR_5__     ((uint32_t)0x08020000)  // Base @ of Sector 5, 128 Kbytes
#define __ADDR_FLASH_SECTOR_6__     ((uint32_t)0x08040000)  // Base @ of Sector 6, 128 Kbytes
#define __ADDR_FLASH_SECTOR_7__     ((uint32_t)0x08060000)  // Base @ of Sector 7, 128 Kbytes
#define __ADDR_FLASH_SECTOR_8__     ((uint32_t)0x08080000)  // Base @ of Sector 8, 128 Kbytes
#define __ADDR_FLASH_SECTOR_9__     ((uint32_t)0x080A0000)  // Base @ of Sector 9, 128 Kbytes
#define __ADDR_FLASH_SECTOR_10__    ((uint32_t)0x080C0000)  // Base @ of Sector 10, 128 Kbytes
#define __ADDR_FLASH_SECTOR_11__    ((uint32_t)0x080E0000)  // Base @ of Sector 11, 128 Kbytes

// Base address of the Flash sectors Bank 2
#define __ADDR_FLASH_SECTOR_12__    ((uint32_t)0x08100000)  // Base @ of Sector 0, 16 Kbytes
#define __ADDR_FLASH_SECTOR_13__    ((uint32_t)0x08104000)  // Base @ of Sector 1, 16 Kbytes
#define __ADDR_FLASH_SECTOR_14__    ((uint32_t)0x08108000)  // Base @ of Sector 2, 16 Kbytes
#define __ADDR_FLASH_SECTOR_15__    ((uint32_t)0x0810C000)  // Base @ of Sector 3, 16 Kbytes
#define __ADDR_FLASH_SECTOR_16__    ((uint32_t)0x08110000)  // Base @ of Sector 4, 64 Kbytes
#define __ADDR_FLASH_SECTOR_17__    ((uint32_t)0x08120000)  // Base @ of Sector 5, 128 Kbytes
#define __ADDR_FLASH_SECTOR_18__    ((uint32_t)0x08140000)  // Base @ of Sector 6, 128 Kbytes
#define __ADDR_FLASH_SECTOR_19__    ((uint32_t)0x08160000)  // Base @ of Sector 7, 128 Kbytes
#define __ADDR_FLASH_SECTOR_20__    ((uint32_t)0x08180000)  // Base @ of Sector 8, 128 Kbytes
#define __ADDR_FLASH_SECTOR_21__    ((uint32_t)0x081A0000)  // Base @ of Sector 9, 128 Kbytes
#define __ADDR_FLASH_SECTOR_22__    ((uint32_t)0x081C0000)  // Base @ of Sector 10, 128 Kbytes
#define __ADDR_FLASH_SECTOR_23__    ((uint32_t)0x081E0000)  // Base @ of Sector 11, 128 Kbytes

#define __FLASH_END_ADDR__          ((uint32_t)0x08200000)

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
static uint32_t _get_sector_num(const uint32_t flashAddress) {

    if ((flashAddress < __ADDR_FLASH_SECTOR_1__) && (flashAddress >= __ADDR_FLASH_SECTOR_0__)) {
        return FLASH_SECTOR_0;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_2__) && (flashAddress >= __ADDR_FLASH_SECTOR_1__)) {
        return FLASH_SECTOR_1;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_3__) && (flashAddress >= __ADDR_FLASH_SECTOR_2__)) {
        return FLASH_SECTOR_2;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_4__) && (flashAddress >= __ADDR_FLASH_SECTOR_3__)) {
        return FLASH_SECTOR_3;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_5__) && (flashAddress >= __ADDR_FLASH_SECTOR_4__)) {
        return FLASH_SECTOR_4;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_6__) && (flashAddress >= __ADDR_FLASH_SECTOR_5__)) {
        return FLASH_SECTOR_5;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_7__) && (flashAddress >= __ADDR_FLASH_SECTOR_6__)) {
        return FLASH_SECTOR_6;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_8__) && (flashAddress >= __ADDR_FLASH_SECTOR_7__)) {
        return FLASH_SECTOR_7;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_9__) && (flashAddress >= __ADDR_FLASH_SECTOR_8__)) {
        return FLASH_SECTOR_8;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_10__) && (flashAddress >= __ADDR_FLASH_SECTOR_9__)) {
        return FLASH_SECTOR_9;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_11__) && (flashAddress >= __ADDR_FLASH_SECTOR_10__)) {
        return FLASH_SECTOR_10;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_12__) && (flashAddress >= __ADDR_FLASH_SECTOR_11__)) {
        return FLASH_SECTOR_11;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_13__) && (flashAddress >= __ADDR_FLASH_SECTOR_12__)) {
        return FLASH_SECTOR_12;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_14__) && (flashAddress >= __ADDR_FLASH_SECTOR_13__)) {
        return FLASH_SECTOR_13;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_15__) && (flashAddress >= __ADDR_FLASH_SECTOR_14__)) {
        return FLASH_SECTOR_14;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_16__) && (flashAddress >= __ADDR_FLASH_SECTOR_15__)) {
        return FLASH_SECTOR_15;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_17__) && (flashAddress >= __ADDR_FLASH_SECTOR_16__)) {
        return FLASH_SECTOR_16;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_18__) && (flashAddress >= __ADDR_FLASH_SECTOR_17__)) {
        return FLASH_SECTOR_17;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_19__) && (flashAddress >= __ADDR_FLASH_SECTOR_18__)) {
        return FLASH_SECTOR_18;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_20__) && (flashAddress >= __ADDR_FLASH_SECTOR_19__)) {
        return FLASH_SECTOR_19;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_21__) && (flashAddress >= __ADDR_FLASH_SECTOR_20__)) {
        return FLASH_SECTOR_20;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_22__) && (flashAddress >= __ADDR_FLASH_SECTOR_21__)) {
        return FLASH_SECTOR_21;
    }
    if ((flashAddress < __ADDR_FLASH_SECTOR_23__) && (flashAddress >= __ADDR_FLASH_SECTOR_22__)) {
        return FLASH_SECTOR_22;
    }
    if ((flashAddress < __FLASH_END_ADDR__) && (flashAddress >= __ADDR_FLASH_SECTOR_23__)) {
        return FLASH_SECTOR_23;
    }

    // If here, ERROR!!!
    TOMMROC_ASSERT_TRUE(false);

    return -1;
}

static HAL_StatusTypeDef _wrapper_init(void) {

    HAL_StatusTypeDef errStatus;

    __disable_irq();
    errStatus = HAL_FLASH_Unlock();
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

    uint32_t firstSector;
    uint32_t sectorAmount;

    FLASH_EraseInitTypeDef EraseInitStruct;

    // 1st sector to erase
    firstSector = _get_sector_num(addStart);
    // Number of sectos to erase from 1st sector
    sectorAmount = _get_sector_num(addStart + lenBytes - 1) - firstSector + 1;

    EraseInitStruct.TypeErase       = FLASH_TYPEERASE_SECTORS;
    EraseInitStruct.VoltageRange    = FLASH_VOLTAGE_RANGE_3;
    EraseInitStruct.Sector          = firstSector;
    EraseInitStruct.NbSectors       = sectorAmount;

    __disable_irq();
    errStatus = HAL_FLASHEx_Erase(&EraseInitStruct, &error);
    __enable_irq();

    if (0xFFFFFFFFU != error) {
        return HAL_ERROR;
    }

    if (HAL_OK != errStatus) {
        return errStatus;
    }

    /**
     * NOTE: from application example.
     * If an erase operation in Flash memory also concerns data in the data or instruction cache,
     * you have to make sure that these data are rewritten before they are accessed during code execution.
     * If this cannot be done safely, it is recommended to flush the caches by setting the
     * DCRST and ICRST bits in the FLASH_CR register.
     */
    __HAL_FLASH_DATA_CACHE_DISABLE();
    __HAL_FLASH_INSTRUCTION_CACHE_DISABLE();

    __HAL_FLASH_DATA_CACHE_RESET();
    __HAL_FLASH_INSTRUCTION_CACHE_RESET();

    __HAL_FLASH_INSTRUCTION_CACHE_ENABLE();
    __HAL_FLASH_DATA_CACHE_ENABLE();

    return HAL_OK;
}

static HAL_StatusTypeDef _wrapper_program(const uint32_t addStart, const uint32_t* const dataBuffer, const uint32_t dataBufferSizeBytes) {

    static const uint32_t addInc        = __FLASH_PROGRAM_BASE_SIZE_BYTE__;
    static const uint32_t dataIdxInc    = __FLASH_PROGRAM_BASE_SIZE_BYTE__ / TOMMROC_UTIL_U32_SIZE;

    HAL_StatusTypeDef errStatus;

    uint32_t relativeAdd;
    uint32_t dataIdx;

    for (relativeAdd = 0, dataIdx = 0; relativeAdd < dataBufferSizeBytes; relativeAdd += addInc, dataIdx += dataIdxInc) {

        __disable_irq();
        errStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addStart + relativeAdd, (uint32_t) &dataBuffer[dataIdx]);
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
