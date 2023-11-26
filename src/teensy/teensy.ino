#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <MIDI.h>
#include "autotune.h"

MIDI_CREATE_DEFAULT_INSTANCE();
#define AUDIO_GUITARTUNER_BLOCKS  16 // redefinition of notefreq parameter to reduce latency

AudioInputI2S            inputAudio;           //xy=140,143
// -------------------------------------------------------
// Vocoder
AudioAmplifier           modulatorGain;
AudioMixer4              synthMixer;
AudioMixer4              carrierMixer;
AudioMixer4              vocoderMixer1;
AudioMixer4              vocoderMixer2;
AudioMixer4              vocoderMixer3;
AudioMixer4              vocoderOut;
// vocoder filters 1-24
AudioFilterStateVariable filter1;
AudioFilterStateVariable filter2;
AudioFilterStateVariable filter3;
AudioFilterStateVariable filter4;
AudioFilterStateVariable filter5;
AudioFilterStateVariable filter6;
AudioFilterStateVariable filter7;
AudioFilterStateVariable filter8;
AudioFilterStateVariable filter9;
AudioFilterStateVariable filter10;
AudioFilterStateVariable filter11;
AudioFilterStateVariable filter12;
AudioFilterStateVariable filter13;
AudioFilterStateVariable filter14;
AudioFilterStateVariable filter15;
AudioFilterStateVariable filter16;
AudioFilterStateVariable filter17;
AudioFilterStateVariable filter18;
AudioFilterStateVariable filter19;
AudioFilterStateVariable filter20;
AudioFilterStateVariable filter21;
AudioFilterStateVariable filter22;
AudioFilterStateVariable filter23;
AudioFilterStateVariable filter24;
// vocoder peak 1-12
AudioAnalyzePeak         peak1;
AudioAnalyzePeak         peak2; 
AudioAnalyzePeak         peak3; 
AudioAnalyzePeak         peak4; 
AudioAnalyzePeak         peak5; 
AudioAnalyzePeak         peak6; 
AudioAnalyzePeak         peak7; 
AudioAnalyzePeak         peak8; 
AudioAnalyzePeak         peak9; 
AudioAnalyzePeak         peak10; 
AudioAnalyzePeak         peak11; 
AudioAnalyzePeak         peak12; 
// vocoder filters 25-48
AudioFilterStateVariable filter25;
AudioFilterStateVariable filter26;
AudioFilterStateVariable filter27;
AudioFilterStateVariable filter28;
AudioFilterStateVariable filter29;
AudioFilterStateVariable filter30;
AudioFilterStateVariable filter31;
AudioFilterStateVariable filter32;
AudioFilterStateVariable filter33;
AudioFilterStateVariable filter34;
AudioFilterStateVariable filter35;
AudioFilterStateVariable filter36;
AudioFilterStateVariable filter37;
AudioFilterStateVariable filter38;
AudioFilterStateVariable filter39;
AudioFilterStateVariable filter40;
AudioFilterStateVariable filter41;
AudioFilterStateVariable filter42;
AudioFilterStateVariable filter43;
AudioFilterStateVariable filter44;
AudioFilterStateVariable filter45;
AudioFilterStateVariable filter46;
AudioFilterStateVariable filter47;
AudioFilterStateVariable filter48;

// -------------------------------------------------------
// autotune
AudioAnalyzeNoteFrequency notefreq;        // frequency detector
AudioFilterBiquad        autotuneFilter;          // filter (biquad, easy lowpass filter)    
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

