# ESP32 Dual MAX30205 Temperature Sensor Reader

This project demonstrates how to read temperature values from two MAX30205 sensors using an ESP32 microcontroller. The sensors are connected via two different I2C buses, allowing simultaneous readings from both sensors.

## Features
- Read temperature from two MAX30205 sensors.
- Utilize two different I2C buses on the ESP32.
- Print temperature data to the serial monitor.

## Components Used
- ESP32 Dev Module
- 2 MAX30205 temperature sensors
- I2C buses

## Connections
- **Sensor 1**: SDA - GPIO21, SCL - GPIO22
- **Sensor 2**: SDA - GPIO13, SCL - GPIO5

## Code Overview

### Libraries
- `Wire.h`

### Constants
- **MAX30205_I2C_ADDRESS**: Common I2C address used by MAX30205 (0x49).

### Functions
- `initMAX30205(TwoWire &i2cBus, uint8_t sda, uint8_t scl)`: Initializes the MAX30205 sensor on the specified I2C bus.
- `readTemperature(TwoWire &i2cBus)`: Reads temperature from MAX30205 sensor.

### Setup
```cpp
void setup() {
  Serial.begin(115200);

  // Initialize the first I2C bus (GPIO 21 and 22)
  initMAX30205(Wire, 21, 22);
  
  // Initialize the second I2C bus (GPIO 13 and 5)
  I2Cone.begin(13, 5);
}
