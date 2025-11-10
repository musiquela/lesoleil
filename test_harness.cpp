// =================================================================================
// C++ TEST HARNESS
// Objective: Programmatically set UI parameters and read v2FreqOut meter value.
// Mandate: Confirm 440 Hz -> P5 Up (7 semitones) shift yields 659.25 Hz.
// =================================================================================

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <map>

#define FAUSTFLOAT float


// Minimal base classes needed by Faust
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

// Include the generated Faust code
#include "SGT_HarmonyGenerator.cpp"

using namespace std;

// MapUI implementation
class MapUI : public UI {
private:
    std::map<std::string, FAUSTFLOAT*> fPathZoneMap;

public:
    virtual ~MapUI() {}

    // Add control elements
    void addButton(const char* label, FAUSTFLOAT* zone) { addParameter(label, zone); }
    void addCheckButton(const char* label, FAUSTFLOAT* zone) { addParameter(label, zone); }
    void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT) { addParameter(label, zone); }
    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT) { addParameter(label, zone); }
    void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT) { addParameter(label, zone); }

    // Add output elements (bargraphs)
    void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT) { addParameter(label, zone); }
    void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT) { addParameter(label, zone); }

    // Layout
    void openTabBox(const char*) {}
    void openHorizontalBox(const char*) {}
    void openVerticalBox(const char*) {}
    void closeBox() {}

    // Metadata
    void declare(FAUSTFLOAT*, const char*, const char*) {}

    // Set parameter value
    void setParamValue(const std::string& path, FAUSTFLOAT value) {
        if (fPathZoneMap.count(path)) {
            *fPathZoneMap[path] = value;
        }
    }

    // Get parameter value
    FAUSTFLOAT getParamValue(const std::string& path) {
        if (fPathZoneMap.count(path)) {
            return *fPathZoneMap[path];
        }
        return 0.0f;
    }

    // List all parameters (for debugging)
    void listParameters() {
        std::cout << "Available parameters:" << std::endl;
        for (auto& p : fPathZoneMap) {
            std::cout << "  " << p.first << " = " << *p.second << std::endl;
        }
    }

private:
    void addParameter(const char* label, FAUSTFLOAT* zone) {
        fPathZoneMap[label] = zone;
    }
};

double calculate_expected_frequency(double base_freq, int semitones) {
    return base_freq * pow(2.0, (double)semitones / 12.0);
}

int main() {
    const int TEST_FREQ = 440;
    const int SHIFT_SEMITONES = 7; // P5 Up
    const double EXPECTED_FREQ = calculate_expected_frequency(TEST_FREQ, SHIFT_SEMITONES);
    const float SAMPLE_RATE = 48000.0f;

    cout << "--- Critical Pitch Validation Test (Headless Harness) ---" << endl;
    cout << "Expected Target Frequency (P5 Up from 440 Hz): " << EXPECTED_FREQ << " Hz" << endl;
    cout << "--------------------------------------------------------" << endl;

    // Initialize the DSP
    mydsp* dsp_instance = new mydsp();
    dsp_instance->init(SAMPLE_RATE);

    // Create UI and build interface
    MapUI ui;
    dsp_instance->buildUserInterface(&ui);

    cout << "\n";
    ui.listParameters();
    cout << "\n";

    // Set parameters
    ui.setParamValue("Debug Tools/Test Tone Freq", (float)TEST_FREQ);
    ui.setParamValue("Harmony 1/Shift", (float)SHIFT_SEMITONES);
    ui.setParamValue("Debug Tools/Test Tone Enable", 1.0f);
    ui.setParamValue("Harmony Generator/v2Enable", 1.0f);
    ui.setParamValue("Harmony Generator/v1Enable", 0.0f);
    ui.setParamValue("Harmony Generator/v3Enable", 0.0f);

    const int BUFFER_SIZE = 8192;

    // Allocate buffers
    vector<float> input_L(BUFFER_SIZE, 0.0f);
    vector<float> input_R(BUFFER_SIZE, 0.0f);
    vector<float> output_Meter(BUFFER_SIZE);
    vector<float> output_L(BUFFER_SIZE);
    vector<float> output_R(BUFFER_SIZE);

    float* inputs[2] = {input_L.data(), input_R.data()};
    float* outputs[3] = {output_Meter.data(), output_L.data(), output_R.data()};

    // Process audio multiple times to let ZCR stabilize
    // The ZCR needs at least 4096 samples to get an accurate reading
    float actual_meter_reading = 0.0f;
    for (int i = 0; i < 10; i++) {
        dsp_instance->compute(BUFFER_SIZE, inputs, outputs);
        actual_meter_reading = output_Meter[BUFFER_SIZE - 1];

        // Check audio output amplitude
        float max_L = 0.0f;
        for (int j = 0; j < BUFFER_SIZE; j++) {
            if (fabs(output_L[j]) > max_L) max_L = fabs(output_L[j]);
        }

        if (i % 2 == 0) {
            cout << "Pass " << (i+1) << ": Meter=" << actual_meter_reading << " Hz, Audio Peak=" << max_L << endl;
        }
    }

    cout << "\nFinal parameter states:" << endl;
    ui.listParameters();
    cout << endl;

    cout << "Actual Meter Reading (v2FreqOut): " << actual_meter_reading << " Hz" << endl;
    cout << "Note: The meter output is the FIRST output channel (index 0)" << endl;

    // Also check the UI parameter that bargraph writes to
    cout << "Bargraph UI Value: " << ui.getParamValue("Debug Tools/v2FreqOut") << " Hz" << endl;

    const double tolerance = 1.0;

    if (abs(actual_meter_reading - EXPECTED_FREQ) < tolerance) {
        cout << "STATUS: ✅ SUCCESS. The shift is mathematically verified." << endl;
    } else {
        cout << "STATUS: ❌ FAILURE. Deviation: " << abs(actual_meter_reading - EXPECTED_FREQ) << " Hz" << endl;
    }

    delete dsp_instance;

    return 0;
}
