#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();
#define AUDIO_GUITARTUNER_BLOCKS  16 // redefinition of notefreq parameter to reduce latency

AudioInputI2S            inputAudio;           //xy=140,143
// -------------------------------------------------------
// Vocoder
// TODO: add in the rest of the vocoder system
AudioMixer4              synthMixer;
AudioMixer4              carrierMixer;

// -------------------------------------------------------
// autotune
AudioAnalyzeNoteFrequency notefreq;        // frequency detector
AudioFilterBiquad        filter1;          // filter (biquad, easy lowpass filter)    
CustomAutoTune autotuner;
// -------------------------------------------------------
AudioMixer4              sourceMixer;         //xy=760,144

AudioEffectReverb        reverb1;        //xy=1049,122
AudioEffectFlange        flange1;        //xy=1046,169
AudioEffectFreeverb      freeverb1;      //xy=1045,215
AudioEffectChorus        chorus1;        //xy=1047,263
AudioMixer4              delayBus;         //xy=1067,562

AudioEffectBitcrusher    bitcrusher1;    //xy=1044,309
AudioEffectWaveshaper    distortion;     //xy=1043,357
AudioEffectWaveshaper    limiter;     //xy=1044,404
AudioEffectMultiply      multiply1;      //xy=1036,456
AudioMixer4              distortionBus;         //xy=1065,641

AudioMixer4              masterMixer;         //xy=904,766
AudioAmplifier           outputVolumeControl;           //xy=928,829
AudioOutputI2S           finalOutputAudio;           //xy=1158,836

AudioControlSGTL5000 sgtl5000_1;

AudioConnection patchCords[33] = {
  
  // Vocoder lower half + synthesizer
  AudioConnection(inputAudio, 1, carrierMixer, 0),
  AudioConnection(synthMixer, 0, carrierMixer, 1),
  // TODO rest of lower half of vocoder
  AudioConnection(carrierMixer, 0, sourceMixer, 3),
  AudioConnection(carrierMixer, 0, multiply1, 1),

  // sourceMixer
  AudioConnection(inputAudio, 0, sourceMixer, 0),
  // delayBus Input
  AudioConnection(sourceMixer, reverb1),
  AudioConnection(sourceMixer, flange1),
  AudioConnection(sourceMixer, freeverb1),
  AudioConnection(sourceMixer, chorus1),
  // distortionBus Input
  AudioConnection(sourceMixer, bitcrusher1),
  AudioConnection(sourceMixer, distortion),
  AudioConnection(sourceMixer, limiter),
  AudioConnection(sourceMixer, 0, multiply1, 0),
  AudioConnection(sourceMixer, 0, masterMixer, 0),

  // delayBus
  AudioConnection(reverb1, 0, delayBus, 0),
  AudioConnection(flange1, 0, delayBus, 1),
  AudioConnection(freeverb1, 0, delayBus, 2),
  AudioConnection(chorus1, 0, delayBus, 3),
  AudioConnection(delayBus, 0, masterMixer, 1),
  // distortionBus
  AudioConnection(bitcrusher1, 0, distortionBus, 0),
  AudioConnection(distortion, 0, distortionBus, 1),
  AudioConnection(limiter, 0, distortionBus, 2),
  AudioConnection(multiply1, 0, distortionBus, 3),
  AudioConnection(distortionBus, 0, masterMixer, 2),

  // Output
  AudioConnection(masterMixer, outputVolumeControl),
  AudioConnection(outputVolumeControl, 0, finalOutputAudio, 0),
};

// Define the number of voices for polyphony
const int numVoices = 4;
int voiceNote[numVoices] = {-1};  // keep track of the note information
bool voiceUsed[numVoices] = {false}; // keep track of usage
unsigned long voiceStartTime[numVoices] = {0}; // keep track of timing
//Audio Components for synthesis
AudioSynthWaveform   waveform[numVoices];  // Create an array of waveforms for polyphony
AudioEffectEnvelope envelope[numVoices];  // Define envelope for each voice
AudioConnection *patchCordsWav[numVoices]; // Patchcords for WaveForms
AudioConnection *patchCordsEnv[numVoices]; // Patchcords for Envelopes

