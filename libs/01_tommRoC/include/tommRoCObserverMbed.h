
#ifndef TOMMROC_OBSERVER_MBED_H_
#define TOMMROC_OBSERVER_MBED_H_

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
 * @defgroup tommRoCObserverMbed tommRoCObserverMbed
 *
 * @brief  TommRoC library embedded observer module
 * @author TommRo Software Department
 *
 * This module is providing library embedded observer functionality.
 * It can be used in case of application needs only one observer.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCObserver.h"

#include <stdbool.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init Mbed observer framework.
 * Mbed observer framework is a layer build over tommRoCObserver to be used when only one observer is needed by application.
 * The observer handler is hide to application by this layer.
 *
 * param[in/out]    observerHandlePtr       observer handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCObserverMbedInit(tommRoC_observer_t* const observerHandlePtr);

/**
 * Close Mbed observer framework.
 * The internal observer framework is resetted to initial value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCObserverMbedClose(void);

/**
 * Get Mbed observer framework init status.
 *
 * return bool
 */
bool tommRoCObserverMbedIsInit(void);

/**
 * Attach an object to Mbed observer framework.
 *
 * param[in]        topicStrPtr             to attach topic string pointer.
 * param[in]        onNotifyCbFunctPtr      on notify on topic function callback.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCObserverMbedAttach(
        const   char*                                   const   topicStrPtr,
        const   tommRoC_observer_on_notify_cb_funct_t           onNotifyCbFunctPtr);

/**
 * Detach an object to Mbed observer framework.
 *
 * param[in]        topicStrPtr             to detach topic string pointer.
 * param[in]        onNotifyCbFunctPtr      on notify on topic function callback.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCObserverMbedDetach(
        const   char*                                   const   topicStrPtr,
        const   tommRoC_observer_on_notify_cb_funct_t           onNotifyCbFunctPtr);

/**
 * Check if an object is attached to Mbed observer framework.
 *
 * param[in]        topicStrPtr             to attach topic string pointer.
 * param[in]        onNotifyCbFunctPtr      on notify on topic function callback.
 * param[out]       isAttachedPtr           is attached status pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCObserverMbedIsAttached(
        const   char*                                   const   topicStrPtr,
        const   tommRoC_observer_on_notify_cb_funct_t           onNotifyCbFunctPtr,
                bool*                                   const   isAttachedPtr);

/**
 * Notify an event to attached objects.
 *
 * param[in]        topicStrPtr             to notify topic string pointer.
 * param[in]        dataBufferPtr           to notify data buffer pointer (NULL if none).
 * param[in]        dataBufferSize          to notify data buffer size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCObserverMbedNotify(
        const   char*                                   const   topicStrPtr,
        const   void*                                   const   dataBufferPtr,
        const   uint32_t                                        dataBufferSize);

/**
 * @}
 */

#endif
