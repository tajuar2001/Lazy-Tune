#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "autotune.h"

// Create an instance of the Autotune class
Autotune autotuner;

void setup() {
    Serial.begin(9600);
    // Additional setup code goes here
}

void loop() {
    // Your main loop code goes here

    // autotuneOriginal 
    const size_t signalLength = 1024;  
    int16_t micSignal[signalLength];   // Replace this with your actual input signal
    autotuner.autotuneOriginal(micSignal, signalLength);

    // Additional loop code goes here
}