AudioConnection patchCords[108] = {

  // autotune
  AudioConnection(inputAudio, 0, autotuneFilter, 0),
  AudioConnection(autotuneFilter, 0, notefreq, 0),
  AudioConnection(autotuneFilter, 0, autotuner, 0),
  AudioConnection(autotuner, 0, sourceMixer, 1),
  
  // Vocoder
  AudioConnection(inputAudio, 1, carrierMixer, 0),
  AudioConnection(synthMixer, 0, carrierMixer, 1),
  AudioConnection(inputAudio, 0, modulatorGain, 0),
  // modulatorGain to filters
  AudioConnection(modulatorGain, 0, filter1, 0),
  AudioConnection(modulatorGain, 0, filter3, 0),
  AudioConnection(modulatorGain, 0, filter5, 0),
  AudioConnection(modulatorGain, 0, filter7, 0),
  AudioConnection(modulatorGain, 0, filter9, 0),
  AudioConnection(modulatorGain, 0, filter11, 0),
  AudioConnection(modulatorGain, 0, filter13, 0),
  AudioConnection(modulatorGain, 0, filter15, 0),
  AudioConnection(modulatorGain, 0, filter17, 0),
  AudioConnection(modulatorGain, 0, filter19, 0),
  AudioConnection(modulatorGain, 0, filter21, 0),
  AudioConnection(modulatorGain, 0, filter23, 0),
  // filter to filter (analyzer)
  AudioConnection(filter1, 0, filter2, 0),
  AudioConnection(filter3, 0, filter4, 0),
  AudioConnection(filter5, 0, filter6, 0),
  AudioConnection(filter7, 0, filter8, 0),
  AudioConnection(filter9, 0, filter10, 0),
  AudioConnection(filter11, 0, filter12, 0),
  AudioConnection(filter13, 0, filter14, 0),
  AudioConnection(filter15, 0, filter16, 0),
  AudioConnection(filter17, 0, filter18, 0),
  AudioConnection(filter19, 0, filter20, 0),
  AudioConnection(filter21, 0, filter22, 0),
  AudioConnection(filter23, 0, filter24, 0),
  // filter to peak
  AudioConnection(filter2, 0, peak1, 0),
  AudioConnection(filter4, 0, peak2, 0),
  AudioConnection(filter6, 0, peak3, 0),
  AudioConnection(filter8, 0, peak4, 0),
  AudioConnection(filter10, 0, peak5, 0),
  AudioConnection(filter12, 0, peak6, 0),
  AudioConnection(filter14, 0, peak7, 0),
  AudioConnection(filter16, 0, peak8, 0),
  AudioConnection(filter18, 0, peak9, 0),
  AudioConnection(filter20, 0, peak10, 0),
  AudioConnection(filter22, 0, peak11, 0),
  AudioConnection(filter24, 0, peak12, 0),
  //
  AudioConnection(carrierMixer, 0, sourceMixer, 3),
  AudioConnection(carrierMixer, 0, multiply1, 1),
  // carrierMixer to filters
  AudioConnection(carrierMixer, 0, filter25, 0),
  AudioConnection(carrierMixer, 0, filter27, 0),
  AudioConnection(carrierMixer, 0, filter29, 0),
  AudioConnection(carrierMixer, 0, filter31, 0),
  AudioConnection(carrierMixer, 0, filter33, 0),
  AudioConnection(carrierMixer, 0, filter35, 0),
  AudioConnection(carrierMixer, 0, filter37, 0),
  AudioConnection(carrierMixer, 0, filter39, 0),
  AudioConnection(carrierMixer, 0, filter41, 0),
  AudioConnection(carrierMixer, 0, filter43, 0),
  AudioConnection(carrierMixer, 0, filter45, 0),
  AudioConnection(carrierMixer, 0, filter47, 0),
  // filters to filters (envelope)
  AudioConnection(filter25, 0, filter26, 0),
  AudioConnection(filter27, 0, filter28, 0),
  AudioConnection(filter29, 0, filter30, 0),
  AudioConnection(filter31, 0, filter32, 0),
  AudioConnection(filter33, 0, filter34, 0),
  AudioConnection(filter35, 0, filter36, 0),
  AudioConnection(filter37, 0, filter38, 0),
  AudioConnection(filter39, 0, filter40, 0),
  AudioConnection(filter41, 0, filter42, 0),
  AudioConnection(filter43, 0, filter44, 0),
  AudioConnection(filter45, 0, filter46, 0),
  AudioConnection(filter47, 0, filter48, 0),
  // filters to mixers
  AudioConnection(filter26, 0, vocoderMixer1, 0),
  AudioConnection(filter28, 0, vocoderMixer1, 1),
  AudioConnection(filter30, 0, vocoderMixer1, 2),
  AudioConnection(filter32, 0, vocoderMixer1, 3),
  AudioConnection(filter34, 0, vocoderMixer2, 0),
  AudioConnection(filter36, 0, vocoderMixer2, 1),
  AudioConnection(filter38, 0, vocoderMixer2, 2),
  AudioConnection(filter40, 0, vocoderMixer2, 3),
  AudioConnection(filter42, 0, vocoderMixer3, 0),
  AudioConnection(filter44, 0, vocoderMixer3, 1),
  AudioConnection(filter46, 0, vocoderMixer3, 2),
  AudioConnection(filter48, 0, vocoderMixer3, 3),
  //
  AudioConnection(vocoderMixer1, 0, vocoderOut, 0),
  AudioConnection(vocoderMixer2, 0, vocoderOut, 1),
  AudioConnection(vocoderMixer3, 0, vocoderOut, 2),
  AudioConnection(vocoderOut, 0, sourceMixer, 2),

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
  AudioConnection(outputVolumeControl, 0, finalOutputAudio, 1),
};


