import tkinter as tk

class InteractiveBoard(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Interactive Board")

        # Configure the grid layout
        self.buttons = {}  # Keep a reference to the buttons
        for row in range(2):
            for column in range(10):
                button = tk.Button(self, text=f"Button {row},{column}",
                                   command=lambda r=row, c=column: self.button_pressed(r, c))
                button.grid(row=row, column=column, sticky="nsew")
                self.buttons[(row, column)] = button

        # Make the grid cells expand equally
        for row in range(2):
            self.grid_rowconfigure(row, weight=1)
        for column in range(10):
            self.grid_columnconfigure(column, weight=1)

    def button_pressed(self, row, column):
        # This function is called whenever a button is pressed
        print(f"Button at row {row}, column {column} was pressed.")
        # You can also change the button text, color, etc.
        self.buttons[(row, column)].config(text="Pressed", bg="green")

if __name__ == "__main__":
    app = InteractiveBoard()
    app.mainloop()
