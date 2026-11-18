# ESP32 Sauna Monitor 🧖

A Wi-Fi connected sauna monitor built on the ESP32. It measures temperature and
humidity in the sauna, shows them on a small display, tells you when the sauna
is ready, and logs the data to a Python dashboard for analysis.

> **Status:** 🚧 In development, currently at Milestone 1 (temperature reading).

## Why this project?

Saunas are part of everyday life in Finland, but most of them only have a simple
analogue thermometer. I wanted to build a device that:

- tells me **when the sauna is ready** without checking it again and again,
- shows **humidity** too, which changes a lot when water is thrown on the stones (löyly),
- **records the data** so I can see how fast the sauna heats up and how löyly affects the air.

It is also a good engineering challenge: the sauna is **hot (80–100 °C) and humid**,
so normal hobby sensors and electronics do not survive there. Choosing the right
parts is part of the project (see [docs/design-decisions.md](docs/design-decisions.md)).

## Features

| Feature | Status |
|---|---|
| Temperature measurement (DS18B20 probe) | 🚧 In progress |
| Humidity measurement (I2C sensor) | ⏳ Planned |
| OLED display | ⏳ Planned |
| "Sauna ready" alert (LED / buzzer) | ⏳ Planned |
| Wi-Fi data logging | ⏳ Planned |
| Python dashboard (Pandas + Matplotlib) | ⏳ Planned |
| Custom PCB in KiCad | ⏳ Planned |
| Real sauna field test | ⏳ Planned |

## Hardware

| Part | Purpose |
|---|---|
| ESP32 DevKit | Microcontroller with Wi-Fi |
| DS18B20 waterproof probe (stainless steel, on a cable) | Temperature in the sauna (rated up to 125 °C) |
| 4.7 kΩ resistor | Pull-up resistor for the 1-Wire data line |
| *(Milestone 2)* humidity sensor rated for high temperature | Humidity in the sauna |
| *(Milestone 3)* 0.96" SSD1306 OLED (I2C) | Local display |

**Design principle:** only the sensor probes go inside the sauna. The ESP32 and
the display stay outside, at room temperature.

## Project structure

```
esp32-sauna-monitor/
├── firmware/          ESP32 code (PlatformIO, Arduino framework)
│   ├── platformio.ini
│   └── src/main.cpp
├── docs/
│   ├── wiring.md            how everything is connected
│   └── design-decisions.md  why I chose these parts
└── README.md
```

## How to build and run

1. Install [VS Code](https://code.visualstudio.com/) and the **PlatformIO** extension.
2. Clone this repository and open the `firmware` folder in VS Code.
3. Connect the ESP32 with a USB cable.
4. Click **Upload** (→) in the PlatformIO toolbar.
5. Open the **Serial Monitor** (115200 baud). You should see the temperature every second.

## Roadmap

- [ ] **Milestone 1:** read temperature with the DS18B20 and print it over serial
- [ ] **Milestone 2:** add the humidity sensor (I2C)
- [ ] **Milestone 3:** show values on the OLED display
- [ ] **Milestone 4:** "sauna ready" logic with hysteresis + LED/buzzer
- [ ] **Milestone 5:** send data over Wi-Fi, log and plot it in Python
- [ ] **Milestone 6:** design a PCB in KiCad and build an enclosure
- [ ] **Milestone 7:** test in a real sauna and add the results and plots here

## Safety

This is a low-voltage (5 V USB) device. It does **not** connect to or control the
sauna heater. Electronics stay outside the sauna room.

## Author

**Ali Esmaeili**, Computing and Electrical Engineering student, Tampere University
# esp32-sauna-monitor
ESP32-based sauna temperature &amp; humidity monitor with OLED display and Wi-Fi dashboard
