# Bluetooth Fighting Robot

An ESP32 fighting robot controlled from a smartphone over Bluetooth with the Dabble app, driving two servos and a relay-switched weapon.

![Platform](https://img.shields.io/badge/Platform-ESP32-E7352C?logo=espressif&logoColor=white)
![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C?logo=cplusplus&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

## Overview

This project is the control firmware for a small fighting robot built around an ESP32. The robot is driven from a phone using the GamePad module of the Dabble app over Bluetooth: the D-pad moves two servos in forward, backward, left and right patterns, and the Triangle button switches a relay that can power an additional actuator such as a weapon motor.

## Features

- Bluetooth control through the **Dabble** app (device name `MyESP32`)
- D-pad control of two servos:
  - **Up** – both servos +40°
  - **Down** – both servos −40°
  - **Left / Right** – servos move in opposite directions for turning
- Servos return to the 90° neutral position when no button is pressed
- **Triangle** button toggles a relay output
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

| ESP32 Pin | Connected To |
|---|---|
| GPIO 13 | Servo 1 signal |
| GPIO 12 | Servo 2 signal |
| GPIO 5 | Relay module input |
| GND | Common ground |

## How It Works

1. On startup, Dabble starts Bluetooth with the name `MyESP32`, both servos are attached and set to 90°, and the relay pin is configured as an output.
2. Each loop, `Dabble.processInput()` reads the latest GamePad state.
3. The pressed D-pad button sets the servo angles to 90° ± 40° in the matching pattern; with no button pressed they return to 90°.
4. The relay pin is driven LOW while Triangle is held and HIGH otherwise, which suits a common active-low relay module (relay on while Triangle is pressed).

## Getting Started

1. Install the [Arduino IDE](https://www.arduino.cc/en/software) and add the **ESP32** board package (Espressif) through the Boards Manager.
2. Install these libraries via **Sketch → Include Library → Manage Libraries**:
   - **DabbleESP32** (provides `DabbleESP32.h`)
   - **ESP32Servo** (provides `ESP32Servo.h`)
3. Open `Fighting_robit/swayam_ka_robit.ino`. The Arduino IDE expects the sketch file and its folder to have the same name, so it may offer to move the file into a matching folder.
4. Select your ESP32 board (e.g. *ESP32 Dev Module*) under **Tools → Board** and the correct **Port**, then click **Upload**.
5. Install the **Dabble** app on your phone, connect to `MyESP32` and open the **GamePad** module.

## Project Structure

```
fighting_robot-/
├── Fighting_robit/
│   └── swayam_ka_robit.ino   # Robot control sketch
├── LICENSE
└── README.md
```

## Future Improvements

- Use the joystick/analog mode of the Dabble GamePad for proportional speed control
- Add a failsafe that stops the robot and switches the relay off when Bluetooth disconnects
- Make the relay's default state consistent between `setup()` and `loop()`
- Add battery voltage monitoring

## Author

**Swayam Khantwal** – [GitHub @Swayam7024](https://github.com/Swayam7024)

## License

This project is licensed under the MIT License – see the [LICENSE](LICENSE) file for details.
