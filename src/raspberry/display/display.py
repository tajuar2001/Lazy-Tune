import tkinter as tk

# Function to create a vertical slider
def create_slider(root, label, from_, to):
    frame = tk.Frame(root)
    frame.pack(side=tk.TOP, padx=10, pady=10)
    tk.Label(frame, text=label).pack()
    slider = tk.Scale(frame, from_=from_, to=to, orient=tk.VERTICAL, resolution=0.01, command=lambda value, l=label: print_slider_value(l, value))
    slider.set(0.5)  # Default value
    slider.pack()
    return slider

# Function to create a toggle button
def create_toggle_button(root, text):
    button = tk.Button(root, text=text, command=lambda: toggle_button(button))
    button.state = False
    button.base_text = text
    button.pack(side=tk.LEFT, padx=10)
    return button

# Function to toggle the button state and print the state
def toggle_button(button):
    button.state = not button.state
    button["text"] = f"{button.base_text} {'ON' if button.state else 'OFF'}"
    print(f"{button.base_text} {'enabled' if button.state else 'disabled'}")

# Function to print the slider value
def print_slider_value(label, value):
    print(f"{label} set to {value}")

# Initialize main window
root = tk.Tk()
root.title("Touch Screen Control Panel")

# Create a frame for sliders and place it at the top
sliders_frame = tk.Frame(root)
sliders_frame.pack(side=tk.TOP)

# Create vertical sliders within the sliders frame
volume_slider = create_slider(sliders_frame, "Volume", 0, 1)
modulation_slider = create_slider(sliders_frame, "Modulation", 0, 1)
dry_signal_slider = create_slider(sliders_frame, "Dry Signal", 0, 1)

# Create a frame for buttons and place it at the bottom
buttons_frame = tk.Frame(root)
buttons_frame.pack(side=tk.BOTTOM)

# Create toggle buttons within the buttons frame
autotune_button = create_toggle_button(buttons_frame, "Autotune")
vocoder_button = create_toggle_button(buttons_frame, "Vocoder")

# Start the GUI
root.mainloop()