// Define the number of voices for polyphony
const int numVoices = 4;
int voiceNote[numVoices] = {0};  // keep track of the note information
bool voiceUsed[numVoices] = {false}; // keep track of usage
unsigned long voiceStartTime[numVoices] = {0}; // keep track of timing

//Audio Components for synthesis
AudioSynthWaveform   waveform[numVoices];  // Create an array of waveforms for polyphony
AudioEffectEnvelope envelope[numVoices];  // Define envelope for each voice
AudioConnection *patchCordsWav[numVoices]; // Patchcords for WaveForms
AudioConnection *patchCordsEnv[numVoices]; // Patchcords for Envelopes


// Buffers for flanger and chorus effects
static const int FLANGE_BUFFER_SIZE = 512;
DMAMEM short flangeBuffer[FLANGE_BUFFER_SIZE];
static const int CHORUS_BUFFER_SIZE = 512;
DMAMEM short chorusBuffer[CHORUS_BUFFER_SIZE];

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

// values for vocoder
const float res = 5;                                            // this is used as resonance value of all state variable filters
const float attack = 0.995884;                                   // controls attack and decay, must not exceed or equal 1,
                                                                // going near 1 decreases attack, must be set at a right value to minimize distortion,
                                                                // while still responsive to voice, this parameter is CPU speed dependent
float threshold = 0.5;                                    // threshold value used to limit sound levels going to mixer used as amplitude
                                                                // modulators
const float freq[37] = {                                        // filter frequency table, tuned to specified musical notes
  110.0000000,  // A2   freq[0]
  123.4708253,  // B2   freq[1]
  138.5913155,  // C#3  freq[2]
  155.5634919,  // D#3  freq[3]
  174.6141157,  // F3   freq[4]
  195.9977180,  // G3   freq[5]
  220.0000000,  // A3   freq[6]
  246.9416506,  // B3   freq[7]
  277.1826310,  // C#4  freq[8]
  311.1269837,  // D#4  freq[9]
  349.2282314,  // F4   freq[10]
  391.9954360,  // G4   freq[11]
  440.0000000,  // A4   freq[12]
  493.8833013,  // B4   freq[13]
  554.3652620,  // C#5  freq[14]
  622.2539674,  // D#5  freq[15]
  698.4564629,  // F5   freq[16]
  783.9908720,  // G5   freq[17]
  880.0000000,  // A5   freq[18]
  987.7666025,  // B5   freq[19]
  1108.730524,  // C#6  freq[20]
  1244.507935,  // D#6  freq[21]
  1396.912926,  // F6   freq[22]
  1567.981744,  // G6   freq[23]
  1760.000000,  // A6   freq[24]
  1975.533205,  // B6   freq[25]
  2217.461048,  // C#7  freq[26]
  2489.015870,  // D#7  freq[27]
  2793.825851,  // F7   freq[28]
  3135.963488,  // G7   freq[29]
  3520.000000,  // A7   freq[30]
  3951.066410,  // B7   freq[31]
  4434.922096,  // C#8  freq[32]
  4978.031740,  // D#8  freq[33]
  5587.651703,  // F8   freq[34]
  6271.926976,  // G8   freq[35]
  7040.000000   // A8   freq[36]
};
float peak1raw, peak2raw, peak3raw, peak4raw, peak5raw, peak6raw,
  peak7raw, peak8raw, peak9raw, peak10raw, peak11raw, peak12raw;
