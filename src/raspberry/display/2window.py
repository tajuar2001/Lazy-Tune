import tkinter as tk

def main():
    window = tk.Tk()
    window.title("Dynamic Buttons")
    window.geometry("600x400")  # Set window size

    # Function to print a custom message
    def print_message(message):
        print(message)

    # Configure grid for spacing and resizing
    def configure_grid():
        for i in range(3):  # Adjust to a 3x3 grid
            window.rowconfigure(i, weight=1)
            window.columnconfigure(i, weight=1)

    # Function to show option buttons
    def show_options(button_number):
        for widget in window.winfo_children():
            widget.destroy()
        configure_grid()

        # Place option buttons
        tk.Button(window, text="Option 1", command=lambda: print_message(f"Button {button_number} - Option 1")).grid(row=1, column=0, sticky="nsew")
        tk.Button(window, text="Option 2", command=lambda: print_message(f"Button {button_number} - Option 2")).grid(row=1, column=1, sticky="nsew")
        tk.Button(window, text="Option 3", command=lambda: print_message(f"Button {button_number} - Option 3")).grid(row=1, column=2, sticky="nsew")
        tk.Button(window, text="Option 4", command=lambda: print_message(f"Button {button_number} - Option 4")).grid(row=2, column=1, sticky="nsew")

        # Back button
        tk.Button(window, text="Back", command=show_main_buttons).grid(row=2, column=2, sticky="nsew")

    # Function to show main buttons
    def show_main_buttons():
        for widget in window.winfo_children():
            widget.destroy()
        configure_grid()

        # Place main buttons
        tk.Button(window, text="Button 1", command=lambda: [show_options(1), print_message("Main Button 1 clicked")]).grid(row=1, column=0, sticky="nsew")
        tk.Button(window, text="Button 2", command=lambda: [show_options(2), print_message("Main Button 2 clicked")]).grid(row=1, column=1, sticky="nsew")
        tk.Button(window, text="Button 3", command=lambda: [show_options(3), print_message("Main Button 3 clicked")]).grid(row=1, column=2, sticky="nsew")
        tk.Button(window, text="Button 4", command=lambda: [show_options(4), print_message("Main Button 4 clicked")]).grid(row=2, column=1, sticky="nsew")

    show_main_buttons()
    window.mainloop()

main()
