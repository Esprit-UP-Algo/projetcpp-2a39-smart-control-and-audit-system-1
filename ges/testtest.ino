#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
char data;

Servo servomotor;
const int servoPin = 10;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  servomotor.attach(servoPin);
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  lcd.print("waiting");
}

void loop() {
  String id = "";        // Store the ID sequence
  String password = "";  // Store the password sequence
  int index = 0;
  bool passwordMode = false;

  if (Serial.available() > 0) {
    data = Serial.read();

    if (data == '1') {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Enter ID:");
      while (index < 3) {
        char key = keypad.getKey();
        if (key) {
          id += key;
          lcd.print(key);  // Afficher le chiffre sur l'afficheur LCD
          index++;
          delay(500); // Delay for visibility
        }
      }
   
      Serial.print(id);

      // Ajouter une logique pour revenir à l'état initial ici
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("waiting");
      id = "";  // Réinitialiser l'ID
      index = 0;
    }
    else if (data == '2') {
     

         
          servomotor.write(0);  
          Serial.write('2');  

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("porteouvert");
}
else if(data == '3')
{
     servomotor.write(90); 
               Serial.write('3');  
   

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("portefermet");
        }
}
  }
