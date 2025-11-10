// =================================================================================
// PROJECT: SGT Harmony Generator (C0-B0 Preset Control)
// AUTHOR: Gemini, The Project Engineer
// VERSION: 2.4 (FINAL STABILITY FIX: Load/Unload "Door Slam" Click & Default Preset)
// STATUS: Solves OLA startup denormalization with aggressive output smoothing.
// =================================================================================

// --- 1. Library Imports ---
import("stdfaust.lib");

// --- 2. Configuration Parameters (OLA Core) ---
olaWindow = hslider("[4] Debug Tools/OLA Window Size (samples)", 2048, 1024, 4096, 1) : int;
olaXFade  = hslider("[4] Debug Tools/OLA Crossfade Size (samples)", 256, 128, 512, 1) : int;

// --- 3. Pitch Ratio Calculation Function (Required for Meter Display ONLY) ---
ratio(semitones) = pow(2.0, semitones / 12.0);

// --- 4. OLA Pitch Shifting Function (Core DSP) ---
tdhs_pitch_shifter(semitone_value) =
    ef.transpose(olaWindow, olaXFade, semitone_value);

// --- 5. Test Tone Generator and Input Selection (STABILIZED) ---
test_osc(freq) = os.osc(freq) * 0.5;

testMode = checkbox("[4] Debug Tools/Test Tone Enable");
testFreq = hslider("[4] Debug Tools/Test Tone Freq [unit:Hz]", 440, 100, 1000, 1);

// Input is either silence (0.0) OR the test tone, based on testMode.
input_source_raw = select2(testMode, 0.0, test_osc(testFreq));

// --- 6. Theoretical Frequency Display (High-Integrity Output) ---
theoretical_freq_display(input_freq, semitones) =
    input_freq * ratio(semitones);

// --- 7. Shift Control Logic (C0-B0 Preset Selector AND Manual Override) ---
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

midi_shift_value = midi_shift_raw : si.smoo;

// FIX: Default manual value changed to 12 (Octave Up) for a clearer, higher test tone.
manual_shift_value = hslider("[1] Harmony Control/Manual Semitones", 12, -24, 24, 1);
control_selector = checkbox("[1] Harmony Control/Manual Mode (Override Preset)");

final_shift_value = select2(control_selector, midi_shift_value, manual_shift_value);

wetDry = hslider("[1] Harmony Control/Wet/Dry Mix[style:knob]", 0.5, 0.0, 1.0, 0.01);

// --- 8. The Process Definition (Single Harmony Core) ---

// Custom smoothing for the master output (0.005 seconds attack/release time)
// This is used to aggressively mitigate the TDHS engine's harsh initialization.
output_smoother = si.smooth(ba.tau2pole(0.005));

process = _, _ : !, ! : (input_freq_meter, output_freq_meter, audio_out)
with {
    // Semantic fix from V2.3: Add tiny DC offset for TDHS stability (passed to pitch shifter)
    proc_input_stable = input_source_raw + (0.0000001);

    // Harmony uses the stable, state-initialized input signal
    voice2 = proc_input_stable : tdhs_pitch_shifter(final_shift_value);

    // Dry/Wet Mixing
    output_mix = (input_source_raw * (1.0 - wetDry)) + (voice2 * wetDry);

    // Smoothed gate for Test Tone ON/OFF transition
    smooth_gate = testMode : si.smoo;

    // Final output is gated and then passed through the global smoother
    audio_out_mixed = (output_mix * smooth_gate);

    // The master output is now run through the aggressive smoother to kill load/unload clicks
    audio_out = (audio_out_mixed : output_smoother), (audio_out_mixed : output_smoother);

    // Meters
    input_freq_meter = testFreq : hbargraph("[4] Debug Tools/Input Freq (Hz)", 0, 1000);
    output_freq_meter = theoretical_freq_display(testFreq, final_shift_value) : hbargraph("[4] Debug Tools/Output Freq (Hz)", 0, 2000);
};
