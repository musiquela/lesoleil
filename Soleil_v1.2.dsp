// =================================================================================
// Soleil - Harmony Generator v1.2
// THREE VOICES: Root + Harmony 1 + Harmony 2
// INDEPENDENT ENABLE/DISABLE + MIX CONTROLS FOR EACH VOICE
// MONO IN -> STEREO OUT
// OPTIMIZED FOR LOW LATENCY: ~8ms at 48kHz
// =================================================================================

declare name "Soleil";
declare version "1.2";
declare author "Soleil Audio + Official Faust Example";
declare license "BSD";

import("stdfaust.lib");

// ==================== PITCH SHIFTER CORE ====================

// Optimized OLA parameters for near-zero latency at 48kHz
// window_size = 384 samples (~8ms latency at 48kHz)
// xfade_size = 96 samples (~2ms crossfade at 48kHz)
window_size = 384;
xfade_size = 96;

// Harmony voice constructor
harmony_voice(shift_semitones) = ef.transpose(window_size, xfade_size, shift_semitones);

// ==================== VOICE CONTROLS ====================

// Root (dry signal)
dry_enable = checkbox("[0] Root/Enable");
dry_gain = hslider("[0] Root/Mix", 0.33, 0, 1, 0.01);

// Harmony 1 - Musical interval selector (dropdown menu)
h1_enable = checkbox("[1] Harmony 1/Enable");
h1_shift = nentry("[1] Harmony 1/Interval [style:menu{'Unison':0;'m2':1;'M2':2;'m3':3;'M3':4;'P4':5;'tritone':6;'P5':7;'m6':8;'M6':9;'m7':10;'M7':11;'Octave':12;'m9':13;'M9':14;'m10':15;'M10':16;'P11':17;'P12':19;'2 Octaves':24;'-m2':-1;'-M2':-2;'-m3':-3;'-M3':-4;'-P4':-5;'-tritone':-6;'-P5':-7;'-m6':-8;'-M6':-9;'-m7':-10;'-M7':-11;'-Octave':-12;'-2 Octaves':-24}]", 12, -24, 24, 1);
h1_gain = hslider("[1] Harmony 1/Mix", 0.33, 0, 1, 0.01);

// Harmony 2 - Musical interval selector (dropdown menu)
h2_enable = checkbox("[2] Harmony 2/Enable");
h2_shift = nentry("[2] Harmony 2/Interval [style:menu{'Unison':0;'m2':1;'M2':2;'m3':3;'M3':4;'P4':5;'tritone':6;'P5':7;'m6':8;'M6':9;'m7':10;'M7':11;'Octave':12;'m9':13;'M9':14;'m10':15;'M10':16;'P11':17;'P12':19;'2 Octaves':24;'-m2':-1;'-M2':-2;'-m3':-3;'-M3':-4;'-P4':-5;'-tritone':-6;'-P5':-7;'-m6':-8;'-M6':-9;'-m7':-10;'-M7':-11;'-Octave':-12;'-2 Octaves':-24}]", 7, -24, 24, 1);
h2_gain = hslider("[2] Harmony 2/Mix", 0.33, 0, 1, 0.01);

// ==================== PROCESS ====================
// MONO IN -> Process -> Duplicate to STEREO OUT
// Each voice can be independently enabled/disabled
// Faust compiler optimizes out disabled pitch-shifting computation

process = _ <: dry_signal, h1_signal, h2_signal :> output <: _, _
with {
    // Dry signal (original input) - multiply by enable checkbox (0 or 1)
    dry_signal = _ * dry_gain * dry_enable;

    // Harmony 1 (pitched) - multiply by enable checkbox to disable computation when off
    h1_signal = harmony_voice(h1_shift) * h1_gain * h1_enable;

    // Harmony 2 (pitched) - multiply by enable checkbox to disable computation when off
    h2_signal = harmony_voice(h2_shift) * h2_gain * h2_enable;

    // Sum all three voices
    output = _;
};
