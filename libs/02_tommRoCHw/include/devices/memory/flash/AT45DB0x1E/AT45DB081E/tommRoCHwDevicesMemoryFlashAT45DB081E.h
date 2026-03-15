
#ifndef TOMMROC_HW_DEVICES_MEMORY_FLASH_AT45DB081E_H_
#define TOMMROC_HW_DEVICES_MEMORY_FLASH_AT45DB081E_H_

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
#define TOMMROC_HW_DEVICES_MEMORY_FLASH_AT45DB081E_PAGE_AMOUNT                      (4096UL)    // Available page amount.
#define TOMMROC_HW_DEVICES_MEMORY_FLASH_AT45DB081E_PAGE_PER_BLOCK_AMOUNT            (8UL)       // Every block is composed by 8 pages.
#define TOMMROC_HW_DEVICES_MEMORY_FLASH_AT45DB081E_BLOCK_PER_SECTOR_AMOUNT          (32UL)      // Every sector is composed by 32 blocks.
#define TOMMROC_HW_DEVICES_MEMORY_FLASH_AT45DB081E_PAGE_PER_SECTOR_AMOUNT           (TOMMROC_HW_DEVICES_MEMORY_FLASH_AT45DB081E_BLOCK_PER_SECTOR_AMOUNT * TOMMROC_HW_DEVICES_MEMORY_FLASH_AT45DB081E_PAGE_PER_BLOCK_AMOUNT) // Every sector is composed by 256 pages.

#define TOMMROC_HW_DEVICES_MEMORY_FLASH_AT45DB081E_PAGE_SIZE_256_MEMORY_SIZE_BYTE   (TOMMROC_HW_DEVICES_MEMORY_FLASH_AT45DB081E_PAGE_AMOUNT * 256UL)
#define TOMMROC_HW_DEVICES_MEMORY_FLASH_AT45DB081E_PAGE_SIZE_264_MEMORY_SIZE_BYTE   (TOMMROC_HW_DEVICES_MEMORY_FLASH_AT45DB081E_PAGE_AMOUNT * 264UL)


// Device data.
#define TOMMROC_HW_DEVICES_MEMORY_FLASH_AT45DB081E_DEVICE_DATA_SIZE (TOMMROC_UTIL_U16_SIZE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of memory flash AT45DB081E page size type.
typedef enum {

    /**
     * Memory flash is configurated with 264 byte page size.
     * NOTE: defaults.
     */
    TOMMRO_C_HW_DEVICES_MEMORY_FLASH_AT45DB081E_PAGE_SIZE_264_BYTE_TYPE = 0,

    /**
     * Memory flash is configurated with 256 byte page size.
     */
    TOMMRO_C_HW_DEVICES_MEMORY_FLASH_AT45DB081E_PAGE_SIZE_256_BYTE_TYPE,

} tommRoC_hw_devices_memory_flash_at45db081e_page_size_enum_t;


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_MEMORY_FLASH_AT45DB081E_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_memory_flash_at45db081e_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryFlashAT45DB081EInitSPI(
        const   tommRoC_hw_gpio_set_cb_t                            chipSelect,
        const   tommRoC_hw_gpio_set_cb_t                            chipDeSelect,
        const   tommRoC_hw_bus_t*                           const   busHandlerPtr,
        const   tommRoC_guard_t*                            const   guardPtr,
                tommRoC_hw_bus_device_specific_spi_slave_t* const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                    const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryFlashAT45DB081EAttachDeviceData(
        const   tommRoC_hw_devices_memory_flash_at45db081e_device_data_t*   const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        pageSize                memory page size.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryFlashAT45DB081EStart(
        const   tommRoC_hw_devices_memory_flash_at45db081e_page_size_enum_t         pageSize,
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Get property.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryFlashAT45DB081EGetProp(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryFlashAT45DB081EChipErase(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr);

/**
 * Page (memory page) erase.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        pageIndex               page index
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryFlashAT45DB081EPageErase(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr,
        const   uint32_t                                pageIndex);

/**
 * Block (memory block of 8 pages) erase.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        blockIndex              block index
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryFlashAT45DB081EBlockErase(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr,
        const   uint32_t                                blockIndex);

/**
 * Sector (memory block of 32 blocks/256 pages) erase.
 * NOTE: sector 0 includes both sector 0a and 0b (see datasheet).
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        sectorIndex             sector index
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryFlashAT45DB081ESectorErase(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr,
        const   uint32_t                                sectorIndex);

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
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryFlashAT45DB081EWriteBuffer(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryFlashAT45DB081EReadBuffer(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr,
        const   uint32_t                                startAddress,
                uint8_t*                        const   readBufferPtr,
        const   uint16_t                                toReadAmount,
                uint16_t*                       const   readedAmountPtr);

/**
 * Update (Read in RAM buffer-Modify-Erase-Write) buffer.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        startAddress            memory start address to update.
 * param[in]        writeBufferPtr          data buffer.
 * param[in]        writeBufferLen          data buffer length.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryFlashAT45DB081EUpdateBuffer(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr,
        const   uint32_t                                startAddress,
        const   uint8_t*                        const   writeBufferPtr,
        const   uint16_t                                writeBufferLen);

/**
 * Start chip as file system interface.
 * Direct access to memory not reserved for file system is still possible with bus device bus device pointer.
 * NOTE: chip is not INIT; specific INIT function MUST be called before.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in]        pageSize                memory page size.
 * param[in]        memoryForFSSize         size of memory reserved for file system [byte].
 * param[in]        fsGuardPtr              file system guard (NULL if none).
 * param[in]        fsInitType              file system init type.
 * param[in/out]    busDevicePtr            bus device pointer.
 * param[out]       fsHandlePtr             file system handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryFlashAT45DB081EStartAsFS(
        const   tommRoC_hw_devices_memory_flash_at45db081e_device_data_t*   const   deviceDataPtr,
        const   tommRoC_hw_devices_memory_flash_at45db081e_page_size_enum_t         pageSize,
        const   uint32_t                                                            memoryForFSSize,
        const   tommRoC_guard_t*                                            const   fsGuardPtr,
        const   tommRoC_fs_init_type_enum_t                                         fsInitType,
                tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
                tommRoC_fs_file_system_t*                                   const   fsHandlePtr);

#endif
