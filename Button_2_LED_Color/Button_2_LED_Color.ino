//Bits4Bots - Larsha Johnson
//October 30th 2024
// I do not know why the NeoPixel RGB is not aligning with the RGB (0,0,0) but the code works as is.

#include <Adafruit_GFX.h>     
#include <Adafruit_ST7735.h>  
#include <Adafruit_NeoPixel.h> 

// Define pin connections for TFT
#define TFT_CS   35  
#define TFT_RST  34  
#define TFT_DC   36  
#define TFT_BL   33  

// Define the RGB LED pin and power
#define RGB_BUILTIN 8   // Power RGB_BUILTIN to use IO8
#define RGB_POWER 7     
#define RGB_BRIGHTNESS 64 

// Define button pins
#define BUTTON_BLUE 0
#define BUTTON_RED 47
#define BUTTON_GREEN 48

// TFT display setup
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  // Initialize serial monitor
  Serial.begin(9600);

  // Set up button pins
  pinMode(BUTTON_BLUE, INPUT_PULLUP);
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);

  // Power the RGB LED
  pinMode(RGB_POWER, OUTPUT);
  digitalWrite(RGB_POWER, HIGH); // Power on the RGB LED

  // Initialize TFT display
  tft.initR(INITR_144GREENTAB);  
  tft.setRotation(1);  
  tft.fillScreen(ST77XX_BLACK);

  // Turn on the TFT backlight
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  // Display static text on the TFT screen
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println("B-States:");
  tft.setTextSize(1);
  tft.setCursor(10, 40);
  tft.println("No Button Pressed");
}

void loop() {
  // Check if the Blue button is pressed
  if (digitalRead(BUTTON_BLUE) == LOW) {
      neopixelWrite(RGB_BUILTIN, 0, 0, RGB_BRIGHTNESS); // Set RGB LED to Green
    displayButtonState("Blue Button Pressed");
  }
  // Check if the Red button is pressed
  else if (digitalRead(BUTTON_RED) == LOW) {
    neopixelWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS, 0); // Set RGB LED to Red
    displayButtonState("Red Button Pressed");
  }
  // Check if the Green button is pressed
  else if (digitalRead(BUTTON_GREEN) == LOW) {
    neopixelWrite(RGB_BUILTIN, RGB_BRIGHTNESS, 0, 0); // Set RGB LED to Blue
    displayButtonState("Green Button Pressed");
  } else {
    // If no button is pressed, turn off RGB LED and display default message
    neopixelWrite(RGB_BUILTIN, 0, 0, 0); // Turn off RGB LED
    displayButtonState("No Button Pressed");
  }

  delay(100); // Short delay to debounce button presses
}

// Function to update button state on TFT screen without changing color
void displayButtonState(const char* buttonText) {
  tft.fillRect(10, 40, 108, 16, ST77XX_BLACK); // Clear previous button state text
  tft.setCursor(10, 40);
  tft.println(buttonText);
}
