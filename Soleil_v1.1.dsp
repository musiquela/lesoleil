// =================================================================================
// Soleil - Harmony Generator v1.1
// MUSICAL INTERVAL SELECTORS (Dropdowns instead of sliders)
// THREE VOICES: Dry + Harmony 1 + Harmony 2
// MONO IN -> STEREO OUT
// =================================================================================

declare name "Soleil";
declare version "1.1";
declare author "Soleil Audio + Official Faust Example";
declare license "BSD";

import("stdfaust.lib");

// ==================== PITCH SHIFTER CORE ====================

// Shared OLA parameters for both harmony voices
window_size = hslider("[0] Settings/Window (samples)", 2048, 50, 10000, 1);
xfade_size = hslider("[0] Settings/Crossfade (samples)", 256, 1, 1000, 1);

// Harmony voice constructor
harmony_voice(shift_semitones) = ef.transpose(window_size, xfade_size, shift_semitones);

// ==================== MUSICAL INTERVAL SELECTORS ====================

// Harmony 1 - Musical interval selector (dropdown menu)
h1_shift = nentry("[1] Harmony 1/Interval [style:menu{'Unison':0;'m2':1;'M2':2;'m3':3;'M3':4;'P4':5;'tritone':6;'P5':7;'m6':8;'M6':9;'m7':10;'M7':11;'Octave':12;'m9':13;'M9':14;'m10':15;'M10':16;'P11':17;'P12':19;'2 Octaves':24;'-m2':-1;'-M2':-2;'-m3':-3;'-M3':-4;'-P4':-5;'-tritone':-6;'-P5':-7;'-m6':-8;'-M6':-9;'-m7':-10;'-M7':-11;'-Octave':-12;'-2 Octaves':-24}]", 12, -24, 24, 1);

h1_gain = hslider("[1] Harmony 1/Gain", 0.33, 0, 1, 0.01);

// Harmony 2 - Musical interval selector (dropdown menu)
h2_shift = nentry("[2] Harmony 2/Interval [style:menu{'Unison':0;'m2':1;'M2':2;'m3':3;'M3':4;'P4':5;'tritone':6;'P5':7;'m6':8;'M6':9;'m7':10;'M7':11;'Octave':12;'m9':13;'M9':14;'m10':15;'M10':16;'P11':17;'P12':19;'2 Octaves':24;'-m2':-1;'-M2':-2;'-m3':-3;'-M3':-4;'-P4':-5;'-tritone':-6;'-P5':-7;'-m6':-8;'-M6':-9;'-m7':-10;'-M7':-11;'-Octave':-12;'-2 Octaves':-24}]", 7, -24, 24, 1);

h2_gain = hslider("[2] Harmony 2/Gain", 0.33, 0, 1, 0.01);

// Dry signal gain
dry_gain = hslider("[3] Mix/Dry Gain", 0.34, 0, 1, 0.01);

// ==================== PROCESS ====================
// MONO IN -> Process -> Duplicate to STEREO OUT

process = _ <: dry_signal, h1_signal, h2_signal :> output <: _, _
with {
    // Dry signal (original input)
    dry_signal = _ * dry_gain;

    // Harmony 1 (pitched)
    h1_signal = harmony_voice(h1_shift) * h1_gain;

    // Harmony 2 (pitched)
    h2_signal = harmony_voice(h2_shift) * h2_gain;

    // Sum all three voices
    output = _;
};
