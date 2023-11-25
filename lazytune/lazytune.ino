#include <Audio.h>
#include <MIDI.h>
#include <Wire.h>
#include <SPI.h>
//#include <SD.h>
#include <SerialFlash.h>

// Audio Components
//DONOT EDIT THIS BECAUSE YOU NEED IT TO GET THE SYSTEM DESIGN TOOL
// GUItool: begin automatically generated code
//AudioSynthWaveform       waveform1;      //xy=82.22222137451172,300.63492584228516
//AudioSynthWaveform       waveform2;      //xy=82.22222518920898,337.7777862548828
//AudioSynthWaveform       waveform3;      //xy=82.22222137451172,376.666654586792
//AudioSynthWaveform       waveform4; //xy=82.77777624130249,414.4444160461426
AudioInputI2S            i2s1;           //xy=85.42857360839844,212.85715866088867
//AudioMixer4              synthMixer;        //xy=88.8888931274414,472.22224044799805
// AudioMixer4              carrierMix;         //xy=292.857120513916,698.571361541748
// AudioFilterStateVariable filter29; //xy=297.80159759521484,933.9483222961426
// AudioFilterStateVariable filter27; //xy=298.80159759521484,873.9483222961426
// AudioFilterStateVariable filter25; //xy=299.80159759521484,813.9483222961426
// AudioFilterStateVariable filter31; //xy=299.80159759521484,991.9483222961426
// AudioAmplifier           modulatorGain;           //xy=312.85712814331055,312.8571357727051
// AudioFilterStateVariable filter5;        //xy=343.99999237060547,536.4285507202148
// AudioFilterStateVariable filter3;        //xy=344.99999237060547,476.42855072021484
// AudioFilterStateVariable filter1;        //xy=345.99999237060547,416.42855072021484
// AudioFilterStateVariable filter7; //xy=345.99999237060547,594.4285507202148
// AudioFilterStateVariable filter30; //xy=422.80159759521484,932.9483222961426
// AudioFilterStateVariable filter32; //xy=424.80159759521484,990.9483222961426
// AudioFilterStateVariable filter28; //xy=425.80159759521484,872.9483222961426
// AudioFilterStateVariable filter26; //xy=427.80159759521484,812.9483222961426
// AudioFilterStateVariable filter6;        //xy=468.99999237060547,535.4285507202148
// AudioFilterStateVariable filter8; //xy=470.99999237060547,593.4285507202148
// AudioFilterStateVariable filter4;        //xy=471.99999237060547,475.42855072021484
// AudioFilterStateVariable filter2;        //xy=473.99999237060547,415.42855072021484
// AudioAnalyzePeak         peak4;  //xy=603.3331798977322,589.2063342200386
// AudioAnalyzePeak         peak3; //xy=605.555534362793,530.3174362182617
// AudioAnalyzePeak         peak2; //xy=606.6665267944336,472.53967094421387
// AudioAnalyzePeak         peak1;          //xy=608.8888812594944,413.650772942437
// AudioMixer4              mixer6;         //xy=627.9365310668945,1135.079360961914
// AudioFilterStateVariable filter37; //xy=635.2142677307129,941.5197238922119
// AudioFilterStateVariable filter35; //xy=637.3253860473633,885.9641666412354
// AudioFilterStateVariable filter39; //xy=637.2142677307129,999.5197238922119
// AudioFilterStateVariable filter33; //xy=638.3253860473633,825.9641666412354
// AudioFilterStateVariable filter13; //xy=734.1110954284668,533.2063369750977
// AudioFilterStateVariable filter11; //xy=736.2222137451172,477.6507797241211
// AudioFilterStateVariable filter15; //xy=736.1110954284668,591.2063369750977
// AudioFilterStateVariable filter9; //xy=737.2222137451172,417.6507797241211
// AudioFilterStateVariable filter38; //xy=760.2142677307129,940.5197238922119
// AudioFilterStateVariable filter40; //xy=762.2142677307129,998.5197238922119
// AudioFilterStateVariable filter36; //xy=764.3253860473633,884.9641666412354
// AudioFilterStateVariable filter34; //xy=766.3253860473633,824.9641666412354
// AudioFilterStateVariable filter14; //xy=859.1110954284668,532.2063369750977
// AudioFilterStateVariable filter16; //xy=861.1110954284668,590.2063369750977
// AudioFilterStateVariable filter12; //xy=863.2222137451172,476.6507797241211
// AudioFilterStateVariable filter10; //xy=865.2222137451172,416.6507797241211
// AudioAnalyzePeak         peak8; //xy=994.4442910088433,589.206333372328
// AudioAnalyzePeak         peak7; //xy=996.666645473904,530.3174353705513
// AudioAnalyzePeak         peak6; //xy=997.7776379055447,472.5396700965034
// AudioAnalyzePeak         peak5; //xy=999.9999923706055,413.65077209472656
// AudioMixer4              mixer7;         //xy=1005.7143402099609,1145.714319229126
// AudioFilterStateVariable filter41; //xy=1009.5951766967773,827.5832996368408
// AudioFilterStateVariable filter45; //xy=1011.2617835998535,944.0277366638184
// AudioFilterStateVariable filter43; //xy=1011.5951766967773,885.5832996368408
// AudioFilterStateVariable filter47; //xy=1013.2617835998535,1002.0277366638184
// AudioEffectFade          REPLACEWITHAUTOTUNEFXN;          //xy=1020.59521484375,273.09524059295654
// AudioFilterStateVariable filter42; //xy=1134.5951766967773,826.5832996368408
// AudioFilterStateVariable filter46; //xy=1136.2617835998535,943.0277366638184
// AudioFilterStateVariable filter44; //xy=1136.5951766967773,884.5832996368408
// AudioFilterStateVariable filter48; //xy=1138.2617835998535,1001.0277366638184
// AudioFilterStateVariable filter17; //xy=1161.6666793823242,412.7618942260742
// AudioFilterStateVariable filter21; //xy=1163.3332862854004,529.2063312530518
// AudioFilterStateVariable filter19; //xy=1163.6666793823242,470.7618942260742
// AudioFilterStateVariable filter23; //xy=1165.3332862854004,587.2063312530518
// AudioFilterStateVariable filter18; //xy=1286.6666793823242,411.7618942260742
// AudioFilterStateVariable filter22; //xy=1288.3332862854004,528.2063312530518
// AudioFilterStateVariable filter20; //xy=1288.6666793823242,469.7618942260742
// AudioFilterStateVariable filter24; //xy=1290.3332862854004,586.2063312530518
// AudioMixer4              mixer8;         //xy=1379.9999732971191,1145.7143020629883
// AudioMixer4              vocoderOut;         //xy=1418.8095779418945,755.0000057220459
// AudioAnalyzePeak         peak12;  //xy=1426.6665009392632,583.6507780287001
// AudioAnalyzePeak         peak11; //xy=1428.888855404324,524.7618800269233
// AudioAnalyzePeak         peak10; //xy=1429.9998478359646,466.9841147528755
// AudioAnalyzePeak         peak9; //xy=1432.2222023010254,408.09521675109863
 AudioMixer4              sourceMixer;         //xy=1597.3215637207031,256.761869430542
 AudioMixer4              master;         //xy=1810.0833587646484,913.2381114959717
