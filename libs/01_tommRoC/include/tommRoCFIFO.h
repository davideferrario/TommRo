
#ifndef TOMMROC_FIFO_H_
#define TOMMROC_FIFO_H_

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
 * @defgroup tommRoCFIFO tommRoCFIFO
 *
 * @brief  TommRoC library FIFO module
 * @author TommRo Software Department
 *
 * This module is providing FIFO (First In-First Out) and FIFOISR functionality.
 *
 * FIFO is a generic FIFO buffer with multi-thread protection guard (optional).
 *
 * FIFOISR is an optimized for ISR (Interrupt Service Routine) FIFO buffer.
 * It has no multi-thread protection guard and it has faster performances.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCGuard.h"
#include "tommRoCUtil.h"

#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

#define TOMMROC_FIFO_MIN_BUF_SIZE       (1)     // For FIFO, buffer size must be greater/equals than 1
#define TOMMROC_FIFO_ISR_MIN_BUF_SIZE   (1 + 1) // For FIFO ISR, buffer size must be greater/equals than 2


// tommRoC FIFO.
#define TOMMROC_FIFO_HANDLE_SIZE            (   TOMMROC_UTIL_U32_SIZE   +   \
                                                TOMMROC_UTIL_U32_SIZE   +   \
                                                TOMMROC_UTIL_U32_SIZE   +   \
                                                TOMMROC_UTIL_U32_SIZE   +   \
                                                TOMMROC_UTIL_PTR_SIZE   +   \
                                                TOMMROC_UTIL_PTR_SIZE   +   \
                                                TOMMROC_UTIL_BOOL_SIZE      )

// tommRoC FIFO ISR.
#define TOMMROC_FIFO_ISR_HANDLE_SIZE        (   TOMMROC_UTIL_PTR_SIZE   +   \
                                                TOMMROC_UTIL_U32_SIZE   +   \
                                                TOMMROC_UTIL_U32_SIZE   +   \
                                                TOMMROC_UTIL_U32_SIZE       )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC fifo status.
typedef enum {

    /**
     * Empty FIFO.
     */
    TOMMRO_C_FIFO_EMPTY = 0,

    /**
     * With data FIFO.
     */
    TOMMRO_C_FIFO_WITH_DATA,

    /**
     * Full FIFO.
     */
    TOMMRO_C_FIFO_FULL,

} tommRoC_fifo_status_enum_t;


// tommRoC FIFO.
typedef struct {
    uint8_t data[TOMMROC_FIFO_HANDLE_SIZE];
} tommRoC_fifo_t;

#define __EMPTY_tommRoC_fifo_t_data_field__             TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_FIFO_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_fifo_t__                        \
{                                                       \
    /* .data */ __EMPTY_tommRoC_fifo_t_data_field__,    \
}


// tommRoC FIFO ISR.
typedef struct {
    uint8_t data[TOMMROC_FIFO_ISR_HANDLE_SIZE];
} tommRoC_fifo_ISR_t;

