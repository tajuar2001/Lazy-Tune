#connecting midi signal from raspberry pi to teensyimport mido
import mido

keyboard_port_name = 'MPKmini2 MIDI 1'  # Replace with your keyboard's MIDI port name
teensy_port_name = 'Teensy MIDI MIDI 1'  # Replace with your Teensy's MIDI port name

try:
    with mido.open_input(keyboard_port_name) as inport, mido.open_output(teensy_port_name) as outport:
        print(f"Forwarding MIDI messages from {keyboard_port_name} to {teensy_port_name}")
        for msg in inport:
            outport.send(msg)

except (IOError, OSError) as e:
    print(f"Error: {e}")
