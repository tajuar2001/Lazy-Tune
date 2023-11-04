import numpy as np

import scipy.io.wavfile as wavfile

# Auto-Tune Prototype

# STFT (Pitch Detection)

# Pitch Shift

# Formant Preservation

# Note Transition

semitone_distance = 2**(1/12)
sample_rate = 48000 # Khz

### Original

def autotune(mic_signal, formant_flag=0, method=0): # input signal 44.1Khz, bool formant-preservation, method
    if formant_flag == 1:
        return autotune_original(mic_signal)
    if method == 0:
        return autotune_cepstrum(mic_signal)
    if method == 1:
        return autotune_cepstrum_new(mic_signal)
    if method == 2:
        return autotune_psola(mic_signal)
    # if method == 3:
    #     return autotune_lpc(mic_signal)
    return

# find the nearest frequency
def shift_to_nearest_semitone(note_frequency):
        # Calculate the nearest semitone frequency
        note_frequency = max(note_frequency, 1e-9) # no zero allowed
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

    if main_frequency == 0:
    # Handle the case where main_frequency is 0 (e.g., when there's no signal)
        shifted_chunk = np.zeros_like(chunk)
    else:
        frequency_ratio = nearest_frequency / main_frequency
        shifted_chunk = np.interp(np.arange(0, len(chunk), frequency_ratio), np.arange(0, len(chunk)), chunk)

    
    return shifted_chunk

### Cepstrum

#Cepstrum (https://en.wikipedia.org/wiki/Cepstrum)
def autotune_cepstrum(mic_signal): 
    # do pitch shifting
    chunk = np.fft.fft(mic_signal)
    shifted_chunk = np.fft.fft(autotune_original(mic_signal))

    # Create envelope from old vs. new version of signal and apply correction envelope
    cepstrum1 = np.real(np.fft.ifft(np.log(np.abs(chunk) + 1e-9)))
    cepstrum2 = np.real(np.fft.ifft(np.log(np.abs(shifted_chunk) + 1e-9)))

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

def overlap_and_add(input_signal, hop_size, overlap_constant):
    input_length = len(input_signal)

    # Calculate the output length and initialize the result array
    output_length = input_length + (overlap_constant - 1) * hop_size
    output_signal = np.zeros(output_length)

    # Perform overlap-and-add without convolution
    for i in range(0, input_length, hop_size):
        start = i
        end = min(i + hop_size, input_length)
        segment = input_signal[start:end]

        # Add the segment to the appropriate location in the output array
        output_start = i
        output_end = output_start + len(segment)
        output_signal[output_start:output_end] += segment

    return output_signal

# idea: https://dsp.stackexchange.com/questions/37141/preserving-formants-using-cepstrum
def autotune_cepstrum_new(mic_signal):
    FFT1 = np.fft.fft(mic_signal)
    FFT2 = np.fft.fft(autotune_original(mic_signal))
    cepstrum1 = np.real(np.fft.ifft(np.log(np.abs(FFT1) + 1e-9)))
    cepstrum2 = np.real(np.fft.ifft(np.log(np.abs(FFT2) + 1e-9)))

    # Low-pass window from cepstrum
    cutoff_index = 50  # Choose your cutoff index
    cep_cut1 = cepstrum1.copy()
    cep_cut2 = cepstrum2.copy()
    cep_cut1[cutoff_index:] = 0
    cep_cut2[cutoff_index:] = 0

    # Extract the envelope from the slashed window
    envelope1 = np.exp(2 * np.real(np.fft.fft(cep_cut1)))  # Spectral shape
    envelope2 = np.exp(2 * np.real(np.fft.fft(cep_cut2)))  # Spectral shape

    if len(envelope1) > len(envelope2):
        envelope1 = envelope1[:len(envelope2)]
    elif len(envelope2) > len(envelope1):
        envelope2 = envelope2[:len(envelope1)]

    # Find the correction factor from envelopes
    warp_factor = envelope1 / envelope2

    if len(warp_factor) > len(FFT2):
        warp_factor = warp_factor[:len(FFT2)]
    elif len(FFT2) > len(warp_factor):
        FFT2 = FFT2[:len(warp_factor)]

    # Apply the correction
    new = FFT2 * warp_factor

    # Back to the time domain
    New_Formant_signal = np.real(np.fft.ifft(new))

    # You may need to implement overlap-and-add for better results
    # You can use scipy's signal.overlap_add or implement your own

    # Perform overlap and add
    hop_size = 147  # Adjust to your preference
    overlap = 0.75  # Adjust to your preference
    return overlap_and_add(New_Formant_signal, hop_size, int(hop_size * overlap))

