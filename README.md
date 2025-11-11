# Soleil - Harmony Generator

## MEET SOLEIL.

Most harmony tools try to be everything to everyone. Soleil is for individuals.

If you need precise three-voice harmony that you control, this is your tool. Build custom voicings based on the intervals you choose. Organize them into scenes that match your setlist or your session structure and easily navigate between groupings of preset harmonies using MIDI or footswitches.

Inspired by the live performance pitch-shifting of jazz pioneers like Josh Johnson and Sam Gendel, but yearning for more versatility and customization, Soleil isn't a one-size-fits-all solution. It's a meticulous instrument for performing musicians who need exact harmonic control—on stage and in the studio.

If you've been searching for a way to architect your harmony with the same precision you bring to your playing, you've found it.

Three voices. Your intervals. Total recall at your fingertips… or toe-tips. You decide.

---

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
