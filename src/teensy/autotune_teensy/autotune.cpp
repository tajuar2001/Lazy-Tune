#include "autotune.h"

/*  COMMENTS FOR POTENTIAL FIXES
 - use arm_cfft_f32 instead of rfft.
 - try to do operations fully in 16 bit integers, or look into making more careful sure that you are not accidentally overflowing when converting values.
*/

// option selector
boolean CustomAutoTune::option_edit(autotuneMethod method) {
  boolean all_ok = true;
  if(all_ok) {
    Serial.println("Edit AutoTune");
    Serial.print("option = ");
    switch(method) {
      // none, original, cepstrum, psola
      case autotuneMethod::none: {
        Serial.println("none");
        break;
      }
      case autotuneMethod::original: {
        Serial.println("original");
        break;
      }
      case autotuneMethod::cepstrum: {
        Serial.println("cepstrum");
        break;
      }
      case autotuneMethod::psola: {
        Serial.println("psola");
        break;
      }
      case autotuneMethod::manual: {
        Serial.println("manual");
        break;
      }
    } // switch
  }

  currMethod = method;

  return all_ok;
}

// main update function
void CustomAutoTune::update(void) {
  audio_block_t *block;
  short* bp;

  // receive data
  block = receiveWritable(0);
  if(block) {
    // call stuff
    float32_t* floatInput = new float32_t[AUDIO_BLOCK_SAMPLES];
    bp = block->data;

    // convert input to floats with proper scaling
    for (size_t i = 0; i < AUDIO_BLOCK_SAMPLES; ++i) {
        floatInput[i] = bp[i] / 32768.0f; // Convert 16-bit int to float
    }
    
    switch(currMethod) {
      // none, original, cepstrum, psola
      case autotuneMethod::none: {
        // do NOTHING
        break;
      }
      case autotuneMethod::original: {
        CustomAutoTune::autotuneOriginal(floatInput, AUDIO_BLOCK_SAMPLES);
        break;
      }
      case autotuneMethod::cepstrum: {
        CustomAutoTune::autotuneCepstrum(floatInput, AUDIO_BLOCK_SAMPLES);
        break;
      }
      case autotuneMethod::psola: {
        // TODO
        // CustomAutoTune::autotunePSOLA(inputBuffer, outputBuffer, BUFFER_SIZE, 0.5); // Pitch shift down by a factor of 0.5
        // for(int i=0; i<AUDIO_BLOCK_SAMPLES; i++){
        // floatInput[i] = outputBuffer[i];
        // }
        break;
      }
      case autotuneMethod::manual: {
        CustomAutoTune::autotuneManualMode(floatInput, AUDIO_BLOCK_SAMPLES);
        break;
      }
    } // switch

  // Convert the processed float32 signal back to the original array
  // and scale back to int16
  for (size_t i = 0; i < AUDIO_BLOCK_SAMPLES; ++i) {
      bp[i] = static_cast<int16_t>(floatInput[i] * 32767.0f); // Convert back to 16-bit int
  }
    transmit(block);
    release(block);
    delete[] floatInput;
  } // if(block)

  return;
}

/*
 * Public Functions
 */
 float CustomAutoTune::shiftToNearestSemitone(float noteFrequency) {
  Serial.println("shifttonearestsemitone");
    // Calculate the nearest semitone frequency
    noteFrequency = max(noteFrequency, 1e-9); // Ensure noteFrequency is not zero
    int nearestSemitone = round(12 * log2(noteFrequency / 440));
    float nearestFrequency = 440 * pow(2, nearestSemitone / 12.0);
    return nearestFrequency;
}

 // Pitch-Shift to Target Frequency
void CustomAutoTune::pitchShift(float targetPitch, float32_t*& micSignal, size_t signalLength) {
    // Calculate the current pitch of the input signal
    float currentPitch = calculatePitch(micSignal, signalLength);
    Serial.print("currentPitch = ");
    Serial.println(currentPitch);
    // Calculate the pitch shift factor based on the target and current pitch
    float pitchShiftFactor = std::pow(2.0f, (targetPitch - currentPitch) / 12.0f);

    // Calculate the adjusted pitch shift factor for time-domain pitch shifting
    float adjustedPitchShiftFactor = static_cast<float>(signalLength) / static_cast<float>(signalLength - pitchShiftFactor);

    // Create an array to store the pitch-shifted signal
    float32_t* pitchShiftedSignal = new float32_t[signalLength];

    // TOD0: Don't pitch shift
    // // Perform pitch shifting using linear interpolation with adjusted pitch shift factor
    interpolate(micSignal, signalLength, pitchShiftedSignal, signalLength, adjustedPitchShiftFactor);

    // Copy the pitch-shifted signal back to the original array
    std::copy(pitchShiftedSignal, pitchShiftedSignal + signalLength, micSignal);

    // Clean up allocated memory
    delete[] pitchShiftedSignal;
}

