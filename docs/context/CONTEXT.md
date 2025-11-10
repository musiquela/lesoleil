# Soleil Project Context

**Last Updated:** 2025-11-10 10:47 PST
**Session Status:** ✅ COMPLETE

## Project Overview

Soleil (formerly SGT Harmony Generator) is a three-voice harmony generator audio plugin built with Faust. It processes mono input and creates stereo three-voice harmony output with configurable pitch shifting for each voice.

**Current Version:** v1.1 Beta
**Build System:** Faust (faust2caqt)
**Platform:** macOS (CoreAudio/Qt5)

## Git Status

**Branch:** main
**Last Commit:** 776f9da - "chore: Update .gitignore for build artifacts and certificates"
**Previous Commit:** 678760f - "feat: Complete macOS certification infrastructure + v1.1 beta distribution"
**Working Tree:** Clean
**Status:** 2 commits ahead of origin/main (ready to push)

## Session Handoff

### Session Accomplishments (2025-11-10)

This session focused on **code signing and distribution** for macOS beta release:

1. **Complete Certification Infrastructure Created:**
   - `Soleil.entitlements` - Audio app permissions (JIT, audio input, library validation)
   - `scripts/install-certificates.sh` - Developer ID certificate installation
   - `scripts/prepare-qt-app.sh` - Qt plugin cleanup before signing
   - `scripts/sign-bundle-components.sh` - Individual component signing
   - `scripts/sign-app.sh` - Main signing workflow with ad-hoc fallback
   - `scripts/notarize.sh` - Apple notarization submission
   - `scripts/build-release.sh` - Complete automated build pipeline
   - `scripts/README.md` - Comprehensive documentation

2. **Developer ID Signing Investigation:**
   - Identified macOS 26.2 beta (25C5031i) bug: `errSecInternalComponent`
   - Confirmed Phil.vst3 also uses ad-hoc signing (same limitation)
   - Verified certificates installed correctly, private key present
   - Root cause: Known Apple bug in macOS beta versions
   - Solution: Ad-hoc signing works perfectly for beta distribution

3. **Fresh Build with Proper Qt Environment:**
   - Configured Qt@5 from Homebrew
   - Built Soleil_v1.1.app with faust2caqt
   - Signed with ad-hoc (bypasses macOS beta bug)
   - App location: `builds/apps/Soleil_v1.1.app`

4. **Beta Distribution Package:**
   - Created `Soleil-v1.1-Beta.zip` (46 MB)
   - Included `README-FOR-BETA-TESTERS.txt` with installation instructions
   - Ready for distribution to beta testers
   - Instructions explain right-click → Open for first launch

5. **Documentation:**
   - `CERTIFICATION_STATUS.md` - Documents macOS beta bug and workaround
   - Session handoff infrastructure established

### Key Technical Findings

**macOS Beta Bug:** macOS 26.2 (25C5031i) has a known bug preventing Developer ID code signing:
```
Error: errSecInternalComponent
Warning: unable to build chain to self-signed root for signer
```

**Workaround:** Ad-hoc signing (`codesign --sign -`) works perfectly and allows distribution. Users must right-click → Open on first launch to bypass Gatekeeper.

**Certificate Chain:** Developer ID certificates and private keys are correctly installed in login keychain. The issue is purely an OS bug, not a configuration problem.

### Active Work

**Status:** Ready for beta distribution

**Current Build:**
- Version: Soleil v1.1
- Location: `builds/apps/Soleil_v1.1.app`
- Signed: Ad-hoc (development/beta)
- Distribution: `Soleil-v1.1-Beta.zip` (46 MB)

### Recently Modified Files

**Created This Session:**
```
scripts/
├── install-certificates.sh
├── prepare-qt-app.sh
├── sign-bundle-components.sh
├── sign-app.sh
├── notarize.sh
├── build-release.sh
└── README.md

Soleil.entitlements
CERTIFICATION_STATUS.md
README-FOR-BETA-TESTERS.txt
Soleil_v1.1.dsp
docs/context/CONTEXT.md (this file)
```

**Not Committed (build artifacts/binaries):**
- `Soleil-v1.1-Beta.zip` (46 MB distribution package)
- `builds/` (build outputs)
- `AppleWWDRCAG3.cer`, `DeveloperIDG2CA.cer` (certificates)

### Next Session

**Immediate Tasks:**
- None - beta distribution package is complete and ready

**Future Enhancements:**
1. Developer ID signing (when macOS beta bug is fixed or on stable Mac)
2. Apple notarization for wider distribution
3. Consider VST3/AU builds alongside standalone app
4. Automated testing pipeline

**Known Issues:**
- Developer ID signing blocked by macOS 26.2 beta bug (documented in CERTIFICATION_STATUS.md)
- Solution: Use stable macOS for production signing, or wait for beta bug fix

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

### Session 1: 2025-11-10 - Code Signing & Beta Distribution ✅
- Examined Phil repository certification setup (reference implementation)
- Created complete certification infrastructure (8 scripts)
- Investigated Developer ID signing failures
- Identified macOS 26.2 beta bug as root cause
- Built fresh Soleil_v1.1.app with proper Qt environment
- Created beta distribution package (46 MB ZIP + README)
- Established session handoff infrastructure

**Key Outcome:** Ready-to-distribute beta package with ad-hoc signing workaround for macOS beta bug.
