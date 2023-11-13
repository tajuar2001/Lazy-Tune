#include <Arduino.h>
#include "AudioStream.h"
#include <stdio.h>
#include <stdint.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputUSB            usb1;           //xy=75,316.66664028167725
AudioSynthWavetable      wavetable1;     //xy=78.09524917602539,268.57140350341797
AudioInputI2S            i2s1;           //xy=85.42857360839844,212.85715866088867
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
AudioEffectFade          REPLACEWITHAUTOTUNEFXN;          //xy=1112.2619171142578,259.7619171142578
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
AudioMixer4              vocoderOut;         //xy=1418.8095169067383,755.0000286102295
AudioAnalyzePeak         peak12;  //xy=1426.6665009392632,583.6507780287001
AudioAnalyzePeak         peak11; //xy=1428.888855404324,524.7618800269233
AudioAnalyzePeak         peak10; //xy=1429.9998478359646,466.9841147528755
AudioAnalyzePeak         peak9; //xy=1432.2222023010254,408.09521675109863
AudioMixer4              sourceMixer;         //xy=1597.3215637207031,256.761869430542
AudioEffectReverb        reverb1;        //xy=1827.6548080444336,345.42855072021484
AudioEffectFlange        flange1;        //xy=1830.6548080444336,297.42855072021484
AudioEffectChorus        chorus1;        //xy=1830.6548080444336,394.42855072021484
AudioEffectBitcrusher    bitcrusher1;    //xy=1837.6548080444336,437.42855072021484
AudioEffectWaveshaper    waveshape1;     //xy=1844.6548080444336,483.42855072021484
AudioEffectWaveshaper    waveshape2;     //xy=1849.6548080444336,527.4285507202148
AudioEffectMultiply      budgetVocoder;      //xy=1853.6548080444336,576.4285507202148
AudioMixer4              delayBus;         //xy=2181.6548080444336,275.42855072021484
AudioMixer4              distortionBus;         //xy=2194.6548080444336,350.42855072021484
AudioMixer4              master;         //xy=2196.988136291504,474.4285583496094
AudioOutputI2S           i2s2;           //xy=2205.988136291504,670.4285583496094
AudioAmplifier           amp1;           //xy=2206.988136291504,589.4285583496094
AudioConnection          patchCord1(usb1, 0, carrierMix, 2);
AudioConnection          patchCord2(wavetable1, 0, carrierMix, 1);
AudioConnection          patchCord3(i2s1, 0, sourceMixer, 0);
AudioConnection          patchCord4(i2s1, 0, REPLACEWITHAUTOTUNEFXN, 0);
AudioConnection          patchCord5(i2s1, 0, modulatorGain, 0);
AudioConnection          patchCord6(i2s1, 1, carrierMix, 0);
AudioConnection          patchCord7(carrierMix, 0, filter25, 0);
AudioConnection          patchCord8(carrierMix, 0, filter27, 0);
AudioConnection          patchCord9(carrierMix, 0, filter29, 0);
AudioConnection          patchCord10(carrierMix, 0, filter31, 0);
AudioConnection          patchCord11(carrierMix, 0, filter33, 0);
AudioConnection          patchCord12(carrierMix, 0, filter35, 0);
AudioConnection          patchCord13(carrierMix, 0, filter37, 0);
AudioConnection          patchCord14(carrierMix, 0, filter39, 0);
AudioConnection          patchCord15(carrierMix, 0, filter41, 0);
AudioConnection          patchCord16(carrierMix, 0, filter43, 0);
AudioConnection          patchCord17(carrierMix, 0, filter45, 0);
AudioConnection          patchCord18(carrierMix, 0, filter47, 0);
AudioConnection          patchCord19(carrierMix, 0, vocoderOut, 0);
AudioConnection          patchCord20(filter29, 1, filter30, 0);
AudioConnection          patchCord21(filter27, 1, filter28, 0);
AudioConnection          patchCord22(filter25, 0, filter26, 0);
AudioConnection          patchCord23(filter31, 1, filter32, 0);
AudioConnection          patchCord24(modulatorGain, 0, filter1, 0);
AudioConnection          patchCord25(modulatorGain, 0, filter3, 0);
AudioConnection          patchCord26(modulatorGain, 0, filter5, 0);
AudioConnection          patchCord27(modulatorGain, 0, filter7, 0);
AudioConnection          patchCord28(modulatorGain, 0, filter9, 0);
AudioConnection          patchCord29(modulatorGain, 0, filter11, 0);
AudioConnection          patchCord30(modulatorGain, 0, filter13, 0);
AudioConnection          patchCord31(modulatorGain, 0, filter15, 0);
AudioConnection          patchCord32(modulatorGain, 0, filter17, 0);
AudioConnection          patchCord33(modulatorGain, 0, filter19, 0);
AudioConnection          patchCord34(modulatorGain, 0, filter21, 0);
AudioConnection          patchCord35(modulatorGain, 0, filter23, 0);
AudioConnection          patchCord36(filter5, 1, filter6, 0);
AudioConnection          patchCord37(filter3, 1, filter4, 0);
AudioConnection          patchCord38(filter1, 0, filter2, 0);
AudioConnection          patchCord39(filter7, 1, filter8, 0);
AudioConnection          patchCord40(filter30, 1, mixer6, 2);
AudioConnection          patchCord41(filter32, 1, mixer6, 3);
AudioConnection          patchCord42(filter28, 1, mixer6, 1);
AudioConnection          patchCord43(filter26, 0, mixer6, 0);
AudioConnection          patchCord44(filter6, 1, peak3, 0);
AudioConnection          patchCord45(filter8, 1, peak4, 0);
AudioConnection          patchCord46(filter4, 1, peak2, 0);
AudioConnection          patchCord47(filter2, 1, peak1, 0);
AudioConnection          patchCord48(mixer6, 0, vocoderOut, 1);
AudioConnection          patchCord49(filter37, 1, filter38, 0);
AudioConnection          patchCord50(filter35, 1, filter36, 0);
AudioConnection          patchCord51(filter39, 1, filter40, 0);
AudioConnection          patchCord52(filter33, 1, filter34, 0);
AudioConnection          patchCord53(filter13, 1, filter14, 0);
AudioConnection          patchCord54(filter11, 1, filter12, 0);
AudioConnection          patchCord55(filter15, 1, filter16, 0);
AudioConnection          patchCord56(filter9, 1, filter10, 0);
AudioConnection          patchCord57(filter38, 1, mixer7, 2);
AudioConnection          patchCord58(filter40, 1, mixer7, 3);
AudioConnection          patchCord59(filter36, 1, mixer7, 1);
AudioConnection          patchCord60(filter34, 1, mixer7, 0);
AudioConnection          patchCord61(filter14, 1, peak7, 0);
AudioConnection          patchCord62(filter16, 1, peak8, 0);
AudioConnection          patchCord63(filter12, 1, peak6, 0);
AudioConnection          patchCord64(filter10, 1, peak5, 0);
AudioConnection          patchCord65(mixer7, 0, vocoderOut, 2);
AudioConnection          patchCord66(filter41, 1, filter42, 0);
AudioConnection          patchCord67(filter45, 1, filter46, 0);
AudioConnection          patchCord68(filter43, 1, filter44, 0);
AudioConnection          patchCord69(filter47, 1, filter48, 0);
AudioConnection          patchCord70(REPLACEWITHAUTOTUNEFXN, 0, sourceMixer, 1);
AudioConnection          patchCord71(filter42, 1, mixer8, 0);
AudioConnection          patchCord72(filter46, 1, mixer8, 2);
AudioConnection          patchCord73(filter44, 1, mixer8, 1);
AudioConnection          patchCord74(filter48, 1, mixer8, 3);
AudioConnection          patchCord75(filter17, 1, filter18, 0);
AudioConnection          patchCord76(filter21, 1, filter22, 0);
AudioConnection          patchCord77(filter19, 1, filter20, 0);
AudioConnection          patchCord78(filter23, 1, filter24, 0);
AudioConnection          patchCord79(filter18, 1, peak9, 0);
AudioConnection          patchCord80(filter22, 1, peak11, 0);
AudioConnection          patchCord81(filter20, 1, peak10, 0);
AudioConnection          patchCord82(filter24, 2, peak12, 0);
AudioConnection          patchCord83(mixer8, 0, vocoderOut, 3);
AudioConnection          patchCord84(vocoderOut, 0, sourceMixer, 2);
AudioConnection          patchCord85(sourceMixer, 0, delayBus, 0);
AudioConnection          patchCord86(sourceMixer, flange1);
AudioConnection          patchCord87(sourceMixer, reverb1);
AudioConnection          patchCord88(sourceMixer, chorus1);
AudioConnection          patchCord89(sourceMixer, bitcrusher1);
AudioConnection          patchCord90(sourceMixer, waveshape1);
AudioConnection          patchCord91(sourceMixer, waveshape2);
AudioConnection          patchCord92(sourceMixer, 0, budgetVocoder, 0);
AudioConnection          patchCord93(reverb1, 0, delayBus, 2);
AudioConnection          patchCord94(flange1, 0, delayBus, 1);
AudioConnection          patchCord95(chorus1, 0, delayBus, 3);
AudioConnection          patchCord96(bitcrusher1, 0, distortionBus, 0);
AudioConnection          patchCord97(waveshape1, 0, distortionBus, 1);
AudioConnection          patchCord98(waveshape2, 0, distortionBus, 2);
AudioConnection          patchCord99(budgetVocoder, 0, distortionBus, 3);
AudioConnection          patchCord100(delayBus, 0, master, 0);
AudioConnection          patchCord101(distortionBus, 0, master, 1);
AudioConnection          patchCord102(master, amp1);
AudioConnection          patchCord103(amp1, 0, i2s2, 0);
AudioConnection          patchCord104(amp1, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=84.5238037109375,395.6666603088379
// GUItool: end automatically generated code


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

void setup() {
  Serial.begin(9600);
  delay(300);
  
  //pinMode(ledPin, OUTPUT);    // used to check timing using a oscilloscope
  //pinMode(FIR_PASSTHRU, INPUT_PULLUP);
  
  // allocate memory for the audio library
  AudioMemory(64);  // how memory blocks are really needed?

  //initialize audioshield
  audioShield.enable();      // configure the sgtl5000
  audioShield.inputSelect(myInput);
  audioShield.volume(0.5);

  modulatorGain.gain(1); //gain of microphone signal (I2S left input)
  carrierMix.gain(0, 1); //gain of carrier signal (I2S right input)
  carrierMix.gain(1, 1); //gain of carrier signal (playing from SD card)

  filter1.resonance(res);    // set the resonance of the filters
  filter2.resonance(res);
  filter3.resonance(res);
  filter4.resonance(res);
  filter5.resonance(res);
  filter6.resonance(res);
  filter7.resonance(res);
  filter8.resonance(res);
  filter9.resonance(res);
  filter10.resonance(res);
  filter11.resonance(res);
  filter12.resonance(res);
  filter13.resonance(res);
  filter14.resonance(res);
  filter15.resonance(res);
  filter16.resonance(res);
  filter17.resonance(res);
  filter18.resonance(res);
  filter19.resonance(res);
  filter20.resonance(res);
  filter21.resonance(res);
  filter22.resonance(res);
  filter23.resonance(res);
  filter24.resonance(res);
  filter25.resonance(res);
  filter26.resonance(res);
  filter27.resonance(res);
  filter28.resonance(res);
  filter29.resonance(res);
  filter30.resonance(res);
  filter31.resonance(res);
  filter32.resonance(res);
  filter33.resonance(res);
  filter34.resonance(res);
  filter35.resonance(res);
  filter36.resonance(res);
  filter37.resonance(res);
  filter38.resonance(res);
  filter39.resonance(res);
  filter40.resonance(res);
  filter41.resonance(res);
  filter42.resonance(res);
  filter43.resonance(res);
  filter44.resonance(res);
  filter45.resonance(res);
  filter46.resonance(res);
  filter47.resonance(res);
  filter48.resonance(res);

  filter1.frequency(freq[0]);                                   // set the frequencies of the filters
  filter2.frequency(freq[0]);                                   // pairs of cascaded filters for optimal frequency isolation
  filter3.frequency(freq[3]);                                   // two sets of filters are used: for voice signal analysis and instrument/synth filter
  filter4.frequency(freq[3]);
  filter5.frequency(freq[6]);
  filter6.frequency(freq[6]);
  filter7.frequency(freq[9]);
  filter8.frequency(freq[9]);
  filter9.frequency(freq[12]);
  filter10.frequency(freq[12]);
  filter11.frequency(freq[15]);
  filter12.frequency(freq[15]);
  filter13.frequency(freq[18]);
  filter14.frequency(freq[18]);
  filter15.frequency(freq[21]);
  filter16.frequency(freq[21]);
  filter17.frequency(freq[24]);
  filter18.frequency(freq[24]);
  filter19.frequency(freq[27]);
  filter20.frequency(freq[27]);
  filter21.frequency(freq[30]);
  filter22.frequency(freq[30]);
  filter23.frequency(freq[33]);
  filter24.frequency(freq[33]);
  filter25.frequency(freq[0]);
  filter26.frequency(freq[0]);
  filter27.frequency(freq[3]);
  filter28.frequency(freq[3]);
  filter29.frequency(freq[6]);
  filter30.frequency(freq[6]);
  filter31.frequency(freq[9]);
  filter32.frequency(freq[9]);
  filter33.frequency(freq[12]);
  filter34.frequency(freq[12]);
  filter35.frequency(freq[15]);
  filter36.frequency(freq[15]);
  filter37.frequency(freq[18]);
  filter38.frequency(freq[18]);
  filter39.frequency(freq[21]);
  filter40.frequency(freq[21]);
  filter41.frequency(freq[24]);
  filter42.frequency(freq[24]);
  filter43.frequency(freq[27]);
  filter44.frequency(freq[27]);
  filter45.frequency(freq[30]);
  filter46.frequency(freq[30]);
  filter47.frequency(freq[33]);
  filter48.frequency(freq[33]);

  peak1val = 1;                                                 // initialize peak values
  peak2val = 1;
  peak3val = 1;
  peak4val = 1;
  peak5val = 1;
  peak6val = 1;
  peak7val = 1;
  peak8val = 1;
  peak9val = 1;
  peak10val = 1;
  peak11val = 1;
  peak12val = 1;

  AudioProcessorUsageMaxReset();                                // and reset these things
  AudioMemoryUsageMaxReset();                                   // I'm doing this cause the source code did it idk if it's necessary
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
       Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  delay(1000);
}
  
}

