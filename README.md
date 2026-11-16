<div align="center">

# Bluetooth Fighting Robot

**An ESP32 fighting robot you drive from your phone – Dabble GamePad over Bluetooth, two servos and a relay-switched weapon.**

![ESP32](https://img.shields.io/badge/ESP32-Dev%20Module-E7352C?style=for-the-badge&logo=espressif&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-Arduino-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Bluetooth](https://img.shields.io/badge/Bluetooth-Dabble%20App-0082FC?style=for-the-badge&logo=bluetooth&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

[Features](#features) · [Hardware](#hardware) · [Getting Started](#getting-started)

</div>

---

## Overview

This project is the control firmware for a small fighting robot built around an ESP32. The robot is driven from a phone using the GamePad module of the Dabble app over Bluetooth: the D-pad moves two servos in forward, backward, left and right patterns, and the Triangle button switches a relay that can power an additional actuator such as a weapon motor.

## Features

- Bluetooth control through the **Dabble** app (device name `MyESP32`)
- D-pad control of two servos:
  - **Up** – both servos +40°
  - **Down** – both servos −40°
  - **Left / Right** – servos move in opposite directions for turning
- Servos return to the 90° neutral position when no button is pressed
- **Triangle** button switches the relay ON while held, OFF when released
- Relay is switched **OFF at start-up** before anything else runs, so the weapon cannot fire on power-up
- Works with active-low (most common) or active-high relay modules – one constant, `RELAY_ACTIVE_LOW`
- Serial output at 115200 baud

## Hardware

| Component | Purpose |
|---|---|
| ESP32 development board | Main controller with built-in Bluetooth |
| 2 × servo motor | Robot movement |
| Relay module | Switches an extra load (e.g. weapon motor) |
| Smartphone with the Dabble app | Wireless controller |
| Battery pack | Powers the ESP32, servos and relay load |

## Pin Connections

| ESP32 Pin | Constant | Connected To |
|---|---|---|
| GPIO 13 | `servo1Pin` | Servo 1 signal |
| GPIO 12 | `servo2Pin` | Servo 2 signal |
| GPIO 5 | `relayPin` | Relay module input |
| GND | – | Common ground |

## How It Works

1. On startup the relay pin is made an output and the relay is switched off, Dabble starts Bluetooth with the name `MyESP32`, and both servos are attached and set to 90°.
2. Each loop, `Dabble.processInput()` reads the latest GamePad state.
3. The pressed D-pad button sets the servo angles to 90° ± 40° in the matching pattern; with no button pressed they return to 90°.
4. While Triangle is held, `relayOn()` is called; otherwise `relayOff()`. Both helpers use `RELAY_ACTIVE_LOW` to pick the correct pin level:

| `RELAY_ACTIVE_LOW` | Relay ON | Relay OFF |
|---|---|---|
| `true` (default, most relay modules) | GPIO 5 LOW | GPIO 5 HIGH |
| `false` | GPIO 5 HIGH | GPIO 5 LOW |

## Getting Started

1. Install the [Arduino IDE](https://www.arduino.cc/en/software) and add the **ESP32** board package (Espressif) through the Boards Manager.
2. Install these libraries via **Sketch → Include Library → Manage Libraries**:
   - **DabbleESP32** (provides `DabbleESP32.h`)
   - **ESP32Servo** (provides `ESP32Servo.h`)

   > Match the DabbleESP32 version to your ESP32 board package: **DabbleESP32 1.5.1** works with ESP32 core **2.0.x**; DabbleESP32 1.6.x targets newer ESP32 cores and fails to compile on 2.0.x (`BLECharacteristic::setValue(String&)` error).
3. Open `fighting_robot/fighting_robot.ino`.
4. If your relay module switches on with a HIGH input, set `RELAY_ACTIVE_LOW` to `false`.
5. Select your ESP32 board (e.g. *ESP32 Dev Module*) under **Tools → Board** and the correct **Port**, then click **Upload**.
6. Install the **Dabble** app on your phone, connect to `MyESP32` and open the **GamePad** module.

## Project Structure

```
fighting_robot-/
├── fighting_robot/
│   └── fighting_robot.ino   # Robot control sketch
├── LICENSE
└── README.md
```

## Future Improvements

- Use the joystick/analog mode of the Dabble GamePad for proportional speed control
- Add a failsafe that stops the robot and switches the relay off when Bluetooth disconnects
- Add battery voltage monitoring

## Author

**Swayam Khantwal** – [GitHub @Swayam7024](https://github.com/Swayam7024)

## License

This project is licensed under the MIT License – see the [LICENSE](LICENSE) file for details.
