import tkinter as tk

def main():
    window = tk.Tk()
    window.title("Dynamic Buttons")

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

        # Manually assign custom messages to each main button
        tk.Button(window, text="Button 1", command=lambda: [show_options(1), print_message("Main Button 1 clicked")]).grid(row=0, column=0, sticky="nsew", padx=20, pady=20)
        tk.Button(window, text="Button 2", command=lambda: [show_options(2), print_message("Main Button 2 clicked")]).grid(row=0, column=1, sticky="nsew", padx=20, pady=20)
        tk.Button(window, text="Button 3", command=lambda: [show_options(3), print_message("Main Button 3 clicked")]).grid(row=0, column=2, sticky="nsew", padx=20, pady=20)
        tk.Button(window, text="Button 4", command=lambda: [show_options(4), print_message("Main Button 4 clicked")]).grid(row=1, column=0, sticky="nsew", padx=20, pady=20)
        tk.Button(window, text="Button 5", command=lambda: [show_options(5), print_message("Main Button 5 clicked")]).grid(row=1, column=1, sticky="nsew", padx=20, pady=20)
        tk.Button(window, text="Button 6", command=lambda: [show_options(6), print_message("Main Button 6 clicked")]).grid(row=1, column=2, sticky="nsew", padx=20, pady=20)

    show_main_buttons()
    window.mainloop()

main()
