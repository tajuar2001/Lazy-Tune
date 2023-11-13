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

#define AUTOTUNE_FFT_SIZE 128
#define AUTOTUNE_SAMPLING_RATE 48000

enum autotuneMethod { none, original, cepstrum, psola };

// FFT configuration structure
extern arm_rfft_fast_instance_f32 fftConfig; // Declare as extern

// Buffers
extern float32_t myfftInput[AUTOTUNE_FFT_SIZE]; // Declare as extern
extern float32_t myfftOutput[2 * AUTOTUNE_FFT_SIZE]; // Declare as extern

class CustomAutoTune : public AudioStream {
public:
    CustomAutoTune(void): AudioStream(1,inputQueueArray) {
      // any extra initialization
      currMethod = autotuneMethod::none;
      arm_rfft_fast_init_f32(&fftConfig, AUTOTUNE_FFT_SIZE);
    }

    // AudioStream object updater
    virtual void update(void);

    // option editor (true if successful, false otherwise)
    boolean option_edit(autotuneMethod method); // select method

    void pitchShift(float targetPitch, int16_t* micSignal, size_t signalLength);
    float shiftToNearestSemitone(float noteFrequency);
    // autotune implementations
    void autotuneOriginal(int16_t* micSignal, size_t signalLength);
    void autotuneCepstrum(int16_t* micSignal, size_t signalLength);
    void autotunePSOLA(int16_t* micSignal, size_t signalLength);

private:
    audio_block_t *inputQueueArray[1];
    arm_rfft_fast_instance_f32 fftConfig;
    autotuneMethod currMethod;
    float32_t myfftInput[AUTOTUNE_FFT_SIZE];
    float32_t myfftOutput[2 * AUTOTUNE_FFT_SIZE];
    float sample_rate = 48000; // KHz, may need to adjust this
};

#endif // AUTOTUNE_H
