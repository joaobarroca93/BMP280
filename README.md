# BMP280 Sensor Library

Arduino library for the BMP280 barometric pressure and temperature sensor, communicating over I2C.

Originally written 03/12/2017 by João Barroca <joao.barroca@tecnico.ulisboa.pt>.
Based on the [Bosch Sensortec BMP280 datasheet](https://www.bosch-sensortec.com/products/environmental-sensors/pressure-sensors/bmp280/) and Adafruit's compensation algorithms.

---

## Installation

1. Download or clone this repository.
2. Copy the folder into your Arduino `libraries/` directory.
3. Restart the Arduino IDE.
4. Include the library in your sketch: `#include <BMP280.h>`

---

## Wiring (I2C)

| BMP280 Pin | Arduino Pin |
|------------|-------------|
| VCC        | 3.3V        |
| GND        | GND         |
| SDA        | SDA (A4 on Uno) |
| SCL        | SCL (A5 on Uno) |
| SDO        | GND (sets I2C address to 0x76) |

> If SDO is pulled high, the I2C address becomes `0x77`. Pass it to the constructor: `BMP280 bmp(0x77);`

---

## API Reference

### Initialization

```cpp
BMP280 bmp;           // default I2C address 0x76
BMP280 bmp(0x77);     // custom I2C address

bool ok = bmp.begin();  // returns false if sensor not found or I2C error
```

`begin()` accepts optional parameters (defaults shown):

| Parameter | Default | Description |
|-----------|---------|-------------|
| `mode`    | `0x03`  | Power mode: 0=sleep, 1/2=forced, 3=normal |
| `osrs_p`  | `0x07`  | Pressure oversampling (x16) |
| `osrs_t`  | `0x02`  | Temperature oversampling (x2) |
| `t_sb`    | `0x00`  | Standby time (0.5 ms) |
| `filter`  | `0x07`  | IIR filter coefficient (16) |

### Readings

```cpp
float temp     = bmp.readTemperature();  // degrees Celsius
float pressure = bmp.readPressure();     // Pascals
float altitude = bmp.readAltitude();     // metres, using standard sea-level pressure (101325 Pa)
float altitude = bmp.readAltitude(seaLevelPa); // metres, using a custom sea-level pressure in Pa
```

> **Note:** `readPressure()` calls `readTemperature()` internally to update the compensation value. Call `readTemperature()` and `readPressure()` separately only if needed; calling both independently in the same loop iteration results in two temperature reads.

### Configuration getters / setters

```cpp
bmp.setPowerMode(uint8_t);              bmp.getPowerMode();
bmp.setPressureOverSampling(uint8_t);   bmp.getPressureOverSampling();
bmp.setTemperatureOverSampling(uint8_t);bmp.getTemperatureOverSampling();
bmp.setStandbyTime(uint8_t);            bmp.getStandbyTime();
bmp.setIIRcoeff(uint8_t);              bmp.getIIRcoeff();
```

---

## Example

```cpp
#include <BMP280.h>

BMP280 bmp;

void setup() {
  Serial.begin(9600);
  while (!bmp.begin()) {
    Serial.println(F("Error initializing BMP280!"));
    delay(1000);
  }
}

void loop() {
  Serial.print(bmp.readTemperature()); Serial.print(" C | ");
  Serial.print(bmp.readPressure());    Serial.print(" Pa | ");
  Serial.print(bmp.readAltitude());    Serial.println(" m");
  delay(50); // minimum ~38 ms between readings in normal mode at default settings
}
```

---

## License

Copyright (C) 2017 João Barroca
Released under the [GNU General Public License v3](LICENSE).
