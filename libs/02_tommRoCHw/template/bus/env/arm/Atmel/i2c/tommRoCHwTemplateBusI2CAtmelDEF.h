
#ifndef TOMMROC_HW_TEMPLATE_BUS_I2C_ATMEL_DEF_H_
#define TOMMROC_HW_TEMPLATE_BUS_I2C_ATMEL_DEF_H_

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

#if defined (__TOMMROC_TEMPLATE_ARM_ATMEL_IS_USED__)
#include "driver_init.h"

/*******************************************************************************
 * defines
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
#if (defined (I2C0_SDA) && defined (I2C0_SCL))
#define TOMMROC_HW_TEMPLATE_BUS_I2C_ATMEL_DEF_I2C0_SDA  (I2C0_SDA)
#define TOMMROC_HW_TEMPLATE_BUS_I2C_ATMEL_DEF_I2C0_SCL  (I2C0_SCL)
#else
#error "Define I2C0_SCL and I2C0_SDA Pin"
#endif
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
#if (defined (I2C1_SDA) && defined (I2C1_SCL))
#define TOMMROC_HW_TEMPLATE_BUS_I2C_ATMEL_DEF_I2C1_SDA  (I2C1_SDA)
#define TOMMROC_HW_TEMPLATE_BUS_I2C_ATMEL_DEF_I2C1_SCL  (I2C1_SCL)
#else
#error "Define I2C1_SCL and I2C1_SDA Pin"
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
