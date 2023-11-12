#include "autotune.h"

#include <cmath>
#include <algorithm>
#include <vector>

// Variable Definitions
float sample_rate = 48000; // KHz, may need to adjust this
arm_rfft_fast_instance_f32 fftConfig;
float32_t myfftInput[FFT_SIZE];
float32_t myfftOutput[2 * FFT_SIZE];

// Constructor
Autotune::Autotune() {
    // Constructor implementation (if needed)
    arm_rfft_fast_init_f32(&fftConfig, FFT_SIZE);
}

/*
 * Public Functions
 */
 // Pitch-Shift to Target Frequency
 void Autotune::pitchShift(float targetPitch, int16_t* micSignal, size_t signalLength) {
    // Calculate the frequency ratio
    float frequencyRatio = targetPitch / 440.0; // Assuming reference pitch of 440 Hz

    // Create an array for the shifted samples
    int16_t shiftedSignal[signalLength];

    // Linear interpolation to find the new sample values
    for (size_t i = 0; i < signalLength; ++i) {
        // Calculate the corresponding index in the original signal
        float originalIndex = i / frequencyRatio;

        // Perform linear interpolation
        int16_t lowerSample = micSignal[static_cast<size_t>(originalIndex)];
        int16_t upperSample = micSignal[std::min(static_cast<size_t>(originalIndex) + 1, signalLength - 1)];
        float fractionalPart = originalIndex - static_cast<size_t>(originalIndex);
        shiftedSignal[i] = static_cast<int16_t>((1.0 - fractionalPart) * lowerSample + fractionalPart * upperSample);
    }

    // Copy the shifted signal back to the original array
    memcpy(micSignal, shiftedSignal, sizeof(shiftedSignal));
}

// Autotune Original: Pitch-Shift to Nearest Frequency
void Autotune::autotuneOriginal(int16_t* micSignal, size_t signalLength) {
    // Convert micSignal to float array
    for (size_t i = 0; i < signalLength; ++i) {
        myfftInput[i] = static_cast<float32_t>(micSignal[i]);
    }

    // Perform FFT
    arm_rfft_fast_f32(&fftConfig, myfftInput, myfftOutput, 0);

    // Find the main frequency
    uint32_t maxIndex;
    float32_t maxValue;
    arm_max_f32(myfftOutput, FFT_SIZE, &maxValue, &maxIndex);
    size_t frequencyIndex = maxIndex;
    float mainFrequency = frequencyIndex * sample_rate / FFT_SIZE;

    // Find the nearest semitone
    float nearestSemitone = shiftToNearestSemitone(mainFrequency);

    // Call pitchShift with the nearest semitone as targetPitch
    pitchShift(nearestSemitone, micSignal, signalLength);
}

// Cepstrum Domain Correction
void Autotune::autotuneCepstrum(int16_t* micSignal, size_t signalLength) {
    // Cepstrum autotune implementation
    // ...
}

// Method #2
void Autotune::autotuneCepstrumNew(int16_t* micSignal, size_t signalLength) {
    // CepstrumNew autotune implementation
    // ...
}

// PSOLA Method
void Autotune::autotunePSOLA(int16_t* micSignal, size_t signalLength) {
    // PSOLA autotune implementation
    // ...
}

/*
 * Private Functions
 */
float Autotune::shiftToNearestSemitone(float noteFrequency) {
    // Calculate the nearest semitone frequency
    noteFrequency = max(noteFrequency, 1e-9); // Ensure noteFrequency is not zero
    int nearestSemitone = round(12 * log2(noteFrequency / 440));
    float nearestFrequency = 440 * pow(2, nearestSemitone / 12.0);
    return nearestFrequency;
}