/* * 3-Stage Sound Detector (RGB Common Anode Version)
 * Green -> Yellow -> Red/Ambulance
 */

// --- Pin Definitions ---
const int sensorPin = A0;
const int redPin = 9;    // RGB Red leg
const int greenPin = 10; // RGB Green leg
const int bluePin = 11;  // RGB Blue leg
const int buzzerPin = 5;

// --- Settings ---
const int soundThreshold = 550; // Adjust this sensitivity!
const int debounceDelay = 200;  

int stageCounter = 0;
unsigned long lastSoundTime = 0; 

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Start with Reset (All OFF)
  resetSystem();
  
  Serial.begin(9600);
}

void loop() {
  int soundLevel = analogRead(sensorPin);

  // Check for sound
  if (soundLevel > soundThreshold && (millis() - lastSoundTime > debounceDelay)) {
    stageCounter++; 
    lastSoundTime = millis();
    activateStage(stageCounter);
  }
}

void activateStage(int stage) {
  switch (stage) {
    case 1:
      // --- STAGE 1: Green + 1s Beep ---
      setColor(0, 255, 0); // Green ON
      tone(buzzerPin, 1000); 
      delay(1000);           
      noTone(buzzerPin);
      break;

    case 2:
      // --- STAGE 2: Yellow + 2s Beep ---
      // Yellow = Red ON + Green ON
      setColor(255, 255, 0); 
      tone(buzzerPin, 1000);
      delay(2000);          
      noTone(buzzerPin);
      break;

    case 3:
      // --- STAGE 3: Red + Ambulance Siren ---
      setColor(255, 0, 0); // Red ON
      playAmbulanceSound();
      
      // --- RESET ---
      delay(1000); 
      resetSystem();
      break;
  }
}

// Helper function to handle Common Anode Logic
// 0 = OFF, 255 = Max Brightness
void setColor(int redValue, int greenValue, int blueValue) {
  // Since it's Common Anode, we INVERT the values
  // 255 - value means: If we want 255 (max), we write 0 (LOW).
  analogWrite(redPin, 255 - redValue);
  analogWrite(greenPin, 255 - greenValue);
  analogWrite(bluePin, 255 - blueValue);
}

void playAmbulanceSound() {
  for(int i = 0; i < 3; i++){
    tone(buzzerPin, 600);
    delay(500);
    tone(buzzerPin, 900);
    delay(500);
  }
  noTone(buzzerPin);
}

void resetSystem() {
  setColor(0, 0, 0); // Turn RGB LED OFF
  noTone(buzzerPin);
  stageCounter = 0;
}