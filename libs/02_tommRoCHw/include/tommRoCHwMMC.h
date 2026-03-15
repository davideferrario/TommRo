
#ifndef TOMMROC_HW_MMC_H_
#define TOMMROC_HW_MMC_H_

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

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC hardware layer MMC properties.
typedef enum {
dummy=0,
    /**
     * tommRoC hardware library MMC layer properties.
     * NOTE: properties are get/set into tommRoC hardware layer MMC.
     */

    /**
     * External implemented MMC layer properties.
     * NOTE: properties are get/set into external implementation of layer MMC.
     */

} tommRoC_hw_mmc_prop_enum_t;


// tommRoC hardware layer MMC callback functions type definition.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_mmc_write_buffer_funct_t)(
        const   uint32_t                            logicalAddStart,
        const   void*                       const   writeBufferPtr,
        const   uint32_t                            writeBufferLen,
                uint32_t*                   const   writtenLenPtr);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_mmc_read_buffer_funct_t)(
        const   uint32_t                            logicalAddStart,
                void*                       const   readBufferPtr,
        const   uint32_t                            readBufferLen,
                uint32_t*                   const   readedLenPtr);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_mmc_low_power_enter_funct_t)(void);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_mmc_low_power_exit_funct_t)(void);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_mmc_get_prop_funct_t)(
        const   tommRoC_hw_mmc_prop_enum_t          property,
                void*                       const   propValuePtr);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_mmc_set_prop_funct_t)(
        const   tommRoC_hw_mmc_prop_enum_t          property,
        const   void*                       const   propValuePtr);


// tommRoC hardware layer MMC callback functions.
typedef struct {

    tommRoC_hw_mmc_write_buffer_funct_t     writeBuffer;    // Write buffer.
    tommRoC_hw_mmc_read_buffer_funct_t      readBuffer;     // Read buffer.
    tommRoC_hw_mmc_low_power_enter_funct_t  lowPowerEnter;  // Low power enter.
    tommRoC_hw_mmc_low_power_exit_funct_t   lowPowerExit;   // Low power exit.
    tommRoC_hw_mmc_get_prop_funct_t         getProp;        // Get property.
    tommRoC_hw_mmc_set_prop_funct_t         setProp;        // Set property.

} tommRoC_hw_mmc_cb_funct_t;

// tommRoC hardware layer MMC.
typedef struct {

    /**
     * Callback functions structure.
     */
    tommRoC_hw_mmc_cb_funct_t*  cbFunctPtr;

} tommRoC_hw_mmc_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Reset MMC callback functions structure.
 *
 * param[out]       cbFunctPtr              MMC callback funct structure.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwMMCCbFunctReset(
                tommRoC_hw_mmc_cb_funct_t*  const   cbFunctPtr);

/**
 * Init MMC.
 *
 * param[in]        cbFunctPtr              MMC callback funct structure.
 * param[out]       MMCPtr                  MMC handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwMMCInit(
        const   tommRoC_hw_mmc_cb_funct_t*  const   cbFunctPtr,
                tommRoC_hw_mmc_t*           const   MMCPtr);

/**
 * Check if a MMC is valid.
 *
 * param[in]        MMCPtr                  MMC handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwMMCCheck(
        const   tommRoC_hw_mmc_t*           const   MMCPtr);

/**
 * Write buffer on MMC.
 *
 * param[in]        MMCPtr                  MMC handle pointer.
 * param[in]        logicalAddStart         logical address to start to write.
 * param[in]        writeBufferPtr          data buffer pointer.
 * param[in]        writeBufferLen          data buffer length [byte].
 * param[out]       writtenLenPtr           written data buffer length [byte] pointer.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwMMCWriteBuffer(
        const   tommRoC_hw_mmc_t*           const   MMCPtr,
        const   uint32_t                            logicalAddStart,
        const   void*                       const   writeBufferPtr,
        const   uint32_t                            writeBufferLen,
                uint32_t*                   const   writtenLenPtr);

/**
 * Read buffer from MMC.
 *
 * param[in]        MMCPtr                  MMC handle pointer.
 * param[in]        logicalAddStart         logical address to start to read.
 * param[in]        readBufferPtr           data buffer pointer.
 * param[in]        readBufferLen           data buffer length [byte].
 * param[out]       readedLenPtr            readed data buffer length [byte] pointer.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwMMCReadBuffer(
        const   tommRoC_hw_mmc_t*           const   MMCPtr,
        const   uint32_t                            logicalAddStart,
                void*                       const   readBufferPtr,
        const   uint32_t                            readBufferLen,
                uint32_t*                   const   readedLenPtr);

/**
 * Prepare MMC for entering low power.
 *
 * param[in]        MMCPtr                  MMC handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwMMCLowPowerEnter(
        const   tommRoC_hw_mmc_t*           const   MMCPtr);

/**
 * Prepare MMC for exiting low power.
 *
 * param[in]        MMCPtr                  MMC handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwMMCLowPowerExit(
        const   tommRoC_hw_mmc_t*           const   MMCPtr);

/**
 * Get a prop.
 *
 * param[in]        MMCPtr                  MMC handle pointer.
 * param[in]        property                property.
 * param[out]       propValuePtr            output property value pointer.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwMMCGetProp(
        const   tommRoC_hw_mmc_t*           const   MMCPtr,
        const   tommRoC_hw_mmc_prop_enum_t          property,
                void*                       const   propValuePtr);

/**
 * Set a prop.
 *
 * param[in]        MMCPtr                  MMC handle pointer.
 * param[in]        property                property.
 * param[in]        propValuePtr            property value pointer.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwMMCSetProp(
                tommRoC_hw_mmc_t*           const   MMCPtr,
        const   tommRoC_hw_mmc_prop_enum_t          property,
        const   void*                       const   propValuePtr);

#endif
