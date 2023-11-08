import subprocess
import pyaudio

import numpy as np
import matplotlib.pyplot as plt

from scipy import signal

# Set up the SoX command
buffer_size = 128
sox_command = ["rec", "--buffer", str(buffer_size), "-r", "48000", "-t", "raw", "-e", "signed", "-b", "16", "-c", "1", "-"]

# Define basic LPF
def low_pass_filter(data, cutoff_frequency, sampling_frequency):
    # Design the Butterworth low-pass filter
    nyquist = 0.5 * sampling_frequency
    normal_cutoff = cutoff_frequency / nyquist
    b, a = signal.butter(4, normal_cutoff, btype='low', analog=False)
    
    # Apply the filter to the data
    filtered_data = signal.filtfilt(b, a, data)
    
    return filtered_data
    

# Define a function to process the audio chunk
def process_audio_chunk(chunk):
    # Implement your audio processing here
    # For example, you could adjust volume, apply filters, etc.
    numeric_array = np.frombuffer(chunk, dtype=np.int16)
    print(numeric_array)

        ### ------------------------------------------------------------------------------------ ###

    processed_chunk = low_pass_filter(numeric_array, 200, 48000)

        ### ------------------------------------------------------------------------------------ ###
    return processed_chunk.astype(np.int16).tobytes()

# Start the SoX process
process = subprocess.Popen(sox_command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# Set up the PyAudio stream for playback
p = pyaudio.PyAudio()
stream = p.open(format=p.get_format_from_width(2),  # 16 bits = 2 bytes
                channels=1,
                rate=48000,
                output=True)

# Create a figure and axis for the live waveform plot
fig, ax = plt.subplots(figsize=(10, 4))
ax.set_title("Live Audio Waveform")
ax.set_xlabel("Time (s)")
ax.set_ylabel("Amplitude")

# Initialize an empty line for the plot
line, = ax.plot([], [])

# Set the x-axis limits based on your desired time range
ax.set_xlim(0, 1)  # Adjust the range as needed

# Set the y-axis limits based on your audio amplitude range
ax.set_ylim(-32768, 32767)  # Adjust based on your audio format

try:
    while True:
        # Read a chunk of audio data
        chunk = process.stdout.read(buffer_size)
        
        # If chunk is empty, break from the loop
        if not chunk:
            break

        # Print the type of the chunk
        print(f"Chunk type: {type(chunk)}")
        
        # Print the first 16 bytes of the chunk to get a sense of the data
        print(f"Chunk value (first 16 bytes): {chunk[:16]}")

        stream.write(process_audio_chunk(chunk))

except KeyboardInterrupt:
    # To stop the loop with a keyboard interrupt (CTRL+C)
    print("Recording stopped by user")

finally:
    # When done, close the stream and the SoX process
    stream.stop_stream()
    stream.close()
    p.terminate()
    process.terminate()
    process.wait()
