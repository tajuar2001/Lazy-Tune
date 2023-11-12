#ifndef AUTOTUNE_H
#define AUTOTUNE_H

#include <Arduino.h>
#include <Audio.h>

#include "arm_math.h"

extern float sample_rate; // Declare as extern

#define FFT_SIZE 1024  // Adjust the size based on your requirements

// FFT configuration structure
extern arm_rfft_fast_instance_f32 fftConfig; // Declare as extern

// Buffers
extern float32_t myfftInput[FFT_SIZE]; // Declare as extern
extern float32_t myfftOutput[2 * FFT_SIZE]; // Declare as extern

class Autotune {
public:
    Autotune(); // Constructor

    void pitchShift(float targetPitch, int16_t* micSignal, size_t signalLength);
    // autotune implementations
    void autotuneOriginal(int16_t* micSignal, size_t signalLength);
    void autotuneCepstrum(int16_t* micSignal, size_t signalLength);
    void autotuneCepstrumNew(int16_t* micSignal, size_t signalLength); // alternate method
    void autotunePSOLA(int16_t* micSignal, size_t signalLength);

private:
    float shiftToNearestSemitone(float noteFrequency);
};

#endif // AUTOTUNE_H
