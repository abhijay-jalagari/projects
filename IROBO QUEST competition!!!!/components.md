🛠️ Components Needed
Microcontroller: 1x Arduino Uno (or similar)

Sensor: 1x Sound Detection Sensor Module (e.g., KY-037 or a similar digital output module). You will use the Digital Output (DO) pin.

Output 1: 1x LED (Light Emitting Diode)

Output 2: 1x Active Buzzer Module (or Piezo Buzzer)

Resistors: 1x 220 Ohm Resistor (for the LED protection)

Wiring: Jumper Wires

Platform: 1x Breadboard

Sound Sensor	VCC	5V	Power
Sound Sensor	GND	GND	Ground
Sound Sensor	OUT/DO	Digital Pin 2	Input for sound trigger
LED	Anode (+)	Digital Pin 3	Connect via a 220$\Omega$ resistor
LED	Cathode (-)	GND	
Buzzer	Positive (+)	Digital Pin 4	Digital Output
Buzzer	Negative (-)	GND