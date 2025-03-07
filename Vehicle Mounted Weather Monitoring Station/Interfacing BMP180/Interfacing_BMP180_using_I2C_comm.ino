#include <Wire.h>              // Library for I2C communication
#include <Adafruit_BMP085.h>   // Adafruit BMP180 Library

Adafruit_BMP085 bmp;  // Create an instance of the BMP180 sensor

void setup() {
  Serial.begin(9600);   // Start serial communication

  if (!bmp.begin()) {   // Check if the sensor is connected
    Serial.println("BMP180 sensor not found! Check wiring.");
    while (1);  // Halt the program if sensor is not found
  }

  Serial.println("BMP180 Sensor Initialized.");
}

void loop() {
  Serial.print("Temperature: ");
  Serial.print(bmp.readTemperature());  // Read and print temperature
  Serial.println(" *C");

  Serial.print("Pressure: ");
  Serial.print(bmp.readPressure());  // Read and print pressure
  Serial.println(" Pa");

  Serial.print("Altitude: ");
  Serial.print(bmp.readAltitude(101325));  // Calculate altitude (adjust sea-level pressure if needed)
  Serial.println(" m");

  Serial.println("----------------------");
  delay(2000);  // Wait for 2 seconds before the next reading
}
