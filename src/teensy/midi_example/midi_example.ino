#include <SerialFlash.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include <MIDI.h>
// MIDI Library Initialization for USB
MIDI_CREATE_DEFAULT_INSTANCE();

// Audio Components
AudioInputI2S i2s1;                        // IS2 input
AudioOutputI2S i2s2;                       // IS2 output
AudioControlSGTL5000 audioShield;          // Audio shield  

AudioConnection patchCords[2] {
  AudioConnection(i2s1, 0, i2s2, 0),
  AudioConnection(i2s1, 0, i2s2, 1),
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
}

void loop() {
    readAndExecuteCommands(); // Check for and execute serial commands

    // read midi signal
    // Channel 0 = Keys, Knobs
    if(usbMIDI.read(0)) {
      switch (usbMIDI.getType()) {
      case midi::NoteOn: // KEY_PRESS
        {
        int keyNote = usbMIDI.getData1(); // integer 48 to 72 on the keyboard
        int keyVelocity = usbMIDI.getData2(); // 0 to 100

        Serial.print("Note = ");
        Serial.print(keyNote);
        Serial.print(", Velocity = ");
        Serial.print(keyVelocity);
        break;
        }
      case midi::NoteOff: // KEY_RELEASE
        {// same as NoteOn
        break;}
      case midi::ControlChange: // KNOBS
        {int controlNum = usbMIDI.getData1(); // integer 1 to 8 (the knob number)
        int controlVal = usbMIDI.getData2(); // integer 0 to 127

        Serial.print("Knob = ");
        Serial.print(controlNum);
        Serial.print(", Value = ");
        Serial.println(controlVal);

        // do something with these values
        break;}
      case midi::PitchBend: // PITCH STICK
        {int pitchValue = usbMIDI.getData1(); // The amount of bend to send (in a signed integer format), between MIDI_PITCHBEND_MIN and MIDI_PITCHBEND_MAX, center value is 0.

        Serial.print("Pitch Bend = ");
        Serial.print(pitchValue);
        break;
      }
      }
    }
    // Channel 1 = Pads
    if(usbMIDI.read(1)) {
      switch (usbMIDI.getType()) {
      case midi::NoteOn: // PAD_PRESS
        {int pad_note = usbMIDI.getData1(); // integer 48 to 55
        int pad_velocity = usbMIDI.getData2(); // 0 to 100
        Serial.print("Note = ");
        Serial.print(pad_note);
        Serial.print(", Velocity = ");
        Serial.print(pad_velocity);
        break;}
      case midi::NoteOff: // PAD_RELEASE
        {// same as NoteOn
        break;}
      }
    }
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
  // use the received string to do something
}