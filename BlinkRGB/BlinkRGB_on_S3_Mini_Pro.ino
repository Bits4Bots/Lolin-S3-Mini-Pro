/*
 Modified by: Bits4Bots LLC - Larsha Johnson
 BlinkRGB
 Demonstrates usage of onboard RGB LED on the S3 Mini Pro ESP dev boards.

 Calling digitalWrite(RGB_BUILTIN, HIGH) will use hidden RGB driver.
 RGBLedWrite demonstrates control of each channel:
 void neopixelWrite(uint8_t pin, uint8_t red_val, uint8_t green_val, uint8_t blue_val)
 WARNING: After using digitalWrite to drive RGB LED it will be impossible to drive the same pin
  with normal HIGH/LOW level
*/

//#define RGB_BRIGHTNESS 64 // Change white brightness (max 255)
// the setup function runs once when you press reset or power the board

void setup() {
 // No need to initialize the RGB LED
  pinMode(7, OUTPUT); //Provide power to the WS2812B-0807 IC (RGB LED)
}

// the loop function runs over and over again forever
void loop() {
 digitalWrite(7, HIGH); //Send power to the WS2812B-0807 IC
#ifdef RGB_BUILTIN
 //digitalWrite(RGB_BUILTIN, HIGH); // Turn the RGB LED white
 //delay(1000);
 //digitalWrite(RGB_BUILTIN, LOW); // Turn the RGB LED off
 // delay(1000);

 neopixelWrite(RGB_BUILTIN, RGB_BRIGHTNESS, 0, 0); // Red
 delay(1000);
 neopixelWrite(RGB_BUILTIN, 0, 0, RGB_BRIGHTNESS); // Green - normally (0, 255, 0) is displayed as green but there internal wiring is flipped
 delay(1000);
 neopixelWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS, 0); // Blue - normally (0, 0, 255) is displayed as blue but there internal wiring is flipped
 delay(1000);

 //neopixelWrite(RGB_BUILTIN, 0, 0, 0); // Off / black
 //delay(1000);
#endif
}