// AudioMixer4              delayBus;         //xy=1816.8930740356445,644.2380867004395
// AudioEffectReverb        reverb1;        //xy=1829.999900817871,254.28570652008057
// AudioMixer4              distortionBus;         //xy=1828.2264137268066,712.5713996887207
// AudioEffectFlange        flange1;        //xy=1830.6548080444336,297.42855072021484
// AudioEffectChorus        chorus1;        //xy=1830.6548080444336,394.42855072021484
// AudioEffectFreeverb      freeverb1;      //xy=1834.2857704162598,341.42858695983887
// AudioEffectBitcrusher    bitcrusher1;    //xy=1837.6548080444336,437.42855072021484
// AudioEffectMultiply      multiplier1;      //xy=1842.2262687683105,567.8570985794067
 AudioOutputI2S           i2s2;           //xy=1840.988353729248,993.5237693786621
// AudioEffectWaveshaper    waveshape1;     //xy=1844.6548080444336,483.42855072021484
// AudioEffectWaveshaper    waveshape2;     //xy=1849.6547393798828,527.4285278320312
 AudioAmplifier           amp1;           //xy=1923.892910003662,912.5237274169922
// //AudioConnection          patchCord1(waveform1, 0, mixer10, 0);
// //AudioConnection          patchCord2(waveform2, 0, mixer10, 1);
// //AudioConnection          patchCord3(waveform3, 0, mixer10, 2);
// //AudioConnection          patchCord4(waveform4, 0, mixer10, 3);
 AudioConnection          patchCord5(i2s1, 0, sourceMixer, 0);
