// -----------------------------------------------------------------------------
// Required definitions
// -----------------------------------------------------------------------------
#define LED_RED   6
#define LED_GREEN 5
#define LED_BLUE  3

#define BUTTON_RED   2
#define BUTTON_GREEN 4

// -----------------------------------------------------------------------------
// Global variables
// -----------------------------------------------------------------------------
uint8_t currentColor = 0;     // 0 - red, 1 - green, 2 - blue
bool    ledIsEnabled = false; // LED diode ON/OFF state

bool buttonRedLastState   = HIGH;
bool buttonGreenLastState = HIGH;

// -----------------------------------------------------------------------------
// Pin initialization
// -----------------------------------------------------------------------------
// Initialization of RGB pins
void initRGB() {
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, LOW);

  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_GREEN, LOW);

  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_BLUE, LOW);
}

// Initialization of button pins
void initButtons() {
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
}

// -----------------------------------------------------------------------------
// Handling pins and diode behavior
// -----------------------------------------------------------------------------
// Setting color of the LED diode
void setColor(uint8_t color) {
  digitalWrite(LED_RED,   color == 0 ? HIGH : LOW);
  digitalWrite(LED_GREEN, color == 1 ? HIGH : LOW);
  digitalWrite(LED_BLUE,  color == 2 ? HIGH : LOW);
}

// Handling the LED state
void handleButtonRed() {
  bool buttonRedCurrentState = digitalRead(BUTTON_RED);
  if (buttonRedCurrentState == LOW && buttonRedLastState == HIGH) {
    ledIsEnabled = !ledIsEnabled;
    delay(100);
  }
  buttonRedLastState = buttonRedCurrentState;
}

// Handling setting the LED color
void handleButtonGreen() {
  bool buttonGreenCurrentState = digitalRead(BUTTON_GREEN);
  if (buttonGreenCurrentState == LOW && buttonGreenLastState == HIGH) {
    currentColor = (currentColor + 1) % 3;
    delay(100);
  }
  buttonGreenLastState = buttonGreenCurrentState;
}

// Complete diode behavior management
void handleDiode() {
  handleButtonRed();
  handleButtonGreen();

  if (ledIsEnabled) setColor(currentColor);
  else              setColor(255);
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
  handleDiode();
}
