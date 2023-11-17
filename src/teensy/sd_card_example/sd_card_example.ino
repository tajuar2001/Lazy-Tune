#include <SerialFlash.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

// Audio Components
AudioPlaySdWav           playWav1;         // SD Card Player
AudioInputI2S i2s1;                        // IS2 input
AudioOutputI2S i2s2;                       // IS2 output
AudioControlSGTL5000 audioShield;          // Audio shield

AudioConnection patchCords[4] {
  AudioConnection(playWav1, 0, i2s2, 0),
  AudioConnection(playWav1, 0, i2s2, 1),

  AudioConnection(i2s1, 0, i2s2, 0),
  AudioConnection(i2s1, 0, i2s2, 1),
};

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7   // Teensy 4 ignores this, uses pin 11
#define SDCARD_SCK_PIN   14  // Teensy 4 ignores this, uses pin 13

// Function declarations
void processAudio(); // Function to process and autotune audio
void readAndExecuteCommands(); // Function to read serial commands and execute them

void setup() {
    Serial.begin(115200); // Start serial communication at a higher baud rate
    AudioMemory(8); // Allocate memory for audio processing

    audioShield.enable(); // audioShield initialization
    audioShield.volume(0.5);

    // SD Card Setup
    SPI.setMOSI(SDCARD_MOSI_PIN);
    SPI.setSCK(SDCARD_SCK_PIN);
    if (!(SD.begin(SDCARD_CS_PIN))) {
      // stop here, but print a message repetitively
      while (1) {
        Serial.println("Unable to access the SD card");
        delay(500);
      }
    }
}

void loop() {
    playFile("drum1.WAV");  // filenames are always uppercase 8.3 format
    // Channel 1 = Pads
    if(usbMIDI.read(1)) {
      switch (usbMIDI.getType()) {
      case midi::NoteOn: { // PAD_PRESS
        int pad_note = usbMIDI.getData1(); // integer 44 to 51
        int pad_velocity = usbMIDI.getData2(); // 0 to 100
        Serial.print("Note = ");
        Serial.print(pad_note);
        Serial.print(", Velocity = ");
        Serial.print(pad_velocity);
        break;
        }
      case midi::NoteOff: // PAD_RELEASE
        {// same as NoteOn
        break;}
      }
    }
}
void playPad(int pad_note, int pad_velocity) {
  int file_number = pad_note - 48 + 1;

}

void playFile(const char *filename)
{
  Serial.print("Playing file: ");
  Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playWav1.play(filename);

  // A brief delay for the library read WAV info
  delay(25);

  // Simply wait for the file to finish playing.
  while (playWav1.isPlaying()) {
    // uncomment these lines if you audio shield
    // has the optional volume pot soldered
    //float vol = analogRead(15);
    //vol = vol / 1024;
    // sgtl5000_1.volume(vol);
  }
}
