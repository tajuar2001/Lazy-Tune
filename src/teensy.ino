#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// Audio Components
AudioInputI2S i2s1;
AudioEffectFlange flange1;
AudioEffectReverb reverb1;
AudioMixer4 mixer1;
AudioOutputI2S i2s2;
AudioControlSGTL5000 sgtl5000_1;
AudioConnection patchCords[7] = {
  AudioConnection(i2s1, 0, flange1, 0),
  AudioConnection(i2s1, 0, reverb1, 0),
  AudioConnection(i2s1, 0, mixer1, 2),
  AudioConnection(flange1, 0, mixer1, 0),
  AudioConnection(reverb1, 0, mixer1, 1),
  AudioConnection(mixer1, 0, i2s2, 0),
  AudioConnection(mixer1, 0, i2s2, 1)
};


// Flanger Buffer
static const int FLANGE_BUFFER_SIZE = 512;
short flangeBuffer[FLANGE_BUFFER_SIZE];

// Setup routine
void setup() {
  Serial.begin(9600);
  AudioMemory(12);

  sgtl5000_1.enable();
  sgtl5000_1.volume(1);

  // Initialize mixer gains
  initializeMixerGains();

  // Initialize flanger
  flange1.begin(flangeBuffer, FLANGE_BUFFER_SIZE, 100, 100, 100);
}

// Loop routine
void loop() {
  // Read commands from Serial
  readAndApplySerialCommands();
}

// Initialize mixer gains
void initializeMixerGains() {
  mixer1.gain(0, 0); // Flange
  mixer1.gain(1, 0); // Reverb
  mixer1.gain(2, 0); // Dry
}

// Read and apply serial commands
void readAndApplySerialCommands() {
  if (Serial.available() > 0) {
    // Read the incoming command
    char commandBuffer[10];
    readSerialCommand(commandBuffer, sizeof(commandBuffer));

    // Parse and apply the command
    applySerialCommand(commandBuffer);
  }
}

// Read serial command into buffer
void readSerialCommand(char *buffer, size_t bufferSize) {
  size_t index = 0;
  while (index < bufferSize - 1 && Serial.available()) {
    char c = Serial.read();
    if (c == '\n') break;
    buffer[index++] = c;
  }
  buffer[index] = '\0'; // Null-terminate the string
}

// Parse and apply the command
void applySerialCommand(const char *command) {
  switch (command[0]) {
    case 'f': setMixerGain(0, command + 1); break;
    case 'r': setMixerGain(1, command + 1); break;
    case 'd': setMixerGain(2, command + 1); break;
    default: Serial.println("Invalid effect type"); break;
  }
}

// Set mixer gain
void setMixerGain(uint8_t channel, const char *gainStr) {
  float gainValue = atof(gainStr);
  mixer1.gain(channel, gainValue);

  // Output the new gain value
  Serial.print("Channel ");
  Serial.print(channel);
  Serial.print(" gain set to ");
  Serial.println(gainValue);
}