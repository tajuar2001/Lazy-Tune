import tkinter as tk
import serial

# Setup the serial connection (adjust 'COM3' and 9600 to your settings)


def main():
    window = tk.Tk()
    window.title("Dynamic Buttons with Serial Communication")

    # Function to send a message over serial
    def send_serial_message(message):
        ser.write(message.encode())

    # Function to print a custom message
    def print_message(message):
        print(message)

    def show_options(button_number):
        # Clear window
        for widget in window.winfo_children():
            widget.destroy()

        # Manually assign custom messages to each option button
        tk.Button(window, text="Option 1", command=lambda: print_message(f"Button {button_number} - Option 1")).grid(row=0, column=0, sticky="nsew", padx=10, pady=10)
        tk.Button(window, text="Option 2", command=lambda: print_message(f"Button {button_number} - Option 2")).grid(row=0, column=1, sticky="nsew", padx=10, pady=10)
        tk.Button(window, text="Option 3", command=lambda: print_message(f"Button {button_number} - Option 3")).grid(row=1, column=0, sticky="nsew", padx=10, pady=10)
        tk.Button(window, text="Option 4", command=lambda: print_message(f"Button {button_number} - Option 4")).grid(row=1, column=1, sticky="nsew", padx=10, pady=10)

        # Back button
        tk.Button(window, text="Back", command=show_main_buttons).grid(row=2, column=0, columnspan=2, sticky="nsew", padx=10, pady=10)

    def show_main_buttons():
        # Clear window
        for widget in window.winfo_children():
            widget.destroy()

        # Manually assign custom messages and serial signals to each main button
        tk.Button(window, text="Button 1", command=lambda: [show_options(1), send_serial_message("Main Button 1 Signal")]).grid(row=0, column=0, sticky="nsew", padx=20, pady=20)
        tk.Button(window, text="Button 2", command=lambda: [show_options(2), send_serial_message("Main Button 2 Signal")]).grid(row=0, column=1, sticky="nsew", padx=20, pady=20)
        tk.Button(window, text="Button 3", command=lambda: [show_options(3), send_serial_message("Main Button 3 Signal")]).grid(row=0, column=2, sticky="nsew", padx=20, pady=20)
        tk.Button(window, text="Button 4", command=lambda: [show_options(4), send_serial_message("Main Button 4 Signal")]).grid(row=1, column=0, sticky="nsew", padx=20, pady=20)
        tk.Button(window, text="Button 5", command=lambda: [show_options(5), send_serial_message("Main Button 5 Signal")]).grid(row=1, column=1, sticky="nsew", padx=20, pady=20)
        tk.Button(window, text="Button 6", command=lambda: [show_options(6), send_serial_message("Main Button 6 Signal")]).grid(row=1, column=2, sticky="nsew", padx=20, pady=20)

    show_main_buttons()
    window.mainloop()

main()
