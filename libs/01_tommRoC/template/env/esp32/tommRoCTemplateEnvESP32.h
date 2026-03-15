
#ifndef TOMMROC_TEMPLATE_ENV_ESP32_H_
#define TOMMROC_TEMPLATE_ENV_ESP32_H_

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
#include "sdkconfig.h"

#include "esp_idf_version.h"

/*******************************************************************************
 * defines
 ******************************************************************************/
#define TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE  (6)

#if (4 == ESP_IDF_VERSION_MAJOR)
#elif (5 == ESP_IDF_VERSION_MAJOR)
#else
#error "ESP-IDF version not supported!"
#endif

#define TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR    (ESP_IDF_VERSION_MAJOR)
#define TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MINOR    (ESP_IDF_VERSION_MINOR)
#define TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_PATCH    (ESP_IDF_VERSION_PATCH)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif

#endif
