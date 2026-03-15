
#ifndef TOMMROC_HW_TEMPLATE_BUS_SPI_EFM32GG990_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_SPI_EFM32GG990_LOCATION_H_

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

#if (defined (USART_PRESENT) && USART_COUNT)
#include "em_usart.h"
#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

#if defined (EFM32GG990F1024)       ||  \
    defined (EFM32GG990F512)

/******************* SPI0 location */

#define SPI_0_LOCATION_0_SCK_PORT           (gpioPortE)
#define SPI_0_LOCATION_0_SCK_PIN            (12)
#define SPI_0_LOCATION_0_MISO_PORT          (gpioPortE)
#define SPI_0_LOCATION_0_MISO_PIN           (11)
#define SPI_0_LOCATION_0_MOSI_PORT          (gpioPortE)
#define SPI_0_LOCATION_0_MOSI_PIN           (10)

#define SPI_0_LOCATION_1_SCK_PORT           (gpioPortE)
#define SPI_0_LOCATION_1_SCK_PIN            (5)
#define SPI_0_LOCATION_1_MISO_PORT          (gpioPortE)
#define SPI_0_LOCATION_1_MISO_PIN           (6)
#define SPI_0_LOCATION_1_MOSI_PORT          (gpioPortE)
#define SPI_0_LOCATION_1_MOSI_PIN           (7)

#define SPI_0_LOCATION_2_SCK_PORT           (gpioPortC)
#define SPI_0_LOCATION_2_SCK_PIN            (9)
#define SPI_0_LOCATION_2_MISO_PORT          (gpioPortC)
#define SPI_0_LOCATION_2_MISO_PIN           (10)
#define SPI_0_LOCATION_2_MOSI_PORT          (gpioPortC)
#define SPI_0_LOCATION_2_MOSI_PIN           (11)

#define SPI_0_LOCATION_4_SCK_PORT           (gpioPortB)
#define SPI_0_LOCATION_4_SCK_PIN            (13)
#define SPI_0_LOCATION_4_MISO_PORT          (gpioPortB)
#define SPI_0_LOCATION_4_MISO_PIN           (8)
#define SPI_0_LOCATION_4_MOSI_PORT          (gpioPortB)
#define SPI_0_LOCATION_4_MOSI_PIN           (7)

#define SPI_0_LOCATION_5_SCK_PORT           (gpioPortB)
#define SPI_0_LOCATION_5_SCK_PIN            (13)
#define SPI_0_LOCATION_5_MISO_PORT          (gpioPortC)
#define SPI_0_LOCATION_5_MISO_PIN           (1)
#define SPI_0_LOCATION_5_MOSI_PORT          (gpioPortC)
#define SPI_0_LOCATION_5_MOSI_PIN           (0)


/******************* SPI1 location */

#define SPI_1_LOCATION_0_SCK_PORT           (gpioPortB)
#define SPI_1_LOCATION_0_SCK_PIN            (7)
#define SPI_1_LOCATION_0_MISO_PORT          (gpioPortC)
#define SPI_1_LOCATION_0_MISO_PIN           (1)
#define SPI_1_LOCATION_0_MOSI_PORT          (gpioPortC)
#define SPI_1_LOCATION_0_MOSI_PIN           (0)

#define SPI_1_LOCATION_1_SCK_PORT           (gpioPortD)
#define SPI_1_LOCATION_1_SCK_PIN            (2)
#define SPI_1_LOCATION_1_MISO_PORT          (gpioPortD)
#define SPI_1_LOCATION_1_MISO_PIN           (1)
#define SPI_1_LOCATION_1_MOSI_PORT          (gpioPortD)
#define SPI_1_LOCATION_1_MOSI_PIN           (0)

#define SPI_1_LOCATION_2_SCK_PORT           (gpioPortF)
#define SPI_1_LOCATION_2_SCK_PIN            (0)
#define SPI_1_LOCATION_2_MISO_PORT          (gpioPortD)
#define SPI_1_LOCATION_2_MISO_PIN           (6)
#define SPI_1_LOCATION_2_MOSI_PORT          (gpioPortD)
#define SPI_1_LOCATION_2_MOSI_PIN           (7)


/******************* SPI2 location */

#define SPI_2_LOCATION_0_SCK_PORT           (gpioPortC)
#define SPI_2_LOCATION_0_SCK_PIN            (4)
#define SPI_2_LOCATION_0_MISO_PORT          (gpioPortC)
#define SPI_2_LOCATION_0_MISO_PIN           (3)
#define SPI_2_LOCATION_0_MOSI_PORT          (gpioPortC)
#define SPI_2_LOCATION_0_MOSI_PIN           (2)

#define SPI_2_LOCATION_1_SCK_PORT           (gpioPortB)
#define SPI_2_LOCATION_1_SCK_PIN            (5)
#define SPI_2_LOCATION_1_MISO_PORT          (gpioPortB)
#define SPI_2_LOCATION_1_MISO_PIN           (4)
#define SPI_2_LOCATION_1_MOSI_PORT          (gpioPortB)
#define SPI_2_LOCATION_1_MOSI_PIN           (3)

#endif

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
