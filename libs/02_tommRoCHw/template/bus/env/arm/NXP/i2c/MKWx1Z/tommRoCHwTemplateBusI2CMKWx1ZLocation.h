
#ifndef TOMMROC_HW_TEMPLATE_BUS_I2C_MKWx1Z_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_I2C_MKWx1Z_LOCATION_H_

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

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKWx1Z_IS_USED__)

/*******************************************************************************
 * defines
 ******************************************************************************/

/******************* I2C0 location */

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define I2C_0_LOCATION_0_CLOCK_NAME                         (kCLOCK_PortC)
#define I2C_0_LOCATION_0_SDA_PORT                           (PORTC)
#define I2C_0_LOCATION_0_SDA_PIN                            (1U)
#define I2C_0_LOCATION_0_SDA_PORT_MUX                       (kPORT_MuxAlt3)
#define I2C_0_LOCATION_0_SCL_PORT                           (PORTC)
#define I2C_0_LOCATION_0_SCL_PIN                            (0U)
#define I2C_0_LOCATION_0_SCL_PORT_MUX                       (kPORT_MuxAlt3)

#define I2C_0_LOCATION_0_SDA_GPIO                           (GPIOC)
#define I2C_0_LOCATION_0_SCL_GPIO                           (GPIOC)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define I2C_0_LOCATION_0_CLOCK_NAME                         (kCLOCK_I2c0)
#define I2C_0_LOCATION_0_PORT_SET_PIN_SELECT_NEEDED         (true)
#define I2C_0_LOCATION_0_PORT_MODULE                        (kPORT_I2C0)
#define I2C_0_LOCATION_0_PORT_PIN_SELECT                    (kPORT_I2C0_SCLPTC0_SDAPTC1)

#define I2C_0_LOCATION_0_SDA_PORT                           (kGPIO_PORTC)
#define I2C_0_LOCATION_0_SDA_PIN                            (1U)
#define I2C_0_LOCATION_0_SCL_PORT                           (kGPIO_PORTC)
#define I2C_0_LOCATION_0_SCL_PIN                            (0U)
#endif

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define I2C_0_LOCATION_1_CLOCK_NAME                         (kCLOCK_PortB)
#define I2C_0_LOCATION_1_SDA_PORT                           (PORTB)
#define I2C_0_LOCATION_1_SDA_PIN                            (1U)
#define I2C_0_LOCATION_1_SDA_PORT_MUX                       (kPORT_MuxAlt3)
#define I2C_0_LOCATION_1_SCL_PORT                           (PORTB)
#define I2C_0_LOCATION_1_SCL_PIN                            (0U)
#define I2C_0_LOCATION_1_SCL_PORT_MUX                       (kPORT_MuxAlt3)

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
#define I2C_0_LOCATION_2_CLOCK_NAME                         (kCLOCK_PortC)
#define I2C_0_LOCATION_2_SDA_PORT                           (PORTC)
#define I2C_0_LOCATION_2_SDA_PIN                            (16U)
#define I2C_0_LOCATION_2_SDA_PORT_MUX                       (kPORT_MuxAlt3)
#define I2C_0_LOCATION_2_SCL_PORT                           (PORTC)
#define I2C_0_LOCATION_2_SCL_PIN                            (19U)
#define I2C_0_LOCATION_2_SCL_PORT_MUX                       (kPORT_MuxAlt3)

#define I2C_0_LOCATION_2_SDA_GPIO                           (GPIOC)
#define I2C_0_LOCATION_2_SCL_GPIO                           (GPIOC)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define I2C_0_LOCATION_2_CLOCK_NAME                         (kCLOCK_I2c0)
#define I2C_0_LOCATION_2_PORT_SET_PIN_SELECT_NEEDED         (true)
#define I2C_0_LOCATION_2_PORT_MODULE                        (kPORT_I2C0)
#define I2C_0_LOCATION_2_PORT_PIN_SELECT                    (kPORT_I2C0_SCLPTC19_SDAPTC16)

#define I2C_0_LOCATION_2_SDA_PORT                           (kGPIO_PORTC)
#define I2C_0_LOCATION_2_SDA_PIN                            (16U)
#define I2C_0_LOCATION_2_SCL_PORT                           (kGPIO_PORTC)
#define I2C_0_LOCATION_2_SCL_PIN                            (19U)
#endif


/******************* I2C1 location */

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define I2C_1_LOCATION_0_CLOCK_NAME                         (kCLOCK_PortB)
#define I2C_1_LOCATION_0_SDA_PORT                           (PORTB)
#define I2C_1_LOCATION_0_SDA_PIN                            (17U)
#define I2C_1_LOCATION_0_SDA_PORT_MUX                       (kPORT_MuxAlt3)
#define I2C_1_LOCATION_0_SCL_PORT                           (PORTB)
#define I2C_1_LOCATION_0_SCL_PIN                            (16U)
#define I2C_1_LOCATION_0_SCL_PORT_MUX                       (kPORT_MuxAlt3)

#define I2C_1_LOCATION_0_SDA_GPIO                           (GPIOB)
#define I2C_1_LOCATION_0_SCL_GPIO                           (GPIOB)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define I2C_1_LOCATION_0_CLOCK_NAME                         (kCLOCK_I2c1)
#define I2C_1_LOCATION_0_PORT_SET_PIN_SELECT_NEEDED         (true)
#define I2C_1_LOCATION_0_PORT_MODULE                        (kPORT_I2C1)
#define I2C_1_LOCATION_0_PORT_PIN_SELECT                    (kPORT_I2C1_SCLPTB16_SDAPTB17)

