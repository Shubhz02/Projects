int rainSensorPin = A0;  // Rain sensor connected to analog pin A0
int rainValue = 0;        // Variable to store the rain sensor value

void setup() {
  Serial.begin(9600);    // Start serial communication
}

void loop() {
  rainValue = analogRead(rainSensorPin);  // Read the rain sensor value
  Serial.print("Rain Sensor Value: ");
  Serial.println(rainValue);   // Print the value to the Serial Monitor

  if (rainValue < 500) {  // Adjust threshold based on your sensor
    Serial.println("Rain detected!");
  } else {
    Serial.println("No rain detected.");
  }

  delay(1000);  // Wait for 1 second before taking the next reading
}
