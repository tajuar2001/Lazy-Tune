#include "autotune.h"

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
     //Serial.printf("Note: %3.2f\n", currFrequency);
    // call stuff
    float floatInput[AUDIO_BLOCK_SAMPLES];
    bp = block->data;

    // convert input to floats with proper scaling
    for (size_t i = 0; i < AUDIO_BLOCK_SAMPLES; ++i) {
        floatInput[i] = (float)((float)bp[i])/(INT_MAX);
    }
    
    switch(currMethod) {
      // none, original, cepstrum, psola
      case autotuneMethod::none: {
        // do NOTHING
        break;
      }
      case autotuneMethod::original: {
        CustomAutoTune::autotuneOriginal(floatInput);
        break;
      }
      case autotuneMethod::cepstrum: {
        //CustomAutoTune::autotuneCepstrum(floatInput, AUDIO_BLOCK_SAMPLES);
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
    } // switch

  // Convert the processed float32 signal back to the original array
  // and scale back to int16
  for (size_t i = 0; i < AUDIO_BLOCK_SAMPLES; ++i) {
      bp[i] = (int16_t)(floatInput[i] * INT_MAX); // Convert back to 16-bit int
  }
    transmit(block);
    release(block);
  } // if(block)

  return;
}

/*
 * Public Functions
 */
 float CustomAutoTune::computeNearestSemitone(float noteFrequency) {
    // Calculate the nearest semitone frequency
    int nearestSemitone = round(12 * log2((noteFrequency + 1e-9) / 440));
    float nearestFrequency = 440 * pow(2, nearestSemitone / 12.0);
    return nearestFrequency;
}

 // Pitch-Shift to Target Frequency
