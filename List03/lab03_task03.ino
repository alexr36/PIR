// -----------------------------------------------------------------------------
// Required includes
// -----------------------------------------------------------------------------
#include <LiquidCrystal_I2C.h>

// -----------------------------------------------------------------------------
// Required definitions
// -----------------------------------------------------------------------------
#define BUTTON_RED   2
#define BUTTON_GREEN 4

#define DEBOUNCE_PERIOD_MS 30ul
#define REFRESH_PERIOD_MS  1000ul

// -----------------------------------------------------------------------------
// Global variables
// -----------------------------------------------------------------------------
bool isTimerRunning          = false;
uint32_t elapsedTime         = 0;
unsigned long lastUpdateTime = 0ul;

// -----------------------------------------------------------------------------
// Initialization
// -----------------------------------------------------------------------------
// Initialization of built-in LED
void initBuiltinLED() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

// Initialization of button pins
void initButtons() {
  pinMode(BUTTON_RED,   INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
}

// Initializing display object
LiquidCrystal_I2C lcdDisplay(0x27, 16, 2);

void initLCD() {
  lcdDisplay.init();
  lcdDisplay.backlight();
}

// -----------------------------------------------------------------------------
// Utility functions
// -----------------------------------------------------------------------------
// Maps buttons to their IDs in code
uint8_t getButtonID(uint8_t button) {
  if (button == BUTTON_GREEN) return 0;
  if (button == BUTTON_RED)   return 1;
  return -1;
}

// Returns given number length (digits count)
uint8_t getNumberLength(uint32_t number) {
  uint8_t length = 0;

  do {
    number /= 10;
    length++;
  }
  while (number);

  return length;
}

// -----------------------------------------------------------------------------
// Handling buttons behavior
// -----------------------------------------------------------------------------
// Debouncing technique for buttons
bool isButtonPressed(uint8_t button) {
  uint8_t index = getButtonID(button);

  if (index == -1) return false;

  static uint8_t debouncedButtonState[2];
  static uint8_t lastReading[2];
  static unsigned long lastChangeTime[2];
  bool isPressed = false;
  uint8_t currentReading = digitalRead(button);

  if (lastReading[index] != currentReading) lastChangeTime[index] = millis();

  if (millis() - lastChangeTime[index] > DEBOUNCE_PERIOD_MS) {
    if (currentReading != debouncedButtonState[index]) {
      if (debouncedButtonState[index] == HIGH && currentReading == LOW) {
        isPressed = true;
      }

      debouncedButtonState[index] = currentReading;
    }
  }

  lastReading[index] = currentReading;

  return isPressed;  
}

// Checks if red button is pressed
bool isButtonPressedRed() {
  return isButtonPressed(BUTTON_RED);
}

// Checks if green button is pressed
bool isButtonPressedGreen() {
  return isButtonPressed(BUTTON_GREEN);
}

// -----------------------------------------------------------------------------
// Handling display behavior
// -----------------------------------------------------------------------------
// Displaying measured time unit and what is being measured
void displayInfo() {
  lcdDisplay.clear();
  lcdDisplay.print("Time: ");
  lcdDisplay.setCursor(15, 0);
  lcdDisplay.print('s');
  displayElapsedTime();
}

// Displays given time
void displayTime(uint32_t timeSeconds) {
  lcdDisplay.setCursor(15 - getNumberLength(timeSeconds), 0);
  lcdDisplay.print(timeSeconds);
}

// -----------------------------------------------------------------------------
// Handling timer behavior
// -----------------------------------------------------------------------------
void updateTime() {
  unsigned long currentTime = millis();

  if (isTimerRunning) {
    if (currentTime - lastUpdateTime >= REFRESH_PERIOD_MS) {
      elapsedTime++;
      lastUpdateTime = currentTime;
      displayElapsedTime();
    }
  }
}

// Stops or resumes the timer
void toggleTimer() {
  if (isButtonPressedGreen()) {
    if (!isTimerRunning) lastUpdateTime = millis();
    isTimerRunning = !isTimerRunning; 
  }
}

// Stops and resets the timer
void resetTimer() {
  if (isButtonPressedRed() && isTimerRunning) {
    isTimerRunning = !isTimerRunning;
    elapsedTime = 0;
    displayInfo();
  }
}

// Displays elapsed time
void displayElapsedTime() {
  displayTime(elapsedTime);
}

// -----------------------------------------------------------------------------
// Setup and main loop
// -----------------------------------------------------------------------------
void setup() {
  initBuiltinLED();
  initButtons();
  initLCD();
  displayInfo();
}

void loop() {
  toggleTimer();
  resetTimer();
  updateTime();
}