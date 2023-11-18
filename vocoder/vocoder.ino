#include <Audio.h>
#include <MIDI.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//DONOT EDIT THIS BECAUSE YOU NEED IT TO GET THE SYSTEM DESIGN TOOL
// GUItool: begin automatically generated code
// AudioSynthWaveform       waveform1;      //xy=82.22222137451172,300.63492584228516
// AudioSynthWaveform       waveform2;      //xy=82.22222518920898,337.7777862548828
// AudioSynthWaveform       waveform3;      //xy=82.22222137451172,376.666654586792
// AudioSynthWaveform       waveform4; //xy=82.77777624130249,414.4444160461426
AudioInputI2S            i2s1;           //xy=85.42857360839844,212.85715866088867
//AudioEffectEnvelope      envelope4; //xy=91.42857360839844,612.857177734375
AudioMixer4              synthMixer;        //xy=91.74603271484375,739.365104675293
//AudioEffectEnvelope      envelope3; //xy=95.71428680419922,574.2857055664062
//AudioEffectEnvelope      envelope1;      //xy=97.14286041259766,500.00002098083496
//AudioEffectEnvelope      envelope2; //xy=97.14286041259766,538.5714111328125
AudioMixer4              carrierMix;         //xy=292.857120513916,698.571361541748
AudioFilterStateVariable filter29; //xy=297.80159759521484,933.9483222961426
AudioFilterStateVariable filter27; //xy=298.80159759521484,873.9483222961426
AudioFilterStateVariable filter25; //xy=299.80159759521484,813.9483222961426
AudioFilterStateVariable filter31; //xy=299.80159759521484,991.9483222961426
AudioAmplifier           modulatorGain;           //xy=312.85712814331055,312.8571357727051
AudioFilterStateVariable filter5;        //xy=343.99999237060547,536.4285507202148
AudioFilterStateVariable filter3;        //xy=344.99999237060547,476.42855072021484
AudioFilterStateVariable filter1;        //xy=345.99999237060547,416.42855072021484
AudioFilterStateVariable filter7; //xy=345.99999237060547,594.4285507202148
AudioFilterStateVariable filter30; //xy=422.80159759521484,932.9483222961426
AudioFilterStateVariable filter32; //xy=424.80159759521484,990.9483222961426
AudioFilterStateVariable filter28; //xy=425.80159759521484,872.9483222961426
AudioFilterStateVariable filter26; //xy=427.80159759521484,812.9483222961426
AudioFilterStateVariable filter6;        //xy=468.99999237060547,535.4285507202148
AudioFilterStateVariable filter8; //xy=470.99999237060547,593.4285507202148
AudioFilterStateVariable filter4;        //xy=471.99999237060547,475.42855072021484
AudioFilterStateVariable filter2;        //xy=473.99999237060547,415.42855072021484
AudioAnalyzePeak         peak4;  //xy=603.3331798977322,589.2063342200386
AudioAnalyzePeak         peak3; //xy=605.555534362793,530.3174362182617
AudioAnalyzePeak         peak2; //xy=606.6665267944336,472.53967094421387
AudioAnalyzePeak         peak1;          //xy=608.8888812594944,413.650772942437
AudioMixer4              mixer6;         //xy=627.9365310668945,1135.079360961914
AudioFilterStateVariable filter37; //xy=635.2142677307129,941.5197238922119
AudioFilterStateVariable filter35; //xy=637.3253860473633,885.9641666412354
AudioFilterStateVariable filter39; //xy=637.2142677307129,999.5197238922119
AudioFilterStateVariable filter33; //xy=638.3253860473633,825.9641666412354
AudioFilterStateVariable filter13; //xy=734.1110954284668,533.2063369750977
AudioFilterStateVariable filter11; //xy=736.2222137451172,477.6507797241211
AudioFilterStateVariable filter15; //xy=736.1110954284668,591.2063369750977
AudioFilterStateVariable filter9; //xy=737.2222137451172,417.6507797241211
AudioFilterStateVariable filter38; //xy=760.2142677307129,940.5197238922119
AudioFilterStateVariable filter40; //xy=762.2142677307129,998.5197238922119
AudioFilterStateVariable filter36; //xy=764.3253860473633,884.9641666412354
AudioFilterStateVariable filter34; //xy=766.3253860473633,824.9641666412354
AudioFilterStateVariable filter14; //xy=859.1110954284668,532.2063369750977
AudioFilterStateVariable filter16; //xy=861.1110954284668,590.2063369750977
AudioFilterStateVariable filter12; //xy=863.2222137451172,476.6507797241211
AudioFilterStateVariable filter10; //xy=865.2222137451172,416.6507797241211
AudioAnalyzePeak         peak8; //xy=994.4442910088433,589.206333372328
AudioAnalyzePeak         peak7; //xy=996.666645473904,530.3174353705513
AudioAnalyzePeak         peak6; //xy=997.7776379055447,472.5396700965034
AudioAnalyzePeak         peak5; //xy=999.9999923706055,413.65077209472656
AudioMixer4              mixer7;         //xy=1005.7143402099609,1145.714319229126
AudioFilterStateVariable filter41; //xy=1009.5951766967773,827.5832996368408
AudioFilterStateVariable filter45; //xy=1011.2617835998535,944.0277366638184
AudioFilterStateVariable filter43; //xy=1011.5951766967773,885.5832996368408
AudioFilterStateVariable filter47; //xy=1013.2617835998535,1002.0277366638184
AudioFilterStateVariable filter42; //xy=1134.5951766967773,826.5832996368408
AudioFilterStateVariable filter46; //xy=1136.2617835998535,943.0277366638184
AudioFilterStateVariable filter44; //xy=1136.5951766967773,884.5832996368408
AudioFilterStateVariable filter48; //xy=1138.2617835998535,1001.0277366638184
AudioFilterStateVariable filter17; //xy=1161.6666793823242,412.7618942260742
AudioFilterStateVariable filter21; //xy=1163.3332862854004,529.2063312530518
AudioFilterStateVariable filter19; //xy=1163.6666793823242,470.7618942260742
AudioFilterStateVariable filter23; //xy=1165.3332862854004,587.2063312530518
AudioFilterStateVariable filter18; //xy=1286.6666793823242,411.7618942260742
AudioFilterStateVariable filter22; //xy=1288.3332862854004,528.2063312530518
AudioFilterStateVariable filter20; //xy=1288.6666793823242,469.7618942260742
AudioFilterStateVariable filter24; //xy=1290.3332862854004,586.2063312530518
AudioMixer4              mixer8;         //xy=1379.9999732971191,1145.7143020629883
AudioMixer4              vocoderOut;         //xy=1418.8095779418945,755.0000057220459
AudioAnalyzePeak         peak12;  //xy=1426.6665009392632,583.6507780287001
AudioAnalyzePeak         peak11; //xy=1428.888855404324,524.7618800269233
AudioAnalyzePeak         peak10; //xy=1429.9998478359646,466.9841147528755
AudioAnalyzePeak         peak9; //xy=1432.2222023010254,408.09521675109863
AudioAmplifier           amp1;           //xy=1562.8571395874023,768.5713920593262
AudioOutputI2S           i2s2;           //xy=1688.5714285714284,779.9999999999999
//AudioConnection          patchCord1(waveform1, envelope1);
//AudioConnection          patchCord2(waveform2, envelope2);
//AudioConnection          patchCord3(waveform3, envelope3);
//AudioConnection          patchCord4(waveform4, envelope4);
AudioConnection          patchCord5(i2s1, 0, modulatorGain, 0);
AudioConnection          patchCord6(i2s1, 1, carrierMix, 0);
// AudioConnection          patchCord7(envelope4, 0, synthMixer, 3);
AudioConnection          patchCord8(synthMixer, 0, carrierMix, 1);
// AudioConnection          patchCord9(envelope3, 0, synthMixer, 2);
// AudioConnection          patchCord10(envelope1, 0, synthMixer, 0);
// AudioConnection          patchCord11(envelope2, 0, synthMixer, 1);
AudioConnection          patchCord12(carrierMix, 0, filter25, 0);
AudioConnection          patchCord13(carrierMix, 0, filter27, 0);
AudioConnection          patchCord14(carrierMix, 0, filter29, 0);
AudioConnection          patchCord15(carrierMix, 0, filter31, 0);
AudioConnection          patchCord16(carrierMix, 0, filter33, 0);
AudioConnection          patchCord17(carrierMix, 0, filter35, 0);
AudioConnection          patchCord18(carrierMix, 0, filter37, 0);
AudioConnection          patchCord19(carrierMix, 0, filter39, 0);
AudioConnection          patchCord20(carrierMix, 0, filter41, 0);
AudioConnection          patchCord21(carrierMix, 0, filter43, 0);
AudioConnection          patchCord22(carrierMix, 0, filter45, 0);
AudioConnection          patchCord23(carrierMix, 0, filter47, 0);
AudioConnection          patchCord24(filter29, 1, filter30, 0);
AudioConnection          patchCord25(filter27, 1, filter28, 0);
AudioConnection          patchCord26(filter25, 0, filter26, 0);
AudioConnection          patchCord27(filter31, 1, filter32, 0);
AudioConnection          patchCord28(modulatorGain, 0, filter1, 0);
AudioConnection          patchCord29(modulatorGain, 0, filter3, 0);
AudioConnection          patchCord30(modulatorGain, 0, filter5, 0);
AudioConnection          patchCord31(modulatorGain, 0, filter7, 0);
AudioConnection          patchCord32(modulatorGain, 0, filter9, 0);
AudioConnection          patchCord33(modulatorGain, 0, filter11, 0);
AudioConnection          patchCord34(modulatorGain, 0, filter13, 0);
AudioConnection          patchCord35(modulatorGain, 0, filter15, 0);
AudioConnection          patchCord36(modulatorGain, 0, filter17, 0);
AudioConnection          patchCord37(modulatorGain, 0, filter19, 0);
AudioConnection          patchCord38(modulatorGain, 0, filter21, 0);
AudioConnection          patchCord39(modulatorGain, 0, filter23, 0);
AudioConnection          patchCord40(filter5, 1, filter6, 0);
AudioConnection          patchCord41(filter3, 1, filter4, 0);
AudioConnection          patchCord42(filter1, 0, filter2, 0);
AudioConnection          patchCord43(filter7, 1, filter8, 0);
AudioConnection          patchCord44(filter30, 1, mixer6, 2);
AudioConnection          patchCord45(filter32, 1, mixer6, 3);
AudioConnection          patchCord46(filter28, 1, mixer6, 1);
AudioConnection          patchCord47(filter26, 0, mixer6, 0);
AudioConnection          patchCord48(filter6, 1, peak3, 0);
AudioConnection          patchCord49(filter8, 1, peak4, 0);
AudioConnection          patchCord50(filter4, 1, peak2, 0);
AudioConnection          patchCord51(filter2, 1, peak1, 0);
AudioConnection          patchCord52(mixer6, 0, vocoderOut, 0);
AudioConnection          patchCord53(filter37, 1, filter38, 0);
AudioConnection          patchCord54(filter35, 1, filter36, 0);
AudioConnection          patchCord55(filter39, 1, filter40, 0);
AudioConnection          patchCord56(filter33, 1, filter34, 0);
AudioConnection          patchCord57(filter13, 1, filter14, 0);
AudioConnection          patchCord58(filter11, 1, filter12, 0);
AudioConnection          patchCord59(filter15, 1, filter16, 0);
AudioConnection          patchCord60(filter9, 1, filter10, 0);
AudioConnection          patchCord61(filter38, 1, mixer7, 2);
AudioConnection          patchCord62(filter40, 1, mixer7, 3);
AudioConnection          patchCord63(filter36, 1, mixer7, 1);
AudioConnection          patchCord64(filter34, 1, mixer7, 0);
AudioConnection          patchCord65(filter14, 1, peak7, 0);
AudioConnection          patchCord66(filter16, 1, peak8, 0);
AudioConnection          patchCord67(filter12, 1, peak6, 0);
AudioConnection          patchCord68(filter10, 1, peak5, 0);
AudioConnection          patchCord69(mixer7, 0, vocoderOut, 1);
AudioConnection          patchCord70(filter41, 1, filter42, 0);
AudioConnection          patchCord71(filter45, 1, filter46, 0);
AudioConnection          patchCord72(filter43, 1, filter44, 0);
AudioConnection          patchCord73(filter47, 1, filter48, 0);
AudioConnection          patchCord74(filter42, 1, mixer8, 0);
AudioConnection          patchCord75(filter46, 1, mixer8, 2);
AudioConnection          patchCord76(filter44, 1, mixer8, 1);
AudioConnection          patchCord77(filter48, 1, mixer8, 3);
AudioConnection          patchCord78(filter17, 1, filter18, 0);
AudioConnection          patchCord79(filter21, 1, filter22, 0);
AudioConnection          patchCord80(filter19, 1, filter20, 0);
AudioConnection          patchCord81(filter23, 1, filter24, 0);
AudioConnection          patchCord82(filter18, 1, peak9, 0);
AudioConnection          patchCord83(filter22, 1, peak11, 0);
AudioConnection          patchCord84(filter20, 1, peak10, 0);
AudioConnection          patchCord85(filter24, 2, peak12, 0);
AudioConnection          patchCord86(mixer8, 0, vocoderOut, 2);
AudioConnection          patchCord87(vocoderOut, amp1);
AudioConnection          patchCord88(amp1, 0, i2s2, 0);
AudioConnection          patchCord89(amp1, 0, i2s2, 1);
AudioControlSGTL5000     audioShield;     //xy=96.74602508544922,165.6666660308838
// GUItool: end automatically generated code


