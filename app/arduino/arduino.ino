#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("LCD");
    lcd.setCursor(0, 1);
  lcd.print("is ON");
  Serial.begin(9600);
  delay(2000);
      lcd.clear();
 // Start the serial communication
}

void loop() {
  
  // Check if there is incoming data from Qt
  if (Serial.available() > 0) {
    // Read the incoming data until a newline character is received
    String incomingString = "";
    char incomingChar;

    while (Serial.available() > 0) {
      incomingChar = Serial.read();

      // Check for newline character as the end of the string
      if (incomingChar == '\n') {
        break;
      }

      incomingString += incomingChar;
    }

    // Display the received string on the LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    
    lcd.setCursor(0, 1);
    lcd.print(incomingString);
  }

  // Your other loop logic can go here

  delay(100); // Add a small delay to avoid continuous LCD updates
}
