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

#define COLOR_STEP 1

#define DELAY_TIME_MS 25

// -----------------------------------------------------------------------------
// Pin initialization
// -----------------------------------------------------------------------------
// Initialization of RGB pins
void initRGB() {
  pinMode(LED_RED, OUTPUT);
  analogWrite(LED_RED, 0);

  pinMode(LED_GREEN, OUTPUT);
  analogWrite(LED_GREEN, 0);

  pinMode(LED_BLUE, OUTPUT);
  analogWrite(LED_BLUE, 0);
}

// Initialization of button pins
void initButtons() {
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
}

// -----------------------------------------------------------------------------
// Handling buttons and diode behavior
// -----------------------------------------------------------------------------
// Perform fade from one given color to another
void fadeBetweenColors(uint8_t color_from, uint8_t color_to) {
  for (int i = 0; i <= BRIGHTNESS_LEVEL_MAX; i += COLOR_STEP) {
    analogWrite(color_from, max(BRIGHTNESS_LEVEL_MAX - i, BRIGHTNESS_LEVEL_MIN);
    analogWrite(color_to, min(i, BRIGHTNESS_LEVEL_MAX));
    delay(DELAY_TIME_MS);
  }

  analogWrite(color_from, BRIGHTNESS_LEVEL_MIN);
  analogWrite(color_to, BRIGHTNESS_LEVEL_MAX);
}

// Perform fade through all colors
void fadeAnimate() {
  fadeBetweenColors(LED_RED, LED_GREEN);
  fadeBetweenColors(LED_GREEN, LED_BLUE);
  fadeBetweenColors(LED_BLUE, LED_RED);
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
  fadeAnimate();
}