float peak1val, peak2val, peak3val, peak4val, peak5val, peak6val,
  peak7val, peak8val, peak9val, peak10val, peak11val, peak12val;

// performance test
elapsedMillis serialtimer;

// Setup routine
void setup() { 
  Serial.begin(115200);
  AudioMemory(64);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // enable Audio Shield
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.7);
  sgtl5000_1.adcHighPassFilterDisable();
  
  // enable Mixer Gain
  setMixer(sourceMixer, 0, 0, 1, 1);
  setMixer(synthMixer, 0.7, 0.7, 0.7, 0.7);
  setMixer(carrierMixer, 0, 1, 0, 0);
  setMixer(vocoderOut, 0.3, 0.3, 0.3, 0);
  setMixer(delayBus, 0, 0, 0, 0);
  setMixer(distortionBus, 0, 0, 0, 0);
  setMixer(masterMixer, 1, 0, 0, 0);
  outputVolumeControl.gain(0.5); // low output, high input (reduces noise)

  // initialize vocoder
  modulatorGain.gain(1);
  Vocoderinit();

  // initialize autotune
    // filter setup
    autotuneFilter.setLowpass(0, 3400, 0.707); // Butterworth filter, 12 db/octave
    notefreq.begin(.15); // Initialize Yin Algorithm Absolute Threshold (15% is a good number)
    // autotune setup
    autotuner.currFrequency = 20;
    autotuner.manualPitchOffset = 0;

  // initialize effects
  flange1.begin(flangeBuffer, FLANGE_BUFFER_SIZE, 100, 100, 100);
  chorus1.begin(chorusBuffer, CHORUS_BUFFER_SIZE, 4);

  bitcrusher1.bits(6);
  bitcrusher1.sampleRate(26000);
  distortion.shape(distortion1, WAVESHAPE_SIZE);
  limiter.shape(limiter1, WAVESHAPE_SIZE);

  // Set up waveforms and mixer
  for (int i = 0; i < numVoices; i++) {
    waveform[i].begin(WAVEFORM_SAWTOOTH);
    waveform[i].amplitude(0);
    envelope[i].attack(10); // Attack time in milliseconds
    envelope[i].decay(100); // Decay time
    envelope[i].sustain(0.5); // Sustain level
    envelope[i].release(300); // Release time
    
    patchCordsWav[i] = new AudioConnection(waveform[i], 0, envelope[i], 0);
    patchCordsEnv[i] = new AudioConnection(envelope[i], 0, synthMixer, i);
  } 

  AudioProcessorUsageMaxReset();                                // and reset these things
  AudioMemoryUsageMaxReset();
  filter1.processorUsageMaxReset();
  autotuner.processorUsageMaxReset();
  serialtimer = 0;                        
}

