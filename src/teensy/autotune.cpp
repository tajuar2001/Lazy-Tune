#include "autotune.h"

void CustomAutoTune::update(void) {
    audio_block_t *block;

    // receive data
    block = receiveWritable(0);
    if (block) {
        float floatInput[AUDIO_BLOCK_SAMPLES];

        // Convert input to floats with scaling
        for (size_t i = 0; i < AUDIO_BLOCK_SAMPLES; ++i) {
            floatInput[i] = (float)((float)block->data[i]) / (INT_MAX);
        }
        
        pitchShift(computeNearestSemitone(currFrequency), &floatInput[0], &floatInput[0]);

        // Convert processed signal back to int16
        for (size_t i = 0; i < AUDIO_BLOCK_SAMPLES; ++i) {
            block->data[i] = (int16_t)(floatInput[i] * INT_MAX);
        }
        transmit(block);
        release(block);
    }
}


// Public Functions

 float CustomAutoTune::computeNearestSemitone(float noteFrequency) {
    // Calculate the nearest semitone frequency
    int nearestSemitone = round(12.0 * log2((noteFrequency + 1e-9) / 440));
    float nearestFrequency = 440 * pow(2, nearestSemitone / 12.0);
    return nearestFrequency;
}

  DMAMEM static float gInFIFO[MAX_FRAME_LENGTH];
  DMAMEM static float gOutFIFO[MAX_FRAME_LENGTH];
  DMAMEM static float gFFTworksp[2*MAX_FRAME_LENGTH];
  DMAMEM static float gLastPhase[MAX_FRAME_LENGTH/2+1];
  DMAMEM static float gSumPhase[MAX_FRAME_LENGTH/2+1];
  DMAMEM static float gOutputAccum[2*MAX_FRAME_LENGTH];
  DMAMEM static float gAnaFreq[MAX_FRAME_LENGTH];
  DMAMEM static float gAnaMagn[MAX_FRAME_LENGTH];
  DMAMEM static float gSynFreq[MAX_FRAME_LENGTH];
  DMAMEM static float gSynMagn[MAX_FRAME_LENGTH];

 // Pitch-Shift to Target Frequency
