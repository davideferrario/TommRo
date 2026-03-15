
#ifndef TOMMROC_HW_DEVICES_AUDIO_VS1053_PLUGIN_OGG_WIDEBAND_STEREO_VOICE_H_
#define TOMMROC_HW_DEVICES_AUDIO_VS1053_PLUGIN_OGG_WIDEBAND_STEREO_VOICE_H_

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
 * Wideband Stereo Voice Ogg profile.
 *
 * Sample rate [Hz]:        16000
 * Channels:                2
 * Bit rate [kbit/s]:       49
 * WAV [kbit/s]:            512
 * Time [h/GB]:             45
 * Available Vox/Pause:     N
 */

const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandStereoVoiceQ00(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandStereoVoiceQ01(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandStereoVoiceQ02(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandStereoVoiceQ03(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandStereoVoiceQ04(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandStereoVoiceQ05(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandStereoVoiceQ06(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandStereoVoiceQ07(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandStereoVoiceQ08(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandStereoVoiceQ09(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggWidebandStereoVoiceQ10(uint16_t* const pluginWordsAmountPtr);

bool tommRoCHwDevicesAudioVS1053PluginOggWidebandStereoVoiceVoxAvailable(void);

#endif