// Loop routine
void loop() {
  // Read commands from Serial
  readAndApplySerialCommands();
  // Read control from MIDI Signal
  readAndApplyMIDIControl();

  vocoderLoop();
  autotuneLoop();

  if(serialtimer >= 100) {                                      // and report MCU usage 10x per second
    serialtimer = 0;
    Serial.print("Processor Usage: ");
    Serial.print(AudioProcessorUsage());
    Serial.print("\nProcessor Usage Max: ");
    Serial.print(AudioProcessorUsageMax());
    Serial.print("\nMemory Usage: ");
    Serial.print(AudioMemoryUsage());
    Serial.print("\nMemory Usage Max: ");
    Serial.print(AudioMemoryUsageMax());
    Serial.print("\nfilter1 processor usage: ");
    Serial.print(filter1.processorUsageMax());
    Serial.print("\nautotune processor usage: ");
    Serial.print(autotuner.processorUsageMax());
    Serial.print("\n\n\n\n\n\n\n\n\n\n");
  }
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

    case 'S': threshold = atof(command + 1); break; // change threshold value for vocoder
    case 'C': carrierMixToggle(); break; // toggle between input channel 2 or synthMixer
    case 'R': freeverb1.roomsize(atof(command + 1)); break; // attempt to change roomsize
    default: Serial.println(("Invalid effect type")); break;
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
        Serial.println("note ON");
        if (keyNote == 72) {
            for (int i = 0; i < numVoices; i++) {
              waveform[i].frequency(0);
              waveform[i].amplitude(0);
              envelope[i].noteOff();
              voiceUsed[i] = false;
              voiceNote[i] = -1; // Reset the note number for this voice
            }
        } else {
          if(keyVelocity > 0) {
            noteOn(keyNote, keyVelocity);
          } else {
            noteOff(keyNote);
          }
        }
        Serial.print("note");
        Serial.println(keyNote);

        break;
      }
      case midi::NoteOff: // KEY_RELEASE
      {// same as NoteOn
        int keyNote = arg1; // integer 48 to 72 on the keyboard
        Serial.println("note OFF");
        Serial.print("note");
        Serial.println(keyNote);
        noteOff(keyNote);
        break;
      }
      case midi::ControlChange: // KNOBS
      {
        int controlNum = arg1; // integer 1 to 8 (the knob number)
        int controlVal = usbMIDI.getData2(); // integer 0 to 127

        if(controlNum == 1) { // MASTER_VOLUME
          outputVolumeControl.gain(convertKnob(controlVal, 0, 6));
        }
        if(controlNum == 4) { // AUTOTUNE_PITCH_BEND
          autotuner.manualPitchOffset = convertKnob(controlVal, -0.5, 2);
        }
        if(controlNum == 5) { // MICROPHONE
          sourceMixer.gain(0, convertKnob(controlVal, 0, 2)); 
        }
        if(controlNum == 6) { // CARRIER
          sourceMixer.gain(3, convertKnob(controlVal, 0, 1)); 
        }
        if(controlNum == 7) { // VOCODER
          sourceMixer.gain(2, convertKnob(controlVal, 0, 2)); 
        }
        if(controlNum == 8) { // AUTOTUNE
          sourceMixer.gain(1, convertKnob(controlVal, 0, 2)); 
        }
        Serial.print(controlNum);
        Serial.println(controlVal);
        // do something with these values
        break;
      }
      case midi::PitchBend: // PITCH STICK
      {
        int pitchValue = arg1; // The amount of bend to send (in a signed integer format), between MIDI_PITCHBEND_MIN and MIDI_PITCHBEND_MAX, center value is 0.
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
        Serial.print(pad_note);
        Serial.print(pad_velocity);
        break;}
      case midi::NoteOff: // PAD_RELEASE
        {// same as NoteOn
        break;}
      }
    } // end MIDI
}

