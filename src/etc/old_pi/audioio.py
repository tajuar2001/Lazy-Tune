import pyaudio
import numpy as np
import sys

# Initialize PyAudio
p = pyaudio.PyAudio()

# Define parameters for audio stream
FORMAT = pyaudio.paInt16
CHANNELS = 1
RATE = 44100  # Sample rate (in Hz)
CHUNK = 1024  # Number of audio frames per buffer

# Create input and output audio streams
input_stream = p.open(format=FORMAT, channels=CHANNELS, rate=RATE, input=True, frames_per_buffer=CHUNK)
output_stream = p.open(format=FORMAT, channels=CHANNELS, rate=RATE, output=True)

print("Recording and playing audio. Press Ctrl+C to exit...")

try:
    while True:
        # Read audio data from the input stream
        input_data = input_stream.read(CHUNK)
        
        # Play the same data through the output stream
        output_stream.write(input_data)
        
except KeyboardInterrupt:
    print("Recording and playback stopped.")

# Close the audio streams and terminate PyAudio
input_stream.stop_stream()
input_stream.close()
output_stream.stop_stream()
output_stream.close()
p.terminate()
