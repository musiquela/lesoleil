#include <iostream>
#include <cmath>
#include "SGT_HarmonyGenerator.cpp"

class TestUI : public UI {
public:
    float testMode = 0.0f;
    float testFreq = 440.0f;
    float v2ShiftValue = 7.0f;
    float v2Enable = 0.0f;
    float v3ShiftValue = 4.0f;
    float v3Enable = 0.0f;
    float v1Enable = 1.0f;
    float wetDry = 0.5f;
    float olaWindow = 2048.0f;
    float olaXFade = 256.0f;
    float v2FreqOut = 0.0f;

    virtual void openTabBox(const char* label) {}
    virtual void openHorizontalBox(const char* label) {}
    virtual void openVerticalBox(const char* label) {}
    virtual void closeBox() {}

    virtual void addButton(const char* label, float* zone) {
        std::string l(label);
        if (l.find("Test Tone Enable") != std::string::npos) {
            *zone = testMode;
        } else if (l.find("v2Enable") != std::string::npos) {
            *zone = v2Enable;
        } else if (l.find("v3Enable") != std::string::npos) {
            *zone = v3Enable;
        } else if (l.find("v1Enable") != std::string::npos) {
            *zone = v1Enable;
        }
    }

    virtual void addCheckButton(const char* label, float* zone) {
        std::string l(label);
        if (l.find("Test Tone Enable") != std::string::npos) {
            *zone = testMode;
        } else if (l.find("v2Enable") != std::string::npos) {
            *zone = v2Enable;
        } else if (l.find("v3Enable") != std::string::npos) {
            *zone = v3Enable;
        } else if (l.find("v1Enable") != std::string::npos) {
            *zone = v1Enable;
        }
    }

    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) {
        std::string l(label);
        if (l.find("Test Tone Freq") != std::string::npos) {
            *zone = testFreq;
        } else if (l.find("Harmony 1/Shift") != std::string::npos) {
            *zone = v2ShiftValue;
        } else if (l.find("Harmony 2/Shift") != std::string::npos) {
            *zone = v3ShiftValue;
        }
    }

    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) {
        std::string l(label);
        if (l.find("Test Tone Freq") != std::string::npos) {
            *zone = testFreq;
        } else if (l.find("Harmony 1/Shift") != std::string::npos) {
            *zone = v2ShiftValue;
        } else if (l.find("Harmony 2/Shift") != std::string::npos) {
            *zone = v3ShiftValue;
        } else if (l.find("wetDry") != std::string::npos) {
            *zone = wetDry;
        } else if (l.find("OLA Window") != std::string::npos) {
            *zone = olaWindow;
        } else if (l.find("Crossfade") != std::string::npos) {
            *zone = olaXFade;
        }
    }

    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) {
        addHorizontalSlider(label, zone, init, min, max, step);
    }

    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) {
        std::string l(label);
        if (l.find("v2FreqOut") != std::string::npos) {
            v2FreqOut = *zone;
        }
    }

    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) {
        std::string l(label);
        if (l.find("v2FreqOut") != std::string::npos) {
            v2FreqOut = *zone;
        }
    }

    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}

    virtual void declare(float* zone, const char* key, const char* val) {}
};

int main() {
    const int SR = 48000;
    const int BUFFER_SIZE = 4096;
    const int NUM_FRAMES = SR * 2; // 2 seconds

    mydsp dsp;
    TestUI ui;

    // Initialize
    dsp.init(SR);
    dsp.buildUserInterface(&ui);

    // Set test parameters
    ui.testMode = 1.0f;  // Enable test tone
    ui.testFreq = 440.0f;  // 440 Hz input
    ui.v2ShiftValue = 7.0f;  // P5 Up (7 semitones)
    ui.v2Enable = 1.0f;  // Enable voice 2
    ui.v1Enable = 0.0f;  // Disable dry signal
    ui.v3Enable = 0.0f;  // Disable voice 3

    // Re-build UI with new values
    dsp.buildUserInterface(&ui);

    // Allocate buffers
    float** inputs = new float*[2];
    float** outputs = new float*[3]; // freq_meter + stereo audio
    for (int i = 0; i < 2; i++) {
        inputs[i] = new float[BUFFER_SIZE];
    }
    for (int i = 0; i < 3; i++) {
        outputs[i] = new float[BUFFER_SIZE];
    }

    // Process audio in chunks
    int totalFrames = 0;
    float lastFreqReading = 0.0f;

    while (totalFrames < NUM_FRAMES) {
        // Zero input (test tone is generated internally)
        for (int i = 0; i < BUFFER_SIZE; i++) {
            inputs[0][i] = 0.0f;
            inputs[1][i] = 0.0f;
        }

        // Process
        dsp.compute(BUFFER_SIZE, inputs, outputs);

        // Get frequency reading from first output (freq_meter)
        lastFreqReading = outputs[0][BUFFER_SIZE-1];

        totalFrames += BUFFER_SIZE;
    }

    // Clean up
    for (int i = 0; i < 2; i++) {
        delete[] inputs[i];
    }
    for (int i = 0; i < 3; i++) {
        delete[] outputs[i];
    }
    delete[] inputs;
    delete[] outputs;

    // Report result
    std::cout << "v2FreqOut Reading: " << lastFreqReading << " Hz" << std::endl;
    std::cout << "Expected: 659.25 Hz" << std::endl;
    std::cout << "Error: " << std::abs(lastFreqReading - 659.25) << " Hz" << std::endl;

    return 0;
}
