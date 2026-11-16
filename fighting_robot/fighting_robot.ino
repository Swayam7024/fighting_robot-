/*
 * ------------------------------------------------------------------
 *  Bluetooth Fighting Robot - ESP32 + Dabble GamePad
 * ------------------------------------------------------------------
 *  Board  : ESP32 Dev Module
 *  Wiring : GPIO13 -> servo 1 signal
 *           GPIO12 -> servo 2 signal
 *           GPIO5  -> relay module input (weapon / extra load)
 *           GND    -> common ground
 *  Control: Dabble app -> GamePad module, Bluetooth name "MyESP32"
 *  Author : Swayam Khantwal (github.com/Swayam7024)
 *  License: MIT
 * ------------------------------------------------------------------
 */

#include <DabbleESP32.h>
#include <ESP32Servo.h>

Servo servo1, servo2;

const int servo1Pin = 13;  // Servo 1 Pin
const int servo2Pin = 12;  // Servo 2 Pin
const int relayPin = 5;    // Relay Pin

// Most relay modules switch ON when their input is LOW (active-low).
// Set this to false if your relay module switches ON with a HIGH input.
const bool RELAY_ACTIVE_LOW = true;

int idealAngle1 = 90;      // Ideal position for Servo 1
int idealAngle2 = 90;      // Ideal position for Servo 2
int activeAngle = 40;      // Angle to move when a button is pressed

void relayOn() {
    digitalWrite(relayPin, RELAY_ACTIVE_LOW ? LOW : HIGH);
}

void relayOff() {
    digitalWrite(relayPin, RELAY_ACTIVE_LOW ? HIGH : LOW);
}

void setup() {
    // Make the relay pin an output and switch the relay OFF first,
    // so the weapon cannot switch on during start-up.
    pinMode(relayPin, OUTPUT);
    relayOff();

    Serial.begin(115200);
    Dabble.begin("MyESP32");  // Start Bluetooth with custom name

    servo1.attach(servo1Pin);
    servo2.attach(servo2Pin);

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

    // Triangle button controls the relay: ON while held, OFF otherwise
    if (GamePad.isTrianglePressed()) {
        relayOn();
    } else {
        relayOff();
    }
}
