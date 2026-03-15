
#ifndef TOMMROC_HW_MEMORY_H_
#define TOMMROC_HW_MEMORY_H_

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
#include "tommRoCHwErr.h"

#include "TOMMROC.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC memory layer properties.
typedef enum {

    /**
     * Memory size property [byte].
     *
     * Available:   get
     * Notes:       propValuePtr has to be uint32_t*
     */
    TOMMRO_C_HW_MEMORY_SIZE_BYTE_PROP = 0,

    /**
     * Memory minimum erasable size property [byte].
     *
     * Available:   get
     * Notes:       propValuePtr has to be uint32_t*
     */
    TOMMRO_C_HW_MEMORY_MINIMUM_ERASABLE_SIZE_BYTE_PROP,

    /**
     * Memory maximum erasable size property [byte].
     * NOTE: maximum erasable size EXCEPT THAT chip erase function.
     *
     * Available:   get
     * Notes:       propValuePtr has to be uint32_t*
     */
    TOMMRO_C_HW_MEMORY_MAXIMUM_ERASABLE_SIZE_BYTE_PROP,

} tommRoC_hw_memory_prop_enum_t;


// tommRoC hardware layer memory callback functions type definition.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_memory_complete_erase_funct_t)(
        const   void*       const   specificHandlePtr);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_memory_write_buffer_funct_t)(
        const   void*       const   specificHandlePtr,
        const   uint32_t            startAddress,
        const   uint8_t*    const   writeBufferPtr,
        const   uint16_t            writeBufferLen);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_memory_read_buffer_funct_t)(
        const   void*       const   specificHandlePtr,
        const   uint32_t            startAddress,
                uint8_t*    const   readBufferPtr,
        const   uint16_t            toReadAmount);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_memory_get_prop_funct_t)(
        const   void*                           const   specificHandlePtr,
        const   tommRoC_hw_memory_prop_enum_t           property,
                void*                           const   propValuePtr);

// tommRoC hardware layer memory callback functions.
typedef struct {

    // Complete erase
    tommRoC_hw_memory_complete_erase_funct_t    completeErase;

    // Write buffer.
    tommRoC_hw_memory_write_buffer_funct_t      writeBuffer;

    // Read buffer.
    tommRoC_hw_memory_read_buffer_funct_t       readBuffer;

    // Get property.
    tommRoC_hw_memory_get_prop_funct_t          getProp;

} tommRoC_hw_memory_cb_funct_t;

// tommRoC hardware layer memory.
typedef struct {

    // Callback functions structure pointer.
    tommRoC_hw_memory_cb_funct_t*   cbFunctPtr;

    // Memory specific handle pointer.
    void*                           specificHandlePtr;

    // Guard (NULL if disabled).
    tommRoC_guard_t*                guardPtr;

} tommRoC_hw_memory_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Reset memory callback functions structure.
 *
 * param[out]       cbFunctPtr              memory callback funct structure.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwMemoryCbFunctReset(
                tommRoC_hw_memory_cb_funct_t*   const   cbFunctPtr);

/**
 * Init memory.
 *
 * param[in]        cbFunctPtr              memory callback structure pointer.
 * param[in]        specificHandlePtr       memory specific handle pointer.
 * param[in]        guardPtr                memory guard (NULL if none).
 * param[out]       handlePtr               memory handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwMemoryInit(
        const   tommRoC_hw_memory_cb_funct_t*   const   cbFunctPtr,
        const   void*                           const   specificHandlePtr,
        const   tommRoC_guard_t*                const   guardPtr,
                tommRoC_hw_memory_t*            const   handlePtr);

/**
 * Complete erase.
 *
 * param[in]        handlePtr               memory handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwMemoryCompleteErase(
        const   tommRoC_hw_memory_t*            const   handlePtr);

/**
 * Write buffer.
 *
 * param[in]        handlePtr               memory handle pointer.
 * param[in]        startAddress            memory write starting address.
 * param[in]        writeBufferPtr          write data buffer pointer.
 * param[in]        writeBufferLen          write data buffer length.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwMemoryWriteBuffer(
        const   tommRoC_hw_memory_t*            const   handlePtr,
        const   uint32_t                                startAddress,
        const   uint8_t*                        const   writeBufferPtr,
        const   uint16_t                                writeBufferLen);

/**
 * Read buffer.
 *
 * param[in]        handlePtr               memory handle pointer.
 * param[in]        startAddress            memory read starting address.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwMemoryReadBuffer(
        const   tommRoC_hw_memory_t*            const   handlePtr,
        const   uint32_t                                startAddress,
                uint8_t*                        const   readBufferPtr,
        const   uint16_t                                toReadAmount);

/**
 * Get memory property.
 *
 * param[in]        handlePtr               memory handle pointer.
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwMemoryGetProp(
        const   tommRoC_hw_memory_t*            const   handlePtr,
        const   tommRoC_hw_memory_prop_enum_t           property,
                void*                           const   propValuePtr);

#endif