#define __EMPTY_tommRoC_fifo_ISR_t_data_field__             TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_FIFO_ISR_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_fifo_ISR_t__                        \
{                                                           \
    /* .data */ __EMPTY_tommRoC_fifo_ISR_t_data_field__,    \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* Standard FIFO structure functions */

/**
 * Init a FIFO struct.
 *
 * param[in]        objBaseSize             FIFO object size [byte].
 * param[in]        bufferPtr               FIFO buffer pointer.
 * param[in]        bufferSize              FIFO buffer size [byte].
 * param[in]        guardPtr                FIFO guard pointer (set to NULL to disable).
 * param[out]       fifoPtr                 FIFO handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOInit(
        const   uint32_t                    objBaseSize,
                void*               const   bufferPtr,
        const   uint32_t                    bufferSize,
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_fifo_t*     const   fifoPtr);

/**
 * Push a single object.
 *
 * param[in/out]    fifoPtr                 FIFO handle pointer.
 * param[in]        dataBufferPtr           FIFO object data pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOPush(
                tommRoC_fifo_t*     const   fifoPtr,
        const   void*               const   dataBufferPtr);

/**
 * Push multiple objects.
 *
 * param[in/out]    fifoPtr                 FIFO handle pointer.
 * param[in]        dataBufferPtr           FIFO object data pointer.
 * param[in]        objAmount               object amount.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOMultiPush(
                tommRoC_fifo_t*     const   fifoPtr,
        const   void*               const   dataBufferPtr,
        const   uint32_t                    objAmount);

/**
 * Wait for free element and push a single object.
 *
 * param[in/out]    fifoPtr                 FIFO handle pointer.
 * param[in]        dataBufferPtr           FIFO object data pointer.
 * param[in]        timeoutMsec             wait for free element timeout [msec].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOWaitForFreeAndPush(
                tommRoC_fifo_t*     const   fifoPtr,
        const   void*               const   dataBufferPtr,
        const   uint32_t                    timeoutMsec);

/**
 * Wait for free element and push multiple objects.
 *
 * param[in/out]    fifoPtr                 FIFO handle pointer.
 * param[in]        dataBufferPtr           FIFO object data pointer.
 * param[in]        objAmount               object amount.
 * param[in]        timeoutMsec             wait for free element timeout [msec].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOWaitForFreeAndMultiPush(
                tommRoC_fifo_t*     const   fifoPtr,
        const   void*               const   dataBufferPtr,
        const   uint32_t                    objAmount,
        const   uint32_t                    timeoutMsec);

/**
 * Pop a single object.
 *
 * param[in/out]    fifoPtr                 FIFO handle pointer.
 * param[out]       dataBufferPtr           FIFO object data pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOPop(
                tommRoC_fifo_t*     const   fifoPtr,
                void*               const   dataBufferPtr);

/**
 * Pop multiple object.
 *
 * param[in/out]    fifoPtr                 FIFO handle pointer.
 * param[out]       dataBufferPtr           FIFO object data pointer.
 * param[in]        objAmount               object amount.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOMultiPop(
                tommRoC_fifo_t*     const   fifoPtr,
                void*               const   dataBufferPtr,
        const   uint32_t                    objAmount);

/**
 * Wait for inside element and pop a single object.
 *
 * param[in/out]    fifoPtr                 FIFO handle pointer.
 * param[out]       dataBufferPtr           FIFO object data pointer.
 * param[in]        timeoutMsec             wait for inside element timeout [msec].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOWaitForInsideAndPop(
                tommRoC_fifo_t*     const   fifoPtr,
                void*               const   dataBufferPtr,
        const   uint32_t                    timeoutMsec);

/**
 * Wait for inside element and pop multiple object.
 *
 * param[in/out]    fifoPtr                 FIFO handle pointer.
 * param[out]       dataBufferPtr           FIFO object data pointer.
 * param[in]        objAmount               object amount.
 * param[in]        timeoutMsec             wait for inside element timeout [msec].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOWaitForInsideAndMultiPop(
                tommRoC_fifo_t*     const   fifoPtr,
                void*               const   dataBufferPtr,
        const   uint32_t                    objAmount,
        const   uint32_t                    timeoutMsec);

/**
 * Get multiple objects.
 * NOTE: objects are not removed from FIFO.
 *
 * param[in]        fifoPtr                 FIFO handle pointer.
 * param[out]       dataBufferPtr           FIFO object data pointer.
 * param[in]        objAmount               object amount.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOGet(
        const   tommRoC_fifo_t*     const   fifoPtr,
                void*               const   dataBufferPtr,
        const   uint32_t                    objAmount);

/**
 * Wait for inside element and get multiple object.
 *
 * param[in/out]    fifoPtr                 FIFO handle pointer.
 * param[out]       dataBufferPtr           FIFO object data pointer.
 * param[in]        objAmount               object amount.
 * param[in]        timeoutMsec             wait for inside element timeout [msec].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOWaitForInsideAndGet(
                tommRoC_fifo_t*     const   fifoPtr,
                void*               const   dataBufferPtr,
        const   uint32_t                    objAmount,
        const   uint32_t                    timeoutMsec);

/**
 * Skip multiple objects.
 *
 * param[in/out]    fifoPtr                 FIFO handle pointer.
 * param[in]        objAmount               object amount.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOSkip(
                tommRoC_fifo_t*     const   fifoPtr,
        const   uint32_t                    objAmount);

/**
 * Clear a FIFO struct.
 *
 * param[in/out]    fifoPtr                 FIFO handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOClear(
                tommRoC_fifo_t*     const   fifoPtr);

/**
 * Get status of a FIFO struct.
 *
 * param[in]        fifoPtr                 FIFO handle pointer.
 * param[out]       fifoStatusPtr           FIFO status pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOGetStatus(
        const   tommRoC_fifo_t*             const   fifoPtr,
                tommRoC_fifo_status_enum_t* const   fifoStatusPtr);

/**
 * Get empty status of a FIFO struct.
 *
 * param[in]        fifoPtr                 FIFO handle pointer.
 *
 * return bool
 */
bool tommRoCFIFOIsEmpty(
        const   tommRoC_fifo_t*     const   fifoPtr);

/**
 * Get objects amount in a FIFO struct.
 *
 * param[in]        fifoPtr                 FIFO handle pointer.
 * param[out]       amountPtr               inside objects amount pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOInsideObjAmount(
        const   tommRoC_fifo_t*     const   fifoPtr,
                uint32_t*           const   amountPtr);

/**
 * Get free objects amount in a FIFO struct.
 *
 * param[in]        fifoPtr                 FIFO handle pointer.
 * param[out]       amountPtr               free objects amount pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOFreeObjAmount(
        const   tommRoC_fifo_t*     const   fifoPtr,
                uint32_t*           const   amountPtr);


/******************* Fast (ISR) FIFO structure functions */

/**
 * Init a fast FIFO struct (intended for ISR - Interrupt Service Routine).
 * NOTE: - one "location" (byte) of buffer is not used.
 *       - some extra controls are disabled.
 *
 * param[in]        bufferPtr               FIFO buffer pointer.
 * param[in]        bufferSize              FIFO buffer size [byte].
 * param[out]       fifoPtr                 FIFO handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOISRInit(
                uint8_t*            const   bufferPtr,
        const   uint32_t                    bufferSize,
                tommRoC_fifo_ISR_t* const   fifoPtr);

/**
 * Push single byte (ISR specific).
 * NOTE: special version for single byte with implementation as fast as possible.
 *
 * param[in/out]    fifoPtr                 FIFO handle pointer.
 * param[in]        data                    FIFO data byte.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOISRPush(
                tommRoC_fifo_ISR_t* const   fifoPtr,
        const   uint8_t                     data);

/**
 * Push data buffer (ISR specific).
 *
 * param[in/out]    fifoPtr                 FIFO handle pointer.
 * param[in]        dataBufferPtr           FIFO object data pointer.
 * param[in]        dataBufferLen           FIFO object data length.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOISRMultiPush(
                tommRoC_fifo_ISR_t* const   fifoPtr,
        const   uint8_t*            const   dataBufferPtr,
        const   uint32_t                    dataBufferLen);

/**
 * Pop single byte (ISR specific).
 * NOTE: special version for single byte with implementation as fast as possible.
 *
 * param[in/out]    fifoPtr                 FIFO handle pointer.
 * param[out]       dataPtr                 FIFO data byte pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOISRPop(
                tommRoC_fifo_ISR_t* const   fifoPtr,
                uint8_t*            const   dataPtr);

/**
 * Pop data buffer (ISR specific).
 *
 * param[in/out]    fifoPtr                 FIFO handle pointer.
 * param[out]       dataBufferPtr           FIFO object data pointer.
 * param[in]        dataBufferLen           FIFO object data length.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOISRMultiPop(
                tommRoC_fifo_ISR_t* const   fifoPtr,
                uint8_t*            const   dataBufferPtr,
        const   uint32_t                    dataBufferLen);

/**
 * Get single byte (ISR specific).
 * NOTE: objects are not removed from FIFO.
 * NOTE: special version for single byte with implementation as fast as possible.
 *
 * param[in/out]    fifoPtr                 FIFO handle pointer.
 * param[out]       dataPtr                 FIFO data byte pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOISRGet(
                tommRoC_fifo_ISR_t* const   fifoPtr,
                uint8_t*            const   dataPtr);

/**
 * Get data buffer (ISR specific).
 * NOTE: objects are not removed from FIFO.
 *
 * param[in]        fifoPtr                 FIFO handle pointer.
 * param[out]       dataBufferPtr           FIFO object data pointer.
 * param[in]        dataBufferLen           FIFO object data length.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOISRMultiGet(
        const   tommRoC_fifo_ISR_t* const   fifoPtr,
                uint8_t*            const   dataBufferPtr,
        const   uint32_t                    dataBufferLen);

/**
 * Skip objects (ISR specific).
 *
 * param[in/out]    fifoPtr                 FIFO handle pointer.
 * param[in]        dataBufferLen           FIFO object data length.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOISRSkip(
                tommRoC_fifo_ISR_t* const   fifoPtr,
        const   uint32_t                    dataBufferLen);

/**
 * Clear a FIFO struct (ISR specific).
 *
 * param[in/out]    fifoPtr                 FIFO handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOISRClear(
                tommRoC_fifo_ISR_t* const   fifoPtr);

/**
 * Get empty status of a FIFO struct (ISR specific).
 *
 * param[in]        fifoPtr                 FIFO handle pointer.
 *
 * return bool
 */
bool tommRoCFIFOISRIsEmpty(
        const   tommRoC_fifo_ISR_t* const   fifoPtr);

/**
 * Get objects amount in a FIFO struct (ISR specific).
 *
 * param[in]        fifoPtr                 FIFO handle pointer.
 * param[out]       amountPtr               inside objects amount pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOISRInsideObjAmount(
        const   tommRoC_fifo_ISR_t* const   fifoPtr,
                uint32_t*           const   amountPtr);

/**
 * Get free objects amount in a FIFO struct (ISR specific).
 *
 * param[in]        fifoPtr                 FIFO handle pointer.
 * param[out]       amountPtr               free objects amount pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFIFOISRFreeObjAmount(
        const   tommRoC_fifo_ISR_t* const   fifoPtr,
                uint32_t*           const   amountPtr);

/**
 * @}
 */

#endif
