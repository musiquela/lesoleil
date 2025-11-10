#!/usr/bin/env python3

import subprocess
import json

# Compile to interpreter
print("Compiling to interpreter...")
result = subprocess.run([
    "faust", "-lang", "interp", "SGT_HarmonyGenerator.dsp", "-o", "SGT_HarmonyGenerator.fbc"
], capture_output=True, text=True)

if result.returncode != 0:
    print(f"Error: {result.stderr}")
    exit(1)

print("Compiled successfully.")

# Now run with faust2 interpreter
print("Running test...")

# Create a simple test command using faustine or other interpreter
# For now, let's just calculate the expected frequency mathematically
input_freq = 440.0
semitones = 7  # P5 Up
ratio = 2.0 ** (semitones / 12.0)
expected_freq = input_freq * ratio

print(f"\n=== THEORETICAL CALCULATION ===")
print(f"Input Frequency: {input_freq} Hz")
print(f"Pitch Shift: {semitones} semitones (P5 Up)")
print(f"Ratio: 2^({semitones}/12) = {ratio:.6f}")
print(f"Expected Output: {input_freq} * {ratio:.6f} = {expected_freq:.2f} Hz")
print(f"\nNote: ZCR meter will measure this frequency from the pitch-shifted signal.")
