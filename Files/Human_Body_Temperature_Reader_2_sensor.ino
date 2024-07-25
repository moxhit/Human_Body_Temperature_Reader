// Code to read temprature values from two MAX30205 sensor using pins 21,22 for sensor 1 and pins 13,5 for sensor 2

#include <Wire.h>

// Define I2C buses for both sensors
TwoWire I2Cone = TwoWire(1);

// Define MAX30205 temperature sensor I2C address
const uint8_t MAX30205_I2C_ADDRESS = 0x49; // Common address used by MAX30205

// Function to initialize the MAX30205 sensor on the specified I2C bus
void initMAX30205(TwoWire &i2cBus, uint8_t sda, uint8_t scl) {
  i2cBus.begin(sda, scl);
}

// Function to read temperature from MAX30205 sensor
float readTemperature(TwoWire &i2cBus) {
  i2cBus.beginTransmission(MAX30205_I2C_ADDRESS);
  i2cBus.write(0x00); // Temperature register
  if (i2cBus.endTransmission() != 0) {
    Serial.println("Error ending transmission");
    return NAN;
  }

  i2cBus.requestFrom(MAX30205_I2C_ADDRESS, 2);
  if (i2cBus.available() == 2) {
    uint16_t rawTemperature = (i2cBus.read() << 8) | i2cBus.read();
    return rawTemperature * 0.00390625; // Conversion factor for MAX30205
  } else {
    Serial.println("Error reading temperature");
  }

  return NAN; // Return Not-a-Number if reading fails
}

void setup() {
  Serial.begin(115200);

  // Initialize the first I2C bus (GPIO 21 and 22)
  initMAX30205(Wire, 21, 22);
  
  // Initialize the second I2C bus (GPIO 13 and 5)
  I2Cone.begin(13, 5);
}

void loop() {
  // Read temperature from the first sensor on default I2C bus (GPIO 21 and 22)
  Serial.print("Sensor 1 Temperature: ");
  float temp1 = readTemperature(Wire);
  if (isnan(temp1)) {
    Serial.println("Failed to read temperature from Sensor 1");
  } else {
    Serial.print(temp1);
    Serial.println(" *C");
  }

  // Read temperature from the second sensor on I2Cone bus (GPIO 13 and 5)
  Serial.print("Sensor 2 Temperature: ");
  float temp2 = readTemperature(I2Cone);
  if (isnan(temp2)) {
    Serial.println("Failed to read temperature from Sensor 2");
  } else {
    Serial.print(temp2);
    Serial.println(" *C");
  }

  delay(2000); // Delay between readings
}
