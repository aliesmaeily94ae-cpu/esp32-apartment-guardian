/*
 * ESP32 Sauna Monitor - Milestone 1
 * ---------------------------------
 * Goal: read the sauna temperature from a DS18B20 probe and print it
 *       to the serial monitor once per second.
 *
 * Wiring (see docs/wiring.md):
 *   DS18B20 red    -> 3.3V
 *   DS18B20 black  -> GND
 *   DS18B20 yellow -> GPIO 4  (+ 4.7 kOhm pull-up resistor to 3.3V)
 *
 * Author: Ali Esmaeili
 */

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ---- Configuration --------------------------------------------------------

// GPIO pin for the DS18B20 data line.
// GPIO 4 is a safe general-purpose pin on the ESP32 (it is not used
// during boot, unlike GPIO 0, 2, 12 and 15).
constexpr uint8_t ONE_WIRE_PIN = 4;

// How often we read the sensor, in milliseconds.
constexpr uint32_t READ_INTERVAL_MS = 1000;

// ---- Objects --------------------------------------------------------------

// OneWire handles the low-level 1-Wire protocol (timing of bits on one wire).
OneWire oneWire(ONE_WIRE_PIN);

// DallasTemperature uses OneWire to talk to the DS18B20 specifically.
DallasTemperature sensors(&oneWire);

// Time of the last reading. We use millis() instead of delay() so the
// loop never "freezes". This matters later, when the ESP32 also has to
// update a display and answer Wi-Fi requests at the same time.
uint32_t lastReadMs = 0;

// ---- Setup ----------------------------------------------------------------

void setup() {
    Serial.begin(115200);
    delay(500);  // give the serial monitor a moment to connect

    sensors.begin();

    Serial.println();
    Serial.println("ESP32 Sauna Monitor - Milestone 1");
    Serial.print("DS18B20 sensors found: ");
    Serial.println(sensors.getDeviceCount());

    if (sensors.getDeviceCount() == 0) {
        Serial.println("No sensor found. Check wiring and the 4.7k pull-up resistor.");
    }
}

// ---- Main loop ------------------------------------------------------------

void loop() {
    uint32_t now = millis();

    // Unsigned subtraction keeps working correctly even when millis()
    // overflows after ~49 days.
    if (now - lastReadMs >= READ_INTERVAL_MS) {
        lastReadMs = now;

        sensors.requestTemperatures();            // start a conversion
        float tempC = sensors.getTempCByIndex(0); // read the first sensor

        // The library returns DEVICE_DISCONNECTED_C (-127) on error.
        if (tempC == DEVICE_DISCONNECTED_C) {
            Serial.println("Error: sensor disconnected");
        } else {
            Serial.print("Temperature: ");
            Serial.print(tempC, 1);
            Serial.println(" C");
        }
    }

    // TODO (Milestone 2): read humidity sensor here
    // TODO (Milestone 3): update OLED display here
}
