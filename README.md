# ESP32 LED Controller Project

[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

## Overview
This project allows you to control LED strips (e.g., WS2812, Neopixel) using an ESP32 microcontroller. You can customize colors, effects, and patterns via Wi-Fi using a web interface.

Key Features:
- Control LED colors and patterns in real-time
- Wi-Fi enabled web interface for easy control
- Supports multiple LED effects
- Compatible with ESP32 boards

## Hardware Requirements
- ESP32 Development Board
- WS2812 / Neopixel LED strip
- 5V Power Supply (suitable for your LED strip)
- Jumper wires and breadboard (optional)
- USB cable to program ESP32

## Software Requirements
- Arduino IDE (latest version)
- ESP32 Arduino Core installed
- Required Arduino libraries:
  - `WiFi.h`
  - `WebServer.h`
  - `Adafruit_NeoPixel` (or relevant LED library)

## Wiring
Connect your LED strip to the ESP32 as follows:
- **Data Pin:** GPIO 5 (or as defined in your code)
- **Power (VCC):** 5V
- **Ground (GND):** GND

**Note:** If using a long LED strip, use an external 5V power supply and connect all grounds together.

## Installation & Usage
1. Clone this repository:
```bash
git clone https://github.com/Kashif-Mustari/ESP32-LED-Controller-project.git