// vocoder init
void Vocoderinit(){

  // set the resonance of the filters
  filter1.resonance(res); filter2.resonance(res); filter3.resonance(res); filter4.resonance(res); filter5.resonance(res);
  filter6.resonance(res); filter7.resonance(res); filter8.resonance(res); filter9.resonance(res); filter10.resonance(res);
  filter11.resonance(res); filter12.resonance(res); filter13.resonance(res); filter14.resonance(res); filter15.resonance(res);
  filter16.resonance(res); filter17.resonance(res); filter18.resonance(res); filter19.resonance(res); filter20.resonance(res);
  filter21.resonance(res); filter22.resonance(res); filter23.resonance(res); filter24.resonance(res); filter25.resonance(res);
  filter26.resonance(res); filter27.resonance(res); filter28.resonance(res); filter29.resonance(res); filter30.resonance(res);
  filter31.resonance(res); filter32.resonance(res); filter33.resonance(res); filter34.resonance(res); filter35.resonance(res);
  filter36.resonance(res); filter37.resonance(res); filter38.resonance(res); filter39.resonance(res); filter40.resonance(res);
  filter41.resonance(res); filter42.resonance(res); filter43.resonance(res); filter44.resonance(res); filter45.resonance(res);
  filter46.resonance(res); filter47.resonance(res); filter48.resonance(res);

  // set the frequencies of the filters
  // pairs of cascaded filters for optimal frequency isolation
  // two sets of filters are used: for voice signal analysis and instrument/synth filter
  filter1.frequency(freq[0]); filter2.frequency(freq[0]); filter3.frequency(freq[3]); filter4.frequency(freq[3]);
  filter5.frequency(freq[6]); filter6.frequency(freq[6]); filter7.frequency(freq[9]); filter8.frequency(freq[9]);
  filter9.frequency(freq[12]); filter10.frequency(freq[12]); filter11.frequency(freq[15]); filter12.frequency(freq[15]);
  filter13.frequency(freq[18]); filter14.frequency(freq[18]); filter15.frequency(freq[21]); filter16.frequency(freq[21]);
  filter17.frequency(freq[24]); filter18.frequency(freq[24]); filter19.frequency(freq[27]); filter20.frequency(freq[27]);
  filter21.frequency(freq[30]); filter22.frequency(freq[30]); filter23.frequency(freq[33]); filter24.frequency(freq[33]);
  filter25.frequency(freq[0]); filter26.frequency(freq[0]); filter27.frequency(freq[3]); filter28.frequency(freq[3]);
  filter29.frequency(freq[6]); filter30.frequency(freq[6]); filter31.frequency(freq[9]); filter32.frequency(freq[9]);
  filter33.frequency(freq[12]); filter34.frequency(freq[12]); filter35.frequency(freq[15]); filter36.frequency(freq[15]);
  filter37.frequency(freq[18]); filter38.frequency(freq[18]); filter39.frequency(freq[21]); filter40.frequency(freq[21]);
  filter41.frequency(freq[24]); filter42.frequency(freq[24]); filter43.frequency(freq[27]); filter44.frequency(freq[27]);
  filter45.frequency(freq[30]); filter46.frequency(freq[30]); filter47.frequency(freq[33]); filter48.frequency(freq[33]);

  // initialize peak values   
  peak1raw = 1; peak2raw = 1; peak3raw = 1; peak4raw =  1; peak5raw =  1; peak6raw =  1;
  peak7raw = 1; peak8raw = 1; peak9raw = 1; peak10raw = 1; peak11raw = 1; peak12raw = 1;
  peak1val = 1; peak2val = 1; peak3val = 1; peak4val =  1; peak5val =  1; peak6val =  1;
  peak7val = 1; peak8val = 1; peak9val = 1; peak10val = 1; peak11val = 1; peak12val = 1;

  setMixer(vocoderMixer1, 0, 0, 0, 0);
  setMixer(vocoderMixer2, 0, 0, 0, 0);
  setMixer(vocoderMixer3, 0, 0, 0, 0);
}

// vocoder code in main loop
void vocoderLoop() {
  AudioNoInterrupts();
    // store peak values at each read
  if(peak1.available()) {peak1raw = peak1.read();}
  if(peak2.available()) {peak2raw = peak2.read();}
  if(peak3.available()) {peak3raw = peak3.read();}
  if(peak4.available()) {peak4raw = peak4.read();}
  if(peak5.available()) {peak5raw = peak5.read();}
  if(peak6.available()) {peak6raw = peak6.read();}
  if(peak7.available()) {peak7raw = peak7.read();}
  if(peak8.available()) {peak8raw = peak8.read();}
  if(peak9.available()) {peak9raw = peak9.read();}
  if(peak10.available()) {peak10raw = peak10.read();}
  if(peak11.available()) {peak11raw = peak11.read();}
  if(peak12.available()) {peak12raw = peak12.read();}

  setEnvelope(peak1raw, peak1val, vocoderMixer1, 0);         // simulate envelope follower: it gets the envelope of the filtered signal through
  setEnvelope(peak2raw, peak2val, vocoderMixer1, 1);         // the peak values and is used to determine the direction (increase or decrease) of
  setEnvelope(peak3raw, peak3val, vocoderMixer1, 2);         // the mixer gain
  setEnvelope(peak4raw, peak4val, vocoderMixer1, 3);         // peak values used to set mixer gain are divided to increase or multiplied to decrease
  setEnvelope(peak5raw, peak5val, vocoderMixer2, 0);         // the values must not change fast to avoid distortion
  setEnvelope(peak6raw, peak6val, vocoderMixer2, 1);
  setEnvelope(peak7raw, peak7val, vocoderMixer2, 2);
  setEnvelope(peak8raw, peak8val, vocoderMixer2, 3);
  setEnvelope(peak9raw, peak9val, vocoderMixer3, 0);
  setEnvelope(peak10raw, peak10val, vocoderMixer3, 1);
  setEnvelope(peak11raw, peak11val, vocoderMixer3, 2);
  setEnvelope(peak12raw, peak12val, vocoderMixer3, 3);
  AudioInterrupts();
}

