// Define Pins
const int irSensorPin = 2; 
const int buzzerPin = 3;

void setup() {
  pinMode(irSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600); // For testing on your computer
}

void loop() {
  int sensorValue = digitalRead(irSensorPin);

  // IR Sensors usually output LOW (0) when an object is detected
  if (sensorValue == LOW) {
    digitalWrite(buzzerPin, HIGH); // Beep ON
    delay(100);                    // Short beep duration
    digitalWrite(buzzerPin, LOW);  // Beep OFF
    delay(100);
  } else {
    digitalWrite(buzzerPin, LOW);  // Silence when path is clear
  }
}