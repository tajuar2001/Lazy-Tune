#include <SerialFlash.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
//----------------------------------------------------------

#define AUDIO_GUITARTUNER_BLOCKS  12 // redefinition of notefreq parameter to reduce latency

// Audio Components
AudioInputI2S i2s1;                        // IS2 input
AudioOutputI2S i2s2;                       // IS2 output
AudioControlSGTL5000 audioShield;          // Audio shield
AudioAnalyzeNoteFrequency notefreq;        // frequency detector
AudioFilterBiquad filter1;                 // filter (biquad, easy lowpass filter)    
AudioEffectGranular granular1;             // granular effect

AudioConnection patchCords[6] {
  AudioConnection(i2s1, 0, filter1, 0),
  AudioConnection(filter1, 0, notefreq, 0),

  AudioConnection(filter1, 0, granular1, 0),
  AudioConnection(granular1, 0, i2s2, 0),
  AudioConnection(granular1, 0, i2s2, 1),
};

#define GRANULAR_MEMORY_SIZE 128  // enough for 2.90 ms at 44.1 kHz
int16_t granularMemory[GRANULAR_MEMORY_SIZE];
float currFrequency;
bool pitchShift;

// Function declarations
void processAudio(); // Function to process and autotune audio
void readAndExecuteCommands(); // Function to read serial commands and execute them

void setup() {
    Serial.begin(115200); // Start serial communication at a higher baud rate
    AudioMemory(31); // Allocate memory for audio processing

    audioShield.enable(); // audioShield initialization
    audioShield.volume(0.5);

    // filter setup
    filter1.setLowpass(0, 3400, 0.707); // Butterworth filter, 12 db/octave
    notefreq.begin(.15); // Initialize Yin Algorithm Absolute Threshold (15% is a good number)

    // Granular Effect setup
    pitchShift = false;
    granular1.begin(granularMemory, GRANULAR_MEMORY_SIZE);
}

void loop() {
    readAndExecuteCommands(); // Check for and execute serial commands
    
    // read current fundamental frequency into AutoTune
    if(notefreq.available()) {
      float note = notefreq.read();
      float prob = notefreq.probability();
      // Serial.printf("Note: %3.2f | Probably %.2f\n", note, prob);
      if(prob > 0.8) {
        currFrequency = note;
      }
    }

    if(pitchShift) {
      // Pitch Shift using Granular
      granular1.beginPitchShift(1);
      granular1.beginPitchShift(1);
      granular1.beginPitchShift(1);
      granular1.stop();
    }
    
    //Serial.println(AudioMemoryUsageMax());
}

// Function to read serial commands and execute them
void readAndExecuteCommands() {
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n');
        executeCommand(command);
    }
}

// Execute a received command
void executeCommand(const String& command) {
    if (command.startsWith("autotune:")) {
        // Parse the command to get the autotune parameters
        // Example command might be "autotune:on" or "autotune:off"
        String parameter = command.substring(9);
      
        if (parameter == "on") {
            // Turn on autotune
            pitchShift = true;

        } else if (parameter == "off") {
            // Turn off autotune
            pitchShift = false;
        }
        // Add other parameters as needed
    } else {
        Serial.println("Unknown command");
    }
}