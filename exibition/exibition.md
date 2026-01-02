AI Lift Controller Project: Complete Guide
This document contains all the necessary components, instructions, and code files for building and running the AI-controlled lift prototype, which uses hand gestures (detected by Teachable Machine) to send commands via Web Serial to an Arduino.
1. Materials List
Component
Purpose
Notes
Arduino Uno/Nano
Microcontroller
Runs the lift control logic.
DC Motor
Lift Actuator
Simulates the lift mechanism.
L293D Motor Driver
Motor Control
Safely drives the DC motor with higher current.
7-Segment Display
Floor Indicator
Displays the current floor number (1, 2, or 3). (Common Anode)
220 Ohm Resistors (x8)
Current Limiting
7 for the display segments, 1 for the Common Anode pin.
Breadboard
Circuit Assembly
Used for connecting components.
Jumper Wires
Connections
For connecting the Arduino to the breadboard and components.
External Power Supply
Motor Power
9V battery or wall adapter for the L293D/Motor.
USB Cable
Communication/Power
Connects the Arduino to the computer.
Computer/Laptop
AI Interface
Runs the Teachable Machine model and Web Serial interface.

2. Project Logic Flow
The system operates in three functional layers:
AI Layer (Web Browser): A webcam captures the user's hand gesture. The Teachable Machine model (integrated into the HTML) classifies the gesture as "Thumbs Up" (U), "Thumbs Down" (D), or "Stop Hand" (S) with high confidence.
Communication Layer (Web Serial): The HTML/JavaScript uses the Web Serial API to establish a connection to the Arduino's serial port and transmits the corresponding command character ('U', 'D', or 'S').
Embedded Layer (Arduino): The Arduino receives the character via the serial port, executes the corresponding motor and display functions, tracks the current floor, and sends feedback back to the web interface.
3. Hardware Connection Guide
⚠️ CRITICAL STEP: You MUST connect the ground (GND) of the Arduino to the ground (GND) of the external motor power supply. This ensures signal consistency across the entire circuit.
3.1. L293D Motor Driver and DC Motor Connections
The L293D acts as an H-Bridge, controlling the direction and speed of the motor. It receives control signals from the Arduino's digital pins 9 and 10.
L293D Pin
Connection
Arduino Pin / Power Source
Purpose
Pin 1, 9, 16
Power
Arduino 5V
Enable/Logic Power (L293D is ON)
Pin 2 (Input 1)
Digital
Arduino Pin 9
Motor Direction Control 1 (UP)
Pin 7 (Input 2)
Digital
Arduino Pin 10
Motor Direction Control 2 (DOWN)
Pin 8 (VCC1)
Power
External Power (9V/12V)
Motor Power Supply
Pin 4, 5, 12, 13
Ground
Arduino GND AND External Power GND
Common Ground Connections
Pin 3 & 6
Motor
DC Motor Terminals
Motor Output

3.2. 7-Segment Display Connections (Common Anode)
The 7-segment display shows the current floor number (1, 2, 3). Since we are using a Common Anode display, the common pin connects to VCC (5V), and individual segments turn ON when the connected digital pin is set to LOW (GND).
Segment
Function
Connection
Arduino Pin
Common (Anode)
VCC
5V via a 220 Ohm Resistor
Arduino 5V
Segment A
Top
Digital
Arduino Pin 2
Segment B
Top Right
Digital
Arduino Pin 3
Segment C
Bottom Right
Digital
Arduino Pin 4
Segment D
Bottom
Digital
Arduino Pin 5
Segment E
Bottom Left
Digital
Arduino Pin 6
Segment F
Top Left
Digital
Arduino Pin 7
Segment G
Middle
Digital
Arduino Pin 8

4. Arduino Code (lift_control_arduino.ino)
Upload this code to your Arduino board. It initializes the pins, manages the motor state, and controls the 7-segment display based on the serial input.

// --- Arduino Code for AI-Controlled Lift Prototype ---e

// L293D Motor Control Pins
const int motorPin1 = 9;  // Input 1 of L293D (Controls one direction - wired to Pin 2)
const int motorPin2 = 10; // Input 2 of L293D (Controls other direction - wired to Pin 7)

// 7-Segment Display Pins (Common Anode Configuration)
// Connected to segments A, B, C, D, E, F, G
const int segmentPins[] = {2, 3, 4, 5, 6, 7, 8}; 
// Pin 2 = Segment A, Pin 3 = Segment B, etc.

// A-G Index:  [A, B, C, D, E, F, G]
// 7-Segment Pattern for 3 Floors (1, 2, 3)
// Common Anode: LOW turns segment ON, HIGH turns segment OFF
const byte floorPatterns[4][7] = {
    //   A, B, C, D, E, F, G
    {1, 1, 1, 1, 1, 1, 1}, // 0: All OFF (Used for error/startup state)
    {1, 0, 0, 1, 1, 1, 1}, // 1: B, C ON
    {0, 0, 1, 0, 0, 1, 0}, // 2: A, B, G, E, D ON
    {0, 0, 0, 0, 1, 1, 0}  // 3: A, B