// Autotune Manual: Pitch-Shift to Preset Target
void CustomAutoTune::autotuneManualMode(float32_t*& micSignal, size_t signalLength) {
  Serial.println(manualFrequency);
  pitchShift(manualFrequency, micSignal, signalLength);
}

// Autotune Original: Pitch-Shift to Nearest Frequency
void CustomAutoTune::autotuneOriginal(float32_t*& micSignal, size_t signalLength) {
  Serial.println("original");
  float mainFrequency = calculatePitch(micSignal, signalLength);

  // Find the nearest semitone
  float nearestSemitone = shiftToNearestSemitone(mainFrequency);
  // Call pitchShift with the nearest semitone as targetPitch
  pitchShift(nearestSemitone, micSignal, signalLength);
}

// Cepstrum Domain Correction
void CustomAutoTune::autotuneCepstrum(float32_t*& micSignal, size_t signalLength) {
  Serial.println("cepstrum");
    // Clone the micSignal for processing
    float32_t* newSignal = new float32_t[signalLength];
    memcpy(newSignal, micSignal, signalLength * sizeof(float32_t));

    // Convert micSignal to float array
    for (size_t i = 0; i < signalLength; ++i) {
        myfftInput[i] = (micSignal[i]);
    }
    for(size_t i = signalLength; i < AUTOTUNE_FFT_SIZE; ++i) {
        myfftInput[i] = 0;
    }

    // Perform FFT on the original signal and save the result
    float32_t originalFFTOutput[2 * AUTOTUNE_FFT_SIZE];
    arm_rfft_fast_f32(&fftConfig, myfftInput, originalFFTOutput, 0);


    // Create newSignal using basic autotune function
    CustomAutoTune::autotuneOriginal(newSignal, signalLength);

    // Convert newSignal to float array
    for (size_t i = 0; i < signalLength; ++i) {
        myfftInput[i] = (newSignal[i]);
    }

    // Perform FFT on the shifted signal
    arm_rfft_fast_f32(&fftConfig, myfftInput, myfftOutput, 0);

    // Calculate cepstrum of the original and shifted signals
    float32_t cepstrum1[2*AUTOTUNE_FFT_SIZE];
    float32_t cepstrum2[2*AUTOTUNE_FFT_SIZE];
    // Find the cepstrum of the original and shifted chunks
    for (size_t i = 0; i < 2*AUTOTUNE_FFT_SIZE; ++i) {
        cepstrum1[i] = log(1e-9 + abs(originalFFTOutput[i]));
        cepstrum2[i] = log(1e-9 + abs(myfftOutput[i]));
    }

    // Cut the cepstrum to get only 50 indexes in the middle
    size_t middle = (2*AUTOTUNE_FFT_SIZE - 50) / 2;
    float32_t cut_original[50];
    float32_t cut_shifted[50];
    arm_copy_f32(&cepstrum1[middle], cut_original, 50);
    arm_copy_f32(&cepstrum2[middle], cut_shifted, 50);

    // Extract the envelope from the cut window
    float32_t envelope1[2*AUTOTUNE_FFT_SIZE];
    float32_t envelope2[2*AUTOTUNE_FFT_SIZE];
    arm_cmplx_mag_f32(cut_original, envelope1, 50);
    arm_cmplx_mag_f32(cut_shifted, envelope2, 50);

    // Find the correction factor from the two envelopes
    float32_t correction_factor[2*AUTOTUNE_FFT_SIZE];
    for (size_t i = 0; i < 2*AUTOTUNE_FFT_SIZE; ++i) {
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
        micSignal[i] = (myfftInput[i]);
    }

    // Clean up
    delete[] newSignal;
}

