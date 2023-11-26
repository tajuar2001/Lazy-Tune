// For each message received:
// Serial name that each effect takes
// On and off, input range

//PRESETS AND GAIN
//initializes LazyTune with default settings. Effects at 0, default values, audio effects off.
void setMixer(AudioMixer4 mixer, float c0, float c1, float c2, float c3){
    mixer.gain(0, c0);
    mixer.gain(1, c1);
    mixer.gain(2, c2);
    mixer.gain(3, c3);
}

void Lazyinit(){
    //Initializer mixers and audio structures
    setMixer(synthMixer, 0.5, 0.5, 0.5, 0.5);
    setMixer(carrierMix, 0, 1, 0, 0);
    setMixer(mixer6, 1, 1, 1, 1);
    setMixer(mixer7, 1, 1, 1, 1);
    setMixer(mixer8, 1, 1, 1, 1);
    setMixer(vocoderOut, 1, 1, 1, 0);
    setMixer(sourceMixer, 1, 0, 0, 0);
    setMixer(delayBus, 0, 0, 0, 0);
    setMixer(distortionBus, 0, 0, 0, 0);
    setMixer(master, 1, 0, 0);
    //set initial gain
    amp1.gain(1);
    modulatorGain.gain(1);
    //initialize effects
    flange1.begin(flangeBuffer, FLANGE_BUFFER_SIZE, 100, 100, 100);
    chorus1.begin(chorusBuffer, CHORUS_BUFFER_SIZE, 4);
    //configure distortion and fuzz
    waveshape1.shape({-1, -0.9999,-0.9996,-0.99911,-0.99841,-0.99751,-0.99642,-0.99512,-0.99362,-0.99192,-0.99001,
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
                    0.9879,0.99001,0.99192,0.99362,0.99512,0.99642,0.99751,0.99841,0.99911,0.9996,0.9999,1},
                    129);
    waveshape2.shape({-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                    -1,-1,-1,-1,-0.98506,-0.95937,-0.9331,-0.90628,-0.8789,-0.851,-0.82258,-0.79367,-0.76428,
                    -0.73443,-0.70414,-0.67342,-0.6423,-0.61079,-0.57892,-0.54669,-0.51414,-0.48127,-0.44812,
                    -0.41469,-0.38102,-0.34711,-0.313,-0.2787,-0.24423,-0.20961,-0.17487,-0.14002,-0.10509,
                    -0.070097,-0.035059,0,0.035059,0.070097,0.10509,0.14002,0.17487,0.20961,0.24423,0.2787,
                    0.313,0.34711,0.38102,0.41469,0.44812,0.48127,0.51414,0.54669,0.57892,0.61079,0.6423,
                    0.67342,0.70414,0.73443,0.76428,0.79367,0.82258,0.851,0.8789,0.90628,0.9331,0.95937,
                    0.98506,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 129);
}

void Vocoderinit(){
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
}

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
//void setWaveshape1(str message);

//set distortion for waveshape 2
//i haven't figured out how to change waveshape effectively and may hardcode it
//void setWaveshape1(str message);

//Change waveform for all of the synthesizer voices
void synthWaveform(short waveType);
