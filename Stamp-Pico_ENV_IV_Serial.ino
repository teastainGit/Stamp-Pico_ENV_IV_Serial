#include <SensirionI2CSht4x.h>
#include <Adafruit_BMP280.h>
#include "Adafruit_Sensor.h"

Adafruit_BMP280 bmp;
SensirionI2CSht4x sht4x;
float temperature, pressure,
  humidity;  // Store the vuale of pressure and Temperature.

void setup() {
  Wire.begin(43, 44);  //(SDA, SCL)
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  while (!bmp.begin(
    0x76)) {  // Init this sensor,True if the init was successful, otherwise
              // false.

    Serial.println(F("BMP280 fail"));
    delay(500);
  }
  Serial.println(F("BMP280 test"));
  uint16_t error;
  char errorMessage[256];
  sht4x.begin(Wire);
  uint32_t serialNumber;
  error = sht4x.serialNumber(serialNumber);
  if (error) {
    Serial.print("Error trying to execute serialNumber(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  } else {
    Serial.print("Serial Number: ");
    Serial.println(serialNumber);
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);
}

void loop() {
  uint16_t error;
  char errorMessage[256];
  delay(500);
  error = sht4x.measureHighPrecision(temperature, humidity);
  if (error) {
    Serial.print("Error trying to execute measureHighPrecision(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  } else {
    Serial.print("Pressure=");
    Serial.println(pressure / 1000 + 3.6, 1);
    Serial.print("Temp=");
    Serial.println(temperature);
    Serial.print("Humidity:");
    Serial.println(humidity);
    Serial.println("   ");
  }
  pressure = bmp.readPressure();
  delay(500);
}