// PSOLA Method
void CustomAutoTune::autotunePSOLA(int* input, int Fs, float inputPitch, float desiredPitch) {
    Serial.println("psola");
  // Percent change of frequency
    float scalingFactor = 1 + (inputPitch - desiredPitch)/desiredPitch;
    // PSOLA constants
    int analysisShift = ceil(Fs/inputPitch);
    int analysisShiftHalfed = round(analysisShift/2);
    int synthesisShift = round(analysisShift*scalingFactor);
    int analysisIndex = -1;
    int synthesisIndex = 0;
    int analysisBlockStart;
    int analysisBlockEnd;
    int synthesisBlockEnd;
    int analysisLimit = _bufferLen - analysisShift - 1;
    // Window declaration
    int winLength = analysisShift + analysisShiftHalfed + 1;
    int windowIndex;
    bartlett(_window,winLength);
    // PSOLA Algorithm
    while (analysisIndex < analysisLimit) {
        // Analysis blocks are two pitch periods long
        analysisBlockStart = (analysisIndex + 1) - analysisShiftHalfed;
        if (analysisBlockStart < 0) {
            analysisBlockStart = 0;
        }
        analysisBlockEnd = analysisBlockStart + analysisShift + analysisShiftHalfed;
        if (analysisBlockEnd > _bufferLen - 1) {
            analysisBlockEnd = _bufferLen - 1;
        }
        // Overlap and add
        synthesisBlockEnd = synthesisIndex + analysisBlockEnd - analysisBlockStart;
        int inputIndex = analysisBlockStart;
        int windowIndex = 0;
        for (int j = synthesisIndex; j <= synthesisBlockEnd; j++) {
            _buffer[j] = Q15addWrap(_buffer[j], Q15mult(input[inputIndex],_window[windowIndex]) );
            inputIndex++;
            windowIndex++;
        }
        // Update pointers
        analysisIndex += analysisShift;
        synthesisIndex += synthesisShift;
    }
    // Write back to input
    for (int i = 0; i < _bufferLen; i++) {
        input[i] = _buffer[i];
        // clean out the buffer
        _buffer[i] = 0;
    }
}

void CustomAutoTune::bartlett(int* window, int length) {
    if (length < 1) return;
    if (length == 1) {
        window[0] = 1;
        return;
    }
    
    int N = length - 1;
    int middle = N >> 1;
    int slope = round( ((float)(1<<(FIXED_FBITS-1)))/N*4 );
    if (N%2 == 0) {
        // N even = L odd
        window[0] = 0;
        for (int i = 1; i <= middle; i++) {
            window[i] = window[i-1] + slope;
        }
        for (int i = middle+1; i <= N; i++) {
            window[i] = window[N - i];
        }
        // double check that the middle value is the maximum Q15 number
        window[middle] = LARGEST_Q15_NUM;
    } else {
        // N odd = L even
        window[0] = 0;
        for (int i = 1; i <= middle; i++) {
            window[i] = window[i-1] + slope;
        }
        window[middle + 1] = window[middle];
        for (int i = middle+1; i <= N; i++) {
            window[i] = window[N - i];
        }
    }
}

/*
  Private Functions
*/
void CustomAutoTune::interpolate(float32_t* input, size_t inLength, float32_t* output, size_t outLength, float factor) {
    for (size_t i = 0; i < outLength; ++i) {
        float index = i * factor;
        size_t floorIndex = static_cast<size_t>(std::floor(index));
        size_t ceilIndex = std::min(floorIndex + 1, inLength - 1);

        float alpha = index - floorIndex;
        output[i] = (1 - alpha) * input[floorIndex] + alpha * input[ceilIndex];
    }
}

float CustomAutoTune::calculatePitch(float32_t* signal, size_t signalLength) {
    // Create an array to store the FFT output
    float32_t fftOutput[AUTOTUNE_FFT_SIZE];

    // Perform FFT
    arm_rfft_fast_f32(&fftConfig, signal, fftOutput, 0);

    // Find the index of the maximum magnitude in the FFT output
    uint32_t maxIndex;
    float32_t maxValue;
    arm_max_f32(fftOutput, AUTOTUNE_FFT_SIZE, &maxValue, &maxIndex);

    // Calculate the corresponding frequency in Hertz
    float pitch = static_cast<float>(maxIndex) * AUTOTUNE_SAMPLING_RATE / AUTOTUNE_FFT_SIZE;

    return pitch;
}