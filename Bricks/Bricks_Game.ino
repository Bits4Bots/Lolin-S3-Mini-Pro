#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// Pin definitions for the display
#define TFT_CS     35
#define TFT_RST    34
#define TFT_DC     36
#define TFT_BL     33

// Button definitions
#define BUTTON_LEFT 0
#define BUTTON_RIGHT 47
#define BUTTON_RESET 48

// Buzzer pin
#define BUZZER_PIN 37

// Paddle and ball settings
#define PADDLE_WIDTH 30   // Paddle width
#define PADDLE_HEIGHT 10
#define BALL_SIZE 3       // Ball size
#define BRICK_WIDTH 24    // Brick width
#define BRICK_HEIGHT 10   // Brick height

// Custom color definitions
#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800
#define GREEN   0x07E0
#define BLUE    0x001F
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define ORANGE  0xFC20

// Tetromino colors
uint16_t colors[7] = {
    CYAN,    // I shape
    YELLOW,  // O shape
    BLUE,    // L shape
    MAGENTA, // T shape
    GREEN,   // J shape
    RED,     // Z shape
    ORANGE   // S shape
};

// Game variables
int paddleX;
int ballX, ballY;
int ballVelocityX = 2;
int ballVelocityY = -2;
bool bricks[5][3];  // 5 bricks, 3 rows
uint16_t brickColors[5][3]; // Colors for each brick
int score = 0;
bool soundEnabled = true;  // Sound toggle state

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Function prototypes
void setupBricks();
void drawPaddle();
void drawBall();
void drawBricks();
void updateBall();
bool checkCollision();
void gameOver();
void playSound(int frequency, int duration);
void checkSoundToggle();

void setup() {
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);  // Turn on backlight
    tft.initR(INITR_BLACKTAB);
    tft.setRotation(1);  // Set rotation to fit the screen

    paddleX = (tft.width() - PADDLE_WIDTH) / 2;
    ballX = tft.width() / 2;
    ballY = tft.height() - PADDLE_HEIGHT - BALL_SIZE - 5;

    // Setup buttons
    pinMode(BUTTON_LEFT, INPUT_PULLUP);
    pinMode(BUTTON_RIGHT, INPUT_PULLUP);
    pinMode(BUTTON_RESET, INPUT_PULLUP);
    pinMode(BUZZER_PIN, OUTPUT);

    setupBricks();
    tft.fillScreen(ST7735_BLACK);
}

void loop() {
    // Clear the screen
    tft.fillScreen(ST7735_BLACK);

    // Update and draw elements
    drawBricks();
    drawPaddle();
    drawBall();
    updateBall();
    
    // Check for game over
    if (ballY > tft.height()) {
        gameOver();
    }

    // Check button states for paddle movement
    if (digitalRead(BUTTON_LEFT) == LOW) {
        paddleX -= 5;  // Move left
        if (paddleX < 0) paddleX = 0;  // Prevent going out of bounds
    }
    if (digitalRead(BUTTON_RIGHT) == LOW) {
        paddleX += 5;  // Move right
        if (paddleX > tft.width() - PADDLE_WIDTH) paddleX = tft.width() - PADDLE_WIDTH;  // Prevent going out of bounds
    }

    // Check for sound toggle
    checkSoundToggle();
    
    delay(30);  // Control the speed of the game
}

void setupBricks() {
    for (int i = 0; i < 5; i++) {  // Adjusted for 5 bricks
        for (int j = 0; j < 3; j++) {
            bricks[i][j] = true;  // All bricks are present
            brickColors[i][j] = colors[random(0, 7)]; // Assign a random color to each brick
        }
    }
}

void drawPaddle() {
    tft.fillRect(paddleX, tft.height() - PADDLE_HEIGHT, PADDLE_WIDTH, PADDLE_HEIGHT, ST7735_WHITE);
}

void drawBall() {
    tft.fillCircle(ballX, ballY, BALL_SIZE, ST7735_WHITE);
}

void drawBricks() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            if (bricks[i][j]) {
                int x = i * (BRICK_WIDTH + 2) + 2;  // Adjusted brick position
                int y = j * (BRICK_HEIGHT + 2) + 10;

                // Use the assigned color for each brick
                tft.fillRect(x, y, BRICK_WIDTH, BRICK_HEIGHT, brickColors[i][j]);
            }
        }
    }
}

void updateBall() {
    ballX += ballVelocityX;
    ballY += ballVelocityY;

    // Ball collision with walls
    if (ballX <= BALL_SIZE || ballX >= tft.width() - BALL_SIZE) {
        ballVelocityX = -ballVelocityX;  // Reverse horizontal direction
    }
    if (ballY <= BALL_SIZE) {
        ballVelocityY = -ballVelocityY;  // Reverse vertical direction
    }

    // Check collision with paddle
    if (ballY + BALL_SIZE >= tft.height() - PADDLE_HEIGHT &&
        ballX >= paddleX && ballX <= paddleX + PADDLE_WIDTH) {
        ballVelocityY = -ballVelocityY;  // Reverse vertical direction
        ballY = tft.height() - PADDLE_HEIGHT - BALL_SIZE;  // Prevent ball from getting stuck
    }

    // Check for collisions with bricks
    if (checkCollision()) {
        ballVelocityY = -ballVelocityY;  // Reverse vertical direction
    }
}

bool checkCollision() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            if (bricks[i][j]) {
                int x = i * (BRICK_WIDTH + 2) + 2;  // Adjusted brick position
                int y = j * (BRICK_HEIGHT + 2) + 10;

                // Check collision with bricks
                if (ballX + BALL_SIZE > x && ballX - BALL_SIZE < x + BRICK_WIDTH &&
                    ballY + BALL_SIZE > y && ballY - BALL_SIZE < y + BRICK_HEIGHT) {
                    bricks[i][j] = false;  // Remove the brick
                    score++;

                    // Play sound if enabled
                    if (soundEnabled) {
                        playSound(1000, 200);  // Play a sound at 1000 Hz for 200 ms
                    }

                    // Check if all bricks are gone
                    bool allBricksGone = true;
                    for (int k = 0; k < 5; k++) {
                        for (int l = 0; l < 3; l++) {
                            if (bricks[k][l]) {
                                allBricksGone = false;
                                break;
                            }
                        }
                    }
                    if (allBricksGone) {
                        gameOver(); // End the game if all bricks are gone
                    }
                    return true;  // Collision occurred
                }
            }
        }
    }
    return false;  // No collision
}

void gameOver() {
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(10, 40);
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(1);
    tft.print("Game Over");
    tft.setCursor(10, 70);
    tft.print("Score: ");
    tft.print(score);

    // Play game over sound if enabled
    if (soundEnabled) {
        playSound(500, 1000);  // Play a sound at 500 Hz for 1000 ms
    }

    while (true);  // Halt the game
}

void playSound(int frequency, int duration) {
    tone(BUZZER_PIN, frequency, duration);
    delay(duration);
    noTone(BUZZER_PIN);
}

void checkSoundToggle() {
    static unsigned long buttonPressTime = 0;
    static bool buttonPressed = false;

    // Check if button 48 is pressed
    if (digitalRead(BUTTON_RESET) == LOW) {
        if (!buttonPressed) {
            buttonPressTime = millis();
            buttonPressed = true;  // Set the button as pressed
        }

        // Check if the button has been held for 3 seconds
        if (millis() - buttonPressTime >= 3000) {
            soundEnabled = !soundEnabled;  // Toggle sound
            buttonPressed = false;  // Reset the button state
        }
    } else {
        buttonPressed = false;  // Reset if button is released
    }
}
