# Wiring

## Pin plan (all milestones)

| Part | Part pin | ESP32 pin | Milestone |
|---|---|---|---|
| DHT11 | DATA | GPIO 4 | 1 |
| OLED | SDA | GPIO 21 | 2 |
| OLED | SCL | GPIO 22 | 2 |
| Button 1 (screen) | one leg | GPIO 32 (other leg to GND) | 2 |
| Button 2 (silence alarm) | one leg | GPIO 33 (other leg to GND) | 3 |
| Water sensor | S (analog out) | GPIO 34 | 3 |
| Water sensor | + (power) | GPIO 26 | 3 |
| Buzzer | + | GPIO 25 | 3 |
| RGB LED | R / G / B | GPIO 16 / 17 / 18 (each through 220 Ω) | 3 |
| Sound sensor KY-038 | AO (analog out) | GPIO 35 | 4 |

All sensors run on **3.3 V**, and all grounds are connected together.

## Milestone 1: DHT11

| DHT11 pin | ESP32 pin |
|---|---|
| VCC (+) | 3.3V |
| GND (−) | GND |
| DATA (S / OUT) | GPIO 4 |

**Pull-up resistor:**
- **3-pin DHT11 module** (sensor on a small board): the pull-up is already on the board. No resistor needed.
- **Bare 4-pin DHT11:** add a **10 kΩ resistor between DATA and 3.3V**. Pin 3 is not connected.

```
 3.3V ──────┬──────────── VCC
            │
          [10k]   (bare sensor only)
            │
 GPIO 4 ────┴──────────── DATA

 GND  ─────────────────── GND
```

### Why a pull-up resistor?

The DHT11 data line is **open-drain**: the sensor and the ESP32 can only pull it
LOW. The resistor pulls the line back HIGH when nobody is pulling it down.
Without it, the line "floats" and the readings fail.

### Why 3.3V?

ESP32 GPIO pins are **3.3V only**. The DHT11 works from 3.3 V to 5.5 V, so
running it on 3.3 V keeps the data line at a safe level for the ESP32.

> 📷 *TODO: add a photo of the real wiring here.*
