int potPin = A0;     // Potentiometer pin

int led1Pin = 9;     // LED Strip 1 (Kan veranderen indien ze te dichtbij elkaar staan)
int led2Pin = 10;    // LED Strip 2 (Kan ook veranderen zorg gewoon dat de pin in code ook verandert als het het geval is)

int button1Pin = 2;  // Button 1 voor Flicker Mode
int button2Pin = 3;  // Button 2 voor Strobe + Shock effect

int trigPin = 11;
int echoPin = 12;

void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
}

void loop() {

  int b1 = digitalRead(button1Pin);
  int b2 = digitalRead(button2Pin);

  // Button 1 met een flicker voor een paar seconden
  if (b1 == LOW) {
    flickerMode();
  }

  // Button 2 zorgt voor strobe en shock effect met alleen maar 1 LED strip dat aan blijft 
  //voor dit code zijn er 2 LED strips maar het principe blijft hetzelfde met oneindigveel LEDs
  if (b2 == LOW) {
    strobeThenHold();
  }

  int potValue = analogRead(potPin);               
  int brightness = map(potValue, 0, 1023, 0, 255); 

  // Beide strips voor hetzelfde brightness knob
  analogWrite(led1Pin, brightness);
  analogWrite(led2Pin, brightness);
}


void flickerMode() {
  unsigned long startTime = millis();

  while (millis() - startTime < 3000) {
    digitalWrite(led1Pin, HIGH);
    digitalWrite(led2Pin, HIGH);
    delay(100);

    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, LOW);
    delay(100);
  }
}


void strobeThenHold() {
  // Strobe effect voor 2 seconden
  unsigned long startTime = millis();

  while (millis() - startTime < 3000) {
    digitalWrite(led1Pin, HIGH);
    digitalWrite(led2Pin, HIGH);
    delay(25);

    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, LOW);
    delay(25);
  }

  // Lichten flickeren -> LED Strip 1 gaat uit
  analogWrite(led1Pin, 0);

  // LED strip 2 blijft aan met haar ingestelde brightness
  int potValue = analogRead(A0);
  int brightness = map(potValue, 0, 1023, 0, 255);
  analogWrite(led2Pin, brightness);
}
