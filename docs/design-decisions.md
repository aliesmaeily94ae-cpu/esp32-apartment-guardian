# Design decisions

This file explains *why* the project is built the way it is.

## 1. Analog sensors on ADC1 pins (GPIO 32–39)

The ESP32 has two ADCs (analog-to-digital converters). **ADC2 cannot be used
while Wi-Fi is on**, because the Wi-Fi driver uses it. This project uses Wi-Fi,
so the analog sensors (water sensor and sound sensor) are connected to
**ADC1 pins**: GPIO 34 and GPIO 35.

GPIO 34–39 are also **input-only** pins, which is fine for sensors and keeps
output-capable pins free for the LED and buzzer.

## 2. The water sensor is powered from a GPIO pin

**Problem:** the water sensor has bare copper tracks. If current flows through
them all the time, they corrode (electrolysis) and the sensor stops working
within weeks.

**Choice:** the sensor's power pin is connected to GPIO 26 instead of 3.3 V. The
ESP32 turns the sensor on only for a few milliseconds when it takes a reading,
for example once per second.

## 3. Non-blocking code (`millis()` instead of `delay()`)

`delay()` stops the whole program. The ESP32 has to read sensors, update the
display, react to buttons and serve a web page at the same time, so all timing
uses `millis()` from the start.

## 4. Buttons use internal pull-up resistors

The buttons connect a GPIO pin to GND. The ESP32's internal pull-up
(`INPUT_PULLUP`) keeps the pin HIGH when the button is not pressed, so no
external resistors are needed. Pressed = LOW.

## 5. DHT11 instead of a more accurate sensor

The DHT11 was already available, and ±2 °C / ±5 % RH is enough to detect
trends such as dry winter air or a humid bathroom. A more accurate sensor
(for example an SHT31) could replace it later without changing the overall design.

## 6. Status shown three ways

- **OLED:** exact values, when you are near the device
- **RGB LED:** status at a glance from across the room
- **Buzzer:** only for real alarms (water leak), so it is not ignored
