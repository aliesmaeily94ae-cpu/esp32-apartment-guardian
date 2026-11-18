# Wiring

## Milestone 1: DS18B20 temperature probe

| DS18B20 wire | ESP32 pin | Note |
|---|---|---|
| Red (VDD) | 3.3V | Power |
| Black (GND) | GND | Ground |
| Yellow (DATA) | GPIO 4 | Data line |

Add a **4.7 kΩ resistor between DATA (GPIO 4) and 3.3V**.

```
 3.3V ──────┬──────────── Red (VDD)
            │
          [4.7k]
            │
 GPIO 4 ────┴──────────── Yellow (DATA)

 GND  ─────────────────── Black (GND)
```

### Why the pull-up resistor?

The 1-Wire bus is **open-drain**: devices can only pull the line LOW, never drive
it HIGH. The resistor pulls the line back up to 3.3V when nobody is pulling it
down. Without it, the line "floats" and the ESP32 reads random values, or finds
no sensor at all.

### Why 3.3V and not 5V?

ESP32 GPIO pins are **3.3V only**. If the sensor ran on 5V, the pull-up would put
5V on GPIO 4, which can damage the ESP32 over time.

> 📷 *TODO: add a photo of the real wiring here.*
