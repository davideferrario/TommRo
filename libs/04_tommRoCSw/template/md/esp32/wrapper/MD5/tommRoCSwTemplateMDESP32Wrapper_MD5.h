
#ifndef TOMMROC_SW_TEMPLATE_MD_ESP32_WRAPPER__MD5_H_
#define TOMMROC_SW_TEMPLATE_MD_ESP32_WRAPPER__MD5_H_

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

#include "mbedtls/md5.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateMDESP32Wrapper_MD5_Init(mbedtls_md5_context* const mdCtxPtr);
tommRoC_sw_err_enum_t tommRoCSwTemplateMDESP32Wrapper_MD5_Close(void);

tommRoC_err_enum_t tommRoCSwTemplateMDESP32Wrapper_MD5_MD5Perform(
        const   void*       const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                void*       const   outputBufferPtr);

#endif

#endif
