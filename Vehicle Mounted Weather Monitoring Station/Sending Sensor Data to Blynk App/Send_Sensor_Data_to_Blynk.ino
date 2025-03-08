// Blynk Template Info
#define BLYNK_TEMPLATE_ID "TMPL3_-yzqejO"
#define BLYNK_TEMPLATE_NAME "Real Time Weather Monitoring System"

// Required Libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>
#include <MQ2.h>

// WiFi & Blynk Credentials
char auth[] = "8SIUMZZ-UO7Y471eiG3TWXAlOHj7sssf";  // Blynk Auth Token
char ssid[] = "Shubham_project";                   // Wi-Fi SSID
char pass[] = "Admin@123";                         // Wi-Fi Password

// Sensor Pins
#define DHTPIN D4       // DHT11 connected to GPIO2 (D4)
#define DHTTYPE DHT11   // DHT Type
#define RAIN_PIN A0     // Rain Sensor on Analog Pin
#define MQ2_PIN A0      // MQ-2 Sensor on Analog Pin
#define I2C_SDA D2      // I2C SDA for ESP8266
#define I2C_SCL D1      // I2C SCL for ESP8266

// Sensor Initialization
DHT dht(DHTPIN, DHTTYPE);       // DHT11 Sensor
Adafruit_BMP085 bmp180;         // BMP180 Sensor
MQ2 mq2(MQ2_PIN);               // MQ-2 Gas Sensor
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C LCD (Address: 0x27)

// Timer for sending data to Blynk
BlynkTimer timer;

// Function to Read Sensors & Update Blynk
void sendSensorData() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    float pressure = bmp180.readPressure() / 100.0;  // Convert to hPa
    float altitude = bmp180.readAltitude();
    int rainValue = analogRead(RAIN_PIN);
    int airQuality = mq2.readPpm();

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("DHT11 Error: Failed to read!");
        return;
    }

    // Print Readings in Serial Monitor
    Serial.print("Temp: "); Serial.print(temperature); Serial.print("°C, ");
    Serial.print("Humidity: "); Serial.print(humidity); Serial.print("%, ");
    Serial.print("Pressure: "); Serial.print(pressure); Serial.print(" hPa, ");
    Serial.print("Altitude: "); Serial.print(altitude); Serial.print(" m, ");
    Serial.print("Rain: "); Serial.print(rainValue); Serial.print(", ");
    Serial.print("Air Quality: "); Serial.println(airQuality);

    // Send Data to Blynk
    Blynk.virtualWrite(V0, temperature);
    Blynk.virtualWrite(V1, humidity);
    Blynk.virtualWrite(V2, pressure);
    Blynk.virtualWrite(V3, altitude);
    Blynk.virtualWrite(V4, rainValue);
    Blynk.virtualWrite(V5, airQuality);

    // Update LCD Display
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T: "); lcd.print(temperature); lcd.print("C H: "); lcd.print(humidity); lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("P: "); lcd.print(pressure); lcd.print(" hPa");
}

void setup() {
    Serial.begin(115200);

    // Initialize WiFi & Blynk
    Blynk.begin(auth, ssid, pass);
    
    // Initialize Sensors
    dht.begin();
    if (!bmp180.begin()) {
        Serial.println("BMP180 Error: Sensor not found!");
    }

    mq2.begin();

    // Initialize I2C for ESP8266
    Wire.begin(I2C_SDA, I2C_SCL);
    lcd.init();
    lcd.backlight();

    // Start Data Sending to Blynk Every 2 Seconds
    timer.setInterval(2000L, sendSensorData);
}

void loop() {
    Blynk.run();
    timer.run();
}