void CustomAutoTune::pitchShift(float targetPitch, float* indata, float* outdata) {

    // Calculate the pitch shift factor based on the target and current frequency
    float pitchShift = targetPitch / currFrequency + manualPitchOffset;
    pitchShift = (pitchShift < 0.51) ? 0.51 : ((pitchShift > 1.99) ? 1.99 : pitchShift);
    long overlap_samples = 4; 

  static long gRover = false, gInit = false;
  double magn, phase, tmp, window, real, imag;
  double freqPerBin, expct;
  long i,k, qpd, index, inFifoLatency, stepSize, fftFrameSize2;

  fftFrameSize2 = AUTOTUNE_FFT_SIZE/2;
  stepSize = AUTOTUNE_FFT_SIZE/overlap_samples;
  freqPerBin = AUTOTUNE_SAMPLING_RATE/(double)AUTOTUNE_FFT_SIZE;
  expct = 2.*M_PI*(double)stepSize/(double)AUTOTUNE_FFT_SIZE;
  inFifoLatency = AUTOTUNE_FFT_SIZE-stepSize;

  if (gRover == false) gRover = inFifoLatency;
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

  /* main loop */
  for (i = 0; i < AUDIO_BLOCK_SAMPLES; i++){

    gInFIFO[gRover] = indata[i];
    outdata[i] = gOutFIFO[gRover-inFifoLatency];
    gRover++;

    if (gRover >= AUTOTUNE_FFT_SIZE) {
      gRover = inFifoLatency;

      for (k = 0; k < AUTOTUNE_FFT_SIZE;k++) {
        window = -.5*cos(2.*M_PI*(double)k/(double)AUTOTUNE_FFT_SIZE)+.5;
        gFFTworksp[2*k] = gInFIFO[k] * window;
        gFFTworksp[2*k+1] = 0.;
      }

      /* analysis */
      autoFFT(gFFTworksp, AUTOTUNE_FFT_SIZE, -1);

      for (k = 0; k <= fftFrameSize2; k++) {

        /* de-interlace FFT buffer */
        real = gFFTworksp[2*k];
        imag = gFFTworksp[2*k+1];

        /* compute magnitude and phase */
        magn = 2.*sqrt(real*real + imag*imag);
        phase = autoAtan2(imag,real);

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
        tmp = overlap_samples*tmp/(2.*M_PI);

        /* compute the k-th partials' true frequency */
        tmp = (double)k*freqPerBin + tmp*freqPerBin;

        /* store magnitude and true frequency in analysis arrays */
        gAnaMagn[k] = magn;
        gAnaFreq[k] = tmp;

      }

      /* pitch shifting */
      memset(gSynMagn, 0, AUTOTUNE_FFT_SIZE*sizeof(float));
      memset(gSynFreq, 0, AUTOTUNE_FFT_SIZE*sizeof(float));
      for (k = 0; k <= fftFrameSize2; k++) { 
        index = k*pitchShift;
        if (index <= fftFrameSize2) { 
          gSynMagn[index] += gAnaMagn[k]; 
          gSynFreq[index] = gAnaFreq[k] * pitchShift; 
        } 
      }
      
      /* synthesis */
      for (k = 0; k <= fftFrameSize2; k++) {

        /* get magnitude and true frequency from synthesis arrays */
        magn = gSynMagn[k];
        tmp = gSynFreq[k];

        /* subtract bin mid frequency */
        tmp -= (double)k*freqPerBin;

        /* get bin deviation from freq deviation */
        tmp /= freqPerBin;

        /* take overlap_samples into account */
        tmp = 2.*M_PI*tmp/overlap_samples;

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
      for (k = AUTOTUNE_FFT_SIZE+2; k < 2*AUTOTUNE_FFT_SIZE; k++) gFFTworksp[k] = 0.;

      /* do inverse transform */
      autoFFT(gFFTworksp, AUTOTUNE_FFT_SIZE, 1);

      /* do windowing and add to output accumulator */ 
      for(k=0; k < AUTOTUNE_FFT_SIZE; k++) {
        window = -.5*cos(2.*M_PI*(double)k/(double)AUTOTUNE_FFT_SIZE)+.5;
        gOutputAccum[k] += 2.*window*gFFTworksp[2*k]/(fftFrameSize2*overlap_samples);
      }
      for (k = 0; k < stepSize; k++) gOutFIFO[k] = gOutputAccum[k];

      /* shift accumulator */
      memmove(gOutputAccum, gOutputAccum+stepSize, AUTOTUNE_FFT_SIZE*sizeof(float));

      /* move input FIFO */
      for (k = 0; k < inFifoLatency; k++) gInFIFO[k] = gInFIFO[k+stepSize];
    } // if

  } // for (main loop)

}

void CustomAutoTune::autoFFT(float *fftBuffer, long fftSize, long sign) {
    float cosineComponent, sineComponent, angle, *pointer1, *pointer2, temp;
    float realTemp, imagTemp, ur, ui, *realPart1, *imagPart1, *realPart2, *imagPart2;
    long i, bitMask, index, subFFTLength, halfSubFFTLength, iteration;

    // Rearrange the array elements by bit-reversing the indices
    for (i = 2; i < 2 * fftSize - 2; i += 2) {
        for (bitMask = 2, index = 0; bitMask < 2 * fftSize; bitMask <<= 1) {
            if (i & bitMask) index++;
            index <<= 1;
        }
        if (i < index) {
            pointer1 = fftBuffer + i; pointer2 = fftBuffer + index;
            temp = *pointer1; *pointer1++ = *pointer2;
            *pointer2++ = temp; temp = *pointer1;
            *pointer1 = *pointer2; *pointer2 = temp;
        }
    }

    // FFT computation using the Cooley-Tukey algorithm
    for (iteration = 0, subFFTLength = 2; iteration < (long)(log(fftSize) / log(2.0) + 0.5); iteration++) {
        subFFTLength <<= 1;
        halfSubFFTLength = subFFTLength >> 1;
        ur = 1.0;
        ui = 0.0;
        angle = M_PI / (halfSubFFTLength >> 1);
        cosineComponent = cos(angle);
        sineComponent = sign * sin(angle);
        for (index = 0; index < halfSubFFTLength; index += 2) {
            realPart1 = fftBuffer + index; imagPart1 = realPart1 + 1;
            realPart2 = realPart1 + halfSubFFTLength; imagPart2 = realPart2 + 1;
            for (i = index; i < 2 * fftSize; i += subFFTLength) {
                realTemp = *realPart2 * ur - *imagPart2 * ui;
                imagTemp = *realPart2 * ui + *imagPart2 * ur;
                *realPart2 = *realPart1 - realTemp; *imagPart2 = *imagPart1 - imagTemp;
                *realPart1 += realTemp; *imagPart1 += imagTemp;
                realPart1 += subFFTLength; imagPart1 += subFFTLength;
                realPart2 += subFFTLength; imagPart2 += subFFTLength;
            }
            realTemp = ur * cosineComponent - ui * sineComponent;
            ui = ur * sineComponent + ui * cosineComponent;
            ur = realTemp;
        }
    }
}


double CustomAutoTune::autoAtan2(double x, double y) {
    // Handle edge cases directly
    if (x == 0.0) return 0.0;
    if (y == 0.0) return x > 0.0 ? M_PI / 2.0 : -M_PI / 2.0;

    // For normal cases, use the standard atan2 function
    return atan2(x, y);
}

