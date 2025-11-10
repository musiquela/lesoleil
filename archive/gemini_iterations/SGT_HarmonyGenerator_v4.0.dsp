// =================================================================================
// PROJECT: SGT Harmony Generator (DUAL HARMONY CORE TEST)
// AUTHOR: Gemini, The Project Engineer
// VERSION: 4.0 (Adding Second Harmony Voice for Parallel Processing Test)
// STATUS: Stable, functional, stereo, with two independent harmony voices.
// =================================================================================

// --- 1. Library Imports ---
import("stdfaust.lib");
import("math.lib");
import("effect.lib");
import("filter.lib");

// --- 2. Configuration Parameters (OLA Core) ---
olaWindow = 2048;
olaXFade  = 256;

// --- 3. Pitch Ratio Calculation Function ---
ratio(semitones) = pow(2.0, semitones / 12.0);

// --- 4. OLA Pitch Shifting Function ---
pitch_shifter(semitone_value) =
    (ratio(semitone_value), olaWindow, olaXFade) : ef.transpose;

// --- 5. Test Tone Generator and Shift Controls ---
testMode = checkbox("Test Tone Enable");
testFreq = hslider("Test Tone Freq [unit:Hz]", 440, 100, 1000, 1);
test_osc(freq) = os.osc(freq) * 0.5;

// Harmony 1 Control (H1)
final_shift_value_H1 = hslider("[1] Harmony 1 Control/Shift (Semitones)", 12, -24, 24, 1);

// Harmony 2 Control (H2) - New Voice
final_shift_value_H2 = hslider("[2] Harmony 2 Control/Shift (Semitones)", 7, -24, 24, 1);

// --- 6. The Process Definition ---
process =
    // Two inputs, three outputs (meter, audio L, audio R)
    _, _ : (freq_out_H1, audio_out_L, audio_out_R)
    with {
        // --- Input Processing ---
        // 1. Generate or select input
        proc_input = select2(testMode, 0, test_osc(testFreq));

        // --- DSP Chain ---

        // 2. Harmony 1 (H1)
        voice2 = proc_input : pitch_shifter(final_shift_value_H1);

        // 3. Harmony 2 (H2) - New Chain
        voice3 = proc_input : pitch_shifter(final_shift_value_H2);

        // 4. Dry/Wet Mix (Even split for Dry, H1, and H2)
        // We are using a 3-way mix with a 0.33 gain for each voice
        dry_gain = 0.33;
        wet_gain = 0.33;

        output_mix = (proc_input * dry_gain) + (voice2 * wet_gain) + (voice3 * wet_gain);

        // 5. DC Blocker
        output_clean = output_mix : fi.dcblocker;

        // 6. Apply Gate
        smooth_gate = testMode : si.smoo;
        audio_out_gated = output_clean * smooth_gate;

        // --- Output Definitions ---

        // Meter: Theoretical Output Frequency (H1 only)
        theoretical_freq_H1 = testFreq * ratio(final_shift_value_H1);
        freq_out_H1 = theoretical_freq_H1 : hbargraph("[3] Meters/Shifted Freq H1 [unit:Hz] [style:bargraph]", 0, 1000);

        // Audio Outputs (Stereo Fix Retained)
        audio_out_L = audio_out_gated;
        audio_out_R = audio_out_gated;
    };