// AudioConnection          patchCord6(i2s1, 0, REPLACEWITHAUTOTUNEFXN, 0);
// AudioConnection          patchCord7(i2s1, 0, modulatorGain, 0);
// AudioConnection          patchCord8(i2s1, 1, carrierMix, 0);
// //AudioConnection          patchCord9(mixer10, 0, carrierMix, 1);
// AudioConnection          patchCord10(carrierMix, 0, filter25, 0);
// AudioConnection          patchCord11(carrierMix, 0, filter27, 0);
// AudioConnection          patchCord12(carrierMix, 0, filter29, 0);
// AudioConnection          patchCord13(carrierMix, 0, filter31, 0);
// AudioConnection          patchCord14(carrierMix, 0, filter33, 0);
// AudioConnection          patchCord15(carrierMix, 0, filter35, 0);
// AudioConnection          patchCord16(carrierMix, 0, filter37, 0);
// AudioConnection          patchCord17(carrierMix, 0, filter39, 0);
// AudioConnection          patchCord18(carrierMix, 0, filter41, 0);
// AudioConnection          patchCord19(carrierMix, 0, filter43, 0);
// AudioConnection          patchCord20(carrierMix, 0, filter45, 0);
// AudioConnection          patchCord21(carrierMix, 0, filter47, 0);
// AudioConnection          patchCord22(carrierMix, 0, sourceMixer, 3);
// AudioConnection          patchCord23(carrierMix, 0, multiplier1, 1);
// AudioConnection          patchCord24(filter29, 1, filter30, 0);
// AudioConnection          patchCord25(filter27, 1, filter28, 0);
// AudioConnection          patchCord26(filter25, 0, filter26, 0);
// AudioConnection          patchCord27(filter31, 1, filter32, 0);
// AudioConnection          patchCord28(modulatorGain, 0, filter1, 0);
// AudioConnection          patchCord29(modulatorGain, 0, filter3, 0);
// AudioConnection          patchCord30(modulatorGain, 0, filter5, 0);
// AudioConnection          patchCord31(modulatorGain, 0, filter7, 0);
// AudioConnection          patchCord32(modulatorGain, 0, filter9, 0);
// AudioConnection          patchCord33(modulatorGain, 0, filter11, 0);
// AudioConnection          patchCord34(modulatorGain, 0, filter13, 0);
// AudioConnection          patchCord35(modulatorGain, 0, filter15, 0);
// AudioConnection          patchCord36(modulatorGain, 0, filter17, 0);
// AudioConnection          patchCord37(modulatorGain, 0, filter19, 0);
// AudioConnection          patchCord38(modulatorGain, 0, filter21, 0);
// AudioConnection          patchCord39(modulatorGain, 0, filter23, 0);
// AudioConnection          patchCord40(filter5, 1, filter6, 0);
// AudioConnection          patchCord41(filter3, 1, filter4, 0);
// AudioConnection          patchCord42(filter1, 0, filter2, 0);
// AudioConnection          patchCord43(filter7, 1, filter8, 0);
// AudioConnection          patchCord44(filter30, 1, mixer6, 2);
// AudioConnection          patchCord45(filter32, 1, mixer6, 3);
// AudioConnection          patchCord46(filter28, 1, mixer6, 1);
// AudioConnection          patchCord47(filter26, 0, mixer6, 0);
// AudioConnection          patchCord48(filter6, 1, peak3, 0);
// AudioConnection          patchCord49(filter8, 1, peak4, 0);
// AudioConnection          patchCord50(filter4, 1, peak2, 0);
// AudioConnection          patchCord51(filter2, 1, peak1, 0);
// AudioConnection          patchCord52(mixer6, 0, vocoderOut, 0);
// AudioConnection          patchCord53(filter37, 1, filter38, 0);
// AudioConnection          patchCord54(filter35, 1, filter36, 0);
// AudioConnection          patchCord55(filter39, 1, filter40, 0);
// AudioConnection          patchCord56(filter33, 1, filter34, 0);
// AudioConnection          patchCord57(filter13, 1, filter14, 0);
// AudioConnection          patchCord58(filter11, 1, filter12, 0);
// AudioConnection          patchCord59(filter15, 1, filter16, 0);
// AudioConnection          patchCord60(filter9, 1, filter10, 0);
// AudioConnection          patchCord61(filter38, 1, mixer7, 2);
// AudioConnection          patchCord62(filter40, 1, mixer7, 3);
// AudioConnection          patchCord63(filter36, 1, mixer7, 1);
// AudioConnection          patchCord64(filter34, 1, mixer7, 0);
// AudioConnection          patchCord65(filter14, 1, peak7, 0);
// AudioConnection          patchCord66(filter16, 1, peak8, 0);
// AudioConnection          patchCord67(filter12, 1, peak6, 0);
// AudioConnection          patchCord68(filter10, 1, peak5, 0);
// AudioConnection          patchCord69(mixer7, 0, vocoderOut, 1);
// AudioConnection          patchCord70(filter41, 1, filter42, 0);
// AudioConnection          patchCord71(filter45, 1, filter46, 0);
// AudioConnection          patchCord72(filter43, 1, filter44, 0);
// AudioConnection          patchCord73(filter47, 1, filter48, 0);
// AudioConnection          patchCord74(REPLACEWITHAUTOTUNEFXN, 0, sourceMixer, 1);
// AudioConnection          patchCord75(filter42, 1, mixer8, 0);
// AudioConnection          patchCord76(filter46, 1, mixer8, 2);
// AudioConnection          patchCord77(filter44, 1, mixer8, 1);
// AudioConnection          patchCord78(filter48, 1, mixer8, 3);
// AudioConnection          patchCord79(filter17, 1, filter18, 0);
// AudioConnection          patchCord80(filter21, 1, filter22, 0);
// AudioConnection          patchCord81(filter19, 1, filter20, 0);
// AudioConnection          patchCord82(filter23, 1, filter24, 0);
// AudioConnection          patchCord83(filter18, 1, peak9, 0);
// AudioConnection          patchCord84(filter22, 1, peak11, 0);
// AudioConnection          patchCord85(filter20, 1, peak10, 0);
// AudioConnection          patchCord86(filter24, 2, peak12, 0);
// AudioConnection          patchCord87(mixer8, 0, vocoderOut, 2);
// AudioConnection          patchCord88(vocoderOut, 0, sourceMixer, 2);
// AudioConnection          patchCord89(sourceMixer, flange1);
// AudioConnection          patchCord90(sourceMixer, chorus1);
// AudioConnection          patchCord91(sourceMixer, bitcrusher1);
// AudioConnection          patchCord92(sourceMixer, waveshape1);
// AudioConnection          patchCord93(sourceMixer, waveshape2);
// AudioConnection          patchCord94(sourceMixer, 0, multiplier1, 0);
// AudioConnection          patchCord95(sourceMixer, freeverb1);
 AudioConnection          patchCord96(sourceMixer, 0, master, 0);
