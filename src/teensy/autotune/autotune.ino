#include <Audio.h>
#include "effect_granular.h" // Include the granular effect header


class AudioEffectGranular : public AudioStream {
public:
    AudioEffectGranular() : AudioStream(1, inputQueueArray) { }
    virtual void update(void);

private:
    void processFreeze(audio_block_t *block); // Implementation placeholder
    void processPitchShift(audio_block_t *block); // Implementation placeholder

    audio_block_t *inputQueueArray[1];
    int16_t *sample_bank;
    uint32_t playpack_rate;
    uint32_t accumulator;
    int16_t max_sample_len;
    int16_t write_head;
    int16_t read_head;
    int16_t grain_mode;
    int16_t freeze_len;
    int16_t prev_input;
    int16_t glitch_len;
    bool allow_len_change;
    bool sample_loaded;
    bool write_en;
    bool sample_req;
};


// Define the number of samples in your granular sample bank
const int16_t GRANULAR_MEMORY_SIZE = 2048;
int16_t granularMemory[GRANULAR_MEMORY_SIZE];

// Instantiate the audio classes
AudioInputI2S i2s1;                // Input from I2S
AudioEffectGranular granular1;     // The granular effect
AudioOutputI2S i2s2;               // Output to I2S
AudioControlSGTL5000 sgtl5000_1;   // Control chip for I2S

// Create the audio connections
AudioConnection patchCord1(i2s1, 0, granular1, 0);
AudioConnection patchCord2(granular1, 0, i2s2, 0);
AudioConnection patchCord3(granular1, 0, i2s2, 1);

void setup() {
  // Initialize serial communication for debugging purposes
  Serial.begin(9600);

  // Initialize the audio shield
  AudioMemory(20); // Allocate memory for audio processing
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5); // Set the initial volume (adjust as necessary)

  // Initialize the granular effect
  granular1.begin(granularMemory, GRANULAR_MEMORY_SIZE);

  // Here you can initialize the granular effect with a specific mode if desired
  // granular1.beginFreeze(); // For a freeze effect
  // granular1.beginPitchShift(); // For a pitch shift effect
}


void loop() {
  // Placeholder for user input or condition to trigger granular effect changes.
  // You should replace this with actual logic or user input handling.
  
  if (Serial.available() > 0) {
    int command = Serial.read();
    
    // Commands to control the granular effect
    switch (command) {
      case 'f': // Command to begin freeze effect
        granular1.beginFreeze_int(150); // Replace 150 with the desired grain size
        break;
      case 'p': // Command to begin pitch shift
        granular1.beginPitchShift_int(150); // Replace 150 with the desired grain size
        break;
      case 's': // Command to stop the granular effect
        granular1.stop();
        break;
      // Add more cases as needed for other functionalities
    }
  }
  
  // Other continuous audio processing can go here if needed
}

void AudioEffectGranular::update(void) {
  audio_block_t *block;

  // Check if the sample bank is properly initialized
  if (sample_bank == NULL) {
    block = receiveReadOnly(0);
    if (block) release(block);
    return;
  }

  // Get the next audio block to process
  block = receiveWritable(0);
  if (!block) return;

  // The granular effect processing is done here
  if (grain_mode == 0) {
    // Passthrough, no granular effect
    prev_input = block->data[AUDIO_BLOCK_SAMPLES-1];
  } else if (grain_mode == 1) {
    // Freeze effect processing code
    processFreeze(block);
  } else if (grain_mode == 2) {
    // Pitch shift effect processing code
    processPitchShift(block);
  }

  // Transmit the processed block and release memory
  transmit(block);
  release(block);
}


void AudioEffectGranular::processFreeze(audio_block_t *block) {
  for (int j = 0; j < AUDIO_BLOCK_SAMPLES; j++) {
    if (sample_req) {
      // only begin capture on zero cross
      int16_t current_input = block->data[j];
      if ((current_input < 0 && prev_input >= 0) ||
          (current_input >= 0 && prev_input < 0)) {
        write_en = true;
        write_head = 0;
        read_head = 0;
        sample_req = false;
      } else {
        prev_input = current_input;
      }
    }
    if (write_en) {
      sample_bank[write_head++] = block->data[j];
      if (write_head >= freeze_len) {
        sample_loaded = true;
      }
      if (write_head >= max_sample_len) {
        write_en = false;
      }
    }
    if (sample_loaded) {
      if (playpack_rate >= 0) {
        accumulator += playpack_rate;
        read_head = accumulator >> 16;
      }
      if (read_head >= freeze_len) {
        accumulator = 0;
        read_head = 0;
      }
      block->data[j] = sample_bank[read_head];
    }
  }
}

void AudioEffectGranular::processPitchShift(audio_block_t *block) {
  for (int k = 0; k < AUDIO_BLOCK_SAMPLES; k++) {
    if (sample_req) {
      int16_t current_input = block->data[k];
      if ((current_input < 0 && prev_input >= 0) ||
          (current_input >= 0 && prev_input < 0)) {
        write_en = true;
      } else {
        prev_input = current_input;
      }
    }

    if (write_en) {
      sample_req = false;
      if (write_head >= glitch_len) {
        write_head = 0;
        sample_loaded = true;
        write_en = false;
        allow_len_change = false;
      }
      sample_bank[write_head] = block->data[k];
      write_head++;
    }

    if (sample_loaded) {
      float fade_len = 20.00;
      int16_t m2 = fade_len;

      for (int m = 0; m < 2; m++) {
        sample_bank[m + glitch_len] = 0;
      }

      for (int m = 2; m < glitch_len - m2; m++) {
        sample_bank[m + glitch_len] = sample_bank[m];
      }

      for (int m = glitch_len - m2; m < glitch_len; m++) {
        float fadet = sample_bank[m] * (m2 / fade_len);
        sample_bank[m + glitch_len] = (int16_t)fadet;
        m2--;
      }
      sample_loaded = false;
      prev_input = block->data[k];
      sample_req = true;
    }

    accumulator += playpack_rate;
    read_head = (accumulator >> 16);

    if (read_head >= glitch_len) {
      read_head -= glitch_len;
      accumulator = 0;

      for (int m = 0; m < glitch_len; m++) {
        sample_bank[m + (glitch_len * 2)] = sample_bank[m + glitch_len];
      }
    }
    block->data[k] = sample_bank[read_head + (glitch_len * 2)];
  }
}

