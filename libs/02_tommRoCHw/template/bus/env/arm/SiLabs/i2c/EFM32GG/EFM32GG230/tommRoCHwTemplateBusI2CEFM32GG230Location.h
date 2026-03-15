
#ifndef TOMMROC_HW_TEMPLATE_BUS_I2C_EFM32GG230_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_I2C_EFM32GG230_LOCATION_H_

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

#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_EFM32GG_IS_USED__)

#if (defined (I2C_PRESENT) && I2C_COUNT)
#include "em_i2c.h"
#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

#if defined (EFM32GG230F1024)       ||  \
    defined (EFM32GG230F512)

/******************* I2C0 location */

#define I2C_0_LOCATION_0_SDA_PORT           (gpioPortA)
#define I2C_0_LOCATION_0_SDA_PIN            (0)
#define I2C_0_LOCATION_0_SCL_PORT           (gpioPortA)
#define I2C_0_LOCATION_0_SCL_PIN            (1)

#define I2C_0_LOCATION_1_SDA_PORT           (gpioPortD)
#define I2C_0_LOCATION_1_SDA_PIN            (6)
#define I2C_0_LOCATION_1_SCL_PORT           (gpioPortD)
#define I2C_0_LOCATION_1_SCL_PIN            (7)

#define I2C_0_LOCATION_2_SDA_PORT           (gpioPortC)
#define I2C_0_LOCATION_2_SDA_PIN            (6)
#define I2C_0_LOCATION_2_SCL_PORT           (gpioPortC)
#define I2C_0_LOCATION_2_SCL_PIN            (7)

#define I2C_0_LOCATION_3_SDA_PORT           (gpioPortD)
#define I2C_0_LOCATION_3_SDA_PIN            (14)
#define I2C_0_LOCATION_3_SCL_PORT           (gpioPortD)
#define I2C_0_LOCATION_3_SCL_PIN            (15)

#define I2C_0_LOCATION_4_SDA_PORT           (gpioPortC)
#define I2C_0_LOCATION_4_SDA_PIN            (0)
#define I2C_0_LOCATION_4_SCL_PORT           (gpioPortC)
#define I2C_0_LOCATION_4_SCL_PIN            (1)

#define I2C_0_LOCATION_5_SDA_PORT           (gpioPortF)
#define I2C_0_LOCATION_5_SDA_PIN            (0)
#define I2C_0_LOCATION_5_SCL_PORT           (gpioPortF)
#define I2C_0_LOCATION_5_SCL_PIN            (1)

#define I2C_0_LOCATION_6_SDA_PORT           (gpioPortE)
#define I2C_0_LOCATION_6_SDA_PIN            (12)
#define I2C_0_LOCATION_6_SCL_PORT           (gpioPortE)
#define I2C_0_LOCATION_6_SCL_PIN            (13)


/******************* I2C1 location */

#define I2C_1_LOCATION_0_SDA_PORT           (gpioPortC)
#define I2C_1_LOCATION_0_SDA_PIN            (4)
#define I2C_1_LOCATION_0_SCL_PORT           (gpioPortC)
#define I2C_1_LOCATION_0_SCL_PIN            (5)

#define I2C_1_LOCATION_1_SDA_PORT           (gpioPortB)
#define I2C_1_LOCATION_1_SDA_PIN            (11)
#define I2C_1_LOCATION_1_SCL_PORT           (gpioPortB)
#define I2C_1_LOCATION_1_SCL_PIN            (12)

#define I2C_1_LOCATION_2_SDA_PORT           (gpioPortE)
#define I2C_1_LOCATION_2_SDA_PIN            (0)
#define I2C_1_LOCATION_2_SCL_PORT           (gpioPortE)
#define I2C_1_LOCATION_2_SCL_PIN            (1)

#endif

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
