
#ifndef TOMMROC_HW_DEVICES_AUDIO_VS1053_PLUGIN_OGG_VOICE_H_
#define TOMMROC_HW_DEVICES_AUDIO_VS1053_PLUGIN_OGG_VOICE_H_

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
 * Voice Ogg profile.
 *
 * Sample rate [Hz]:        8000
 * Channels:                1
 * Bit rate [kbit/s]:       15
 * WAV [kbit/s]:            128
 * Time [h/GB]:             149
 * Available Vox/Pause:     Y
 */

const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggVoiceQ00(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggVoiceQ01(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggVoiceQ02(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggVoiceQ03(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggVoiceQ04(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggVoiceQ05(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggVoiceQ06(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggVoiceQ07(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggVoiceQ08(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggVoiceQ09(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggVoiceQ10(uint16_t* const pluginWordsAmountPtr);

bool tommRoCHwDevicesAudioVS1053PluginOggVoiceVoxAvailable(void);

#endif
