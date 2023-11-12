#include <Audio.h>
#include <MIDI.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// MIDI Library Initialization for USB
MIDI_CREATE_DEFAULT_INSTANCE();

// Define the audio components
AudioSynthWaveform   waveform;      //xy=270,230
AudioOutputI2S       audioOutput;   //xy=450,230
AudioConnection      patchCord1(waveform, 0, audioOutput, 0);
AudioConnection      patchCord2(waveform, 0, audioOutput, 1);
AudioControlSGTL5000 audioShield;   //xy=270,330

void setup() {
  // Start serial and MIDI communications
  Serial.begin(115200);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // Audio setup
  AudioMemory(10);
  audioShield.enable();
  audioShield.volume(0.5);

  // Set waveform to a sine wave
  waveform.begin(WAVEFORM_SINE);
}

void loop() {
  // Read incoming MIDI messages
  if (usbMIDI.read()) {
    switch (usbMIDI.getType()) {
      case midi::NoteOn:
        handleNoteOn(usbMIDI.getData1(), usbMIDI.getData2());
        break;
      case midi::NoteOff:
        handleNoteOff(usbMIDI.getData1(), usbMIDI.getData2());
        break;
      // Handle other MIDI message types as needed
    }
  }
}

void handleNoteOn(uint8_t note, uint8_t velocity) {
  // Turn on the note with the corresponding frequency and velocity
  float frequency = noteToFrequency(note);
  waveform.frequency(frequency);
  waveform.amplitude(velocity / 127.0);
}

void handleNoteOff(uint8_t note, uint8_t velocity) {
  // Turn off the note by setting its amplitude to zero
  waveform.amplitude(0);
}

float noteToFrequency(uint8_t note) {
  // Convert MIDI note number to frequency (Hz)
  return 440.0 * pow(2.0, (note - 69) / 12.0);
}
