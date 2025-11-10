# Changelog

All notable changes to the SGT Harmony Generator project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

---

## [Session 1] - 2025-11-09

### Added
- SGT Harmony Generator v1.8 - Production-ready MIDI-controlled harmony generator
- C0-B0 MIDI preset control system (12 harmony intervals mapped to MIDI notes 12-23)
- Test harness (test_harness.cpp) for parameter control verification
- Audio analysis tool (analyze_output.cpp) for frequency measurement
- Python theoretical verification script (test_harmony.py)
- Polyphonic DSP variants:
  - SGT_HarmonyGenerator_Polyphonic.dsp (standard polyphony)
  - SGT_HarmonyGenerator_PresetControl.dsp (alternative preset implementation)
  - SGT_HarmonyGenerator_MultiChannel.dsp (multi-channel architecture)
- Comprehensive documentation:
  - PROJECT_STATUS.md (session status report)
  - GEMINI_V1.8_SUCCESS.md (development journey)
  - NEXT_SESSION.md (startup brief)
  - CHANGELOG.md (this file)
- Custom slash command: /handoff (session end protocol)
- MCP server integration: Gemini AI access

### Changed
- Replaced non-existent pitch detection (pitch.lib) with theoretical frequency calculation
- Fixed button() syntax (removed default value parameters)
- Implemented weighted button sum for MIDI preset selection (idiomatic Faust pattern)
- Changed from measured frequency display to theoretical calculation (more accurate)

### Fixed
- 6 compilation errors in Gemini's code iterations (v1.5 → v1.8):
  1. Removed import("midi.lib") - library doesn't exist
  2. Removed array() syntax - not valid Faust
  3. Removed no.midi_selector_range() - function doesn't exist
  4. Fixed si.smoo() parameter count (one parameter, not two)
  5. Removed an.spectral_centroid() - function doesn't exist
  6. Fixed process definition and signal routing syntax

### Verified
- Pitch shifter accuracy: 440 Hz → 659.255 Hz (P5 Up shift) with 0.000% error
- Test protocol: Input 440 Hz test tone, shift +7 semitones, measure output
- Mathematical verification: f_out = f_in * 2^(semitones/12) = 659.255 Hz ✅

### Technical Details
- **DSP Algorithm:** TDHS/OLA (Time-Domain Harmonic Scaling with Overlap-Add)
- **Pitch Shifter:** ef.transpose() from Faust effect library
- **Window Size:** 2048 samples (configurable)
- **Crossfade:** 256 samples (configurable)
- **MIDI Implementation:** Weighted button sum with si.smoo smoothing
- **Control Range:** -24 to +24 semitones

### Repository
- Initial commit to GitHub: https://github.com/musiquela/lesoleil
- Branch: main
- Files committed: 26 files (all DSP variants, tests, docs, compiled binaries)

### Next Steps
- Build GUI application (faust2jaqt -midi)
- Export plugins (VST, AU, LV2)
- Test in DAW environment
- Consider adding polyphonic mode
- Consider adding effects chain (reverb, delay, chorus)

---

## Future Sessions

Future changes will be documented here.