// Define the number of voices for polyphony
const int numVoices = 4;
int voiceNote[numVoices] = {-1}; 

// Array to keep track of voice usage
bool voiceUsed[numVoices] = {false};

//Audio Components for synthesis
MIDI_CREATE_DEFAULT_INSTANCE();
AudioSynthWaveform   waveform[numVoices];  // Create an array of waveforms for polyphony
AudioEffectEnvelope envelope[numVoices];  // Define envelope for each voice
AudioConnection      *patchCords[numVoices * 2];  // Patch cords for waveforms to mixer

AudioConnection patchWaveforms[numVoices] {
  AudioConnection(waveform[0], 0, envelope[0], 0),
  AudioConnection(waveform[1], 0, envelope[1], 0),
  AudioConnection(waveform[2], 0, envelope[2], 0),
  AudioConnection(waveform[3], 0, envelope[3], 0),
};

AudioConnection patchEnvelopes[numVoices] {
  AudioConnection(envelope[0], 0, synthMixer, 0),
  AudioConnection(envelope[1], 0, synthMixer, 1),
  AudioConnection(envelope[2], 0, synthMixer, 2),
  AudioConnection(envelope[3], 0, synthMixer, 3),
};

// Set up waveforms and mixer
for (int i = 0; i < numVoices; i++) {
  waveform[i].begin(WAVEFORM_SINE);
  waveform[i].amplitude(0);
}
 
