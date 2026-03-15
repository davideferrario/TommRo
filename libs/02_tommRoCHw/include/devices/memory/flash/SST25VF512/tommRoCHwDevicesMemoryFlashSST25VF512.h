
#ifndef TOMMROC_HW_DEVICES_MEMORY_FLASH_SST25VF512_H_
#define TOMMROC_HW_DEVICES_MEMORY_FLASH_SST25VF512_H_

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
#include "tommRoCHwBus.h"
#include "tommRoCHwBusDevice.h"
#include "tommRoCHwErr.h"
#include "tommRoCHwGPIO.h"
#include "tommRoCHwMemory.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Memory feature size
#define TOMMROC_HW_DEVICES_MEMORY_FLASH_SST25VF512_MEMORY_SIZE_KBIT (512UL)                                                                                 // 512 Kbit
#define TOMMROC_HW_DEVICES_MEMORY_FLASH_SST25VF512_SIZE_BIT         (TOMMROC_UNIT_MEASURE_KBIT_TO_BIT(TOMMROC_HW_DEVICES_MEMORY_FLASH_SST25VF512_MEMORY_SIZE_KBIT))
#define TOMMROC_HW_DEVICES_MEMORY_FLASH_SST25VF512_SIZE_BYTE        (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(TOMMROC_HW_DEVICES_MEMORY_FLASH_SST25VF512_SIZE_BIT)) // 64 KByte
#define TOMMROC_HW_DEVICES_MEMORY_FLASH_SST25VF512_SECTOR_SIZE_BYTE (TOMMROC_UNIT_MEASURE_KBYTE_TO_BYTE(4))
#define TOMMROC_HW_DEVICES_MEMORY_FLASH_SST25VF512_BLOCK_SIZE_BYTE  (TOMMROC_UNIT_MEASURE_KBYTE_TO_BYTE(32))

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init bus device as for SPI master bus.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        chipSelect              chip select function pointer.
 * param[in]        chipDeSelect            chip de-select function pointer.
 * param[in]        busHandlerPtr           bus pointer.
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[out]       specificSlavePtr        output specific SPI slave pointer [needed as static because linked by bus device].
 * param[out]       busDevicePtr            output bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryFlashSST25VF512InitSPI(
        const   tommRoC_hw_gpio_set_cb_t                            chipSelect,
        const   tommRoC_hw_gpio_set_cb_t                            chipDeSelect,
        const   tommRoC_hw_bus_t*                           const   busHandlerPtr,
        const   tommRoC_guard_t*                            const   guardPtr,
                tommRoC_hw_bus_device_specific_spi_slave_t* const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                    const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryFlashSST25VF512Start(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr);

/**
 * Get property.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryFlashSST25VF512GetProp(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr,
        const   tommRoC_hw_memory_prop_enum_t           property,
                void*                           const   propValuePtr);

/**
 * Chip (memory complete) erase.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryFlashSST25VF512ChipErase(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr);

/**
 * Write buffer.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        startAddress            memory start address to write.
 * param[in]        writeBufferPtr          data buffer.
 * param[in]        writeBufferLen          data buffer length.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryFlashSST25VF512WriteBuffer(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr,
        const   uint32_t                                startAddress,
        const   uint8_t*                        const   writeBufferPtr,
        const   uint16_t                                writeBufferLen);

/**
 * Read buffer.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        startAddress            memory start address to read.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryFlashSST25VF512ReadBuffer(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr,
        const   uint32_t                                startAddress,
                uint8_t*                        const   readBufferPtr,
        const   uint16_t                                toReadAmount,
                uint16_t*                       const   readedAmountPtr);

#endif
