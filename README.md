# EECS 452 Project: LazyTune

![Overall System](/src/etc/System.png)

## Project Overview
LazyTune involves reengineering the AKAI MPK Mini II MIDI keyboard into a multifaceted digital and electronic synthesizer. At the heart of the project is the Teensy 4.1 microcontroller, which is programmed to facilitate real-time autotune and vocoder functionalities. Additionally, a Raspberry Pi is utilized to adeptly manage input and output operations. Moreover, it controls the mechanisms for both the autotune and vocoder through serial communication. The MIDI keyboard, integral to our design, serves as a dynamic interface for manipulating various sound effects as well. Utilizing a Raspberry Pi, Teensy 4.1, and an audio shield, the project stands out in its signal processing and audio I/O capabilities.

### Key Components
- **AKAI MPK Mini II**: Repurposed as the main project enclosure, excluding it from the budget requirements.
- **Raspberry Pi**: Acts as the processing unit, primarily for signal manipulation and routing audio/MIDI data between the AKAI MPK Mini II and Teensy 4.1. It plays a key role in managing the overall control flow of the project.
- **Teensy Audio Shield**: This shield, when combined with Teensy 4.1, significantly enhances the system's audio processing capabilities. It is optimized for high-fidelity audio input and output, crucial for effective real-time audio effects processing.
- **Mido MIDI Library**: Facilitates MIDI input processing within the Python environment.
- **PJRC Libraries**: Essential for maximizing the audio processing potential of the Teensy 4.1, these libraries are used to implement and optimize the core audio processing algorithms, including autotune and vocoder effects.

## Software Architecture
The heart of Lazytune lies in its software, designed to be both robust and flexible:
- **Python Environment on Raspberry Pi**: Serves as the control hub for managing MIDI data and user interface interactions. This environment handles the routing of audio and MIDI signals to and from the Teensy 4.1. Additionally, it may include some preliminary audio processing and is responsible for overall system coordination.
- **C/C++ Implementation on Teensy 4.1**: The core of real-time audio processing, including the autotune and vocoder algorithms, is implemented in C/C++ on the Teensy 4.1, leveraging its powerful processing capabilities. This ensures low-latency and high-performance audio processing, essential for real-time audio effects.

### Audio Processing
Lazytune aims to deliver a rich suite of audio effects:
- **Autotune**: This feature is intricately implemented using PSOLA (Pitch-Synchronous Overlap and Add) and pitch-shifting techniques on the Teensy 4.1. It provides precise pitch correction in vocals, delivering the sought-after contemporary autotune effect. This implementation ensures real-time responsiveness and high-quality vocal transformation.
- **Vocoder**: A 12-band vocoder is executed on the Teensy 4.1, blending the characteristics of instrument inputs with vocal modulation. This sophisticated approach creates a wide range of unique textures, from classic robotic voices to complex and richly textured sounds.
![Vocoder](/src/etc/vocoder.png)
- **Additional Effects**: The vocoder incorporates a suite of additional effects like reverb, distortion, delay, and flanger. These effects are integrated within the vocoder's processing chain and can be interactively controlled using the AKAI MPK Mini II MIDI keyboard. This setup allows users to play and modify these effects in real-time, significantly expanding the instrument's expressive capabilities.

### Technical Aspects
- **PJRC Libraries**: The project heavily relies on the PJRC libraries and the Teensy Audio Shield to achieve high-quality audio processing with minimal latency. These libraries are essential for harnessing the capabilities of the Teensy 4.1, particularly for real-time tasks like PSOLA/pitch shifting for autotune and the 12-band vocoder processing. The Audio Shield further enhances audio fidelity and ensures low-latency signal processing, which is critical for real-time audio applications.[PJRC](https://www.pjrc.com/teensy/gui/)
- **Serial Communication for System Integration**: T serial link between the Raspberry Pi and Teensy 4.1 is essential for the precise, real-time relay of data, aligning user interactions with audio output seamlessly. It ensures that every adjustment made on the MIDI controller translates instantly into audio processing changes, maintaining the system’s interactive and responsive nature.
- **Auto-Configuration**: The system is designed to automatically configure itself upon startup, ensuring that the Teensy 4.1 and Raspberry Pi are synchronized and ready to process audio. This feature is essential for the system's usability, as it eliminates the need for manual configuration and ensures that the system is always ready to use.


## Project Goals
Lazytune is not just about creating music; it's about pushing the boundaries of digital music synthesis, opening up new possibilities for audio effects, and integrating advanced features that could potentially include:
- DAW integration via VST 3 API
- Machine learning for predictive audio effects
- User presets and configuration saving
- Wireless connectivity for remote access and data streaming
- Room equalization for optimal audio output in different environments
- A broad spectrum of audio effects to enhance user creativity

## Team Contributions

### Tajuar Bhuiyan [GitHub](https://github.com/tajuar2001)
- **Hardware Implementation, Algorithm Development, Real-Time- Audio Processing** 
  
### Christopher Brown [GitHub](https://github.com/chrsbrwn)
- **Audio I/O, Signal Processing & Embedded Systems, Quality Assurance**

### Seiya Kozakai [GitHub](https://github.com/skozakai)
- **Signal Processing, Algorithm Development (C/C++), Quality Assurance**