for (int i = 0; i < numVoices; i++) {
  envelope[i].attack(10); // Attack time in milliseconds
  envelope[i].decay(100); // Decay time
  envelope[i].sustain(0.5); // Sustain level
  envelope[i].release(300); // Release time
}

const float res = 5;                                            // this is used as resonance value of all state variable filters
const float attack = 0.99588;                                   // controls attack and decay, must not exceed or equal 1,
                                                                // going near 1 decreases attack, must be set at a right value to minimize distortion,
                                                                // while still responsive to voice, this parameter is CPU speed dependent
const float threshold = 0.1;                                    // threshold value used to limit sound levels going to mixer used as amplitude
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

const int myInput = AUDIO_INPUT_MIC;

//void setEnvelope(float peakRaw, float &peakVal, AudioMixer4 mixer, int channel);

void setup() {
  Serial.begin(9600);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  delay(300);
  
  //pinMode(ledPin, OUTPUT);    // used to check timing using a oscilloscope
  //pinMode(FIR_PASSTHRU, INPUT_PULLUP);
  
  // allocate memory for the audio library
  AudioMemory(64);  // how memory blocks are really needed?

  Vocoderinit();

  //initialize audioshield
  audioShield.enable();      // configure the sgtl5000
  audioShield.inputSelect(myInput);
  audioShield.volume(0.5);
  audioShield.adcHighPassFilterDisable();

  //set initial mixer gains
  modulatorGain.gain(0.5); //gain of microphone signal (I2S left input)
  setMixer(carrierMix, 0, 0, 0, 0); //channel 1 for synthesized audio, no carrier input yet
//  sourceMixer.gain(0, 0); //dry audio input (I2S left input)
//  sourceMixer.gain(1, 0); //autotuned audio input
//  sourceMixer.gain(2, 1); //vocoder input
//  delayBus.gain(0, 1); //dry input
//  delayBus.gain(1, 0); //reverbed input
//  delayBus.gain(2, 0); //chorus input
//  delayBus.gain(3, 0); //bitcrush input
//  distortionBus.gain(0, 0); //dry input
//  distortionBus.gain(1, 0); //reverbed input
//  distortionBus.gain(2, 0); //chorus input
//  distortionBus.gain(3, 0); //bitcrush input
//  master.gain(0, 1); //delay bus
//  master.gain(1, 1); //distortion bus
  amp1.gain(1);

  AudioProcessorUsageMaxReset();                                // and reset these things
  AudioMemoryUsageMaxReset();                                   // I'm doing this cause the source code did it idk if it's necessary
//  SPI.setMOSI(SDCARD_MOSI_PIN);
//  SPI.setSCK(SDCARD_SCK_PIN);
//  if (!(SD.begin(SDCARD_CS_PIN))) {
//    while (1) {
//       Serial.println("Unable to access the SD card");
//      delay(500);
//    }
//  }
//  delay(1000);
//}
}

