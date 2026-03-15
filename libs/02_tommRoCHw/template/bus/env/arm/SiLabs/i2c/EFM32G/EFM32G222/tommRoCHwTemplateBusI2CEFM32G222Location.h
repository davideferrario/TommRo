
#ifndef TOMMROC_HW_TEMPLATE_BUS_I2C_EFM32G222_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_I2C_EFM32G222_LOCATION_H_

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
#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_EFM32G_IS_USED__)

#if (defined (I2C_PRESENT) && I2C_COUNT)
#include "em_i2c.h"
#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

#if defined (EFM32G222F128)         ||  \
    defined (EFM32G222F32)          ||  \
    defined (EFM32G222F64)

/******************* I2C0 location */

#define I2C_0_LOCATION_0_SDA_PORT           (gpioPortA)
#define I2C_0_LOCATION_0_SDA_PIN            (0)
#define I2C_0_LOCATION_0_SCL_PORT           (gpioPortA)
#define I2C_0_LOCATION_0_SCL_PIN            (1)

#define I2C_0_LOCATION_1_SDA_PORT           (gpioPortD)
#define I2C_0_LOCATION_1_SDA_PIN            (6)
#define I2C_0_LOCATION_1_SCL_PORT           (gpioPortD)
#define I2C_0_LOCATION_1_SCL_PIN            (7)

#endif

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