void CustomAutoTune::pitchShift(float targetPitch, float* indata, float* outdata) {
    // Calculate the pitch shift factor based on the target and current frequency
    float pitchShift = targetPitch / currFrequency;
    pitchShift = (pitchShift < 0.6) ? 0.6 : ((pitchShift > 1.9) ? 1.9 : pitchShift);
    long numSampsToProcess = AUDIO_BLOCK_SAMPLES;
    long fftFrameSize = AUTOTUNE_FFT_SIZE;
    long osamp = 4;
    float sampleRate = 44100;

  static float gInFIFO[MAX_FRAME_LENGTH];
  static float gOutFIFO[MAX_FRAME_LENGTH];
  static float gFFTworksp[2*MAX_FRAME_LENGTH];
  static float gLastPhase[MAX_FRAME_LENGTH/2+1];
  static float gSumPhase[MAX_FRAME_LENGTH/2+1];
  static float gOutputAccum[2*MAX_FRAME_LENGTH];
  static float gAnaFreq[MAX_FRAME_LENGTH];
  static float gAnaMagn[MAX_FRAME_LENGTH];
  static float gSynFreq[MAX_FRAME_LENGTH];
  static float gSynMagn[MAX_FRAME_LENGTH];
  static long gRover = false, gInit = false;
  double magn, phase, tmp, window, real, imag;
  double freqPerBin, expct;
  long i,k, qpd, index, inFifoLatency, stepSize, fftFrameSize2;

  /* set up some handy variables */
  fftFrameSize2 = fftFrameSize/2;
  stepSize = fftFrameSize/osamp;
  freqPerBin = sampleRate/(double)fftFrameSize;
  expct = 2.*M_PI*(double)stepSize/(double)fftFrameSize;
  inFifoLatency = fftFrameSize-stepSize;
  if (gRover == false) gRover = inFifoLatency;

  /* initialize our static arrays */
  if (gInit == false) {
    memset(gInFIFO, 0, MAX_FRAME_LENGTH*sizeof(float));
    memset(gOutFIFO, 0, MAX_FRAME_LENGTH*sizeof(float));
    memset(gFFTworksp, 0, 2*MAX_FRAME_LENGTH*sizeof(float));
    memset(gLastPhase, 0, (MAX_FRAME_LENGTH/2+1)*sizeof(float));
    memset(gSumPhase, 0, (MAX_FRAME_LENGTH/2+1)*sizeof(float));
    memset(gOutputAccum, 0, 2*MAX_FRAME_LENGTH*sizeof(float));
    memset(gAnaFreq, 0, MAX_FRAME_LENGTH*sizeof(float));
    memset(gAnaMagn, 0, MAX_FRAME_LENGTH*sizeof(float));
    gInit = true;
  }

  /* main processing loop */
  for (i = 0; i < numSampsToProcess; i++){

    /* As long as we have not yet collected enough data just read in */
    gInFIFO[gRover] = indata[i];
    outdata[i] = gOutFIFO[gRover-inFifoLatency];
    gRover++;

    /* now we have enough data for processing */
    if (gRover >= fftFrameSize) {
      gRover = inFifoLatency;

      /* do windowing and re,im interleave */
      for (k = 0; k < fftFrameSize;k++) {
        window = -.5*cos(2.*M_PI*(double)k/(double)fftFrameSize)+.5;
        gFFTworksp[2*k] = gInFIFO[k] * window;
        gFFTworksp[2*k+1] = 0.;
      }


      /* ***************** ANALYSIS ******************* */
      /* do transform */
      smbFft(gFFTworksp, fftFrameSize, -1);

      /* this is the analysis step */
      for (k = 0; k <= fftFrameSize2; k++) {

        /* de-interlace FFT buffer */
        real = gFFTworksp[2*k];
        imag = gFFTworksp[2*k+1];

        /* compute magnitude and phase */
        magn = 2.*sqrt(real*real + imag*imag);
        phase = smbAtan2(imag,real);

        /* compute phase difference */
        tmp = phase - gLastPhase[k];
        gLastPhase[k] = phase;

        /* subtract expected phase difference */
        tmp -= (double)k*expct;

        /* map delta phase into +/- Pi interval */
        qpd = tmp/M_PI;
        if (qpd >= 0) qpd += qpd&1;
        else qpd -= qpd&1;
        tmp -= M_PI*(double)qpd;

        /* get deviation from bin frequency from the +/- Pi interval */
        tmp = osamp*tmp/(2.*M_PI);

        /* compute the k-th partials' true frequency */
        tmp = (double)k*freqPerBin + tmp*freqPerBin;

        /* store magnitude and true frequency in analysis arrays */
        gAnaMagn[k] = magn;
        gAnaFreq[k] = tmp;

      }

      /* ***************** PROCESSING ******************* */
      /* this does the actual pitch shifting */
      memset(gSynMagn, 0, fftFrameSize*sizeof(float));
      memset(gSynFreq, 0, fftFrameSize*sizeof(float));
      for (k = 0; k <= fftFrameSize2; k++) { 
        index = k*pitchShift;
        if (index <= fftFrameSize2) { 
          gSynMagn[index] += gAnaMagn[k]; 
          gSynFreq[index] = gAnaFreq[k] * pitchShift; 
        } 
      }
      
      /* ***************** SYNTHESIS ******************* */
      /* this is the synthesis step */
      for (k = 0; k <= fftFrameSize2; k++) {

        /* get magnitude and true frequency from synthesis arrays */
        magn = gSynMagn[k];
        tmp = gSynFreq[k];

        /* subtract bin mid frequency */
        tmp -= (double)k*freqPerBin;

        /* get bin deviation from freq deviation */
        tmp /= freqPerBin;

        /* take osamp into account */
        tmp = 2.*M_PI*tmp/osamp;

        /* add the overlap phase advance back in */
        tmp += (double)k*expct;

        /* accumulate delta phase to get bin phase */
        gSumPhase[k] += tmp;
        phase = gSumPhase[k];

        /* get real and imag part and re-interleave */
        gFFTworksp[2*k] = magn*cos(phase);
        gFFTworksp[2*k+1] = magn*sin(phase);
      } 

      /* zero negative frequencies */
      for (k = fftFrameSize+2; k < 2*fftFrameSize; k++) gFFTworksp[k] = 0.;

      /* do inverse transform */
      smbFft(gFFTworksp, fftFrameSize, 1);

      /* do windowing and add to output accumulator */ 
      for(k=0; k < fftFrameSize; k++) {
        window = -.5*cos(2.*M_PI*(double)k/(double)fftFrameSize)+.5;
        gOutputAccum[k] += 2.*window*gFFTworksp[2*k]/(fftFrameSize2*osamp);
      }
      for (k = 0; k < stepSize; k++) gOutFIFO[k] = gOutputAccum[k];

      /* shift accumulator */
      memmove(gOutputAccum, gOutputAccum+stepSize, fftFrameSize*sizeof(float));

      /* move input FIFO */
      for (k = 0; k < inFifoLatency; k++) gInFIFO[k] = gInFIFO[k+stepSize];
    }
  }
}

// -------------------------------



