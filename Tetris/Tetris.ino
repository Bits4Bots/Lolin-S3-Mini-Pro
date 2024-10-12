#include <TFT_eSPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#define TFT_CS     35
#define TFT_RST    34
#define TFT_DC     36
#define TFT_BL     33

// Define button pins
#define BUTTON_LEFT   0   // IO0 for the left button
#define BUTTON_CENTER 47   // IO47 for the center button (rotate)
#define BUTTON_RIGHT  48   // IO48 for the right button (drop)

// Define display size
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 128

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

const int blockSize = 8;         // Size of each block
const int boardWidth = SCREEN_WIDTH / blockSize;
const int boardHeight = SCREEN_HEIGHT / blockSize;

int board[boardWidth][boardHeight] = {0}; // Game board
int currentTetromino[4][2]; // Current tetromino position
int currentX, currentY; // Current position of tetromino

// Tetromino shapes (2D array representation)
const int shapes[7][4][2] = {
    {{0, 1}, {1, 1}, {2, 1}, {1, 0}}, // T shape
    {{0, 0}, {1, 0}, {1, 1}, {2, 1}}, // Z shape
    {{0, 1}, {1, 1}, {1, 0}, {2, 0}}, // S shape
    {{0, 0}, {0, 1}, {0, 2}, {0, 3}}, // I shape
    {{0, 1}, {1, 1}, {2, 1}, {2, 0}}, // L shape
    {{0, 0}, {0, 1}, {1, 1}, {1, 0}}, // O shape
    {{0, 0}, {0, 1}, {0, 2}, {1, 2}}  // J shape
};

void setup() {
    pinMode(7, OUTPUT); //Provide power to the WS2812B-0807 IC (RGB LED)
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST7735_BLACK);
    pinMode(BUTTON_LEFT, INPUT_PULLUP);
    pinMode(BUTTON_CENTER, INPUT_PULLUP); // Rotate
    pinMode(BUTTON_RIGHT, INPUT_PULLUP); // Drop
    randomSeed(analogRead(0)); // Seed random for tetromino generation
    spawnTetromino();
}

void loop() {
    digitalWrite(7, HIGH); //Send power to the WS2812B-0807 IC
//#ifdef RGB_BUILTIN
    digitalWrite(RGB_BUILTIN, HIGH);  // Turn the RGB LED white
    delay(1000);
    digitalWrite(RGB_BUILTIN, LOW);  // Turn the RGB LED off
    delay(1000);

    // Read button states
    if (digitalRead(BUTTON_LEFT) == LOW) {
        moveTetromino(-1, 0); // Move left
        delay(200); // Debounce delay
    }
    if (digitalRead(BUTTON_CENTER) == LOW) {
        rotateTetromino(); // Rotate tetromino
        delay(200); // Debounce delay
    }
    if (digitalRead(BUTTON_RIGHT) == LOW) {
        dropTetromino(); // Drop tetromino to the bottom
        delay(200); // Debounce delay
    }
    
    if (!moveTetromino(0, 1)) { // Move down
        fixTetromino(); // Fix tetromino in place
        clearLines(); // Check and clear lines
        spawnTetromino(); // Spawn new tetromino
    }

    drawBoard();
    delay(200); // Adjust speed of the game
}

void spawnTetromino() {
    currentX = boardWidth / 2 - 1; // Start in the middle
    currentY = 0; // Start at the top
    int shapeIndex = random(0, 7);
    for (int i = 0; i < 4; i++) {
        currentTetromino[i][0] = shapes[shapeIndex][i][0];
        currentTetromino[i][1] = shapes[shapeIndex][i][1];
    }
}

bool moveTetromino(int dx, int dy) {
    // Check if the move is valid
    for (int i = 0; i < 4; i++) {
        int x = currentX + currentTetromino[i][0] + dx;
        int y = currentY + currentTetromino[i][1] + dy;

        if (x < 0 || x >= boardWidth || y >= boardHeight || (y >= 0 && board[x][y])) {
            return false; // Invalid move
        }
    }
    
    currentX += dx;
    currentY += dy;
    return true; // Valid move
}

void rotateTetromino() {
    // Rotate the tetromino clockwise
    int tempTetromino[4][2];
    for (int i = 0; i < 4; i++) {
        tempTetromino[i][0] = currentTetromino[i][1];
        tempTetromino[i][1] = -currentTetromino[i][0];
    }
    
    // Check if the rotated tetromino is valid
    for (int i = 0; i < 4; i++) {
        int x = currentX + tempTetromino[i][0];
        int y = currentY + tempTetromino[i][1];

        if (x < 0 || x >= boardWidth || y >= boardHeight || (y >= 0 && board[x][y])) {
            return; // Invalid rotation
        }
    }

    // Apply the rotation
    for (int i = 0; i < 4; i++) {
        currentTetromino[i][0] = tempTetromino[i][0];
        currentTetromino[i][1] = tempTetromino[i][1];
    }
}

void dropTetromino() {
    while (moveTetromino(0, 1)); // Drop until it can't move down anymore
}

void fixTetromino() {
    for (int i = 0; i < 4; i++) {
        int x = currentX + currentTetromino[i][0];
        int y = currentY + currentTetromino[i][1];
        if (y >= 0) {
            board[x][y] = 1; // Mark block on the board
        }
    }
}

void clearLines() {
    for (int y = 0; y < boardHeight; y++) {
        bool complete = true;
        for (int x = 0; x < boardWidth; x++) {
            if (!board[x][y]) {
                complete = false;
                break;
            }
        }

        if (complete) {
            // Clear the line
            for (int x = 0; x < boardWidth; x++) {
                board[x][y] = 0; // Remove the block
            }

            // Move lines down
            for (int y2 = y; y2 > 0; y2--) {
                for (int x = 0; x < boardWidth; x++) {
                    board[x][y2] = board[x][y2 - 1];
                }
            }
        }
    }
}

void drawBoard() {
    tft.fillScreen(ST7735_BLACK);
    for (int y = 0; y < boardHeight; y++) {
        for (int x = 0; x < boardWidth; x++) {
            if (board[x][y]) {
                tft.fillRect(x * blockSize, y * blockSize, blockSize, blockSize, ST7735_WHITE);
            }
        }
    }

    // Draw current tetromino
    for (int i = 0; i < 4; i++) {
        int x = currentX + currentTetromino[i][0];
        int y = currentY + currentTetromino[i][1];
        if (y >= 0) {
            tft.fillRect(x * blockSize, y * blockSize, blockSize, blockSize, ST7735_RED);
        }
    }
}

