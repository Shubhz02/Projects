#define BLYNK_TEMPLATE_ID "TMPL3_-yzqejO"
#define BLYNK_TEMPLATE_NAME "Real Time Weather Monitoring System"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Adafruit_BMP085_U.h>
#include <MQ2.h>

// WiFi & Blynk Credentials
char auth[] = "8SIUMZZ-UO7Y471eiG3TWXAlOHj7sssf";  // Blynk Auth Token
char ssid[] = "Shubham_project";                   // Wi-Fi SSID
char pass[] = "Admin@123";                         // Wi-Fi Password

// Sensor Pins and Definitions
#define DHTPIN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP085_Unified bmp;
MQ2 mq2(A0);  // Analog pin for MQ2

LiquidCrystal_I2C lcd(0x3F, 16, 2);  // LCD I2C address 0x3F, 16x2 size

// Setup
void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);  // Connect to Blynk
  dht.begin();  // Initialize DHT sensor
  lcd.begin(16, 2);  // Initialize LCD
  lcd.print("Initializing...");
  bmp.begin();  // Initialize BMP180
  mq2.begin();  // Initialize MQ2 sensor
  delay(2000);
}

// Main loop
void loop() {
  Blynk.run();  // Keep Blynk running
  
  // Read sensor data
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  float pressure;
  bmp.getPressure(&pressure);
  float airQuality = mq2.read();

  // Send data to Blynk
  Blynk.virtualWrite(V1, temp);  // Temperature
  Blynk.virtualWrite(V2, humidity);  // Humidity
  Blynk.virtualWrite(V3, airQuality);  // Air Quality
  Blynk.virtualWrite(V4, pressure);  // Atmospheric Pressure

  // Display data on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");

  delay(2000);  // Update every 2 seconds
}
