import subprocess
import pyaudio

# local modules
import auto_tune

# Set up the SoX command
buffer_size = 1024
sox_command = ["rec", "--buffer", str(buffer_size), "-r", "48000", "-t", "raw", "-e", "signed", "-b", "16", "-c", "1", "-"]

# Define a function to process the audio chunk
def process_audio_chunk(chunk):
    # Implement your audio processing here
    # For example, you could adjust volume, apply filters, etc.

        ### ------------------------------------------------------------------------------------ ###

    processed_chunk = auto_tune.autotune(chunk, formant_flag=0, method=1) # formant_flag=1 (no correction), 0=following methods=0 cepstrum, 1=cepstrum_new, 2=psola
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

# Start the SoX process
process = subprocess.Popen(sox_command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# Set up the PyAudio stream for playback
p = pyaudio.PyAudio()
stream = p.open(format=p.get_format_from_width(2),  # 16 bits = 2 bytes
                channels=1,
                rate=48000,
                output=True)

try:
    while True:
        # Read a chunk of audio data
        chunk = process.stdout.read(buffer_size)
        
        # If chunk is empty, break from the loop
        if not chunk:
            break
        
        # Play the chunk
        stream.write(chunk)

        # Print the type of the chunk
        print(f"Chunk type: {type(chunk)}")
        
        # Print the first 16 bytes of the chunk to get a sense of the data
        print(f"Chunk value (first 16 bytes): {chunk[:16]}")

        # Here you would process the chunk as needed (if you're doing more than just playing it)
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
