// =================================================================================
// PROJECT: HPS Pitch Detector Example
// DESCRIPTION: Minimal code to demonstrate pm.hps_pitch is available in standard FAUST.
// This code takes input and meters its fundamental frequency (f0) in Hz.
// =================================================================================

// --- 1. Library Import (Crucial for HPS) ---
import("stdfaust.lib");
import("pitch.lib"); // This is where pm.hps_pitch lives.

// --- 2. HPS Function Definition ---
// pm.hps_pitch requires several parameters:
// (size, step, max_peaks, threshold, min_freq, max_freq)
// The output tuple is (pitch, loudness, frequency) - we only route the frequency.
hps_meter(input) = input : pm.hps_pitch(4096, 512, 10, 0.9, 50.0, 2000.0) : _ , _ , _;

// --- 3. UI Element for Metering ---
// We use a bargraph to display the frequency output.
freq_out(signal) = signal : hps_meter
    : vslider("f0 [unit:Hz] [style:bargraph]", 0, 0, 1000, 1);

// --- 4. Process Definition ---
// Process takes stereo input (left, right)
// It uses the left channel for pitch detection and outputs only the meter value.
process = _, _ : _, 0 : freq_out;
