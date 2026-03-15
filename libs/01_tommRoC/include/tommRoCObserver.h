
#ifndef TOMMROC_OBSERVER_H_
#define TOMMROC_OBSERVER_H_

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
 * @defgroup tommRoCObserver tommRoCObserver
 *
 * @brief  TommRoC library observer module
 * @author TommRo Software Department
 *
 * This module is providing observer pattern implementation for embedded device functionality.
 *
 * It is based on objects (tasks) that attach on observer to receive specific event generation notifications.
 * The event notification is made asynchronously by other objects.
 *
 * The identification of event to observe/notify is made by strings (topic).
 * Every object that observe specific topic string, will receive (callback function will be called) event notification.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCGuard.h"
#include "tommRoCList.h"
#include "tommRoCString.h"
#include "tommRoCUtil.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

#define TOMMROC_OBSERVER_TOPIC_STR_MAX_LENGTH   (16)                                                                                // Max length of topic string [byte]
#define TOMMROC_OBSERVER_TOPIC_STR_MAX_SIZE     (TOMMROC_OBSERVER_TOPIC_STR_MAX_LENGTH + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)  // Max size of topic string [byte]

#define TOMMROC_OBSERVER_OBJ_BASE_SIZE          (TOMMROC_OBSERVER_TOPIC_STR_MAX_SIZE + TOMMROC_UTIL_FUNCT_PTR_SIZE)                 // Object base size [byte]

#define TOMMROC_OBSERVER_HANDLE_SIZE            (TOMMROC_LIST_HANDLE_SIZE + TOMMROC_UTIL_PTR_SIZE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC observer on notify callback function type definition.
typedef void (*tommRoC_observer_on_notify_cb_funct_t)(
        const   char*       const   topicStrPtr,
        const   void*       const   dataBufferPtr,
        const   uint32_t            dataBufferSize);

// tommRoC observer struct.
typedef struct {
    uint8_t data[TOMMROC_OBSERVER_HANDLE_SIZE];
} tommRoC_observer_t;

#define __EMPTY_tommRoC_observer_t_data_field__             TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_OBSERVER_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_observer_t__                        \
{                                                           \
    /* .data */ __EMPTY_tommRoC_observer_t_data_field__,    \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init an observer struct.
 *
 * param[in]        bufferPtr               observer low level buffer pointer.
 * param[in]        bufferSize              observer low level buffer size [byte].
 *                                          NOTE: MUST be multiple of TOMMROC_OBSERVER_OBJ_BASE_SIZE.
 * param[in]        guardPtr                observer guard pointer (set to NULL to disable).
 * param[out]       observerHandlePtr       observer handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCObserverInit(
                void*                                   const   bufferPtr,
        const   uint32_t                                        bufferSize,
        const   tommRoC_guard_t*                        const   guardPtr,
                tommRoC_observer_t*                     const   observerHandlePtr);

/**
 * Attach an object to an observer struct.
 *
 * param[in/out]    observerHandlePtr       observer handle pointer.
 * param[in]        topicStrPtr             to attach topic string pointer.
 * param[in]        onNotifyCbFunctPtr      on notify on topic function callback.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCObserverAttach(
                tommRoC_observer_t*                     const   observerHandlePtr,
        const   char*                                   const   topicStrPtr,
        const   tommRoC_observer_on_notify_cb_funct_t           onNotifyCbFunctPtr);

/**
 * Detach an object to an observer struct.
 *
 * param[in/out]    observerHandlePtr       observer handle pointer.
 * param[in]        topicStrPtr             to detach topic string pointer.
 * param[in]        onNotifyCbFunctPtr      on notify on topic function callback.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCObserverDetach(
                tommRoC_observer_t*                     const   observerHandlePtr,
        const   char*                                   const   topicStrPtr,
        const   tommRoC_observer_on_notify_cb_funct_t           onNotifyCbFunctPtr);

/**
 * Check if an object is attached to an observer struct.
 *
 * param[in]        observerHandlePtr       observer handle pointer.
 * param[in]        topicStrPtr             to attach topic string pointer.
 * param[in]        onNotifyCbFunctPtr      on notify on topic function callback.
 * param[out]       isAttachedPtr           is attached status pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCObserverIsAttached(
        const   tommRoC_observer_t*                     const   observerHandlePtr,
        const   char*                                   const   topicStrPtr,
        const   tommRoC_observer_on_notify_cb_funct_t           onNotifyCbFunctPtr,
                bool*                                   const   isAttachedPtr);

/**
 * Notify an event to attached objects.
 *
 * param[in]        observerHandlePtr       observer handle pointer.
 * param[in]        topicStrPtr             to notify topic string pointer.
 * param[in]        dataBufferPtr           to notify data buffer pointer (NULL if none).
 * param[in]        dataBufferSize          to notify data buffer size [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCObserverNotify(
        const   tommRoC_observer_t*                     const   observerHandlePtr,
        const   char*                                   const   topicStrPtr,
        const   void*                                   const   dataBufferPtr,
        const   uint32_t                                        dataBufferSize);

/**
 * @}
 */

#endif
