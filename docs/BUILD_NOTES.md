# SGT Harmony Generator - Build Notes

**Date:** 2025-11-09
**Platform:** macOS (Darwin 25.2.0)
**Faust Version:** 2.81.10

---

## ✅ Successfully Built

### GUI Application (CoreAudio)
**File:** `SGT_HarmonyGenerator_v1.8.app`
**Build Command:** `faust2caqt -midi SGT_HarmonyGenerator_v1.8.dsp`
**Status:** ✅ Built and launched successfully
**Audio Backend:** CoreAudio (macOS native)

---

## 📦 Dependencies Installed

1. **pkg-config** (2.5.1) - Required by faust2jaqt/faust2caqt
2. **JACK** (1.9.22_1) - Audio Connection Kit
   - Dependencies: berkeley-db@5, libsamplerate, aften
3. **Qt5** (5.15.17_1) - GUI framework
   - 10,849 files, 340.0MB
   - Keg-only (not symlinked)
   - Dependencies: libpng, freetype, pcre2, glib, jpeg-turbo, libtiff, md4c, giflib, webp

---

## 🔧 Build Process

### Attempt 1: faust2jaqt (JACK + Qt)
**Command:** `faust2jaqt -midi SGT_HarmonyGenerator_v1.8.dsp`
**Result:** ❌ Failed
**Error:** `fatal error: 'jack/jack.h' file not found`
**Reason:** qmake build system not picking up JACK include paths from environment variables

### Attempt 2: faust2caqt (CoreAudio + Qt) ✅
**Command:** `faust2caqt -midi SGT_HarmonyGenerator_v1.8.dsp`
**Result:** ✅ Success
**Output:** `./SGT_HarmonyGenerator_v1.8.app`
**Warnings:**
- Qt version mismatch (tested with SDK 14, using SDK 26)
- Non-critical, build completed successfully

### Environment Setup Required
```bash
export PATH="/opt/homebrew/opt/qt@5/bin:$PATH"
```

---

## ❌ Plugin Build Failures

### VST Plugin
**Command:** `faust2vst SGT_HarmonyGenerator_v1.8.dsp`
**Result:** ❌ Failed
**Error:** VST SDK not found at `/usr/local/include/vstsdk2.4/`
**Solution:** Would need to download and install Steinberg VST SDK

### Audio Unit (AU)
**Command:** `faust2au SGT_HarmonyGenerator_v1.8.dsp`
**Result:** ❌ Failed
**Error:** Cannot find Faust directories at `/usr/local/include/faust`
**Actual Location:** `/opt/homebrew/include/faust` (Homebrew installation)
**Issue:** faust2au script has hardcoded paths for non-Homebrew installation

### LV2 Plugin
**Command:** `faust2lv2 SGT_HarmonyGenerator_v1.8.dsp`
**Result:** ❌ Failed
**Error:** `faust-lv2 library files not found`
**Solution:** Would need to install faust-lv2 architecture files

---

## 🚀 Working Application

### Launch Command
```bash
open SGT_HarmonyGenerator_v1.8.app
```

### Features
- ✅ MIDI input support
- ✅ C0-B0 preset control (12 harmony intervals)
- ✅ Real-time TDHS/OLA pitch shifting
- ✅ Wet/Dry mix control
- ✅ Test tone generator
- ✅ Frequency display meter
- ✅ Manual override mode

### Testing
1. Launch application
2. Connect MIDI keyboard
3. Enable "Test Tone Enable" in Debug Tools
4. Set "Test Tone Freq" to 440 Hz
5. Press C#0 (MIDI note 13) for P5 Up preset
6. Observe frequency meter showing ~659 Hz
7. Adjust "Wet/Dry Mix" slider to blend harmony with original

---

## 🔄 Alternative Plugin Export Options

Since standard plugin builders failed, here are alternatives:

### Option 1: Manual VST SDK Installation
```bash
# Download VST SDK 2.4 from Steinberg
# Extract to /usr/local/include/vstsdk2.4/
# Retry: faust2vst SGT_HarmonyGenerator_v1.8.dsp
```

### Option 2: Fix faust2au Script
```bash
# Edit /opt/homebrew/bin/faust2au
# Change /usr/local/include/faust to /opt/homebrew/include/faust
# Change /usr/local/share/faust to /opt/homebrew/share/faust
```

### Option 3: Use GUI App in DAW
Many DAWs can host standalone audio applications via plugins like:
- Hosting AU (from Blue Cat Audio)
- AudioGridder
- Loopback (by Rogue Amoeba)

### Option 4: Export to Other Formats
```bash
# Web Assembly (for browser use)
faust2wasm SGT_HarmonyGenerator_v1.8.dsp

# Pure Data external
faust2puredata SGT_HarmonyGenerator_v1.8.dsp

# Max/MSP external
faust2max6 SGT_HarmonyGenerator_v1.8.dsp
```

---

## 📊 Build Summary

| Target | Command | Status | Notes |
|--------|---------|--------|-------|
| GUI (CoreAudio) | faust2caqt -midi | ✅ Success | Use this! |
| GUI (JACK) | faust2jaqt -midi | ❌ Failed | JACK header path issues |
| VST Plugin | faust2vst | ❌ Failed | Missing VST SDK |
| AU Plugin | faust2au | ❌ Failed | Hardcoded paths |
| LV2 Plugin | faust2lv2 | ❌ Failed | Missing faust-lv2 lib |

---

## 🎯 Recommended Usage

**For now:** Use the standalone GUI application (`SGT_HarmonyGenerator_v1.8.app`)

**Advantages:**
- Full MIDI support
- All controls accessible
- No DAW required for testing
- Real-time performance
- CoreAudio integration (low latency)

**For DAW integration:**
- Route audio from DAW to app via Loopback or BlackHole
- Use MIDI routing via IAC Driver
- Or: Fix faust2au script to build native AU plugin

---

## 🐛 Known Issues

1. **Qt SDK Version Warning**
   - Non-critical
   - App builds and runs despite warning
   - Using SDK 26 instead of tested SDK 14

2. **JACK Build Failure**
   - JACK headers not found by qmake
   - Environment variables not propagated
   - CoreAudio build works as alternative

3. **Plugin Builders**
   - VST: Missing SDK
   - AU: Hardcoded non-Homebrew paths
   - LV2: Missing library files

---

## 🎉 Success Metrics

✅ GUI application built successfully
✅ Application launches without errors
✅ MIDI support enabled
✅ All DSP features accessible
✅ CoreAudio backend working
✅ Ready for real-world testing

---

**Next Steps:**
1. Test MIDI preset switching with real keyboard
2. Verify harmony generation accuracy
3. Test with various audio sources
4. Measure latency and performance
5. Consider fixing faust2au for plugin export

**Build completed:** 2025-11-09 20:25
**Total build time:** ~10 minutes (including dependency installation)
