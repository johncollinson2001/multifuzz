#define PLUG_MFR "John Collinson"
#define PLUG_NAME "Multifuzz"

#define PLUG_CLASS_NAME Multifuzz

#define BUNDLE_MFR "John Collinson"
#define BUNDLE_NAME "Multifuzz"

#define PLUG_ENTRY Multifuzz_Entry
#define PLUG_VIEW_ENTRY Multifuzz_ViewEntry

#define PLUG_ENTRY_STR "Multifuzz_Entry"
#define PLUG_VIEW_ENTRY_STR "Multifuzz_ViewEntry"

#define VIEW_CLASS Multifuzz_View
#define VIEW_CLASS_STR "Multifuzz_View"

// Format        0xMAJR.MN.BG - in HEX! so version 10.1.5 would be 0x000A0105
#define PLUG_VER 0x00010000
#define VST3_VER_STR "1.0.0"

// http://service.steinberg.de/databases/plugin.nsf/plugIn?openForm
// 4 chars, single quotes. At least one capital letter
#define PLUG_UNIQUE_ID 'Mfzz'
// make sure this is not the same as BUNDLE_MFR
#define PLUG_MFR_ID 'JCol'

// ProTools stuff

#if (defined(AAX_API) || defined(RTAS_API)) && !defined(_PIDS_)
#define _PIDS_
const int PLUG_TYPE_IDS[2] = { 'EFN1', 'EFN2' };
const int PLUG_TYPE_IDS_AS[2] = { 'EFA1', 'EFA2' }; // AudioSuite
#endif

#define PLUG_MFR_PT "JohnCollinson\nJohnCollinson\nJCol"
#define PLUG_NAME_PT "Multifuzz\nIPEF"
#define PLUG_TYPE_PT "Effect"
#define PLUG_DOES_AUDIOSUITE 1

/* PLUG_TYPE_PT can be "None", "EQ", "Dynamics", "PitchShift", "Reverb", "Delay", "Modulation",
"Harmonic" "NoiseReduction" "Dither" "SoundField" "Effect"
instrument determined by PLUG _IS _INST
*/

#define PLUG_CHANNEL_IO "1-1 2-2"

#define PLUG_LATENCY 0
#define PLUG_IS_INST 0

// if this is 0 RTAS can't get tempo info
#define PLUG_DOES_MIDI 0

#define PLUG_DOES_STATE_CHUNKS 0

// Unique IDs for each image resource.
#define BACKGROUND_METAL_ID 101
#define BACKGROUND_YELLOW_ID 102
#define LED_PANEL_ID 103
#define ON_OFF_BUTTON_ID 104
#define POWER_SWITCH_ID 105
#define KNOB_MINI_ID 106
#define KNOB_SMALL_ID 107
#define KNOB_MEDIUM_ID 108
#define KNOB_LARGE_ID 109
#define VU_METER_BLACK_ID 110
#define VU_METER_BLUE_ID 111

// Image resource locations for this plug.
#define BACKGROUND_METAL_FN "resources/img/bg-metal-807x400.png"
#define BACKGROUND_YELLOW_FN "resources/img/bg-yellow-807x400.png"
#define LED_PANEL_FN "resources/img/led-panel-130x26.png"
#define ON_OFF_BUTTON_FN "resources/img/on-off-btn-52x52-2f.png"
#define POWER_SWITCH_FN "resources/img/power-switch-72x72-2f.png"
#define KNOB_MINI_FN "resources/img/silver-knob-28x28-101f.png"
#define KNOB_SMALL_FN "resources/img/silver-knob-36x36-101f.png"
#define KNOB_MEDIUM_FN "resources/img/silver-knob-52x52-101f.png"
#define KNOB_LARGE_FN "resources/img/silver-knob-65x65-101f.png"
#define VU_METER_BLACK_FN "resources/img/vu-meter-black-113x113-50f.png"
#define VU_METER_BLUE_FN "resources/img/vu-meter-blue-144x100-50f.png"

// GUI default dimensions
#define GUI_WIDTH 807
#define GUI_HEIGHT 400

// on MSVC, you must define SA_API in the resource editor preprocessor macros as well as the c++ ones
#if defined(SA_API) && !defined(OS_IOS)
#include "../app_wrapper/app_resource.h"
#endif

// vst3 stuff
#define MFR_URL "www.olilarkin.co.uk"
#define MFR_EMAIL "spam@me.com"
#define EFFECT_TYPE_VST3 "Fx"

/* "Fx|Analyzer"", "Fx|Delay", "Fx|Distortion", "Fx|Dynamics", "Fx|EQ", "Fx|Filter",
"Fx", "Fx|Instrument", "Fx|InstrumentExternal", "Fx|Spatial", "Fx|Generator",
"Fx|Mastering", "Fx|Modulation", "Fx|PitchShift", "Fx|Restoration", "Fx|Reverb",
"Fx|Surround", "Fx|Tools", "Instrument", "Instrument|Drum", "Instrument|Sampler",
"Instrument|Synth", "Instrument|Synth|Sampler", "Instrument|External", "Spatial",
"Spatial|Fx", "OnlyRT", "OnlyOfflineProcess", "Mono", "Stereo",
"Surround"
*/
