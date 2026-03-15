
#ifndef TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_H_
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_H_

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

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)
#include "bus/spi/master/tommRoCHwTemplateBusSPIMasterDEF.h"
#include "bus/spi/slave/tommRoCHwTemplateBusSPISlaveDEF.h"
#include "main.h"
#if defined (__TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_DEF_AT_LEAST_ONE_IS_USED__) || defined (__TOMMROC_HW_TEMPLATE_BUS_SPI_SLAVE_DEF_AT_LEAST_ONE_IS_USED__)
#if !defined (HAL_SPI_MODULE_ENABLED)
#error "HAL_SPI_MODULE_ENABLED must be defined"
#endif
#endif

/*******************************************************************************
 * defines
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
#if (defined (SPI1_SCK_Pin) && defined (SPI1_SCK_GPIO_Port) && defined (SPI1_MISO_Pin) && defined (SPI1_MISO_GPIO_Port) && defined (SPI1_MOSI_Pin) && defined (SPI1_MOSI_GPIO_Port))
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI1_SCK_PIN          (SPI1_SCK_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI1_SCK_GPIO_PORT    (SPI1_SCK_GPIO_Port)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI1_MISO_PIN         (SPI1_MISO_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI1_MISO_GPIO_PORT   (SPI1_MISO_GPIO_Port)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI1_MOSI_PIN         (SPI1_MOSI_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI1_MOSI_GPIO_PORT   (SPI1_MOSI_GPIO_Port)
#else
#error "Define SPI1_SCK and SPI1_MISO and SPI1_MOSI Pin"
#endif
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_TEMPLATE__)
#if (defined (SPI2_SCK_Pin) && defined (SPI2_SCK_GPIO_Port) && defined (SPI2_MISO_Pin) && defined (SPI2_MISO_GPIO_Port) && defined (SPI2_MOSI_Pin) && defined (SPI2_MOSI_GPIO_Port))
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI2_SCK_PIN          (SPI2_SCK_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI2_SCK_GPIO_PORT    (SPI2_SCK_GPIO_Port)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI2_MISO_PIN         (SPI2_MISO_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI2_MISO_GPIO_PORT   (SPI2_MISO_GPIO_Port)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI2_MOSI_PIN         (SPI2_MOSI_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI2_MOSI_GPIO_PORT   (SPI2_MOSI_GPIO_Port)
#else
#error "Define SPI2_SCK and SPI2_MISO and SPI2_MOSI Pin"
#endif
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_3_TEMPLATE__)
#if (defined (SPI3_SCK_Pin) && defined (SPI3_SCK_GPIO_Port) && defined (SPI3_MISO_Pin) && defined (SPI3_MISO_GPIO_Port) && defined (SPI3_MOSI_Pin) && defined (SPI3_MOSI_GPIO_Port))
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI3_SCK_PIN          (SPI3_SCK_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI3_SCK_GPIO_PORT    (SPI3_SCK_GPIO_Port)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI3_MISO_PIN         (SPI3_MISO_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI3_MISO_GPIO_PORT   (SPI3_MISO_GPIO_Port)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI3_MOSI_PIN         (SPI3_MOSI_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI3_MOSI_GPIO_PORT   (SPI3_MOSI_GPIO_Port)
#else
#error "Define SPI3_SCK and SPI3_MISO and SPI3_MOSI Pin"
#endif
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_4_TEMPLATE__)
#if (defined (SPI4_SCK_Pin) && defined (SPI4_SCK_GPIO_Port) && defined (SPI4_MISO_Pin) && defined (SPI4_MISO_GPIO_Port) && defined (SPI4_MOSI_Pin) && defined (SPI4_MOSI_GPIO_Port))
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI4_SCK_PIN          (SPI4_SCK_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI4_SCK_GPIO_PORT    (SPI4_SCK_GPIO_Port)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI4_MISO_PIN         (SPI4_MISO_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI4_MISO_GPIO_PORT   (SPI4_MISO_GPIO_Port)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI4_MOSI_PIN         (SPI4_MOSI_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI4_MOSI_GPIO_PORT   (SPI4_MOSI_GPIO_Port)
#else
#error "Define SPI4_SCK and SPI4_MISO and SPI4_MOSI Pin"
#endif
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_5_TEMPLATE__)
#if (defined (SPI5_SCK_Pin) && defined (SPI5_SCK_GPIO_Port) && defined (SPI5_MISO_Pin) && defined (SPI5_MISO_GPIO_Port) && defined (SPI5_MOSI_Pin) && defined (SPI5_MOSI_GPIO_Port))
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI5_SCK_PIN          (SPI5_SCK_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI5_SCK_GPIO_PORT    (SPI5_SCK_GPIO_Port)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI5_MISO_PIN         (SPI5_MISO_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI5_MISO_GPIO_PORT   (SPI5_MISO_GPIO_Port)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI5_MOSI_PIN         (SPI5_MOSI_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI5_MOSI_GPIO_PORT   (SPI5_MOSI_GPIO_Port)
#else
#error "Define SPI5_SCK and SPI5_MISO and SPI5_MOSI Pin"
#endif
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif

#endif

#endif
