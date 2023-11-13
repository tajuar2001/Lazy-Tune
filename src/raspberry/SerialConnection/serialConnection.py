import serial
import time

# Replace '/dev/ttyACM0' with your serial port if different
serial_port = '/dev/ttyACM0'
baud_rate = 9600  # Should be the same as Teensy's

# Open the serial connection
ser = serial.Serial(serial_port, baud_rate, timeout=1)

def send_command(effect_type, value):
    """
    Send a command to the Teensy to control audio effects.
    
    :param effect_type: The effect type ('f' for flange, 'r' for reverb, 'd' for dry)
    :param value: The gain value to set for the effect (0.0 to 1.0)
    """
    command = f"{effect_type}{value}\n"
    ser.write(command.encode())

def set_flange_gain(value):
    send_command('f', value)

def set_reverb_gain(value):
    send_command('r', value)

def set_dry_gain(value):
    send_command('d', value)

try:
    # Example usage:
    while True:
        # Set flange gain to 0.5
        set_flange_gain(0.5)
        time.sleep(2)

        # Set reverb gain to 0.8
        set_reverb_gain(0.8)
        time.sleep(2)

        # Set dry gain to 0.3
        set_dry_gain(0.3)
        time.sleep(2)
        
except KeyboardInterrupt:
    print("Program terminated by user")

finally:
    ser.close()  # Always close the connection when done
