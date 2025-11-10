# Soleil - Harmony Generator

A real-time 3-voice harmony generator built with Faust.

## Features

- **Three Voice Processing**: Dry signal + two independent harmony voices
- **Real-time Pitch Shifting**: Based on TDHS (Time-Domain Harmonic Scaling)
- **Adjustable Parameters**: Independent control over pitch shift and gain per voice
- **Mono to Stereo**: Takes mono input, outputs to stereo

## Quick Start

```bash
# Open the standalone app
open builds/apps/Soleil_v1.0.app
```

## Default Settings

- **Harmony 1**: +12 semitones (octave up)
- **Harmony 2**: +7 semitones (perfect 5th up)
- **Result**: Power chord harmony!

## Project Structure

```
soleil/
├── Soleil_v1.0.dsp          # Main source code
├── builds/
│   ├── apps/                # Standalone applications
│   └── plugins/             # VST/AU plugins
├── docs/                    # Documentation
├── src/                     # Source code and tools
└── archive/                 # Historical versions
```

## License

BSD License

## Credits

Based on official Faust pitch shifter examples from Grame.
