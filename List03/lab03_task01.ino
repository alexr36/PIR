// -----------------------------------------------------------------------------
// Required definitions
// -----------------------------------------------------------------------------
#define LED_RED   6
#define LED_GREEN 5
#define LED_BLUE  3

#define BUTTON_RED   2
#define BUTTON_GREEN 4

#define DEBOUNCE_PERIOD 30ul

// -----------------------------------------------------------------------------
// Global variables
// -----------------------------------------------------------------------------
uint8_t currentColor = 0;     // 0 - red, 1 - green, 2 - blue

// -----------------------------------------------------------------------------
// Pin initialization
// -----------------------------------------------------------------------------
// Initialization of RGB pins
void initRGB() {
  pinMode(LED_RED,   OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE,  OUTPUT);
  turnLEDOff();
}

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

// -----------------------------------------------------------------------------
// Utility functions
// -----------------------------------------------------------------------------
// Maps buttons to their IDs in code
uint8_t getButtonID(uint8_t button) {
  if (button == BUTTON_GREEN) return 0;
  if (button == BUTTON_RED)   return 1;

  return -1;
}

// Custom short delay 
void customDelay(unsigned long delay) {
  unsigned long currentTime = millis();
  while (millis() - currentTime <= delay);
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

  if (millis() - lastChangeTime[index] > DEBOUNCE_PERIOD) {
    if (currentReading != debouncedButtonState[index]) {
      if (debouncedButtonState[index] == LOW && currentReading == HIGH) {
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

// Setting the LED color
void setColor(uint8_t color) {
  digitalWrite(LED_RED,   color == 0 ? HIGH : LOW);
  digitalWrite(LED_GREEN, color == 1 ? HIGH : LOW);
  digitalWrite(LED_BLUE,  color == 2 ? HIGH : LOW);
}

// Setting the next color
void setNextColor() {
  currentColor = (currentColor + 1) % 3;
  setColor(currentColor);
}

// Turns off the LED
void turnLEDOff() {
  digitalWrite(LED_RED,   LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE,  LOW);
}

// Switches the color when a button is released
void handleButtons() {
  if (isButtonPressedRed() || isButtonPressedGreen()) {
    turnLEDOff();
    customDelay(1000);
    setNextColor();
  }
}

// -----------------------------------------------------------------------------
// Setup and main loop
// -----------------------------------------------------------------------------
void setup() {
  initRGB();
  initBuiltinLED();
  initButtons();
}

void loop() {
  handleButtons();
}