// autotune code in main loop
void autotuneLoop() {
      // read current fundamental frequency into AutoTune
    if(notefreq.available()) {
      float note = notefreq.read();
      float prob = notefreq.probability();
      if(prob > 0.99) {
        if(note > 80 && note < 880) {
          Serial.printf("Note: %3.2f | Probably %.2f\n", note, prob);
          autotuner.currFrequency = note;
          Serial.print("target: ");
      Serial.println(autotuner.computeNearestSemitone(note));
      Serial.print("manual: ");
      Serial.println(autotuner.manualPitchOffset);
      Serial.print("shift ratio: ");
      float pitchShift = autotuner.computeNearestSemitone(note) / note + autotuner.manualPitchOffset;
      pitchShift = (pitchShift < 0.51) ? 0.51 : ((pitchShift > 1.99) ? 1.99 : pitchShift);
        }
      }
    }
}

// set envelope
void setEnvelope(float peakRaw, float& peakVal, AudioMixer4& mixer, int channel){
  if((peakRaw * threshold) > peakVal) {
    peakVal = peakVal / attack;
    peakVal = (peakVal > 1) ? 1 : peakVal;
    mixer.gain(channel, peakVal);
  }
  if((peakRaw * threshold) < peakVal) {
    peakVal = peakVal * attack;
    peakVal = (peakVal > 1) ? 1 : peakVal;
    mixer.gain(channel, peakVal);
  }
}

// Set mixer gain
void setMixerGain(AudioMixer4& mixer, uint8_t channel, const char *gainStr) {
  float gainValue = atof(gainStr);
  mixer.gain(channel, gainValue);
}
//edits a mixer to set gain of each channel
void setMixer(AudioMixer4& mixer, float c0, float c1, float c2, float c3){
    mixer.gain(0, c0);
    mixer.gain(1, c1);
    mixer.gain(2, c2);
    mixer.gain(3, c3);
}

bool isSynth = true;
void carrierMixToggle() {
  if(isSynth) {
    setMixer(carrierMixer, 1, 0, 0, 0);
  } else {
    setMixer(carrierMixer, 0, 1, 0, 0);
  }
  isSynth = !isSynth;
}

// MIDi control functions
void noteOn(uint8_t note, uint8_t velocity) {
  int freeVoice = -1;
  unsigned long oldestTime = millis();
  int oldestVoice = 0;

  for (int i = 0; i < numVoices; i++) {
    if (voiceNote[i] == note) { // TODO: test if this prevents playing a duplicate note, which I think is the cause
      freeVoice = i;
      break;
    }
    if (!voiceUsed[i]) { 
      freeVoice = i;
      //break;
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
    voiceStartTime[freeVoice] = millis();
  } else { // replace with an existing voice
    float frequency = noteToFrequency(note);
    waveform[oldestVoice].frequency(frequency);
    waveform[oldestVoice].amplitude(velocity / 127.0);
    envelope[oldestVoice].noteOn();
    voiceUsed[oldestVoice] = true;
    voiceNote[oldestVoice] = note; // Store the note number that this voice is now playing
    voiceStartTime[oldestVoice] = millis();
  }
}

void noteOff(uint8_t note) {
  for (int i = 0; i < numVoices; i++) {
    if (voiceUsed[i] && voiceNote[i] == note) { // Check if this voice is playing the note
      waveform[i].frequency(0);
      waveform[i].amplitude(0);
      envelope[i].noteOff();
      voiceUsed[i] = false;
      voiceNote[i] = -1; // Reset the note number for this voice
    }
  }
}

float noteToFrequency(uint8_t note) {
  return 440.0 * pow(2.0, (note - 69) / 12.0);
}

// convert a knob value from range 0, 127 to a range lower_bound, upper_bound
float convertKnob(float knob_value, float lower_bound, float upper_bound) {
  return lower_bound + ((knob_value - 0) / static_cast<float>(127 - 0)) * (upper_bound - lower_bound);
  // autotuner.manualPitchOffset = AUTOTUNE_MIN_PS + ((controlVal - 0) / static_cast<float>(127 - 0)) * (AUTOTUNE_MAX_PS - AUTOTUNE_MIN_PS);
}