// Setup Variables

// Buffers for flanger and chorus effects
static const int FLANGE_BUFFER_SIZE = 512;
short flangeBuffer[FLANGE_BUFFER_SIZE];
static const int CHORUS_BUFFER_SIZE = 512;
short chorusBuffer[CHORUS_BUFFER_SIZE];

//waveshape for distortion effects
static const int WAVESHAPE_SIZE = 129;
float limiter1[WAVESHAPE_SIZE] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                    -1,-1,-1,-1,-0.98506,-0.95937,-0.9331,-0.90628,-0.8789,-0.851,-0.82258,-0.79367,-0.76428,
                    -0.73443,-0.70414,-0.67342,-0.6423,-0.61079,-0.57892,-0.54669,-0.51414,-0.48127,-0.44812,
                    -0.41469,-0.38102,-0.34711,-0.313,-0.2787,-0.24423,-0.20961,-0.17487,-0.14002,-0.10509,
                    -0.070097,-0.035059,0,0.035059,0.070097,0.10509,0.14002,0.17487,0.20961,0.24423,0.2787,
                    0.313,0.34711,0.38102,0.41469,0.44812,0.48127,0.51414,0.54669,0.57892,0.61079,0.6423,
                    0.67342,0.70414,0.73443,0.76428,0.79367,0.82258,0.851,0.8789,0.90628,0.9331,0.95937,
                    0.98506,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
float distortion1[WAVESHAPE_SIZE] = {-1, -0.9999,-0.9996,-0.99911,-0.99841,-0.99751,-0.99642,-0.99512,-0.99362,-0.99192,-0.99001,
                    -0.9879,-0.98558,-0.98305,-0.98032,-0.97737,-0.97421,-0.97083,-0.96724,-0.96342,-0.95938,
                    -0.95512,-0.95062,-0.94588,-0.94091,-0.9357,-0.93024,-0.92452,-0.91855,-0.91231,-0.9058,
                    -0.89901,-0.89193,-0.88455,-0.87688,-0.86888,-0.86055,-0.85189,-0.84287,-0.83347,-0.82369,
                    -0.8135,-0.80287,-0.79179,-0.78022,-0.76813,-0.75549,-0.74224,-0.72834,-0.71374,-0.69835,
                    -0.68209,-0.66486,-0.64654,-0.62696,-0.60592,-0.58315,-0.55829,-0.53083,-0.50001,-0.46465,
                    -0.42267,-0.3698,-0.29422,0,0.29422,0.3698,0.42267,0.46465,0.50001,0.53083,0.55829,0.58315,
                    0.60592,0.62696,0.64654,0.66486,0.68209,0.69835,0.71374,0.72834,0.74224,0.75549,0.76813,
                    0.78022,0.79179,0.80287,0.8135,0.82369,0.83347,0.84287,0.85189,0.86055,0.86888,0.87688,
                    0.88455,0.89193,0.89901,0.9058,0.91231,0.91855,0.92452,0.93024,0.9357,0.94091,0.94588,
                    0.95062,0.95512,0.95938,0.96342,0.96724,0.97083,0.97421,0.97737,0.98032,0.98305,0.98558,
                    0.9879,0.99001,0.99192,0.99362,0.99512,0.99642,0.99751,0.99841,0.99911,0.9996,0.9999,1};


