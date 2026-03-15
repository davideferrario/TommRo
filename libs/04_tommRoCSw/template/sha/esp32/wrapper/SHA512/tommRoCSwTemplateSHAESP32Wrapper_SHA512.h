
#ifndef TOMMROC_SW_TEMPLATE_SHA_ESP32_WRAPPER__SHA512_H_
#define TOMMROC_SW_TEMPLATE_SHA_ESP32_WRAPPER__SHA512_H_

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

#include "mbedtls/sha512.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA512_Init(mbedtls_sha512_context* const shaCtxPtr);
tommRoC_sw_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA512_Close(void);

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA512_SHA384Perform(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr);

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA512_SHA512Perform(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr);

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA512_SHA384Start(
                void*       const   shaCtxPtr);
tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA512_SHA512Start(
                void*       const   shaCtxPtr);

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA512_SHA384_512Update(
                void*       const   shaCtxPtr,
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen);

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA512_SHA384_512Finish(
                void*       const   shaCtxPtr,
                uint8_t*    const   outputBufferPtr);

#endif

#endif
