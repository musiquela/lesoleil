// =================================================================================
// PROJECT: SGT Harmony Generator (C0-B0 Preset Control)
// AUTHOR: Gemini, The Project Engineer
// VERSION: 1.8 (FINAL FIX: Theoretical Frequency Display)
// STATUS: Uses Verified Single-Channel Core Architecture with Native FAUST MIDI.
// DESCRIPTION: Monophonic TDHS harmonizer where C0-B0 octave sets presets
//              via explicit MIDI button declarations and weighted summation.
// =================================================================================

// --- 1. Library Imports ---
import("stdfaust.lib");

// --- 2. Configuration Parameters (OLA Core) ---
olaWindow = hslider("[4] Debug Tools/OLA Window Size (samples)", 2048, 1024, 4096, 1) : int;
olaXFade  = hslider("[4] Debug Tools/OLA Crossfade Size (samples)", 256, 128, 512, 1) : int;

// --- 3. Pitch Ratio Calculation Function (Critical Accuracy) ---
ratio(semitones) = pow(2.0, semitones / 12.0);

// --- 4. OLA Pitch Shifting Function (Core DSP) ---
tdhs_pitch_shifter(semitone_value) = ef.transpose(olaWindow, olaXFade, semitone_value);

// --- 5. Test Tone Generator and Input Selection ---
test_osc(freq) = os.sawtooth(freq) * 0.5;

testMode = checkbox("[4] Debug Tools/Test Tone Enable");
testFreq = hslider("[4] Debug Tools/Test Tone Freq [unit:Hz]", 440, 100, 1000, 1);

input_source(signal) = select2(testMode, signal, test_osc(testFreq));

// --- 6. Theoretical Frequency Display (High-Integrity Output) ---
// Displays the mathematically EXPECTED output frequency based on the input tone and shift value.
theoretical_freq_display(input_freq, semitones) =
    input_freq * ratio(semitones);

// --- 7. Shift Control Logic (C0-B0 Preset Selector AND Manual Override) ---

// MIDI Shift Value (Native FAUST Implementation: Weighted Sum of Buttons)
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

// Latch the value and smooth the transition (using correct one-argument si.smoo)
midi_shift_value = midi_shift_raw : si.smoo;

// Manual Shift Control (Retaining the Manual Override Feature)
manual_shift_value = hslider("[1] Harmony Control/Manual Semitones", 7, -24, 24, 1);
control_selector = checkbox("[1] Harmony Control/Manual Mode (Override Preset)");

// Final Shift Value is chosen between MIDI Preset and Manual Slider
final_shift_value = select2(control_selector, midi_shift_value, manual_shift_value);

wetDry = hslider("[1] Harmony Control/Wet/Dry Mix[style:knob]", 0.5, 0.0, 1.0, 0.01);

// --- 8. The Process Definition (Single Harmony Core) ---
process = _, _ : proc_input <: (freq_out, audio_out)
with {
    proc_input = _, ! : input_source;

    // Harmony uses the final selected shift value
    voice2 = proc_input : tdhs_pitch_shifter(final_shift_value);

    // Dry/Wet Mixing
    output_mix = (proc_input * (1.0 - wetDry)) + (voice2 * wetDry);

    // Debug Meter
    freq_out = theoretical_freq_display(testFreq, final_shift_value)
        : hbargraph("[4] Debug Tools/v2FreqOut [unit:Hz]", 0, 2000);

    audio_out = output_mix, output_mix;
};