// Setup routine
void setup() {
  Serial.begin(115200);
  AudioMemory(128);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // enable Audio Shield
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.7);
  
  // enable Mixer Gain
  setMixer(sourceMixer, 1, 0, 0, 1);  
  setMixer(synthMixer, 0.7, 0.7, 0.7, 0.7);  
  setMixer(carrierMixer, 0, 1, 0, 0);  
  setMixer(delayBus, 0, 0, 0, 0);
  setMixer(distortionBus, 0, 0, 0, 0);
  setMixer(masterMixer, 1, 0, 0, 0);
  outputVolumeControl.gain(1);

  // initialize effects
  flange1.begin(flangeBuffer, FLANGE_BUFFER_SIZE, 100, 100, 100);
  chorus1.begin(chorusBuffer, CHORUS_BUFFER_SIZE, 4);

  bitcrusher1.bits(8);
  bitcrusher1.sampleRate(44100);
  distortion.shape(distortion1, WAVESHAPE_SIZE);
  limiter.shape(limiter1, WAVESHAPE_SIZE);

  // Set up waveforms and mixer
  for (int i = 0; i < numVoices; i++) {
    waveform[i].begin(WAVEFORM_SINE);
    waveform[i].amplitude(0);
    envelope[i].attack(10); // Attack time in milliseconds
    envelope[i].decay(100); // Decay time
    envelope[i].sustain(0.5); // Sustain level
    envelope[i].release(300); // Release time
    
    patchCordsWav[i] = new AudioConnection(waveform[i], 0, envelope[i], 0);
    patchCordsEnv[i] = new AudioConnection(envelope[i], 0, synthMixer, i);
  }

}

// Loop routine
void loop() {
  // Read commands from Serial
  readAndApplySerialCommands();
  // Read control from MIDI Signal
  readAndApplyMIDIControl();

  Serial.println(AudioMemoryUsageMax());
}

// Read and apply serial commands
void readAndApplySerialCommands() {
  if (Serial.available() > 0) {
    // Read the incoming command
    char commandBuffer[10];
    readSerialCommand(commandBuffer, sizeof(commandBuffer));

    // Parse and apply the command
    applySerialCommand(commandBuffer);
  }
}
// Read serial command into buffer
void readSerialCommand(char *buffer, size_t bufferSize) {
  size_t index = 0;
  while (index < bufferSize - 1 && Serial.available()) {
    char c = Serial.read();
    if (c == '\n') break;
    buffer[index++] = c;
  }
  buffer[index] = '\0'; // Null-terminate the string
}
// Parse and apply the command
void applySerialCommand(const char *command) {
  switch (command[0]) {
    case 'm': setMixerGain(sourceMixer, 0, command + 1); break; //dry microphone gain
    case 'c': setMixerGain(sourceMixer, 3, command + 1); break; //dry carrier signal gain
    case 'a': setMixerGain(sourceMixer, 1, command + 1); break; //autotune gain
    case 'v': setMixerGain(sourceMixer, 2, command + 1); break; //vocoder gain

    case 'r': setMixerGain(delayBus, 0, command + 1); break; // reverb gain
    case 'f': setMixerGain(delayBus, 1, command + 1); break; // flanger gain
    case 'e': setMixerGain(delayBus, 2, command + 1); break; // freeverb gain
    case 'h': setMixerGain(delayBus, 3, command + 1); break; // chorus gain

    case 'b': setMixerGain(distortionBus, 0, command + 1); break; // bitcrusher gain
    case 't': setMixerGain(distortionBus, 1, command + 1); break; // distortion gain
    case 'l': setMixerGain(distortionBus, 2, command + 1); break; // limiter gain
    case 'u': setMixerGain(distortionBus, 3, command + 1); break; // multiplier gain

    case 's': setMixerGain(masterMixer, 0, command + 1); break; //dry source master gain
    case 'd': setMixerGain(masterMixer, 1, command + 1); break; //delay bus master gain
    case 'i': setMixerGain(masterMixer, 2, command + 1); break; //distortion bus master gain

    case 'o': outputVolumeControl.gain(atof(command + 1)); break; //master volume output

    case 'R': freeverb1.roomsize(atof(command + 1)); break; // attempt to change roomsize
    default: Serial.println("Invalid effect type"); break;
  }
}

