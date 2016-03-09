#define PLUG_MFR "John Collinson"
#define PLUG_NAME "SuperSlicer"

#define PLUG_CLASS_NAME SuperSlicer

#define BUNDLE_MFR "John Collinson"
#define BUNDLE_NAME "SuperSlicer"

#define PLUG_ENTRY SuperSlicer_Entry
#define PLUG_VIEW_ENTRY SuperSlicer_ViewEntry

#define PLUG_ENTRY_STR "SuperSlicer_Entry"
#define PLUG_VIEW_ENTRY_STR "SuperSlicer_ViewEntry"

#define VIEW_CLASS SuperSlicer_View
#define VIEW_CLASS_STR "SuperSlicer_View"

// Format        0xMAJR.MN.BG - in HEX! so version 10.1.5 would be 0x000A0105
#define PLUG_VER 0x00010000
#define VST3_VER_STR "1.0.0"

// http://service.steinberg.de/databases/plugin.nsf/plugIn?openForm
// 4 chars, single quotes. At least one capital letter
#define PLUG_UNIQUE_ID 'SSli'
// make sure this is not the same as BUNDLE_MFR
#define PLUG_MFR_ID 'JCol'

// ProTools stuff

#if (defined(AAX_API) || defined(RTAS_API)) && !defined(_PIDS_)
#define _PIDS_
const int PLUG_TYPE_IDS[2] = { 'EFN1', 'EFN2' };
const int PLUG_TYPE_IDS_AS[2] = { 'EFA1', 'EFA2' }; // AudioSuite
#endif

#define PLUG_MFR_PT "JohnCollinson\nJohnCollinson\nJCol"
#define PLUG_NAME_PT "SuperSlicer\nIPEF"
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
#define BACKGROUND_ID 101
#define POWER_SWITCH_ID 102

// Image resource locations for this plug.
#define BACKGROUND_FN "resources/img/bg-metal-900x468.png"
#define POWER_SWITCH_FN "resources/img/power-switch-72x72-2f.png"

// GUI default dimensions
#define GUI_WIDTH 900
#define GUI_HEIGHT 468

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