void smbFft(float *fftBuffer, long fftFrameSize, long sign) {
  float wr, wi, arg, *p1, *p2, temp;
  float tr, ti, ur, ui, *p1r, *p1i, *p2r, *p2i;
  long i, bitm, j, le, le2, k;

  for (i = 2; i < 2*fftFrameSize-2; i += 2) {
    for (bitm = 2, j = 0; bitm < 2*fftFrameSize; bitm <<= 1) {
      if (i & bitm) j++;
      j <<= 1;
    }
    if (i < j) {
      p1 = fftBuffer+i; p2 = fftBuffer+j;
      temp = *p1; *(p1++) = *p2;
      *(p2++) = temp; temp = *p1;
      *p1 = *p2; *p2 = temp;
    }
  }
  for (k = 0, le = 2; k < (long)(log(fftFrameSize)/log(2.)+.5); k++) {
    le <<= 1;
    le2 = le>>1;
    ur = 1.0;
    ui = 0.0;
    arg = M_PI / (le2>>1);
    wr = cos(arg);
    wi = sign*sin(arg);
    for (j = 0; j < le2; j += 2) {
      p1r = fftBuffer+j; p1i = p1r+1;
      p2r = p1r+le2; p2i = p2r+1;
      for (i = j; i < 2*fftFrameSize; i += le) {
        tr = *p2r * ur - *p2i * ui;
        ti = *p2r * ui + *p2i * ur;
        *p2r = *p1r - tr; *p2i = *p1i - ti;
        *p1r += tr; *p1i += ti;
        p1r += le; p1i += le;
        p2r += le; p2i += le;
      }
      tr = ur*wr - ui*wi;
      ui = ur*wi + ui*wr;
      ur = tr;
    }
  }
}

double smbAtan2(double x, double y)
{
  double signx;
  if (x > 0.) signx = 1.;  
  else signx = -1.;
  
  if (x == 0.) return 0.;
  if (y == 0.) return signx * M_PI / 2.;
  
  return atan2(x, y);
}

// -------------------------------

// Autotune Original: Pitch-Shift to Nearest Frequency
void CustomAutoTune::autotuneOriginal(float* micSignal) {
  Serial.println("autotune");
  // Find the nearest semitone
  float nearestSemitone = computeNearestSemitone(currFrequency);
  // Call pitchShift with the nearest semitone as targetPitch
  pitchShift(nearestSemitone, &micSignal[0], &micSignal[0]);
}

// Cepstrum Domain Correction
void CustomAutoTune::autotuneCepstrum(float32_t* micSignal, size_t signalLength) {
  Serial.println("cepstrum");
    // // Clone the micSignal for processing
    // float32_t* newSignal = new float32_t[signalLength];
    // memcpy(newSignal, micSignal, signalLength * sizeof(float32_t));

    // // Convert micSignal to float array
    // for (size_t i = 0; i < signalLength; ++i) {
    //     myfftInput[i] = (micSignal[i]);
    // }
    // for(size_t i = signalLength; i < AUTOTUNE_FFT_SIZE; ++i) {
    //     myfftInput[i] = 0;
    // }

    // // Perform FFT on the original signal and save the result
    // float32_t originalFFTOutput[2 * AUTOTUNE_FFT_SIZE];
    // arm_rfft_fast_f32(&fftConfig, myfftInput, originalFFTOutput, 0);


    // // Create newSignal using basic autotune function
    // CustomAutoTune::autotuneOriginal(newSignal, signalLength);

    // // Convert newSignal to float array
    // for (size_t i = 0; i < signalLength; ++i) {
    //     myfftInput[i] = (newSignal[i]);
    // }

    // // Perform FFT on the shifted signal
    // arm_rfft_fast_f32(&fftConfig, myfftInput, myfftOutput, 0);

    // // Calculate cepstrum of the original and shifted signals
    // float32_t cepstrum1[2*AUTOTUNE_FFT_SIZE];
    // float32_t cepstrum2[2*AUTOTUNE_FFT_SIZE];
    // // Find the cepstrum of the original and shifted chunks
    // for (size_t i = 0; i < 2*AUTOTUNE_FFT_SIZE; ++i) {
    //     cepstrum1[i] = log(1e-9 + abs(originalFFTOutput[i]));
    //     cepstrum2[i] = log(1e-9 + abs(myfftOutput[i]));
    // }

    // // Cut the cepstrum to get only 50 indexes in the middle
    // size_t middle = (2*AUTOTUNE_FFT_SIZE - 50) / 2;
    // float32_t cut_original[50];
    // float32_t cut_shifted[50];
    // arm_copy_f32(&cepstrum1[middle], cut_original, 50);
    // arm_copy_f32(&cepstrum2[middle], cut_shifted, 50);

    // // Extract the envelope from the cut window
    // float32_t envelope1[2*AUTOTUNE_FFT_SIZE];
    // float32_t envelope2[2*AUTOTUNE_FFT_SIZE];
    // arm_cmplx_mag_f32(cut_original, envelope1, 50);
    // arm_cmplx_mag_f32(cut_shifted, envelope2, 50);

    // // Find the correction factor from the two envelopes
    // float32_t correction_factor[2*AUTOTUNE_FFT_SIZE];
    // for (size_t i = 0; i < 2*AUTOTUNE_FFT_SIZE; ++i) {
    //     correction_factor[i] = envelope1[i] / envelope2[i];
    // }

    // // Perform linear interpolation so that correction_factor matches myfftOutput
    // // TODO

    // // Apply correction to the shifted signal
    // arm_mult_f32(myfftOutput, correction_factor, myfftOutput, AUTOTUNE_FFT_SIZE);

    // // Perform IFFT
    // arm_rfft_fast_f32(&fftConfig, myfftOutput, myfftInput, 1);

    // // Copy the result back to micSignal
    // for (size_t i = 0; i < signalLength; ++i) {
    //     micSignal[i] = (myfftInput[i]);
    // }

    // // Clean up
    // delete[] newSignal;
}

