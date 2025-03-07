int gasSensorPin = A1;  // MQ-2 sensor connected to analog pin A1
int gasValue = 0;       // Variable to store gas sensor value

void setup() {
  Serial.begin(9600);    // Start serial communication
}

void loop() {
  gasValue = analogRead(gasSensorPin);  // Read the gas sensor value
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);  // Print the value to the Serial Monitor

  if (gasValue > 400) {  // Adjust threshold based on your environment
    Serial.println("High gas concentration detected!");
  } else {
    Serial.println("Air quality is normal.");
  }

  delay(1000);  // Wait for 1 second before the next reading
}