// AudioConnection          patchCord97(sourceMixer, reverb1);
 AudioConnection          patchCord98(master, amp1);
// AudioConnection          patchCord99(delayBus, 0, master, 1);
// AudioConnection          patchCord100(reverb1, 0, delayBus, 0);
// AudioConnection          patchCord101(distortionBus, 0, master, 2);
// AudioConnection          patchCord102(flange1, 0, delayBus, 1);
// AudioConnection          patchCord103(chorus1, 0, delayBus, 3);
// AudioConnection          patchCord104(freeverb1, 0, delayBus, 2);
// AudioConnection          patchCord105(bitcrusher1, 0, distortionBus, 0);
// AudioConnection          patchCord106(multiplier1, 0, distortionBus, 3);
// AudioConnection          patchCord107(waveshape1, 0, distortionBus, 1);
// AudioConnection          patchCord108(waveshape2, 0, distortionBus, 2);
 AudioConnection          patchCord109(amp1, 0, i2s2, 0);
 AudioConnection          patchCord110(amp1, 0, i2s2, 1);
 AudioControlSGTL5000     audioShield;     //xy=96.74602508544922,165.6666660308838
// GUItool: end automatically generated code

//
//  SYNTHESIZER OBJECTS
//
// Define the number of voices for polyphony
const int numVoices = 4;
int voiceNote[numVoices] = {-1}; 

