import numpy as np
import aubio # https://github.com/aubio/aubio
import pyaudio

# Auto-Tune Prototype

# STFT (Pitch Detection)

# Pitch Shift

# Formant Preservation

# Note Transition

semitone_distance = 2**(1/12)
sample_rate = 44100 # Khz
chunk_size = 882

def autotune(mic_signal, formant_flag=0, method=0): # input signal 44.1Khz, bool formant-preservation, method
    if formant_flag == 1:
        return autotune_original(mic_signal)
    if method == 0:
        return autotune_cepstrum(mic_signal)
    if method == 1:
        return autotune_psola(mic_signal)
    if method == 2:
        return autotune_lpc(mic_signal)
    return

# find the nearest frequency
def shift_to_nearest_semitone(note_frequency):
        # Calculate the nearest semitone frequency
        nearest_semitone = round(12 * np.log2(note_frequency / 440))
        nearest_frequency = 440 * 2**(nearest_semitone / 12)
        return nearest_frequency

# basic pitch shifting no formant preservation
def autotune_original(mic_signal):
    # find the main frequency of the chunk

    # find the nearest semitone

    # shift it to that semitone

    return 

#Cepstrum (https://en.wikipedia.org/wiki/Cepstrum)
def autotune_cepstrum(mic_signal): 

    # do pitch shifting

    # Create envelope from old vs. new version of signal and apply correction envelope

    return


# PSOLA https://en.wikipedia.org/wiki/PSOLA
def autotune_psola(mic_signal):

    # Detect the note as they come in

    # Shift to intended target note

    # Create envelope from old vs. new version of signal and apply correction envelope

    return

# Linear Predictive Coding (https://en.wikipedia.org/wiki/Linear_predictive_coding)
def autotune_lpc(mic_signal): 

    # Detect the note as they come in

    # Shift to intended target note

    # Create envelope from old vs. new version of signal and apply correction envelope

    return