void loop() {
//  if(playSdWav1.isPlaying() == false) {     //uncomment if we're using SD card to play
//    Serial.println("Start playing");
//    playSdWav1.play("SABER.WAV");
//    delay(10); // wait for library to parse WAV info
//  }
  
  if(peak1.available()) {                                       // store peak values at each read
    peak1raw = peak1.read();
  }
  if(peak2.available()) {
    peak2raw = peak2.read();
  }
  if(peak3.available()) {
    peak3raw = peak3.read();
  }
  if(peak4.available()) {
    peak4raw = peak4.read();
  }
  if(peak5.available()) {
    peak5raw = peak5.read();
  }
  if(peak6.available()) {
    peak6raw = peak6.read();
  }
  if(peak7.available()) {
    peak7raw = peak7.read();
  }
  if(peak8.available()) {
    peak8raw = peak8.read();
  }
  if(peak9.available()) {
    peak9raw = peak9.read();
  }
  if(peak10.available()) {
    peak10raw = peak10.read();
  }
  if(peak11.available()) {
    peak11raw = peak11.read();
  }
  if(peak12.available()) {
    peak12raw = peak12.read();
  }
  
  if((peak1raw * threshold) > peak1val) {                       // simulate envelope follower: it gets the envelope of the filtered signal through
    peak1val = peak1val / attack;                               // the peak values and is used to determine the direction (increase or decrease) of
    mixer6.gain(0, peak1val);                                   // the mixer gain
  }                                                             // filters won't work here because it is implemented as a sample-and-hold code
  if((peak1raw * threshold) < peak1val) {                       // peak values used to set mixer gain are divided to increase or multiplied to decrease
    peak1val = peak1val * attack;                               // the values must not change fast to avoid distortion
    mixer6.gain(0, peak1val);
  }
  if((peak2raw * threshold) > peak2val) {
    peak2val = peak2val / attack;
    mixer6.gain(1, peak2val);
  }
  if((peak2raw * threshold) < peak2val) {
    peak2val = peak2val * attack;
    mixer6.gain(1, peak2val);
  }
  if((peak3raw * threshold) > peak3val) {
    peak3val = peak3val / attack;
    mixer6.gain(2, peak3val);
  }
  if((peak3raw * threshold) < peak3val) {
    peak3val = peak3val * attack;
    mixer6.gain(2, peak3val);
  }
  if((peak4raw * threshold) > peak4val) {
    peak4val = peak4val / attack;
    mixer6.gain(3, peak4val);
  }
  if((peak4raw * threshold) < peak4val) {
    peak4val = peak4val * attack;
    mixer6.gain(3, peak4val);
  }
  if((peak5raw * threshold) > peak5val) {
    peak5val = peak5val / attack;
    mixer7.gain(0, peak5val);
  }
  if((peak5raw * threshold) < peak5val) {
    peak5val = peak5val * attack;
    mixer7.gain(0, peak5val);
  }
  if((peak6raw * threshold) > peak6val) {
    peak6val = peak6val / attack;
    mixer7.gain(1, peak6val);
  }
  if((peak6raw * threshold) < peak6val) {
    peak6val = peak6val * attack;
    mixer7.gain(1, peak6val);
  }
  if((peak7raw * threshold) > peak7val) {
    peak7val = peak7val / attack;
    mixer7.gain(2, peak7val);
  }
  if((peak7raw * threshold) < peak7val) {
    peak7val = peak7val * attack;
    mixer7.gain(2, peak7val);
  }
  if((peak8raw * threshold) > peak8val) {
    peak8val = peak8val / attack;
    mixer7.gain(0, peak8val);
  }
  if((peak8raw * threshold) < peak8val) {
    peak8val = peak8val * attack;
    mixer7.gain(0, peak8val);
  }
  if((peak9raw * threshold) > peak9val) {
    peak9val = peak9val / attack;
    mixer8.gain(1, peak9val);
  }
  if((peak9raw * threshold) < peak9val) {
    peak9val = peak9val * attack;
    mixer8.gain(1, peak9val);
  }
  if((peak10raw * threshold) > peak10val) {
    peak10val = peak10val / attack;
    mixer8.gain(2, peak10val);
  }
  if((peak10raw * threshold) < peak10val) {
    peak10val = peak10val * attack;
    mixer8.gain(2, peak10val);
  }
  if((peak11raw * threshold) > peak11val) {
    peak11val = peak11val / attack;
    mixer8.gain(3, peak11val);
  }
  if((peak11raw * threshold) < peak11val) {
    peak11val = peak11val * attack;
    mixer8.gain(3, peak11val);
  }
  if((peak12raw * threshold) > peak12val) {
    peak12val = peak12val / attack;
    mixer8.gain(0, peak12val);
  }
  if((peak12raw * threshold) < peak12val) {
    peak12val = peak12val * attack;
    mixer8.gain(0, peak12val);
  }
 
  
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
  }
}
