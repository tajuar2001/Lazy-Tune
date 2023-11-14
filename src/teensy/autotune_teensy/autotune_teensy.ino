#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "autotune.h"

// Audio Components and Autotune Instance
AudioInputI2S i2s1; // Assuming we using I2S for audio input
CustomAutoTune autotuner;
AudioOutputI2S i2s2;

AudioConnection patchCords[3] {
  AudioConnection(i2s1, 0, autotuner, 0),
  AudioConnection(autotuner, 0, i2s2, 0),
  AudioConnection(autotuner, 0, i2s2, 1)
};

// Function declarations
void processAudio(); // Function to process and autotune audio
void readAndExecuteCommands(); // Function to read serial commands and execute them

void setup() {
    Serial.flush();
    Serial.begin(9600); // Start serial communication at a higher baud rate
    AudioMemory(12); // Allocate memory for audio processing
    // Additional setup code for audio components goes here
}

void loop() {
    readAndExecuteCommands(); // Check for and execute serial commands
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
    // Here, you'll parse the command and apply settings to the autotuner
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

// Add other functions as needed, for example to set autotune parameters
