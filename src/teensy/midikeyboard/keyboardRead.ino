#include <Audio.h>
#include <MIDI.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// Define the number of voices for polyphony
const int numVoices = 4;
int voiceNote[numVoices] = {-1}; 

// MIDI Library Initialization for USB
MIDI_CREATE_DEFAULT_INSTANCE();

// Define the audio components
AudioSynthWaveform   waveform[numVoices];  // Create an array of waveforms for polyphony
AudioMixer4          mixer;                // Mix the waveforms before output
AudioOutputI2S       audioOutput;          // Audio output
AudioConnection      *patchCords[numVoices * 2];  // Patch cords for waveforms to mixer
AudioConnection      patchCordToOutput(mixer, 0, audioOutput, 0);
AudioConnection      patchCordToOutput2(mixer, 0, audioOutput, 1);
AudioControlSGTL5000 audioShield;          // Audio shield

// Array to keep track of voice usage
bool voiceUsed[numVoices] = {false};

// Define envelope for each voice
AudioEffectEnvelope envelope[numVoices];

// New patch cords for the envelope effect
AudioConnection *patchCordsEnv[numVoices];

void setup() {
  // Start serial and MIDI communications
  Serial.begin(115200);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // Audio setup
  AudioMemory(20);
  audioShield.enable();
  audioShield.volume(0.5);

  // Set up waveforms and mixer
  for (int i = 0; i < numVoices; i++) {
    waveform[i].begin(WAVEFORM_SINE);
    waveform[i].amplitude(0);
    patchCords[i * 2] = new AudioConnection(waveform[i], 0, mixer, i);
  }

  for (int i = 0; i < numVoices; i++) {
    envelope[i].attack(10); // Attack time in milliseconds
    envelope[i].decay(100); // Decay time
    envelope[i].sustain(0.5); // Sustain level
    envelope[i].release(300); // Release time

    patchCordsEnv[i] = new AudioConnection(waveform[i], 0, envelope[i], 0);
    patchCords[i * 2] = new AudioConnection(envelope[i], 0, mixer, i);
  }

  
  mixer.gain(0, 0.25);
  mixer.gain(1, 0.25);
  mixer.gain(2, 0.25);
  mixer.gain(3, 0.25);
}

void loop() {
  // Read incoming MIDI messages
  if (usbMIDI.read()) {
    int note = usbMIDI.getData1();
    int velocity = usbMIDI.getData2();
    
    switch (usbMIDI.getType()) {
      case midi::NoteOn:
        if (velocity > 0) {
          noteOn(note, velocity);
        } else {
          noteOff(note);
        }
        break;
      case midi::NoteOff:
        noteOff(note);
        break;
      // Handle other MIDI message types as needed
    }
  }
}

void noteOn(uint8_t note, uint8_t velocity) {
  for (int i = 0; i < numVoices; i++) {
    if (!voiceUsed[i]) {
      float frequency = noteToFrequency(note);
      waveform[i].frequency(frequency);
      waveform[i].amplitude(velocity / 127.0);
      voiceUsed[i] = true;
      voiceNote[i] = note; // Store the note number that this voice is now playing
      break;
    }
  }
}

void noteOff(uint8_t note) {
  for (int i = 0; i < numVoices; i++) {
    if (voiceUsed[i] && voiceNote[i] == note) { // Check if this voice is playing the note
      waveform[i].amplitude(0);
      voiceUsed[i] = false;
      voiceNote[i] = -1; // Reset the note number for this voice
      break;
    }
  }
}

float noteToFrequency(uint8_t note) {
  return 440.0 * pow(2.0, (note - 69) / 12.0);
}
