
#ifndef TOMMROC_MW_TEMPLATE_RTOS_QUEUE_FIFO_H_
#define TOMMROC_MW_TEMPLATE_RTOS_QUEUE_FIFO_H_

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

#include "tommRoCMwTemplateRTOSMutex.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef struct {

    void*           dataBufferPtr;
    uint32_t        msgSizeByte;
    tommRoC_fifo_t  FIFO;
    tommRoC_queue_t queue;

    tommRoC_mw_template_mutex_t mutex;

} tommRoC_mw_template_rtos_queue_fifo_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
