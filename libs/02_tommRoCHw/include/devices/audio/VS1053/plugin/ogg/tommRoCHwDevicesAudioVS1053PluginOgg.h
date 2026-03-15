
#ifndef TOMMROC_HW_DEVICES_AUDIO_VS1053_PLUGIN_OGG_H_
#define TOMMROC_HW_DEVICES_AUDIO_VS1053_PLUGIN_OGG_H_

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

/**
 * Download the latest VS1053 Ogg Vorbis Encoder Application package and its plugins.
 * The patches package is available at:
 * http://www.vlsi.fi/en/support/software/vs10xxapplications.html
 */

#include "devices/audio/VS1053/plugin/ogg/00_voice/tommRoCHwDevicesAudioVS1053PluginOggVoice.h"
#include "devices/audio/VS1053/plugin/ogg/01_widebandVoice/tommRoCHwDevicesAudioVS1053PluginOggWidebandVoice.h"
#include "devices/audio/VS1053/plugin/ogg/02_widebandStereoVoice/tommRoCHwDevicesAudioVS1053PluginOggWidebandStereoVoice.h"
#include "devices/audio/VS1053/plugin/ogg/03_hiFiVoice/tommRoCHwDevicesAudioVS1053PluginOggHiFiVoice.h"
#include "devices/audio/VS1053/plugin/ogg/04_stereoMusic/tommRoCHwDevicesAudioVS1053PluginOggStereoMusic.h"

#include <stdbool.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC devices audio VS1053 plugin Ogg get Vox/Pause available functions type definition.
typedef bool (*tommRoC_hw_devices_audio_vs1053_plugin_ogg_vox_available_funct_t)(void);

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
