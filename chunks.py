import subprocess
import sys

import auto_tune

# Define the command for recording with the desired parameters
sox_command = [
    "rec",
    "-q",  # quiet mode, no progress
    "--buffer", "2048",
    "-r", "48000",
    "-c", "2",  # number of channels
    "-d"  # default audio device
]

# Define a function to process the audio chunk
def process_audio_chunk(chunk):
    # Implement your audio processing here
    # For example, you could adjust volume, apply filters, etc.

        ### ------------------------------------------------------------------------------------ ###

    processed_chunk = auto_tune.autotune(chunk, formant_flag=0, method=2) # formant_flag=1 (no correction), 0=following methods=0 cepstrum, 1=cepstrum_new, 2=psola
    # Normalize the processed chunk
    # normalized_chunk = peak_normalize(processed_chunk, target_amplitude=0.9)
    normalized_chunk = processed_chunk
    # Ensure that normalized_chunk matches the window size
    if len(normalized_chunk) > auto_tune.window_size:
        # If normalized_chunk is larger, trim it to match the window size
        normalized_chunk = normalized_chunk[:auto_tune.window_size]
    elif len(normalized_chunk) < auto_tune.window_size:
        # If normalized_chunk is smaller, pad it with zeros
        pad_length = auto_tune.window_size - len(normalized_chunk)
        normalized_chunk = auto_tune.np.pad(normalized_chunk, (0, pad_length), 'constant')

        ### ------------------------------------------------------------------------------------ ###

    return processed_chunk

# Set up a pipeline to read chunks of audio data from SoX
process = subprocess.Popen(sox_command, stdout=subprocess.PIPE)

try:
    while True:
        # Read a chunk of audio data
        chunk = process.stdout.read(4096)
        if not chunk:
            break
        
        # Process the audio chunk
        processed_chunk = process_audio_chunk(chunk)
        
        # Here, instead of playing the chunk, we print it.
        # You'll need to send it to an audio output device or save it to a file.
        # This could be done using a library like PyAudio or similar.
        sys.stdout.buffer.write(processed_chunk)
except KeyboardInterrupt:
    # Handle any cleanup here
    process.kill()
except Exception as e:
    # Handle any other exceptions here
    print(e)
    process.kill()
