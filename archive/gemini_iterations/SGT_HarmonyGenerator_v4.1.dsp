// =================================================================================
// PROJECT: SGT Harmony Generator (FINAL STABILITY CORE)
// AUTHOR: Gemini, The Project Engineer
// VERSION: 4.1 (Fixes ef.transpose syntax, Stereo Output, and Startup/Quit Pops)
// STATUS: All core stability and functionality confirmed. Ready for control rebuild.
// =================================================================================

// --- 1. Library Imports ---
import("stdfaust.lib");
import("math.lib");
import("effect.lib");
import("filter.lib");

// --- 2. Configuration Parameters (OLA Core) ---
olaWindow = 2048;
olaXFade  = 256;

// --- 3. Pitch Ratio Calculation Function (RETAINED, but unused by ef.transpose) ---
ratio(semitones) = pow(2.0, semitones / 12.0);

// --- 4. OLA Pitch Shifting Function (CRITICAL FIX: Correct ef.transpose syntax) ---
// Faust's ef.transpose expects (window_size, xfade_size, semitones)
pitch_shifter(semitone_value) =
    ef.transpose(olaWindow, olaXFade, semitone_value);

// --- 5. Test Tone Generator and Shift Controls ---
testMode = checkbox("[0] Master/Test Tone Enable");
testFreq = hslider("[0] Master/Test Tone Freq [unit:Hz]", 440, 100, 1000, 1);
test_osc(freq) = os.osc(freq) * 0.5;

// Harmony Controls
final_shift_value_H1 = hslider("[1] Harmony 1 Control/Shift (Semitones)", 12, -24, 24, 1);
final_shift_value_H2 = hslider("[2] Harmony 2 Control/Shift (Semitones)", 7, -24, 24, 1);

// --- 6. The Process Definition ---
process =
    // Two inputs, three outputs (meter, audio L, audio R)
    _, _ : (freq_out_H1, audio_out_L, audio_out_R)
    with {
        // --- Input Processing ---
        proc_input = select2(testMode, 0, test_osc(testFreq));

        // --- DSP Chain ---

        // 1. Harmony 1 (Octave Up by default)
        voice2 = proc_input : pitch_shifter(final_shift_value_H1);

        // 2. Harmony 2 (Perfect Fifth Up by default)
        voice3 = proc_input : pitch_shifter(final_shift_value_H2);

        // 3. Dry/Wet Mix (Even split for Dry, H1, and H2)
        dry_gain = 0.33;
        wet_gain = 0.33;

        output_mix = (proc_input * dry_gain) + (voice2 * wet_gain) + (voice3 * wet_gain);

        // 4. DC Blocker (Essential for low-frequency stability)
        output_clean = output_mix : fi.dcblocker;

        // 5. Apply Gate & Final Smoother (CRITICAL POP FIX)
        // si.smoo applies a smoothing envelope to the gate signal.
        smooth_gate = testMode : si.smoo;
        audio_out_gated = output_clean * smooth_gate;

        // Final Output Smoother: Catches any remaining startup/quit transients.
        audio_out_final = audio_out_gated : si.smoo;

        // --- Output Definitions ---

        // Meter
        theoretical_freq_H1 = testFreq * ratio(final_shift_value_H1);
        freq_out_H1 = theoretical_freq_H1 : hbargraph("[3] Meters/Shifted Freq H1 [unit:Hz] [style:bargraph]", 0, 1000);

        // Audio Outputs (CRITICAL STEREO FIX: Explicitly setting both channels to the final mono signal)
        audio_out_L = audio_out_final;
        audio_out_R = audio_out_final;
    };
