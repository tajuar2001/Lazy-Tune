import os
import time
import mido
import serial
import threading
import tkinter as tk
from tkinter import *
from ttkthemes import ThemedTk
from tkinter import Scale, Canvas, ttk

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

    # Create Root window to hold all other windows
    root = ThemedTk(theme='kroc')
    print(root.get_themes())
    root.title("Sound Effects Controller")
    root.geometry("1200x600")  # Set window size
    root.columnconfigure(0, weight=1)
    root.rowconfigure(0, weight=1)

    # Configure styles for various GUI elements
    style = ttk.Style()
    style.configure("Custom.Vertical.TScale", troughcolor="pink", background="black", sliderlength=20, sliderthickness=100)
    button_font=("Courier", 24, "bold")
    style.configure("Custom.TButton", font=button_font)
    label_font=("Courier", 30, "bold")
    style.configure("TLabel", foreground="black", font=label_font)
    style.configure("Custom.Horitontal.TScale", troughcolor="pink", background="black", sliderlength=20, sliderthickness=50)
    style.configure("Custom.Horizontal.TScale", troughcolor="pink", sliderlength=20, sliderthickness=100, troughborderwidth=2, sliderborderwidth=2)

    # Define Values for effects initialization
    effects_values = {
            "Delay": 0,
            "Flange": 0,
            "Freeverb": 0,
            "Chorus": 0,
            "Bitcrush": 0,
            "Overdrive": 0,
            "Limiter": 0,
            "Multiplier": 0,
            "Delay Time": 5,
            "Flange Offset": 30,
            "Flange Depth": 0,
            "Flange Delay": 5,
            "Reverb Size": 1,
            "Chorus Voices": 4,
            "Bitcrush Bitdepth": 8,
            "Bitcrush Frequency": 20000
        }

    # Define dynamic variables for live text readthrough
    dynamic_labels = {}
    for label in effects_values:
        dynamic_labels[label] = tk.StringVar()
        dynamic_labels[label].set(f"{label}: {effects_values[label]}")
        
    # Function to handle slider value changes
    def on_slider_change(label, value, designator):
        effects_values[label] = value
        formatted_value = f"{float(value):.2f}"  # Format to 2 decimal places
        send_serial_data(f"{designator}{formatted_value}")
        dynamic_labels[label].set(f"{label}: {formatted_value}")

    def send_serial_data(message, port='/dev/ttyACM0', baud_rate=115200):
        try:
            # Open the serial port
            with serial.Serial(port, baud_rate, timeout=1) as ser:
                # Send the message
                ser.write(message.encode())
                time.sleep(0.1)  # Wait for the data to be transmitted
        except Exception as e:
            print(f"Error sending data: {e}")


    # Functions for various Lazytune presets
    def vocalsPreset():
        send_serial_data("m1")
        send_serial_data('c0')
        send_serial_data('a0')
        send_serial_data('v0')

    def synthPreset():
        send_serial_data("m0")
        send_serial_data('c1')
        send_serial_data('a0')
        send_serial_data('v0')

    def vocoderPreset():
        send_serial_data("m0")
        send_serial_data('c0')
        send_serial_data('a0')
        send_serial_data('v1')

    def autotunePreset():
        send_serial_data("m0")
        send_serial_data('c0')
        send_serial_data('a1')
        send_serial_data('v0')       

    # Function to switch to the edit effect screen
    def show_effect_mix_screen():
        for widget in root.winfo_children():
            widget.destroy()

        # Create background panel
        window = ttk.Frame(root, padding=(10, 10, 10, 10))

        # Configure grid for centering with appropriate weights
        window.grid(column=0, row=0, sticky="nsew")
        window.rowconfigure(0, weight=0)  # Top row for window buttons
        window.rowconfigure(1, weight=0)  # Title
        window.rowconfigure(2, weight=4)  # For effects Faders
        window.rowconfigure(3, weight=0)   # For slider Labels
        window.columnconfigure(0, weight=1)
        window.columnconfigure(1, weight=1)
        window.columnconfigure(2, weight=1)
        window.columnconfigure(3, weight=1)
        window.columnconfigure(4, weight=1)
        window.columnconfigure(5, weight=1)
        window.columnconfigure(6, weight=1)
        window.columnconfigure(7, weight=1)

        # Set title for effects panel
        lazy_tune_label = tk.Label(window, text="Effects Mix", font=("Courier", 30, "bold"))
        lazy_tune_label.grid(row=0, column=0, columnspan=8, sticky="ew")  # Span 8 columns for centering
        lazy_tune_label.configure(background="orange")

        # #  vertical sliders for effects
        effects_sliders = {
            "Delay": ttk.Scale(window, from_=1, to=0, orient="vertical", style="Custom.Vertical.TScale", command=lambda value: on_slider_change("Delay", value, "r")),
            "Flange": ttk.Scale(window, from_=1, to=0, orient="vertical", style="Custom.Vertical.TScale", command=lambda value: on_slider_change("Flange", value, "f")),
            "Freeverb": ttk.Scale(window, from_=1, to=0, orient="vertical", style="Custom.Vertical.TScale", command=lambda value: on_slider_change("Freeverb", value, "e")),
            "Chorus": ttk.Scale(window, from_=1, to=0, orient="vertical", style="Custom.Vertical.TScale", command=lambda value: on_slider_change("Chorus", value, "h")),
            "Bitcrush": ttk.Scale(window, from_=1, to=0, orient="vertical", style="Custom.Vertical.TScale", command=lambda value: on_slider_change("Bitcrush", value, "b")),
            "Overdrive": ttk.Scale(window, from_=1, to=0, orient="vertical", style="Custom.Vertical.TScale", command=lambda value: on_slider_change("Overdrive", value, "t")),
            "Limiter": ttk.Scale(window, from_=1, to=0, orient="vertical", style="Custom.Vertical.TScale", command=lambda value: on_slider_change("Limiter", value, "l")),
            "Multiplier": ttk.Scale(window, from_=1, to=0, orient="vertical", style="Custom.Vertical.TScale", command=lambda value: on_slider_change("Multiplier", value, "u"))
        }
        
        # Initialize slider values from stored memory
        for label in effects_sliders:
            effects_sliders[label].set(effects_values[label])

        # Place Sliders in Grid
        effects_sliders["Delay"].grid(row=2, column=0, columnspan=1, sticky="ns", padx=5, pady=25)
        effects_sliders["Flange"].grid(row=2, column=1, columnspan=1, sticky="ns", padx=5, pady=25)
        effects_sliders["Freeverb"].grid(row=2, column=2, columnspan=1, sticky="ns", padx=5, pady=25)
        effects_sliders["Chorus"].grid(row=2, column=3, columnspan=1, sticky="ns", padx=5, pady=25)
        effects_sliders["Bitcrush"].grid(row=2, column=4, columnspan=1, sticky="ns", padx=5, pady=25)
        effects_sliders["Overdrive"].grid(row=2, column=5, columnspan=1, sticky="ns", padx=5, pady=25)
        effects_sliders["Limiter"].grid(row=2, column=6, columnspan=1, sticky="ns", padx=5, pady=25)
        effects_sliders["Multiplier"].grid(row=2, column=7, columnspan=1, sticky="ns", padx=5, pady=25)

        # Effects Labels
        effects_labels = {
            "Delay": ttk.Label(window, textvariable=dynamic_labels["Delay"], font=("Courier", 12, "bold")),
            "Flange": ttk.Label(window, textvariable=dynamic_labels["Flange"], font=("Courier", 12, "bold")),
            "Freeverb": ttk.Label(window, textvariable=dynamic_labels["Freeverb"], font=("Courier", 12, "bold")),
            "Chorus": ttk.Label(window, textvariable=dynamic_labels["Chorus"], font=("Courier", 12, "bold")),
            "Bitcrush": ttk.Label(window, textvariable=dynamic_labels["Bitcrush"], font=("Courier", 12, "bold")),
            "Overdrive": ttk.Label(window, textvariable=dynamic_labels["Overdrive"], font=("Courier", 12, "bold")),
            "Limiter": ttk.Label(window, textvariable=dynamic_labels["Limiter"], font=("Courier", 12, "bold")),
            "Multiplier": ttk.Label(window, textvariable=dynamic_labels["Multiplier"], font=("Courier", 12, "bold"))
        }

        # Place effects Labels
        effects_labels["Delay"].grid(row=3, column=0, columnspan=1, sticky="ew", padx=0, pady=10)
        effects_labels["Flange"].grid(row=3, column=1, columnspan=1, sticky="ew", padx=0, pady=10)
        effects_labels["Freeverb"].grid(row=3, column=2, columnspan=1, sticky="ew", padx=0, pady=10)
        effects_labels["Chorus"].grid(row=3, column=3, columnspan=1, sticky="ew", padx=0, pady=10)
        effects_labels["Bitcrush"].grid(row=3, column=4, columnspan=1, sticky="ew", padx=0, pady=10)
        effects_labels["Overdrive"].grid(row=3, column=5, columnspan=1, sticky="ew", padx=0, pady=10)
        effects_labels["Limiter"].grid(row=3, column=6, columnspan=1, sticky="ew", padx=0, pady=10)
        effects_labels["Multiplier"].grid(row=3, column=7, columnspan=1, sticky="ew", padx=0, pady=10)

        # # Button to switch to edit effects tab and main screen
        edit_button = ttk.Button(window, text="Edit", command=show_edit_effects_screen)
        edit_button.grid(row=0, column=6, columnspan=2, sticky="ew", padx=5, pady=10)
        back_button = ttk.Button(window, text="Back", command=show_main_screen)
        back_button.grid(row=0, column=0, columnspan=2, sticky="ew", padx=5, pady=10)

    # Function to switch to the distortion screen
    def show_edit_effects_screen():
        for widget in root.winfo_children():
            widget.destroy()

        # Create background panel
        window = ttk.Frame(root, padding=(10, 10, 10, 10))

        # Configure grid for centering with appropriate weights
        window.grid(column=0, row=0, sticky="nsew")
        window.rowconfigure(0, weight=0)  # Top row for window buttons
        window.rowconfigure(1, weight=1)  # Four rows for effects faders
        window.rowconfigure(2, weight=0)  
        window.rowconfigure(3, weight=1)
        window.rowconfigure(4, weight=0)  
        window.rowconfigure(5, weight=1)  
        window.rowconfigure(6, weight=0)
        window.rowconfigure(7, weight=1)  
        window.rowconfigure(8, weight=0)
        window.columnconfigure(0, weight=1) # Four rows for effects button layout
        window.columnconfigure(1, weight=1)
        window.columnconfigure(2, weight=1)
        window.columnconfigure(3, weight=1)

        # Set title for effects panel
        lazy_tune_label = tk.Label(window, text="Edit Effects", font=("Courier", 30, "bold"))
        lazy_tune_label.grid(row=0, column=0, columnspan=4, sticky="ew")  # Span 4 columns for centering
        lazy_tune_label.configure(background="orange")

        # #  vertical sliders for effects
        effects_sliders = {
            "Delay Time": ttk.Scale(window, from_=0, to=10, orient="horizontal", style="Custom.Horizontal.TScale", command=lambda value: on_slider_change("Delay Time", value, "D")),
            "Flange Offset": ttk.Scale(window, from_=0, to=180, orient="horizontal", style="Custom.Horizontal.TScale", command=lambda value: on_slider_change("Flange Offset", value, "F")),
            "Flange Depth": ttk.Scale(window, from_=-1, to=1, orient="horizontal", style="Custom.Horizontal.TScale", command=lambda value: on_slider_change("Flange Depth", value, "L")),
            "Flange Delay": ttk.Scale(window, from_=0, to=20, orient="horizontal", style="Custom.Horizontal.TScale", command=lambda value: on_slider_change("Flange Delay", value, "Y")),
            "Reverb Size": ttk.Scale(window, from_=0, to=1, orient="horizontal", style="Custom.Horizontal.TScale", command=lambda value: on_slider_change("Reverb Size", value, "R")),
            "Chorus Voices": ttk.Scale(window, from_=0, to=8, orient="horizontal", style="Custom.Horizontal.TScale", command=lambda value: on_slider_change("Chorus Voices", value, "H")),
            "Bitcrush Bitdepth": ttk.Scale(window, from_=1, to=16, orient="horizontal", style="Custom.Horizontal.TScale", command=lambda value: on_slider_change("Bitcrush Bitdepth", value, "B")),
            "Bitcrush Frequency": ttk.Scale(window, from_=44100, to=4000, orient="horizontal", style="Custom.Horizontal.TScale", command=lambda value: on_slider_change("Bitcrush Frequency", value, "M"))
        }

        # Initialize effects values from stored memory
        for label in effects_sliders:
            effects_sliders[label].set(effects_values[label])

        # Place Sliders in Grid
        effects_sliders["Delay Time"].grid(row=1, column=0, columnspan=2, sticky="nsew", padx=5, pady=10)
        effects_sliders["Flange Offset"].grid(row=1, column=2, columnspan=2, sticky="nsew", padx=5, pady=10)
        effects_sliders["Flange Depth"].grid(row=3, column=0, columnspan=2, sticky="nsew", padx=5, pady=10)
        effects_sliders["Flange Delay"].grid(row=3, column=2, columnspan=2, sticky="nsew", padx=5, pady=10)
        effects_sliders["Reverb Size"].grid(row=5, column=0, columnspan=2, sticky="nsew", padx=5, pady=10)
        effects_sliders["Chorus Voices"].grid(row=5, column=2, columnspan=2, sticky="nsew", padx=5, pady=10)
        effects_sliders["Bitcrush Bitdepth"].grid(row=7, column=0, columnspan=2, sticky="nsew", padx=5, pady=10)
        effects_sliders["Bitcrush Frequency"].grid(row=7, column=2, columnspan=2, sticky="nsew", padx=5, pady=10)

        # Effects Labels
        effects_labels = {
            "Delay Time": ttk.Label(window, textvariable=dynamic_labels["Delay Time"], font=("Courier", 16, "bold")),
            "Flange Offset": ttk.Label(window, textvariable=dynamic_labels["Flange Offset"], font=("Courier", 16, "bold")),
            "Flange Depth": ttk.Label(window, textvariable=dynamic_labels["Flange Depth"], font=("Courier", 16, "bold")),
            "Flange Delay": ttk.Label(window, textvariable=dynamic_labels["Flange Delay"], font=("Courier", 16, "bold")),
            "Reverb Size": ttk.Label(window, textvariable=dynamic_labels["Reverb Size"], font=("Courier", 16, "bold")),
            "Chorus Voices": ttk.Label(window, textvariable=dynamic_labels["Chorus Voices"], font=("Courier", 16, "bold")),
            "Bitcrush Bitdepth": ttk.Label(window, textvariable=dynamic_labels["Bitcrush Bitdepth"], font=("Courier", 16, "bold")),
            "Bitcrush Frequency": ttk.Label(window, textvariable=dynamic_labels["Bitcrush Frequency"], font=("Courier", 16, "bold"))
        }

        # Place effects on the grid
        effects_labels["Delay Time"].grid(row=2, column=0, columnspan=1, sticky="ew", padx=0, pady=0)
        effects_labels["Flange Offset"].grid(row=2, column=2, columnspan=1, sticky="ew", padx=0, pady=0)
        effects_labels["Flange Depth"].grid(row=4, column=0, columnspan=1, sticky="ew", padx=0, pady=0)
        effects_labels["Flange Delay"].grid(row=4, column=2, columnspan=1, sticky="ew", padx=0, pady=0)
        effects_labels["Reverb Size"].grid(row=6, column=0, columnspan=1, sticky="ew", padx=0, pady=0)
        effects_labels["Chorus Voices"].grid(row=6, column=2, columnspan=1, sticky="ew", padx=0, pady=0)
        effects_labels["Bitcrush Bitdepth"].grid(row=8, column=0, columnspan=1, sticky="ew", padx=0, pady=0)
        effects_labels["Bitcrush Frequency"].grid(row=8, column=2, columnspan=1, sticky="ew", padx=0, pady=0)

        # # Button to switch to distortion tab
        back_button = ttk.Button(window, text="Mix", command=show_effect_mix_screen)
        back_button.grid(row=0, column=0, columnspan=1, sticky="ew", padx=5, pady=10)

    # Function to show the main screen
    def show_main_screen():
        for widget in root.winfo_children():
            widget.destroy()

        # Create background panel
        window = ttk.Frame(root, padding=(10, 10, 10, 10))

        # Configure grid for centering with appropriate weights
        window.grid(column=0, row=0, sticky="nsew")
        window.rowconfigure(0, weight=0)  # Top row for "Lazy-Tune" and "Edit Effect"
        window.rowconfigure(1, weight=0)
        window.rowconfigure(2, weight=1)
        window.rowconfigure(3, weight=1)
        window.rowconfigure(4, weight=0)
        window.rowconfigure(5, weight=1)
        window.rowconfigure(6, weight=1)
        window.columnconfigure(0, weight=1)
        window.columnconfigure(1, weight=1)
        window.columnconfigure(2, weight=1)
        window.columnconfigure(3, weight=1)

        # Label for "Lazy-Tune"
        lazy_tune_label = tk.Label(window, text="Lazy-Tune", font=("Courier", 30, "bold"))
        lazy_tune_label.grid(row=0, column=0, columnspan=4, sticky="ew")  # Span 4 columns for centering
        lazy_tune_label.configure(background="orange")

        # Labels for Buttons
        sound_label = tk.Label(window, text="Select Sound", font=("Courier", 16, "bold"))
        sound_label.grid(row=1, column=0, columnspan=4, sticky="ew")  # Span 2 columns for centering
        sound_label.configure(background="pink")
        preset_label = tk.Label(window, text="Select Instrument", font=("Courier", 16, "bold"))
        preset_label.grid(row=4, column=0, columnspan=4, sticky="ew")  # Span 2 columns for centering
        preset_label.configure(background="pink")

        # Buttons for main screen
        buttons = {
            "Sine": ttk.Button(window, text="Sine", style="Custom.TButton", command=lambda: send_serial_data("I")),
            "Saw": ttk.Button(window, text="Saw", style="Custom.TButton", command=lambda: send_serial_data("A")),
            "Square": ttk.Button(window, text="Square", style="Custom.TButton", command=lambda: send_serial_data("Q")),
            "Triangle": ttk.Button(window, text="Triangle", style="Custom.TButton", command=lambda: send_serial_data("T")),
            "Vocals": ttk.Button(window, text="Vocals", style="Custom.TButton", command=lambda: vocalsPreset()),
            "Synth": ttk.Button(window, text="Synth", style="Custom.TButton", command=lambda: synthPreset()),
            "Vocoder": ttk.Button(window, text="Vocoder", style="Custom.TButton", command=lambda: vocoderPreset()),
            "Autotune": ttk.Button(window, text="Autotune", style="Custom.TButton", command=lambda: autotunePreset())
        }

        # Place buttons in grid, centered below "Lazy-Tune" label
        buttons["Sine"].grid(row=2, column=0, columnspan=2, sticky="nsew", padx=5, pady=10)
        buttons["Saw"].grid(row=2, column=2, columnspan=2, sticky="nsew", padx=5, pady=10)
        buttons["Square"].grid(row=3, column=0, columnspan=2, sticky="nsew", padx=5, pady=10)
        buttons["Triangle"].grid(row=3, column=2, columnspan=2, sticky="nsew", padx=5, pady=10)
        buttons["Vocals"].grid(row=5, column=0, columnspan=2, sticky="nsew", padx=5, pady=10)
        buttons["Synth"].grid(row=5, column=2, columnspan=2, sticky="nsew", padx=5, pady=10)
        buttons["Vocoder"].grid(row=6, column=0, columnspan=2, sticky="nsew", padx=5, pady=10)
        buttons["Autotune"].grid(row=6, column=2, columnspan=2, sticky="nsew", padx=5, pady=10)

        # Edit effect button in top right corner
        edit_effect_button = ttk.Button(window, text="Effect Mixer", command=show_effect_mix_screen)
        edit_effect_button.grid(row=0, column=3, columnspan=1, sticky="ew", padx=5, pady=10)

    show_main_screen()
    root.mainloop()

main()
