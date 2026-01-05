// --- FINAL AI LIFT CODE (Motor + 7-Segment Display) ---

const long BAUD_RATE = 9600;

// Variables for state tracking
char incomingCommand = ' ';
String currentLiftState = "STOPPED";
int currentFloor = 1; // Start at Floor 1

// --- PHYSICAL OUTPUT PINS ---
const int MOTOR_UP_PIN = 9;   // L293D Input 1
const int MOTOR_DOWN_PIN = 10; // L293D Input 2

// 7-Segment Pins (Common Anode)
const int segmentPins[] = {2, 3, 4, 5, 6, 7, 8}; 

// Patterns for 1, 2, 3 (Common Anode: 0 is ON, 1 is OFF)
const byte floorPatterns[4][7] = {
    {1, 1, 1, 1, 1, 1, 1}, // 0: Off
    {1, 0, 0, 1, 1, 1, 1}, // 1: Floor 1
    {0, 0, 1, 0, 0, 1, 0}, // 2: Floor 2
    {0, 0, 0, 0, 1, 1, 0}  // 3: Floor 3
};

void setup() {
  Serial.begin(BAUD_RATE);
  while (!Serial);

  // Initialize Motor Pins
  pinMode(MOTOR_UP_PIN, OUTPUT);
  pinMode(MOTOR_DOWN_PIN, OUTPUT);

  // Initialize 7-Segment Pins
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  // Initial Status
  displayFloor(currentFloor);
  Serial.println("ARDUINO READY");
  Serial.print("Initial Floor: ");
  Serial.println(currentFloor);
}

void loop() {
  if (Serial.available() > 0) {
    incomingCommand = Serial.read();

    switch (incomingCommand) {
      case 'U': 
        if (currentFloor < 3) handleUpCommand();
        else Serial.println("ALREADY AT TOP");
        break;

      case 'D': 
        if (currentFloor > 1) handleDownCommand();
        else Serial.println("ALREADY AT BOTTOM");
        break;

      case 'S': 
        handleStopCommand();
        break;
    }
  }
}

// --- COMMAND HANDLER FUNCTIONS ---

void handleUpCommand() {
  digitalWrite(MOTOR_DOWN_PIN, LOW);
  delay(100); 
  digitalWrite(MOTOR_UP_PIN, HIGH);
  
  Serial.println("LIFT ACTION: Moving Up...");
  delay(2000); // Simulate travel time
  
  stopMotors();
  currentFloor++;
  displayFloor(currentFloor);
  
  Serial.print("Arrived at Floor: ");
  Serial.println(currentFloor);
}

void handleDownCommand() {
  digitalWrite(MOTOR_UP_PIN, LOW);
  delay(100); 
  digitalWrite(MOTOR_DOWN_PIN, HIGH);
  
  Serial.println("LIFT ACTION: Moving Down...");
  delay(2000); // Simulate travel time
  
  stopMotors();
  currentFloor--;
  displayFloor(currentFloor);
  
  Serial.print("Arrived at Floor: ");
  Serial.println(currentFloor);
}

void handleStopCommand() {
  stopMotors();
  Serial.println("LIFT ACTION: EMERGENCY STOP");
}

void stopMotors() {
  digitalWrite(MOTOR_UP_PIN, LOW);
  digitalWrite(MOTOR_DOWN_PIN, LOW);
}

void displayFloor(int floorNum) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], floorPatterns[floorNum][i]);
  }
}