#ifndef AUTOTUNE_H
#define AUTOTUNE_H

#include <cmath>
#include <algorithm>
#include <vector>
#include <cstring>

#include <Arduino.h>
#include <AudioStream.h>
#include <Audio.h>

#include "arm_math.h"
#include "arm_common_tables.h"

#define AUTOTUNE_FFT_SIZE 1024
#define AUTOTUNE_SAMPLING_RATE AUDIO_SAMPLE_RATE

enum autotuneMethod { none, original, cepstrum, psola, manual };

// FFT configuration structure
extern arm_rfft_fast_instance_f32 fftConfig; // Declare as extern

// Buffers
extern float32_t myfftInput[AUTOTUNE_FFT_SIZE]; // Declare as extern
extern float32_t myfftOutput[2 * AUTOTUNE_FFT_SIZE]; // Declare as extern

class CustomAutoTune : public AudioStream {
public:
    CustomAutoTune(void): AudioStream(1,inputQueueArray) {
      // any extra initialization
      arm_rfft_fast_init_f32(&fftConfig, AUTOTUNE_FFT_SIZE);
    }

    // AudioStream object updater
    virtual void update(void);

    /* Controls */
    // option editor (true if successful, false otherwise)
    boolean option_edit(autotuneMethod method); // select method
    boolean set_frequency(float32_t freq) { // seet manualFrequency for autotuneManualMode
      manualFrequency = freq;
      return true;
    }

    /* AutoTune */
    void pitchShift(float targetPitch, float32_t*& micSignal, size_t signalLength);
    float shiftToNearestSemitone(float noteFrequency);
    void autotuneManualMode(float32_t*& micSignal, size_t signalLength);
    // autotune implementations
    void autotuneOriginal(float32_t*& micSignal, size_t signalLength);
    void autotuneCepstrum(float32_t*& micSignal, size_t signalLength);
    void autotunePSOLA(float *input, float *output, int bufferSize, float pitchFactor);

private:
    audio_block_t *inputQueueArray[1];
    arm_rfft_fast_instance_f32 fftConfig;
    autotuneMethod currMethod = autotuneMethod::none;
    float32_t myfftInput[AUTOTUNE_FFT_SIZE];
    float32_t myfftOutput[2 * AUTOTUNE_FFT_SIZE];
    float32_t manualFrequency = 440;

    // functions
    float calculatePitch(float32_t* signal, size_t signalLength);
    void interpolate(float32_t* input, size_t inLength, float32_t* output, size_t outLength, float factor);
};

#endif // AUTOTUNE_H