// PSOLA Method
void CustomAutoTune::autotunePSOLA(int* input, int Fs, float inputPitch, float desiredPitch) {
    Serial.println("psola");
  // // Percent change of frequency
  //   float scalingFactor = 1 + (inputPitch - desiredPitch)/desiredPitch;
  //   // PSOLA constants
  //   int analysisShift = ceil(Fs/inputPitch);
  //   int analysisShiftHalfed = round(analysisShift/2);
  //   int synthesisShift = round(analysisShift*scalingFactor);
  //   int analysisIndex = -1;
  //   int synthesisIndex = 0;
  //   int analysisBlockStart;
  //   int analysisBlockEnd;
  //   int synthesisBlockEnd;
  //   int analysisLimit = _bufferLen - analysisShift - 1;
  //   // Window declaration
  //   int winLength = analysisShift + analysisShiftHalfed + 1;
  //   int windowIndex;
  //   bartlett(_window,winLength);
  //   // PSOLA Algorithm
  //   while (analysisIndex < analysisLimit) {
  //       // Analysis blocks are two pitch periods long
  //       analysisBlockStart = (analysisIndex + 1) - analysisShiftHalfed;
  //       if (analysisBlockStart < 0) {
  //           analysisBlockStart = 0;
  //       }
  //       analysisBlockEnd = analysisBlockStart + analysisShift + analysisShiftHalfed;
  //       if (analysisBlockEnd > _bufferLen - 1) {
  //           analysisBlockEnd = _bufferLen - 1;
  //       }
  //       // Overlap and add
  //       synthesisBlockEnd = synthesisIndex + analysisBlockEnd - analysisBlockStart;
  //       int inputIndex = analysisBlockStart;
  //       int windowIndex = 0;
  //       for (int j = synthesisIndex; j <= synthesisBlockEnd; j++) {
  //           _buffer[j] = Q15addWrap(_buffer[j], Q15mult(input[inputIndex],_window[windowIndex]) );
  //           inputIndex++;
  //           windowIndex++;
  //       }
  //       // Update pointers
  //       analysisIndex += analysisShift;
  //       synthesisIndex += synthesisShift;
  //   }
  //   // Write back to input
  //   for (int i = 0; i < _bufferLen; i++) {
  //       input[i] = _buffer[i];
  //       // clean out the buffer
  //       _buffer[i] = 0;
  //   }
}

// void CustomAutoTune::bartlett(int* window, int length) {
//     if (length < 1) return;
//     if (length == 1) {
//         window[0] = 1;
//         return;
//     }
    
//     int N = length - 1;
//     int middle = N >> 1;
//     int slope = round( ((float)(1<<(FIXED_FBITS-1)))/N*4 );
//     if (N%2 == 0) {
//         // N even = L odd
//         window[0] = 0;
//         for (int i = 1; i <= middle; i++) {
//             window[i] = window[i-1] + slope;
//         }
//         for (int i = middle+1; i <= N; i++) {
//             window[i] = window[N - i];
//         }
//         // double check that the middle value is the maximum Q15 number
//         window[middle] = LARGEST_Q15_NUM;
//     } else {
//         // N odd = L even
//         window[0] = 0;
//         for (int i = 1; i <= middle; i++) {
//             window[i] = window[i-1] + slope;
//         }
//         window[middle + 1] = window[middle];
//         for (int i = middle+1; i <= N; i++) {
//             window[i] = window[N - i];
//         }
//     }
// }