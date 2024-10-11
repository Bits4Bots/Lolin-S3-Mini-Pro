# S3 Mini Pro ESP32 - Arduino IDE Setup
This repository provides an introduction to using the S3 Mini Pro ESP32 microcontroller with the Arduino IDE. The S3 Mini Pro is a powerful board that features Wi-Fi, Bluetooth, built-in RGB LEDs, buttons, and advanced peripherals for IoT, gaming, and other embedded applications.

## Table of Contents
- Introduction
- Hardware Requirements
- Software Requirements
- Getting Started
- Pin Configuration
- Example Projects
- Contributing
- License
## Introduction
The S3 Mini Pro ESP32 is a versatile, compact, and powerful microcontroller, ideal for IoT, smart devices, games, and embedded electronics. This guide will help you set up the board with the Arduino IDE to start creating projects.

Key features:

- Dual-core ESP32 S3 microcontroller
- Wi-Fi and Bluetooth connectivity
- Built-in RGB LED and buttons
- 128x128 TFT display support
- High-speed SPI, I2C, UART, and more
- Hardware Requirements To follow along with this guide, you'll need the following hardware:
- S3 Mini Pro ESP32 board USB-C to USB-A cable (for powering and programming the board)
- Optional peripherals (e.g., TFT 
  display, sensors, LEDs, buttons)

## Technical Details
- Based ESP32-S3FH4R2
- 2.4 GHz Wi-Fi
- Bluetooth LE
- 4MB Flash
- 2MB PSRAM
- 0.85” 128x128 LCD TFT display (GC9107/GC9A01)
- 6D MEMS IMU (QMI8658C)
- 12x IO
- 3x Button (IO0, IO47, IO48)
- 1x RGB LED (Data: IO8, Power: IO7)
- 1x IR (IO9)
- ADC, DAC, I2C, SPI, UART, USB OTG
- Size:  34.3mm*25.4mm
- Compatible with MicroPython, Arduino
- Default firmware: MicroPython
- Compatible with LOLIN D1 mini shields
More: https://www.wemos.cc/en/latest/s3/s3_mini_pro.html

## Software Requirements
Ensure you have the following software installed:

Arduino IDE Download from Arduino's official website. Follow the instructions to install the IDE on your computer.
ESP32 Board Support In the Arduino IDE, go to File > Preferences. In the "Additional Boards Manager URLs" field, enter: https://dl.espressif.com/dl/package_esp32_index.json Then, go to Tools > Board > Boards Manager and search for "ESP32." Install the latest version.
Required Libraries You may need to install additional libraries to enable certain functionalities (e.g., TFT display support). Libraries can be installed via Sketch > Include Library > Manage Libraries in the Arduino IDE.

## Recommended libraries:
- Adafruit GFX (for graphical displays)
- Adafruit ST7735 and ST7789 (for TFT screens)
- FastLED (for controlling RGB LEDs)

## Getting Started
- Step 1: Connect Your Board Connect the S3 Mini Pro ESP32 to your computer using a USB-C cable. The board should power up, but there will not be any indication of a successful connection.
- Step 2: Select the ESP32 Board (Lolin S3 Mini Pro) In the Arduino IDE, go to Tools > Board > ESP32 Arduino. Select ESP32S3 Dev Module from the list.
- Step 3: Select the COM Port Go to Tools > Port, and select the port corresponding to your connected ESP32 S3 Mini Pro.
- Step 4: Upload a Test Sketch Open the "Blink" example by navigating to File > Examples > 01.Basics > Blink. Modify the LED_BUILTIN pin to match the onboard RGB LED pin (e.g., GPIO37 for red, GPIO47 for blue, GPIO48 for green). Compile and upload the sketch. If successful, the onboard LED will blink.

## Pin Configuration
Here is a basic pinout for the S3 Mini Pro ESP32:
![image](https://github.com/user-attachments/assets/f8c4bb76-5f99-445e-a696-7a6a50aab946)


## Function Pin 
- WS2812B-0807 7 (Power)
- RGB LED - 8  (DI)
- Button 1 (Left) 0 
- Button 2 (Center) 47 
- Button 3 (Right) 48 
- TFT Display CS 35 
- TFT Display RST 34 
- TFT Display DC 36 
- TFT Display BL 33 

You can also refer to the S3 Mini Pro pinout diagram (link to be added if applicable) for further details on GPIO usage.

Example Projects Here are some basic starter projects for the S3 Mini Pro ESP32:

- BlinkRGB Cycle through Red, Green, and Blue colors on the built-in RGB LED.
- Blink (3mm LED) A simple program that blinks an LED.
- Draw a Circle (TFT Display) A basic graphics program that draws a circle on a 128x128 TFT display.
- Falling Pumpkins Game A Halloween-themed game where players catch pumpkins falling down the TFT display using buttons.

## Contributing
If you want to contribute to this repository, feel free to open a pull request or submit issues to improve the documentation and examples.

## License This project is licensed under the MIT License - see the LICENSE file for details.

By following this guide, you should be up and running with the S3 Mini Pro ESP32 in the Arduino IDE and ready to explore the world of IoT, gaming, and other embedded systems projects!
