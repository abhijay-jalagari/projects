// Define the baud rate to match the Web Serial code (9600)
const long BAUD_RATE = 9600;

// Variables for state tracking
char incomingCommand = ' ';
String currentLiftState = "STOPPED at Ground";

// --- PHYSICAL OUTPUT PINS ---
// You will connect these pins to your motor driver or relays.
const int MOTOR_UP_PIN = 9;   // Represents the motor moving UP or an indicator LED
const int MOTOR_DOWN_PIN = 10; // Represents the motor moving DOWN or an indicator LED

void setup() {
  // Start serial communication
  Serial.begin(BAUD_RATE);
  // Wait for the serial port to connect. Needed for Leonardo/Micro and web serial.
  while (!Serial);

  // Initialize the output pins
  pinMode(MOTOR_UP_PIN, OUTPUT);
  pinMode(MOTOR_DOWN_PIN, OUTPUT);

  // Initial status messages sent back to the web console
  Serial.println("ARDUINO READY");
  Serial.print("Initial State: ");
  Serial.println(currentLiftState);
}

void loop() {
  // --- 1. Check for incoming commands from the Web Serial API ---
  if (Serial.available() > 0) {
    // Read the incoming byte (command character)
    incomingCommand = Serial.read();

    // --- 2. Process the command ---
    switch (incomingCommand) {
      case 'U': // Command to move Up (from Thumbs Up gesture)
        handleUpCommand();
        break;

      case 'D': // Command to move Down (from Thumbs Down gesture)
        handleDownCommand();
        break;

      case 'S': // Command to Stop (from Stop Hand gesture)
        handleStopCommand();
        break;

      default:
        // Handle unexpected commands (optional)
        Serial.print("ERROR: Unknown command received: ");
        Serial.println(incomingCommand);
        break;
    }
  }

  // --- 3. (Optional) Your continuous logic goes here (e.g., checking limit switches) ---
}

// --- COMMAND HANDLER FUNCTIONS ---

void handleUpCommand() {
  // 1. Ensure the opposing motor is off for safety
  digitalWrite(MOTOR_DOWN_PIN, LOW);
  delay(100); 

  // 2. Start the motor UP
  digitalWrite(MOTOR_UP_PIN, HIGH);
  currentLiftState = "MOVING UP";

  // 3. Send feedback to the web console
  Serial.print("LIFT ACTION: Moving Up (Code: U). Current State: ");
  Serial.println(currentLiftState);
}

void handleDownCommand() {
  // 1. Ensure the opposing motor is off for safety
  digitalWrite(MOTOR_UP_PIN, LOW);
  delay(100); 

  // 2. Start the motor DOWN
  digitalWrite(MOTOR_DOWN_PIN, HIGH);
  currentLiftState = "MOVING DOWN";

  // 3. Send feedback to the web console
  Serial.print("LIFT ACTION: Moving Down (Code: D). Current State: ");
  Serial.println(currentLiftState);
}

void handleStopCommand() {
  // 1. Stop both motor indicators/relays
  digitalWrite(MOTOR_UP_PIN, LOW);
  digitalWrite(MOTOR_DOWN_PIN, LOW);
  currentLiftState = "STOPPED";

  // 2. Send feedback to the web console
  Serial.print("LIFT ACTION: STOPPING (Code: S). Current State: ");
  Serial.println(currentLiftState);
}