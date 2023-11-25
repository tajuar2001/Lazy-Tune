#ifndef LAZYTUNE_H
#define LAZYTUNE_H

#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#define numVoices = 4;
#define voiceNote[numVoices] = {-1}; 


/*
// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=82.22222137451172,300.63492584228516
AudioSynthWaveform       waveform2;      //xy=82.22222518920898,337.7777862548828
AudioSynthWaveform       waveform3;      //xy=82.22222137451172,376.666654586792
AudioSynthWaveform       waveform4; //xy=82.77777624130249,414.4444160461426
AudioInputI2S            i2s1;           //xy=85.42857360839844,212.85715866088867
AudioMixer4              mixer10;        //xy=88.8888931274414,472.22224044799805
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
AudioEffectFade          REPLACEWITHAUTOTUNEFXN;          //xy=1020.59521484375,273.09524059295654
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
AudioMixer4              sourceMixer;         //xy=1597.3215637207031,256.761869430542
AudioMixer4              master;         //xy=1810.0833587646484,913.2381114959717
AudioMixer4              delayBus;         //xy=1816.8930740356445,644.2380867004395
AudioEffectReverb        reverb1;        //xy=1829.999900817871,254.28570652008057
AudioMixer4              distortionBus;         //xy=1828.2264137268066,712.5713996887207
AudioEffectFlange        flange1;        //xy=1830.6548080444336,297.42855072021484
AudioEffectChorus        chorus1;        //xy=1830.6548080444336,394.42855072021484
AudioEffectFreeverb      freeverb1;      //xy=1834.2857704162598,341.42858695983887
AudioEffectBitcrusher    bitcrusher1;    //xy=1837.6548080444336,437.42855072021484
AudioEffectMultiply      multiplier1;      //xy=1842.2262687683105,567.8570985794067
AudioOutputI2S           i2s2;           //xy=1840.988353729248,993.5237693786621
AudioEffectWaveshaper    waveshape1;     //xy=1844.6548080444336,483.42855072021484
AudioEffectWaveshaper    waveshape2;     //xy=1849.6547393798828,527.4285278320312
AudioAmplifier           amp1;           //xy=1923.892910003662,912.5237274169922
AudioConnection          patchCord1(waveform1, 0, mixer10, 0);
AudioConnection          patchCord2(waveform2, 0, mixer10, 1);
AudioConnection          patchCord3(waveform3, 0, mixer10, 2);
AudioConnection          patchCord4(waveform4, 0, mixer10, 3);
AudioConnection          patchCord5(i2s1, 0, sourceMixer, 0);
AudioConnection          patchCord6(i2s1, 0, REPLACEWITHAUTOTUNEFXN, 0);
AudioConnection          patchCord7(i2s1, 0, modulatorGain, 0);
AudioConnection          patchCord8(i2s1, 1, carrierMix, 0);
AudioConnection          patchCord9(mixer10, 0, carrierMix, 1);
AudioConnection          patchCord10(carrierMix, 0, filter25, 0);
AudioConnection          patchCord11(carrierMix, 0, filter27, 0);
AudioConnection          patchCord12(carrierMix, 0, filter29, 0);
AudioConnection          patchCord13(carrierMix, 0, filter31, 0);
AudioConnection          patchCord14(carrierMix, 0, filter33, 0);
AudioConnection          patchCord15(carrierMix, 0, filter35, 0);
AudioConnection          patchCord16(carrierMix, 0, filter37, 0);
AudioConnection          patchCord17(carrierMix, 0, filter39, 0);
AudioConnection          patchCord18(carrierMix, 0, filter41, 0);
AudioConnection          patchCord19(carrierMix, 0, filter43, 0);
AudioConnection          patchCord20(carrierMix, 0, filter45, 0);
AudioConnection          patchCord21(carrierMix, 0, filter47, 0);
AudioConnection          patchCord22(carrierMix, 0, sourceMixer, 3);
AudioConnection          patchCord23(carrierMix, 0, multiplier1, 1);
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
AudioConnection          patchCord74(REPLACEWITHAUTOTUNEFXN, 0, sourceMixer, 1);
AudioConnection          patchCord75(filter42, 1, mixer8, 0);
AudioConnection          patchCord76(filter46, 1, mixer8, 2);
AudioConnection          patchCord77(filter44, 1, mixer8, 1);
AudioConnection          patchCord78(filter48, 1, mixer8, 3);
AudioConnection          patchCord79(filter17, 1, filter18, 0);
AudioConnection          patchCord80(filter21, 1, filter22, 0);
AudioConnection          patchCord81(filter19, 1, filter20, 0);
AudioConnection          patchCord82(filter23, 1, filter24, 0);
AudioConnection          patchCord83(filter18, 1, peak9, 0);
AudioConnection          patchCord84(filter22, 1, peak11, 0);
AudioConnection          patchCord85(filter20, 1, peak10, 0);
AudioConnection          patchCord86(filter24, 2, peak12, 0);
AudioConnection          patchCord87(mixer8, 0, vocoderOut, 2);
AudioConnection          patchCord88(vocoderOut, 0, sourceMixer, 2);
AudioConnection          patchCord89(sourceMixer, flange1);
AudioConnection          patchCord90(sourceMixer, chorus1);
AudioConnection          patchCord91(sourceMixer, bitcrusher1);
AudioConnection          patchCord92(sourceMixer, waveshape1);
AudioConnection          patchCord93(sourceMixer, waveshape2);
AudioConnection          patchCord94(sourceMixer, 0, multiplier1, 0);
AudioConnection          patchCord95(sourceMixer, freeverb1);
AudioConnection          patchCord96(sourceMixer, 0, master, 0);
AudioConnection          patchCord97(sourceMixer, reverb1);
AudioConnection          patchCord98(master, amp1);
AudioConnection          patchCord99(delayBus, 0, master, 1);
AudioConnection          patchCord100(reverb1, 0, delayBus, 0);
AudioConnection          patchCord101(distortionBus, 0, master, 2);
AudioConnection          patchCord102(flange1, 0, delayBus, 1);
AudioConnection          patchCord103(chorus1, 0, delayBus, 3);
AudioConnection          patchCord104(freeverb1, 0, delayBus, 2);
AudioConnection          patchCord105(bitcrusher1, 0, distortionBus, 0);
AudioConnection          patchCord106(multiplier1, 0, distortionBus, 3);
AudioConnection          patchCord107(waveshape1, 0, distortionBus, 1);
AudioConnection          patchCord108(waveshape2, 0, distortionBus, 2);
AudioConnection          patchCord109(amp1, 0, i2s2, 0);
AudioConnection          patchCord110(amp1, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=96.74602508544922,165.6666660308838
// GUItool: end automatically generated code


//PARAMETERS TO BE EDITED DURING LOOP:
carrierMix; //channel 0 for line input, channel 1 for synth input. Potentially add more input sources for variable carrier sources.
sourceMixer; //c0 dry microphone signal, c1 autotune signal, c2 vocoder signal, c3 dry carrier signal
reverb1; //reverb, change delay time 
flange1; //flanger, requires buffer and buffer size to be implemented
freeverb1; //reverb with room size parameters and damping
chorus1; //chorus, requires # of voices and buffer (like flanger)
bitcrusher1; //can edit bits to distort or sample rate
waveshape1; //simple overdrive
waveshape2; //simple fuzz
multiplier1; //only to be used with dry or autotune signal. works as a budget vocoder by multiplying the modulator and carrier signals
delayBus; //c0 for reverb, c1 for flanger, c2 for freeverb, c3 for chorus. edit gain for dry/wet on effects
distortionBus; //c0 for bitcrush, c1 for waveshape 1, c2 for waveshape 2, c3 for multiplier. edit gain for dry/wet on effects
master; //master mixer, c0 for dry source signal, c1 for delay bus, c2 for distortion bus
amp1; //master volume
*/


//PRESETS AND GAIN
//edits a mixer to set gain of each channel
void setMixer(AudioMixer4 mixer, float c0, float c1, float c2, float c3)

//initializes LazyTune with default settings. Effects at 0, default values, audio effects off.
void Lazyinit();

//initializes Vocoder filters
void Vocoderinit();

//toggle mode from dry signal to autotune to vocoder to carrier signal
void setMode(short vocalMode);

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
void masterGain(str message);

//PARAMETER EDITING
//switch resonance values on the vocoder filters. increase resonance for narrower bands
void vocoderResonance(str message);

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
void synthWaveform(short waveType);

#endif