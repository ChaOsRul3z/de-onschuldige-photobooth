int potPin = A0;
int led1Pin = 9;
int led2Pin = 10;

int button1Pin = 2;  // Flicker Mode
int button2Pin = 3;  // Strobe + Shock effect  
int button3Pin = 4;  // On/Off toggle

bool lightsOn = true;
bool button3LastState = HIGH;
unsigned long flickerStart = 0;
unsigned long strobeStart = 0;
bool inFlicker = false;
bool inStrobe = false;
bool strobeHoldActive = false;

void setup() {
  Serial.begin(9600);
  
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);
}

void loop() {
  handleOnOffButton();
  
  if (!lightsOn) {
    analogWrite(led1Pin, 0);
    analogWrite(led2Pin, 0);
    return;
  }

  int b1 = digitalRead(button1Pin);
  int b2 = digitalRead(button2Pin);

  // Button 1: Start flicker mode
  if (b1 == LOW && !inFlicker && !inStrobe) {
    startFlicker();
  }

  // Button 2: Start strobe mode  
  if (b2 == LOW && !inFlicker && !inStrobe) {
    startStrobe();
  }

  updateEffects();
  updateNormalBrightness();
}

void handleOnOffButton() {
  bool button3State = digitalRead(button3Pin);
  
  if (button3LastState == HIGH && button3State == LOW) {
    lightsOn = !lightsOn;
    inFlicker = false;
    inStrobe = false;
    strobeHoldActive = false;
  }


  if ( = digitalRead())
  
  button3LastState = button3State;
}

void startFlicker() {
  inFlicker = true;
  flickerStart = millis();
}

void startStrobe() {
  inStrobe = true;
  strobeStart = millis();
  strobeHoldActive = false;
}

void updateEffects() {
  unsigned long currentTime = millis();
  
  if (inFlicker) {
    if (currentTime - flickerStart < 3000) {
      bool flickerState = (currentTime / 100) % 2;
      digitalWrite(led1Pin, flickerState ? HIGH : LOW);
      digitalWrite(led2Pin, flickerState ? HIGH : LOW);
    } else {
      inFlicker = false;
    }
  }
  
  if (inStrobe) {
    if (currentTime - strobeStart < 3000) {
      bool strobeState = (currentTime / 25) % 2;
      digitalWrite(led1Pin, strobeState ? HIGH : LOW);
      digitalWrite(led2Pin, strobeState ? HIGH : LOW);
    } else {
      strobeHoldActive = true;
      inStrobe = false;
      analogWrite(led1Pin, 0);
    }
  }
}

void updateNormalBrightness() {
  if (!inFlicker && !inStrobe) {
    int potValue = analogRead(potPin);
    int brightness = map(potValue, 0, 1023, 0, 255);
    
    if (!strobeHoldActive) {
      analogWrite(led1Pin, brightness);
    }
    analogWrite(led2Pin, brightness);
  }
}