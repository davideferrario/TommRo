
#ifndef TOMMROC_HW_TEMPLATE_MCU_FLASH_H_
#define TOMMROC_HW_TEMPLATE_MCU_FLASH_H_

/*
 *******************************************************************************
 * License
 * (C) Copyright 2017
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications according to the supply agreement.
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: this software is provided
 * "AS IS", with no express or implied warranties of any kind, including,
 * but not limited to, any implied warranties of merchantability or
 * fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Supplier will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 */

/**
 * Author
 * TommRo Software Department
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROCHw.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init hardware MCU flash.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateMCUFlashInit(void);

/**
 * De-Init hardware MCU flash.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateMCUFlashDeInit(void);

/**
 * Erase hardware MCU flash.
 *
 * param[in]        addStart                MCU flash start address of erase operation.
 * param[in]        lenBytes                MCU flash length of erase operation [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateMCUFlashErase(const uint32_t addStart, const uint32_t lenBytes);

/**
 * Write hardware MCU flash.
 *
 * param[in]        addStart                MCU flash start address of write operation.
 * param[in]        dataBuffer              data buffer to write pointer.
 * param[in]        dataBufferSizeBytes     data buffer to write size [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateMCUFlashWrite(const uint32_t addStart, const void* const dataBuffer, const uint32_t dataBufferSizeBytes);

/**
 * Read hardware MCU flash.
 *
 * param[in]        addStart                MCU flash start address of read operation.
 * param[out]       dataBuffer              data buffer to read pointer.
 * param[in]        dataBufferSizeBytes     data buffer to read size [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateMCUFlashRead(const uint32_t addStart, void* const dataBuffer, const uint32_t dataBufferSizeBytes);

#endif

