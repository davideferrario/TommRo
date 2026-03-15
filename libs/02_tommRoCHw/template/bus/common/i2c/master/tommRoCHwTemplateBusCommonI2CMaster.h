
#ifndef TOMMROC_HW_TEMPLATE_BUS_COMMON_I2C_MASTER_H_
#define TOMMROC_HW_TEMPLATE_BUS_COMMON_I2C_MASTER_H_

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

/*******************************************************************************
 * defines
 ******************************************************************************/
#define I2C_MASTER_RETRY_COUNT                          (3)

#define I2C_MASTER_WRITE_x_BYTE_TIMEOUT_MSEC            ((uint32_t) 5)
#define I2C_MASTER_READ_x_BYTE_TIMEOUT_MSEC             ((uint32_t) 5)
#define I2C_MASTER_WRITE_READ_x_BYTE_TIMEOUT_MSEC       ((uint32_t) 5)
#define I2C_MASTER_WAIT_STATUS_x_BYTE_LENGTH_MSEC       ((uint32_t) 5)

#define I2C_MASTER_ON_ERROR_WAIT_MSEC                   ((uint32_t) 10)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
