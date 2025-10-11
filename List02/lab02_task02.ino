// -----------------------------------------------------------------------------
// Required definitions
// -----------------------------------------------------------------------------
#define LED_RED   6
#define LED_GREEN 5
#define LED_BLUE  3

#define BUTTON_RED   2
#define BUTTON_GREEN 4

#define BRIGHTNESS_LEVEL_MAX 255
#define BRIGHTNESS_LEVEL_MIN 0
#define BRIGHTNESS_STEP      5

// -----------------------------------------------------------------------------
// Global variables
// -----------------------------------------------------------------------------
uint16_t brightnessLevel = 127;   // 0 - OFF, 255 - full brightness

// -----------------------------------------------------------------------------
// Pin initialization
// -----------------------------------------------------------------------------
// Initialization of RGB pins
void initRGB() {
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, LOW);

  pinMode(LED_GREEN, OUTPUT);
  analogWrite(LED_GREEN, brightnessLevel);

  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_BLUE, LOW);
}

// Initialization of button pins
void initButtons() {
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
}

// -----------------------------------------------------------------------------
// Handling buttons and diode behavior
// -----------------------------------------------------------------------------
// Turning the brightness level down
void handleButtonRed() {
  if (digitalRead(BUTTON_RED) == LOW && brightnessLevel > BRIGHTNESS_LEVEL_MIN) {
    brightnessLevel = max(brightnessLevel - BRIGHTNESS_STEP, BRIGHTNESS_LEVEL_MIN);
    setDiodeBrightness();
  }
}

// Turning the brightness level up
void handleButtonGreen() {
  if (digitalRead(BUTTON_GREEN) == LOW && brightnessLevel < BRIGHTNESS_LEVEL_MAX) {
    brightnessLevel = min(brightnessLevel + BRIGHTNESS_STEP, BRIGHTNESS_LEVEL_MAX);
    setDiodeBrightness();
  }
}

// Setting the LED diode brightness level
void setDiodeBrightness() {
  analogWrite(LED_GREEN, brightnessLevel);
}

void handleBrightness() {
  handleButtonRed();
  handleButtonGreen();
}

// -----------------------------------------------------------------------------
// Setup and main loop
// -----------------------------------------------------------------------------
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  initRGB();
  initButtons();
}


void loop() {
  handleBrightness();
}
