//blynk 
#define BLYNK_TEMPLATE_ID "TMPL3_-yzqejO"
#define BLYNK_TEMPLATE_NAME "Real Time Weather Monitoring System"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>




char auth[] = "8SIUMZZ-UO7Y471eiG3TWXAlOHj7sssf";  // Paste Blynk Auth Token
char ssid[] = "Shubham_project";         // Enter Wi-Fi Name
char pass[] = "Admin@123";     // Enter Wi-Fi Password

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);  // Connect to Blynk server
}

void loop() {
  Blynk.run();  // Keep connection alive
}


