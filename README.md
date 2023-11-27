# LazyTune

![Overall System](/src/etc/diagrams/System.png)

## Project Overview
LazyTune involves reengineering the AKAI MPK Mini II MIDI keyboard into a multifaceted digital and electronic synthesizer. At the heart of the project is the Teensy 4.1 microcontroller, which is programmed to facilitate real-time autotune and vocoder functionalities. Additionally, a Raspberry Pi is utilized to adeptly manage input and output operations. Moreover, it controls the mechanisms for both the autotune and vocoder through serial communication. The MIDI keyboard, integral to our design, serves as a dynamic interface for manipulating various sound effects as well. Utilizing a Raspberry Pi, Teensy 4.1, and an audio shield, the project stands out in its signal processing and audio I/O capabilities.

### Key Components
- **AKAI MPK Mini II**: Repurposed as the main project enclosure, excluding it from the budget requirements. Allows for precise control through its 25 velocity-sensitive keys, 8 backlit drum pads, and 8 assignable knobs. It is also used to control the various audio effects, including autotune and vocoder through MIDI input.
- **Raspberry Pi**: Serves as the central processing unit, crucial for signal manipulation and directing audio/MIDI data between the AKAI MPK Mini II and Teensy 4.1. It is instrumental in orchestrating the control flow of the project. The Raspberry Pi employs multithreading to efficiently manage various tasks simultaneously: it runs our GUI, handles MIDI input/output, and manages serial communication with the Teensy 4.1, ensuring smooth and responsive operation across all functionalities.
- **Teensy 4.1**: The Teensy 4.1 is the core of the project, handling all audio processing tasks. It is programmed to implement the autotune and vocoder algorithms, as well as the additional effects.
- **Teensy Audio Shield**: This shield, when combined with Teensy 4.1, significantly enhances the system's audio processing capabilities. It is optimized for high-fidelity audio input and output, crucial for effective real-time audio effects processing. The shield also allows for reading digital audio samples from the on-board microSD card, which is used to store audio samples.
- **Mido MIDI Library**: Facilitates MIDI input processing within the Python environment.
- **PJRC Libraries**: Essential for maximizing the audio processing potential of the Teensy 4.1, these libraries are used to implement and optimize the core audio processing algorithms, including autotune and vocoder effects.
- **Tkinter Library**: Used to create the GUI for the Raspberry Pi, allowing for seamless user interaction with the system. The GUI communicates with the Teensy 4.1 via serial communication, allowing for real-time audio processing adjustments.

## Software Architecture
The heart of Lazytune lies in its software, designed to be both robust and flexible:
- **Python Environment on Raspberry Pi**: Serves as the control hub for managing MIDI data and user interface interactions. This environment handles the routing of audio and MIDI signals to and from the Teensy 4.1. Additionally, it may include some preliminary audio processing and is responsible for overall system coordination.
- **C/C++ Implementation on Teensy 4.1**: The core of real-time audio processing, including the autotune and vocoder algorithms, is implemented in C/C++ on the Teensy 4.1, leveraging its powerful processing capabilities combined with the real-time efficiency of C/C++. This ensures low-latency and high-performance audio processing, essential for real-time audio effects.

### Audio Processing
Lazytune is built on a robust and modular software architecture designed to provide a comprehensive suite of audio effects:
![Vocoder](/src/etc/diagrams/vocoder.png)
- **Autotune**: This feature is intricately implemented using a combination of pitch detection and pitch shifting. Pitch detection is handled by the NoteFrequency object of the PJRC object, with parameters optimized for low-latency. The pitch shifting is implemented using a Phase Vocoder approach. This technique operates in the frequency domain, where it calculates phase differences for small segments and then reassembles the signal using the Overlap and Add method. This implementation ensures real-time responsiveness and high-quality vocal transformation.
- **Vocoder**: A 12-band vocoder is executed on the Teensy 4.1, blending the characteristics of instrument inputs with vocal modulation. This sophisticated approach creates a wide range of unique textures, from classic robotic voices to complex and richly textured sounds.
- **Additional Effects**: The vocoder incorporates a suite of additional effects like reverb, distortion, delay, and flanger. These effects are integrated within the vocoder's processing chain and can be interactively controlled using the AKAI MPK Mini II MIDI keyboard. This setup allows users to play and modify these effects in real-time, significantly expanding the instrument's expressive capabilities.

### Technical Aspects
- **PJRC Libraries**: The project heavily relies on the PJRC libraries and the Teensy Audio Shield to achieve high-quality audio processing with minimal latency. These libraries are essential for harnessing the capabilities of the Teensy 4.1, particularly for real-time tasks like PSOLA/pitch shifting for autotune and the 12-band vocoder processing. The Audio Shield further enhances audio fidelity and ensures low-latency signal processing, which is critical for real-time audio applications. Check it out @[PJRC GUI](https://www.pjrc.com/teensy/gui/)
- **Serial Communication for System Integration**: T serial link between the Raspberry Pi and Teensy 4.1 is essential for the precise, real-time relay of data, aligning user interactions with audio output seamlessly. It ensures that every adjustment made on the touch-screen GUI and MIDI controller translates instantly into audio processing changes, maintaining the system’s interactive and responsive nature.
- **Auto-Configuration**: The system is designed to automatically configure itself upon startup, ensuring that the Teensy 4.1 and Raspberry Pi are synchronized and ready to process audio. This feature is essential for the system's usability, as it eliminates the need for manual configuration and ensures that the system is always ready to use.


## Project Goals
Lazytune is not just about creating music; it's about pushing the boundaries of digital music synthesis, opening up new possibilities for audio effects, and integrating advanced features. Our current focus is on enhancing the system's audio capabilities and introducing a range of sophisticated features, including:
- Advanced Synthesizer Features: Expanding the synthesizer functionality by incorporating an extensive instrument sample library. This feature will allow users to play a wide range of sounds via the MIDI keyboard.
- Waveform Generator: Add control for users to generate and edit their own waveforms, allowing for the creation of unique sounds.
- Stereo Audio Effects: Transitioning from mono to stereo audio processing to enhance the depth and spatial quality of the audio output. Stereo effects such as a widener will significantly improve the audio quality and user experience.

## Team Contributions

### [Tajuar Bhuiyan](https://github.com/tajuar2001)
- **Hardware Implementation, Algorithm Development, Real-Time- Audio Processing** 
  
### [Christopher Brown](https://github.com/chrsbrwn)
- **Audio I/O, Signal Processing & Embedded Systems, Quality Assurance**

### [Seiya Kozakai](https://github.com/skozakai)
- **Signal Processing, Algorithm Development (C/C++), Quality Assurance**




