
#ifndef TOMMROC_TEMPLATE_DEBUG_H_
#define TOMMROC_TEMPLATE_DEBUG_H_

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
 *  - ARM:
 *      - __TOMMROC_USE_ARM_DEBUG_TEMPLATE__        hardware ARM ITM SWO
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"

/******************** ARM debug template */
#if defined (__TOMMROC_USE_ARM_DEBUG_TEMPLATE__)
#if defined (__TOMMROC_PRINT_DEBUG_TEMPLATE_IS_USED__)
#error "tommRoC debug template multiple definition"
#else
#define __TOMMROC_PRINT_DEBUG_TEMPLATE_IS_USED__
#endif
#endif


/******************** Debug save template */
#if defined (__TOMMROC_USE_SAVE_DEBUG_TEMPLATE__)
#define __TOMMROC_SAVE_DEBUG_TEMPLATE_IS_USED__
#endif


/******************** Check template is used */
#if defined (__TOMMROC_PRINT_DEBUG_TEMPLATE_IS_USED__) && defined (__TOMMROC_DEBUG_PRINT_USE_ENV_DEFAULT__)
#error "it is not possible to use both __TOMMROC_PRINT_DEBUG_TEMPLATE_IS_USED__ and __TOMMROC_DEBUG_PRINT_USE_ENV_DEFAULT__"
#endif

#if !defined (__TOMMROC_DEBUG_ENABLE__) && defined (__TOMMROC_USE_SAVE_DEBUG_TEMPLATE__)
#warning "tommRoC debug disabled BUT tommRoC save debug template used"
#endif

#if !defined (__TOMMROC_DEBUG_ENABLE__) && defined (__TOMMROC_PRINT_DEBUG_TEMPLATE_IS_USED__)
#warning "tommRoC debug disabled BUT tommRoC debug template used"
#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef struct {

    tommRoC_debug_funct_enabled_status_t*   libDebugStatusPtr;
    tommRoC_guard_t*                        printGuardPtr;
    tommRoC_guard_t*                        saveGuardPtr;

} tommRoC_template_debug_init_t;

#define __EMPTY_tommRoC_template_debug_init_t__             \
{                                                           \
    /* .libDebugStatusPtr */    NULL,                       \
    /* .printGuardPtr */        NULL,                       \
    /* .saveGuardPtr */         NULL,                       \
}


/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateDebugStart(
        const   tommRoC_template_debug_init_t*  const   templateInitPtr);

tommRoC_err_enum_t tommRoCTemplateDebugStop(void);

#endif
