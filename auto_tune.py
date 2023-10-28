import numpy as np
import aubio # https://github.com/aubio/aubio
import pyaudio

import scipy.io.wavfile as wavfile

# Auto-Tune Prototype

# STFT (Pitch Detection)

# Pitch Shift

# Formant Preservation

# Note Transition

semitone_distance = 2**(1/12)
sample_rate = 44100 # Khz

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
    chunk = mic_signal

    fft_result = np.fft.fft(chunk)
    magnitudes = np.abs(fft_result)
    frequency_index = np.argmax(magnitudes)
    main_frequency = frequency_index * sample_rate / len(chunk)

    # find the nearest semitone
    nearest_frequency = shift_to_nearest_semitone(main_frequency)

    # shift it to that semitone idk just scalar of FFT
    frequency_ratio = nearest_frequency / main_frequency
    shifted_chunk = np.interp(np.arange(0, len(chunk), frequency_ratio), np.arange(0, len(chunk)), chunk)
    
    return shifted_chunk

#Cepstrum (https://en.wikipedia.org/wiki/Cepstrum)
def autotune_cepstrum(mic_signal): 
    # do pitch shifting
    chunk = np.fft.fft(mic_signal)
    shifted_chunk = np.fft.fft(autotune_original(mic_signal))

    # Create envelope from old vs. new version of signal and apply correction envelope
    cepstrum1 = np.real(np.fft.ifft(np.log(np.abs(chunk))))
    cepstrum2 = np.real(np.fft.ifft(np.log(np.abs(shifted_chunk))))

    # cut the cepstrum to get only 50 indexes in the middle
    middle = (len(cepstrum1) - 50) // 2
    cut_original = cepstrum1[middle:middle+50]
    cut_shifted = cepstrum2[middle:middle+50]

    # extract the envelope from the cut window
    envelope1 = np.exp(2*np.real(np.fft.fft(cut_original)))
    envelope2 = np.exp(2*np.real(np.fft.fft(cut_shifted)))

    # find the correction factor from the two envelopes
    correction_factor = envelope1/envelope2

    interpolated_correction_factor = np.interp(
    np.linspace(0, len(correction_factor) - 1, len(shifted_chunk)),
    np.arange(0, len(correction_factor)),
    correction_factor
)

    # apply correction to the shifted_chunk
    result = np.multiply(shifted_chunk, interpolated_correction_factor)

    # real(ifft(result)) to return time domain version
    return np.real(np.fft.ifft(result))


# PSOLA https://en.wikipedia.org/wiki/PSOLA
def autotune_psola(mic_signal):
    # find the main frequency of the chunk

    # find the nearest semitone

    # pitch shift using psola

    return

# Linear Predictive Coding (https://en.wikipedia.org/wiki/Linear_predictive_coding)
def autotune_lpc(mic_signal): 

    # Detect the note as they come in

    # Shift to intended target note

    # Create envelope from old vs. new version of signal and apply correction envelope

    return

# Function to normalize audio data to the specified maximum amplitude
def peak_normalize(audio_data, target_amplitude=0.9):
    max_amplitude = np.max(np.abs(audio_data))
    scaling_factor = 32767*target_amplitude / max_amplitude
    normalized_audio_data = audio_data * scaling_factor
    return normalized_audio_data

input_file = 'test_chunk.wav'
output_file = 'autotuned_chunk.wav'
window_size = 882

sample_rate, audio_data = wavfile.read(input_file)

processed_audio = np.zeros_like(audio_data, dtype=np.float64)

# Process the audio in chunks using a sliding window
for i in range(0, len(audio_data), window_size):
    chunk = audio_data[i:i+window_size]
    # Process the chunk using your autotune function
    processed_chunk = autotune(chunk, formant_flag=0, method=0)
    # Normalize the processed chunk
    normalized_chunk = peak_normalize(processed_chunk, target_amplitude=0.9)
    # Store the normalized chunk in the processed audio array
    processed_audio[i:i+window_size] = normalized_chunk

# Save the processed and normalized audio as a new WAV file
wavfile.write(output_file, sample_rate, processed_audio.astype(np.int16))