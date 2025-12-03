int potPin = A0;

int led1Pin = 9;
int led2Pin = 10;

int button1Pin = 2;
int button2Pin = 3;

enum Mode { NORMAL, FLICKER, STROBE_HOLD };
Mode currentMode = NORMAL;

unsigned long modeStartTime = 0;
unsigned long lastToggle = 0;
bool ledState = false;

bool lastB1 = HIGH;
bool lastB2 = HIGH;

void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
}

void loop() {
  readButtons();

  int potValue = analogRead(potPin);
  int brightness = map(potValue, 0, 1023, 0, 255);

  switch (currentMode) {
    case NORMAL:
      analogWrite(led1Pin, brightness);
      analogWrite(led2Pin, brightness);
      break;

    case FLICKER:
      runBlinkMode(60, brightness, false);
      break;

    case STROBE_HOLD:
      runBlinkMode(100, brightness, true);
      break;
  }
}

void readButtons() {
  bool b1 = digitalRead(button1Pin);
  bool b2 = digitalRead(button2Pin);

  if (lastB1 == HIGH && b1 == LOW) {
    currentMode = FLICKER;
    modeStartTime = millis();
    lastToggle = millis();
    ledState = false;
  }
  lastB1 = b1;

  if (lastB2 == HIGH && b2 == LOW) {
    currentMode = STROBE_HOLD;
    modeStartTime = millis();
    lastToggle = millis();
    ledState = false;
  }
  lastB2 = b2;
}

void runBlinkMode(int interval, int brightness, bool holdAfter) {
  unsigned long now = millis();
  unsigned long elapsed = now - modeStartTime;

  // Blink for 3 seconds
  if (elapsed < 3000) {
    if (now - lastToggle > interval) {
      lastToggle = now;
      ledState = !ledState;

      analogWrite(led1Pin, ledState ? brightness : 0);
      analogWrite(led2Pin, ledState ? brightness : 0);
    }
    return;
  }

  // After 3 seconds:
  if (holdAfter) {
    // Strobe/Hold: LED1 off, LED2 held at brightness
    analogWrite(led1Pin, 0);
    analogWrite(led2Pin, brightness);
  } else {
    // Flicker ends → return to normal
    currentMode = NORMAL;
  }
}
