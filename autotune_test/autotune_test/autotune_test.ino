#include <cmath>
#include <algorithm>
#include <vector>
#include <cstring>

#include <Arduino.h>
#include <AudioStream.h>
#include <Audio.h>

// Audio library objects
AudioInputI2S            audioInput;
AudioOutputI2S           audioOutput;
AudioControlSGTL5000     audioShield;
AudioConnection          patchCord1(audioInput, 0, audioOutput, 0);
AudioConnection          patchCord2(audioInput, 1, audioOutput, 1);

// PSOLA algorithm parameters
const int BUFFER_SIZE = 256; // Size of the audio buffer
float inputBuffer[BUFFER_SIZE]; // Input buffer to store audio samples
float outputBuffer[BUFFER_SIZE]; // Output buffer for processed audio
int writeIndex = 0; // Write index for the input buffer

void setup() {
  Serial.begin(115200);
  AudioMemory(60); // Allocate memory for audio
  audioShield.enable(); // Enable the audio shield
  audioShield.inputSelect(AUDIO_INPUT_LINEIN); // Select the input
  audioShield.volume(0.5); // Set the volume
}

void loop() {
  // Capture audio
  audio_block_t *block = receiveWritable(0);
  if (block) {
    // Copy audio data into the buffer
    for(int i=0; i<AUDIO_BLOCK_SAMPLES; i++){
      inputBuffer[writeIndex++] = (float)block->data[i];
      if(writeIndex >= BUFFER_SIZE) writeIndex = 0;
    }
    release(block);
    
    // Call the pitch-shifting function
    pitchShift(inputBuffer, outputBuffer, BUFFER_SIZE, 0.5); // Pitch shift down by a factor of 0.5
    
    // Output processed audio
    audio_block_t *outBlock = allocate();
    if (outBlock) {
      for(int i=0; i<AUDIO_BLOCK_SAMPLES; i++){
        outBlock->data[i] = (int16_t)outputBuffer[i];
      }
      transmit(outBlock, 0);
      release(outBlock);
    }
  }
}

void pitchShift(float *input, float *output, int bufferSize, float pitchFactor) {
  // Simple pitch shifting by changing the pitch and using linear interpolation to maintain duration
  int outputIndex = 0;
  for (int i = 0; i < bufferSize; i += pitchFactor) {
    int index = (int)i;
    int nextIndex = (index + 1) % bufferSize;
    float frac = i - (float)index; // Get the fractional part for interpolation
    output[outputIndex++] = (1.0f - frac) * input[index] + frac * input[nextIndex];
    if (outputIndex >= bufferSize) break; // Ensure we don't overflow the buffer
  }
}