// Read and apply MIDI control input
void readAndApplyMIDIControl() {
  // read MIDI signal
    // Channel 0 = Keys, Knobs
    if(usbMIDI.read(0)) {
      int arg1 = usbMIDI.getData1();

      switch (usbMIDI.getType()) {
      case midi::NoteOn: // KEY_PRESS
      {
        int keyNote = arg1; // integer 48 to 72 on the keyboard
        int keyVelocity = usbMIDI.getData2(); // 0 to 100

        if(keyVelocity > 0) {
          noteOn(keyNote, keyVelocity);
        } else {
          noteOff(keyNote);
        }
        break;
      }
      case midi::NoteOff: // KEY_RELEASE
      {// same as NoteOn
        int keyNote = arg1; // integer 48 to 72 on the keyboard
        noteOff(keyNote);
        break;
      }
      case midi::ControlChange: // KNOBS
      {
        int controlNum = arg1; // integer 1 to 8 (the knob number)
        int controlVal = usbMIDI.getData2(); // integer 0 to 127

        Serial.print("Knob = ");
        Serial.print(controlNum);
        Serial.print(", Value = ");
        Serial.println(controlVal);
        // do something with these values
        break;
      }
      case midi::PitchBend: // PITCH STICK
      {
        int pitchValue = arg1; // The amount of bend to send (in a signed integer format), between MIDI_PITCHBEND_MIN and MIDI_PITCHBEND_MAX, center value is 0.

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
      {
        int pad_note = usbMIDI.getData1(); // integer 48 to 55
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
    } // end MIDI
}

// Set mixer gain
void setMixerGain(AudioMixer4& mixer, uint8_t channel, const char *gainStr) {
  float gainValue = atof(gainStr);
  mixer.gain(channel, gainValue);

  // Output the new gain value
  Serial.print("Channel ");
  Serial.print(channel);
  Serial.print(" gain set to ");
  Serial.println(gainValue);
}
//edits a mixer to set gain of each channel
void setMixer(AudioMixer4& mixer, float c0, float c1, float c2, float c3){
    mixer.gain(0, c0);
    mixer.gain(1, c1);
    mixer.gain(2, c2);
    mixer.gain(3, c3);
}

// MIDi control functions
void noteOn(uint8_t note, uint8_t velocity) {
  int freeVoice = -1;
  unsigned long oldestTime = millis();
  int oldestVoice = 0;

  for (int i = 0; i < numVoices; i++) {
    if (voiceNote[i] == note || !voiceUsed[i]) { // TODO: test if this prevents playing a duplicate note, which I think is the cause
      freeVoice = i;
      break;
    } else if(voiceStartTime[i] < oldestTime) {
      oldestTime = voiceStartTime[i];
      oldestVoice = i;
    }
  }

  if(freeVoice > -1) { // found a free voice
    float frequency = noteToFrequency(note);
    waveform[freeVoice].frequency(frequency);
    waveform[freeVoice].amplitude(velocity / 127.0);
    envelope[freeVoice].noteOn();
    voiceUsed[freeVoice] = true;
    voiceNote[freeVoice] = note; // Store the note number that this voice is now playing
  } else { // replace with an existing voice
    float frequency = noteToFrequency(note);
    waveform[oldestVoice].frequency(frequency);
    waveform[oldestVoice].amplitude(velocity / 127.0);
    envelope[oldestVoice].noteOn();
    voiceUsed[oldestVoice] = true;
    voiceNote[oldestVoice] = note; // Store the note number that this voice is now playing
  }
}

void noteOff(uint8_t note) {
  for (int i = 0; i < numVoices; i++) {
    if (voiceUsed[i] && voiceNote[i] == note) { // Check if this voice is playing the note
      waveform[i].amplitude(0);
      waveform[i].frequency(0);
      envelope[i].noteOff();
      voiceUsed[i] = false;
      voiceNote[i] = -1; // Reset the note number for this voice
    }
  }
}

float noteToFrequency(uint8_t note) {
  return 440.0 * pow(2.0, (note - 69) / 12.0);
}