// Array to keep track of voice usage
bool voiceUsed[numVoices] = {false};

// Define envelope for each voice
AudioEffectEnvelope envelope[numVoices];

// New patch cords for the envelope effect
//AudioConnection *patchCordsEnv[numVoices];

//Audio Components for synthesis
MIDI_CREATE_DEFAULT_INSTANCE();
// AudioSynthWaveform   waveform[numVoices];  // Create an array of waveforms for polyphony
// AudioMixer4          synthMixer;                // Mix the waveforms before output
// //AudioOutputI2S       audioOutput;          // Audio output
// AudioConnection      *patchCords[numVoices * 2];  // Patch cords for waveforms to mixer
// AudioConnection      patchCordToOutput(synthMixer, 0, carrierMix, 1);

float peak1raw, peak2raw, peak3raw, peak4raw, peak5raw, peak6raw,
  peak7raw, peak8raw, peak9raw, peak10raw, peak11raw, peak12raw;
float peak1val, peak2val, peak3val, peak4val, peak5val, peak6val,
  peak7val, peak8val, peak9val, peak10val, peak11val, peak12val;

const float res = 5;                                            // this is used as resonance value of all state variable filters
const float attack = 0.9958;                                   // controls attack and decay, must not exceed or equal 1,
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

// // Buffers for flanger and chorus effects
// static const int FLANGE_BUFFER_SIZE = 512;
// short flangeBuffer[FLANGE_BUFFER_SIZE];
// static const int CHORUS_BUFFER_SIZE = 512;
// short chorusBuffer[CHORUS_BUFFER_SIZE];

// //waveshape for distortion effects
// static const int WAVESHAPE_SIZE = 129;
// float hardlimiter1[WAVESHAPE_SIZE] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
//                     -1,-1,-1,-1,-0.98506,-0.95937,-0.9331,-0.90628,-0.8789,-0.851,-0.82258,-0.79367,-0.76428,
//                     -0.73443,-0.70414,-0.67342,-0.6423,-0.61079,-0.57892,-0.54669,-0.51414,-0.48127,-0.44812,
//                     -0.41469,-0.38102,-0.34711,-0.313,-0.2787,-0.24423,-0.20961,-0.17487,-0.14002,-0.10509,
//                     -0.070097,-0.035059,0,0.035059,0.070097,0.10509,0.14002,0.17487,0.20961,0.24423,0.2787,
//                     0.313,0.34711,0.38102,0.41469,0.44812,0.48127,0.51414,0.54669,0.57892,0.61079,0.6423,
//                     0.67342,0.70414,0.73443,0.76428,0.79367,0.82258,0.851,0.8789,0.90628,0.9331,0.95937,
//                     0.98506,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
// float distortion1[WAVESHAPE_SIZE] = {-1, -0.9999,-0.9996,-0.99911,-0.99841,-0.99751,-0.99642,-0.99512,-0.99362,-0.99192,-0.99001,
//                     -0.9879,-0.98558,-0.98305,-0.98032,-0.97737,-0.97421,-0.97083,-0.96724,-0.96342,-0.95938,
//                     -0.95512,-0.95062,-0.94588,-0.94091,-0.9357,-0.93024,-0.92452,-0.91855,-0.91231,-0.9058,
//                     -0.89901,-0.89193,-0.88455,-0.87688,-0.86888,-0.86055,-0.85189,-0.84287,-0.83347,-0.82369,
//                     -0.8135,-0.80287,-0.79179,-0.78022,-0.76813,-0.75549,-0.74224,-0.72834,-0.71374,-0.69835,
//                     -0.68209,-0.66486,-0.64654,-0.62696,-0.60592,-0.58315,-0.55829,-0.53083,-0.50001,-0.46465,
//                     -0.42267,-0.3698,-0.29422,0,0.29422,0.3698,0.42267,0.46465,0.50001,0.53083,0.55829,0.58315,
//                     0.60592,0.62696,0.64654,0.66486,0.68209,0.69835,0.71374,0.72834,0.74224,0.75549,0.76813,
//                     0.78022,0.79179,0.80287,0.8135,0.82369,0.83347,0.84287,0.85189,0.86055,0.86888,0.87688,
//                     0.88455,0.89193,0.89901,0.9058,0.91231,0.91855,0.92452,0.93024,0.9357,0.94091,0.94588,
//                     0.95062,0.95512,0.95938,0.96342,0.96724,0.97083,0.97421,0.97737,0.98032,0.98305,0.98558,
//                     0.9879,0.99001,0.99192,0.99362,0.99512,0.99642,0.99751,0.99841,0.99911,0.9996,0.9999,1};