### PSOLA

def find_pitch_periods(input_audio):
    # Assuming a fixed pitch period of your choice in samples.
    fixed_period_samples = 147  # Adjust this value as needed

    # Determine pitch periods based on the fixed period in samples.
    pitch_periods = []

    # Iterate through the audio signal and find pitch marks at fixed intervals.
    for i in range(0, len(input_audio), fixed_period_samples):
        pitch_periods.append(i)

    return pitch_periods

def overlap_and_add_psola(output_audio, segment):
    # Ensure that the segment is not shorter than the expected overlap length.
    overlap_length = len(segment) // 2
    if overlap_length == 0:
        return output_audio

    # Ensure that the segment is not longer than the existing output_audio.
    if len(segment) > len(output_audio):
        output_audio = np.pad(output_audio, (0, len(segment) - len(output_audio)))

    # Define a window function (e.g., Hanning window) to use for overlap-and-add.
    window = np.hanning(len(segment))

    # Convert both segment and window to float64 to avoid data type mismatch.
    segment = segment.astype(float)
    window = window.astype(float)

    # Apply the window function to the segment.
    segment *= window

    # Overlap-and-add the modified segment to the output.
    output_audio[:overlap_length] += segment[:overlap_length]
    output_audio[overlap_length:overlap_length + len(segment[overlap_length:])] = segment[overlap_length:]

    return output_audio

# PSOLA https://en.wikipedia.org/wiki/PSOLA
def autotune_psola(mic_signal):
    # Analyze pitch and find pitch marks
    pitch_periods = find_pitch_periods(mic_signal)

    # Initialize an empty output signal
    output_audio = np.zeros(len(mic_signal))

    # PSOLA: Overlap and add
    for period in pitch_periods:
        pitch_period = 2 * (period - pitch_periods[0])

        # Extract segments centered at pitch marks
        segment = mic_signal[period - pitch_period // 2 : period + pitch_period // 2]

        # Modify the segment (expand/contract as needed)

        # Overlap and add the modified segment to the output
        output_audio = overlap_and_add_psola(output_audio, segment)

    # Scale the new signal to match the length of the original (use resampling or time-stretching)

    # You can add your resampling or time-stretching code here
    # For example, using librosa's time-stretching functions
    return output_audio

# Linear Predictive Coding (https://en.wikipedia.org/wiki/Linear_predictive_coding)
def autotune_lpc(mic_signal): 

    # Detect the note as they come in

    # Shift to intended target note

    # Create envelope from old vs. new version of signal and apply correction envelope

    return

# Function to normalize audio data to the specified maximum amplitude
def peak_normalize(audio_data, target_amplitude=0.9):
    max_amplitude = np.max(np.abs(audio_data))
    if max_amplitude == 0:
         scaling_factor = 0
    else:
         scaling_factor = 32767*target_amplitude / max_amplitude
    normalized_audio_data = audio_data * scaling_factor
    return normalized_audio_data

input_file = 'test_chunk.wav'
output_file = 'autotuned_chunk.wav'
window_size = 882

sample_rate, audio_data = wavfile.read(input_file)

num_chunks = len(audio_data) // window_size
processed_audio = np.zeros(len(audio_data), dtype=np.float64)

for i in range(num_chunks):
        chunk = audio_data[i*window_size:(i+1)*window_size]
        # Process the chunk using your autotune function
        processed_chunk = autotune(chunk, formant_flag=0, method=2)
        # Normalize the processed chunk
        # normalized_chunk = peak_normalize(processed_chunk, target_amplitude=0.9)
        normalized_chunk = processed_chunk

        # Ensure that normalized_chunk matches the window size
        if len(normalized_chunk) > window_size:
            # If normalized_chunk is larger, trim it to match the window size
            normalized_chunk = normalized_chunk[:window_size]
        elif len(normalized_chunk) < window_size:
            # If normalized_chunk is smaller, pad it with zeros
            pad_length = window_size - len(normalized_chunk)
            normalized_chunk = np.pad(normalized_chunk, (0, pad_length), 'constant')
        
        # Store the normalized chunk in the processed audio array
        processed_audio[i*window_size:(i+1)*window_size] = normalized_chunk

    # Save the processed and normalized audio as a new WAV file
wavfile.write(output_file, sample_rate, processed_audio.astype(np.int16))