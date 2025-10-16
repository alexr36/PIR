// -----------------------------------------------------------------------------
// Required definitions
// -----------------------------------------------------------------------------
#define LED_RED   6
#define LED_GREEN 5
#define LED_BLUE  3

#define INTERVAL_RED   900ul
#define INTERVAL_GREEN 1000ul
#define INTERVAL_BLUE  1100ul

// -----------------------------------------------------------------------------
// Global variables
// -----------------------------------------------------------------------------
unsigned long lastChangeRed   = 0ul;
unsigned long lastChangeGreen = 0ul;
unsigned long lastChangeBlue  = 0ul;

bool ledStateRed   = LOW;
bool ledStateGreen = LOW;
bool ledStateBlue  = LOW;

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

// -----------------------------------------------------------------------------
// Handling diode behavior
// -----------------------------------------------------------------------------
// Hanlding the individual color blinking
void blinkColor(uint8_t color, unsigned long interval, unsigned long &lastChange, bool &ledState) {
  unsigned long currentTime = millis();

  if (currentTime - lastChange > interval) {
    ledState = !ledState;
    digitalWrite(color, ledState);
    lastChange = currentTime;
  }
}

// Handling the diode blinking
void blinkDiode() {
  blinkColor(LED_RED,   INTERVAL_RED,   lastChangeRed,   ledStateRed);
  blinkColor(LED_GREEN, INTERVAL_GREEN, lastChangeGreen, ledStateGreen);
  blinkColor(LED_BLUE,  INTERVAL_BLUE,  lastChangeBlue,  ledStateBlue);
}

// Turns off the LED
void turnLEDOff() {
  digitalWrite(LED_RED,   LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE,  LOW);
}

// -----------------------------------------------------------------------------
// Setup and main loop
// -----------------------------------------------------------------------------
void setup() {
  initRGB();
  initBuiltinLED();
}

void loop() {
  blinkDiode();
}