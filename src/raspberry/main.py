import os
import mido
import threading
import tkinter as tk
from tkinter import Scale

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
        window.rowconfigure(0, weight=0)  # Top row where "Lazy-Tune" and "Edit Effect" will be
        window.rowconfigure(1, weight=1)
        window.rowconfigure(2, weight=1)
        window.columnconfigure(0, weight=1)
        window.columnconfigure(1, weight=1)
        window.columnconfigure(2, weight=1)
        window.columnconfigure(3, weight=1)  # Column for "Edit Effect" button, minimal weight

        # Label for "Lazy-Tune"
        lazy_tune_label = tk.Label(window, text="Lazy-Tune", font=("Helvetica", 30))
        lazy_tune_label.grid(row=0, column=0, columnspan=4, sticky="ew")  # Span 4 columns for centering
        
        # Determine button size
        button_width = 16
        button_height = 6

        # Place main buttons in grid, centered below "Lazy-Tune" label
        tk.Button(window, text="Microphone", width=button_width, height=button_height, command=lambda: print("Microphone button clicked")).grid(row=1, column=1, sticky="nsew", padx=10, pady=10)
        tk.Button(window, text="Carrier", width=button_width, height=button_height, command=lambda: print("Carrier button clicked")).grid(row=1, column=2, sticky="nsew", padx=10, pady=10)
        tk.Button(window, text="Autotune", width=button_width, height=button_height, command=lambda: print("Autotune button clicked")).grid(row=2, column=1, sticky="nsew", padx=10, pady=10)
        tk.Button(window, text="Vocoder", width=button_width, height=button_height, command=lambda: print("Vocoder button clicked")).grid(row=2, column=2, sticky="nsew", padx=10, pady=10)

        # Edit effect button in top right corner
        edit_effect_button = tk.Button(window, text="Edit Effect", font=("Helvetica", 14), width=20, height=2, command=lambda: print("Edit Effect button clicked"))
        edit_effect_button.grid(row=0, column=2, sticky="ne", padx=0, pady=10)
    
    show_main_screen()
    window.mainloop()

main()
