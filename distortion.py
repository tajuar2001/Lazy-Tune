import numpy as np

# Distortion
def distortion(audio_chunk, threshold=0.7):

    return np.clip(audio_chunk, -threshold, threshold)