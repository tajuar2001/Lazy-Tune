#ifndef AUTOTUNE_H
#define AUTOTUNE_H

#include <Arduino.h>
#include <AudioStream.h>

// -------------------------------
#define M_PI 3.14159265358979323846
#define MAX_FRAME_LENGTH 8192

void smbFft(float *fftBuffer, long fftFrameSize, long sign);
// -------------------------------


#include "arm_math.h"
#include "arm_common_tables.h"

#define AUTOTUNE_FFT_SIZE 128
#define AUTOTUNE_SAMPLING_RATE AUDIO_SAMPLE_RATE
#define AUTOTUNE_LOWER_LIMIT 0.529731547
#define AUTOTUNE_UPPER_LIMIT 1.88774863
#define AUTOTUNE_MIN_PS -0.4
#define AUTOTUNE_MAX_PS 0.9

// enum autotuneMethod { none, original };

class CustomAutoTune : public AudioStream {
public:
    CustomAutoTune(void): AudioStream(1,inputQueueArray) {
      // any extra initialization
      currFrequency = 20;
      manualPitchOffset = 0;
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
