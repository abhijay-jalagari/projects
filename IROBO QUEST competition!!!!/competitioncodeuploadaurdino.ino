// --- Pin Definitions ---
const int SoundSensorPin = 2; // Digital Input (D0 pin on the sensor)
const int LEDPin = 3;         // Digital Output for the LED
const int BuzzerPin = 4;      // Digital Output for the Buzzer

// --- State Variables ---
int triggerCounter = 0;       // Tracks the number of sound detections
const long waitTime = 500;    // Debounce time in milliseconds

void setup() {
  // Initialize the pins
  pinMode(SoundSensorPin, INPUT);
  pinMode(LEDPin, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);

  // Ensure outputs are off initially
  digitalWrite(LEDPin, LOW);
  digitalWrite(BuzzerPin, LOW);
  
  // Start Serial communication for debugging (optional but recommended)
  Serial.begin(9600);
  Serial.println("Decibel Alert System Initialized.");
  Serial.println("Adjust sound sensor sensitivity until it triggers at 60dB.");
}

void loop() {
  // Read the digital state of the sound sensor.
  // A LOW reading typically indicates sound detected (sensor triggered).
  int sensorValue = digitalRead(SoundSensorPin);

  if (sensorValue == LOW) {
    // Sound detected (60dB or above)
    triggerCounter++;
    Serial.print("Trigger Detected! Count: ");
    Serial.println(triggerCounter);

    // --- Action Logic based on Trigger Count ---
    
    if (triggerCounter == 1) {
      // 1st Trigger: LED for 10 seconds
      Serial.println("Action: LED ON (10s)");
      digitalWrite(LEDPin, HIGH);
      delay(10000); // 10 seconds
      digitalWrite(LEDPin, LOW);
      
    } else if (triggerCounter == 2) {
      // 2nd Trigger: Buzzer for 10 seconds
      Serial.println("Action: Buzzer ON (10s)");
      digitalWrite(BuzzerPin, HIGH);
      delay(10000); // 10 seconds
      digitalWrite(BuzzerPin, LOW);
      
    } else if (triggerCounter == 3) {
      // 3rd Trigger: LED and Buzzer for 20 seconds
      Serial.println("Action: LED & Buzzer ON (20s) - Reset imminent.");
      digitalWrite(LEDPin, HIGH);
      digitalWrite(BuzzerPin, HIGH);
      delay(20000); // 20 seconds
      digitalWrite(LEDPin, LOW);
      digitalWrite(BuzzerPin, LOW);
      
      // Reset the counter
      triggerCounter = 0;
      Serial.println("Cycle Complete. System Reset.");
    }

    // Debounce: Wait briefly after the action to avoid counting the same noise multiple times
    delay(waitTime);
  }
}