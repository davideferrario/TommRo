
#ifndef TOMMROC_HW_NET_HTTP_RESPONSE_H_
#define TOMMROC_HW_NET_HTTP_RESPONSE_H_

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
#include "net/HTTP/tommRoCHwNetHTTPDEF.h"

#include "tommRoCHwErr.h"

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
 * Check if an HTTP response is valid.
 *
 * param[in]        responsePtr             HTTP response data buffer pointer.
 * param[in]        responseLen             HTTP response data buffer length [byte].
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NULL_PARAM_ERR              -> NULL param error
 *          TOMMRO_C_HW_PARAM_ERR                   -> param error
 *          TOMMRO_C_HW_LOW_LEVEL_ERR               -> HTTP response is not valid
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> HTTP response is valid
 */
tommRoC_hw_err_enum_t tommRoCHwNetHTTPResponseCheck(
        const   void*                                   const   responsePtr,
        const   uint32_t                                        responseLen);

/**
 * Extract HTTP version/status from HTTP response.
 *
 * param[in]        responsePtr             HTTP response data buffer pointer.
 * param[in]        responseLen             HTTP response data buffer length [byte].
 * param[out]       httpDefVerPtr           HTTP response version pointer.
 * param[out]       responseStatusPtr       HTTP response status pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetHTTPResponseGetVersionStatus(
        const   void*                                   const   responsePtr,
        const   uint32_t                                        responseLen,
                tommRoC_hw_net_http_def_version_enum_t* const   httpDefVerPtr,
                uint16_t*                               const   responseStatusPtr);

/**
 * Extract HTTP header from HTTP response.
 *
 * param[in]        responsePtr             HTTP response data buffer pointer.
 * param[in]        responseLen             HTTP response data buffer length [byte].
 * param[out]       responseHeaderBufPtr    HTTP response header data buffer pointer.
 * param[in]        responseHeaderBufSize   HTTP response header data buffer size [byte].
 * param[out]       responseHeaderLenPtr    HTTP response header length pointer [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetHTTPResponseGetHeader(
        const   void*                                   const   responsePtr,
        const   uint32_t                                        responseLen,
                void*                                   const   responseHeaderBufPtr,
        const   uint32_t                                        responseHeaderBufSize,
                uint32_t*                               const   responseHeaderLenPtr);

/**
 * Extract HTTP body from HTTP response.
 *
 * param[in]        responsePtr             HTTP response data buffer pointer.
 * param[in]        responseLen             HTTP response data buffer length [byte].
 * param[out]       responseHeaderBufPtr    HTTP response body data buffer pointer.
 * param[in]        responseHeaderBufSize   HTTP response body data buffer size [byte].
 * param[out]       responseHeaderLenPtr    HTTP response body length pointer [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetHTTPResponseGetBody(
        const   void*                                   const   responsePtr,
        const   uint32_t                                        responseLen,
                void*                                   const   responseBodyBufPtr,
        const   uint32_t                                        responseBodyBufSize,
                uint32_t*                               const   responseBodyLenPtr);

#endif
