
#ifndef TOMMROC_HW_DEVICES_AUDIO_VS1053_H_
#define TOMMROC_HW_DEVICES_AUDIO_VS1053_H_

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
#include "devices/audio/VS1053/plugin/tommRoCHwDevicesAudioVS1053Plugin.h"

#include "tommRoCHwBus.h"
#include "tommRoCHwBusDevice.h"
#include "tommRoCHwErr.h"
#include "tommRoCHwGPIO.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Typical Vorbis Ogg header maximum size.
#define TOMMROC_HW_DEVICES_AUDIO_VS1053_VORBIS_OGG_HEADER_MAX_SIZE  (1378 + 192)

// Device data.
#define TOMMROC_HW_DEVICES_AUDIO_VS1053_DEVICE_DATA_SIZE    (   TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                TOMMROC_UTIL_PTR_SIZE       +   \
                                                                TOMMROC_UTIL_U16_SIZE       +   \
                                                                TOMMROC_UTIL_U16_SIZE       +   \
                                                                TOMMROC_UTIL_U16_SIZE       +   \
                                                                TOMMROC_UTIL_BOOL_SIZE          )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Ogg header status.
TOMMRO_C_UTIL_PACKED_PRE typedef struct TOMMRO_C_UTIL_PACKED_POST {

    uint8_t*    oggHeaderBufferPtr;     // Ogg header pointer.
    uint16_t    oggHeaderBufferLength;  // Ogg header length [byte].
    bool        oggHeaderDetected;      // Ogg header detected.

} tommRoC_hw_devices_audio_vs1053_ogg_header_status_t;


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_AUDIO_VS1053_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_audio_vs1053_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesAudioVS1053InitSPI(
        const   tommRoC_hw_gpio_set_cb_t                                                    chipSelect,
        const   tommRoC_hw_gpio_set_cb_t                                                    chipDeSelect,
        const   tommRoC_hw_bus_t*                                                   const   busHandlerPtr,
        const   tommRoC_guard_t*                                                    const   guardPtr,
                tommRoC_hw_bus_device_specific_spi_slave_t*                         const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                                            const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesAudioVS1053AttachDeviceData(
        const   tommRoC_hw_devices_audio_vs1053_device_data_t*                      const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                            const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        resetLow                set RESET pin low function pointer.
 * param[in]        resetHigh               set RESET pin high function pointer.
 * param[in]        DREQStatus              get DREQ pin status function pointer.
 * param[in]        XDCSLow                 set XDCS pin low function pointer.
 * param[in]        XDCSHigh                set XDCS pin high function pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesAudioVS1053Start(
        const   tommRoC_hw_gpio_set_cb_t                                                    resetLow,
        const   tommRoC_hw_gpio_set_cb_t                                                    resetHigh,
        const   tommRoC_hw_gpio_get_cb_t                                                    DREQStatus,
        const   tommRoC_hw_gpio_set_cb_t                                                    XDCSLow,
        const   tommRoC_hw_gpio_set_cb_t                                                    XDCSHigh,
        const   tommRoC_hw_bus_device_t*                                            const   busDevicePtr);

/**
 * Load a plugin.
 * NOTE: plugins are little programs that run along with the firmware and add some new features to the IC.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        pluginWordsBufferPtr    plugin words data buffer pointer.
 * param[in]        pluginWordsAmount       plugin words amount.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesAudioVS1053LoadPlugin(
        const   tommRoC_hw_bus_device_t*                                            const   busDevicePtr,
        const   uint16_t*                                                           const   pluginWordsBufferPtr,
        const   uint16_t                                                                    pluginWordsAmount);

/**
 * Attach Ogg header buffer to bus device.
 * NOTE: Ogg Vorbis files always need to have a specific header which tells the exact decoding parameters.
 *       If split Ogg stream into separate files is needed, to store the header in a separate place is needed,
 *       so that it can be possible to apply it in front of any subsequent piece of the whole stream.
 *       Ogg header buffer is used to store header.
 *
 * param[in]        oggHeaderBufferPtr      Ogg header buffer pointer (HAVE to be a static variable).
 * param[in]        oggHeaderBufferSize     Ogg header buffer size.
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesAudioVS1053AttachOggHeaderBuffer(
                uint8_t*                                                            const   oggHeaderBufferPtr,
        const   uint16_t                                                                    oggHeaderBufferSize,
                tommRoC_hw_bus_device_t*                                            const   busDevicePtr);

/**
 * Analyze some Ogg data to detect/save Ogg header.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        oggWordsBufferPtr       Ogg words buffer pointer.
 * param[in]        oggWordsAmount          Ogg words buffer amount.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesAudioVS1053OggHeaderDetect(
        const   tommRoC_hw_bus_device_t*                                            const   busDevicePtr,
        const   uint16_t*                                                           const   oggWordsBufferPtr,
        const   uint16_t                                                                    oggWordsAmount);

/**
 * Get Ogg header status.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       oggHeaderStatusPtr      Ogg header status pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesAudioVS1053OggHeaderStatus(
        const   tommRoC_hw_bus_device_t*                                            const   busDevicePtr,
                tommRoC_hw_devices_audio_vs1053_ogg_header_status_t*                const   oggHeaderStatusPtr);

/**
 * Prepare record Ogg.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        pluginFunct             plugin get function pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesAudioVS1053PrepareRecordOgg(
        const   tommRoC_hw_bus_device_t*                                            const   busDevicePtr,
        const   tommRoC_hw_devices_audio_vs1053_plugin_funct_t                              pluginFunct);

/**
 * Start/stop record Ogg.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        oggVoxAvailableFunct    ogg plugin get Vox/Pause available function pointer.
 * param[in]        enableAutomaticVox      enable (if supported) automatic Vox/Pause.
 * param[in]        automaticVoxOffLimit    signal limit for Vox pause.
 * param[in]        automaticVoxOnLimit     signal limit for Vox record.
 * param[in]        automaticVoxOffTimeSec  pause delay time [sec].
 *
 * NOTE:
 * If the signal after the high-pass filter is below OffLimit for more than OffTime 48 kHz samples, then pause mode is activated.
 * Default value of OffTime = 0x17700 = 96000 equals two seconds.
 * Note that OffTime is always calculated in the 48 kHz domain regardless of the samplerate of the Ogg Vorbis Encoder Profile.
 *
 * If even a single sample goes above OnLimit, then pause mode is deactivated and normal recording continues.
 *
 * OffLimit and OnLimit are linear values. Thus, doubling the value lifts the limit by 6 dB.
 * Having two separate values for the limits allow for hysteresis between stopping and restarting recording.
 * OnLimit must always be greater than or equal to OffLimit.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesAudioVS1053StartOgg(
        const   tommRoC_hw_bus_device_t*                                            const   busDevicePtr,
        const   tommRoC_hw_devices_audio_vs1053_plugin_ogg_vox_available_funct_t            oggVoxAvailableFunct,
        const   bool                                                                        enableAutomaticVox,
        const   uint16_t                                                                    automaticVoxOffLimit,
        const   uint16_t                                                                    automaticVoxOnLimit,
        const   uint32_t                                                                    automaticVoxOffTimeSec);

tommRoC_hw_err_enum_t tommRoCHwDevicesAudioVS1053StopOgg(
        const   tommRoC_hw_bus_device_t*                                            const   busDevicePtr);

/**
 * Get amount of available words.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       wordsReadyAmountPtr     amount of available words pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesAudioVS1053WordsReady(
        const   tommRoC_hw_bus_device_t*                                            const   busDevicePtr,
                uint16_t*                                                           const   wordsReadyAmountPtr);

/**
 * Read words into buffer.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       readWordsBufferPtr      output words data buffer pointer.
 * param[in]        toReadWordsAmount       to read words amount.
 * param[out]       readedWordsAmountPtr    readed words count pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesAudioVS1053ReadWords(
        const   tommRoC_hw_bus_device_t*                                            const   busDevicePtr,
                uint16_t*                                                           const   readWordsBufferPtr,
        const   uint16_t                                                                    toReadWordsAmount,
                uint16_t*                                                           const   readedWordsAmountPtr);

#endif