#define I2C_1_LOCATION_0_SDA_PORT                           (kGPIO_PORTB)
#define I2C_1_LOCATION_0_SDA_PIN                            (17U)
#define I2C_1_LOCATION_0_SCL_PORT                           (kGPIO_PORTB)
#define I2C_1_LOCATION_0_SCL_PIN                            (16U)
#endif

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define I2C_1_LOCATION_1_CLOCK_NAME                         (kCLOCK_PortC)
#define I2C_1_LOCATION_1_SDA_PORT                           (PORTC)
#define I2C_1_LOCATION_1_SDA_PIN                            (3U)
#define I2C_1_LOCATION_1_SDA_PORT_MUX                       (kPORT_MuxAlt3)
#define I2C_1_LOCATION_1_SCL_PORT                           (PORTC)
#define I2C_1_LOCATION_1_SCL_PIN                            (2U)
#define I2C_1_LOCATION_1_SCL_PORT_MUX                       (kPORT_MuxAlt3)

#define I2C_1_LOCATION_1_SDA_GPIO                           (GPIOC)
#define I2C_1_LOCATION_1_SCL_GPIO                           (GPIOC)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define I2C_1_LOCATION_1_CLOCK_NAME                         (kCLOCK_I2c1)
#define I2C_1_LOCATION_1_PORT_SET_PIN_SELECT_NEEDED         (true)
#define I2C_1_LOCATION_1_PORT_MODULE                        (kPORT_I2C1)
#define I2C_1_LOCATION_1_PORT_PIN_SELECT                    (kPORT_I2C1_SCLPTC2_SDAPTC3)

#define I2C_1_LOCATION_1_SDA_PORT                           (kGPIO_PORTC)
#define I2C_1_LOCATION_1_SDA_PIN                            (3U)
#define I2C_1_LOCATION_1_SCL_PORT                           (kGPIO_PORTC)
#define I2C_1_LOCATION_1_SCL_PIN                            (2U)
#endif

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define I2C_1_LOCATION_2_CLOCK_NAME                         (kCLOCK_PortC)
#define I2C_1_LOCATION_2_SDA_PORT                           (PORTC)
#define I2C_1_LOCATION_2_SDA_PIN                            (7U)
#define I2C_1_LOCATION_2_SDA_PORT_MUX                       (kPORT_MuxAlt3)
#define I2C_1_LOCATION_2_SCL_PORT                           (PORTC)
#define I2C_1_LOCATION_2_SCL_PIN                            (6U)
#define I2C_1_LOCATION_2_SCL_PORT_MUX                       (kPORT_MuxAlt3)

#define I2C_1_LOCATION_2_SDA_GPIO                           (GPIOC)
#define I2C_1_LOCATION_2_SCL_GPIO                           (GPIOC)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define I2C_1_LOCATION_2_CLOCK_NAME                         (kCLOCK_I2c1)
#define I2C_1_LOCATION_2_PORT_SET_PIN_SELECT_NEEDED         (true)
#define I2C_1_LOCATION_2_PORT_MODULE                        (kPORT_I2C1)
#define I2C_1_LOCATION_2_PORT_PIN_SELECT                    (kPORT_I2C1_SCLPTC6_SDAPTC7)

#define I2C_1_LOCATION_2_SDA_PORT                           (kGPIO_PORTC)
#define I2C_1_LOCATION_2_SDA_PIN                            (7U)
#define I2C_1_LOCATION_2_SCL_PORT                           (kGPIO_PORTC)
#define I2C_1_LOCATION_2_SCL_PIN                            (6U)
#endif

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define I2C_1_LOCATION_3_CLOCK_NAME                         (kCLOCK_PortC)
#define I2C_1_LOCATION_3_SDA_PORT                           (PORTC)
#define I2C_1_LOCATION_3_SDA_PIN                            (18U)
#define I2C_1_LOCATION_3_SDA_PORT_MUX                       (kPORT_MuxAlt3)
#define I2C_1_LOCATION_3_SCL_PORT                           (PORTC)
#define I2C_1_LOCATION_3_SCL_PIN                            (17U)
#define I2C_1_LOCATION_3_SCL_PORT_MUX                       (kPORT_MuxAlt3)

#define I2C_1_LOCATION_3_SDA_GPIO                           (GPIOC)
#define I2C_1_LOCATION_3_SCL_GPIO                           (GPIOC)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#define I2C_1_LOCATION_3_CLOCK_NAME                         (kCLOCK_I2c1)
#define I2C_1_LOCATION_3_PORT_SET_PIN_SELECT_NEEDED         (true)
#define I2C_1_LOCATION_3_PORT_MODULE                        (kPORT_I2C1)
#define I2C_1_LOCATION_3_PORT_PIN_SELECT                    (kPORT_I2C1_SCLPTC17_SDAPTC18)

#define I2C_1_LOCATION_3_SDA_PORT                           (kGPIO_PORTC)
#define I2C_1_LOCATION_3_SDA_PIN                            (18U)
#define I2C_1_LOCATION_3_SCL_PORT                           (kGPIO_PORTC)
#define I2C_1_LOCATION_3_SCL_PIN                            (17U)
#endif

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
