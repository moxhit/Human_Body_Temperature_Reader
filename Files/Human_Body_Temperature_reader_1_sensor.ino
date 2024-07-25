//code to read temperature values of human body using MAX30205 using i2c pins

#include <Wire.h>

// Define I2C address for the MAX30205 temperature sensor
const uint8_t MAX30205_I2C_ADDRESS = 0x48; // Address used by MAX30205

// Function to initialize the MAX30205 sensor
void initMAX30205(uint8_t sda, uint8_t scl) {
  Wire.begin(sda, scl);
}

// Function to read temperature from MAX30205 sensor
float readTemperature() {
  Wire.beginTransmission(MAX30205_I2C_ADDRESS);
  Wire.write(0x00); // Temperature register
  if (Wire.endTransmission() != 0) {
    Serial.println("Error ending transmission");
    return NAN;
  }

  Wire.requestFrom(MAX30205_I2C_ADDRESS, 2);
  if (Wire.available() == 2) {
    uint16_t rawTemperature = (Wire.read() << 8) | Wire.read();
    return rawTemperature * 0.00390625; // Conversion factor for MAX30205
  } else {
    Serial.println("Error reading temperature");
  }

  return NAN; // Return Not-a-Number if reading fails
}

void setup() {
  Serial.begin(115200);

  // Initialize the MAX30205 sensor (GPIO 21 and 22)
  initMAX30205(21, 22);
}

void loop() {
  // Read temperature from the sensor on I2C bus (GPIO 21 and 22)
  Serial.print("Sensor Temperature: ");
  float temp = readTemperature();
  if (isnan(temp)) {
    Serial.println("Failed to read temperature from Sensor");
  } else {
    Serial.print(temp);
    Serial.println(" *C");
  }

  delay(2000); // Delay between readings
}