//
//    FUNCTION HEADERS
//
//   PRESETS AND GAIN
//edits a mixer to set gain of each channel
//void setMixer(AudioMixer4 mixer, float c0, float c1, float c2, float c3);

//initializes LazyTune with default settings. Effects at 0, microphone signal only, audio effects off.
//void Lazyinit();

//initializes Vocoder filters and waveforms
//void Vocoderinit();

//big reverb preset -- set reverb to max, add additional effects
//void bigReverb();

//distortion preset -- set bitcrush and distortions to maxxxxx
//void distort();

//set gain of effects in delay bus: 0 for reverb, 1 for flanger, 2 for freeverb, 3 for chorus
//void delayGain(short gain);

//set gain of effects in distortion bus: 0 for bitcrush, c1 for waveshape, c2 for waveshape2, 3 for multiplier
//void distortGain(short gain);

//set master gain - 0 for source, 1 for delay, 2 for distortion
//void masterGain(str message);

//      PARAMETER EDITING
//switch resonance values on the vocoder filters. increase resonance for narrower bands
//void vocoderResonance(str message);

//set reverb1 time
//void reverbTime(str message);

//set flange1 parameters (offest, depth, delayrate)
//void setFlange(str message);

//set freeverb parameters (roomsize, damping)
//void setFreeverb(str message);

//set number of voices in chorus
//void setChorus(str message); 

//set bitdepth or bitfreq for bitcrusher effect
//void setBitcrush(str message);

//set distortion for waveshape 1
//i haven't figured out how to change waveshape effectively and may hardcode it
//void setWaveshape1(str message);

//set distortion for waveshape 2
//i haven't figured out how to change waveshape effectively and may hardcode it
//void setWaveshape1(str message);

//Change waveform for all of the synthesizer voices
//void synthWaveform(short waveType);

// Setup routine
void setup() {
  Serial.begin(9600);
  AudioMemory(64);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  audioShield.enable();
  audioShield.volume(0.7);

  // Initialize mixer gains
  Lazyinit();
  //Vocoderinit();

}

// Loop routine
void loop() {
  // Read commands from Serial
  readAndApplySerialCommands();

  // Read MIDI Signals
  if (usbMIDI.read()) {
    int note = usbMIDI.getData1();
    int velocity = usbMIDI.getData2();
    
    switch (usbMIDI.getType()) {
      case midi::NoteOn:
        if (velocity > 0) {
          //noteOn(note, velocity);
        } else {
          //noteOff(note);
        }
        break;
      case midi::NoteOff:
        //noteOff(note);
        break;
      // Handle other MIDI message types as needed
    }
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
    case 's': setMixerGain(master, 0, command + 1); break; //dry source master gain
    case 'd': setMixerGain(master, 1, command + 1); break; //delay bus master gain
    case 'i': setMixerGain(master, 2, command + 1); break; //distortion bus master gain
    case 'o': amp1.gain(atof(command + 1)); break; //master volume output
    default: Serial.println("Invalid effect type"); break;
  }
}


// Set mixer gain
void setMixerGain(AudioMixer4 mix, uint8_t channel, const char *gainStr) {
  float gainValue = atof(gainStr);
  mix.gain(channel, gainValue);

  // Output the new gain value
  Serial.print("Channel ");
  Serial.print(channel);
  Serial.print(" gain set to ");
  Serial.println(gainValue);
}

//edits a mixer to set gain of each channel
void setMixer(AudioMixer4 mixer, float c0, float c1, float c2, float c3){
    mixer.gain(0, c0);
    mixer.gain(1, c1);
    mixer.gain(2, c2);
    mixer.gain(3, c3);
}

