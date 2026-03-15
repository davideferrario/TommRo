
#ifndef TOMMROC_HW_TEMPLATE_MONGOOSE_H_
#define TOMMROC_HW_TEMPLATE_MONGOOSE_H_

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

/**
 *  - __TOMMROC_HW_USE_MONGOOSE_TEMPLATE__          to use mongoose library template
 *
 *      - __TOMMROC_HW_USE_MONGOOSE_FAT_FS_FILE_TEMPLATE__          to use FAT FS template as file system for mongoose library
 *      - __TOMMROC_HW_USE_MONGOOSE_TOMMROC_FS_MBED_FILE_TEMPLATE__ to use tommRoC FS Mbed as file system for mongoose library
 *      - __TOMMROC_HW_USE_MONGOOSE_CUSTOM_FILE_TEMPLATE__          to use custom file system for mongoose library
 */

/**
 * Mongoose is a networking library for C/C++.
 * It implements event-driven, non-blocking APIs for TCP, UDP, HTTP, WebSocket, MQTT.
 * It connects devices and brings them online.
 *
 * https://github.com/cesanta/mongoose
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_MONGOOSE_TEMPLATE__)
#include "mongoose/lib/source/lib/mongoose.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif

#endif
