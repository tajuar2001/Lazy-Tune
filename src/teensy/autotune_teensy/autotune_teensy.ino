#include <SerialFlash.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
//----------------------------------------------------------
#include "autotune.h"

CustomAutoTune autotuner;
// Audio Components
AudioInputI2S i2s1;                        // IS2 input
AudioOutputI2S i2s2;                       // IS2 output
AudioControlSGTL5000 audioShield;          // Audio shield
AudioAnalyzeNoteFrequency notefreq;        // frequency detector
AudioFilterBiquad        filter1;          // filter (biquad, easy lowpass filter)    

AudioConnection patchCords[5] {
  AudioConnection(i2s1, 0, autotuner, 0),
  AudioConnection(autotuner, 0, i2s2, 0),
  AudioConnection(autotuner, 0, i2s2, 1),
  AudioConnection(i2s1, 0, filter1, 0),
  AudioConnection(filter1, 0, notefreq, 0), // use filter2 as highpass
};

// Function declarations
void processAudio(); // Function to process and autotune audio
void readAndExecuteCommands(); // Function to read serial commands and execute them

void setup() {
    Serial.begin(115200); // Start serial communication at a higher baud rate
    AudioMemory(1028); // Allocate memory for audio processing

    audioShield.enable(); // audioShield initialization
    audioShield.volume(0.5);

    // filter setup
    filter1.setLowpass(0, 3400, 0.707); // Butterworth filter, 12 db/octave
    notefreq.begin(.15); // Initialize Yin Algorithm Absolute Threshold (15% is a good number)

    autotuner.option_edit(autotuneMethod::none); // AutoTune initialization
    autotuner.set_frequency(440.0);
    autotuner.currFrequency = 20;
}

void loop() {
    readAndExecuteCommands(); // Check for and execute serial commands
    
    // read current fundamental frequency into AutoTune
    if(notefreq.available()) {
      float note = notefreq.read();
      // float prob = notefreq.probability();
      // Serial.printf("Note: %3.2f | Probably %.2f\n", note, prob);
      autotuner.currFrequency = note;
    }
    Serial.println(AudioMemoryUsageMax());
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
            Serial.println("autotune on");
            autotuner.option_edit(autotuneMethod::original);

        } else if (parameter == "cepstrum") {
            // Turn on cepstrum meethod
            Serial.println("cepstrum on");
            autotuner.option_edit(autotuneMethod::cepstrum);

        } else if (parameter == "psola") {
            // Turn on psola method
            Serial.println("psola on (NYI)");

        } else if (parameter == "off") {
            // Turn off autotune
            Serial.println("autotune off");
            autotuner.option_edit(autotuneMethod::none);

        } else if (parameter.startsWith("manual")) {
            // Parse the target frequency from the command
            float32_t targetFrequency = parameter.substring(6).toFloat();
            // Check if the target frequency is a valid number
            if (!isnan(targetFrequency)) {
                Serial.println("manual mode with target frequency: " + String(targetFrequency));
                autotuner.option_edit(autotuneMethod::manual);
                autotuner.set_frequency(targetFrequency);
            } else {
                Serial.println("Invalid target frequency");
            }

        }
        // Add other parameters as needed
    } else {
        Serial.println("Unknown command");
    }
}