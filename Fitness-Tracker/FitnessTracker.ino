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

// Define variables
int stepCount = 0;  // Variable to store step count
float distanceTraveled = 0;  // Distance in meters
float caloriesBurned = 0;    // Calories

qmi_data_t data;  // Variable to store sensor data

void setup() {
    Serial.begin(9600);     // Start serial communication

    // Initialize the TFT display
    tft.initR(INITR_BLACKTAB);  
    tft.setRotation(1);
    tft.fillScreen(ST7735_BLACK);

    // Set backlight pin as output and turn it on
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);  // Set to HIGH to turn on the backlight

    // Initialize the sensor and other necessary configurations
    qmi8658c.open(&qmi8658_cfg);
}

bool detectStep(const qmi_data_t& data) {
    static float last_accel = 0;
    static unsigned long last_time = 0;
    const unsigned long debounce_time = 200; // Debounce for 200 ms

    float accel_magnitude = sqrt(data.acc_xyz.x * data.acc_xyz.x +
                                 data.acc_xyz.y * data.acc_xyz.y +
                                 data.acc_xyz.z * data.acc_xyz.z);
    float threshold = 1.0; // Adjust based on trial and testing
    
    // Print the acceleration magnitude for debugging
    Serial.print("Accel Magnitude: "); Serial.println(accel_magnitude);

    // Step detection with debouncing
    if (accel_magnitude > threshold && last_accel <= threshold && (millis() - last_time > debounce_time)) {
        last_accel = accel_magnitude;
        last_time = millis();
        return true;  // Step detected
    }
    
    last_accel = accel_magnitude;
    return false;  // No step detected
}


void updateDisplay(const qmi_data_t& data) {

      // Display the title "Fitness Tracker"
    tft.setCursor(10, 10); // Position for the title
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(1); // Optionally, you can increase the text size
    tft.println("Fitness Tracker");

   // Clear the display area before updating
    tft.fillRect(10, 30, 220, 120, ST7735_BLACK); // Adjust width and height to cover new text area
 
    // Display sensor and fitness data
    tft.setCursor(10, 30);
    tft.setTextColor(ST7735_WHITE);
    tft.print("Temp: ");
    tft.print(data.temperature);
    tft.println(" C");

    tft.setCursor(10, 50);
    tft.print("Steps: ");
    tft.println(stepCount);

    tft.setCursor(10, 90);
    tft.print("Distance: ");
    tft.print(distanceTraveled);
    tft.println(" m");

    tft.setCursor(10, 120);
    tft.print("Calories: ");
    tft.print(caloriesBurned);
    tft.println(" kcal");
}

void loop() {
    qmi_data_t data;
    qmi8658c.read(&data);

    if (detectStep(data)) {
        stepCount++;
        distanceTraveled = stepCount * 0.75;  // Assume average step length
        caloriesBurned = stepCount * 0.04;    // Calorie estimate per step
    }

    updateDisplay(data); // Update the display with new data
    delay(500); // Update every 0.5 seconds
}
