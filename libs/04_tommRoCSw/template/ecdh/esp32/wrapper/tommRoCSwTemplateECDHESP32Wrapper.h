
#ifndef TOMMROC_SW_TEMPLATE_ECDH_ESP32_WRAPPER_H_
#define TOMMROC_SW_TEMPLATE_ECDH_ESP32_WRAPPER_H_

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

#include "ecdh/esp32/context/tommRoCSwTemplateECDHESP32Context.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateECDHESP32WrapperInit(tommRoC_sw_template_ecdh_esp32_context_t* const ecdhCtxPtr);
tommRoC_sw_err_enum_t tommRoCSwTemplateECDHESP32WrapperClose(void);

bool tommRoCSwTemplateECDHESP32WrapperIsEcpGroupAvailable(
        const   tommRoC_crypto_ecdh_ecp_group_id_enum_t         ecpGroupId);

tommRoC_err_enum_t tommRoCSwTemplateECDHESP32WrapperGenKeypair(
        const   tommRoC_crypto_ecdh_ecp_group_id_enum_t         ecpGroupId,
                uint8_t*                                const   privateKeyPtr,
        const   uint16_t                                        privateKeySize,
                uint8_t*                                const   publicKeyPtr,
        const   uint16_t                                        publicKeyMaxSize,
                uint16_t*                               const   publicKeyLenPtr);

tommRoC_err_enum_t tommRoCSwTemplateECDHESP32WrapperComputeShared(
        const   tommRoC_crypto_ecdh_ecp_group_id_enum_t         ecpGroupId,
        const   uint8_t*                                const   privateKeyPtr,
        const   uint16_t                                        privateKeySize,
        const   uint8_t*                                const   publicKeyPtr,
        const   uint16_t                                        publicKeySize,
                uint8_t*                                const   sharedPtr,
        const   uint16_t                                        sharedSize);

void tommRoCSwTemplateECDHESP32WrapperEnableProtectionTimingAttacks(void);
void tommRoCSwTemplateECDHESP32WrapperDisableProtectionTimingAttacks(void);

#endif

#endif
