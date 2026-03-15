
#ifndef TOMMROC_HW_TEMPLATE_BUS_I2C_MK22_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_I2C_MK22_LOCATION_H_

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

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MK22_IS_USED__)

/*******************************************************************************
 * defines
 ******************************************************************************/

/******************* I2C0 location */

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define I2C_0_LOCATION_0_CLOCK_NAME                         (kCLOCK_PortB)
#define I2C_0_LOCATION_0_SDA_PORT                           (PORTB)
#define I2C_0_LOCATION_0_SDA_PIN                            (3U)
#define I2C_0_LOCATION_0_SDA_PORT_MUX                       (kPORT_MuxAlt2)
#define I2C_0_LOCATION_0_SCL_PORT                           (PORTB)
#define I2C_0_LOCATION_0_SCL_PIN                            (2U)
#define I2C_0_LOCATION_0_SCL_PORT_MUX                       (kPORT_MuxAlt2)

#define I2C_0_LOCATION_0_SDA_GPIO                           (GPIOB)
#define I2C_0_LOCATION_0_SCL_GPIO                           (GPIOB)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define I2C_0_LOCATION_0_CLOCK_NAME                         (kCLOCK_I2c0)
#define I2C_0_LOCATION_0_PORT_SET_PIN_SELECT_NEEDED         (true)
#define I2C_0_LOCATION_0_PORT_MODULE                        (kPORT_I2C0)
#define I2C_0_LOCATION_0_PORT_PIN_SELECT                    (kPORT_I2C0_SCLPTB2_SDAPTB3)

#define I2C_0_LOCATION_0_SDA_PORT                           (kGPIO_PORTB)
#define I2C_0_LOCATION_0_SDA_PIN                            (3U)
#define I2C_0_LOCATION_0_SCL_PORT                           (kGPIO_PORTB)
#define I2C_0_LOCATION_0_SCL_PIN                            (2U)
#endif

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define I2C_0_LOCATION_1_CLOCK_NAME                         (kCLOCK_PortB)
#define I2C_0_LOCATION_1_SDA_PORT                           (PORTB)
#define I2C_0_LOCATION_1_SDA_PIN                            (1U)
#define I2C_0_LOCATION_1_SDA_PORT_MUX                       (kPORT_MuxAlt2)
#define I2C_0_LOCATION_1_SCL_PORT                           (PORTB)
#define I2C_0_LOCATION_1_SCL_PIN                            (0U)
#define I2C_0_LOCATION_1_SCL_PORT_MUX                       (kPORT_MuxAlt2)

#define I2C_0_LOCATION_1_SDA_GPIO                           (GPIOB)
#define I2C_0_LOCATION_1_SCL_GPIO                           (GPIOB)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define I2C_0_LOCATION_1_CLOCK_NAME                         (kCLOCK_I2c0)
#define I2C_0_LOCATION_1_PORT_SET_PIN_SELECT_NEEDED         (true)
#define I2C_0_LOCATION_1_PORT_MODULE                        (kPORT_I2C0)
#define I2C_0_LOCATION_1_PORT_PIN_SELECT                    (kPORT_I2C0_SCLPTB0_SDAPTB1)

#define I2C_0_LOCATION_1_SDA_PORT                           (kGPIO_PORTB)
#define I2C_0_LOCATION_1_SDA_PIN                            (1U)
#define I2C_0_LOCATION_1_SCL_PORT                           (kGPIO_PORTB)
#define I2C_0_LOCATION_1_SCL_PIN                            (0U)
#endif

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define I2C_0_LOCATION_2_CLOCK_NAME                         (kCLOCK_PortD)
#define I2C_0_LOCATION_2_SDA_PORT                           (PORTD)
#define I2C_0_LOCATION_2_SDA_PIN                            (3U)
#define I2C_0_LOCATION_2_SDA_PORT_MUX                       (kPORT_MuxAlt7)
#define I2C_0_LOCATION_2_SCL_PORT                           (PORTD)
#define I2C_0_LOCATION_2_SCL_PIN                            (2U)
#define I2C_0_LOCATION_2_SCL_PORT_MUX                       (kPORT_MuxAlt7)

