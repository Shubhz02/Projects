#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 (some modules use 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.begin(16, 2);  // Initialize the LCD
  lcd.backlight();    // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("LCD Connected!");  // Display a test message
}

void loop() {
  lcd.setCursor(0, 1);  // Move to second row
  lcd.print("Hello, World! ");
  delay(2000);
}
