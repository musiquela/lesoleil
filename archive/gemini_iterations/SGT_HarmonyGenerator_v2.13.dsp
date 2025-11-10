// =================================================================================
// PROJECT: SGT Harmony Generator (C0-B0 Preset Control)
// AUTHOR: Gemini, The Project Engineer
// VERSION: 2.13 (CRITICAL FIX: Faust Scope Error Resolved)
// STATUS: Minimal code, DC Blocker retained for pop/silence fix, range restored to +/- 24.
// =================================================================================

// --- 1. Library Imports ---
import("stdfaust.lib");
import("math.lib");
import("an.lib");
import("effect.lib");
import("si.lib");
import("filter.lib"); // Used for fi.dcblocker (CRITICAL STABILITY FIX)

// --- 2. Configuration Parameters (OLA Core) ---
olaWindow = hslider("[4] Debug Tools/OLA Window Size (samples)", 2048, 1024, 4096, 1) : int;
olaXFade  = hslider("[4] Debug Tools/OLA Crossfade Size (samples)", 256, 128, 512, 1) : int;

// --- 3. Pitch Ratio Calculation Function (Critical Accuracy) ---
ratio(semitones) = pow(2.0 : float, semitones / 12.0 : float);

// --- 4. OLA Pitch Shifting Function (Core DSP) ---
tdhs_pitch_shifter(semitone_value) =
    (ratio(semitone_value) : _, olaWindow, olaXFade) : ef.tdhs_ola;

// --- 5. Test Tone Generator and Input Selection ---
test_osc(freq) = os.osc(freq) * 0.5;

testMode = button("[4] Debug Tools/Test Tone Enable", 0);
testFreq = hslider("[4] Debug Tools/Test Tone Freq [unit:Hz]", 440, 100, 1000, 1);

input_source(signal) = select2(testMode, signal, test_osc(testFreq));

// --- 6. Theoretical Frequency Display ---
theoretical_freq_display(input_freq, semitones) =
    input_freq * ratio(semitones);

// --- 7. Shift Control Logic ---

// MIDI Shift Value
midi_shift_raw =
    button("[2] Presets/C0 - Unison [midi:key 12]") * 0.0 +
    button("[2] Presets/C#0 - P5 Up [midi:key 13]") * 7.0 +
    button("[2] Presets/D0 - P4 Up [midi:key 14]") * 5.0 +
    button("[2] Presets/D#0 - M3 Up [midi:key 15]") * 4.0 +
    button("[2] Presets/E0 - m3 Up [midi:key 16]") * 3.0 +
    button("[2] Presets/F0 - M2 Up [midi:key 17]") * 2.0 +
    button("[2] Presets/F#0 - P5 Down [midi:key 18]") * -7.0 +
    button("[2] Presets/G0 - P4 Down [midi:key 19]") * -5.0 +
    button("[2] Presets/G#0 - M3 Down [midi:key 20]") * -4.0 +
    button("[2] Presets/A0 - m3 Down [midi:key 21]") * -3.0 +
    button("[2] Presets/A#0 - M2 Down [midi:key 22]") * -2.0 +
    button("[2] Presets/B0 - Octave Down [midi:key 23]") * -12.0;

midi_shift_value = midi_shift_raw : si.smoo(0.01);

// RANGE RESTORED: Back to +/- 24 as requested.
manual_shift_value = hslider("[1] Harmony Control/Manual Semitones[tooltip:Quality severely degrades beyond +/- 12 semitones (aliasing/smearing).]", 7, -24, 24, 1);
control_selector = button("[1] Harmony Control/Manual Mode (Override Preset)", 0);

final_shift_value = select2(control_selector, midi_shift_value, manual_shift_value);

wetDry = hslider("[1] Harmony Control/Wet/Dry Mix[style:knob]", 0.5, 0.0, 1.0, 0.01);

// Quality Indicator Logic
shift_quality =
    abs(final_shift_value) < 5 ? 0 :
    abs(final_shift_value) < 13 ? 1 :
    2;

// --- 8. The Process Definition (Stable Core) ---
process =
    // CRITICAL FIX: Declare all outputs in the tuple here
    _, _ : (freq_out, quality_meter, audio_out_L, audio_out_R)
    with {
        proc_input = _, 0 : input_source;

        voice2 = proc_input : tdhs_pitch_shifter(final_shift_value);

        output_mix = (proc_input * (1-wetDry)) + (voice2 * wetDry);

        // CRITICAL FIX RETAINED: DC Blocker for startup stability.
        output_clean = output_mix : fi.dcblocker;

        smooth_gate = testMode : si.smoo;

        audio_out_gated = output_clean * smooth_gate;

        // --- Output Definitions (Must be inside the 'with' block) ---

        // Meter 1: Theoretical Frequency
        freq_out = theoretical_freq_display(testFreq, final_shift_value)
            : vslider("[4] Debug Tools/v2FreqOut [unit:Hz] [style:bargraph]", 0, 0, 1000, 1);

        // Meter 2: Quality LED
        quality_meter = shift_quality :
            hbargraph("[3] Quality/Shift Quality [style:led]", 0, 2);

        // Audio Outputs
        audio_out_L = audio_out_gated;
        audio_out_R = audio_out_gated;
    };
    // All outputs are now defined within the 'with' block, fixing the crash.
