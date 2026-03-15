
#ifndef TOMMROC_HW_DEVICES_MEMORY_EEPROM_24xx128_H_
#define TOMMROC_HW_DEVICES_MEMORY_EEPROM_24xx128_H_

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
#include "tommRoCHwMemory.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Compatible device I2C addresses.
#define TOMMROC_HW_DEVICES_MEMORY_EEPROM_24xx128_I2C_7_BIT_ADDRESS_A2A1A0_PIN_GNDGNDGND (0b1010000)
#define TOMMROC_HW_DEVICES_MEMORY_EEPROM_24xx128_I2C_7_BIT_ADDRESS_A2A1A0_PIN_GNDGNDVDD (0b1010001)
#define TOMMROC_HW_DEVICES_MEMORY_EEPROM_24xx128_I2C_7_BIT_ADDRESS_A2A1A0_PIN_GNDVDDGND (0b1010010)
#define TOMMROC_HW_DEVICES_MEMORY_EEPROM_24xx128_I2C_7_BIT_ADDRESS_A2A1A0_PIN_GNDVDDVDD (0b1010011)
#define TOMMROC_HW_DEVICES_MEMORY_EEPROM_24xx128_I2C_7_BIT_ADDRESS_A2A1A0_PIN_VDDGNDGND (0b1010100)
#define TOMMROC_HW_DEVICES_MEMORY_EEPROM_24xx128_I2C_7_BIT_ADDRESS_A2A1A0_PIN_VDDGNDVDD (0b1010101)
#define TOMMROC_HW_DEVICES_MEMORY_EEPROM_24xx128_I2C_7_BIT_ADDRESS_A2A1A0_PIN_VDDVDDGND (0b1010110)
#define TOMMROC_HW_DEVICES_MEMORY_EEPROM_24xx128_I2C_7_BIT_ADDRESS_A2A1A0_PIN_VDDVDDVDD (0b1010111)

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
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryEEPROM24xx128InitI2C(
        const   uint8_t                                             i2c7BitSlaveAddress,
        const   tommRoC_hw_bus_t*                           const   busHandlerPtr,
        const   tommRoC_guard_t*                            const   guardPtr,
                tommRoC_hw_bus_device_specific_i2c_slave_t* const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                    const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryEEPROM24xx128Start(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr);

/**
 * Get property.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryEEPROM24xx128GetProp(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr,
        const   tommRoC_hw_memory_prop_enum_t           property,
                void*                           const   propValuePtr);

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
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryEEPROM24xx128WriteBuffer(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryEEPROM24xx128ReadBuffer(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr,
        const   uint32_t                                startAddress,
                uint8_t*                        const   readBufferPtr,
        const   uint16_t                                toReadAmount,
                uint16_t*                       const   readedAmountPtr);

/**
 * Start chip as file system interface.
 * Direct access to memory not reserved for file system is still possible with bus device bus device pointer.
 * NOTE: chip is not INIT; specific INIT function MUST be called before.
 *
 * param[in]        memoryForFSSize         size of memory reserved for file system [byte].
 * param[in]        fsGuardPtr              file system guard (NULL if none).
 * param[in]        fsInitType              file system init type.
 * param[in/out]    busDevicePtr            bus device pointer.
 * param[out]       fsHandlePtr             file system handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMemoryEEPROM24xx128StartAsFS(
        const   uint32_t                                memoryForFSSize,
        const   tommRoC_guard_t*                const   fsGuardPtr,
        const   tommRoC_fs_init_type_enum_t             fsInitType,
                tommRoC_hw_bus_device_t*        const   busDevicePtr,
                tommRoC_fs_file_system_t*       const   fsHandlePtr);

#endif