void loop() {
//  if(playSdWav1.isPlaying() == false) {     //uncomment if we're using SD card to play
//    Serial.println("Start playing");
//    playSdWav1.play("SABER.WAV");
//    delay(10); // wait for library to parse WAV info
//  }
        // read midi signal
    // Channel 0 = Keys, Knobs
    if(usbMIDI.read(0)) {
      switch (usbMIDI.getType()) {
      case midi::NoteOn: // KEY_PRESS
        {
        int keyNote = usbMIDI.getData1(); // integer 48 to 72 on the keyboard
        int keyVelocity = usbMIDI.getData2(); // 0 to 100
        noteOn(keyNote, keyVelocity);
        Serial.print("Note = ");
        Serial.print(keyNote);
        Serial.print(", Velocity = ");
        Serial.print(keyVelocity);
        break;
        }
      case midi::NoteOff: // KEY_RELEASE
        {// same as NoteOn
        int keyNote = usbMIDI.getData1(); // integer 48 to 72 on the keyboard
        noteOff(keyNote);
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

  setEnvelope(peak1raw, peak1val, mixer6, 0);         // simulate envelope follower: it gets the envelope of the filtered signal through
  setEnvelope(peak2raw, peak2val, mixer6, 1);         // the peak values and is used to determine the direction (increase or decrease) of
  setEnvelope(peak3raw, peak3val, mixer6, 2);         // the mixer gain
  setEnvelope(peak4raw, peak4val, mixer6, 3);         // peak values used to set mixer gain are divided to increase or multiplied to decrease
  setEnvelope(peak5raw, peak5val, mixer7, 0);         // the values must not change fast to avoid distortion
  setEnvelope(peak6raw, peak6val, mixer7, 1);
  setEnvelope(peak7raw, peak7val, mixer7, 2);
  setEnvelope(peak8raw, peak8val, mixer7, 3);
  setEnvelope(peak9raw, peak9val, mixer8, 0);
  setEnvelope(peak10raw, peak10val, mixer8, 1);
  setEnvelope(peak11raw, peak11val, mixer8, 2);
  setEnvelope(peak12raw, peak12val, mixer8, 3);
 
  
//  if(serialtimer >= 100) {                                      // and report MCU usage 10x per second
//    serialtimer = 0;
//    Serial.print("Processor Usage: ");
//    Serial.print(AudioProcessorUsage());
//    Serial.print("\nProcessor Usage Max: ");
//    Serial.print(AudioProcessorUsageMax());
//    Serial.print("\nMemory Usage: ");
//    Serial.print(AudioMemoryUsage());
//    Serial.print("\nMemory Usage Max: ");
//    Serial.print(AudioMemoryUsageMax());
//    Serial.print("\n\n\n\n\n\n\n\n\n\n");
//  }
}


void setEnvelope(float peakRaw, float &peakVal, AudioMixer4 mixer, int channel){
  if((peakRaw * threshold) > peakVal) {
    peakVal = peakVal / attack;
    mixer.gain(channel, peakVal);
  }
  if((peakRaw * threshold) < peakVal) {
    peakVal = peakVal * attack;
    mixer.gain(channel, peakVal);
  }
}


//initializes Vocoder filters
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
  peak1val = 1; peak2val = 1; peak3val = 1; peak4val = 1; peak5val = 1; peak6val = 1;
  peak7val = 1; peak8val = 1; peak9val = 1; peak10val = 1; peak11val = 1; peak12val = 1;

  setMixer(synthMixer, 0, 0, 0, 0);
  setMixer(vocoderOut, 0,0,0, 0);
  setMixer(mixer6, 0, 0, 0, 0);
  setMixer(mixer7, 0, 0, 0, 0);
  setMixer(mixer8, 0, 0, 0, 0);

}

//edits a mixer to set gain of each channel
void setMixer(AudioMixer4 mixer, float c0, float c1, float c2, float c3){
    mixer.gain(0, c0);
    mixer.gain(1, c1);
    mixer.gain(2, c2);
    mixer.gain(3, c3);
}


void noteOn(uint8_t note, uint8_t velocity) {
  for (int i = 0; i < numVoices; i++) {
    if (!voiceUsed[i]) {
      float frequency = noteToFrequency(note);
      waveform[i].frequency(frequency);
      waveform[i].amplitude(velocity / 127.0);
      envelope[i].noteOn();
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
      envelope[i].noteOff();
      voiceUsed[i] = false;
      voiceNote[i] = -1; // Reset the note number for this voice
      break;
    }
  }
}

float noteToFrequency(uint8_t note) {
  return 440.0 * pow(2.0, (note - 69) / 12.0);
}
