#include "autotune.h"

// option selector
boolean CustomAutoTune::option_edit(autotuneMethod method) {
  boolean all_ok = true;
  if(0) {
    Serial.print("Edit AutoTune");
    Serial.print("option = ");
    Serial.print(method);
  }

  currMethod = method;

  return all_ok;
}

// main update function
void CustomAutoTune::update(void) {
  audio_block_t *block;
  short *bp;

  // receive data
  block = receiveWritable(0);
  if(block) {
    // call stuff
    bp = block->data;

    switch(currMethod) {
      // none, original, cepstrum, psola
      case autotuneMethod::none: {
        // do NOTHING
        break;
      }
      case autotuneMethod::original: {
        CustomAutoTune::autotuneOriginal(bp, 128);
        break;
      }
      case autotuneMethod::cepstrum: {
        CustomAutoTune::autotuneCepstrum(bp, 128);
        break;
      }
      case autotuneMethod::psola: {
        // TODO
        break;
      }
    } // switch
    transmit(block);
      release(block);
  } // if(block)
  return;
}

/*
 * Public Functions
 */
 // Pitch-Shift to Target Frequency
 void CustomAutoTune::pitchShift(float targetPitch, int16_t* micSignal, size_t signalLength) {
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
void CustomAutoTune::autotuneOriginal(int16_t* micSignal, size_t signalLength) {
    // Convert micSignal to float array
    for (size_t i = 0; i < signalLength; ++i) {
        myfftInput[i] = static_cast<float32_t>(micSignal[i]);
    }

    // Perform FFT
    arm_rfft_fast_f32(&fftConfig, myfftInput, myfftOutput, 0);

    // Find the main frequency
    uint32_t maxIndex;
    float32_t maxValue;
    arm_max_f32(myfftOutput, AUTOTUNE_FFT_SIZE, &maxValue, &maxIndex);
    size_t frequencyIndex = maxIndex;
    float mainFrequency = frequencyIndex * sample_rate / AUTOTUNE_FFT_SIZE;

    // Find the nearest semitone
    float nearestSemitone = shiftToNearestSemitone(mainFrequency);

    // Call pitchShift with the nearest semitone as targetPitch
    pitchShift(nearestSemitone, micSignal, signalLength);
}

// Cepstrum Domain Correction
void CustomAutoTune::autotuneCepstrum(int16_t* micSignal, size_t signalLength) {
    // Clone the micSignal for processing
    int16_t* newSignal = new int16_t[signalLength];
    memcpy(newSignal, micSignal, signalLength * sizeof(int16_t));

    // Convert micSignal to float array
    for (size_t i = 0; i < signalLength; ++i) {
        myfftInput[i] = static_cast<float32_t>(micSignal[i]);
    }

    // Perform FFT on the original signal and save the result
    float32_t originalFFTOutput[2 * AUTOTUNE_FFT_SIZE];
    arm_rfft_fast_f32(&fftConfig, myfftInput, originalFFTOutput, 0);


    // Create newSignal using basic autotune function
    CustomAutoTune::autotuneOriginal(newSignal, signalLength);

    // Convert newSignal to float array
    for (size_t i = 0; i < signalLength; ++i) {
        myfftInput[i] = static_cast<float32_t>(newSignal[i]);
    }

    // Perform FFT on the shifted signal
    arm_rfft_fast_f32(&fftConfig, myfftInput, myfftOutput, 0);

    // Calculate cepstrum of the original and shifted signals
    float32_t cepstrum1[AUTOTUNE_FFT_SIZE];
    float32_t cepstrum2[AUTOTUNE_FFT_SIZE];
    // Find the cepstrum of the original and shifted chunks
    for (size_t i = 0; i < AUTOTUNE_FFT_SIZE; ++i) {
        cepstrum1[i] = log(1e-9 + abs(originalFFTOutput[i]));
        cepstrum2[i] = log(1e-9 + abs(myfftOutput[i]));
    }

    // Cut the cepstrum to get only 50 indexes in the middle
    size_t middle = (AUTOTUNE_FFT_SIZE - 50) / 2;
    float32_t cut_original[50];
    float32_t cut_shifted[50];
    arm_copy_f32(&cepstrum1[middle], cut_original, 50);
    arm_copy_f32(&cepstrum2[middle], cut_shifted, 50);

    // Extract the envelope from the cut window
    float32_t envelope1[AUTOTUNE_FFT_SIZE];
    float32_t envelope2[AUTOTUNE_FFT_SIZE];
    arm_cmplx_mag_f32(cut_original, envelope1, 50);
    arm_cmplx_mag_f32(cut_shifted, envelope2, 50);

    // Find the correction factor from the two envelopes
    float32_t correction_factor[AUTOTUNE_FFT_SIZE];
    for (size_t i = 0; i < AUTOTUNE_FFT_SIZE; ++i) {
        correction_factor[i] = envelope1[i] / envelope2[i];
    }

    // Perform linear interpolation so that correction_factor matches myfftOutput
    // TODO

    // Apply correction to the shifted signal
    arm_mult_f32(myfftOutput, correction_factor, myfftOutput, AUTOTUNE_FFT_SIZE);

    // Perform IFFT
    arm_rfft_fast_f32(&fftConfig, myfftOutput, myfftInput, 1);

    // Copy the result back to micSignal
    for (size_t i = 0; i < signalLength; ++i) {
        micSignal[i] = static_cast<int16_t>(myfftInput[i]);
    }

    // Clean up
    delete[] newSignal;
}

// PSOLA Method
void CustomAutoTune::autotunePSOLA(int16_t* micSignal, size_t signalLength) {
    // PSOLA autotune implementation
    // ...
}

/*
 * Private Functions
 */
float CustomAutoTune::shiftToNearestSemitone(float noteFrequency) {
    // Calculate the nearest semitone frequency
    noteFrequency = max(noteFrequency, 1e-9); // Ensure noteFrequency is not zero
    int nearestSemitone = round(12 * log2(noteFrequency / 440));
    float nearestFrequency = 440 * pow(2, nearestSemitone / 12.0);
    return nearestFrequency;
}