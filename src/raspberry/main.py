import os
import time
import mido
import serial
import threading
import tkinter as tk
from tkinter import Scale, Canvas


#Setting Display Environment 
os.environ['DISPLAY'] = ':0.0'

#connecting the keyboard to the teensy
keyboard_port_name = 'MPKmini2 MIDI 1' 
teensy_port_name = 'Teensy MIDI MIDI 1'  

def midi_forwarding_task():
    with mido.open_input(keyboard_port_name) as inport, mido.open_output(teensy_port_name) as outport:
        for msg in inport:
            outport.send(msg)

def main():        
    threading.Thread(target=midi_forwarding_task, daemon=True).start()
    
    window = tk.Tk()
    window.title("Sound Effects Controller")
    window.geometry("1200x600")  # Set window size

    # Function to handle slider value changes
    def on_slider_change(value, label):
        print(f"{label} value: {value}")
        
    def send_serial_data(message, port='/dev/ttyACM0', baud_rate=115200):
        try:
            # Open the serial port
            with serial.Serial(port, baud_rate, timeout=1) as ser:
                # Send the message
                ser.write(message.encode())
                time.sleep(0.1)  # Wait for the data to be transmitted

        except Exception as e:
            print(f"Error sending data: {e}")



    # Function to switch to the edit effect screen
    def show_edit_effect_screen():
        for widget in window.winfo_children():
            widget.destroy()

        # Create vertical sliders for effects
        Scale(window, label="Delay", from_=0, to=100, orient="vertical", command=lambda value: on_slider_change(value, "Delay")).pack(side="left")
        Scale(window, label="Flange", from_=0, to=100, orient="vertical", command=lambda value: on_slider_change(value, "Flange")).pack(side="left")
        Scale(window, label="Freeverb", from_=0, to=100, orient="vertical", command=lambda value: on_slider_change(value, "Freeverb")).pack(side="left")
        Scale(window, label="Chorus", from_=0, to=100, orient="vertical", command=lambda value: on_slider_change(value, "Chorus")).pack(side="left")

        # Button to switch to distortion tab
        tk.Button(window, text="Distortion", command=show_distortion_screen).pack(side="left")

        # Back button
        tk.Button(window, text="Back", command=show_main_screen).pack(side="left")

    # Function to switch to the distortion screen
    def show_distortion_screen():
        for widget in window.winfo_children():
            widget.destroy()

        # Create vertical sliders for distortion effects
        Scale(window, label="Bitcrush", from_=0, to=100, orient="vertical", command=lambda value: on_slider_change(value, "Bitcrush")).pack(side="left")
        Scale(window, label="Overdrive", from_=0, to=100, orient="vertical", command=lambda value: on_slider_change(value, "Overdrive")).pack(side="left")
        Scale(window, label="Fuzz", from_=0, to=100, orient="vertical", command=lambda value: on_slider_change(value, "Fuzz")).pack(side="left")
        Scale(window, label="Multiplier", from_=0, to=100, orient="vertical", command=lambda value: on_slider_change(value, "Multiplier")).pack(side="left")

        # Back button
        tk.Button(window, text="Back", command=show_edit_effect_screen).pack(side="left")

    # Function to show the main screen
    def show_main_screen():
        for widget in window.winfo_children():
            widget.destroy()

        # Configure grid for centering with appropriate weights
        window.rowconfigure(0, weight=0)  # Top row for "Lazy-Tune" and "Edit Effect"
        window.rowconfigure(1, weight=1)
        window.rowconfigure(2, weight=1)
        window.columnconfigure(0, weight=1)
        window.columnconfigure(1, weight=1)
        window.columnconfigure(2, weight=1)
        window.columnconfigure(3, weight=1)

        # Label for "Lazy-Tune"
        lazy_tune_label = tk.Label(window, text="Lazy-Tune", font=("Helvetica", 30))
        lazy_tune_label.grid(row=0, column=0, columnspan=4, sticky="ew")  # Span 4 columns for centering

        # Determine button size
        button_width = 20  # Adjust button width as needed
        button_height = 3  # Adjust button height as needed

        # Define toggle functionality for buttons
        def toggle_button(button_name):
            button_states[button_name] = not button_states[button_name]
            color = "green" if button_states[button_name] else "red"
            buttons[button_name].config(bg=color)
            print(f"{button_name} state: {'On' if button_states[button_name] else 'Off'}")
            if button_name == "Microphone":
                if button_states[button_name]:
                    send_serial_data("d1")
                else:
                    send_serial_data("d0")
            elif button_name == "Carrier":
                if button_states[button_name]:
                    send_serial_data("c1")
                else:
                    send_serial_data("c0")
            

        # Maintain state for each button
        global button_states
        button_states = {
            "Microphone": False,
            "Carrier": False,
            "Autotune": False,
            "Vocoder": False
        }

        # Buttons with toggle functionality
        global buttons
        buttons = {
            "Microphone": tk.Button(window, text="Microphone", width=button_width, height=button_height, bg="red", command=lambda: toggle_button("Microphone")),
            "Carrier": tk.Button(window, text="Carrier", width=button_width, height=button_height, bg="red", command=lambda: toggle_button("Carrier")),
            "Autotune": tk.Button(window, text="Autotune", width=button_width, height=button_height, bg="red", command=lambda: toggle_button("Autotune")),
            "Vocoder": tk.Button(window, text="Vocoder", width=button_width, height=button_height, bg="red", command=lambda: toggle_button("Vocoder"))
        }

        # Place buttons in grid, centered below "Lazy-Tune" label
        buttons["Microphone"].grid(row=1, column=1, sticky="nsew", padx=10, pady=10)
        buttons["Carrier"].grid(row=1, column=2, sticky="nsew", padx=10, pady=10)
        buttons["Autotune"].grid(row=2, column=1, sticky="nsew", padx=10, pady=10)
        buttons["Vocoder"].grid(row=2, column=2, sticky="nsew", padx=10, pady=10)

        # Edit effect button in top right corner
        edit_effect_button = tk.Button(window, text="Edit Effect", font=("Helvetica", 14), width=20, height=2, command=show_edit_effect_screen)
        edit_effect_button.grid(row=0, column=2, sticky="ne", padx=0, pady=10)

    show_main_screen()
    window.mainloop()

main()
