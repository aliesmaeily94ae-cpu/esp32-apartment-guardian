/*
 * ESP32 Apartment Guardian - Milestone 1
 * --------------------------------------
 * Goal: read indoor temperature and humidity from a DHT11 sensor and
 *       print them to the serial monitor every 2 seconds.
 *
 * Wiring (see docs/wiring.md):
 *   DHT11 VCC  -> 3.3V
 *   DHT11 GND  -> GND
 *   DHT11 DATA -> GPIO 4
 *   (bare 4-pin DHT11 only: add a 10 kOhm pull-up from DATA to 3.3V;
 *    3-pin modules already have one on the board)
 *
 * Author: Ali Esmaeili
 */

#include <Arduino.h>
#include <DHT.h>

// ---- Configuration --------------------------------------------------------

// GPIO 4 is a safe general-purpose pin on the ESP32 (it is not a
// boot-strapping pin like GPIO 0, 2, 12 or 15).
constexpr uint8_t DHT_PIN = 4;

// The DHT11 can only give a new measurement about once per second.
// Reading faster just returns old or invalid data, so we use 2 seconds.
constexpr uint32_t READ_INTERVAL_MS = 2000;

// ---- Objects --------------------------------------------------------------

DHT dht(DHT_PIN, DHT11);

// Time of the last reading. We use millis() instead of delay() so the
// loop never "freezes". This matters later, when the ESP32 must also
// watch the water sensor, update the display and answer Wi-Fi requests.
uint32_t lastReadMs = 0;

// ---- Setup ----------------------------------------------------------------

void setup() {
    Serial.begin(115200);
    delay(500);  // give the serial monitor a moment to connect

    dht.begin();

    Serial.println();
    Serial.println("ESP32 Apartment Guardian - Milestone 1");
    Serial.println("Reading DHT11 every 2 seconds...");
}

// ---- Main loop ------------------------------------------------------------

void loop() {
    uint32_t now = millis();

    // Unsigned subtraction keeps working correctly even when millis()
    // overflows after ~49 days.
    if (now - lastReadMs >= READ_INTERVAL_MS) {
        lastReadMs = now;

        float humidity = dht.readHumidity();      // relative humidity, %
        float tempC    = dht.readTemperature();   // degrees Celsius

        // If the sensor does not answer, the library returns NaN
        // ("not a number"). isnan() checks for that.
        if (isnan(humidity) || isnan(tempC)) {
            Serial.println("Error: could not read DHT11. Check the wiring.");
            return;
        }

        Serial.print("Temperature: ");
        Serial.print(tempC, 1);
        Serial.print(" C   Humidity: ");
        Serial.print(humidity, 0);
        Serial.println(" %");
    }

    // TODO (Milestone 2): update the OLED display here
    // TODO (Milestone 3): check the water sensor here
}
