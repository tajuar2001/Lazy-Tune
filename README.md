# EECS 452 Project: LazyTune

## Project Overview
Lazytune is an ambitious project that merges creativity with technology, transforming an AKAI MPK Mini II MIDI keyboard into a versatile digital/electronic synth instrument. Utilizing a Raspberry Pi and Teensy audio shield, the project stands out in signal processing and audio I/O capabilities.

### Key Components
- **AKAI MPK Mini II**: Repurposed as the main project enclosure, excluding it from the budget requirements.
- **Raspberry Pi**: Serves as the processing unit for signal manipulation and audio input/output operations.
- **Teensy Audio Shield**: Enhances the audio processing capabilities with a focus on high-fidelity output.
- **Mido MIDI Library**: Facilitates MIDI input processing within the Python environment.
- **C Programming on Teensy**: Employs the power of C for efficient execution of signal processing tasks.

## Software Architecture
The heart of Lazytune lies in its software, designed to be both robust and flexible:
- **Python Environment**: Acts as the backbone for real-time audio processing, where audio chunks are manipulated using custom functions to apply effects and transformations.
- **C/C++ Implementation**: Core algorithms, especially the vocoder, are implemented in C/C++ on the Teensy platform for optimized performance.

### Audio Processing
Lazytune aims to deliver a rich suite of audio effects:
- **Autotune**: A fundamental feature that corrects pitch in vocals, providing that quintessential contemporary sound.
- **Vocoder**: Merges the sonic characteristics of an instrument input with vocal modulation, creating unique textures.
- **Additional Effects**: Plans to include reverb, distortion, delay, flanger, and more, broadening the creative palette.

### Technical Aspects
- **Libarray**: This library is crucial for managing complex data structures, ensuring efficient audio data manipulation.
- **Python Functions**: Dedicated to processing audio chunks, these functions are where the magic happens—each chunk is passed through Python's versatile environment before playback.
- **C++ on Teensy**: Select processing tasks, like the vocoder algorithm, are handled by the Teensy for real-time performance and low latency.

## Integration of SoX and Python for Audio Processing

In the landscape of Lazytune's audio processing, SoX (Sound eXchange) stands as a pivotal tool. SoX is a cross-platform command-line audio utility that allows us to handle various audio formats and apply a myriad of effects. Here's how we incorporate it:

### The Role of SoX
- **Audio Conversion and Manipulation**: SoX is adept at converting audio files to different formats, adjusting quality, and performing sound manipulations, making it an indispensable part of Lazytune's audio processing pipeline.
- **Effects Chain**: Through SoX, we apply a chain of effects to audio signals. This includes pitch correction, equalization, and more complex transformations pivotal for the autotune and vocoder features of Lazytune.

### Python and SoX
- **Subprocess Control**: Our Python scripts wield the `subprocess` module to interact with SoX, enabling us to build a real-time audio processing environment that's both flexible and powerful.
- **Stream Handling**: Audio streams are meticulously managed by Python, which communicates with SoX to process and manipulate audio chunks on-the-fly, ensuring a seamless user experience.

### LibSoX: The C Library
- **Low-Level Access**: For scenarios requiring granular control, we delve into LibSoX, the underlying C library that powers the SoX utility. This allows Lazytune to achieve lower-level audio processing tasks, crucial for real-time performance.
- **Teensy Integration**: Critical audio processing routines, especially those requiring low latency, are implemented directly in C/C++ on the Teensy hardware using LibSoX for maximum efficiency.

### Libarray: Managing Data with Ease
- **Efficient Data Handling**: Libarray is leveraged to manage audio data structures efficiently. It's instrumental in organizing the audio chunks that SoX processes, ensuring that data is handled in an optimized fashion.
- **Python Interfacing**: Our Python code interfaces with libarray to maintain the integrity of audio data throughout the processing lifecycle, from input to effect application and eventual output.

## Project Goals
Lazytune is not just about creating music; it's about pushing the boundaries of digital music synthesis, opening up new possibilities for audio effects, and integrating advanced features that could potentially include:
- DAW integration via VST 3 API
- Machine learning for predictive audio effects
- User presets and configuration saving
- Wireless connectivity for remote access and data streaming
- Room equalization for optimal audio output in different environments
- A broad spectrum of audio effects to enhance user creativity

## Contributions
We welcome contributions and collaborations. If you're passionate about music, audio processing, or just love tinkering with sound, join us in making Lazytune a symphony of technology and creativity!
