// =================================================================================
// PROJECT: SGT Harmony Generator (MINIMAL CORE TEST)
// AUTHOR: Gemini, The Project Engineer
// VERSION: 3.0 (START FROM SCRATCH: Minimal DSP, Max Stability)
// STATUS: Testing core pitch shift stability with a single voice and test tone.
// =================================================================================

// --- 1. Library Imports ---
import("stdfaust.lib");
import("math.lib");
import("effect.lib");
import("filter.lib"); // Critical for fi.dcblocker stability

// --- 2. Configuration Parameters ---
// Standard Faust library transposition uses fixed parameters.
olaWindow = 2048;
olaXFade  = 256;

// --- 3. Pitch Ratio Calculation Function ---
ratio(semitones) = pow(2.0 : float, semitones / 12.0 : float);

// --- 4. OLA Pitch Shifting Function (Now using ef.transpose) ---
// ef.transpose is a simpler, more common Faust pitch shifter.
pitch_shifter(semitone_value) =
    (ratio(semitone_value) : _, olaWindow, olaXFade) : ef.transpose;

// --- 5. Test Tone Generator and Shift Control ---
testMode = button("Test Tone Enable", 1); // Default ON for immediate test
testFreq = hslider("Test Tone Freq [unit:Hz]", 440, 100, 1000, 1);
test_osc(freq) = os.osc(freq) * 0.5;

// Simple shift control: -2 Octaves to +2 Octaves
final_shift_value = hslider("Pitch Shift (Semitones)", 12, -24, 24, 1);

// --- 6. The Process Definition (The True Stability Test) ---
process =
    // Declare all outputs in the tuple here (CRITICAL SCOPE FIX)
    _, _ : (freq_out, audio_out_L, audio_out_R)
    with {
        // --- Input Processing ---
        // 1. Generate or select input
        proc_input = select2(testMode, 0, test_osc(testFreq));

        // --- DSP Chain ---

        // 2. Pitch Shift
        voice2 = proc_input : pitch_shifter(final_shift_value);

        // 3. Dry/Wet Mix (50/50 mix for this test)
        output_mix = (proc_input * 0.5) + (voice2 * 0.5);

        // 4. DC Blocker (CRITICAL: Retained to solve initialization pop/silence)
        output_clean = output_mix : fi.dcblocker;

        // 5. Apply Gate (Ensures signal is only passed when Test Mode is active)
        smooth_gate = testMode : si.smoo;
        audio_out_gated = output_clean * smooth_gate;

        // --- Output Definitions (Must be inside the 'with' block) ---

        // Meter: Theoretical Output Frequency
        theoretical_freq = testFreq * ratio(final_shift_value);
        freq_out = theoretical_freq : hslider("Shifted Freq [unit:Hz] [style:bargraph]", 0, 0, 1000, 1);

        // Audio Outputs
        audio_out_L = audio_out_gated;
        audio_out_R = audio_out_gated;
    };
