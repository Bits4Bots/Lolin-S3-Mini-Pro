/*Bits4Bots - By Larsha Johnson
Date 11/1/2024
Add ESP32 to the Qmi8658c library.properties file... example architectures=avr, esp32, ESP32  
Modified Qmi8658c.h please check GitHub*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <Qmi8658c.h>
#include <Arduino.h>

#define QMI_ADDRESS 0x6B  // Define the QMI8658C I2C address
#define QMI8658C_I2C_FREQUENCY 80000  // Define the I2C frequency

// TFT screen pin definitions
#define TFT_CS   35
#define TFT_RST  34
#define TFT_DC   36
#define TFT_BL   33

// Create TFT display object
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Declare an instance of Qmi8658c
Qmi8658c qmi8658c(QMI_ADDRESS, QMI8658C_I2C_FREQUENCY);

qmi8658_cfg_t qmi8658_cfg = {
    .qmi8658_mode = qmi8658_mode_dual,
    .acc_scale = acc_scale_2g,
    .acc_odr = acc_odr_8000,
    .gyro_scale = gyro_scale_16dps,
    .gyro_odr = gyro_odr_8000,
};

void setup() {
    Serial.begin(9600);
    qmi8658_result_t result = qmi8658c.open(&qmi8658_cfg); // Initialize the sensor
    delay(1000); // Delay for sensor initialization

    // Initialize TFT display
    tft.initB();  // Use initB for ST7735
    tft.setRotation(3); // Adjust rotation as needed Options 0, 1, 2, or 3
    tft.fillScreen(ST7735_BLACK);

    // Turn on backlight
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH); // Turn on backlight

    // Display initialization result
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(1); // Set text size
    tft.setCursor(10, 10);
    tft.print("Init: ");
    tft.println(result == qmi8658_result_open_success ? "Success" : "Failed");

    // Check for initialization error
    if (result != qmi8658_result_open_success) {
        tft.setCursor(10, 40);
        tft.setTextColor(ST7735_RED);
        tft.println("Init Error!");
        while (1); // Halt execution
    }

    // Read and display the device ID
    tft.setTextColor(ST7735_WHITE);
    tft.setCursor(10, 40);
    tft.print("Device ID: 0x");
    tft.println(qmi8658c.deviceID, HEX);
}

void updateDisplay(const qmi_data_t& data) {
    // Clear the display for new data
    tft.fillRect(10, 70, 220, 150, ST7735_BLACK); // Clear previous data area

    // Display temperature data first
    tft.setCursor(10, 70);
    tft.setTextColor(ST7735_WHITE);
    tft.print("Temp: "); 
    tft.print(data.temperature);
    tft.println(" C"); // Assuming the unit is Celsius

    // Display accelerometer data in (x, y) format
    tft.setCursor(10, 100);
    tft.print("Acc: (");
    tft.print(data.acc_xyz.x);
    tft.print(", ");
    tft.print(data.acc_xyz.y);
    tft.print(")");

    // Display gyroscope data in (x, y) format
    tft.setCursor(10, 120);
    tft.print("Gyro: (");
    tft.print(data.gyro_xyz.x);
    tft.print(", ");
    tft.print(data.gyro_xyz.y);
    tft.print(")");
}

void loop() {
    qmi_data_t data;
    qmi8658c.read(&data);
    updateDisplay(data); // Update the display with new data
    delay(1000); // Update every second
}
