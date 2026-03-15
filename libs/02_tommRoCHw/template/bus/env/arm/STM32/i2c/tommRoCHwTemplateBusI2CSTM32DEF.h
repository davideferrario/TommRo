
#ifndef TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_H_
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_H_

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
#include "bus/i2c/master/tommRoCHwTemplateBusI2CMasterDEF.h"
#include "bus/i2c/slave/tommRoCHwTemplateBusI2CSlaveDEF.h"
#include "main.h"
#if defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_DEF_AT_LEAST_ONE_IS_USED__) || defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_SLAVE_DEF_AT_LEAST_ONE_IS_USED__)
#if !defined (HAL_I2C_MODULE_ENABLED)
#error "HAL_I2C_MODULE_ENABLED must be defined"
#endif
#endif

/*******************************************************************************
 * defines
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
#if (defined (I2C1_SCL_Pin) && defined (I2C1_SCL_GPIO_Port) && defined (I2C1_SDA_Pin) && defined (I2C1_SDA_GPIO_Port))
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C1_SCL_PIN          (I2C1_SCL_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C1_SCL_GPIO_PORT    (I2C1_SCL_GPIO_Port)
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C1_SDA_PIN          (I2C1_SDA_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C1_SDA_GPIO_PORT    (I2C1_SDA_GPIO_Port)
#else
#error "Define I2C1_SCL and I2C1_SDA Pin"
#endif
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_2_TEMPLATE__)
#if (defined (I2C2_SCL_Pin) && defined (I2C2_SCL_GPIO_Port) && defined (I2C2_SDA_Pin) && defined (I2C2_SDA_GPIO_Port))
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C2_SCL_PIN          (I2C2_SCL_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C2_SCL_GPIO_PORT    (I2C2_SCL_GPIO_Port)
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C2_SDA_PIN          (I2C2_SDA_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C2_SDA_GPIO_PORT    (I2C2_SDA_GPIO_Port)
#else
#error "Define I2C2_SCL and I2C2_SDA Pin"
#endif
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_3_TEMPLATE__)
#if (defined (I2C3_SCL_Pin) && defined (I2C3_SCL_GPIO_Port) && defined (I2C3_SDA_Pin) && defined (I2C3_SDA_GPIO_Port))
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C3_SCL_PIN          (I2C3_SCL_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C3_SCL_GPIO_PORT    (I2C3_SCL_GPIO_Port)
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C3_SDA_PIN          (I2C3_SDA_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C3_SDA_GPIO_PORT    (I2C3_SDA_GPIO_Port)
#else
#error "Define I2C3_SCL and I2C3_SDA Pin"
#endif
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_4_TEMPLATE__)
#if (defined (I2C4_SCL_Pin) && defined (I2C4_SCL_GPIO_Port) && defined (I2C4_SDA_Pin) && defined (I2C4_SDA_GPIO_Port))
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C4_SCL_PIN          (I2C4_SCL_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C4_SCL_GPIO_PORT    (I2C4_SCL_GPIO_Port)
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C4_SDA_PIN          (I2C4_SDA_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C4_SDA_GPIO_PORT    (I2C4_SDA_GPIO_Port)
#else
#error "Define I2C4_SCL and I2C4_SDA Pin"
#endif
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_5_TEMPLATE__)
#if (defined (I2C5_SCL_Pin) && defined (I2C5_SCL_GPIO_Port) && defined (I2C5_SDA_Pin) && defined (I2C5_SDA_GPIO_Port))
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C5_SCL_PIN          (I2C5_SCL_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C5_SCL_GPIO_PORT    (I2C5_SCL_GPIO_Port)
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C5_SDA_PIN          (I2C5_SDA_Pin)
#define TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C5_SDA_GPIO_PORT    (I2C5_SDA_GPIO_Port)
#else
#error "Define I2C5_SCL and I2C5_SDA Pin"
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
