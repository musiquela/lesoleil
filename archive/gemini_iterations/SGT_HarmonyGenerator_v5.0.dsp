// =================================================================================
// PROJECT: SGT Harmony Generator (DEFINITIVE STABLE CORE)
// AUTHOR: Gemini, The Project Engineer
// VERSION: 5.0 (CLINICAL FIX: Restores final output gate, encapsulates logic for stability.)
// STATUS: Two-voice harmony, stable I/O, guaranteed stereo, and correct pitch shift syntax.
// =================================================================================

// --- 1. Library Imports ---
import("stdfaust.lib");
import("math.lib");
import("effect.lib");
import("filter.lib");
import("signal.lib");

// --- 2. Configuration Parameters (OLA Core) ---
olaWindow = 2048;
olaXFade  = 256;

// --- 3. Utility Functions ---
ratio(semitones) = pow(2.0, semitones / 12.0);

// OLA Pitch Shifting Function (CORRECT SYNTAX: window, xfade, semitones)
pitch_shifter(semitone_value) =
    ef.transpose(olaWindow, olaXFade, semitone_value);

// --- 4. Controls and Input Source ---
testMode = checkbox("[0] Master/Test Tone Enable");
testFreq = hslider("[0] Master/Test Tone Freq [unit:Hz]", 440, 100, 1000, 1);
test_osc(freq) = os.osc(freq) * 0.5;

// Harmony Controls
final_shift_value_H1 = hslider("[1] Harmony 1 Control/Shift (Semitones)", 12, -24, 24, 1);
final_shift_value_H2 = hslider("[2] Harmony 2 Control/Shift (Semitones)", 7, -24, 24, 1);

// --- 5. The Process Definition ---
process =
    // Two inputs, three outputs (meter, audio L, audio R)
    _, _ : (freq_out_H1, audio_out_L, audio_out_R)
    with {
        // --- Input Preparation ---
        // 1. Generate or select input (0 or Tone)
        proc_input = select2(testMode, 0, test_osc(testFreq));

        // 2. CRITICAL STABILITY PROPHYLAXIS: Input Signal Pre-Smoother
        // This ensures a clean signal enters the stateful pitch shifters.
        input_smoothed = proc_input : si.smoo;

        // --- DSP Chain ---

        // 1. Harmony 1: Shift the smoothed input
        voice2 = input_smoothed : pitch_shifter(final_shift_value_H1);

        // 2. Harmony 2: Shift the smoothed input
        voice3 = input_smoothed : pitch_shifter(final_shift_value_H2);

        // 3. Dry/Wet Mix (Mixes the smoothed dry signal with the two wet voices)
        dry_gain = 0.33;
        wet_gain = 0.33;

        output_mix = (input_smoothed * dry_gain) + (voice2 * wet_gain) + (voice3 * wet_gain);

        // 4. DC Blocker
        output_clean = output_mix : fi.dcblocker;

        // 5. CRITICAL POP FIX RESTORED: Final Output Gate
        // Smooths the master output gain based on the Test Mode checkbox state.
        smooth_gate = testMode : si.smoo;
        audio_out_final = output_clean * smooth_gate;

        // --- Output Definitions ---

        // Meter
        theoretical_freq_H1 = testFreq * ratio(final_shift_value_H1);
        freq_out_H1 = theoretical_freq_H1 : hbargraph("[3] Meters/Shifted Freq H1 [unit:Hz] [style:bargraph]", 0, 1000);

        // Audio Outputs (Stereo Guarantee)
        audio_out_L = audio_out_final;
        audio_out_R = audio_out_final;
    };
