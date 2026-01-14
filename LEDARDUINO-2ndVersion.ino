const int relayPin = 2;  // Pin connected to relay control
unsigned long previousMillis = 0;
const unsigned long interval = 3000;  // 3 seconds
bool ledState = false;

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Start with relay off
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledState = !ledState;  // Toggle state
    
    digitalWrite(relayPin, ledState ? HIGH : LOW);
  }
}