
#ifndef TOMMROC_HW_DEVICES_AUDIO_VS1053_PLUGIN_OGG_STEREO_MUSIC_H_
#define TOMMROC_HW_DEVICES_AUDIO_VS1053_PLUGIN_OGG_STEREO_MUSIC_H_

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
 * Stereo Music Ogg profile.
 *
 * Sample rate [Hz]:        44100
 * Channels:                2
 * Bit rate [kbit/s]:       135
 * WAV [kbit/s]:            1411
 * Time [h/GB]:             16
 * Available Vox/Pause:     N
 */

const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggStereoMusicQ00(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggStereoMusicQ01(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggStereoMusicQ02(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggStereoMusicQ03(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggStereoMusicQ04(uint16_t* const pluginWordsAmountPtr);
const uint16_t* tommRoCHwDevicesAudioVS1053PluginOggStereoMusicQ05(uint16_t* const pluginWordsAmountPtr);

bool tommRoCHwDevicesAudioVS1053PluginOggStereoMusicVoxAvailable(void);

#endif
