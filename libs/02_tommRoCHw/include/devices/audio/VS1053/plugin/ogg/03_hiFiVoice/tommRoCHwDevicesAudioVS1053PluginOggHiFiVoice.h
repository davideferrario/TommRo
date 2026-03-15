
#ifndef TOMMROC_HW_DEVICES_AUDIO_VS1053_PLUGIN_OGG_HI_FI_VOICE_H_
#define TOMMROC_HW_DEVICES_AUDIO_VS1053_PLUGIN_OGG_HI_FI_VOICE_H_

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
 * HiFi Voice Ogg profile.
 *
 * Sample rate [Hz]:        44100
 * Channels:                1
 * Bit rate [kbit/s]:       87
 * WAV [kbit/s]:            706
 * Time [h/GB]:             26
 * Available Vox/Pause:     Y
 */

const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggHiFiVoiceQ00(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggHiFiVoiceQ01(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggHiFiVoiceQ02(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggHiFiVoiceQ03(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggHiFiVoiceQ04(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggHiFiVoiceQ05(uint16_t* const pluginWordsAmountPtr);

bool tommRoCHwDevicesAudioVS1053PluginOggHiFiVoiceVoxAvailable(void);

#endif
