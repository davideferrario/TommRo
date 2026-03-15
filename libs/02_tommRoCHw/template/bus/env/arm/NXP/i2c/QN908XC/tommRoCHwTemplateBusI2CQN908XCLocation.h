
#ifndef TOMMROC_HW_TEMPLATE_BUS_I2C_QN908XC_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_I2C_QN908XC_LOCATION_H_

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

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__)

#include "fsl_iocon.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/******************* I2C0 location */

#define I2C_0_LOCATION_0_CLOCK_NAME                         (kCLOCK_Flexcomm1)
#define I2C_0_LOCATION_0_SDA_PORT_IDX                       (0)
#define I2C_0_LOCATION_0_SDA_PIN                            (21U)
#define I2C_0_LOCATION_0_SDA_IOCON_FUNC                     (IOCON_FUNC5)
#define I2C_0_LOCATION_0_SCL_PORT_IDX                       (0)
#define I2C_0_LOCATION_0_SCL_PIN                            (20U)
#define I2C_0_LOCATION_0_SCL_IOCON_FUNC                     (IOCON_FUNC5)

#define I2C_0_LOCATION_0_SDA_GPIO                           (GPIOA)
#define I2C_0_LOCATION_0_SCL_GPIO                           (GPIOA)

#define I2C_0_LOCATION_1_CLOCK_NAME                         (kCLOCK_Flexcomm1)
#define I2C_0_LOCATION_1_SDA_PORT_IDX                       (0)
#define I2C_0_LOCATION_1_SDA_PIN                            (13U)
#define I2C_0_LOCATION_1_SDA_IOCON_FUNC                     (IOCON_FUNC4)
#define I2C_0_LOCATION_1_SCL_PORT_IDX                       (0)
#define I2C_0_LOCATION_1_SCL_PIN                            (12U)
#define I2C_0_LOCATION_1_SCL_IOCON_FUNC                     (IOCON_FUNC4)

#define I2C_0_LOCATION_1_SDA_GPIO                           (GPIOA)
#define I2C_0_LOCATION_1_SCL_GPIO                           (GPIOA)

#define I2C_0_LOCATION_2_CLOCK_NAME                         (kCLOCK_Flexcomm1)
#define I2C_0_LOCATION_2_SDA_PORT_IDX                       (0)
#define I2C_0_LOCATION_2_SDA_PIN                            (9U)
#define I2C_0_LOCATION_2_SDA_IOCON_FUNC                     (IOCON_FUNC4)
#define I2C_0_LOCATION_2_SCL_PORT_IDX                       (0)
#define I2C_0_LOCATION_2_SCL_PIN                            (8U)
#define I2C_0_LOCATION_2_SCL_IOCON_FUNC                     (IOCON_FUNC4)

#define I2C_0_LOCATION_2_SDA_GPIO                           (GPIOA)
#define I2C_0_LOCATION_2_SCL_GPIO                           (GPIOA)

#define I2C_0_LOCATION_3_CLOCK_NAME                         (kCLOCK_Flexcomm1)
#define I2C_0_LOCATION_3_SDA_PORT_IDX                       (0)
#define I2C_0_LOCATION_3_SDA_PIN                            (7U)
#define I2C_0_LOCATION_3_SDA_IOCON_FUNC                     (IOCON_FUNC4)
#define I2C_0_LOCATION_3_SCL_PORT_IDX                       (0)
#define I2C_0_LOCATION_3_SCL_PIN                            (6U)
#define I2C_0_LOCATION_3_SCL_IOCON_FUNC                     (IOCON_FUNC4)

#define I2C_0_LOCATION_3_SDA_GPIO                           (GPIOA)
#define I2C_0_LOCATION_3_SCL_GPIO                           (GPIOA)


/******************* I2C1 location */

#define I2C_1_LOCATION_0_CLOCK_NAME                         (kCLOCK_Flexcomm2)
#define I2C_1_LOCATION_0_SDA_PORT_IDX                       (0)
#define I2C_1_LOCATION_0_SDA_PIN                            (26U)
#define I2C_1_LOCATION_0_SDA_IOCON_FUNC                     (IOCON_FUNC4)
#define I2C_1_LOCATION_0_SCL_PORT_IDX                       (0)
#define I2C_1_LOCATION_0_SCL_PIN                            (27U)
#define I2C_1_LOCATION_0_SCL_IOCON_FUNC                     (IOCON_FUNC4)

#define I2C_1_LOCATION_0_SDA_GPIO                           (GPIOA)
#define I2C_1_LOCATION_0_SCL_GPIO                           (GPIOA)

#define I2C_1_LOCATION_1_CLOCK_NAME                         (kCLOCK_Flexcomm2)
#define I2C_1_LOCATION_1_SDA_PORT_IDX                       (0)
#define I2C_1_LOCATION_1_SDA_PIN                            (22U)
#define I2C_1_LOCATION_1_SDA_IOCON_FUNC                     (IOCON_FUNC4)
#define I2C_1_LOCATION_1_SCL_PORT_IDX                       (0)
#define I2C_1_LOCATION_1_SCL_PIN                            (23U)
#define I2C_1_LOCATION_1_SCL_IOCON_FUNC                     (IOCON_FUNC4)

#define I2C_1_LOCATION_1_SDA_GPIO                           (GPIOA)
#define I2C_1_LOCATION_1_SCL_GPIO                           (GPIOA)

#define I2C_1_LOCATION_2_CLOCK_NAME                         (kCLOCK_Flexcomm2)
#define I2C_1_LOCATION_2_SDA_PORT_IDX                       (0)
#define I2C_1_LOCATION_2_SDA_PIN                            (4U)
#define I2C_1_LOCATION_2_SDA_IOCON_FUNC                     (IOCON_FUNC5)
#define I2C_1_LOCATION_2_SCL_PORT_IDX                       (0)
#define I2C_1_LOCATION_2_SCL_PIN                            (5U)
#define I2C_1_LOCATION_2_SCL_IOCON_FUNC                     (IOCON_FUNC5)

#define I2C_1_LOCATION_2_SDA_GPIO                           (GPIOA)
#define I2C_1_LOCATION_2_SCL_GPIO                           (GPIOA)

#define I2C_1_LOCATION_3_CLOCK_NAME                         (kCLOCK_Flexcomm2)
#define I2C_1_LOCATION_3_SDA_PORT_IDX                       (0)
#define I2C_1_LOCATION_3_SDA_PIN                            (3U)
#define I2C_1_LOCATION_3_SDA_IOCON_FUNC                     (IOCON_FUNC5)
#define I2C_1_LOCATION_3_SCL_PORT_IDX                       (0)
#define I2C_1_LOCATION_3_SCL_PIN                            (2U)
#define I2C_1_LOCATION_3_SCL_IOCON_FUNC                     (IOCON_FUNC5)

#define I2C_1_LOCATION_3_SDA_GPIO                           (GPIOA)
#define I2C_1_LOCATION_3_SCL_GPIO                           (GPIOA)

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