//initializes LazyTune with default settings. Effects at 0, default values, audio effects off.
void Lazyinit(){
    //Initializer mixers and audio structures
    // setMixer(carrierMix, 0, 1, 0, 0); //channel 1 for synthesized audio, no carrier input yet
    setMixer(sourceMixer, 1, 0, 0, 0);
    // setMixer(delayBus, 0, 0, 0, 0);
    // setMixer(distortionBus, 0, 0, 0, 0);
    setMixer(master, 1, 0, 0, 0);
    // //set initial gain
    amp1.gain(0.5);
    // modulatorGain.gain(1);
    // //initialize effects
    // flange1.begin(flangeBuffer, FLANGE_BUFFER_SIZE, 100, 100, 100);
    // chorus1.begin(chorusBuffer, CHORUS_BUFFER_SIZE, 4);
    // //configure distortion and fuzz
    // waveshape1.shape(distortion1, 129);
    // waveshape2.shape(hardlimiter1, 129);
}

//initializes Vocoder filters
//void Vocoderinit(){
//  // Set up waveforms and mixer
//  for (int i = 0; i < numVoices; i++) {
//    waveform[i].begin(WAVEFORM_SINE);
//    waveform[i].amplitude(0);
//    //I think this line is causing problems it's not supposed to be there
//    //patchCords[i * 2] = new AudioConnection(waveform[i], 0, synthMixer, i);
//  }
//
//  for (int i = 0; i < numVoices; i++) {
//    envelope[i].attack(10); // Attack time in milliseconds
//    envelope[i].decay(100); // Decay time
//    envelope[i].sustain(0.5); // Sustain level
//    envelope[i].release(300); // Release time
//
//    //patchCordsEnv[i] = new AudioConnection(waveform[i], 0, envelope[i], 0);
//    patchCords[i] = new AudioConnection(waveform[i], 0, envelope[i], 0);
//    patchCords[i+4] = new AudioConnection(envelope[i], 0, synthMixer, i);
//  }
//
//  // set the resonance of the filters
//  filter1.resonance(res); filter2.resonance(res); filter3.resonance(res); filter4.resonance(res); filter5.resonance(res);
//  filter6.resonance(res); filter7.resonance(res); filter8.resonance(res); filter9.resonance(res); filter10.resonance(res);
//  filter11.resonance(res); filter12.resonance(res); filter13.resonance(res); filter14.resonance(res); filter15.resonance(res);
//  filter16.resonance(res); filter17.resonance(res); filter18.resonance(res); filter19.resonance(res); filter20.resonance(res);
//  filter21.resonance(res); filter22.resonance(res); filter23.resonance(res); filter24.resonance(res); filter25.resonance(res);
//  filter26.resonance(res); filter27.resonance(res); filter28.resonance(res); filter29.resonance(res); filter30.resonance(res);
//  filter31.resonance(res); filter32.resonance(res); filter33.resonance(res); filter34.resonance(res); filter35.resonance(res);
//  filter36.resonance(res); filter37.resonance(res); filter38.resonance(res); filter39.resonance(res); filter40.resonance(res);
//  filter41.resonance(res); filter42.resonance(res); filter43.resonance(res); filter44.resonance(res); filter45.resonance(res);
//  filter46.resonance(res); filter47.resonance(res); filter48.resonance(res);
//
//  // set the frequencies of the filters
//  // pairs of cascaded filters for optimal frequency isolation
//  // two sets of filters are used: for voice signal analysis and instrument/synth filter
//  filter1.frequency(freq[0]); filter2.frequency(freq[0]); filter3.frequency(freq[3]); filter4.frequency(freq[3]);
//  filter5.frequency(freq[6]); filter6.frequency(freq[6]); filter7.frequency(freq[9]); filter8.frequency(freq[9]);
//  filter9.frequency(freq[12]); filter10.frequency(freq[12]); filter11.frequency(freq[15]); filter12.frequency(freq[15]);
//  filter13.frequency(freq[18]); filter14.frequency(freq[18]); filter15.frequency(freq[21]); filter16.frequency(freq[21]);
//  filter17.frequency(freq[24]); filter18.frequency(freq[24]); filter19.frequency(freq[27]); filter20.frequency(freq[27]);
//  filter21.frequency(freq[30]); filter22.frequency(freq[30]); filter23.frequency(freq[33]); filter24.frequency(freq[33]);
//  filter25.frequency(freq[0]); filter26.frequency(freq[0]); filter27.frequency(freq[3]); filter28.frequency(freq[3]);
//  filter29.frequency(freq[6]); filter30.frequency(freq[6]); filter31.frequency(freq[9]); filter32.frequency(freq[9]);
//  filter33.frequency(freq[12]); filter34.frequency(freq[12]); filter35.frequency(freq[15]); filter36.frequency(freq[15]);
//  filter37.frequency(freq[18]); filter38.frequency(freq[18]); filter39.frequency(freq[21]); filter40.frequency(freq[21]);
//  filter41.frequency(freq[24]); filter42.frequency(freq[24]); filter43.frequency(freq[27]); filter44.frequency(freq[27]);
//  filter45.frequency(freq[30]); filter46.frequency(freq[30]); filter47.frequency(freq[33]); filter48.frequency(freq[33]);
//
//  // initialize peak values   
//  peak1val = 1; peak2val = 1; peak3val = 1; peak4val = 1; peak5val = 1; peak6val = 1;
//  peak7val = 1; peak8val = 1; peak9val = 1; peak10val = 1; peak11val = 1; peak12val = 1;
//
//  setMixer(synthMixer, 0.5, 0.5, 0.5, 0.5);
//  setMixer(vocoderOut, 0.4, 0.4, 0.4, 0);
//  setMixer(mixer6, 1, 1, 1, 1);
//  setMixer(mixer7, 1, 1, 1, 1);
//  setMixer(mixer8, 1, 1, 1, 1);
//
//}
//
//void noteOn(uint8_t note, uint8_t velocity) {
//  for (int i = 0; i < numVoices; i++) {
//    if (!voiceUsed[i]) {
//      float frequency = noteToFrequency(note);
//      waveform[i].frequency(frequency);
//      waveform[i].amplitude(velocity / 127.0);
//      voiceUsed[i] = true;
//      voiceNote[i] = note; // Store the note number that this voice is now playing
//      break;
//    }
//  }
//}
//
//void noteOff(uint8_t note) {
//  for (int i = 0; i < numVoices; i++) {
//    if (voiceUsed[i] && voiceNote[i] == note) { // Check if this voice is playing the note
//      waveform[i].amplitude(0);
//      voiceUsed[i] = false;
//      voiceNote[i] = -1; // Reset the note number for this voice
//      break;
//    }
//  }
//}
//
//float noteToFrequency(uint8_t note) {
//  return 440.0 * pow(2.0, (note - 69) / 12.0);
//}