#define I2C_0_LOCATION_2_SDA_GPIO                           (GPIOD)
#define I2C_0_LOCATION_2_SCL_GPIO                           (GPIOD)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define I2C_0_LOCATION_2_CLOCK_NAME                         (kCLOCK_I2c0)
#define I2C_0_LOCATION_2_PORT_SET_PIN_SELECT_NEEDED         (true)
#define I2C_0_LOCATION_2_PORT_MODULE                        (kPORT_I2C0)
#define I2C_0_LOCATION_2_PORT_PIN_SELECT                    (kPORT_I2C0_SCLPTD2_SDAPTD3)

#define I2C_0_LOCATION_2_SDA_PORT                           (kGPIO_PORTD)
#define I2C_0_LOCATION_2_SDA_PIN                            (3U)
#define I2C_0_LOCATION_2_SCL_PORT                           (kGPIO_PORTD)
#define I2C_0_LOCATION_2_SCL_PIN                            (2U)
#endif


/******************* I2C1 location */

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define I2C_1_LOCATION_0_CLOCK_NAME                         (kCLOCK_PortC)
#define I2C_1_LOCATION_0_SDA_PORT                           (PORTC)
#define I2C_1_LOCATION_0_SDA_PIN                            (10U)
#define I2C_1_LOCATION_0_SDA_PORT_MUX                       (kPORT_MuxAlt2)
#define I2C_1_LOCATION_0_SCL_PORT                           (PORTC)
#define I2C_1_LOCATION_0_SCL_PIN                            (11U)
#define I2C_1_LOCATION_0_SCL_PORT_MUX                       (kPORT_MuxAlt2)

#define I2C_1_LOCATION_0_SDA_GPIO                           (GPIOC)
#define I2C_1_LOCATION_0_SCL_GPIO                           (GPIOC)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define I2C_1_LOCATION_0_CLOCK_NAME                         (kCLOCK_I2c1)
#define I2C_1_LOCATION_0_PORT_SET_PIN_SELECT_NEEDED         (true)
#define I2C_1_LOCATION_0_PORT_MODULE                        (kPORT_I2C1)
#define I2C_1_LOCATION_0_PORT_PIN_SELECT                    (kPORT_I2C1_SCLPTC11_SDAPTC10)

#define I2C_1_LOCATION_0_SDA_PORT                           (kGPIO_PORTC)
#define I2C_1_LOCATION_0_SDA_PIN                            (10U)
#define I2C_1_LOCATION_0_SCL_PORT                           (kGPIO_PORTC)
#define I2C_1_LOCATION_0_SCL_PIN                            (11U)
#endif

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define I2C_1_LOCATION_1_CLOCK_NAME                         (kCLOCK_PortE)
#define I2C_1_LOCATION_1_SDA_PORT                           (PORTE)
#define I2C_1_LOCATION_1_SDA_PIN                            (0U)
#define I2C_1_LOCATION_1_SDA_PORT_MUX                       (kPORT_MuxAlt6)
#define I2C_1_LOCATION_1_SCL_PORT                           (PORTE)
#define I2C_1_LOCATION_1_SCL_PIN                            (1U)
#define I2C_1_LOCATION_1_SCL_PORT_MUX                       (kPORT_MuxAlt6)

#define I2C_1_LOCATION_1_SDA_GPIO                           (GPIOE)
#define I2C_1_LOCATION_1_SCL_GPIO                           (GPIOE)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define I2C_1_LOCATION_1_CLOCK_NAME                         (kCLOCK_I2c1)
#define I2C_1_LOCATION_1_PORT_SET_PIN_SELECT_NEEDED         (true)
#define I2C_1_LOCATION_1_PORT_MODULE                        (kPORT_I2C1)
#define I2C_1_LOCATION_1_PORT_PIN_SELECT                    (kPORT_I2C1_SCLPTE1_SDAPTE0)

#define I2C_1_LOCATION_1_SDA_PORT                           (kGPIO_PORTE)
#define I2C_1_LOCATION_1_SDA_PIN                            (0U)
#define I2C_1_LOCATION_1_SCL_PORT                           (kGPIO_PORTE)
#define I2C_1_LOCATION_1_SCL_PIN                            (1U)
#endif

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
