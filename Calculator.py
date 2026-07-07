import sys
from PyQt5.QtWidgets import (
    QApplication,
    QWidget,
    QPushButton,
    QLineEdit,
    QGridLayout,
    QVBoxLayout
)
from PyQt5.QtGui import QFont


class Calculator(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("PETER's Calculator")
        self.setGeometry(300, 200, 350, 450)

        self.create_ui()

    def create_ui(self):
        # Display
        self.display = QLineEdit()
        self.display.setFont(QFont("Arial", 20))
        self.display.setReadOnly(True)

        # Main Layout
        main_layout = QVBoxLayout()

        # Grid Layout
        grid = QGridLayout()

        buttons = [
            ("7", 0, 0), ("8", 0, 1), ("9", 0, 2), ("/", 0, 3),
            ("4", 1, 0), ("5", 1, 1), ("6", 1, 2), ("*", 1, 3),
            ("1", 2, 0), ("2", 2, 1), ("3", 2, 2), ("-", 2, 3),
            ("0", 3, 0), (".", 3, 1), ("=", 3, 2), ("+", 3, 3)
        ]

        for text, row, column in buttons:
            button = QPushButton(text)
            button.setFont(QFont("Arial", 16))
            button.setMaximumHeight(60)

            if text == "=":
                button.clicked.connect(self.calculate)
            else:
                button.clicked.connect(self.button_clicked)

            grid.addWidget(button, row, column)

        # Clear Button
        clear_button = QPushButton("Clear")
        clear_button.setFont(QFont("Arial", 16))
        clear_button.setMaximumHeight(60)
        clear_button.clicked.connect(self.clear_display)

        # Add widgets to layout
        main_layout.addWidget(self.display)
        main_layout.addLayout(grid)
        main_layout.addWidget(clear_button)

        self.setLayout(main_layout)

    def button_clicked(self):
        button = self.sender()
        current = self.display.text()
        self.display.setText(current + button.text())

    def calculate(self):
        try:
            expression = self.display.text()
            result = eval(expression)
            self.display.setText(str(result))
        except Exception:
            self.display.setText("Error")

    def clear_display(self):
        self.display.clear()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = Calculator()
    window.show()
    sys.exit(app.exec_())