
#ifndef TOMMROC_SW_TEMPLATE_SHA_ESP32_WRAPPER__SHA1_H_
#define TOMMROC_SW_TEMPLATE_SHA_ESP32_WRAPPER__SHA1_H_

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
#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "TOMMROCSw.h"

#include "mbedtls/sha1.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA1_Init(mbedtls_sha1_context* const shaCtxPtr);
tommRoC_sw_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA1_Close(void);

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA1_SHA1Perform(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr);

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA1_SHA1Start(
                void*       const   shaCtxPtr);

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA1_SHA1Update(
                void*       const   shaCtxPtr,
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen);

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA1_SHA1Finish(
                void*       const   shaCtxPtr,
                uint8_t*    const   outputBufferPtr);

#endif

#endif
