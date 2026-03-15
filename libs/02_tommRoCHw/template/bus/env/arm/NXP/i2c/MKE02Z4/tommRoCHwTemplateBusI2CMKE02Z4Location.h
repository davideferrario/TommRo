
#ifndef TOMMROC_HW_TEMPLATE_BUS_I2C_MKE02Z4_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_I2C_MKE02Z4_LOCATION_H_

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

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)

/*******************************************************************************
 * defines
 ******************************************************************************/

/******************* I2C0 location */

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define I2C_0_LOCATION_0_CLOCK_NAME                         (kCLOCK_PortB)
#define I2C_0_LOCATION_0_SDA_PORT                           (PORTB)
#define I2C_0_LOCATION_0_SDA_PIN                            (6U)
#define I2C_0_LOCATION_0_SDA_PORT_MUX                       (kPORT_MuxAlt2)
#define I2C_0_LOCATION_0_SCL_PORT                           (PORTB)
#define I2C_0_LOCATION_0_SCL_PIN                            (7U)
#define I2C_0_LOCATION_0_SCL_PORT_MUX                       (kPORT_MuxAlt2)

#define I2C_0_LOCATION_0_SDA_GPIO                           (GPIOB)
#define I2C_0_LOCATION_0_SCL_GPIO                           (GPIOB)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION) || (MAKE_VERSION(2, 0, 2) == FSL_PORT_DRIVER_VERSION)
#define I2C_0_LOCATION_0_CLOCK_NAME                         (kCLOCK_I2c0)
#define I2C_0_LOCATION_0_PORT_SET_PIN_SELECT_NEEDED         (true)
#define I2C_0_LOCATION_0_PORT_MODULE                        (kPORT_I2C0)
#define I2C_0_LOCATION_0_PORT_PIN_SELECT                    (kPORT_I2C0_SCLPTB7_SDAPTB6)

#define I2C_0_LOCATION_0_SDA_PORT                           (kGPIO_PORTB)
#define I2C_0_LOCATION_0_SDA_PIN                            (6U)
#define I2C_0_LOCATION_0_SCL_PORT                           (kGPIO_PORTB)
#define I2C_0_LOCATION_0_SCL_PIN                            (7U)
#endif

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define I2C_0_LOCATION_1_CLOCK_NAME                         (kCLOCK_PortA)
#define I2C_0_LOCATION_1_SDA_PORT                           (PORTA)
#define I2C_0_LOCATION_1_SDA_PIN                            (2U)
#define I2C_0_LOCATION_1_SDA_PORT_MUX                       (kPORT_MuxAlt3)
#define I2C_0_LOCATION_1_SCL_PORT                           (PORTA)
#define I2C_0_LOCATION_1_SCL_PIN                            (3U)
#define I2C_0_LOCATION_1_SCL_PORT_MUX                       (kPORT_MuxAlt3)

#define I2C_0_LOCATION_1_SDA_GPIO                           (GPIOA)
#define I2C_0_LOCATION_1_SCL_GPIO                           (GPIOA)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION) || (MAKE_VERSION(2, 0, 2) == FSL_PORT_DRIVER_VERSION)
#define I2C_0_LOCATION_1_CLOCK_NAME                         (kCLOCK_I2c0)
#define I2C_0_LOCATION_1_PORT_SET_PIN_SELECT_NEEDED         (true)
#define I2C_0_LOCATION_1_PORT_MODULE                        (kPORT_I2C0)
#define I2C_0_LOCATION_1_PORT_PIN_SELECT                    (kPORT_I2C0_SCLPTA3_SDAPTA2)

#define I2C_0_LOCATION_1_SDA_PORT                           (kGPIO_PORTA)
#define I2C_0_LOCATION_1_SDA_PIN                            (2U)
#define I2C_0_LOCATION_1_SCL_PORT                           (kGPIO_PORTA)
#define I2C_0_LOCATION_1_SCL_PIN                            (3U)
#endif

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
