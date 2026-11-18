# Design decisions

This file explains *why* the project is built the way it is.

## 1. Temperature sensor: DS18B20 waterproof probe

**Problem:** a sauna is usually 70–100 °C. Many common hobby sensors (for example
the DHT11 or DHT22) are only rated up to about 50–80 °C.

**Choice:** DS18B20 in a stainless-steel waterproof probe.

**Reasons:**
- Rated from −55 °C to +125 °C, so it covers sauna temperatures with margin.
- Digital output (1-Wire): long cables do not add measurement error like they
  would with an analog sensor.
- Only one GPIO pin needed, and several sensors can share the same wire later
  (for example one near the ceiling and one near the bench).
- Cheap and widely available.

**Trade-off:** a reading takes up to ~750 ms at 12-bit resolution, which is
slow, but more than fast enough for a sauna that heats up over 30–60 minutes.

## 2. Electronics stay outside the sauna

**Problem:** high temperature and humidity damage electronics and USB power
supplies.

**Choice:** only the sensor probes go into the sauna through the wall or door
gap. The ESP32, display and power supply stay outside.

## 3. Non-blocking code (`millis()` instead of `delay()`)

`delay()` stops the whole program. Later the ESP32 must update the display,
handle Wi-Fi and check the alert at the same time, so the code uses `millis()`
timing from the start.

## 4. Humidity sensor (Milestone 2): *to be decided*

TODO: compare candidate sensors (operating temperature range, humidity
accuracy at high temperature, interface, price) and write the decision here.
