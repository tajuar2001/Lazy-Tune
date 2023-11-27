#pragma GCC diagnostic ignored "-Wcpp"
#include <SerialFlash.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include <MIDI.h>
// MIDI Library Initialization for USB
MIDI_CREATE_DEFAULT_INSTANCE();
//----------------------------------------------------------
#include "autotune.h"

#define AUDIO_GUITARTUNER_BLOCKS  16 // redefinition of notefreq parameter to reduce latency

CustomAutoTune autotuner;
// Audio Components
AudioInputI2S i2s1;                        // IS2 input
AudioOutputI2S i2s2;                       // IS2 output
AudioControlSGTL5000 audioShield;          // Audio shield
AudioAnalyzeNoteFrequency notefreq;        // frequency detector
AudioFilterBiquad        filter1;          // filter (biquad, easy lowpass filter)    

AudioConnection patchCords[5] {
  AudioConnection(i2s1, 0, filter1, 0),
  AudioConnection(filter1, 0, notefreq, 0),

  AudioConnection(filter1, 0, autotuner, 0),
  AudioConnection(autotuner, 0, i2s2, 0),
  AudioConnection(autotuner, 0, i2s2, 1),
};

// Function declarations
void processAudio(); // Function to process and autotune audio
void readAndExecuteCommands(); // Function to read serial commands and execute them

void setup() {
    Serial.begin(115200); // Start serial communication at a higher baud rate
    MIDI.begin(MIDI_CHANNEL_OMNI);
    AudioMemory(31); // Allocate memory for audio processing

    audioShield.enable(); // audioShield initialization
    audioShield.volume(0.5);

    // filter setup
    filter1.setLowpass(0, 3400, 0.707); // Butterworth filter, 12 db/octave
    notefreq.begin(.15); // Initialize Yin Algorithm Absolute Threshold (15% is a good number)

    // autotune setup
    autotuner.option_edit(autotuneMethod::original); // AutoTune initialization
    autotuner.currFrequency = 20;
    autotuner.manualPitchOffset = 0;
}

void loop() {
    readAndExecuteCommands(); // Check for and execute serial commands
    
    // read current fundamental frequency into AutoTune
    if(notefreq.available()) {
      float note = notefreq.read();
      float prob = notefreq.probability();
      // Serial.printf("Note: %3.2f | Probably %.2f\n", note, prob);
      if(prob > 0.9) {
        autotuner.currFrequency = note;
      }
    }

    // read midi signal 
    if(usbMIDI.read(0)) { // Channel 0
      switch (usbMIDI.getType()) {
      case midi::PitchBend: { // PITCH STICK
        int pitchValue = usbMIDI.getData1(); // The amount of bend to send (in a signed integer format), between MIDI_PITCHBEND_MIN and MIDI_PITCHBEND_MAX, center value is 0.
        autotuner.manualPitchOffset = AUTOTUNE_MIN_PS + ((pitchValue - MIDI_PITCHBEND_MIN) / static_cast<float>(MIDI_PITCHBEND_MAX - MIDI_PITCHBEND_MIN)) * (AUTOTUNE_MAX_PS - AUTOTUNE_MIN_PS);
        break;
      }
      // case midi::ControlChange:
      //   int controlNum = usbMIDI.getData1();
      //   int controlVal = usbMIDI.getData2();

      //   Serial.print("Knob = ");
      //   Serial.print(controlNum);
      //   Serial.print(", Value = ");
      //   Serial.println(controlVal);

      //   if(controlNum == AUTOTUNE_MIDI_KNOB) {
      //     // controlVal goes from 0 to 127, map it to -0.4 to 0.9
      //     autotuner.manualPitchOffset = -0.4 + (controlVal / static_cast<float>(127)) * (0.9-(-0.4));
      //   }
      //   break;
    }
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
    if (command.startsWith("AT_")) {
        // Parse the command to get the autotune parameters
        // Example command might be "autotune:on" or "autotune:off"
        String parameter = command.substring(3);
      
        if (parameter == "ON") {
            // Turn on autotune
            Serial.println("Autotune Enabled");
            autotuner.option_edit(autotuneMethod::original);
        } else if (parameter == "OFF") {
            // Turn off autotune
            Serial.println("Autotune Disabled");
            autotuner.option_edit(autotuneMethod::none);
        }
        // Add other parameters as needed
    } else {
        Serial.println("Unknown command");
    }
}
