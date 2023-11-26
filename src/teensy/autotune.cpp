#include "autotune.h"

// ---------------------------------

// main update function
void CustomAutoTune::update(void) {
  audio_block_t *block;

  // receive data
  block = receiveWritable(0);
  if(block) {
     //Serial.printf("Note: %3.2f\n", currFrequency);
    // call stuff
    float floatInput[AUDIO_BLOCK_SAMPLES];

    // convert input to floats with proper scaling
    for (size_t i = 0; i < AUDIO_BLOCK_SAMPLES; ++i) {
        floatInput[i] = (float)((float)block->data[i])/(INT_MAX);
    }
    
    pitchShift(computeNearestSemitone(currFrequency), &floatInput[0], &floatInput[0]);

  // Convert the processed float32 signal back to the original array
  // and scale back to int16
  for (size_t i = 0; i < AUDIO_BLOCK_SAMPLES; ++i) {
      block->data[i] = (int16_t)(floatInput[i] * INT_MAX); // Convert back to 16-bit int
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
    long osamp = 4;
    float sampleRate = 44100;

  static long gRover = false, gInit = false;
  double magn, phase, tmp, window, real, imag;
  double freqPerBin, expct;
  long i,k, qpd, index, inFifoLatency, stepSize, fftFrameSize2;

  /* set up some handy variables */
  fftFrameSize2 = AUTOTUNE_FFT_SIZE/2;
  stepSize = AUTOTUNE_FFT_SIZE/osamp;
  freqPerBin = sampleRate/(double)AUTOTUNE_FFT_SIZE;
  expct = 2.*M_PI*(double)stepSize/(double)AUTOTUNE_FFT_SIZE;
  inFifoLatency = AUTOTUNE_FFT_SIZE-stepSize;
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
  for (i = 0; i < AUDIO_BLOCK_SAMPLES; i++){

    /* As long as we have not yet collected enough data just read in */
    gInFIFO[gRover] = indata[i];
    outdata[i] = gOutFIFO[gRover-inFifoLatency];
    gRover++;

    /* now we have enough data for processing */
    if (gRover >= AUTOTUNE_FFT_SIZE) {
      gRover = inFifoLatency;

      /* do windowing and re,im interleave */
      for (k = 0; k < AUTOTUNE_FFT_SIZE;k++) {
        window = -.5*cos(2.*M_PI*(double)k/(double)AUTOTUNE_FFT_SIZE)+.5;
        gFFTworksp[2*k] = gInFIFO[k] * window;
        gFFTworksp[2*k+1] = 0.;
      }


      /* ***************** ANALYSIS ******************* */
      /* do transform */
      smbFft(gFFTworksp, AUTOTUNE_FFT_SIZE, -1);

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
      memset(gSynMagn, 0, AUTOTUNE_FFT_SIZE*sizeof(float));
      memset(gSynFreq, 0, AUTOTUNE_FFT_SIZE*sizeof(float));
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
      for (k = AUTOTUNE_FFT_SIZE+2; k < 2*AUTOTUNE_FFT_SIZE; k++) gFFTworksp[k] = 0.;

      /* do inverse transform */
      smbFft(gFFTworksp, AUTOTUNE_FFT_SIZE, 1);

      /* do windowing and add to output accumulator */ 
      for(k=0; k < AUTOTUNE_FFT_SIZE; k++) {
        window = -.5*cos(2.*M_PI*(double)k/(double)AUTOTUNE_FFT_SIZE)+.5;
        gOutputAccum[k] += 2.*window*gFFTworksp[2*k]/(fftFrameSize2*osamp);
      }
      for (k = 0; k < stepSize; k++) gOutFIFO[k] = gOutputAccum[k];

      /* shift accumulator */
      memmove(gOutputAccum, gOutputAccum+stepSize, AUTOTUNE_FFT_SIZE*sizeof(float));

      /* move input FIFO */
      for (k = 0; k < inFifoLatency; k++) gInFIFO[k] = gInFIFO[k+stepSize];
    }
  }
}

// -------------------------------

void smbFft(float *fftBuffer, long fftSize, long sign) {
  float wr, wi, arg, *p1, *p2, temp;
  float tr, ti, ur, ui, *p1r, *p1i, *p2r, *p2i;
  long i, bitm, j, le, le2, k;

  for (i = 2; i < 2*fftSize-2; i += 2) {
    for (bitm = 2, j = 0; bitm < 2*fftSize; bitm <<= 1) {
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
  for (k = 0, le = 2; k < (long)(log(fftSize)/log(2.)+.5); k++) {
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
      for (i = j; i < 2*AUTOTUNE_FFT_SIZE; i += le) {
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
double smbAtan2(double x, double y) {
  double signx;
  if (x > 0.) signx = 1.;  
  else signx = -1.;
  
  if (x == 0.) return 0.;
  if (y == 0.) return signx * M_PI / 2.;
  
  return atan2(x, y);
}
// -------------------------------