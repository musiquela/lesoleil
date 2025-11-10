#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Simple zero-crossing rate calculator
float calculate_zcr(const vector<float>& signal) {
    int crossings = 0;
    for (size_t i = 1; i < signal.size(); i++) {
        if ((signal[i-1] >= 0 && signal[i] < 0) || (signal[i-1] < 0 && signal[i] >= 0)) {
            crossings++;
        }
    }
    return (float)crossings / 2.0f; // Divide by 2 because each cycle has 2 crossings
}

// Estimate frequency from period
float estimate_frequency_from_signal(const vector<float>& signal, float sample_rate) {
    // Find zero crossings
    vector<int> zero_crossings;
    for (size_t i = 1; i < signal.size(); i++) {
        if (signal[i-1] < 0 && signal[i] >= 0) { // Rising zero crossing
            zero_crossings.push_back(i);
        }
    }

    if (zero_crossings.size() < 2) {
        return 0.0f;
    }

    // Calculate average period
    float avg_period = 0;
    for (size_t i = 1; i < zero_crossings.size(); i++) {
        avg_period += (zero_crossings[i] - zero_crossings[i-1]);
    }
    avg_period /= (zero_crossings.size() - 1);

    return sample_rate / avg_period;
}

#define FAUSTFLOAT float

class UI {
public:
    virtual ~UI() {}
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;
    virtual void addButton(const char* label, FAUSTFLOAT* zone) = 0;
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) = 0;
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) = 0;
};

class Meta {
public:
    virtual ~Meta() {}
    virtual void declare(const char* key, const char* value) = 0;
};

class dsp {
public:
    virtual ~dsp() {}
    virtual int getNumInputs() = 0;
    virtual int getNumOutputs() = 0;
    virtual void init(int sample_rate) = 0;
    virtual void buildUserInterface(UI* ui_interface) = 0;
    virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    virtual void metadata(Meta* m) = 0;
};

#include "SGT_HarmonyGenerator.cpp"

class SimpleUI : public UI {
public:
    FAUSTFLOAT testMode = 1.0f;
    FAUSTFLOAT testFreq = 440.0f;
    FAUSTFLOAT v2Shift = 7.0f;
    FAUSTFLOAT v2Enable = 1.0f;
    FAUSTFLOAT v1Enable = 0.0f;

    void openTabBox(const char*) {}
    void openHorizontalBox(const char*) {}
    void openVerticalBox(const char*) {}
    void closeBox() {}

    void addButton(const char* label, FAUSTFLOAT* zone) { setParam(label, zone); }
    void addCheckButton(const char* label, FAUSTFLOAT* zone) { setParam(label, zone); }
    void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT) { setParam(label, zone); }
    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT) { setParam(label, zone); }
    void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT) { setParam(label, zone); }
    void addHorizontalBargraph(const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) {}
    void addVerticalBargraph(const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) {}
    void declare(FAUSTFLOAT*, const char*, const char*) {}

    void setParam(const char* label, FAUSTFLOAT* zone) {
        string l(label);
        if (l.find("Test Tone Enable") != string::npos) *zone = testMode;
        else if (l.find("Test Tone Freq") != string::npos) *zone = testFreq;
        else if (l.find("Harmony 1/Shift") != string::npos) *zone = v2Shift;
        else if (l.find("v2Enable") != string::npos) *zone = v2Enable;
        else if (l.find("v1Enable") != string::npos) *zone = v1Enable;
    }
};

int main() {
    const float SR = 48000.0f;
    const int BUFFER_SIZE = 8192;

    mydsp* dsp_instance = new mydsp();
    dsp_instance->init(SR);

    SimpleUI ui;
    dsp_instance->buildUserInterface(&ui);

    vector<float> input_L(BUFFER_SIZE, 0.0f);
    vector<float> input_R(BUFFER_SIZE, 0.0f);
    vector<float> output_Meter(BUFFER_SIZE);
    vector<float> output_L(BUFFER_SIZE);
    vector<float> output_R(BUFFER_SIZE);

    float* inputs[2] = {input_L.data(), input_R.data()};
    float* outputs[3] = {output_Meter.data(), output_L.data(), output_R.data()};

    // Process several times to stabilize (OLA needs time to fill buffers)
    // With window size = 2048, we need at least that many samples to stabilize
    for (int i = 0; i < 20; i++) {
        dsp_instance->compute(BUFFER_SIZE, inputs, outputs);

        if (i % 5 == 0) {
            float freq = estimate_frequency_from_signal(output_L, SR);
            cout << "Pass " << (i+1) << ": Measured = " << freq << " Hz" << endl;
        }
    }

    // Final analysis
    float measured_freq = estimate_frequency_from_signal(output_L, SR);
    float zcr = calculate_zcr(output_L);
    float zcr_freq = (zcr / BUFFER_SIZE) * SR;

    cout << "\n=== FINAL AUDIO ANALYSIS ===" << endl;
    cout << "Measured Frequency (zero-crossing analysis): " << measured_freq << " Hz" << endl;
    cout << "ZCR Count: " << zcr << " crossings" << endl;
    cout << "ZCR Frequency Estimate: " << zcr_freq << " Hz" << endl;
    cout << "Expected: 659.255 Hz" << endl;
    cout << "Error: " << fabs(measured_freq - 659.255) << " Hz (" << (fabs(measured_freq - 659.255) / 659.255 * 100.0) << "%)" << endl;

    delete dsp_instance;
    return 0;
}
