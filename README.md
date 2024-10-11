# Lolin-S3-Mini-Pro
Falling Pumpkins Game 🎃
A simple, fun Halloween-themed game for the S3 Mini Pro ESP32 microcontroller! Catch the falling pumpkins by pressing the correct button before they hit the ground. This project is a great way for electronics enthusiasts to get hands-on experience with the ESP32 S3 Mini Pro, TFT display, and button inputs. Perfect for beginners and advanced users alike!

## Table of Contents
Introduction
### Hardware Requirements
- ESP32 microcontroller
- ST7789 display (128x128 resolution)
- RGB LED
- Three buttons for controlling the game
- Wiring and connectors as needed
### Software Requirements
Features
Installation
### Game Rules

Introduction
In this project, you'll create a Falling Pumpkins game using the S3 Mini Pro ESP32 and a 128x128 pixel TFT display. Pumpkins will fall down the screen, and your task is to catch them by pressing the correct button. If you miss, it's game over!

This project introduces the following concepts:

- Handling TFT displays using SPI communication
- Button input for real-time interaction
- Basic game mechanics (score tracking, game over condition)
- Hardware Requirements
- To build this project, you'll need the following hardware components:

### ESP32 S3 Mini Pro:

Microcontroller (S3 Mini Pro) that supports Wi-Fi and Bluetooth and provides built-in RGB LEDs and buttons.
TFT 0.85" Display (128x128):

SPI-based display to show the falling pumpkins and game interface.
Three Push Buttons:

Used to control the player’s actions (left, center, and right buttons).
Connect these buttons to the following GPIO pins:
Button 1 (Left): IO0
Button 2 (Center): IO47
Button 3 (Right): IO48
Breadboard and Wires:

For connecting the buttons and display to the ESP32 board.
Optional: USB Power Supply:

To power the ESP32 board.
Software Requirements
Make sure you have the following software installed:

### Arduino IDE:

Download from Arduino Official Website
Install ESP32 board support using the following instructions:
In the Arduino IDE, go to File > Preferences.
Add this URL in "Additional Boards Manager URLs": https://dl.espressif.com/dl/package_esp32_index.json.
Go to Tools > Board > Boards Manager, search for "ESP32," and install the latest version.
Adafruit GFX and ST7735 Libraries:

Install these libraries via the Library Manager in Arduino IDE:
Go to Sketch > Include Library > Manage Libraries.
Search for "Adafruit GFX" and "Adafruit ST7735" and install them.
Pumpkin Bitmap Image:

If you wish to display a bitmap pumpkin, use an online image-to-byte-array converter to generate the byte array for the image.
Example converter: LCD Assistant.
### Features
Falling Pumpkin Animation: Pumpkins drop from the top of the screen, and the player must catch them.
Button Controls: Use three buttons to catch the pumpkins in the correct columns.
Game Over Condition: The game ends when a pumpkin isn't caught in time.
Score Display: The final score is displayed on the screen when the game ends.
Pre-game Image: A large pumpkin image is displayed after the title screen to enhance the Halloween theme.
### Installation
Step 1: Hardware Setup
TFT Display Connection:
TFT_CS: Pin 35
TFT_RST: Pin 34
TFT_DC: Pin 36
TFT_BL: Pin 33 (optional for backlight control)
Button Connections:
Button 1 (Left) -> Pin IO0
Button 2 (Center) -> Pin IO47
Button 3 (Right) -> Pin IO48
### Power Supply:
Connect the ESP32 to a USB power supply or computer for programming and running the game.
Step 2: Software Setup
Clone this repository or download the ZIP file.
Open the FallingPumpkins.ino file in Arduino IDE.
Upload the sketch to your ESP32 S3 Mini Pro.
### Game Rules
Objective: Catch the falling pumpkins using the buttons.
### Gameplay:
Pumpkins fall down from one of the three columns.
Press the corresponding button (left, center, or right) to catch the pumpkin.
Each successful catch increases your score.
### Game Over: The game ends if you miss catching a pumpkin.
Pre-game Pumpkin Image: After the title screen, a large pumpkin image is displayed to set the Halloween mood.

Feel free to contribute, suggest features, or ask questions! 🎮 Happy coding and Happy Halloween! 🎃

This README provides an overview of the game, lists the hardware and software requirements, and gives instructions on how to set everything up, making it easier for electronics enthusiasts to replicate and enjoy the project!
