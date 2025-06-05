#include <DabbleESP32.h>
#include <ESP32Servo.h>

Servo servo1, servo2;

const int servo1Pin = 13;  // Servo 1 Pin
const int servo2Pin = 12;  // Servo 2 Pin
const int relayPin = 5;   // Relay Pin
int idealAngle1 = 90;      // Ideal position for Servo 1
int idealAngle2 = 90;      // Ideal position for Servo 2
int activeAngle = 40;      // Angle to move when a button is pressed

void setup() {
    Serial.begin(115200);  
    Dabble.begin("MyESP32");  // Start Bluetooth with custom name

    servo1.attach(servo1Pin);
    servo2.attach(servo2Pin);

    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW);  // Relay OFF by default

    servo1.write(idealAngle1);  // Set servos to ideal position
    servo2.write(idealAngle2);
}

void loop() {
    Dabble.processInput();  // Process input from Dabble app

    // Move servos based on button presses
    if (GamePad.isUpPressed()) {
        servo1.write(idealAngle1 + activeAngle);
        servo2.write(idealAngle2 + activeAngle);
    } else if (GamePad.isDownPressed()) {
        servo1.write(idealAngle1 - activeAngle);
        servo2.write(idealAngle2 - activeAngle);
    } else if (GamePad.isLeftPressed()) {
        servo1.write(idealAngle1 + activeAngle);
        servo2.write(idealAngle2 - activeAngle);
    } else if (GamePad.isRightPressed()) {
        servo1.write(idealAngle1 - activeAngle);
        servo2.write(idealAngle2 + activeAngle);
    } else {
        // No button pressed, return to ideal position
        servo1.write(idealAngle1);
        servo2.write(idealAngle2);
    }

    // Triangle button controls the relay
    digitalWrite(relayPin, GamePad.isTrianglePressed() ? LOW : HIGH);
}