/*

//switches carrier signal from line in input to MIDI synth
void toggleCarrier(short c_type);

//big reverb preset -- set reverb to max, add additional effects
void bigReverb();

//distortion preset -- set bitcrush and distortions to maxxxxx
void distort();

//set gain of effects in delay bus: 0 for reverb, 1 for flanger, 2 for freeverb, 3 for chorus
void delayGain(short gain);

//set gain of effects in distortion bus: 0 for bitcrush, c1 for waveshape, c2 for waveshape2, 3 for multiplier
void distortGain(short gain);

//set master gain - 0 for source, 1 for delay, 2 for distortion
void masterGain(str message);*/

//      PARAMETER EDITING
//switch resonance values on the vocoder filters. increase resonance for narrower bands
/*void vocoderResonance(str message);

//set reverb1 time
void reverbTime(str message);

//set flange1 parameters (offest, depth, delayrate)
void setFlange(str message);

//set freeverb parameters (roomsize, damping)
void setFreeverb(str message);

//set number of voices in chorus
void setChorus(str message); 

//set bitdepth or bitfreq for bitcrusher effect
void setBitcrush(str message);

//set distortion for waveshape 1
//i haven't figured out how to change waveshape effectively and may hardcode it
void setWaveshape1(str message);

//set distortion for waveshape 2
//i haven't figured out how to change waveshape effectively and may hardcode it
void setWaveshape1(str message);

//Change waveform for all of the synthesizer voices
void synthWaveform(short waveType);*/
