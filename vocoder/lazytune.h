#ifndef LAZYTUNE_H
#define LAZYTUNE_H

#include <Arduino.h>

#define numVoices = 4;
#define voiceNote[numVoices] = {-1}; 

/* */

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

//PRESETS AND GAIN
//initializes LazyTune with default settings. Effects at 0, default values, audio effects off.
void Lazyinit();

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