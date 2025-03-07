#include <DHT.h>  // Include the DHT library

#define DHTPIN 2       // Pin for DHT11 data pin
#define DHTTYPE DHT11  // Define the DHT sensor type (DHT11)

DHT dht(DHTPIN, DHTTYPE);  // Create an instance of the DHT sensor

void setup() {
    Serial.begin(9600);   // Start serial communication
    dht.begin();          // Initialize the DHT sensor
}

void loop() {
    float humidity = dht.readHumidity();        // Read humidity
    float temperature = dht.readTemperature();  // Read temperature

    // Check if the readings are valid
    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    // Display readings on Serial Monitor
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C");

    delay(2000);  // Wait for 2 seconds before the next reading
}
