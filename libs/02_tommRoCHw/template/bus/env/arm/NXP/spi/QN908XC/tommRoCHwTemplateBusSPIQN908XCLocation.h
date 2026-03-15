
#ifndef TOMMROC_HW_TEMPLATE_BUS_SPI_QN908XC_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_SPI_QN908XC_LOCATION_H_

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

/******************* SPI0 location */

#define SPI_0_LOCATION_0_CLOCK_NAME                         (kCLOCK_Flexcomm2)
#define SPI_0_LOCATION_0_SCK_PORT_IDX                       (0)
#define SPI_0_LOCATION_0_SCK_PIN                            (29U)
#define SPI_0_LOCATION_0_SCK_IOCON_FUNC                     (IOCON_FUNC4)
#define SPI_0_LOCATION_0_MISO_PORT_IDX                      (0)
#define SPI_0_LOCATION_0_MISO_PIN                           (27U)
#define SPI_0_LOCATION_0_MISO_IOCON_FUNC                    (IOCON_FUNC4)
#define SPI_0_LOCATION_0_MOSI_PORT_IDX                      (0)
#define SPI_0_LOCATION_0_MOSI_PIN                           (26U)
#define SPI_0_LOCATION_0_MOSI_IOCON_FUNC                    (IOCON_FUNC4)

#define SPI_0_LOCATION_0_SCK_GPIO                           (GPIOA)
#define SPI_0_LOCATION_0_MISO_GPIO                          (GPIOA)
#define SPI_0_LOCATION_0_MOSI_GPIO                          (GPIOA)

#define SPI_0_LOCATION_1_CLOCK_NAME                         (kCLOCK_Flexcomm2)
#define SPI_0_LOCATION_1_SCK_PORT_IDX                       (0)
#define SPI_0_LOCATION_1_SCK_PIN                            (30U)
#define SPI_0_LOCATION_1_SCK_IOCON_FUNC                     (IOCON_FUNC4)
#define SPI_0_LOCATION_1_MISO_PORT_IDX                      (0)
#define SPI_0_LOCATION_1_MISO_PIN                           (5U)
#define SPI_0_LOCATION_1_MISO_IOCON_FUNC                    (IOCON_FUNC5)
#define SPI_0_LOCATION_1_MOSI_PORT_IDX                      (0)
#define SPI_0_LOCATION_1_MOSI_PIN                           (4U)
#define SPI_0_LOCATION_1_MOSI_IOCON_FUNC                    (IOCON_FUNC5)

#define SPI_0_LOCATION_1_SCK_GPIO                           (GPIOA)
#define SPI_0_LOCATION_1_MISO_GPIO                          (GPIOA)
#define SPI_0_LOCATION_1_MOSI_GPIO                          (GPIOA)


/******************* SPI1 location */

#define SPI_1_LOCATION_0_CLOCK_NAME                         (kCLOCK_Flexcomm3)
#define SPI_1_LOCATION_0_SCK_PORT_IDX                       (0)
#define SPI_1_LOCATION_0_SCK_PIN                            (31U)
#define SPI_1_LOCATION_0_SCK_IOCON_FUNC                     (IOCON_FUNC5)
#define SPI_1_LOCATION_0_MISO_PORT_IDX                      (0)
#define SPI_1_LOCATION_0_MISO_PIN                           (29U)
#define SPI_1_LOCATION_0_MISO_IOCON_FUNC                    (IOCON_FUNC5)
#define SPI_1_LOCATION_0_MOSI_PORT_IDX                      (0)
#define SPI_1_LOCATION_0_MOSI_PIN                           (30U)
#define SPI_1_LOCATION_0_MOSI_IOCON_FUNC                    (IOCON_FUNC5)

#define SPI_1_LOCATION_0_SCK_GPIO                           (GPIOA)
#define SPI_1_LOCATION_0_MISO_GPIO                          (GPIOA)
#define SPI_1_LOCATION_0_MOSI_GPIO                          (GPIOA)

#define SPI_1_LOCATION_1_CLOCK_NAME                         (kCLOCK_Flexcomm3)
#define SPI_1_LOCATION_1_SCK_PORT_IDX                       (0)
#define SPI_1_LOCATION_1_SCK_PIN                            (15U)
#define SPI_1_LOCATION_1_SCK_IOCON_FUNC                     (IOCON_FUNC5)
#define SPI_1_LOCATION_1_MISO_PORT_IDX                      (0)
#define SPI_1_LOCATION_1_MISO_PIN                           (17U)
#define SPI_1_LOCATION_1_MISO_IOCON_FUNC                    (IOCON_FUNC5)
#define SPI_1_LOCATION_1_MOSI_PORT_IDX                      (0)
#define SPI_1_LOCATION_1_MOSI_PIN                           (16U)
#define SPI_1_LOCATION_1_MOSI_IOCON_FUNC                    (IOCON_FUNC5)

#define SPI_1_LOCATION_1_SCK_GPIO                           (GPIOA)
#define SPI_1_LOCATION_1_MISO_GPIO                          (GPIOA)
#define SPI_1_LOCATION_1_MOSI_GPIO                          (GPIOA)

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
