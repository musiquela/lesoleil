#include <iostream>
#include <cmath>

#define FAUSTFLOAT float

#include "test_minimal.cpp"

int main(int argc, char* argv[]) {
    const int SR = 48000;
    const int BUFFER_SIZE = 4096;
    const int NUM_FRAMES = SR * 2; // 2 seconds

    mydsp dsp;

    // Initialize
    dsp.init(SR);

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
