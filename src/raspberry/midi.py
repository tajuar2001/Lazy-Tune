#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
    Serial.begin(115200);  // Start serial communication
    MIDI.begin(MIDI_CHANNEL_OMNI); // Start MIDI listening on all channels
    // Other setup code...
}

void loop() {
    // Handle serial communication
    if (Serial.available()) {
        // Read and process serial data
    }

    // Handle MIDI messages
    if (MIDI.read()) {
        // Process MIDI messages
        unsigned char type = MIDI.getType();
        unsigned char channel = MIDI.getChannel();
        unsigned char data1 = MIDI.getData1();
        unsigned char data2 = MIDI.getData2();

        // Example: If note on message, do something
        if (type == midi::NoteOn) {
            // Handle note on
        }
    }
}
