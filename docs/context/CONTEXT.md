# Soleil Project Context

**Last Updated:** 2025-11-10 14:32 PST
**Session Status:** ✅ COMPLETE

## Project Overview

Soleil (formerly SGT Harmony Generator) is a three-voice harmony generator audio plugin built with Faust. It processes mono input and creates stereo three-voice harmony output with configurable pitch shifting for each voice.

**Current Version:** v1.1 Beta
**Build System:** Faust (faust2caqt)
**Platform:** macOS (CoreAudio/Qt5)

## Git Status

**Branch:** main
**Last Commit:** 10789d3 - "docs: Update /handoff command to include push step"
**Previous Commit:** 065f7d8 - "docs: Update session handoff (Session 1 complete)"
**Working Tree:** Modified (README.md updated, pedal mockup created)
**Status:** Up to date with origin/main

## Session Handoff

### Session Accomplishments (2025-11-10 Session 2)

This session focused on **brand messaging and hardware design mockup**:

1. **Product Description Refinement:**
   - Crafted sophisticated marketing copy for performing musicians
   - Emphasized precision, control, and musical intent over randomization
   - Highlighted scene-based preset organization and MIDI/footswitch control
   - Added inspiration from Josh Johnson and Sam Gendel's live pitch-shifting
   - Updated README.md with final brand messaging ("MEET SOLEIL")

2. **Hardware Pedal Design Mockup:**
   - Created SVG mockup: `docs/soleil-pedal-mockup.svg`
   - Design features:
     - OLED display showing scene name and harmony intervals (H1 & H2)
     - Three navigation buttons below OLED (Left/OK/Right)
     - Six footswitches: Scene ▲ | Preset 1-4 | Scene ▼
     - Dark metallic finish with gold "SOLEIL" branding
     - Clean layout without visible input/output jacks
   - Purpose: Visual reference for future hardware development

3. **Brand Identity Clarification:**
   - Positioned Soleil as a tool for musicians who understand music theory
   - Emphasized scene-based workflow for live performance and DAW automation
   - Tagline: "Three voices. Your intervals. Total recall at your fingertips… or toe-tips."

### Key Messaging Points

**Target Audience:** Performing musicians who need precise harmonic control, not algorithmic guesswork.

**Core Features:**
- Three-voice harmony with exact interval control
- Scene-based preset organization
- MIDI and footswitch navigation
- Dual format: Plugin (DAW) and hardware pedal (stage)

**Brand Voice:** Direct, intelligent, focused on solving a specific problem that doesn't exist in current market offerings.

### Active Work

**Status:** Ready for beta distribution

**Current Build:**
- Version: Soleil v1.1
- Location: `builds/apps/Soleil_v1.1.app`
- Signed: Ad-hoc (development/beta)
- Distribution: `Soleil-v1.1-Beta.zip` (46 MB)

### Recently Modified Files

**Modified This Session:**
```
README.md                         # Updated with "MEET SOLEIL" brand messaging
docs/soleil-pedal-mockup.svg      # NEW: Hardware pedal design mockup
docs/context/CONTEXT.md           # This file - session 2 handoff
```

**Previous Session (Session 1):**
```
scripts/                          # Complete certification infrastructure
Soleil.entitlements              # macOS entitlements
CERTIFICATION_STATUS.md          # Signing status documentation
README-FOR-BETA-TESTERS.txt      # End-user instructions
Soleil_v1.1.dsp                  # Current DSP implementation
```

### Next Session

**Immediate Tasks:**
1. Implement scene-based preset system in DSP code
2. Add MIDI CC mapping for scene/preset switching
3. Design preset data structure (scenes with 4 presets each)

**Future Development:**
1. Scene management UI/UX
2. Preset save/load functionality
3. MIDI learn for footswitch mapping
4. Hardware pedal prototyping (based on mockup design)
5. VST3/AU builds alongside standalone app
6. Developer ID signing (when macOS beta bug is fixed)

**Known Issues:**
- Current v1.1 has basic interval selection but no scene/preset infrastructure
- Developer ID signing blocked by macOS 26.2 beta bug (documented in CERTIFICATION_STATUS.md)

### Project Structure

```
soleil/
├── src/                          # Source code (test tools)
├── scripts/                      # Build and certification scripts (NEW)
├── docs/                         # Documentation
│   ├── context/                  # Session context (NEW)
│   │   └── CONTEXT.md           # This file
│   ├── CHANGELOG.md
│   ├── BUILD_NOTES.md
│   └── NEXT_SESSION.md
├── archive/                      # Historical code/iterations
├── builds/                       # Build outputs (not in repo)
├── Soleil_v1.1.dsp              # Current DSP implementation
├── Soleil_v1.0.dsp              # Previous stable version
├── Soleil.entitlements          # macOS entitlements (NEW)
├── CERTIFICATION_STATUS.md       # Signing status documentation (NEW)
├── README-FOR-BETA-TESTERS.txt  # End-user instructions (NEW)
└── README.md                    # Project documentation
```

### Dependencies

**Build Tools:**
- Faust compiler (installed)
- faust2caqt (CoreAudio/Qt5 builder)
- Qt@5 (Homebrew: /opt/homebrew/opt/qt@5)
- Xcode Command Line Tools

**Runtime:**
- macOS 10.13+ (High Sierra or later)
- Audio interface or built-in audio

**Code Signing:**
- Developer ID Application certificate (installed)
- Apple WWDR G3 + Developer ID G2 CA (installed)
- Private key in login keychain

### Testing Status

**Tested:**
- ✅ Fresh build with Qt@5
- ✅ Ad-hoc code signing
- ✅ App launches successfully
- ✅ Distribution package creation

**Not Tested:**
- ⏳ Developer ID signing (blocked by macOS beta bug)
- ⏳ Apple notarization
- ⏳ Beta tester feedback

---

## Session History

### Session 2: 2025-11-10 - Brand Messaging & Hardware Design ✅
- Developed sophisticated product description for performing musicians
- Created hardware pedal mockup (SVG) with OLED, navigation buttons, and 6 footswitches
- Updated README.md with "MEET SOLEIL" brand messaging
- Clarified target audience: musicians who understand music theory and need precision
- Established brand voice: direct, intelligent, problem-solving focused
- Designed pedal layout: Scene ▲/▼ + 4 preset buttons

**Key Outcome:** Clear brand identity and visual reference for future hardware development.

### Session 1: 2025-11-10 - Code Signing & Beta Distribution ✅
- Examined Phil repository certification setup (reference implementation)
- Created complete certification infrastructure (8 scripts)
- Investigated Developer ID signing failures
- Identified macOS 26.2 beta bug as root cause
- Built fresh Soleil_v1.1.app with proper Qt environment
- Created beta distribution package (46 MB ZIP + README)
- Established session handoff infrastructure

**Key Outcome:** Ready-to-distribute beta package with ad-hoc signing workaround for macOS beta bug.
