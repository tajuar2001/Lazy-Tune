#ifndef AUTOTUNE_H
#define AUTOTUNE_H

#include <Arduino.h>
#include <AudioStream.h>
#include <Audio.h>
// -------------------------------
#include <string.h>
#include <math.h>
#include <stdio.h>

// -------------------------------
#define M_PI 3.14159265358979323846
#define MAX_FRAME_LENGTH 8192

void smbFft(float *fftBuffer, long fftFrameSize, long sign);
double smbAtan2(double x, double y);
// -------------------------------


#include "arm_math.h"
#include "arm_common_tables.h"

#define AUTOTUNE_FFT_SIZE 512
#define AUTOTUNE_SAMPLING_RATE AUDIO_SAMPLE_RATE

// enum autotuneMethod { none, original };

class CustomAutoTune : public AudioStream {
public:
    CustomAutoTune(void): AudioStream(1,inputQueueArray) {
      // any extra initialization
    }

    // AudioStream object updater
    virtual void update(void);

    /* Public Parameters */
    float currFrequency;
    float manualPitchOffset; // -0.4 to 0.9

    /* Controls */
    // option editor (true if successful, false otherwise)
    // boolean option_edit(autotuneMethod method); // select method

    /* AutoTune */
    float computeNearestSemitone(float noteFrequency);
    void pitchShift(float targetPitch, float* indata, float* outdata);
    // autotune implementations
    void autotuneOriginal(float* micSignal);

private:
    audio_block_t *inputQueueArray[1];
    // autotuneMethod currMethod;
};

#endif // AUTOTUNE_H
