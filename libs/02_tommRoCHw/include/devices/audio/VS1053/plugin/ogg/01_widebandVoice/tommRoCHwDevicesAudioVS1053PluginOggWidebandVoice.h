
#ifndef TOMMROC_HW_DEVICES_AUDIO_VS1053_PLUGIN_OGG_WIDEBAND_VOICE_H_
#define TOMMROC_HW_DEVICES_AUDIO_VS1053_PLUGIN_OGG_WIDEBAND_VOICE_H_

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
#include <stdbool.h>
#include <stdint.h>

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
 * Wideband Voice Ogg profile.
 *
 * Sample rate [Hz]:        16000
 * Channels:                1
 * Bit rate [kbit/s]:       28
 * WAV [kbit/s]:            256
 * Time [h/GB]:             79
 * Available Vox/Pause:     Y
 */

const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandVoiceQ00(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandVoiceQ01(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandVoiceQ02(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandVoiceQ03(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandVoiceQ04(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandVoiceQ05(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandVoiceQ06(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandVoiceQ07(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandVoiceQ08(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandVoiceQ09(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandVoiceQ10(uint16_t* const pluginWordsAmountPtr);

bool tommRoCHwDevicesAudioVS1053PluginOggWidebandVoiceVoxAvailable(void);

#endif
