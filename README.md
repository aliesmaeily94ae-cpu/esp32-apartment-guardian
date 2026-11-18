# ESP32 Apartment Guardian 🏠

An ESP32-based device that watches over an apartment: it detects **water leaks**,
monitors **noise during quiet hours**, and tracks **indoor temperature and humidity**.
Readings are shown on a small OLED display and on a web page over Wi-Fi, and a
Python script logs and plots the data.

> **Status:** 🚧 In development, currently at Milestone 1 (temperature and humidity).

## Why this project?

Three everyday problems in Finnish apartments:

- **Water damage** (vesivahinko) is one of the most common and expensive problems
  in Finnish homes. A leak under a dishwasher or sink can go unnoticed for days.
- **Quiet hours** (usually 22:00–07:00) are part of most building rules. It is
  useful to see how loud your own apartment actually is.
- **Indoor climate:** in winter the air gets very dry, and high humidity in
  bathrooms increases the risk of mould.

I wanted one small device that covers all three, built only from basic, cheap parts.

## Features

| Feature | Status |
|---|---|
| Temperature and humidity (DHT11) | 🚧 In progress |
| OLED display with screens switched by buttons | ⏳ Planned |
| Water leak alarm (water sensor + buzzer) | ⏳ Planned |
| Status light (RGB LED: green OK, yellow warning, red alarm) | ⏳ Planned |
| Noise level monitoring (sound sensor) | ⏳ Planned |
| Wi-Fi web dashboard + quiet-hours logic (NTP time) | ⏳ Planned |
| Python data logger and plots (Pandas + Matplotlib) | ⏳ Planned |
| One-week test in my apartment | ⏳ Planned |

## Hardware

| Part | Purpose |
|---|---|
| ESP32 DevKit | Microcontroller with Wi-Fi |
| DHT11 | Temperature and humidity |
| Water level sensor module | Leak detection |
| KY-038 sound sensor (microphone + LM393) | Noise level |
| 0.96" OLED display (I2C) | Local display |
| Buzzer | Alarm sound |
| RGB LED + 220 Ω resistors | Status light |
| Push buttons | Switch display screens, silence the alarm |
| Breadboard, jumper wires, 220 Ω / 1 kΩ / 10 kΩ resistors | Prototyping |

## Project structure

```
esp32-apartment-guardian/
├── firmware/          ESP32 code (PlatformIO, Arduino framework)
│   ├── platformio.ini
│   └── src/main.cpp
├── docs/
│   ├── wiring.md            pin plan and how everything is connected
│   └── design-decisions.md  why the project is built this way
└── README.md
```

## How to build and run

1. Install [VS Code](https://code.visualstudio.com/) and the **PlatformIO** extension.
2. Clone this repository and open the `firmware` folder in VS Code.
3. Connect the ESP32 with a USB cable.
4. Click **Upload** (→) in the PlatformIO toolbar.
5. Open the **Serial Monitor** (115200 baud). You should see temperature and humidity every 2 seconds.

## Roadmap

- [ ] **Milestone 1:** read temperature and humidity (DHT11) and print them over serial
- [ ] **Milestone 2:** show readings on the OLED display, switch screens with a button
- [ ] **Milestone 3:** water leak detection with buzzer alarm and RGB status LED
- [ ] **Milestone 4:** noise level measurement with the sound sensor
- [ ] **Milestone 5:** Wi-Fi web dashboard and quiet-hours logic (time from NTP)
- [ ] **Milestone 6:** Python data logger with plots
- [ ] **Milestone 7:** one-week test in my apartment, with results and plots here

## Known limitations

- The DHT11 is a basic sensor (about ±2 °C and ±5 % RH). It is fine for
  trends and alarms, but not for precise measurements.
- The KY-038 measures sound *level*, not calibrated decibels.

## Author

**Ali Esmaeili**, Computing and Electrical Engineering student, Tampere University
